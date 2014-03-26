#!/bin/bash

rm -r t2tt
cp -r $CMSSW_BASE/src/StopAnalysis/CombinedExclusions/cards/t2tt/combined t2tt 
cp -r $CMSSW_BASE/src/StopAnalysis/CombinedExclusions/batch_combine/sweepRoot.cc .

tar -czf input.tgz  --exclude='*.git*' *
