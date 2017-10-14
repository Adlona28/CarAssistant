#include "text_parser_alg_node.h"

TextParserAlgNode::TextParserAlgNode(void) :
  algorithm_base::IriBaseAlgorithm<TextParserAlgorithm>()
{
  //init class attributes if necessary
  //this->loop_rate_ = 2;//in [Hz]

  // [init publishers]

  // [init subscribers]

  // [init services]

  // [init clients]
  command_client_ = this->public_node_handle_.serviceClient<text_parser::Command>("command");


  // [init action servers]

  // [init action clients]
}

TextParserAlgNode::~TextParserAlgNode(void)
{
  // [free dynamic memory]
}

void TextParserAlgNode::mainNodeThread(void) {
  // [fill msg structures]

  // [fill srv structure and make request to the server]
  this->command_srv_.request.command = read_command_from_txt_files();
  ROS_INFO("TextParserAlgNode:: Sending New Request!");
  if (this->command_client_.call(this->command_srv_)) {
    ROS_INFO("TextParserAlgNode:: Call succeeded");
  }
  else {
    ROS_INFO("TextParserAlgNode:: Failed to Call Server on topic command ");
  }



  // [fill action structure and make request to the action server]

  // [publish messages]
  // Uncomment the following line to publish the topic message
  //this->command_publisher_.publish(this->command_String_msg_);

}

/*  [subscriber callbacks] */

/*  [service callbacks] */

/*  [action callbacks] */

/*  [action requests] */
std::string TextParserAlgNode::read_command_from_txt_files(void) {
  return "hi";
}


void TextParserAlgNode::node_config_update(Config &config, uint32_t level)
{
  this->alg_.lock();
  this->config_=config;
  this->alg_.unlock();
}

void TextParserAlgNode::addNodeDiagnostics(void)
{
}

/* main function */
int main(int argc,char *argv[])
{
  return algorithm_base::main<TextParserAlgNode>(argc, argv, "text_parser_alg_node");
}
