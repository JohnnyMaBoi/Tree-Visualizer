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
static const size_t URL_MAX = 1024;

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

  // Set the output file for libcurl to write the response to
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
  }

  return 0;
}

int main() {
  // Construct the URL for the Wikipedia API request
  const char* api_params =
      "action=query&titles=Belgrade&prop=extracts&format=json&exintro=1";
  // open output file

  // Make the API request and get the response
  int success = makeAPIRequest(api_params);
  if (success != 0) {
    (void)fprintf(stderr, "request failed!");
  }

  return 1;
}
