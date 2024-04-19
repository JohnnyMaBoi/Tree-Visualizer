#include "file_system_traversal.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Function to recursively traverse a directory and construct the file structure
// graph
void traverse_directory(const char* dirname, struct FileNode* parent) {
  DIR* dir;
  struct dirent* entry;

  // Open the directory
  dir = opendir(dirname);
  if (dir == NULL) {
    perror("opendir");
    return;
  }

  // Read directory entries
  while ((entry = readdir(dir)) != NULL) {
    // Skip "." and ".." entries
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    // Allocate memory for the new file node
    struct FileNode* new_node =
        (struct FileNode*)malloc(sizeof(struct FileNode));
    if (new_node == NULL) {
      perror("malloc");
      closedir(dir);
      return;
    }

    // Construct the file path
    char filepath[1024];  // Adjust the size as needed
    snprintf(filepath, sizeof(filepath), "%s/%s", dirname, entry->d_name);

    // Populate file information using stat
    if (stat(filepath, &(new_node->file_info)) != 0) {
      perror("stat");
      free(new_node);
      continue;
    }

    // Set the filename
    new_node->filename = strdup(entry->d_name);
    if (new_node->filename == NULL) {
      perror("strdup");
      free(new_node);
      continue;
    }

    // Initialize child and sibling pointers
    new_node->children = NULL;
    new_node->next = NULL;

    // Link the new node to the parent node
    if (parent != NULL) {
      if (parent->children == NULL) {
        parent->children = new_node;
      } else {
        struct FileNode* temp = parent->children;
        while (temp->next != NULL) {
          temp = temp->next;
        }
        temp->next = new_node;
      }
    }

    // Recursively traverse subdirectories
    if (S_ISDIR(new_node->file_info.st_mode)) {
      traverse_directory(filepath, new_node);
    }
  }

  // Close the directory
  closedir(dir);
}

// Function to initialize a file graph and populate it with file structure data
struct FileGraph* create_file_graph(const char* root_dir) {
  // Allocate memory for the file graph
  struct FileGraph* graph = (struct FileGraph*)malloc(sizeof(struct FileGraph));
  if (graph == NULL) {
    perror("malloc");
    return NULL;
  }

  // Initialize the root node
  graph->root = (struct FileNode*)malloc(sizeof(struct FileNode));
  if (graph->root == NULL) {
    perror("malloc");
    free(graph);
    return NULL;
  }

  // Set root node attributes
  graph->root->filename = strdup(root_dir);  // Root directory name
  if (graph->root->filename == NULL) {
    perror("strdup");
    free(graph->root);
    free(graph);
    return NULL;
  }
  if (stat(root_dir, &(graph->root->file_info)) != 0) {
    perror("stat");
    free(graph->root->filename);
    free(graph->root);
    free(graph);
    return NULL;
  }
  graph->root->children = NULL;
  graph->root->next = NULL;

  // Recursively traverse the directory structure
  traverse_directory(root_dir, graph->root);

  return graph;
}

// Function to free memory allocated for the file graph
void free_file_graph(struct FileGraph* graph) {
  if (graph != NULL) {
    free(graph->root->filename);
    free(graph->root);
    free(graph);
  }
}

// Function to print file structure graph (for debugging)
void print_file_graph(struct FileNode* node, int depth) {
  if (node != NULL) {
    for (int i = 0; i < depth; i++) {
      printf("  ");  // Indentation for visualization
    }
    printf("%s\n", node->filename);               // Print filename
    print_file_graph(node->children, depth + 1);  // Recursively print children
    print_file_graph(node->next, depth);          // Print next sibling
  }
}

// int main() {
//   // Create file graph for the specified directory
//   struct FileGraph* graph = create_file_graph("path/to/directory");
//   if (graph == NULL) {
//     fprintf(stderr, "Failed to create file graph\n");
//     return 1;
//   }

//   // Print file structure graph (for debugging)
//   printf("File Structure:\n");
//   print_file_graph(graph->root, 0);

//   // Free memory allocated for the file graph
//   free_file_graph(graph);

//   return 0;
// }
