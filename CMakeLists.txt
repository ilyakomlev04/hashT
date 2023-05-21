cmake_minimum_required(VERSION 3.20.0)
project(hashT VERSION 0.1.0)



set(SRC_FILES  TDList.c testList.c)
set(Include_Dirs  "c:/Distr/eDocs/pr/Ilya/hash/")


add_executable(hashT ${SRC_FILES})


#add_compile_options(-static)
include_directories(${Include_Dirs})
# target_link_libraries(test4 ${wxWidgets_LIBRARIES})
# target_include_directories(test4 PRIVATE ${wxWidgets_INCLUDE_DIRS})