#include<TH1F.h>
#include<TF1.h>
#include<TCanvas.h>
#include<TRandom.h>
#include<TGraph.h>
#include<TGraphErrors.h>
#include<TLegend.h>
#include<TArrow.h>
#include<TLatex.h>

#pragma once
class basicFeatures
{
    private:
        /* data */
    public:
        void getParams(TF1 *);
        void getLegends(std::map<const char *, const TObject*>, Int_t, Option_t *, Double_t, Double_t, Double_t, Double_t);
};

void basicFeatures::getParams(TF1* fit)
{
    Double_t mean = fit->GetParameter(1);
    Double_t sd = fit->GetParameter(2);
    std::cout << "mean: " << mean << ", sd: " << sd << ", var: " << pow(sd, 2) << std::endl;
}

void basicFeatures::getLegends(std::map<const char *, const TObject*> legend_hashmap, Int_t border_size=4, Option_t *opt="l", Double_t xmin=0.7, Double_t ymin=0.7, Double_t xmax=0.85, Double_t ymax=0.85)
{
    TLegend *leg = new TLegend(xmin, ymin, xmax, ymax);
    leg->Draw();
    leg->SetBorderSize(border_size);
    for(auto &it:legend_hashmap)
    {
        leg->AddEntry(it.second, it.first, opt);
    }
}
    