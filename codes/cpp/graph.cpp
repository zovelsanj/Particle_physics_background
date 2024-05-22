#include "root_basics.hpp"

void graph(int N = 100)
{
    float x[N], y[N];
    for (int i = 0; i < N; i++)
    {
        x[i] = i;
        y[i] = cos(x[i]);
    }

    TGraph *g = new TGraph(N, x, y);  
    TCanvas *c1 = new TCanvas();
    g->SetMarkerStyle(20);
    g->SetMarkerSize(1);
    g->Draw("ALP");
    
}