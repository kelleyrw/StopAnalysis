#!/bin/bash

#UNIVERSE="grid"
UNIVERSE="vanilla"
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
# g++ sweepRoot.C -o sweepRoot `root-config --cflags --libs`
cd ${DIR}/job_input
rm input.*
# mv ../sweepRoot .
tar -czf input.tgz --exclude='*CVS*' *
cd ${DIR}

#
# arguments to run the script
#
SAMPLE="$1"
CARDDIR="$2"
COPYDIRBASE="$3"
METHOD=$4
COPYDIR="/hadoop/cms/store/user/$USER/${COPYDIRBASE}"
OUTPUT=condor_${COPYDIRBASE##*/}_method${METHOD}.cmd

#
# write configuration
#

# Grid_Resource=gt2 osg-gw-6.t2.ucsd.edu:2119/jobmanager-condor                  
echo "universe=${UNIVERSE}
when_to_transfer_output = ON_EXIT
#the actual executable to run is not transfered by its name.
#In fact, some sites may do weird things like renaming it and such.
transfer_input_files=${INPUT}
+DESIRED_Sites=\"${SITE}\"
+Owner = undefined
log=${LOG}
output=${OUT}
error =${ERR}
notification=Never
x509userproxy=${PROXY}
" > ${OUTPUT}
    #
    # now set the rest of the arguments 
    # for each job
    # 

    for FILE in `ls ${CARDDIR}`; do
        if [[ $FILE == *"root"* ]]; then 
            continue;
        fi
		CARD=${FILE}
        echo "
executable=${EXE}
transfer_executable=True
arguments=\"${SAMPLE}/$(basename ${FILE}) ${METHOD} ${COPYDIR}\"
queue
" >> ${OUTPUT}
    done

echo "[writeConfig] wrote ${OUTPUT}" 
