
#include "StopAnalysis/CombinedExclusions/interface/STOP_BABY.h"
#include <iostream>

// global object
STOP_BABY stop_baby_obj;

// implementation of STOP_BABY
// ---------------------------------------------------------------------------------------------- //

STOP_BABY::STOP_BABY()
    : acc_2010_handle("acc_2010")
    , acc_highmet_handle("acc_highmet")
    , acc_highht_handle("acc_highht")
    , eldup_handle("eldup")
    , csc_handle("csc")
    , hbhe_handle("hbhe")
    , hbhenew_handle("hbhenew")
    , hcallaser_handle("hcallaser")
    , ecaltp_handle("ecaltp")
    , trkfail_handle("trkfail")
    , eebadsc_handle("eebadsc")
    , lep1_badecallaser_handle("lep1_badecallaser")
    , lep2_badecallaser_handle("lep2_badecallaser")
    , isdata_handle("isdata")
    , jetid_handle("jetid")
    , jetid30_handle("jetid30")
    , json_handle("json")
    , htoffset_handle("htoffset")
    , htuncor_handle("htuncor")
    , ptt_handle("ptt")
    , pttbar_handle("pttbar")
    , ptttbar_handle("ptttbar")
    , mttbar_handle("mttbar")
    , npartons_handle("npartons")
    , nwzpartons_handle("nwzpartons")
    , hyptype_handle("hyptype")
    , maxpartonpt_handle("maxpartonpt")
    , etattbar_handle("etattbar")
    , njetsoffset_handle("njetsoffset")
    , njetsuncor_handle("njetsuncor")
    , costhetaweight_handle("costhetaweight")
    , weight_handle("weight")
    , weightleft_handle("weightleft")
    , weightright_handle("weightright")
    , mutrigweight_handle("mutrigweight")
    , mutrigweight2_handle("mutrigweight2")
    , sltrigweight_handle("sltrigweight")
    , dltrigweight_handle("dltrigweight")
    , trgeff_handle("trgeff")
    , pthat_handle("pthat")
    , qscale_handle("qscale")
    , mgcor_handle("mgcor")
    , wflav_handle("wflav")
    , ksusy_handle("ksusy")
    , ksusyup_handle("ksusyup")
    , ksusydn_handle("ksusydn")
    , xsecsusy_handle("xsecsusy")
    , xsecsusy2_handle("xsecsusy2")
    , smeff_handle("smeff")
    , k_handle("k")
    , mllgen_handle("mllgen")
    , ptwgen_handle("ptwgen")
    , ptzgen_handle("ptzgen")
    , nlep_handle("nlep")
    , nosel_handle("nosel")
    , ngoodlep_handle("ngoodlep")
    , ngoodel_handle("ngoodel")
    , ngoodmu_handle("ngoodmu")
    , mull_handle("mull")
    , mult_handle("mult")
    , mullgen_handle("mullgen")
    , multgen_handle("multgen")
    , proc_handle("proc")
    , leptype_handle("leptype")
    , topmass_handle("topmass")
    , dilmass_handle("dilmass")
    , dilrecoil_handle("dilrecoil")
    , dilrecoilparl_handle("dilrecoilparl")
    , dilrecoilperp_handle("dilrecoilperp")
    , tcmet_handle("tcmet")
    , genmet_handle("genmet")
    , gensumet_handle("gensumet")
    , genmetphi_handle("genmetphi")
    , calomet_handle("calomet")
    , calometphi_handle("calometphi")
    , trkmet_handle("trkmet")
    , trkmetphi_handle("trkmetphi")
    , trkmet_nolepcorr_handle("trkmet_nolepcorr")
    , trkmetphi_nolepcorr_handle("trkmetphi_nolepcorr")
    , pfmet_handle("pfmet")
    , pfmetveto_handle("pfmetveto")
    , pfmetsig_handle("pfmetsig")
    , pfmetphi_handle("pfmetphi")
    , pfsumet_handle("pfsumet")
    , mucormet_handle("mucormet")
    , mucorjesmet_handle("mucorjesmet")
    , tcmet35X_handle("tcmet35X")
    , tcmetevent_handle("tcmetevent")
    , tcmetlooper_handle("tcmetlooper")
    , tcmetphi_handle("tcmetphi")
    , tcsumet_handle("tcsumet")
    , tcmetUp_handle("tcmetUp")
    , tcmetDown_handle("tcmetDown")
    , tcmetTest_handle("tcmetTest")
    , pfmetUp_handle("pfmetUp")
    , pfmetDown_handle("pfmetDown")
    , pfmetTest_handle("pfmetTest")
    , sumjetpt_handle("sumjetpt")
    , dileta_handle("dileta")
    , dilpt_handle("dilpt")
    , dildphi_handle("dildphi")
    , ngenjets_handle("ngenjets")
    , njpt_handle("njpt")
    , trgmu1_handle("trgmu1")
    , trgmu2_handle("trgmu2")
    , trgel1_handle("trgel1")
    , trgel2_handle("trgel2")
    , isomu24_handle("isomu24")
    , ele27wp80_handle("ele27wp80")
    , mm_handle("mm")
    , mmtk_handle("mmtk")
    , me_handle("me")
    , em_handle("em")
    , mu_handle("mu")
    , ee_handle("ee")
    , npfjets30_handle("npfjets30")
    , npfjets30lepcorr_handle("npfjets30lepcorr")
    , knjets_handle("knjets")
    , rhovor_handle("rhovor")
    , htpf30_handle("htpf30")
    , t1met10_handle("t1met10")
    , t1met20_handle("t1met20")
    , t1met30_handle("t1met30")
    , t1met10phi_handle("t1met10phi")
    , t1met20phi_handle("t1met20phi")
    , t1met30phi_handle("t1met30phi")
    , t1met10mt_handle("t1met10mt")
    , t1met20mt_handle("t1met20mt")
    , t1met30mt_handle("t1met30mt")
    , lepmetpt_handle("lepmetpt")
    , lept1met10pt_handle("lept1met10pt")
    , t1met10s_handle("t1met10s")
    , t1met10sphi_handle("t1met10sphi")
    , t1met10smt_handle("t1met10smt")
    , t1metphicorr_handle("t1metphicorr")
    , t1metphicorrup_handle("t1metphicorrup")
    , t1metphicorrdn_handle("t1metphicorrdn")
    , t1metphicorrphi_handle("t1metphicorrphi")
    , t1metphicorrphiup_handle("t1metphicorrphiup")
    , t1metphicorrphidn_handle("t1metphicorrphidn")
    , t1metphicorrlep_handle("t1metphicorrlep")
    , t1metphicorrlepphi_handle("t1metphicorrlepphi")
    , t1metphicorrmt_handle("t1metphicorrmt")
    , t1metphicorrmtup_handle("t1metphicorrmtup")
    , t1metphicorrmtdn_handle("t1metphicorrmtdn")
    , t1metphicorrlepmt_handle("t1metphicorrlepmt")
    , t1met_off_handle("t1met_off")
    , t1metphi_off_handle("t1metphi_off")
    , t1metmt_off_handle("t1metmt_off")
    , t1metphicorr_off_handle("t1metphicorr_off")
    , t1metphicorrphi_off_handle("t1metphicorrphi_off")
    , t1metphicorrmt_off_handle("t1metphicorrmt_off")
    , mt2bmin_handle("mt2bmin")
    , mt2blmin_handle("mt2blmin")
    , mt2wmin_handle("mt2wmin")
    , chi2min_handle("chi2min")
    , chi2minprob_handle("chi2minprob")
    , nbtagsssv_handle("nbtagsssv")
    , nbtagstcl_handle("nbtagstcl")
    , nbtagstcm_handle("nbtagstcm")
    , nbtagscsvl_handle("nbtagscsvl")
    , nbtagscsvm_handle("nbtagscsvm")
    , nbtagscsvt_handle("nbtagscsvt")
    , nbtagsssvcorr_handle("nbtagsssvcorr")
    , nbtagstclcorr_handle("nbtagstclcorr")
    , nbtagstcmcorr_handle("nbtagstcmcorr")
    , nbtagscsvlcorr_handle("nbtagscsvlcorr")
    , nbtagscsvmcorr_handle("nbtagscsvmcorr")
    , nbtagscsvtcott_handle("nbtagscsvtcott")
    , njetsUp_handle("njetsUp")
    , njetsDown_handle("njetsDown")
    , htUp_handle("htUp")
    , htDown_handle("htDown")
    , ntruepu_handle("ntruepu")
    , npu_handle("npu")
    , npuMinusOne_handle("npuMinusOne")
    , npuPlusOne_handle("npuPlusOne")
    , nvtx_handle("nvtx")
    , indexfirstGoodVertex__handle("indexfirstGoodVertex_")
    , nvtxweight_handle("nvtxweight")
    , n3dvtxweight_handle("n3dvtxweight")
    , pdfid1_handle("pdfid1")
    , pdfid2_handle("pdfid2")
    , pdfx1_handle("pdfx1")
    , pdfx2_handle("pdfx2")
    , pdfQ_handle("pdfQ")
    , vecjetpt_handle("vecjetpt")
    , pass_handle("pass")
    , passz_handle("passz")
    , m0_handle("m0")
    , mg_handle("mg")
    , ml_handle("ml")
    , x_handle("x")
    , m12_handle("m12")
    , lep1chi2ndf_handle("lep1chi2ndf")
    , lep2chi2ndf_handle("lep2chi2ndf")
    , lep1dpt_handle("lep1dpt")
    , lep2dpt_handle("lep2dpt")
    , id1_handle("id1")
    , id2_handle("id2")
    , leptype1_handle("leptype1")
    , leptype2_handle("leptype2")
    , w1_handle("w1")
    , w2_handle("w2")
    , iso1_handle("iso1")
    , isont1_handle("isont1")
    , isopfold1_handle("isopfold1")
    , isopf1_handle("isopf1")
    , etasc1_handle("etasc1")
    , etasc2_handle("etasc2")
    , eoverpin_handle("eoverpin")
    , eoverpout_handle("eoverpout")
    , dEtaIn_handle("dEtaIn")
    , dPhiIn_handle("dPhiIn")
    , sigmaIEtaIEta_handle("sigmaIEtaIEta")
    , hOverE_handle("hOverE")
    , ooemoop_handle("ooemoop")
    , d0vtx_handle("d0vtx")
    , dzvtx_handle("dzvtx")
    , expinnerlayers_handle("expinnerlayers")
    , fbrem_handle("fbrem")
    , pfisoch_handle("pfisoch")
    , pfisoem_handle("pfisoem")
    , pfisonh_handle("pfisonh")
    , eSC_handle("eSC")
    , phiSC_handle("phiSC")
    , eSCRaw_handle("eSCRaw")
    , eSCPresh_handle("eSCPresh")
    , lep1_scslasercormean_handle("lep1_scslasercormean")
    , lep1_scslasercormax_handle("lep1_scslasercormax")
    , eoverpin2_handle("eoverpin2")
    , eoverpout2_handle("eoverpout2")
    , dEtaIn2_handle("dEtaIn2")
    , dPhiIn2_handle("dPhiIn2")
    , sigmaIEtaIEta2_handle("sigmaIEtaIEta2")
    , hOverE2_handle("hOverE2")
    , ooemoop2_handle("ooemoop2")
    , d0vtx2_handle("d0vtx2")
    , dzvtx2_handle("dzvtx2")
    , expinnerlayers2_handle("expinnerlayers2")
    , fbrem2_handle("fbrem2")
    , pfisoch2_handle("pfisoch2")
    , pfisoem2_handle("pfisoem2")
    , pfisonh2_handle("pfisonh2")
    , eSC2_handle("eSC2")
    , phiSC2_handle("phiSC2")
    , eSCRaw2_handle("eSCRaw2")
    , eSCPresh2_handle("eSCPresh2")
    , lep2_scslasercormean_handle("lep2_scslasercormean")
    , lep2_scslasercormax_handle("lep2_scslasercormax")
    , scslasercormax_handle("scslasercormax")
    , scslasercormax_pt_handle("scslasercormax_pt")
    , scslasercormax_eta_handle("scslasercormax_eta")
    , iso2_handle("iso2")
    , ecalveto1_handle("ecalveto1")
    , ecalveto2_handle("ecalveto2")
    , hcalveto1_handle("hcalveto1")
    , hcalveto2_handle("hcalveto2")
    , isont2_handle("isont2")
    , isopf2_handle("isopf2")
    , ptl1_handle("ptl1")
    , ptl2_handle("ptl2")
    , etal1_handle("etal1")
    , etal2_handle("etal2")
    , phil1_handle("phil1")
    , phil2_handle("phil2")
    , meff_handle("meff")
    , mt_handle("mt")
    , dataset_handle("dataset")
    , run_handle("run")
    , lumi_handle("lumi")
    , event_handle("event")
    , y_handle("y")
    , ht_handle("ht")
    , htgen_handle("htgen")
    , htjpt_handle("htjpt")
    , nels_handle("nels")
    , nmus_handle("nmus")
    , ntaus_handle("ntaus")
    , nleps_handle("nleps")
    , nbs_handle("nbs")
    , dphijm_handle("dphijm")
    , ptjetraw_handle("ptjetraw")
    , ptjet23_handle("ptjet23")
    , ptjetF23_handle("ptjetF23")
    , ptjetO23_handle("ptjetO23")
    , mcid1_handle("mcid1")
    , mcdr1_handle("mcdr1")
    , mcdecay1_handle("mcdecay1")
    , mcndec1_handle("mcndec1")
    , mcndec2_handle("mcndec2")
    , mcndeckls1_handle("mcndeckls1")
    , mcndeckls2_handle("mcndeckls2")
    , mcndecem1_handle("mcndecem1")
    , mcndecem2_handle("mcndecem2")
    , mcid2_handle("mcid2")
    , mcdr2_handle("mcdr2")
    , mcdecay2_handle("mcdecay2")
    , mctaudpt1_handle("mctaudpt1")
    , mctaudpt2_handle("mctaudpt2")
    , mctaudid1_handle("mctaudid1")
    , mctaudid2_handle("mctaudid2")
    , mlepid_handle("mlepid")
    , mleppassid_handle("mleppassid")
    , mleppassiso_handle("mleppassiso")
    , mlepiso_handle("mlepiso")
    , mlepdr_handle("mlepdr")
    , pflepiso_handle("pflepiso")
    , pflepdr_handle("pflepdr")
    , pfleppt_handle("pfleppt")
    , pflepmindrj_handle("pflepmindrj")
    , pftaudiso_handle("pftaudiso")
    , pftauddr_handle("pftauddr")
    , pftaudpt_handle("pftaudpt")
    , pftaudmindrj_handle("pftaudmindrj")
    , pfcandid5_handle("pfcandid5")
    , pfcandiso5_handle("pfcandiso5")
    , pfcandpt5_handle("pfcandpt5")
    , pfcanddz5_handle("pfcanddz5")
    , pfcandmindrj5_handle("pfcandmindrj5")
    , pfcandid10_handle("pfcandid10")
    , pfcandiso10_handle("pfcandiso10")
    , pfcandpt10_handle("pfcandpt10")
    , pfcanddz10_handle("pfcanddz10")
    , pfcandmindrj10_handle("pfcandmindrj10")
    , pfcandidOS10_handle("pfcandidOS10")
    , pfcandisoOS10_handle("pfcandisoOS10")
    , pfcandptOS10_handle("pfcandptOS10")
    , pfcanddzOS10_handle("pfcanddzOS10")
    , pfcandid5looseZ_handle("pfcandid5looseZ")
    , pfcandiso5looseZ_handle("pfcandiso5looseZ")
    , pfcandpt5looseZ_handle("pfcandpt5looseZ")
    , pfcanddz5looseZ_handle("pfcanddz5looseZ")
    , pfcandidOS10looseZ_handle("pfcandidOS10looseZ")
    , pfcandisoOS10looseZ_handle("pfcandisoOS10looseZ")
    , pfcandptOS10looseZ_handle("pfcandptOS10looseZ")
    , pfcanddzOS10looseZ_handle("pfcanddzOS10looseZ")
    , pfcanddirid10_handle("pfcanddirid10")
    , pfcanddiriso10_handle("pfcanddiriso10")
    , pfcanddirpt10_handle("pfcanddirpt10")
    , pfcanddirmindrj10_handle("pfcanddirmindrj10")
    , pfcandvetoid10_handle("pfcandvetoid10")
    , pfcandvetoiso10_handle("pfcandvetoiso10")
    , pfcandvetopt10_handle("pfcandvetopt10")
    , pfcandvetomindrj10_handle("pfcandvetomindrj10")
    , pfcandvetoLid10_handle("pfcandvetoLid10")
    , pfcandvetoLiso10_handle("pfcandvetoLiso10")
    , pfcandvetoLpt10_handle("pfcandvetoLpt10")
    , pfcandvetoLmindrj10_handle("pfcandvetoLmindrj10")
    , emjet10_handle("emjet10")
    , mjj_handle("mjj")
    , emjet20_handle("emjet20")
    , trkpt5_handle("trkpt5")
    , trkpt10_handle("trkpt10")
    , mleptrk5_handle("mleptrk5")
    , mleptrk10_handle("mleptrk10")
    , trkreliso5_handle("trkreliso5")
    , trkreliso10_handle("trkreliso10")
    , trkpt5loose_handle("trkpt5loose")
    , trkpt10loose_handle("trkpt10loose")
    , trkreliso5loose_handle("trkreliso5loose")
    , trkreliso10loose_handle("trkreliso10loose")
    , trkpt10pt0p1_handle("trkpt10pt0p1")
    , trkpt10pt0p2_handle("trkpt10pt0p2")
    , trkpt10pt0p3_handle("trkpt10pt0p3")
    , trkpt10pt0p4_handle("trkpt10pt0p4")
    , trkpt10pt0p5_handle("trkpt10pt0p5")
    , trkpt10pt0p6_handle("trkpt10pt0p6")
    , trkpt10pt0p7_handle("trkpt10pt0p7")
    , trkpt10pt0p8_handle("trkpt10pt0p8")
    , trkpt10pt0p9_handle("trkpt10pt0p9")
    , trkpt10pt1p0_handle("trkpt10pt1p0")
    , trkreliso10pt0p1_handle("trkreliso10pt0p1")
    , trkreliso10pt0p2_handle("trkreliso10pt0p2")
    , trkreliso10pt0p3_handle("trkreliso10pt0p3")
    , trkreliso10pt0p4_handle("trkreliso10pt0p4")
    , trkreliso10pt0p5_handle("trkreliso10pt0p5")
    , trkreliso10pt0p6_handle("trkreliso10pt0p6")
    , trkreliso10pt0p7_handle("trkreliso10pt0p7")
    , trkreliso10pt0p8_handle("trkreliso10pt0p8")
    , trkreliso10pt0p9_handle("trkreliso10pt0p9")
    , trkreliso10pt1p0_handle("trkreliso10pt1p0")
    , pfcandpt10pt0p1_handle("pfcandpt10pt0p1")
    , pfcandpt10pt0p2_handle("pfcandpt10pt0p2")
    , pfcandpt10pt0p3_handle("pfcandpt10pt0p3")
    , pfcandpt10pt0p4_handle("pfcandpt10pt0p4")
    , pfcandpt10pt0p5_handle("pfcandpt10pt0p5")
    , pfcandpt10pt0p6_handle("pfcandpt10pt0p6")
    , pfcandpt10pt0p7_handle("pfcandpt10pt0p7")
    , pfcandpt10pt0p8_handle("pfcandpt10pt0p8")
    , pfcandpt10pt0p9_handle("pfcandpt10pt0p9")
    , pfcandpt10pt1p0_handle("pfcandpt10pt1p0")
    , pfcandiso10pt0p1_handle("pfcandiso10pt0p1")
    , pfcandiso10pt0p2_handle("pfcandiso10pt0p2")
    , pfcandiso10pt0p3_handle("pfcandiso10pt0p3")
    , pfcandiso10pt0p4_handle("pfcandiso10pt0p4")
    , pfcandiso10pt0p5_handle("pfcandiso10pt0p5")
    , pfcandiso10pt0p6_handle("pfcandiso10pt0p6")
    , pfcandiso10pt0p7_handle("pfcandiso10pt0p7")
    , pfcandiso10pt0p8_handle("pfcandiso10pt0p8")
    , pfcandiso10pt0p9_handle("pfcandiso10pt0p9")
    , pfcandiso10pt1p0_handle("pfcandiso10pt1p0")
    , mbb_handle("mbb")
    , lep1pfjetdr_handle("lep1pfjetdr")
    , lep2pfjetdr_handle("lep2pfjetdr")
    , mclep_handle("mclep")
    , mcnu_handle("mcnu")
    , mcmln_handle("mcmln")
    , mcmtln_handle("mcmtln")
    , mlep_handle("mlep")
    , lep1_handle("lep1")
    , lep2_handle("lep2")
    , trklep1_handle("trklep1")
    , trklep2_handle("trklep2")
    , gfitlep1_handle("gfitlep1")
    , gfitlep2_handle("gfitlep2")
    , lepp_handle("lepp")
    , lepm_handle("lepm")
    , pflep1_handle("pflep1")
    , pflep2_handle("pflep2")
    , leppfjet1_handle("leppfjet1")
    , leppfjet2_handle("leppfjet2")
    , mclep1_handle("mclep1")
    , mclep2_handle("mclep2")
    , mctaud1_handle("mctaud1")
    , mctaud2_handle("mctaud2")
    , mctaudvis1_handle("mctaudvis1")
    , mctaudvis2_handle("mctaudvis2")
    , pflep_handle("pflep")
    , pftaud_handle("pftaud")
    , pfcand5_handle("pfcand5")
    , pfcand10_handle("pfcand10")
    , pfTau15_leadPtcandID_handle("pfTau15_leadPtcandID")
    , pfTau15_handle("pfTau15")
    , pfTau15_leadPtcand_handle("pfTau15_leadPtcand")
    , pfTau_leadPtcandID_handle("pfTau_leadPtcandID")
    , pfTau_handle("pfTau")
    , pfTau_leadPtcand_handle("pfTau_leadPtcand")
    , pfTauLoose_leadPtcandID_handle("pfTauLoose_leadPtcandID")
    , pfTauLoose_handle("pfTauLoose")
    , pfTauLoose_leadPtcand_handle("pfTauLoose_leadPtcand")
    , pfcandOS10_handle("pfcandOS10")
    , pfcandOS10looseZ_handle("pfcandOS10looseZ")
    , pfcand5looseZ_handle("pfcand5looseZ")
    , pfcanddir10_handle("pfcanddir10")
    , pfcandveto10_handle("pfcandveto10")
    , pfcandvetoL10_handle("pfcandvetoL10")
    , jet_handle("jet")
    , nonisoel_handle("nonisoel")
    , nonisomu_handle("nonisomu")
    , t_handle("t")
    , tbar_handle("tbar")
    , ttbar_handle("ttbar")
    , lep_t_handle("lep_t")
    , lep_tbar_handle("lep_tbar")
    , stop_t_handle("stop_t")
    , stop_tbar_handle("stop_tbar")
    , neutralino_t_handle("neutralino_t")
    , neutralino_tbar_handle("neutralino_tbar")
    , lep_t_id_handle("lep_t_id")
    , lep_tbar_id_handle("lep_tbar_id")
    , pfjets_handle("pfjets")
    , pfjets_genJet__handle("pfjets_genJet_")
    , pfjets_csv_handle("pfjets_csv")
    , pfjets_chm_handle("pfjets_chm")
    , pfjets_neu_handle("pfjets_neu")
    , pfjets_l1corr_handle("pfjets_l1corr")
    , pfjets_corr_handle("pfjets_corr")
    , pfjets_mc3_handle("pfjets_mc3")
    , pfjets_mcflavorAlgo_handle("pfjets_mcflavorAlgo")
    , pfjets_mcflavorPhys_handle("pfjets_mcflavorPhys")
    , pfjets_uncertainty_handle("pfjets_uncertainty")
    , pfjets_flav_handle("pfjets_flav")
    , pfjets_lrm_handle("pfjets_lrm")
    , pfjets_lrm2_handle("pfjets_lrm2")
    , pfjets_qgtag_handle("pfjets_qgtag")
    , pfjets_genJetDr_handle("pfjets_genJetDr")
    , pfjets_sigma_handle("pfjets_sigma")
    , pfjets_lepjet_handle("pfjets_lepjet")
    , pfjets_beta_handle("pfjets_beta")
    , pfjets_beta2_handle("pfjets_beta2")
    , pfjets_beta_0p1_handle("pfjets_beta_0p1")
    , pfjets_beta_0p2_handle("pfjets_beta_0p2")
    , pfjets_beta2_0p1_handle("pfjets_beta2_0p1")
    , pfjets_beta2_0p5_handle("pfjets_beta2_0p5")
    , pfjets_mvaPUid_handle("pfjets_mvaPUid")
    , pfjets_mva5xPUid_handle("pfjets_mva5xPUid")
    , pfjets_mvaBeta_handle("pfjets_mvaBeta")
    , genbs_handle("genbs")
    , genps_pdgId_handle("genps_pdgId")
    , genps_firstMother_handle("genps_firstMother")
    , genps_energy_handle("genps_energy")
    , genps_pt_handle("genps_pt")
    , genps_eta_handle("genps_eta")
    , genps_phi_handle("genps_phi")
    , genps_mass_handle("genps_mass")
    , mini_mt_handle("mini_mt")
    , mini_mtup_handle("mini_mtup")
    , mini_mtdown_handle("mini_mtdown")
    , mini_isrweight_handle("mini_isrweight")
    , mini_met_handle("mini_met")
    , mini_metup_handle("mini_metup")
    , mini_metdown_handle("mini_metdown")
    , mini_sig_handle("mini_sig")
    , mini_cr1_handle("mini_cr1")
    , mini_cr4_handle("mini_cr4")
    , mini_cr5_handle("mini_cr5")
    , mini_whsig_handle("mini_whsig")
    , mini_whcr1_handle("mini_whcr1")
    , mini_chi2_handle("mini_chi2")
    , mini_chi2up_handle("mini_chi2up")
    , mini_chi2down_handle("mini_chi2down")
    , mini_chi2bup_handle("mini_chi2bup")
    , mini_chi2bdown_handle("mini_chi2bdown")
    , mini_mt2b_handle("mini_mt2b")
    , mini_mt2bl_handle("mini_mt2bl")
    , mini_mt2w_handle("mini_mt2w")
    , mini_mt2wup_handle("mini_mt2wup")
    , mini_mt2wdown_handle("mini_mt2wdown")
    , mini_mt2wbup_handle("mini_mt2wbup")
    , mini_mt2wbdown_handle("mini_mt2wbdown")
    , mini_weight_handle("mini_weight")
    , mini_nvtxweight_handle("mini_nvtxweight")
    , mini_sltrigeff_handle("mini_sltrigeff")
    , mini_dltrigeff_handle("mini_dltrigeff")
    , mini_nsigevents_handle("mini_nsigevents")
    , mini_nb_handle("mini_nb")
    , mini_nbupBC_handle("mini_nbupBC")
    , mini_nbdownBC_handle("mini_nbdownBC")
    , mini_nbupL_handle("mini_nbupL")
    , mini_nbdownL_handle("mini_nbdownL")
    , mini_njets_handle("mini_njets")
    , mini_njetsup_handle("mini_njetsup")
    , mini_njetsdown_handle("mini_njetsdown")
    , mini_passisotrk_handle("mini_passisotrk")
    , mini_passtauveto_handle("mini_passtauveto")
    , mini_nlep_handle("mini_nlep")
    , mini_lep1pt_handle("mini_lep1pt")
    , mini_lep1eta_handle("mini_lep1eta")
    , mini_lep2pt_handle("mini_lep2pt")
    , mini_lep2eta_handle("mini_lep2eta")
    , mini_dilmass_handle("mini_dilmass")
    , mini_mstop_handle("mini_mstop")
    , mini_mlsp_handle("mini_mlsp")
    , mini_x_handle("mini_x")
    , mini_xsecsusy_handle("mini_xsecsusy")
    , mini_dRleptB1_handle("mini_dRleptB1")
    , mini_dRleptB1_bup_handle("mini_dRleptB1_bup")
    , mini_dRleptB1_bdown_handle("mini_dRleptB1_bdown")
    , mini_htssl_handle("mini_htssl")
    , mini_htosl_handle("mini_htosl")
    , mini_htratiol_handle("mini_htratiol")
    , mini_htssm_handle("mini_htssm")
    , mini_htosm_handle("mini_htosm")
    , mini_htratiom_handle("mini_htratiom")
    , mini_htratiomup_handle("mini_htratiomup")
    , mini_htratiomdown_handle("mini_htratiomdown")
    , mini_dphimj1_handle("mini_dphimj1")
    , mini_dphimj2_handle("mini_dphimj2")
    , mini_dphimjmin_handle("mini_dphimjmin")
    , mini_pt_b_handle("mini_pt_b")
    , mini_pt_b_up_handle("mini_pt_b_up")
    , mini_pt_b_down_handle("mini_pt_b_down")
    , mini_pt_b_bup_handle("mini_pt_b_bup")
    , mini_pt_b_bdown_handle("mini_pt_b_bdown")
    , mini_pt_J1_handle("mini_pt_J1")
    , mini_pt_J2_handle("mini_pt_J2")
    , mini_bbmass_handle("mini_bbmass")
    , mini_bbpt_handle("mini_bbpt")
    , mini_wpt_handle("mini_wpt")
    , mini_bbwdphi_handle("mini_bbwdphi")
    , mini_rand_handle("mini_rand")
    , mini_t2ttLM_handle("mini_t2ttLM")
    , mini_t2ttHM_handle("mini_t2ttHM")
    , mini_bdt_handle("mini_bdt")
    , mini_bdtup_handle("mini_bdtup")
    , mini_bdtdown_handle("mini_bdtdown")
    , mini_bdtbup_handle("mini_bdtbup")
    , mini_bdtbdown_handle("mini_bdtbdown")
{
}

