#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdio.h>

int main() {
  // Create a .dot file
  FILE* dotFile = fopen("graph.dot", "we");
  if (dotFile == NULL) {
    // Handle error
    return 1;
  }
  char* twopi_head =
      "graph page {\n\
        labelloc='t'\n\
        label='Mind map of Happiness.\nTwopi radial graph.'\n\
        fontname='URW Chancery L, Apple Chancery, Comic Sans MS, cursive'\n\
        layout=twopi; graph [ranksep=2];\n\
        edge [penwidth=5 color='#f0f0ff']\n\
        node [fontname='URW Chancery L, Apple Chancery, Comic Sans MS, cursive']\n\
        node [style='filled' penwidth=0 fillcolor='#f0f0ffA0' fontcolor=indigo]\n";

  // Write the DOT representation to the file
  (void)fputs(twopi_head, dotFile);
  (void)fclose(dotFile);

  //   // Create a new graph object
  //   Agraph_t* graph = agopen(NULL, Agdirected, NULL);

  //   // Read the DOT file
  //   dotFile = fopen("graph.dot", "r");
  //   if (dotFile == NULL) {
  //     // Handle error
  //     return 1;
  //   }

  //   if (agread(dotFile, graph) != 0) {
  //     // Handle error
  //     (void)fclose(dotFile);
  //     return 1;
  //   }

  //   (void)fclose(dotFile);

  //   // Set the layout
  //   agattr(graph, AGRAPH, "layout", "twopi");

  //   // Render the graph to a PNG file
  //   FILE* pngFile = fopen("graph.png", "w");
  //   if (pngFile == NULL) {
  //     // Handle error
  //     return 1;
  //   }
  //   GVC_t* gvc = gvContext();
  //   if (gvRenderData(gvc, graph, "png", pngFile) != 0) {
  //     // Handle error
  //     fclose(pngFile);
  //     return 1;
  //   }

  //   fclose(pngFile);

  // Clean up
  //   agclose(graph);

  return 0;
}
