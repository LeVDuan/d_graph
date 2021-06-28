#include <stdlib.h>

#include "d_graph_interface.h"
#include "d_graph_visitor_paths.h"
#include "libfdr/dllist.h"
//kiểm tra trong danh sách result_v có đỉnh t hay không
int check_has_path(int *result_v,int count, int t){
	int flag = 0;
	for (int i = 0; i < count; ++i)
	{
		if(t == result_v[i])
		{
			flag = 1;
			return flag;
		}
	}
	return flag;
}

/**
 * ``function d_graph_BFS_path``
 - Duyệt đồ thị từ bắt đầu từ đỉnh from dừng lại tại to.
   đặt to = D_GRAPH_V_DEFAULT, hàm sẽ duyệt toàn bộ đồ thị
 - Có thể dùng để tìm một đường từ một đỉnh tới một đỉnh khác, sử dụng giải thuật BFS.
 *
 - `graph` Đồ thị đầu vào, có thể có hướng hoặc vô hướng.
 - `from` id của đỉnh nguồn.
 - `to` id của đỉnh đích.
 - `v_path` địa chỉ danh sách đường đi bao gồm cả đỉnh nguồn và đích.
 - `path_size` địa chỉ để lưu chiều dài đường đi.
 - `mode` Một hằng số xác định cách sử dụng hướng của cạnh.
   trong đồ thị có hướng.
   		CGRAPH_OUT đi theo hướng của cạnh,
   		CGRAPH_IN đi theo chiều ngược lại,
   		CGRAPH_ALL bỏ qua hướng của cạnh. 
   Tham số này bị bỏ qua đối với đồ thị vô hướng.
 - return Mã lỗi.
 */
int d_graph_BFS_path(const d_graph_t graph, 
					  int from,
					  int to,
				  	  int **v_path,
				  	  int *path_size,
               		  d_graph_neimode_t mode){
	JRB find_f = jrb_find_int(graph->edges,from);
	if(to != D_GRAPH_V_DEFAULT)
	{
		JRB find_t = jrb_find_int(graph->edges,to);
		if (from < 0 || find_f == NULL || find_t == NULL) {
    		printf("Error: Invalid root and stop vertex in BFS!\n");
    		return 0;
	  	}
	}
	else if (from < 0 || find_f == NULL) {
    	printf("Error: Invalid root vertex in BFS!\n");
    	return 0;
	  }
	if (mode != D_GRAPH_OUT && mode != D_GRAPH_IN && mode != D_GRAPH_ALL) {
	   printf("Error: Invalid mode argument!\n");
	   return 0;
	}

	if (!d_graph_is_directed(graph)) {
	    mode = D_GRAPH_ALL;
	}

	JRB cur, visited = make_jrb();
	int *result_v = (int*)malloc(d_graph_vcount(graph)*sizeof(int));

	jrb_traverse(cur, graph->edges)
	{
		//gán tất cả đỉnh là chưa thăm
		jrb_insert_int(visited,jval_i(cur->key), new_jval_v(D_GRAPH_UNVISITED));
	}

	Dllist queue_src = new_dllist();
	dll_append(queue_src, new_jval_i(from));

	int v_tmp, count = 0;
	Dllist node;
	while(!dll_empty(queue_src))
	{
		//dequeue 
		node = dll_first(queue_src);
 		v_tmp = jval_i(node->val);
 		dll_delete_node(node);

 		JRB tmp = jrb_find_int(visited, v_tmp);
 		if(jval_v(tmp->val) == D_GRAPH_UNVISITED)
 		{
 			result_v[count] = v_tmp;
 			count++;
 			tmp->val = new_jval_v(D_GRAPH_VISITED);

 			if(v_tmp == to)
 			{
 				break;
 			}
 			int *neis, num_neis;
 			d_graph_neighbors(graph,
                     &neis,
                     v_tmp,
                     &num_neis,
                     mode);
 			for (int i = 0; i < num_neis; ++i)
 			{
 				JRB tmp1 = jrb_find_int(visited, neis[i]);
				if(jval_v(tmp1->val) == D_GRAPH_UNVISITED)
				{
					dll_append(queue_src,new_jval_i(neis[i]));
				}
 			}
 			free(neis);
 		}
	}

	//nếu trong danh sách duyệt không có đỉnh cần tìm -> không tìm thấy đường đi
 	if(!check_has_path(result_v,count,to)){
 		printf("Cannot get path by BFS!\n");
 		*v_path = NULL;
		*path_size = 0;
		jrb_free_tree(visited);
		free_dllist(queue_src);
		return 0;
 	}

	*v_path = result_v;
	*path_size = count;
	jrb_free_tree(visited);
	free_dllist(queue_src);
	return 1;
}

