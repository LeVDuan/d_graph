#ifndef D_GRAPH_DATATYPE_H_
#define D_GRAPH_DATATYPE_H_

#include "libfdr/jrb.h"
#include "d_graph_constants.h"
/**
``Cấu trúc dữ liệu biểu diễn đồ thị``
- Cấu trúc dữ lệu sử dụng cây đỏ đen của thư viện libfdr 
  để lưu danh sách kề của mỗi đỉnh của đồ thị
* Các thành phần: 
- `vertices_num`: số lượng đỉnh đồ thị, là số nguyên không âm
- `directed`: đồ thị có hướng (directed == D_GRAPH_UNDIRECTED)
			   hoặc vô hướng (directed == D_GRAPH_DIRECTED)
- `edges`: cây đỏ đen kiểu JRB chứa danh sách đỉnh kề tương ứng
		   key : kiểu int chứa id của đỉnh
		   val : là một cây đỏ đen JRB chứa danh sách đỉnh kề với đỉnh key

- `vertices_to_id`: cây đỏ đen kiểu JRB chứa danh sách đỉnh của đồ thị (để tra cứu ra id của đỉnh)
		   key : kiểu char* chứa tên các đỉnh
		   val : kiểu int chứa id của đỉnh tương ứng

- `id_to_vertices`: cây đỏ đen kiểu JRB chứa danh sách đỉnh của đồ thị (để tra cứu ra tên của đỉnh)
		   key : kiểu int chứa id các đỉnh
		   val : kiểu char* chứa tên của đỉnh tương ứng
		   
**/

typedef struct d_graph_s
{
	int vertices_num;
	d_graph_directed_t directed;
	JRB edges;
	JRB vertices_to_id;
	JRB id_to_vertices;
} *d_graph_t;

#endif  // D_GRAPH_DATATYPE_H_