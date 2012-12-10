#!/bin/sh

[ ! -d build ] && mkdir build
cd build
cmake -G"CodeBlocks - Unix Makefiles" ..
(nohup codeblocks *.cbp &)
cd bin
[ ! -d data ] && mkdir data
