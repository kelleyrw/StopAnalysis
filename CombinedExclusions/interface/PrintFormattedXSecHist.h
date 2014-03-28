#ifndef STOP_PRINTFORMATTEDXSECHIST_H 
#define STOP_PRINTFORMATTEDXSECHIST_H 

#include <string>
#include "TH2F.h"

namespace stop
{
    void PrintFormattedXSecHist
    (
        TH2F& hist,
        const std::string& plot_name,
        const std::string& path,
        const std::string& suffix,
        const std::string& draw_option,
        const std::string& paint_text_option = "1.0f",
        const float zmin = 1.0f,
        const float zmax = -1.0f
   );

} // namspace stop

#endif // STOP_PRINTFORMATTEDXSECHIST_H 
