#define HTTPSERVER_IMPL
#include "httpserver.h"

#define PORT 8080

char* getTime() {
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  char* temp = asctime(timeinfo);
  temp[strlen(temp)-1] = '\0';
  return temp;
}

char* getPath(struct http_request_s* request) {
  http_string_t url = http_request_target(request);
  int sizeOfPath = 0;

  for(int i = 0; i < url.len; i++) {
    sizeOfPath++;
    if(url.buf[i] == ' ') {
      break;
    }
  }

  if(sizeOfPath == 0) {
    return "/";
  }

  char* path = malloc(sizeOfPath);
  
  for(int i = 0; i < sizeOfPath; i++) {
    path[i] = url.buf[i];
  }

  return path;
}

void handle_request(struct http_request_s* request) {
  char* path = getPath(request);
  // printf("%s", url.buf);

  char* msg;
  asprintf(&msg, "Hello world! The time is %s and you requested the path %s", getTime(), path);

  struct http_response_s* response = http_response_init();
  http_response_status(response, 200);
  http_response_header(response, "Content-Type", "text/plain");
  http_response_body(response, msg, strlen(msg));
  http_respond(request, response);

  free(msg);
  free(path);
}

int main() {
  printf("Listening on http://127.0.0.1:%d\n", PORT);
  struct http_server_s* server = http_server_init(PORT, handle_request);
  http_server_listen(server);
}