#ifndef D_GRAPH_CONSTANTS_H_
#define D_GRAPH_CONSTANTS_H_

typedef enum {
  D_GRAPH_OUT = 1,
  D_GRAPH_IN = 2,
  D_GRAPH_ALL = 3
} d_graph_neimode_t;

typedef enum {
  D_GRAPH_UNDIRECTED = 0,
  D_GRAPH_DIRECTED = 1
} d_graph_directed_t;

typedef enum {
  D_GRAPH_UNVISITED = 0,
  D_GRAPH_VISITED = 1
} d_graph_visited_t;

typedef enum {
  D_GRAPH_UNFINDED = 0,
  D_GRAPH_FINDED = 1
} d_graph_finded_t;

typedef enum {
  D_GRAPH_NOT_USE_WEIGHT = 0,
  D_GRAPH_USE_WEIGHT = 1
} d_graph_w_mode_t;

#define D_GRAPH_WEIGHT_DEFAULT 1
#define D_GRAPH_V_DEFAULT -1
#define D_GRAPH_INFINITIVE_VALUE 100000000

#define d_graph_is_directed(graph) graph->directed

#define d_graph_vcount(graph)  graph->vertices_num
#define d_graph_ecount(graph)  d_graph_get_ecount(graph)

#endif  // D_GRAPH_CONSTANTS_H_