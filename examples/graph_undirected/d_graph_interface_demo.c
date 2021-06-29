#include "d_graph.h"

int main(int argc, char const *argv[])
{
	printf("Graph interface demo:\n");

	d_graph_t g = d_graph_create(D_GRAPH_UNDIRECTED);
	// Tạo đồ thị có hướng như trong ảnh graph_undirected_demo.png
	d_graph_add_Vertice(g, 1, "V1");
	d_graph_add_Vertice(g, 2, "V2");
	d_graph_add_Vertice(g, 3, "V3");
	d_graph_add_Vertice(g, 4, "V4");
	d_graph_add_Vertice(g, 5, "V5");
	d_graph_add_Vertice(g, 6, "V6");
	d_graph_add_Vertice(g, 7, "V7");

	d_graph_add_Edge_weight(g,1, 2, 2);
	d_graph_add_Edge_weight(g,1, 3, 3);
	d_graph_add_Edge_weight(g,1, 4, 1);

	d_graph_add_Edge_weight(g,2, 3, 2);
	d_graph_add_Edge_weight(g,2, 6, 3);

	d_graph_add_Edge_weight(g,3, 4, 1);
	d_graph_add_Edge_weight(g,3, 6, 5);
	d_graph_add_Edge_weight(g,3, 5, 4);
	d_graph_add_Edge_weight(g,3, 7, 6);

	d_graph_add_Edge_weight(g,4, 5, 2);

	d_graph_add_Edge_weight(g,5, 7, 7);

	d_graph_add_Edge_weight(g,6, 7, 4);

	//interface:
	d_graph_print(g);

	d_graph_print_e_w(g);
	d_graph_print_matrix(g);
	d_graph_drop(&g);
	return 0;
}