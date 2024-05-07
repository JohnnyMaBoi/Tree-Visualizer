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
cmake_minimum_required(VERSION 3.0)
project(WikipediaLinkExtractor C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GRAPHVIZ REQUIRED GraphicsMagick++)
# find_package(GraphViz REQUIRED)
find_package(CURL REQUIRED)
find_package(LibXml2 REQUIRED)

add_executable(link_extractor link_extractor.c)
add_executable(graph_builder graph_builder.c)

target_link_libraries(graph_builder PUBLIC cgraph gvc)
target_link_libraries(graph_builder PRIVATE ${GRAPHVIZ_LIBRARIES} ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})
target_include_directories(graph_builder PRIVATE ${GRAPHVIZ_INCLUDE_DIRS})
target_include_directories(link_extractor PRIVATE ${CURL_INCLUDE_DIRS} ${LIBXML2_INCLUDE_DIR})
target_link_libraries(link_extractor PRIVATE ${GRAPHVIZ_LIBRARIES} ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})
