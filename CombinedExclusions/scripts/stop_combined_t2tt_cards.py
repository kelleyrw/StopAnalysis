#!/usr/bin/env python

# ------------------#
# imports
# ------------------#

from optparse import OptionParser
import os
import sys

# ------------------#
# parse inputs
# ------------------#

# parameter options
parser = OptionParser()
parser.add_option("--onelep_cards" , dest="onelep_path"  , default="cards/t2tt/singlelep"          , help="path to the single lepton cards"     )
parser.add_option("--razor_cards"  , dest="razor_path"   , default="cards/t2tt/razor"              , help="path to the razor cards"             )
parser.add_option("--combine_cards", dest="combined_path", default="cards/t2tt/combined"           , help="path to the combined lepton cards"   )
parser.add_option("--sr_filename"  , dest="sr_filename"  , default="data/T2tt_onelep_bdt_orig.root", help="path to the onelep best SR histogram")
parser.add_option("--sr_histname"  , dest="sr_histname"  , default="hbest"                         , help="name of the onelep best SR histogram")
parser.add_option("--mass_stop"    , dest="mass_stop"    , default=-1                              , help="mass stop (-1 means full plane)"     )
parser.add_option("--mass_lsp"     , dest="mass_lsp"     , default=-1                              , help="mass LSP (-1 means full plane)"      )
(options, args) = parser.parse_args()

# convert to ints (how do i do this automatically?)
options.mass_stop = int(options.mass_stop)
options.mass_lsp  = int(options.mass_lsp )

# check for validity
def CheckOptions():
	# onelep_path
	if (not options.onelep_path or not os.path.isdir(options.onelep_path)):
		raise Exception("required onelep_path is missing")

	# razor_path
	if (not options.razor_path or not os.path.isdir(options.razor_path)):
		raise Exception("required razor_path is missing")

	# combined_path
	if (not options.combined_path):
		raise Exception("required combined_path is missing")

	# tree_name
	if (not options.sr_filename or not os.path.isfile(options.sr_filename)):
		raise Exception("required sr_filename is missing")

	# tree_name
	if (not options.sr_histname):
		raise Exception("required sr_histname is missing")

	return

# ------------------#
# get the best SR 
# ------------------#

from ROOT import TFile, TH1

def GetBestSRHist():
	# get the tree
	file = TFile.Open(options.sr_filename)
	if file.IsZombie():
		raise Exception("[stop_combine_t2tt_card.py] file is zombie")
	hist = file.Get(options.sr_histname)
	if not hist:
		raise ValueError("%s not found in %s" % (options.sr_histname, options.sr_filename))
	return hist

def GetBestSR(hist, mass_stop, mass_lsp):
	bdt_label = {
		'1' : "bdt1l",
		'2' : "bdt1t",
		'3' : "bdt2",
		'4' : "bdt3",
		'5' : "bdt4",
		'6' : "bdt5"
	}
	xbin   = hist.GetXaxis().FindBin(mass_stop)
	ybin   = hist.GetYaxis().FindBin(mass_lsp)
	result = bdt_label["%1.0f" % hist.GetBinContent(xbin, ybin)]
	return result

# ---------------------------#
# get the appropriate masses
# ---------------------------#

def GetStopMasses():
	default_masses = range(100, 825, 25)
	if (options.mass_stop < 0):
		return default_masses
	if options.mass_stop in default_masses:
		return range(options.mass_stop, options.mass_stop+1)
	else:
		raise ValueError("mass_stop = %s out of bounds -- must be in %s" % (options.mass_stop, default_masses))

def GetLSPMasses():
	default_masses = range(0, 725, 25)
	if (options.mass_lsp < 0):
		return default_masses
	if options.mass_lsp in default_masses:
		return range(options.mass_lsp, options.mass_lsp+1)
	else:
		raise ValueError("mass_lsp = %s out of bounds -- must be in %s" % (options.mass_lsp, default_masses))

# ------------------#
# "main program" 
# ------------------#



def main():

	try:
		# check the validity of the options
		CheckOptions()

		# best signal region histogram
		hist_best_sr = GetBestSRHist()

		# make combined dir if doens't exist
		if (not os.path.exists(options.combined_path)):
			os.makedirs(options.combined_path)

		# loop over the selected masses create the card
		stop_masses = GetStopMasses()
		lsp_masses  = GetLSPMasses()
		for mass_stop in stop_masses:
			for mass_lsp in lsp_masses:

				if (mass_lsp > (mass_stop - 100)):
					continue

				# get the single lepton best SR's card name
				best_sr = GetBestSR(hist_best_sr, mass_stop, mass_lsp)
				onelep_card = "t2tt_%1.0f_%1.0f_%s.txt" % (mass_stop, mass_lsp, best_sr)
				onelep_full = "%s/%s" % (options.onelep_path, onelep_card)
				if (not os.path.isfile(onelep_full)):
					print ("single lepton card %s does not exist -- skipping" % onelep_full)
					continue
				else:
					cmd = "cp %s %s/." % (onelep_full, options.combined_path)
					os.system(cmd)

				# get the razor card name
				razor_card = "razor_combine_Had_T2tt_MG_%1.0f.000000_MCHI_%1.0f.000000.txt" % (mass_stop, mass_lsp)
				razor_full = "%s/%s" % (options.razor_path, razor_card)
				if (not os.path.isfile(razor_full)):
					print ("razor card %s does not exist -- skipping" % razor_full)
					continue
				razor_multijet_root = "%s/razor_combine_MultiJet_T2tt_MG_%1.0f.000000_MCHI_%1.0f.000000.root" % (options.razor_path, mass_stop, mass_lsp)
				if (not os.path.isfile(razor_multijet_root)):
					print ("razor ROOT file %s does not exist -- skipping" % razor_multijet_root)
					continue
				razor_jet2b_root = "%s/razor_combine_Jet2b_T2tt_MG_%1.0f.000000_MCHI_%1.0f.000000.root" % (options.razor_path, mass_stop, mass_lsp)
				if (not os.path.isfile(razor_jet2b_root)):
					print ("razor ROOT file %s does not exist -- skipping" % razor_jet2b_root)
					continue

				# combine command:
				combined_card = "combined_t2tt_%1.0f_%1.0f_%s.txt" % (mass_stop, mass_lsp, best_sr)
				cmd =  "cp %s %s/."        % (razor_full         , options.combined_path)
				cmd += "; \\\n cp %s %s/." % (onelep_full        , options.combined_path)
				cmd += "; \\\n cp %s %s/." % (razor_multijet_root, options.combined_path)
				cmd += "; \\\n cp %s %s/." % (razor_jet2b_root   , options.combined_path)
				cmd += "; \\\n pushd %s"   % options.combined_path
				cmd += "; \\\n combineCards.py had=%s onelep=%s > %s" % (razor_card, onelep_card, combined_card)
				cmd += "; \\\n popd"

				# make combined dir if doens't exist
				#print cmd
				os.system(cmd)

	except Exception, e:
		print "[stop_combine_t2tt_cards] ERROR:", e
		return 1
	except:
		print "[stop_combine_t2tt_cards] ERROR:", sys.exc_info()[0]
		return 1

# do it
if __name__ == '__main__':
	main()
