#!/bin/bash

OUTPUT_PATH=limits/lep1_razor_combine/test_method1
CARD_PATH=$CMSSW_BASE/src/StopAnalysis/CombinedExclusions/batch_full_combine/job_input
METHOD=3 # 1: asymptotic, 2: hybrid new, 3: hybrid new with pre-generated grid

# scans
./writeConfig.sh t2tt $CARD_PATH/t2tt $OUTPUT_PATH/t2tt $METHOD
