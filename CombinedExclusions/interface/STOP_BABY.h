
#ifndef STOP_BABY_H
#define STOP_BABY_H

#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TBits.h"
#include "TString.h"
#include <vector> 
#include <string>          

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVectorD;

// Handle Classes to handle branch loading 
// ------------------------------------------------------------------------------------------------- //

namespace stop
{
    struct BranchType
    {
        enum value_type
        {
            CLASS,
            BUILTIN,
            NOT_SET,

            static_size
        };
    };

    template <typename T>
    class Handle
    {
        public:
            
            // construct: 
            explicit Handle(const std::string& branch_name);

            // destroy:
            virtual ~Handle() {}

            // set the branch's entry 
            void GetEntry(const unsigned int entry);

            // initialize the handle's branches
            void Init(TTree& tree);

            // is the branch already loaded
            bool IsLoaded() const;

            // load the branch
            void Load();

            // clear the branch
            void Clear();

            // get the value
            const T& get();

        protected:

            // set the branch type private member (based on the TBranch) 
            void SetBranchType(const std::string& branch_class);

            // members:
            bool                   m_is_loaded;
            unsigned int           m_entry;
            std::string            m_branch_name;
            T*                     m_object_ptr;
            T                      m_object;
            BranchType::value_type m_branch_type;

            // the TTree owns the branch (this is only a reference pointer)
            TBranch*     m_branch;

        private:
            // no default constructor
            Handle() {}
    };

    template <typename T>
    /*explicit*/ Handle<T>::Handle(const std::string& branch_name)
        : m_is_loaded(false)
        , m_entry(0)
        , m_branch_name(branch_name)
        , m_object_ptr(NULL)
        , m_object()
        , m_branch_type(BranchType::NOT_SET)
        , m_branch(NULL)
    {
    }

    template <typename T>
    void Handle<T>::GetEntry(const unsigned int entry)
    {
        Clear();
        m_entry = entry;
    }

    template <typename T>
    bool Handle<T>::IsLoaded() const
    {
        return m_is_loaded;
    }
   
    template <typename T>
    void Handle<T>::Clear()
    {
        m_is_loaded = false;
    }

    template <typename T>
    void Handle<T>::Load()
    {
        if (m_branch)
        {
            m_branch->GetEntry(m_entry);
            m_is_loaded = true;
        }
        else
        {
            throw std::runtime_error("[STOP_BABY] ERROR: branch " + m_branch_name + " does not exist!"); 
        }
    }

    template <typename T>
    void Handle<T>::SetBranchType(const std::string& branch_class)
    {
        if (branch_class.find("edm::Wrapper")!=std::string::npos)
        {
            m_branch_type = BranchType::BUILTIN;
        }
        else if 
        (
            branch_class.find("/B")!=std::string::npos || // char
            branch_class.find("/C")!=std::string::npos || // char
            branch_class.find("/b")!=std::string::npos || // unsigned char
            branch_class.find("/c")!=std::string::npos || // unsigned char
            branch_class.find("/S")!=std::string::npos || // short
            branch_class.find("/s")!=std::string::npos || // unsigned short
            branch_class.find("/I")!=std::string::npos || // int
            branch_class.find("/i")!=std::string::npos || // unsigned int
            branch_class.find("/F")!=std::string::npos || // float
            branch_class.find("/D")!=std::string::npos || // double
            branch_class.find("/L")!=std::string::npos || // long
            branch_class.find("/l")!=std::string::npos || // unsigned long
            branch_class.find("/O")!=std::string::npos    // bool
        )
        {
            m_branch_type = BranchType::BUILTIN;
        }
        else
        {
            m_branch_type = BranchType::CLASS;
        }
    }

    template <typename T>
    void Handle<T>::Init(TTree& tree)
    {
        // no protection if the branch pointer is NULL
        // (so you can use this if the branch doesn't exist
        // as long as you don't call it).
        m_branch = tree.GetBranch(m_branch_name.c_str());
        if (m_branch)
        {
            if (m_branch_type == BranchType::NOT_SET)
            {
                std::string branch_class = m_branch->GetClassName();
                if (branch_class.empty())  // built in types don't have a ClassName --> using title
                {
                    branch_class = m_branch->GetTitle();
                }
                SetBranchType(branch_class);
            }
            switch (m_branch_type)
            {
                case BranchType::CLASS  : m_branch->SetAddress(&m_object_ptr); break;
                case BranchType::BUILTIN: m_branch->SetAddress(&m_object)    ; break;
                default: throw std::runtime_error("[STOP_BABY] ERROR: branch type not supported!"); 
            }
        }
    }

    template <typename T>
    const T& Handle<T>::get()
    {
        if (not IsLoaded())
        {
            Load();
        }
        switch (m_branch_type)
        {
            case BranchType::CLASS  : return *m_object_ptr;
            case BranchType::BUILTIN: return m_object;
            default: throw std::runtime_error("[STOP_BABY] ERROR: branch type not supported!"); 
        }
    }
    
} // namespace stop


// STOP_BABY to handle all the branches for the TTree 
// ------------------------------------------------------------------------------------------------- //

class STOP_BABY
{
    public:
        STOP_BABY();

        // methods:
        void Init(TTree* const tree);
        void Init(TTree& tree);
        void GetEntry(const unsigned int entry);
		void LoadAllBranches();


       	// static methods:
       	static void progress(const int nEventsTotal, const int nEventsChain);

