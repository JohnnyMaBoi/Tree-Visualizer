#include "link_extractor.h"

// #include <cjson/cJSON.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char WIKIPEDIA_API[] = "https://en.wikipedia.org/w/api.php?";
// const char WIKIPEDIA_API[] =
// "https://en.wikipedia.org/w/"
// "api.php?action=query&titles=Belgrade&prop=extracts&format=json&exintro=1";

const char OUTPUT_FILE[] = "api_response.json";
const size_t URL_MAX = 200;

// requests without api url prefix and title suffix
const char LINKS_TO_REQUEST[] =
    "action=query&prop=links&format=json&exintro=1&titles=";
const char LINKS_FROM_REQUEST[] =
    "action=query&prop=links&format=json&exintro=1&titles=";

// Function to make an HTTP request to the Wikipedia API
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
  (void)fprintf(stdout, "%s", full_url);
  // (void)snprintf(full_url, sizeof(full_url), "%s%s", WIKIPEDIA_API,
  // api_params);

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
    // free(full_url);
    return 1;
  }

  // Clean up resources
  curl_easy_cleanup(handle);
  // free(full_url);
  if (fclose(output) != 0) {
    (void)fprintf(stderr, "closing output filestream failed!");
  }

  return 0;
}

int get_links_from_title(char* title) {
  char* api_params = malloc(URL_MAX * sizeof(char));
  strncpy(api_params, LINKS_TO_REQUEST, strlen(LINKS_TO_REQUEST));
  strncpy(api_params + strlen(api_params), title, strlen(title));
  int success = makeAPIRequest(api_params);
  if (success != 0) {
    (void)fprintf(stderr, "request failed!");
    free(api_params);
    return 0;
  }
  free(api_params);
  return 1;
}

int main() {
  // Construct the URL for the Wikipedia API request
  const char* api_params =
      "action=query&titles=Belgrade&prop=links&format=json&exintro=1";
  // open output file

  // Make the API request and get the response
  int success = makeAPIRequest(api_params);
  if (success != 0) {
    (void)fprintf(stderr, "request failed!");
  }

  return 1;
}
