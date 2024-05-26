#include<TH1F.h>
#include<TF1.h>
#include<TCanvas.h>
#include<TRandom.h>
#include<TGraph.h>
#include<TGraphErrors.h>

#pragma once
class basicFeatures
{
    private:
        /* data */
    public:
        void histogram();
        void graph(int N);
        void fit_distribution();
        void get_params(TF1 *fit);
};
