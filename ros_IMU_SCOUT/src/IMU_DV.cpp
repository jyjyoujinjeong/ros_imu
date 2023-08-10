#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Twist.h>

class SubscribeAndPublish
{
 public:
 SubscribeAndPublish()
 {
  pub_=nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  
  sub_= nh.subscribe("/vectornav/IMU", 1, &SubscribeAndPublish::callback, this);
  }
  
  void callback(const sensor_msgs::Imu::ConstPtr& msg)
  {
  geometry_msgs::Twist t;
  
  
  t.linear.x = msg->linear_acceleration.x ;
  t.angular.z = msg->angular_velocity.z ;
  
  ROS_INFO("speed = %f", t.linear.x);
  ROS_INFO("steer = %f", t.angular.z);
  

  
  
  pub_.publish(t);
  }
  
  private:    
  ros::NodeHandle nh;       // NodeHandle 선언
  ros::Publisher pub_;      // Publisher 선언
  ros::Subscriber sub_;     // Subscriber 선언
  
  
  };
  int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "dv");

  // 모든 것을 처리 할 SubscremibeAndPublish 클래스 개체 'SAPObject' 생성
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}
