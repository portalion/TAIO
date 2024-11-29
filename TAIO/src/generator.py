import numpy as np
import os
import random

out_name = 'test2.txt'
sizes = [3, 4, 5, 6, 7, 8, 9, 10]

file_path = os.path.join('..', 'data', out_name)
with open(file_path, 'w') as file:
    file.write(f'{len(sizes)}\n')
    for size in sizes:
        prob = random.uniform(0, 1)
        adj_matrix = np.random.rand(size, size)
        idx = adj_matrix >= prob
        adj_matrix[idx] = 1
        adj_matrix[~idx] = 0
        np.fill_diagonal(adj_matrix, 0)
        adj_matrix = adj_matrix.astype(int).tolist()
        adj_matrix = '\n'.join([' '.join([str(y) for y in x]) for x in adj_matrix])
        file.write(str(size))
        file.write('\n')
        file.write(adj_matrix)
        file.write('\n\n')
    