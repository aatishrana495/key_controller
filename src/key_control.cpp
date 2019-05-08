#include "key_controller/key_control.h"
 
#include <QApplication>
#include <QKeyEvent>
 
KeyControl::KeyControl(ros::NodeHandle _nh,QWidget *parent) :
    QWidget(parent)
{
    spPub = nh.advertise<pid_controller::Setpoint>("/setpoints", 1, true);
    myLabel = new QLabel("LABEL");
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(myLabel);
    setLayout(mainLayout);

    for(int i=0;i<6;i++)
    {
        spMsg.setpoints.push_back(0);
    }
    spMsg.setpoints[2]=1010;  // heave
    publish_sp(); 
}
 
void KeyControl::keyPressEvent(QKeyEvent *event)
{
    //surge adjustment
    if(event->key() == Qt::Key_W)
    {
	
        spMsg.setpoints[0] = 3;
    }
    
    if(event->key() == Qt::Key_S)
    {
        spMsg.setpoints[0] = -3;
    }


    // sway adjustment
    if(event->key() == Qt::Key_D)
    {
        spMsg.setpoints[1] = 3;
    }
    if(event->key() == Qt::Key_A)
    {
        spMsg.setpoints[1] = -3;
    }

    //heave adjustmnet
    if(event->key() == Qt::Key_Z)
    {
	
        	
	if( spMsg.setpoints[2] > 1025){
		spMsg.setpoints[2] = 1025;
	}
	else if(spMsg.setpoints[2] < 1010){
		spMsg.setpoints[2] = 1010;
	}
	else {
		spMsg.setpoints[2] += 1;
	}
	
    }
    if(event->key() == Qt::Key_Space)
    {
        
	if( spMsg.setpoints[2] > 1025){
		spMsg.setpoints[2] = 1025;
	}
	else if(spMsg.setpoints[2] < 1010){
		spMsg.setpoints[2] = 1010;
	}
	else {
		spMsg.setpoints[2] -= 1;
	}
	
    }

 // yaw adjustment
    if(event->key() == Qt::Key_E)
    {
        if( spMsg.setpoints[5] > 179){
		spMsg.setpoints[5] -= 359;
	}
	else if(spMsg.setpoints[5] < -179){
		spMsg.setpoints[5] +=360;

	}
	else {
		spMsg.setpoints[5] += 1;
	}
    }
    if(event->key() == Qt::Key_Q)
    {
        if( spMsg.setpoints[5] > 179){
		spMsg.setpoints[5] -= 360;
	}
	else if(spMsg.setpoints[5] < -179){
		spMsg.setpoints[5] += 359;

	}
	else {
		spMsg.setpoints[5] -= 1;
	}
    }

    if(event->key() == Qt::Key_R){
	for(int i=0;i<6;i++){
		spMsg.setpoints[i] = 0;
	}
	spMsg.setpoints[2] = 1010;
    }

}
 
void KeyControl::keyReleaseEvent(QKeyEvent *event)
{

    //surge adjustment
    if(event->key() == Qt::Key_W || event->key() == Qt::Key_S)
    {
        spMsg.setpoints[0] = 0;
    }
    
    // sway adjustment
    if(event->key() == Qt::Key_D || event->key() == Qt::Key_A)
    {
        spMsg.setpoints[1] = 0;
    }
    

    
      
    

}

void KeyControl::publish_sp(void)
{    
    spPub.publish(spMsg);
}
