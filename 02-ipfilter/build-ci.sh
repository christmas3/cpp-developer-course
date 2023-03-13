#!/usr/bin/env bash

function print_help() {
  echo "usage: build-ci.sh <build-number>"
}

if [ $# -lt 1 ]; then
  print_help
  exit 1
fi

BUILD_NUMBER="$1"

echo "Building"
rm -Rf ./build
mkdir ./build
pushd ./build
cmake .. -DBUILD_VERSION="$BUILD_NUMBER"
cmake --build .

echo "Testing"
CALC_MD5SUM=$(cat ../ip_filter.tsv | ./ipfilter | md5sum | cut -d ' ' -f 1)
CHECK_SUM="24e7a7b2270daee89c64d3ca5fb3da1a"
if [ "$CALC_MD5SUM" = "$CHECK_SUM" ]; then
  echo "md5 correct and equal $CALC_MD5SUM"
else
  echo "md5 error calc md5sum: $CALC_MD5SUM and check m5sum: $CHECK_SUM"
  exit 1
fi
echo "Building package"
cmake --build . --target package
popd

exit 0
