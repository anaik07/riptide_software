#ifndef PS3_CONTROLLER_H
#define PS3_CONTROLLER_H

#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Vector3.h"
#include "tf/transform_listener.h"
#include "riptide_teleop/ps3_button_mapping.h"
#include "riptide_msgs/Imu.h"
#include "riptide_msgs/DepthCommand.h"
#include "riptide_msgs/ResetControls.h"

class PS3Controller
{
 private:
  ros::NodeHandle nh;
  ros::Publisher attitude_pub, depth_pub, lin_accel_pub, reset_pub;
  ros::Subscriber joy_sub;

  geometry_msgs::Vector3 cmd_attitude, cmd_accel, delta_attitude;
  riptide_msgs::DepthCommand cmd_depth;
  riptide_msgs::ResetControls reset_msg;
  bool isReset, isStarted, isInit, isDepthWorking;
  tf::Vector3 tf;
  int rt;
  double delta_depth, mass, volume, stable_z_accel;

  // Max values, and command ates
  double MAX_ROLL, MAX_PITCH, MAX_DEPTH, MAX_XY_ACCEL, MAX_Z_ACCEL;
  double CMD_ROLL_RATE, CMD_PITCH_RATE, CMD_YAW_RATE, CMD_DEPTH_RATE;

  // Multiplication Factors (based on command rates)
  double roll_factor, pitch_factor, yaw_factor, depth_factor;
  bool surge_factor, sway_factor, heave_factor;

  void InitMsgs();
  double Constrain(double current, double max);
  void UpdateCommands();
  void PublishCommands();

 public:
  PS3Controller();
  void LoadProperty(std::string name, double &param);
  void JoyCB(const sensor_msgs::Joy::ConstPtr& joy);
  void ImuCB(const riptide_msgs::Imu::ConstPtr& imu_msg);
  void Loop();
};

#endif
