# Source information:
#   License:    CC0 "No rights reserved"
#   Repository: https://github.com/nordicolympiad/testdata_tools/
#   Commit:     bba8ccddd137e7a744a4e436c1d9eec767dc7050)

# This file provides support functions for generating testdata for scoring problems with test groups.
# See generator_example.sh for example usage. For non-scoring problems, include gen-acm.sh instead.

set -e

SOLUTION_BASE=$PPATH/submissions/accepted

TOTAL_SCORE=0

# Feature-detect symlink support if not explicitly set.
if [[ $USE_SYMLINKS = '' ]]; then
  set +e
  rm -f .dummy .dummy2
  ln -s .dummy .dummy2 2>/dev/null
  echo -n test >.dummy
  if [[ $(cat .dummy2 2>/dev/null) = test ]]; then
    USE_SYMLINKS=1
  else
    USE_SYMLINKS=0
  fi
  rm -f .dummy .dummy2
  set -e
fi

# Set USE_PARALLEL=0 before including gen.sh to disable parallelism.
if [[ $USE_PARALLEL != 0 ]]; then
  USE_PARALLEL=1
  PARALLELISM_ACTIVE=1
fi

declare -A programs
declare -A cases
declare -A groups
declare -a cleanup

get_ext () {
  echo $(echo $1 | rev | cut -d. -f1 | rev)
}

base () {
  ext=$(get_ext $1)
  echo `basename $1 .$ext`
}

_assert_scoring () {
  if [[ $USE_ACM != '' ]]; then
    echo "Do not call $1 for non-scoring generators"
    exit 1
  fi
}

# Add a program to the list of programs
# Arguments: name execution_command
add_program () {
  programs[$1]="$2"
}

# Mark a file as needing to be removed when the generator finishes.
add_cleanup () {
  cleanup+=("$1")
}

add_program cat "bash -c cat<\$0"

# Compile a C++ program to run.
# Arguments: file opts
compile_cpp () {
  echo Compiling $1...
  if [[ $2 == *"opt"* ]]; then
    g++ -O2 -Wall -std=gnu++14 -DGENERATING_TEST_DATA -o $(base $1) $1
  else
    g++ -O2 -fsanitize=undefined -Wall -std=gnu++14 -DGENERATING_TEST_DATA -o $(base $1) $1
  fi
  add_program $(base $1) "./$(base $1)"
  add_cleanup $(base $1)
}

