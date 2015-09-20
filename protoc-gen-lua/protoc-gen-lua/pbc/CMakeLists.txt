project(protobuf)
#添加头文件


include_directories(../../../lua/include)
include_directories(../../../pbc)
add_library(protobuf  SHARED pbc-lua.c)
#链接库
target_link_libraries(protobuf ../../../lua/lib/lua5.1)
target_link_libraries(protobuf ../../../pbc/Release/pbc)
set_target_properties(protobuf PROPERTIES COMPILE_FLAGS "/TP" ) 