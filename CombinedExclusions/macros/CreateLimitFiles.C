#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "RootTools.h"
#include "LanguageTools.h"
#include "Sample.h"
#include "SignalRegion.h"

using namespace std;

struct LimitInfo
{
    float sparm0;
    float sparm1;
    double xsec;
    double xsec_err;
    double obs;
    double obs_err;
    double exp;
    double exp_err;
    double exp_1sigma_up;
    double exp_1sigma_dn;
    double exp_2sigma_up;
    double exp_2sigma_dn;
};

// sort by sparm0 and then sparm1
bool operator < (const LimitInfo& lhs, const LimitInfo& rhs)
{
    if (lhs.sparm0 < rhs.sparm0) {return true; }
    if (lhs.sparm0 > rhs.sparm0) {return false;}
    if (lhs.sparm1 < rhs.sparm1) {return true; }
    else {return false;}
}

ostream& operator << (ostream& os, const LimitInfo& limit_info)
{
    os << Form("%1.0f\t%1.0f\t%1.6f\t%1.6f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f",
        limit_info.sparm0,
        limit_info.sparm1,
        limit_info.xsec,
        limit_info.xsec_err,
        limit_info.obs,
        limit_info.obs_err,
        limit_info.exp,
        limit_info.exp_err,
        limit_info.exp_1sigma_up,
        limit_info.exp_1sigma_dn,
        limit_info.exp_2sigma_up,
        limit_info.exp_2sigma_dn
    );
    return os;
}

std::istream& operator >> (std::istream& in, LimitInfo& limit_info)
{
    in >> limit_info.sparm0;
    in >> limit_info.sparm1;
    in >> limit_info.xsec;
    in >> limit_info.xsec_err;
    in >> limit_info.obs;
    in >> limit_info.obs_err;
    in >> limit_info.exp;
    in >> limit_info.exp_err;
    in >> limit_info.exp_1sigma_up;
    in >> limit_info.exp_1sigma_dn;
    in >> limit_info.exp_2sigma_up;
    in >> limit_info.exp_2sigma_dn;
    return in;
};

LimitInfo CreateLimitInfo(const TH1& h_xsec, const std::string& band_file_name)
{
    const std::vector<std::string> split = lt::string_split(band_file_name, "_");
    LimitInfo limit_info;
    limit_info.sparm0   = lt::string_to_double(split.at(2)); 
    limit_info.sparm1   = lt::string_to_double(split.at(3)); 
    limit_info.xsec     = rt::GetBinContent1D(&h_xsec, limit_info.sparm0);
    limit_info.xsec_err = rt::GetBinError1D(&h_xsec, limit_info.sparm0);

    TChain chain("T");
    chain.Add(band_file_name.c_str());
    chain.SetBranchAddress("limit"     , &limit_info.obs           ); 
    chain.SetBranchAddress("limitErr"  , &limit_info.obs_err       ); 
    chain.SetBranchAddress("rmedian"   , &limit_info.exp           ); 
    chain.SetBranchAddress("rmedianErr", &limit_info.exp_err       ); 
    chain.SetBranchAddress("rp1s"      , &limit_info.exp_1sigma_up ); 
    chain.SetBranchAddress("rm1s"      , &limit_info.exp_1sigma_dn ); 
    chain.SetBranchAddress("rp2s"      , &limit_info.exp_2sigma_up ); 
    chain.SetBranchAddress("rm2s"      , &limit_info.exp_2sigma_dn ); 
    chain.GetEntry(0);
    return limit_info;
}


struct SelectBySparms
{
    SelectBySparms(const float sparm0, const float sparm1) 
        : m_sparm0(sparm0)
        , m_sparm1(sparm1)
    {}
    const float m_sparm0;
    const float m_sparm1;

    bool operator () (const LimitInfo& limit_info) const
    {
        return (lt::is_equal(limit_info.sparm0, m_sparm0) && lt::is_equal(limit_info.sparm1, m_sparm1));
    }
};

