#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "RootTools.h"
#include "LanguageTools.h"
#include "Sample.h"
#include "SignalRegion.h"
#include "PrintFormattedXSecHist.h"

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
    double exp_1sigma_up_err;
    double exp_1sigma_dn;
    double exp_1sigma_dn_err;
    double exp_2sigma_up;
    double exp_2sigma_up_err;
    double exp_2sigma_dn;
    double exp_2sigma_dn_err;
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
    os << Form("%1.0f\t%1.0f\t%1.6f\t%1.6f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f",
        limit_info.sparm0,
        limit_info.sparm1,
        limit_info.xsec,
        limit_info.xsec_err,
        limit_info.obs,
        limit_info.obs_err,
        limit_info.exp,
        limit_info.exp_err,
        limit_info.exp_1sigma_up,
        limit_info.exp_1sigma_up_err,
        limit_info.exp_1sigma_dn,
        limit_info.exp_1sigma_dn_err,
        limit_info.exp_2sigma_up,
        limit_info.exp_2sigma_up_err,
        limit_info.exp_2sigma_dn,
        limit_info.exp_2sigma_dn_err
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
    in >> limit_info.exp_1sigma_up_err;
    in >> limit_info.exp_1sigma_dn;
    in >> limit_info.exp_1sigma_dn_err;
    in >> limit_info.exp_2sigma_up;
    in >> limit_info.exp_2sigma_up_err;
    in >> limit_info.exp_2sigma_dn;
    in >> limit_info.exp_2sigma_dn_err;
    return in;
};

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

struct Channel
{
    enum value_type
    {
        Razor,
        SingleLep,
        Combined,
        static_size
    };
};

LimitInfo CreateLimitInfoCombine
(
    const Channel::value_type channel_type,
    const TH2F& h_xsec, 
    const std::string& file_name
)
{
    const std::string raw_file_name = lt::filename(lt::string_remove_all(file_name, ".root"));
    const std::vector<std::string> split = lt::string_split(raw_file_name, "_");
    //std::cout << lt::ArrayString(split) << std::endl;
    LimitInfo limit_info;
    switch (channel_type)
    {
        case Channel::SingleLep:
            limit_info.sparm0   = lt::string_to_double(split.at(3));
            limit_info.sparm1   = lt::string_to_double(split.at(4));
            break;
        case Channel::Razor:
            limit_info.sparm0   = lt::string_to_double(split.at(7));
            limit_info.sparm1   = lt::string_to_double(split.at(9));
            break;
        case Channel::Combined:
            limit_info.sparm0   = lt::string_to_double(split.at(4));
            limit_info.sparm1   = lt::string_to_double(split.at(5));
            break;
        default: 
            return limit_info;
    }
    limit_info.xsec     = rt::GetBinContent2D(&h_xsec, limit_info.sparm0, limit_info.sparm1);
    limit_info.xsec_err = rt::GetBinError2D  (&h_xsec, limit_info.sparm0, limit_info.sparm1);
    //************************************************************************************************************************************
    //*    Row   *     limit *  limitErr *        mh *      syst *      iToy *     iSeed *  iChannel *     t_cpu *    t_real * quantileE *
    //************************************************************************************************************************************
    //*        0 * 458.94241 * 19.426551 *       120 *         1 *         0 *      1234 *         0 * 0.0513333 * 11.885654 * 0.0227499 *
    //*        1 * 574.77644 * 4.9762625 *       120 *         1 *         0 *      1234 *         0 * 0.0128333 * 5.9013505 * 0.1586499 *
    //*        2 * 775.87554 * 27.388386 *       120 *         1 *         0 *      1234 *         0 * 0.0040000 * 0.8493257 *       0.5 *
    //*        3 * 1050.4895 * 14.983479 *       120 *         1 *         0 *      1234 *         0 * 0.0035000 * 0.6285593 * 0.8413500 *
    //*        4 * 1393.6381 * 67.220865 *       120 *         1 *         0 *      1234 *         0 * 0.0030000 * 0.2962681 * 0.9772499 *
    //*        5 * 689.73085 * 4.0671192 *       120 *         1 *         0 *      1234 *         0 * 0.0063333 * 2.8123662 *        -1 *
    //************************************************************************************************************************************

    TChain chain("limit");
    chain.Add(file_name.c_str());
    double ul;
    double ul_err;
    chain.SetBranchAddress("limit"   , &ul    );
    chain.SetBranchAddress("limitErr", &ul_err);
    chain.GetEntry(5);
    limit_info.obs               = limit_info.xsec * ul;
    limit_info.obs_err           = limit_info.xsec * ul_err;
    chain.GetEntry(2);
    limit_info.exp               = limit_info.xsec * ul;
    limit_info.exp_err           = limit_info.xsec * ul_err;
    chain.GetEntry(3);
    limit_info.exp_1sigma_up     = limit_info.xsec * ul;
    limit_info.exp_1sigma_up_err = limit_info.xsec * ul_err;
    chain.GetEntry(0);
    limit_info.exp_1sigma_dn     = limit_info.xsec * ul;
    limit_info.exp_1sigma_dn_err = limit_info.xsec * ul_err;
    chain.GetEntry(4);
    limit_info.exp_2sigma_up     = limit_info.xsec * ul;
    limit_info.exp_2sigma_up_err = limit_info.xsec * ul_err;
    chain.GetEntry(1);
    limit_info.exp_2sigma_dn     = limit_info.xsec * ul;
    limit_info.exp_2sigma_dn_err = limit_info.xsec * ul_err;
    return limit_info;
}

