#!/bin/bash

OUTPUT_PATH=limits/combine
CARD_PATH=$CMSSW_BASE/src/StopAnalysis/CombinedExclusions/batch_combine/job_input

# SUSY scans
./writeConfig.sh t2tt $CARD_PATH/t2tt $OUTPUT_PATH/t2tt                        
