#!/bin/sh -e

# Check if exactly one argument is provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <arg>"
  exit 1
fi

arg=$1

# Compile the main.c file
arm-linux-gnueabi-gcc -static src/main.c -o info

qemu-arm info $arg

# Check if the compilation was successful
if [ "$?" -eq 0 ]; then
  echo "\e[32mCompilation successful. Executable created.\e[0m"
else
  echo "\e[31mCompilation failed.\e[:e0m"
fi
