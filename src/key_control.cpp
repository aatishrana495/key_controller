#include "key_controller/key_control.h"

#include <QApplication>
#include <QKeyEvent>

KeyControl::KeyControl(ros::NodeHandle _nh, QWidget *parent) : QWidget(parent) {
  spPub = nh.advertise<pid_controller::Setpoint>("/setpoints", 1, true);
  myLabel = new QLabel("LABEL");
  mainLayout = new QVBoxLayout;
  mainLayout->addWidget(myLabel);
  setLayout(mainLayout);

  for (int i = 0; i < 6; i++) {
    spMsg.setpoints.push_back(0);
  }
  spMsg.setpoints[2] = 935; // heave
  publish_sp();
}

void KeyControl::keyPressEvent(QKeyEvent *event) {
  // surge adjustment
  if (event->key() == Qt::Key_W) {

    spMsg.setpoints[0] = 5;
  }

  if (event->key() == Qt::Key_S) {
    spMsg.setpoints[0] = -5;
  }
  // continuous surge adjustment
  if (event->key() == Qt::Key_I) {

    spMsg.setpoints[0] = 5;
  }

  if (event->key() == Qt::Key_K) {
    spMsg.setpoints[0] = -5;
  }

  // sway adjustment
  if (event->key() == Qt::Key_D) {
    spMsg.setpoints[1] = 5;
  }
  if (event->key() == Qt::Key_A) {
    spMsg.setpoints[1] = -5;
  }

  // continuous sway adjustment
  if (event->key() == Qt::Key_L) {
    spMsg.setpoints[1] = 5;
  }
  if (event->key() == Qt::Key_J) {
    spMsg.setpoints[1] = -5;
  }

  // heave adjustmnet
  if (event->key() == Qt::Key_Z) {

    if (spMsg.setpoints[2] > 1180) {
      spMsg.setpoints[2] = 1180;
    } else if (spMsg.setpoints[2] < 950) {
      spMsg.setpoints[2] = 950;
    } else {
      spMsg.setpoints[2] += 10;
    }
  }
  if (event->key() == Qt::Key_Space) {

    if (spMsg.setpoints[2] > 1180) {
      spMsg.setpoints[2] = 1180;
    } else if (spMsg.setpoints[2] < 950) {
      spMsg.setpoints[2] = 950;
    } else {
      spMsg.setpoints[2] -= 10;
    }
  }

  // yaw adjustment
  if (event->key() == Qt::Key_E) {
    if (spMsg.setpoints[5] > 179) {
      spMsg.setpoints[5] -= 359;
    } else if (spMsg.setpoints[5] < -179) {
      spMsg.setpoints[5] += 360;

    } else {
      spMsg.setpoints[5] += 1;
    }
  }
  if (event->key() == Qt::Key_Q) {
    if (spMsg.setpoints[5] > 179) {
      spMsg.setpoints[5] -= 360;
    } else if (spMsg.setpoints[5] < -179) {
      spMsg.setpoints[5] += 359;

    } else {
      spMsg.setpoints[5] -= 1;
    }
  }

  if (event->key() == Qt::Key_R) {
    for (int i = 0; i < 6; i++) {
      spMsg.setpoints[i] = 0;
    }
    spMsg.setpoints[2] = 0;
  }
  // reset setpoints of sway and surge
  if (event->key() == Qt::Key_R) {
    spMsg.setpoints[0] = 0;
    spMsg.setpoints[1] = 0;
  }
}

void KeyControl::keyReleaseEvent(QKeyEvent *event) {

  // surge adjustment
  if (event->key() == Qt::Key_W || event->key() == Qt::Key_S) {
    spMsg.setpoints[0] = 0;
  }

  // sway adjustment
  if (event->key() == Qt::Key_D || event->key() == Qt::Key_A) {
    spMsg.setpoints[1] = 0;
  }
}

void KeyControl::publish_sp(void) { spPub.publish(spMsg); }
