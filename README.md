# d_graph ✨
Thư viện các thuật toán đồ thị được xây dựng trên các thư viện tiêu chuẩn trong ngôn ngữ lập trình `C` và sử dụng thêm thư viện [libfdr của Jim Plank's](http://www.cs.utk.edu/~plank/plank/classes/cs360/360/notes/Libfdr/)
# Giới thiệu
- Thư viện xây dựng cấu trúc đồ thị để giải quyết các vấn đề liên quan
- Thư viện có nhiều hàm API cụ thể để hướng đến các học sinh, sinh viên ứng dụng để học các môn có liên quan
- Đồ thị được lưu trữ bằng danh sách đỉnh kề
# Yêu cầu 📌
## Kiến thức 📚
- Có kiến thức cơ bản về các khái niệm liên quan đến đồ thị cũng như các thuật toán liên quan như:
 [biểu diễn đồ thị](https://vi.wikipedia.org/wiki/Bi%E1%BB%83u_di%E1%BB%85n_%C4%91%E1%BB%93_th%E1%BB%8B),
 [DFS](https://en.wikipedia.org/wiki/Depth-first_search), 
 [BFS](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/), 
 [DAG](https://en.wikipedia.org/wiki/Directed_acyclic_graph), 
 [Topological Sort](https://vi.wikipedia.org/wiki/S%E1%BA%AFp_x%E1%BA%BFp_t%C3%B4_p%C3%B4), 
 [Dijkstra's shortest path algorithm](https://vi.wikipedia.org/wiki/Thu%E1%BA%ADt_to%C3%A1n_Dijkstra), ...
- Ngôn ngữ `C`
- Sử dụng `Cmake`, `ninja_build`
## Công nghệ 🖥
- Hệ điều hành: **Ubuntu**
- Trình biên dịch: [gcc](https://gcc.gnu.org/) 
- Hỗ trợ biên dịch: [Cmake](https://cmake.org/), ninja_build
- git, ...\
Có thể xem cài cmake và ninja_build trên Ubuntu với dòng lệnh như sau:
```
sudo apt-get install cmake
```
```
sudo apt-get install ninja-build
```

# Cài đặt ⚙
1. Tải xuống: 
``` 
git clone https://github.com/LeVDuan/d_graph.git 
```
2. Tạo file `CMakeLists.txt` bên ngoài thư mục của thư viện để biên dịch trong đó liên kết với thư viện với tên `d_graph`
# Cách sử dụng 👨‍💻
- Trong các file cần sử dụng đến các API của thư viện cần khai báo 
```
#include "d_graph/d_graph.h"
```
- Bạn nên tạo trước thư mục mà bạn làm việc sau đó tải thư viện trong thư mục này, và các file main chính của bạn cũng lưu ở đây
- Bạn nên tạo thêm 1 thư mục gọi là thư mục `b` (build, bạn có thể đặt tên bất kì) để lưu các file chạy của dự án
- Biên dịch và chạy chương trình tại thư mục `b` như sau:
```
cmake .. -G Ninja
```
- Bạn có thể xem ví dụ sử dụng thư viện để tạo đồ thị đơn giản ở [đây](https://github.com/LeVDuan/d_graph/blob/master/Example_for_use.md).
# Những người đóng góp 👨‍👨‍👦‍👦
- [Lê Văn Duẩn](https://github.com/LeVDuan)
# Nguồn 🔗
- Thư viện [Jim Plank's libfdr](http://www.cs.utk.edu/~plank/plank/classes/cs360/360/notes/Libfdr/)
# Thông tin và liên lạc ☎
- Tên: Lê Văn Duẩn
- Trình độ: Sinh viên [CNTT Việt-Nhật](https://www.hust.edu.vn/cntt-vietnhat), [Đại học Bách khoa Hà Nội](https://www.hust.edu.vn/)
- Số điện thoại: 0346277085
- Facebook : [Lê Duẩn](https://www.facebook.com/profile.php?id=100051555680303)
