#include "RootTools.h"
#include "LanguageTools.h"
#include "SignalRegion.h"
#include "StopYields.h"
#include "Sample.h"
#include "TStyle.h"
#include "TChain.h"
#include "TCanvas.h"
#include <iostream>

stop::Yield::value_t ExtractExpUpperLimitCombine(const std::string& filename, const float scale = 1.0)
{
    TChain chain("limit");
    chain.Add(filename.c_str());
    stop::Yield::value_t result;
    chain.SetBranchAddress("limit"   , &result.value);
    chain.SetBranchAddress("limitErr", &result.error);
    chain.GetEntry(2);
    result.value *= scale;
    result.error *= scale;
    return result;
}

stop::Yield::value_t ExtractObsUpperLimitCombine(const std::string& filename, const float scale = 1.0)
{
    TChain chain("limit");
    chain.Add(filename.c_str());
    stop::Yield::value_t result;
    chain.SetBranchAddress("limit"   , &result.value);
    chain.SetBranchAddress("limitErr", &result.error);
    chain.GetEntry(5);
    result.value *= scale;
    result.error *= scale;
    return result;
}

void FillLimitHistogram
(
    TH1F& hist,
    stop::Yield::value_t* const ul
)
{
    hist.Sumw2();
    for (size_t bin = 1; bin <= 7; bin++)
    {
        hist.SetBinContent(bin, ul[bin-1].value);
        hist.SetBinError  (bin, ul[bin-1].error);
    }
    hist.GetXaxis()->SetBinLabel(1, "1Lep"     );
    hist.GetXaxis()->SetBinLabel(2, "Razor"    );
    hist.GetXaxis()->SetBinLabel(3, "No Corr"  );
    hist.GetXaxis()->SetBinLabel(4, "JES Corr" );
    hist.GetXaxis()->SetBinLabel(5, "Btag Corr");
    hist.GetXaxis()->SetBinLabel(6, "ISR Corr" );
    hist.GetXaxis()->SetBinLabel(7, "Lep ACorr");
    return;
}

void CompareWithRazor(const double mass_stop, const double mass_lsp, const std::string sr, const std::string& suffix = "png")
{
    // get observed limits 
    const std::string limit_path = "test";
    const unsigned int num_obs   = 7;
    stop::Yield::value_t ul_obs[num_obs] =
    {
        ExtractObsUpperLimitCombine(Form("%s/higgsCombine_t2tt_%1.0f_%1.0f_%s.Asymptotic.mH120.1234.root"                                      , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        //ExtractObsUpperLimitCombine(Form("%s/higgsCombine_razor_combine_Had_T2tt_MG_%1.0f.000000_MCHI_%1.0f.000000.Asymptotic.mH120.1234.root" , limit_path.c_str() , mass_stop , mass_lsp            )), 
        ExtractObsUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s_junk2.Asymptotic.mH120.1234.root"                       , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractObsUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s.Asymptotic.mH120.1234.root"                             , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractObsUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s_jescorr.Asymptotic.mH120.1234.root"                     , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractObsUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s_btagcorr.Asymptotic.mH120.1234.root"                    , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractObsUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s_isrcorr.Asymptotic.mH120.1234.root"                     , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())),
        ExtractObsUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s_lepacorr.Asymptotic.mH120.1234.root"                    , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str()))
    };

    // get exp limits 
    stop::Yield::value_t ul_exp[num_obs] =
    {
        ExtractExpUpperLimitCombine(Form("%s/higgsCombine_t2tt_%1.0f_%1.0f_%s.Asymptotic.mH120.1234.root"                                      , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        //ExtractExpUpperLimitCombine(Form("%s/higgsCombine_razor_combine_Had_T2tt_MG_%1.0f.000000_MCHI_%1.0f.000000.Asymptotic.mH120.1234.root" , limit_path.c_str() , mass_stop , mass_lsp            )), 
        ExtractExpUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s_junk2.Asymptotic.mH120.1234.root"                       , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractExpUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s.Asymptotic.mH120.1234.root"                             , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractExpUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s_jescorr.Asymptotic.mH120.1234.root"                     , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractExpUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s_btagcorr.Asymptotic.mH120.1234.root"                    , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractExpUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s_isrcorr.Asymptotic.mH120.1234.root"                     , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())),
        ExtractExpUpperLimitCombine(Form("%s/higgsCombine_combined_t2tt_%1.0f_%1.0f_%s_lepacorr.Asymptotic.mH120.1234.root"                    , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str()))
    };

    // output table
    const char* const fmt = "1.5";
    CTable t1;
    t1.useTitle();
    t1.setTitle(Form("Comparison of limits for m_stop = %1.0f and m_lsp = %1.0f", mass_stop, mass_lsp));
    t1.setTable()(                                           "obs limits",     "exp limits")
                 ("Single lepton"                    , ul_obs[0].pm(fmt) , ul_exp[0].value )
                 ("Razor hadronic"                   , ul_obs[1].pm(fmt) , ul_exp[1].value )
                 ("cobmined (uncorrelated)"          , ul_obs[2].pm(fmt) , ul_exp[2].value )
                 ("cobmined (JES 100%% corr)"        , ul_obs[3].pm(fmt) , ul_exp[3].value )
                 ("cobmined (Btag 100%% corr)"       , ul_obs[4].pm(fmt) , ul_exp[4].value )
                 ("cobmined (ISR 100%% corr)"        , ul_obs[5].pm(fmt) , ul_exp[5].value )
                 ("cobmined (lepton 100%% anti-corr)", ul_obs[6].pm(fmt) , ul_exp[6].value )
    ;
    cout << t1 << std::endl;

    // output plot
    TH1F h_obs("h_obs", Form("Observed signal strength (r-value), m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV, SR= %s;Card;r-value", mass_stop, mass_lsp, sr.c_str()), 7, 0.5, 7.5);
    TH1F h_exp("h_exp", Form("Expected signal strength (r-value), m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV, SR= %s;Card;r-value", mass_stop, mass_lsp, sr.c_str()), 7, 0.5, 7.5);
    FillLimitHistogram(h_obs, ul_obs);
    FillLimitHistogram(h_exp, ul_exp);

    TCanvas c1;
    rt::TH1Overlay p_obs(Form("Signal strength (r-value), m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV, SR= %s;Card;r-value", mass_stop, mass_lsp, sr.c_str()), "sb::off lg::top_left");
    p_obs.Add(&h_obs, "Observed", kBlack, 2);
    p_obs.Add(&h_exp, "Expected", kRed  , 2);
    p_obs.Draw();
    lt::mkdir("plots/razor_compare", /*force=*/true);
    c1.Print(Form("plots/razor_compare/p_rvalue_%1.0f_%1.0f_%s.%s", mass_stop, mass_lsp, sr.c_str(), suffix.c_str()));
}

void CompareWithRazor()
{
    CompareWithRazor(200, 100, "bdt5", "eps");
    CompareWithRazor(600, 150, "bdt4", "eps");
    CompareWithRazor(725,  25, "bdt4", "eps");
}