# Compile a Java program to run.
# Arguments: file
compile_java () {
  javac $1
  cp $(dirname $1)/*.class .
  add_program $(base $1) "java $(base $1)"
  add_cleanup $(base $1)
}

# Compile a Python program to run.
# Arguments: file opts
compile_py () {
  if [[ $2 == *"pypy"* ]]; then
    add_program $(base $1) "pypy $1"
  else
    add_program $(base $1) "python3 $1"
  fi
}

# Compile a bash program to run.
# Arguments: file
compile_sh () {
  add_program $(base $1) "bash $1"
}

# Compile a program
# Arguments: file opts
compile () {
  ext=$(get_ext $1)
  if [ $ext == "java" ]
  then 
    compile_java $1
  elif [ $ext == "cpp" -o $ext == "cc" ]
  then
    compile_cpp $1 $2
  elif [ $ext == "py" ]
  then
    compile_py $1 $2
  elif [ $ext == "sh" ]
  then
    compile_sh $1 $2
  else
    echo "Unsupported program: $1"
    exit 1
  fi
}

_update_scores() {
  _assert_scoring "_update_scores"
  echo "on_reject: continue
range: 0 $TOTAL_SCORE" > secret/testdata.yaml
  echo "range: 0 $TOTAL_SCORE
on_reject: continue
grader_flags: always_accept" > testdata.yaml
}

# Solve a test case using the solution
# Arguments: testcase path
solve () {
  execmd=${programs[$SOLUTION]}
  $($execmd < $1.in > $1.ans)
}

CURGROUP_NAME=.
CURGROUP_DIR=secret
CURTEST_ID=1

# Use a certain solution as the reference solution
# Arguments: solution name
use_solution () {
  path=$SOLUTION_BASE/$1
  SOLUTION=$(base $path)
  compile $path $2
}


# Add the sample group:
# Arguments: none
samplegroup () {
  _assert_scoring samplegroup
  echo "Sample group"
  CURGROUP_DIR=sample
}

# Arguments: testcasename
sample () {
  echo "Solving case sample/$1..."
  solve sample/$1
}

# Arguments: testgroupname score
group () {
  _assert_scoring group
  mkdir secret/$1
  CURGROUP_NAME=$1
  CURGROUP_DIR=secret/$1
  echo 
  echo "Group $CURGROUP_NAME"
  groups[$1]=""

  score=$2
  echo "on_reject: break
accept_score: $score
range: 0 $score
grader_flags: min" > secret/$1/testdata.yaml
  TOTAL_SCORE=$((TOTAL_SCORE + score))
  _update_scores
}

# Arguments: parameters sent to input validator
limits () {
  if [[ $USE_ACM == '' ]]; then
    echo "input_validator_flags: $@" >> $CURGROUP_DIR/testdata.yaml
  else
    echo "input_validator_flags: $@" >> testdata.yaml
  fi
}

do_tc () {
  name="$1"
  filename="$2"
  execmd="$3"
  # Let the seed be the 6 first hex digits of the hash of the name converted
  # to decimal (range 0-16777215), to make things more deterministic.
  seed=$((16#$(echo -n "$name" | md5sum | head -c 6)))
  echo "Generating case $name..."
  $execmd "${@:4}" $seed > "$filename.in"

  echo "Solving case $name..."
  solve "$filename"
}

handle_err() {
  echo ERROR generating case $1
  # Kill the parent. This might fail if the other subprocesses do so at the
  # same time, but the PID is unlikely to be reused in this window, so...
  # Just silence the error.
  kill $$ 2>/dev/null
  exit 1
}

par_tc () {
  set -E
  trap "handle_err $1" ERR
  do_tc "$@"
}

# Arguments: testcasename generator arguments...
tc () {
  name="$1"
  fullname="${CURGROUP_DIR}/${name}"
  testcase_id=$(printf '%03d' ${CURTEST_ID})
  while ls "${CURGROUP_DIR}/${testcase_id}"-*.in 1> /dev/null 2>&1
    do
      ((CURTEST_ID++))
      testcase_id=$(printf '%03d' ${CURTEST_ID})
    done
  filename="${CURGROUP_DIR}/${testcase_id}-${name}"
  ((CURTEST_ID++))

  if [[ $USE_ACM == '' && $CURGROUP_NAME == '.' ]]; then
    echo "ERROR: Test case $name must be within a test group"
    exit 1
  fi

  if [[ ${cases[$name]} != "" ]]
  then
    echo "ERROR: duplicate test case name $name"
    exit 1
  fi

  cases[$name]=$CURGROUP_DIR
  groups[$CURGROUP_NAME]="${groups[$CURGROUP_NAME]} $name"

  program="${programs[$2]}"

  if [[ $USE_PARALLEL != 1 ]]; then
    do_tc "${fullname}" "${filename}" "$program" "${@:3}"
  else
    if [[ $PARALLELISM_ACTIVE = 17 ]]; then
      # wait after every 16 cases
      wait
      let PARALLELISM_ACTIVE=1
    fi
    let PARALLELISM_ACTIVE++
    par_tc "${fullname}" "${filename}" "$program" "${@:3}" &
  fi
}

# Arguments: ../manual-tests/testcasename.in
tc_manual () {
  tc $(base $1) cat $1
}

# Include all testcases in another group
# Arguments: group name to include
include_group () {
  _assert_scoring include_group
  any=0
  for x in ${groups[$1]}; do
    tc $x
    any=1
  done
  if [[ $any = 0 ]]; then
    echo "ERROR: included group $1 does not exist"
    exit 1
  fi
}

# Initialization and cleanup code, automatically included.
_setup_dirs () {
  mkdir -p sample secret
  find secret -maxdepth 1 -type f -not -iname "*-hand.*" -delete
  if [[ $USE_ACM == '' ]]; then
    echo "on_reject: continue
range: -1 0
accept_score: 0
grader_flags: no_errors" > sample/testdata.yaml
    _update_scores
  fi
}
_setup_dirs

_cleanup_programs () {
  wait
  for x in "${cleanup[@]}"; do
    rm -f $x
  done
  rm -rf __pycache__
  rm -rf *.class
}
trap _cleanup_programs EXIT
