#include "DigitizerReco.h"

double log(double charge)
{
  if (charge>0)
    return TMath::Log10(charge);
  else
    return -100000000.0;
}
                                                    bool we_are_impinging_xtal11 = true;

float channel_weights_crystal4APD[18] = {2.41098,1.62535,1.49631,0,0,0.470364,0.954885,0.931846,1.15933,0.983237,1.3819,0,0,0.452602,1.86884,1.41348,0,0};
float channel_weights_crystal11[18] = {0,1,1,1,0,0,0.327*0.954885,0.327*0.931846,0.327*1.15933,0.327*0.983237,1,0.957,0,0,1,1.06,1,0};
float crystal_x[18] = {34,17,0,-17,-34,34,17,17,17,17,0,-17,-34,34,17,0,-17,-34};
float crystal_y[18] = {17,17,17,17,17,0,0,0,0,0,0,0,0,-17,-17,-17,-17,-17};

float channel17[1024];

float integrated_charge(float *histogram){
  float baseline = 0;
  for (int i = 15; i<100;i++) baseline += (histogram[i]-channel17[i])/85.0;
  int start = 0;
  for (int i = 100; i<500;i++){
    if ((histogram[i]-channel17[i]) - baseline > 15){
      start = i;
      break;
    }
  }
  int end = 0;
  for (int i = start; i<1024;i++){
    if ((histogram[i]-channel17[i]) - baseline < 15){
      end = i;
      break;
    }
  }
  //start = 35*5;
  end = start + 500;
  float charge = 0;
  for (int i = start; i<end;i++) charge += (histogram[i]-channel17[i]) - baseline;
  return charge;
}

float smoothed_vector[1024];
TH1F *histogram = new TH1F("histogram","histogram",1024,-0.1,204.7);

float *smoothed(float* vector,int radius = 10,int iteration = 1,bool saveMAX = true){
  for (int i = 0;i < 1024;i++) histogram->SetBinContent(i+1,vector[i]-channel17[i]);
  float interval[2*radius+1];
  int buffer = -1000;
  for (int epoch = 0; epoch < iteration ;epoch++){
    for (int i = 0; i < 1024; i++){
      if (i < radius || i > 1024-radius || (saveMAX == true && TMath::Abs(i+1 - histogram->GetMaximumBin()) < radius)) smoothed_vector[i] = histogram->GetBinContent(i+1);
      else{
        for (int j = 0; j < 2*radius+1 ;j++){
          interval[j] = histogram->GetBinContent(i+1+j-radius);
        }
        for (int j = 0;j < 2*radius+1 ;j++){
          for (int k = j;k < 2*radius+1 ;k++){
            if (interval[j] > interval[k]){
              buffer = interval[j];
              interval[j] = interval[k];
              interval[k] = buffer;
            }
          }
        }
        smoothed_vector[i] = interval[radius];
      }
    }
  }
  return smoothed_vector;
}

