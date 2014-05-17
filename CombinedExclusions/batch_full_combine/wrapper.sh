#!/bin/bash

chmod +x appendTimeStamp.sh

# args

CARD="$1"
METHOD="$2"
COPYDIR="$3"

echo "[wrapper] List of args = $@" | ./appendTimeStamp.sh
for arg in "$@"; do
	echo "[wrapper] $arg"
done

echo "[wrapper] CARD    = ${CARD}"    | ./appendTimeStamp.sh
echo "[wrapper] METHOD  = ${METHOD}"  | ./appendTimeStamp.sh
echo "[wrapper] COPYDIR = ${COPYDIR}" | ./appendTimeStamp.sh
echo


# set up environment


echo
echo "[wrapper] setting env" | ./appendTimeStamp.sh
ls /code/osgcode/cmssoft/cms/cmsset_default.sh | ./appendTimeStamp.sh
if [ $? != 0 ]; then
   echo /code/osgcode/cmssoft/cms/cmsset_default.sh is not found  | ./appendTimeStamp.sh
fi
source /code/osgcode/cmssoft/cms/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc472
CMSSWRelease="CMSSW_6_2_5"
scram list CMSSW 
if [ $? != 0 ]; then
   echo "ERROR: Failed to check out CMSSW release $CMSSWRelease. Exiting job without running."
   scram list CMSSW 
   scram list CMSSW | ./appendTimeStamp.sh
   sleep 5
   exit 1
fi
scram p CMSSW $CMSSWRelease
cd $CMSSWRelease
eval `scramv1 ru -sh`
cd -
export LD_LIBRARY_PATH=$PWD:$ROOTSYS/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH
echo

echo
echo "[wrapper] envirment variables" | ./appendTimeStamp.sh
/bin/env
echo


# print out which worker node 

echo
echo "[wrapper] worker node is" `/bin/hostname` | ./appendTimeStamp.sh
echo "[wrapper] running as user " `/usr/bin/whoami` | ./appendTimeStamp.sh
echo


# untar input sandbox

echo
echo "[wrapper] extracting input sandbox" | ./appendTimeStamp.sh
tar -zxvf input.tgz
echo


# run it


ls -l ${FILE}
if [ $? -ne 0 ]; then
   echo ${FILE} "[wrapper] is missing or is inaccessable" | ./appendTimeStamp.sh
   exit 99
fi


# set a job exit code for record keeping

JOB_EXIT_CODE=-0


# check directory permissions

echo
echo "[wrapper} permission of CWD: " `ls -ld $PWD` | ./appendTimeStamp.sh
echo


# begin time stamp

echo
echo "[wrapper] starting job: " | ./appendTimeStamp.sh
echo

echo -e "
#!/bin/bash

# run the driver script
./driver.sh ${CARD} ${METHOD}

# test the output
JOB_EXIT_CODE=`echo $?`
if [[ $JOB_EXIT_CODE -ne 0 ]] ; then
   echo
   echo "[runme.sh] JOB_EXIT_CODE = $JOB_EXIT_CODE" 
   echo
fi
" > runme.sh

echo
if [ ! -f runme.sh ]; then
   echo "[wrapper] runme.sh doesn't exist." | ./appendTimeStamp.sh
   JOB_EXIT_CODE=99
else
   echo "runme.sh is:" | ./appendTimeStamp.sh
   echo
   cat runme.sh
fi
echo

if [[ $JOB_EXIT_CODE -ne 0 ]] ; then
   echo
   echo "[wrapper] JOB_EXIT_CODE = $JOB_EXIT_CODE" | ./appendTimeStamp.sh
   echo
   exit $JOB_EXIT_CODE
fi

source runme.sh


# record runme exit code

JOB_EXIT_CODE=`echo $?`
if [[ $JOB_EXIT_CODE -ne 0 ]] ; then
   echo
   echo "[wrapper] JOB_EXIT_CODE = $JOB_EXIT_CODE" | ./appendTimeStamp.sh
   echo
fi


# end time stamp

echo
echo "[wrapper] ending job: " | ./appendTimeStamp.sh
echo


# do something with output


ls -la
echo
echo "[wrapper] checking certificate" | ./appendTimeStamp.sh
voms-proxy-info --all
echo

echo
echo "[wrapper] envirment variables" | ./appendTimeStamp.sh
/bin/env
echo


# print out which worker node 

echo
echo "[wrapper] worker node is" `/bin/hostname` | ./appendTimeStamp.sh
echo "[wrapper] running as user " `/usr/bin/whoami` | ./appendTimeStamp.sh
echo


# only copy files that pass sweepRoot

echo
echo "[wrapper] copying file" | ./appendTimeStamp.sh
JOBID=`echo $(basename ${CARD}) | sed 's/\.txt//g'`
OUTPUT=combine_output_${JOBID}.root
ls $OUTPUT | ./appendTimeStamp.sh
JOB_EXIT_CODE=`echo $?`
if [[ $? -ne 0 ]] ; then
   echo
   echo "[wrapper] $OUTPUT file not found!  Exiting." | ./appendTimeStamp.sh
   echo
fi
cmd="./sweepRoot -o limit $OUTPUT"
echo OUTPUT = $OUTPUT
ls -l $OUTPUT
eval $cmd
echo "[wrapper] $cmd" | ./appendTimeStamp.sh
if [ $(eval $cmd >&1 | grep SUMMARY | awk '{print $2}') == 0 ];
then 
   echo "[wrapper] preparing to transfer $OUTPUT to ${COPYDIR}/${OUTPUT}..." | ./appendTimeStamp.sh
   cmd="lcg-cp -b -D srmv2 --vo cms --connect-timeout 2400 --verbose file://`pwd`/${OUTPUT} srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/${OUTPUT}" 
   echo $cmd | ./appendTimeStamp.sh
   eval $cmd | ./appendTimeStamp.sh
else
   echo "[wrapper] $OUTPUT is considered bad by sweepRoot..." | ./appendTimeStamp.sh
fi
echo

# clean up

echo
echo "[wrapper] cleaning up" | ./appendTimeStamp.sh
find . -not -name "*stderr" -not -name "*stdout" -exec rm -rf {} \;            
echo "[wrapper] cleaned up"
ls
