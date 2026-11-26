#!/bin/bash

cd "$(dirname "$0")" || exit 1

g++ src/*.cpp -o opencv_1 $(pkg-config --cflags --libs opencv4) && ./opencv_1