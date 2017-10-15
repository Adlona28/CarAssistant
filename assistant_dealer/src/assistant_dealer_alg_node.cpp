#include "assistant_dealer_alg_node.h"

AssistantDealerAlgNode::AssistantDealerAlgNode(void) :
  algorithm_base::IriBaseAlgorithm<AssistantDealerAlgorithm>()
{
  //init class attributes if necessary
  //this->loop_rate_ = 2;//in [Hz]

  // [init publishers]
  this->command_to_print_publisher_ = this->public_node_handle_.advertise<std_msgs::String>("command_to_print", 5);

  // [init subscribers]

  // [init services]
  this->command_server_ = this->public_node_handle_.advertiseService("command", &AssistantDealerAlgNode::commandCallback, this);
  pthread_mutex_init(&this->command_mutex_,NULL);


  // [init clients]
  sound_order_client_ = this->public_node_handle_.serviceClient<assistant_dealer::PlaySound>("sound_order");

  onShort_lights_client_ = this->public_node_handle_.serviceClient<std_srvs::SetBool>("onShort");

  offShort_lights_client_ = this->public_node_handle_.serviceClient<std_srvs::SetBool>("offShort");

  onLarge_lights_client_ = this->public_node_handle_.serviceClient<std_srvs::SetBool>("onLarge");

  offLarge_lights_client_ = this->public_node_handle_.serviceClient<std_srvs::SetBool>("offLarge");

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

  // [fill action structure and make request to the action server]

  // [publish messages]


}

/*  [subscriber callbacks] */

/*  [service callbacks] */
bool AssistantDealerAlgNode::commandCallback(text_parser::Command::Request &req, text_parser::Command::Response &res)
{
  ROS_INFO("AssistantDealerAlgNode::commandCallback: New Request Received!");
  std::string aux = req.command;
  transform(aux.begin(), aux.end(), aux.begin(),::tolower);
  std::vector<std::string> command_to_deal = string_split(aux, " ");

  if (command_to_deal[0] == "play" || command_to_deal[0] == "reproduce") {
    std::string aux;
    for (int i = 1; i < command_to_deal.size(); ++i) {
      aux += command_to_deal[i];
      if (i != command_to_deal.size() - 1) aux += " ";
    }

    this->sound_order_srv_.request.song_to_play = aux;
    this->sound_order_srv_.request.order = 0;
    ROS_INFO("Sending play music callback");
    if (this->sound_order_client_.call(this->sound_order_srv_)) {
      ROS_INFO("TextParserAlgNode:: Call succeeded");
      this->command_to_print_String_msg_.data = "Playing - " + aux;
      this->command_to_print_publisher_.publish(this->command_to_print_String_msg_);
    }
    else {
      ROS_INFO("TextParserAlgNode:: Failed to Call Server on topic command ");
    }
  }

  else if (command_to_deal[0] == "stop") {
    std::string aux;
    for (int i = 1; i < command_to_deal.size(); ++i) {
      aux += command_to_deal[i];
      if (i != command_to_deal.size() - 1) aux += " ";
    }
    this->sound_order_srv_.request.song_to_play = aux;
    this->sound_order_srv_.request.order = 1;
    ROS_INFO("Sending stop music");
    if (this->sound_order_client_.call(this->sound_order_srv_)) {
      ROS_INFO("TextParserAlgNode:: Call succeeded");
      this->command_to_print_String_msg_.data = "Song stopped! :)";
      this->command_to_print_publisher_.publish(this->command_to_print_String_msg_);
    }
    else {
      ROS_INFO("TextParserAlgNode:: Failed to Call Server on topic command ");
    }
  }

  else if (command_to_deal.size() == 3) {
    bool on_bool = false;
    bool off_bool = false;
    bool long_bool = false;
    bool short_bool = false;
    bool light_bool = false;
    bool lights_bool = false;
    for (int i = 0; i < command_to_deal.size(); ++i) {
      if (command_to_deal[i] == "on") {
        on_bool = true;
      }
      if (command_to_deal[i] == "off") {
        off_bool = true;
      }
      if (command_to_deal[i] == "long") {
        long_bool = true;
      }
      if (command_to_deal[i] == "short") {
        short_bool = true;
      }
      if (command_to_deal[i] == "light") {
        light_bool = true;
      }
      if (command_to_deal[i] == "lights") {
        lights_bool = true;
      }
      //std::cout << command_to_deal[i] + "||||" << std::endl;
    }
    //std::cout << on_bool << " " << off_bool << " " << long_bool << " " << short_bool << " " << light_bool << " " << lights_bool << std::endl;
    if (on_bool) {
      if (long_bool) {
        if (light_bool || lights_bool) {
          this->onLarge_lights_srv_.request.data = false;
          ROS_INFO("Enabling long lights");
          sc.say("LONG LIGHTS ENABLED");
          if (this->onLarge_lights_client_.call(this->onLarge_lights_srv_)) {
            ROS_INFO("TextParserAlgNode:: Call succeeded");
          }
          else {
            ROS_INFO("TextParserAlgNode:: Failed to Call Server on topic command ");
          }
        }
      }
      else if (short_bool) {
        if (light_bool || lights_bool) {
          this->onShort_lights_srv_.request.data = false;
          ROS_INFO("Enabling short lights");
          sc.say("SHORT LIGHTS ENABLED");
          if (this->onShort_lights_client_.call(this->onShort_lights_srv_)) {
            ROS_INFO("TextParserAlgNode:: Call succeeded");
          }
          else {
            ROS_INFO("TextParserAlgNode:: Failed to Call Server on topic command ");
          }
        }
      }
    }
    else if (off_bool) {
      if (long_bool) {
        if (light_bool || lights_bool) {
          this->offLarge_lights_srv_.request.data = false;
          ROS_INFO("Disabling long lights");
          sc.say("LONG LIGHTS DISABLED");
          if (this->offLarge_lights_client_.call(this->offLarge_lights_srv_)) {
            ROS_INFO("TextParserAlgNode:: Call succeeded");
          }
          else {
            ROS_INFO("TextParserAlgNode:: Failed to Call Server on topic command ");
          }
        }
      }
      else if (short_bool) {
        if (light_bool || lights_bool) {
          this->offShort_lights_srv_.request.data = false;
          ROS_INFO("Disabling short lights");
          sc.say("SHORT LIGHTS DISABLED");
          if (this->offShort_lights_client_.call(this->offShort_lights_srv_)) {
            ROS_INFO("TextParserAlgNode:: Call succeeded");
          }
          else {
            ROS_INFO("TextParserAlgNode:: Failed to Call Server on topic command ");
          }
        }
      }
    }
  }
  else sc.say("COMMAND NOT RECOGNIZED");
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

std::vector<std::string> AssistantDealerAlgNode::string_split(std::string input, std::string delimiter) {
  size_t pos = 0;
  std::vector<std::string> token;
  while ((pos = input.find(delimiter)) != std::string::npos) {
      token.push_back(input.substr(0, pos));
      input.erase(0, pos + delimiter.length());
  }
  token.push_back(input);
  return token;
}

void AssistantDealerAlgNode::addNodeDiagnostics(void)
{
}

/* main function */
int main(int argc,char *argv[])
{
  return algorithm_base::main<AssistantDealerAlgNode>(argc, argv, "assistant_dealer_alg_node");
}
