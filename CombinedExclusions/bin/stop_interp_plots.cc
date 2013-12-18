// C++ includes
#include <iostream>
#include <string>
#include <stdexcept>

// ROOT includes
#include "TH1.h"
#include "TFile.h"
#include "TSystem.h"
#include "TChain.h"
#include "TBenchmark.h"
#include "TTreeCache.h"
#include "TStyle.h"

// CMSSW includes
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

// Tools
#include "AnalysisTools/RootTools/interface/RootTools.h"
#include "AnalysisTools/LanguageTools/interface/LanguageTools.h"
#include "StopAnalysis/CombinedExclusions/interface/Sample.h"
#include "StopAnalysis/CombinedExclusions/interface/AnalysisType.h"
#include "StopAnalysis/CombinedExclusions/interface/SignalRegion.h"
#include "StopAnalysis/CombinedExclusions/interface/STOP_BABY.h"

// ------------------------------------------------------------------------------------ //
// Looper class to hold all the variables and make the histograms 
// ------------------------------------------------------------------------------------ //

class InterpLooper
{
    public:
        // construct: 
        InterpLooper
        (
             const std::string& output_file_name,
             const std::string& sample_name,
             const std::string& analysis_type_name,
             const std::string& xsec_file_path,
             const std::string& xsec_hist_name,
             const std::vector<unsigned int>& sr_nums,
             const double lumi,
             const double mass_stop,
             const double mass_lsp,
             const double unc_lumi,
             const double unc_trig,
             const double unc_lept,
             const std::string& suffix,
             const bool verbose
        );

        // destroy:
        ~InterpLooper();

        // public methods:
        void ScanChain
        (
            TChain& dataset,
            const long long num_events = -1,
            const int evt_run = -1,   // -1 == all runs
            const int evt_lumi = -1,  // -1 == all lumis
            const int evt_event = -1  // -1 == all events
        );

    private:

        // parameter members:
        const std::string m_output_file_name;
        const std::string m_sample_name;
        const std::string m_analysis_type_name;
        const std::string m_xsec_file_path;
        const std::string m_xsec_hist_name;
        const std::vector<unsigned int> m_sr_nums;
        const double m_lumi;
        const double m_mass_stop;
        const double m_mass_lsp;
        const double m_unc_lumi;
        const double m_unc_trig;
        const double m_unc_lept;
        const std::string m_suffix;
        const bool m_verbose;

        // members
        stop::AnalysisType::value_type m_analysis_type;
        stop::Sample::value_type m_sample;
        rt::TH1Container m_hist_container;

        // private methods:
        void BeginJob();
        void EndJob();
        void Analyze();
        void CalculateEfficiencyAndUncertainties();
};

// construct:
InterpLooper::InterpLooper
(
    const std::string& output_file_name,
    const std::string& sample_name,
    const std::string& analysis_type_name,
    const std::string& xsec_file_path,
    const std::string& xsec_hist_name,
    const std::vector<unsigned int>& sr_nums,
    const double lumi,
    const double mass_stop,
    const double mass_lsp,
    const double unc_lumi,
    const double unc_trig,
    const double unc_lept,
    const std::string& suffix,
    const bool verbose
)
    : m_output_file_name(output_file_name)
    , m_sample_name(sample_name)
    , m_analysis_type_name(analysis_type_name)
    , m_xsec_file_path(xsec_file_path)
    , m_xsec_hist_name(xsec_hist_name)
    , m_sr_nums(sr_nums)
    , m_lumi(lumi)
    , m_mass_stop(mass_stop)
    , m_mass_lsp(mass_lsp)
    , m_unc_lumi(unc_lumi)
    , m_unc_trig(unc_trig)
    , m_unc_lept(unc_lept)
    , m_suffix(suffix)
    , m_verbose(verbose)
    , m_analysis_type(stop::GetAnalysisTypeFromName(m_analysis_type_name))
    , m_sample(stop::GetSampleFromName(m_sample_name))
    , m_hist_container()
{
    // run begin job when object is constructed
    BeginJob();
}

// destroy:
InterpLooper::~InterpLooper()
{
    // run end job when object is destroyed 
    EndJob();
}

