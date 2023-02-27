#!/usr/bin/env bash

function print_help() {
  echo "usage: build-ci.sh <build-number>"
}

if [ $# -lt 1 ]; then
  print_help
  exit 1
fi

BUILD_NUMBER="$1"

rm -Rf ./build
mkdir ./build
pushd ./build
cmake .. -DBUILD_VERSION="$BUILD_NUMBER"
cmake --build .
./test/version_test $BUILD_NUMBER
cmake --build . --target package
popd

exit 0
