if [ -z $CAPSTONE_DIR ]; then
  export CAPSTONE_DIR=$(dirname $(readlink -f "$0"));
fi

function build()
{
  if [ -z $GTEST_DIR ]; then
    GTEST_DIR = $1;
  fi

  if [ -z "$GTEST_DIR" ]; then
    echo "ERROR! If the GTEST_DIR environment variable is not set, then the first argument to this function must be the path to the googletest directory!";
  else
    cd $CAPSTONE_DIR                             &&
      echo  "Setting up build directory..."      &&
      rm -R build                                &&
      mkdir build                                &&
      cd    build                                &&
      clear                                      &&

      echo "Generating..."                       &&
      cmake -DGTEST_DIR=$GTEST_DIR $CAPSTONE_DIR &&
      echo "Making..."                           &&
      make;
  fi
}

