export IH=~/ih
export PATH=$PATH:$IH/bin
export IHQ=1

UNAME=`uname`
if [ "$UNAME" = "Darwin" ]; then
  export XTC=/opt/local/lib/gcc46/gcc/x86_64-apple-darwin10/4.6.0/include
fi
if [ "$UNAME" = "Linux" ]; then
  export XTC=/usr/lib/gcc/i486-linux-gnu/4.4/include
fi
