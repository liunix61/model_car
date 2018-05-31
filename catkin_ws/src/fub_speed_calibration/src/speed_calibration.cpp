#include "speed_calibration.h"

#define MIN_SPEED 100
#define MAX_SPEED 1000
#define SPEED_STEP 50

namespace fub_speed_calibration {

SpeedCalibration::SpeedCalibration(ros::NodeHandle& nh) {
    twistSubscriber = nh.subscribe("/twist", 1, &SpeedCalibration::onTwist, this);
    speedPublisher = nh.advertise<std_msgs::Int16>("/manual_control/speed", 1);

    startMeasurementTimer = nh.createTimer(ros::Duration(5), &SpeedCalibration::onStartMeasurement, this, true, false);
    stopMeasurementTimer = nh.createTimer(ros::Duration(10), &SpeedCalibration::onStopMeasurement, this, true, false);
    increaseSpeedTimer = nh.createTimer(ros::Duration(1), &SpeedCalibration::onIncreaseSpeed, this, true, true);

    speedMsg.data = MIN_SPEED - SPEED_STEP;
}

void SpeedCalibration::onTwist(geometry_msgs::TwistPtr const &twist) {
    measurements.push_back(twist);
}

void SpeedCalibration::onIncreaseSpeed(ros::TimerEvent const &event) {
    std_msgs::Int16 speedMsg;
    speedMsg.data += SPEED_STEP;

    if (speedMsg.data <= MAX_SPEED) {
        ROS_INFO("Setting speed to %d", speedMsg.data);

        startMeasurementTimer.stop();
        startMeasurementTimer.setPeriod(ros::Duration(5));
        startMeasurementTimer.start();

        speedPublisher.publish(speedMsg);
    } else {
        ROS_INFO("Calibration finished");
    }
}

void SpeedCalibration::onStartMeasurement(ros::TimerEvent const &event) {
    measurements.clear();
    ROS_INFO("Starting measurement for speed %d", speedMsg.data);

    stopMeasurementTimer.stop();
    stopMeasurementTimer.setPeriod(ros::Duration(10));
    stopMeasurementTimer.start();
}

void SpeedCalibration::onStopMeasurement(ros::TimerEvent const &event) {

    double averageSpeed = 0;
    for (const auto &twist : measurements) {
        averageSpeed += twist->linear.x / measurements.size();
    }

    ROS_INFO("Average speed for command %d: %f", speedMsg.data, averageSpeed);

    increaseSpeedTimer.stop();
    increaseSpeedTimer.setPeriod(ros::Duration(1));
    increaseSpeedTimer.start();
}

}