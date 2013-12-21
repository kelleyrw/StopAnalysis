#ifndef STOP_YIELDS_H
#define STOP_YIELDS_H

#include <string>
#include <iostream>
#include "StopAnalysis/CombinedExclusions/interface/SignalRegion.h"

namespace stop
{
    // simple struct to hold the yield
    struct Yield
    {
        struct value_t
        {
            // members:
            double value;
            double error;
        
            // methods:
            std::string pm() const;
            double frac_error() const;
        };

        value_t el;
        value_t mu;
        value_t lep;
    };

    // simple struct to hold the results
    struct Result
    {
        Yield ttdil;
        Yield ttslo;
        Yield wjets;
        Yield rare;
        Yield bkgd;
        Yield data;
    };

    // retun the results for each signal region (for BDT only for now)
    typedef Result ResultArray[stop::SignalRegion::static_size];
    const ResultArray& GetResultArray();

    // return the results for an individual SR
    const Result& GetResult(const stop::SignalRegion::value_type signal_region);

    // quick method to print the yields
    void PrintYieldTable(std::ostream& out = std::cout);

} // namespace stop

#endif // STOP_YIELDS_H
