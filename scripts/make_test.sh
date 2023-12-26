#!/bin/bash
cd "$(dirname "$0")"
cd ../test/
mkdir $1
cp empty_test.cpp $1/$1.cpp
touch $1/expected.txt
touch $1/input.txt
touch $1/output.txt
touch $1/error.txt
cd ..
echo "$1 creation successful"