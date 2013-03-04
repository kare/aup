#!/bin/sh
AUPSRC=/Users/kare/Projects/aup
OS=DARWIN
SUV=SUV_SUS3
LIBS="-lncurses"
TLIBS="-llthread -llgcc_r"
export AUPSRC OS LIBS TLIBS SUV
make $2 -f $AUPSRC/$1/Makefile $3
