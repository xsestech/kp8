# KP 8
## Usage
### Prerequisites
You will need:
- llvm clang with google santizers
- cmake 3.25 installed
- ctest
### Building
```bash
cmake -S . -B build
cmake --build build
```
## Running
```bash
cd build
ctest --verbose
```
