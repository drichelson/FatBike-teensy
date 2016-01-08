#ifndef FATBIKE_SENSORS_H
#define FATBIKE_SENSORS_H

#include <Arduino.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_LSM303_U.h>
#include "Adafruit_9DOF.h"
#include "FatBike.h"
#include "digital_smooth.h"

//Sensor setup, reading, unit conversion, and fitting for https://www.adafruit.com/products/1714

#define PIXELS_BETWEEN_SENSOR_AND_ZERO_PIXEL 20.0F
#define SPEED_FACTOR 1.256636F

Adafruit_9DOF dof = Adafruit_9DOF();
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
int speedSmoothingArray[filterSamples];

float sensorPitchTo360Scale(float sensorDegrees) {
    if (sensorDegrees > 0) {
        return 360.0F - sensorDegrees;
    }
    else {
        return -sensorDegrees;
    }
}

float getBikeSpeedMph() {
    sensors_event_t event;
//    long gyroStartMicros = micros();

    //NOTE: This takes about 1ms
    gyro.getEvent(&event);
//    float gyroMicros = (micros() - gyroStartMicros) / 1000.0 ;
//    Serial.print(F("Gyro sensor time (ms):  "));
//    Serial.println(gyroMicros);

    // 1mph = 1.2566 rad/sec
    // 10mph = 12.56636 rad/sec
    float y = -event.gyro.y;
    if (y < 0.113636364) y = 0.0F; //if rolling backwards or less than 2"/sec

    float speedMph = y / SPEED_FACTOR;
    int speedAsInt = (int) (speedMph * 1000.0F);

    int smoothedSpeed = digitalSmooth(speedAsInt, speedSmoothingArray);
    return smoothedSpeed / 1000.0F;
}

uint8_t getPixelOnGround() {
    sensors_event_t accel_event;
    sensors_vec_t orientation;

//    long startMicros = micros();
    //NOTE: This takes about 1ms
    accel.getEvent(&accel_event);
//    float timeMicros = micros() - startMicros ;
    
//    Serial.print(F("Accel sensor time (micros):  "));
//    Serial.println(timeMicros);

    if (dof.accelGetOrientation(&accel_event, &orientation)) {
        /* 'orientation' should have valid .roll and .pitch fields */
//        Serial.print("Roll: ");
//        Serial.print(orientation.roll);
//        Serial.print("; ");

//        Serial.print("Pitch: ");
//        Serial.print(orientation.pitch);
//        Serial.println("");
    }
    float normalizedDegrees = sensorPitchTo360Scale(orientation.pitch);

    uint8_t thisPixel = (uint8_t) ((normalizedDegrees / 360.0F) * (NUM_LEDS - 1));
    return (uint8_t) FatBike::Forward(thisPixel, PIXELS_BETWEEN_SENSOR_AND_ZERO_PIXEL);
//    return (uint8_t) digitalSmooth(pixelOnGround, pixelOnGroundSmoothingArray);
}

void initSensors() {
    if (!gyro.begin()) {
        /* There was a problem detecting the L3GD20 ... check your connections */
        Serial.print(F("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!"));
        while (1);
    }
    if (!accel.begin()) {
        /* There was a problem detecting the LSM303 ... check your connections */
        Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
        while (1);
    }
}

void addSensorEntropy() {
    sensors_event_t event;
    gyro.getEvent(&event);
    random16_add_entropy((uint16_t) (micros() / event.magnetic.heading));
}
//
//uint16_t getRandomSeed() {
//    sensors_event_t event;
//    gyro.getEvent(&event);
//    unsigned long micros1 = micros();
//    Serial.println(micros1);
//    float heading = event.magnetic.heading;
//    Serial.println(heading);
//    float pitch = event.magnetic.pitch;
//    Serial.println(pitch);
//
//    float current = event.current;
//    Serial.println(current);
//    return 100;
//}
//
//void showGyro() {
//    sensors_event_t event;
//    gyro.getEvent(&event);
//    Serial.print("GYRO  ");
//    Serial.print("X: ");
//    Serial.print(event.gyro.x);
//    Serial.print("  ");
//    Serial.print("Y: ");
//    Serial.print(event.gyro.y);
//    Serial.print("  ");
//    Serial.print("Z: ");
//    Serial.print(event.gyro.z);
//    Serial.print("  ");
//    Serial.println("rad/s ");
//
//    Serial.println("");
////    delay(100);
//}

#endif //FATBIKE_SENSORS_H
