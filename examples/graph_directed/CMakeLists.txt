add_executable(d_graph_interface_demo d_graph_interface_demo.c)
add_executable(d_graph_dag_demo d_graph_dag_demo.c)
add_executable(d_graph_visit_demo d_graph_visit_demo.c)

foreach(i d_graph_dag_demo
          d_graph_interface_demo
          d_graph_visit_demo)
    target_link_libraries(${i} d_graph)
endforeach()