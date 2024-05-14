# edu-concurrency

## Prerequisites

- CMake
- C++ compiler with C++20 support
- [Spin](https://spinroot.com/spin/whatispin.html) (for verification only)

## Build

Go to the project root directory and execute the following commands:

```shell
cmake -S . -B build/debug
cmake --build build/debug
```

## Index

- Concurrency
  - Mutual Exclusion
    - [LockOne algorithm](MutualExclusion/LockOne)

## Verification

Let's assume that the file with a model is named `model.pml`.

1. To generate source code for the verifier, execute the command `spin -a model.pml`.
2. Execute `cc -o pan pan.c` to build the verifier.
3. Run the verifier with the command `./pan`.
4. If the verification run reports an error, execute the following command to
   get more information about it: `spin -t -p model.pml`.
