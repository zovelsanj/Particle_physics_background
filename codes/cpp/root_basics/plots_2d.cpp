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

void contour_2d(TH2F *hist, Int_t xlow = 0, Int_t xup = 100, Int_t ylow = 0, Int_t yup = 100)
{
    TCanvas *canvas = new TCanvas("canvas", "2D Contour", xlow, ylow, xup, yup);
    canvas->Divide(2, 2);
    canvas->SetFillColor(kEllipse);

    TPaveLabel *pl = new TPaveLabel();

    canvas->cd(1);
    hist->Draw("contz");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "contour1", "brNDC");

    canvas->cd(2);
    hist->Draw("cont1");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "contour2", "brNDC");

    canvas->cd(3);
    hist->Draw("cont2");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "contour3", "brNDC");

    canvas->cd(4);
    hist->Draw("cont3");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "contour4", "brNDC");

    canvas->Update();
}

void surface_2d(TH2F *hist, Int_t xlow = 0, Int_t xup = 100, Int_t ylow = 0, Int_t yup = 100)
{
    TCanvas *canvas = new TCanvas("surfopt", "2D Contour", xlow, ylow, xup, yup);
    canvas->Divide(3, 2);
    canvas->SetFillColor(kEllipse);

    TPaveLabel *pl = new TPaveLabel();

    canvas->cd(1);
    hist->Draw("surf1z");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "SURF1", "brNDC");

    canvas->cd(2);
    hist->Draw("surf2");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "SURF2", "brNDC");

    canvas->cd(3);
    hist->Draw("surf3");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "SURF3", "brNDC");

    canvas->cd(4);
    hist->Draw("surf4");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "SURF4", "brNDC");

    canvas->cd(5);
    hist->Draw("surf1pol");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "SURF4", "brNDC");

    canvas->cd(6);
    hist->Draw("surf1cyl");
    gPad->SetGrid();
    pl->DrawPaveLabel(xlow, ylow, xup, yup, "SURF4", "brNDC");

    canvas->Update();
}

void plots_2d()
{
    Int_t xbins = 50, ybins = 50;
    Int_t xlow = -4,  xup = 4;
    Int_t ylow = -4, yup = 4;

    TF2 *hist = new TF2("hist", "xygaus + xygaus(5) + xylandau(10)", xlow, xup, ylow, yup);
    Double_t params[] = {130,-1.4,1.8,1.5,1, 150,2,0.5,-2,0.5, 3600,-2,0.7,-3,0.3};
    hist->SetParameters(params);

    TH2F *h2 = new TH2F("h2","Sample Contour Plot", xbins, xlow, xup, ybins, ylow, yup);
    h2->FillRandom("hist");

    // basic_plot_2d(1e7);
    // contour_2d(h2);
    surface_2d(h2);
}