void STOP_BABY::Init(TTree& tree)
{
    acc_2010_handle.Init(tree);
    acc_highmet_handle.Init(tree);
    acc_highht_handle.Init(tree);
    eldup_handle.Init(tree);
    csc_handle.Init(tree);
    hbhe_handle.Init(tree);
    hbhenew_handle.Init(tree);
    hcallaser_handle.Init(tree);
    ecaltp_handle.Init(tree);
    trkfail_handle.Init(tree);
    eebadsc_handle.Init(tree);
    lep1_badecallaser_handle.Init(tree);
    lep2_badecallaser_handle.Init(tree);
    isdata_handle.Init(tree);
    jetid_handle.Init(tree);
    jetid30_handle.Init(tree);
    json_handle.Init(tree);
    htoffset_handle.Init(tree);
    htuncor_handle.Init(tree);
    ptt_handle.Init(tree);
    pttbar_handle.Init(tree);
    ptttbar_handle.Init(tree);
    mttbar_handle.Init(tree);
    npartons_handle.Init(tree);
    nwzpartons_handle.Init(tree);
    hyptype_handle.Init(tree);
    maxpartonpt_handle.Init(tree);
    etattbar_handle.Init(tree);
    njetsoffset_handle.Init(tree);
    njetsuncor_handle.Init(tree);
    costhetaweight_handle.Init(tree);
    weight_handle.Init(tree);
    weightleft_handle.Init(tree);
    weightright_handle.Init(tree);
    mutrigweight_handle.Init(tree);
    mutrigweight2_handle.Init(tree);
    sltrigweight_handle.Init(tree);
    dltrigweight_handle.Init(tree);
    trgeff_handle.Init(tree);
    pthat_handle.Init(tree);
    qscale_handle.Init(tree);
    mgcor_handle.Init(tree);
    wflav_handle.Init(tree);
    ksusy_handle.Init(tree);
    ksusyup_handle.Init(tree);
    ksusydn_handle.Init(tree);
    xsecsusy_handle.Init(tree);
    xsecsusy2_handle.Init(tree);
    smeff_handle.Init(tree);
    k_handle.Init(tree);
    mllgen_handle.Init(tree);
    ptwgen_handle.Init(tree);
    ptzgen_handle.Init(tree);
    nlep_handle.Init(tree);
    nosel_handle.Init(tree);
    ngoodlep_handle.Init(tree);
    ngoodel_handle.Init(tree);
    ngoodmu_handle.Init(tree);
    mull_handle.Init(tree);
    mult_handle.Init(tree);
    mullgen_handle.Init(tree);
    multgen_handle.Init(tree);
    proc_handle.Init(tree);
    leptype_handle.Init(tree);
    topmass_handle.Init(tree);
    dilmass_handle.Init(tree);
    dilrecoil_handle.Init(tree);
    dilrecoilparl_handle.Init(tree);
    dilrecoilperp_handle.Init(tree);
    tcmet_handle.Init(tree);
    genmet_handle.Init(tree);
    gensumet_handle.Init(tree);
    genmetphi_handle.Init(tree);
    calomet_handle.Init(tree);
    calometphi_handle.Init(tree);
    trkmet_handle.Init(tree);
    trkmetphi_handle.Init(tree);
    trkmet_nolepcorr_handle.Init(tree);
    trkmetphi_nolepcorr_handle.Init(tree);
    pfmet_handle.Init(tree);
    pfmetveto_handle.Init(tree);
    pfmetsig_handle.Init(tree);
    pfmetphi_handle.Init(tree);
    pfsumet_handle.Init(tree);
    mucormet_handle.Init(tree);
    mucorjesmet_handle.Init(tree);
    tcmet35X_handle.Init(tree);
    tcmetevent_handle.Init(tree);
    tcmetlooper_handle.Init(tree);
    tcmetphi_handle.Init(tree);
    tcsumet_handle.Init(tree);
    tcmetUp_handle.Init(tree);
    tcmetDown_handle.Init(tree);
    tcmetTest_handle.Init(tree);
    pfmetUp_handle.Init(tree);
    pfmetDown_handle.Init(tree);
    pfmetTest_handle.Init(tree);
    sumjetpt_handle.Init(tree);
    dileta_handle.Init(tree);
    dilpt_handle.Init(tree);
    dildphi_handle.Init(tree);
    ngenjets_handle.Init(tree);
    njpt_handle.Init(tree);
    trgmu1_handle.Init(tree);
    trgmu2_handle.Init(tree);
    trgel1_handle.Init(tree);
    trgel2_handle.Init(tree);
    isomu24_handle.Init(tree);
    ele27wp80_handle.Init(tree);
    mm_handle.Init(tree);
    mmtk_handle.Init(tree);
    me_handle.Init(tree);
    em_handle.Init(tree);
    mu_handle.Init(tree);
    ee_handle.Init(tree);
    npfjets30_handle.Init(tree);
    npfjets30lepcorr_handle.Init(tree);
    knjets_handle.Init(tree);
    rhovor_handle.Init(tree);
    htpf30_handle.Init(tree);
    t1met10_handle.Init(tree);
    t1met20_handle.Init(tree);
    t1met30_handle.Init(tree);
    t1met10phi_handle.Init(tree);
    t1met20phi_handle.Init(tree);
    t1met30phi_handle.Init(tree);
    t1met10mt_handle.Init(tree);
    t1met20mt_handle.Init(tree);
    t1met30mt_handle.Init(tree);
    lepmetpt_handle.Init(tree);
    lept1met10pt_handle.Init(tree);
    t1met10s_handle.Init(tree);
    t1met10sphi_handle.Init(tree);
    t1met10smt_handle.Init(tree);
    t1metphicorr_handle.Init(tree);
    t1metphicorrup_handle.Init(tree);
    t1metphicorrdn_handle.Init(tree);
    t1metphicorrphi_handle.Init(tree);
    t1metphicorrphiup_handle.Init(tree);
    t1metphicorrphidn_handle.Init(tree);
    t1metphicorrlep_handle.Init(tree);
    t1metphicorrlepphi_handle.Init(tree);
    t1metphicorrmt_handle.Init(tree);
    t1metphicorrmtup_handle.Init(tree);
    t1metphicorrmtdn_handle.Init(tree);
    t1metphicorrlepmt_handle.Init(tree);
    t1met_off_handle.Init(tree);
    t1metphi_off_handle.Init(tree);
    t1metmt_off_handle.Init(tree);
    t1metphicorr_off_handle.Init(tree);
    t1metphicorrphi_off_handle.Init(tree);
    t1metphicorrmt_off_handle.Init(tree);
    mt2bmin_handle.Init(tree);
    mt2blmin_handle.Init(tree);
    mt2wmin_handle.Init(tree);
    chi2min_handle.Init(tree);
    chi2minprob_handle.Init(tree);
    nbtagsssv_handle.Init(tree);
    nbtagstcl_handle.Init(tree);
    nbtagstcm_handle.Init(tree);
    nbtagscsvl_handle.Init(tree);
    nbtagscsvm_handle.Init(tree);
    nbtagscsvt_handle.Init(tree);
    nbtagsssvcorr_handle.Init(tree);
    nbtagstclcorr_handle.Init(tree);
    nbtagstcmcorr_handle.Init(tree);
    nbtagscsvlcorr_handle.Init(tree);
    nbtagscsvmcorr_handle.Init(tree);
    nbtagscsvtcott_handle.Init(tree);
    njetsUp_handle.Init(tree);
    njetsDown_handle.Init(tree);
    htUp_handle.Init(tree);
    htDown_handle.Init(tree);
    ntruepu_handle.Init(tree);
    npu_handle.Init(tree);
    npuMinusOne_handle.Init(tree);
    npuPlusOne_handle.Init(tree);
    nvtx_handle.Init(tree);
    indexfirstGoodVertex__handle.Init(tree);
    nvtxweight_handle.Init(tree);
    n3dvtxweight_handle.Init(tree);
    pdfid1_handle.Init(tree);
    pdfid2_handle.Init(tree);
    pdfx1_handle.Init(tree);
    pdfx2_handle.Init(tree);
    pdfQ_handle.Init(tree);
    vecjetpt_handle.Init(tree);
    pass_handle.Init(tree);
    passz_handle.Init(tree);
    m0_handle.Init(tree);
    mg_handle.Init(tree);
    ml_handle.Init(tree);
    x_handle.Init(tree);
    m12_handle.Init(tree);
    lep1chi2ndf_handle.Init(tree);
    lep2chi2ndf_handle.Init(tree);
    lep1dpt_handle.Init(tree);
    lep2dpt_handle.Init(tree);
    id1_handle.Init(tree);
    id2_handle.Init(tree);
    leptype1_handle.Init(tree);
    leptype2_handle.Init(tree);
    w1_handle.Init(tree);
    w2_handle.Init(tree);
    iso1_handle.Init(tree);
    isont1_handle.Init(tree);
    isopfold1_handle.Init(tree);
    isopf1_handle.Init(tree);
    etasc1_handle.Init(tree);
    etasc2_handle.Init(tree);
    eoverpin_handle.Init(tree);
    eoverpout_handle.Init(tree);
    dEtaIn_handle.Init(tree);
    dPhiIn_handle.Init(tree);
    sigmaIEtaIEta_handle.Init(tree);
    hOverE_handle.Init(tree);
    ooemoop_handle.Init(tree);
    d0vtx_handle.Init(tree);
    dzvtx_handle.Init(tree);
    expinnerlayers_handle.Init(tree);
    fbrem_handle.Init(tree);
    pfisoch_handle.Init(tree);
    pfisoem_handle.Init(tree);
    pfisonh_handle.Init(tree);
    eSC_handle.Init(tree);
    phiSC_handle.Init(tree);
    eSCRaw_handle.Init(tree);
    eSCPresh_handle.Init(tree);
    lep1_scslasercormean_handle.Init(tree);
    lep1_scslasercormax_handle.Init(tree);
    eoverpin2_handle.Init(tree);
    eoverpout2_handle.Init(tree);
    dEtaIn2_handle.Init(tree);
    dPhiIn2_handle.Init(tree);
    sigmaIEtaIEta2_handle.Init(tree);
    hOverE2_handle.Init(tree);
    ooemoop2_handle.Init(tree);
    d0vtx2_handle.Init(tree);
    dzvtx2_handle.Init(tree);
    expinnerlayers2_handle.Init(tree);
    fbrem2_handle.Init(tree);
    pfisoch2_handle.Init(tree);
    pfisoem2_handle.Init(tree);
    pfisonh2_handle.Init(tree);
    eSC2_handle.Init(tree);
    phiSC2_handle.Init(tree);
    eSCRaw2_handle.Init(tree);
    eSCPresh2_handle.Init(tree);
    lep2_scslasercormean_handle.Init(tree);
    lep2_scslasercormax_handle.Init(tree);
    scslasercormax_handle.Init(tree);
    scslasercormax_pt_handle.Init(tree);
    scslasercormax_eta_handle.Init(tree);
    iso2_handle.Init(tree);
    ecalveto1_handle.Init(tree);
    ecalveto2_handle.Init(tree);
    hcalveto1_handle.Init(tree);
    hcalveto2_handle.Init(tree);
    isont2_handle.Init(tree);
    isopf2_handle.Init(tree);
    ptl1_handle.Init(tree);
    ptl2_handle.Init(tree);
    etal1_handle.Init(tree);
    etal2_handle.Init(tree);
    phil1_handle.Init(tree);
    phil2_handle.Init(tree);
    meff_handle.Init(tree);
    mt_handle.Init(tree);
    dataset_handle.Init(tree);
    run_handle.Init(tree);
    lumi_handle.Init(tree);
    event_handle.Init(tree);
    y_handle.Init(tree);
    ht_handle.Init(tree);
    htgen_handle.Init(tree);
    htjpt_handle.Init(tree);
    nels_handle.Init(tree);
    nmus_handle.Init(tree);
    ntaus_handle.Init(tree);
    nleps_handle.Init(tree);
    nbs_handle.Init(tree);
    dphijm_handle.Init(tree);
    ptjetraw_handle.Init(tree);
    ptjet23_handle.Init(tree);
    ptjetF23_handle.Init(tree);
    ptjetO23_handle.Init(tree);
    mcid1_handle.Init(tree);
    mcdr1_handle.Init(tree);
    mcdecay1_handle.Init(tree);
    mcndec1_handle.Init(tree);
    mcndec2_handle.Init(tree);
    mcndeckls1_handle.Init(tree);
    mcndeckls2_handle.Init(tree);
    mcndecem1_handle.Init(tree);
    mcndecem2_handle.Init(tree);
    mcid2_handle.Init(tree);
    mcdr2_handle.Init(tree);
    mcdecay2_handle.Init(tree);
    mctaudpt1_handle.Init(tree);
    mctaudpt2_handle.Init(tree);
    mctaudid1_handle.Init(tree);
    mctaudid2_handle.Init(tree);
    mlepid_handle.Init(tree);
    mleppassid_handle.Init(tree);
    mleppassiso_handle.Init(tree);
    mlepiso_handle.Init(tree);
    mlepdr_handle.Init(tree);
    pflepiso_handle.Init(tree);
    pflepdr_handle.Init(tree);
    pfleppt_handle.Init(tree);
    pflepmindrj_handle.Init(tree);
    pftaudiso_handle.Init(tree);
    pftauddr_handle.Init(tree);
    pftaudpt_handle.Init(tree);
    pftaudmindrj_handle.Init(tree);
    pfcandid5_handle.Init(tree);
    pfcandiso5_handle.Init(tree);
    pfcandpt5_handle.Init(tree);
    pfcanddz5_handle.Init(tree);
    pfcandmindrj5_handle.Init(tree);
    pfcandid10_handle.Init(tree);
    pfcandiso10_handle.Init(tree);
    pfcandpt10_handle.Init(tree);
    pfcanddz10_handle.Init(tree);
    pfcandmindrj10_handle.Init(tree);
    pfcandidOS10_handle.Init(tree);
    pfcandisoOS10_handle.Init(tree);
    pfcandptOS10_handle.Init(tree);
    pfcanddzOS10_handle.Init(tree);
    pfcandid5looseZ_handle.Init(tree);
    pfcandiso5looseZ_handle.Init(tree);
    pfcandpt5looseZ_handle.Init(tree);
    pfcanddz5looseZ_handle.Init(tree);
    pfcandidOS10looseZ_handle.Init(tree);
    pfcandisoOS10looseZ_handle.Init(tree);
    pfcandptOS10looseZ_handle.Init(tree);
    pfcanddzOS10looseZ_handle.Init(tree);
    pfcanddirid10_handle.Init(tree);
    pfcanddiriso10_handle.Init(tree);
    pfcanddirpt10_handle.Init(tree);
    pfcanddirmindrj10_handle.Init(tree);
    pfcandvetoid10_handle.Init(tree);
    pfcandvetoiso10_handle.Init(tree);
    pfcandvetopt10_handle.Init(tree);
    pfcandvetomindrj10_handle.Init(tree);
    pfcandvetoLid10_handle.Init(tree);
    pfcandvetoLiso10_handle.Init(tree);
    pfcandvetoLpt10_handle.Init(tree);
    pfcandvetoLmindrj10_handle.Init(tree);
    emjet10_handle.Init(tree);
    mjj_handle.Init(tree);
    emjet20_handle.Init(tree);
    trkpt5_handle.Init(tree);
    trkpt10_handle.Init(tree);
    mleptrk5_handle.Init(tree);
    mleptrk10_handle.Init(tree);
    trkreliso5_handle.Init(tree);
    trkreliso10_handle.Init(tree);
    trkpt5loose_handle.Init(tree);
    trkpt10loose_handle.Init(tree);
    trkreliso5loose_handle.Init(tree);
    trkreliso10loose_handle.Init(tree);
    trkpt10pt0p1_handle.Init(tree);
    trkpt10pt0p2_handle.Init(tree);
    trkpt10pt0p3_handle.Init(tree);
    trkpt10pt0p4_handle.Init(tree);
    trkpt10pt0p5_handle.Init(tree);
    trkpt10pt0p6_handle.Init(tree);
    trkpt10pt0p7_handle.Init(tree);
    trkpt10pt0p8_handle.Init(tree);
    trkpt10pt0p9_handle.Init(tree);
    trkpt10pt1p0_handle.Init(tree);
    trkreliso10pt0p1_handle.Init(tree);
    trkreliso10pt0p2_handle.Init(tree);
    trkreliso10pt0p3_handle.Init(tree);
    trkreliso10pt0p4_handle.Init(tree);
    trkreliso10pt0p5_handle.Init(tree);
    trkreliso10pt0p6_handle.Init(tree);
    trkreliso10pt0p7_handle.Init(tree);
    trkreliso10pt0p8_handle.Init(tree);
    trkreliso10pt0p9_handle.Init(tree);
    trkreliso10pt1p0_handle.Init(tree);
    pfcandpt10pt0p1_handle.Init(tree);
    pfcandpt10pt0p2_handle.Init(tree);
    pfcandpt10pt0p3_handle.Init(tree);
    pfcandpt10pt0p4_handle.Init(tree);
    pfcandpt10pt0p5_handle.Init(tree);
    pfcandpt10pt0p6_handle.Init(tree);
    pfcandpt10pt0p7_handle.Init(tree);
    pfcandpt10pt0p8_handle.Init(tree);
    pfcandpt10pt0p9_handle.Init(tree);
    pfcandpt10pt1p0_handle.Init(tree);
    pfcandiso10pt0p1_handle.Init(tree);
    pfcandiso10pt0p2_handle.Init(tree);
    pfcandiso10pt0p3_handle.Init(tree);
    pfcandiso10pt0p4_handle.Init(tree);
    pfcandiso10pt0p5_handle.Init(tree);
    pfcandiso10pt0p6_handle.Init(tree);
    pfcandiso10pt0p7_handle.Init(tree);
    pfcandiso10pt0p8_handle.Init(tree);
    pfcandiso10pt0p9_handle.Init(tree);
    pfcandiso10pt1p0_handle.Init(tree);
    mbb_handle.Init(tree);
    lep1pfjetdr_handle.Init(tree);
    lep2pfjetdr_handle.Init(tree);
    mclep_handle.Init(tree);
    mcnu_handle.Init(tree);
    mcmln_handle.Init(tree);
    mcmtln_handle.Init(tree);
    mlep_handle.Init(tree);
    lep1_handle.Init(tree);
    lep2_handle.Init(tree);
    trklep1_handle.Init(tree);
    trklep2_handle.Init(tree);
    gfitlep1_handle.Init(tree);
    gfitlep2_handle.Init(tree);
    lepp_handle.Init(tree);
    lepm_handle.Init(tree);
    pflep1_handle.Init(tree);
    pflep2_handle.Init(tree);
    leppfjet1_handle.Init(tree);
    leppfjet2_handle.Init(tree);
    mclep1_handle.Init(tree);
    mclep2_handle.Init(tree);
    mctaud1_handle.Init(tree);
    mctaud2_handle.Init(tree);
    mctaudvis1_handle.Init(tree);
    mctaudvis2_handle.Init(tree);
    pflep_handle.Init(tree);
    pftaud_handle.Init(tree);
    pfcand5_handle.Init(tree);
    pfcand10_handle.Init(tree);
    pfTau15_leadPtcandID_handle.Init(tree);
    pfTau15_handle.Init(tree);
    pfTau15_leadPtcand_handle.Init(tree);
    pfTau_leadPtcandID_handle.Init(tree);
    pfTau_handle.Init(tree);
    pfTau_leadPtcand_handle.Init(tree);
    pfTauLoose_leadPtcandID_handle.Init(tree);
    pfTauLoose_handle.Init(tree);
    pfTauLoose_leadPtcand_handle.Init(tree);
    pfcandOS10_handle.Init(tree);
    pfcandOS10looseZ_handle.Init(tree);
    pfcand5looseZ_handle.Init(tree);
    pfcanddir10_handle.Init(tree);
    pfcandveto10_handle.Init(tree);
    pfcandvetoL10_handle.Init(tree);
    jet_handle.Init(tree);
    nonisoel_handle.Init(tree);
    nonisomu_handle.Init(tree);
    t_handle.Init(tree);
    tbar_handle.Init(tree);
    ttbar_handle.Init(tree);
    lep_t_handle.Init(tree);
    lep_tbar_handle.Init(tree);
    stop_t_handle.Init(tree);
    stop_tbar_handle.Init(tree);
    neutralino_t_handle.Init(tree);
    neutralino_tbar_handle.Init(tree);
    lep_t_id_handle.Init(tree);
    lep_tbar_id_handle.Init(tree);
    pfjets_handle.Init(tree);
    pfjets_genJet__handle.Init(tree);
    pfjets_csv_handle.Init(tree);
    pfjets_chm_handle.Init(tree);
    pfjets_neu_handle.Init(tree);
    pfjets_l1corr_handle.Init(tree);
    pfjets_corr_handle.Init(tree);
    pfjets_mc3_handle.Init(tree);
    pfjets_mcflavorAlgo_handle.Init(tree);
    pfjets_mcflavorPhys_handle.Init(tree);
    pfjets_uncertainty_handle.Init(tree);
    pfjets_flav_handle.Init(tree);
    pfjets_lrm_handle.Init(tree);
    pfjets_lrm2_handle.Init(tree);
    pfjets_qgtag_handle.Init(tree);
    pfjets_genJetDr_handle.Init(tree);
    pfjets_sigma_handle.Init(tree);
    pfjets_lepjet_handle.Init(tree);
    pfjets_beta_handle.Init(tree);
    pfjets_beta2_handle.Init(tree);
    pfjets_beta_0p1_handle.Init(tree);
    pfjets_beta_0p2_handle.Init(tree);
    pfjets_beta2_0p1_handle.Init(tree);
    pfjets_beta2_0p5_handle.Init(tree);
    pfjets_mvaPUid_handle.Init(tree);
    pfjets_mva5xPUid_handle.Init(tree);
    pfjets_mvaBeta_handle.Init(tree);
    genbs_handle.Init(tree);
    genps_pdgId_handle.Init(tree);
    genps_firstMother_handle.Init(tree);
    genps_energy_handle.Init(tree);
    genps_pt_handle.Init(tree);
    genps_eta_handle.Init(tree);
    genps_phi_handle.Init(tree);
    genps_mass_handle.Init(tree);
    mini_mt_handle.Init(tree);
    mini_mtup_handle.Init(tree);
    mini_mtdown_handle.Init(tree);
    mini_isrweight_handle.Init(tree);
    mini_met_handle.Init(tree);
    mini_metup_handle.Init(tree);
    mini_metdown_handle.Init(tree);
    mini_sig_handle.Init(tree);
    mini_cr1_handle.Init(tree);
    mini_cr4_handle.Init(tree);
    mini_cr5_handle.Init(tree);
    mini_whsig_handle.Init(tree);
    mini_whcr1_handle.Init(tree);
    mini_chi2_handle.Init(tree);
    mini_chi2up_handle.Init(tree);
    mini_chi2down_handle.Init(tree);
    mini_chi2bup_handle.Init(tree);
    mini_chi2bdown_handle.Init(tree);
    mini_mt2b_handle.Init(tree);
    mini_mt2bl_handle.Init(tree);
    mini_mt2w_handle.Init(tree);
    mini_mt2wup_handle.Init(tree);
    mini_mt2wdown_handle.Init(tree);
    mini_mt2wbup_handle.Init(tree);
    mini_mt2wbdown_handle.Init(tree);
    mini_weight_handle.Init(tree);
    mini_nvtxweight_handle.Init(tree);
    mini_sltrigeff_handle.Init(tree);
    mini_dltrigeff_handle.Init(tree);
    mini_nsigevents_handle.Init(tree);
    mini_nb_handle.Init(tree);
    mini_nbupBC_handle.Init(tree);
    mini_nbdownBC_handle.Init(tree);
    mini_nbupL_handle.Init(tree);
    mini_nbdownL_handle.Init(tree);
    mini_njets_handle.Init(tree);
    mini_njetsup_handle.Init(tree);
    mini_njetsdown_handle.Init(tree);
    mini_passisotrk_handle.Init(tree);
    mini_passtauveto_handle.Init(tree);
    mini_nlep_handle.Init(tree);
    mini_lep1pt_handle.Init(tree);
    mini_lep1eta_handle.Init(tree);
    mini_lep2pt_handle.Init(tree);
    mini_lep2eta_handle.Init(tree);
    mini_dilmass_handle.Init(tree);
    mini_mstop_handle.Init(tree);
    mini_mlsp_handle.Init(tree);
    mini_x_handle.Init(tree);
    mini_xsecsusy_handle.Init(tree);
    mini_dRleptB1_handle.Init(tree);
    mini_dRleptB1_bup_handle.Init(tree);
    mini_dRleptB1_bdown_handle.Init(tree);
    mini_htssl_handle.Init(tree);
    mini_htosl_handle.Init(tree);
    mini_htratiol_handle.Init(tree);
    mini_htssm_handle.Init(tree);
    mini_htosm_handle.Init(tree);
    mini_htratiom_handle.Init(tree);
    mini_htratiomup_handle.Init(tree);
    mini_htratiomdown_handle.Init(tree);
    mini_dphimj1_handle.Init(tree);
    mini_dphimj2_handle.Init(tree);
    mini_dphimjmin_handle.Init(tree);
    mini_pt_b_handle.Init(tree);
    mini_pt_b_up_handle.Init(tree);
    mini_pt_b_down_handle.Init(tree);
    mini_pt_b_bup_handle.Init(tree);
    mini_pt_b_bdown_handle.Init(tree);
    mini_pt_J1_handle.Init(tree);
    mini_pt_J2_handle.Init(tree);
    mini_bbmass_handle.Init(tree);
    mini_bbpt_handle.Init(tree);
    mini_wpt_handle.Init(tree);
    mini_bbwdphi_handle.Init(tree);
    mini_rand_handle.Init(tree);
    mini_t2ttLM_handle.Init(tree);
    mini_t2ttHM_handle.Init(tree);
    mini_bdt_handle.Init(tree);
    mini_bdtup_handle.Init(tree);
    mini_bdtdown_handle.Init(tree);
    mini_bdtbup_handle.Init(tree);
    mini_bdtbdown_handle.Init(tree);

}

