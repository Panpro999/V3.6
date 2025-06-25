#include "ov_api/dataset_runner.hpp"
#include <iostream>
#include <ros/ros.h>
#include <string>

static void usage() { std::cout << "Usage: ov_run_dataset --bag PATH --config YAML [--out CSV]" << std::endl; }

int main(int argc, char **argv) {
  ros::init(argc, argv, "ov_run_dataset", ros::init_options::AnonymousName);

  std::string bag;
  std::string yaml;
  std::string out;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--bag" && i + 1 < argc) {
      bag = argv[++i];
    } else if (arg == "--config" && i + 1 < argc) {
      yaml = argv[++i];
    } else if (arg == "--out" && i + 1 < argc) {
      out = argv[++i];
    } else {
      usage();
      return 1;
    }
  }

  if (bag.empty() || yaml.empty()) {
    usage();
    return 1;
  }

  openvins_api::Runner runner(yaml, bag);
  runner.run(out);
  return 0;
}
