# Assignment 2 - Jack Vento
## The Program

The program is a light math library featuring the sin, cos, tan, and exp functions. Sin, cos, and tan are all implemented using Pade approximants in Horner normal form while exp uses a Maclaurin series with an epsilon of 10<sup>-9</sup>. 

The program tests these functions against the standard C library versions in math.h and prints the results in tables.

There are five possible command line arguments:
* -s: *sin* tests
* -c: *cos* tests
* -t: *tan* tests
* -e: *exp* tests
* -a: *all* the aforementioned tests

Run the program using `./math <argument>` (only ONE of the five arguments may be used at a time) after compiling using `make` or `make all`.

## Makefile
* `make` and `make all` will compile the program to an executable named "*math*".
* `make clean` removes all compiler-generated files.
* `infer` is also an optional featured command, which the program passes.
