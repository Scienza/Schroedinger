#include "Numerov.h"

static inline double square (double x) { return x*x; }

Numerov::Numerov(Potential potential, int nbox)
{
    this->potential        = &potential;
    this->nbox             = nbox;
    this->solutionEnergy   = 0;
    this->probability      = std::vector<double>(nbox+1);
    this->wavefunction     = std::vector<double>(nbox+1);
    this->tempWavefunction = std::vector<double>(nbox+1);

    // Fill wavefunction with 1 in order to multiply each wavefunction found on separated potentials
    std::fill(this->wavefunction.begin(), this->wavefunction.end(), 1.0);
    std::fill(this->tempWavefunction.begin(), this->tempWavefunction.end(), 0.0);
    this->tempWavefunction[0] = 0.0;
    this->tempWavefunction[1] = 0.1;
}

// Numerov Algorithm solves f''(x) + v(x)f(x) = 0, 
// by considering
// \left( 1+ \frac{h^2}{12} v(x+h) \right) f(x+h) = 2 \left( 1 - \frac{5h^2}{12} v(x) \right) f(x) - \left( 1 + \frac{h^2}{12} v(x-h) \right) f(x-h).
// for the Shroedinger equation v(x) = V(x) - E, where V(x) is the potential and E the eigenenergy
void Numerov::findWavefunction(double energy, std::vector<double> &potential_values)
{
    double x;
    double c = (2.0 * mass / hbar / hbar) * (dx * dx / 12.0);
    potential_values.push_back(1.0); // tricky fix

    //Build Numerov f(x) solution from left.
    for (int i = 2; i <= this->nbox; i++)
    {
        x = (-this->nbox / 2 + i) * dx;
        double &value = this->tempWavefunction[i];
        double &pot_1 = potential_values.at(i - 1);
        double &pot_2 = potential_values.at(i - 2);
        double &pot_a = potential_values.at(i);

        double &wave_1 = this->tempWavefunction.at(i - 1);
        double &wave_2 = this->tempWavefunction.at(i - 2);

        value = 2 * (1.0 - (5 * c) * (energy - pot_1)) * wave_1 - (1.0 + (c) * (energy - pot_2)) * wave_2;
        value /= (1.0 + (c) * (energy - pot_a));
    }

}

// A solver of differential equation using Numerov algorithm and selecting non-trivial solutions.
// It solves the pointed potential using the Numerov algorithm and
// renormalizing the output wavefunction to 1. To do this it must try the solutions
// for different energies. The natural solution to the second degree differential equation
// is the exponential. But my boundary conditions impose 0 at both beginning and end
// of the wavefunction, so you have to try until you find such solution by finding
// where the exponential solution changes sign.
double Numerov::solve(double e_min, double e_max, double e_step)
{
    double c, x, first_step, norm, energy = 0.0;
    int n, sign;

    std::vector< std::vector<double> > potentials;
    
    // Get potentials from the main potentials (check if it's separated or not)
    if (this->potential->isSeparated()) {
        for (int i = 0; i < this->potential->getSeparatedPotentials().size(); i++) {
            potentials.push_back(this->potential->getSeparatedPotentials().at(i).getValues());
        }
    } 
    else {
        potentials.push_back(this->potential->getValues());
    }
 
    // For each separated potential values...
    for (int potential_counter = 0; potential_counter < potentials.size(); potential_counter++)
    {
        std::vector<double> &this_potential_values = potentials[potential_counter];

        // The final solution energy is the sum of each energy
        this->solutionEnergy += this->findEnergy(e_min, e_max, e_step, this_potential_values);
        this->probability     = this->findProbability();
        this->normalize();
        this->multiplyWavefunction();
    }
    return this->solutionEnergy;
}

// Applies a bisection algorith to the numerov method to find
// the energy that gives the non-trivial (non-exponential) solution
// with the correct boundary conditions
double Numerov::bisection(double e_min, double e_max, std::vector<double> &this_potential)
{
    double energy_middle, fx1, fb, fa;
    std::cout.precision(17);

    // The number of iterations that the bisection routine needs can be evaluated in advance
    int itmax = ceil(log2(e_max - e_min) - log2(err)) - 1;

    for (int i = 0; i < itmax; i++)
    {
        energy_middle = (e_max + e_min) / 2.0;

        this->findWavefunction(energy_middle, this_potential);
        fx1 = this->tempWavefunction[this->nbox];

        this->findWavefunction(e_max, this_potential);
        fb = this->tempWavefunction[this->nbox];

        if (std::abs(fx1) < err)
        {
            return energy_middle;
        }

        if (fb * fx1 < 0.)
        {
            e_min = energy_middle;
        }
        else
        {
            this->findWavefunction(e_min, this_potential);
            fa = this->tempWavefunction[this->nbox];

            if (fa * fx1 < 0.)
                e_max = energy_middle;
        }
    }

    std::cerr << "ERROR: Solution not found using the bisection method, " << this->tempWavefunction[this->nbox] << " > " << err << std::endl;
    return energy_middle;
}

