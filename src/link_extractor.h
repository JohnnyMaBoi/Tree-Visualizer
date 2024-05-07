#define MAX_LINKS 25  // Maximum number of links a page can have

// Struct to hold a Wikipedia page
typedef struct {
  char* title;
  int depth;
  int num_links;
  char* links[MAX_LINKS];
} Page;
