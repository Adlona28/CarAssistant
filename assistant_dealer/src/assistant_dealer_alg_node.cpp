#include "assistant_dealer_alg_node.h"

AssistantDealerAlgNode::AssistantDealerAlgNode(void) :
  algorithm_base::IriBaseAlgorithm<AssistantDealerAlgorithm>()
{
  //init class attributes if necessary
  //this->loop_rate_ = 2;//in [Hz]

  // [init publishers]

  // [init subscribers]

  // [init services]

  // [init clients]

  // [init action servers]

  // [init action clients]
}

AssistantDealerAlgNode::~AssistantDealerAlgNode(void)
{
  // [free dynamic memory]
}

void AssistantDealerAlgNode::mainNodeThread(void)
{
  // [fill msg structures]

  // [fill srv structure and make request to the server]

  // [fill action structure and make request to the action server]

  // [publish messages]
}

/*  [subscriber callbacks] */

/*  [service callbacks] */

/*  [action callbacks] */

/*  [action requests] */

void AssistantDealerAlgNode::node_config_update(Config &config, uint32_t level)
{
  this->alg_.lock();
  this->config_=config;
  this->alg_.unlock();
}

void AssistantDealerAlgNode::addNodeDiagnostics(void)
{
}

/* main function */
int main(int argc,char *argv[])
{
  return algorithm_base::main<AssistantDealerAlgNode>(argc, argv, "assistant_dealer_alg_node");
}
