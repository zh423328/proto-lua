project(sproto)
#添加头文件


include_directories(../../../lua/include)
add_library(sproto  SHARED sproto.h)
add_library(sproto  SHARED sproto.c)
add_library(sproto  SHARED msvcint.h)
add_library(sproto  SHARED lsproto.c)
#链接库
target_link_libraries(sproto ../../../lua/lib/lua5.1)
set_target_properties(sproto PROPERTIES COMPILE_FLAGS "/TC" ) 