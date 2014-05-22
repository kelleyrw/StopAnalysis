#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <utility>

#include "RootTools.h"
#include "LanguageTools.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TObjArray.h"
#include "TList.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TColor.h"
#include "TPaletteAxis.h"

TGraph* GetContourTGraph
(
    TH1& hist, 
    const Color_t color,
    const double level = 1.0
)
{
    using namespace std;
    TCanvas c("c_GetContourTGraph_temp", "c_GetContourTGraph_temp");
    const float min         = hist.GetMinimum();
    const float max         = hist.GetMaximum();
    const double contours[] = {min, level, max};
    hist.SetContour(2, contours);
    hist.Draw("CONT Z LIST");
    c.Update();

    TGraph* curve = NULL;
    TObjArray* const array = dynamic_cast<TObjArray*>(gROOT->GetListOfSpecials()->FindObject("contours"));
    if (array == NULL)
    {
        curve = new TGraph();
    }
    else
    {
        TList * const list = dynamic_cast<TList*>(array->First());
        if (list->First())
        {
            curve = dynamic_cast<TGraph*>(list->First()->Clone()); 
        }
        else
        {
            curve = new TGraph();
        }
    }

    // reset the contours
    hist.SetContour(static_cast<int>(max-min)+1);
    curve->SetLineWidth(3);
    curve->SetLineStyle(1);
    curve->SetLineColor(color);
    return curve;
}

std::pair<TH2* const, TH2* const> SplitHist(TH2& hist)
{
    
    TH2* const h1 = dynamic_cast<TH2*>(hist.Clone(Form("%s_1", hist.GetName()))); 
    TH2* const h2 = dynamic_cast<TH2*>(hist.Clone(Form("%s_2", hist.GetName())));
    h1->SetTitle(h1->GetName());
    h2->SetTitle(h2->GetName());

    // reset points
    static const double m_top = 173; // GeV
    const unsigned int nbinsx = h1->GetNbinsX()+1;
    const unsigned int nbinsy = h1->GetNbinsY()+1;
    for (unsigned int xbin = 1; xbin < nbinsx; xbin++)
    {
        for (unsigned int ybin = 1; ybin < nbinsy; ybin++)
        {
            const float m_stop = h1->GetXaxis()->GetBinCenter(xbin);
            const float m_lsp  = h1->GetYaxis()->GetBinCenter(ybin);

            //cout << m_lsp << ", " << m_stop << "\t" << m_stop - m_top << endl;

            // zero out bins below line
            if (m_lsp < (m_stop - m_top + 25))
            {
                h1->SetBinContent(xbin, ybin, 0);
                h1->SetBinError  (xbin, ybin, 0);
            }

            // zero out bins below line
            if (m_lsp > (m_stop - m_top - 25))
            {
                h2->SetBinContent(xbin, ybin, 0);
                h2->SetBinError  (xbin, ybin, 0);
            }
        }
    }

    return std::make_pair(h1, h2);
}

void SetStyleColz(TH1& h_xsec)
{
    // set z axis
    h_xsec.GetZaxis()->SetLabelFont(42);
    h_xsec.GetZaxis()->SetTitleFont(42);
    h_xsec.GetZaxis()->SetLabelSize(0.035);
    h_xsec.GetZaxis()->SetTitleSize(0.035);

    // define the palette for z axis
    static const int NRGBs     = 5;
    static const int NCont     = 255;
    static double stops[NRGBs] = {0.00 , 0.34 , 0.61 , 0.84 , 1.00};
    static double red  [NRGBs] = {0.50 , 0.50 , 1.00 , 1.00 , 1.00};
    static double green[NRGBs] = {0.50 , 1.00 , 1.00 , 0.60 , 0.50};
    static double blue [NRGBs] = {1.00 , 1.00 , 0.50 , 0.40 , 0.50};
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);

    h_xsec.Draw("colz");
    gPad->Update();
    gPad->SetLogz(true);
    gStyle->SetPadRightMargin(0.15);
    gStyle->SetPaintTextFormat("1.0f");
    TPaletteAxis* const palette = dynamic_cast<TPaletteAxis*>(h_xsec.GetListOfFunctions()->FindObject("palette"));
    palette->SetLabelFont(42);
    palette->SetLabelSize(0.035);
}