void CreateRazorCombinedLimitHists
(
    const Channel::value_type channel_type,
    const std::string& input_file_path,
    const std::string& output_file_name
)
{
    try
    {
        // get best SR histogram 
        const TH2F h_sr_best(*rt::GetHistFromRootFile<TH2F>("data/T2tt_onelep_bdt_orig.root", "hbest"));

        // theoretical xsec
        const TH2F h_xsec = *rt::GetHistFromRootFile<TH2F>("data/stop_xsec_2D.root", "h_stop_xsec_2D");

        // dummy histogram to get the bin information
        TH2F h_bins(h_sr_best);
        h_bins.Reset();
        const std::string xbin_label = h_bins.GetXaxis()->GetTitle();
        const std::string ybin_label = h_bins.GetYaxis()->GetTitle();
        const std::string zbin_label = "#sigma Upper Limit (pb)"; 

        // "best" upper limit hists
        TH2F h_xsec_obs_ul  (h_bins);
        TH2F h_xsec_exp_ul  (h_bins);
        TH2F h_xsec_expp1_ul(h_bins);
        TH2F h_xsec_expm1_ul(h_bins);
        TH2F h_xsec_expp2_ul(h_bins);
        TH2F h_xsec_expm2_ul(h_bins);
        h_xsec_obs_ul  .SetNameTitle("h_xsec_obs_ul"  , Form("Xsec Observed Upper Limit (pb);%s;%s;%s"          , xbin_label.c_str(), ybin_label.c_str(), zbin_label.c_str()));
        h_xsec_exp_ul  .SetNameTitle("h_xsec_exp_ul"  , Form("Xsec Expected Upper Limit (pb);%s;%s;%s"          , xbin_label.c_str(), ybin_label.c_str(), zbin_label.c_str()));
        h_xsec_expp1_ul.SetNameTitle("h_xsec_expp1_ul", Form("Xsec Expected Upper Limit + 1#sigma (pb);%s;%s;%s", xbin_label.c_str(), ybin_label.c_str(), zbin_label.c_str()));
        h_xsec_expm1_ul.SetNameTitle("h_xsec_expm1_ul", Form("Xsec Expected Upper Limit + 1#sigma (pb);%s;%s;%s", xbin_label.c_str(), ybin_label.c_str(), zbin_label.c_str()));
        h_xsec_expp2_ul.SetNameTitle("h_xsec_expp2_ul", Form("Xsec Expected Upper Limit + 2#sigma (pb);%s;%s;%s", xbin_label.c_str(), ybin_label.c_str(), zbin_label.c_str()));
        h_xsec_expm2_ul.SetNameTitle("h_xsec_expm2_ul", Form("Xsec Expected Upper Limit + 2#sigma (pb);%s;%s;%s", xbin_label.c_str(), ybin_label.c_str(), zbin_label.c_str()));

        TH2F h_excl_obs  (h_bins);
        TH2F h_excl_exp  (h_bins);
        TH2F h_excl_expp1(h_bins);
        TH2F h_excl_expm1(h_bins);
        TH2F h_excl_obsp1(h_bins);
        TH2F h_excl_obsm1(h_bins);
        h_excl_obs  .SetNameTitle("h_excl_obs"  , Form("Excluded Observed;%s;%s"               , xbin_label.c_str(), ybin_label.c_str()));
        h_excl_exp  .SetNameTitle("h_excl_exp"  , Form("Excluded Expected;%s;%s"               , xbin_label.c_str(), ybin_label.c_str()));
        h_excl_expp1.SetNameTitle("h_excl_expp1", Form("Excluded Expected + 1#sigma;%s;%s"     , xbin_label.c_str(), ybin_label.c_str()));
        h_excl_expm1.SetNameTitle("h_excl_expm1", Form("Excluded Expected + 1#sigma;%s;%s"     , xbin_label.c_str(), ybin_label.c_str()));
        h_excl_obsp1.SetNameTitle("h_excl_obsp1", Form("Excluded Observed + 1#sigma_{th};%s;%s", xbin_label.c_str(), ybin_label.c_str()));
        h_excl_obsm1.SetNameTitle("h_excl_obsm1", Form("Excluded Observed + 1#sigma_{th};%s;%s", xbin_label.c_str(), ybin_label.c_str()));

        for (int xbin = 1; xbin < h_bins.GetNbinsX(); ++xbin)
        {
            for (int ybin = 1; ybin < h_bins.GetNbinsX(); ++ybin)
            {
                // get the mass for that bin
                const float mass_stop = h_bins.GetXaxis()->GetBinCenter(xbin);
                const float mass_lsp  = h_bins.GetYaxis()->GetBinCenter(ybin);
                if (mass_lsp > (mass_stop - 100)) {continue;}

                // get the best SR for that mass point
                const int sr_num                        = static_cast<int>(rt::GetBinContent2D(&h_sr_best, mass_stop, mass_lsp));
                const stop::SignalRegion::value_type sr = static_cast<stop::SignalRegion::value_type>(sr_num);
                const stop::SignalRegionInfo sr_info    = stop::GetSignalRegionInfo(sr);
                if (sr == stop::SignalRegion::sr0) {continue;}

                std::string limit_file_name = input_file_path + "/combine_output_";
                switch (channel_type)
                {
                    case Channel::Razor    : limit_file_name += Form("razor_combine_Had_T2tt_MG_%1.0f.000000_MCHI_%1.0f.000000.root", mass_stop, mass_lsp);                        break;
                    case Channel::SingleLep: limit_file_name += Form("t2tt_%1.0f_%1.0f_%s.root"                                     , mass_stop, mass_lsp, sr_info.label.c_str()); break;
                    case Channel::Combined : limit_file_name += Form("combined_t2tt_%1.0f_%1.0f_%s.root"                            , mass_stop, mass_lsp, sr_info.label.c_str()); break;
                    default:
                        std::cout << "[CreateRazorCombinedLimitHists] Error: invalid channel" << std::endl;
                        return;
                };

                if (not lt::file_exists(limit_file_name))
                {
                    std::cout << "[CreateRazorCombinedLimitHists] Error: file doesn't exist: " << limit_file_name << std::endl;
                    continue;
                }

                const LimitInfo limit_info = CreateLimitInfoCombine(channel_type, h_xsec, limit_file_name);
                //cout << limit_info << endl;

                rt::SetBinContent2D(&h_xsec_obs_ul  , mass_stop, mass_lsp, limit_info.obs          , limit_info.obs_err          );
                rt::SetBinContent2D(&h_xsec_exp_ul  , mass_stop, mass_lsp, limit_info.exp          , limit_info.exp_err          );
                rt::SetBinContent2D(&h_xsec_expp1_ul, mass_stop, mass_lsp, limit_info.exp_1sigma_up, limit_info.exp_1sigma_up_err);
                rt::SetBinContent2D(&h_xsec_expm1_ul, mass_stop, mass_lsp, limit_info.exp_1sigma_dn, limit_info.exp_1sigma_dn_err);
                rt::SetBinContent2D(&h_xsec_expp2_ul, mass_stop, mass_lsp, limit_info.exp_2sigma_up, limit_info.exp_2sigma_up_err);
                rt::SetBinContent2D(&h_xsec_expm2_ul, mass_stop, mass_lsp, limit_info.exp_2sigma_dn, limit_info.exp_2sigma_dn_err);

                // determin if point is excluded
                const float xsec     = rt::GetBinContent2D(&h_xsec, mass_stop, mass_lsp);
                const float xsec_err = rt::GetBinError2D  (&h_xsec, mass_stop, mass_lsp);
                const float xsec_up  = xsec + xsec_err;
                const float xsec_dn  = xsec - xsec_err;

                if (xsec    > limit_info.obs          ) {rt::SetBinContent2D(&h_excl_obs  , mass_stop, mass_lsp, 1);}
                if (xsec    > limit_info.exp          ) {rt::SetBinContent2D(&h_excl_exp  , mass_stop, mass_lsp, 1);}
                if (xsec    > limit_info.exp_1sigma_up) {rt::SetBinContent2D(&h_excl_expp1, mass_stop, mass_lsp, 1);}
                if (xsec    > limit_info.exp_1sigma_dn) {rt::SetBinContent2D(&h_excl_expp1, mass_stop, mass_lsp, 1);}
                if (xsec_up > limit_info.obs          ) {rt::SetBinContent2D(&h_excl_obsp1, mass_stop, mass_lsp, 1);}
                if (xsec_dn > limit_info.obs          ) {rt::SetBinContent2D(&h_excl_obsm1, mass_stop, mass_lsp, 1);}
            }
        }

        // add hists to container
        rt::TH1Container hc;
        hc.Add(h_sr_best      );
        hc.Add(h_xsec_obs_ul  );
        hc.Add(h_xsec_exp_ul  );
        hc.Add(h_xsec_expp1_ul);
        hc.Add(h_xsec_expm1_ul);
        hc.Add(h_xsec_expp2_ul);
        hc.Add(h_xsec_expm2_ul);
        hc.Add(h_excl_obs);
        hc.Add(h_excl_exp);
        hc.Add(h_excl_expp1);
        hc.Add(h_excl_expm1);
        hc.Add(h_excl_obsp1);
        hc.Add(h_excl_obsm1);

        std::string plot_path = lt::dirname(output_file_name);
        switch (channel_type)
        {
            case Channel::Razor    : plot_path += "/razor";     break;
            case Channel::SingleLep: plot_path += "/singlelep"; break;
            case Channel::Combined : plot_path += "/combined";  break;
            default                : {/*do nothing*/}
        };
        stop::PrintFormattedXSecHist(h_xsec_obs_ul  , "h_xsec_obs_ul"  , plot_path, "png", "colz", "1.2f", 1e-3, 1e2);
        stop::PrintFormattedXSecHist(h_xsec_exp_ul  , "h_xsec_exp_ul"  , plot_path, "png", "colz", "1.2f", 1e-3, 1e2);
        stop::PrintFormattedXSecHist(h_xsec_expp1_ul, "h_xsec_expp1_ul", plot_path, "png", "colz", "1.2f", 1e-3, 1e2);
        stop::PrintFormattedXSecHist(h_xsec_expm1_ul, "h_xsec_expm1_ul", plot_path, "png", "colz", "1.2f", 1e-3, 1e2);
        stop::PrintFormattedXSecHist(h_xsec_expp2_ul, "h_xsec_expp2_ul", plot_path, "png", "colz", "1.2f", 1e-3, 1e2);
        stop::PrintFormattedXSecHist(h_xsec_expm2_ul, "h_xsec_expm2_ul", plot_path, "png", "colz", "1.2f", 1e-3, 1e2);
        stop::PrintFormattedXSecHist(h_excl_obs     , "h_excl_obs"     , plot_path, "png", "text", "1.0f", 0.0 , 1.0);
        stop::PrintFormattedXSecHist(h_excl_exp     , "h_excl_exp"     , plot_path, "png", "text", "1.0f", 0.0 , 1.0);
        stop::PrintFormattedXSecHist(h_excl_expp1   , "h_excl_expp1"   , plot_path, "png", "text", "1.0f", 0.0 , 1.0);
        stop::PrintFormattedXSecHist(h_excl_expm1   , "h_excl_expm1"   , plot_path, "png", "text", "1.0f", 0.0 , 1.0);
        stop::PrintFormattedXSecHist(h_excl_obsp1   , "h_excl_obsp1"   , plot_path, "png", "text", "1.0f", 0.0 , 1.0);
        stop::PrintFormattedXSecHist(h_excl_obsm1   , "h_excl_obsm1"   , plot_path, "png", "text", "1.0f", 0.0 , 1.0);

        // save
        hc.Write(output_file_name);
    }
    catch (std::exception& e)
    {
        cerr << "[CreateLimitHists] Error: " << e.what() << endl;
    }
}

