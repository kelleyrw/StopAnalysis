#!/usr/bin/env python

# ------------------#
# imports
# ------------------#

from optparse import OptionParser
import math
import os
import sys

# ------------------#
# parse inputs
# ------------------#

# parameter options
parser = OptionParser()
parser.add_option("--card"  , dest="card"                , type="string", help="card to run on"                                                 )
parser.add_option("--method", dest="method", default=1   , type="int"   , help="method -- 1: asymptotic, 2: hybrid no grid, 3: hybrid with grid")
parser.add_option("--ngrid" , dest="ngrid" , default=10  , type="int"   , help="number of points on the grid (method 3 only)"                   )
parser.add_option("--seed"  , dest="seed"  , default=1000, type="int"   , help="seed for the combine job"                                       )
(options, args) = parser.parse_args()

# check for validity
def CheckOptions():
    """Check the inputs are valid"""

    # check that input exists
    if (not options.card or not os.path.isfile(options.card)):
        raise Exception("required card is missing is invalid")

    return

# ------------------#
# asymptotic limit 
# ------------------#

def GetCardStem():
    """Extract the basename of the card """
    return os.path.splitext(os.path.basename(options.card))[0]

def AsymptoticLimit():
    """Run the asympotic limit"""

    # command
    cmd = "combine %s" % options.card

    # output
    cmd += " --name _%s" % GetCardStem()

    # options
    cmd += " --method Asymptotic --minimizerTolerance 0.0001 --rRelAcc 0.0001 --verbose 2"

    # options
    cmd += " --seed %d" % options.seed

    # run it
    print "[stop_produce_limit] running asymptotic"
    print cmd
    os.system(cmd)

    return

from ROOT import *

def ExtractAsymptoticLimit():
    """Extract the asymptotic limit from ROOT file"""

    # open the resulting ROOT file
    root_file = "higgsCombine_%s.Asymptotic.mH120.%d.root" % (GetCardStem(), options.seed)
    chain = TChain("limit")
    chain.Add(root_file)

    # set branches from TChain 
    gROOT.ProcessLine(
    "struct entry_t\
    {\
        double limit;\
        double limitErr;\
        double mh;\
        double syst;\
        int iToy;\
        int iSeed;\
        int iChannel;\
        float t_cpu;\
        float t_rea;\
        double quantileExpected;\
    };")
    entry = entry_t()
    chain.SetBranchAddress("limit", AddressOf(entry, "limit"))

    # extract limits
    limits = [0, 0, 0, 0, 0, 0]
    chain.GetEntry(0); limits[0] = entry.limit # exp - 2s
    chain.GetEntry(1); limits[1] = entry.limit # exp - 1s
    chain.GetEntry(2); limits[2] = entry.limit # exp
    chain.GetEntry(3); limits[3] = entry.limit # exp + 1s
    chain.GetEntry(4); limits[4] = entry.limit # exp + 2s
    chain.GetEntry(5); limits[5] = entry.limit # obs

    return limits

# ------------------#
# hybrid with no grid 
# ------------------#

def HybridLimitNoGridSingleQuantile(quantile=-1):
    """Run the hybrid limit without using a pre-generated grid for a single quantile"""

    # command
    cmd = "combine %s" % options.card

    # output
    cmd += " --name _%s_nogrid" % GetCardStem() 

    # options
    cmd += " --method HybridNew --frequentist --testStat LHC --hintMethod Asymptotic --clsAcc 0.005 --fork 10"

    #quantile
    if (quantile > 0):
    	cmd += " --expectedFromGrid %f" % quantile

    # seed
    cmd += " --seed %d" % options.seed

    # run it
    print cmd
    os.system(cmd)
    
    return

def HybridLimitNoGrid():
    """Run the hybrid limit without using a pre-generated grid for a obs and expected limits"""

    # run combine for each quantile
    print "[stop_produce_limit] running hybrid new without pre-generated grid"
    HybridLimitNoGridSingleQuantile(quantile=-1   )
    HybridLimitNoGridSingleQuantile(quantile=0.5  )
    HybridLimitNoGridSingleQuantile(quantile=0.16 )
    HybridLimitNoGridSingleQuantile(quantile=0.84 )
    HybridLimitNoGridSingleQuantile(quantile=0.025)
    HybridLimitNoGridSingleQuantile(quantile=0.975)

    # combine all the ROOT files
    name = "%s_nogrid" % GetCardStem()
    cmd  = "hadd -f higgsCombine_%s.HybridNew.%d.root higgsCombine_%s.HybridNew.mH120.*" % (name, options.seed, name)
    print "[stop_produce_limit] combining output"
    print cmd
    os.system(cmd)

    return

# ------------------#
# hybrid with grid 
# ------------------#