// operations performed at the beginning of the job
void InterpLooper::BeginJob()
{
    // set the style
    rt::SetStyle();

    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // book all the histograms
    const int   nbinsx            = 41;
    const float xmin              = -12.5;
    const float xmax              = 1012.5;
    const std::string xaxis_label = "m_{#tilde{t}} (GeV)";
    const int   nbinsy            = 41;
    const float ymin              = -12.5;
    const float ymax              = 1012.5;
    const std::string yaxis_label = "m_{#tilde{#chi}^{0}_{1}} (GeV)";

    // signal histograms 
    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const stop::SignalRegionInfo sr_info = stop::GetSignalRegionInfo(Form("sr%d", m_sr_nums.at(i))); 
        const std::string bin_stem = Form("(%s);%s;%s", sr_info.title.c_str(), xaxis_label.c_str(), yaxis_label.c_str());

        hc.Add(new TH2F(Form("h_nevt_%s"      , sr_info.label.c_str()), Form("# Raw Count Passing %s"  , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_num_%s"       , sr_info.label.c_str()), Form("# Passing with scale1fb*lumi %s"              , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_eff_%s"       , sr_info.label.c_str()), Form("Efficiency with scale1fb*lumi %s"             , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_eff_perc_%s"  , sr_info.label.c_str()), Form("Efficiency Percentage with scale1fb*lumi %s"  , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_num_jesup_%s" , sr_info.label.c_str()), Form("# Passing with scale1fb*lumi, JES+ %s"        , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_num_jesdn_%s" , sr_info.label.c_str()), Form("# Passing with scale1fb*lumi, JES- %s"        , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_err_jes_%s"   , sr_info.label.c_str()), Form("Uncertainy with scale1fb*lumi, JES+/- %s"     , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_num_btagup_%s", sr_info.label.c_str()), Form("# Passing with scale1fb*lumi, BTAG+ %s"       , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_num_btagdn_%s", sr_info.label.c_str()), Form("# Passing with scale1fb*lumi, BTAG- %s"       , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_err_btag_%s"  , sr_info.label.c_str()), Form("Uncertainy with scale1fb*lumi, BTAG+/- %s"    , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_num_noisr_%s" , sr_info.label.c_str()), Form("# Passing with scale1fb*lumi, ISR %s"         , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_err_noisr_%s" , sr_info.label.c_str()), Form("Uncertainy with scale1fb*lumi, ISR %s"        , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_err_total_%s" , sr_info.label.c_str()), Form("Uncertainy with scale1fb*lumi, Total %s"      , bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
        hc.Add(new TH2F(Form("h_err_stats_%s" , sr_info.label.c_str()), Form("Uncertainy with scale1fb*lumi, Statistical %s", bin_stem.c_str()), nbinsx, xmin, xmax, nbinsy, ymin, ymax));
    }

    // number of generated events (from the file)
    TH2F* h_ngen = stop::GetSampleNGenHist(m_sample);
    h_ngen->SetNameTitle("h_ngen", Form("# Generated;%s;%s", xaxis_label.c_str(), yaxis_label.c_str()));
    hc.Add(h_ngen); // hc own's the object now

    // xsec histogram
    TFile xsec_file(m_xsec_file_path.c_str());
    TH1F* h_xsec = dynamic_cast<TH1F*>(xsec_file.Get(m_xsec_hist_name.c_str()));
    h_xsec->SetNameTitle("h_xsec", "Cross Section #tilde{t} Pair Production;m_{#tilde{t}} (GeV);Cross Section (pb)");
    h_xsec->SetDirectory(NULL);
    hc.Add(h_xsec); // hc own's the object now

    // scale1fb histogram
    TH2F* h_scale1fb = dynamic_cast<TH2F*>(h_ngen->Clone("h_scale1fb"));
    h_scale1fb->SetTitle(Form("Scale1fb Histogram;%s;%s", xaxis_label.c_str(), yaxis_label.c_str()));
    for (int xbin = 1; xbin != h_scale1fb->GetNbinsX()+1; xbin++)
    {
        for (int ybin = 1; ybin != h_scale1fb->GetNbinsY()+1; ybin++)
        {
            const float mass_stop = h_ngen->GetXaxis()->GetBinCenter(xbin);
            const float mass_lsp  = h_ngen->GetYaxis()->GetBinCenter(ybin);
            const float xsec      = rt::GetBinContent1D(h_xsec, mass_stop); 
            const float ngen      = rt::GetBinContent2D(h_ngen, mass_stop, mass_lsp);
            const float scale1fb  = (ngen > 0 ? xsec * 1000.0f/ngen : 0.0f); 
            rt::SetBinContent2D(h_scale1fb, mass_stop, mass_lsp, scale1fb, /*error=*/0.0);
        }
    }
    h_scale1fb->SetDirectory(NULL);
    hc.Add(h_scale1fb); // hc own's the object now

    // multiply the ngen hist got scaled denominator event count
    hc.Add(rt::MultiplyHists(h_ngen, h_scale1fb, "h_den", Form("# Generated with scale1fb*lumi;%s;%s", xaxis_label.c_str(), yaxis_label.c_str())));
    hc["h_den"]->Scale(m_lumi);

    // set sumw2
    hc.Sumw2();

    if (m_verbose)
    {
        std::cout << "[InterpLooper::BeginJob] The following histgrams are booked: " << std::endl;
        hc.List();
    }
}

// operations performed at the end of the job
void InterpLooper::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // calculate the efficiencies/uncertainties
    CalculateEfficiencyAndUncertainties();

    // save the plots
    if (m_verbose) {std::cout << "[InterpLooper::EndJob] InterpLooper saving histograms." << std::endl;}
    hc.Write(m_output_file_name);

    // print the plots
    if (not m_suffix.empty())
    {
        if (m_verbose) {std::cout << "[InterpLooper::EndJob] printing histograms:" << std::endl;}
        gStyle->SetPaintTextFormat("0.0f");
        hc.Print(lt::dirname(m_output_file_name), m_suffix, "text");
    }
}
       
// selection helper functions
// ------------------------------------------------------------------------------------ //

struct ScaleType
{
    enum value_type
    {
        NONE,
        JES_UP,
        JES_DN,
        BTAG_UP,
        BTAG_DN,
        static_size
    };
};

const bool PassesPreselection
(
    const stop::AnalysisType::value_type analysis_type,
    const ScaleType::value_type scale_type = ScaleType::NONE
)
{
    using namespace stop;
    if (analysis_type == AnalysisType::bdt)
    {
        // contant values (independent of scale type)
        const bool passes_rho        = (rhovor()>0 && rhovor()<40                                                                                                      ); 
        const bool passes_goodlep    = (ngoodlep() > 0 && fabs(pflep1().pt() - lep1().pt()) < 10.0 && fabs(isopf1() * lep1().pt()) < 5.0                               ); 
        const bool passes_el         = (leptype() == 0 && fabs(lep1().eta()) < 1.4442 && lep1().pt() > 30.0 && eoverpin() < 4.0 && (isdata() == 0 || ele27wp80() == 1) ); 
        const bool passes_mu         = (leptype() == 1 && fabs(lep1().eta()) < 2.1    && lep1().pt() > 25.0 && (isdata() == 0 || isomu24() == 1)                       ); 
        const bool passes_passisotrk = (mini_passisotrk() == 1                                                                                                         ); 
        const bool passes_tauveto    = (mini_passtauveto() == 1                                                                                                        ); 
        const bool passes_testing    = (event()%2 == 0                                                                                                                 ); 
        
        // baseline preslection value
        int   temp_njets = mini_njets();
        float temp_met   = mini_met();
        float temp_mt    = mini_mt();
        int   temp_nb    = mini_nb();

        // select the appropriate variable to cut on based on the scale type
        switch(scale_type)
        {
            case ScaleType::NONE:
                temp_njets = mini_njets();
                temp_met   = mini_met();
                temp_mt    = mini_mt();
                temp_nb    = mini_nb();
                break;
            case ScaleType::JES_UP:
                temp_njets = mini_njetsup();
                temp_met   = mini_metup();
                temp_mt    = mini_mtup();
                temp_nb    = mini_nb();
                break;
            case ScaleType::JES_DN:
                temp_njets = mini_njetsdown();
                temp_met   = mini_metdown();
                temp_mt    = mini_mtdown();
                temp_nb    = mini_nb();
                break;
            case ScaleType::BTAG_UP:
                temp_njets = mini_njets();
                temp_met   = mini_met();
                temp_mt    = mini_mt();
                temp_nb    = mini_nbupBC();
                break;
            case ScaleType::BTAG_DN:
                temp_njets = mini_njets();
                temp_met   = mini_met();
                temp_mt    = mini_mt();
                temp_nb    = mini_nbdownBC();
                break;
            default: {/*do nothing*/}
        };

        // apply cuts for scale type dependent variables
        bool passes_njets4  = (temp_njets >= 4  ); 
        bool passes_met100  = (temp_met > 100   ); 
        bool passes_mt120   = (temp_mt > 120    ); 
        bool passes_btag1   = (temp_nb >= 1     ); 
    
        // preselection decision
        bool passes_presel = passes_rho
                           && passes_goodlep
                           && (passes_el or passes_mu)
                           && passes_njets4
                           && passes_btag1
                           && passes_passisotrk
                           && passes_tauveto
                           && passes_met100
                           && passes_mt120
                           && (analysis_type == AnalysisType::bdt ? passes_testing : true);

        // return decision
        return passes_presel;
    }
    else
    {
        std::cout << "[InterpLooper::PassesPreslection] selection returning false for unsupported analysis type" << std::endl;
        return false;
    }
}

// passes signal region
const bool PassesSignalRegion
(
    const stop::SignalRegion::value_type signal_region,
    const stop::AnalysisType::value_type analysis_type,
    const ScaleType::value_type scale_type
)
{
    // check that it passes the preselection
    if (not PassesPreselection(analysis_type, scale_type))
    {
        return false;
    }

    using namespace stop;
    const std::vector<float>* bdt_ptr = NULL;
    switch(scale_type)
    {
        case ScaleType::NONE   : bdt_ptr = &mini_bdt()     ; break;
        case ScaleType::JES_UP : bdt_ptr = &mini_bdtup()   ; break;
        case ScaleType::JES_DN : bdt_ptr = &mini_bdtdown() ; break;
        case ScaleType::BTAG_UP: bdt_ptr = &mini_bdtbup()  ; break;
        case ScaleType::BTAG_DN: bdt_ptr = &mini_bdtbdown(); break;
        default: 
        {
            std::cout << "[InterpLooper::PassesSignalRegion] selection returning false for unsupported scale type" << std::endl;
            return false;
        }
    };
    const std::vector<float>& bdt = *bdt_ptr;
    if (analysis_type == AnalysisType::bdt)
    {
        switch(signal_region)
        {
            case SignalRegion::sr0: return true; // preselection only
            case SignalRegion::sr1: return (bdt.at(1) > 0.30);
            case SignalRegion::sr2: return (bdt.at(1) > 0.40);
            case SignalRegion::sr3: return (bdt.at(2) > 0.55);
            case SignalRegion::sr4: return (bdt.at(3) > 0.65);
            case SignalRegion::sr5: return (bdt.at(4) > 0.50);
            case SignalRegion::sr6: return (bdt.at(5) > 0.30);
            default: return false; 
        }
    }
    else
    {
        std::cout << "[InterpLooper::PassesSignalRegion] selection returning false for unsupported analysis type" << std::endl;
        return false;
    }
}


// operations performed per event 
void InterpLooper::Analyze()
{
    using namespace std;
    using namespace stop;

    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // print susy point for the event
    if (m_verbose)
    {
        cout << "mass point:" << endl; 
        cout << Form("m0   = %1.2f", m0() ) << endl;
        cout << Form("ml   = %1.2f", ml() ) << endl;
        cout << Form("mg   = %1.2f", mg() ) << endl;
        cout << Form("m12s = %1.2f", m12()) << endl;
        cout << endl;
    }

    // selected susy parameters 
    // ---------------------------------------------------------------------------------------------------------------------------- //

    const double mass_stop = mg(); // names from babies aren't consistent
    const double mass_lsp  = ml(); // names from babies aren't consistent

    // if the value of m_m_sparm0 negative, this check is skipped
    if (m_mass_stop >= 0.0f && not lt::is_equal(m_mass_stop, mass_stop))
    {
        if (m_verbose) {cout << Form("fails the m_stop check: %1.2f != %1.2f", m_mass_stop, mass_stop) << endl;}
        return;
    }

    // if the value of m_sparm1 is negative, this check is skipped
    if (m_mass_lsp >= 0.0f && not lt::is_equal(m_mass_lsp, mass_lsp))
    {
        if (m_verbose) {cout << Form("fails the m_lsp check: %1.2f != %1.2f", m_mass_lsp, mass_lsp) << endl;}
        return;
    }

    // does it pass the preselection?
    //--------------------------------------------------
    const bool passes_presel_nominal = PassesPreselection(m_analysis_type, ScaleType::NONE);
    const bool passes_presel_jes_up  = PassesPreselection(m_analysis_type, ScaleType::JES_UP);
    const bool passes_presel_jes_dn  = PassesPreselection(m_analysis_type, ScaleType::JES_DN);
    const bool passes_presel_btag_up = PassesPreselection(m_analysis_type, ScaleType::BTAG_UP);
    const bool passes_presel_btag_dn = PassesPreselection(m_analysis_type, ScaleType::BTAG_DN);

    if (not (passes_presel_nominal or passes_presel_jes_up or passes_presel_jes_dn or 
             passes_presel_btag_up or passes_presel_btag_dn))
    {
        if (m_verbose) {cout << "fails the preselection" << endl;}
        return;
    }

    // Weight Factors
    // ----------------------------------------------------------------------------------------------------------------------------//

    // scale1fb
    const float xsec     = rt::GetBinContent1D(hc["h_xsec"], mass_stop); 
    const float ngen     = rt::GetBinContent2D(hc["h_ngen"], mass_stop, mass_lsp);
    const float scale1fb = (ngen > 0 ? xsec * 1000.0f/ngen : -999999.0f); 

    // scale factors
    float evt_weight_noisr = scale1fb * m_lumi * mini_sltrigeff() * 2.0;
    float evt_weight       = evt_weight_noisr * mini_isrweight();

    // vertex re-weight (not used) 
    const float vtxw = 1.0;
    evt_weight       *= vtxw;
    evt_weight_noisr *= vtxw;

    // Fill hists
    // ------------------------------------------------------------------------------------//

    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const stop::SignalRegion::value_type signal_region = stop::GetSignalRegionFromName(Form("sr%d", m_sr_nums.at(i))); 
        const std::string sr_label = stop::GetSignalRegionInfo(signal_region).label; 

        // number of signal events (nominal)
        if (PassesSignalRegion(signal_region, m_analysis_type, ScaleType::NONE))
        {
            rt::Fill2D(hc["h_nevt_"     +sr_label], mass_stop, mass_lsp, 1.0             ); 
            rt::Fill2D(hc["h_num_"      +sr_label], mass_stop, mass_lsp, evt_weight      ); 
            rt::Fill2D(hc["h_num_noisr_"+sr_label], mass_stop, mass_lsp, evt_weight_noisr); 
        }
        // number of signal events (JES UP)
        if (PassesSignalRegion(signal_region, m_analysis_type, ScaleType::JES_UP))
        {
            rt::Fill2D(hc["h_num_jesup_"+sr_label], mass_stop, mass_lsp, evt_weight);
        }
        // number of signal events (JES Down)
        if (PassesSignalRegion(signal_region, m_analysis_type, ScaleType::JES_DN))
        {
            rt::Fill2D(hc["h_num_jesdn_"+sr_label], mass_stop, mass_lsp, evt_weight);
        }
        // number of signal events (Btag UP)
        if (PassesSignalRegion(signal_region, m_analysis_type, ScaleType::BTAG_UP))
        {
            rt::Fill2D(hc["h_num_btagup_"+sr_label], mass_stop, mass_lsp, evt_weight);
        }
        // number of signal events (Btag Down)
        if (PassesSignalRegion(signal_region, m_analysis_type, ScaleType::BTAG_DN))
        {
            rt::Fill2D(hc["h_num_btagdn_"+sr_label], mass_stop, mass_lsp, evt_weight);
        }
    }

    // done
    return;
}

