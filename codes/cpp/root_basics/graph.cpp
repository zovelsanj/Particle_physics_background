#include "root_basics.hpp"

void draw_graph(int N)
{
    TRandom *rn = new TRandom();
    float x[N], y[N];
    for (int i = 0; i < N; i++)
    {
        x[i] = i*0.1;
        y[i] = rn->Gaus(70.0, 10.0);
    }

    TGraph *g = new TGraph(N, x, y);  
    g->SetMarkerStyle(20);
    g->SetMarkerSize(1);
    g->Draw("ALP");
}

void draw_error_bar(int N, bool fit=false)
{
    float x[N], y[N], xerr[N], yerr[N];
    TRandom *rn = new TRandom();

    for (int i = 0; i < N; i++)
    {
        x[i] = (i+1.5)*0.2;
        xerr[i] = x[i]*0.01;
        y[i] = rn->Gaus(50.0, 5.0);
        yerr[i] = y[i] * 0.08;
    }
    TGraphErrors *gerr = new TGraphErrors(10, x, y, xerr, yerr);
    gerr->SetMarkerColor(kRed);
    gerr->SetMarkerStyle(20);
    gerr->Draw("LP");

    if (fit)
    {
        TF1 *f = new TF1("f", "curve fitting", 0, 5);
        gerr->Fit("f");
    }
}

void graph(int N = 25)
{
    TCanvas *cerr =  new TCanvas("Test", "Sample Error Bar");
    cerr->SetGrid();
    
    TH1F *herr = cerr->DrawFrame(-0.4, 0, 10, 100);
    herr->SetXTitle("X title");
    herr->SetYTitle("Y title");
    draw_graph(N);
    draw_error_bar(N, true);
}