/**
 * ``function d_graph_DFS_path``
 - Tương tự hàm d_graph_BFS_path nhưng sử dụng thuật toán DFS.
 */

int d_graph_DFS_path(const d_graph_t graph, 
					  int from,
					  int to,
				  	  int **v_path,
				  	  int *path_size,
               		  d_graph_neimode_t mode){
	JRB find_f = jrb_find_int(graph->edges,from);
	if(to != D_GRAPH_V_DEFAULT)
	{
		JRB find_t = jrb_find_int(graph->edges,to);
		if (from < 0 || find_f == NULL || find_t == NULL) {
    		printf("Error: Invalid root and stop vertex in DFS!\n");
    		return 0;
	  	}
	}
	else if (from < 0 || find_f == NULL) {
    	printf("Error: Invalid root and stop vertex in DFS!\n");
    	return 0;
	  }
	if (mode != D_GRAPH_OUT && mode != D_GRAPH_IN && mode != D_GRAPH_ALL) {
	   printf("Error: Invalid mode argument!\n");
	   return 0;
	}

	if (!d_graph_is_directed(graph)) {
	    mode = D_GRAPH_ALL;
	}


	JRB cur, visited = make_jrb();
	int *result_v = (int*)malloc(d_graph_vcount(graph)*sizeof(int));

	jrb_traverse(cur, graph->edges)
	{
		//gán tất cả đỉnh là chưa thăm
		jrb_insert_int(visited,jval_i(cur->key), new_jval_v(D_GRAPH_UNVISITED));
	}

	Dllist stack_src = new_dllist();
	//push from vào stack 
	dll_append(stack_src, new_jval_i(from));

	int v_tmp, count = 0;
	Dllist node;
	while(!dll_empty(stack_src))
	{
		//pop
		node = dll_last(stack_src);
		v_tmp = jval_i(node->val);
		dll_delete_node(node);

		//kiểm tra v_tmp đã thăm hay chưa
		JRB tmp = jrb_find_int(visited, v_tmp);

 		if(jval_v(tmp->val) == D_GRAPH_UNVISITED)
 		{
 			result_v[count] = v_tmp;
 			count++;
 			tmp->val = new_jval_v(D_GRAPH_VISITED);

 			if(v_tmp == to)
 			{
 				break;
 			}
 			int *neis, num_neis;
 			d_graph_neighbors(graph,
                     &neis,
                     v_tmp,
                     &num_neis,
                     mode);
 			for (int i = 0; i < num_neis; ++i)
 			{
 				JRB tmp1 = jrb_find_int(visited, neis[i]);
				if(jval_v(tmp1->val) == D_GRAPH_UNVISITED)
				{
					dll_append(stack_src, new_jval_i(neis[i]));
				}
 			}
 			free(neis);
 		}
 	}

 	//nếu trong danh sách duyệt không có đỉnh cần tìm -> không tìm thấy đường đi
 	if(!check_has_path(result_v,count,to)){
 		printf("cannot get path by DFS!\n");
 		*v_path = NULL;
		*path_size = 0;
		jrb_free_tree(visited);
		free_dllist(stack_src);
		return 0;
 	}

  	*v_path = result_v;
	*path_size = count;
	jrb_free_tree(visited);
	free_dllist(stack_src);
	return 1;
}

