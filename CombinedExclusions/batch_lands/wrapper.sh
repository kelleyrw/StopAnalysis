#!/bin/bash

chmod +x appendTimeStamp.sh

#
# args
#

CARD="$1"
JOBID="$2"
COPYDIR="$3"

echo "[wrapper] List of args = $@" | ./appendTimeStamp.sh
for arg in "$@"; do
	echo "[wrapper] $arg"
done

echo "[wrapper] CARD    =" "${CARD}"    | ./appendTimeStamp.sh
echo "[wrapper] JOBID   =" "${JOBID}"   | ./appendTimeStamp.sh
echo "[wrapper] COPYDIR =" "${COPYDIR}" | ./appendTimeStamp.sh
echo

#
# set up environment
#

echo
echo "[wrapper] setting env" | ./appendTimeStamp.sh
source /code/osgcode/cmssoft/cms/cmsset_default.sh
# export SCRAM_ARCH=slc5_amd64_gcc472
# CMSSWRelease="CMSSW_6_1_2"
# export SCRAM_ARCH=slc5_amd64_gcc462
# CMSSWRelease="CMSSW_5_3_2_patch4"
export SCRAM_ARCH=slc6_amd64_gcc472
CMSSWRelease="CMSSW_6_2_5"
if [ $? != 0 ]; then
        echo "ERROR: Failed to check out CMSSW release $CMSSWRelease. Exiting job without running."
                scram list
                sleep 10
                exit 1
fi
scram p CMSSW $CMSSWRelease
cd $CMSSWRelease
eval `scramv1 ru -sh`
cd -
#source /code/osgcode/fgolf/5.30-patches/bin/thisroot.sh
#source /code/osgcode/cmssoft/cms/slc5_amd64_gcc462/lcg/root/5.32.00-cms9/bin/thisroot.sh
# source /code/osgcode/imacneill/root/05.34.07/bin/thisroot.sh
export LD_LIBRARY_PATH=$PWD:$ROOTSYS/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH
echo

echo
echo "[wrapper] envirment variables" | ./appendTimeStamp.sh
/bin/env
echo

#
# print out which worker node 
#
echo
echo "[wrapper] worker node is" `/bin/hostname` | ./appendTimeStamp.sh
echo "[wrapper] running as user " `/usr/bin/whoami` | ./appendTimeStamp.sh
echo

#
# untar input sandbox
#
echo
echo "[wrapper] extracting input sandbox" | ./appendTimeStamp.sh
tar -zxvf input.tgz
echo

#
# run it
#

ls -l ${FILE}
if [ $? -ne 0 ]; then
    echo ${FILE} "[wrapper] is missing or is inaccessable" | ./appendTimeStamp.sh
    exit 99
fi

#
# set a job exit code for record keeping
#
JOB_EXIT_CODE=-0

#
# check directory permissions
#
echo
echo "[wrapper} permission of CWD: " `ls -ld $PWD` | ./appendTimeStamp.sh
echo

#
# begin time stamp
#
echo
echo "[wrapper] starting job: " | ./appendTimeStamp.sh
echo

echo -e "
#!/bin/bash

# run the driver script
./driver.sh ${CARD} ${JOBID}

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

#
# record runme exit code
#
JOB_EXIT_CODE=`echo $?`
if [[ $JOB_EXIT_CODE -ne 0 ]] ; then
    echo
    echo "[wrapper] JOB_EXIT_CODE = $JOB_EXIT_CODE" | ./appendTimeStamp.sh
    echo
fi

#
# end time stamp
#
echo
echo "[wrapper] ending job: " | ./appendTimeStamp.sh
echo

#
# do something with output
#

ls -la
echo
echo "[wrapper] checking certificate" | ./appendTimeStamp.sh
voms-proxy-info --all
echo

#
# only copy files that pass sweepRoot
#
echo
echo "[wrapper] copying file" | ./appendTimeStamp.sh
OUTPUT=${JOBID}_m2lnQ.root
ls $OUTPUT | ./appendTimeStamp.sh
JOB_EXIT_CODE=`echo $?`
if [[ $? -ne 0 ]] ; then
    echo
    echo "[wrapper] *m2lnQ.root file not found!  Exiting." | ./appendTimeStamp.sh
    echo
fi
./sweepRoot $OUTPUT
echo OUTPUT = $OUTPUT
ls -l $OUTPUT
#if [ $(du -b $OUTPUT | cut -f 1) -le 23136 ];
echo ./sweepRoot $OUTPUT
if [ $(./sweepRoot $OUTPUT 2>&1 | grep SUMMARY | awk '{print $2}') == 0 ];
then 
    echo "[wrapper] preparing to transfer $OUTPUT to ${COPYDIR}/${OUTPUT}..." | ./appendTimeStamp.sh
    echo lcg-cp -b -D srmv2 --vo cms -t 2400 --verbose file:`pwd`/${OUTPUT} srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/${OUTPUT}             | ./appendTimeStamp.sh
    echo lcg-cp -b -D srmv2 --vo cms -t 2400 --verbose file:`pwd`/bands_${OUTPUT} srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/bands_${OUTPUT} | ./appendTimeStamp.sh
    lcg-cp -b -D srmv2 --vo cms -t 2400 --verbose file:`pwd`/${OUTPUT} srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/${OUTPUT}
    lcg-cp -b -D srmv2 --vo cms -t 2400 --verbose file:`pwd`/bands_${OUTPUT} srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/bands_${OUTPUT}
else
    echo "[wrapper] $OUTPUT is considered bad by sweepRoot..." | ./appendTimeStamp.sh
fi
echo

#
# clean up
#
echo
echo "[wrapper] cleaning up" | ./appendTimeStamp.sh
for FILE in `find . -not -name "*stderr" -not -name "*stdout"`; do rm -rf $FILE; done
echo "[wrapper] cleaned up"
ls
