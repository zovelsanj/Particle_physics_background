#include "root_basics.hpp"

void histogram()
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
}

void io()
{
    basicFeatures *b = new basicFeatures(); 
    b->writeRoot("output_test.root", &histogram);
    b->readRoot("output_test.root", true);
}