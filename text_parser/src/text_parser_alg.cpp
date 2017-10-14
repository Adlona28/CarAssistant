#include "text_parser_alg.h"

TextParserAlgorithm::TextParserAlgorithm(void)
{
  pthread_mutex_init(&this->access_,NULL);
}

TextParserAlgorithm::~TextParserAlgorithm(void)
{
  pthread_mutex_destroy(&this->access_);
}

void TextParserAlgorithm::config_update(Config& config, uint32_t level)
{
  this->lock();

  // save the current configuration
  this->config_=config;
  
  this->unlock();
}

// TextParserAlgorithm Public API
