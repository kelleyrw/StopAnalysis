#!/bin/bash

# inputs
# -------------------------- #
card="$1"
job_id="$2"
working_dir=$PWD

echo "[driver] List of args = $@"
for arg in "$@"; do
    echo $arg
done

echo "[driver] card    = ""${card}"
echo "[driver] job_id  = ""${job_id}"

# set local dir to library path
# -------------------------- #
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD

# setup HiggsCombine
git config --global user.email "kelleyrw@gmail.com"
git config --global user.name "kelleyrw"
pushd $CMSSW_BASE/src
git clone https://github.com/RazorCMS/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
pushd HiggsAnalysis/CombinedLimit
git pull origin master
git checkout onelepcomb_032614
mv $working_dir/SimpleCacheSentry.h.rwkfix interface/SimpleCacheSentry.h
popd
scramv1 b clean
scramv1 b -j20
popd

# compile sweepRoot.cc
g++ sweepRoot.cc -o sweepRoot `root-config --cflags --libs`

# run combine
function run_combine_asymptotic
{
    local card=$1
    local job_id=$2
    local output="combine_output_${job_id}.root"
    local seed=1234
    #local options="--method Asymptotic --seed $seed"
    local options="--method Asymptotic --minimizerTolerance 0.0001 --rRelAcc 0.0001 -v 2 --seed $seed"

    # run combine 

    # run combine for observed limit 
    cmd="combine --datacard $card --name $job_id $options"
    echo $cmd
    eval $cmd

    # move output
    cmd="hadd -f $output higgsCombine${job_id}.Asymptotic.mH120.${seed}.*"
    echo $cmd
    eval $cmd
}

function run_combine_hybridnew
{
    local card=$1
    local job_id=$2
    local output="combine_output_${job_id}.root"
    local seed=1234
    local options="--method HybridNew --frequentist --testStat LHC --hintMethod Asymptotic --seed $seed"

    # run combine 

    # run combine for observed limit 
    cmd="combine --datacard $card --name $job_id $options"
    echo $cmd
    eval $cmd

    # run combine for expected
    #0.5 gives you the median. use 0.16/0.84 to get the endpoints of 68% interval, 0.025/0.975 to get the 95% one)
    cmd="combine --datacard $card --name $job_id $options --expectedFromGrid 0.50000" # median
    echo $cmd
    eval $cmd
    cmd="combine --datacard $card --name $job_id $options --expectedFromGrid 0.84135" # median + 1 sigma
    echo $cmd
    eval $cmd
    cmd="combine --datacard $card --name $job_id $options --expectedFromGrid 0.15865" # median - 1 sigma
    echo $cmd
    eval $cmd
    cmd="combine --datacard $card --name $job_id $options --expectedFromGrid 0.97725" # median + 2 sigma
    echo $cmd
    eval $cmd
    cmd="combine --datacard $card --name $job_id $options --expectedFromGrid 0.02275" # median - 2 sigma
    echo $cmd
    eval $cmd

    # move output
    cmd="hadd -f $output higgsCombine${job_id}.HybridNew.mH120.${seed}.*"
    echo $cmd
    eval $cmd
}

# set the command
# -------------------------- #
cmd="run_combine_asymptotic ${card} ${job_id}"
#cmd="run_combine_hybridnew ${card} ${job_id}"

# run combine 
# -------------------------- #
echo [driver] command to run:
echo $cmd
eval $cmd