// convenience
void CreateCombinedLimitHists()
{
    CreateRazorCombinedLimitHists(Channel::SingleLep, "output/limits/lep1_razor_combine/asymptotic/t2tt", "plots/limits/lep1_razor_combine/asymptotic/t2tt/t2tt_singlelep_limit_hists.root");
    CreateRazorCombinedLimitHists(Channel::Razor    , "output/limits/lep1_razor_combine/asymptotic/t2tt", "plots/limits/lep1_razor_combine/asymptotic/t2tt/t2tt_razor_limit_hists.root"    );
    CreateRazorCombinedLimitHists(Channel::Combined , "output/limits/lep1_razor_combine/asymptotic/t2tt", "plots/limits/lep1_razor_combine/asymptotic/t2tt/t2tt_combined_limit_hists.root" );

    CreateRazorCombinedLimitHists(Channel::SingleLep, "output/limits/lep1_razor_combine/hybridnew/t2tt", "plots/limits/lep1_razor_combine/hybridnew/t2tt/t2tt_singlelep_limit_hists.root");
    CreateRazorCombinedLimitHists(Channel::Razor    , "output/limits/lep1_razor_combine/hybridnew/t2tt", "plots/limits/lep1_razor_combine/hybridnew/t2tt/t2tt_razor_limit_hists.root"    );
    CreateRazorCombinedLimitHists(Channel::Combined , "output/limits/lep1_razor_combine/hybridnew/t2tt", "plots/limits/lep1_razor_combine/hybridnew/t2tt/t2tt_combined_limit_hists.root" );
}
