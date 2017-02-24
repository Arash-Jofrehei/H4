#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"
#include "TCanvas.h"
#include "TMath.h"
using namespace std;
float charge_sig[18];
float x[2];
float y[2];
float single_channel_weight[18] = {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0};
float set0_channel_weight[18] = {0,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,0};
float set1_channel_weight[18] = {0,0.521416,0.791515,0.524998,0,0,0.504333,0.506726,0.517119,0.50302,1,1.00179,0,0,0.512666,0.622622,0.899577,0};
float set2_channel_weight[18] = {0,0.932688,1.56220,0.850238,0,0,0.492765,0.482391,0.606879,0.508326,1,1.37240,0,0,0.963999,1.44540,0.862974,0};
float set3_channel_weight[18] = {0,1,1,1,0,0,0.4,0.4,0.4,0.4,1,1,0,0,1,1,1,0};
double integrated_charge_single = 0;
double integrated_charge_set0 = 0;
double integrated_charge_set1 = 0;
double integrated_charge_set2 = 0;
double integrated_charge_set3 = 0;
TF1 *crys = new TF1("crys","crystalball",10000,100000);
void xtal11calibs(){
  TCanvas *canvas = new TCanvas("xtal11calibs","xtal11calibs");
  //TFile *merged = new TFile("/afs/cern.ch/work/a/ajofrehe/cern-summer-2016/H4Analysis/ntuples/merged_crystal11.root");
  TFile *merged = new TFile("/afs/cern.ch/work/a/ajofrehe/cern-summer-2016/H4Analysis/ntuples/analysis_4683.root");
  TTree *mtree = (TTree*) merged->Get("h4");
  mtree->SetBranchAddress("charge_sig",charge_sig);
  mtree->SetBranchAddress("x", x);
  mtree->SetBranchAddress("y", y);
  TH1F *integrated_charge_hist_single = new TH1F("integrated_charge_hist_single","integrated charge (single channel)",140,10000,70000);
  TH1F *integrated_charge_hist_set0 = new TH1F("integrated_charge_hist_set0","integrated charge (uncalibrated)",180,10000,100000);
  TH1F *integrated_charge_hist_set1 = new TH1F("integrated_charge_hist_set1","integrated charge (set1)",140,10000,80000);
  TH1F *integrated_charge_hist_set2 = new TH1F("integrated_charge_hist_set2","integrated charge (set2)",140,10000,80000);
  TH1F *integrated_charge_hist_set3 = new TH1F("integrated_charge_hist_set3","integrated charge (set3)",140,10000,80000);
  TProfile *integrated_charge_x1_set0 = new TProfile("integrated_charge_x1_set0","integrated charge for a 4mm strip in Y at the center (uncalibrated)",60,209,239);
  TProfile *integrated_charge_x1_set1 = new TProfile("integrated_charge_x1_set1","integrated charge for a 4mm strip in Y at the center (set1)",60,209,239);
  TProfile *integrated_charge_x1_set2 = new TProfile("integrated_charge_x1_set2","integrated charge for a 4mm strip in Y at the center (set2)",60,209,239);
  TProfile *integrated_charge_y1_set0 = new TProfile("integrated_charge_y1_set0","integrated charge for a 4mm strip in X at the center (uncalibrated)",60,279.5,309.5);
  TProfile *integrated_charge_y1_set1 = new TProfile("integrated_charge_y1_set1","integrated charge for a 4mm strip in X at the center (set1)",60,279.5,309.5);
  TProfile *integrated_charge_y1_set2 = new TProfile("integrated_charge_y1_set2","integrated charge for a 4mm strip in X at the center (set2)",60,279.5,309.5);
  Long64_t nentries = mtree->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = mtree->LoadTree(jentry);
    nb = mtree->GetEntry(jentry);   nbytes += nb;
    if (TMath::Abs(x[1]-224)<500&&TMath::Abs(y[1]-294.5)<500){
      integrated_charge_single = 0;
      integrated_charge_set0 = 0;
      integrated_charge_set1 = 0;
      integrated_charge_set2 = 0;
      integrated_charge_set3 = 0;
      for (int i = 0;i < 18;i++){
        integrated_charge_single += charge_sig[i] * single_channel_weight[i];
        integrated_charge_set0 += charge_sig[i] * set0_channel_weight[i];
        integrated_charge_set1 += charge_sig[i] * set1_channel_weight[i];
        integrated_charge_set2 += charge_sig[i] * set2_channel_weight[i];
        integrated_charge_set3 += charge_sig[i] * set3_channel_weight[i];
      }
      if (TMath::Abs(x[1]-224)< 2&&TMath::Abs(y[1]-294.5)< 2){
        integrated_charge_hist_single->Fill(integrated_charge_single);
        integrated_charge_hist_set0->Fill(integrated_charge_set0);
        integrated_charge_hist_set1->Fill(integrated_charge_set1);
        integrated_charge_hist_set2->Fill(integrated_charge_set2);
        integrated_charge_hist_set3->Fill(integrated_charge_set3);
      }
      if (TMath::Abs(y[1]-294.5)< 2){
        integrated_charge_x1_set0->Fill(x[1],integrated_charge_set0);
        integrated_charge_x1_set1->Fill(x[1],integrated_charge_set1);
        integrated_charge_x1_set2->Fill(x[1],integrated_charge_set2);
      }
      if (TMath::Abs(x[1]-224.0)< 2){
        integrated_charge_y1_set0->Fill(y[1],integrated_charge_set0);
        integrated_charge_y1_set1->Fill(y[1],integrated_charge_set1);
        integrated_charge_y1_set2->Fill(y[1],integrated_charge_set2);
      }
    }
  }
  crys->SetParameters(800,integrated_charge_hist_single->GetMean(),0.5*integrated_charge_hist_single->GetStdDev(),1.1,2.1);
  integrated_charge_hist_single->Fit("crys");
  crys->SetParameters(800,integrated_charge_hist_set0->GetMean(),0.5*integrated_charge_hist_set0->GetStdDev(),1.1,2.1);
  integrated_charge_hist_set0->Fit("crys");
  crys->SetParameters(800,integrated_charge_hist_set1->GetMean(),0.5*integrated_charge_hist_set1->GetStdDev(),1.1,2.1);
  integrated_charge_hist_set1->Fit("crys");
  crys->SetParameters(800,integrated_charge_hist_set2->GetMean(),0.5*integrated_charge_hist_set2->GetStdDev(),1.1,2.1);
  integrated_charge_hist_set2->Fit("crys");
  crys->SetParameters(800,integrated_charge_hist_set3->GetMean(),0.5*integrated_charge_hist_set3->GetStdDev(),1.1,2.1);
  integrated_charge_hist_set3->Fit("crys");
}