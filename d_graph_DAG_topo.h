#ifndef D_GRAPH_DAG_TOPO_H_
#define D_GRAPH_DAG_TOPO_H_
#include "d_graph_datatype.h"

int d_graph_Is_DAG(const d_graph_t graph);
int d_graph_topological_sorting(const d_graph_t graph,
                               int **output,
                               int *res,
                               d_graph_neimode_t mode);
#endif  // D_GRAPH_DAG_TOPO_H_