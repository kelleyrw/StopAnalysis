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

void CompareAsymptoticToHybrid(const double mass_stop, const double mass_lsp, const std::string sr)
{
    // get observed combined limits 
    std::string limit_path = "output/limits/lep1_razor_combine_asymptotic/t2tt/combine_output";
    const unsigned int num_obs   = 3;
    stop::Yield::value_t ul_obs_com[num_obs] =
    {
        ExtractObsUpperLimitCombine(Form("%s_t2tt_%1.0f_%1.0f_%s.root"                       , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractObsUpperLimitCombine(Form("%s_razor_combine_Had_T2tt_MG_%1.6f_MCHI_%1.6f.root", limit_path.c_str() , mass_stop , mass_lsp)), 
        ExtractObsUpperLimitCombine(Form("%s_combined_t2tt_%1.0f_%1.0f_%s.root"              , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
    };

    // get exp limits 
    stop::Yield::value_t ul_exp_com[num_obs] =
    {
        ExtractExpUpperLimitCombine(Form("%s_t2tt_%1.0f_%1.0f_%s.root"                       , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractExpUpperLimitCombine(Form("%s_razor_combine_Had_T2tt_MG_%1.6f_MCHI_%1.6f.root", limit_path.c_str() , mass_stop , mass_lsp)), 
        ExtractExpUpperLimitCombine(Form("%s_combined_t2tt_%1.0f_%1.0f_%s.root"              , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
    };

    // get observed combined limits 
    limit_path = "output/limits/lep1_razor_combine_hybridnew/t2tt/combine_output";
    stop::Yield::value_t ul_obs_hyb[num_obs] =
    {
        ExtractObsUpperLimitCombine(Form("%s_t2tt_%1.0f_%1.0f_%s.root"                       , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractObsUpperLimitCombine(Form("%s_razor_combine_Had_T2tt_MG_%1.6f_MCHI_%1.6f.root", limit_path.c_str() , mass_stop , mass_lsp)), 
        ExtractObsUpperLimitCombine(Form("%s_combined_t2tt_%1.0f_%1.0f_%s.root"              , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
    };

    // get exp limits 
    stop::Yield::value_t ul_exp_hyb[num_obs] =
    {
        ExtractExpUpperLimitCombine(Form("%s_t2tt_%1.0f_%1.0f_%s.root"                       , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
        ExtractExpUpperLimitCombine(Form("%s_razor_combine_Had_T2tt_MG_%1.6f_MCHI_%1.6f.root", limit_path.c_str() , mass_stop , mass_lsp)), 
        ExtractExpUpperLimitCombine(Form("%s_combined_t2tt_%1.0f_%1.0f_%s.root"              , limit_path.c_str() , mass_stop , mass_lsp, sr.c_str())), 
    };


    // output table
    const char* const fmt = "1.5";
    CTable t1;
    t1.useTitle();
    t1.setTitle(Form("Comparison of limits for m_stop = %1.0f and m_lsp = %1.0f", mass_stop, mass_lsp));
    t1.setTable()(                   "obs combined limits", "obs hybrid new limits")
                 ("Single lepton" , ul_obs_com[0].pm(fmt) ,   ul_obs_hyb[0].pm(fmt))
                 ("Razor hadronic", ul_obs_com[1].pm(fmt) ,   ul_obs_hyb[1].pm(fmt))
                 ("combined"      , ul_obs_com[2].pm(fmt) ,   ul_obs_hyb[2].pm(fmt))
    ;
    cout << t1 << std::endl;

    CTable t2;
    t2.useTitle();
    t2.setTitle(Form("Comparison of limits for m_stop = %1.0f and m_lsp = %1.0f", mass_stop, mass_lsp));
    t2.setTable()(                 "exp combined limits", "exp hybrid new limits")
                 ("Single lepton" , ul_exp_com[0].value ,   ul_exp_hyb[0].value)
                 ("Razor hadronic", ul_exp_com[1].value ,   ul_exp_hyb[1].value)
                 ("combined"      , ul_exp_com[2].value ,   ul_exp_hyb[2].value)
    ;
    cout << t2 << std::endl;
}

void CompareAsymptoticToHybrid()
{
    CompareAsymptoticToHybrid(200, 100, "bdt5");
    CompareAsymptoticToHybrid(600, 150, "bdt4");
    CompareAsymptoticToHybrid(725,  25, "bdt4");
}
