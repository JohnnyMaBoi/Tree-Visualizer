#ifndef FILE_SYSTEM_TRAVERSAL_H
#define FILE_SYSTEM_TRAVERSAL_H
#include <sys/stat.h>

// Define a structure to represent a node in the file structure graph
struct FileNode {
  char* filename;             // Name of the file or directory
  struct stat file_info;      // Information about the file (using struct stat)
  struct FileNode* children;  // Pointer to the first child node
  struct FileNode* next;      // Pointer to the next sibling node
};

// Define a structure to represent the file structure graph
struct FileGraph {
  struct FileNode* root;  // Pointer to the root node of the graph
};

/*
   Creates a file structure graph for the specified directory.

   @param root_dir The root directory for which to create the file graph.
   @return A pointer to the created file graph on success, NULL on failure.

   @remarks This function dynamically allocates memory for the file graph and
   its nodes. It uses the traverse_directory function to recursively traverse
   the directory structure. The caller is responsible for freeing the allocated
   memory using free_file_graph.
*/
struct FileGraph* create_file_graph(const char* root_dir);

/*
   Frees memory allocated for the file graph and its nodes.

   @param graph A pointer to the file graph to be freed.

   @remarks This function deallocates memory previously allocated by
   create_file_graph.
*/
void free_file_graph(struct FileGraph* graph);

/*
   Recursively traverses a directory and constructs the file structure graph.

   @param dirname The directory to traverse.
   @param parent  A pointer to the parent node in the file structure graph.

   @remarks This function populates the FileNode attributes using calls to stat.
            It handles errors encountered during traversal, such as directory
   opening and stat calls.
*/
void traverse_directory(const char* dirname, struct FileNode* parent);

/*
   Prints the file structure graph for debugging purposes.

   @param node   A pointer to the root node of the file structure graph.
   @param depth  The depth of the current node in the graph.

   @remarks This function recursively prints the file structure graph starting
   from the root node. It prints each node's filename and recursively traverses
   children and next siblings.
*/
void print_file_graph(struct FileNode* node, int depth);

#endif /* FILE_SYSTEM_TRAVERSAL_H */
