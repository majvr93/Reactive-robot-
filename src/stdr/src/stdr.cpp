#include <ros/ros.h> //Must include this for all ROS cpp projects
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h> //Including the Float32 class from std_msgs
#include <std_msgs/Bool.h> // boolean message time
#include "sensor_msgs/Range.h"
#include <geometry_msgs/Twist.h> // For geometry_msgs : : Twist
#include <stdlib.h> // For rand () and RAND_MAX
#include <math.h>

ros:: Publisher pub;
bool start = true;
double sonar1 = NULL; 
double sonar2 = NULL; 

int sonar = 1;
int x = 0;



void sonarCallback_sonar_2(const sensor_msgs::Range::ConstPtr& m)
{
	sonar2 = m->range;
}

void sonarCallback_sonar_0(const sensor_msgs::Range::ConstPtr& m)
{	
	
	geometry_msgs:: Twist msg;

	sonar1 = m->range;
	ROS_INFO_STREAM("\nOrientacao sonar: " << sonar);
	ROS_INFO_STREAM("\nsonar1: " << sonar1);
	ROS_INFO_STREAM("\nsonar2: " << sonar2);
  	
  	ros:: Rate rate(2);


  	if(sonar == 1)
    {   
      if(sonar1 < 0.8)
      {
        msg.linear.x = 0;
        msg.angular.z = M_PI; 

        /*if(sonar2 < 1)*/ 
        sonar = 2;
        ROS_INFO_STREAM("\n \n  MUDOU PRA SONAR = 2");
      }
      else 
      {
        msg.linear.x = 1;
      }
    }
    
  	else if(sonar == 2)
  	{
  		if(sonar2 <= 2)
      {
           ROS_INFO_STREAM("\n \n MUDOU PARA x = 0");
           x = 0;
      }


  		if(!(sonar2 < 2) && !(sonar1 < 1) && x == 0)  
  		{
  			ROS_INFO_STREAM("\n \n SEM LEITURA DE SENSORES, RODA - PI  ");
       	msg.linear.x = 0;
      	msg.angular.z = -M_PI; 
        x = 1;
  		}
      else if(!(sonar2 < 2) && !(sonar1 < 1)&& x == 1)  
      {
        ROS_INFO_STREAM("\n \n Andar em frente depois de ter rodado (procura de parede)");

        msg.linear.x = 1; 
      }
  		else if(!(sonar1 < 1) && sonar2 < 2) 
  		{
        //ROS_INFO_STREAM("\n \n  SEGUE EM FRENTE");
  			msg.linear.x = 1;
  		} 
  		else if(sonar1 < 1) 
  		{
       // ROS_INFO_STREAM("\n \n  RODA PI  ");
  			msg.linear.x = 0;
      	msg.angular.z = M_PI; 
  		}
    }  
      	
	pub.publish(msg);
  rate.sleep();
 		
} 

int main(int argc, char **argv) 
{
    ros::init(argc, argv, "lab"); //name this node
    ros::NodeHandle nh; 
   
    ros::Subscriber lidar_subscriber = nh.subscribe("robot0/sonar_0", 1, sonarCallback_sonar_0);
    
    ros::Subscriber lidar_subscriber2 = nh.subscribe("robot0/sonar_2", 1, sonarCallback_sonar_2);

    pub = nh.advertise <geometry_msgs:: Twist > ("robot0/cmd_vel" , 1000) ;
	
    srand(time(0));

    ros::spin(); 
    
    return 0; 
}


