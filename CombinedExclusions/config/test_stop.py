import FWCore.ParameterSet.Config as cms
import os

## path the analysis (THIS SHOULD NOT CHANGE)
analysis_path = os.getenv("CMSSW_BASE") + "/src/StopAnalysis/CombinedExclusions"

## add the configuration path (THIS SHOULD NOT CHANGE)
import sys
sys.path.append(analysis_path + "/config")

## process to parse (THIS SHOULD NOT CHANGE)
process = cms.PSet()

## ------------------------------------------------------------- #
## Parameters for the selection, plot making, and fitting 
## ------------------------------------------------------------- #

process.stop_interp_plots = cms.PSet(

	## path to the analysis
	analysis_path = cms.string(analysis_path),

	## the sample name (from Sample.h/cc) 
	sample_name = cms.string("t2tt"),
	
	## integrated luminosity 
	lumi = cms.double(19.5),
	
	## output label to give it a unique name
	output_label = cms.string("stop_test"),

	## analysis type name 
	analysis_type_name = cms.string("bdt"),
	
	## search regions
	search_regions = cms.vuint32(0, 1, 2, 3, 4, 5, 6),

	## signal uncertainties measured elsewhere
	unc_lumi = cms.double(0.044),
	unc_trig = cms.double(0.030),
	unc_lept = cms.double(0.050),

	## select a specific sparm parameter
	mass_stop = cms.double(-1),
	mass_lsp  = cms.double(-1),
	
	## suffix to print the plots (before the fit)
	## blank means do not print
	## available options are: eps, png, pdf
	suffix = cms.string(""), 
	
	## xsec histogram
	## taken from Ben's code -- not consistent with
	## https://twiki.cern.ch/twiki/bin/viewauth/CMS/SUSYCrossSectionsForProjections
	xsec_file_path = cms.string(analysis_path + "/data/stop_xsec.root"),
	xsec_hist_name = cms.string("h_stop_xsec"),
	
	## max number of events to run on
	max_events = cms.int64(-1),
	
	## verbosity (for trouble shooting)
	verbose = cms.bool(False),
)
