#include "StopAnalysis/CombinedExclusions/interface/Sample.h"
#include "StopAnalysis/CombinedExclusions/interface/AnalysisType.h"
#include "StopAnalysis/CombinedExclusions/interface/SignalRegion.h"
#include "StopAnalysis/CombinedExclusions/interface/StopYields.h"
#ifdef __MAKECINT__ 

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace stop;
#pragma link C++ class stop::AnalysisType+;
#pragma link C++ class stop::Sample+;
#pragma link C++ class stop::SignalRegion+;
#pragma link C++ class stop::Yield+;
#pragma link C++ class stop::Result+;
#pragma link C++ enum stop::AnalysisType::value_type;
#pragma link C++ enum stop::Sample::value_type;
#pragma link C++ enum stop::SignalRegion::value_type;
#pragma link C++ typedef stop::ResultArray;
// #pragma link C++ function stop::GetResultArray;
// #pragma link C++ function stop::GetResult;
// #pragma link C++ function stop::PrintYieldTable;

#endif
