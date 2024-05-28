#include<TH1F.h>
#include<TF1.h>
#include<TCanvas.h>
#include<TRandom.h>
#include<TGraph.h>
#include<TGraphErrors.h>
#include<TLegend.h>

#pragma once
class basicFeatures
{
    private:
        /* data */
    public:
        void get_params(TF1 *);
        void get_legends(std::map<const char *, const TObject*>,  Option_t *, Double_t, Double_t, Double_t, Double_t);
};

void basicFeatures::get_params(TF1* fit)
{
    Double_t mean = fit->GetParameter(1);
    Double_t sd = fit->GetParameter(2);
    std::cout << "mean: " << mean << ", sd: " << sd << ", var: " << pow(sd, 2) << std::endl;
}

void basicFeatures::get_legends(std::map<const char *, const TObject*> legend_hashmap, Option_t *opt="l", Double_t xmin=0.7, Double_t ymin=0.7, Double_t xmax=0.9, Double_t ymax=0.9)
{
    TLegend *leg = new TLegend(xmin, ymin, xmax, ymax);
    leg->Draw();
    for(auto &it:legend_hashmap)
    {
        leg->AddEntry(it.second, it.first, opt);
    }
}