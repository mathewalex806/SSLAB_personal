#!/bin/bash

# Compile the program
gcc -o priority.c priority.c.c

# Check if compilation was successful
if [[ $? -ne 0 ]]; then
    echo "Compilation failed."
    exit 1
fi

# Function to run a test case
run_test() {
    local test_input="$1"
    local test_name="$2"

    echo "Running $test_name"
    echo -e "$test_input" | ./priority.c
    echo "--------------------------"
}

# Define test cases
# Format: "number_of_processes\npid burst_time priority\n..."

# Test Case 1: Basic test with two processes
test_case_1="2
1 5 2
2 3 1"

# Test Case 2: Edge case with one process
test_case_2="1
1 10 3"

# Test Case 3: Multiple processes with the same priority
test_case_3="4
1 4 2
2 6 2
3 5 2
4 3 2"

# Test Case 4: Multiple processes with ascending priority
test_case_4="3
1 8 1
2 4 2
3 2 3"

# Test Case 5: Multiple processes with descending priority
test_case_5="3
1 2 3
2 4 2
3 8 1"

# Test Case 6: Large number of processes
test_case_6="5
1 10 3
2 20 1
3 15 2
4 5 4
5 7 2"

# Test Case 7: All burst times are zero (edge case)
test_case_7="3
1 0 3
2 0 1
3 0 2"

# Test Case 8: Negative values for burst time and priority (invalid input case)
test_case_8="3
1 -5 -2
2 -3 -1
3 -2 -3"

# Run all test cases
run_test "$test_case_1" "Test Case 1: Basic test with two processes"
run_test "$test_case_2" "Test Case 2: Edge case with one process"
run_test "$test_case_3" "Test Case 3: Multiple processes with the same priority"
run_test "$test_case_4" "Test Case 4: Multiple processes with ascending priority"
run_test "$test_case_5" "Test Case 5: Multiple processes with descending priority"
run_test "$test_case_6" "Test Case 6: Large number of processes"
run_test "$test_case_7" "Test Case 7: All burst times are zero"
run_test "$test_case_8" "Test Case 8: Negative values for burst time and priority"

# Clean up
rm -f priority.c
