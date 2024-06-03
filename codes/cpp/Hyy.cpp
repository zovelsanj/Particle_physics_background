// The root file used here can be downloaded from https://atlas-opendata.web.cern.ch/atlas-opendata/samples/2020/GamGam/Data/
// This root file contains 81 entries such as runNumber, eventNumber, and so on.

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#define GET_VARIABLE_NAME(Variable) (#Variable)

void fill_histogram(TTree *tree, const char *branch_name, Int_t branch_value, Int_t branch_id, Int_t num_branches, Int_t nbins = 100)
{
    tree->SetBranchAddress(branch_name, &branch_value);

    int entries = tree->GetEntries();
    std::cout << "entries: " << entries << std::endl;
    std::vector<Int_t> branch_values;

    int step = branch_id + num_branches;

    for (int i = 0; i < entries; i += step)
    {
        branch_value = tree->GetEntry(i);
        std::cout << "branch_value: " << branch_value << std::endl;
        branch_values.push_back(branch_value);
    }
    Int_t min_x = *std::min_element(branch_values.begin(), branch_values.end());
    Int_t max_x = *std::min_element(branch_values.begin(), branch_values.end());
    std::cout << "min: " << min_x << ", max: " << max_x << std::endl;

    TH1F *hist = new TH1F("hist", "tree histogram", nbins, min_x, max_x);
    for (Int_t branch_value : branch_values)
        hist->Fill(branch_value);

    hist->Draw();
}

void readRoot(const char *rootfile)
{
    TFile *file = new TFile(rootfile, "READ");

    if (!file || file->IsZombie())
    {
        if (file)
            file->Close();
        throw std::runtime_error("File doesn't exist or is not readable: " + std::string(rootfile));
    }

    TTree *tree = (TTree *)file->Get("mini");
    Int_t runNumber;

    fill_histogram(tree, GET_VARIABLE_NAME(runNumber), runNumber, 0, 81);
}

void Hyy()
{
    readRoot("../../data/data_A.GamGam.root");
}
