#!/bin/bash

#Exit on any error
set -e 

LANGUAGE=$1


PATH=$PATH:/opt/local/bin
export PATH

OPTIONS=""

# set GTEST path
OPTIONS="$OPTIONS -DGTEST_ROOT=~/sw/gtest-1.7.0/"

if [ "$LANGUAGE" == "C++98" ]; then
  echo "Building with C++98";
  BUILDPATH="cpp98"
elif [ "$LANGUAGE" == "C++11" ]; then
  echo "Building with C++11";
  OPTIONS="$OPTIONS -DCMAKE_CXX_FLAGS='-std=c++11' "
  BUILDPATH="cpp11"  
elif [ "$LANGUAGE" == "C++14" ]; then
  echo "Building with C++14";
  OPTIONS="$OPTIONS -DCMAKE_CXX_FLAGS='-std=c++14' "
  BUILDPATH="cpp14"
fi  

#=====================================
# Color Settings:
#=====================================
NC='\033[0m'
OUTPUT='\033[0;32m'
WARNING='\033[0;93m'


echo -e "${OUTPUT}"
echo ""
echo "======================================================================"
echo "Basic configuration details:"
echo "======================================================================"
echo -e "${NC}"

echo "Options:    $OPTIONS"
echo "BuildPath:  $BUILDPATH"
echo "Path:       $PATH"
echo "Language:   $LANGUAGE"

echo -e "${OUTPUT}"
echo ""
echo "======================================================================"
echo "Building Release version with vectorchecks enabled"
echo "======================================================================"
echo -e "${NC}"


if [ ! -d build-release-$BUILDPATH-Vector-Checks ]; then
  mkdir build-release-$BUILDPATH-Vector-Checks
fi

cd build-release-$BUILDPATH-Vector-Checks

cmake -DCMAKE_BUILD_TYPE=Release -DOPENMESH_BUILD_UNIT_TESTS=TRUE -DSTL_VECTOR_CHECKS=ON $OPTIONS ../

#build it
make

#build the unit tests
make unittests

echo -e "${OUTPUT}"
echo ""
echo "======================================================================"
echo "Running unittests Release version with vectorchecks enabled"
echo "======================================================================"
echo -e "${NC}"

cd Unittests

#execute tests
./unittests --gtest_color=yes --gtest_output=xml

echo -e "${OUTPUT}"
echo ""
echo "======================================================================"
echo "Running unittests Release version with minimal vector type"
echo "======================================================================"
echo -e "${NC}"

./unittests_customvec --gtest_color=yes --gtest_output=xml

cd ..
cd ..

echo -e "${OUTPUT}"
echo ""
echo "======================================================================"
echo "Building Debug version with vectorchecks enabled"
echo "======================================================================"
echo -e "${NC}"


if [ ! -d build-debug-$BUILDPATH-Vector-Checks ]; then
  mkdir build-debug-$BUILDPATH-Vector-Checks
fi

cd build-debug-$BUILDPATH-Vector-Checks

cmake -DCMAKE_BUILD_TYPE=Debug -DOPENMESH_BUILD_UNIT_TESTS=TRUE -DSTL_VECTOR_CHECKS=ON $OPTIONS ../

#build it
make

#build the unit tests
make unittests

echo -e "${OUTPUT}"
echo ""
echo "======================================================================"
echo "Running unittests Debug version with vectorchecks enabled"
echo "======================================================================"
echo -e "${NC}"


cd Unittests

#execute tests
./unittests --gtest_color=yes --gtest_output=xml

echo -e "${OUTPUT}"
echo ""
echo "======================================================================"
echo "Running unittests Debug version with minimal vector type"
echo "======================================================================"
echo -e "${NC}"

./unittests_customvec --gtest_color=yes --gtest_output=xml

cd ..
cd ..

echo -e "${OUTPUT}"
echo ""
echo "======================================================================"
echo "Package creation (DMG and tarball)"
echo "======================================================================"
echo -e "${NC}"


if [ ! -d build-release-$BUILDPATH ]; then
  mkdir build-release-$BUILDPATH
fi

cd build-release-$BUILDPATH

cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_APPS=OFF -DCPACK_BINARY_DRAGNDROP=ON $OPTIONS ../

#build it
make
make package
