#include<TH1F.h>
#include<TF1.h>
#include<TCanvas.h>
#include<TRandom.h>
#include<TGraph.h>
#include<TGraphErrors.h>
#include<TLegend.h>
#include<TArrow.h>
#include<TLatex.h>
#include<TFile.h>
#include<TBrowser.h>
#include<TTree.h>

#pragma once
class basicFeatures
{
    private:
        /* data */
    public:
        void getParams(TF1 *);
        void getLegends(std::map<const char *, const TObject*>, Int_t, Option_t *, Double_t, Double_t, Double_t, Double_t);
        void writeRoot(const char *, void (*)());
        void readRoot(const char *, bool);
        void writeTree(const char *, std::vector<std::tuple<Double_t, Double_t>>);
        void readTree(const char *);

        template<typename customFunc>
        void customFunctions(customFunc my_func, Double_t p0, Double_t p1, const char *title,  const char *outpath=nullptr, const char *xlabel="x-axis", const char *ylabel="y-axis")
        {
            TCanvas *c1 = new TCanvas();

            TF1 *custom_func = new TF1("func", my_func, 0, 10, 2);
            custom_func->SetTitle(title);
            custom_func->SetParameter(0, p0);
            custom_func->SetParameter(1, p1);
            
            custom_func->GetXaxis()->SetTitle(xlabel);
            custom_func->GetYaxis()->SetTitle(ylabel);
            custom_func->Draw();

            if (outpath!=nullptr)
            {
                c1->Print(outpath); //save plot as image
            }
        }
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

void basicFeatures::writeRoot(const char *outpath, void (*func)())
{
    TFile *file = new TFile(outpath, "RECREATE");
    func();
    file->Write();
    file->Close();
}

void basicFeatures::readRoot(const char *rootpath, bool browse=false)
{
    TFile *file = new TFile(rootpath, "READ");
    TH1F *hist = (TH1F*)file->Get("hist");
    if (browse)
        TBrowser *browser = new TBrowser("browser", "Read Rootfile demo");
    else 
        hist->Draw();
}

void basicFeatures::writeTree(const char *outpath, std::vector<std::tuple<Double_t, Double_t>> data)
{
    TFile *file = new TFile(outpath, "RECREATE");
    TTree *tree = new TTree("tree", "sample_tree");
    Double_t x, y;
    tree->Branch("x", &x, "x/D");
    tree->Branch("y", &y, "y/D");

    for (auto &itr : data)
    {
        auto [x, y] = itr;
        std::cout << x << ", " << y << std::endl;
        tree->Fill();
    }
    file->Write();
    file->Close();
}

void basicFeatures::readTree(const char *input_file)
{
    TFile *file = new TFile(input_file, "READ");
    TTree *tree = (TTree*)file->Get("tree");
    Double_t x, y;

    tree->SetBranchAddress("x", &x);
    tree->SetBranchAddress("y", &y);
    int entries = tree->GetEntries();
    std::cout << "entries: " << entries << std::endl;

    TH1F *hist = new TH1F("hist", "tree histogram", 20, 0, 10);
    for (int i = 0; i < entries; i++)
    {
        tree->GetEntry(i);
        std::cout << "x " << x << ", y " << y << std::endl;
        hist->Fill(x);
    }
    hist->Draw();
}