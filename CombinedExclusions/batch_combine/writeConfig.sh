#!/bin/bash

UNIVERSE="grid"
EXE="wrapper.sh"
INPUT="wrapper.sh, job_input/input.tgz, appendTimeStamp.sh"
SITE="UCSD"
PROXY="/tmp/x509up_u10194"

DIR=$PWD
SUBMITLOGDIR="${DIR}/submit_logs"
JOBLOGDIR="${DIR}/job_logs"
LOGDIR="${DIR}/"
LOG="${LOGDIR}/submit_logs/condor_`date "+%m_%d_%Y"`.log"
OUT="${LOGDIR}/job_logs/1e.\$(Cluster).\$(Process).out"
ERR="${LOGDIR}/job_logs/1e.\$(Cluster).\$(Process).err"


#
# prepare input sandbox
#
g++ sweepRoot.C -o sweepRoot `root-config --cflags --libs`
cd ${DIR}/job_input
rm input.*
mv ../sweepRoot .
tar -czf input.tgz --exclude='*CVS*' *
cd ${DIR}

#
# arguments to run the script
#
SAMPLE="$1"
CARDDIR="$2"
COPYDIRBASE="$3"
COPYDIR="/hadoop/cms/store/user/$USER/${COPYDIRBASE}"

#
# write configuration
#

echo "
UNIVERSE="vanilla"
EXE="wrapper.sh"
INPUT="wrapper.sh, job_input/input.tgz, appendTimeStamp.sh"
SITE="UCSD"
PROXY="/tmp/x509up_u$(id -u)"

DIR=$PWD
SUBMITLOGDIR="${DIR}/submit_logs"
JOBLOGDIR="${DIR}/job_logs"
LOGDIR="${DIR}/"
LOG="${LOGDIR}/submit_logs/condor_`date "+%m_%d_%Y"`.log"
OUT="${LOGDIR}/job_logs/1e.\$(Cluster).\$(Process).out"
ERR="${LOGDIR}/job_logs/1e.\$(Cluster).\$(Process).err"
" > condor_${COPYDIRBASE##*/}.cmd

    #
    # now set the rest of the arguments 
    # for each job
    # 

    for FILE in `ls ${CARDDIR}`; do
		CARD=${FILE}
		JOBID=`echo $(basename ${FILE}) | sed 's/\.txt//g'`
        echo "
executable=${EXE}
transfer_executable=True
arguments=\"${SAMPLE}/$(basename ${FILE}) ${JOBID} ${COPYDIR}\"
queue
" >> condor_${COPYDIRBASE##*/}.cmd
    done

echo "[writeConfig] wrote condor_${COPYDIRBASE##*/}.cmd" 
