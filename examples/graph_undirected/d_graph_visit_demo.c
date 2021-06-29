#include "d_graph.h"
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	printf("Graph visit example:\n");

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

	int *v_path, path_size;

	// Duyệt BFS hết đồ thị
	d_graph_BFS_path(g, 1, D_GRAPH_V_DEFAULT, &v_path, &path_size, D_GRAPH_ALL);
	printf("BFS: ");
	d_graph_print_out_put(g, v_path, path_size);

	// Duyệt BFS từ đỉnh 3 dừng tại 6
	if(d_graph_BFS_path(g, 3, 6, &v_path, &path_size, D_GRAPH_ALL)){
		printf("BFS from 3 to 6:");
		d_graph_print_out_put(g, v_path, path_size);
	}

	// Duyệt DFS hết đồ thị
	d_graph_DFS_path(g, 1, D_GRAPH_V_DEFAULT, &v_path, &path_size, D_GRAPH_ALL);
	printf("DFS: ");
	d_graph_print_out_put(g, v_path, path_size);

	// Duyệt DFS từ đỉnh 3 dừng tại 6
	if(d_graph_DFS_path(g, 3, 6, &v_path, &path_size, D_GRAPH_ALL)){
		printf("DFS from 3 to 6: ");
		d_graph_print_out_put(g, v_path, path_size);
	}

	// Tìm đường đi ngắn nhất từ 2 đến 4
	if(d_graph_get_shortest_path(g, 2, 4, &v_path, &path_size, D_GRAPH_ALL))
	{
		printf("Path from 2 to 4: ");
		d_graph_print_out_put(g, v_path, path_size);
	}

	double cost;
	// Tìm đường đi ngắn nhất từ 2 đến 4 bằng dijkstra
	if(d_graph_get_shortest_path_dijkstra(g, 2, 4, &v_path, &path_size, &cost, D_GRAPH_USE_WEIGHT, D_GRAPH_ALL))
	{
		printf("Path from 2 to 4 by dijkstra\nCost: %.4f, Path: ",cost);
		d_graph_print_out_put(g, v_path, path_size);
	}
	//free(v_path);
	d_graph_drop(&g);
	return 0;
}