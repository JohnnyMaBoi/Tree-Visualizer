#include "link_extractor.h"

// #include <cjson/cJSON.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char WIKIPEDIA_API[] = "https://en.wikipedia.org/w/api.php?";
// const char WIKIPEDIA_API[] =
// "https://en.wikipedia.org/w/"
// "api.php?action=query&titles=Belgrade&prop=extracts&format=json";

const char OUTPUT_FILE[] = "api_response.json";
const size_t URL_MAX = 200;
const size_t RESP_MAX = 2000;

// requests without api url prefix and title suffix
const char LINKS_REQUEST[] =
    "action=query&prop=links&pllimit=25&format=json&titles=";

Page* make_page(int depth, char* title) {
  Page* new_page = malloc(sizeof(Page));
  new_page->depth = depth;
  new_page->title = title;
  new_page->num_links = 0;
  return new_page;
}

void add_link(Page* page, char* title) {
  page->links[(page->num_links) + 1] = title;
  page->num_links += 1;
}

// Function {to make an HTTP request to the Wikipedia API
int makeAPIRequest(const char* api_params) {
  // initialize curl instance
  CURL* handle = curl_easy_init();
  if (!handle) {
    (void)fprintf(stderr, "Failed to initialize libcurl\n");
    return 0;
  }

  FILE* output = fopen(OUTPUT_FILE, "wbe");
  if (output == NULL) {
    (void)fprintf(stderr, "Failed to open output file\n");
    return 0;
  }

  // Set the URL for the API request
  char full_url[URL_MAX];
  strncpy(full_url, WIKIPEDIA_API, strlen(WIKIPEDIA_API));
  strncpy(full_url + strlen(WIKIPEDIA_API), api_params, strlen(api_params));
  full_url[strlen(WIKIPEDIA_API) + strlen(api_params)] = '\0';

  curl_easy_setopt(handle, CURLOPT_URL, full_url);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, output);
  // Perform the API request
  CURLcode res = curl_easy_perform(handle);

  if (res != CURLE_OK) {
    (void)fprintf(stderr, "API request failed: %s\n", curl_easy_strerror(res));
    curl_easy_cleanup(handle);
    if (fclose(output) != 0) {
      (void)fprintf(stderr, "closing output filestream failed!");
    }
    return 1;
  }

  // Clean up resources
  curl_easy_cleanup(handle);
  if (fclose(output) != 0) {
    (void)fprintf(stderr, "closing output filestream failed!");
    return 0;
  }

  return 1;
}

int links_request(char* title) {
  char* api_params = malloc(URL_MAX * sizeof(char));
  strncpy(api_params, LINKS_REQUEST, strlen(LINKS_REQUEST));
  strncpy(api_params + strlen(api_params), title, strlen(title));
  int success = makeAPIRequest(api_params);
  if (success == 0) {
    (void)fprintf(stderr, "request failed!");
    free(api_params);
    return 0;
  }
  free(api_params);
  return 1;
}

// Helper function to count the number of links
int count_links(const char* json_str) {
  int count = 0;
  const char* link_start = strstr(json_str, "\"title\":\"");
  while (link_start != NULL) {
    count++;
    link_start = strstr(link_start + 1, "\"title\":\"");
  }
  return count;
}

// Helper function to extract a link title
char* extract_link_title(const char* link_start) {
  char* end = strstr(link_start + 10, "\\\"}");
  if (end != NULL) {
    long len = end - (link_start + 10);
    char* title = malloc(len + (long)1);
    strncpy(title, link_start + 10, len);
    title[len] = '\\0';
    return title;
  } else {
    // Handle the case where the expected substring is not found
    return NULL;
  }
}

// after an api call, populate a page's links with the response data
int links_populate(Page* page) {
  FILE* input = fopen(OUTPUT_FILE, "re");
  if (input == NULL) {
    (void)fprintf(stderr, "Failed to open output file\n");
    return 0;
  }
  char json_str[RESP_MAX];
  int num_links = 0;
  if (fgets(json_str, sizeof(json_str), input) != NULL) {
    num_links += count_links(json_str);
    char** links = malloc((num_links + 1) * sizeof(char*));
    const char* link_start = strstr(json_str, "\"title\":\"");
    int iter = 0;
    while (link_start != NULL) {
      links[iter++] = extract_link_title(link_start);
      link_start = strstr(link_start + 1, "\"title\":\"");
    }
    links[iter] = NULL;  // Null-terminate the array
    for (int idx = 1; idx < iter - 1; idx++) {
      add_link(page, links[idx]);
    }
    fprintf(stdout, "num links: %d last link: %s", page->num_links,
            page->links[page->num_links]);
  } else {
    fprintf(stderr, "reading json file output failed!");
    return 0;
  }
}

int main() {
  // Construct the URL for the Wikipedia API request
  // open output file
  char* title = "C%20(programming%20language)";
  int success = links_request(title);
  Page* root_page = make_page(0, title);
  // links_populate(root_page);
  // Make the API request and get the response

  if (success == 0) {
    (void)fprintf(stderr, "request failed!");
  }

  return 1;
}
