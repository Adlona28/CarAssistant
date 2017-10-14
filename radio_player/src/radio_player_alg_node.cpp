#include "radio_player_alg_node.h"

RadioPlayerAlgNode::RadioPlayerAlgNode(void) :
  algorithm_base::IriBaseAlgorithm<RadioPlayerAlgorithm>()
{
  //init class attributes if necessary
  //this->loop_rate_ = 2;//in [Hz]
  this->first_iteration = true;
  // [init publishers]

  // [init subscribers]

  // [init services]
  this->sound_order_server_ = this->public_node_handle_.advertiseService("sound_order", &RadioPlayerAlgNode::sound_orderCallback, this);
  pthread_mutex_init(&this->sound_order_mutex_,NULL);


  // [init clients]

  // [init action servers]

  // [init action clients]
}

RadioPlayerAlgNode::~RadioPlayerAlgNode(void)
{
  // [free dynamic memory]
  pthread_mutex_destroy(&this->sound_order_mutex_);
}

void RadioPlayerAlgNode::mainNodeThread(void)
{
  if (this->first_iteration) {
    ros::NodeHandle n("~");
    if (n.getParam("path_songs", path_songs)) {
      this->first_iteration = false;
      ROS_INFO("SONGS PATH READ");
    }
    else {
      ROS_WARN("UNABLE TO READ SONGS PATH");
      exit(1);
    }
  }
  // [fill msg structures]

  // [fill srv structure and make request to the server]

  // [fill action structure and make request to the action server]

  // [publish messages]
}

/*  [subscriber callbacks] */

/*  [service callbacks] */
bool RadioPlayerAlgNode::sound_orderCallback(assistant_dealer::PlaySound::Request &req, assistant_dealer::PlaySound::Response &res)
{
  ROS_INFO("RadioPlayerAlgNode::sound_orderCallback: New Request Received!");
  std::map<std::string, sound_play::Sound>::iterator it;
  switch(req.order) {
    case 0: //play_song
    //path_songs + req.song_to_play + ".wav"
      it = songs_playing.find(req.song_to_play);
      if (it == songs_playing.end()) {
        sc.say("MUSIC ACTIVATED");
        //songs_playing[req.song_to_play] = sc.waveSound("/home/ferran/Desktop/AllStar.wav"););
        for (it = songs_playing.begin(); it != songs_playing.end(); ++it) {
          it->second.stop();
        }
        //songs_playing[req.song_to_play].play();
      }
      break;

    case 1: //stop_song
      for (it = songs_playing.begin(); it != songs_playing.end(); ++it) {
        it->second.stop();
      }
      break;
  }
  return true;
}

void RadioPlayerAlgNode::sound_order_mutex_enter(void)
{
  pthread_mutex_lock(&this->sound_order_mutex_);
}

void RadioPlayerAlgNode::sound_order_mutex_exit(void)
{
  pthread_mutex_unlock(&this->sound_order_mutex_);
}


/*  [action callbacks] */

/*  [action requests] */
void RadioPlayerAlgNode::sleepok(int t, ros::NodeHandle &nh) {
   if (nh.ok()) sleep(t);
}

void RadioPlayerAlgNode::node_config_update(Config &config, uint32_t level)
{
  this->alg_.lock();
  this->config_=config;
  this->alg_.unlock();
}

void RadioPlayerAlgNode::addNodeDiagnostics(void)
{
}

/* main function */
int main(int argc,char *argv[])
{
  return algorithm_base::main<RadioPlayerAlgNode>(argc, argv, "radio_player_alg_node");
}
