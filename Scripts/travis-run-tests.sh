#!/bin/bash

# Log commands and exit on error
set -xe

#mkdir Build-Unix
cd Build-Unix
cmake .. -G "Unix Makefiles"

cmake --build . --target Frontier.Engine.Tests

cd Tests
../bin/Frontier.Engine.Tests
