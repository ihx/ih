#include "ih/core/string.h"
#include "ih/core/standard.h"
#include "ih/core/tools.h"
#include "ih/net/http/tools.h"

char *encoded_uri = "%3D%29";

int main(int argc, char *argv[])
{
  char *decoded_uri;

  decoded_uri = ih_net_http_decode_uri(encoded_uri, strlen(encoded_uri));
  if (decoded_uri) {
    printf("%s\n", decoded_uri);
    ih_core_string_destroy(decoded_uri);
  } else {
    ih_core_trace("ih_net_http_decode_uri");
  }

  return 0;
}
