#ifndef TEENSYCMAKE_SENSORS2_H_H
#define TEENSYCMAKE_SENSORS2_H_H

#include <Arduino.h>

#include <NXPMotionSense.h>
#include <SensorFusion.cpp>

NXPMotionSense imu;
NXPSensorFusion filter;

void start(){
    imu.begin();
    filter.begin(100);
}

void update(){
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;
    float roll, pitch, heading;

    if (imu.available()) {
        // Read the motion sensors
        imu.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);


        // Update the SensorFusion filter
        filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

        // print the heading, pitch and roll
        roll = filter.getRoll();
        pitch = filter.getPitch();
        heading = filter.getYaw();


        Serial.print("Orientation: ");
        Serial.print(heading);
        Serial.print(" ");
        Serial.print(pitch);
        Serial.print(" ");
        Serial.println(roll);
    }

fRotationVectorDegFromQuaternion()

}

#endif //TEENSYCMAKE_SENSORS2_H_H
