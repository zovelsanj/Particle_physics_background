#include<TF2.h>
#include<TH2F.h>
#include<TCanvas.h>
#include<TRandom.h>
#include<TStyle.h>
#include<TPaveLabel.h>

void basic_plot_2d(int N, Int_t xbins = 100, Int_t ybins = 100, Int_t xlow = 0, Int_t xup = 4, Int_t ylow = 0, Int_t yup = 4)
{
    TCanvas *canvas = new TCanvas();
    TH2F *hist = new TH2F("hist", "Sample 2D Histogram", xbins, xlow, xup, ybins, ylow, yup);

    TRandom *rand = new TRandom(314);
    for (int i = 0; i < N; i++)
    {
        Double_t x = rand->Gaus(2, 1.5);
        Double_t y = rand->Gaus(2, 1.5);
        hist->Fill(x, y);
    }

    hist->GetXaxis()->SetTitle("X axis");
    hist->GetYaxis()->SetTitle("Y axis");
    hist->GetZaxis()->SetTitle("Entries");

    gStyle->SetPalette(kRainBow);  
    gStyle->SetOptStat(0);  
    gStyle->SetCanvasColor(33);
    gStyle->SetFrameFillColor(18);

    hist->Draw("colz");
}

void contour_2d(Int_t xlow = 0, Int_t xup = 100, Int_t ylow = 0, Int_t yup = 100)
{
    TCanvas *canvas = new TCanvas("canvas", "2D Contour", xlow, ylow, xup, yup);
    canvas->Divide(2, 2);
    canvas->SetFillColor(kEllipse);

    TF2 *hist = new TF2("hist", "xygaus + xygaus(5) + xylandau(10)", xlow, xup, ylow, yup);
    Double_t params[] = {130,-1.4,1.8,1.5,1, 150,2,0.5,-2,0.5, 3600,-2,0.7,-3,0.3};
    hist->SetParameters(params);

    TH2F *h2 = new TH2F("h2","Sample Contour Plot",20,-4,4,20,-4,4);
    h2->FillRandom("hist");

    TPaveLabel *pl = new TPaveLabel();

    canvas->cd(1);
    h2->Draw("contz");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "contour1", "brNDC");

    canvas->cd(2);
    h2->Draw("cont1");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "contour2", "brNDC");

    canvas->cd(3);
    h2->Draw("cont2");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "contour3", "brNDC");

    canvas->cd(4);
    h2->Draw("cont3");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "contour4", "brNDC");

    canvas->Update();
}

void plots_2d()
{
    basic_plot_2d(1e7);
    contour_2d();
}