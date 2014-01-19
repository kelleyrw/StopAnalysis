#!/bin/bash

HADOOPDIR=/hadoop/cms/store/user/${USER}/$1
rm unmerged/*.root

echo "
void mergeHadoopFiles() {
  TChain *chain = new TChain(\"tree\");
  chain->SetMaxTreeSize(5000000000LL); //default is 100000000000LL
" > mergeHadoopFiles.C

PREFIX=""
for FILE in `ls $HADOOPDIR`; do
    echo cp ${HADOOPDIR}/${FILE} unmerged/
    cp ${HADOOPDIR}/${FILE} unmerged/
    echo "chain->Add(\"unmerged/${FILE}\");" >> mergeHadoopFiles.C
    PREFIX=`echo ${FILE} | sed 's/\(.*\)_merged.*.root/\1/'`
done

echo $PREFIX

echo "
chain->Merge(\"merged/${PREFIX}.root\", \"fast\");
}" >> mergeHadoopFiles.C

root -b -q mergeHadoopFiles.C

