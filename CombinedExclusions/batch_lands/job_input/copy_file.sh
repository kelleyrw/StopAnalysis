#!/bin/bash

cp -r $CMSSW_BASE/src/StopAnalysis/CombinedExclusions/cards/t2tt .
cp ~/code/LandS/03.06.07/test/lands.exe lands.exe
cp $CMSSW_BASE/src/StopAnalysis/CombinedExclusions/macros/fitRvsCLs.C .

tar -czf input.tgz  --exclude='*.git*' *
