#include "ih/config/tools.h"
#include "ih/core/tools.h"
#include "ih/net/star/node/system.h"
#include "ih/net/star/node/conf.h"

int main(int argc, char *argv[])
{
  ih_config_disable_if_running_batch_tests(argc, argv);

  ih_net_star_node_system_t *node;
  ih_net_star_node_conf_t *node_conf;
  ih_core_log_t *log;

  node_conf = ih_net_star_node_conf_create("x_net_node.conf");
  if (!node_conf) {
    ih_core_trace_exit("x_net_node_conf_create");
  }

  log = ih_core_log_create(stdout);
  if (!log) {
    ih_core_trace_exit("x_audit_log_create");
  }

  node = ih_net_star_node_system_create(node_conf->node_ip, node_conf->node_port,
      node_conf->node_port, node_conf->node_max_threads,
      node_conf->peer_node_ips, node_conf->peer_node_port_min,
      node_conf->peer_node_port_max, log);
  if (!node) {
    ih_core_trace_exit("x_net_node_create");
  }

  ih_net_star_node_system_set_server_unresponsive_client_time_seconds(node, 32);

  if (!ih_net_star_node_system_start(node)) {
    ih_core_trace_exit("x_net_node_start");
  }

  ih_net_star_node_system_destroy(node);
  ih_net_star_node_conf_destroy(node_conf);
  ih_core_log_destroy(log);

  return 0;
}
