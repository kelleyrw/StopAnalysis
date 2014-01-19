#!/bin/bash

cp -r $CMSSW_BASE/src/StopAnalysis/CombinedExclusions/cards/t2tt .
cp -r $CMSSW_BASE/src/StopAnalysis/CombinedExclusions/batch_combine/sweepRoot.cc .
cp -r $CMSSW_BASE/bin/$SCRAM_ARCH/combine combine.exe 

tar -czf input.tgz  --exclude='*.git*' *
