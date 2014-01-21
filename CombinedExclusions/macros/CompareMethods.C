#include "RootTools.h"
#include "LanguageTools.h"
#include "SignalRegion.h"
#include "StopYields.h"
#include "Sample.h"
#include "TStyle.h"
#include "TChain.h"
#include "TCanvas.h"
#include <iostream>

using namespace std;

stop::Yield::value_t ExtractExpUpperLimit
(
    const std::string& filename
)
{
    TChain chain("T");
    chain.Add(filename.c_str());
    stop::Yield::value_t result;
    chain.SetBranchAddress("rmedian"   , &result.value);
    chain.SetBranchAddress("rmedianErr", &result.error);
    chain.GetEntry(0);
    return result;
}

stop::Yield::value_t ExtractObsUpperLimit
(
    const std::string& filename
)
{
    TChain chain("T");
    chain.Add(filename.c_str());
    stop::Yield::value_t result;
    chain.SetBranchAddress("limit"   , &result.value);
    chain.SetBranchAddress("limitErr", &result.error);
    chain.GetEntry(0);
    return result;
}

void CompareMethods 
(
    const float mass_stop,
    const float mass_lsp
)
{
    // get the original results
    rt::TH1Container hc_orig("/Users/rwk7t/temp/from_ben/exclusion2012_postLHCP_T2bwFixed/rootfiles/T2tt_BDT_histos.root");
    //hc_orig.List();

    int bin = hc_orig["heff_0"]->FindBin(mass_stop, mass_lsp);
    stop::Yield::value_t ul_obs_orig[stop::SignalRegion::static_size] =
    {
        {1000.0*hc_orig["hxsec_0"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_1"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_2"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_3"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_4"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_5"]->GetBinContent(bin), 0},
    };
    stop::Yield::value_t ul_exp_orig[stop::SignalRegion::static_size] =
    {
        {1000.0*hc_orig["hxsec_exp_0"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_0"]->GetBinContent(bin), hc_orig["hxsec_expm1_0"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_1"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_1"]->GetBinContent(bin), hc_orig["hxsec_expm1_1"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_2"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_2"]->GetBinContent(bin), hc_orig["hxsec_expm1_2"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_3"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_3"]->GetBinContent(bin), hc_orig["hxsec_expm1_3"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_4"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_4"]->GetBinContent(bin), hc_orig["hxsec_expm1_4"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_5"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_5"]->GetBinContent(bin), hc_orig["hxsec_expm1_5"]->GetBinContent(bin))},
    };

    const std::string limit_path = "output/lands/t2tt/";

    // get method1 a posteriori (m1a)
    stop::Yield::value_t ul_obs_m1a[stop::SignalRegion::static_size] =
    {
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    stop::Yield::value_t ul_exp_m1a[stop::SignalRegion::static_size] =
    {
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };

    // get method2 a posteriori (m2a)
    stop::Yield::value_t ul_obs_m2a[stop::SignalRegion::static_size] =
    {
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    stop::Yield::value_t ul_exp_m2a[stop::SignalRegion::static_size] =
    {
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };

    // get method3 a posteriori (m3a)
    stop::Yield::value_t ul_obs_m3a[stop::SignalRegion::static_size] =
    {
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    stop::Yield::value_t ul_exp_m3a[stop::SignalRegion::static_size] =
    {
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    

    // output table
    const char* const fmt = "1.3";
    CTable table;
    table.useTitle();
    table.setTitle(Form("Comparison for m_stop = %1.0f and m_lsp = %1.0f", mass_stop, mass_lsp));
    table.setTable()(                  "BDT1L"                , "BDT1T"               , "BDT2"                , "BDT3"                , "BDT4"                , "BDT5"                 )
    ("orig obs UL"                   , ul_obs_orig[0].value   , ul_obs_orig[1].value  , ul_obs_orig[2].value  , ul_obs_orig[3].value  , ul_obs_orig[4].value  , ul_obs_orig[5].value   )
    ("orig exp UL"                   , ul_exp_orig[0].value   , ul_exp_orig[1].value  , ul_exp_orig[2].value  , ul_exp_orig[3].value  , ul_exp_orig[4].value  , ul_exp_orig[5].value   )
    ("method1 obs UL (a posteriori)" , ul_obs_m1a [0].pm(fmt) , ul_obs_m1a [1].pm(fmt), ul_obs_m1a [2].pm(fmt), ul_obs_m1a [3].pm(fmt), ul_obs_m1a [4].pm(fmt), ul_obs_m1a [5].pm(fmt) )
    ("method1 exp UL (a posteriori)" , ul_exp_m1a [0].pm(fmt) , ul_exp_m1a [1].pm(fmt), ul_exp_m1a [2].pm(fmt), ul_exp_m1a [3].pm(fmt), ul_exp_m1a [4].pm(fmt), ul_exp_m1a [5].pm(fmt) )
    ("method2 obs UL (a posteriori)" , ul_obs_m2a [0].pm(fmt) , ul_obs_m2a [1].pm(fmt), ul_obs_m2a [2].pm(fmt), ul_obs_m2a [3].pm(fmt), ul_obs_m2a [4].pm(fmt), ul_obs_m2a [5].pm(fmt) )
    ("method2 exp UL (a posteriori)" , ul_exp_m2a [0].pm(fmt) , ul_exp_m2a [1].pm(fmt), ul_exp_m2a [2].pm(fmt), ul_exp_m2a [3].pm(fmt), ul_exp_m2a [4].pm(fmt), ul_exp_m2a [5].pm(fmt) )
    ("method3 obs UL (a posteriori)" , ul_obs_m3a [0].pm(fmt) , ul_obs_m3a [1].pm(fmt), ul_obs_m3a [2].pm(fmt), ul_obs_m3a [3].pm(fmt), ul_obs_m3a [4].pm(fmt), ul_obs_m3a [5].pm(fmt) )
    ("method3 exp UL (a posteriori)" , ul_exp_m3a [0].pm(fmt) , ul_exp_m3a [1].pm(fmt), ul_exp_m3a [2].pm(fmt), ul_exp_m3a [3].pm(fmt), ul_exp_m3a [4].pm(fmt), ul_exp_m3a [5].pm(fmt) )
    ;

    cout << table << std::endl;
}

void CompareMethodsFromGrid
(
    const float mass_stop,
    const float mass_lsp
)
{
    // get the original results
    rt::TH1Container hc_orig("/Users/rwk7t/temp/from_ben/exclusion2012_postLHCP_T2bwFixed/rootfiles/T2tt_BDT_histos.root");
    //hc_orig.List();

    int bin = hc_orig["heff_0"]->FindBin(mass_stop, mass_lsp);
    stop::Yield::value_t ul_obs_orig[stop::SignalRegion::static_size] =
    {
        {1000.0*hc_orig["hxsec_0"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_1"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_2"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_3"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_4"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_5"]->GetBinContent(bin), 0},
    };
    stop::Yield::value_t ul_exp_orig[stop::SignalRegion::static_size] =
    {
        {1000.0*hc_orig["hxsec_exp_0"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_0"]->GetBinContent(bin), hc_orig["hxsec_expm1_0"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_1"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_1"]->GetBinContent(bin), hc_orig["hxsec_expm1_1"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_2"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_2"]->GetBinContent(bin), hc_orig["hxsec_expm1_2"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_3"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_3"]->GetBinContent(bin), hc_orig["hxsec_expm1_3"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_4"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_4"]->GetBinContent(bin), hc_orig["hxsec_expm1_4"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_5"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_5"]->GetBinContent(bin), hc_orig["hxsec_expm1_5"]->GetBinContent(bin))},
    };

    // lands 
    const std::string lands_path = "output/limits/lands/t2tt/";
    stop::Yield::value_t ul_obs_m3a[stop::SignalRegion::static_size] =
    {
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt1l_m2lnQ.root", lands_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt1t_m2lnQ.root", lands_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt2_m2lnQ.root" , lands_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt3_m2lnQ.root" , lands_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt4_m2lnQ.root" , lands_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt5_m2lnQ.root" , lands_path.c_str(), mass_stop, mass_lsp)),
    };
    stop::Yield::value_t ul_exp_m3a[stop::SignalRegion::static_size] =
    {
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt1l_m2lnQ.root", lands_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt1t_m2lnQ.root", lands_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt2_m2lnQ.root" , lands_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt3_m2lnQ.root" , lands_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt4_m2lnQ.root" , lands_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt5_m2lnQ.root" , lands_path.c_str(), mass_stop, mass_lsp)),
    };
    
    // output table
    const char* const fmt = "1.3";
    CTable table;
    table.useTitle();
    table.setTitle(Form("Comparison for m_stop = %1.0f and m_lsp = %1.0f", mass_stop, mass_lsp));
    table.setTable()(   "BDT1L"                , "BDT1T"               , "BDT2"                , "BDT3"                , "BDT4"                , "BDT5"                 )
    ("orig obs UL"    , ul_obs_orig[0].value   , ul_obs_orig[1].value  , ul_obs_orig[2].value  , ul_obs_orig[3].value  , ul_obs_orig[4].value  , ul_obs_orig[5].value   )
    ("orig exp UL"    , ul_exp_orig[0].value   , ul_exp_orig[1].value  , ul_exp_orig[2].value  , ul_exp_orig[3].value  , ul_exp_orig[4].value  , ul_exp_orig[5].value   )
    ("Lands obs UL"   , ul_obs_m3a [0].pm(fmt) , ul_obs_m3a [1].pm(fmt), ul_obs_m3a [2].pm(fmt), ul_obs_m3a [3].pm(fmt), ul_obs_m3a [4].pm(fmt), ul_obs_m3a [5].pm(fmt) )
    ("Lands exp UL"   , ul_exp_m3a [0].pm(fmt) , ul_exp_m3a [1].pm(fmt), ul_exp_m3a [2].pm(fmt), ul_exp_m3a [3].pm(fmt), ul_exp_m3a [4].pm(fmt), ul_exp_m3a [5].pm(fmt) )
    ;

    cout << table << std::endl;
}


stop::Yield::value_t ExtractExpUpperLimitCombine(const std::string& filename)
{
    TChain chain("limit");
    chain.Add(filename.c_str());
    stop::Yield::value_t result;
    chain.SetBranchAddress("limit"   , &result.value);
    chain.SetBranchAddress("limitErr", &result.error);
    chain.GetEntry(2);
    return result;
}

stop::Yield::value_t ExtractObsUpperLimitCombine(const std::string& filename)
{
    TChain chain("limit");
    chain.Add(filename.c_str());
    stop::Yield::value_t result;
    chain.SetBranchAddress("limit"   , &result.value);
    chain.SetBranchAddress("limitErr", &result.error);
    chain.GetEntry(5);
    return result;
}

void FillLimitHistogram
(
    TH1F& hist,
    stop::Yield::value_t* const ul
)
{
    hist.Sumw2();
    for (size_t bin = 1; bin <= 6; bin++)
    {
        hist.SetBinContent(bin, ul[bin-1].value);
        hist.SetBinError  (bin, ul[bin-1].error);
    }
    hist.GetXaxis()->SetBinLabel(1, "BDT1L");
    hist.GetXaxis()->SetBinLabel(2, "BDT1T");
    hist.GetXaxis()->SetBinLabel(3, "BDT2" );
    hist.GetXaxis()->SetBinLabel(4, "BDT3" );
    hist.GetXaxis()->SetBinLabel(5, "BDT4" );
    hist.GetXaxis()->SetBinLabel(6, "BDT5" );
    return;
}

void CompareMethodsCombine
(
    const float mass_stop,
    const float mass_lsp
)
{
    // get the original results
    rt::TH1Container hc_orig("/Users/rwk7t/temp/from_ben/exclusion2012_postLHCP_T2bwFixed/rootfiles/T2tt_BDT_histos.root");
    //hc_orig.List();

    int bin = hc_orig["heff_0"]->FindBin(mass_stop, mass_lsp);
    stop::Yield::value_t ul_obs_orig[stop::SignalRegion::static_size] =
    {
        {1000.0*hc_orig["hxsec_0"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_1"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_2"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_3"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_4"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_5"]->GetBinContent(bin), 0},
    };
    stop::Yield::value_t ul_exp_orig[stop::SignalRegion::static_size] =
    {
        {1000.0*hc_orig["hxsec_exp_0"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_exp_1"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_exp_2"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_exp_3"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_exp_4"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_exp_5"]->GetBinContent(bin), 0},
    };


    // get method3 a posteriori (m3a) -- LandS
    std::string limit_path = "output/limits/lands/t2tt";
    stop::Yield::value_t ul_obs_m3a[stop::SignalRegion::static_size] =
    {
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    stop::Yield::value_t ul_exp_m3a[stop::SignalRegion::static_size] =
    {
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_t2tt_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };

    // get method3 (m3c) -- Combine 
    limit_path = "output/limits/combine/t2tt";
    stop::Yield::value_t ul_obs_m3c[stop::SignalRegion::static_size] =
    {
        ExtractObsUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt1l.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt1t.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt2.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt3.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt4.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt5.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    stop::Yield::value_t ul_exp_m3c[stop::SignalRegion::static_size] =
    {
        ExtractExpUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt1l.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt1t.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt2.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt3.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt4.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimitCombine(Form("%s/combine_t2tt_%1.0f_%1.0f_bdt5.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };

    // output table
    const char* const fmt = "1.3";
    CTable table;
    table.useTitle();
    table.setTitle(Form("Comparison for m_stop = %1.0f and m_lsp = %1.0f", mass_stop, mass_lsp));
    table.setTable()(             "BDT1L"                , "BDT1T"               , "BDT2"                , "BDT3"                , "BDT4"                , "BDT5"                 )
    ("orig obs UL"              , ul_obs_orig[0].value   , ul_obs_orig[1].value  , ul_obs_orig[2].value  , ul_obs_orig[3].value  , ul_obs_orig[4].value  , ul_obs_orig[5].value   )
    ("orig exp UL"              , ul_exp_orig[0].value   , ul_exp_orig[1].value  , ul_exp_orig[2].value  , ul_exp_orig[3].value  , ul_exp_orig[4].value  , ul_exp_orig[5].value   )
    ("method3 obs UL (LandS)"   , ul_obs_m3a [0].pm(fmt) , ul_obs_m3a [1].pm(fmt), ul_obs_m3a [2].pm(fmt), ul_obs_m3a [3].pm(fmt), ul_obs_m3a [4].pm(fmt), ul_obs_m3a [5].pm(fmt) )
    ("method3 exp UL (LandS)"   , ul_exp_m3a [0].pm(fmt) , ul_exp_m3a [1].pm(fmt), ul_exp_m3a [2].pm(fmt), ul_exp_m3a [3].pm(fmt), ul_exp_m3a [4].pm(fmt), ul_exp_m3a [5].pm(fmt) )
    ("method3 obs UL (Combine)" , ul_obs_m3c [0].pm(fmt) , ul_obs_m3c [1].pm(fmt), ul_obs_m3c [2].pm(fmt), ul_obs_m3c [3].pm(fmt), ul_obs_m3c [4].pm(fmt), ul_obs_m3c [5].pm(fmt) )
    ("method3 exp UL (Combine)" , ul_exp_m3c [0].pm(fmt) , ul_exp_m3c [1].pm(fmt), ul_exp_m3c [2].pm(fmt), ul_exp_m3c [3].pm(fmt), ul_exp_m3c [4].pm(fmt), ul_exp_m3c [5].pm(fmt) )
    ;
    cout << table << std::endl;

    // output plot
    TH1F h_obs_orig("h_obs_orig", Form("Observed xsec UL Original, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)"       , mass_stop, mass_lsp), 6, 0.5, 6.5);
    TH1F h_exp_orig("h_exp_orig", Form("Expected xsec UL Original, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)"       , mass_stop, mass_lsp), 6, 0.5, 6.5);
    TH1F h_obs_m3a ("h_obs_m3a" , Form("Observed xsec UL method3 LandS, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)"  , mass_stop, mass_lsp), 6, 0.5, 6.5);
    TH1F h_exp_m3a ("h_exp_m3a" , Form("Expected xsec UL method3 LandS, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)"  , mass_stop, mass_lsp), 6, 0.5, 6.5);
    TH1F h_obs_m3c ("h_obs_m3c" , Form("Observed xsec UL method3 combine, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)", mass_stop, mass_lsp), 6, 0.5, 6.5);
    TH1F h_exp_m3c ("h_exp_m3c" , Form("Expected xsec UL method3 combine, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)", mass_stop, mass_lsp), 6, 0.5, 6.5);

    FillLimitHistogram(h_obs_orig, ul_obs_orig);
    FillLimitHistogram(h_exp_orig, ul_exp_orig);
    FillLimitHistogram(h_obs_m3a , ul_obs_m3a );
    FillLimitHistogram(h_exp_m3a , ul_exp_m3a );
    FillLimitHistogram(h_obs_m3c , ul_obs_m3c );
    FillLimitHistogram(h_exp_m3c , ul_exp_m3c );

    TCanvas c1;
    gStyle->SetPadRightMargin(0.05);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetTitleOffset(1.50, "Y"); 
    rt::TH1Overlay p_obs(Form("Observed xsec UL, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)", mass_stop, mass_lsp), "sb::off lg::top_left");
    p_obs.Add(&h_obs_orig, "Original"       , kBlack, 2);
    p_obs.Add(&h_obs_m3a , "method3 LandS"  , kRed  , 2);
    p_obs.Add(&h_obs_m3c , "method3 combine", kBlue , 2);
    p_obs.Draw();
    lt::mkdir("plots/compare/", /*force=*/true);
    c1.Print(Form("plots/compare/p_obs_%1.0f_%1.0f.pdf", mass_stop, mass_lsp));

    rt::TH1Overlay p_exp(Form("Expected xsec UL, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)", mass_stop, mass_lsp), "sb::off lg::top_left");
    p_exp.Add(&h_exp_orig, "Original"       , kBlack, 2);
    p_exp.Add(&h_exp_m3a , "method3 LandS"  , kRed  , 2);
    p_exp.Add(&h_exp_m3c , "method3 combine", kBlue , 2);
    p_exp.Draw();
    c1.Print(Form("plots/compare/p_exp_%1.0f_%1.0f.pdf", mass_stop, mass_lsp));
}

void CompareMethodsFromHists
(
    const float mass_stop,
    const float mass_lsp
)
{
    // get the original results
    rt::TH1Container hc_orig("/Users/rwk7t/temp/from_ben/exclusion2012_postLHCP_T2bwFixed/rootfiles/T2tt_BDT_histos.root");
    //hc_orig.List();

    int bin = hc_orig["heff_0"]->FindBin(mass_stop, mass_lsp);
    stop::Yield::value_t ul_obs_orig[stop::SignalRegion::static_size] =
    {
        {hc_orig["hxsec_0"]->GetBinContent(bin), 0},
        {hc_orig["hxsec_1"]->GetBinContent(bin), 0},
        {hc_orig["hxsec_2"]->GetBinContent(bin), 0},
        {hc_orig["hxsec_3"]->GetBinContent(bin), 0},
        {hc_orig["hxsec_4"]->GetBinContent(bin), 0},
        {hc_orig["hxsec_5"]->GetBinContent(bin), 0},
    };
    stop::Yield::value_t ul_exp_orig[stop::SignalRegion::static_size] =
    {
        {hc_orig["hxsec_exp_0"]->GetBinContent(bin), 0},
        {hc_orig["hxsec_exp_1"]->GetBinContent(bin), 0},
        {hc_orig["hxsec_exp_2"]->GetBinContent(bin), 0},
        {hc_orig["hxsec_exp_3"]->GetBinContent(bin), 0},
        {hc_orig["hxsec_exp_4"]->GetBinContent(bin), 0},
        {hc_orig["hxsec_exp_5"]->GetBinContent(bin), 0},
    };


    // lands 
    rt::TH1Container hc_lands("plots/limits/lands/t2tt/t2tt_bdt_limit_hists.root");
    stop::Yield::value_t ul_obs_m3a[stop::SignalRegion::static_size] =
    {
        {hc_lands["h_xsec_obs_ul_bdt1l"]->GetBinContent(bin), hc_lands["h_xsec_obs_ul_bdt1l"]->GetBinError(bin)},
        {hc_lands["h_xsec_obs_ul_bdt1t"]->GetBinContent(bin), hc_lands["h_xsec_obs_ul_bdt1t"]->GetBinError(bin)},
        {hc_lands["h_xsec_obs_ul_bdt2" ]->GetBinContent(bin), hc_lands["h_xsec_obs_ul_bdt2" ]->GetBinError(bin)},
        {hc_lands["h_xsec_obs_ul_bdt3" ]->GetBinContent(bin), hc_lands["h_xsec_obs_ul_bdt3" ]->GetBinError(bin)},
        {hc_lands["h_xsec_obs_ul_bdt4" ]->GetBinContent(bin), hc_lands["h_xsec_obs_ul_bdt4" ]->GetBinError(bin)},
        {hc_lands["h_xsec_obs_ul_bdt5" ]->GetBinContent(bin), hc_lands["h_xsec_obs_ul_bdt5" ]->GetBinError(bin)},
    };
    stop::Yield::value_t ul_exp_m3a[stop::SignalRegion::static_size] =
    {
        {hc_lands["h_xsec_exp_ul_bdt1l"]->GetBinContent(bin), hc_lands["h_xsec_exp_ul_bdt1l"]->GetBinError(bin)},
        {hc_lands["h_xsec_exp_ul_bdt1t"]->GetBinContent(bin), hc_lands["h_xsec_exp_ul_bdt1t"]->GetBinError(bin)},
        {hc_lands["h_xsec_exp_ul_bdt2" ]->GetBinContent(bin), hc_lands["h_xsec_exp_ul_bdt2" ]->GetBinError(bin)},
        {hc_lands["h_xsec_exp_ul_bdt3" ]->GetBinContent(bin), hc_lands["h_xsec_exp_ul_bdt3" ]->GetBinError(bin)},
        {hc_lands["h_xsec_exp_ul_bdt4" ]->GetBinContent(bin), hc_lands["h_xsec_exp_ul_bdt4" ]->GetBinError(bin)},
        {hc_lands["h_xsec_exp_ul_bdt5" ]->GetBinContent(bin), hc_lands["h_xsec_exp_ul_bdt5" ]->GetBinError(bin)},
    };

    // Combine 
    rt::TH1Container hc_combine("plots/limits/combine/t2tt/t2tt_bdt_limit_hists.root");
    stop::Yield::value_t ul_obs_m3c[stop::SignalRegion::static_size] =
    {
        {hc_combine["h_xsec_obs_ul_bdt1l"]->GetBinContent(bin), hc_combine["h_xsec_obs_ul_bdt1l"]->GetBinError(bin)},
        {hc_combine["h_xsec_obs_ul_bdt1t"]->GetBinContent(bin), hc_combine["h_xsec_obs_ul_bdt1t"]->GetBinError(bin)},
        {hc_combine["h_xsec_obs_ul_bdt2" ]->GetBinContent(bin), hc_combine["h_xsec_obs_ul_bdt2" ]->GetBinError(bin)},
        {hc_combine["h_xsec_obs_ul_bdt3" ]->GetBinContent(bin), hc_combine["h_xsec_obs_ul_bdt3" ]->GetBinError(bin)},
        {hc_combine["h_xsec_obs_ul_bdt4" ]->GetBinContent(bin), hc_combine["h_xsec_obs_ul_bdt4" ]->GetBinError(bin)},
        {hc_combine["h_xsec_obs_ul_bdt5" ]->GetBinContent(bin), hc_combine["h_xsec_obs_ul_bdt5" ]->GetBinError(bin)},
    };
    stop::Yield::value_t ul_exp_m3c[stop::SignalRegion::static_size] =
    {
        {hc_combine["h_xsec_exp_ul_bdt1l"]->GetBinContent(bin), hc_combine["h_xsec_exp_ul_bdt1l"]->GetBinError(bin)},
        {hc_combine["h_xsec_exp_ul_bdt1t"]->GetBinContent(bin), hc_combine["h_xsec_exp_ul_bdt1t"]->GetBinError(bin)},
        {hc_combine["h_xsec_exp_ul_bdt2" ]->GetBinContent(bin), hc_combine["h_xsec_exp_ul_bdt2" ]->GetBinError(bin)},
        {hc_combine["h_xsec_exp_ul_bdt3" ]->GetBinContent(bin), hc_combine["h_xsec_exp_ul_bdt3" ]->GetBinError(bin)},
        {hc_combine["h_xsec_exp_ul_bdt4" ]->GetBinContent(bin), hc_combine["h_xsec_exp_ul_bdt4" ]->GetBinError(bin)},
        {hc_combine["h_xsec_exp_ul_bdt5" ]->GetBinContent(bin), hc_combine["h_xsec_exp_ul_bdt5" ]->GetBinError(bin)},
    };

    // output table
    const char* const fmt = "1.3";
    CTable table;
    table.useTitle();
    table.setTitle(Form("Comparison for m_stop = %1.0f and m_lsp = %1.0f", mass_stop, mass_lsp));
    table.setTable()(             "BDT1L"                , "BDT1T"               , "BDT2"                , "BDT3"                , "BDT4"                , "BDT5"                 )
    ("orig obs UL"              , ul_obs_orig[0].value   , ul_obs_orig[1].value  , ul_obs_orig[2].value  , ul_obs_orig[3].value  , ul_obs_orig[4].value  , ul_obs_orig[5].value   )
    ("orig exp UL"              , ul_exp_orig[0].value   , ul_exp_orig[1].value  , ul_exp_orig[2].value  , ul_exp_orig[3].value  , ul_exp_orig[4].value  , ul_exp_orig[5].value   )
    ("method3 obs UL (LandS)"   , ul_obs_m3a [0].pm(fmt) , ul_obs_m3a [1].pm(fmt), ul_obs_m3a [2].pm(fmt), ul_obs_m3a [3].pm(fmt), ul_obs_m3a [4].pm(fmt), ul_obs_m3a [5].pm(fmt) )
    ("method3 exp UL (LandS)"   , ul_exp_m3a [0].pm(fmt) , ul_exp_m3a [1].pm(fmt), ul_exp_m3a [2].pm(fmt), ul_exp_m3a [3].pm(fmt), ul_exp_m3a [4].pm(fmt), ul_exp_m3a [5].pm(fmt) )
    ("method3 obs UL (Combine)" , ul_obs_m3c [0].pm(fmt) , ul_obs_m3c [1].pm(fmt), ul_obs_m3c [2].pm(fmt), ul_obs_m3c [3].pm(fmt), ul_obs_m3c [4].pm(fmt), ul_obs_m3c [5].pm(fmt) )
    ("method3 exp UL (Combine)" , ul_exp_m3c [0].pm(fmt) , ul_exp_m3c [1].pm(fmt), ul_exp_m3c [2].pm(fmt), ul_exp_m3c [3].pm(fmt), ul_exp_m3c [4].pm(fmt), ul_exp_m3c [5].pm(fmt) )
    ;
    cout << table << std::endl;

    // output plot
    TH1F h_obs_orig("h_obs_orig", Form("Observed xsec UL Original, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)"       , mass_stop, mass_lsp), 6, 0.5, 6.5);
    TH1F h_exp_orig("h_exp_orig", Form("Expected xsec UL Original, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)"       , mass_stop, mass_lsp), 6, 0.5, 6.5);
    TH1F h_obs_m3a ("h_obs_m3a" , Form("Observed xsec UL method3 LandS, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)"  , mass_stop, mass_lsp), 6, 0.5, 6.5);
    TH1F h_exp_m3a ("h_exp_m3a" , Form("Expected xsec UL method3 LandS, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)"  , mass_stop, mass_lsp), 6, 0.5, 6.5);
    TH1F h_obs_m3c ("h_obs_m3c" , Form("Observed xsec UL method3 combine, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)", mass_stop, mass_lsp), 6, 0.5, 6.5);
    TH1F h_exp_m3c ("h_exp_m3c" , Form("Expected xsec UL method3 combine, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)", mass_stop, mass_lsp), 6, 0.5, 6.5);

    FillLimitHistogram(h_obs_orig, ul_obs_orig);
    FillLimitHistogram(h_exp_orig, ul_exp_orig);
    FillLimitHistogram(h_obs_m3a , ul_obs_m3a );
    FillLimitHistogram(h_exp_m3a , ul_exp_m3a );
    FillLimitHistogram(h_obs_m3c , ul_obs_m3c );
    FillLimitHistogram(h_exp_m3c , ul_exp_m3c );

    TCanvas c1;
    gStyle->SetPadRightMargin(0.05);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetTitleOffset(1.50, "Y"); 
    rt::TH1Overlay p_obs(Form("Observed xsec UL, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)", mass_stop, mass_lsp), "sb::off lg::top_left");
    p_obs.Add(&h_obs_orig, "Original"       , kBlack, 2);
    p_obs.Add(&h_obs_m3a , "method3 LandS"  , kRed  , 2);
    p_obs.Add(&h_obs_m3c , "method3 combine", kBlue , 2);
    p_obs.Draw();
    lt::mkdir("plots/compare/", /*force=*/true);
    c1.Print(Form("plots/compare/p_obs_%1.0f_%1.0f.pdf", mass_stop, mass_lsp));

    rt::TH1Overlay p_exp(Form("Expected xsec UL, m_{stop} = %1.0f GeV, m_{LSP} = %1.0f GeV; Signal Regon; #sigma UL (fb)", mass_stop, mass_lsp), "sb::off lg::top_left");
    p_exp.Add(&h_exp_orig, "Original"       , kBlack, 2);
    p_exp.Add(&h_exp_m3a , "method3 LandS"  , kRed  , 2);
    p_exp.Add(&h_exp_m3c , "method3 combine", kBlue , 2);
    p_exp.Draw();
    c1.Print(Form("plots/compare/p_exp_%1.0f_%1.0f.pdf", mass_stop, mass_lsp));
}


void QuickCompareMethodsCombine()
{
    CompareMethodsCombine(300,50);
    CompareMethodsCombine(500,50);
    CompareMethodsCombine(650,50);
}

void PrintComparison
(
    TH1* const h1,
    TH1* const h2,
    const std::string& path,
    const std::string& suffix,
    const std::string& draw_option,
    const std::string& paint_text_option = "1.0f",
    const float zmin = 1.0f,
    const float zmax = -1.0f,
    const float diff_scale = 100.0f
)
{
    const std::string diff_name  = Form("%s_diff", h2->GetName());
    const std::string diff_title = Form("100*(%s_v1 - %s_v2)/%s_v1", h2->GetName(), h2->GetName(), h2->GetName());
    TH1* h_diff = rt::RelativeDiffHists(h1, h2, diff_name, diff_title);
    h_diff->Scale(diff_scale);
    h_diff->SetDirectory(NULL);

    // unzoom
    h1->GetXaxis()->SetRangeUser(75, 825);
    h1->GetYaxis()->SetRangeUser(0 , 725);
    h2->GetXaxis()->SetRangeUser(75, 825);
    h2->GetYaxis()->SetRangeUser(0 , 725);
    h_diff->GetXaxis()->SetRangeUser(75, 825);
    h_diff->GetYaxis()->SetRangeUser(0 , 725);
    if (zmax > zmin)
    {
        h1->GetZaxis()->SetRangeUser(zmin, zmax);
        h2->GetZaxis()->SetRangeUser(zmin, zmax);
    }

    TCanvas c1("c1", "c1", 1600, 1200);
    gStyle->SetPadRightMargin(0.10);
    if (lt::string_contains(draw_option, "colz"))
    {
        gStyle->SetPadRightMargin(0.15);
    }
    {
        gStyle->SetPaintTextFormat(paint_text_option.c_str());
    }
    h1->Draw(draw_option.c_str());
    c1.Print(Form("%s/%s_v1.%s", path.c_str(), h2->GetName(), suffix.c_str()));
    h2->Draw(draw_option.c_str());
    c1.Print(Form("%s/%s_v2.%s", path.c_str(), h2->GetName(), suffix.c_str()));

    gStyle->SetPaintTextFormat("1.0f");
    h_diff->Draw("text"); c1.Print(Form("%s/%s.%s", path.c_str(), diff_name.c_str(), suffix.c_str()));
    delete h_diff;
}

void CompareToBen(const std::string& file_name, const std::string& label = "test1", const std::string& suffix = "pdf")
{
    rt::TH1Container hc1a("/Users/rwk7t/temp/from_ben/exclusion2012_postLHCP_T2bwFixed/rootfiles/T2tt_BDT_histos.root");
    rt::TH1Container hc1b("/Users/rwk7t/temp/from_ben/exclusion2012_postLHCP_T2bwFixed/rootfiles/T2tt_combinePlots_BDT.root");
    rt::TH1Container hc2(file_name);

    gStyle->SetCanvasDefX(1600);
    gStyle->SetCanvasDefY(1200);

    // no stat boxes
    hc1a.SetStats(false);
    hc1b.SetStats(false);
    hc2.SetStats(false);

    std::string path = "plots/compare/t2tt/" + label;
    lt::mkdir(path, true);

    PrintComparison(hc1b["hbest"         ], hc2["h_sr_best"          ], path, suffix, "text", "1.0f", 1, -1, 100);
    PrintComparison(hc1a["hxsec_0"       ], hc2["h_xsec_obs_ul_bdt1l"], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1a["hxsec_1"       ], hc2["h_xsec_obs_ul_bdt1t"], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1a["hxsec_2"       ], hc2["h_xsec_obs_ul_bdt2" ], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1a["hxsec_3"       ], hc2["h_xsec_obs_ul_bdt3" ], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1a["hxsec_4"       ], hc2["h_xsec_obs_ul_bdt4" ], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1a["hxsec_5"       ], hc2["h_xsec_obs_ul_bdt5" ], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1b["hxsec_best_exp"], hc2["h_xsec_exp_ul_best" ], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1b["hxsec_best"    ], hc2["h_xsec_obs_ul_best" ], path, suffix, "text", "1.1f", 1, -1, 100);
}

void CompareToLandS(const std::string& label = "test1", const std::string& suffix = "pdf")
{
    rt::TH1Container hc1("plots/limits/lands/t2tt/t2tt_bdt_limit_hists.root");
    rt::TH1Container hc2("plots/limits/combine/t2tt/t2tt_bdt_limit_hists.root");

    gStyle->SetCanvasDefX(1600);
    gStyle->SetCanvasDefY(1200);

    // no stat boxes
    hc1.SetStats(false);
    hc2.SetStats(false);

    std::string path = "plots/compare/t2tt/" + label;
    lt::mkdir(path, true);

    PrintComparison(hc1["h_sr_best"          ], hc2["h_sr_best"          ], path, suffix, "text", "1.0f", 1, -1, 100);
    PrintComparison(hc1["h_xsec_obs_ul_bdt1l"], hc2["h_xsec_obs_ul_bdt1l"], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1["h_xsec_obs_ul_bdt1l"], hc2["h_xsec_obs_ul_bdt1l"], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1["h_xsec_obs_ul_bdt1t"], hc2["h_xsec_obs_ul_bdt1t"], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1["h_xsec_obs_ul_bdt2" ], hc2["h_xsec_obs_ul_bdt2" ], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1["h_xsec_obs_ul_bdt3" ], hc2["h_xsec_obs_ul_bdt3" ], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1["h_xsec_obs_ul_bdt4" ], hc2["h_xsec_obs_ul_bdt4" ], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1["h_xsec_obs_ul_bdt5" ], hc2["h_xsec_obs_ul_bdt5" ], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1["h_xsec_exp_ul_best" ], hc2["h_xsec_exp_ul_best" ], path, suffix, "text", "1.1f", 1, -1, 100);
    PrintComparison(hc1["h_xsec_obs_ul_best" ], hc2["h_xsec_obs_ul_best" ], path, suffix, "text", "1.1f", 1, -1, 100);
}

void QuickCompareHists()
{
/*      CompareToBen("plots/limits/lands/t2tt/t2tt_bdt_limit_hists.root"  , "lands"  , "eps"); */
/*      CompareToBen("plots/limits/combine/t2tt/t2tt_bdt_limit_hists.root", "combine", "eps"); */
/*      CompareToLandS("lands_combine", "eps"); */
}