void STOP_BABY::Init(TTree* const tree)
{
    Init(*tree);
}

void STOP_BABY::GetEntry(const unsigned int entry)
{
    acc_2010_handle.GetEntry(entry);
    acc_highmet_handle.GetEntry(entry);
    acc_highht_handle.GetEntry(entry);
    eldup_handle.GetEntry(entry);
    csc_handle.GetEntry(entry);
    hbhe_handle.GetEntry(entry);
    hbhenew_handle.GetEntry(entry);
    hcallaser_handle.GetEntry(entry);
    ecaltp_handle.GetEntry(entry);
    trkfail_handle.GetEntry(entry);
    eebadsc_handle.GetEntry(entry);
    lep1_badecallaser_handle.GetEntry(entry);
    lep2_badecallaser_handle.GetEntry(entry);
    isdata_handle.GetEntry(entry);
    jetid_handle.GetEntry(entry);
    jetid30_handle.GetEntry(entry);
    json_handle.GetEntry(entry);
    htoffset_handle.GetEntry(entry);
    htuncor_handle.GetEntry(entry);
    ptt_handle.GetEntry(entry);
    pttbar_handle.GetEntry(entry);
    ptttbar_handle.GetEntry(entry);
    mttbar_handle.GetEntry(entry);
    npartons_handle.GetEntry(entry);
    nwzpartons_handle.GetEntry(entry);
    hyptype_handle.GetEntry(entry);
    maxpartonpt_handle.GetEntry(entry);
    etattbar_handle.GetEntry(entry);
    njetsoffset_handle.GetEntry(entry);
    njetsuncor_handle.GetEntry(entry);
    costhetaweight_handle.GetEntry(entry);
    weight_handle.GetEntry(entry);
    weightleft_handle.GetEntry(entry);
    weightright_handle.GetEntry(entry);
    mutrigweight_handle.GetEntry(entry);
    mutrigweight2_handle.GetEntry(entry);
    sltrigweight_handle.GetEntry(entry);
    dltrigweight_handle.GetEntry(entry);
    trgeff_handle.GetEntry(entry);
    pthat_handle.GetEntry(entry);
    qscale_handle.GetEntry(entry);
    mgcor_handle.GetEntry(entry);
    wflav_handle.GetEntry(entry);
    ksusy_handle.GetEntry(entry);
    ksusyup_handle.GetEntry(entry);
    ksusydn_handle.GetEntry(entry);
    xsecsusy_handle.GetEntry(entry);
    xsecsusy2_handle.GetEntry(entry);
    smeff_handle.GetEntry(entry);
    k_handle.GetEntry(entry);
    mllgen_handle.GetEntry(entry);
    ptwgen_handle.GetEntry(entry);
    ptzgen_handle.GetEntry(entry);
    nlep_handle.GetEntry(entry);
    nosel_handle.GetEntry(entry);
    ngoodlep_handle.GetEntry(entry);
    ngoodel_handle.GetEntry(entry);
    ngoodmu_handle.GetEntry(entry);
    mull_handle.GetEntry(entry);
    mult_handle.GetEntry(entry);
    mullgen_handle.GetEntry(entry);
    multgen_handle.GetEntry(entry);
    proc_handle.GetEntry(entry);
    leptype_handle.GetEntry(entry);
    topmass_handle.GetEntry(entry);
    dilmass_handle.GetEntry(entry);
    dilrecoil_handle.GetEntry(entry);
    dilrecoilparl_handle.GetEntry(entry);
    dilrecoilperp_handle.GetEntry(entry);
    tcmet_handle.GetEntry(entry);
    genmet_handle.GetEntry(entry);
    gensumet_handle.GetEntry(entry);
    genmetphi_handle.GetEntry(entry);
    calomet_handle.GetEntry(entry);
    calometphi_handle.GetEntry(entry);
    trkmet_handle.GetEntry(entry);
    trkmetphi_handle.GetEntry(entry);
    trkmet_nolepcorr_handle.GetEntry(entry);
    trkmetphi_nolepcorr_handle.GetEntry(entry);
    pfmet_handle.GetEntry(entry);
    pfmetveto_handle.GetEntry(entry);
    pfmetsig_handle.GetEntry(entry);
    pfmetphi_handle.GetEntry(entry);
    pfsumet_handle.GetEntry(entry);
    mucormet_handle.GetEntry(entry);
    mucorjesmet_handle.GetEntry(entry);
    tcmet35X_handle.GetEntry(entry);
    tcmetevent_handle.GetEntry(entry);
    tcmetlooper_handle.GetEntry(entry);
    tcmetphi_handle.GetEntry(entry);
    tcsumet_handle.GetEntry(entry);
    tcmetUp_handle.GetEntry(entry);
    tcmetDown_handle.GetEntry(entry);
    tcmetTest_handle.GetEntry(entry);
    pfmetUp_handle.GetEntry(entry);
    pfmetDown_handle.GetEntry(entry);
    pfmetTest_handle.GetEntry(entry);
    sumjetpt_handle.GetEntry(entry);
    dileta_handle.GetEntry(entry);
    dilpt_handle.GetEntry(entry);
    dildphi_handle.GetEntry(entry);
    ngenjets_handle.GetEntry(entry);
    njpt_handle.GetEntry(entry);
    trgmu1_handle.GetEntry(entry);
    trgmu2_handle.GetEntry(entry);
    trgel1_handle.GetEntry(entry);
    trgel2_handle.GetEntry(entry);
    isomu24_handle.GetEntry(entry);
    ele27wp80_handle.GetEntry(entry);
    mm_handle.GetEntry(entry);
    mmtk_handle.GetEntry(entry);
    me_handle.GetEntry(entry);
    em_handle.GetEntry(entry);
    mu_handle.GetEntry(entry);
    ee_handle.GetEntry(entry);
    npfjets30_handle.GetEntry(entry);
    npfjets30lepcorr_handle.GetEntry(entry);
    knjets_handle.GetEntry(entry);
    rhovor_handle.GetEntry(entry);
    htpf30_handle.GetEntry(entry);
    t1met10_handle.GetEntry(entry);
    t1met20_handle.GetEntry(entry);
    t1met30_handle.GetEntry(entry);
    t1met10phi_handle.GetEntry(entry);
    t1met20phi_handle.GetEntry(entry);
    t1met30phi_handle.GetEntry(entry);
    t1met10mt_handle.GetEntry(entry);
    t1met20mt_handle.GetEntry(entry);
    t1met30mt_handle.GetEntry(entry);
    lepmetpt_handle.GetEntry(entry);
    lept1met10pt_handle.GetEntry(entry);
    t1met10s_handle.GetEntry(entry);
    t1met10sphi_handle.GetEntry(entry);
    t1met10smt_handle.GetEntry(entry);
    t1metphicorr_handle.GetEntry(entry);
    t1metphicorrup_handle.GetEntry(entry);
    t1metphicorrdn_handle.GetEntry(entry);
    t1metphicorrphi_handle.GetEntry(entry);
    t1metphicorrphiup_handle.GetEntry(entry);
    t1metphicorrphidn_handle.GetEntry(entry);
    t1metphicorrlep_handle.GetEntry(entry);
    t1metphicorrlepphi_handle.GetEntry(entry);
    t1metphicorrmt_handle.GetEntry(entry);
    t1metphicorrmtup_handle.GetEntry(entry);
    t1metphicorrmtdn_handle.GetEntry(entry);
    t1metphicorrlepmt_handle.GetEntry(entry);
    t1met_off_handle.GetEntry(entry);
    t1metphi_off_handle.GetEntry(entry);
    t1metmt_off_handle.GetEntry(entry);
    t1metphicorr_off_handle.GetEntry(entry);
    t1metphicorrphi_off_handle.GetEntry(entry);
    t1metphicorrmt_off_handle.GetEntry(entry);
    mt2bmin_handle.GetEntry(entry);
    mt2blmin_handle.GetEntry(entry);
    mt2wmin_handle.GetEntry(entry);
    chi2min_handle.GetEntry(entry);
    chi2minprob_handle.GetEntry(entry);
    nbtagsssv_handle.GetEntry(entry);
    nbtagstcl_handle.GetEntry(entry);
    nbtagstcm_handle.GetEntry(entry);
    nbtagscsvl_handle.GetEntry(entry);
    nbtagscsvm_handle.GetEntry(entry);
    nbtagscsvt_handle.GetEntry(entry);
    nbtagsssvcorr_handle.GetEntry(entry);
    nbtagstclcorr_handle.GetEntry(entry);
    nbtagstcmcorr_handle.GetEntry(entry);
    nbtagscsvlcorr_handle.GetEntry(entry);
    nbtagscsvmcorr_handle.GetEntry(entry);
    nbtagscsvtcott_handle.GetEntry(entry);
    njetsUp_handle.GetEntry(entry);
    njetsDown_handle.GetEntry(entry);
    htUp_handle.GetEntry(entry);
    htDown_handle.GetEntry(entry);
    ntruepu_handle.GetEntry(entry);
    npu_handle.GetEntry(entry);
    npuMinusOne_handle.GetEntry(entry);
    npuPlusOne_handle.GetEntry(entry);
    nvtx_handle.GetEntry(entry);
    indexfirstGoodVertex__handle.GetEntry(entry);
    nvtxweight_handle.GetEntry(entry);
    n3dvtxweight_handle.GetEntry(entry);
    pdfid1_handle.GetEntry(entry);
    pdfid2_handle.GetEntry(entry);
    pdfx1_handle.GetEntry(entry);
    pdfx2_handle.GetEntry(entry);
    pdfQ_handle.GetEntry(entry);
    vecjetpt_handle.GetEntry(entry);
    pass_handle.GetEntry(entry);
    passz_handle.GetEntry(entry);
    m0_handle.GetEntry(entry);
    mg_handle.GetEntry(entry);
    ml_handle.GetEntry(entry);
    x_handle.GetEntry(entry);
    m12_handle.GetEntry(entry);
    lep1chi2ndf_handle.GetEntry(entry);
    lep2chi2ndf_handle.GetEntry(entry);
    lep1dpt_handle.GetEntry(entry);
    lep2dpt_handle.GetEntry(entry);
    id1_handle.GetEntry(entry);
    id2_handle.GetEntry(entry);
    leptype1_handle.GetEntry(entry);
    leptype2_handle.GetEntry(entry);
    w1_handle.GetEntry(entry);
    w2_handle.GetEntry(entry);
    iso1_handle.GetEntry(entry);
    isont1_handle.GetEntry(entry);
    isopfold1_handle.GetEntry(entry);
    isopf1_handle.GetEntry(entry);
    etasc1_handle.GetEntry(entry);
    etasc2_handle.GetEntry(entry);
    eoverpin_handle.GetEntry(entry);
    eoverpout_handle.GetEntry(entry);
    dEtaIn_handle.GetEntry(entry);
    dPhiIn_handle.GetEntry(entry);
    sigmaIEtaIEta_handle.GetEntry(entry);
    hOverE_handle.GetEntry(entry);
    ooemoop_handle.GetEntry(entry);
    d0vtx_handle.GetEntry(entry);
    dzvtx_handle.GetEntry(entry);
    expinnerlayers_handle.GetEntry(entry);
    fbrem_handle.GetEntry(entry);
    pfisoch_handle.GetEntry(entry);
    pfisoem_handle.GetEntry(entry);
    pfisonh_handle.GetEntry(entry);
    eSC_handle.GetEntry(entry);
    phiSC_handle.GetEntry(entry);
    eSCRaw_handle.GetEntry(entry);
    eSCPresh_handle.GetEntry(entry);
    lep1_scslasercormean_handle.GetEntry(entry);
    lep1_scslasercormax_handle.GetEntry(entry);
    eoverpin2_handle.GetEntry(entry);
    eoverpout2_handle.GetEntry(entry);
    dEtaIn2_handle.GetEntry(entry);
    dPhiIn2_handle.GetEntry(entry);
    sigmaIEtaIEta2_handle.GetEntry(entry);
    hOverE2_handle.GetEntry(entry);
    ooemoop2_handle.GetEntry(entry);
    d0vtx2_handle.GetEntry(entry);
    dzvtx2_handle.GetEntry(entry);
    expinnerlayers2_handle.GetEntry(entry);
    fbrem2_handle.GetEntry(entry);
    pfisoch2_handle.GetEntry(entry);
    pfisoem2_handle.GetEntry(entry);
    pfisonh2_handle.GetEntry(entry);
    eSC2_handle.GetEntry(entry);
    phiSC2_handle.GetEntry(entry);
    eSCRaw2_handle.GetEntry(entry);
    eSCPresh2_handle.GetEntry(entry);
    lep2_scslasercormean_handle.GetEntry(entry);
    lep2_scslasercormax_handle.GetEntry(entry);
    scslasercormax_handle.GetEntry(entry);
    scslasercormax_pt_handle.GetEntry(entry);
    scslasercormax_eta_handle.GetEntry(entry);
    iso2_handle.GetEntry(entry);
    ecalveto1_handle.GetEntry(entry);
    ecalveto2_handle.GetEntry(entry);
    hcalveto1_handle.GetEntry(entry);
    hcalveto2_handle.GetEntry(entry);
    isont2_handle.GetEntry(entry);
    isopf2_handle.GetEntry(entry);
    ptl1_handle.GetEntry(entry);
    ptl2_handle.GetEntry(entry);
    etal1_handle.GetEntry(entry);
    etal2_handle.GetEntry(entry);
    phil1_handle.GetEntry(entry);
    phil2_handle.GetEntry(entry);
    meff_handle.GetEntry(entry);
    mt_handle.GetEntry(entry);
    dataset_handle.GetEntry(entry);
    run_handle.GetEntry(entry);
    lumi_handle.GetEntry(entry);
    event_handle.GetEntry(entry);
    y_handle.GetEntry(entry);
    ht_handle.GetEntry(entry);
    htgen_handle.GetEntry(entry);
    htjpt_handle.GetEntry(entry);
    nels_handle.GetEntry(entry);
    nmus_handle.GetEntry(entry);
    ntaus_handle.GetEntry(entry);
    nleps_handle.GetEntry(entry);
    nbs_handle.GetEntry(entry);
    dphijm_handle.GetEntry(entry);
    ptjetraw_handle.GetEntry(entry);
    ptjet23_handle.GetEntry(entry);
    ptjetF23_handle.GetEntry(entry);
    ptjetO23_handle.GetEntry(entry);
    mcid1_handle.GetEntry(entry);
    mcdr1_handle.GetEntry(entry);
    mcdecay1_handle.GetEntry(entry);
    mcndec1_handle.GetEntry(entry);
    mcndec2_handle.GetEntry(entry);
    mcndeckls1_handle.GetEntry(entry);
    mcndeckls2_handle.GetEntry(entry);
    mcndecem1_handle.GetEntry(entry);
    mcndecem2_handle.GetEntry(entry);
    mcid2_handle.GetEntry(entry);
    mcdr2_handle.GetEntry(entry);
    mcdecay2_handle.GetEntry(entry);
    mctaudpt1_handle.GetEntry(entry);
    mctaudpt2_handle.GetEntry(entry);
    mctaudid1_handle.GetEntry(entry);
    mctaudid2_handle.GetEntry(entry);
    mlepid_handle.GetEntry(entry);
    mleppassid_handle.GetEntry(entry);
    mleppassiso_handle.GetEntry(entry);
    mlepiso_handle.GetEntry(entry);
    mlepdr_handle.GetEntry(entry);
    pflepiso_handle.GetEntry(entry);
    pflepdr_handle.GetEntry(entry);
    pfleppt_handle.GetEntry(entry);
    pflepmindrj_handle.GetEntry(entry);
    pftaudiso_handle.GetEntry(entry);
    pftauddr_handle.GetEntry(entry);
    pftaudpt_handle.GetEntry(entry);
    pftaudmindrj_handle.GetEntry(entry);
    pfcandid5_handle.GetEntry(entry);
    pfcandiso5_handle.GetEntry(entry);
    pfcandpt5_handle.GetEntry(entry);
    pfcanddz5_handle.GetEntry(entry);
    pfcandmindrj5_handle.GetEntry(entry);
    pfcandid10_handle.GetEntry(entry);
    pfcandiso10_handle.GetEntry(entry);
    pfcandpt10_handle.GetEntry(entry);
    pfcanddz10_handle.GetEntry(entry);
    pfcandmindrj10_handle.GetEntry(entry);
    pfcandidOS10_handle.GetEntry(entry);
    pfcandisoOS10_handle.GetEntry(entry);
    pfcandptOS10_handle.GetEntry(entry);
    pfcanddzOS10_handle.GetEntry(entry);
    pfcandid5looseZ_handle.GetEntry(entry);
    pfcandiso5looseZ_handle.GetEntry(entry);
    pfcandpt5looseZ_handle.GetEntry(entry);
    pfcanddz5looseZ_handle.GetEntry(entry);
    pfcandidOS10looseZ_handle.GetEntry(entry);
    pfcandisoOS10looseZ_handle.GetEntry(entry);
    pfcandptOS10looseZ_handle.GetEntry(entry);
    pfcanddzOS10looseZ_handle.GetEntry(entry);
    pfcanddirid10_handle.GetEntry(entry);
    pfcanddiriso10_handle.GetEntry(entry);
    pfcanddirpt10_handle.GetEntry(entry);
    pfcanddirmindrj10_handle.GetEntry(entry);
    pfcandvetoid10_handle.GetEntry(entry);
    pfcandvetoiso10_handle.GetEntry(entry);
    pfcandvetopt10_handle.GetEntry(entry);
    pfcandvetomindrj10_handle.GetEntry(entry);
    pfcandvetoLid10_handle.GetEntry(entry);
    pfcandvetoLiso10_handle.GetEntry(entry);
    pfcandvetoLpt10_handle.GetEntry(entry);
    pfcandvetoLmindrj10_handle.GetEntry(entry);
    emjet10_handle.GetEntry(entry);
    mjj_handle.GetEntry(entry);
    emjet20_handle.GetEntry(entry);
    trkpt5_handle.GetEntry(entry);
    trkpt10_handle.GetEntry(entry);
    mleptrk5_handle.GetEntry(entry);
    mleptrk10_handle.GetEntry(entry);
    trkreliso5_handle.GetEntry(entry);
    trkreliso10_handle.GetEntry(entry);
    trkpt5loose_handle.GetEntry(entry);
    trkpt10loose_handle.GetEntry(entry);
    trkreliso5loose_handle.GetEntry(entry);
    trkreliso10loose_handle.GetEntry(entry);
    trkpt10pt0p1_handle.GetEntry(entry);
    trkpt10pt0p2_handle.GetEntry(entry);
    trkpt10pt0p3_handle.GetEntry(entry);
    trkpt10pt0p4_handle.GetEntry(entry);
    trkpt10pt0p5_handle.GetEntry(entry);
    trkpt10pt0p6_handle.GetEntry(entry);
    trkpt10pt0p7_handle.GetEntry(entry);
    trkpt10pt0p8_handle.GetEntry(entry);
    trkpt10pt0p9_handle.GetEntry(entry);
    trkpt10pt1p0_handle.GetEntry(entry);
    trkreliso10pt0p1_handle.GetEntry(entry);
    trkreliso10pt0p2_handle.GetEntry(entry);
    trkreliso10pt0p3_handle.GetEntry(entry);
    trkreliso10pt0p4_handle.GetEntry(entry);
    trkreliso10pt0p5_handle.GetEntry(entry);
    trkreliso10pt0p6_handle.GetEntry(entry);
    trkreliso10pt0p7_handle.GetEntry(entry);
    trkreliso10pt0p8_handle.GetEntry(entry);
    trkreliso10pt0p9_handle.GetEntry(entry);
    trkreliso10pt1p0_handle.GetEntry(entry);
    pfcandpt10pt0p1_handle.GetEntry(entry);
    pfcandpt10pt0p2_handle.GetEntry(entry);
    pfcandpt10pt0p3_handle.GetEntry(entry);
    pfcandpt10pt0p4_handle.GetEntry(entry);
    pfcandpt10pt0p5_handle.GetEntry(entry);
    pfcandpt10pt0p6_handle.GetEntry(entry);
    pfcandpt10pt0p7_handle.GetEntry(entry);
    pfcandpt10pt0p8_handle.GetEntry(entry);
    pfcandpt10pt0p9_handle.GetEntry(entry);
    pfcandpt10pt1p0_handle.GetEntry(entry);
    pfcandiso10pt0p1_handle.GetEntry(entry);
    pfcandiso10pt0p2_handle.GetEntry(entry);
    pfcandiso10pt0p3_handle.GetEntry(entry);
    pfcandiso10pt0p4_handle.GetEntry(entry);
    pfcandiso10pt0p5_handle.GetEntry(entry);
    pfcandiso10pt0p6_handle.GetEntry(entry);
    pfcandiso10pt0p7_handle.GetEntry(entry);
    pfcandiso10pt0p8_handle.GetEntry(entry);
    pfcandiso10pt0p9_handle.GetEntry(entry);
    pfcandiso10pt1p0_handle.GetEntry(entry);
    mbb_handle.GetEntry(entry);
    lep1pfjetdr_handle.GetEntry(entry);
    lep2pfjetdr_handle.GetEntry(entry);
    mclep_handle.GetEntry(entry);
    mcnu_handle.GetEntry(entry);
    mcmln_handle.GetEntry(entry);
    mcmtln_handle.GetEntry(entry);
    mlep_handle.GetEntry(entry);
    lep1_handle.GetEntry(entry);
    lep2_handle.GetEntry(entry);
    trklep1_handle.GetEntry(entry);
    trklep2_handle.GetEntry(entry);
    gfitlep1_handle.GetEntry(entry);
    gfitlep2_handle.GetEntry(entry);
    lepp_handle.GetEntry(entry);
    lepm_handle.GetEntry(entry);
    pflep1_handle.GetEntry(entry);
    pflep2_handle.GetEntry(entry);
    leppfjet1_handle.GetEntry(entry);
    leppfjet2_handle.GetEntry(entry);
    mclep1_handle.GetEntry(entry);
    mclep2_handle.GetEntry(entry);
    mctaud1_handle.GetEntry(entry);
    mctaud2_handle.GetEntry(entry);
    mctaudvis1_handle.GetEntry(entry);
    mctaudvis2_handle.GetEntry(entry);
    pflep_handle.GetEntry(entry);
    pftaud_handle.GetEntry(entry);
    pfcand5_handle.GetEntry(entry);
    pfcand10_handle.GetEntry(entry);
    pfTau15_leadPtcandID_handle.GetEntry(entry);
    pfTau15_handle.GetEntry(entry);
    pfTau15_leadPtcand_handle.GetEntry(entry);
    pfTau_leadPtcandID_handle.GetEntry(entry);
    pfTau_handle.GetEntry(entry);
    pfTau_leadPtcand_handle.GetEntry(entry);
    pfTauLoose_leadPtcandID_handle.GetEntry(entry);
    pfTauLoose_handle.GetEntry(entry);
    pfTauLoose_leadPtcand_handle.GetEntry(entry);
    pfcandOS10_handle.GetEntry(entry);
    pfcandOS10looseZ_handle.GetEntry(entry);
    pfcand5looseZ_handle.GetEntry(entry);
    pfcanddir10_handle.GetEntry(entry);
    pfcandveto10_handle.GetEntry(entry);
    pfcandvetoL10_handle.GetEntry(entry);
    jet_handle.GetEntry(entry);
    nonisoel_handle.GetEntry(entry);
    nonisomu_handle.GetEntry(entry);
    t_handle.GetEntry(entry);
    tbar_handle.GetEntry(entry);
    ttbar_handle.GetEntry(entry);
    lep_t_handle.GetEntry(entry);
    lep_tbar_handle.GetEntry(entry);
    stop_t_handle.GetEntry(entry);
    stop_tbar_handle.GetEntry(entry);
    neutralino_t_handle.GetEntry(entry);
    neutralino_tbar_handle.GetEntry(entry);
    lep_t_id_handle.GetEntry(entry);
    lep_tbar_id_handle.GetEntry(entry);
    pfjets_handle.GetEntry(entry);
    pfjets_genJet__handle.GetEntry(entry);
    pfjets_csv_handle.GetEntry(entry);
    pfjets_chm_handle.GetEntry(entry);
    pfjets_neu_handle.GetEntry(entry);
    pfjets_l1corr_handle.GetEntry(entry);
    pfjets_corr_handle.GetEntry(entry);
    pfjets_mc3_handle.GetEntry(entry);
    pfjets_mcflavorAlgo_handle.GetEntry(entry);
    pfjets_mcflavorPhys_handle.GetEntry(entry);
    pfjets_uncertainty_handle.GetEntry(entry);
    pfjets_flav_handle.GetEntry(entry);
    pfjets_lrm_handle.GetEntry(entry);
    pfjets_lrm2_handle.GetEntry(entry);
    pfjets_qgtag_handle.GetEntry(entry);
    pfjets_genJetDr_handle.GetEntry(entry);
    pfjets_sigma_handle.GetEntry(entry);
    pfjets_lepjet_handle.GetEntry(entry);
    pfjets_beta_handle.GetEntry(entry);
    pfjets_beta2_handle.GetEntry(entry);
    pfjets_beta_0p1_handle.GetEntry(entry);
    pfjets_beta_0p2_handle.GetEntry(entry);
    pfjets_beta2_0p1_handle.GetEntry(entry);
    pfjets_beta2_0p5_handle.GetEntry(entry);
    pfjets_mvaPUid_handle.GetEntry(entry);
    pfjets_mva5xPUid_handle.GetEntry(entry);
    pfjets_mvaBeta_handle.GetEntry(entry);
    genbs_handle.GetEntry(entry);
    genps_pdgId_handle.GetEntry(entry);
    genps_firstMother_handle.GetEntry(entry);
    genps_energy_handle.GetEntry(entry);
    genps_pt_handle.GetEntry(entry);
    genps_eta_handle.GetEntry(entry);
    genps_phi_handle.GetEntry(entry);
    genps_mass_handle.GetEntry(entry);
    mini_mt_handle.GetEntry(entry);
    mini_mtup_handle.GetEntry(entry);
    mini_mtdown_handle.GetEntry(entry);
    mini_isrweight_handle.GetEntry(entry);
    mini_met_handle.GetEntry(entry);
    mini_metup_handle.GetEntry(entry);
    mini_metdown_handle.GetEntry(entry);
    mini_sig_handle.GetEntry(entry);
    mini_cr1_handle.GetEntry(entry);
    mini_cr4_handle.GetEntry(entry);
    mini_cr5_handle.GetEntry(entry);
    mini_whsig_handle.GetEntry(entry);
    mini_whcr1_handle.GetEntry(entry);
    mini_chi2_handle.GetEntry(entry);
    mini_chi2up_handle.GetEntry(entry);
    mini_chi2down_handle.GetEntry(entry);
    mini_chi2bup_handle.GetEntry(entry);
    mini_chi2bdown_handle.GetEntry(entry);
    mini_mt2b_handle.GetEntry(entry);
    mini_mt2bl_handle.GetEntry(entry);
    mini_mt2w_handle.GetEntry(entry);
    mini_mt2wup_handle.GetEntry(entry);
    mini_mt2wdown_handle.GetEntry(entry);
    mini_mt2wbup_handle.GetEntry(entry);
    mini_mt2wbdown_handle.GetEntry(entry);
    mini_weight_handle.GetEntry(entry);
    mini_nvtxweight_handle.GetEntry(entry);
    mini_sltrigeff_handle.GetEntry(entry);
    mini_dltrigeff_handle.GetEntry(entry);
    mini_nsigevents_handle.GetEntry(entry);
    mini_nb_handle.GetEntry(entry);
    mini_nbupBC_handle.GetEntry(entry);
    mini_nbdownBC_handle.GetEntry(entry);
    mini_nbupL_handle.GetEntry(entry);
    mini_nbdownL_handle.GetEntry(entry);
    mini_njets_handle.GetEntry(entry);
    mini_njetsup_handle.GetEntry(entry);
    mini_njetsdown_handle.GetEntry(entry);
    mini_passisotrk_handle.GetEntry(entry);
    mini_passtauveto_handle.GetEntry(entry);
    mini_nlep_handle.GetEntry(entry);
    mini_lep1pt_handle.GetEntry(entry);
    mini_lep1eta_handle.GetEntry(entry);
    mini_lep2pt_handle.GetEntry(entry);
    mini_lep2eta_handle.GetEntry(entry);
    mini_dilmass_handle.GetEntry(entry);
    mini_mstop_handle.GetEntry(entry);
    mini_mlsp_handle.GetEntry(entry);
    mini_x_handle.GetEntry(entry);
    mini_xsecsusy_handle.GetEntry(entry);
    mini_dRleptB1_handle.GetEntry(entry);
    mini_dRleptB1_bup_handle.GetEntry(entry);
    mini_dRleptB1_bdown_handle.GetEntry(entry);
    mini_htssl_handle.GetEntry(entry);
    mini_htosl_handle.GetEntry(entry);
    mini_htratiol_handle.GetEntry(entry);
    mini_htssm_handle.GetEntry(entry);
    mini_htosm_handle.GetEntry(entry);
    mini_htratiom_handle.GetEntry(entry);
    mini_htratiomup_handle.GetEntry(entry);
    mini_htratiomdown_handle.GetEntry(entry);
    mini_dphimj1_handle.GetEntry(entry);
    mini_dphimj2_handle.GetEntry(entry);
    mini_dphimjmin_handle.GetEntry(entry);
    mini_pt_b_handle.GetEntry(entry);
    mini_pt_b_up_handle.GetEntry(entry);
    mini_pt_b_down_handle.GetEntry(entry);
    mini_pt_b_bup_handle.GetEntry(entry);
    mini_pt_b_bdown_handle.GetEntry(entry);
    mini_pt_J1_handle.GetEntry(entry);
    mini_pt_J2_handle.GetEntry(entry);
    mini_bbmass_handle.GetEntry(entry);
    mini_bbpt_handle.GetEntry(entry);
    mini_wpt_handle.GetEntry(entry);
    mini_bbwdphi_handle.GetEntry(entry);
    mini_rand_handle.GetEntry(entry);
    mini_t2ttLM_handle.GetEntry(entry);
    mini_t2ttHM_handle.GetEntry(entry);
    mini_bdt_handle.GetEntry(entry);
    mini_bdtup_handle.GetEntry(entry);
    mini_bdtdown_handle.GetEntry(entry);
    mini_bdtbup_handle.GetEntry(entry);
    mini_bdtbdown_handle.GetEntry(entry);

}

