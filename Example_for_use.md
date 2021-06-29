# Tạo thư mục lưu dự án
```
mkdir project
```
# Tải thư viện và tạo file `CMakelists.txt`, `main.c` 
Đi tới thư mục vừa tạo:
```
cd project
```
Tải thư viện:
```
git clone https://github.com/LeVDuan/d_graph.git 
```
Tạo file:
```
touch CMakeLists.txt
```
```
touch main.c
```
Sau đó kiểm tra kết quả như hình:
![image](https://user-images.githubusercontent.com/84384872/123837514-1f816580-d935-11eb-8b8a-cd07ddca66b6.png)
# Chỉnh sửa file `CMakelists.txt` và `main.c` như sau:
- `CMakelists.txt`:
```
add_executable(main main.c) // thêm file exe và tên của nó, ở đây file exe của main.c là main
add_subdirectory(d_graph)   // thêm thư viện
target_link_libraries(main d_graph) // link thư viện và file exe (main)
```
- `main.c`:
```
#include <stdio.h>
#include "d_graph/d_graph.h"
int main()
{
  // Tạo đồ thị
  d_graph_t g = d_graph_create(D_GRAPH_DIRECTED);
  
  // Thêm đỉnh
	d_graph_add_Vertice(g, 0, "v0");
	d_graph_add_Vertice(g, 1, "v1");
	d_graph_add_Vertice(g, 2, "v2");
	d_graph_add_Vertice(g, 3, "v3");
	d_graph_add_Vertice(g, 4, "v4");
  
  //Thêm cạnh
  d_graph_add_Edge(g, 0, 1);
	d_graph_add_Edge(g, 1, 2);
	d_graph_add_Edge(g, 2, 3);
	d_graph_add_Edge(g, 3, 4);
	d_graph_add_Edge(g, 4, 0);
	d_graph_add_Edge(g, 2, 4);
	d_graph_add_Edge(g, 0, 3);
  
  // Xóa đồ thị
  d_graph_print(g);
  return 0;
}
```
# Biên dịch và chạy chương trình
- Tạo thư mục để lưu các file chạy:
```
mkdir b
```
- Đi tới `b` và biên dịch chương trình tại đây
```
cd b
```
```
cmake .. -G Ninja
```
Sau đó kết quả thành công như hình:
![image](https://user-images.githubusercontent.com/84384872/123839180-07aae100-d937-11eb-8851-491dac1ac65c.png)
- Sau đó biên dịch bằng lệnh:
```
ninja
```
- Bây giờ trong thư mục `b` đã chứa các file chạy của dự án như sau:
![image](https://user-images.githubusercontent.com/84384872/123839691-9ddf0700-d937-11eb-9c68-3dd314bbbabd.png)
- Như trong hình thì `main` chính là file chạy đã định nghĩa trong `CMakelists.txt`
- Chạy chương trình:
```
./main
```
- Đây là Kết quả của mã code được soạn thảo trong file `main.c`:
![image](https://user-images.githubusercontent.com/84384872/123840197-3ffeef00-d938-11eb-9616-54b78daf132a.png)
# Lưu ý:
- Những lần sửa code sau đó bạn chỉ cần thực hiện lại lệnh `ninja` tại thư mục `b` và nếu có lỗi nó sẽ báo ngay sau lệnh này
- Trường hợp bạn có file đầu vào ví dụ như file `input.txt` thì bạn nên lưu nó trong thư mục `b` vì chúng ta đang biên dịch tại thư mục này.
Vì vậy khi đọc file bạn không cần đưa đường dẫn của file nữa, có nghĩa là lệnh: 
```
FILE *fp = fopen("input.txt","r");
``` 
sẽ không bị lỗi. 
Nếu bạn lưu trữ file `input.txt` ở thư mục khác thì cần đưa đường dẫn file để đọc : 
```
FILE *fp = fopen("*đường_dẫn_file_input.txt*","r");
```
Ví dụ như bạn lưu file `input.txt` ngay tại thư mục `project` thì để đọc dùng lệnh:
```
FILE *fp = fopen("../input.txt","r");
```
