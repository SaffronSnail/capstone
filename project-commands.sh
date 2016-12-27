if [ -z $CAPSTONE_DIR ]; then
  export CAPSTONE_DIR=$(dirname $(readlink -f "$0"));
fi

function generate()
{
  echo "generating the build directory..."

  OWD=$PWD
  if [ -z $GTEST_DIR ]; then
    GTEST_DIR = $1;
  fi

  if [ -z "$GTEST_DIR" ]; then
    echo "ERROR! If the GTEST_DIR environment variable is not set, then the first argument to this function must be the path to the googletest directory!";
  else
    cd $CAPSTONE_DIR                             &&
      echo  "Setting up build directory..."      &&
      rm -Rf build                               &&
      mkdir build                                &&
      cd    build                                &&
      echo "Generating..."                       &&
      cmake -DGTEST_DIR=$GTEST_DIR $CAPSTONE_DIR
  fi
  cd $OWD
}

function build()
{
  echo "building..."

  OWD=$PWD
  BUILD_DIR=$CAPSTONE_DIR/build
  if [ ! -d $BUILD_DIR ]; then
    generate;
  fi

  cd $BUILD_DIR
  echo "Making..."
  make
  EXIT_STATUS=$?
  cd $OWD
  return $EXIT_STATUS
}

function test()
{
  build

  if [ $? -eq 0 ]; then
    echo "testing..."
    $CAPSTONE_DIR/build/bin/butler/butler-test-suite
  else
    echo "Build failed! Aborting test!"
  fi
}

function debug()
{
  build

  if [ $? -eq 0 ]; then
    echo "debugging..."
    gdb $CAPSTONE_DIR/build/bin/butler/butler-test-suite
  else
    echo "Build failed! Aborting debug session!"
  fi
}