// calculate the efficiencies and uncertainties
void InterpLooper::CalculateEfficiencyAndUncertainties()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // looper over num/den hists and divide
    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const stop::SignalRegion::value_type signal_region = stop::GetSignalRegionFromName(Form("sr%d", m_sr_nums.at(i))); 
        const std::string sr_label = stop::GetSignalRegionInfo(signal_region).label; 

        const unsigned int nbinsx = hc["h_den"]->GetNbinsX()+1;
        const unsigned int nbinsy = hc["h_den"]->GetNbinsY()+1;
        for (unsigned int xbin = 1; xbin < nbinsx; xbin++)
        {
            for (unsigned int ybin = 1; ybin < nbinsy; ybin++)
            {
                const float num = hc["h_num_"+sr_label]->GetBinContent(xbin, ybin);
                const float den = hc["h_den"          ]->GetBinContent(xbin ,ybin);

                float eff       = 0.0;
                float unc_jes   = 0.0;
                float unc_btag  = 0.0;
                float unc_noisr = 0.0;
                float unc_stats = 0.0;
                float unc_total = 0.0;
                if (den > 0.0 and num >= 0.0)
                {
                    // nominal efficiency
                    eff = num / den;

                    // JES +/-
                    const float num_jes_up = hc["h_num_jesup_"+sr_label]->GetBinContent(xbin, ybin);
                    const float num_jes_dn = hc["h_num_jesdn_"+sr_label]->GetBinContent(xbin, ybin);
                    const float eff_jes_up = (num_jes_up) / den;
                    const float eff_jes_dn = (num_jes_dn) / den;
                    const float unc_jes_up = fabs(eff_jes_up/eff-1.0);
                    const float unc_jes_dn = fabs(1.0-eff_jes_dn/eff);
                    unc_jes    = 0.5 * (unc_jes_up + unc_jes_dn);

                    // Btag +/-
                    const float num_btag_up = hc["h_num_btagup_"+sr_label]->GetBinContent(xbin, ybin);
                    const float num_btag_dn = hc["h_num_btagdn_"+sr_label]->GetBinContent(xbin, ybin);
                    const float eff_btag_up = (num_btag_up) / den;
                    const float eff_btag_dn = (num_btag_dn) / den;
                    const float unc_btag_up = fabs(eff_btag_up/eff-1.0);
                    const float unc_btag_dn = fabs(1.0-eff_btag_dn/eff);
                    unc_btag    = 0.5 * (unc_btag_up + unc_btag_dn);

                    // no ISR
                    const float num_noisr = hc["h_num_noisr_"+sr_label]->GetBinContent(xbin, ybin);
                    const float eff_noisr = (num_noisr) / den;
                    unc_noisr = fabs(1.0-eff/eff_noisr);

                    // stats error
                    const float nevt = hc["h_nevt_"+sr_label]->GetBinContent(xbin, ybin);
                    unc_stats = (nevt > 0.0 ? 1.0/sqrt(nevt) : 0.0);

                    // total systematic unc
                    // lumi (4.4%), trigger (3%), lepton selection (5%), JES, ISR, btagging
                    unc_total = sqrt(m_unc_lumi*m_unc_lumi + m_unc_trig*m_unc_trig + m_unc_lept*m_unc_lept +
                                     unc_jes*unc_jes + unc_noisr*unc_noisr + unc_btag*unc_btag);
                }
                hc["h_eff_"      +sr_label]->SetBinContent(xbin, ybin, eff      );
                hc["h_eff_perc_" +sr_label]->SetBinContent(xbin, ybin, eff*100.0);
                hc["h_err_jes_"  +sr_label]->SetBinContent(xbin, ybin, unc_jes  );
                hc["h_err_btag_" +sr_label]->SetBinContent(xbin, ybin, unc_btag );
                hc["h_err_noisr_"+sr_label]->SetBinContent(xbin, ybin, unc_noisr);
                hc["h_err_stats_"+sr_label]->SetBinContent(xbin, ybin, unc_stats);
                hc["h_err_total_"+sr_label]->SetBinContent(xbin, ybin, unc_total);
            }
        }
    } // end sr loop

    return;
}

