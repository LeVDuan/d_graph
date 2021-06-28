#include "d_graph_DAG_topo.h"
#include "libfdr/dllist.h"
/**
 * function ``d_graph_Is_DAG``
 - Kiểm tra liệu một đồ thị có hướng có là DAG hay không.
 - Một đồ thị có hướng không chứa chu trình được gọi là DAG (Directed Acyclic Graph).

 - `graph` Đồ thị đầu vào.
 - \return 1 nếu đồ thị là DAG, 0 nếu ngược lại.
 *
 * Độ phức tạp: O(|V|+|E|), trong đó |V| và |E| là số lượng đỉnh 
   và số lượng cạnh trong đồ thị ban đầu.
 - sử dụng d_graph_topological_sorting() để lấy một trật tự topo nếu có của một đồ thị có hướng.
 */

int d_graph_Is_DAG(const d_graph_t graph){

	if (!d_graph_is_directed(graph)) {
		printf("Error: Graph undirected cannot check DAG (Directed acyclic graph)!\n");
    	return 0;
  	}
  	int v_count  = d_graph_vcount(graph);
  	int *neis, node, nei, v_left;
  	JRB cur ,degree_list = make_jrb();
  	Dllist queue = new_dllist();

  	//lấy bậc ra của tất cả đỉnh, lưu vào degree_list
  	jrb_traverse(cur, graph->edges)
  	{
  		int *output;
  		int n = d_graph_degree_one(graph,jval_i(cur->key),&output, D_GRAPH_OUT);
  		jrb_insert_int(degree_list, jval_i(cur->key), new_jval_i(n));
  		free(output);
  	}
  	v_left = v_count;

    // Kiểm tra xem chúng ta có đỉnh không có cạnh đi ra hay không
  	jrb_traverse(cur, degree_list)
  	{
  		//jval_i(cur->val) là bậc ra của đỉnh cur->key
  		if( jval_i(cur->val)  == 0 )
  		{
  			//enqueue
  			dll_append(queue,cur->key);
  		}
  	}
 
   	// Xử lý và xóa các đỉnh không có cạnh đi ra 

  	while(!dll_empty(queue))
  	{
  		//dequeue 
		Dllist q_node = dll_first(queue);
 		node = jval_i(q_node->val);
 		dll_delete_node(q_node);

 		//Lấy bậc ra của đỉnh node và giảm đi 1 
 		cur = jrb_find_int(degree_list, node);
 		cur->val = new_jval_i(-1);
 		v_left --;


	    // Lấy các láng giềng đi vào và giảm bậc ra một đơn vị
	 	int num_neis;
	 	d_graph_neighbors(graph,&neis,node,&num_neis,D_GRAPH_IN);
	 	for (int i = 0; i < num_neis; ++i)
	 	{
	 		nei = neis[i];

	 		cur = jrb_find_int(degree_list, nei);
	 		cur->val = new_jval_i( jval_i(cur->val) - 1 ); 
 			if(jval_i(cur->val) == 0)
 			{
 				//enqueue
 				dll_append(queue, new_jval_i(nei));
 			}
	 	}
  	}
	return (v_left == 0);
}

/**
 * function ``d_graph_topological_sorting``
 - Sắp xếp các đỉnh của một đồ thị theo thứ tự topo.
 - Trật tự topo của các đỉnh của một đồ thị có hướng không chứa chu
   trình (DAG) là một trật tự tuyến tính trong đó tất cả các đỉnh đều
   xuất hiện trước các đỉnh có cạnh nối với nó. Tất cả các DAG đều có
   ít nhất một trật tự topo, và có thể có nhiều trật tự topo khác
   nhau. Hàm này trả về một trật tự topo nếu có của đồ thị. Nếu đồ
   thị có chứa ít nhất một chu trình, một phần của trật tự topo được
   trả về và một cảnh báo được đưa ra.
 *
 - `graph` Đồ thị đầu vào.
 - `output` Con trỏ tới một danh sách, danh sách đỉnh được sắp xếp
   theo trật tự topo sẽ được lưu ở đây.
 - `res` Con trỏ kiể int, lưu độ dài danh sách output.
 - `mode` Tùy chỉnh hướng cho các cạnh.
 * Đối với CGRAPH_OUT: trật tự đảm bảo rằng tất cả các đỉnh đều xuất hiện 
   						trước các đỉnh mà nó có cạnh đi tới đó, như vậy các đỉnh
   						không có cạnh đi tới sẽ xuất hiện đầu tiên. 
 * Đối với CGRAPH_IN: quan hệ gần như ngược lại: Mỗi đỉnh đều xuất hiện 
  				 	  trước các nút có cạnh đi tới nó. Các đỉnh không có 
 					  cạnh đi tới xuất hiện đầu tiên.
 * \return Mã lỗi.
 *
 * Độ phức tạp: O(|V|+|E|), trong đó |V| và |E| là số lượng đỉnh và
   cạnh trong đồ thị đầu vào ban đầu.
 */

int d_graph_topological_sorting(const d_graph_t graph,
                               int **output,
                               int *res,
                               d_graph_neimode_t mode){

	d_graph_neimode_t degree_mode;
	if (mode == D_GRAPH_ALL || !d_graph_is_directed(graph)) {
	    printf("Error: Topological sorting does not make sense for undirected graphs\n");
	    return 0;
	  } else if (mode == D_GRAPH_OUT) {
	    degree_mode = D_GRAPH_IN;
	  } else if (mode == D_GRAPH_IN) {
	    degree_mode = D_GRAPH_OUT;
	  } else {
	    printf("Error: invalid mode\n");
	    return 0;
	  }

	int *result = (int*)malloc(d_graph_vcount(graph)*sizeof(int));
	Dllist queue_src = new_dllist();
	
	JRB cur, degree_list = make_jrb();

	Dllist node;
	int v_tmp, count = 0, *neis, n, *tmp;
	jrb_traverse(cur, graph->edges)
	{
		int in_degree = d_graph_degree_one(graph, jval_i(cur->key), &tmp, degree_mode);
		jrb_insert_int(degree_list,jval_i(cur->key), new_jval_i(in_degree));
		if(in_degree == 0){
			dll_append(queue_src, cur->key);
		}
		free(tmp);
	}
 	while(!dll_empty(queue_src))
 	{
 		node = dll_first(queue_src);
 		v_tmp = jval_i(node->val);
 		dll_delete_node(node);
 		result[count] = v_tmp;
 		count++;
 		d_graph_neighbors(graph,
                     &neis,
                     v_tmp,
                     &n,
                     mode);
 		for (int i = 0; i < n; ++i)
 		{
 			JRB node = jrb_find_int(degree_list,neis[i]);
 			node->val = new_jval_i(jval_i(node->val) - 1);
 			if(jval_i(node->val) == 0){
 				dll_append(queue_src, new_jval_i(neis[i]));
 			}
 		}
 		free(neis);
 	}

 	*output = result;
 	*res = count;
 	jrb_free_tree(degree_list);
	free_dllist(queue_src);
	return 1;
}