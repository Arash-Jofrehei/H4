#include "TCanvas.h"
void fitGraphs(){
  TCanvas *canvas = new TCanvas("fitGraphs","fitGraphs");
  double energy[4] = {20,50,100,200};
  double energy_error[4] = {0.06,0.15,0.3,0.6}; // 3 permil
  double integrated_charge_resolution_single4APD[4] = {4.1636,2.64043,1.77,1.42};//{4.47,2.738,1.77,1.42};//{4.1636,2.64043,1.81,1.5};
  double integrated_charge_resolution_single4APD_error[4] = {0.1,0.06,0.03,0.04};//{0.09,0.0487,0.029,0.037};
  double integrated_charge_resolution_matrix4APD[4] = {5.758,3.18,2.01,1.40};
  double integrated_charge_resolution_matrix4APD_error[4] = {0.19,0.07,0.04,0.04};
  TF1 *res_fit = new TF1("res_fit","[0]/x + [1]/sqrt(x) + [2]",10,220);
  res_fit->SetParNames("noise term","stochastic term","constant term");
  res_fit->SetParLimits(0,0,300);
  res_fit->SetParLimits(1,0,300);
  res_fit->SetParLimits(2,0,300);
  TGraphErrors *integrated_charge_resolution_single4APD_vs_beam_energy = new TGraphErrors(3,energy,integrated_charge_resolution_single4APD,energy_error,integrated_charge_resolution_single4APD_error);
  TGraphErrors *integrated_charge_resolution_matrix4APD_vs_beam_energy = new TGraphErrors(4,energy,integrated_charge_resolution_matrix4APD,energy_error,integrated_charge_resolution_matrix4APD_error);
  integrated_charge_resolution_matrix4APD_vs_beam_energy->Draw();
  integrated_charge_resolution_matrix4APD_vs_beam_energy->Fit(res_fit);
  integrated_charge_resolution_single4APD_vs_beam_energy->Draw("same");
  integrated_charge_resolution_single4APD_vs_beam_energy->Fit(res_fit,"","",10,220);
}