if [ -z $CAPSTONE_DIR ]; then
  export CAPSTONE_DIR=$(dirname $(readlink -f "$0"));
fi

function generate()
{
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
}

function build()
{
  OWD=$PWD
  BUILD_DIR=$CAPSTONE_DIR/build
  if [ ! -d $BUILD_DIR ]; then
    generate;
  fi

  cd $BUILD_DIR
  echo "Making..."
  make;
  cd $OWD
}

function test()
{
  BUILD_DIR=$CAPSTONE_DIR/build
  if [ ! -d $BUILD_DIR ]; then
    generate;
  fi

  TEST_COMMAND=$BUILD_DIR/source/butler/test/butler-test-suite
  make
  $TEST_COMMAND
}

