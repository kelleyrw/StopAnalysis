#!/bin/bash

OUTPUT_PATH=limits/lep1_razor_combine/hybrid_v2
METHOD=3 # 1: asymptotic, 2: hybrid new, 3: hybrid new with pre-generated grid
# OUTPUT_PATH=limits/lep1_razor_combine/asymptotic_new
# METHOD=1 # 1: asymptotic, 2: hybrid new, 3: hybrid new with pre-generated grid
CARD_PATH=$CMSSW_BASE/src/StopAnalysis/CombinedExclusions/batch_full_combine/job_input

# scans
./writeConfig.sh t2tt $CARD_PATH/t2tt $OUTPUT_PATH/t2tt $METHOD
