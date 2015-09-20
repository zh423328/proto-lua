project(pbc)
#添加头文件
include_directories(../../../lua/include)
include_directories(../../../pbc)
add_library(pbc  SHARED pbc-lua.c)
#链接库
target_link_libraries(pbc ../../../lua/lib/lua5.1)
target_link_libraries(pbc ../../../pbc/Release/pbc)