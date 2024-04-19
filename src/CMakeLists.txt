# If you have a program that's just a .c file and it has a main method, define
# an executable. If it has both a .c and .h file, make it a library. Also, link
# libraries appropriately here. Targets should be added in dependency order - if
# executable bar needs library foo, then you should do
#   add_library(foo foo.c foo.h)
#   add_executable(bar bar.c)
#   target_link_libraries(bar PRIVATE foo)
# or similar. The PRIVATE/INTERFACE/PUBLIC keyword will depend on whether the
# library is used only in function bodies (PRIVATE), only in function
# signatures/types (INTERFACE), or both (PUBLIC).
cmake_minimum_required(VERSION 3.10)
project(FileGraph)

add_library(file_system_traversal file_system_traversal.c file_system_traversal.h)

# Add executable
add_executable(main main.c)
target_link_libraries(main PRIVATE file_system_traversal)


# Add header file directory
target_include_directories(file_system_traversal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
