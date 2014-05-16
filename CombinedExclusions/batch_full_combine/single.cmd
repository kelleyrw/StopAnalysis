universe=grid
Grid_Resource=gt2 osg-gw-6.t2.ucsd.edu:2119/jobmanager-condor
when_to_transfer_output = ON_EXIT
#the actual executable to run is not transfered by its name.
#In fact, some sites may do weird things like renaming it and such.
transfer_input_files=wrapper.sh, job_input/input.tgz, appendTimeStamp.sh
+DESIRED_Sites="UCSD"
+Owner = undefined
log=/home/users/rwkelley/Development/CMSSW_6_1_2_Analysis/src/StopAnalysis/CombinedExclusions/batch_full_combine//submit_logs/condor_05_16_2014.log
output=/home/users/rwkelley/Development/CMSSW_6_1_2_Analysis/src/StopAnalysis/CombinedExclusions/batch_full_combine//job_logs/1e.$(Cluster).$(Process).out
error =/home/users/rwkelley/Development/CMSSW_6_1_2_Analysis/src/StopAnalysis/CombinedExclusions/batch_full_combine//job_logs/1e.$(Cluster).$(Process).err
notification=Never
x509userproxy=/tmp/x509up_u10194

executable=wrapper.sh
transfer_executable=True
arguments="t2tt/combined_t2tt_200_100_bdt5.txt combined_t2tt_200_100_bdt5 /hadoop/cms/store/user/rwkelley/limits/lep1_razor_combine/hybridnew/t2tt"
queue