void CreateExpectedExclusionOverlay
(
    TH2& h_excl_exp, 
    TH2& h_excl_obs, 
    TH2& h_xsec_ul,
    const std::string file_name,
    const std::string suffix
)
{
    std::pair<TH2* const, TH2* const> h_excl_exp_split = SplitHist(h_excl_exp);
    std::pair<TH2* const, TH2* const> h_excl_obs_split = SplitHist(h_excl_obs);

    h_xsec_ul.SetStats(false);
    h_xsec_ul.GetYaxis()->SetRangeUser(0   , 450);
    h_xsec_ul.GetXaxis()->SetRangeUser(100 , 800);
    h_xsec_ul.GetZaxis()->SetRangeUser(1e-3, 1e2);
    h_xsec_ul.SetContour(1024);

    // curves
    TGraph* const g_excl_exp_1 = GetContourTGraph(*h_excl_exp_split.first , kRed  , 0.0);
    TGraph* const g_excl_exp_2 = GetContourTGraph(*h_excl_exp_split.second, kRed  , 0.0);
    TGraph* const g_excl_obs_1 = GetContourTGraph(*h_excl_obs_split.first , kBlack, 0.0);
    TGraph* const g_excl_obs_2 = GetContourTGraph(*h_excl_obs_split.second, kBlack, 0.0);

    // legend
    float stat_y1 = 1.0 - gStyle->GetPadTopMargin() - 0.01;
    float stat_y2 = 0.70;
    float stat_x1 = gStyle->GetPadLeftMargin() + 0.02;
    float stat_x2 = 0.6;
    TLegend* const leg = new TLegend(stat_x1, stat_y1, stat_x2, stat_y2);
    leg->AddEntry(g_excl_exp_1, "Expected", "L");
    leg->AddEntry(g_excl_obs_1, "Observed", "L");
    leg->SetFillColor(0);  // 0 makes it the background clear on the pad
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);

    // Draw the hist and curve
    TCanvas* const c1 = new TCanvas("c1", "c1", 600, 600);
    h_xsec_ul.GetZaxis()->SetTitle("#sigma upper limit (pb)");
    SetStyleColz(h_xsec_ul);
    gPad->Update();
    h_xsec_ul.Draw("colz");
    if (g_excl_exp_1->GetN()>0) g_excl_exp_1->Draw("same");
    if (g_excl_exp_2->GetN()>0) g_excl_exp_2->Draw("same");
    if (g_excl_obs_1->GetN()>0) g_excl_obs_1->Draw("same");
    if (g_excl_obs_2->GetN()>0) g_excl_obs_2->Draw("same");
    leg->Draw();

    // Draw the hist and curve
    lt::mkdir(lt::dirname(file_name), /*force=*/true);
    c1->Print(Form("%s.%s", file_name.c_str(), suffix.c_str()));
}

