#include <QtGui>
#include "key_controller/key_control.h"
 
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "key_controller");
    ros::NodeHandle nh;
    QApplication a(argc, argv);
    KeyControl w(nh);
    w.show();
    
    ros::Rate rate(15);
    while(ros::ok() && w.isVisible())
    {
        a.processEvents();
	w.publish_sp();
        rate.sleep();
        
    }
 
    
}
