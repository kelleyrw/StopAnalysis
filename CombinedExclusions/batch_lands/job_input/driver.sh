#!/bin/bash

# inputs
# -------------------------- #
card="$1"
job_id="$2"

echo "[driver] List of args = $@"
for arg in "$@"; do
    echo $arg
done

echo "[driver] card    = ""${card}"
echo "[driver] job_id  = ""${job_id}"

# set local dir to library path
# -------------------------- #
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD

# set the command
# -------------------------- #
cmd="./lands.exe -d ${card} -n ${job_id} -M Hybrid --freq --ExpectationHints Asymptotic --scanRs 1 --nToysForCLsb 10000 --nToysForCLb 5000 --seed 1234"

# run lands 
# -------------------------- #
echo [driver] command to run:
echo $cmd
eval $cmd

# run the limits
echo [driver] ROOT command to run:
cmd="root -b -q -l \"RunLimitsWrapper.C+ (\\\"${job_id}_m2lnQ.root\\\")\""
echo $cmd
eval $cmd
