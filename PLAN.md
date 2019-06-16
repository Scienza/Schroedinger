# The Master Plan

Right now Schroedinger is a unique piece of software in search of use cases. 
Its uniqueness sits on the flexible definition of the basis as Singleton, and OO construction of the Hilbert space (basis) and Hamiltonian (potential). 
The particle then move in the world constructed above, and this is guaranteed by the Schroedinger solve (Numerov).

Of course this is nothing new and Schroedinger equations solvers have been used since computers existed. However, the difficult part and the hard ground is laid down. Now, with the right work, the possibility of easily extending basis provides with opportunities both scientifically and computationally.

The plan for the publication and scientific usefulness of Schroedinger can move on two related, but independent, tracks. 
The prerequisites suggested for each milestone with the objective of publication are defined below. 
If you would like to contribute without satisfying the prerequisites, you are welcome and we will do our best to filling the gaps. Moreover, this could be an excellent didactic opportunity to learn, that fits in my pedagogical experiment and might merit a separate publication.

Every contributor to the project will be properly accredited.

## [Publication 1] Template basis change

### Prerequisites

- Linear Algebra
- Network theory

### Project

The project aim to automatize the definition of basis, which is one of the most important, but overlooked part of any quantum mechanical calculation. The reason why physicist grudge to explore different bases for their calculations is because of the heavy handed calculations (either analytical or computational) involved. Very often the market is full of a fauna of codes, with the only difference being the definition of the basis and related solver.

The quantum mechanical wavefunctions live in an Hilbert space, that is a complex vector field of arbitrary dimension with the definition of inner product. The Hilbert space is described by a (complete) basis, that is a set of vectors. A familiar example of a basis is the cartesian set, made by the unitary vectors corresponding to the perpendicular directions that defines the coordinates (usually in 2 or 3 Dimensions denoted with x,y,z). 

![The cartesian Plane](https://upload.wikimedia.org/wikipedia/commons/0/0e/Cartesian-coordinate-system.svg)

Changing basis implies the construction of a transformation (isomorphism) from one set of coordinate to the other, often in matrix form. This is necessary to define the interaction, that is usually given in coordinate form (e.g. the Coulomb interaction ~1/r ) but that we might want to use in another basis for solver convenience. This is also important to obtain the fastest convergence.

The objectives of this problem are to set up:
- easy, flexible, initialization of the basis class (mostly done);
- rules for deducing solver behaviour according to the basis;
- change of basis routine with automated calculus.

This project will not concern physics cases or properties. Therefore, the knowledge of quantum mechanics is only needed for checking the convergence/correctness of the solution. That can be done setting up progressive testing checks.

#### Initialization of Basis

#### Solver rules

#### Automated calculus for basis change

Automate basis changes through implementation of Yutis Graph for handling of spherical harmonics and generalise the basis change as a network problem.

cf. [Ripoche](https://abinitio.triumf.ca/2019/ripoche_SlidesTriumf2019.pdf)

## [Publication 2] Imaginary basis for non hamiltonian time evolution

### Prerequisites

- Basic quantum mechanics in first quantization

### Project

Implement an imaginary basis and disappearing boundary conditions. 

- Try to model non-hamiltonian systems where the wave function current is not conserved, compare to one-body Green functions with imaginary self-energy.
- Model fission in an exact 1-D toy-model
