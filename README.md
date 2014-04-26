Linear Cryptanalysis on SPN
============================

The implementation is done in a couple of source files. Please refer to the report
for details of the linear cryptanalysis.

### Files

    ├── docs/
    │   └── report.pdf                  # theoretical implementation report
    ├── src/
    │   ├── docs/
    │   │   ├── latex/                  # directory with files used to generate report
    │   │   ├── expressions.html        # linear approximation expressions
    │   │   └── sbox_approx.html        # sbox linear approximation table in HTML
    │   ├── util/
    │   │   └── expressions.c           # auxiliar program to generate expressions.html
    │   ├── linearcryptanalysis.c       # actual implementation of the linear crypt. attack
    │   ├── linearcryptanalysis.h       # header definition of linear implementation
    │   ├── Makefile                    # used for generating and cleaning binaries
    │   ├── pairs.dat                   # pairs of plaintext-ciphertext to avoid recomputation
    │   ├── spn.c                       # implementation of SPN and some auxiliar functions
    │   └── spn.h                       # header definition of SPN implementation
    └── README.md                       # this file


### How to compile

    make linear

### How to run

    ./linear
