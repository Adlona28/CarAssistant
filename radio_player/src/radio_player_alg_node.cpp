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
  sound_play::Sound s1 = sc.waveSound("/home/ferran/Desktop/one piece.wav");
  sound_play::Sound s2 = sc.waveSound("/home/ferran/Desktop/mamma.wav");
  sound_play::Sound s3 = sc.waveSound("/home/ferran/Desktop/maniac.wav");
  sound_play::Sound s4 = sc.waveSound("/home/ferran/Desktop/galway girl.wav");
  sound_play::Sound s5 = sc.waveSound("/home/ferran/Desktop/all star.wav");
  ROS_INFO("RadioPlayerAlgNode::sound_orderCallback: New Request Received!");
  switch(req.order) {
    case 0: //play_song

      sc.stopAll();
      sc.say("MUSIC ACTIVATED");
      sleepok(5, nh);

      if(req.song_to_play == "one piece") s1.play();
      if(req.song_to_play == "mamma") s2.play();
      if(req.song_to_play == "maniac") s3.play();
      if(req.song_to_play == "galway girl") s4.play();
      if(req.song_to_play == "all star") s5.play();

      //std::string song_full_path = path_songs + req.song_to_play + ".wav";
      //const char * char_aux = song_full_path.c_str();
      //sound_play::Sound s1 = sc.waveSound(char_aux);
      //s1.play();
      break;

    case 1: //stop_song
      sc.say("MUSIC OFF");
      sleepok(1, nh);
      sc.stopAll();
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
