#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

wave = np.loadtxt('wavefunction.dat')
potential = np.loadtxt('potential.dat')
#probability = np.loadtxt('probability.dat')

#plt.plot(probability[:,0], probability[:,1], 'b')
plt.plot(wave[:,0], wave[:,1], 'r') 
plt.plot(potential[:,0], potential[:,1], 'g')
plt.gca().legend(('Wavefunction','Potential'))
plt.savefig('graph.png')
