#!/bin/bash

function run_lands
{
    local card=$1
    local output=$2

    # run lands
#     cmd="lands.exe -d $card -n $output -M Hybrid --freq --ExpectationHints Asymptotic --scanRs 1 --nToysForCLsb 3000  --nToysForCLb 1500 --seed 1234"
    cmd="lands.exe -d $card -n $output -M Hybrid --freq --ExpectationHints Asymptotic --scanRs 1 --nToysForCLsb 10000 --nToysForCLb 5000 --seed 1234"
#     cmd="lands.exe -d $card -n $output -M Hybrid --freq --ExpectationHints Asymptotic --scanRs 1 --nToysForCLsb 10000 --nToysForCLb 5000 --seed 1234 -D asimov_b"
    echo $cmd
    eval $cmd

    # run the limits
    cmd="root -b -q -l \"macros/RunLimitsWrapper.C+ (\\\"${output}_m2lnQ.root\\\")\""
    echo $cmd
    eval $cmd
}

# run_lands cards/lands/t2tt/ben_300_50_sr1.txt                   output/lands/t2tt/limit_300_50_sr1_ben
# run_lands cards/lands/t2tt/card_300_50_sr1.txt                  output/lands/t2tt/limit_300_50_sr1_signal_factored
# run_lands cards/lands/t2tt/card_300_50_sr1_fully_factorized.txt output/lands/t2tt/limit_300_50_sr1_fully_factored
# run_lands cards/lands/t2tt/card_300_50_sr1_simple.txt           output/lands/t2tt/limit_300_50_sr1_simple

# run_lands cards/lands/t2tt/card_300_50_sr1.txt output/lands/t2tt/limit_300_50_sr1_signal_factored
# run_lands cards/lands/t2tt/card_300_50_sr2.txt output/lands/t2tt/limit_300_50_sr2_signal_factored
# run_lands cards/lands/t2tt/card_300_50_sr3.txt output/lands/t2tt/limit_300_50_sr3_signal_factored
# run_lands cards/lands/t2tt/card_300_50_sr4.txt output/lands/t2tt/limit_300_50_sr4_signal_factored
# run_lands cards/lands/t2tt/card_300_50_sr5.txt output/lands/t2tt/limit_300_50_sr5_signal_factored
# run_lands cards/lands/t2tt/card_300_50_sr6.txt output/lands/t2tt/limit_300_50_sr6_signal_factored

run_lands cards/lands/t2tt/card_method3_300_50_bdt1l.txt output/lands/t2tt/limit_method3_apriori_300_50_bdt1l_signal_factored
run_lands cards/lands/t2tt/card_method3_300_50_bdt1t.txt output/lands/t2tt/limit_method3_apriori_300_50_bdt1t_signal_factored
run_lands cards/lands/t2tt/card_method3_300_50_bdt2.txt  output/lands/t2tt/limit_method3_apriori_300_50_bdt2_signal_factored
run_lands cards/lands/t2tt/card_method3_300_50_bdt3.txt  output/lands/t2tt/limit_method3_apriori_300_50_bdt3_signal_factored
run_lands cards/lands/t2tt/card_method3_300_50_bdt4.txt  output/lands/t2tt/limit_method3_apriori_300_50_bdt4_signal_factored
run_lands cards/lands/t2tt/card_method3_300_50_bdt5.txt  output/lands/t2tt/limit_method3_apriori_300_50_bdt5_signal_factored

a posteriori
run_lands cards/lands/t2tt/card_method3_300_50_bdt1l.txt output/lands/t2tt/limit_method3_aposteriori_300_50_bdt1l_signal_factored
run_lands cards/lands/t2tt/card_method3_300_50_bdt1t.txt output/lands/t2tt/limit_method3_aposteriori_300_50_bdt1t_signal_factored
run_lands cards/lands/t2tt/card_method3_300_50_bdt2.txt  output/lands/t2tt/limit_method3_aposteriori_300_50_bdt2_signal_factored
run_lands cards/lands/t2tt/card_method3_300_50_bdt3.txt  output/lands/t2tt/limit_method3_aposteriori_300_50_bdt3_signal_factored
run_lands cards/lands/t2tt/card_method3_300_50_bdt4.txt  output/lands/t2tt/limit_method3_aposteriori_300_50_bdt4_signal_factored
run_lands cards/lands/t2tt/card_method3_300_50_bdt5.txt  output/lands/t2tt/limit_method3_aposteriori_300_50_bdt5_signal_factored

# run_lands cards/lands/t2tt/card_600_0_sr1.txt output/lands/t2tt/limit_600_0_sr1_signal_factored
# run_lands cards/lands/t2tt/card_600_0_sr2.txt output/lands/t2tt/limit_600_0_sr2_signal_factored
# run_lands cards/lands/t2tt/card_600_0_sr3.txt output/lands/t2tt/limit_600_0_sr3_signal_factored
# run_lands cards/lands/t2tt/card_600_0_sr4.txt output/lands/t2tt/limit_600_0_sr4_signal_factored
# run_lands cards/lands/t2tt/card_600_0_sr5.txt output/lands/t2tt/limit_600_0_sr5_signal_factored
# run_lands cards/lands/t2tt/card_600_0_sr6.txt output/lands/t2tt/limit_600_0_sr6_signal_factored
