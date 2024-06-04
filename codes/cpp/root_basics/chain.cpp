#include "root_basics.hpp"
#include <TChain.h>

void chain(std::string data_dir = "Particle_physics_background/codes/cpp/root_basics/", std::string extension = ".root")
{
    std::vector<std::string> rootfiles;
    basicFeatures *b = new basicFeatures();
    rootfiles = b->glob_files(data_dir, extension);

    TChain *chain = new TChain("tree");
    for (auto itr : rootfiles)
    {
        std::cout << "path: " << itr << std::endl;
        chain->Add(itr.c_str());
    }

    Double_t x;
    chain->SetBranchAddress("x", &x);
    Int_t entries = chain->GetEntries();
    std::cout << "entries: " << entries << std::endl;

    TH1F *hist = new TH1F("hist", "Chain Sample Plot", 100, 0, 1000);
    for (int i = 0; i < entries; i++)
    {
        x = chain->GetEntry(i);
        hist->Fill(x);
    }

    hist->Draw();
    
}