void CreateLimitHists
(
    const std::string& input_file_path,
    const std::string& interp_file_name,
    const std::string& output_file_name
)
{
    // get the xsec and systematic information
    rt::TH1Container hc(interp_file_name);
/*     hc.List(); */

    // dummy histogram to get the bin information
    TH2F h_bins(*dynamic_cast<TH2F*>(hc["h_num_bdt1l"]));
    h_bins.Reset();
    const std::string xbin_label = h_bins.GetXaxis()->GetTitle();
    const std::string ybin_label = h_bins.GetYaxis()->GetTitle();

    // theoretical xsec
    const TH1& h_xsec = *hc["h_xsec"];

    // "best" upper limit hists
    TH2F h_sr_best           (h_bins);
    TH2F h_xsec_obs_ul_best  (h_bins);
    TH2F h_xsec_exp_ul_best  (h_bins);
    TH2F h_xsec_expp1_ul_best(h_bins);
    TH2F h_xsec_expm1_ul_best(h_bins);
    TH2F h_xsec_expp2_ul_best(h_bins);
    TH2F h_xsec_expm2_ul_best(h_bins);
    h_sr_best           .SetNameTitle("h_sr_best"           , Form("Best Signal Region;%s;%s"                        , xbin_label.c_str(), ybin_label.c_str()));
    h_xsec_obs_ul_best  .SetNameTitle("h_xsec_obs_ul_best"  , Form("Xsec Observed Upper Limit (pb) (Best);%s;%s"     , xbin_label.c_str(), ybin_label.c_str()));
    h_xsec_exp_ul_best  .SetNameTitle("h_xsec_exp_ul_best"  , Form("Xsec Expected Upper Limit (pb) (Best);%s;%s"     , xbin_label.c_str(), ybin_label.c_str()));
    h_xsec_expp1_ul_best.SetNameTitle("h_xsec_expp1_ul_best", Form("Xsec Expected Upper Limit + 1#sigma (pb) (Best);%s;%s", xbin_label.c_str(), ybin_label.c_str()));
    h_xsec_expm1_ul_best.SetNameTitle("h_xsec_expm1_ul_best", Form("Xsec Expected Upper Limit + 1#sigma (pb) (Best);%s;%s", xbin_label.c_str(), ybin_label.c_str()));
    h_xsec_expp2_ul_best.SetNameTitle("h_xsec_expp2_ul_best", Form("Xsec Expected Upper Limit + 2#sigma (pb) (Best);%s;%s", xbin_label.c_str(), ybin_label.c_str()));
    h_xsec_expm2_ul_best.SetNameTitle("h_xsec_expm2_ul_best", Form("Xsec Expected Upper Limit + 2#sigma (pb) (Best);%s;%s", xbin_label.c_str(), ybin_label.c_str()));

    for (size_t sr_num = 1; sr_num != stop::SignalRegion::static_size; sr_num++)
    {
        // sr info
        const stop::SignalRegion::value_type signal_region = static_cast<stop::SignalRegion::value_type>(sr_num);
        const stop::SignalRegionInfo sr_info               = stop::GetSignalRegionInfo(signal_region); 
        const std::string sr_hist_name                     = sr_info.label;
        const std::string sr_hist_title                    = sr_info.title;
    
        // UL hists
        TH2F h_xsec_obs_ul  (h_bins);
        TH2F h_xsec_exp_ul  (h_bins);
        TH2F h_xsec_expp1_ul(h_bins);
        TH2F h_xsec_expm1_ul(h_bins);
        TH2F h_xsec_expp2_ul(h_bins);
        TH2F h_xsec_expm2_ul(h_bins);
        h_xsec_obs_ul  .SetNameTitle(Form("h_xsec_obs_ul_%s"  , sr_hist_name.c_str()), Form("Xsec Observed Upper Limit (pb) (%s);%s;%s"          , sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));
        h_xsec_exp_ul  .SetNameTitle(Form("h_xsec_exp_ul_%s"  , sr_hist_name.c_str()), Form("Xsec Expected Upper Limit (pb) (%s);%s;%s"          , sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));
        h_xsec_expp1_ul.SetNameTitle(Form("h_xsec_expp1_ul_%s", sr_hist_name.c_str()), Form("Xsec Expected Upper Limit + 1#sigma (pb) (%s);%s;%s", sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));
        h_xsec_expm1_ul.SetNameTitle(Form("h_xsec_expm1_ul_%s", sr_hist_name.c_str()), Form("Xsec Expected Upper Limit + 1#sigma (pb) (%s);%s;%s", sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));
        h_xsec_expp2_ul.SetNameTitle(Form("h_xsec_expp2_ul_%s", sr_hist_name.c_str()), Form("Xsec Expected Upper Limit + 2#sigma (pb) (%s);%s;%s", sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));
        h_xsec_expm2_ul.SetNameTitle(Form("h_xsec_expm2_ul_%s", sr_hist_name.c_str()), Form("Xsec Expected Upper Limit + 2#sigma (pb) (%s);%s;%s", sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));

        // exclusion hists
        TH2F h_excl_obs_ul  (h_bins);
        TH2F h_excl_exp_ul  (h_bins);
        TH2F h_excl_expp1_ul(h_bins);
        TH2F h_excl_expm1_ul(h_bins);
        TH2F h_excl_obsp1_ul(h_bins);
        TH2F h_excl_obsm1_ul(h_bins);
        h_excl_obs_ul  .SetNameTitle(Form("h_excl_obs_ul_%s"  , sr_hist_name.c_str()), Form("Excluded Observed (%s);%s;%s"               , sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));
        h_excl_exp_ul  .SetNameTitle(Form("h_excl_exp_ul_%s"  , sr_hist_name.c_str()), Form("Excluded Expected (%s);%s;%s"               , sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));
        h_excl_expp1_ul.SetNameTitle(Form("h_excl_expp1_ul_%s", sr_hist_name.c_str()), Form("Excluded Expected + 1#sigma (%s);%s;%s"     , sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));
        h_excl_expm1_ul.SetNameTitle(Form("h_excl_expm1_ul_%s", sr_hist_name.c_str()), Form("Excluded Expected + 1#sigma (%s);%s;%s"     , sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));
        h_excl_obsp1_ul.SetNameTitle(Form("h_excl_obsp1_ul_%s", sr_hist_name.c_str()), Form("Excluded Observed + 1#sigma_{th} (%s);%s;%s", sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));
        h_excl_obsm1_ul.SetNameTitle(Form("h_excl_obsm1_ul_%s", sr_hist_name.c_str()), Form("Excluded Observed + 1#sigma_{th} (%s);%s;%s", sr_hist_title.c_str(), xbin_label.c_str(), ybin_label.c_str()));

        // populate hists 
        std::vector<std::string> band_files = lt::ls(input_file_path + "/bands_*_" + sr_info.label + "_m2lnQ.root");
        for (size_t i = 0; i != band_files.size(); i++)
        {
            const std::string band_file_name = band_files.at(i);
            const std::vector<std::string> split = lt::string_split(band_file_name);
            LimitInfo limit_info = CreateLimitInfo(h_xsec, band_file_name);
            const float sparm0   = limit_info.sparm0;
            const float sparm1   = limit_info.sparm1;

            rt::SetBinContent2D(&h_xsec_obs_ul  , sparm0, sparm1, 1e-3*limit_info.obs, 1e-3*limit_info.obs_err);
            rt::SetBinContent2D(&h_xsec_exp_ul  , sparm0, sparm1, 1e-3*limit_info.exp, 1e-3*limit_info.exp_err);
            rt::SetBinContent2D(&h_xsec_expp1_ul, sparm0, sparm1, 1e-3*limit_info.exp_1sigma_up, 0.0);
            rt::SetBinContent2D(&h_xsec_expm1_ul, sparm0, sparm1, 1e-3*limit_info.exp_1sigma_dn, 0.0);
            rt::SetBinContent2D(&h_xsec_expp2_ul, sparm0, sparm1, 1e-3*limit_info.exp_2sigma_up, 0.0);
            rt::SetBinContent2D(&h_xsec_expm2_ul, sparm0, sparm1, 1e-3*limit_info.exp_2sigma_dn, 0.0);

            // set "best" SR to dummy value for comparison
            rt::SetBinContent2D(&h_xsec_exp_ul_best, sparm0, sparm1, std::numeric_limits<float>::max());

            // determin if point is excluded
            const float xsec     = rt::GetBinContent1D(&h_xsec, sparm0);
            const float xsec_err = rt::GetBinError1D  (&h_xsec, sparm0);
            const float xsec_up  = xsec + xsec_err;
            const float xsec_dn  = xsec - xsec_err;

            if (xsec    > 1e-3*limit_info.obs          ) {rt::SetBinContent2D(&h_excl_obs_ul  , sparm0, sparm1, 1);}
            if (xsec    > 1e-3*limit_info.exp          ) {rt::SetBinContent2D(&h_excl_exp_ul  , sparm0, sparm1, 1);}
            if (xsec    > 1e-3*limit_info.exp_1sigma_up) {rt::SetBinContent2D(&h_excl_expp1_ul, sparm0, sparm1, 1);}
            if (xsec    > 1e-3*limit_info.exp_1sigma_dn) {rt::SetBinContent2D(&h_excl_expp1_ul, sparm0, sparm1, 1);}
            if (xsec_up > 1e-3*limit_info.obs          ) {rt::SetBinContent2D(&h_excl_obsp1_ul, sparm0, sparm1, 1);}
            if (xsec_dn > 1e-3*limit_info.obs          ) {rt::SetBinContent2D(&h_excl_obsm1_ul, sparm0, sparm1, 1);}

        }
    
        // add hists to container
        hc.Add(h_xsec_obs_ul  );
        hc.Add(h_xsec_exp_ul  );
        hc.Add(h_xsec_expp1_ul);
        hc.Add(h_xsec_expm1_ul);
        hc.Add(h_xsec_expp2_ul);
        hc.Add(h_xsec_expm2_ul);

        hc.Add(h_excl_obs_ul  );
        hc.Add(h_excl_exp_ul  );
        hc.Add(h_excl_expp1_ul);
        hc.Add(h_excl_expm1_ul);
        hc.Add(h_excl_obsp1_ul);
        hc.Add(h_excl_obsm1_ul);
    }

    // get the "best" sr
    for (size_t sr_num = 1; sr_num != stop::SignalRegion::static_size; sr_num++)
    {
        // sr info
        const stop::SignalRegion::value_type signal_region = static_cast<stop::SignalRegion::value_type>(sr_num);
        const stop::SignalRegionInfo sr_info               = stop::GetSignalRegionInfo(signal_region); 
        const std::string sr_hist_name                     = sr_info.label;

        for (int xbin = 0; xbin != h_bins.GetNbinsX(); xbin++)
        {
            for (int ybin = 0; ybin != h_bins.GetNbinsY(); ybin++)
            {
                const float xsec_exp = hc["h_xsec_exp_ul_"+sr_hist_name]->GetBinContent(xbin, ybin);
                if (lt::is_zero(xsec_exp)) {continue;}

                if (xsec_exp < h_xsec_exp_ul_best.GetBinContent(xbin, ybin))
                {
                    h_sr_best           .SetBinContent(xbin, ybin, sr_num);
                    h_xsec_obs_ul_best  .SetBinContent(xbin, ybin, hc["h_xsec_obs_ul_"  +sr_hist_name]->GetBinContent(xbin, ybin));
                    h_xsec_exp_ul_best  .SetBinContent(xbin, ybin, hc["h_xsec_exp_ul_"  +sr_hist_name]->GetBinContent(xbin, ybin));
                    h_xsec_expp1_ul_best.SetBinContent(xbin, ybin, hc["h_xsec_expp1_ul_"+sr_hist_name]->GetBinContent(xbin, ybin));
                    h_xsec_expm1_ul_best.SetBinContent(xbin, ybin, hc["h_xsec_expm1_ul_"+sr_hist_name]->GetBinContent(xbin, ybin));
                    h_xsec_expp2_ul_best.SetBinContent(xbin, ybin, hc["h_xsec_expp2_ul_"+sr_hist_name]->GetBinContent(xbin, ybin));
                    h_xsec_expm2_ul_best.SetBinContent(xbin, ybin, hc["h_xsec_expm2_ul_"+sr_hist_name]->GetBinContent(xbin, ybin));

                    h_sr_best           .SetBinError(xbin, ybin, 0);
                    h_xsec_obs_ul_best  .SetBinError(xbin, ybin, hc["h_xsec_obs_ul_"  +sr_hist_name]->GetBinError(xbin, ybin));
                    h_xsec_exp_ul_best  .SetBinError(xbin, ybin, hc["h_xsec_exp_ul_"  +sr_hist_name]->GetBinError(xbin, ybin));
                    h_xsec_expp1_ul_best.SetBinError(xbin, ybin, hc["h_xsec_expp1_ul_"+sr_hist_name]->GetBinError(xbin, ybin));
                    h_xsec_expm1_ul_best.SetBinError(xbin, ybin, hc["h_xsec_expm1_ul_"+sr_hist_name]->GetBinError(xbin, ybin));
                    h_xsec_expp2_ul_best.SetBinError(xbin, ybin, hc["h_xsec_expp2_ul_"+sr_hist_name]->GetBinError(xbin, ybin));
                    h_xsec_expm2_ul_best.SetBinError(xbin, ybin, hc["h_xsec_expm2_ul_"+sr_hist_name]->GetBinError(xbin, ybin));
                }
            }
        }
    }

    // add hists to container
    hc.Add(h_sr_best           );
    hc.Add(h_xsec_obs_ul_best  );
    hc.Add(h_xsec_exp_ul_best  );
    hc.Add(h_xsec_expp1_ul_best);
    hc.Add(h_xsec_expm1_ul_best);
    hc.Add(h_xsec_expp2_ul_best);
    hc.Add(h_xsec_expm2_ul_best);

    // save
    hc.Write(output_file_name);
/*     hc.Print(lt::dirname(output_file_name) + "/png", "png"); */
}
