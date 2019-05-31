#!/usr/bin/env bash

RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
CYAN="\033[36m"
B="\033[1;4m"
NC="\033[0m"

dir_under_test=${1/%\//}
echo ${dir_under_test};
CC="g++ -std=c++11"
verbose=false

function judge {
    echo -e "${B}${problem} Test${NC}"
    code="${dir_under_test}/${problem}_test.cpp"
    sed -i "s|#include\s*\"${header}\"|#include\ \"${PWD}/${src}/${header}\"|g" "$code"
    sed -i "s|#include\s*\"catch.hpp\"|#include\ \"${PWD}/catch.hpp\"|g" "$code"
    sed -i "s|#include\s*<catch2/catch.hpp>|#include\ \"${PWD}/catch.hpp\"|g" "$code"
    passed=0
    if ! ${CC} -c "$code" -o "${code/%.cpp/.o}"; then
        echo -e "${RED}compile error${NC}"
    else
        for test in ${all[@]}; do
            echo -e ${YELLOW}$test${NC}
            if ! test -f "$src/${test/%.cpp/.o}"; then
                ${CC} -c "$src/${test}" -o "$src/${test/%.cpp/.o}"
            fi
            if ! ${CC} "${code/%.cpp/.o}" "$src/${test/%.cpp/.o}" -o "${code/%.cpp/.out}"; then
                echo -e "${RED}link error${NC}"
            else
                if [[ "${verbose}" = true ]]; then
                    "./${code/%.cpp/.out}" --success
                else
                    "./${code/%.cpp/.out}" >/dev/null
                fi
                ret=$?
                if ([[ " ${should_fail[@]} " == *" $test "* ]] && [[ $ret != 0 ]] ) || ([[ " ${should_fail[@]} " != *" $test "* ]] && [[ $ret == 0 ]] ); then
                    echo -e "${GREEN}pass${NC}"
                    ((passed++))
                else
                    echo -e "${RED}fail${NC} ($ret)"
                fi
                if [[ "${verbose}" = true ]]; then
                    echo ""
                fi
            fi
        done
    fi
    echo -e "${CYAN}$passed of ${#all[@]} passed.${NC}"
    echo ""
    unset problem
    unset src
    unset header
    unset all
    unset should_fail
}


function judge_triangle {
    problem="triangle"
    src="triangle"
    header="Triangle.hpp"
    all=("Triangle.cpp" "TriangleCorrect.cpp" "TriangleConstructor.cpp" "TriangleInequality.cpp" "TriangleGetPerimeter.cpp" "TriangleGetKind.cpp")
    should_fail=("Triangle.cpp" "TriangleConstructor.cpp" "TriangleInequality.cpp" "TriangleGetPerimeter.cpp" "TriangleGetKind.cpp")
    ((all_to_pass+=${#all[@]}))
    judge
    ((all_passed+=passed))
}


function judge_avg {
    problem="get_avg_of_vector"
    src="get_avg_of_vector"
    header="get_avg_of_vector.hpp"
    all=("get_avg_of_vector.cpp" "get_avg_of_vector_v1.cpp" "get_avg_of_vector_v2.cpp" "get_avg_of_vector_v3.cpp" "get_avg_of_vector_v4.cpp" "get_avg_of_vector_v5.cpp")
    should_fail=("get_avg_of_vector_v1.cpp" "get_avg_of_vector_v2.cpp" "get_avg_of_vector_v4.cpp")
    ((all_to_pass+=${#all[@]}))
    judge
    ((all_passed+=passed))
}

all_passed=0
all_to_pass=0
judge_triangle
judge_avg
echo -e "${dir_under_test}\t${CYAN}Overall passed: ${all_passed} of ${all_to_pass} ($((${all_passed} * 100 / ${all_to_pass}))%)${NC}"
echo -e "\n\n"
