#!/bin/sh -e

# Check if exactly one argument is provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <arg>"
  exit 1
fi

arg=$1

# Compile the main.c file
riscv64-linux-gnu-gcc -static src/main.c -o info
qemu-riscv64 info $arg

# Check if the compilation was successful
if [ "$?" -eq 0 ]; then
  echo "Compilation successful. Executable created: ../src/info"
else
  echo "Compilation failed."
fi