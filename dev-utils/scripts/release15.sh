#!/bin/sh
# generate OpenJPEG release on *NIX (both Linux and MacOSX)
# There are two cases for MacOSX: 10.4 compat (PPC) and 10.6 and above (intel only 32 & 64 bits)

# control verbosity
set -x

# All OpenJPEG (=false) or just Part-1 (=true) ?
PART1ONLY=false

# get tmpdir:
TMPDIR=/tmp/openjpeg_release

isOSX="`uname -s | grep -i Darwin`"
if [ "$isOSX" != "" ]; then
osxVerFul=`system_profiler |grep 'System Version'| sed -e"s/^.*OS X \([0-9.]*\) .*$/\1/"`
osxVerMajMin="`echo $osxVerFul | cut -d. -f1-2`"
fi

mkdir -p $TMPDIR
mkdir -p $TMPDIR/openjpeg-build
cd $TMPDIR
# Use tag to construct package:
svn checkout -q http://openjpeg.googlecode.com/svn/tags/version.1.5.2 openjpeg
# DEBUG: use openjpeg from trunk
#svn checkout -q http://openjpeg.googlecode.com/svn/trunk openjpeg
# END DEBUG

cmake_options_min="\
 -DCMAKE_BUILD_TYPE:STRING=RelWithDebInfo \
 -DBUILD_THIRDPARTY:BOOL=ON \
 "
cmake_options_extra="\
 -DBUILD_JPWL:BOOL=ON \
 -DBUILD_MJ2:BOOL=ON \
 -DBUILD_JPIP:BOOL=ON \
 "
if [ "$PART1ONLY" = "true" ]; then
  echo "Building Part 1 Only"
  cmake_options=$cmake_options_min
elif [ "$PART1ONLY" = "false" ]; then
  echo "Building all Parts"
  cmake_options="$cmake_options_min $cmake_options_extra"
else
  echo "I'm sorry, Dave. I'm afraid I can't do that"
  exit 1
fi

# On apple let's build universal binaries
if [ "$isOSX" != "" ]; then
if [ "$osxVerMajMin" = "10.4" ]; then
cmake_options="$cmake_options -DCMAKE_OSX_ARCHITECTURES:STRING=ppc;i386 -DCMAKE_OSX_DEPLOYMENT_TARGET:STRING=10.4 -DCPACK_SYSTEM_NAME:STRING=Darwin-universal"
elif [ "$osxVerMajMin" = "10.8" ]; then
cmake_options="$cmake_options -DCMAKE_OSX_ARCHITECTURES:STRING=i386;x86_64 -DCMAKE_OSX_DEPLOYMENT_TARGET:STRING=10.6 -DCPACK_SYSTEM_NAME:STRING=Darwin64-universal"
fi
fi

# On linux 64 bits machines, build 32 bits version
# (comment if needed)
is64="`uname -m | grep -i x86_64`"
if [ "$is64" != "" ]; then
  isLinux="`uname -s | grep -i Linux`"
  if [ "$isLinux" != "" ]; then
    CFLAGS="$CFLAGS -m32"
    cmake_options="$cmake_options -DCPACK_SYSTEM_NAME:STRING=Linux-i386"
  fi
fi
# pass CFLAGS to cmake:
export CFLAGS

cd $TMPDIR/openjpeg-build
cmake -G"Unix Makefiles" $cmake_options ../openjpeg > config.log 2>&1

# build openjpeg
make -j2 > make.log 2>&1

# create TGZ installer
cpack -G TGZ > tgz.log 2>&1

if [ "$isOSX" != "" ]; then
# PackageMaker
cpack -G PackageMaker > packagemaker.log 2>&1
fi

# create source zip
cpack -G TGZ --config CPackSourceConfig.cmake > s-tgz.log 2>&1

echo "Tarball generated here:"
ls $TMPDIR/openjpeg-build/*.tar.gz