//----------Utils-------------------------------------------------------------------------
bool DigitizerReco::Begin(CfgManager& opts, uint64* index)
{
    //---inputs---
    channelsNames_ = opts.GetOpt<vector<string> >(instanceName_+".channelsNames");
    nSamples_ = opts.GetOpt<int>(instanceName_+".nSamples");
    tUnit_ = opts.GetOpt<float>(instanceName_+".tUnit");

    //---channels setup
    string templateTag="";
    if(opts.GetOpt<bool>(instanceName_+".templateTags"))
        for(auto& tag : opts.GetOpt<vector<string> >(instanceName_+".templateTags"))
            for(auto& run : opts.GetOpt<vector<string> >(tag+".runList"))
                if(run == opts.GetOpt<string>("h4reco.run"))
                    templateTag = tag;
    for(auto& channel : channelsNames_)
    {
        if(opts.GetOpt<bool>(channel+".type") && opts.GetOpt<string>(channel+".type") == "NINO")
            WFs[channel] = new WFClassNINO(opts.GetOpt<int>(channel+".polarity"), tUnit_);
        else
            WFs[channel] = new WFClass(opts.GetOpt<int>(channel+".polarity"), tUnit_);
        if(opts.GetOpt<bool>(channel+".templateFit"))
        {            
            TFile* templateFile = TFile::Open(opts.GetOpt<string>(channel+".templateFit.file", 0).c_str(), ".READ");
            TH1* wfTemplate=(TH1*)templateFile->Get((opts.GetOpt<string>(channel+".templateFit.file", 1)+
                                                     +"_"+templateTag).c_str());
            WFs[channel]->SetTemplate(wfTemplate);
            WFViewers[channel]=WFViewer(channel, (TH1F*)wfTemplate);
            RegisterSharedData(&WFViewers[channel], channel+"_view", true);
            templateFile->Close();
        }
        timeOpts_[channel] = opts.GetOpt<vector<float> >(channel+".timeOpts");
        RegisterSharedData(WFs[channel], channel, false);
    }
    
    //---outputs---
    string recoTreeName = opts.OptExist(instanceName_+".recoTreeName") ?
        opts.GetOpt<string>(instanceName_+".recoTreeName") : "reco";
    RegisterSharedData(new TTree(recoTreeName.c_str(), "reco_tree"), "reco_tree", true);
    recoTree_ = DigiTree(index, (TTree*)data_.back().obj);
    recoTree_.Init(channelsNames_);
    if(opts.GetOpt<int>(instanceName_+".fillWFtree"))
    {
        string wfTreeName = opts.OptExist(instanceName_+".wfTreeName") ?
            opts.GetOpt<string>(instanceName_+".wfTreeName") : "wf";
        RegisterSharedData(new TTree(wfTreeName.c_str(), "wf_tree"), "wf_tree", true);
        outWFTree_ = WFTree(channelsNames_.size(), nSamples_, index, (TTree*)data_.back().obj);
        outWFTree_.Init();
    }
}

