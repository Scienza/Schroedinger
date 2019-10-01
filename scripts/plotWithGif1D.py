#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
import os
import imageio

# We want to create a graph for each change in the wavefunction,
list_of_wavefunctions = os.listdir('wavefunctions')

number = 0
for wavefile in list_of_wavefunctions:
    plt.figure()
    base = np.loadtxt('base.dat')
    wave = np.loadtxt(os.path.join('wavefunctions', wavefile))
    potential = np.loadtxt('potential.dat')
    #probability = np.loadtxt('probability.dat')
    #plt.plot(probability[:,0], probability[:,1], 'b')
    plt.title('Iteration {}'.format(number))
    plt.plot(base[:], wave[:], 'r') 
    plt.plot(base[:], potential[:], 'g')
    plt.gca().legend(('Wavefunction','Potential'))
    number = number + 1
    plt.savefig('graphs/{}'.format(number))


png_dir = 'graphs'
images = []
filenames = [int(os.path.splitext(complete_name)[0]) for complete_name in os.listdir(png_dir)]
filenames.sort()

for file_name in filenames:
        file_path = os.path.join(png_dir, "{}.png".format(file_name))
        images.append(imageio.imread(file_path))
imageio.mimsave(os.path.join('graphs', 'result.gif'), images, fps="1.5")