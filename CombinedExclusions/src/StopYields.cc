#include "StopAnalysis/CombinedExclusions/interface/StopYields.h"
#include "StopAnalysis/CombinedExclusions/interface/SignalRegion.h"
#include "AnalysisTools/LanguageTools/interface/LanguageTools.h"

namespace stop
{
    // simple struct to print +/-
    std::string Yield::value_t::pm() const
    {
        return lt::pm(value, error, "4.1");
    }

    // calc the percent error 
    double Yield::value_t::frac_error() const
    {
        return error/value;
    }

    // static variable to hold the data
    // Taken from AN-2013/89 (page 48)
    // http://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2013_089_v9.pdf
    // BDT only results
    static const ResultArray s_yields = 
    {
        //                electrons       muons           both
        { // preselection (not used)
            /* ttdil */{{-99.0, 0.0 }, {-99.0, 0.0 }, {-99.0, 0.0  }},
            /* ttslo */{{-99.0, 0.0 }, {-99.0, 0.0 }, {-99.0, 0.0  }},
            /* wjets */{{-99.0, 0.0 }, {-99.0, 0.0 }, {-99.0, 0.0  }},
            /* rare  */{{-99.0, 0.0 }, {-99.0, 0.0 }, {-99.0, 0.0  }},
            /* bkgd  */{{-99.0, 0.0 }, {-99.0, 0.0 }, {-99.0, 0.0  }},
            /* data  */{{-99.0, 0.0 }, {-99.0, 0.0 }, {-99.0, 0.0  }},
        },
        { // BDT1 Loose
            /* ttdil */{{181.7, 16.2}, {256.6, 22.2}, {438.2, 36.8 }},
            /* ttslo */{{97.8 , 36.3}, {153.7, 57.1}, {251.4, 93.3 }},
            /* wjets */{{10.5 , 2.7 }, {16.2 , 4.1 }, {26.7 , 6.8  }},
            /* rare  */{{19.0 , 9.5 }, {27.8 , 13.9}, {46.8 , 23.4 }},
            /* bkgd  */{{308.9, 40.6}, {454.3, 62.3}, {763.1, 102.2}},
            /* data  */{{300  , 0   }, {428  , 0   }, {728  , 0    }},
        },
        { // BDT1 Title
            /* ttdil */{{31.6 , 5.7 }, {67.9 , 11.3}, {36.3 , 6.4  }}, 
            /* ttslo */{{15.7 , 7.2 }, {37.3 , 17.1}, {21.6 , 10.0 }}, 
            /* wjets */{{3.0  , 0.8 }, {7.2  , 1.9 }, {4.2  , 1.1  }}, 
            /* rare  */{{4.6  , 2.3 }, {11.3 , 5.6 }, {6.6  , 3.3  }}, 
            /* bkgd  */{{54.9 , 9.4 }, {123.7, 21.1}, {68.7 , 12.2 }}, 
            /* data  */{{37   , 0   }, {104  , 0   }, {67   , 0    }} 
        },
        { // BDT2
            /* ttdil */{{21.3 , 5.0 }, {25.2 , 5.7 }, {46.4 , 10.1 }},
            /* ttslo */{{9.7  , 5.3 }, {12.5 , 6.8 }, {22.2 , 12.1 }},
            /* wjets */{{2.5  , 0.7 }, {3.6  , 1.0 }, {6.2  , 1.7  }},
            /* rare  */{{3.8  , 1.9 }, {6.0  , 3.0 }, {9.8  , 4.9  }},
            /* bkgd  */{{37.3 , 7.5 }, {47.3 , 9.3 }, {84.6 , 16.3 }},
            /* data  */{{23   , 0   }, {33   , 0   }, {56   , 0    }}
        },
        { // BDT3
            /* ttdil */{{2.4  , 1.1 }, {2.3  , 1.1 }, {4.6  , 1.9  }},
            /* ttslo */{{1.3  , 1.0 }, {2.3  , 1.8 }, { 3.6 , 2.8  }},
            /* wjets */{{0.9  , 0.3 }, {1.3  , 0.4 }, {2.2  , 0.7  }},
            /* rare  */{{1.1  , 0.5 }, {1.5  , 0.8 }, {2.6  , 1.3  }},
            /* bkgd  */{{5.5  , 1.6 }, {7.5  , 2.2 }, {13.0 , 3.6  }},
            /* data  */{{3    , 0   }, {5    , 0   }, {8    , 0    }}
        },
        { // BDT4
            /* ttdil */{{0.3  , 0.3 }, {0.1  , 0.1 }, {0.3  , 0.3  }},
            /* ttslo */{{0.2  , 0.3 }, {0.6  , 0.7 }, { 0.8 , 0.9  }},
            /* wjets */{{0.3  , 0.1 }, {0.5  , 0.2 }, {0.8  , 0.3  }},
            /* rare  */{{0.4  , 0.2 }, {0.6  , 0.3 }, {1.0  , 0.5  }},
            /* bkgd  */{{1.1  , 0.4 }, {1.8  , 0.8 }, {2.9  , 1.1  }},
            /* data  */{{1    , 0   }, {1    , 0   }, {2    , 0    }}
        },
        { // BDT5
            /* ttdil */{{19.6 , 5.5 }, {28.5 , 7.7 }, {48.1 , 12.7 }},
            /* ttslo */{{10.5 , 4.3 }, {19.1 , 7.7 }, { 29.6, 11.8 }},
            /* wjets */{{2.0  , 0.7 }, {3.1  , 1.1 }, {5.1  , 1.8  }},
            /* rare  */{{1.8  , 0.9 }, {2.3  , 1.2 }, {4.1  , 2.0  }},
            /* bkgd  */{{33.9 , 7.0 }, {52.9 , 11.0}, {86.9 , 17.6 }},
            /* data  */{{35   , 0   }, {41   , 0   }, {76   , 0    }}
        }
    };

