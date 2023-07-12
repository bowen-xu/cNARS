# cNARS
C/C++ implementation of NARS (Non-Axiomatic-Reasoning-System)

## TODOS

 - [ ] Precedence when parsing infix compound expression. ("&" > "|" > "&|" > "&/" >  "&&" > "||" > "*")

## Supplementary

To detect memory leaks, run

```
leaks --atExit -- <program-path, e.g. `./main`>
```