void CreateCombinedExclusionOverlays()
{
    const std::string suffix = "eps";

/*     rt::TH1Container hc_sl("plots/limits/lep1_razor_combine/asymptotic/t2tt/t2tt_singlelep_limit_hists.root"); */
/*     TH2& h_excl_obs_sl    = *dynamic_cast<TH2F*>(hc_sl["h_excl_obs"   ]->Clone("h_excl_obs_sl"   )); */
/*     TH2& h_excl_exp_sl    = *dynamic_cast<TH2F*>(hc_sl["h_excl_exp"   ]->Clone("h_excl_exp_sl"   )); */
/*     TH2& h_xsec_exp_ul_sl = *dynamic_cast<TH2F*>(hc_sl["h_xsec_exp_ul"]->Clone("h_xsec_exp_ul_sl")); */
/*     CreateExpectedExclusionOverlay(h_excl_exp_sl, h_excl_obs_sl, h_xsec_exp_ul_sl, "plots/limits/lep1_razor_combine/asymptotic/t2tt/singlelep/p_obs_excl_curve", suffix); */
/*  */
/*     rt::TH1Container hc_rz("plots/limits/lep1_razor_combine/asymptotic/t2tt/t2tt_razor_limit_hists.root"); */
/*     TH2& h_excl_obs_rz    = *dynamic_cast<TH2F*>(hc_rz["h_excl_obs"   ]->Clone("h_excl_obs_rz"   )); */
/*     TH2& h_excl_exp_rz    = *dynamic_cast<TH2F*>(hc_rz["h_excl_exp"   ]->Clone("h_excl_exp_rz"   )); */
/*     TH2& h_xsec_exp_ul_rz = *dynamic_cast<TH2F*>(hc_rz["h_xsec_exp_ul"]->Clone("h_xsec_exp_ul_rz")); */
/*     CreateExpectedExclusionOverlay(h_excl_exp_rz, h_excl_obs_rz, h_xsec_exp_ul_rz, "plots/limits/lep1_razor_combine/asymptotic/t2tt/razor/p_obs_excl_curve", suffix); */
/*  */
/*     rt::TH1Container hc_cb("plots/limits/lep1_razor_combine/asymptotic/t2tt/t2tt_combined_limit_hists.root"); */
/*     TH2& h_excl_obs_cb    = *dynamic_cast<TH2F*>(hc_cb["h_excl_obs"   ]->Clone("h_excl_obs_cb"   )); */
/*     TH2& h_excl_exp_cb    = *dynamic_cast<TH2F*>(hc_cb["h_excl_exp"   ]->Clone("h_excl_exp_cb"   )); */
/*     TH2& h_xsec_exp_ul_cb = *dynamic_cast<TH2F*>(hc_cb["h_xsec_exp_ul"]->Clone("h_xsec_exp_ul_cb")); */
/*     CreateExpectedExclusionOverlay(h_excl_exp_cb, h_excl_obs_cb, h_xsec_exp_ul_cb, "plots/limits/lep1_razor_combine/asymptotic/t2tt/combined/p_obs_excl_curve", suffix); */
/*  */
/*     rt::TH1Container hc_sl("plots/limits/lep1_razor_combine/hybridnew/t2tt/t2tt_singlelep_limit_hists.root"); */
/*     TH2& h_excl_obs_sl    = *dynamic_cast<TH2F*>(hc_sl["h_excl_obs"   ]->Clone("h_excl_obs_sl"   )); */
/*     TH2& h_excl_exp_sl    = *dynamic_cast<TH2F*>(hc_sl["h_excl_exp"   ]->Clone("h_excl_exp_sl"   )); */
/*     TH2& h_xsec_exp_ul_sl = *dynamic_cast<TH2F*>(hc_sl["h_xsec_exp_ul"]->Clone("h_xsec_exp_ul_sl")); */
/*     CreateExpectedExclusionOverlay(h_excl_exp_sl, h_excl_obs_sl, h_xsec_exp_ul_sl, "plots/limits/lep1_razor_combine/hybridnew/t2tt/singlelep/p_obs_excl_curve", suffix); */
/*  */
    // asymptotic new batch
/*     rt::TH1Container hc_sl("plots/limits/lep1_razor_combine/asymptotic_new/t2tt/t2tt_singlelep_limit_hists.root"); */
/*     TH2& h_excl_obs_sl    = *dynamic_cast<TH2F*>(hc_sl["h_excl_obs"   ]->Clone("h_excl_obs_sl"   )); */
/*     TH2& h_excl_exp_sl    = *dynamic_cast<TH2F*>(hc_sl["h_excl_exp"   ]->Clone("h_excl_exp_sl"   )); */
/*     TH2& h_xsec_exp_ul_sl = *dynamic_cast<TH2F*>(hc_sl["h_xsec_exp_ul"]->Clone("h_xsec_exp_ul_sl")); */
/*     CreateExpectedExclusionOverlay(h_excl_exp_sl, h_excl_obs_sl, h_xsec_exp_ul_sl, "plots/limits/lep1_razor_combine/asymptotic_new/t2tt/singlelep/p_obs_excl_curve", suffix); */
/*  */
/*     rt::TH1Container hc_rz("plots/limits/lep1_razor_combine/asymptotic_new/t2tt/t2tt_razor_limit_hists.root"); */
/*     TH2& h_excl_obs_rz    = *dynamic_cast<TH2F*>(hc_rz["h_excl_obs"   ]->Clone("h_excl_obs_rz"   )); */
/*     TH2& h_excl_exp_rz    = *dynamic_cast<TH2F*>(hc_rz["h_excl_exp"   ]->Clone("h_excl_exp_rz"   )); */
/*     TH2& h_xsec_exp_ul_rz = *dynamic_cast<TH2F*>(hc_rz["h_xsec_exp_ul"]->Clone("h_xsec_exp_ul_rz")); */
/*     CreateExpectedExclusionOverlay(h_excl_exp_rz, h_excl_obs_rz, h_xsec_exp_ul_rz, "plots/limits/lep1_razor_combine/asymptotic_new/t2tt/razor/p_obs_excl_curve", suffix); */
/*  */
/*     rt::TH1Container hc_cb("plots/limits/lep1_razor_combine/asymptotic_new/t2tt/t2tt_combined_limit_hists.root"); */
/*     TH2& h_excl_obs_cb    = *dynamic_cast<TH2F*>(hc_cb["h_excl_obs"   ]->Clone("h_excl_obs_cb"   )); */
/*     TH2& h_excl_exp_cb    = *dynamic_cast<TH2F*>(hc_cb["h_excl_exp"   ]->Clone("h_excl_exp_cb"   )); */
/*     TH2& h_xsec_exp_ul_cb = *dynamic_cast<TH2F*>(hc_cb["h_xsec_exp_ul"]->Clone("h_xsec_exp_ul_cb")); */
/*     CreateExpectedExclusionOverlay(h_excl_exp_cb, h_excl_obs_cb, h_xsec_exp_ul_cb, "plots/limits/lep1_razor_combine/asymptotic_new/t2tt/combined/p_obs_excl_curve", suffix); */
    
    // hybrid 
    rt::TH1Container hc_sl("plots/limits/lep1_razor_combine/hybrid/t2tt/t2tt_singlelep_limit_hists.root");
    TH2& h_excl_obs_sl    = *dynamic_cast<TH2F*>(hc_sl["h_excl_obs"   ]->Clone("h_excl_obs_sl"   ));
    TH2& h_excl_exp_sl    = *dynamic_cast<TH2F*>(hc_sl["h_excl_exp"   ]->Clone("h_excl_exp_sl"   ));
    TH2& h_xsec_exp_ul_sl = *dynamic_cast<TH2F*>(hc_sl["h_xsec_exp_ul"]->Clone("h_xsec_exp_ul_sl"));
    CreateExpectedExclusionOverlay(h_excl_exp_sl, h_excl_obs_sl, h_xsec_exp_ul_sl, "plots/limits/lep1_razor_combine/hybrid/t2tt/singlelep/p_obs_excl_curve", suffix);

    rt::TH1Container hc_rz("plots/limits/lep1_razor_combine/hybrid/t2tt/t2tt_razor_limit_hists.root");
    TH2& h_excl_obs_rz    = *dynamic_cast<TH2F*>(hc_rz["h_excl_obs"   ]->Clone("h_excl_obs_rz"   ));
    TH2& h_excl_exp_rz    = *dynamic_cast<TH2F*>(hc_rz["h_excl_exp"   ]->Clone("h_excl_exp_rz"   ));
    TH2& h_xsec_exp_ul_rz = *dynamic_cast<TH2F*>(hc_rz["h_xsec_exp_ul"]->Clone("h_xsec_exp_ul_rz"));
    CreateExpectedExclusionOverlay(h_excl_exp_rz, h_excl_obs_rz, h_xsec_exp_ul_rz, "plots/limits/lep1_razor_combine/hybrid/t2tt/razor/p_obs_excl_curve", suffix);

    rt::TH1Container hc_cb("plots/limits/lep1_razor_combine/hybrid/t2tt/t2tt_combined_limit_hists.root");
    TH2& h_excl_obs_cb    = *dynamic_cast<TH2F*>(hc_cb["h_excl_obs"   ]->Clone("h_excl_obs_cb"   ));
    TH2& h_excl_exp_cb    = *dynamic_cast<TH2F*>(hc_cb["h_excl_exp"   ]->Clone("h_excl_exp_cb"   ));
    TH2& h_xsec_exp_ul_cb = *dynamic_cast<TH2F*>(hc_cb["h_xsec_exp_ul"]->Clone("h_xsec_exp_ul_cb"));
    CreateExpectedExclusionOverlay(h_excl_exp_cb, h_excl_obs_cb, h_xsec_exp_ul_cb, "plots/limits/lep1_razor_combine/hybrid/t2tt/combined/p_obs_excl_curve", suffix);
}

