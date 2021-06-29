#ifndef D_GRAPH_INTERFACE_H_
#define D_GRAPH_INTERFACE_H_
#include "d_graph_datatype.h"

void d_graph_add_Vertice(d_graph_t graph, int id, char* name);
void d_graph_add_Edge(d_graph_t graph, int v1, int v2);
void d_graph_add_Edge_weight(d_graph_t graph, int v1, int v2, double w);

int d_graph_Is_Edge(const d_graph_t graph, int v1, int v2);

char *d_graph_get_Vertice_name(const d_graph_t graph, int id);
int d_graph_get_Vertice_id(const d_graph_t graph, char *name);
int d_graph_get_ecount(const d_graph_t graph);
double d_graph_get_weight(const d_graph_t graph, int v1, int v2);

void d_graph_print_matrix(const d_graph_t graph);

int d_graph_neighbors(const d_graph_t graph,
                     int **neis,
                     int vid,
                     int *num_neis,
                     d_graph_neimode_t mode);

int d_graph_degree_one(const d_graph_t graph, 
                        int v, 
                        int** output, 
                        d_graph_neimode_t mode);

void d_graph_print_out_put(const d_graph_t graph,int* output, int size);
void d_graph_print_edges(const d_graph_t graph);
void d_graph_print_e_w(const d_graph_t graph);
void d_graph_drop(d_graph_t *graph);
#endif  // D_GRAPH_INTERFACE_H_