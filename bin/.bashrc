export IH=~/ih
export IH_INCLUDE_PATH=/net/u/6/c/clownfysh/include
export IH_LIBRARY_PATH=/net/u/6/c/clownfysh/lib
export IHQ=1
export PATH=$PATH:$IH/bin
export LD_LIBRARY_PATH=/net/u/6/c/clownfysh/lib

UNAME=`uname`
if [ "$UNAME" = "Darwin" ]; then
  export XTC=/opt/local/lib/gcc46/gcc/x86_64-apple-darwin10/4.6.0/include
fi
if [ "$UNAME" = "Linux" ]; then
  export XTC=/usr/lib/gcc/i486-linux-gnu/4.4/include
fi
