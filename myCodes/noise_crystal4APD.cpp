#include <iostream>
using namespace std;

float charge_sig[18];
float WF_time10[1024];
float WF_val10[1024];
float x[2];
float y[2];
float Time[18];
TProfile *WF6 = new TProfile("noise APD1","noise APD1",1024,-0.1,204.7);
void noise_crystal4APD(){
  TCanvas *canvas = new TCanvas("noise crystal4APd","noise crystal4APd");
  //TFile *pedestal = new TFile("/afs/cern.ch/work/a/ajofrehe/cern-summer-2016/H4Analysis/ntuples/analysis_4787.root");
  TFile *pedestal = new TFile("/afs/cern.ch/work/a/ajofrehe/cern-summer-2016/H4Analysis/ntuples/analysis_4684.root");
  TTree *mtree = (TTree*) pedestal->Get("h4");
  mtree->SetBranchAddress("charge_sig",charge_sig);
  mtree->SetBranchAddress("x",x);
  mtree->SetBranchAddress("y",y);
  mtree->SetBranchAddress("WF_time10",WF_time10);
  mtree->SetBranchAddress("WF_val10",WF_val10);
  mtree->SetBranchAddress("Time",Time);
  Long64_t nentries = mtree->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = mtree->LoadTree(jentry);
    nb = mtree->GetEntry(jentry);   nbytes += nb;
    if (TMath::Abs(x[1]-207)<2&&TMath::Abs(y[1]-294.5)<2){
      for (int i = 0;i < 1024;i++){
        WF6->Fill(WF_time10[i],WF_val10[i]);
      }
    }
  }
  WF6->Draw();
}