        // branch accessors
        const int& acc_2010();
        const int& acc_highmet();
        const int& acc_highht();
        const int& eldup();
        const int& csc();
        const int& hbhe();
        const int& hbhenew();
        const int& hcallaser();
        const int& ecaltp();
        const int& trkfail();
        const int& eebadsc();
        const int& lep1_badecallaser();
        const int& lep2_badecallaser();
        const int& isdata();
        const int& jetid();
        const int& jetid30();
        const int& json();
        const float& htoffset();
        const float& htuncor();
        const float& ptt();
        const float& pttbar();
        const float& ptttbar();
        const float& mttbar();
        const int& npartons();
        const int& nwzpartons();
        const int& hyptype();
        const float& maxpartonpt();
        const float& etattbar();
        const int& njetsoffset();
        const int& njetsuncor();
        const float& costhetaweight();
        const float& weight();
        const float& weightleft();
        const float& weightright();
        const float& mutrigweight();
        const float& mutrigweight2();
        const float& sltrigweight();
        const float& dltrigweight();
        const float& trgeff();
        const float& pthat();
        const float& qscale();
        const float& mgcor();
        const int& wflav();
        const float& ksusy();
        const float& ksusyup();
        const float& ksusydn();
        const float& xsecsusy();
        const float& xsecsusy2();
        const float& smeff();
        const float& k();
        const float& mllgen();
        const float& ptwgen();
        const float& ptzgen();
        const int& nlep();
        const int& nosel();
        const int& ngoodlep();
        const int& ngoodel();
        const int& ngoodmu();
        const int& mull();
        const int& mult();
        const int& mullgen();
        const int& multgen();
        const int& proc();
        const int& leptype();
        const float& topmass();
        const float& dilmass();
        const float& dilrecoil();
        const float& dilrecoilparl();
        const float& dilrecoilperp();
        const float& tcmet();
        const float& genmet();
        const float& gensumet();
        const float& genmetphi();
        const float& calomet();
        const float& calometphi();
        const float& trkmet();
        const float& trkmetphi();
        const float& trkmet_nolepcorr();
        const float& trkmetphi_nolepcorr();
        const float& pfmet();
        const float& pfmetveto();
        const float& pfmetsig();
        const float& pfmetphi();
        const float& pfsumet();
        const float& mucormet();
        const float& mucorjesmet();
        const float& tcmet35X();
        const float& tcmetevent();
        const float& tcmetlooper();
        const float& tcmetphi();
        const float& tcsumet();
        const float& tcmetUp();
        const float& tcmetDown();
        const float& tcmetTest();
        const float& pfmetUp();
        const float& pfmetDown();
        const float& pfmetTest();
        const float& sumjetpt();
        const float& dileta();
        const float& dilpt();
        const float& dildphi();
        const int& ngenjets();
        const int& njpt();
        const int& trgmu1();
        const int& trgmu2();
        const int& trgel1();
        const int& trgel2();
        const int& isomu24();
        const int& ele27wp80();
        const int& mm();
        const int& mmtk();
        const int& me();
        const int& em();
        const int& mu();
        const int& ee();
        const int& npfjets30();
        const int& npfjets30lepcorr();
        const float& knjets();
        const float& rhovor();
        const float& htpf30();
        const float& t1met10();
        const float& t1met20();
        const float& t1met30();
        const float& t1met10phi();
        const float& t1met20phi();
        const float& t1met30phi();
        const float& t1met10mt();
        const float& t1met20mt();
        const float& t1met30mt();
        const float& lepmetpt();
        const float& lept1met10pt();
        const float& t1met10s();
        const float& t1met10sphi();
        const float& t1met10smt();
        const float& t1metphicorr();
        const float& t1metphicorrup();
        const float& t1metphicorrdn();
        const float& t1metphicorrphi();
        const float& t1metphicorrphiup();
        const float& t1metphicorrphidn();
        const float& t1metphicorrlep();
        const float& t1metphicorrlepphi();
        const float& t1metphicorrmt();
        const float& t1metphicorrmtup();
        const float& t1metphicorrmtdn();
        const float& t1metphicorrlepmt();
        const float& t1met_off();
        const float& t1metphi_off();
        const float& t1metmt_off();
        const float& t1metphicorr_off();
        const float& t1metphicorrphi_off();
        const float& t1metphicorrmt_off();
        const float& mt2bmin();
        const float& mt2blmin();
        const float& mt2wmin();
        const float& chi2min();
        const float& chi2minprob();
        const int& nbtagsssv();
        const int& nbtagstcl();
        const int& nbtagstcm();
        const int& nbtagscsvl();
        const int& nbtagscsvm();
        const int& nbtagscsvt();
        const int& nbtagsssvcorr();
        const int& nbtagstclcorr();
        const int& nbtagstcmcorr();
        const int& nbtagscsvlcorr();
        const int& nbtagscsvmcorr();
        const int& nbtagscsvtcott();
        const int& njetsUp();
        const int& njetsDown();
        const float& htUp();
        const float& htDown();
        const int& ntruepu();
        const int& npu();
        const int& npuMinusOne();
        const int& npuPlusOne();
        const int& nvtx();
        const int& indexfirstGoodVertex_();
        const float& nvtxweight();
        const float& n3dvtxweight();
        const int& pdfid1();
        const int& pdfid2();
        const float& pdfx1();
        const float& pdfx2();
        const float& pdfQ();
        const float& vecjetpt();
        const int& pass();
        const int& passz();
        const float& m0();
        const float& mg();
        const float& ml();
        const float& x();
        const float& m12();
        const float& lep1chi2ndf();
        const float& lep2chi2ndf();
        const float& lep1dpt();
        const float& lep2dpt();
        const int& id1();
        const int& id2();
        const int& leptype1();
        const int& leptype2();
        const int& w1();
        const int& w2();
        const float& iso1();
        const float& isont1();
        const float& isopfold1();
        const float& isopf1();
        const float& etasc1();
        const float& etasc2();
        const float& eoverpin();
        const float& eoverpout();
        const float& dEtaIn();
        const float& dPhiIn();
        const float& sigmaIEtaIEta();
        const float& hOverE();
        const float& ooemoop();
        const float& d0vtx();
        const float& dzvtx();
        const float& expinnerlayers();
        const float& fbrem();
        const float& pfisoch();
        const float& pfisoem();
        const float& pfisonh();
        const float& eSC();
        const float& phiSC();
        const float& eSCRaw();
        const float& eSCPresh();
        const float& lep1_scslasercormean();
        const float& lep1_scslasercormax();
        const float& eoverpin2();
        const float& eoverpout2();
        const float& dEtaIn2();
        const float& dPhiIn2();
        const float& sigmaIEtaIEta2();
        const float& hOverE2();
        const float& ooemoop2();
        const float& d0vtx2();
        const float& dzvtx2();
        const float& expinnerlayers2();
        const float& fbrem2();
        const float& pfisoch2();
        const float& pfisoem2();
        const float& pfisonh2();
        const float& eSC2();
        const float& phiSC2();
        const float& eSCRaw2();
        const float& eSCPresh2();
        const float& lep2_scslasercormean();
        const float& lep2_scslasercormax();
        const float& scslasercormax();
        const float& scslasercormax_pt();
        const float& scslasercormax_eta();
        const float& iso2();
        const float& ecalveto1();
        const float& ecalveto2();
        const float& hcalveto1();
        const float& hcalveto2();
        const float& isont2();
        const float& isopf2();
        const float& ptl1();
        const float& ptl2();
        const float& etal1();
        const float& etal2();
        const float& phil1();
        const float& phil2();
        const float& meff();
        const float& mt();
        const char& dataset();
        const unsigned int& run();
        const unsigned int& lumi();
        const unsigned int& event();
        const float& y();
        const float& ht();
        const float& htgen();
        const float& htjpt();
        const int& nels();
        const int& nmus();
        const int& ntaus();
        const int& nleps();
        const int& nbs();
        const float& dphijm();
        const float& ptjetraw();
        const float& ptjet23();
        const float& ptjetF23();
        const float& ptjetO23();
        const int& mcid1();
        const float& mcdr1();
        const int& mcdecay1();
        const int& mcndec1();
        const int& mcndec2();
        const int& mcndeckls1();
        const int& mcndeckls2();
        const int& mcndecem1();
        const int& mcndecem2();
        const int& mcid2();
        const float& mcdr2();
        const int& mcdecay2();
        const float& mctaudpt1();
        const float& mctaudpt2();
        const int& mctaudid1();
        const int& mctaudid2();
        const int& mlepid();
        const int& mleppassid();
        const int& mleppassiso();
        const float& mlepiso();
        const float& mlepdr();
        const float& pflepiso();
        const float& pflepdr();
        const float& pfleppt();
        const float& pflepmindrj();
        const float& pftaudiso();
        const float& pftauddr();
        const float& pftaudpt();
        const float& pftaudmindrj();
        const int& pfcandid5();
        const float& pfcandiso5();
        const float& pfcandpt5();
        const float& pfcanddz5();
        const float& pfcandmindrj5();
        const int& pfcandid10();
        const float& pfcandiso10();
        const float& pfcandpt10();
        const float& pfcanddz10();
        const float& pfcandmindrj10();
        const int& pfcandidOS10();
        const float& pfcandisoOS10();
        const float& pfcandptOS10();
        const float& pfcanddzOS10();
        const int& pfcandid5looseZ();
        const float& pfcandiso5looseZ();
        const float& pfcandpt5looseZ();
        const float& pfcanddz5looseZ();
        const int& pfcandidOS10looseZ();
        const float& pfcandisoOS10looseZ();
        const float& pfcandptOS10looseZ();
        const float& pfcanddzOS10looseZ();
        const int& pfcanddirid10();
        const float& pfcanddiriso10();
        const float& pfcanddirpt10();
        const float& pfcanddirmindrj10();
        const int& pfcandvetoid10();
        const float& pfcandvetoiso10();
        const float& pfcandvetopt10();
        const float& pfcandvetomindrj10();
        const int& pfcandvetoLid10();
        const float& pfcandvetoLiso10();
        const float& pfcandvetoLpt10();
        const float& pfcandvetoLmindrj10();
        const float& emjet10();
        const float& mjj();
        const float& emjet20();
        const float& trkpt5();
        const float& trkpt10();
        const float& mleptrk5();
        const float& mleptrk10();
        const float& trkreliso5();
        const float& trkreliso10();
        const float& trkpt5loose();
        const float& trkpt10loose();
        const float& trkreliso5loose();
        const float& trkreliso10loose();
        const float& trkpt10pt0p1();
        const float& trkpt10pt0p2();
        const float& trkpt10pt0p3();
        const float& trkpt10pt0p4();
        const float& trkpt10pt0p5();
        const float& trkpt10pt0p6();
        const float& trkpt10pt0p7();
        const float& trkpt10pt0p8();
        const float& trkpt10pt0p9();
        const float& trkpt10pt1p0();
        const float& trkreliso10pt0p1();
        const float& trkreliso10pt0p2();
        const float& trkreliso10pt0p3();
        const float& trkreliso10pt0p4();
        const float& trkreliso10pt0p5();
        const float& trkreliso10pt0p6();
        const float& trkreliso10pt0p7();
        const float& trkreliso10pt0p8();
        const float& trkreliso10pt0p9();
        const float& trkreliso10pt1p0();
        const float& pfcandpt10pt0p1();
        const float& pfcandpt10pt0p2();
        const float& pfcandpt10pt0p3();
        const float& pfcandpt10pt0p4();
        const float& pfcandpt10pt0p5();
        const float& pfcandpt10pt0p6();
        const float& pfcandpt10pt0p7();
        const float& pfcandpt10pt0p8();
        const float& pfcandpt10pt0p9();
        const float& pfcandpt10pt1p0();
        const float& pfcandiso10pt0p1();
        const float& pfcandiso10pt0p2();
        const float& pfcandiso10pt0p3();
        const float& pfcandiso10pt0p4();
        const float& pfcandiso10pt0p5();
        const float& pfcandiso10pt0p6();
        const float& pfcandiso10pt0p7();
        const float& pfcandiso10pt0p8();
        const float& pfcandiso10pt0p9();
        const float& pfcandiso10pt1p0();
        const float& mbb();
        const float& lep1pfjetdr();
        const float& lep2pfjetdr();
        const LorentzVector& mclep();
        const LorentzVector& mcnu();
        const float& mcmln();
        const float& mcmtln();
        const LorentzVector& mlep();
        const LorentzVector& lep1();
        const LorentzVector& lep2();
        const LorentzVector& trklep1();
        const LorentzVector& trklep2();
        const LorentzVector& gfitlep1();
        const LorentzVector& gfitlep2();
        const LorentzVector& lepp();
        const LorentzVector& lepm();
        const LorentzVector& pflep1();
        const LorentzVector& pflep2();
        const LorentzVector& leppfjet1();
        const LorentzVector& leppfjet2();
        const LorentzVector& mclep1();
        const LorentzVector& mclep2();
        const LorentzVector& mctaud1();
        const LorentzVector& mctaud2();
        const LorentzVector& mctaudvis1();
        const LorentzVector& mctaudvis2();
        const LorentzVector& pflep();
        const LorentzVector& pftaud();
        const LorentzVector& pfcand5();
        const LorentzVector& pfcand10();
        const int& pfTau15_leadPtcandID();
        const LorentzVector& pfTau15();
        const LorentzVector& pfTau15_leadPtcand();
        const int& pfTau_leadPtcandID();
        const LorentzVector& pfTau();
        const LorentzVector& pfTau_leadPtcand();
        const int& pfTauLoose_leadPtcandID();
        const LorentzVector& pfTauLoose();
        const LorentzVector& pfTauLoose_leadPtcand();
        const LorentzVector& pfcandOS10();
        const LorentzVector& pfcandOS10looseZ();
        const LorentzVector& pfcand5looseZ();
        const LorentzVector& pfcanddir10();
        const LorentzVector& pfcandveto10();
        const LorentzVector& pfcandvetoL10();
        const LorentzVector& jet();
        const LorentzVector& nonisoel();
        const LorentzVector& nonisomu();
        const LorentzVector& t();
        const LorentzVector& tbar();
        const LorentzVector& ttbar();
        const LorentzVector& lep_t();
        const LorentzVector& lep_tbar();
        const LorentzVector& stop_t();
        const LorentzVector& stop_tbar();
        const LorentzVector& neutralino_t();
        const LorentzVector& neutralino_tbar();
        const int& lep_t_id();
        const int& lep_tbar_id();
        const std::vector<LorentzVector >& pfjets();
        const std::vector<LorentzVector >& pfjets_genJet_();
        const std::vector<float>& pfjets_csv();
        const std::vector<float>& pfjets_chm();
        const std::vector<float>& pfjets_neu();
        const std::vector<float>& pfjets_l1corr();
        const std::vector<float>& pfjets_corr();
        const std::vector<int>& pfjets_mc3();
        const std::vector<int>& pfjets_mcflavorAlgo();
        const std::vector<int>& pfjets_mcflavorPhys();
        const std::vector<float>& pfjets_uncertainty();
        const std::vector<int>& pfjets_flav();
        const std::vector<float>& pfjets_lrm();
        const std::vector<float>& pfjets_lrm2();
        const std::vector<float>& pfjets_qgtag();
        const std::vector<float>& pfjets_genJetDr();
        const std::vector<float>& pfjets_sigma();
        const std::vector<int>& pfjets_lepjet();
        const std::vector<float>& pfjets_beta();
        const std::vector<float>& pfjets_beta2();
        const std::vector<float>& pfjets_beta_0p1();
        const std::vector<float>& pfjets_beta_0p2();
        const std::vector<float>& pfjets_beta2_0p1();
        const std::vector<float>& pfjets_beta2_0p5();
        const std::vector<float>& pfjets_mvaPUid();
        const std::vector<float>& pfjets_mva5xPUid();
        const std::vector<float>& pfjets_mvaBeta();
        const std::vector<LorentzVector >& genbs();
        const std::vector<int>& genps_pdgId();
        const std::vector<int>& genps_firstMother();
        const std::vector<float>& genps_energy();
        const std::vector<float>& genps_pt();
        const std::vector<float>& genps_eta();
        const std::vector<float>& genps_phi();
        const std::vector<float>& genps_mass();
        const float& mini_mt();
        const float& mini_mtup();
        const float& mini_mtdown();
        const float& mini_isrweight();
        const float& mini_met();
        const float& mini_metup();
        const float& mini_metdown();
        const int& mini_sig();
        const int& mini_cr1();
        const int& mini_cr4();
        const int& mini_cr5();
        const int& mini_whsig();
        const int& mini_whcr1();
        const float& mini_chi2();
        const float& mini_chi2up();
        const float& mini_chi2down();
        const float& mini_chi2bup();
        const float& mini_chi2bdown();
        const float& mini_mt2b();
        const float& mini_mt2bl();
        const float& mini_mt2w();
        const float& mini_mt2wup();
        const float& mini_mt2wdown();
        const float& mini_mt2wbup();
        const float& mini_mt2wbdown();
        const float& mini_weight();
        const float& mini_nvtxweight();
        const float& mini_sltrigeff();
        const float& mini_dltrigeff();
        const int& mini_nsigevents();
        const int& mini_nb();
        const int& mini_nbupBC();
        const int& mini_nbdownBC();
        const int& mini_nbupL();
        const int& mini_nbdownL();
        const int& mini_njets();
        const int& mini_njetsup();
        const int& mini_njetsdown();
        const int& mini_passisotrk();
        const int& mini_passtauveto();
        const int& mini_nlep();
        const float& mini_lep1pt();
        const float& mini_lep1eta();
        const float& mini_lep2pt();
        const float& mini_lep2eta();
        const float& mini_dilmass();
        const float& mini_mstop();
        const float& mini_mlsp();
        const float& mini_x();
        const float& mini_xsecsusy();
        const float& mini_dRleptB1();
        const float& mini_dRleptB1_bup();
        const float& mini_dRleptB1_bdown();
        const float& mini_htssl();
        const float& mini_htosl();
        const float& mini_htratiol();
        const float& mini_htssm();
        const float& mini_htosm();
        const float& mini_htratiom();
        const float& mini_htratiomup();
        const float& mini_htratiomdown();
        const float& mini_dphimj1();
        const float& mini_dphimj2();
        const float& mini_dphimjmin();
        const float& mini_pt_b();
        const float& mini_pt_b_up();
        const float& mini_pt_b_down();
        const float& mini_pt_b_bup();
        const float& mini_pt_b_bdown();
        const float& mini_pt_J1();
        const float& mini_pt_J2();
        const float& mini_bbmass();
        const float& mini_bbpt();
        const float& mini_wpt();
        const float& mini_bbwdphi();
        const float& mini_rand();
        const float& mini_t2ttLM();
        const float& mini_t2ttHM();
        const std::vector<float>& mini_bdt();
        const std::vector<float>& mini_bdtup();
        const std::vector<float>& mini_bdtdown();
        const std::vector<float>& mini_bdtbup();
        const std::vector<float>& mini_bdtbdown();

