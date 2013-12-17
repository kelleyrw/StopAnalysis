#include "RootTools.h"
#include "LanguageTools.h"
#include "SignalRegion.h"
#include "Sample.h"
#include "TStyle.h"
#include "TCanvas.h"

void PrintPlots
(
    const std::string& plot_name,
    const rt::TH1Container& hc,
    const std::string& path,
    const std::string& suffix,
    const std::string& draw_option,
    const std::string& paint_text_option = "1.0f",
    const float zmin = 1.0f,
    const float zmax = -1.0f
)
{
    TCanvas c1("c1", "c1", 1600, 1200);
    gStyle->SetPadRightMargin(0.10);
    if (lt::string_contains(draw_option, "colz"))
    {
        gStyle->SetPadRightMargin(0.15);
    }
    {
        gStyle->SetPaintTextFormat(paint_text_option.c_str());
    }
    if (zmax > zmin)
    {
        hc[plot_name]->GetZaxis()->SetRangeUser(zmin, zmax);
/*         hc2[plot_name]->GetZaxis()->SetRangeUser(zmin, zmax); */
    }
    hc[plot_name]->Draw(draw_option.c_str()); c1.Print((path + "/" + plot_name + "." + suffix).c_str());
}

void PrintFormattedPlots()
{
    rt::TH1Container hc("plots/stop_test/t2tt_bdt_hists.root");
    const std::string suffix      = "png";
    const std::string path        = "plots/stop_test/" + suffix;
    const std::string draw_option = "text";
    const unsigned int sr_nums[]  = {0, 1, 2, 3, 4, 5, 6};

    gStyle->SetCanvasDefX(1600);
    gStyle->SetCanvasDefY(1200);

    // no stat boxes
    hc.SetStats(false);


    PrintPlots("h_ngen", hc, path, suffix, draw_option, "1.0f");
    for (size_t i = 0; i != 7; i++)
    {
        const stop::SignalRegion::value_type signal_region = stop::GetSignalRegionFromName(Form("sr%d", sr_nums[i])); 
        const std::string sr_label = stop::GetSignalRegionInfo(signal_region).label; 

        PrintPlots("h_nevt_"    +sr_label, hc, path, suffix, draw_option, "1.0f");
        PrintPlots("h_eff_"     +sr_label, hc, path, suffix, draw_option, "1.2f");
        PrintPlots("h_eff_perc_"+sr_label, hc, path, suffix, draw_option, "1.2f");
    }
}
