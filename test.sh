#!/bin/bash

###################################################
# Run checker.bash for all test cases
###################################################

# Path to the checker script
checker="./checker.bash"

# Path to the shell script
shell="./shell"

# Directory containing the test files
test_dir="./tests"

# Get the optional file name argument
file_name="$1"

# Loop through each file in the test directory
for file in "$test_dir"/*.bash; do
  # Check if a specific file name pattern was provided as an argument
  if [[ -n "$file_name" ]]; then
    # Extract the base name of the file without the directory path
    base_name="$(basename "$file")"
    
    # Check if the file matches the provided pattern
    if [[ ! "$base_name" =~ .*"$file_name".* ]]; then
      continue  # Skip this file and move to the next iteration
    fi
  fi
  
  # Execute the command on each file
  "$checker" --valgrind "$shell" "$file"
  
  # Check the exit code of the previous command
  if [[ $? -ne 0 ]]; then
    # If the command failed, print the name of the test file and exit the script
    echo "Test failed: $file"
    exit 1
  fi

  echo -e ": $file"
done


