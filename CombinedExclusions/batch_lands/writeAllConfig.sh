#!/bin/bash

OUTPUT_PATH=limits/lands
CARD_PATH=$CMSSW_BASE/src/StopAnalysis/CombinedExclusions/batch_lands/job_input

# SUSY scans
# ./writeConfig.sh t2tt $CARD_PATH/t2tt $OUTPUT_PATH/t2tt                        
./writeConfig.sh t2tt $CARD_PATH/t2tt $OUTPUT_PATH/t2tt_v2
