{
    // load the AnalysisTools for interactive use 
    const TString cmssw_base = gSystem->Getenv("CMSSW_BASE");
    const bool cmssw = cmssw_base.Length() > 0;
    if (cmssw)
    {
        std::cout << "Loading Stop tools" << std::endl;
        const TString scram_arch = gSystem->Getenv("SCRAM_ARCH");
        const TString cmssw_lib  = Form("%s/lib/%s", cmssw_base.Data(), scram_arch.Data());
        const TString dy_suffix  = (scram_arch.Contains("osx") ? "dylib" : "so");

        gSystem->AddIncludePath(Form("-I\"%s/src/StopAnalysis/CombinedExclusions/interface\"", cmssw_base.Data()));
        gSystem->Load(Form("%s/libStopAnalysisCombinedExclusions.%s", cmssw_lib.Data(), dy_suffix.Data()));
    }
}
