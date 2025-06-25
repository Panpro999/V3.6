#include "ov_api/dataset_runner.hpp"

// \u4f7f\u7528\u793a\u4f8b\uff1a\u53ea\u9700\u4e00\u884c\u5373\u53ef\u8fd0\u884c\u6570\u636e\u96c6
int main(int argc, char **argv) {
  const std::string cfg = "open_vins/config/kaist/estimator_config.yaml"; // \u914d\u7f6e\u6587\u4ef6
  const std::string bag = "dataset.bag";                                  // \u6570\u636e\u5305
  return openvins_api::Runner(cfg, bag).run(), 0;
}
