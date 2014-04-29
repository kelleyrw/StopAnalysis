#include "StopAnalysis/CombinedExclusions/interface/PrintFormattedXSecHist.h"
#include "StopAnalysis/CombinedExclusions/interface/SignalRegion.h"
#include "StopAnalysis/CombinedExclusions/interface/Sample.h"
#include "AnalysisTools/RootTools/interface/RootTools.h"
#include "AnalysisTools/LanguageTools/interface/LanguageTools.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TColor.h"
// #include "TPaletteAxis.h"

namespace stop
{
    void PrintFormattedXSecHist
    (
        TH2F& hist,
        const std::string& plot_name,
        const std::string& path,
        const std::string& suffix,
        const std::string& draw_option,
        const std::string& paint_text_option,
        const float zmin,
        const float zmax
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
            static const int NRGBs     = 5;
            static const int NCont     = 255;
            static double stops[NRGBs] = {0.00 , 0.34 , 0.61 , 0.84 , 1.00};
            static double red  [NRGBs] = {0.50 , 0.50 , 1.00 , 1.00 , 1.00};
            static double green[NRGBs] = {0.50 , 1.00 , 1.00 , 0.60 , 0.50};
            static double blue [NRGBs] = {1.00 , 1.00 , 0.50 , 0.40 , 0.50};
            TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
            gStyle->SetNumberContours(NCont);

            hist.Draw("colz");
            gPad->Update();
            gPad->SetLogz(true);
            gStyle->SetPadRightMargin(0.15);
            gStyle->SetPaintTextFormat("1.0f");
//             TPaletteAxis* const palette = dynamic_cast<TPaletteAxis*>(hist.GetListOfFunctions()->FindObject("palette"));
//             palette->SetLabelFont(42);
//             palette->SetLabelSize(0.035);
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
        lt::mkdir(path, /*force=*/true);
        hist.Draw(draw_option.c_str());
        c1.Print(file_name.c_str());
    }

} // namspace stop

