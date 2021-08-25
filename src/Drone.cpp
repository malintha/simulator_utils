//
// Created by malintha on 10/14/20.
//
#include <iostream>
#include "Drone.h"

using namespace std;

simulator_utils::Waypoint Drone::get_state() const {
//    ROS_DEBUG_STREAM("state: "<<state.position.x << " "<< state.position.y << " " << state.position.z);
    return this->state;
}

void Drone::state_cb(const simulator_utils::WaypointConstPtr &wp) {
    this->state.position = wp->position;
    this->state.velocity = wp->velocity;
    this->state.acceleration = wp->acceleration;
}

Drone::Drone(int id, const ros::NodeHandle &n):id(id), nh(n) {
    stringstream ss;
    ss << "/robot_"<<to_string(id)<<"/current_state";
    this->state_sub = nh.subscribe(ss.str(), 1,
                                   &Drone::state_cb,
                                   this);

    ROS_DEBUG_STREAM("Robot: "<<id<<" Waiting for quadrotor states.");
    ros::topic::waitForMessage<simulator_utils::Waypoint>(ss.str(), ros::Duration(5));
}
