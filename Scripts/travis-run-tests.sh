#!/bin/bash

# Log commands and exit on error
set -xe

mkdir Build-Unix
cd Build-Unix
cmake .. -G "Unix Makefiles"

cmake --build . --target Frontier.Engine.Tests

cd bin
./Frontier.Engine.Tests


cd ..
cd ..
mkdir Build-Unix-Release
cd Build-Unix-Release
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo

cmake --build . --target Frontier.Engine.Tests

cd bin
./Frontier.Engine.Tests
