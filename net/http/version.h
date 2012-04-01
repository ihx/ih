#ifndef ih_net_http_version_h
#define ih_net_http_version_h

enum ih_net_http_version_t {
  IH_NET_HTTP_VERSION_UNKNOWN,
  IH_NET_HTTP_VERSION_1_0,
  IH_NET_HTTP_VERSION_1_1,
};
typedef enum ih_net_http_version_t ih_net_http_version_t;

const char *ih_net_http_version_get_name(ih_net_http_version_t http_version);

#endif
