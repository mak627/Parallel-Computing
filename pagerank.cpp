#include "page_rank.h"

#include <stdlib.h>
#include <cmath>
#include <omp.h>
#include <utility>

#include <stdio.h>
#include <iostream>

#include "../common/CycleTimer.h"
#include "../common/graph.h"


// pageRank --
//
// g:           graph to process (see common/graph.h)
// solution:    array of per-vertex vertex scores (length of array is num_nodes(g))
// damping:     page-rank algorithm's damping parameter
// convergence: page-rank algorithm's convergence threshold
//
void pageRank(Graph g, double* solution, double damping, double convergence)
{


  // initialize vertex weights to uniform probability. Double
  // precision scores are used to avoid underflow for large graphs

  int numNodes = num_nodes(g);
  double equal_prob = 1.0 / numNodes;
  //allocate arrays to hold old and new scores for each node
  double* score_old = (double*) malloc(numNodes * sizeof(double));
  double* score_new = (double*) malloc(numNodes * sizeof(double));

  //score is distrubuted evenly at the beginning
  for (int i = 0; i < numNodes; ++i) {
    score_old[i] = equal_prob;
  }
  bool converged = false;
  
  
  /*
     CS149 students: Implement the page rank algorithm here.  You
     are expected to parallelize the algorithm using openMP.  Your
     solution may need to allocate (and free) temporary arrays.

     Basic page rank pseudocode is provided below to get you started:

     // initialization: see example code above
     score_old[vi] = 1/numNodes;

     while (!converged) {

       // compute score_new[vi] for all nodes vi:
       score_new[vi] = sum over all nodes vj reachable from incoming edges
                          { score_old[vj] / number of edges leaving vj  }
       score_new[vi] = (damping * score_new[vi]) + (1.0-damping) / numNodes;

       score_new[vi] += sum over all nodes v in graph with no outgoing edges
                          { damping * score_old[v] / numNodes }

       // compute how much per-node scores have changed
       // quit once algorithm has converged

       global_diff = sum over all nodes vi { abs(score_new[vi] - score_old[vi]) };
       converged = (global_diff < convergence)
     }
   */
    while(!converged){
        // compute score_new[vi] for all nodes vi
	double global_diff = 0.0;
	#pragma omp parallel for
	for (int i = 0; i < numNodes; ++i) {
          score_new[i] = 0.0;
          int start_edge = g->incoming_starts[i];
          int end_edge = (i == g->num_nodes - 1)
                           ? g->num_edges
                           : g->incoming_starts[i + 1];
	  int num_neighbours = end_edge - start_edge;
	  for (int neighbour = start_edge; neighbour < end_edge; neighbour++) {
            int incoming_vertex = g->incoming_edges[neighbour];
	    score_new[i] += score_old[incoming_vertex] / num_neighbours;
	  }

        // include damping
        score_new[i] = (damping * score_new[i]) + (1.0 - damping) / numNodes;
        
	/*** need to account for sink nodes i.e. nodes with no outgoing edges here ***/
	
	global_diff += std::abs(score_new[i] - score_old[i]);
        }
    converged = (global_diff < convergence);

    // swap new and old pagerank scores
    double* tmp = score_new;
    score_new = score_old;
    score_old = tmp;
    }
    for (int i = 0; i < numNodes; ++i) {
    solution[i] = score_old[i];
    }
    free(score_old);
    free(score_new);
}
