#include "d_graph_interface.h"
#include <string.h>
#include <ctype.h>

/**
 * \function `d_graph_add_Vertice`
 * Thêm đỉnh vào đồ thị.
 - `graph` đồ thị đầu vào
 - `id` id của đỉnh 
 - `name` tên của đồ thị
 * \example examples/
 */
void d_graph_add_Vertice(d_graph_t graph, int id, char* name){
	JRB node = jrb_find_int(graph->id_to_vertices, id);
	if(node == NULL)
	{
		jrb_insert_int(graph->id_to_vertices, id, new_jval_s(strdup(name)));
		jrb_insert_str(graph->vertices_to_id, name, new_jval_i(id));
	}
}

/**
 * \function `d_graph_add_Edge`
 * Thêm cạnh vào đồ thị.
 - `graph` đồ thị đầu vào
 - `v1`, `v2` id của đỉnh
 * \example examples/
 */
void d_graph_add_Edge(d_graph_t graph, int v1, int v2){
	JRB node, tree;
	if(!d_graph_Is_Edge(graph, v1, v2))
	{
		node = jrb_find_int(graph->edges, v1);
		if(node == NULL){
			tree = make_jrb();
			jrb_insert_int(graph->edges, v1, new_jval_v(tree));
			d_graph_vcount(graph)++;
		}
		else {
			tree = (JRB) jval_v(node->val);
		}
		jrb_insert_int(tree, v2, new_jval_d(D_GRAPH_WEIGHT_DEFAULT));

		//tạo luôn danh sách cho kề cho đỉnh v2
		node = jrb_find_int(graph->edges, v2);
		if(node == NULL){
			tree = make_jrb();
			jrb_insert_int(graph->edges, v2, new_jval_v(tree));
			d_graph_vcount(graph)++;
		}

		//xét đồ thị vô hướng để tạo cặp cạnh có chiều ngược lại 
		if(!d_graph_is_directed(graph))
		{
			node = jrb_find_int(graph->edges, v2);
			tree = (JRB) jval_v(node->val);
			jrb_insert_int(tree, v1, new_jval_i(D_GRAPH_WEIGHT_DEFAULT));
		}
	}
}

/**
 * \function `d_graph_add_Edge_weight`
 * Thêm cạnh vào đồ thị với trọng số cạnh.
 * Nếu đã có cạnh thì chỉ gán trọng số cho cạnh đó
 - `graph` đồ thị đầu vào
 - `v1`, `v2` id của đỉnh
 - `w` trọng số cạnh (v1,v2)
 * \example examples/
 */
void d_graph_add_Edge_weight(d_graph_t graph, int v1, int v2, double w){

	if(!d_graph_Is_Edge(graph, v1, v2)){
		d_graph_add_Edge(graph,v1,v2);
	}

	JRB node = jrb_find_int(graph->edges, v1);
	JRB tree = (JRB) jval_v(node->val);
	JRB find = jrb_find_int(tree, v2);
	find->val = new_jval_d(w);
	
	if (!d_graph_is_directed(graph))
	{
		JRB node = jrb_find_int(graph->edges, v2);
		JRB tree = (JRB) jval_v(node->val);
		JRB find1 = jrb_find_int(tree, v1);
		find1->val = new_jval_d(w);
	}
}


/**
 * \function `d_graph_Is_Edge`
 * kiểm tra tồn tại cạnh (v1,v2) hay không
 - `graph` đồ thị đầu vào
 - `v1`, `v2` id của đỉnh 
 - \return 1 khi tồn tại đỉnh ngược lại trả về 0
 * \example examples/
 */
int d_graph_Is_Edge(const d_graph_t graph, int v1, int v2){
	JRB node = jrb_find_int(graph->edges, v1);
	if(node == NULL){
		return 0;
	}
	else {
		JRB tree = (JRB) jval_v(node->val);
		if(jrb_find_int(tree, v2) == NULL){
			return 0;
		}
		else {
			return 1;
		}
	}
}

/**
 * \function `d_graph_get_Vertice_name`
 * Lấy name đỉnh khi biết id của nó.
 - `graph` đồ thị đầu vào
 - `id` tên của đỉnh 
 - \return con trỏ chuỗi name của đỉnh
 * \example examples/
 */
