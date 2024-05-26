#include "root_basics.hpp"

void fit_distribution()
{
    TH1F *hist = new TH1F("hist", "Gaussian Distribution Fitting", 80, 0, 80);
    TRandom *rn = new TRandom(314);
    Double_t val;

    for (int i = 0; i < 100; i++)
    {
        val = rn->Gaus(1.0, 1.0)*10;
        hist->Fill(val);
    }
    
    hist->SetXTitle("Distribution");
    hist->SetYTitle("Entries");

    TCanvas *c1 = new TCanvas();
    hist->Draw();
    hist->Fit("gaus");
}
