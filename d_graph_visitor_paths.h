#ifndef D_GRAPH_VISITOR_PATHS_H_
#define D_GRAPH_VISITOR_PATHS_H_

#include "d_graph_datatype.h"
#include "d_graph_constants.h"

int d_graph_BFS_path(const d_graph_t graph, 
					  int from,
					  int to,
				  	  int **v_path,
				  	  int *path_size,
               		  d_graph_neimode_t mode);
int d_graph_DFS_path(const d_graph_t graph, 
					  int from,
					  int to,
				  	  int **v_path,
				  	  int *path_size,
               		  d_graph_neimode_t mode);

int d_graph_get_shortest_path_dijkstra(const d_graph_t graph,
							        int from,
							        int to,
							        int **v_path,
							        int *path_size,
							        double *cost,
							        d_graph_w_mode_t w_mode,
							        d_graph_neimode_t mode);

int d_graph_get_shortest_path(d_graph_t graph,
							   int from,
						       int to,
						       int **v_path,
						       int *path_size,
						       d_graph_neimode_t mode);

#endif  // D_GRAPH_VISITOR_PATHS_H_