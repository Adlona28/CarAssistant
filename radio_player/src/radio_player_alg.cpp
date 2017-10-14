#include "radio_player_alg.h"

RadioPlayerAlgorithm::RadioPlayerAlgorithm(void)
{
  pthread_mutex_init(&this->access_,NULL);
}

RadioPlayerAlgorithm::~RadioPlayerAlgorithm(void)
{
  pthread_mutex_destroy(&this->access_);
}

void RadioPlayerAlgorithm::config_update(Config& config, uint32_t level)
{
  this->lock();

  // save the current configuration
  this->config_=config;
  
  this->unlock();
}

// RadioPlayerAlgorithm Public API