void Numerov::printToFile()
{
    if (this->wavefunction.size() > 0) {
        std::ofstream myfile("wavefunction.dat");
        if (myfile.is_open())
        {

            for (int i = 0; i < this->wavefunction.size(); i++)
            {
                myfile << i << " " << this->wavefunction.at(i) << std::endl;
            }
            myfile.close();
        }
    }

    if (this->probability.size() > 0) {
        std::ofstream myfile("probability.dat");
        if (myfile.is_open())
        {

            for (int i = 0; i < this->probability.size(); i++)
            {
                myfile << i << " " << this->probability.at(i) << std::endl;
            }
            myfile.close();
        }
    }

}


std::vector<double> Numerov::findProbability() {
    std::vector<double> probability = this->tempWavefunction; 
    std::transform(probability.begin(), probability.end(), probability.begin(), square);
    return probability;
}

void Numerov::normalize(){
    double norm = this->trapezoidalRule(0.0, this->nbox, dx, this->probability);
    std::transform(this->tempWavefunction.begin(), this->tempWavefunction.end(), this->tempWavefunction.begin(), [norm](double value) { return value / sqrt(norm); });
}

double Numerov::findEnergy(double e_min, double e_max, double e_step, std::vector<double> &this_potential) {
    double solutionEnergy = 0;
    int sign;
    // scan energies to find when the Numerov solution is = 0 at the right extreme of the box.
    for (int n = 0; n < (e_max - e_min) / e_step; n++)
    {
        double energy = e_min + n * e_step;
        this->findWavefunction(energy, this_potential);
        double &last_wavefunction_value = this->tempWavefunction[this->nbox];

        if (fabs(last_wavefunction_value) < err)
        {
            std::cout << "Solution found" << last_wavefunction_value << std::endl;
            solutionEnergy = energy;
            break;
        }

        if (n == 0)
            sign = (last_wavefunction_value > 0) ? 1 : -1;

        // when the sign changes, means that the solution for f[nbox]=0 is in in the middle, thus calls bisection rule.
        if (sign * last_wavefunction_value < 0)
        {
            std::cout << "Bisection " << last_wavefunction_value << std::endl;
            solutionEnergy = this->bisection(energy - e_step, energy + e_step, this_potential);
            break;
        }
    }
    return solutionEnergy;
}

std::ostream& operator<<(std::ostream& stream, Numerov& solver) {

	// Print solution energy
    stream << "Solution energy: " << solver.getSolutionEnergy() << std::endl;
    
    // Print wavefunction
    if (solver.getWavefunction().size() > 0) {
        stream << "Wavefunction: " << std::endl;
        for (double x : solver.getWavefunction())
            stream << "\t" << x << std::endl;
    } else 
        stream << "Wavefunction not evaluated." << std::endl;

	// Print probability
    if (solver.getProbability().size() > 0) {
        stream << "Probability: " << std::endl;
        for (double x : solver.getProbability())
            stream << "\t" << x << std::endl;
    } else 
        stream << "Probability not evaluated." << std::endl;

    return stream;
 }

// If we have separable potentials V(a, ... ,z) = V(a)+ ... +V(z), then we have a resulting wavefunction
// that in the form W(a,...,z) = W(a) * ... * W(z). With this routine, each time a new wavefunction
// is evaluated, update the final wavefunction multiplying it with the new one.
// So, it takes a W(x) wavefunction as a parameter and multiply it with the global W(a, ... ,z)
void Numerov::multiplyWavefunction() {
    std::transform( this->wavefunction.begin(), this->wavefunction.end(), this->tempWavefunction.begin(), this->wavefunction.begin(),  std::multiplies<double>() );
}

double Numerov::getSolutionEnergy()
{
    return this->solutionEnergy;
}

std::vector<double> Numerov::getWavefunction()
{
    return this->wavefunction;
}

std::vector<double> Numerov::getProbability()
{
    return this->probability;
}