#include <iostream>
#include <fstream>
#include <string>
#include <limits>

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

void CreateExpectedExclusionOverlay()
{
    rt::TH1Container hc_an("/Users/rwk7t/temp/from_ben/exclusion2012_postLHCP_T2bwFixed/rootfiles/T2tt_combinePlots_BDT.root");
    rt::TH1Container hc_ls("plots/limits/t2tt/lands/t2tt_bdt_limit_hists.root");
    rt::TH1Container hc_cb("plots/limits/t2tt/combine/t2tt_bdt_limit_hists.root");
    /*     hc_ls.List(); */

    TH1& h_an       = *dynamic_cast<TH1*>(hc_an["hexcl_exp"         ]->Clone());
    TH1& h_ls       = *dynamic_cast<TH1*>(hc_ls["h_excl_exp_best"   ]->Clone());
    TH1& h_cb       = *dynamic_cast<TH1*>(hc_cb["h_excl_exp_best"   ]->Clone());
    TH1& h_xsec_exp = *dynamic_cast<TH1*>(hc_ls["h_xsec_exp_ul_best"]->Clone());
    h_xsec_exp.SetStats(false);
    h_xsec_exp.GetYaxis()->SetRangeUser(0  , 425);
    h_xsec_exp.GetXaxis()->SetRangeUser(100, 800);
    h_xsec_exp.SetContour(1024);

    // curves
    TGraph* const g_an = GetContourTGraph(h_an, 0.0); g_an->SetLineWidth(4); g_an->SetLineStyle(1); g_an->SetLineColor(kBlack); 
    TGraph* const g_ls = GetContourTGraph(h_ls, 0.0); g_ls->SetLineWidth(4); g_ls->SetLineStyle(2); g_ls->SetLineColor(kRed); 
    TGraph* const g_cb = GetContourTGraph(h_cb, 0.0); g_cb->SetLineWidth(4); g_cb->SetLineStyle(3); g_cb->SetLineColor(kGreen+2); 

    // legend
    float stat_y1 = 1.0 - gStyle->GetPadTopMargin() - 0.01;
    float stat_y2 = 0.70;
    float stat_x1 = gStyle->GetPadLeftMargin() + 0.02;
    float stat_x2 = 0.5;
    TLegend* const leg = new TLegend(stat_x1, stat_y1, stat_x2, stat_y2);
    leg->AddEntry(g_an, "Analysis Note", "L");
    leg->AddEntry(g_ls, "LandS"        , "L");
    leg->AddEntry(g_cb, "Combine"      , "L");
    leg->SetFillColor(0);  // 0 makes it the background clear on the pad
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);

    // Draw the hist and curve
    gStyle->SetPadRightMargin(0.15);
    gStyle->SetPaintTextFormat("1.1f");
    TCanvas* const c1 = new TCanvas("c1", "c1", 800, 600);
    h_xsec_exp.Draw("colz");
    g_an->Draw("same");
    g_ls->Draw("same");
    g_cb->Draw("same");
    leg->Draw();


    c1->Print("plots/limits/t2tt/t2tt_bdt_exp_limit_summary.eps");
}

