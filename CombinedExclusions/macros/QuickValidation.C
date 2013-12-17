#include "RootTools.h"
#include "LanguageTools.h"
#include "SignalRegion.h"
#include "Sample.h"
#include "TStyle.h"
#include "TCanvas.h"

void PrintValidation 
(
    const float mass_stop,
    const float mass_lsp,
    const int signal_region_num
)
{
    rt::TH1Container hc("plots/stop_test/t2tt_bdt_hists.root");
    hc.List();
    const stop::SignalRegion::value_type signal_region = stop::GetSignalRegionFromName(Form("sr%d", signal_region_num)); 
    const std::string sr_label = stop::GetSignalRegionInfo(signal_region).label; 

    const float xsec            = rt::GetBinContent1D(hc["h_xsec"                      ], mass_stop);
    const float ngen            = rt::GetBinContent2D(hc["h_ngen"                      ], mass_stop, mass_lsp);
    const float nevt            = rt::GetBinContent2D(hc["h_nevt_"    +sr_label        ], mass_stop, mass_lsp);
    const float num             = rt::GetBinContent2D(hc["h_num_"     +sr_label        ], mass_stop, mass_lsp);
    const float eff             = rt::GetBinContent2D(hc["h_eff_"     +sr_label        ], mass_stop, mass_lsp);
    const float eff_perc        = rt::GetBinContent2D(hc["h_eff_perc_"+sr_label        ], mass_stop, mass_lsp);
    const float num_scaled      = rt::GetBinContent2D(hc["h_num_scaled_"     +sr_label ], mass_stop, mass_lsp);
    const float den_scaled      = rt::GetBinContent2D(hc["h_den"                       ], mass_stop, mass_lsp);
    const float eff_scaled      = rt::GetBinContent2D(hc["h_eff_scaled_"     +sr_label ], mass_stop, mass_lsp);
    const float eff_scaled_perc = rt::GetBinContent2D(hc["h_eff_scaled_perc_"+sr_label ], mass_stop, mass_lsp);
    const float err_jes         = rt::GetBinContent2D(hc["h_err_jes_"        +sr_label ], mass_stop, mass_lsp);
    const float num_jesup       = rt::GetBinContent2D(hc["h_num_jesup_"      +sr_label ], mass_stop, mass_lsp);
    const float num_jesdn       = rt::GetBinContent2D(hc["h_num_jesdn_"      +sr_label ], mass_stop, mass_lsp);
    const float err_btag        = rt::GetBinContent2D(hc["h_err_btag_"       +sr_label ], mass_stop, mass_lsp);
    const float num_btagup      = rt::GetBinContent2D(hc["h_num_btagup_"     +sr_label ], mass_stop, mass_lsp);
    const float num_btagdn      = rt::GetBinContent2D(hc["h_num_btagdn_"     +sr_label ], mass_stop, mass_lsp);
    const float err_noisr       = rt::GetBinContent2D(hc["h_err_noisr_"      +sr_label ], mass_stop, mass_lsp);
    const float num_noisr       = rt::GetBinContent2D(hc["h_num_noisr_"      +sr_label ], mass_stop, mass_lsp);
                                               
    cout << "\nQuick Validation for Search Region " << signal_region_num <<     endl ;
    cout << Form("mass point           = m_stop = %1.0f, m_lsp = %1.0f", mass_stop, mass_lsp) << endl;
    cout << Form("xsec                 = %1.4f", xsec)                                        << endl;
    cout << Form("efficiency           = %1.4f", eff*100.0)                                   << endl;
    cout << Form("num_generated        = %1.0f", ngen)                                        << endl;
    cout << Form("nevents              = %1.0f", nevt)                                        << endl;
    cout << Form("num                  = %1.0f", num)                                         << endl;
    cout << Form("efficiency scaled    = %1.4f", eff_scaled*100.0)                            << endl;
    cout << Form("num_generated scaled = %1.0f", den_scaled)                                  << endl;
    cout << Form("num scaled           = %1.0f", num_scaled)                                  << endl;
    cout << Form("num JES+             = %1.0f", num_jesup)                                   << endl;
    cout << Form("num JES-             = %1.0f", num_jesdn)                                   << endl;
    cout << Form("Uncertainty JES+/-   = %1.5f", err_jes)                                     << endl;
    cout << Form("num Btag+            = %1.0f", num_btagup)                                  << endl;
    cout << Form("num Btag-            = %1.0f", num_btagdn)                                  << endl;
    cout << Form("Uncertainty Btag+/-  = %1.5f", err_btag)                                    << endl;
    cout << Form("num ISR              = %1.0f", num_noisr)                                   << endl;
    cout << Form("Uncertainty ISR      = %1.5f", err_noisr)                                   << endl;
}

void QuickValidation()
{
    PrintValidation(300, 50, 1);
/*     PrintValidation(300, 50, 2); */
/*     PrintValidation(300, 50, 3); */
/*     PrintValidation(300, 50, 4); */
/*     PrintValidation(300, 50, 5); */
/*     PrintValidation(300, 50, 6); */
}
