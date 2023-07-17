# cNARS
C/C++ implementation of NARS (Non-Axiomatic-Reasoning-System)

This is an on-going project, which have almost the same structure with [pynars](https://github.com/bowen-xu/PyNARS). This project aims to provide the C/C++ acceleration for [pynars](https://github.com/bowen-xu/PyNARS).

## TODOS

 - [ ] Precedence when parsing infix compound expression. ("&" > "|" > "&|" > "&/" >  "&&" > "||" > "*")

## Supplementary

To detect memory leaks, run

```
leaks --atExit -- <program-path, e.g. `./main`>
```
