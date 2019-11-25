#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "std_msgs/Header.h"
#include "nav_msgs/MapMetaData.h"

#include "quadtree.h"

ros::Publisher map_pub_robot1;
nav_msgs::OccupancyGrid* newGrid;

void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg){
  std_msgs::Header header = msg->header;
  nav_msgs::MapMetaData info = msg->info;
  ROS_INFO("Got map %d %d", info.width, info.height);
  Map map(info.width, info.height);
  for (unsigned int x = 0; x < info.width; x++)
    for (unsigned int y = 0; y < info.height; y++)
      map.Insert(Cell(x,y,info.width,msg->data[x+ info.width * y]));
  newGrid = map.Grid();
  newGrid->header = header;
  newGrid->info = info;
}

int main(int argc, char **argv){
  ros::init(argc, argv, "grid");
  ros::NodeHandle n1;
  ros::Rate r(10);


  map_pub_robot1 = n1.advertise<nav_msgs::OccupancyGrid>("robot_1/map",10);
  ros::Subscriber map_sub = n1.subscribe("client1",10,mapCallback);
  
  
  while (ros::ok())
  {





  

    // Publish the marker
    map_pub_robot1.publish(*newGrid);

    r.sleep();
    ros::spinOnce();

  }
}