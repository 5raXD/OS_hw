#!/bin/bash

# Test script for hw1shell

# Function to run a test and check the output
run_test() {
    expected_output="$1"
    command="$2"
    output=$(eval "$command")
    
    if [ "$output" == "$expected_output" ]; then
        echo "Test passed: $command"
    else
        echo "Test failed: $command"
        echo "Expected: $expected_output"
        echo "Got: $output"
    fi
}

# Test case for 'exit' command
run_test "" "./hw1shell -c 'exit'"

# Test case for 'cd' command
run_test "" "./hw1shell -c 'cd /tmp; pwd'"

# Test case for 'jobs' command (assuming no background jobs)
run_test "No background jobs." "./hw1shell -c 'jobs'"

# Test case for an external command (e.g., 'ls')
run_test "$(ls)" "./hw1shell -c 'ls'"

# Test case for invalid command
run_test "Command not found" "./hw1shell -c 'invalid_command'"