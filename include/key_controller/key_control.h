#ifndef KEY_CONTROL_H
#define KEY_CONTROL_H
 
#include <QWidget>
#include <QtGui>
#include <fstream>
#include <iostream>
#include <thread>
#include <future>

#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/Int16.h>

#include <pid_controller/Setpoint.h>

#include <hammerhead/hammerhead.h>

 
class KeyControl : public QWidget
{
    Q_OBJECT
public:
   explicit KeyControl(ros::NodeHandle _nh,QWidget *parent = 0);
   void publish_sp(void);
protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    
private:
    QLabel *myLabel;
    QVBoxLayout *mainLayout;
    ros::NodeHandle nh;
    pid_controller::Setpoint spMsg;
    ros::Publisher spPub;
    int count;
    
};
 
#endif // KEY_CONTROL_H
