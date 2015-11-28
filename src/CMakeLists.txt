

include_directories("../../lib")
add_executable(kpartition main.cc)

target_link_libraries(kpartition partitionlib)

