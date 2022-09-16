#!/usr/bin/env bash

# Setup
rm -fr build;
source setup.profile;
export PROJECT_DIR SYSTEMC_HOME

# Record
date          | tee    version.log
uname -a      | tee -a version.log
c++ --version | tee -a version.log

# Configure
cmake -S . -B build -DCMAKE_PREFIX_PATH="${PROJECT_DIR}" 2>&1 | tee config.log;

# Compile & link
cmake --build build                                      2>&1 | tee compile.log;

# Run the test
ctest --test-dir build -V                                2>&1 | tee test.log;
