#include "d_graph.h"

int main(int argc, char const *argv[])
{
	printf("dag examples\n");

	d_graph_t g = d_graph_create(D_GRAPH_DIRECTED);

	d_graph_add_Vertice(g, 1, "v1");
	d_graph_add_Vertice(g, 2, "v2");
	d_graph_add_Vertice(g, 3, "v3");
	d_graph_add_Vertice(g, 4, "v4");

	d_graph_add_Edge(g, 1, 2);
	d_graph_add_Edge(g, 2, 3);
	d_graph_add_Edge(g, 3, 4);
	d_graph_add_Edge(g, 4, 1);

	if(d_graph_Is_DAG(g)){
		printf("is dag\n");
	}
	else{
		printf("is not dag\n");
	}
	d_graph_drop(&g);
	return 0;
}