#!/bin/sh

set -e
# set -x
mkdir -p ./build/
pushd ./build/ > /dev/null

#
# Libs
#

gcc -Wall -Wextra -ggdb -c ../target.c
ar rs libtarget.a target.o
# cheat bypass dynamic linking
ln -s -f libtarget.a libtarget-st.a

# same as `libtarget-dec.so`
gcc -Wall -Wextra -ggdb -fPIC -shared ../target.c -o libtarget.so

gcc -Wall -Wextra -ggdb -fPIC -shared -DBASE=10 ../target.c -o libtarget-dec.so
gcc -Wall -Wextra -ggdb -fPIC -shared -DBASE=02 ../target.c -o libtarget-bin.so

#
# Apps
#

gcc -Wall -Wextra -ggdb -L .  ../main.c -o main-static -ltarget-st

gcc -Wall -Wextra -ggdb -L .  ../main.c -o main-dynamic -ltarget

gcc -Wall -Wextra -ggdb -L .  ../main.c -o main-all-static -static -ltarget

gcc -Wall -Wextra -ggdb -L . ../main-hl.c -ldl -o main-hl

popd > /dev/null
echo DONE!