#include "root_basics.hpp"
#include <TCut.h>

std::vector<std::tuple<Double_t, Double_t>> get_data(int N, int scale = 1)
{
    TRandom *rn = new TRandom(31415);
    std::vector<std::tuple<Double_t, Double_t>> data;
    for (int i = 0; i < N; i++)
    {
        Double_t x = rn->Rndm(i) * scale;
        Double_t y = rn->Rndm(x) * scale;
        data.emplace_back(x, y);
    }
    return data;
}

void cut(const char *treepath)
{
    TCut cut1 = "y > 5";
    TCut cut2 = "x > 5";
    TFile *file = new TFile(treepath, "READ");
    TTree *tree = (TTree *)file->Get("tree");
    tree->Draw("y", cut1 && cut2);
}

void cut()
{
    basicFeatures *b = new basicFeatures();
    std::vector<std::tuple<Double_t, Double_t>> data = get_data(1000, 10);
    b->writeTree("output.root", data);
    cut("output.root");
}
