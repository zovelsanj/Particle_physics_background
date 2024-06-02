#include "root_basics.hpp"

void custom_func()
{
    auto my_func = [](Double_t *x, Double_t *a)
    {
        return TMath::Abs(TMath::Exp(-a[0]*x[0])*a[1]*sin(x[0]));
    };

    basicFeatures *b = new basicFeatures();
    b->customFunctions(my_func, 1, 2, "custom function visualization");
}
