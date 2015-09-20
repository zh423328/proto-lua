project(pb)
#添加头文件
include_directories(../../../lua/include)
add_library(pb SHARED pb.c)
#链接库
target_link_libraries(pb ../../../lua/lib/lua5.1)