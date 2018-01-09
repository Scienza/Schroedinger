## Schroedinger Solver
This is a first instance of a Schroedinger Solver that makes use of the Numerov algorithm to numerically calcolate the solution of the time-indepedent Schroedinger equation in position space, treated as second order differential equation.

The potential is embedded in the code as a double function, and passed to the Numerov solving routine as a pointer.

Output are the energy and technical results of the algorithm, plus the resulting wavefunction. They are just video streamed.

### Numerov Solver
Numerov solver takes in input an energy bracket in which to look for solution. Increasing from the minimum energy, it takes the lowest energy non-trivial solution as the one that respects boundary conditions.

### Contribute
To contribute, considers the [issues](https://github.com/AndreaIdini/Schroedinger/issues) and the [to-do](https://github.com/AndreaIdini/Schroedinger/projects) lists.
Watch the introduction video [video \(IT\)](https://www.youtube.com/watch?v=KH8xd0TKkz4) and contact [Andrea Idini](andrea.idini@gmail.com).
Priviledge channel for contributions is the telegram group [@scienza](t.me/Scienza).
