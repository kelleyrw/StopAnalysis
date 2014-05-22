#!/bin/bash

# remove old cards
rm -r t2tt

# copy relevant files
cp -r $CMSSW_BASE/src/StopAnalysis/CombinedExclusions/scripts/stop_produce_limit.py . 
# cp -r $CMSSW_BASE/src/StopAnalysis/CombinedExclusions/cards/t2tt/combined t2tt 
cp -r $CMSSW_BASE/src/StopAnalysis/CombinedExclusions/cards/t2tt/combined_22May2014 t2tt 
cp -r $CMSSW_BASE/src/StopAnalysis/CombinedExclusions/batch_combine/sweepRoot.cc .

# tar up inputs
tar -czf input.tgz  --exclude='*.git*' *
