#!/bin/bash

# NOTES
# - PROJECT_DIR contains two key directories: common/ and cmake/
#   + cmake/ may be omitted if using make
# - SYSTEMC_HOME should point to the installed code (not source)

# ACTION
export SYSTEMC_HOME LD_LIBRARY_PATH DYLD_LIBRARY_PATH PROJECT_DIR
PROJECT_DIR="$(git rev-parse --show-toplevel)"
APPS="${HOME}/.local/apps"
SYSTEMC_HOME="${APPS}/systemc"
LD_LIBRARY_PATH="${HOME}/.local/apps/systemc/lib"
DYLD_LIBRARY_PATH="${HOME}/.local/apps/systemc/lib"

echo "$0: environment setup"

# vim:nospell
