#!/bin/bash
export LD_LIBRARY_PATH=$HOME/custom-malloc.so
echo $LD_LIBRARY_PATH
$@