#ifndef __DIGI_TREE__
#define __DIGI_TREE__

#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include "TTree.h"
#include "TString.h"

using namespace std;

typedef unsigned long int uint32;
typedef unsigned long long int uint64;
 
//****************************************************************************************
const int nsamples = 1024;
class DigiTree
{
public: 
    //---ctors---
    DigiTree(){};
    DigiTree(uint64* idx, TTree* tree=NULL, string prefix="");
    //---dtor---
    ~DigiTree();

    //---utils---
    void Init(vector<string>& names);
    void Fill() {tree_->Fill();};
    
    TTree*        tree_; 
    string        prefix_;

    uint64*       index;
    unsigned int  n_channels;
    float         beam_energy;
    double        xbar;
    double        ybar;
    float*        b_charge;
    float*        b_slope;
    float*        b_rms;
    float*        Time;
    float*        time_chi2;
    float*        maximum;
    float*        amp_max;
    float*        charge_tot;
    float*        charge_sig;
    float*        fit_ampl;
    float*        fit_time;
    float*        fit_chi2;
    int*          channels;
    float*        calibration;
    //int           (*WF_ch)[nsamples];
    //float         (*WF_time)[nsamples];
    //float         (*WF_val)[nsamples];
    float*        WF_time0;
    float*        WF_val0;
    float*        WF_time1;
    float*        WF_val1;
    float*        WF_time2;
    float*        WF_val2;
    float*        WF_time3;
    float*        WF_val3;
    float*        WF_time4;
    float*        WF_val4;
    float*        WF_time5;
    float*        WF_val5;
    float*        WF_time6;
    float*        WF_val6;
    float*        WF_time7;
    float*        WF_val7;
    float*        WF_time8;
    float*        WF_val8;
    float*        WF_time9;
    float*        WF_val9;
    float*        WF_time10;
    float*        WF_val10;
    float*        WF_time11;
    float*        WF_val11;
    float*        WF_time12;
    float*        WF_val12;
    float*        WF_time13;
    float*        WF_val13;
    float*        WF_time14;
    float*        WF_val14;
    float*        WF_time15;
    float*        WF_val15;
    float*        WF_time16;
    float*        WF_val16;
    float*        WF_time17;
    float*        WF_val17;
    float*        median_charge;
    float*        subtracted_median_charge;
    double        subtracted_xbar;
    double        subtracted_ybar;
};

#endif
