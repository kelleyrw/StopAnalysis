#!/bin/bash

# ---------------------------------------------------------------------------------- #
# Simple wrapper script to create the StopBaby.h/cc wrappers for the looper.
# It uses the makeTTreeClassFiles.py
#
# Usage: makeStopBabyClassFiles.sh stop_baby_file_name
# ---------------------------------------------------------------------------------- #

if [ $# -ne 1 ]; then
    echo "Usage: makeStopBabyClassFiles.sh stop_baby_file_name"
    exit 1
fi

# file name is the only argument
file_name=$1
# /nfs-7/userdata/rwkelley/babies/stop/cms2V05-03-26_stoplooperV00-02-25/T2tt_mad/minibabies_V00-03-06/Skim_4jets_MET100_MT120/merged_T2tt_mStop-925to1000_mLSP-1_and_mLSP-25to900_1.root

# create the STOP_BABY.cc/h
dir=$CMSSW_BASE/src/StopAnalysis/CombinedExclusions
pushd $dir
echo "[makeStopBabyClassFiles.sh] calling"
EXE=$CMSSW_BASE/src/AnalysisTools/utils/makeTTreeClassFiles.py
cmd="python $EXE --file_name $file_name --obj_name stop_baby_obj --namespace stop --class_name STOP_BABY --tree_name \"t\" --no_trig"
echo $cmd
eval $cmd
# EXE=$CMSSW_BASE/src/AnalysisTools/utils/makeCMS2ClassFiles.C
# root_cmd="$EXE+(\"$file_name\", false, \"t\", \"\", \"STOP_BABY\", \"stop\", \"stop_baby_obj\")"
# echo $root_cmd
# root -b -l -q "$root_cmd" 

# move STOP_BABY.h
mv STOP_BABY.h $dir/interface/.

# move STOP_BABY.cc and change include path for STOP_BABY.h to conform with SCRAM convention
sed 's/\#include "STOP_BABY.h"/\#include "StopAnalysis\/CombinedExclusions\/interface\/STOP_BABY.h"/g' STOP_BABY.cc > $dir/src/STOP_BABY.cc
rm STOP_BABY.cc
 
# done
popd
echo "[makeStopBabyClassFiles.sh] finished"
