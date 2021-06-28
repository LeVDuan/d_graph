#ifndef D_GRAPH_INTERFACE_H_
#define D_GRAPH_INTERFACE_H_
#include "d_graph_datatype.h"

void d_graph_add_Vertice(d_graph_t graph, int id, char* name);
char *d_graph_get_Vertice_name(d_graph_t graph, int id);
int d_graph_get_Vertice_id(d_graph_t graph, char *name);

int d_graph_is_directed(const d_graph_t graph);

int d_graph_Is_Edge(d_graph_t graph, int v1, int v2);
void d_graph_add_Edge(d_graph_t graph, int v1, int v2);
void d_graph_add_Edge_weight(d_graph_t graph, int v1, int v2, double w);

int d_graph_get_ecount(const d_graph_t graph);
double d_graph_get_weight(const d_graph_t graph, int v1, int v2);

int d_graph_neighbors(const d_graph_t graph,
                     int **neis,
                     int vid,
                     int *num_neis,
                     d_graph_neimode_t mode);

int d_graph_degree_one(const d_graph_t graph, 
                        int v, 
                        int** output, 
                        d_graph_neimode_t mode);

void d_graph_print_out_put(d_graph_t const graph,int* output, int size);
void d_graph_print_edges(d_graph_t const graph);
void d_graph_print_e_w(d_graph_t const graph);
void d_graph_drop(d_graph_t *graph);
#endif  // D_GRAPH_INTERFACE_H_