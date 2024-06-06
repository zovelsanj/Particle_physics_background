#include "root_basics.hpp" //need not include the header when compiling with `root`
#include <THStack.h>
#include <TPaveText.h>

TH1F *get_histogram(bool visualize = true)
{
    TH1F *histogram = new TH1F("hist", "Histogram", 100, 0, 100);
    for (int i = 0; i < 1000; i++)
    {
        histogram->Fill(gRandom->Gaus(50.0, 10.0));
    }

    histogram->GetXaxis()->SetTitle("X axis");
    histogram->GetYaxis()->SetTitle("Y axis");

    if (visualize)
    {
        TCanvas *c1 = new TCanvas();
        histogram->Draw();
    }
    return histogram;
}

void stack_histograms(Int_t nx=2, Int_t ny=2)
{
    THStack *stack = new THStack();
    TH1F *hist1 = get_histogram(false);
    hist1->SetFillColor(kGreen);

    TH1F *hist2 = get_histogram(false);
    hist2->SetFillColor(kBlue);

    stack->Add(hist1);
    stack->Add(hist2);

    std::vector<const char *> plot_names = {"", "nostack", "nostack e1p", "lego"};
    basicFeatures *b = new basicFeatures();
    b->subplots(nx, ny, plot_names, stack);
}

void histogram(bool stack = false)
{
    if (stack)
        stack_histograms();
    else
        get_histogram();
}
