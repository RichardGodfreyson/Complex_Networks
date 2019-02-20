import numpy as np
import matplotlib.pyplot as plt

clu_coeffs = []
with open('nodes.dat', 'r') as f:
    for line in f:
        if len(line.split()) == 1:
            continue
        clu_coeffs = list(map(float, line.split())) + clu_coeffs

plt.hist(clu_coeffs, bins=100)
plt.show()
