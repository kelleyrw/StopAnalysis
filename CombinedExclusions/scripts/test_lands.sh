#!/bin/bash

function run_lands_aposteriori
{
    local card=$1
    local output=$2

    # run lands
    cmd="lands.exe -d $card -n $output -M Hybrid --freq --ExpectationHints Asymptotic --scanRs 1 --nToysForCLsb 10000 --nToysForCLb 5000 --seed 1234"
    echo $cmd
#     eval $cmd

    # run the limits
    cmd="root -b -q -l \"macros/RunLimitsWrapper.C+ (\\\"${output}_m2lnQ.root\\\")\""
    echo $cmd
    eval $cmd
}

function run_lands_apriori
{
    local card=$1
    local output=$2

    # run lands
    cmd="lands.exe -d $card -n $output -M Hybrid --freq --ExpectationHints Asymptotic --scanRs 1 --nToysForCLsb 10000 --nToysForCLb 5000 --seed 1234 -D asimov_b"
    echo $cmd
    eval $cmd

    # run the limits
    cmd="root -b -q -l \"macros/RunLimitsWrapper.C+ (\\\"${output}_m2lnQ.root\\\")\""
    echo $cmd
    eval $cmd
}

mass_stop=250
mass_lsp=150
# method=1
# method=2
method=3

run_lands_aposteriori cards/t2tt/t2tt_${mass_stop}_${mass_lsp}_bdt4.txt  output/lands/test/limit_method${method}_${mass_stop}_${mass_lsp}_bdt4
# run_lands_aposteriori cards/t2tt/t2tt_${mass_stop}_${mass_lsp}_bdt1l.txt output/lands/test/limit_method${method}_${mass_stop}_${mass_lsp}_bdt1l >& logs/m${method}_${mass_stop}_${mass_lsp}_bdt1l.txt &
# run_lands_aposteriori cards/t2tt/t2tt_${mass_stop}_${mass_lsp}_bdt1t.txt output/lands/test/limit_method${method}_${mass_stop}_${mass_lsp}_bdt1t >& logs/m${method}_${mass_stop}_${mass_lsp}_bdt1t.txt &
# run_lands_aposteriori cards/t2tt/t2tt_${mass_stop}_${mass_lsp}_bdt2.txt  output/lands/test/limit_method${method}_${mass_stop}_${mass_lsp}_bdt2  >& logs/m${method}_${mass_stop}_${mass_lsp}_bdt2.txt  &
# run_lands_aposteriori cards/t2tt/t2tt_${mass_stop}_${mass_lsp}_bdt3.txt  output/lands/test/limit_method${method}_${mass_stop}_${mass_lsp}_bdt3  >& logs/m${method}_${mass_stop}_${mass_lsp}_bdt3.txt  &
# run_lands_aposteriori cards/t2tt/t2tt_${mass_stop}_${mass_lsp}_bdt4.txt  output/lands/test/limit_method${method}_${mass_stop}_${mass_lsp}_bdt4  >& logs/m${method}_${mass_stop}_${mass_lsp}_bdt4.txt  &
# run_lands_aposteriori cards/t2tt/t2tt_${mass_stop}_${mass_lsp}_bdt5.txt  output/lands/test/limit_method${method}_${mass_stop}_${mass_lsp}_bdt5  >& logs/m${method}_${mass_stop}_${mass_lsp}_bdt5.txt  &

# run_lands_aposteriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt1l.txt output/lands/t2tt/limit_method${method}_aposteriori_${mass_stop}_${mass_lsp}_bdt1l >& logs/m${method}a_${mass_stop}_${mass_lsp}_bdt1l.txt &
# run_lands_aposteriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt1t.txt output/lands/t2tt/limit_method${method}_aposteriori_${mass_stop}_${mass_lsp}_bdt1t >& logs/m${method}a_${mass_stop}_${mass_lsp}_bdt1t.txt &
# run_lands_aposteriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt2.txt  output/lands/t2tt/limit_method${method}_aposteriori_${mass_stop}_${mass_lsp}_bdt2  >& logs/m${method}a_${mass_stop}_${mass_lsp}_bdt2.txt  &
# run_lands_aposteriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt3.txt  output/lands/t2tt/limit_method${method}_aposteriori_${mass_stop}_${mass_lsp}_bdt3  >& logs/m${method}a_${mass_stop}_${mass_lsp}_bdt3.txt  &
# run_lands_aposteriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt4.txt  output/lands/t2tt/limit_method${method}_aposteriori_${mass_stop}_${mass_lsp}_bdt4  >& logs/m${method}a_${mass_stop}_${mass_lsp}_bdt4.txt  &
# run_lands_aposteriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt5.txt  output/lands/t2tt/limit_method${method}_aposteriori_${mass_stop}_${mass_lsp}_bdt5  >& logs/m${method}a_${mass_stop}_${mass_lsp}_bdt5.txt  &
# 
# run_lands_apriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt1l.txt output/lands/t2tt/limit_method${method}_apriori_${mass_stop}_${mass_lsp}_bdt1l >& logs/m${method}b_${mass_stop}_${mass_lsp}_bdt1l.txt &
# run_lands_apriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt1t.txt output/lands/t2tt/limit_method${method}_apriori_${mass_stop}_${mass_lsp}_bdt1t >& logs/m${method}b_${mass_stop}_${mass_lsp}_bdt1t.txt &
# run_lands_apriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt2.txt  output/lands/t2tt/limit_method${method}_apriori_${mass_stop}_${mass_lsp}_bdt2  >& logs/m${method}b_${mass_stop}_${mass_lsp}_bdt2.txt  &
# run_lands_apriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt3.txt  output/lands/t2tt/limit_method${method}_apriori_${mass_stop}_${mass_lsp}_bdt3  >& logs/m${method}b_${mass_stop}_${mass_lsp}_bdt3.txt  &
# run_lands_apriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt4.txt  output/lands/t2tt/limit_method${method}_apriori_${mass_stop}_${mass_lsp}_bdt4  >& logs/m${method}b_${mass_stop}_${mass_lsp}_bdt4.txt  &
# run_lands_apriori cards/lands/t2tt/card_method${method}_${mass_stop}_${mass_lsp}_bdt5.txt  output/lands/t2tt/limit_method${method}_apriori_${mass_stop}_${mass_lsp}_bdt5  >& logs/m${method}b_${mass_stop}_${mass_lsp}_bdt5.txt  &
# 
