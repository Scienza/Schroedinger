import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from matplotlib import cm

base = np.loadtxt('base.dat')
probability = np.loadtxt('probability.dat')
wavefunction = np.loadtxt('wavefunction.dat')
potential = np.loadtxt('potential.dat')

ax = plt.axes(projection='3d')

X = base[:,0]
Y = base[:,1]

ax.plot3D(X, Y, potential[:])
#ax.plot3D(X, Y, probability[:])
ax.plot3D(X, Y, wavefunction[:])

plt.show()

plt.savefig('graph.png')