bool DigitizerReco::ProcessEvent(const H4Tree& event, map<string, PluginBase*>& plugins, CfgManager& opts, bool important)
{
    if (important == false) return false;
    //---setup output event 
    int outCh=0;
    bool badEvent=false;
    bool fillWFtree=false;
    if(opts.GetOpt<int>(instanceName_+".fillWFtree"))
        fillWFtree = *recoTree_.index % opts.GetOpt<int>(instanceName_+".WFtreePrescale") == 0;
        
    //---read the digitizer
    //---set time reference from digitized trigger
    int timeRef=0;
    if(opts.GetOpt<int>(instanceName_+".useTrigRef"))
    {
        for(int iSample=nSamples_*8; iSample<nSamples_*9; ++iSample)
        {
            if(event.digiSampleValue[iSample] < 1000)
            {
                timeRef = iSample-nSamples_*8;
                break;
            }
        }
    }
    
    float sum[nSamples_];
    for (int i = 0;i < nSamples_;i++) sum[i] = 0;
    //float calib[12] = {0.780222,2.68862,2.03275,1.02364,0.95,0.93,1.17,0.98,1.90089,1.27835,2.06173,3.05746};
    //float calib[12] = {6.65444,5.10198,4.63361,1.39104,0.951252,0.932984,1.16544,0.981471,4,1.30581,5.34046,4};
    //float calib[12] = {2.29894,1.72464,1.60079,0.470221,0.951252,0.932984,1.16544,0.981471,1.35214,0.451124,1.80526,1.3819};
    float calib[12] = {1.28673,1.37646,0.862157,0.38369,0.9088*0.951252,0.9088*0.932984,0.9088*1.16544,0.9088*0.981471,1.14679,0.234947,1.55411,0.795243};
    //float calib[12] = {2.29894,1.72464,1.60079,0.470221,0,0,0,0,1.35214,0.451124,1.80526,1.3819};
    //float calib[12] = {4.22939,3.03897,1.9653,1,0.810848,0.552276,0.541423,1,2.11745,1,3.73868,3.58402};
    //---user channels
    for(auto& channel : channelsNames_)
    {
        //---reset and read new WFs
        WFs[channel]->Reset();
        int digiGr = opts.GetOpt<int>(channel+".digiGroup");
        int digiCh = opts.GetOpt<int>(channel+".digiChannel");
        int offset = event.digiMap.at(make_pair(digiGr, digiCh));
        /*int digiGr1 = opts.GetOpt<int>("xtal1.digiGroup");
        int digiCh1 = opts.GetOpt<int>("xtal1.digiChannel");
        int offset1 = event.digiMap.at(make_pair(digiGr1, digiCh1));
        int digiGr2 = opts.GetOpt<int>("xtal2.digiGroup");
        int digiCh2 = opts.GetOpt<int>("xtal2.digiChannel");
        int offset2 = event.digiMap.at(make_pair(digiGr2, digiCh2));
        int digiGr3 = opts.GetOpt<int>("xtal3.digiGroup");
        int digiCh3 = opts.GetOpt<int>("xtal3.digiChannel");
        int offset3 = event.digiMap.at(make_pair(digiGr3, digiCh3));
        int digiGr6 = opts.GetOpt<int>("xtal6.digiGroup");
        int digiCh6 = opts.GetOpt<int>("xtal6.digiChannel");
        int offset6 = event.digiMap.at(make_pair(digiGr6, digiCh6));
        int digiGr7 = opts.GetOpt<int>("xtal4apd_1.digiGroup");
        int digiCh7 = opts.GetOpt<int>("xtal4apd_1.digiChannel");
        int offset7 = event.digiMap.at(make_pair(digiGr7, digiCh7));
        int digiGr8 = opts.GetOpt<int>("xtal4apd_2.digiGroup");
        int digiCh8 = opts.GetOpt<int>("xtal4apd_2.digiChannel");
        int offset8 = event.digiMap.at(make_pair(digiGr8, digiCh8));
        int digiGr9 = opts.GetOpt<int>("xtal4apd_3.digiGroup");
        int digiCh9 = opts.GetOpt<int>("xtal4apd_3.digiChannel");
        int offset9 = event.digiMap.at(make_pair(digiGr9, digiCh9));
        int digiGr10 = opts.GetOpt<int>("xtal4apd_4.digiGroup");
        int digiCh10 = opts.GetOpt<int>("xtal4apd_4.digiChannel");
        int offset10 = event.digiMap.at(make_pair(digiGr10, digiCh10));
        int digiGr11 = opts.GetOpt<int>("xtal11.digiGroup");
        int digiCh11 = opts.GetOpt<int>("xtal11.digiChannel");
        int offset11 = event.digiMap.at(make_pair(digiGr11, digiCh11));
        int digiGr13 = opts.GetOpt<int>("xtal13.digiGroup");
        int digiCh13 = opts.GetOpt<int>("xtal13.digiChannel");
        int offset13 = event.digiMap.at(make_pair(digiGr13, digiCh13));
        int digiGr14 = opts.GetOpt<int>("xtal14.digiGroup");
        int digiCh14 = opts.GetOpt<int>("xtal14.digiChannel");
        int offset14 = event.digiMap.at(make_pair(digiGr14, digiCh14));
        int digiGr15 = opts.GetOpt<int>("xtal15.digiGroup");
        int digiCh15 = opts.GetOpt<int>("xtal15.digiChannel");
        int offset15 = event.digiMap.at(make_pair(digiGr15, digiCh15));
        int digiGr16 = opts.GetOpt<int>("xtal16.digiGroup");
        int digiCh16 = opts.GetOpt<int>("xtal16.digiChannel");
        int offset16 = event.digiMap.at(make_pair(digiGr16, digiCh16));
        int digiGr18 = opts.GetOpt<int>("xtal18.digiGroup");
        int digiCh18 = opts.GetOpt<int>("xtal18.digiChannel");
        int offset18 = event.digiMap.at(make_pair(digiGr18, digiCh18));*/
        for(int iSample=offset; iSample<offset+nSamples_; ++iSample)
        {
            //---H4DAQ bug: sometimes ADC value is out of bound.
            //---skip everything if one channel is bad
            if(event.digiSampleValue[iSample] > 10000)
            {
                cout << ">>>DigiReco WARNING: skipped event" << endl;
                return false;
            }
            /*if (offset != offset13)*/ WFs[channel]->AddSample(event.digiSampleValue[iSample]);//-event.digiSampleValue[iSample-offset+offset18]);
            //if (offset != offset18) WFs[channel]->AddSample(event.digiSampleValue[iSample]-event.digiSampleValue[iSample-offset+offset18]);
            //sum[iSample-offset] += event.digiSampleValue[iSample]-event.digiSampleValue[iSample-offset+offset18];
            //WFs["xtal18"]->AddSample(sum[iSample-offset]); //it's OK because WFs resets
        }
        for (int iSample=0;iSample<nSamples_;iSample++){
          if(event.digiSampleValue[iSample] > 10000)
          {
            cout << ">>>DigiReco WARNING: skipped event" << endl;
            return false;
          }
          //WFs["xtal13"]->AddSample(calib[0]*(event.digiSampleValue[iSample+offset1]-event.digiSampleValue[iSample+offset18])+calib[1]*(event.digiSampleValue[iSample+offset2]-event.digiSampleValue[iSample+offset18])+calib[2]*(event.digiSampleValue[iSample+offset3]-event.digiSampleValue[iSample+offset18])+calib[3]*(event.digiSampleValue[iSample+offset6])+calib[4]*(event.digiSampleValue[iSample+offset7])+calib[5]*(event.digiSampleValue[iSample+offset8])+calib[6]*(event.digiSampleValue[iSample+offset9])+calib[7]*(event.digiSampleValue[iSample+offset10])+calib[8]*(event.digiSampleValue[iSample+offset11]-event.digiSampleValue[iSample+offset18])+calib[9]*(event.digiSampleValue[iSample+offset14]-event.digiSampleValue[iSample+offset18])+calib[10]*(event.digiSampleValue[iSample+offset15]-event.digiSampleValue[iSample+offset18])+calib[11]*(event.digiSampleValue[iSample+offset16]-event.digiSampleValue[iSample+offset18]));
          //WFs["xtal18"]->AddSample(calib[0]*(event.digiSampleValue[iSample+offset1]-event.digiSampleValue[iSample+offset18])+calib[1]*(event.digiSampleValue[iSample+offset2]-event.digiSampleValue[iSample+offset18])+calib[2]*(event.digiSampleValue[iSample+offset3]-event.digiSampleValue[iSample+offset18])+calib[3]*(event.digiSampleValue[iSample+offset6]-event.digiSampleValue[iSample+offset18])+calib[4]*(event.digiSampleValue[iSample+offset7]-event.digiSampleValue[iSample+offset18])+calib[5]*(event.digiSampleValue[iSample+offset8]-event.digiSampleValue[iSample+offset18])+calib[6]*(event.digiSampleValue[iSample+offset9]-event.digiSampleValue[iSample+offset18])+calib[7]*(event.digiSampleValue[iSample+offset10]-event.digiSampleValue[iSample+offset18])+calib[8]*(event.digiSampleValue[iSample+offset11]-event.digiSampleValue[iSample+offset18])+calib[9]*(event.digiSampleValue[iSample+offset14]-event.digiSampleValue[iSample+offset18])+calib[10]*(event.digiSampleValue[iSample+offset15]-event.digiSampleValue[iSample+offset18])+calib[11]*(event.digiSampleValue[iSample+offset16]-event.digiSampleValue[iSample+offset18]));
          //WFs["xtal18"]->AddSample(calib[0]*(event.digiSampleValue[iSample+offset1])+calib[1]*(event.digiSampleValue[iSample+offset2])+calib[2]*(event.digiSampleValue[iSample+offset3])+calib[3]*(event.digiSampleValue[iSample+offset6])+calib[4]*(event.digiSampleValue[iSample+offset7])+calib[5]*(event.digiSampleValue[iSample+offset8])+calib[6]*(event.digiSampleValue[iSample+offset9])+calib[7]*(event.digiSampleValue[iSample+offset10])+calib[8]*(event.digiSampleValue[iSample+offset11])+calib[9]*(event.digiSampleValue[iSample+offset14])+calib[10]*(event.digiSampleValue[iSample+offset15])+calib[11]*(event.digiSampleValue[iSample+offset16]));
        }
    }
    
    //---compute reco variables
    for(auto& channel : channelsNames_)
    {
        //---subtract a specified channel if requested
        if(opts.OptExist(channel+".subtractChannel"))
            *WFs[channel] -= *WFs[opts.GetOpt<string>(channel+".subtractChannel")];        
        WFs[channel]->SetBaselineWindow(opts.GetOpt<int>(channel+".baselineWin", 0), 
                                        opts.GetOpt<int>(channel+".baselineWin", 1));
        WFs[channel]->SetSignalWindow(opts.GetOpt<int>(channel+".signalWin", 0)+timeRef, 
                                      opts.GetOpt<int>(channel+".signalWin", 1)+timeRef);
        WFBaseline baselineInfo = WFs[channel]->SubtractBaseline();
        pair<float, float> timeInfo = WFs[channel]->GetTime(opts.GetOpt<string>(channel+".timeType"), timeOpts_[channel]);
        recoTree_.b_charge[outCh] = WFs[channel]->GetIntegral(opts.GetOpt<int>(channel+".baselineInt", 0), 
                                                             opts.GetOpt<int>(channel+".baselineInt", 1));        
        recoTree_.b_slope[outCh] = baselineInfo.slope;
        recoTree_.b_rms[outCh] = baselineInfo.rms;
        recoTree_.Time[outCh] = timeInfo.first;
        recoTree_.time_chi2[outCh] = timeInfo.second;
        recoTree_.maximum[outCh] = WFs[channel]->GetAmpMax();
        recoTree_.amp_max[outCh] = WFs[channel]->GetInterpolatedAmpMax(-1,-1,opts.GetOpt<int>(channel+".signalWin", 2));
        recoTree_.charge_tot[outCh] = WFs[channel]->GetModIntegral(opts.GetOpt<int>(channel+".baselineInt", 1), 
                                                                 nSamples_);
        recoTree_.charge_sig[outCh] = WFs[channel]->GetSignalIntegral(opts.GetOpt<int>(channel+".signalInt", 0), 
                                                                     opts.GetOpt<int>(channel+".signalInt", 1));
        //---template fit (only specified channels)
        WFFitResults fitResults{-1, -1000, -1};
        if(opts.GetOpt<bool>(channel+".templateFit"))
        {
            fitResults = WFs[channel]->TemplateFit(opts.GetOpt<float>(channel+".templateFit.fitWin", 0),
                                                   opts.GetOpt<int>(channel+".templateFit.fitWin", 1),
                                                   opts.GetOpt<int>(channel+".templateFit.fitWin", 2));
            recoTree_.fit_ampl[outCh] = fitResults.ampl;
            recoTree_.fit_time[outCh] = fitResults.time;
            recoTree_.fit_chi2[outCh] = fitResults.chi2;
        }
	//---calibration constant for each channel if needed
	if(opts.OptExist(channel+".calibration.calibrationConst"))
	  recoTree_.calibration[outCh]=opts.GetOpt<float>(channel+".calibration.calibrationConst");
	else
	  recoTree_.calibration[outCh]=1;
	


        //---WFs---
        /*if(fillWFtree)
        {
            vector<float>* analizedWF = WFs[channel]->GetSamples();
            for(int jSample=0; jSample<analizedWF->size(); ++jSample)
            {
              recoTree_.WF_time[outCh][jSample] = jSample*tUnit_;
              recoTree_.WF_val[outCh][jSample] = analizedWF->at(jSample);
            }
        }*/
        //---increase output tree channel counter
        ++outCh;
    }
    
    if(fillWFtree){
    
    vector<float>* analizedWF = WFs["xtal1"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time0[jSample] = jSample*tUnit_;
      recoTree_.WF_val0[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal2"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time1[jSample] = jSample*tUnit_;
      recoTree_.WF_val1[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal3"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time2[jSample] = jSample*tUnit_;
      recoTree_.WF_val2[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal4"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time3[jSample] = jSample*tUnit_;
      recoTree_.WF_val3[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal5"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time4[jSample] = jSample*tUnit_;
      recoTree_.WF_val4[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal6"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time5[jSample] = jSample*tUnit_;
      recoTree_.WF_val5[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal4apd_1"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time6[jSample] = jSample*tUnit_;
      recoTree_.WF_val6[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal4apd_2"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time7[jSample] = jSample*tUnit_;
      recoTree_.WF_val7[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal4apd_3"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time8[jSample] = jSample*tUnit_;
      recoTree_.WF_val8[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal4apd_4"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time9[jSample] = jSample*tUnit_;
      recoTree_.WF_val9[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal11"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time10[jSample] = jSample*tUnit_;
      recoTree_.WF_val10[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal12"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time11[jSample] = jSample*tUnit_;
      recoTree_.WF_val11[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal13"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time12[jSample] = jSample*tUnit_;
      recoTree_.WF_val12[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal14"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time13[jSample] = jSample*tUnit_;
      recoTree_.WF_val13[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal15"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time14[jSample] = jSample*tUnit_;
      recoTree_.WF_val14[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal16"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time15[jSample] = jSample*tUnit_;
      recoTree_.WF_val15[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal17"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time16[jSample] = jSample*tUnit_;
      recoTree_.WF_val16[jSample] = analizedWF->at(jSample);
    }
    analizedWF = WFs["xtal18"]->GetSamples();
    for(int jSample=0; jSample<analizedWF->size(); ++jSample)
    {
      recoTree_.WF_time17[jSample] = jSample*tUnit_;
      recoTree_.WF_val17[jSample] = analizedWF->at(jSample);
    }
    }
    for (int i = 0;i < 1024;i++) channel17[i] = 0;
    if (important){
      if (we_are_impinging_xtal11){
        recoTree_.median_charge[0] = integrated_charge(recoTree_.WF_val0);
        recoTree_.median_charge[3] = integrated_charge(smoothed(smoothed(recoTree_.WF_val3,15,2,false),150,1));
        recoTree_.median_charge[5] = integrated_charge(recoTree_.WF_val5);
        recoTree_.median_charge[11] = integrated_charge(smoothed(smoothed(recoTree_.WF_val11,15,2,false),150,1));
        recoTree_.median_charge[13] = integrated_charge(recoTree_.WF_val13);
        recoTree_.median_charge[16] = integrated_charge(smoothed(smoothed(recoTree_.WF_val16,15,2,false),150,1));
      }
      else{
        recoTree_.median_charge[0] = integrated_charge(smoothed(smoothed(recoTree_.WF_val0,15,2,false),150,1));
        recoTree_.median_charge[3] = integrated_charge(recoTree_.WF_val3);
        recoTree_.median_charge[5] = integrated_charge(smoothed(smoothed(recoTree_.WF_val5,15,2,false),150,1));
        recoTree_.median_charge[11] = integrated_charge(recoTree_.WF_val11);
        recoTree_.median_charge[13] = integrated_charge(smoothed(smoothed(recoTree_.WF_val13,15,2,false),150,1));
        recoTree_.median_charge[16] = integrated_charge(recoTree_.WF_val16);
      }
      recoTree_.median_charge[1] = integrated_charge(smoothed(smoothed(recoTree_.WF_val1,15,2,false),150,1));
      recoTree_.median_charge[2] = integrated_charge(smoothed(smoothed(recoTree_.WF_val2,15,2,false),150,1));
      recoTree_.median_charge[4] = integrated_charge(recoTree_.WF_val4);
      recoTree_.median_charge[6] = integrated_charge(smoothed(smoothed(recoTree_.WF_val6,15,2,false),150,1));
      recoTree_.median_charge[7] = integrated_charge(smoothed(smoothed(recoTree_.WF_val7,15,2,false),150,1));
      recoTree_.median_charge[8] = integrated_charge(smoothed(smoothed(recoTree_.WF_val8,15,2,false),150,1));
      recoTree_.median_charge[9] = integrated_charge(smoothed(smoothed(recoTree_.WF_val9,15,2,false),150,1));
      recoTree_.median_charge[10] = integrated_charge(smoothed(smoothed(recoTree_.WF_val10,15,2,false),150,1));
      recoTree_.median_charge[12] = integrated_charge(recoTree_.WF_val12);
      recoTree_.median_charge[14] = integrated_charge(smoothed(smoothed(recoTree_.WF_val14,15,2,false),150,1));
      recoTree_.median_charge[15] = integrated_charge(smoothed(smoothed(recoTree_.WF_val15,15,2,false),150,1));
      recoTree_.median_charge[17] = integrated_charge(recoTree_.WF_val17);
      
      for (int i = 0;i < 1024;i++) channel17[i] = recoTree_.WF_val17[i];
      
      if (we_are_impinging_xtal11){
        recoTree_.subtracted_median_charge[0] = integrated_charge(recoTree_.WF_val0);
        recoTree_.subtracted_median_charge[3] = integrated_charge(smoothed(smoothed(recoTree_.WF_val3,15,2,false),150,1));
        recoTree_.subtracted_median_charge[5] = integrated_charge(recoTree_.WF_val5);
        recoTree_.subtracted_median_charge[11] = integrated_charge(smoothed(smoothed(recoTree_.WF_val11,15,2,false),150,1));
        recoTree_.subtracted_median_charge[13] = integrated_charge(recoTree_.WF_val13);
        recoTree_.subtracted_median_charge[16] = integrated_charge(smoothed(smoothed(recoTree_.WF_val16,15,2,false),150,1));
      }
      else{
        recoTree_.subtracted_median_charge[0] = integrated_charge(smoothed(smoothed(recoTree_.WF_val0,15,2,false),150,1));
        recoTree_.subtracted_median_charge[3] = integrated_charge(recoTree_.WF_val3);
        recoTree_.subtracted_median_charge[5] = integrated_charge(smoothed(smoothed(recoTree_.WF_val5,15,2,false),150,1));
        recoTree_.subtracted_median_charge[11] = integrated_charge(recoTree_.WF_val11);
        recoTree_.subtracted_median_charge[13] = integrated_charge(smoothed(smoothed(recoTree_.WF_val13,15,2,false),150,1));
        recoTree_.subtracted_median_charge[16] = integrated_charge(recoTree_.WF_val16);
      }
      recoTree_.subtracted_median_charge[1] = integrated_charge(smoothed(smoothed(recoTree_.WF_val1,15,2,false),150,1));
      recoTree_.subtracted_median_charge[2] = integrated_charge(smoothed(smoothed(recoTree_.WF_val2,15,2,false),150,1));
      recoTree_.subtracted_median_charge[4] = integrated_charge(recoTree_.WF_val4);
      recoTree_.subtracted_median_charge[6] = integrated_charge(smoothed(smoothed(recoTree_.WF_val6,15,2,false),150,1));
      recoTree_.subtracted_median_charge[7] = integrated_charge(smoothed(smoothed(recoTree_.WF_val7,15,2,false),150,1));
      recoTree_.subtracted_median_charge[8] = integrated_charge(smoothed(smoothed(recoTree_.WF_val8,15,2,false),150,1));
      recoTree_.subtracted_median_charge[9] = integrated_charge(smoothed(smoothed(recoTree_.WF_val9,15,2,false),150,1));
      recoTree_.subtracted_median_charge[10] = integrated_charge(smoothed(smoothed(recoTree_.WF_val10,15,2,false),150,1));
      recoTree_.subtracted_median_charge[12] = integrated_charge(recoTree_.WF_val12);
      recoTree_.subtracted_median_charge[14] = integrated_charge(smoothed(smoothed(recoTree_.WF_val14,15,2,false),150,1));
      recoTree_.subtracted_median_charge[15] = integrated_charge(smoothed(smoothed(recoTree_.WF_val15,15,2,false),150,1));
      recoTree_.subtracted_median_charge[17] = 0;
    }
    else{
      for (int i = 0; i < 18;i++) recoTree_.median_charge[i] = 0;
      for (int i = 0; i < 18;i++) recoTree_.subtracted_median_charge[i] = 0;
    }
    
    recoTree_.beam_energy = 100;
    /*recoTree_.xbar = 207.0 + 17*(log(recoTree_.charge_sig[0])-log(recoTree_.charge_sig[2])+log(recoTree_.charge_sig[5])-log(recoTree_.charge_sig[10])+log(recoTree_.charge_sig[13])-log(recoTree_.charge_sig[15]))/(log(recoTree_.charge_sig[2])+log(recoTree_.charge_sig[0])+log(recoTree_.charge_sig[5])+log(recoTree_.charge_sig[10])+log(recoTree_.charge_sig[13])+log(recoTree_.charge_sig[15]));
    recoTree_.ybar = 294.5 + 17*(log(recoTree_.charge_sig[2])+log(recoTree_.charge_sig[0])+log(recoTree_.charge_sig[1])-log(recoTree_.charge_sig[14])-log(recoTree_.charge_sig[13])-log(recoTree_.charge_sig[15]))/(log(recoTree_.charge_sig[2])+log(recoTree_.charge_sig[0])+log(recoTree_.charge_sig[1])+log(recoTree_.charge_sig[14])+log(recoTree_.charge_sig[13])+log(recoTree_.charge_sig[15]));*/
    
    float energy_sum;
    float position_weight[18];
    float weight_sum;
    if (we_are_impinging_xtal11){
      energy_sum = 0;
      for (int i = 0;i < 18;i++) energy_sum += channel_weights_crystal11[i]*recoTree_.median_charge[i];
      for (int i = 0;i < 18;i++){
        if (channel_weights_crystal11[i]*recoTree_.median_charge[i]/energy_sum < 0.001){
          position_weight[i] = 0;
          continue;
        }
        position_weight[i] = 3 + TMath::Log10(channel_weights_crystal11[i]*recoTree_.median_charge[i]/energy_sum);
      }
      weight_sum = 0;
      for (int i = 0;i < 18;i++) weight_sum += position_weight[i];
      recoTree_.xbar = 0;
      recoTree_.ybar = 0;
      for (int i = 0;i < 18;i++) recoTree_.xbar += position_weight[i] * crystal_x[i] / weight_sum;
      for (int i = 0;i < 18;i++) recoTree_.ybar += position_weight[i] * crystal_y[i] / weight_sum;
    }
    else{
      energy_sum = 0;
      for (int i = 0;i < 18;i++) energy_sum += channel_weights_crystal4APD[i]*recoTree_.median_charge[i];
      for (int i = 0;i < 18;i++){
        if (channel_weights_crystal4APD[i]*recoTree_.median_charge[i]/energy_sum < 0.001){
          position_weight[i] = 0;
          continue;
        }
        position_weight[i] = 3 + TMath::Log10(channel_weights_crystal4APD[i]*recoTree_.median_charge[i]/energy_sum);
      }
      weight_sum = 0;
      for (int i = 0;i < 18;i++) weight_sum += position_weight[i];
      recoTree_.xbar = 0;
      recoTree_.ybar = 0;
      for (int i = 0;i < 18;i++) recoTree_.xbar += position_weight[i] * crystal_x[i] / weight_sum;
      for (int i = 0;i < 18;i++) recoTree_.ybar += position_weight[i] * crystal_y[i] / weight_sum;
    }
    
    if (we_are_impinging_xtal11){
      energy_sum = 0;
      for (int i = 0;i < 18;i++) energy_sum += channel_weights_crystal11[i]*recoTree_.subtracted_median_charge[i];
      for (int i = 0;i < 18;i++){
        if (channel_weights_crystal11[i]*recoTree_.subtracted_median_charge[i]/energy_sum < 0.001){
          position_weight[i] = 0;
          continue;
        }
        position_weight[i] = 3 + TMath::Log10(channel_weights_crystal11[i]*recoTree_.subtracted_median_charge[i]/energy_sum);
      }
      weight_sum = 0;
      for (int i = 0;i < 18;i++) weight_sum += position_weight[i];
      recoTree_.subtracted_xbar = 0;
      recoTree_.subtracted_ybar = 0;
      for (int i = 0;i < 18;i++) recoTree_.subtracted_xbar += position_weight[i] * crystal_x[i] / weight_sum;
      for (int i = 0;i < 18;i++) recoTree_.subtracted_ybar += position_weight[i] * crystal_y[i] / weight_sum;
    }
    else{
      energy_sum = 0;
      for (int i = 0;i < 18;i++) energy_sum += channel_weights_crystal4APD[i]*recoTree_.subtracted_median_charge[i];
      for (int i = 0;i < 18;i++){
        if (channel_weights_crystal4APD[i]*recoTree_.subtracted_median_charge[i]/energy_sum < 0.001){
          position_weight[i] = 0;
          continue;
        }
        position_weight[i] = 3 + TMath::Log10(channel_weights_crystal4APD[i]*recoTree_.subtracted_median_charge[i]/energy_sum);
      }
      weight_sum = 0;
      for (int i = 0;i < 18;i++) weight_sum += position_weight[i];
      recoTree_.subtracted_xbar = 0;
      recoTree_.subtracted_ybar = 0;
      for (int i = 0;i < 18;i++) recoTree_.subtracted_xbar += position_weight[i] * crystal_x[i] / weight_sum;
      for (int i = 0;i < 18;i++) recoTree_.subtracted_ybar += position_weight[i] * crystal_y[i] / weight_sum;
    }
    
    //---fill the output trees if the event is good
    if(!badEvent)
    {
        //---reco var
        recoTree_.Fill();
        //---WFs
        if(fillWFtree)
            outWFTree_.Fill();
    }

    return true;
}