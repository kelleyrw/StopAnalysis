#!/bin/bash

if [[ `string_contains $HOSTNAME tensor` ]]; then
    cmd="export PATH=$PATH:/usr/local/lands/03.06.07/test"
elif [[ `string_contains $HOSTNAME uaf` ]]; then
    cmd="export PATH=$PATH:$HOME/code/lands/03.06.07/test"
fi
echo $cmd
eval $cmd
