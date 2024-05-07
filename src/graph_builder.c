#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdio.h>

#include "link_extractor.h"

#define GRAPH_PATH "graph.dot"

int initialize_twopi_dot() {
  // Create a .dot file
  FILE* dotFile = fopen(GRAPH_PATH, "we");
  if (dotFile == NULL) {
    // Handle error
    return 0;
  }
  char* twopi_head =
      "graph page {\n\
	labelloc=\"t\"\n\
	label=\"wikipidia link web.\nTwopi radial graph.\"\n\
	fontname=\"URW Chancery L, Apple Chancery, Comic Sans MS, cursive\"\n\
	layout=twopi; graph [ranksep=2];\n\
	edge [penwidth=5 color=\"#f0f0ff\"]\n\
	node [fontname=\"URW Chancery L, Apple Chancery, Comic Sans MS, cursive\"]\n\
	node [style=\"filled\" penwidth=0 fillcolor=\"#f0f0ffA0\" fontcolor=indigo]\n";

  // Write the DOT representation to the file
  (void)fputs(twopi_head, dotFile);
  (void)fclose(dotFile);
  return 1;
}

int close_twopi_dot() {
  FILE* dotFile = fopen("graph.dot", "ae");
  if (dotFile == NULL) {
    // Handle error
    return 0;
  }
  (void)fprintf(dotFile, "}");
  (void)fclose(dotFile);

  return 1;
}
// add central node and children to the graph
int add_page_and_children() {
  FILE* dotFile = fopen("graph.dot", "ae");
  if (dotFile == NULL) {
    // Handle error
    return 0;
  }
  //   const char* dummy_example =

  (void)fprintf(dotFile,
                "   C [fontsize=50 fontcolor=red]\n\
	node [fontsize=40]\n\
	C -- {\n\
		C++\n\
		Python\n\
		C#\n\
		Low-Level\n\
		Programming\n\
		Registers\n\
	}");
  (void)fclose(dotFile);

  return 1;
}
int main() {
  initialize_twopi_dot();
  add_page_and_children();
  close_twopi_dot();
}
