// Copyright (C) 2010-2011 Institut de Robotica i Informatica Industrial, CSIC-UPC.
// Author
// All rights reserved.
//
// This file is part of iri-ros-pkg
// iri-ros-pkg is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// IMPORTANT NOTE: This code has been generated through a script from the
// iri_ros_scripts. Please do NOT delete any comments to guarantee the correctness
// of the scripts. ROS topics can be easly add by using those scripts. Please
// refer to the IRI wiki page for more information:
// http://wikiri.upc.es/index.php/Robotics_Lab

#ifndef _assistant_dealer_alg_node_h_
#define _assistant_dealer_alg_node_h_

#include <iri_base_algorithm/iri_base_algorithm.h>
#include "assistant_dealer_alg.h"
#include <std_srvs/SetBool.h>
// [publisher subscriber headers]
#include <std_msgs/String.h>

// [service client headers]
#include <assistant_dealer/PlaySound.h>
#include <assistant_dealer/ChangeLights.h>
#include <text_parser/Command.h>

// [action server client headers]

/**
 * \brief IRI ROS Specific Algorithm Class
 *
 */
 typedef enum {IDLE,
              GIVE_ORDER
              } state_machine_states;

class AssistantDealerAlgNode : public algorithm_base::IriBaseAlgorithm<AssistantDealerAlgorithm>
{
  private:
    // [publisher attributes]
    ros::Publisher command_to_print_publisher_;
    std_msgs::String command_to_print_String_msg_;


    // [subscriber attributes]

    // [service attributes]
    ros::ServiceServer command_server_;
    bool commandCallback(text_parser::Command::Request &req, text_parser::Command::Response &res);
    pthread_mutex_t command_mutex_;
    void command_mutex_enter(void);
    void command_mutex_exit(void);


    // [client attributes]
    ros::ServiceClient sound_order_client_;
    assistant_dealer::PlaySound sound_order_srv_;

    ros::ServiceClient onShort_lights_client_;
    std_srvs::SetBool onShort_lights_srv_;

    ros::ServiceClient offShort_lights_client_;
    std_srvs::SetBool offShort_lights_srv_;

    ros::ServiceClient onLarge_lights_client_;
    std_srvs::SetBool onLarge_lights_srv_;

    ros::ServiceClient offLarge_lights_client_;
    std_srvs::SetBool offLarge_lights_srv_;

    // [action server attributes]

    // [action client attributes]


    Config config_;
  public:
   /**
    * \brief Constructor
    *
    * This constructor initializes specific class attributes and all ROS
    * communications variables to enable message exchange.
    */
    AssistantDealerAlgNode(void);

   /**
    * \brief Destructor
    *
    * This destructor frees all necessary dynamic memory allocated within this
    * this class.
    */
    ~AssistantDealerAlgNode(void);

  protected:
   /**
    * \brief main node thread
    *
    * This is the main thread node function. Code written here will be executed
    * in every node loop while the algorithm is on running state. Loop frequency
    * can be tuned by modifying loop_rate attribute.
    *
    * Here data related to the process loop or to ROS topics (mainly data structs
    * related to the MSG and SRV files) must be updated. ROS publisher objects
    * must publish their data in this process. ROS client servers may also
    * request data to the corresponding server topics.
    */
    void mainNodeThread(void);

   /**
    * \brief dynamic reconfigure server callback
    *
    * This method is called whenever a new configuration is received through
    * the dynamic reconfigure. The derivated generic algorithm class must
    * implement it.
    *
    * \param config an object with new configuration from all algorithm
    *               parameters defined in the config file.
    * \param level  integer referring the level in which the configuration
    *               has been changed.
    */
    void node_config_update(Config &config, uint32_t level);

   /**
    * \brief node add diagnostics
    *
    * In this abstract function additional ROS diagnostics applied to the
    * specific algorithms may be added.
    */
    void addNodeDiagnostics(void);

    // [diagnostic functions]

    // [test functions]
};

#endif