char *d_graph_get_Vertice_name(const d_graph_t graph, int id){
	JRB node = jrb_find_int(graph->id_to_vertices, id);
	if(node == NULL){
		return NULL;
	}
	else {
		return jval_s(node->val);
	}
}

/**
 * \function `d_graph_get_Vertice_id`
 * Lấy id đỉnh khi biết tên của nó.
 - `graph` đồ thị đầu vào
 - `name` tên của đỉnh 
 - \return id của đỉnh
 * \example examples/
 */
int d_graph_get_Vertice_id(const d_graph_t graph, char *name){
	JRB node = jrb_find_str(graph->vertices_to_id, name);
	if(node == NULL){
		return -1;
	}
	else {
		return jval_i(node->val);
	}
}

// Trả về số lượng cạnh của đồ thị graph
int d_graph_get_ecount(const d_graph_t graph){
	int ecount = 0;
	JRB cur, cur2, tree, visited = make_jrb();
	if(d_graph_is_directed(graph)){
		jrb_traverse(cur, graph->edges)
		{
				tree = (JRB) jval_v(cur->val);
				jrb_traverse(cur2, tree)
				{
					ecount++;
				}
		}
	}
	else{
		jrb_traverse(cur, graph->edges)
		{
				tree = (JRB) jval_v(cur->val);
				jrb_traverse(cur2, tree)
				{
					JRB node = jrb_find_int(visited,jval_i(cur2->key));
					if( !(node != NULL &&  jval_i(node->key) == jval_i(cur2->key) ) )
					{
						jrb_insert_int(visited,jval_i(cur->key),cur2->key);
						ecount++;
					}
				}
		}
	}
	jrb_free_tree(visited);
	return ecount;
}

// Trả về số trọng số cạnh (v1, v2)
double d_graph_get_weight(const d_graph_t graph, int v1, int v2){
	if(!d_graph_Is_Edge(graph, v1, v2)){
		return 0;
	}
	JRB node = jrb_find_int(graph->edges, v1);
	JRB tree = (JRB) jval_v(node->val);
	JRB find = jrb_find_int(tree, v2);
	return jval_d(find->val);
}

/**
 * \function `d_graph_print_matrix`
 * In ma trận đỉnh kề.
 - `graph` đồ thị đầu vào
 * \example examples/
 */
void d_graph_print_matrix(const d_graph_t graph){
	int size = d_graph_vcount(graph), i = 0, j, index_to_vid[size];

	//Tạo bảng tra cứu id đỉnh đồ thị bằng index tăng từ 0 -> số lượng đỉnh
	JRB cur;
	jrb_traverse(cur, graph->edges)
	{
		index_to_vid[i] = jval_i(cur->key);
		i++;
	}
	//In Ma trận (size x size) với size là số lượng đỉnh
	printf("Graph's Matrix(%dx%d):\n  ",size,size);
	for (i = 0; i < size; ++i)
	{
		printf("%d ",index_to_vid[i]);
	} 	printf("\n");
	for (i = 0; i < size+1; ++i)
	{
		printf("--");
	} printf("\n");
	for (i = 0; i < size; ++i)
	{
		printf("%d ",index_to_vid[i]);
		for (j = 0; j < size; ++j)
		{
			if(d_graph_Is_Edge(graph, index_to_vid[i], index_to_vid[j]))
			{
				printf("1|");
			}
			else{
				printf("0|");
			}
		} printf("\n");
	}
}

/**
 * \function `d_graph_degree_one`
 * Tìm bậc của đỉnh.
 - `graph` đồ thị đầu vào
 - `v` đỉnh cần tìm bậc
 - `output` địa chỉ danh sách các đỉnh là hàng xóm
 - `mode` Một hằng số xác định cách sử dụng hướng của cạnh
 					CGRAPH_OUT bậc ra,
   				CGRAPH_IN  bậc vào,
   				sCGRAPH_ALL bỏ qua hướng của cạnh.
 - \return bậc tương ứng của đỉnh
 * \example examples/
 */
