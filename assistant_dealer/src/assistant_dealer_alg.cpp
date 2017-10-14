#include "assistant_dealer_alg.h"

AssistantDealerAlgorithm::AssistantDealerAlgorithm(void)
{
  pthread_mutex_init(&this->access_,NULL);
}

AssistantDealerAlgorithm::~AssistantDealerAlgorithm(void)
{
  pthread_mutex_destroy(&this->access_);
}

void AssistantDealerAlgorithm::config_update(Config& config, uint32_t level)
{
  this->lock();

  // save the current configuration
  this->config_=config;
  
  this->unlock();
}

// AssistantDealerAlgorithm Public API
