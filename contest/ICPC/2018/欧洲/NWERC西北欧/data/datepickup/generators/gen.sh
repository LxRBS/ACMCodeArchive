#!/bin/bash

set -e
set -o pipefail

DENSE='pypy ../generators/dense/random_generator.py'
SOLUTION=.'./submissions/accepted/rgl-integers.cc'
SOLVER=$(mktemp)

trap "{ rm -f $SOLVER; }" EXIT

# First test case ID
TCID=50

testcase() {
  generator="$1"
  name="$2"
  ${generator} --name="${name}" "${@:3}" \
   > "$(printf 'secret/%03d-%s.in' "${TCID}" "${name}")" \
   &

  sleep 0
  ((TCID++))
  if { ( ((TCID%5 == 0)) ) } then wait; fi
}

echo "Creating secret data directory"
mkdir -p secret
find secret -mindepth 1 -not -name '*hand*' -delete

testcase "${DENSE}" dense-small1 --vertices 4
testcase "${DENSE}" dense-small2 --vertices 5 --max 2000
testcase "${DENSE}" dense-small3 --vertices 6 --max 2000
testcase "${DENSE}" dense-small4 --vertices 7 --max 2000
testcase "${DENSE}" dense-small5 --vertices 8 --max 2000
testcase "${DENSE}" dense-small6 --vertices 10 --max 2000
testcase "${DENSE}" dense-small7 --vertices 15 --max 2000
testcase "${DENSE}" dense-small8 --vertices 20
testcase "${DENSE}" dense-small9 --vertices 25

testcase "${DENSE}" dense-mid41 --vertices 41
testcase "${DENSE}" dense-mid53 --vertices 53
testcase "${DENSE}" dense-mid62 --vertices 62
testcase "${DENSE}" dense-mid85 --vertices 85
testcase "${DENSE}" dense-mid101 --vertices 101
testcase "${DENSE}" dense-mid200 --vertices 200
testcase "${DENSE}" dense-mid513 --vertices 513 --edges 40000
testcase "${DENSE}" dense-mid1001 --vertices 1001 --edges 100000
testcase "${DENSE}" dense-mid2222 --vertices 2222 --edges 100000
testcase "${DENSE}" dense-mid4213 --vertices 4213 --edges 100000

testcase "${DENSE}" dense-large10202 --vertices 10202 --edges 100000

## Solve all the cases

echo "Compiling solution"
g++ -std=c++14 -O2 -o "${SOLVER}" "${SOLUTION}"
for test_in in secret/*.in
  do
    echo "Solving case ${test_in}"
    test_ans="$(dirname "${test_in}")"/"$(basename "${test_in}" ".in").ans"
    ${SOLVER} <"${test_in}" 1>"${test_ans}" 2>/dev/null &
  done
