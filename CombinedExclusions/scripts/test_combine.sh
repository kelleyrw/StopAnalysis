#!/bin/bash

mass_stop=${1:-300}
mass_lsp=${2:-50}
method=${3:-3}
echo "[test_combine]: m_stop $mass_stop, m_lsp $mass_lsp, method $method"

function run_combine
{
    local card=$1
    local output=$2
	local stem=`echo $(basename $output) | cut -c 7- | perl -pe 's/\..*$//;s{^.*/}{}'`
	local base=`basename $output`
	local seed=1234
# 	local options="--method HybridNew --frequentist --testStat LHC --hintMethod ProfileLikelihood --seed $seed"
	local options="--method HybridNew --frequentist --testStat LHC --hintMethod Asymptotic --seed $seed --rMin 10 --rMax 1000000"

    # run combine 

    # run combine for observed limit 
	cmd="combine --datacard $card --name $stem $options"
    echo $cmd
    eval $cmd

    # run combine for expected
	#0.5 gives you the median. use 0.16/0.84 to get the endpoints of 68% interval, 0.025/0.975 to get the 95% one)
	cmd="combine --datacard $card --name $stem $options --expectedFromGrid 0.50000" # median
    echo $cmd
    eval $cmd
	cmd="combine --datacard $card --name $stem $options --expectedFromGrid 0.84135" # median + 1 sigma
    echo $cmd
#     eval $cmd
	cmd="combine --datacard $card --name $stem $options --expectedFromGrid 0.15865" # median - 1 sigma
    echo $cmd
#     eval $cmd
	cmd="combine --datacard $card --name $stem $options --expectedFromGrid 0.97725" # median + 2 sigma
    echo $cmd
#     eval $cmd
	cmd="combine --datacard $card --name $stem $options --expectedFromGrid 0.02275" # median - 2 sigma
    echo $cmd
#     eval $cmd


	# move output
	mkdir -p `dirname $output`
	cmd="hadd -f $output higgsCombine${stem}.HybridNew.mH120.${seed}.*"
    echo $cmd
    eval $cmd

	# remove junk
#     rm roostats-* higgsCombine*.root                                           
# 	rm *higgsCombine${stem}.HybridNew.mH120.${seed}.*
# 	rm roostats-*
}

run_combine cards/t2tt/t2tt_${mass_stop}_${mass_lsp}_bdt4.txt output/combine/test/limit_method${method}_${mass_stop}_${mass_lsp}_bdt4.root
# run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt1l.txt output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt1l.root >& logs/combine_m${method}_${mass_stop}_${mass_lsp}_bdt1l.txt &
# run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt1t.txt output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt1t.root >& logs/combine_m${method}_${mass_stop}_${mass_lsp}_bdt1t.txt &
# run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt2.txt  output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt2.root  >& logs/combine_m${method}_${mass_stop}_${mass_lsp}_bdt2.txt  &
# run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt3.txt  output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt3.root  >& logs/combine_m${method}_${mass_stop}_${mass_lsp}_bdt3.txt  &
# run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt4.txt  output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt4.root  >& logs/combine_m${method}_${mass_stop}_${mass_lsp}_bdt4.txt  &
# run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt5.txt  output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt5.root  >& logs/combine_m${method}_${mass_stop}_${mass_lsp}_bdt5.txt  &