    private:
    
        // handles
        stop::Handle< int > acc_2010_handle;
        stop::Handle< int > acc_highmet_handle;
        stop::Handle< int > acc_highht_handle;
        stop::Handle< int > eldup_handle;
        stop::Handle< int > csc_handle;
        stop::Handle< int > hbhe_handle;
        stop::Handle< int > hbhenew_handle;
        stop::Handle< int > hcallaser_handle;
        stop::Handle< int > ecaltp_handle;
        stop::Handle< int > trkfail_handle;
        stop::Handle< int > eebadsc_handle;
        stop::Handle< int > lep1_badecallaser_handle;
        stop::Handle< int > lep2_badecallaser_handle;
        stop::Handle< int > isdata_handle;
        stop::Handle< int > jetid_handle;
        stop::Handle< int > jetid30_handle;
        stop::Handle< int > json_handle;
        stop::Handle< float > htoffset_handle;
        stop::Handle< float > htuncor_handle;
        stop::Handle< float > ptt_handle;
        stop::Handle< float > pttbar_handle;
        stop::Handle< float > ptttbar_handle;
        stop::Handle< float > mttbar_handle;
        stop::Handle< int > npartons_handle;
        stop::Handle< int > nwzpartons_handle;
        stop::Handle< int > hyptype_handle;
        stop::Handle< float > maxpartonpt_handle;
        stop::Handle< float > etattbar_handle;
        stop::Handle< int > njetsoffset_handle;
        stop::Handle< int > njetsuncor_handle;
        stop::Handle< float > costhetaweight_handle;
        stop::Handle< float > weight_handle;
        stop::Handle< float > weightleft_handle;
        stop::Handle< float > weightright_handle;
        stop::Handle< float > mutrigweight_handle;
        stop::Handle< float > mutrigweight2_handle;
        stop::Handle< float > sltrigweight_handle;
        stop::Handle< float > dltrigweight_handle;
        stop::Handle< float > trgeff_handle;
        stop::Handle< float > pthat_handle;
        stop::Handle< float > qscale_handle;
        stop::Handle< float > mgcor_handle;
        stop::Handle< int > wflav_handle;
        stop::Handle< float > ksusy_handle;
        stop::Handle< float > ksusyup_handle;
        stop::Handle< float > ksusydn_handle;
        stop::Handle< float > xsecsusy_handle;
        stop::Handle< float > xsecsusy2_handle;
        stop::Handle< float > smeff_handle;
        stop::Handle< float > k_handle;
        stop::Handle< float > mllgen_handle;
        stop::Handle< float > ptwgen_handle;
        stop::Handle< float > ptzgen_handle;
        stop::Handle< int > nlep_handle;
        stop::Handle< int > nosel_handle;
        stop::Handle< int > ngoodlep_handle;
        stop::Handle< int > ngoodel_handle;
        stop::Handle< int > ngoodmu_handle;
        stop::Handle< int > mull_handle;
        stop::Handle< int > mult_handle;
        stop::Handle< int > mullgen_handle;
        stop::Handle< int > multgen_handle;
        stop::Handle< int > proc_handle;
        stop::Handle< int > leptype_handle;
        stop::Handle< float > topmass_handle;
        stop::Handle< float > dilmass_handle;
        stop::Handle< float > dilrecoil_handle;
        stop::Handle< float > dilrecoilparl_handle;
        stop::Handle< float > dilrecoilperp_handle;
        stop::Handle< float > tcmet_handle;
        stop::Handle< float > genmet_handle;
        stop::Handle< float > gensumet_handle;
        stop::Handle< float > genmetphi_handle;
        stop::Handle< float > calomet_handle;
        stop::Handle< float > calometphi_handle;
        stop::Handle< float > trkmet_handle;
        stop::Handle< float > trkmetphi_handle;
        stop::Handle< float > trkmet_nolepcorr_handle;
        stop::Handle< float > trkmetphi_nolepcorr_handle;
        stop::Handle< float > pfmet_handle;
        stop::Handle< float > pfmetveto_handle;
        stop::Handle< float > pfmetsig_handle;
        stop::Handle< float > pfmetphi_handle;
        stop::Handle< float > pfsumet_handle;
        stop::Handle< float > mucormet_handle;
        stop::Handle< float > mucorjesmet_handle;
        stop::Handle< float > tcmet35X_handle;
        stop::Handle< float > tcmetevent_handle;
        stop::Handle< float > tcmetlooper_handle;
        stop::Handle< float > tcmetphi_handle;
        stop::Handle< float > tcsumet_handle;
        stop::Handle< float > tcmetUp_handle;
        stop::Handle< float > tcmetDown_handle;
        stop::Handle< float > tcmetTest_handle;
        stop::Handle< float > pfmetUp_handle;
        stop::Handle< float > pfmetDown_handle;
        stop::Handle< float > pfmetTest_handle;
        stop::Handle< float > sumjetpt_handle;
        stop::Handle< float > dileta_handle;
        stop::Handle< float > dilpt_handle;
        stop::Handle< float > dildphi_handle;
        stop::Handle< int > ngenjets_handle;
        stop::Handle< int > njpt_handle;
        stop::Handle< int > trgmu1_handle;
        stop::Handle< int > trgmu2_handle;
        stop::Handle< int > trgel1_handle;
        stop::Handle< int > trgel2_handle;
        stop::Handle< int > isomu24_handle;
        stop::Handle< int > ele27wp80_handle;
        stop::Handle< int > mm_handle;
        stop::Handle< int > mmtk_handle;
        stop::Handle< int > me_handle;
        stop::Handle< int > em_handle;
        stop::Handle< int > mu_handle;
        stop::Handle< int > ee_handle;
        stop::Handle< int > npfjets30_handle;
        stop::Handle< int > npfjets30lepcorr_handle;
        stop::Handle< float > knjets_handle;
        stop::Handle< float > rhovor_handle;
        stop::Handle< float > htpf30_handle;
        stop::Handle< float > t1met10_handle;
        stop::Handle< float > t1met20_handle;
        stop::Handle< float > t1met30_handle;
        stop::Handle< float > t1met10phi_handle;
        stop::Handle< float > t1met20phi_handle;
        stop::Handle< float > t1met30phi_handle;
        stop::Handle< float > t1met10mt_handle;
        stop::Handle< float > t1met20mt_handle;
        stop::Handle< float > t1met30mt_handle;
        stop::Handle< float > lepmetpt_handle;
        stop::Handle< float > lept1met10pt_handle;
        stop::Handle< float > t1met10s_handle;
        stop::Handle< float > t1met10sphi_handle;
        stop::Handle< float > t1met10smt_handle;
        stop::Handle< float > t1metphicorr_handle;
        stop::Handle< float > t1metphicorrup_handle;
        stop::Handle< float > t1metphicorrdn_handle;
        stop::Handle< float > t1metphicorrphi_handle;
        stop::Handle< float > t1metphicorrphiup_handle;
        stop::Handle< float > t1metphicorrphidn_handle;
        stop::Handle< float > t1metphicorrlep_handle;
        stop::Handle< float > t1metphicorrlepphi_handle;
        stop::Handle< float > t1metphicorrmt_handle;
        stop::Handle< float > t1metphicorrmtup_handle;
        stop::Handle< float > t1metphicorrmtdn_handle;
        stop::Handle< float > t1metphicorrlepmt_handle;
        stop::Handle< float > t1met_off_handle;
        stop::Handle< float > t1metphi_off_handle;
        stop::Handle< float > t1metmt_off_handle;
        stop::Handle< float > t1metphicorr_off_handle;
        stop::Handle< float > t1metphicorrphi_off_handle;
        stop::Handle< float > t1metphicorrmt_off_handle;
        stop::Handle< float > mt2bmin_handle;
        stop::Handle< float > mt2blmin_handle;
        stop::Handle< float > mt2wmin_handle;
        stop::Handle< float > chi2min_handle;
        stop::Handle< float > chi2minprob_handle;
        stop::Handle< int > nbtagsssv_handle;
        stop::Handle< int > nbtagstcl_handle;
        stop::Handle< int > nbtagstcm_handle;
        stop::Handle< int > nbtagscsvl_handle;
        stop::Handle< int > nbtagscsvm_handle;
        stop::Handle< int > nbtagscsvt_handle;
        stop::Handle< int > nbtagsssvcorr_handle;
        stop::Handle< int > nbtagstclcorr_handle;
        stop::Handle< int > nbtagstcmcorr_handle;
        stop::Handle< int > nbtagscsvlcorr_handle;
        stop::Handle< int > nbtagscsvmcorr_handle;
        stop::Handle< int > nbtagscsvtcott_handle;
        stop::Handle< int > njetsUp_handle;
        stop::Handle< int > njetsDown_handle;
        stop::Handle< float > htUp_handle;
        stop::Handle< float > htDown_handle;
        stop::Handle< int > ntruepu_handle;
        stop::Handle< int > npu_handle;
        stop::Handle< int > npuMinusOne_handle;
        stop::Handle< int > npuPlusOne_handle;
        stop::Handle< int > nvtx_handle;
        stop::Handle< int > indexfirstGoodVertex__handle;
        stop::Handle< float > nvtxweight_handle;
        stop::Handle< float > n3dvtxweight_handle;
        stop::Handle< int > pdfid1_handle;
        stop::Handle< int > pdfid2_handle;
        stop::Handle< float > pdfx1_handle;
        stop::Handle< float > pdfx2_handle;
        stop::Handle< float > pdfQ_handle;
        stop::Handle< float > vecjetpt_handle;
        stop::Handle< int > pass_handle;
        stop::Handle< int > passz_handle;
        stop::Handle< float > m0_handle;
        stop::Handle< float > mg_handle;
        stop::Handle< float > ml_handle;
        stop::Handle< float > x_handle;
        stop::Handle< float > m12_handle;
        stop::Handle< float > lep1chi2ndf_handle;
        stop::Handle< float > lep2chi2ndf_handle;
        stop::Handle< float > lep1dpt_handle;
        stop::Handle< float > lep2dpt_handle;
        stop::Handle< int > id1_handle;
        stop::Handle< int > id2_handle;
        stop::Handle< int > leptype1_handle;
        stop::Handle< int > leptype2_handle;
        stop::Handle< int > w1_handle;
        stop::Handle< int > w2_handle;
        stop::Handle< float > iso1_handle;
        stop::Handle< float > isont1_handle;
        stop::Handle< float > isopfold1_handle;
        stop::Handle< float > isopf1_handle;
        stop::Handle< float > etasc1_handle;
        stop::Handle< float > etasc2_handle;
        stop::Handle< float > eoverpin_handle;
        stop::Handle< float > eoverpout_handle;
        stop::Handle< float > dEtaIn_handle;
        stop::Handle< float > dPhiIn_handle;
        stop::Handle< float > sigmaIEtaIEta_handle;
        stop::Handle< float > hOverE_handle;
        stop::Handle< float > ooemoop_handle;
        stop::Handle< float > d0vtx_handle;
        stop::Handle< float > dzvtx_handle;
        stop::Handle< float > expinnerlayers_handle;
        stop::Handle< float > fbrem_handle;
        stop::Handle< float > pfisoch_handle;
        stop::Handle< float > pfisoem_handle;
        stop::Handle< float > pfisonh_handle;
        stop::Handle< float > eSC_handle;
        stop::Handle< float > phiSC_handle;
        stop::Handle< float > eSCRaw_handle;
        stop::Handle< float > eSCPresh_handle;
        stop::Handle< float > lep1_scslasercormean_handle;
        stop::Handle< float > lep1_scslasercormax_handle;
        stop::Handle< float > eoverpin2_handle;
        stop::Handle< float > eoverpout2_handle;
        stop::Handle< float > dEtaIn2_handle;
        stop::Handle< float > dPhiIn2_handle;
        stop::Handle< float > sigmaIEtaIEta2_handle;
        stop::Handle< float > hOverE2_handle;
        stop::Handle< float > ooemoop2_handle;
        stop::Handle< float > d0vtx2_handle;
        stop::Handle< float > dzvtx2_handle;
        stop::Handle< float > expinnerlayers2_handle;
        stop::Handle< float > fbrem2_handle;
        stop::Handle< float > pfisoch2_handle;
        stop::Handle< float > pfisoem2_handle;
        stop::Handle< float > pfisonh2_handle;
        stop::Handle< float > eSC2_handle;
        stop::Handle< float > phiSC2_handle;
        stop::Handle< float > eSCRaw2_handle;
        stop::Handle< float > eSCPresh2_handle;
        stop::Handle< float > lep2_scslasercormean_handle;
        stop::Handle< float > lep2_scslasercormax_handle;
        stop::Handle< float > scslasercormax_handle;
        stop::Handle< float > scslasercormax_pt_handle;
        stop::Handle< float > scslasercormax_eta_handle;
        stop::Handle< float > iso2_handle;
        stop::Handle< float > ecalveto1_handle;
        stop::Handle< float > ecalveto2_handle;
        stop::Handle< float > hcalveto1_handle;
        stop::Handle< float > hcalveto2_handle;
        stop::Handle< float > isont2_handle;
        stop::Handle< float > isopf2_handle;
        stop::Handle< float > ptl1_handle;
        stop::Handle< float > ptl2_handle;
        stop::Handle< float > etal1_handle;
        stop::Handle< float > etal2_handle;
        stop::Handle< float > phil1_handle;
        stop::Handle< float > phil2_handle;
        stop::Handle< float > meff_handle;
        stop::Handle< float > mt_handle;
        stop::Handle< char > dataset_handle;
        stop::Handle< unsigned int > run_handle;
        stop::Handle< unsigned int > lumi_handle;
        stop::Handle< unsigned int > event_handle;
        stop::Handle< float > y_handle;
        stop::Handle< float > ht_handle;
        stop::Handle< float > htgen_handle;
        stop::Handle< float > htjpt_handle;
        stop::Handle< int > nels_handle;
        stop::Handle< int > nmus_handle;
        stop::Handle< int > ntaus_handle;
        stop::Handle< int > nleps_handle;
        stop::Handle< int > nbs_handle;
        stop::Handle< float > dphijm_handle;
        stop::Handle< float > ptjetraw_handle;
        stop::Handle< float > ptjet23_handle;
        stop::Handle< float > ptjetF23_handle;
        stop::Handle< float > ptjetO23_handle;
        stop::Handle< int > mcid1_handle;
        stop::Handle< float > mcdr1_handle;
        stop::Handle< int > mcdecay1_handle;
        stop::Handle< int > mcndec1_handle;
        stop::Handle< int > mcndec2_handle;
        stop::Handle< int > mcndeckls1_handle;
        stop::Handle< int > mcndeckls2_handle;
        stop::Handle< int > mcndecem1_handle;
        stop::Handle< int > mcndecem2_handle;
        stop::Handle< int > mcid2_handle;
        stop::Handle< float > mcdr2_handle;
        stop::Handle< int > mcdecay2_handle;
        stop::Handle< float > mctaudpt1_handle;
        stop::Handle< float > mctaudpt2_handle;
        stop::Handle< int > mctaudid1_handle;
        stop::Handle< int > mctaudid2_handle;
        stop::Handle< int > mlepid_handle;
        stop::Handle< int > mleppassid_handle;
        stop::Handle< int > mleppassiso_handle;
        stop::Handle< float > mlepiso_handle;
        stop::Handle< float > mlepdr_handle;
        stop::Handle< float > pflepiso_handle;
        stop::Handle< float > pflepdr_handle;
        stop::Handle< float > pfleppt_handle;
        stop::Handle< float > pflepmindrj_handle;
        stop::Handle< float > pftaudiso_handle;
        stop::Handle< float > pftauddr_handle;
        stop::Handle< float > pftaudpt_handle;
        stop::Handle< float > pftaudmindrj_handle;
        stop::Handle< int > pfcandid5_handle;
        stop::Handle< float > pfcandiso5_handle;
        stop::Handle< float > pfcandpt5_handle;
        stop::Handle< float > pfcanddz5_handle;
        stop::Handle< float > pfcandmindrj5_handle;
        stop::Handle< int > pfcandid10_handle;
        stop::Handle< float > pfcandiso10_handle;
        stop::Handle< float > pfcandpt10_handle;
        stop::Handle< float > pfcanddz10_handle;
        stop::Handle< float > pfcandmindrj10_handle;
        stop::Handle< int > pfcandidOS10_handle;
        stop::Handle< float > pfcandisoOS10_handle;
        stop::Handle< float > pfcandptOS10_handle;
        stop::Handle< float > pfcanddzOS10_handle;
        stop::Handle< int > pfcandid5looseZ_handle;
        stop::Handle< float > pfcandiso5looseZ_handle;
        stop::Handle< float > pfcandpt5looseZ_handle;
        stop::Handle< float > pfcanddz5looseZ_handle;
        stop::Handle< int > pfcandidOS10looseZ_handle;
        stop::Handle< float > pfcandisoOS10looseZ_handle;
        stop::Handle< float > pfcandptOS10looseZ_handle;
        stop::Handle< float > pfcanddzOS10looseZ_handle;
        stop::Handle< int > pfcanddirid10_handle;
        stop::Handle< float > pfcanddiriso10_handle;
        stop::Handle< float > pfcanddirpt10_handle;
        stop::Handle< float > pfcanddirmindrj10_handle;
        stop::Handle< int > pfcandvetoid10_handle;
        stop::Handle< float > pfcandvetoiso10_handle;
        stop::Handle< float > pfcandvetopt10_handle;
        stop::Handle< float > pfcandvetomindrj10_handle;
        stop::Handle< int > pfcandvetoLid10_handle;
        stop::Handle< float > pfcandvetoLiso10_handle;
        stop::Handle< float > pfcandvetoLpt10_handle;
        stop::Handle< float > pfcandvetoLmindrj10_handle;
        stop::Handle< float > emjet10_handle;
        stop::Handle< float > mjj_handle;
        stop::Handle< float > emjet20_handle;
        stop::Handle< float > trkpt5_handle;
        stop::Handle< float > trkpt10_handle;
        stop::Handle< float > mleptrk5_handle;
        stop::Handle< float > mleptrk10_handle;
        stop::Handle< float > trkreliso5_handle;
        stop::Handle< float > trkreliso10_handle;
        stop::Handle< float > trkpt5loose_handle;
        stop::Handle< float > trkpt10loose_handle;
        stop::Handle< float > trkreliso5loose_handle;
        stop::Handle< float > trkreliso10loose_handle;
        stop::Handle< float > trkpt10pt0p1_handle;
        stop::Handle< float > trkpt10pt0p2_handle;
        stop::Handle< float > trkpt10pt0p3_handle;
        stop::Handle< float > trkpt10pt0p4_handle;
        stop::Handle< float > trkpt10pt0p5_handle;
        stop::Handle< float > trkpt10pt0p6_handle;
        stop::Handle< float > trkpt10pt0p7_handle;
        stop::Handle< float > trkpt10pt0p8_handle;
        stop::Handle< float > trkpt10pt0p9_handle;
        stop::Handle< float > trkpt10pt1p0_handle;
        stop::Handle< float > trkreliso10pt0p1_handle;
        stop::Handle< float > trkreliso10pt0p2_handle;
        stop::Handle< float > trkreliso10pt0p3_handle;
        stop::Handle< float > trkreliso10pt0p4_handle;
        stop::Handle< float > trkreliso10pt0p5_handle;
        stop::Handle< float > trkreliso10pt0p6_handle;
        stop::Handle< float > trkreliso10pt0p7_handle;
        stop::Handle< float > trkreliso10pt0p8_handle;
        stop::Handle< float > trkreliso10pt0p9_handle;
        stop::Handle< float > trkreliso10pt1p0_handle;
        stop::Handle< float > pfcandpt10pt0p1_handle;
        stop::Handle< float > pfcandpt10pt0p2_handle;
        stop::Handle< float > pfcandpt10pt0p3_handle;
        stop::Handle< float > pfcandpt10pt0p4_handle;
        stop::Handle< float > pfcandpt10pt0p5_handle;
        stop::Handle< float > pfcandpt10pt0p6_handle;
        stop::Handle< float > pfcandpt10pt0p7_handle;
        stop::Handle< float > pfcandpt10pt0p8_handle;
        stop::Handle< float > pfcandpt10pt0p9_handle;
        stop::Handle< float > pfcandpt10pt1p0_handle;
        stop::Handle< float > pfcandiso10pt0p1_handle;
        stop::Handle< float > pfcandiso10pt0p2_handle;
        stop::Handle< float > pfcandiso10pt0p3_handle;
        stop::Handle< float > pfcandiso10pt0p4_handle;
        stop::Handle< float > pfcandiso10pt0p5_handle;
        stop::Handle< float > pfcandiso10pt0p6_handle;
        stop::Handle< float > pfcandiso10pt0p7_handle;
        stop::Handle< float > pfcandiso10pt0p8_handle;
        stop::Handle< float > pfcandiso10pt0p9_handle;
        stop::Handle< float > pfcandiso10pt1p0_handle;
        stop::Handle< float > mbb_handle;
        stop::Handle< float > lep1pfjetdr_handle;
        stop::Handle< float > lep2pfjetdr_handle;
        stop::Handle< LorentzVector > mclep_handle;
        stop::Handle< LorentzVector > mcnu_handle;
        stop::Handle< float > mcmln_handle;
        stop::Handle< float > mcmtln_handle;
        stop::Handle< LorentzVector > mlep_handle;
        stop::Handle< LorentzVector > lep1_handle;
        stop::Handle< LorentzVector > lep2_handle;
        stop::Handle< LorentzVector > trklep1_handle;
        stop::Handle< LorentzVector > trklep2_handle;
        stop::Handle< LorentzVector > gfitlep1_handle;
        stop::Handle< LorentzVector > gfitlep2_handle;
        stop::Handle< LorentzVector > lepp_handle;
        stop::Handle< LorentzVector > lepm_handle;
        stop::Handle< LorentzVector > pflep1_handle;
        stop::Handle< LorentzVector > pflep2_handle;
        stop::Handle< LorentzVector > leppfjet1_handle;
        stop::Handle< LorentzVector > leppfjet2_handle;
        stop::Handle< LorentzVector > mclep1_handle;
        stop::Handle< LorentzVector > mclep2_handle;
        stop::Handle< LorentzVector > mctaud1_handle;
        stop::Handle< LorentzVector > mctaud2_handle;
        stop::Handle< LorentzVector > mctaudvis1_handle;
        stop::Handle< LorentzVector > mctaudvis2_handle;
        stop::Handle< LorentzVector > pflep_handle;
        stop::Handle< LorentzVector > pftaud_handle;
        stop::Handle< LorentzVector > pfcand5_handle;
        stop::Handle< LorentzVector > pfcand10_handle;
        stop::Handle< int > pfTau15_leadPtcandID_handle;
        stop::Handle< LorentzVector > pfTau15_handle;
        stop::Handle< LorentzVector > pfTau15_leadPtcand_handle;
        stop::Handle< int > pfTau_leadPtcandID_handle;
        stop::Handle< LorentzVector > pfTau_handle;
        stop::Handle< LorentzVector > pfTau_leadPtcand_handle;
        stop::Handle< int > pfTauLoose_leadPtcandID_handle;
        stop::Handle< LorentzVector > pfTauLoose_handle;
        stop::Handle< LorentzVector > pfTauLoose_leadPtcand_handle;
        stop::Handle< LorentzVector > pfcandOS10_handle;
        stop::Handle< LorentzVector > pfcandOS10looseZ_handle;
        stop::Handle< LorentzVector > pfcand5looseZ_handle;
        stop::Handle< LorentzVector > pfcanddir10_handle;
        stop::Handle< LorentzVector > pfcandveto10_handle;
        stop::Handle< LorentzVector > pfcandvetoL10_handle;
        stop::Handle< LorentzVector > jet_handle;
        stop::Handle< LorentzVector > nonisoel_handle;
        stop::Handle< LorentzVector > nonisomu_handle;
        stop::Handle< LorentzVector > t_handle;
        stop::Handle< LorentzVector > tbar_handle;
        stop::Handle< LorentzVector > ttbar_handle;
        stop::Handle< LorentzVector > lep_t_handle;
        stop::Handle< LorentzVector > lep_tbar_handle;
        stop::Handle< LorentzVector > stop_t_handle;
        stop::Handle< LorentzVector > stop_tbar_handle;
        stop::Handle< LorentzVector > neutralino_t_handle;
        stop::Handle< LorentzVector > neutralino_tbar_handle;
        stop::Handle< int > lep_t_id_handle;
        stop::Handle< int > lep_tbar_id_handle;
        stop::Handle< std::vector<LorentzVector > > pfjets_handle;
        stop::Handle< std::vector<LorentzVector > > pfjets_genJet__handle;
        stop::Handle< std::vector<float> > pfjets_csv_handle;
        stop::Handle< std::vector<float> > pfjets_chm_handle;
        stop::Handle< std::vector<float> > pfjets_neu_handle;
        stop::Handle< std::vector<float> > pfjets_l1corr_handle;
        stop::Handle< std::vector<float> > pfjets_corr_handle;
        stop::Handle< std::vector<int> > pfjets_mc3_handle;
        stop::Handle< std::vector<int> > pfjets_mcflavorAlgo_handle;
        stop::Handle< std::vector<int> > pfjets_mcflavorPhys_handle;
        stop::Handle< std::vector<float> > pfjets_uncertainty_handle;
        stop::Handle< std::vector<int> > pfjets_flav_handle;
        stop::Handle< std::vector<float> > pfjets_lrm_handle;
        stop::Handle< std::vector<float> > pfjets_lrm2_handle;
        stop::Handle< std::vector<float> > pfjets_qgtag_handle;
        stop::Handle< std::vector<float> > pfjets_genJetDr_handle;
        stop::Handle< std::vector<float> > pfjets_sigma_handle;
        stop::Handle< std::vector<int> > pfjets_lepjet_handle;
        stop::Handle< std::vector<float> > pfjets_beta_handle;
        stop::Handle< std::vector<float> > pfjets_beta2_handle;
        stop::Handle< std::vector<float> > pfjets_beta_0p1_handle;
        stop::Handle< std::vector<float> > pfjets_beta_0p2_handle;
        stop::Handle< std::vector<float> > pfjets_beta2_0p1_handle;
        stop::Handle< std::vector<float> > pfjets_beta2_0p5_handle;
        stop::Handle< std::vector<float> > pfjets_mvaPUid_handle;
        stop::Handle< std::vector<float> > pfjets_mva5xPUid_handle;
        stop::Handle< std::vector<float> > pfjets_mvaBeta_handle;
        stop::Handle< std::vector<LorentzVector > > genbs_handle;
        stop::Handle< std::vector<int> > genps_pdgId_handle;
        stop::Handle< std::vector<int> > genps_firstMother_handle;
        stop::Handle< std::vector<float> > genps_energy_handle;
        stop::Handle< std::vector<float> > genps_pt_handle;
        stop::Handle< std::vector<float> > genps_eta_handle;
        stop::Handle< std::vector<float> > genps_phi_handle;
        stop::Handle< std::vector<float> > genps_mass_handle;
        stop::Handle< float > mini_mt_handle;
        stop::Handle< float > mini_mtup_handle;
        stop::Handle< float > mini_mtdown_handle;
        stop::Handle< float > mini_isrweight_handle;
        stop::Handle< float > mini_met_handle;
        stop::Handle< float > mini_metup_handle;
        stop::Handle< float > mini_metdown_handle;
        stop::Handle< int > mini_sig_handle;
        stop::Handle< int > mini_cr1_handle;
        stop::Handle< int > mini_cr4_handle;
        stop::Handle< int > mini_cr5_handle;
        stop::Handle< int > mini_whsig_handle;
        stop::Handle< int > mini_whcr1_handle;
        stop::Handle< float > mini_chi2_handle;
        stop::Handle< float > mini_chi2up_handle;
        stop::Handle< float > mini_chi2down_handle;
        stop::Handle< float > mini_chi2bup_handle;
        stop::Handle< float > mini_chi2bdown_handle;
        stop::Handle< float > mini_mt2b_handle;
        stop::Handle< float > mini_mt2bl_handle;
        stop::Handle< float > mini_mt2w_handle;
        stop::Handle< float > mini_mt2wup_handle;
        stop::Handle< float > mini_mt2wdown_handle;
        stop::Handle< float > mini_mt2wbup_handle;
        stop::Handle< float > mini_mt2wbdown_handle;
        stop::Handle< float > mini_weight_handle;
        stop::Handle< float > mini_nvtxweight_handle;
        stop::Handle< float > mini_sltrigeff_handle;
        stop::Handle< float > mini_dltrigeff_handle;
        stop::Handle< int > mini_nsigevents_handle;
        stop::Handle< int > mini_nb_handle;
        stop::Handle< int > mini_nbupBC_handle;
        stop::Handle< int > mini_nbdownBC_handle;
        stop::Handle< int > mini_nbupL_handle;
        stop::Handle< int > mini_nbdownL_handle;
        stop::Handle< int > mini_njets_handle;
        stop::Handle< int > mini_njetsup_handle;
        stop::Handle< int > mini_njetsdown_handle;
        stop::Handle< int > mini_passisotrk_handle;
        stop::Handle< int > mini_passtauveto_handle;
        stop::Handle< int > mini_nlep_handle;
        stop::Handle< float > mini_lep1pt_handle;
        stop::Handle< float > mini_lep1eta_handle;
        stop::Handle< float > mini_lep2pt_handle;
        stop::Handle< float > mini_lep2eta_handle;
        stop::Handle< float > mini_dilmass_handle;
        stop::Handle< float > mini_mstop_handle;
        stop::Handle< float > mini_mlsp_handle;
        stop::Handle< float > mini_x_handle;
        stop::Handle< float > mini_xsecsusy_handle;
        stop::Handle< float > mini_dRleptB1_handle;
        stop::Handle< float > mini_dRleptB1_bup_handle;
        stop::Handle< float > mini_dRleptB1_bdown_handle;
        stop::Handle< float > mini_htssl_handle;
        stop::Handle< float > mini_htosl_handle;
        stop::Handle< float > mini_htratiol_handle;
        stop::Handle< float > mini_htssm_handle;
        stop::Handle< float > mini_htosm_handle;
        stop::Handle< float > mini_htratiom_handle;
        stop::Handle< float > mini_htratiomup_handle;
        stop::Handle< float > mini_htratiomdown_handle;
        stop::Handle< float > mini_dphimj1_handle;
        stop::Handle< float > mini_dphimj2_handle;
        stop::Handle< float > mini_dphimjmin_handle;
        stop::Handle< float > mini_pt_b_handle;
        stop::Handle< float > mini_pt_b_up_handle;
        stop::Handle< float > mini_pt_b_down_handle;
        stop::Handle< float > mini_pt_b_bup_handle;
        stop::Handle< float > mini_pt_b_bdown_handle;
        stop::Handle< float > mini_pt_J1_handle;
        stop::Handle< float > mini_pt_J2_handle;
        stop::Handle< float > mini_bbmass_handle;
        stop::Handle< float > mini_bbpt_handle;
        stop::Handle< float > mini_wpt_handle;
        stop::Handle< float > mini_bbwdphi_handle;
        stop::Handle< float > mini_rand_handle;
        stop::Handle< float > mini_t2ttLM_handle;
        stop::Handle< float > mini_t2ttHM_handle;
        stop::Handle< std::vector<float> > mini_bdt_handle;
        stop::Handle< std::vector<float> > mini_bdtup_handle;
        stop::Handle< std::vector<float> > mini_bdtdown_handle;
        stop::Handle< std::vector<float> > mini_bdtbup_handle;
        stop::Handle< std::vector<float> > mini_bdtbdown_handle;

};


