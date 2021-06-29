#include "d_graph_constructors.h"
#include <stdio.h>

/**
 - function `cgraph_create_empty`
   Tạo một đồ thị rỗng .
 - directed Kiểu d_graph_directed_t xác định tính chất có hướng của đồ thị.
 * Các giá trị được hỗ trợ là:
 *    	D_GRAPH_DIRECTED   Đồ thị có hướng.
 *    	D_GRAPH_UNDIRECTED Đồ thị vô hướng.
 - \return NULL nếu không thể tạo đồ thị, hoặc con trỏ đồ thị mới
 * được tạo.
 */

d_graph_t d_graph_create(d_graph_directed_t directed){

	if(directed != D_GRAPH_UNDIRECTED && directed != D_GRAPH_DIRECTED)
	{
		printf("Error: invalid directed!\n");
		return NULL;
	}
	d_graph_t graph = malloc(sizeof(struct d_graph_s));
	graph->vertices_num = 0;
	graph->directed = directed;

	graph->edges = make_jrb();
	graph->vertices_to_id = make_jrb();
	graph->id_to_vertices = make_jrb();
	return graph;
}

void d_graph_print(const d_graph_t graph){
	JRB cur;
	if(graph->directed == D_GRAPH_UNDIRECTED)
	{
		printf("GRAPH undirected\n");
	}else {
		printf("GRAPH directed\n");
	}
	printf("Vertices:%d\nElement: ",d_graph_vcount(graph));

	jrb_traverse(cur, graph->vertices_to_id)
	{
		printf("%d(%s) ",jval_i(cur->val),jval_s(cur->key));
	}
	printf("\n");
	d_graph_print_edges(graph);
}