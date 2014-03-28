#include "RootTools.h"
#include "LanguageTools.h"
#include "SignalRegion.h"
#include "Sample.h"
#include "TStyle.h"
#include "TCanvas.h"

void PrintPlots
(
    const std::string& plot_name,
    const rt::TH1Container& hist,
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
        // set z axis
        hist.GetZaxis()->SetLabelFont(42);
        hist.GetZaxis()->SetTitleFont(42);
        hist.GetZaxis()->SetLabelSize(0.035);
        hist.GetZaxis()->SetTitleSize(0.035);

        // define the palette for z axis
        static const int NRGBs = 5;
        static const int NCont = 255;
        static double stops[NRGBs] = {0.00  , 0.34 , 0.61 , 0.84 , 1.00};
        static double red  [NRGBs] = {0.50  , 0.50 , 1.00 , 1.00 , 1.00};
        static double green[NRGBs] = { 0.50 , 1.00 , 1.00 , 0.60 , 0.50};
        static double blue [NRGBs] = {1.00  , 1.00 , 0.50 , 0.40 , 0.50};
        TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
        gStyle->SetNumberContours(NCont);
        
        hist.Draw("colz");
        gPad->Update();
        gStyle->SetPadRightMargin(0.15);
        gStyle->SetPaintTextFormat("1.0f");
        TPaletteAxis* const palette = dynamic_cast<TPaletteAxis*>(hist.GetListOfFunctions()->FindObject("palette"));
        palette->SetLabelFont(42);
        palette->SetLabelSize(0.035);
        gStyle->SetPadRightMargin(0.15);
    }
    {
        gStyle->SetPaintTextFormat(paint_text_option.c_str());
    }
    if (zmax > zmin)
    {
        hist.GetZaxis()->SetRangeUser(zmin, zmax);
    }
    const std::string file_name = Form("%s/%s.%s", path.c_str(), plot_name.c_str(), suffix.c_str());
    hist.Draw(draw_option.c_str());
    c1.Print(file_name.c_str());
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
