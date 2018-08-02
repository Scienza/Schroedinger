## Schroedinger Solver     
[![CircleCI](https://circleci.com/gh/Scienza/Schroedinger/tree/master.svg?style=shield)](https://circleci.com/gh/Scienza/Schroedinger/tree/dev-basis) 
![Linux](https://img.shields.io/badge/linux-supported-brightgreen.svg)
![License](https://img.shields.io/badge/license-LGPL%20v2.1-blue.svg)

This is a first instance of a Schroedinger Solver that makes use of the Numerov algorithm to numerically calcolate the solution of the time-indepedent Schroedinger equation in position space, treated as second order differential equation.

The potential is embedded in the code as a class, together with the basis. At the moment the implementation still going on to realize an extremely versatile object oriented code. But one-dimensional worker at the moment is working just fine.

Output are the energy and the resulting wavefunction.

### Numerov Solver
Numerov solver takes in input an energy bracket in which to look for solution. Increasing from the minimum energy, it takes the lowest energy non-trivial solution as the one that respects boundary conditions.

### Requisites
- compiler which fully supports C++17, due to src implementation of Hermite polynomials in std available in the latest implementations of C++17. That is:
  - g++ version newer than 6.0, due to src implementation of Hermite polynomials in std available in C++17.
  - clang version > 9.0 (there are reports of it working for 5.0)
  - Intel Compilers version > 18.0
- CMake

### How to build
From the CLI navigate into project's directory, then run:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
You'll find the executable file in `Schroedinger/build/bin/`.

### Contribute
To contribute, considers the [issues](https://github.com/AndreaIdini/Schroedinger/issues) and the [to-do](https://github.com/AndreaIdini/Schroedinger/projects) lists. Good first issues are tagged appropriately, depending on contribution aspirations there are issues with different requirements of physics and computer science. 
Watch the introduction video [video \(IT\)](https://www.youtube.com/watch?v=KH8xd0TKkz4) and contact [Andrea Idini](mailto:andrea.idini@gmail.com).
Priviledged channel for contributions is the telegram group [@scienza](https://t.me/Scienza).