// boiler plate code to perform a analysis on a chain
// (no run list or duplicate removal at the moment)
void InterpLooper::ScanChain
(
    TChain& chain,
    const long long num_events,
    const int evt_run,
    const int evt_lumi,
    const int evt_event
)
{
    using namespace std;

    if (m_verbose)
    {
        printf("[InterpLooper::ScanChain] running on files:\n"); 
        rt::PrintFilesFromTChain(chain);
    }

    // test chain
    if (chain.GetListOfFiles()->GetEntries()<1)
    {
        throw std::invalid_argument("[InterpLooper::ScanChain] Error: chain has no files!");
    }
    if (not chain.GetFile())
    {
        throw std::invalid_argument("[InterpLooper::ScanChain] Error: chain has no files or file path is invalid!");
    }

    // tree name
    string tree_name = chain.GetName();

    // benchmark
    TBenchmark bmark;
    bmark.Start("benchmark");

    // events counts and max events
    int i_permilleOld = 0;
    long num_events_total = 0;
    long num_events_chain = (num_events >= 0 && num_events < chain.GetEntries()) ? num_events : chain.GetEntries();
    TObjArray* list_of_files = chain.GetListOfFiles();
    TIter file_iter(list_of_files);
    TFile* current_file = NULL;

    // loop over files in the chain
    while ((current_file = (TFile*)file_iter.Next()))
    {
        TFile *file = TFile::Open(current_file->GetTitle());
        if (!file || file->IsZombie())
        {
            throw std::runtime_error(Form("[InterpLooper::ScanChain] Error: File from TChain is invalid or corrupt: %s", current_file->GetTitle()));
        }

        // get the trees in each file
        TTree *tree = dynamic_cast<TTree*>(file->Get(tree_name.c_str()));
        if (!tree || tree->IsZombie())
        {
            throw std::runtime_error(Form("[InterpLooper::ScanChain] Error: File from TChain has an invalid TTree or is corrupt: %s", current_file->GetTitle()));
        }
        TTreeCache::SetLearnEntries(10);
        tree->SetCacheSize(128*1024*1024);
        stop_baby_obj.Init(tree);

        // Loop over Events in current file
        if (num_events_total >= num_events_chain) continue;
        long num_events_tree = tree->GetEntriesFast();

        // loop over events to Analyze
        for (long event = 0; event != num_events_tree; ++event)
        {
            // quit if the total is > the number in the chain
            if (num_events_total >= num_events_chain) continue;

            // load the entry
            tree->LoadTree(event);
            stop_baby_obj.GetEntry(event);
            ++num_events_total;

            // pogress
            int i_permille = (int)floor(1000 * num_events_total / float(num_events_chain));
            if (i_permille != i_permilleOld)
            {
                printf("  \015\033[32m ---> \033[1m\033[31m%4.1f%%" "\033[0m\033[32m <---\033[0m\015", i_permille/10.);
                fflush(stdout);
                i_permilleOld = i_permille;
            }

            // check run/ls/evt
            unsigned int run = stop_baby_obj.run();
            unsigned int ls  = stop_baby_obj.lumi();
            unsigned int evt = stop_baby_obj.event();

            if (evt_event >= 0)
            {
                if (evt==static_cast<unsigned int>(evt_event))
                {
                    if (m_verbose) {cout << "[ScanChain] selected event:\t" << evt << endl;}
                }
                else
                {
                    continue;
                }
            }
            if (evt_lumi >= 0)
            {
                if (ls==static_cast<unsigned int>(evt_lumi))
                {
                    if (m_verbose) {cout << "[ScanChain] selected lumi:\t" << ls << endl;}
                }
                else
                {
                    continue;
                }
            }
            if (evt_run >= 0)
            {
                if (ls==static_cast<unsigned int>(evt_run))
                {
                    if (m_verbose) {cout << "[ScanChain] selected run:\t" << run << endl;}
                }
                else
                {
                    continue;
                }
            }

            // print run/ls/event
            if (m_verbose)
            {
                cout << Form("[ScanChain] run %d, ls %d, evt %d", run, ls, evt) << endl;
            }

            // analysis
            Analyze();

        } // end event loop

        // close current file
        file->Close();
        delete file;

    } // end file loop

    // print warning if the totals don't line up
    if (num_events_chain != num_events_total) 
    {
        cout << "[InterpLooper::ScanChain] Error: number of events from the files " 
            << "(" << num_events_chain << ") " 
            << "is not equal to the total number of events "
            << "(" << num_events_total << ")." 
            << endl;
    }

    // the benchmark results 
    // -------------------------------------------------------------------------------------------------//
    bmark.Stop("benchmark");
    cout << endl;
    cout << "[InterpLooper::ScanChain] " << num_events_total << " Events Processed" << endl;
    cout << "------------------------------" << endl;
    cout << "CPU  Time: " << Form("%.01f", bmark.GetCpuTime("benchmark" )) << endl;
    cout << "Real Time: " << Form("%.01f", bmark.GetRealTime("benchmark")) << endl;
    cout << endl;

    // done
    return;
}

