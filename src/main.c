#include <stdio.h>

#include "file_system_traversal.h"

int main() {
  // Create file graph for the specified directory
  struct FileGraph* graph =
      create_file_graph("/home/rajiv/Github/Tree-Visualizer/src");
  if (graph == NULL) {
    fprintf(stderr, "Failed to create file graph\n");
    return 1;
  }

  // Print file structure graph (for debugging)
  printf("File Structure:\n");
  print_file_graph(graph->root, 0);

  // Free memory allocated for the file graph
  free_file_graph(graph);

  return 0;
}