int d_graph_degree_one(const d_graph_t graph, int v, int** output, d_graph_neimode_t mode){
	JRB find_v = jrb_find_int(graph->edges,v);
	if (find_v == NULL) {
    	printf("cannot get degree!\n");
    	return 0;
  	}
	if (mode != D_GRAPH_OUT && mode != D_GRAPH_IN && mode != D_GRAPH_ALL) {
  	printf("cannot get degree!\n");
  	return 0;
	}

	int index = 0;
	int *result;
	result = (int *)malloc(d_graph_vcount(graph) * sizeof(int));
	if(result == NULL)
	{
		printf("Not enough memory for output!\n");
		return 0;
	}
	JRB tree, cur;
	if(mode == D_GRAPH_IN){
		jrb_traverse(cur, graph->edges)
		{
			tree = (JRB) jval_v(cur->val);
			if(jrb_find_int(tree, v))
			{
				result[index] = jval_i(cur->key);
				index++;
			}
		}
	}
	if(mode == D_GRAPH_OUT){
		cur = jrb_find_int(graph->edges, v);
		if(cur == NULL) {
			return 0;
		}
		else {
			tree = (JRB) jval_v(cur->val);
			jrb_traverse(cur, tree)
			{
				result[index] = jval_i(cur->key);
				index++;
			}
		}
	}
	if(mode == D_GRAPH_ALL){
		if(!d_graph_is_directed(graph)){
			cur = jrb_find_int(graph->edges, v);

			if(cur == NULL) {
				return 0;
			}
			else {
				tree = (JRB) jval_v(cur->val);
				jrb_traverse(cur, tree)
				{
					result[index] = jval_i(cur->key);
					index++;
				}
			}
		}

		else{
			jrb_traverse(cur, graph->edges)
			{
				tree = (JRB) jval_v(cur->val);
				if(jrb_find_int(tree, v))
				{
					result[index] = jval_i(cur->key);
					index++;
				}
			}
			cur = jrb_find_int(graph->edges, v);
			if(cur == NULL) {
				return 0;
			}
			else {
				tree = (JRB) jval_v(cur->val);
				jrb_traverse(cur, tree)
				{
					result[index] = jval_i(cur->key);
					index++;
				}
			}
		}
		
	}
	*output = result;
	return index;
}

/**
 * \\function `d_graph_neighbors` 
 * trả về 1 nếu thành công và về 0 nếu ngược lại, 
 * con trỏ num_neis chứa số lượng hàm xóm, 
 * danh sách kiểu int neis chứa id các đỉnh hàng xóm
*/
int d_graph_neighbors(const d_graph_t graph,
                     int **neis,
                     int vid,
                     int *num_neis,
                     d_graph_neimode_t mode){
	const int node = vid;
	JRB find_vid = jrb_find_int(graph->edges, vid);
  if (find_vid == NULL) {
    printf("Cannot get neighbors\n");
    return 0;
  }
  if (mode != D_GRAPH_OUT && mode != D_GRAPH_IN && mode != D_GRAPH_ALL) {
    printf("Cannot get neighbors\n");
    return 0;
  }
  if ( !graph->directed) {
      mode = D_GRAPH_ALL;
  }

  JRB cur, tree;
  int *result = (int*)malloc(d_graph_vcount(graph)*sizeof(int));
  int count = 0;

  if(mode == D_GRAPH_IN){
		jrb_traverse(cur, graph->edges)
		{
			tree = (JRB) jval_v(cur->val);
			if(jrb_find_int(tree, vid))
			{
				result[count] = jval_i(cur->key);
				count++;
			}
		}
	}

	if(mode == D_GRAPH_OUT){
		cur = jrb_find_int(graph->edges, vid);
		if(cur == NULL) {
			return 0;
		}
		else {
			tree = (JRB) jval_v(cur->val);
			jrb_traverse(cur, tree)
			{
				result[count] = jval_i(cur->key);
				count++;
			}
		}
	}

	if(mode == D_GRAPH_ALL){
		//trường hợp vô hướng
		if(!d_graph_is_directed(graph)){
			cur = jrb_find_int(graph->edges, vid);
			if(cur == NULL) {
				return 0;
			}
			else {
				tree = (JRB) jval_v(cur->val);
				jrb_traverse(cur, tree)
				{
					result[count] = jval_i(cur->key);
					count++;
				}
			}
		}
		//trường hợp có hướng
		else{
			jrb_traverse(cur, graph->edges)
			{
				tree = (JRB) jval_v(cur->val);
				if(jrb_find_int(tree, vid))
				{
					result[count] = jval_i(cur->key);
					count++;
				}
			}
			cur = jrb_find_int(graph->edges, vid);
			if(cur == NULL) {
				return 0;
			}
			else {
				tree = (JRB) jval_v(cur->val);
				jrb_traverse(cur, tree)
				{
					result[count] = jval_i(cur->key);
					count++;
				}
			}
		}
	}
	*num_neis = count;
	*neis = result;
	return 1;
}