void STOP_BABY::LoadAllBranches()
{
    acc_2010_handle.Load();
    acc_highmet_handle.Load();
    acc_highht_handle.Load();
    eldup_handle.Load();
    csc_handle.Load();
    hbhe_handle.Load();
    hbhenew_handle.Load();
    hcallaser_handle.Load();
    ecaltp_handle.Load();
    trkfail_handle.Load();
    eebadsc_handle.Load();
    lep1_badecallaser_handle.Load();
    lep2_badecallaser_handle.Load();
    isdata_handle.Load();
    jetid_handle.Load();
    jetid30_handle.Load();
    json_handle.Load();
    htoffset_handle.Load();
    htuncor_handle.Load();
    ptt_handle.Load();
    pttbar_handle.Load();
    ptttbar_handle.Load();
    mttbar_handle.Load();
    npartons_handle.Load();
    nwzpartons_handle.Load();
    hyptype_handle.Load();
    maxpartonpt_handle.Load();
    etattbar_handle.Load();
    njetsoffset_handle.Load();
    njetsuncor_handle.Load();
    costhetaweight_handle.Load();
    weight_handle.Load();
    weightleft_handle.Load();
    weightright_handle.Load();
    mutrigweight_handle.Load();
    mutrigweight2_handle.Load();
    sltrigweight_handle.Load();
    dltrigweight_handle.Load();
    trgeff_handle.Load();
    pthat_handle.Load();
    qscale_handle.Load();
    mgcor_handle.Load();
    wflav_handle.Load();
    ksusy_handle.Load();
    ksusyup_handle.Load();
    ksusydn_handle.Load();
    xsecsusy_handle.Load();
    xsecsusy2_handle.Load();
    smeff_handle.Load();
    k_handle.Load();
    mllgen_handle.Load();
    ptwgen_handle.Load();
    ptzgen_handle.Load();
    nlep_handle.Load();
    nosel_handle.Load();
    ngoodlep_handle.Load();
    ngoodel_handle.Load();
    ngoodmu_handle.Load();
    mull_handle.Load();
    mult_handle.Load();
    mullgen_handle.Load();
    multgen_handle.Load();
    proc_handle.Load();
    leptype_handle.Load();
    topmass_handle.Load();
    dilmass_handle.Load();
    dilrecoil_handle.Load();
    dilrecoilparl_handle.Load();
    dilrecoilperp_handle.Load();
    tcmet_handle.Load();
    genmet_handle.Load();
    gensumet_handle.Load();
    genmetphi_handle.Load();
    calomet_handle.Load();
    calometphi_handle.Load();
    trkmet_handle.Load();
    trkmetphi_handle.Load();
    trkmet_nolepcorr_handle.Load();
    trkmetphi_nolepcorr_handle.Load();
    pfmet_handle.Load();
    pfmetveto_handle.Load();
    pfmetsig_handle.Load();
    pfmetphi_handle.Load();
    pfsumet_handle.Load();
    mucormet_handle.Load();
    mucorjesmet_handle.Load();
    tcmet35X_handle.Load();
    tcmetevent_handle.Load();
    tcmetlooper_handle.Load();
    tcmetphi_handle.Load();
    tcsumet_handle.Load();
    tcmetUp_handle.Load();
    tcmetDown_handle.Load();
    tcmetTest_handle.Load();
    pfmetUp_handle.Load();
    pfmetDown_handle.Load();
    pfmetTest_handle.Load();
    sumjetpt_handle.Load();
    dileta_handle.Load();
    dilpt_handle.Load();
    dildphi_handle.Load();
    ngenjets_handle.Load();
    njpt_handle.Load();
    trgmu1_handle.Load();
    trgmu2_handle.Load();
    trgel1_handle.Load();
    trgel2_handle.Load();
    isomu24_handle.Load();
    ele27wp80_handle.Load();
    mm_handle.Load();
    mmtk_handle.Load();
    me_handle.Load();
    em_handle.Load();
    mu_handle.Load();
    ee_handle.Load();
    npfjets30_handle.Load();
    npfjets30lepcorr_handle.Load();
    knjets_handle.Load();
    rhovor_handle.Load();
    htpf30_handle.Load();
    t1met10_handle.Load();
    t1met20_handle.Load();
    t1met30_handle.Load();
    t1met10phi_handle.Load();
    t1met20phi_handle.Load();
    t1met30phi_handle.Load();
    t1met10mt_handle.Load();
    t1met20mt_handle.Load();
    t1met30mt_handle.Load();
    lepmetpt_handle.Load();
    lept1met10pt_handle.Load();
    t1met10s_handle.Load();
    t1met10sphi_handle.Load();
    t1met10smt_handle.Load();
    t1metphicorr_handle.Load();
    t1metphicorrup_handle.Load();
    t1metphicorrdn_handle.Load();
    t1metphicorrphi_handle.Load();
    t1metphicorrphiup_handle.Load();
    t1metphicorrphidn_handle.Load();
    t1metphicorrlep_handle.Load();
    t1metphicorrlepphi_handle.Load();
    t1metphicorrmt_handle.Load();
    t1metphicorrmtup_handle.Load();
    t1metphicorrmtdn_handle.Load();
    t1metphicorrlepmt_handle.Load();
    t1met_off_handle.Load();
    t1metphi_off_handle.Load();
    t1metmt_off_handle.Load();
    t1metphicorr_off_handle.Load();
    t1metphicorrphi_off_handle.Load();
    t1metphicorrmt_off_handle.Load();
    mt2bmin_handle.Load();
    mt2blmin_handle.Load();
    mt2wmin_handle.Load();
    chi2min_handle.Load();
    chi2minprob_handle.Load();
    nbtagsssv_handle.Load();
    nbtagstcl_handle.Load();
    nbtagstcm_handle.Load();
    nbtagscsvl_handle.Load();
    nbtagscsvm_handle.Load();
    nbtagscsvt_handle.Load();
    nbtagsssvcorr_handle.Load();
    nbtagstclcorr_handle.Load();
    nbtagstcmcorr_handle.Load();
    nbtagscsvlcorr_handle.Load();
    nbtagscsvmcorr_handle.Load();
    nbtagscsvtcott_handle.Load();
    njetsUp_handle.Load();
    njetsDown_handle.Load();
    htUp_handle.Load();
    htDown_handle.Load();
    ntruepu_handle.Load();
    npu_handle.Load();
    npuMinusOne_handle.Load();
    npuPlusOne_handle.Load();
    nvtx_handle.Load();
    indexfirstGoodVertex__handle.Load();
    nvtxweight_handle.Load();
    n3dvtxweight_handle.Load();
    pdfid1_handle.Load();
    pdfid2_handle.Load();
    pdfx1_handle.Load();
    pdfx2_handle.Load();
    pdfQ_handle.Load();
    vecjetpt_handle.Load();
    pass_handle.Load();
    passz_handle.Load();
    m0_handle.Load();
    mg_handle.Load();
    ml_handle.Load();
    x_handle.Load();
    m12_handle.Load();
    lep1chi2ndf_handle.Load();
    lep2chi2ndf_handle.Load();
    lep1dpt_handle.Load();
    lep2dpt_handle.Load();
    id1_handle.Load();
    id2_handle.Load();
    leptype1_handle.Load();
    leptype2_handle.Load();
    w1_handle.Load();
    w2_handle.Load();
    iso1_handle.Load();
    isont1_handle.Load();
    isopfold1_handle.Load();
    isopf1_handle.Load();
    etasc1_handle.Load();
    etasc2_handle.Load();
    eoverpin_handle.Load();
    eoverpout_handle.Load();
    dEtaIn_handle.Load();
    dPhiIn_handle.Load();
    sigmaIEtaIEta_handle.Load();
    hOverE_handle.Load();
    ooemoop_handle.Load();
    d0vtx_handle.Load();
    dzvtx_handle.Load();
    expinnerlayers_handle.Load();
    fbrem_handle.Load();
    pfisoch_handle.Load();
    pfisoem_handle.Load();
    pfisonh_handle.Load();
    eSC_handle.Load();
    phiSC_handle.Load();
    eSCRaw_handle.Load();
    eSCPresh_handle.Load();
    lep1_scslasercormean_handle.Load();
    lep1_scslasercormax_handle.Load();
    eoverpin2_handle.Load();
    eoverpout2_handle.Load();
    dEtaIn2_handle.Load();
    dPhiIn2_handle.Load();
    sigmaIEtaIEta2_handle.Load();
    hOverE2_handle.Load();
    ooemoop2_handle.Load();
    d0vtx2_handle.Load();
    dzvtx2_handle.Load();
    expinnerlayers2_handle.Load();
    fbrem2_handle.Load();
    pfisoch2_handle.Load();
    pfisoem2_handle.Load();
    pfisonh2_handle.Load();
    eSC2_handle.Load();
    phiSC2_handle.Load();
    eSCRaw2_handle.Load();
    eSCPresh2_handle.Load();
    lep2_scslasercormean_handle.Load();
    lep2_scslasercormax_handle.Load();
    scslasercormax_handle.Load();
    scslasercormax_pt_handle.Load();
    scslasercormax_eta_handle.Load();
    iso2_handle.Load();
    ecalveto1_handle.Load();
    ecalveto2_handle.Load();
    hcalveto1_handle.Load();
    hcalveto2_handle.Load();
    isont2_handle.Load();
    isopf2_handle.Load();
    ptl1_handle.Load();
    ptl2_handle.Load();
    etal1_handle.Load();
    etal2_handle.Load();
    phil1_handle.Load();
    phil2_handle.Load();
    meff_handle.Load();
    mt_handle.Load();
    dataset_handle.Load();
    run_handle.Load();
    lumi_handle.Load();
    event_handle.Load();
    y_handle.Load();
    ht_handle.Load();
    htgen_handle.Load();
    htjpt_handle.Load();
    nels_handle.Load();
    nmus_handle.Load();
    ntaus_handle.Load();
    nleps_handle.Load();
    nbs_handle.Load();
    dphijm_handle.Load();
    ptjetraw_handle.Load();
    ptjet23_handle.Load();
    ptjetF23_handle.Load();
    ptjetO23_handle.Load();
    mcid1_handle.Load();
    mcdr1_handle.Load();
    mcdecay1_handle.Load();
    mcndec1_handle.Load();
    mcndec2_handle.Load();
    mcndeckls1_handle.Load();
    mcndeckls2_handle.Load();
    mcndecem1_handle.Load();
    mcndecem2_handle.Load();
    mcid2_handle.Load();
    mcdr2_handle.Load();
    mcdecay2_handle.Load();
    mctaudpt1_handle.Load();
    mctaudpt2_handle.Load();
    mctaudid1_handle.Load();
    mctaudid2_handle.Load();
    mlepid_handle.Load();
    mleppassid_handle.Load();
    mleppassiso_handle.Load();
    mlepiso_handle.Load();
    mlepdr_handle.Load();
    pflepiso_handle.Load();
    pflepdr_handle.Load();
    pfleppt_handle.Load();
    pflepmindrj_handle.Load();
    pftaudiso_handle.Load();
    pftauddr_handle.Load();
    pftaudpt_handle.Load();
    pftaudmindrj_handle.Load();
    pfcandid5_handle.Load();
    pfcandiso5_handle.Load();
    pfcandpt5_handle.Load();
    pfcanddz5_handle.Load();
    pfcandmindrj5_handle.Load();
    pfcandid10_handle.Load();
    pfcandiso10_handle.Load();
    pfcandpt10_handle.Load();
    pfcanddz10_handle.Load();
    pfcandmindrj10_handle.Load();
    pfcandidOS10_handle.Load();
    pfcandisoOS10_handle.Load();
    pfcandptOS10_handle.Load();
    pfcanddzOS10_handle.Load();
    pfcandid5looseZ_handle.Load();
    pfcandiso5looseZ_handle.Load();
    pfcandpt5looseZ_handle.Load();
    pfcanddz5looseZ_handle.Load();
    pfcandidOS10looseZ_handle.Load();
    pfcandisoOS10looseZ_handle.Load();
    pfcandptOS10looseZ_handle.Load();
    pfcanddzOS10looseZ_handle.Load();
    pfcanddirid10_handle.Load();
    pfcanddiriso10_handle.Load();
    pfcanddirpt10_handle.Load();
    pfcanddirmindrj10_handle.Load();
    pfcandvetoid10_handle.Load();
    pfcandvetoiso10_handle.Load();
    pfcandvetopt10_handle.Load();
    pfcandvetomindrj10_handle.Load();
    pfcandvetoLid10_handle.Load();
    pfcandvetoLiso10_handle.Load();
    pfcandvetoLpt10_handle.Load();
    pfcandvetoLmindrj10_handle.Load();
    emjet10_handle.Load();
    mjj_handle.Load();
    emjet20_handle.Load();
    trkpt5_handle.Load();
    trkpt10_handle.Load();
    mleptrk5_handle.Load();
    mleptrk10_handle.Load();
    trkreliso5_handle.Load();
    trkreliso10_handle.Load();
    trkpt5loose_handle.Load();
    trkpt10loose_handle.Load();
    trkreliso5loose_handle.Load();
    trkreliso10loose_handle.Load();
    trkpt10pt0p1_handle.Load();
    trkpt10pt0p2_handle.Load();
    trkpt10pt0p3_handle.Load();
    trkpt10pt0p4_handle.Load();
    trkpt10pt0p5_handle.Load();
    trkpt10pt0p6_handle.Load();
    trkpt10pt0p7_handle.Load();
    trkpt10pt0p8_handle.Load();
    trkpt10pt0p9_handle.Load();
    trkpt10pt1p0_handle.Load();
    trkreliso10pt0p1_handle.Load();
    trkreliso10pt0p2_handle.Load();
    trkreliso10pt0p3_handle.Load();
    trkreliso10pt0p4_handle.Load();
    trkreliso10pt0p5_handle.Load();
    trkreliso10pt0p6_handle.Load();
    trkreliso10pt0p7_handle.Load();
    trkreliso10pt0p8_handle.Load();
    trkreliso10pt0p9_handle.Load();
    trkreliso10pt1p0_handle.Load();
    pfcandpt10pt0p1_handle.Load();
    pfcandpt10pt0p2_handle.Load();
    pfcandpt10pt0p3_handle.Load();
    pfcandpt10pt0p4_handle.Load();
    pfcandpt10pt0p5_handle.Load();
    pfcandpt10pt0p6_handle.Load();
    pfcandpt10pt0p7_handle.Load();
    pfcandpt10pt0p8_handle.Load();
    pfcandpt10pt0p9_handle.Load();
    pfcandpt10pt1p0_handle.Load();
    pfcandiso10pt0p1_handle.Load();
    pfcandiso10pt0p2_handle.Load();
    pfcandiso10pt0p3_handle.Load();
    pfcandiso10pt0p4_handle.Load();
    pfcandiso10pt0p5_handle.Load();
    pfcandiso10pt0p6_handle.Load();
    pfcandiso10pt0p7_handle.Load();
    pfcandiso10pt0p8_handle.Load();
    pfcandiso10pt0p9_handle.Load();
    pfcandiso10pt1p0_handle.Load();
    mbb_handle.Load();
    lep1pfjetdr_handle.Load();
    lep2pfjetdr_handle.Load();
    mclep_handle.Load();
    mcnu_handle.Load();
    mcmln_handle.Load();
    mcmtln_handle.Load();
    mlep_handle.Load();
    lep1_handle.Load();
    lep2_handle.Load();
    trklep1_handle.Load();
    trklep2_handle.Load();
    gfitlep1_handle.Load();
    gfitlep2_handle.Load();
    lepp_handle.Load();
    lepm_handle.Load();
    pflep1_handle.Load();
    pflep2_handle.Load();
    leppfjet1_handle.Load();
    leppfjet2_handle.Load();
    mclep1_handle.Load();
    mclep2_handle.Load();
    mctaud1_handle.Load();
    mctaud2_handle.Load();
    mctaudvis1_handle.Load();
    mctaudvis2_handle.Load();
    pflep_handle.Load();
    pftaud_handle.Load();
    pfcand5_handle.Load();
    pfcand10_handle.Load();
    pfTau15_leadPtcandID_handle.Load();
    pfTau15_handle.Load();
    pfTau15_leadPtcand_handle.Load();
    pfTau_leadPtcandID_handle.Load();
    pfTau_handle.Load();
    pfTau_leadPtcand_handle.Load();
    pfTauLoose_leadPtcandID_handle.Load();
    pfTauLoose_handle.Load();
    pfTauLoose_leadPtcand_handle.Load();
    pfcandOS10_handle.Load();
    pfcandOS10looseZ_handle.Load();
    pfcand5looseZ_handle.Load();
    pfcanddir10_handle.Load();
    pfcandveto10_handle.Load();
    pfcandvetoL10_handle.Load();
    jet_handle.Load();
    nonisoel_handle.Load();
    nonisomu_handle.Load();
    t_handle.Load();
    tbar_handle.Load();
    ttbar_handle.Load();
    lep_t_handle.Load();
    lep_tbar_handle.Load();
    stop_t_handle.Load();
    stop_tbar_handle.Load();
    neutralino_t_handle.Load();
    neutralino_tbar_handle.Load();
    lep_t_id_handle.Load();
    lep_tbar_id_handle.Load();
    pfjets_handle.Load();
    pfjets_genJet__handle.Load();
    pfjets_csv_handle.Load();
    pfjets_chm_handle.Load();
    pfjets_neu_handle.Load();
    pfjets_l1corr_handle.Load();
    pfjets_corr_handle.Load();
    pfjets_mc3_handle.Load();
    pfjets_mcflavorAlgo_handle.Load();
    pfjets_mcflavorPhys_handle.Load();
    pfjets_uncertainty_handle.Load();
    pfjets_flav_handle.Load();
    pfjets_lrm_handle.Load();
    pfjets_lrm2_handle.Load();
    pfjets_qgtag_handle.Load();
    pfjets_genJetDr_handle.Load();
    pfjets_sigma_handle.Load();
    pfjets_lepjet_handle.Load();
    pfjets_beta_handle.Load();
    pfjets_beta2_handle.Load();
    pfjets_beta_0p1_handle.Load();
    pfjets_beta_0p2_handle.Load();
    pfjets_beta2_0p1_handle.Load();
    pfjets_beta2_0p5_handle.Load();
    pfjets_mvaPUid_handle.Load();
    pfjets_mva5xPUid_handle.Load();
    pfjets_mvaBeta_handle.Load();
    genbs_handle.Load();
    genps_pdgId_handle.Load();
    genps_firstMother_handle.Load();
    genps_energy_handle.Load();
    genps_pt_handle.Load();
    genps_eta_handle.Load();
    genps_phi_handle.Load();
    genps_mass_handle.Load();
    mini_mt_handle.Load();
    mini_mtup_handle.Load();
    mini_mtdown_handle.Load();
    mini_isrweight_handle.Load();
    mini_met_handle.Load();
    mini_metup_handle.Load();
    mini_metdown_handle.Load();
    mini_sig_handle.Load();
    mini_cr1_handle.Load();
    mini_cr4_handle.Load();
    mini_cr5_handle.Load();
    mini_whsig_handle.Load();
    mini_whcr1_handle.Load();
    mini_chi2_handle.Load();
    mini_chi2up_handle.Load();
    mini_chi2down_handle.Load();
    mini_chi2bup_handle.Load();
    mini_chi2bdown_handle.Load();
    mini_mt2b_handle.Load();
    mini_mt2bl_handle.Load();
    mini_mt2w_handle.Load();
    mini_mt2wup_handle.Load();
    mini_mt2wdown_handle.Load();
    mini_mt2wbup_handle.Load();
    mini_mt2wbdown_handle.Load();
    mini_weight_handle.Load();
    mini_nvtxweight_handle.Load();
    mini_sltrigeff_handle.Load();
    mini_dltrigeff_handle.Load();
    mini_nsigevents_handle.Load();
    mini_nb_handle.Load();
    mini_nbupBC_handle.Load();
    mini_nbdownBC_handle.Load();
    mini_nbupL_handle.Load();
    mini_nbdownL_handle.Load();
    mini_njets_handle.Load();
    mini_njetsup_handle.Load();
    mini_njetsdown_handle.Load();
    mini_passisotrk_handle.Load();
    mini_passtauveto_handle.Load();
    mini_nlep_handle.Load();
    mini_lep1pt_handle.Load();
    mini_lep1eta_handle.Load();
    mini_lep2pt_handle.Load();
    mini_lep2eta_handle.Load();
    mini_dilmass_handle.Load();
    mini_mstop_handle.Load();
    mini_mlsp_handle.Load();
    mini_x_handle.Load();
    mini_xsecsusy_handle.Load();
    mini_dRleptB1_handle.Load();
    mini_dRleptB1_bup_handle.Load();
    mini_dRleptB1_bdown_handle.Load();
    mini_htssl_handle.Load();
    mini_htosl_handle.Load();
    mini_htratiol_handle.Load();
    mini_htssm_handle.Load();
    mini_htosm_handle.Load();
    mini_htratiom_handle.Load();
    mini_htratiomup_handle.Load();
    mini_htratiomdown_handle.Load();
    mini_dphimj1_handle.Load();
    mini_dphimj2_handle.Load();
    mini_dphimjmin_handle.Load();
    mini_pt_b_handle.Load();
    mini_pt_b_up_handle.Load();
    mini_pt_b_down_handle.Load();
    mini_pt_b_bup_handle.Load();
    mini_pt_b_bdown_handle.Load();
    mini_pt_J1_handle.Load();
    mini_pt_J2_handle.Load();
    mini_bbmass_handle.Load();
    mini_bbpt_handle.Load();
    mini_wpt_handle.Load();
    mini_bbwdphi_handle.Load();
    mini_rand_handle.Load();
    mini_t2ttLM_handle.Load();
    mini_t2ttHM_handle.Load();
    mini_bdt_handle.Load();
    mini_bdtup_handle.Load();
    mini_bdtdown_handle.Load();
    mini_bdtbup_handle.Load();
    mini_bdtbdown_handle.Load();

}

