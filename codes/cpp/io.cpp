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

std::vector<std::tuple<Double_t, Double_t>> get_data(int N)
{
    TRandom *rn = new TRandom(31415);
    std::vector<std::tuple<Double_t, Double_t>> data;
    for (int i = 0; i < N; i++)
    {
        Double_t x = rn->Rndm(i);
        Double_t y = rn->Rndm(x);
        data.emplace_back(x, y);
    }
    return data;
}

void io()
{
    basicFeatures *b = new basicFeatures();
    b->writeRoot("output_test.root", &histogram);
    b->readRoot("output_test.root", true);
    
    std::vector<std::tuple<Double_t, Double_t>> data = get_data(5);
    b->writeTree("output.root", data);
}
