#!/bin/bash

function run_combine
{
    local card=$1
    local output=$2
	local stem=`echo $(basename $output) | cut -c 7- | perl -pe 's/\..*$//;s{^.*/}{}'`
	local base=`basename $output`

    # run combine
	cmd="combine --method Asymptotic --datacard $card --seed 1234 --rMin 0.01 --rMax 2000 --name $stem"
    echo $cmd
    eval $cmd

	# move output
	local higgs_file="higgsCombine${stem}.Asymptotic.mH120.1234.root"
	cmd="mv $higgs_file $output"
    echo $cmd
    eval $cmd

	# remove junk
	rm roostats-*
}

mass_stop=650
mass_lsp=50
# method=1
# method=2
method=3

run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt1l.txt output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt1l.root >& logs/combine_m${method}a_${mass_stop}_${mass_lsp}_bdt1l.txt &
run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt1t.txt output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt1t.root >& logs/combine_m${method}a_${mass_stop}_${mass_lsp}_bdt1t.txt &
run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt2.txt  output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt2.root  >& logs/combine_m${method}a_${mass_stop}_${mass_lsp}_bdt2.txt  &
run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt3.txt  output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt3.root  >& logs/combine_m${method}a_${mass_stop}_${mass_lsp}_bdt3.txt  &
run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt4.txt  output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt4.root  >& logs/combine_m${method}a_${mass_stop}_${mass_lsp}_bdt4.txt  &
run_combine cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt5.txt  output/combine/t2tt/limit_method${method}_${mass_stop}_${mass_lsp}_bdt5.root  >& logs/combine_m${method}a_${mass_stop}_${mass_lsp}_bdt5.txt  &