    // retun the results for each signal region (for BDT only for now)
    const ResultArray& GetResultArray()
    {
        return s_yields;
    }

    // return the results for an individual SR
    const Result& GetResult(const stop::SignalRegion::value_type signal_region)
    {
        return s_yields[signal_region];
    }

    // quick method to print the yields
    void PrintYieldTable(std::ostream& out)
    {
        // convenience reference
        const ResultArray& y = GetResultArray();

        CTable t_mu;
        t_mu.useTitle();
        t_mu.setTitle("Stop Yields Muons");
        t_mu.setTable()(                                                "BDT1L",            "BDT1T",             "BDT2",             "BDT3",             "BDT4",             "BDT5")
                    ("t\\bar{t} \\rigtharrow \\ell\\ell" , y[1].ttdil.mu.pm() , y[2].ttdil.mu.pm() , y[3].ttdil.mu.pm() , y[4].ttdil.mu.pm() , y[5].ttdil.mu.pm() , y[6].ttdil.mu.pm())
                    ("t\\bar{t} \\rigtharrow \\ell + X"  , y[1].ttslo.mu.pm() , y[2].ttslo.mu.pm() , y[3].ttslo.mu.pm() , y[4].ttslo.mu.pm() , y[5].ttslo.mu.pm() , y[6].ttslo.mu.pm())
                    ("W + \\text{jets}"                  , y[1].wjets.mu.pm() , y[2].wjets.mu.pm() , y[3].wjets.mu.pm() , y[4].wjets.mu.pm() , y[5].wjets.mu.pm() , y[6].wjets.mu.pm())
                    ("Rare"                              , y[1].rare.mu.pm()  , y[2].rare.mu.pm()  , y[3].rare.mu.pm()  , y[4].rare.mu.pm()  , y[5].rare.mu.pm()  , y[6].rare.mu.pm() )
                    ("Total"                             , y[1].bkgd.mu.pm()  , y[2].bkgd.mu.pm()  , y[3].bkgd.mu.pm()  , y[4].bkgd.mu.pm()  , y[5].bkgd.mu.pm()  , y[6].bkgd.mu.pm())
                    ("Data"                              , y[1].data.mu.value , y[2].data.mu.value , y[3].data.mu.value , y[4].data.mu.value , y[5].data.mu.value , y[6].data.mu.value)
                    ;
        out << t_mu << std::endl;

        CTable t_el;
        t_el.useTitle();
        t_el.setTitle("Stop Yields Electron");
        t_el.setTable()(                                                "BDT1L",            "BDT1T",             "BDT2",             "BDT3",             "BDT4",             "BDT5")
                    ("t\\bar{t} \\rigtharrow \\ell\\ell" , y[1].ttdil.el.pm() , y[2].ttdil.el.pm() , y[3].ttdil.el.pm() , y[4].ttdil.el.pm() , y[5].ttdil.el.pm() , y[6].ttdil.el.pm())
                    ("t\\bar{t} \\rigtharrow \\ell + X"  , y[1].ttslo.el.pm() , y[2].ttslo.el.pm() , y[3].ttslo.el.pm() , y[4].ttslo.el.pm() , y[5].ttslo.el.pm() , y[6].ttslo.el.pm())
                    ("W + \\text{jets}"                  , y[1].wjets.el.pm() , y[2].wjets.el.pm() , y[3].wjets.el.pm() , y[4].wjets.el.pm() , y[5].wjets.el.pm() , y[6].wjets.el.pm())
                    ("Rare"                              , y[1].rare.el.pm()  , y[2].rare.el.pm()  , y[3].rare.el.pm()  , y[4].rare.el.pm()  , y[5].rare.el.pm()  , y[6].rare.el.pm() )
                    ("Total"                             , y[1].bkgd.el.pm()  , y[2].bkgd.el.pm()  , y[3].bkgd.el.pm()  , y[4].bkgd.el.pm()  , y[5].bkgd.el.pm()  , y[6].bkgd.el.pm())
                    ("Data"                              , y[1].data.el.value , y[2].data.el.value , y[3].data.el.value , y[4].data.el.value , y[5].data.el.value , y[6].data.el.value)
                    ;
        out << t_el << std::endl;

        CTable t_lep;
        t_lep.useTitle();
        t_lep.setTitle("Stop Yields Muon+Electron");
        t_lep.setTable()(                                                "BDT1L",            "BDT1T",             "BDT2",             "BDT3",             "BDT4",             "BDT5")
                    ("t\\bar{t} \\rigtharrow \\ell\\ell" , y[1].ttdil.lep.pm() , y[2].ttdil.lep.pm() , y[3].ttdil.lep.pm() , y[4].ttdil.lep.pm() , y[5].ttdil.lep.pm() , y[6].ttdil.lep.pm())
                    ("t\\bar{t} \\rigtharrow \\ell + X"  , y[1].ttslo.lep.pm() , y[2].ttslo.lep.pm() , y[3].ttslo.lep.pm() , y[4].ttslo.lep.pm() , y[5].ttslo.lep.pm() , y[6].ttslo.lep.pm())
                    ("W + \\text{jets}"                  , y[1].wjets.lep.pm() , y[2].wjets.lep.pm() , y[3].wjets.lep.pm() , y[4].wjets.lep.pm() , y[5].wjets.lep.pm() , y[6].wjets.lep.pm())
                    ("Rare"                              , y[1].rare.lep.pm()  , y[2].rare.lep.pm()  , y[3].rare.lep.pm()  , y[4].rare.lep.pm()  , y[5].rare.lep.pm()  , y[6].rare.lep.pm() )
                    ("Total"                             , y[1].bkgd.lep.pm()  , y[2].bkgd.lep.pm()  , y[3].bkgd.lep.pm()  , y[4].bkgd.lep.pm()  , y[5].bkgd.lep.pm()  , y[6].bkgd.lep.pm())
                    ("Data"                              , y[1].data.lep.value , y[2].data.lep.value , y[3].data.lep.value , y[4].data.lep.value , y[5].data.lep.value , y[6].data.lep.value)
                    ;
        out << t_lep << std::endl;
    }

} // namespace stop




 
 
 
 
 
 

 
 
 
 
 

 
 
 
 
 
 








 
 
 
 
 









            
            
            
            
            
            
            
            
            
             
