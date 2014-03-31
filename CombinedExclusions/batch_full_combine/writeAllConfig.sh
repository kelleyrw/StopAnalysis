#!/bin/bash

#OUTPUT_PATH=limits/lep1_razor_combine
OUTPUT_PATH=limits/lep1_razor_combine_hybridnew
CARD_PATH=$CMSSW_BASE/src/StopAnalysis/CombinedExclusions/batch_full_combine/job_input

# SUSY scans
./writeConfig.sh t2tt $CARD_PATH/t2tt $OUTPUT_PATH/t2tt                        
