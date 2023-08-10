#include <ros/ros.h>
#include<sensor_msgs/Imu.h>
#include<geometry_msgs/Twist.h>

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    pub_ = n_.advertise<geometry_msgs::Twist>("/cms_vel", 1);

    //Topic you want to subscribe
    sub_ = n_.subscribe("/vectornav/IMU", 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const sensor_msgs::Imu& it)
  {
    	
    geometry_msgs::Twist I;
    
    I.linear.x = it.linear_acceleration.x *(-1);
    I.linear.y = it.linear_acceleration.y;
    I.angular.z = it.angular_velocity.z *(-1);
    
    //.... do something with the input and generate the output...
    pub_.publish(I);
  }

private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "subscribe_and_publish");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}
