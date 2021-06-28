add_executable(create_graph_demo create_graph_demo.c)
add_executable(dag_demo dag_demo.c)


foreach(i create_graph_demo 
          dag_demo)
          
  target_link_libraries(${i} d_graph)
endforeach()
