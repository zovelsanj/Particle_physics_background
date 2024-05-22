#include "root_basics.hpp" //need not include the header when compiling with `root`

void histogram()
{
    TH1F *histogram = new TH1F("hist", "Histogram", 100, 0, 100);
    for (int i = 0; i < 1000; i++)
    {
        histogram->Fill(gRandom->Gaus(50.0, 10.0));
    }
    
    histogram->GetXaxis()->SetTitle("X axis");
    histogram->GetYaxis()->SetTitle("Y axis");
    
    TCanvas *c1 = new TCanvas();
    histogram->Draw();
}
