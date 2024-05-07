#define MAX_LINKS 100  // Maximum number of links a page can have

// Struct to hold a Wikipedia page
typedef struct {
  char* title;
  char* url;
} Page;

// Struct to hold the links from a parent page
typedef struct {
  Page parent;
  int num_links;
  Page links[MAX_LINKS];
} PageLinks;