// Tra cứu index trong list khi biết id của đỉnh 
int vid_to_i(int *list,int size,int vid)
{
	for (int i = 0; i < size; ++i)
	{
		if (list[i] == vid)
		{
			return i;
		}
	}
}
// Hàm lấy ra đường đi từ s đến t 
// Trả kết quả đường đi vào địa chỉ vpath, độ dài đường đi vào địa chỉ p_size
void get_vid_from_ipath(int* index_to_vid, int *p,int s,int t,int size,int *p_size, int **vpath)
{
	int reverse[size];
	int i = t, count = 0;
	do{
		reverse[count] = i;
		count ++;
		i = p[i];
	}while(i != s);
	reverse[count] = s;
	count++;
	*p_size = count;
	int path[count];
	for(int i = 0; i< count; i++)
	{
		path[i] =  index_to_vid[reverse[count-i-1]];
	}
	*vpath = path;
}

// kiểm tra trong đồ thị tồn tại hay không cạnh có trọng số âm
int check_weights(d_graph_t graph)
{
	JRB cur, cur2, tree;
	jrb_traverse(cur, graph->edges)
	{
		tree = (JRB) jval_v(cur->val);
		jrb_traverse(cur2, tree)
		{
			if ( jval_d(cur2->val) < 0 )
			{
				return 0;
			}
		}
	}
}

/**
 * ``function d_graph_get_shortest_path_dijkstra``
 - Đường đi ngắn nhất có trọng số từ một đỉnh tới một đỉnh khác.
 - Tìm một đường đi ngắn nhất có trọng số (dương) từ một đỉnh tới một
   đỉnh khác, sử dụng giải thuật Dijkstra.
 *
 - `graph` Đồ thị đầu vào, có thể có hướng hoặc vô hướng.
 - `from` id của đỉnh nguồn.
 - `to` id của đỉnh đích.
 - `v_path` địa chỉ danh sách đường đi bao gồm cả đỉnh nguồn và đích.
 - `path_size` địa chỉ để lưu chiều dài đường đi.
 - `cost` địa chỉ để lưu độ dài của đường đi tìm được.
 - `w_mode` Một hằng số xác định xem có sử dụng trọng số cạnh hiện tại của đồ thị không.
 			nếu là đồ thị vô hướng thì w_mode luôn là D_GRAPH_NOT_USE_WEIGHT.
 - `mode` Một hằng số xác định cách sử dụng hướng của cạnh.
   trong đồ thị có hướng.
   		CGRAPH_OUT đi theo hướng của cạnh,
   		CGRAPH_IN đi theo chiều ngược lại,
   		CGRAPH_ALL bỏ qua hướng của cạnh. 
   Tham số này bị bỏ qua đối với đồ thị vô hướng.
 - return Mã lỗi.
 * Độ phức tạp: O(|E|log|E|+|V|), |V| là số lượng đỉnh,
 * |E| là số lượng cạnh trong đồ thị.
 */
