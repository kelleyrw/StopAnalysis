#!/bin/bash

input_path="$CMSSW_BASE/src/StopAnalysis/CombinedExclusions/cards/from_javier_14May2014/cards/T2tt"
output_path="$CMSSW_BASE/src/StopAnalysis/CombinedExclusions/cards/t2tt/razor_22May2014"

# copy cards to correct place
mkdir -p $output_path
cp $input_path/razor_combine_MultiJet_T2tt_MG_* $output_path/.
cp $input_path/razor_combine_Jet2b_T2tt_MG_*    $output_path/.

# move to output_path
pushd $output_path

for multi_card in $(ls razor_combine_MultiJet_T2tt_MG_*.txt);
do
    # other cards
    jet2b_card=$(echo $multi_card | sed 's/MultiJet/Jet2b/g')
    had_card=$(echo $multi_card | sed 's/MultiJet/Had/g')

    # command
    cmd="combineCards.py MultiJet=$multi_card Jet2b=$jet2b_card > $had_card"
    echo $cmd
    eval $cmd
done

popd
