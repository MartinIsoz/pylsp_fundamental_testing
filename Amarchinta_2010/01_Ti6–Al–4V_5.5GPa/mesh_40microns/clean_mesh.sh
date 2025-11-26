#!/bin/bash

echo '------------------------------------'
echo ' Clean Mesh                         '
echo '------------------------------------'

case_dir="$(pwd)"

rm -rf $case_dir/mesh.foam
rm -rf $case_dir/[0-9]*
rm -rf $case_dir/processor*
rm -rf $case_dir/constant
rm -rf $case_dir/dynamicCode
rm -f $case_dir/log.*
rm -rf *.foam
