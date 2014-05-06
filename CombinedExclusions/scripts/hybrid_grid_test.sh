#!/bin/bash

seed=1234
options="--method HybridNew --frequentist --testStat LHC --hintMethod Asymptotic --seed $seed --clsAcc 0.1"

function run_cmd
{
    local cmd=$1
    echo $cmd
    eval $cmd
}

function create_grid
{
    local card=$1
    local rvalue=$2
    local name="_grid_${card}_r$(echo $rvalue | sed -e "s/\./p/")"
    run_cmd "combine ${card}.txt --name $name $options --singlePoint $rvalue --saveToys --saveHybridResult"
}

function run_combine_grid
{
    local card=${1}.txt
    local name="_${1}_grid"
    local grid=$2
    run_cmd "combine ${card} --name ${name} --method HybridNew --frequentist --seed $seed --grid=${grid}"
    run_cmd "combine ${card} --name ${name} --method HybridNew --frequentist --seed $seed --grid=${grid} --expectedFromGrid 0.5"
    run_cmd "combine ${card} --name ${name} --method HybridNew --frequentist --seed $seed --grid=${grid} --expectedFromGrid 0.16"
    run_cmd "combine ${card} --name ${name} --method HybridNew --frequentist --seed $seed --grid=${grid} --expectedFromGrid 0.84"
    run_cmd "combine ${card} --name ${name} --method HybridNew --frequentist --seed $seed --grid=${grid} --expectedFromGrid 0.025"
    run_cmd "combine ${card} --name ${name} --method HybridNew --frequentist --seed $seed --grid=${grid} --expectedFromGrid 0.975"
    run_cmd "hadd -f higgsCombine_${card}.HybridNew.grid.root higgsCombine${name}.HybridNew.mH120.*"
}

function run_combine_nogrid
{
    local card=${1}.txt
    local name="_${1}_nogrid"
    run_cmd "combine ${card} --name $name $options"
    run_cmd "combine ${card} --name $name $options --expectedFromGrid 0.5"
    run_cmd "combine ${card} --name $name $options --expectedFromGrid 0.16"
    run_cmd "combine ${card} --name $name $options --expectedFromGrid 0.84"
    run_cmd "combine ${card} --name $name $options --expectedFromGrid 0.025"
    run_cmd "combine ${card} --name $name $options --expectedFromGrid 0.975"
    run_cmd "hadd -f higgsCombine_${card}.HybridNew.nogrid.root higgsCombine${name}.HybridNew.mH120.*"
}

function create_limits
{
    # create the grid
    local card=$1
    local rmin=$2
    local rmax=$3
    local n=$4
    local step=`echo "scale=4; ($rmax-$rmin)/$n" | bc`
    for r in `seq $rmin $step $rmax`
    do
        rvalue=`printf "%1.4f\n" $r`
        create_grid $card $rvalue
    done

    local name="higgsCombine_grid_${card}"
    local grid="${name}_n${n}.root"
    run_cmd "hadd -f ${grid} ${name}_r*.root" 

    # limit with grid
    run_combine_grid   $card $grid

    # limit without grid
    run_combine_nogrid $card $grid
}

create_limits t2tt_200_100_bdt5 0.25 2.25 100 