// branch accessor methods:
const int& STOP_BABY::acc_2010() {return acc_2010_handle.get();}
const int& STOP_BABY::acc_highmet() {return acc_highmet_handle.get();}
const int& STOP_BABY::acc_highht() {return acc_highht_handle.get();}
const int& STOP_BABY::eldup() {return eldup_handle.get();}
const int& STOP_BABY::csc() {return csc_handle.get();}
const int& STOP_BABY::hbhe() {return hbhe_handle.get();}
const int& STOP_BABY::hbhenew() {return hbhenew_handle.get();}
const int& STOP_BABY::hcallaser() {return hcallaser_handle.get();}
const int& STOP_BABY::ecaltp() {return ecaltp_handle.get();}
const int& STOP_BABY::trkfail() {return trkfail_handle.get();}
const int& STOP_BABY::eebadsc() {return eebadsc_handle.get();}
const int& STOP_BABY::lep1_badecallaser() {return lep1_badecallaser_handle.get();}
const int& STOP_BABY::lep2_badecallaser() {return lep2_badecallaser_handle.get();}
const int& STOP_BABY::isdata() {return isdata_handle.get();}
const int& STOP_BABY::jetid() {return jetid_handle.get();}
const int& STOP_BABY::jetid30() {return jetid30_handle.get();}
const int& STOP_BABY::json() {return json_handle.get();}
const float& STOP_BABY::htoffset() {return htoffset_handle.get();}
const float& STOP_BABY::htuncor() {return htuncor_handle.get();}
const float& STOP_BABY::ptt() {return ptt_handle.get();}
const float& STOP_BABY::pttbar() {return pttbar_handle.get();}
const float& STOP_BABY::ptttbar() {return ptttbar_handle.get();}
const float& STOP_BABY::mttbar() {return mttbar_handle.get();}
const int& STOP_BABY::npartons() {return npartons_handle.get();}
const int& STOP_BABY::nwzpartons() {return nwzpartons_handle.get();}
const int& STOP_BABY::hyptype() {return hyptype_handle.get();}
const float& STOP_BABY::maxpartonpt() {return maxpartonpt_handle.get();}
const float& STOP_BABY::etattbar() {return etattbar_handle.get();}
const int& STOP_BABY::njetsoffset() {return njetsoffset_handle.get();}
const int& STOP_BABY::njetsuncor() {return njetsuncor_handle.get();}
const float& STOP_BABY::costhetaweight() {return costhetaweight_handle.get();}
const float& STOP_BABY::weight() {return weight_handle.get();}
const float& STOP_BABY::weightleft() {return weightleft_handle.get();}
const float& STOP_BABY::weightright() {return weightright_handle.get();}
const float& STOP_BABY::mutrigweight() {return mutrigweight_handle.get();}
const float& STOP_BABY::mutrigweight2() {return mutrigweight2_handle.get();}
const float& STOP_BABY::sltrigweight() {return sltrigweight_handle.get();}
const float& STOP_BABY::dltrigweight() {return dltrigweight_handle.get();}
const float& STOP_BABY::trgeff() {return trgeff_handle.get();}
const float& STOP_BABY::pthat() {return pthat_handle.get();}
const float& STOP_BABY::qscale() {return qscale_handle.get();}
const float& STOP_BABY::mgcor() {return mgcor_handle.get();}
const int& STOP_BABY::wflav() {return wflav_handle.get();}
const float& STOP_BABY::ksusy() {return ksusy_handle.get();}
const float& STOP_BABY::ksusyup() {return ksusyup_handle.get();}
const float& STOP_BABY::ksusydn() {return ksusydn_handle.get();}
const float& STOP_BABY::xsecsusy() {return xsecsusy_handle.get();}
const float& STOP_BABY::xsecsusy2() {return xsecsusy2_handle.get();}
const float& STOP_BABY::smeff() {return smeff_handle.get();}
const float& STOP_BABY::k() {return k_handle.get();}
const float& STOP_BABY::mllgen() {return mllgen_handle.get();}
const float& STOP_BABY::ptwgen() {return ptwgen_handle.get();}
const float& STOP_BABY::ptzgen() {return ptzgen_handle.get();}
const int& STOP_BABY::nlep() {return nlep_handle.get();}
const int& STOP_BABY::nosel() {return nosel_handle.get();}
const int& STOP_BABY::ngoodlep() {return ngoodlep_handle.get();}
const int& STOP_BABY::ngoodel() {return ngoodel_handle.get();}
const int& STOP_BABY::ngoodmu() {return ngoodmu_handle.get();}
const int& STOP_BABY::mull() {return mull_handle.get();}
const int& STOP_BABY::mult() {return mult_handle.get();}
const int& STOP_BABY::mullgen() {return mullgen_handle.get();}
const int& STOP_BABY::multgen() {return multgen_handle.get();}
const int& STOP_BABY::proc() {return proc_handle.get();}
const int& STOP_BABY::leptype() {return leptype_handle.get();}
const float& STOP_BABY::topmass() {return topmass_handle.get();}
const float& STOP_BABY::dilmass() {return dilmass_handle.get();}
const float& STOP_BABY::dilrecoil() {return dilrecoil_handle.get();}
const float& STOP_BABY::dilrecoilparl() {return dilrecoilparl_handle.get();}
const float& STOP_BABY::dilrecoilperp() {return dilrecoilperp_handle.get();}
const float& STOP_BABY::tcmet() {return tcmet_handle.get();}
const float& STOP_BABY::genmet() {return genmet_handle.get();}
const float& STOP_BABY::gensumet() {return gensumet_handle.get();}
const float& STOP_BABY::genmetphi() {return genmetphi_handle.get();}
const float& STOP_BABY::calomet() {return calomet_handle.get();}
const float& STOP_BABY::calometphi() {return calometphi_handle.get();}
const float& STOP_BABY::trkmet() {return trkmet_handle.get();}
const float& STOP_BABY::trkmetphi() {return trkmetphi_handle.get();}
const float& STOP_BABY::trkmet_nolepcorr() {return trkmet_nolepcorr_handle.get();}
const float& STOP_BABY::trkmetphi_nolepcorr() {return trkmetphi_nolepcorr_handle.get();}
const float& STOP_BABY::pfmet() {return pfmet_handle.get();}
const float& STOP_BABY::pfmetveto() {return pfmetveto_handle.get();}
const float& STOP_BABY::pfmetsig() {return pfmetsig_handle.get();}
const float& STOP_BABY::pfmetphi() {return pfmetphi_handle.get();}
const float& STOP_BABY::pfsumet() {return pfsumet_handle.get();}
const float& STOP_BABY::mucormet() {return mucormet_handle.get();}
const float& STOP_BABY::mucorjesmet() {return mucorjesmet_handle.get();}
const float& STOP_BABY::tcmet35X() {return tcmet35X_handle.get();}
const float& STOP_BABY::tcmetevent() {return tcmetevent_handle.get();}
const float& STOP_BABY::tcmetlooper() {return tcmetlooper_handle.get();}
const float& STOP_BABY::tcmetphi() {return tcmetphi_handle.get();}
const float& STOP_BABY::tcsumet() {return tcsumet_handle.get();}
const float& STOP_BABY::tcmetUp() {return tcmetUp_handle.get();}
const float& STOP_BABY::tcmetDown() {return tcmetDown_handle.get();}
const float& STOP_BABY::tcmetTest() {return tcmetTest_handle.get();}
const float& STOP_BABY::pfmetUp() {return pfmetUp_handle.get();}
const float& STOP_BABY::pfmetDown() {return pfmetDown_handle.get();}
const float& STOP_BABY::pfmetTest() {return pfmetTest_handle.get();}
const float& STOP_BABY::sumjetpt() {return sumjetpt_handle.get();}
const float& STOP_BABY::dileta() {return dileta_handle.get();}
const float& STOP_BABY::dilpt() {return dilpt_handle.get();}
const float& STOP_BABY::dildphi() {return dildphi_handle.get();}
const int& STOP_BABY::ngenjets() {return ngenjets_handle.get();}
const int& STOP_BABY::njpt() {return njpt_handle.get();}
const int& STOP_BABY::trgmu1() {return trgmu1_handle.get();}
const int& STOP_BABY::trgmu2() {return trgmu2_handle.get();}
const int& STOP_BABY::trgel1() {return trgel1_handle.get();}
const int& STOP_BABY::trgel2() {return trgel2_handle.get();}
const int& STOP_BABY::isomu24() {return isomu24_handle.get();}
const int& STOP_BABY::ele27wp80() {return ele27wp80_handle.get();}
const int& STOP_BABY::mm() {return mm_handle.get();}
const int& STOP_BABY::mmtk() {return mmtk_handle.get();}
const int& STOP_BABY::me() {return me_handle.get();}
const int& STOP_BABY::em() {return em_handle.get();}
const int& STOP_BABY::mu() {return mu_handle.get();}
const int& STOP_BABY::ee() {return ee_handle.get();}
const int& STOP_BABY::npfjets30() {return npfjets30_handle.get();}
const int& STOP_BABY::npfjets30lepcorr() {return npfjets30lepcorr_handle.get();}
const float& STOP_BABY::knjets() {return knjets_handle.get();}
const float& STOP_BABY::rhovor() {return rhovor_handle.get();}
const float& STOP_BABY::htpf30() {return htpf30_handle.get();}
const float& STOP_BABY::t1met10() {return t1met10_handle.get();}
const float& STOP_BABY::t1met20() {return t1met20_handle.get();}
const float& STOP_BABY::t1met30() {return t1met30_handle.get();}
const float& STOP_BABY::t1met10phi() {return t1met10phi_handle.get();}
const float& STOP_BABY::t1met20phi() {return t1met20phi_handle.get();}
const float& STOP_BABY::t1met30phi() {return t1met30phi_handle.get();}
const float& STOP_BABY::t1met10mt() {return t1met10mt_handle.get();}
const float& STOP_BABY::t1met20mt() {return t1met20mt_handle.get();}
const float& STOP_BABY::t1met30mt() {return t1met30mt_handle.get();}
const float& STOP_BABY::lepmetpt() {return lepmetpt_handle.get();}
const float& STOP_BABY::lept1met10pt() {return lept1met10pt_handle.get();}
const float& STOP_BABY::t1met10s() {return t1met10s_handle.get();}
const float& STOP_BABY::t1met10sphi() {return t1met10sphi_handle.get();}
const float& STOP_BABY::t1met10smt() {return t1met10smt_handle.get();}
const float& STOP_BABY::t1metphicorr() {return t1metphicorr_handle.get();}
const float& STOP_BABY::t1metphicorrup() {return t1metphicorrup_handle.get();}
const float& STOP_BABY::t1metphicorrdn() {return t1metphicorrdn_handle.get();}
const float& STOP_BABY::t1metphicorrphi() {return t1metphicorrphi_handle.get();}
const float& STOP_BABY::t1metphicorrphiup() {return t1metphicorrphiup_handle.get();}
const float& STOP_BABY::t1metphicorrphidn() {return t1metphicorrphidn_handle.get();}
const float& STOP_BABY::t1metphicorrlep() {return t1metphicorrlep_handle.get();}
const float& STOP_BABY::t1metphicorrlepphi() {return t1metphicorrlepphi_handle.get();}
const float& STOP_BABY::t1metphicorrmt() {return t1metphicorrmt_handle.get();}
const float& STOP_BABY::t1metphicorrmtup() {return t1metphicorrmtup_handle.get();}
const float& STOP_BABY::t1metphicorrmtdn() {return t1metphicorrmtdn_handle.get();}
const float& STOP_BABY::t1metphicorrlepmt() {return t1metphicorrlepmt_handle.get();}
const float& STOP_BABY::t1met_off() {return t1met_off_handle.get();}
const float& STOP_BABY::t1metphi_off() {return t1metphi_off_handle.get();}
const float& STOP_BABY::t1metmt_off() {return t1metmt_off_handle.get();}
const float& STOP_BABY::t1metphicorr_off() {return t1metphicorr_off_handle.get();}
const float& STOP_BABY::t1metphicorrphi_off() {return t1metphicorrphi_off_handle.get();}
const float& STOP_BABY::t1metphicorrmt_off() {return t1metphicorrmt_off_handle.get();}
const float& STOP_BABY::mt2bmin() {return mt2bmin_handle.get();}
const float& STOP_BABY::mt2blmin() {return mt2blmin_handle.get();}
const float& STOP_BABY::mt2wmin() {return mt2wmin_handle.get();}
const float& STOP_BABY::chi2min() {return chi2min_handle.get();}
const float& STOP_BABY::chi2minprob() {return chi2minprob_handle.get();}
const int& STOP_BABY::nbtagsssv() {return nbtagsssv_handle.get();}
const int& STOP_BABY::nbtagstcl() {return nbtagstcl_handle.get();}
const int& STOP_BABY::nbtagstcm() {return nbtagstcm_handle.get();}
const int& STOP_BABY::nbtagscsvl() {return nbtagscsvl_handle.get();}
const int& STOP_BABY::nbtagscsvm() {return nbtagscsvm_handle.get();}
const int& STOP_BABY::nbtagscsvt() {return nbtagscsvt_handle.get();}
const int& STOP_BABY::nbtagsssvcorr() {return nbtagsssvcorr_handle.get();}
const int& STOP_BABY::nbtagstclcorr() {return nbtagstclcorr_handle.get();}
const int& STOP_BABY::nbtagstcmcorr() {return nbtagstcmcorr_handle.get();}
const int& STOP_BABY::nbtagscsvlcorr() {return nbtagscsvlcorr_handle.get();}
const int& STOP_BABY::nbtagscsvmcorr() {return nbtagscsvmcorr_handle.get();}
const int& STOP_BABY::nbtagscsvtcott() {return nbtagscsvtcott_handle.get();}
const int& STOP_BABY::njetsUp() {return njetsUp_handle.get();}
const int& STOP_BABY::njetsDown() {return njetsDown_handle.get();}
const float& STOP_BABY::htUp() {return htUp_handle.get();}
const float& STOP_BABY::htDown() {return htDown_handle.get();}
const int& STOP_BABY::ntruepu() {return ntruepu_handle.get();}
const int& STOP_BABY::npu() {return npu_handle.get();}
const int& STOP_BABY::npuMinusOne() {return npuMinusOne_handle.get();}
const int& STOP_BABY::npuPlusOne() {return npuPlusOne_handle.get();}
const int& STOP_BABY::nvtx() {return nvtx_handle.get();}
const int& STOP_BABY::indexfirstGoodVertex_() {return indexfirstGoodVertex__handle.get();}
const float& STOP_BABY::nvtxweight() {return nvtxweight_handle.get();}
const float& STOP_BABY::n3dvtxweight() {return n3dvtxweight_handle.get();}
const int& STOP_BABY::pdfid1() {return pdfid1_handle.get();}
const int& STOP_BABY::pdfid2() {return pdfid2_handle.get();}
const float& STOP_BABY::pdfx1() {return pdfx1_handle.get();}
const float& STOP_BABY::pdfx2() {return pdfx2_handle.get();}
const float& STOP_BABY::pdfQ() {return pdfQ_handle.get();}
const float& STOP_BABY::vecjetpt() {return vecjetpt_handle.get();}
const int& STOP_BABY::pass() {return pass_handle.get();}
const int& STOP_BABY::passz() {return passz_handle.get();}
const float& STOP_BABY::m0() {return m0_handle.get();}
const float& STOP_BABY::mg() {return mg_handle.get();}
const float& STOP_BABY::ml() {return ml_handle.get();}
const float& STOP_BABY::x() {return x_handle.get();}
const float& STOP_BABY::m12() {return m12_handle.get();}
const float& STOP_BABY::lep1chi2ndf() {return lep1chi2ndf_handle.get();}
const float& STOP_BABY::lep2chi2ndf() {return lep2chi2ndf_handle.get();}
const float& STOP_BABY::lep1dpt() {return lep1dpt_handle.get();}
const float& STOP_BABY::lep2dpt() {return lep2dpt_handle.get();}
const int& STOP_BABY::id1() {return id1_handle.get();}
const int& STOP_BABY::id2() {return id2_handle.get();}
const int& STOP_BABY::leptype1() {return leptype1_handle.get();}
const int& STOP_BABY::leptype2() {return leptype2_handle.get();}
const int& STOP_BABY::w1() {return w1_handle.get();}
const int& STOP_BABY::w2() {return w2_handle.get();}
const float& STOP_BABY::iso1() {return iso1_handle.get();}
const float& STOP_BABY::isont1() {return isont1_handle.get();}
const float& STOP_BABY::isopfold1() {return isopfold1_handle.get();}
const float& STOP_BABY::isopf1() {return isopf1_handle.get();}
const float& STOP_BABY::etasc1() {return etasc1_handle.get();}
const float& STOP_BABY::etasc2() {return etasc2_handle.get();}
const float& STOP_BABY::eoverpin() {return eoverpin_handle.get();}
const float& STOP_BABY::eoverpout() {return eoverpout_handle.get();}
const float& STOP_BABY::dEtaIn() {return dEtaIn_handle.get();}
const float& STOP_BABY::dPhiIn() {return dPhiIn_handle.get();}
const float& STOP_BABY::sigmaIEtaIEta() {return sigmaIEtaIEta_handle.get();}
const float& STOP_BABY::hOverE() {return hOverE_handle.get();}
const float& STOP_BABY::ooemoop() {return ooemoop_handle.get();}
const float& STOP_BABY::d0vtx() {return d0vtx_handle.get();}
const float& STOP_BABY::dzvtx() {return dzvtx_handle.get();}
const float& STOP_BABY::expinnerlayers() {return expinnerlayers_handle.get();}
const float& STOP_BABY::fbrem() {return fbrem_handle.get();}
const float& STOP_BABY::pfisoch() {return pfisoch_handle.get();}
const float& STOP_BABY::pfisoem() {return pfisoem_handle.get();}
const float& STOP_BABY::pfisonh() {return pfisonh_handle.get();}
const float& STOP_BABY::eSC() {return eSC_handle.get();}
const float& STOP_BABY::phiSC() {return phiSC_handle.get();}
const float& STOP_BABY::eSCRaw() {return eSCRaw_handle.get();}
const float& STOP_BABY::eSCPresh() {return eSCPresh_handle.get();}
const float& STOP_BABY::lep1_scslasercormean() {return lep1_scslasercormean_handle.get();}
const float& STOP_BABY::lep1_scslasercormax() {return lep1_scslasercormax_handle.get();}
const float& STOP_BABY::eoverpin2() {return eoverpin2_handle.get();}
const float& STOP_BABY::eoverpout2() {return eoverpout2_handle.get();}
const float& STOP_BABY::dEtaIn2() {return dEtaIn2_handle.get();}
const float& STOP_BABY::dPhiIn2() {return dPhiIn2_handle.get();}
const float& STOP_BABY::sigmaIEtaIEta2() {return sigmaIEtaIEta2_handle.get();}
const float& STOP_BABY::hOverE2() {return hOverE2_handle.get();}
const float& STOP_BABY::ooemoop2() {return ooemoop2_handle.get();}
const float& STOP_BABY::d0vtx2() {return d0vtx2_handle.get();}
const float& STOP_BABY::dzvtx2() {return dzvtx2_handle.get();}
const float& STOP_BABY::expinnerlayers2() {return expinnerlayers2_handle.get();}
const float& STOP_BABY::fbrem2() {return fbrem2_handle.get();}
const float& STOP_BABY::pfisoch2() {return pfisoch2_handle.get();}
const float& STOP_BABY::pfisoem2() {return pfisoem2_handle.get();}
const float& STOP_BABY::pfisonh2() {return pfisonh2_handle.get();}
const float& STOP_BABY::eSC2() {return eSC2_handle.get();}
const float& STOP_BABY::phiSC2() {return phiSC2_handle.get();}
const float& STOP_BABY::eSCRaw2() {return eSCRaw2_handle.get();}
const float& STOP_BABY::eSCPresh2() {return eSCPresh2_handle.get();}
const float& STOP_BABY::lep2_scslasercormean() {return lep2_scslasercormean_handle.get();}
const float& STOP_BABY::lep2_scslasercormax() {return lep2_scslasercormax_handle.get();}
const float& STOP_BABY::scslasercormax() {return scslasercormax_handle.get();}
const float& STOP_BABY::scslasercormax_pt() {return scslasercormax_pt_handle.get();}
const float& STOP_BABY::scslasercormax_eta() {return scslasercormax_eta_handle.get();}
const float& STOP_BABY::iso2() {return iso2_handle.get();}
const float& STOP_BABY::ecalveto1() {return ecalveto1_handle.get();}
const float& STOP_BABY::ecalveto2() {return ecalveto2_handle.get();}
const float& STOP_BABY::hcalveto1() {return hcalveto1_handle.get();}
const float& STOP_BABY::hcalveto2() {return hcalveto2_handle.get();}
const float& STOP_BABY::isont2() {return isont2_handle.get();}
const float& STOP_BABY::isopf2() {return isopf2_handle.get();}
const float& STOP_BABY::ptl1() {return ptl1_handle.get();}
const float& STOP_BABY::ptl2() {return ptl2_handle.get();}
const float& STOP_BABY::etal1() {return etal1_handle.get();}
const float& STOP_BABY::etal2() {return etal2_handle.get();}
const float& STOP_BABY::phil1() {return phil1_handle.get();}
const float& STOP_BABY::phil2() {return phil2_handle.get();}
const float& STOP_BABY::meff() {return meff_handle.get();}
const float& STOP_BABY::mt() {return mt_handle.get();}
const char& STOP_BABY::dataset() {return dataset_handle.get();}
const unsigned int& STOP_BABY::run() {return run_handle.get();}
const unsigned int& STOP_BABY::lumi() {return lumi_handle.get();}
const unsigned int& STOP_BABY::event() {return event_handle.get();}
const float& STOP_BABY::y() {return y_handle.get();}
const float& STOP_BABY::ht() {return ht_handle.get();}
const float& STOP_BABY::htgen() {return htgen_handle.get();}
const float& STOP_BABY::htjpt() {return htjpt_handle.get();}
const int& STOP_BABY::nels() {return nels_handle.get();}
const int& STOP_BABY::nmus() {return nmus_handle.get();}
const int& STOP_BABY::ntaus() {return ntaus_handle.get();}
const int& STOP_BABY::nleps() {return nleps_handle.get();}
const int& STOP_BABY::nbs() {return nbs_handle.get();}
const float& STOP_BABY::dphijm() {return dphijm_handle.get();}
const float& STOP_BABY::ptjetraw() {return ptjetraw_handle.get();}
const float& STOP_BABY::ptjet23() {return ptjet23_handle.get();}
const float& STOP_BABY::ptjetF23() {return ptjetF23_handle.get();}
const float& STOP_BABY::ptjetO23() {return ptjetO23_handle.get();}
const int& STOP_BABY::mcid1() {return mcid1_handle.get();}
const float& STOP_BABY::mcdr1() {return mcdr1_handle.get();}
const int& STOP_BABY::mcdecay1() {return mcdecay1_handle.get();}
const int& STOP_BABY::mcndec1() {return mcndec1_handle.get();}
const int& STOP_BABY::mcndec2() {return mcndec2_handle.get();}
const int& STOP_BABY::mcndeckls1() {return mcndeckls1_handle.get();}
const int& STOP_BABY::mcndeckls2() {return mcndeckls2_handle.get();}
const int& STOP_BABY::mcndecem1() {return mcndecem1_handle.get();}
const int& STOP_BABY::mcndecem2() {return mcndecem2_handle.get();}
const int& STOP_BABY::mcid2() {return mcid2_handle.get();}
const float& STOP_BABY::mcdr2() {return mcdr2_handle.get();}
const int& STOP_BABY::mcdecay2() {return mcdecay2_handle.get();}
const float& STOP_BABY::mctaudpt1() {return mctaudpt1_handle.get();}
const float& STOP_BABY::mctaudpt2() {return mctaudpt2_handle.get();}
const int& STOP_BABY::mctaudid1() {return mctaudid1_handle.get();}
const int& STOP_BABY::mctaudid2() {return mctaudid2_handle.get();}
const int& STOP_BABY::mlepid() {return mlepid_handle.get();}
const int& STOP_BABY::mleppassid() {return mleppassid_handle.get();}
const int& STOP_BABY::mleppassiso() {return mleppassiso_handle.get();}
const float& STOP_BABY::mlepiso() {return mlepiso_handle.get();}
const float& STOP_BABY::mlepdr() {return mlepdr_handle.get();}
const float& STOP_BABY::pflepiso() {return pflepiso_handle.get();}
const float& STOP_BABY::pflepdr() {return pflepdr_handle.get();}
const float& STOP_BABY::pfleppt() {return pfleppt_handle.get();}
const float& STOP_BABY::pflepmindrj() {return pflepmindrj_handle.get();}
const float& STOP_BABY::pftaudiso() {return pftaudiso_handle.get();}
const float& STOP_BABY::pftauddr() {return pftauddr_handle.get();}
const float& STOP_BABY::pftaudpt() {return pftaudpt_handle.get();}
const float& STOP_BABY::pftaudmindrj() {return pftaudmindrj_handle.get();}
const int& STOP_BABY::pfcandid5() {return pfcandid5_handle.get();}
const float& STOP_BABY::pfcandiso5() {return pfcandiso5_handle.get();}
const float& STOP_BABY::pfcandpt5() {return pfcandpt5_handle.get();}
const float& STOP_BABY::pfcanddz5() {return pfcanddz5_handle.get();}
const float& STOP_BABY::pfcandmindrj5() {return pfcandmindrj5_handle.get();}
const int& STOP_BABY::pfcandid10() {return pfcandid10_handle.get();}
const float& STOP_BABY::pfcandiso10() {return pfcandiso10_handle.get();}
const float& STOP_BABY::pfcandpt10() {return pfcandpt10_handle.get();}
const float& STOP_BABY::pfcanddz10() {return pfcanddz10_handle.get();}
const float& STOP_BABY::pfcandmindrj10() {return pfcandmindrj10_handle.get();}
const int& STOP_BABY::pfcandidOS10() {return pfcandidOS10_handle.get();}
const float& STOP_BABY::pfcandisoOS10() {return pfcandisoOS10_handle.get();}
const float& STOP_BABY::pfcandptOS10() {return pfcandptOS10_handle.get();}
const float& STOP_BABY::pfcanddzOS10() {return pfcanddzOS10_handle.get();}
const int& STOP_BABY::pfcandid5looseZ() {return pfcandid5looseZ_handle.get();}
const float& STOP_BABY::pfcandiso5looseZ() {return pfcandiso5looseZ_handle.get();}
const float& STOP_BABY::pfcandpt5looseZ() {return pfcandpt5looseZ_handle.get();}
const float& STOP_BABY::pfcanddz5looseZ() {return pfcanddz5looseZ_handle.get();}
const int& STOP_BABY::pfcandidOS10looseZ() {return pfcandidOS10looseZ_handle.get();}
const float& STOP_BABY::pfcandisoOS10looseZ() {return pfcandisoOS10looseZ_handle.get();}
const float& STOP_BABY::pfcandptOS10looseZ() {return pfcandptOS10looseZ_handle.get();}
const float& STOP_BABY::pfcanddzOS10looseZ() {return pfcanddzOS10looseZ_handle.get();}
const int& STOP_BABY::pfcanddirid10() {return pfcanddirid10_handle.get();}
const float& STOP_BABY::pfcanddiriso10() {return pfcanddiriso10_handle.get();}
const float& STOP_BABY::pfcanddirpt10() {return pfcanddirpt10_handle.get();}
const float& STOP_BABY::pfcanddirmindrj10() {return pfcanddirmindrj10_handle.get();}
const int& STOP_BABY::pfcandvetoid10() {return pfcandvetoid10_handle.get();}
const float& STOP_BABY::pfcandvetoiso10() {return pfcandvetoiso10_handle.get();}
const float& STOP_BABY::pfcandvetopt10() {return pfcandvetopt10_handle.get();}
const float& STOP_BABY::pfcandvetomindrj10() {return pfcandvetomindrj10_handle.get();}
const int& STOP_BABY::pfcandvetoLid10() {return pfcandvetoLid10_handle.get();}
const float& STOP_BABY::pfcandvetoLiso10() {return pfcandvetoLiso10_handle.get();}
const float& STOP_BABY::pfcandvetoLpt10() {return pfcandvetoLpt10_handle.get();}
const float& STOP_BABY::pfcandvetoLmindrj10() {return pfcandvetoLmindrj10_handle.get();}
const float& STOP_BABY::emjet10() {return emjet10_handle.get();}
const float& STOP_BABY::mjj() {return mjj_handle.get();}
const float& STOP_BABY::emjet20() {return emjet20_handle.get();}
const float& STOP_BABY::trkpt5() {return trkpt5_handle.get();}
const float& STOP_BABY::trkpt10() {return trkpt10_handle.get();}
const float& STOP_BABY::mleptrk5() {return mleptrk5_handle.get();}
const float& STOP_BABY::mleptrk10() {return mleptrk10_handle.get();}
const float& STOP_BABY::trkreliso5() {return trkreliso5_handle.get();}
const float& STOP_BABY::trkreliso10() {return trkreliso10_handle.get();}
const float& STOP_BABY::trkpt5loose() {return trkpt5loose_handle.get();}
const float& STOP_BABY::trkpt10loose() {return trkpt10loose_handle.get();}
const float& STOP_BABY::trkreliso5loose() {return trkreliso5loose_handle.get();}
const float& STOP_BABY::trkreliso10loose() {return trkreliso10loose_handle.get();}
const float& STOP_BABY::trkpt10pt0p1() {return trkpt10pt0p1_handle.get();}
const float& STOP_BABY::trkpt10pt0p2() {return trkpt10pt0p2_handle.get();}
const float& STOP_BABY::trkpt10pt0p3() {return trkpt10pt0p3_handle.get();}
const float& STOP_BABY::trkpt10pt0p4() {return trkpt10pt0p4_handle.get();}
const float& STOP_BABY::trkpt10pt0p5() {return trkpt10pt0p5_handle.get();}
const float& STOP_BABY::trkpt10pt0p6() {return trkpt10pt0p6_handle.get();}
const float& STOP_BABY::trkpt10pt0p7() {return trkpt10pt0p7_handle.get();}
const float& STOP_BABY::trkpt10pt0p8() {return trkpt10pt0p8_handle.get();}
const float& STOP_BABY::trkpt10pt0p9() {return trkpt10pt0p9_handle.get();}
const float& STOP_BABY::trkpt10pt1p0() {return trkpt10pt1p0_handle.get();}
const float& STOP_BABY::trkreliso10pt0p1() {return trkreliso10pt0p1_handle.get();}
const float& STOP_BABY::trkreliso10pt0p2() {return trkreliso10pt0p2_handle.get();}
const float& STOP_BABY::trkreliso10pt0p3() {return trkreliso10pt0p3_handle.get();}
const float& STOP_BABY::trkreliso10pt0p4() {return trkreliso10pt0p4_handle.get();}
const float& STOP_BABY::trkreliso10pt0p5() {return trkreliso10pt0p5_handle.get();}
const float& STOP_BABY::trkreliso10pt0p6() {return trkreliso10pt0p6_handle.get();}
const float& STOP_BABY::trkreliso10pt0p7() {return trkreliso10pt0p7_handle.get();}
const float& STOP_BABY::trkreliso10pt0p8() {return trkreliso10pt0p8_handle.get();}
const float& STOP_BABY::trkreliso10pt0p9() {return trkreliso10pt0p9_handle.get();}
const float& STOP_BABY::trkreliso10pt1p0() {return trkreliso10pt1p0_handle.get();}
const float& STOP_BABY::pfcandpt10pt0p1() {return pfcandpt10pt0p1_handle.get();}
const float& STOP_BABY::pfcandpt10pt0p2() {return pfcandpt10pt0p2_handle.get();}
const float& STOP_BABY::pfcandpt10pt0p3() {return pfcandpt10pt0p3_handle.get();}
const float& STOP_BABY::pfcandpt10pt0p4() {return pfcandpt10pt0p4_handle.get();}
const float& STOP_BABY::pfcandpt10pt0p5() {return pfcandpt10pt0p5_handle.get();}
const float& STOP_BABY::pfcandpt10pt0p6() {return pfcandpt10pt0p6_handle.get();}
const float& STOP_BABY::pfcandpt10pt0p7() {return pfcandpt10pt0p7_handle.get();}
const float& STOP_BABY::pfcandpt10pt0p8() {return pfcandpt10pt0p8_handle.get();}
const float& STOP_BABY::pfcandpt10pt0p9() {return pfcandpt10pt0p9_handle.get();}
const float& STOP_BABY::pfcandpt10pt1p0() {return pfcandpt10pt1p0_handle.get();}
const float& STOP_BABY::pfcandiso10pt0p1() {return pfcandiso10pt0p1_handle.get();}
const float& STOP_BABY::pfcandiso10pt0p2() {return pfcandiso10pt0p2_handle.get();}
const float& STOP_BABY::pfcandiso10pt0p3() {return pfcandiso10pt0p3_handle.get();}
const float& STOP_BABY::pfcandiso10pt0p4() {return pfcandiso10pt0p4_handle.get();}
const float& STOP_BABY::pfcandiso10pt0p5() {return pfcandiso10pt0p5_handle.get();}
const float& STOP_BABY::pfcandiso10pt0p6() {return pfcandiso10pt0p6_handle.get();}
const float& STOP_BABY::pfcandiso10pt0p7() {return pfcandiso10pt0p7_handle.get();}
const float& STOP_BABY::pfcandiso10pt0p8() {return pfcandiso10pt0p8_handle.get();}
const float& STOP_BABY::pfcandiso10pt0p9() {return pfcandiso10pt0p9_handle.get();}
const float& STOP_BABY::pfcandiso10pt1p0() {return pfcandiso10pt1p0_handle.get();}
const float& STOP_BABY::mbb() {return mbb_handle.get();}
const float& STOP_BABY::lep1pfjetdr() {return lep1pfjetdr_handle.get();}
const float& STOP_BABY::lep2pfjetdr() {return lep2pfjetdr_handle.get();}
const LorentzVector& STOP_BABY::mclep() {return mclep_handle.get();}
const LorentzVector& STOP_BABY::mcnu() {return mcnu_handle.get();}
const float& STOP_BABY::mcmln() {return mcmln_handle.get();}
const float& STOP_BABY::mcmtln() {return mcmtln_handle.get();}
const LorentzVector& STOP_BABY::mlep() {return mlep_handle.get();}
const LorentzVector& STOP_BABY::lep1() {return lep1_handle.get();}
const LorentzVector& STOP_BABY::lep2() {return lep2_handle.get();}
const LorentzVector& STOP_BABY::trklep1() {return trklep1_handle.get();}
const LorentzVector& STOP_BABY::trklep2() {return trklep2_handle.get();}
const LorentzVector& STOP_BABY::gfitlep1() {return gfitlep1_handle.get();}
const LorentzVector& STOP_BABY::gfitlep2() {return gfitlep2_handle.get();}
const LorentzVector& STOP_BABY::lepp() {return lepp_handle.get();}
const LorentzVector& STOP_BABY::lepm() {return lepm_handle.get();}
const LorentzVector& STOP_BABY::pflep1() {return pflep1_handle.get();}
const LorentzVector& STOP_BABY::pflep2() {return pflep2_handle.get();}
const LorentzVector& STOP_BABY::leppfjet1() {return leppfjet1_handle.get();}
const LorentzVector& STOP_BABY::leppfjet2() {return leppfjet2_handle.get();}
const LorentzVector& STOP_BABY::mclep1() {return mclep1_handle.get();}
const LorentzVector& STOP_BABY::mclep2() {return mclep2_handle.get();}
const LorentzVector& STOP_BABY::mctaud1() {return mctaud1_handle.get();}
const LorentzVector& STOP_BABY::mctaud2() {return mctaud2_handle.get();}
const LorentzVector& STOP_BABY::mctaudvis1() {return mctaudvis1_handle.get();}
const LorentzVector& STOP_BABY::mctaudvis2() {return mctaudvis2_handle.get();}
const LorentzVector& STOP_BABY::pflep() {return pflep_handle.get();}
const LorentzVector& STOP_BABY::pftaud() {return pftaud_handle.get();}
const LorentzVector& STOP_BABY::pfcand5() {return pfcand5_handle.get();}
const LorentzVector& STOP_BABY::pfcand10() {return pfcand10_handle.get();}
const int& STOP_BABY::pfTau15_leadPtcandID() {return pfTau15_leadPtcandID_handle.get();}
const LorentzVector& STOP_BABY::pfTau15() {return pfTau15_handle.get();}
const LorentzVector& STOP_BABY::pfTau15_leadPtcand() {return pfTau15_leadPtcand_handle.get();}
const int& STOP_BABY::pfTau_leadPtcandID() {return pfTau_leadPtcandID_handle.get();}
const LorentzVector& STOP_BABY::pfTau() {return pfTau_handle.get();}
const LorentzVector& STOP_BABY::pfTau_leadPtcand() {return pfTau_leadPtcand_handle.get();}
const int& STOP_BABY::pfTauLoose_leadPtcandID() {return pfTauLoose_leadPtcandID_handle.get();}
const LorentzVector& STOP_BABY::pfTauLoose() {return pfTauLoose_handle.get();}
const LorentzVector& STOP_BABY::pfTauLoose_leadPtcand() {return pfTauLoose_leadPtcand_handle.get();}
const LorentzVector& STOP_BABY::pfcandOS10() {return pfcandOS10_handle.get();}
const LorentzVector& STOP_BABY::pfcandOS10looseZ() {return pfcandOS10looseZ_handle.get();}
const LorentzVector& STOP_BABY::pfcand5looseZ() {return pfcand5looseZ_handle.get();}
const LorentzVector& STOP_BABY::pfcanddir10() {return pfcanddir10_handle.get();}
const LorentzVector& STOP_BABY::pfcandveto10() {return pfcandveto10_handle.get();}
const LorentzVector& STOP_BABY::pfcandvetoL10() {return pfcandvetoL10_handle.get();}
const LorentzVector& STOP_BABY::jet() {return jet_handle.get();}
const LorentzVector& STOP_BABY::nonisoel() {return nonisoel_handle.get();}
const LorentzVector& STOP_BABY::nonisomu() {return nonisomu_handle.get();}
const LorentzVector& STOP_BABY::t() {return t_handle.get();}
const LorentzVector& STOP_BABY::tbar() {return tbar_handle.get();}
const LorentzVector& STOP_BABY::ttbar() {return ttbar_handle.get();}
const LorentzVector& STOP_BABY::lep_t() {return lep_t_handle.get();}
const LorentzVector& STOP_BABY::lep_tbar() {return lep_tbar_handle.get();}
const LorentzVector& STOP_BABY::stop_t() {return stop_t_handle.get();}
const LorentzVector& STOP_BABY::stop_tbar() {return stop_tbar_handle.get();}
const LorentzVector& STOP_BABY::neutralino_t() {return neutralino_t_handle.get();}
const LorentzVector& STOP_BABY::neutralino_tbar() {return neutralino_tbar_handle.get();}
const int& STOP_BABY::lep_t_id() {return lep_t_id_handle.get();}
const int& STOP_BABY::lep_tbar_id() {return lep_tbar_id_handle.get();}
const std::vector<LorentzVector >& STOP_BABY::pfjets() {return pfjets_handle.get();}
const std::vector<LorentzVector >& STOP_BABY::pfjets_genJet_() {return pfjets_genJet__handle.get();}
const std::vector<float>& STOP_BABY::pfjets_csv() {return pfjets_csv_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_chm() {return pfjets_chm_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_neu() {return pfjets_neu_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_l1corr() {return pfjets_l1corr_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_corr() {return pfjets_corr_handle.get();}
const std::vector<int>& STOP_BABY::pfjets_mc3() {return pfjets_mc3_handle.get();}
const std::vector<int>& STOP_BABY::pfjets_mcflavorAlgo() {return pfjets_mcflavorAlgo_handle.get();}
const std::vector<int>& STOP_BABY::pfjets_mcflavorPhys() {return pfjets_mcflavorPhys_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_uncertainty() {return pfjets_uncertainty_handle.get();}
const std::vector<int>& STOP_BABY::pfjets_flav() {return pfjets_flav_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_lrm() {return pfjets_lrm_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_lrm2() {return pfjets_lrm2_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_qgtag() {return pfjets_qgtag_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_genJetDr() {return pfjets_genJetDr_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_sigma() {return pfjets_sigma_handle.get();}
const std::vector<int>& STOP_BABY::pfjets_lepjet() {return pfjets_lepjet_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_beta() {return pfjets_beta_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_beta2() {return pfjets_beta2_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_beta_0p1() {return pfjets_beta_0p1_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_beta_0p2() {return pfjets_beta_0p2_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_beta2_0p1() {return pfjets_beta2_0p1_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_beta2_0p5() {return pfjets_beta2_0p5_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_mvaPUid() {return pfjets_mvaPUid_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_mva5xPUid() {return pfjets_mva5xPUid_handle.get();}
const std::vector<float>& STOP_BABY::pfjets_mvaBeta() {return pfjets_mvaBeta_handle.get();}
const std::vector<LorentzVector >& STOP_BABY::genbs() {return genbs_handle.get();}
const std::vector<int>& STOP_BABY::genps_pdgId() {return genps_pdgId_handle.get();}
const std::vector<int>& STOP_BABY::genps_firstMother() {return genps_firstMother_handle.get();}
const std::vector<float>& STOP_BABY::genps_energy() {return genps_energy_handle.get();}
const std::vector<float>& STOP_BABY::genps_pt() {return genps_pt_handle.get();}
const std::vector<float>& STOP_BABY::genps_eta() {return genps_eta_handle.get();}
const std::vector<float>& STOP_BABY::genps_phi() {return genps_phi_handle.get();}
const std::vector<float>& STOP_BABY::genps_mass() {return genps_mass_handle.get();}
const float& STOP_BABY::mini_mt() {return mini_mt_handle.get();}
const float& STOP_BABY::mini_mtup() {return mini_mtup_handle.get();}
const float& STOP_BABY::mini_mtdown() {return mini_mtdown_handle.get();}
const float& STOP_BABY::mini_isrweight() {return mini_isrweight_handle.get();}
const float& STOP_BABY::mini_met() {return mini_met_handle.get();}
const float& STOP_BABY::mini_metup() {return mini_metup_handle.get();}
const float& STOP_BABY::mini_metdown() {return mini_metdown_handle.get();}
const int& STOP_BABY::mini_sig() {return mini_sig_handle.get();}
const int& STOP_BABY::mini_cr1() {return mini_cr1_handle.get();}
const int& STOP_BABY::mini_cr4() {return mini_cr4_handle.get();}
const int& STOP_BABY::mini_cr5() {return mini_cr5_handle.get();}
const int& STOP_BABY::mini_whsig() {return mini_whsig_handle.get();}
const int& STOP_BABY::mini_whcr1() {return mini_whcr1_handle.get();}
const float& STOP_BABY::mini_chi2() {return mini_chi2_handle.get();}
const float& STOP_BABY::mini_chi2up() {return mini_chi2up_handle.get();}
const float& STOP_BABY::mini_chi2down() {return mini_chi2down_handle.get();}
const float& STOP_BABY::mini_chi2bup() {return mini_chi2bup_handle.get();}
const float& STOP_BABY::mini_chi2bdown() {return mini_chi2bdown_handle.get();}
const float& STOP_BABY::mini_mt2b() {return mini_mt2b_handle.get();}
const float& STOP_BABY::mini_mt2bl() {return mini_mt2bl_handle.get();}
const float& STOP_BABY::mini_mt2w() {return mini_mt2w_handle.get();}
const float& STOP_BABY::mini_mt2wup() {return mini_mt2wup_handle.get();}
const float& STOP_BABY::mini_mt2wdown() {return mini_mt2wdown_handle.get();}
const float& STOP_BABY::mini_mt2wbup() {return mini_mt2wbup_handle.get();}
const float& STOP_BABY::mini_mt2wbdown() {return mini_mt2wbdown_handle.get();}
const float& STOP_BABY::mini_weight() {return mini_weight_handle.get();}
const float& STOP_BABY::mini_nvtxweight() {return mini_nvtxweight_handle.get();}
const float& STOP_BABY::mini_sltrigeff() {return mini_sltrigeff_handle.get();}
const float& STOP_BABY::mini_dltrigeff() {return mini_dltrigeff_handle.get();}
const int& STOP_BABY::mini_nsigevents() {return mini_nsigevents_handle.get();}
const int& STOP_BABY::mini_nb() {return mini_nb_handle.get();}
const int& STOP_BABY::mini_nbupBC() {return mini_nbupBC_handle.get();}
const int& STOP_BABY::mini_nbdownBC() {return mini_nbdownBC_handle.get();}
const int& STOP_BABY::mini_nbupL() {return mini_nbupL_handle.get();}
const int& STOP_BABY::mini_nbdownL() {return mini_nbdownL_handle.get();}
const int& STOP_BABY::mini_njets() {return mini_njets_handle.get();}
const int& STOP_BABY::mini_njetsup() {return mini_njetsup_handle.get();}
const int& STOP_BABY::mini_njetsdown() {return mini_njetsdown_handle.get();}
const int& STOP_BABY::mini_passisotrk() {return mini_passisotrk_handle.get();}
const int& STOP_BABY::mini_passtauveto() {return mini_passtauveto_handle.get();}
const int& STOP_BABY::mini_nlep() {return mini_nlep_handle.get();}
const float& STOP_BABY::mini_lep1pt() {return mini_lep1pt_handle.get();}
const float& STOP_BABY::mini_lep1eta() {return mini_lep1eta_handle.get();}
const float& STOP_BABY::mini_lep2pt() {return mini_lep2pt_handle.get();}
const float& STOP_BABY::mini_lep2eta() {return mini_lep2eta_handle.get();}
const float& STOP_BABY::mini_dilmass() {return mini_dilmass_handle.get();}
const float& STOP_BABY::mini_mstop() {return mini_mstop_handle.get();}
const float& STOP_BABY::mini_mlsp() {return mini_mlsp_handle.get();}
const float& STOP_BABY::mini_x() {return mini_x_handle.get();}
const float& STOP_BABY::mini_xsecsusy() {return mini_xsecsusy_handle.get();}
const float& STOP_BABY::mini_dRleptB1() {return mini_dRleptB1_handle.get();}
const float& STOP_BABY::mini_dRleptB1_bup() {return mini_dRleptB1_bup_handle.get();}
const float& STOP_BABY::mini_dRleptB1_bdown() {return mini_dRleptB1_bdown_handle.get();}
const float& STOP_BABY::mini_htssl() {return mini_htssl_handle.get();}
const float& STOP_BABY::mini_htosl() {return mini_htosl_handle.get();}
const float& STOP_BABY::mini_htratiol() {return mini_htratiol_handle.get();}
const float& STOP_BABY::mini_htssm() {return mini_htssm_handle.get();}
const float& STOP_BABY::mini_htosm() {return mini_htosm_handle.get();}
const float& STOP_BABY::mini_htratiom() {return mini_htratiom_handle.get();}
const float& STOP_BABY::mini_htratiomup() {return mini_htratiomup_handle.get();}
const float& STOP_BABY::mini_htratiomdown() {return mini_htratiomdown_handle.get();}
const float& STOP_BABY::mini_dphimj1() {return mini_dphimj1_handle.get();}
const float& STOP_BABY::mini_dphimj2() {return mini_dphimj2_handle.get();}
const float& STOP_BABY::mini_dphimjmin() {return mini_dphimjmin_handle.get();}
const float& STOP_BABY::mini_pt_b() {return mini_pt_b_handle.get();}
const float& STOP_BABY::mini_pt_b_up() {return mini_pt_b_up_handle.get();}
const float& STOP_BABY::mini_pt_b_down() {return mini_pt_b_down_handle.get();}
const float& STOP_BABY::mini_pt_b_bup() {return mini_pt_b_bup_handle.get();}
const float& STOP_BABY::mini_pt_b_bdown() {return mini_pt_b_bdown_handle.get();}
const float& STOP_BABY::mini_pt_J1() {return mini_pt_J1_handle.get();}
const float& STOP_BABY::mini_pt_J2() {return mini_pt_J2_handle.get();}
const float& STOP_BABY::mini_bbmass() {return mini_bbmass_handle.get();}
const float& STOP_BABY::mini_bbpt() {return mini_bbpt_handle.get();}
const float& STOP_BABY::mini_wpt() {return mini_wpt_handle.get();}
const float& STOP_BABY::mini_bbwdphi() {return mini_bbwdphi_handle.get();}
const float& STOP_BABY::mini_rand() {return mini_rand_handle.get();}
const float& STOP_BABY::mini_t2ttLM() {return mini_t2ttLM_handle.get();}
const float& STOP_BABY::mini_t2ttHM() {return mini_t2ttHM_handle.get();}
const std::vector<float>& STOP_BABY::mini_bdt() {return mini_bdt_handle.get();}
const std::vector<float>& STOP_BABY::mini_bdtup() {return mini_bdtup_handle.get();}
const std::vector<float>& STOP_BABY::mini_bdtdown() {return mini_bdtdown_handle.get();}
const std::vector<float>& STOP_BABY::mini_bdtbup() {return mini_bdtbup_handle.get();}
const std::vector<float>& STOP_BABY::mini_bdtbdown() {return mini_bdtbdown_handle.get();}




/*static*/ void STOP_BABY::progress(const int nEventsTotal, const int nEventsChain)
{
    int period = 1000;
    if (nEventsTotal%1000 == 0)
    {
        // xterm magic from L. Vacavant and A. Cerri
        if (isatty(1))
        {
            if ((nEventsChain - nEventsTotal) > period)
            {
                float frac = (float)nEventsTotal/(nEventsChain*0.01);
                printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%\033[0m\033[32m <---\033[0m\015", frac);
                fflush(stdout);
            }
            else
            {
                printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%\033[0m\033[32m <---\033[0m\015", 100.0);
                std::cout << std::endl;
            }
        }
    }
}
namespace stop
{

    const int& acc_2010() {return stop_baby_obj.acc_2010();}
    const int& acc_highmet() {return stop_baby_obj.acc_highmet();}
    const int& acc_highht() {return stop_baby_obj.acc_highht();}
    const int& eldup() {return stop_baby_obj.eldup();}
    const int& csc() {return stop_baby_obj.csc();}
    const int& hbhe() {return stop_baby_obj.hbhe();}
    const int& hbhenew() {return stop_baby_obj.hbhenew();}
    const int& hcallaser() {return stop_baby_obj.hcallaser();}
    const int& ecaltp() {return stop_baby_obj.ecaltp();}
    const int& trkfail() {return stop_baby_obj.trkfail();}
    const int& eebadsc() {return stop_baby_obj.eebadsc();}
    const int& lep1_badecallaser() {return stop_baby_obj.lep1_badecallaser();}
    const int& lep2_badecallaser() {return stop_baby_obj.lep2_badecallaser();}
    const int& isdata() {return stop_baby_obj.isdata();}
    const int& jetid() {return stop_baby_obj.jetid();}
    const int& jetid30() {return stop_baby_obj.jetid30();}
    const int& json() {return stop_baby_obj.json();}
    const float& htoffset() {return stop_baby_obj.htoffset();}
    const float& htuncor() {return stop_baby_obj.htuncor();}
    const float& ptt() {return stop_baby_obj.ptt();}
    const float& pttbar() {return stop_baby_obj.pttbar();}
    const float& ptttbar() {return stop_baby_obj.ptttbar();}
    const float& mttbar() {return stop_baby_obj.mttbar();}
    const int& npartons() {return stop_baby_obj.npartons();}
    const int& nwzpartons() {return stop_baby_obj.nwzpartons();}
    const int& hyptype() {return stop_baby_obj.hyptype();}
    const float& maxpartonpt() {return stop_baby_obj.maxpartonpt();}
    const float& etattbar() {return stop_baby_obj.etattbar();}
    const int& njetsoffset() {return stop_baby_obj.njetsoffset();}
    const int& njetsuncor() {return stop_baby_obj.njetsuncor();}
    const float& costhetaweight() {return stop_baby_obj.costhetaweight();}
    const float& weight() {return stop_baby_obj.weight();}
    const float& weightleft() {return stop_baby_obj.weightleft();}
    const float& weightright() {return stop_baby_obj.weightright();}
    const float& mutrigweight() {return stop_baby_obj.mutrigweight();}
    const float& mutrigweight2() {return stop_baby_obj.mutrigweight2();}
    const float& sltrigweight() {return stop_baby_obj.sltrigweight();}
    const float& dltrigweight() {return stop_baby_obj.dltrigweight();}
    const float& trgeff() {return stop_baby_obj.trgeff();}
    const float& pthat() {return stop_baby_obj.pthat();}
    const float& qscale() {return stop_baby_obj.qscale();}
    const float& mgcor() {return stop_baby_obj.mgcor();}
    const int& wflav() {return stop_baby_obj.wflav();}
    const float& ksusy() {return stop_baby_obj.ksusy();}
    const float& ksusyup() {return stop_baby_obj.ksusyup();}
    const float& ksusydn() {return stop_baby_obj.ksusydn();}
    const float& xsecsusy() {return stop_baby_obj.xsecsusy();}
    const float& xsecsusy2() {return stop_baby_obj.xsecsusy2();}
    const float& smeff() {return stop_baby_obj.smeff();}
    const float& k() {return stop_baby_obj.k();}
    const float& mllgen() {return stop_baby_obj.mllgen();}
    const float& ptwgen() {return stop_baby_obj.ptwgen();}
    const float& ptzgen() {return stop_baby_obj.ptzgen();}
    const int& nlep() {return stop_baby_obj.nlep();}
    const int& nosel() {return stop_baby_obj.nosel();}
    const int& ngoodlep() {return stop_baby_obj.ngoodlep();}
    const int& ngoodel() {return stop_baby_obj.ngoodel();}
    const int& ngoodmu() {return stop_baby_obj.ngoodmu();}
    const int& mull() {return stop_baby_obj.mull();}
    const int& mult() {return stop_baby_obj.mult();}
    const int& mullgen() {return stop_baby_obj.mullgen();}
    const int& multgen() {return stop_baby_obj.multgen();}
    const int& proc() {return stop_baby_obj.proc();}
    const int& leptype() {return stop_baby_obj.leptype();}
    const float& topmass() {return stop_baby_obj.topmass();}
    const float& dilmass() {return stop_baby_obj.dilmass();}
    const float& dilrecoil() {return stop_baby_obj.dilrecoil();}
    const float& dilrecoilparl() {return stop_baby_obj.dilrecoilparl();}
    const float& dilrecoilperp() {return stop_baby_obj.dilrecoilperp();}
    const float& tcmet() {return stop_baby_obj.tcmet();}
    const float& genmet() {return stop_baby_obj.genmet();}
    const float& gensumet() {return stop_baby_obj.gensumet();}
    const float& genmetphi() {return stop_baby_obj.genmetphi();}
    const float& calomet() {return stop_baby_obj.calomet();}
    const float& calometphi() {return stop_baby_obj.calometphi();}
    const float& trkmet() {return stop_baby_obj.trkmet();}
    const float& trkmetphi() {return stop_baby_obj.trkmetphi();}
    const float& trkmet_nolepcorr() {return stop_baby_obj.trkmet_nolepcorr();}
    const float& trkmetphi_nolepcorr() {return stop_baby_obj.trkmetphi_nolepcorr();}
    const float& pfmet() {return stop_baby_obj.pfmet();}
    const float& pfmetveto() {return stop_baby_obj.pfmetveto();}
    const float& pfmetsig() {return stop_baby_obj.pfmetsig();}
    const float& pfmetphi() {return stop_baby_obj.pfmetphi();}
    const float& pfsumet() {return stop_baby_obj.pfsumet();}
    const float& mucormet() {return stop_baby_obj.mucormet();}
    const float& mucorjesmet() {return stop_baby_obj.mucorjesmet();}
    const float& tcmet35X() {return stop_baby_obj.tcmet35X();}
    const float& tcmetevent() {return stop_baby_obj.tcmetevent();}
    const float& tcmetlooper() {return stop_baby_obj.tcmetlooper();}
    const float& tcmetphi() {return stop_baby_obj.tcmetphi();}
    const float& tcsumet() {return stop_baby_obj.tcsumet();}
    const float& tcmetUp() {return stop_baby_obj.tcmetUp();}
    const float& tcmetDown() {return stop_baby_obj.tcmetDown();}
    const float& tcmetTest() {return stop_baby_obj.tcmetTest();}
    const float& pfmetUp() {return stop_baby_obj.pfmetUp();}
    const float& pfmetDown() {return stop_baby_obj.pfmetDown();}
    const float& pfmetTest() {return stop_baby_obj.pfmetTest();}
    const float& sumjetpt() {return stop_baby_obj.sumjetpt();}
    const float& dileta() {return stop_baby_obj.dileta();}
    const float& dilpt() {return stop_baby_obj.dilpt();}
    const float& dildphi() {return stop_baby_obj.dildphi();}
    const int& ngenjets() {return stop_baby_obj.ngenjets();}
    const int& njpt() {return stop_baby_obj.njpt();}
    const int& trgmu1() {return stop_baby_obj.trgmu1();}
    const int& trgmu2() {return stop_baby_obj.trgmu2();}
    const int& trgel1() {return stop_baby_obj.trgel1();}
    const int& trgel2() {return stop_baby_obj.trgel2();}
    const int& isomu24() {return stop_baby_obj.isomu24();}
    const int& ele27wp80() {return stop_baby_obj.ele27wp80();}
    const int& mm() {return stop_baby_obj.mm();}
    const int& mmtk() {return stop_baby_obj.mmtk();}
    const int& me() {return stop_baby_obj.me();}
    const int& em() {return stop_baby_obj.em();}
    const int& mu() {return stop_baby_obj.mu();}
    const int& ee() {return stop_baby_obj.ee();}
    const int& npfjets30() {return stop_baby_obj.npfjets30();}
    const int& npfjets30lepcorr() {return stop_baby_obj.npfjets30lepcorr();}
    const float& knjets() {return stop_baby_obj.knjets();}
    const float& rhovor() {return stop_baby_obj.rhovor();}
    const float& htpf30() {return stop_baby_obj.htpf30();}
    const float& t1met10() {return stop_baby_obj.t1met10();}
    const float& t1met20() {return stop_baby_obj.t1met20();}
    const float& t1met30() {return stop_baby_obj.t1met30();}
    const float& t1met10phi() {return stop_baby_obj.t1met10phi();}
    const float& t1met20phi() {return stop_baby_obj.t1met20phi();}
    const float& t1met30phi() {return stop_baby_obj.t1met30phi();}
    const float& t1met10mt() {return stop_baby_obj.t1met10mt();}
    const float& t1met20mt() {return stop_baby_obj.t1met20mt();}
    const float& t1met30mt() {return stop_baby_obj.t1met30mt();}
    const float& lepmetpt() {return stop_baby_obj.lepmetpt();}
    const float& lept1met10pt() {return stop_baby_obj.lept1met10pt();}
    const float& t1met10s() {return stop_baby_obj.t1met10s();}
    const float& t1met10sphi() {return stop_baby_obj.t1met10sphi();}
    const float& t1met10smt() {return stop_baby_obj.t1met10smt();}
    const float& t1metphicorr() {return stop_baby_obj.t1metphicorr();}
    const float& t1metphicorrup() {return stop_baby_obj.t1metphicorrup();}
    const float& t1metphicorrdn() {return stop_baby_obj.t1metphicorrdn();}
    const float& t1metphicorrphi() {return stop_baby_obj.t1metphicorrphi();}
    const float& t1metphicorrphiup() {return stop_baby_obj.t1metphicorrphiup();}
    const float& t1metphicorrphidn() {return stop_baby_obj.t1metphicorrphidn();}
    const float& t1metphicorrlep() {return stop_baby_obj.t1metphicorrlep();}
    const float& t1metphicorrlepphi() {return stop_baby_obj.t1metphicorrlepphi();}
    const float& t1metphicorrmt() {return stop_baby_obj.t1metphicorrmt();}
    const float& t1metphicorrmtup() {return stop_baby_obj.t1metphicorrmtup();}
    const float& t1metphicorrmtdn() {return stop_baby_obj.t1metphicorrmtdn();}
    const float& t1metphicorrlepmt() {return stop_baby_obj.t1metphicorrlepmt();}
    const float& t1met_off() {return stop_baby_obj.t1met_off();}
    const float& t1metphi_off() {return stop_baby_obj.t1metphi_off();}
    const float& t1metmt_off() {return stop_baby_obj.t1metmt_off();}
    const float& t1metphicorr_off() {return stop_baby_obj.t1metphicorr_off();}
    const float& t1metphicorrphi_off() {return stop_baby_obj.t1metphicorrphi_off();}
    const float& t1metphicorrmt_off() {return stop_baby_obj.t1metphicorrmt_off();}
    const float& mt2bmin() {return stop_baby_obj.mt2bmin();}
    const float& mt2blmin() {return stop_baby_obj.mt2blmin();}
    const float& mt2wmin() {return stop_baby_obj.mt2wmin();}
    const float& chi2min() {return stop_baby_obj.chi2min();}
    const float& chi2minprob() {return stop_baby_obj.chi2minprob();}
    const int& nbtagsssv() {return stop_baby_obj.nbtagsssv();}
    const int& nbtagstcl() {return stop_baby_obj.nbtagstcl();}
    const int& nbtagstcm() {return stop_baby_obj.nbtagstcm();}
    const int& nbtagscsvl() {return stop_baby_obj.nbtagscsvl();}
    const int& nbtagscsvm() {return stop_baby_obj.nbtagscsvm();}
    const int& nbtagscsvt() {return stop_baby_obj.nbtagscsvt();}
    const int& nbtagsssvcorr() {return stop_baby_obj.nbtagsssvcorr();}
    const int& nbtagstclcorr() {return stop_baby_obj.nbtagstclcorr();}
    const int& nbtagstcmcorr() {return stop_baby_obj.nbtagstcmcorr();}
    const int& nbtagscsvlcorr() {return stop_baby_obj.nbtagscsvlcorr();}
    const int& nbtagscsvmcorr() {return stop_baby_obj.nbtagscsvmcorr();}
    const int& nbtagscsvtcott() {return stop_baby_obj.nbtagscsvtcott();}
    const int& njetsUp() {return stop_baby_obj.njetsUp();}
    const int& njetsDown() {return stop_baby_obj.njetsDown();}
    const float& htUp() {return stop_baby_obj.htUp();}
    const float& htDown() {return stop_baby_obj.htDown();}
    const int& ntruepu() {return stop_baby_obj.ntruepu();}
    const int& npu() {return stop_baby_obj.npu();}
    const int& npuMinusOne() {return stop_baby_obj.npuMinusOne();}
    const int& npuPlusOne() {return stop_baby_obj.npuPlusOne();}
    const int& nvtx() {return stop_baby_obj.nvtx();}
    const int& indexfirstGoodVertex_() {return stop_baby_obj.indexfirstGoodVertex_();}
    const float& nvtxweight() {return stop_baby_obj.nvtxweight();}
    const float& n3dvtxweight() {return stop_baby_obj.n3dvtxweight();}
    const int& pdfid1() {return stop_baby_obj.pdfid1();}
    const int& pdfid2() {return stop_baby_obj.pdfid2();}
    const float& pdfx1() {return stop_baby_obj.pdfx1();}
    const float& pdfx2() {return stop_baby_obj.pdfx2();}
    const float& pdfQ() {return stop_baby_obj.pdfQ();}
    const float& vecjetpt() {return stop_baby_obj.vecjetpt();}
    const int& pass() {return stop_baby_obj.pass();}
    const int& passz() {return stop_baby_obj.passz();}
    const float& m0() {return stop_baby_obj.m0();}
    const float& mg() {return stop_baby_obj.mg();}
    const float& ml() {return stop_baby_obj.ml();}
    const float& x() {return stop_baby_obj.x();}
    const float& m12() {return stop_baby_obj.m12();}
    const float& lep1chi2ndf() {return stop_baby_obj.lep1chi2ndf();}
    const float& lep2chi2ndf() {return stop_baby_obj.lep2chi2ndf();}
    const float& lep1dpt() {return stop_baby_obj.lep1dpt();}
    const float& lep2dpt() {return stop_baby_obj.lep2dpt();}
    const int& id1() {return stop_baby_obj.id1();}
    const int& id2() {return stop_baby_obj.id2();}
    const int& leptype1() {return stop_baby_obj.leptype1();}
    const int& leptype2() {return stop_baby_obj.leptype2();}
    const int& w1() {return stop_baby_obj.w1();}
    const int& w2() {return stop_baby_obj.w2();}
    const float& iso1() {return stop_baby_obj.iso1();}
    const float& isont1() {return stop_baby_obj.isont1();}
    const float& isopfold1() {return stop_baby_obj.isopfold1();}
    const float& isopf1() {return stop_baby_obj.isopf1();}
    const float& etasc1() {return stop_baby_obj.etasc1();}
    const float& etasc2() {return stop_baby_obj.etasc2();}
    const float& eoverpin() {return stop_baby_obj.eoverpin();}
    const float& eoverpout() {return stop_baby_obj.eoverpout();}
    const float& dEtaIn() {return stop_baby_obj.dEtaIn();}
    const float& dPhiIn() {return stop_baby_obj.dPhiIn();}
    const float& sigmaIEtaIEta() {return stop_baby_obj.sigmaIEtaIEta();}
    const float& hOverE() {return stop_baby_obj.hOverE();}
    const float& ooemoop() {return stop_baby_obj.ooemoop();}
    const float& d0vtx() {return stop_baby_obj.d0vtx();}
    const float& dzvtx() {return stop_baby_obj.dzvtx();}
    const float& expinnerlayers() {return stop_baby_obj.expinnerlayers();}
    const float& fbrem() {return stop_baby_obj.fbrem();}
    const float& pfisoch() {return stop_baby_obj.pfisoch();}
    const float& pfisoem() {return stop_baby_obj.pfisoem();}
    const float& pfisonh() {return stop_baby_obj.pfisonh();}
    const float& eSC() {return stop_baby_obj.eSC();}
    const float& phiSC() {return stop_baby_obj.phiSC();}
    const float& eSCRaw() {return stop_baby_obj.eSCRaw();}
    const float& eSCPresh() {return stop_baby_obj.eSCPresh();}
    const float& lep1_scslasercormean() {return stop_baby_obj.lep1_scslasercormean();}
    const float& lep1_scslasercormax() {return stop_baby_obj.lep1_scslasercormax();}
    const float& eoverpin2() {return stop_baby_obj.eoverpin2();}
    const float& eoverpout2() {return stop_baby_obj.eoverpout2();}
    const float& dEtaIn2() {return stop_baby_obj.dEtaIn2();}
    const float& dPhiIn2() {return stop_baby_obj.dPhiIn2();}
    const float& sigmaIEtaIEta2() {return stop_baby_obj.sigmaIEtaIEta2();}
    const float& hOverE2() {return stop_baby_obj.hOverE2();}
    const float& ooemoop2() {return stop_baby_obj.ooemoop2();}
    const float& d0vtx2() {return stop_baby_obj.d0vtx2();}
    const float& dzvtx2() {return stop_baby_obj.dzvtx2();}
    const float& expinnerlayers2() {return stop_baby_obj.expinnerlayers2();}
    const float& fbrem2() {return stop_baby_obj.fbrem2();}
    const float& pfisoch2() {return stop_baby_obj.pfisoch2();}
    const float& pfisoem2() {return stop_baby_obj.pfisoem2();}
    const float& pfisonh2() {return stop_baby_obj.pfisonh2();}
    const float& eSC2() {return stop_baby_obj.eSC2();}
    const float& phiSC2() {return stop_baby_obj.phiSC2();}
    const float& eSCRaw2() {return stop_baby_obj.eSCRaw2();}
    const float& eSCPresh2() {return stop_baby_obj.eSCPresh2();}
    const float& lep2_scslasercormean() {return stop_baby_obj.lep2_scslasercormean();}
    const float& lep2_scslasercormax() {return stop_baby_obj.lep2_scslasercormax();}
    const float& scslasercormax() {return stop_baby_obj.scslasercormax();}
    const float& scslasercormax_pt() {return stop_baby_obj.scslasercormax_pt();}
    const float& scslasercormax_eta() {return stop_baby_obj.scslasercormax_eta();}
    const float& iso2() {return stop_baby_obj.iso2();}
    const float& ecalveto1() {return stop_baby_obj.ecalveto1();}
    const float& ecalveto2() {return stop_baby_obj.ecalveto2();}
    const float& hcalveto1() {return stop_baby_obj.hcalveto1();}
    const float& hcalveto2() {return stop_baby_obj.hcalveto2();}
    const float& isont2() {return stop_baby_obj.isont2();}
    const float& isopf2() {return stop_baby_obj.isopf2();}
    const float& ptl1() {return stop_baby_obj.ptl1();}
    const float& ptl2() {return stop_baby_obj.ptl2();}
    const float& etal1() {return stop_baby_obj.etal1();}
    const float& etal2() {return stop_baby_obj.etal2();}
    const float& phil1() {return stop_baby_obj.phil1();}
    const float& phil2() {return stop_baby_obj.phil2();}
    const float& meff() {return stop_baby_obj.meff();}
    const float& mt() {return stop_baby_obj.mt();}
    const char& dataset() {return stop_baby_obj.dataset();}
    const unsigned int& run() {return stop_baby_obj.run();}
    const unsigned int& lumi() {return stop_baby_obj.lumi();}
    const unsigned int& event() {return stop_baby_obj.event();}
    const float& y() {return stop_baby_obj.y();}
    const float& ht() {return stop_baby_obj.ht();}
    const float& htgen() {return stop_baby_obj.htgen();}
    const float& htjpt() {return stop_baby_obj.htjpt();}
    const int& nels() {return stop_baby_obj.nels();}
    const int& nmus() {return stop_baby_obj.nmus();}
    const int& ntaus() {return stop_baby_obj.ntaus();}
    const int& nleps() {return stop_baby_obj.nleps();}
    const int& nbs() {return stop_baby_obj.nbs();}
    const float& dphijm() {return stop_baby_obj.dphijm();}
    const float& ptjetraw() {return stop_baby_obj.ptjetraw();}
    const float& ptjet23() {return stop_baby_obj.ptjet23();}
    const float& ptjetF23() {return stop_baby_obj.ptjetF23();}
    const float& ptjetO23() {return stop_baby_obj.ptjetO23();}
    const int& mcid1() {return stop_baby_obj.mcid1();}
    const float& mcdr1() {return stop_baby_obj.mcdr1();}
    const int& mcdecay1() {return stop_baby_obj.mcdecay1();}
    const int& mcndec1() {return stop_baby_obj.mcndec1();}
    const int& mcndec2() {return stop_baby_obj.mcndec2();}
    const int& mcndeckls1() {return stop_baby_obj.mcndeckls1();}
    const int& mcndeckls2() {return stop_baby_obj.mcndeckls2();}
    const int& mcndecem1() {return stop_baby_obj.mcndecem1();}
    const int& mcndecem2() {return stop_baby_obj.mcndecem2();}
    const int& mcid2() {return stop_baby_obj.mcid2();}
    const float& mcdr2() {return stop_baby_obj.mcdr2();}
    const int& mcdecay2() {return stop_baby_obj.mcdecay2();}
    const float& mctaudpt1() {return stop_baby_obj.mctaudpt1();}
    const float& mctaudpt2() {return stop_baby_obj.mctaudpt2();}
    const int& mctaudid1() {return stop_baby_obj.mctaudid1();}
    const int& mctaudid2() {return stop_baby_obj.mctaudid2();}
    const int& mlepid() {return stop_baby_obj.mlepid();}
    const int& mleppassid() {return stop_baby_obj.mleppassid();}
    const int& mleppassiso() {return stop_baby_obj.mleppassiso();}
    const float& mlepiso() {return stop_baby_obj.mlepiso();}
    const float& mlepdr() {return stop_baby_obj.mlepdr();}
    const float& pflepiso() {return stop_baby_obj.pflepiso();}
    const float& pflepdr() {return stop_baby_obj.pflepdr();}
    const float& pfleppt() {return stop_baby_obj.pfleppt();}
    const float& pflepmindrj() {return stop_baby_obj.pflepmindrj();}
    const float& pftaudiso() {return stop_baby_obj.pftaudiso();}
    const float& pftauddr() {return stop_baby_obj.pftauddr();}
    const float& pftaudpt() {return stop_baby_obj.pftaudpt();}
    const float& pftaudmindrj() {return stop_baby_obj.pftaudmindrj();}
    const int& pfcandid5() {return stop_baby_obj.pfcandid5();}
    const float& pfcandiso5() {return stop_baby_obj.pfcandiso5();}
    const float& pfcandpt5() {return stop_baby_obj.pfcandpt5();}
    const float& pfcanddz5() {return stop_baby_obj.pfcanddz5();}
    const float& pfcandmindrj5() {return stop_baby_obj.pfcandmindrj5();}
    const int& pfcandid10() {return stop_baby_obj.pfcandid10();}
    const float& pfcandiso10() {return stop_baby_obj.pfcandiso10();}
    const float& pfcandpt10() {return stop_baby_obj.pfcandpt10();}
    const float& pfcanddz10() {return stop_baby_obj.pfcanddz10();}
    const float& pfcandmindrj10() {return stop_baby_obj.pfcandmindrj10();}
    const int& pfcandidOS10() {return stop_baby_obj.pfcandidOS10();}
    const float& pfcandisoOS10() {return stop_baby_obj.pfcandisoOS10();}
    const float& pfcandptOS10() {return stop_baby_obj.pfcandptOS10();}
    const float& pfcanddzOS10() {return stop_baby_obj.pfcanddzOS10();}
    const int& pfcandid5looseZ() {return stop_baby_obj.pfcandid5looseZ();}
    const float& pfcandiso5looseZ() {return stop_baby_obj.pfcandiso5looseZ();}
    const float& pfcandpt5looseZ() {return stop_baby_obj.pfcandpt5looseZ();}
    const float& pfcanddz5looseZ() {return stop_baby_obj.pfcanddz5looseZ();}
    const int& pfcandidOS10looseZ() {return stop_baby_obj.pfcandidOS10looseZ();}
    const float& pfcandisoOS10looseZ() {return stop_baby_obj.pfcandisoOS10looseZ();}
    const float& pfcandptOS10looseZ() {return stop_baby_obj.pfcandptOS10looseZ();}
    const float& pfcanddzOS10looseZ() {return stop_baby_obj.pfcanddzOS10looseZ();}
    const int& pfcanddirid10() {return stop_baby_obj.pfcanddirid10();}
    const float& pfcanddiriso10() {return stop_baby_obj.pfcanddiriso10();}
    const float& pfcanddirpt10() {return stop_baby_obj.pfcanddirpt10();}
    const float& pfcanddirmindrj10() {return stop_baby_obj.pfcanddirmindrj10();}
    const int& pfcandvetoid10() {return stop_baby_obj.pfcandvetoid10();}
    const float& pfcandvetoiso10() {return stop_baby_obj.pfcandvetoiso10();}
    const float& pfcandvetopt10() {return stop_baby_obj.pfcandvetopt10();}
    const float& pfcandvetomindrj10() {return stop_baby_obj.pfcandvetomindrj10();}
    const int& pfcandvetoLid10() {return stop_baby_obj.pfcandvetoLid10();}
    const float& pfcandvetoLiso10() {return stop_baby_obj.pfcandvetoLiso10();}
    const float& pfcandvetoLpt10() {return stop_baby_obj.pfcandvetoLpt10();}
    const float& pfcandvetoLmindrj10() {return stop_baby_obj.pfcandvetoLmindrj10();}
    const float& emjet10() {return stop_baby_obj.emjet10();}
    const float& mjj() {return stop_baby_obj.mjj();}
    const float& emjet20() {return stop_baby_obj.emjet20();}
    const float& trkpt5() {return stop_baby_obj.trkpt5();}
    const float& trkpt10() {return stop_baby_obj.trkpt10();}
    const float& mleptrk5() {return stop_baby_obj.mleptrk5();}
    const float& mleptrk10() {return stop_baby_obj.mleptrk10();}
    const float& trkreliso5() {return stop_baby_obj.trkreliso5();}
    const float& trkreliso10() {return stop_baby_obj.trkreliso10();}
    const float& trkpt5loose() {return stop_baby_obj.trkpt5loose();}
    const float& trkpt10loose() {return stop_baby_obj.trkpt10loose();}
    const float& trkreliso5loose() {return stop_baby_obj.trkreliso5loose();}
    const float& trkreliso10loose() {return stop_baby_obj.trkreliso10loose();}
    const float& trkpt10pt0p1() {return stop_baby_obj.trkpt10pt0p1();}
    const float& trkpt10pt0p2() {return stop_baby_obj.trkpt10pt0p2();}
    const float& trkpt10pt0p3() {return stop_baby_obj.trkpt10pt0p3();}
    const float& trkpt10pt0p4() {return stop_baby_obj.trkpt10pt0p4();}
    const float& trkpt10pt0p5() {return stop_baby_obj.trkpt10pt0p5();}
    const float& trkpt10pt0p6() {return stop_baby_obj.trkpt10pt0p6();}
    const float& trkpt10pt0p7() {return stop_baby_obj.trkpt10pt0p7();}
    const float& trkpt10pt0p8() {return stop_baby_obj.trkpt10pt0p8();}
    const float& trkpt10pt0p9() {return stop_baby_obj.trkpt10pt0p9();}
    const float& trkpt10pt1p0() {return stop_baby_obj.trkpt10pt1p0();}
    const float& trkreliso10pt0p1() {return stop_baby_obj.trkreliso10pt0p1();}
    const float& trkreliso10pt0p2() {return stop_baby_obj.trkreliso10pt0p2();}
    const float& trkreliso10pt0p3() {return stop_baby_obj.trkreliso10pt0p3();}
    const float& trkreliso10pt0p4() {return stop_baby_obj.trkreliso10pt0p4();}
    const float& trkreliso10pt0p5() {return stop_baby_obj.trkreliso10pt0p5();}
    const float& trkreliso10pt0p6() {return stop_baby_obj.trkreliso10pt0p6();}
    const float& trkreliso10pt0p7() {return stop_baby_obj.trkreliso10pt0p7();}
    const float& trkreliso10pt0p8() {return stop_baby_obj.trkreliso10pt0p8();}
    const float& trkreliso10pt0p9() {return stop_baby_obj.trkreliso10pt0p9();}
    const float& trkreliso10pt1p0() {return stop_baby_obj.trkreliso10pt1p0();}
    const float& pfcandpt10pt0p1() {return stop_baby_obj.pfcandpt10pt0p1();}
    const float& pfcandpt10pt0p2() {return stop_baby_obj.pfcandpt10pt0p2();}
    const float& pfcandpt10pt0p3() {return stop_baby_obj.pfcandpt10pt0p3();}
    const float& pfcandpt10pt0p4() {return stop_baby_obj.pfcandpt10pt0p4();}
    const float& pfcandpt10pt0p5() {return stop_baby_obj.pfcandpt10pt0p5();}
    const float& pfcandpt10pt0p6() {return stop_baby_obj.pfcandpt10pt0p6();}
    const float& pfcandpt10pt0p7() {return stop_baby_obj.pfcandpt10pt0p7();}
    const float& pfcandpt10pt0p8() {return stop_baby_obj.pfcandpt10pt0p8();}
    const float& pfcandpt10pt0p9() {return stop_baby_obj.pfcandpt10pt0p9();}
    const float& pfcandpt10pt1p0() {return stop_baby_obj.pfcandpt10pt1p0();}
    const float& pfcandiso10pt0p1() {return stop_baby_obj.pfcandiso10pt0p1();}
    const float& pfcandiso10pt0p2() {return stop_baby_obj.pfcandiso10pt0p2();}
    const float& pfcandiso10pt0p3() {return stop_baby_obj.pfcandiso10pt0p3();}
    const float& pfcandiso10pt0p4() {return stop_baby_obj.pfcandiso10pt0p4();}
    const float& pfcandiso10pt0p5() {return stop_baby_obj.pfcandiso10pt0p5();}
    const float& pfcandiso10pt0p6() {return stop_baby_obj.pfcandiso10pt0p6();}
    const float& pfcandiso10pt0p7() {return stop_baby_obj.pfcandiso10pt0p7();}
    const float& pfcandiso10pt0p8() {return stop_baby_obj.pfcandiso10pt0p8();}
    const float& pfcandiso10pt0p9() {return stop_baby_obj.pfcandiso10pt0p9();}
    const float& pfcandiso10pt1p0() {return stop_baby_obj.pfcandiso10pt1p0();}
    const float& mbb() {return stop_baby_obj.mbb();}
    const float& lep1pfjetdr() {return stop_baby_obj.lep1pfjetdr();}
    const float& lep2pfjetdr() {return stop_baby_obj.lep2pfjetdr();}
    const LorentzVector& mclep() {return stop_baby_obj.mclep();}
    const LorentzVector& mcnu() {return stop_baby_obj.mcnu();}
    const float& mcmln() {return stop_baby_obj.mcmln();}
    const float& mcmtln() {return stop_baby_obj.mcmtln();}
    const LorentzVector& mlep() {return stop_baby_obj.mlep();}
    const LorentzVector& lep1() {return stop_baby_obj.lep1();}
    const LorentzVector& lep2() {return stop_baby_obj.lep2();}
    const LorentzVector& trklep1() {return stop_baby_obj.trklep1();}
    const LorentzVector& trklep2() {return stop_baby_obj.trklep2();}
    const LorentzVector& gfitlep1() {return stop_baby_obj.gfitlep1();}
    const LorentzVector& gfitlep2() {return stop_baby_obj.gfitlep2();}
    const LorentzVector& lepp() {return stop_baby_obj.lepp();}
    const LorentzVector& lepm() {return stop_baby_obj.lepm();}
    const LorentzVector& pflep1() {return stop_baby_obj.pflep1();}
    const LorentzVector& pflep2() {return stop_baby_obj.pflep2();}
    const LorentzVector& leppfjet1() {return stop_baby_obj.leppfjet1();}
    const LorentzVector& leppfjet2() {return stop_baby_obj.leppfjet2();}
    const LorentzVector& mclep1() {return stop_baby_obj.mclep1();}
    const LorentzVector& mclep2() {return stop_baby_obj.mclep2();}
    const LorentzVector& mctaud1() {return stop_baby_obj.mctaud1();}
    const LorentzVector& mctaud2() {return stop_baby_obj.mctaud2();}
    const LorentzVector& mctaudvis1() {return stop_baby_obj.mctaudvis1();}
    const LorentzVector& mctaudvis2() {return stop_baby_obj.mctaudvis2();}
    const LorentzVector& pflep() {return stop_baby_obj.pflep();}
    const LorentzVector& pftaud() {return stop_baby_obj.pftaud();}
    const LorentzVector& pfcand5() {return stop_baby_obj.pfcand5();}
    const LorentzVector& pfcand10() {return stop_baby_obj.pfcand10();}
    const int& pfTau15_leadPtcandID() {return stop_baby_obj.pfTau15_leadPtcandID();}
    const LorentzVector& pfTau15() {return stop_baby_obj.pfTau15();}
    const LorentzVector& pfTau15_leadPtcand() {return stop_baby_obj.pfTau15_leadPtcand();}
    const int& pfTau_leadPtcandID() {return stop_baby_obj.pfTau_leadPtcandID();}
    const LorentzVector& pfTau() {return stop_baby_obj.pfTau();}
    const LorentzVector& pfTau_leadPtcand() {return stop_baby_obj.pfTau_leadPtcand();}
    const int& pfTauLoose_leadPtcandID() {return stop_baby_obj.pfTauLoose_leadPtcandID();}
    const LorentzVector& pfTauLoose() {return stop_baby_obj.pfTauLoose();}
    const LorentzVector& pfTauLoose_leadPtcand() {return stop_baby_obj.pfTauLoose_leadPtcand();}
    const LorentzVector& pfcandOS10() {return stop_baby_obj.pfcandOS10();}
    const LorentzVector& pfcandOS10looseZ() {return stop_baby_obj.pfcandOS10looseZ();}
    const LorentzVector& pfcand5looseZ() {return stop_baby_obj.pfcand5looseZ();}
    const LorentzVector& pfcanddir10() {return stop_baby_obj.pfcanddir10();}
    const LorentzVector& pfcandveto10() {return stop_baby_obj.pfcandveto10();}
    const LorentzVector& pfcandvetoL10() {return stop_baby_obj.pfcandvetoL10();}
    const LorentzVector& jet() {return stop_baby_obj.jet();}
    const LorentzVector& nonisoel() {return stop_baby_obj.nonisoel();}
    const LorentzVector& nonisomu() {return stop_baby_obj.nonisomu();}
    const LorentzVector& t() {return stop_baby_obj.t();}
    const LorentzVector& tbar() {return stop_baby_obj.tbar();}
    const LorentzVector& ttbar() {return stop_baby_obj.ttbar();}
    const LorentzVector& lep_t() {return stop_baby_obj.lep_t();}
    const LorentzVector& lep_tbar() {return stop_baby_obj.lep_tbar();}
    const LorentzVector& stop_t() {return stop_baby_obj.stop_t();}
    const LorentzVector& stop_tbar() {return stop_baby_obj.stop_tbar();}
    const LorentzVector& neutralino_t() {return stop_baby_obj.neutralino_t();}
    const LorentzVector& neutralino_tbar() {return stop_baby_obj.neutralino_tbar();}
    const int& lep_t_id() {return stop_baby_obj.lep_t_id();}
    const int& lep_tbar_id() {return stop_baby_obj.lep_tbar_id();}
    const std::vector<LorentzVector >& pfjets() {return stop_baby_obj.pfjets();}
    const std::vector<LorentzVector >& pfjets_genJet_() {return stop_baby_obj.pfjets_genJet_();}
    const std::vector<float>& pfjets_csv() {return stop_baby_obj.pfjets_csv();}
    const std::vector<float>& pfjets_chm() {return stop_baby_obj.pfjets_chm();}
    const std::vector<float>& pfjets_neu() {return stop_baby_obj.pfjets_neu();}
    const std::vector<float>& pfjets_l1corr() {return stop_baby_obj.pfjets_l1corr();}
    const std::vector<float>& pfjets_corr() {return stop_baby_obj.pfjets_corr();}
    const std::vector<int>& pfjets_mc3() {return stop_baby_obj.pfjets_mc3();}
    const std::vector<int>& pfjets_mcflavorAlgo() {return stop_baby_obj.pfjets_mcflavorAlgo();}
    const std::vector<int>& pfjets_mcflavorPhys() {return stop_baby_obj.pfjets_mcflavorPhys();}
    const std::vector<float>& pfjets_uncertainty() {return stop_baby_obj.pfjets_uncertainty();}
    const std::vector<int>& pfjets_flav() {return stop_baby_obj.pfjets_flav();}
    const std::vector<float>& pfjets_lrm() {return stop_baby_obj.pfjets_lrm();}
    const std::vector<float>& pfjets_lrm2() {return stop_baby_obj.pfjets_lrm2();}
    const std::vector<float>& pfjets_qgtag() {return stop_baby_obj.pfjets_qgtag();}
    const std::vector<float>& pfjets_genJetDr() {return stop_baby_obj.pfjets_genJetDr();}
    const std::vector<float>& pfjets_sigma() {return stop_baby_obj.pfjets_sigma();}
    const std::vector<int>& pfjets_lepjet() {return stop_baby_obj.pfjets_lepjet();}
    const std::vector<float>& pfjets_beta() {return stop_baby_obj.pfjets_beta();}
    const std::vector<float>& pfjets_beta2() {return stop_baby_obj.pfjets_beta2();}
    const std::vector<float>& pfjets_beta_0p1() {return stop_baby_obj.pfjets_beta_0p1();}
    const std::vector<float>& pfjets_beta_0p2() {return stop_baby_obj.pfjets_beta_0p2();}
    const std::vector<float>& pfjets_beta2_0p1() {return stop_baby_obj.pfjets_beta2_0p1();}
    const std::vector<float>& pfjets_beta2_0p5() {return stop_baby_obj.pfjets_beta2_0p5();}
    const std::vector<float>& pfjets_mvaPUid() {return stop_baby_obj.pfjets_mvaPUid();}
    const std::vector<float>& pfjets_mva5xPUid() {return stop_baby_obj.pfjets_mva5xPUid();}
    const std::vector<float>& pfjets_mvaBeta() {return stop_baby_obj.pfjets_mvaBeta();}
    const std::vector<LorentzVector >& genbs() {return stop_baby_obj.genbs();}
    const std::vector<int>& genps_pdgId() {return stop_baby_obj.genps_pdgId();}
    const std::vector<int>& genps_firstMother() {return stop_baby_obj.genps_firstMother();}
    const std::vector<float>& genps_energy() {return stop_baby_obj.genps_energy();}
    const std::vector<float>& genps_pt() {return stop_baby_obj.genps_pt();}
    const std::vector<float>& genps_eta() {return stop_baby_obj.genps_eta();}
    const std::vector<float>& genps_phi() {return stop_baby_obj.genps_phi();}
    const std::vector<float>& genps_mass() {return stop_baby_obj.genps_mass();}
    const float& mini_mt() {return stop_baby_obj.mini_mt();}
    const float& mini_mtup() {return stop_baby_obj.mini_mtup();}
    const float& mini_mtdown() {return stop_baby_obj.mini_mtdown();}
    const float& mini_isrweight() {return stop_baby_obj.mini_isrweight();}
    const float& mini_met() {return stop_baby_obj.mini_met();}
    const float& mini_metup() {return stop_baby_obj.mini_metup();}
    const float& mini_metdown() {return stop_baby_obj.mini_metdown();}
    const int& mini_sig() {return stop_baby_obj.mini_sig();}
    const int& mini_cr1() {return stop_baby_obj.mini_cr1();}
    const int& mini_cr4() {return stop_baby_obj.mini_cr4();}
    const int& mini_cr5() {return stop_baby_obj.mini_cr5();}
    const int& mini_whsig() {return stop_baby_obj.mini_whsig();}
    const int& mini_whcr1() {return stop_baby_obj.mini_whcr1();}
    const float& mini_chi2() {return stop_baby_obj.mini_chi2();}
    const float& mini_chi2up() {return stop_baby_obj.mini_chi2up();}
    const float& mini_chi2down() {return stop_baby_obj.mini_chi2down();}
    const float& mini_chi2bup() {return stop_baby_obj.mini_chi2bup();}
    const float& mini_chi2bdown() {return stop_baby_obj.mini_chi2bdown();}
    const float& mini_mt2b() {return stop_baby_obj.mini_mt2b();}
    const float& mini_mt2bl() {return stop_baby_obj.mini_mt2bl();}
    const float& mini_mt2w() {return stop_baby_obj.mini_mt2w();}
    const float& mini_mt2wup() {return stop_baby_obj.mini_mt2wup();}
    const float& mini_mt2wdown() {return stop_baby_obj.mini_mt2wdown();}
    const float& mini_mt2wbup() {return stop_baby_obj.mini_mt2wbup();}
    const float& mini_mt2wbdown() {return stop_baby_obj.mini_mt2wbdown();}
    const float& mini_weight() {return stop_baby_obj.mini_weight();}
    const float& mini_nvtxweight() {return stop_baby_obj.mini_nvtxweight();}
    const float& mini_sltrigeff() {return stop_baby_obj.mini_sltrigeff();}
    const float& mini_dltrigeff() {return stop_baby_obj.mini_dltrigeff();}
    const int& mini_nsigevents() {return stop_baby_obj.mini_nsigevents();}
    const int& mini_nb() {return stop_baby_obj.mini_nb();}
    const int& mini_nbupBC() {return stop_baby_obj.mini_nbupBC();}
    const int& mini_nbdownBC() {return stop_baby_obj.mini_nbdownBC();}
    const int& mini_nbupL() {return stop_baby_obj.mini_nbupL();}
    const int& mini_nbdownL() {return stop_baby_obj.mini_nbdownL();}
    const int& mini_njets() {return stop_baby_obj.mini_njets();}
    const int& mini_njetsup() {return stop_baby_obj.mini_njetsup();}
    const int& mini_njetsdown() {return stop_baby_obj.mini_njetsdown();}
    const int& mini_passisotrk() {return stop_baby_obj.mini_passisotrk();}
    const int& mini_passtauveto() {return stop_baby_obj.mini_passtauveto();}
    const int& mini_nlep() {return stop_baby_obj.mini_nlep();}
    const float& mini_lep1pt() {return stop_baby_obj.mini_lep1pt();}
    const float& mini_lep1eta() {return stop_baby_obj.mini_lep1eta();}
    const float& mini_lep2pt() {return stop_baby_obj.mini_lep2pt();}
    const float& mini_lep2eta() {return stop_baby_obj.mini_lep2eta();}
    const float& mini_dilmass() {return stop_baby_obj.mini_dilmass();}
    const float& mini_mstop() {return stop_baby_obj.mini_mstop();}
    const float& mini_mlsp() {return stop_baby_obj.mini_mlsp();}
    const float& mini_x() {return stop_baby_obj.mini_x();}
    const float& mini_xsecsusy() {return stop_baby_obj.mini_xsecsusy();}
    const float& mini_dRleptB1() {return stop_baby_obj.mini_dRleptB1();}
    const float& mini_dRleptB1_bup() {return stop_baby_obj.mini_dRleptB1_bup();}
    const float& mini_dRleptB1_bdown() {return stop_baby_obj.mini_dRleptB1_bdown();}
    const float& mini_htssl() {return stop_baby_obj.mini_htssl();}
    const float& mini_htosl() {return stop_baby_obj.mini_htosl();}
    const float& mini_htratiol() {return stop_baby_obj.mini_htratiol();}
    const float& mini_htssm() {return stop_baby_obj.mini_htssm();}
    const float& mini_htosm() {return stop_baby_obj.mini_htosm();}
    const float& mini_htratiom() {return stop_baby_obj.mini_htratiom();}
    const float& mini_htratiomup() {return stop_baby_obj.mini_htratiomup();}
    const float& mini_htratiomdown() {return stop_baby_obj.mini_htratiomdown();}
    const float& mini_dphimj1() {return stop_baby_obj.mini_dphimj1();}
    const float& mini_dphimj2() {return stop_baby_obj.mini_dphimj2();}
    const float& mini_dphimjmin() {return stop_baby_obj.mini_dphimjmin();}
    const float& mini_pt_b() {return stop_baby_obj.mini_pt_b();}
    const float& mini_pt_b_up() {return stop_baby_obj.mini_pt_b_up();}
    const float& mini_pt_b_down() {return stop_baby_obj.mini_pt_b_down();}
    const float& mini_pt_b_bup() {return stop_baby_obj.mini_pt_b_bup();}
    const float& mini_pt_b_bdown() {return stop_baby_obj.mini_pt_b_bdown();}
    const float& mini_pt_J1() {return stop_baby_obj.mini_pt_J1();}
    const float& mini_pt_J2() {return stop_baby_obj.mini_pt_J2();}
    const float& mini_bbmass() {return stop_baby_obj.mini_bbmass();}
    const float& mini_bbpt() {return stop_baby_obj.mini_bbpt();}
    const float& mini_wpt() {return stop_baby_obj.mini_wpt();}
    const float& mini_bbwdphi() {return stop_baby_obj.mini_bbwdphi();}
    const float& mini_rand() {return stop_baby_obj.mini_rand();}
    const float& mini_t2ttLM() {return stop_baby_obj.mini_t2ttLM();}
    const float& mini_t2ttHM() {return stop_baby_obj.mini_t2ttHM();}
    const std::vector<float>& mini_bdt() {return stop_baby_obj.mini_bdt();}
    const std::vector<float>& mini_bdtup() {return stop_baby_obj.mini_bdtup();}
    const std::vector<float>& mini_bdtdown() {return stop_baby_obj.mini_bdtdown();}
    const std::vector<float>& mini_bdtbup() {return stop_baby_obj.mini_bdtbup();}
    const std::vector<float>& mini_bdtbdown() {return stop_baby_obj.mini_bdtbdown();}

} // namespace stop
