#!/usr/bin//sh

CPP_FILES=$(find src/ -type f -name '*cpp')
echo "$CPP_FILES"

set -e

# add -DNDEBUG
clang++ -g -O0 ${CPP_FILES} `llvm-config --cxxflags --ldflags --system-libs --libs core` -o voltt
