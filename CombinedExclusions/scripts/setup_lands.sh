#!/bin/bash

if [[ `string_contains $HOSTNAME tensor` ]]; then
    cmd="export PATH=$PATH:/usr/local/lands/03.06.07/test"
    echo $cmd
    eval $cmd
fi