// ------------------------------------------------------------------------------------ //
// The main program 
// ------------------------------------------------------------------------------------ //

int main(int argc, char **argv)
try
{
    using namespace std;

    // FWLite libs
    gSystem->Load("libFWCoreFWLite");
    AutoLibraryLoader::enable();

    // parse the inputs
    // -------------------------------------------------------------------------------------------------//

    // check that the python is passed
    if (argc < 2)
    {
        throw std::invalid_argument(Form("Usage : %s [parameters.py]", argv[0]));
    }

    // check that pset contains "process" 
    const std::string pset_filename = argv[1];
    if (!edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process"))
    {
        throw std::invalid_argument(Form("[stop_interp_plots] Error: ParametersSet 'process' is missing in your configuration file"));
    }

    // get the python configuration
    const edm::ParameterSet& process = edm::readPSetsFrom(pset_filename)->getParameter<edm::ParameterSet>("process");
    const edm::ParameterSet& cfg     = process.getParameter<edm::ParameterSet>("stop_interp_plots");

    // get the inputs 
    const long long max_events                     = cfg.getParameter<long long>("max_events");
    const bool verbose                             = cfg.getParameter<bool>("verbose");
    const std::string analysis_path                = cfg.getParameter<std::string>("analysis_path");
    const std::string suffix                       = cfg.getParameter<std::string>("suffix");
    const std::string output_label                 = cfg.getParameter<std::string>("output_label");
    const std::string sample_name                  = cfg.getParameter<std::string>("sample_name");
    const std::string analysis_type_name           = cfg.getParameter<std::string>("analysis_type_name");
    const std::string xsec_file_path               = cfg.getParameter<std::string>("xsec_file_path");
    const std::string xsec_hist_name               = cfg.getParameter<std::string>("xsec_hist_name");
    const double lumi                              = cfg.getParameter<double>("lumi");
    const double mass_stop                         = cfg.getParameter<double>("mass_stop");
    const double mass_lsp                          = cfg.getParameter<double>("mass_lsp");
    const double unc_lumi                          = cfg.getParameter<double>("unc_lumi");
    const double unc_trig                          = cfg.getParameter<double>("unc_trig");
    const double unc_lept                          = cfg.getParameter<double>("unc_lept");
    const std::vector<unsigned int> search_regions = cfg.getParameter<std::vector<unsigned int> >("search_regions");

    // for each search region, makes the set of histograms
    // -------------------------------------------------------------------------------------------------//

    // output ROOT file name
    const std::string output_file_name = Form("%s/plots/%s/%s_%s_hists.root",
            analysis_path.c_str(),
            output_label.c_str(),
            sample_name.c_str(),
            analysis_type_name.c_str()
    );

    // print out the parameters for each run
    cout << "\n[stop_interp_plots] running with the following inputs:" << endl;
    printf("%-25s = %lld\n"  , "max_events"         , max_events                 ); 
    printf("%-25s = %1.1f\n" , "lumi"               , lumi                       ); 
    printf("%-25s = %s\n"    , "sample_name"        , sample_name.c_str()        ); 
    printf("%-25s = %s\n"    , "analysis_type_name" , analysis_type_name.c_str() ); 
    printf("%-25s = %s\n"    , "xsec_file_path"     , xsec_file_path.c_str()     ); 
    printf("%-25s = %s\n"    , "xsec_hist_name"     , xsec_hist_name.c_str()     ); 
    printf("%-25s = %d\n"    , "verbose"            , verbose                    ); 
    printf("%-25s = %s\n"    , "suffix"             , suffix.c_str()             ); 
    printf("%-25s = %1.0f\n" , "mass_stop"          , mass_stop                  ); 
    printf("%-25s = %1.0f\n" , "mass_lsp"           , mass_lsp                   ); 
    printf("%-25s = %1.3f\n" , "unc_lumi"           , unc_lumi                   ); 
    printf("%-25s = %1.3f\n" , "unc_trig"           , unc_trig                   ); 
    printf("%-25s = %1.3f\n" , "unc_lept"           , unc_lept                   ); 

    // print the search regions
    printf("%-25s = ", "SR(s)");
    for (size_t i = 0; i != search_regions.size(); i++)
    {
        if (search_regions.at(i) != search_regions.back()) {cout << search_regions.at(i) << ", ";}
        else                                               {cout << search_regions.at(i) << endl;}
    }

    // get the input TChain 
    // -------------------------------------------------------------------------------------------------//
    TChain* chain_ptr = stop::GetSampleTChain(stop::GetSampleFromName(sample_name)); 
    rt::PrintFilesFromTChain(chain_ptr);
    TChain& chain = *chain_ptr;

    // analysis looper
    InterpLooper interp_looper
    (
        output_file_name,
        sample_name,
        analysis_type_name,
        xsec_file_path,
        xsec_hist_name,
        search_regions,
        lumi,
        mass_stop,
        mass_lsp,
        unc_lumi,
        unc_trig,
        unc_lept,
        suffix,
        verbose
    ); 
    interp_looper.ScanChain(chain, max_events);

    // cleanup
    // -------------------------------------------------------------------------------------------------//
    delete chain_ptr;

    // done
    return 0;
}
catch (std::exception& e)
{
    std::cerr << "[stop_interp_plots] Error: failed..." << std::endl;
    std::cerr << e.what() << std::endl;
    return 1;
}
