#!/bin/bash
clear

#Colors
BLACK="\033[0;30m"
RED="\033[0;31m"
GREEN="\033[0;32m"
ORANGE="\033[0;33m"
BLUE="\033[0;34m"
PURPLE="\033[0;35m"
CYAN="\033[0;36m"
LIGHT_GRAY="\033[0;37m"

DARK_GRAY="\033[1;30m"
LIGHT_RED="\033[1;31m"
LIGHT_GREEN="\033[1;32m"
YELLOW="\033[1;33m"
LIGHT_BLUE="\033[1;34m"
LIGHT_PURPLE="\033[1;35m"
LIGHT_CYAN="\033[1;36m"
WHITE="\033[1;37m"

GNL_DIR=".."
export GNL_DIR

#Buffer sizes
BUFFER_SIZES=(1 2 3 8 41 42 43 128 99999 100000)
#BUFFER_SIZES=(99999 100000)

SetColor() {
  printf "$1"
}


SetColor "$YELLOW"
printf "Starting normal tests using gnlTester!\n"
echo -n > deeperthought
TEST_FILES_INT=$(ls -P ./tests | grep -v "/")
TEST_FILES=""
for file in ${TEST_FILES_INT[@]}
do
  TEST_FILES="$TEST_FILES tests/$file"
done
#echo ${TEST_FILES}

for bfs in "${BUFFER_SIZES[@]}"
do
  make fclean >> /dev/null
  BUF_SIZE="$bfs"
  export BUF_SIZE
  make mandatory >> /dev/null
#   shellcheck disable=SC2068
  for file in ${TEST_FILES[@]}
  do
    SetColor "$WHITE"
    printf $file
    printf " (%d) " "$BUF_SIZE"
#    make $file
    eval "./gnlTester ${file}"
    RETVAL=$?
    if [ $RETVAL -ne 0 ];
    then
      SetColor "$LIGHT_RED"
      printf "KO %d\n" "$RETVAL"
    else
      SetColor "$LIGHT_GREEN"
      printf "OK\n"
    fi
    cat deepthought >> deeperthought
  done
done

SetColor "$YELLOW"
printf "Starting malloc failure tests using gnlTester!\n"
for bfs in "${BUFFER_SIZES[@]}"
do
  make fclean >> /dev/null
  BUF_SIZE="$bfs"
  export BUF_SIZE
  make memfail >> /dev/null
#   shellcheck disable=SC2068
  for file in ${TEST_FILES[@]}
  do
    SetColor "$WHITE"
    printf $file
    printf " (%d) " "$BUF_SIZE"
#    make $file
    eval "./gnlTester ${file}"
    RETVAL=$?
    if [ $RETVAL -ne 0 ];
    then
      SetColor "$LIGHT_RED"
      printf "KO %d\n" "$RETVAL"
    else
      SetColor "$LIGHT_GREEN"
      printf "OK\n"
    fi
    cat deepthought >> deeperthought
  done
done

SetColor "$YELLOW"
printf "Starting read failure tests using gnlTester!\n"
for bfs in "${BUFFER_SIZES[@]}"
do
  make fclean >> /dev/null
  BUF_SIZE="$bfs"
  export BUF_SIZE
  make readfail >> /dev/null
#   shellcheck disable=SC2068
  for file in ${TEST_FILES[@]}
  do
    SetColor "$WHITE"
    printf $file
    printf " (%d) " "$BUF_SIZE"
#    make $file
    eval "./gnlTester ${file}"
    RETVAL=$?
    if [ $RETVAL -ne 0 ];
    then
      SetColor "$LIGHT_RED"
      printf "KO %d\n" "$RETVAL"
    else
      SetColor "$LIGHT_GREEN"
      printf "OK\n"
    fi
    cat deepthought >> deeperthought
  done
done
SetColor "$YELLOW"
printf "Done with all the tests!\n"

#SetColor "$LIGHT_GREEN"
#printf "Testing bonus!\n"
#printf "Static count: "
#grep "static.*;" "*_bonus.c" | wc -l | td -d ' '
#printf "\n"

SetColor "$LIGHT_CYAN"
printf "Testing bonus!\n"
SetColor "$LIGHT_BLUE"
printf "Static count: "
grep "static.*;" ${GNL_DIR}/*_bonus.c | wc -l | tr -d ' '
SetColor "$YELLOW"
printf "Starting bonus tests using gnlTester!\n"
for bfs in "${BUFFER_SIZES[@]}"
do
  make fclean >> /dev/null
  BUF_SIZE="$bfs"
  export BUF_SIZE
  SetColor "$WHITE"
  printf "BUFFER_SIZE:%d " "$BUF_SIZE"
  make bonus >> /dev/null
  eval "./gnlTester ${TEST_FILES[@]}"
  RETVAL=$?
  if [ $RETVAL -ne 0 ];
  then
    SetColor "$LIGHT_RED"
    printf "KO %d\n" "$RETVAL"
   else
    SetColor "$LIGHT_GREEN"
    printf "OK\n"
  fi
  cat deepthought >> deeperthought
done

SetColor "$YELLOW"
printf "Testing speed of get_next_line using gnlTester!\n"
echo -n > profiling
for bfs in "${BUFFER_SIZES[@]}"
do
  make fclean >> /dev/null
  BUF_SIZE="$bfs"
  export BUF_SIZE
  make profiler >> /dev/null
#   shellcheck disable=SC2068
  for file in ${TEST_FILES[@]}
  do
    SetColor "$WHITE"
    printf $file
    printf " (%d) " "$BUF_SIZE"
#    make $file
    eval "./gnlTester ${file}"
    RETVAL=$?
    if [ $RETVAL -ne 0 ];
    then
      SetColor "$LIGHT_RED"
      printf "KO %d\n" "$RETVAL"
    else
      SetColor "$LIGHT_GREEN"
      printf "OK\n"
    fi
    cat deepthought >> profiling
  done
done
SetColor "$YELLOW"
printf "Done with all the tests!\n"