// public interface 
// ------------------------------------------------------------------------------------------------- //

namespace stop
{

    const int& acc_2010();
    const int& acc_highmet();
    const int& acc_highht();
    const int& eldup();
    const int& csc();
    const int& hbhe();
    const int& hbhenew();
    const int& hcallaser();
    const int& ecaltp();
    const int& trkfail();
    const int& eebadsc();
    const int& lep1_badecallaser();
    const int& lep2_badecallaser();
    const int& isdata();
    const int& jetid();
    const int& jetid30();
    const int& json();
    const float& htoffset();
    const float& htuncor();
    const float& ptt();
    const float& pttbar();
    const float& ptttbar();
    const float& mttbar();
    const int& npartons();
    const int& nwzpartons();
    const int& hyptype();
    const float& maxpartonpt();
    const float& etattbar();
    const int& njetsoffset();
    const int& njetsuncor();
    const float& costhetaweight();
    const float& weight();
    const float& weightleft();
    const float& weightright();
    const float& mutrigweight();
    const float& mutrigweight2();
    const float& sltrigweight();
    const float& dltrigweight();
    const float& trgeff();
    const float& pthat();
    const float& qscale();
    const float& mgcor();
    const int& wflav();
    const float& ksusy();
    const float& ksusyup();
    const float& ksusydn();
    const float& xsecsusy();
    const float& xsecsusy2();
    const float& smeff();
    const float& k();
    const float& mllgen();
    const float& ptwgen();
    const float& ptzgen();
    const int& nlep();
    const int& nosel();
    const int& ngoodlep();
    const int& ngoodel();
    const int& ngoodmu();
    const int& mull();
    const int& mult();
    const int& mullgen();
    const int& multgen();
    const int& proc();
    const int& leptype();
    const float& topmass();
    const float& dilmass();
    const float& dilrecoil();
    const float& dilrecoilparl();
    const float& dilrecoilperp();
    const float& tcmet();
    const float& genmet();
    const float& gensumet();
    const float& genmetphi();
    const float& calomet();
    const float& calometphi();
    const float& trkmet();
    const float& trkmetphi();
    const float& trkmet_nolepcorr();
    const float& trkmetphi_nolepcorr();
    const float& pfmet();
    const float& pfmetveto();
    const float& pfmetsig();
    const float& pfmetphi();
    const float& pfsumet();
    const float& mucormet();
    const float& mucorjesmet();
    const float& tcmet35X();
    const float& tcmetevent();
    const float& tcmetlooper();
    const float& tcmetphi();
    const float& tcsumet();
    const float& tcmetUp();
    const float& tcmetDown();
    const float& tcmetTest();
    const float& pfmetUp();
    const float& pfmetDown();
    const float& pfmetTest();
    const float& sumjetpt();
    const float& dileta();
    const float& dilpt();
    const float& dildphi();
    const int& ngenjets();
    const int& njpt();
    const int& trgmu1();
    const int& trgmu2();
    const int& trgel1();
    const int& trgel2();
    const int& isomu24();
    const int& ele27wp80();
    const int& mm();
    const int& mmtk();
    const int& me();
    const int& em();
    const int& mu();
    const int& ee();
    const int& npfjets30();
    const int& npfjets30lepcorr();
    const float& knjets();
    const float& rhovor();
    const float& htpf30();
    const float& t1met10();
    const float& t1met20();
    const float& t1met30();
    const float& t1met10phi();
    const float& t1met20phi();
    const float& t1met30phi();
    const float& t1met10mt();
    const float& t1met20mt();
    const float& t1met30mt();
    const float& lepmetpt();
    const float& lept1met10pt();
    const float& t1met10s();
    const float& t1met10sphi();
    const float& t1met10smt();
    const float& t1metphicorr();
    const float& t1metphicorrup();
    const float& t1metphicorrdn();
    const float& t1metphicorrphi();
    const float& t1metphicorrphiup();
    const float& t1metphicorrphidn();
    const float& t1metphicorrlep();
    const float& t1metphicorrlepphi();
    const float& t1metphicorrmt();
    const float& t1metphicorrmtup();
    const float& t1metphicorrmtdn();
    const float& t1metphicorrlepmt();
    const float& t1met_off();
    const float& t1metphi_off();
    const float& t1metmt_off();
    const float& t1metphicorr_off();
    const float& t1metphicorrphi_off();
    const float& t1metphicorrmt_off();
    const float& mt2bmin();
    const float& mt2blmin();
    const float& mt2wmin();
    const float& chi2min();
    const float& chi2minprob();
    const int& nbtagsssv();
    const int& nbtagstcl();
    const int& nbtagstcm();
    const int& nbtagscsvl();
    const int& nbtagscsvm();
    const int& nbtagscsvt();
    const int& nbtagsssvcorr();
    const int& nbtagstclcorr();
    const int& nbtagstcmcorr();
    const int& nbtagscsvlcorr();
    const int& nbtagscsvmcorr();
    const int& nbtagscsvtcott();
    const int& njetsUp();
    const int& njetsDown();
    const float& htUp();
    const float& htDown();
    const int& ntruepu();
    const int& npu();
    const int& npuMinusOne();
    const int& npuPlusOne();
    const int& nvtx();
    const int& indexfirstGoodVertex_();
    const float& nvtxweight();
    const float& n3dvtxweight();
    const int& pdfid1();
    const int& pdfid2();
    const float& pdfx1();
    const float& pdfx2();
    const float& pdfQ();
    const float& vecjetpt();
    const int& pass();
    const int& passz();
    const float& m0();
    const float& mg();
    const float& ml();
    const float& x();
    const float& m12();
    const float& lep1chi2ndf();
    const float& lep2chi2ndf();
    const float& lep1dpt();
    const float& lep2dpt();
    const int& id1();
    const int& id2();
    const int& leptype1();
    const int& leptype2();
    const int& w1();
    const int& w2();
    const float& iso1();
    const float& isont1();
    const float& isopfold1();
    const float& isopf1();
    const float& etasc1();
    const float& etasc2();
    const float& eoverpin();
    const float& eoverpout();
    const float& dEtaIn();
    const float& dPhiIn();
    const float& sigmaIEtaIEta();
    const float& hOverE();
    const float& ooemoop();
    const float& d0vtx();
    const float& dzvtx();
    const float& expinnerlayers();
    const float& fbrem();
    const float& pfisoch();
    const float& pfisoem();
    const float& pfisonh();
    const float& eSC();
    const float& phiSC();
    const float& eSCRaw();
    const float& eSCPresh();
    const float& lep1_scslasercormean();
    const float& lep1_scslasercormax();
    const float& eoverpin2();
    const float& eoverpout2();
    const float& dEtaIn2();
    const float& dPhiIn2();
    const float& sigmaIEtaIEta2();
    const float& hOverE2();
    const float& ooemoop2();
    const float& d0vtx2();
    const float& dzvtx2();
    const float& expinnerlayers2();
    const float& fbrem2();
    const float& pfisoch2();
    const float& pfisoem2();
    const float& pfisonh2();
    const float& eSC2();
    const float& phiSC2();
    const float& eSCRaw2();
    const float& eSCPresh2();
    const float& lep2_scslasercormean();
    const float& lep2_scslasercormax();
    const float& scslasercormax();
    const float& scslasercormax_pt();
    const float& scslasercormax_eta();
    const float& iso2();
    const float& ecalveto1();
    const float& ecalveto2();
    const float& hcalveto1();
    const float& hcalveto2();
    const float& isont2();
    const float& isopf2();
    const float& ptl1();
    const float& ptl2();
    const float& etal1();
    const float& etal2();
    const float& phil1();
    const float& phil2();
    const float& meff();
    const float& mt();
    const char& dataset();
    const unsigned int& run();
    const unsigned int& lumi();
    const unsigned int& event();
    const float& y();
    const float& ht();
    const float& htgen();
    const float& htjpt();
    const int& nels();
    const int& nmus();
    const int& ntaus();
    const int& nleps();
    const int& nbs();
    const float& dphijm();
    const float& ptjetraw();
    const float& ptjet23();
    const float& ptjetF23();
    const float& ptjetO23();
    const int& mcid1();
    const float& mcdr1();
    const int& mcdecay1();
    const int& mcndec1();
    const int& mcndec2();
    const int& mcndeckls1();
    const int& mcndeckls2();
    const int& mcndecem1();
    const int& mcndecem2();
    const int& mcid2();
    const float& mcdr2();
    const int& mcdecay2();
    const float& mctaudpt1();
    const float& mctaudpt2();
    const int& mctaudid1();
    const int& mctaudid2();
    const int& mlepid();
    const int& mleppassid();
    const int& mleppassiso();
    const float& mlepiso();
    const float& mlepdr();
    const float& pflepiso();
    const float& pflepdr();
    const float& pfleppt();
    const float& pflepmindrj();
    const float& pftaudiso();
    const float& pftauddr();
    const float& pftaudpt();
    const float& pftaudmindrj();
    const int& pfcandid5();
    const float& pfcandiso5();
    const float& pfcandpt5();
    const float& pfcanddz5();
    const float& pfcandmindrj5();
    const int& pfcandid10();
    const float& pfcandiso10();
    const float& pfcandpt10();
    const float& pfcanddz10();
    const float& pfcandmindrj10();
    const int& pfcandidOS10();
    const float& pfcandisoOS10();
    const float& pfcandptOS10();
    const float& pfcanddzOS10();
    const int& pfcandid5looseZ();
    const float& pfcandiso5looseZ();
    const float& pfcandpt5looseZ();
    const float& pfcanddz5looseZ();
    const int& pfcandidOS10looseZ();
    const float& pfcandisoOS10looseZ();
    const float& pfcandptOS10looseZ();
    const float& pfcanddzOS10looseZ();
    const int& pfcanddirid10();
    const float& pfcanddiriso10();
    const float& pfcanddirpt10();
    const float& pfcanddirmindrj10();
    const int& pfcandvetoid10();
    const float& pfcandvetoiso10();
    const float& pfcandvetopt10();
    const float& pfcandvetomindrj10();
    const int& pfcandvetoLid10();
    const float& pfcandvetoLiso10();
    const float& pfcandvetoLpt10();
    const float& pfcandvetoLmindrj10();
    const float& emjet10();
    const float& mjj();
    const float& emjet20();
    const float& trkpt5();
    const float& trkpt10();
    const float& mleptrk5();
    const float& mleptrk10();
    const float& trkreliso5();
    const float& trkreliso10();
    const float& trkpt5loose();
    const float& trkpt10loose();
    const float& trkreliso5loose();
    const float& trkreliso10loose();
    const float& trkpt10pt0p1();
    const float& trkpt10pt0p2();
    const float& trkpt10pt0p3();
    const float& trkpt10pt0p4();
    const float& trkpt10pt0p5();
    const float& trkpt10pt0p6();
    const float& trkpt10pt0p7();
    const float& trkpt10pt0p8();
    const float& trkpt10pt0p9();
    const float& trkpt10pt1p0();
    const float& trkreliso10pt0p1();
    const float& trkreliso10pt0p2();
    const float& trkreliso10pt0p3();
    const float& trkreliso10pt0p4();
    const float& trkreliso10pt0p5();
    const float& trkreliso10pt0p6();
    const float& trkreliso10pt0p7();
    const float& trkreliso10pt0p8();
    const float& trkreliso10pt0p9();
    const float& trkreliso10pt1p0();
    const float& pfcandpt10pt0p1();
    const float& pfcandpt10pt0p2();
    const float& pfcandpt10pt0p3();
    const float& pfcandpt10pt0p4();
    const float& pfcandpt10pt0p5();
    const float& pfcandpt10pt0p6();
    const float& pfcandpt10pt0p7();
    const float& pfcandpt10pt0p8();
    const float& pfcandpt10pt0p9();
    const float& pfcandpt10pt1p0();
    const float& pfcandiso10pt0p1();
    const float& pfcandiso10pt0p2();
    const float& pfcandiso10pt0p3();
    const float& pfcandiso10pt0p4();
    const float& pfcandiso10pt0p5();
    const float& pfcandiso10pt0p6();
    const float& pfcandiso10pt0p7();
    const float& pfcandiso10pt0p8();
    const float& pfcandiso10pt0p9();
    const float& pfcandiso10pt1p0();
    const float& mbb();
    const float& lep1pfjetdr();
    const float& lep2pfjetdr();
    const LorentzVector& mclep();
    const LorentzVector& mcnu();
    const float& mcmln();
    const float& mcmtln();
    const LorentzVector& mlep();
    const LorentzVector& lep1();
    const LorentzVector& lep2();
    const LorentzVector& trklep1();
    const LorentzVector& trklep2();
    const LorentzVector& gfitlep1();
    const LorentzVector& gfitlep2();
    const LorentzVector& lepp();
    const LorentzVector& lepm();
    const LorentzVector& pflep1();
    const LorentzVector& pflep2();
    const LorentzVector& leppfjet1();
    const LorentzVector& leppfjet2();
    const LorentzVector& mclep1();
    const LorentzVector& mclep2();
    const LorentzVector& mctaud1();
    const LorentzVector& mctaud2();
    const LorentzVector& mctaudvis1();
    const LorentzVector& mctaudvis2();
    const LorentzVector& pflep();
    const LorentzVector& pftaud();
    const LorentzVector& pfcand5();
    const LorentzVector& pfcand10();
    const int& pfTau15_leadPtcandID();
    const LorentzVector& pfTau15();
    const LorentzVector& pfTau15_leadPtcand();
    const int& pfTau_leadPtcandID();
    const LorentzVector& pfTau();
    const LorentzVector& pfTau_leadPtcand();
    const int& pfTauLoose_leadPtcandID();
    const LorentzVector& pfTauLoose();
    const LorentzVector& pfTauLoose_leadPtcand();
    const LorentzVector& pfcandOS10();
    const LorentzVector& pfcandOS10looseZ();
    const LorentzVector& pfcand5looseZ();
    const LorentzVector& pfcanddir10();
    const LorentzVector& pfcandveto10();
    const LorentzVector& pfcandvetoL10();
    const LorentzVector& jet();
    const LorentzVector& nonisoel();
    const LorentzVector& nonisomu();
    const LorentzVector& t();
    const LorentzVector& tbar();
    const LorentzVector& ttbar();
    const LorentzVector& lep_t();
    const LorentzVector& lep_tbar();
    const LorentzVector& stop_t();
    const LorentzVector& stop_tbar();
    const LorentzVector& neutralino_t();
    const LorentzVector& neutralino_tbar();
    const int& lep_t_id();
    const int& lep_tbar_id();
    const std::vector<LorentzVector >& pfjets();
    const std::vector<LorentzVector >& pfjets_genJet_();
    const std::vector<float>& pfjets_csv();
    const std::vector<float>& pfjets_chm();
    const std::vector<float>& pfjets_neu();
    const std::vector<float>& pfjets_l1corr();
    const std::vector<float>& pfjets_corr();
    const std::vector<int>& pfjets_mc3();
    const std::vector<int>& pfjets_mcflavorAlgo();
    const std::vector<int>& pfjets_mcflavorPhys();
    const std::vector<float>& pfjets_uncertainty();
    const std::vector<int>& pfjets_flav();
    const std::vector<float>& pfjets_lrm();
    const std::vector<float>& pfjets_lrm2();
    const std::vector<float>& pfjets_qgtag();
    const std::vector<float>& pfjets_genJetDr();
    const std::vector<float>& pfjets_sigma();
    const std::vector<int>& pfjets_lepjet();
    const std::vector<float>& pfjets_beta();
    const std::vector<float>& pfjets_beta2();
    const std::vector<float>& pfjets_beta_0p1();
    const std::vector<float>& pfjets_beta_0p2();
    const std::vector<float>& pfjets_beta2_0p1();
    const std::vector<float>& pfjets_beta2_0p5();
    const std::vector<float>& pfjets_mvaPUid();
    const std::vector<float>& pfjets_mva5xPUid();
    const std::vector<float>& pfjets_mvaBeta();
    const std::vector<LorentzVector >& genbs();
    const std::vector<int>& genps_pdgId();
    const std::vector<int>& genps_firstMother();
    const std::vector<float>& genps_energy();
    const std::vector<float>& genps_pt();
    const std::vector<float>& genps_eta();
    const std::vector<float>& genps_phi();
    const std::vector<float>& genps_mass();
    const float& mini_mt();
    const float& mini_mtup();
    const float& mini_mtdown();
    const float& mini_isrweight();
    const float& mini_met();
    const float& mini_metup();
    const float& mini_metdown();
    const int& mini_sig();
    const int& mini_cr1();
    const int& mini_cr4();
    const int& mini_cr5();
    const int& mini_whsig();
    const int& mini_whcr1();
    const float& mini_chi2();
    const float& mini_chi2up();
    const float& mini_chi2down();
    const float& mini_chi2bup();
    const float& mini_chi2bdown();
    const float& mini_mt2b();
    const float& mini_mt2bl();
    const float& mini_mt2w();
    const float& mini_mt2wup();
    const float& mini_mt2wdown();
    const float& mini_mt2wbup();
    const float& mini_mt2wbdown();
    const float& mini_weight();
    const float& mini_nvtxweight();
    const float& mini_sltrigeff();
    const float& mini_dltrigeff();
    const int& mini_nsigevents();
    const int& mini_nb();
    const int& mini_nbupBC();
    const int& mini_nbdownBC();
    const int& mini_nbupL();
    const int& mini_nbdownL();
    const int& mini_njets();
    const int& mini_njetsup();
    const int& mini_njetsdown();
    const int& mini_passisotrk();
    const int& mini_passtauveto();
    const int& mini_nlep();
    const float& mini_lep1pt();
    const float& mini_lep1eta();
    const float& mini_lep2pt();
    const float& mini_lep2eta();
    const float& mini_dilmass();
    const float& mini_mstop();
    const float& mini_mlsp();
    const float& mini_x();
    const float& mini_xsecsusy();
    const float& mini_dRleptB1();
    const float& mini_dRleptB1_bup();
    const float& mini_dRleptB1_bdown();
    const float& mini_htssl();
    const float& mini_htosl();
    const float& mini_htratiol();
    const float& mini_htssm();
    const float& mini_htosm();
    const float& mini_htratiom();
    const float& mini_htratiomup();
    const float& mini_htratiomdown();
    const float& mini_dphimj1();
    const float& mini_dphimj2();
    const float& mini_dphimjmin();
    const float& mini_pt_b();
    const float& mini_pt_b_up();
    const float& mini_pt_b_down();
    const float& mini_pt_b_bup();
    const float& mini_pt_b_bdown();
    const float& mini_pt_J1();
    const float& mini_pt_J2();
    const float& mini_bbmass();
    const float& mini_bbpt();
    const float& mini_wpt();
    const float& mini_bbwdphi();
    const float& mini_rand();
    const float& mini_t2ttLM();
    const float& mini_t2ttHM();
    const std::vector<float>& mini_bdt();
    const std::vector<float>& mini_bdtup();
    const std::vector<float>& mini_bdtdown();
    const std::vector<float>& mini_bdtbup();
    const std::vector<float>& mini_bdtbdown();

} // namespace stop

#ifndef __CINT__
extern STOP_BABY stop_baby_obj;
#endif


#endif // STOP_BABY_H
