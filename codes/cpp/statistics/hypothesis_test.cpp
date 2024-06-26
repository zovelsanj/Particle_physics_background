#include "stats.hpp"

void hypothesis_test()
{
    RooWorkspace *wspace = new RooWorkspace("myWS");
    rootStats *stat = new rootStats();

    stat->addModel(wspace); // add the signal and background models to the workspace
    stat->addData(wspace); // add some toy data to the workspace

    std::cout<<"Inspecting workspace ................"<<std::endl;
    wspace->Print();  // inspect the workspace 

    stat->hypothesisTesting(wspace);
    stat->plotTests(wspace);

    delete wspace;
}