def GenerateRValues():
    """Generate a list of r-values"""

    AsymptoticLimit()
    limits    = ExtractAsymptoticLimit()
    limit_min = math.floor(10*0.5*limits[0]) / 10.0
    limit_max = math.ceil (10*1.5*limits[4]) / 10.0
    step      = (limit_max-limit_min)/(options.ngrid-1)
    rvalues   = [limit_min + n*step for n in range(0, options.ngrid)]
    print "[stop_produce_limit] generating grid with values: ", rvalues

    return rvalues

def GenerateGrid():
    """Create a pre-generated grid for the hybrid new calculation"""

    # generate grid
    rvalues = GenerateRValues()
    seed_delta=0
    for r in rvalues:
        # command
        cmd = "combine %s" % options.card
        
        # output
        cmd += " --name _grid_%s_r%s" % (GetCardStem(), ("%1.4f" % r).replace(".", "p"))
    
        # options
        cmd += " --method HybridNew --frequentist --testStat LHC --clsAcc 0 --toysH 1000 --iterations 1 --fullBToys --singlePoint %1.4f --saveToys --saveHybridResult --fork 10 --rMin %1.0f --rMax %1.0f" % (r, 0, 1.5*r)
    
        # seed
        seed = seed_delta + options.seed
        cmd += " --seed %d" % seed
        seed_delta += 1
    
        # run it
        print cmd
        os.system(cmd)
    
    # combine the grid files
    cmd = "hadd -f higgsCombine_grid_%s_n%d.root higgsCombine_grid_*_r*.root" % (GetCardStem(), options.ngrid)
    print cmd
    os.system(cmd)

    return

def HybridLimitWithGridSingleQuantile(quantile=-1):
    """Run the hybrid limit witt using a pre-generated grid for a single quantile"""

    # command
    cmd = "combine %s" % options.card

    # output
    cmd += " --name _%s_grid" % GetCardStem()

    # options
    grid_file = "higgsCombine_grid_%s_n%d.root" % (GetCardStem(), options.ngrid)
    cmd += " --method HybridNew --frequentist --clsAcc 0.005 --grid=%s --verbose 2 --fork 10" % grid_file

    #quantile
    if (quantile > 0):
    	cmd += " --expectedFromGrid %f" % quantile

    # options
    cmd += " --seed %d" % options.seed

    # run it
    print cmd
    os.system(cmd)
    return

def HybridLimitWithGrid():
    """Run the hybrid limit with using a pre-generated grid for a obs and expected limits"""

    # Generate the grid
    GenerateGrid()

    # run combine for each quantile
    print "[stop_produce_limit] running hybrid new with pre-generated grid"
    HybridLimitWithGridSingleQuantile(quantile=-1   )
    HybridLimitWithGridSingleQuantile(quantile=0.5  )
    HybridLimitWithGridSingleQuantile(quantile=0.16 )
    HybridLimitWithGridSingleQuantile(quantile=0.84 )
    HybridLimitWithGridSingleQuantile(quantile=0.025)
    HybridLimitWithGridSingleQuantile(quantile=0.975)

    # combine all the ROOT files
    name = "%s_grid" % GetCardStem()
    cmd  = "hadd -f higgsCombine_%s.HybridNew.%d.root higgsCombine_%s.HybridNew.mH120.*" % (name, options.seed, name)
    print "[stop_produce_limit] combining output"
    print cmd
    os.system(cmd)
    return

# ------------------#
# rename output file
# ------------------#
def RenameOutputFile():
    """Standardize the output name"""

    # original name
    if   (options.method==1): old_name = "higgsCombine_%s.Asymptotic.mH120.%d.root" % (GetCardStem(), options.seed)
    elif (options.method==2): old_name = "higgsCombine_%s_nogrid.HybridNew.%d.root" % (GetCardStem(), options.seed)
    elif (options.method==3): old_name = "higgsCombine_%s_grid.HybridNew.%d.root"   % (GetCardStem(), options.seed)

    # new name
    new_name = "combine_output_%s.root" % GetCardStem()

    # execuse rename
    cmd = "cp %s %s" % (old_name, new_name)
    print cmd
    os.system(cmd)
    return

# ------------------#
# "main program" 
# ------------------#

def main():

    try:
        # check the options
        CheckOptions()

        # run assymptotic limit
        if   (options.method == 1): AsymptoticLimit()
        elif (options.method == 2): HybridLimitNoGrid()
        elif (options.method == 3): HybridLimitWithGrid()

        # rename output file
        RenameOutputFile()

        return 0

    except Exception, e:
        print "[stop_produce_limit] ERROR:", e
        return 1
    except:
        print "[stop_produce_limit] ERROR:", sys.exc_info()[0]
        return 1

# do it
if __name__ == '__main__':
    main()
