#!/bin/sh
make CC="gcc -fno-peephole2" CXX="g++" AS=as AR=ar RANLIB=ranlib PLATFORM=AMIGA AMISUFFIX=".ppc"  $*
