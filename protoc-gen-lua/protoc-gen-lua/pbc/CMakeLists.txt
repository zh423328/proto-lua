project(protobuf.c)
#添加头文件
include_directories(../../../lua/include)
add_library(protobuf.c SHARED pbc-lua.c)
#链接库
target_link_libraries(pb ../../../lua/lib/lua5.1)