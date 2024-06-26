#include <RooDataSet.h>
#include <RooRealVar.h>
#include <RooGaussian.h>
#include <RooAddPdf.h>
#include <RooProdPdf.h>
#include <RooAddition.h>
#include <RooProduct.h>
#include <RooChebychev.h>
#include <RooAbsPdf.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include <RooAbsArg.h>
#include <RooWorkspace.h>
#include <RooStats/ProfileLikelihoodCalculator.h>
#include <RooStats/HypoTestResult.h>

class rootStats
{
private:
    /* data */
public:
    void addModel(RooWorkspace *, Double_t, Double_t);
    void addData(RooWorkspace *, Int_t);
    void hypothesisTesting(RooWorkspace *);
    void plotTests(RooWorkspace *);
};

void rootStats::addModel(RooWorkspace *wspace, Double_t obs_low = 60.0, Double_t obs_high = 200.0)
{
    const char *unit = "GeV";
    // Build a sample model for Higgs (signal) with Z+jets and QCD backgrounds
    RooRealVar invMass("invMass", "M_{inv}", obs_low, obs_high, unit); // Observable

    // Signal Model
    Double_t mH_val = 130, mH_min = 90, mH_max = 160;
    RooRealVar mH("mH", "m_{H}", mH_val, mH_min, mH_max, unit);
    RooRealVar sigma_sig("sigma1", "Width of Gaussian", 12, 2, 100);
    RooGaussian sig_model("sig_model", "Signal Model", invMass, mH, sigma_sig); // Ref_x, Ref_mean, Ref_sigma
    mH.setConstant();                                                           // this specific mass point for the signal will be tested
    sigma_sig.setConstant();                                                    // Let's assume we know the mass resolution

    // Background Model: Z+jets
    Double_t mZ_val = 91.2, mZ_min = 0, mZ_max = 100;
    RooRealVar mZ("mH", "m_{H}", mZ_val, mZ_min, mZ_max, unit);
    RooRealVar sigma_bkg1("sigma2", "Width of Gaussian", 10, 6, 100);
    RooGaussian Zjj_model("Zjj_model", "Z+Jets Model", invMass, mZ, sigma_bkg1); // Ref_x, Ref_mean, Ref_sigma
    mZ.setConstant();                                                            // we know mZ
    sigma_bkg1.setConstant();                                                    // Let's assume we know the mass resolution

    // Background Model: QCD
    RooRealVar a0("a0", "a0", 0.26, -1, 1);
    RooRealVar a1("a1", "a1", -0.17596, -1, 1);
    RooRealVar a2("a2", "a2", 0.018437, -1, 1);
    RooChebychev QCD_model("QCD_model", "Polynomial for QCD", invMass, RooArgList(a0, a1, a2));
    // Let's assume we know this shape is known, but not the normalization
    a0.setConstant();
    a1.setConstant();
    a2.setConstant();

    // Combine Models
    RooRealVar frac_Zjj("frac_Zjj", "Fraction of Z+Jets bkg events", 0.4, 0, 1);            // 40% of initial guess
    RooRealVar frac_sigExp("frac_sigExp", "Expected fraction of signal events", 0.2, 0, 1); // 20%
    frac_sigExp.setConstant();

    RooRealVar mu("mu", "Signal strength (in units of SM expectation)", 1, 0, 2);                               // mu = 1 is the SM, mu = 0 is no signal, mu=2 is 2x the SM
    RooRealVar ratio_sigEff("ratio_sigEff", "Ratio of signal efficiency to nomial signal efficiency", 1, 0, 2); // useful if you want to do limits on cross section.
    ratio_sigEff.setConstant(kTRUE);

    RooProduct frac_sig("frac_sig", "Fraction of signal events", RooArgSet(mu, ratio_sigEff, frac_sigExp));

    const RooArgList &pdf_list = RooArgList(sig_model, Zjj_model, QCD_model);
    const RooArgList &coeff_list = RooArgList(frac_sig, frac_Zjj);
    RooAddPdf model("model", "Final model: Signal+Zjj+QCD background shapes", pdf_list, coeff_list);

    wspace->import(model);
}

