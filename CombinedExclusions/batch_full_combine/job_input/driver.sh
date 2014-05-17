#!/bin/bash

# inputs
# -------------------------- #
card="$1"
method="$2"
working_dir=$PWD

echo "[driver] List of args = $@"
for arg in "$@"; do
    echo $arg
done

echo "[driver] card   = ${card}"
echo "[driver] method = ${method}"

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
cp $working_dir/SimpleCacheSentry.h.rwkfix interface/SimpleCacheSentry.h
popd
scramv1 b clean
scramv1 b -j20
popd

# compile sweepRoot.cc
g++ sweepRoot.cc -o sweepRoot `root-config --cflags --libs`

# set the command
# -------------------------- #
cmd="python stop_produce_limit.py --card ${card} --method ${method}"

# run combine 
# -------------------------- #
echo [driver] command to run:
echo $cmd
eval $cmd
