#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

const int NUM_NODES = 1000;
const int NUM_TRIALS = 10;
const int MAX_CONNECT = NUM_NODES / 2;

double *clustering_coefficient = (double *)calloc(NUM_NODES, sizeof(double));

//Abandoned
//calculate the number of neighbors for a given node
int Neighbors(int **graph, int node)
{
	int count = 0;
	for (int i = 0; i < NUM_NODES; i++)
	{
		if (graph[node][i] == 1)
		{
			count++;
		}
	}
	return count;
}

// Create a matrix with dimensions on heap
// returns a 2D pointer to the matrix
int **MatrixAllocation(int rows, int cols)
{
	int **mat = (int **)malloc(rows * sizeof(int *));
	for (int i = 0; i < rows; i++)
	{
		mat[i] = (int *)calloc(cols, sizeof(int));
	}
	return mat;
}

int main()
{
	ofstream node_info, general_info;
	node_info.open("nodes.dat");
	general_info.open("average.dat");

	for (int connectivity = 1; connectivity <= MAX_CONNECT; ++connectivity)
	{
		int num_sides = NUM_NODES * connectivity;
		for (int t = 0; t < NUM_TRIALS; ++t)
		{
			//initialize randomizer
			srand(time(NULL));

			//create the random graph
			int **graph = MatrixAllocation(NUM_NODES, NUM_NODES);
			for (int i = 0; i < num_sides; i++)
			{
				int node1 = rand() % NUM_NODES;
				int node2 = rand() % NUM_NODES;
				graph[node1][node2] = 1;
				graph[node2][node1] = 1;
			}

			//calculate clustering coefficient for the nodes
			double average = 0.0;
			for (int i = 0; i < NUM_NODES; ++i)
			{
				double count = 0.0;
				double neighbors = 0.0;

				for (int j = 0; j < NUM_NODES; j++)
				{
					if (graph[i][j] == 1)
					{
						neighbors += 1.0;
						for (int k = 0; k < NUM_NODES; k++)
						{
							if (graph[j][k] == 1)
							{
								count += 2.0;
							}
						}
					}
				}
				if (neighbors < 2)
				{
					clustering_coefficient[i] = 0;
					continue;
				}
				double full_edges = neighbors * (neighbors - 1);
				clustering_coefficient[i] = count / full_edges;
				average += clustering_coefficient[i] / NUM_NODES;
			}
			//output for clustering coefficient
			node_info << connectivity << endl;
			for (int i = 0; i < NUM_NODES; i++)
			{
				node_info << clustering_coefficient[i] << " ";
			}
			node_info << endl;
			general_info << connectivity << " " << average << endl;

			free(graph);
		}
	}
	return 0;
}