void rootStats::addData(RooWorkspace *wspace, Int_t n_events = 150)
{
    RooAbsPdf *model = wspace->pdf("model");
    RooRealVar *invMass = wspace->var("invMass");

    std::unique_ptr<RooDataSet> data{model->generate(*invMass, n_events)};
    wspace->import(*data, RooFit::Rename("data"));
}

void rootStats::hypothesisTesting(RooWorkspace *wspace)
{
    RooFit::ModelConfig model;
    model.SetWorkspace(*wspace);
    model.SetPdf("model");

    RooStats::ProfileLikelihoodCalculator plc; //Profile Likelihood calculator for hypothesis testing
    plc.SetData(*wspace->data("data"));

    //Null Hypothesis (mu=0): set the parameters explicitly. No signal contribution.
    RooRealVar *mu = wspace->var("mu");
    RooArgSet poi(*mu); //Parameter of Interest
    RooArgSet *null_params = (RooArgSet *)poi.snapshot();   //using snapshot imports nullparams
    null_params->setRealValue("mu", 0);

    plc.SetModel(model);
    plc.SetNullParameters(*null_params);

    RooStats::HypoTestResult *htest_result = plc.GetHypoTest();
    std::cout << "The p-value for Null Hypothesis is " << htest_result->NullPValue() << std::endl;
    std::cout << "Corresponding to a significance of " << htest_result->Significance() << std::endl;
}

void rootStats::plotTests(RooWorkspace *wspace)
{
    RooAbsPdf *model = wspace->pdf("model");
    RooAbsPdf *sig_model = wspace->pdf("sig_model");
    RooAbsPdf *Zjj_model = wspace->pdf("Zjj_model");
    RooAbsPdf *QCD_model = wspace->pdf("QCD_model");

    RooRealVar *mu = wspace->var("mu");
    RooRealVar *invMass = wspace->var("invMass");
    RooAbsData *data = wspace->data("data");

    //Alternative Hypothesis H_1 (mu not 0) plots
    mu->setConstant(kFALSE);
    model->fitTo(*data, RooFit::Save(kTRUE), RooFit::Minos(kFALSE), RooFit::Hesse(kFALSE),RooFit::PrintLevel(-1));

    new TCanvas();
    RooPlot *frame = invMass->frame();
    data->plotOn(frame);
    model->plotOn(frame);
    model->plotOn(frame, RooFit::Components(*sig_model), RooFit::LineStyle(kDashed), RooFit::LineColor(kRed));
    model->plotOn(frame, RooFit::Components(*Zjj_model), RooFit::LineStyle(kDashed), RooFit::LineColor(kBlack));
    model->plotOn(frame, RooFit::Components(*QCD_model), RooFit::LineStyle(kDashed), RooFit::LineColor(kGreen));
    frame->SetTitle("Fit to Signal+Background Model (H_{1})");
    frame->Draw();

    // //Null Hypothesis H_0 (mu = 0) plots
    mu->setVal(0);
    mu->setConstant(kTRUE);
    model->fitTo(*data, RooFit::Save(kTRUE), RooFit::Minos(kFALSE), RooFit::Hesse(kFALSE),RooFit::PrintLevel(-1));
    
    new TCanvas();
    RooPlot *frame_bkg = invMass->frame();
    data->plotOn(frame_bkg, RooFit::DataError(RooAbsData::SumW2));
    model->plotOn(frame_bkg);
    model->plotOn(frame_bkg, RooFit::Components(*Zjj_model), RooFit::LineStyle(kSolid), RooFit::LineColor(kBlack));
    model->plotOn(frame_bkg, RooFit::Components(*QCD_model), RooFit::LineStyle(kSolid), RooFit::LineColor(kGreen));
    frame_bkg->SetTitle("Fit to Background-only Model (H_{0})");
    frame_bkg->Draw();    
}
