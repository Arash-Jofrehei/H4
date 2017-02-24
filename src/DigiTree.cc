#include "interface/DigiTree.h"

DigiTree::DigiTree(uint64* idx, TTree* tree, string prefix)
{
    prefix_=prefix;
    tree_ = tree ? tree : new TTree();

    index=idx;
}

void DigiTree::Init(vector<string>& names)
{
    //---allocate enough space for all channels
    n_channels = names.size();
    channels = new int[n_channels];
    b_charge = new float[n_channels];
    b_slope = new float[n_channels];
    b_rms = new float[n_channels];
    Time = new float[n_channels];
    time_chi2 = new float[n_channels];
    maximum = new float[n_channels];
    amp_max = new float[n_channels];
    charge_tot = new float[n_channels];
    charge_sig = new float[n_channels];
    fit_ampl = new float[n_channels];
    fit_time = new float[n_channels];
    fit_chi2 = new float[n_channels];
    calibration = new float[n_channels];
    WF_time0 = new float[nsamples];
    WF_val0 = new float[nsamples];
    WF_time1 = new float[nsamples];
    WF_val1 = new float[nsamples];
    WF_time2 = new float[nsamples];
    WF_val2 = new float[nsamples];
    WF_time3 = new float[nsamples];
    WF_val3 = new float[nsamples];
    WF_time4 = new float[nsamples];
    WF_val4 = new float[nsamples];
    WF_time5 = new float[nsamples];
    WF_val5 = new float[nsamples];
    WF_time6 = new float[nsamples];
    WF_val6 = new float[nsamples];
    WF_time7 = new float[nsamples];
    WF_val7 = new float[nsamples];
    WF_time8 = new float[nsamples];
    WF_val8 = new float[nsamples];
    WF_time9 = new float[nsamples];
    WF_val9 = new float[nsamples];
    WF_time10 = new float[nsamples];
    WF_val10 = new float[nsamples];
    WF_time11 = new float[nsamples];
    WF_val11 = new float[nsamples];
    WF_time12 = new float[nsamples];
    WF_val12 = new float[nsamples];
    WF_time13 = new float[nsamples];
    WF_val13 = new float[nsamples];
    WF_time14 = new float[nsamples];
    WF_val14 = new float[nsamples];
    WF_time15 = new float[nsamples];
    WF_val15 = new float[nsamples];
    WF_time16 = new float[nsamples];
    WF_val16 = new float[nsamples];
    WF_time17 = new float[nsamples];
    WF_val17 = new float[nsamples];
    median_charge = new float[n_channels];
    subtracted_median_charge = new float[n_channels];

    //---channels branches
    /*for(int iCh=0; iCh<n_channels; iCh++)
    {
        channels[iCh]=iCh;
        tree_->Branch(names[iCh].c_str(), &(channels[iCh]), (names[iCh]+"/I").c_str());
    }*/
    //---global branches    
    string size_var = "n_"+prefix_+"channels";
    tree_->Branch("index", index, "index/l");
    tree_->Branch("beam_energy",&beam_energy,"beam_energy/F");
    tree_->Branch("xbar",&xbar,"xbar/D");
    tree_->Branch("ybar",&ybar,"ybar/D");
    tree_->Branch("subtracted_xbar",&subtracted_xbar,"subtracted_xbar/D");
    tree_->Branch("subtracted_ybar",&subtracted_ybar,"subtracted_ybar/D");
    tree_->Branch(size_var.c_str(), &n_channels, (size_var+"/i").c_str());
    tree_->Branch((prefix_+"b_charge").c_str(), b_charge, (prefix_+"b_charge["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"b_slope").c_str(), b_slope, (prefix_+"b_slope["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"b_rms").c_str(), b_rms, (prefix_+"b_rms["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"Time").c_str(), Time, (prefix_+"Time["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"time_chi2").c_str(), time_chi2, (prefix_+"time_chi2["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"maximum").c_str(), maximum, (prefix_+"maximum["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"amp_max").c_str(), amp_max, (prefix_+"amp_max["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"charge_tot").c_str(), charge_tot, (prefix_+"charge_tot["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"charge_sig").c_str(), charge_sig, (prefix_+"charge_sig["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"fit_ampl").c_str(), fit_ampl, (prefix_+"fit_ampl["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"fit_time").c_str(), fit_time, (prefix_+"fit_time["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"fit_chi2").c_str(), fit_chi2, (prefix_+"fit_chi2["+size_var+"]/F").c_str());
    tree_->Branch((prefix_+"calibration").c_str(), calibration, (prefix_+"calibration["+size_var+"]/F").c_str());
    tree_->Branch("WF_time0",WF_time0,TString::Format("WF_time0[%i]/F", nsamples));
    tree_->Branch("WF_val0",WF_val0,TString::Format("WF_val0[%i]/F", nsamples));
    tree_->Branch("WF_time1",WF_time1,TString::Format("WF_time1[%i]/F", nsamples));
    tree_->Branch("WF_val1",WF_val1,TString::Format("WF_val1[%i]/F", nsamples));
    tree_->Branch("WF_time2",WF_time2,TString::Format("WF_time2[%i]/F", nsamples));
    tree_->Branch("WF_val2",WF_val2,TString::Format("WF_val2[%i]/F", nsamples));
    tree_->Branch("WF_time3",WF_time3,TString::Format("WF_time3[%i]/F", nsamples));
    tree_->Branch("WF_val3",WF_val3,TString::Format("WF_val3[%i]/F", nsamples));
    tree_->Branch("WF_time4",WF_time4,TString::Format("WF_time4[%i]/F", nsamples));
    tree_->Branch("WF_val4",WF_val4,TString::Format("WF_val4[%i]/F", nsamples));
    tree_->Branch("WF_time5",WF_time5,TString::Format("WF_time5[%i]/F", nsamples));
    tree_->Branch("WF_val5",WF_val5,TString::Format("WF_val5[%i]/F", nsamples));
    tree_->Branch("WF_time6",WF_time6,TString::Format("WF_time6[%i]/F", nsamples));
    tree_->Branch("WF_val6",WF_val6,TString::Format("WF_val6[%i]/F", nsamples));
    tree_->Branch("WF_time7",WF_time7,TString::Format("WF_time7[%i]/F", nsamples));
    tree_->Branch("WF_val7",WF_val7,TString::Format("WF_val7[%i]/F", nsamples));
    tree_->Branch("WF_time8",WF_time8,TString::Format("WF_time8[%i]/F", nsamples));
    tree_->Branch("WF_val8",WF_val8,TString::Format("WF_val8[%i]/F", nsamples));
    tree_->Branch("WF_time9",WF_time9,TString::Format("WF_time9[%i]/F", nsamples));
    tree_->Branch("WF_val9",WF_val9,TString::Format("WF_val9[%i]/F", nsamples));
    tree_->Branch("WF_time10",WF_time10,TString::Format("WF_time10[%i]/F", nsamples));
    tree_->Branch("WF_val10",WF_val10,TString::Format("WF_val10[%i]/F", nsamples));
    tree_->Branch("WF_time11",WF_time11,TString::Format("WF_time11[%i]/F", nsamples));
    tree_->Branch("WF_val11",WF_val11,TString::Format("WF_val11[%i]/F", nsamples));
    tree_->Branch("WF_time12",WF_time12,TString::Format("WF_time12[%i]/F", nsamples));
    tree_->Branch("WF_val12",WF_val12,TString::Format("WF_val12[%i]/F", nsamples));
    tree_->Branch("WF_time13",WF_time13,TString::Format("WF_time13[%i]/F", nsamples));
    tree_->Branch("WF_val13",WF_val13,TString::Format("WF_val13[%i]/F", nsamples));
    tree_->Branch("WF_time14",WF_time14,TString::Format("WF_time14[%i]/F", nsamples));
    tree_->Branch("WF_val14",WF_val14,TString::Format("WF_val14[%i]/F", nsamples));
    tree_->Branch("WF_time15",WF_time15,TString::Format("WF_time15[%i]/F", nsamples));
    tree_->Branch("WF_val15",WF_val15,TString::Format("WF_val15[%i]/F", nsamples));
    tree_->Branch("WF_time16",WF_time16,TString::Format("WF_time16[%i]/F", nsamples));
    tree_->Branch("WF_val16",WF_val16,TString::Format("WF_val16[%i]/F", nsamples));
    tree_->Branch("WF_time17",WF_time17,TString::Format("WF_time17[%i]/F", nsamples));
    tree_->Branch("WF_val17",WF_val17,TString::Format("WF_val17[%i]/F", nsamples));
    tree_->Branch("median_charge",median_charge,TString::Format("median_charge[%i]/F", n_channels));
    tree_->Branch("subtracted_median_charge",subtracted_median_charge,TString::Format("subtracted_median_charge[%i]/F", n_channels));
}

DigiTree::~DigiTree()
{}
