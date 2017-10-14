#include "assistant_dealer_alg_node.h"

AssistantDealerAlgNode::AssistantDealerAlgNode(void) :
  algorithm_base::IriBaseAlgorithm<AssistantDealerAlgorithm>()
{
  //init class attributes if necessary
  //this->loop_rate_ = 2;//in [Hz]

  // [init publishers]

  // [init subscribers]

  // [init services]
  this->command_server_ = this->public_node_handle_.advertiseService("command", &AssistantDealerAlgNode::commandCallback, this);
  pthread_mutex_init(&this->command_mutex_,NULL);


  // [init clients]
  sound_order_client_ = this->public_node_handle_.serviceClient<assistant_dealer::PlaySound>("sound_order");

  change_lights_client_ = this->public_node_handle_.serviceClient<assistant_dealer::ChangeLights>("change_lights");



  // [init action servers]

  // [init action clients]
}

AssistantDealerAlgNode::~AssistantDealerAlgNode(void)
{
  // [free dynamic memory]
  pthread_mutex_destroy(&this->command_mutex_);
}

void AssistantDealerAlgNode::mainNodeThread(void)
{
  // [fill msg structures]

  // [fill srv structure and make request to the server]
  //sound_order_srv_.request.data = my_var;
  //ROS_INFO("AssistantDealerAlgNode:: Sending New Request!");
  //if (sound_order_client_.call(sound_order_srv_))
  //{
    //ROS_INFO("AssistantDealerAlgNode:: Response: %s", sound_order_srv_.response.result);
  //}
  //else
  //{
    //ROS_INFO("AssistantDealerAlgNode:: Failed to Call Server on topic sound_order ");
  //}


  //change_lights_srv_.request.data = my_var;
  //ROS_INFO("AssistantDealerAlgNode:: Sending New Request!");
  //if (change_lights_client_.call(change_lights_srv_))
  //{
    //ROS_INFO("AssistantDealerAlgNode:: Response: %s", change_lights_srv_.response.result);
  //}
  //else
  //{
    //ROS_INFO("AssistantDealerAlgNode:: Failed to Call Server on topic change_lights ");
  //}




  // [fill action structure and make request to the action server]

  // [publish messages]
}

/*  [subscriber callbacks] */

/*  [service callbacks] */
bool AssistantDealerAlgNode::commandCallback(text_parser::Command::Request &req, text_parser::Command::Response &res)
{
  ROS_INFO("AssistantDealerAlgNode::commandCallback: New Request Received!");

  //use appropiate mutex to shared variables if necessary
  //this->alg_.lock();
  //this->command_mutex_enter();

  //ROS_INFO("AssistantDealerAlgNode::commandCallback: Processing New Request!");
  //do operations with req and output on res
  //res.data2 = req.data1 + my_var;

  //unlock previously blocked shared variables
  //this->command_mutex_exit();
  //this->alg_.unlock();

  return true;
}

void AssistantDealerAlgNode::command_mutex_enter(void)
{
  pthread_mutex_lock(&this->command_mutex_);
}

void AssistantDealerAlgNode::command_mutex_exit(void)
{
  pthread_mutex_unlock(&this->command_mutex_);
}



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
