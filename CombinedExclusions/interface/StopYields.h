#ifndef STOP_YIELDS_H
#define STOP_YIELDS_H

#include <string>

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
        Yield total;
        Yield data;
    };

    // quick method to print the yields
    void PrintYieldTable();

} // namespace stop

#endif // STOP_YIELDS_H