int d_graph_get_shortest_path_dijkstra(const d_graph_t graph,
							        int from,
							        int to,
							        int **v_path,
							        int *path_size,
							        double *cost,
							        d_graph_w_mode_t w_mode,
							        d_graph_neimode_t mode){

		if(!check_weights(graph))
		{
			printf("Error: Graph is has edge with negative weight!\n");
			return 0;
		}
// – k[v] - đã tìm được đường đi ngắn nhất từ đỉnh nguồn đến v hay chưa,
// – d[v] - khoảng cách (độ dài đường đi) từ s đến v hiện biết
// – p[v] - đỉnh đi trước đỉnh v trong đường đi tốt nhất hiện biết.
	JRB node1 = jrb_find_int(graph->edges,from);
	JRB node2 = jrb_find_int(graph->edges,to);
	if( node1 == NULL || node2 == NULL )
	{
		printf("Error: Vertices cannot founded!\n");
		return 0;
	}
	int index_to_vid[d_graph_ecount(graph)];
	int size = 0;
	JRB cur;
	//tao bang tra cuu id dinh do thi bang index tang tu 0 -> solg dinh
	jrb_traverse(cur, graph->edges)
	{
		index_to_vid[size] = jval_i(cur->key);
		size++;
	}

	int s = vid_to_i(index_to_vid,size, from), 
		t = vid_to_i(index_to_vid, size, to);

 	double d[size], k[size], min, w;
	int n, output[size], p[size], u, v;
	Dllist ptr, queue;
	JRB node;

	 for (int i = 0; i < size; ++i)
	 {
	 	d[i] = D_GRAPH_INFINITIVE_VALUE;
	 	k[i] = D_GRAPH_UNFINDED;
	 }

	d[s] = 0; p[s] = s;
	queue = new_dllist();
	for (int i = 0; i < size; i++)
	{
		dll_append(queue, new_jval_i(i));
	}

	 while(!dll_empty(queue))
	 {
		 	min = D_GRAPH_INFINITIVE_VALUE + 1;
		 	dll_traverse(ptr, queue)
		 	{
		 		v = jval_i(ptr->val);
		 		if(min > d[v])
		 		{
		 			min = d[v];
		 			node = ptr;
		 			u = v;
		 		}
		 	}
	 	k[u] = 1;
		dll_delete_node(node);

		 if( u == t ) break;

	 	// n = outdegree(g, u, output);
		int *neis;
		d_graph_neighbors(graph,
	                     &neis,
	                     index_to_vid[u],
	                     &n,
	                     mode);
		for(int i = 0; i < n; i++)
		{
			output[i] = vid_to_i(index_to_vid,size,neis[i]);
		}
	 	for (int i = 0; i < n; ++i)
	 	{
	 		v = output[i];
	 		if(k[v] == 0)
	 		{
	 			// w = getEdgeValue(g, u, v);
	 			if (w_mode == D_GRAPH_NOT_USE_WEIGHT)
	 			{
	 				w = D_GRAPH_WEIGHT_DEFAULT;
	 			}
	 			else{
	 				w = d_graph_get_weight(graph, index_to_vid[u], index_to_vid[v]);
	 			}
	 			if( d[v] > d[u] + w)
	 			{
	 				d[v] = d[u] + w;
	 				p[v] = u;
	 			}
	 		}
	 	}
	 	free(neis);
 	}
 	//nếu trong số đến t có giá trị vô cùng -> không có đường đi
	if(d[t] == D_GRAPH_INFINITIVE_VALUE)
	{
		printf("Cannot get path!\n");
		*cost = 0;
		*path_size = 0;
		*v_path = NULL;
		free_dllist(queue);
		return 0;
	}
	//lấy đường đi từ danh sách p
	get_vid_from_ipath(index_to_vid,p,s,t,size,path_size,v_path);
	*cost = d[t];
	free_dllist(queue);
	return 1;
}

/**
 * ``function d_graph_get_shortest_path``
 - Đường đi ngắn nhất có (không sử dụng đến trọng số cạnh) từ một đỉnh tới một đỉnh khác.
 - Là một trường hợp của hàm d_graph_get_shortest_path_dijkstra với chế độ D_GRAPH_NOT_USE_WEIGHT.
*/
int d_graph_get_shortest_path(d_graph_t graph,
							   int from,
						       int to,
						       int **v_path,
						       int *path_size,
						       d_graph_neimode_t mode){
	double cost;
	return d_graph_get_shortest_path_dijkstra(graph,
							        	from,
							       		to,
								        v_path,
								        path_size,
								        &cost,
								        D_GRAPH_NOT_USE_WEIGHT,
								        mode);
}