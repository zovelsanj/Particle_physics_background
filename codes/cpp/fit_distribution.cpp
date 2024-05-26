#include "root_basics.hpp"
#include<iostream>

void get_params(TF1* fit)
{
    Double_t mean = fit->GetParameter(1);
    Double_t sd = fit->GetParameter(2);
    std::cout << "mean: " << mean << ", sd: " << sd << ", var: " << pow(sd, 2) << std::endl;
}

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

    TCanvas *c1 = new TCanvas();
    hist->Draw();

    TF1 *fit = new TF1("Gauss fit", "gaus", 0, 5);
    hist->Fit("Gauss fit", "Q"); //`R` => stricts the fit curve range, `Q` => quiet terminal info
    get_params(fit);
}
