#include "root_basics.hpp"
#include<iostream>

void stylize_hist(TH1F *hist, bool grid=false, bool latex=false)
{
    hist->GetXaxis()->SetTitleSize(0.03);
    hist->GetYaxis()->SetTitleSize(0.03);
    hist->GetXaxis()->SetLabelSize(0.03);
    hist->GetYaxis()->SetLabelSize(0.03);

    hist->SetStats(0);
    hist->SetFillColor(kBlue-9);

    TCanvas *c1 = new TCanvas();
    hist->Draw();

    if (grid) c1->SetGrid();
    if (latex)
    {   
        Double_t x = 5.5;
        Int_t bin = hist->FindBin(x);
        Double_t y = hist->GetBinContent(bin);

        TArrow *arr = new TArrow(7, 5, x, y);
        arr->SetLineWidth(2);
        arr->SetArrowSize(0.02);
        arr->SetLineColor(kBlue-3);
        arr->Draw();

        TLatex *latex = new TLatex(7, 5, "Point of interest (P_{0})");
        latex->SetTextSize(0.03);
        latex->Draw();
    }
}

void fit_distribution()
{
    TH1F *hist = new TH1F("hist", "Gaussian Distribution Fitting", 80, 0, 10);
    TRandom *rn = new TRandom(314);
    basicFeatures *b = new basicFeatures(); 
    Double_t val;

    for (int i = 0; i < 100; i++)
    {
        val = rn->Gaus(5.0, 1.0);
        hist->Fill(val);
    }
    
    hist->SetXTitle("Distribution");
    hist->SetYTitle("Entries");
    stylize_hist(hist, true, true);

    TF1 *fit = new TF1("Gauss fit", "gaus", 0, 5);
    fit->SetLineStyle(2);
    fit->SetLineColor(kRed);
    hist->Fit("Gauss fit", "Q");

    b->getParams(fit);
    std::map<const char *, const TObject*> legend_hashmap;
    legend_hashmap["histogram"] = hist;
    legend_hashmap["gaussian fit"] = fit;

    b->getLegends(legend_hashmap, 0);
}
