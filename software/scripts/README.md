# Scripts for CI

The scripts in this folder are for some CI systems or can also be used to compile directly on the user system.
Every script has at the end a valid line which can be copied to a command line for running.

## prepare.sh

This script will prepare the local system. Currently it downloading some Arduino Libraries which are needed for compilation.

## compile.sh

This script will compile the source code for the target system (AVR) with the help of the arduino-cli.
Dependency: prepare.sh has to be run bevor.

## cppcheck.sh

This script will do a cppcheck (Linter) and will check if it can find some static bugs in the code.
Dependency: prepare.sh has to be run bevor (currently cppcheck will not look for external libaries, but this will change).

## doxygen.sh

This script will run doxygen and will generate the html files which will be uploaded to Github Pages.

