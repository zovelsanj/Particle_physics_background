#include "root_basics.hpp"
#include<iostream>

void fit_distribution()
{
    TH1F *hist = new TH1F("hist", "Gaussian Distribution Fitting", 80, 0, 10);
    TRandom *rn = new TRandom(314);
    Double_t val;

    for (int i = 0; i < 100; i++)
    {
        val = rn->Gaus(5.0, 1.0);
        hist->Fill(val);
    }
    
    hist->SetXTitle("Distribution");
    hist->SetYTitle("Entries");
    hist->SetStats(0);

    TCanvas *c1 = new TCanvas();
    hist->Draw();

    TF1 *fit = new TF1("Gauss fit", "gaus", 0, 5);
    hist->Fit("Gauss fit", "Q"); //`R` => stricts the fit curve range, `Q` => quiet terminal info
    basicFeatures *b = new basicFeatures(); 
    b->get_params(fit);
    
    std::map<const char *, const TObject*> legend_hashmap;
    legend_hashmap["histogram"] = hist;
    legend_hashmap["gaussian fit"] = fit;

    b->get_legends(legend_hashmap);
}
