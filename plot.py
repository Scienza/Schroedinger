#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

base = np.loadtxt('base.dat')
wave = np.loadtxt('wavefunction.dat')
potential = np.loadtxt('potential.dat')
#probability = np.loadtxt('probability.dat')

#plt.plot(probability[:,0], probability[:,1], 'b')
plt.plot(base[:], wave[:], 'r') 
plt.plot(base[:], potential[:], 'g')
plt.gca().legend(('Wavefunction','Potential'))
plt.savefig('graph.png')
plt.show()
