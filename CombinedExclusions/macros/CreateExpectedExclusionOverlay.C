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

TGraph* GetContourTGraph(TH1& hist, const double level = 1.0)
{
    TCanvas c("c_GetContourTGraph_temp", "c_GetContourTGraph_temp");
    const float min   = hist.GetMinimum();
    const float max   = hist.GetMaximum();
    double contours[] = {min, level, max};
    hist.SetContour(2, contours);
    hist.Draw("CONT Z LIST");
    c.Update();

    TObjArray* array = dynamic_cast<TObjArray*>(gROOT->GetListOfSpecials()->FindObject("contours"));
    TList *list      = dynamic_cast<TList*>(array->First());
    TGraph* curve    = dynamic_cast<TGraph*>(list->First()->Clone()); 

    // reset the contours
    hist.SetContour(static_cast<int>(max-min)+1);
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
        static const int NRGBs = 5;
        static const int NCont = 255;
        static double stops[NRGBs] = {0.00  , 0.34 , 0.61 , 0.84 , 1.00};
        static double red  [NRGBs] = {0.50  , 0.50 , 1.00 , 1.00 , 1.00};
        static double green[NRGBs] = { 0.50 , 1.00 , 1.00 , 0.60 , 0.50};
        static double blue [NRGBs] = {1.00  , 1.00 , 0.50 , 0.40 , 0.50};
        TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
        gStyle->SetNumberContours(NCont);
        
        h_xsec.Draw("colz");
        gPad->Update();
        gStyle->SetPadRightMargin(0.15);
        gStyle->SetPaintTextFormat("1.0f");
        TPaletteAxis* const palette = dynamic_cast<TPaletteAxis*>(h_xsec.GetListOfFunctions()->FindObject("palette"));
/*         palette->SetX1NDC(1.-0.18); */
/*         palette->SetY1NDC(0.14); */
/*         palette->SetX2NDC(1.-0.13); */
/*         palette->SetY2NDC(1.-0.08); */
        palette->SetLabelFont(42);
        palette->SetLabelSize(0.035);
}

void CreateExpectedExclusionOverlay()
{
    rt::TH1Container hc_an("from_ben/exclusion2012_postLHCP_T2bwFixed/rootfiles/T2tt_combinePlots_BDT.root");
    rt::TH1Container hc_ls("plots/limits/t2tt/lands/t2tt_bdt_limit_hists.root");
    rt::TH1Container hc_cb("plots/limits/t2tt/combine/t2tt_bdt_limit_hists.root");
    /*     hc_ls.List(); */

    TH2& h_an       = *dynamic_cast<TH2*>(hc_an["hexcl_exp"         ]->Clone("h_an"      ));
    TH2& h_ls       = *dynamic_cast<TH2*>(hc_ls["h_excl_exp_best"   ]->Clone("h_ls"      ));
    TH2& h_cb       = *dynamic_cast<TH2*>(hc_cb["h_excl_exp_best"   ]->Clone("h_cb"      ));
    TH2& h_xsec_exp = *dynamic_cast<TH2*>(hc_ls["h_xsec_exp_ul_best"]->Clone("h_xsec_exp"));
    std::pair<TH2* const, TH2* const> h_an_split = SplitHist(h_an);
    std::pair<TH2* const, TH2* const> h_ls_split = SplitHist(h_ls);
    std::pair<TH2* const, TH2* const> h_cb_split = SplitHist(h_cb);

    h_xsec_exp.SetStats(false);
    h_xsec_exp.GetYaxis()->SetRangeUser(0   , 425);
    h_xsec_exp.GetXaxis()->SetRangeUser(100 , 800);
    h_xsec_exp.GetZaxis()->SetRangeUser(1e-3, 1e2);
    h_xsec_exp.SetContour(1024);

    // curves
    TGraph* const g_an_1 = GetContourTGraph(*h_an_split.first  , 0.0); g_an_1->SetLineWidth(4); g_an_1->SetLineStyle(1); g_an_1->SetLineColor(kBlack  ); 
    TGraph* const g_an_2 = GetContourTGraph(*h_an_split.second , 0.0); g_an_2->SetLineWidth(4); g_an_2->SetLineStyle(1); g_an_2->SetLineColor(kBlack  ); 
    TGraph* const g_ls_1 = GetContourTGraph(*h_ls_split.first  , 0.0); g_ls_1->SetLineWidth(4); g_ls_1->SetLineStyle(2); g_ls_1->SetLineColor(kRed    ); 
    TGraph* const g_ls_2 = GetContourTGraph(*h_ls_split.second , 0.0); g_ls_2->SetLineWidth(4); g_ls_2->SetLineStyle(2); g_ls_2->SetLineColor(kRed    ); 
    TGraph* const g_cb_1 = GetContourTGraph(*h_cb_split.first  , 0.0); g_cb_1->SetLineWidth(4); g_cb_1->SetLineStyle(3); g_cb_1->SetLineColor(kGreen+2); 
    TGraph* const g_cb_2 = GetContourTGraph(*h_cb_split.second , 0.0); g_cb_2->SetLineWidth(4); g_cb_2->SetLineStyle(3); g_cb_2->SetLineColor(kGreen+2); 

    // legend
    float stat_y1 = 1.0 - gStyle->GetPadTopMargin() - 0.01;
    float stat_y2 = 0.70;
    float stat_x1 = gStyle->GetPadLeftMargin() + 0.02;
    float stat_x2 = 0.5;
    TLegend* const leg = new TLegend(stat_x1, stat_y1, stat_x2, stat_y2);
    leg->AddEntry(g_an_1, "Analysis Note", "L");
    leg->AddEntry(g_ls_1, "LandS"        , "L");
    leg->AddEntry(g_cb_1, "Combine"      , "L");
    leg->SetFillColor(0);  // 0 makes it the background clear on the pad
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);

    // Draw the hist and curve
    TCanvas* const c1 = new TCanvas("c1", "c1", 800, 600);
    c1->SetLogz();
    h_xsec_exp.GetZaxis()->SetTitle("#sigma upper limit (pb)");
    SetStyleColz(h_xsec_exp);
    h_xsec_exp.Draw("colz");
    g_an_1->Draw("same");
    g_ls_1->Draw("same");
    g_cb_1->Draw("same");
    g_an_2->Draw("same");
    g_ls_2->Draw("same");
    g_cb_2->Draw("same");
    leg->Draw();

    c1->Print("plots/limits/t2tt/t2tt_bdt_exp_limit_summary.eps");
}