// In danh sách chứa id các đỉnh
void d_graph_print_out_put(const d_graph_t graph, int* output, int size){
	if(size < 0)
	{
		printf("Error: size is invalid!\n");
		return;
	}
	//printf("size: %d, element: ",size);
	for (int i = 0; i < size; ++i)
	{
		if(d_graph_get_Vertice_name(graph, output[i]) == NULL)
		{
			printf("%d ", output[i]);
		}
		else{
			printf("%d(%s) ", output[i], d_graph_get_Vertice_name(graph, output[i]));
		}
	}
	printf("\n");
}

//In danh sách cạnh
void d_graph_print_edges(const d_graph_t graph){
	JRB cur, cur2, tree, visited = make_jrb();
	printf("Edges: %d\nElement: ",d_graph_ecount(graph));
	if(d_graph_is_directed(graph)){
		jrb_traverse(cur, graph->edges)
		{
				tree = (JRB) jval_v(cur->val);
				jrb_traverse(cur2, tree)
				{
					printf("(%d->%d) ",jval_i(cur->key), jval_i(cur2->key));
				}
		}
	}
	else{
		jrb_traverse(cur, graph->edges)
		{
				tree = (JRB) jval_v(cur->val);
				jrb_traverse(cur2, tree)
				{
					JRB node = jrb_find_int(visited,jval_i(cur2->key));
					if( !(node != NULL &&  jval_i(node->key) == jval_i(cur2->key) ) )
					{
						printf("(%d-%d) ",jval_i(cur->key), jval_i(cur2->key));
						jrb_insert_int(visited,jval_i(cur->key),cur2->key);
					}
				}
		}
	}
	printf("\n");
	jrb_free_tree(visited);
}

// In danh sách cạnh, kèm trọng số
void d_graph_print_e_w(const d_graph_t graph){
	JRB cur,cur2 , tree, visited = make_jrb();
	printf("Edges: %d\nElement: ",d_graph_ecount(graph));
	if(d_graph_is_directed(graph)){
		jrb_traverse(cur, graph->edges)
		{
				tree = (JRB) jval_v(cur->val);
				jrb_traverse(cur2, tree)
				{
					printf("[(%d->%d): %.2f] ",jval_i(cur->key), jval_i(cur2->key), jval_d(cur2->val));
				}
		}
	}
	else{
		jrb_traverse(cur, graph->edges)
		{
				tree = (JRB) jval_v(cur->val);
				jrb_traverse(cur2, tree)
				{
					JRB node = jrb_find_int(visited,jval_i(cur2->key));
					if( !(node != NULL &&  jval_i(node->key) == jval_i(cur2->key) ) )
					{
						printf("[(%d-%d): %.2f] ",jval_i(cur->key), jval_i(cur2->key), jval_d(cur2->val));
						jrb_insert_int(visited,jval_i(cur->key),cur2->key);
					}
				}
		}
	}
	printf("\n");
	jrb_free_tree(visited);
}

// Giải phóng đồ thị
void d_graph_drop(d_graph_t *graph)
{
	d_graph_t g = *graph;
	JRB cur, tree;
	jrb_traverse(cur, g->edges)
	{
		tree = (JRB) jval_v(cur->val);
		jrb_free_tree(tree);
	}
	jrb_free_tree(g->edges);
	jrb_free_tree(g->vertices_to_id);
	jrb_free_tree(g->id_to_vertices);
	free(g);
	g = NULL;
}