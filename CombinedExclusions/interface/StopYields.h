#ifndef STOP_YIELDS_H
#define STOP_YIELDS_H

namespace stop
{
    // simple struct to hold the values
    struct value_t
    {
        const float value;
        const float error;
    };

    struct Yield
    {
        value_t el;
        value_t mu;
        value_t lep;
    };

    struct Result
    {
        Yield ttdil;
        Yield single_top;
        Yield wjets;
        Yield rare;
        Yield total;
        Yield data;
    };

} // namespace stop

#endif // STOP_YIELDS_H


// yield[sr].rare.el.value = blah


