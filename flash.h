#ifndef TEENSYCMAKE_FLASH_H
#define TEENSYCMAKE_FLASH_H

#define CS_PIN 10
#define SI_PIN 11
#define SO_PIN 12
#define SCK_PIN 13
#define FILE_NAME "log.txt"
#define FILE_SIZE 10000000

#include <SerialFlash.h>
#include <SPI.h>

SerialFlashFile file;
bool writeMode = false;
bool erase = true;

uint32_t write(String toWrite) {
    int length = toWrite.length();
//    Serial.print("Length: ");
//    Serial.println(length);
//    Serial.print("chars: ");
    unsigned char chars[length];
    toWrite.getBytes(chars, length + 1, 0);
//    for (int i = 0; i < length; i++) {
//        Serial.println(chars[i]);
//    }
//    Serial.println(chars);
//    char bufferC[3] = {'c', 'c', 'c'};
    return file.write(&chars, length);
//    return file.write(bufferC, 3);
}

void initFlash() {
    Serial.println("Initializing Flash");
    SPI.setCS(CS_PIN);
    SPI.setMOSI(SI_PIN);
    SPI.setMISO(SO_PIN);
    SPI.setSCK(SCK_PIN);

    if (!SerialFlash.begin(CS_PIN)) {
        Serial.println("Unable to access SPI Flash chip");
        exit(1);
    }


//    SerialFlash.opendir();

    if (writeMode) {
        if (erase) {
            Serial.println("Erasing flash...");
            SerialFlash.eraseAll();
            while (!SerialFlash.ready()) {
                delay(10);
                // wait, 30 seconds to 2 minutes for most chips
            }
        }

        if (SerialFlash.exists(FILE_NAME)) {
            Serial.println(F("File exists, so we'll delete it"));

            if (!SerialFlash.remove(FILE_NAME)) {
                Serial.println("Could not erase file!");
                exit(1);
            };
        }
        //create 1MBit file
        Serial.println("Creating file..");
        if (!SerialFlash.createErasable(FILE_NAME, FILE_SIZE)) {
            Serial.println(F("Could not create file"));
            exit(1);
        }
    }
    file = SerialFlash.open(FILE_NAME);
    if (file) {  // true if the file exists
        Serial.println(F("Found file"));
        Serial.println(file.size());
    }
    else {
        Serial.println("Unable to access file");
        exit(1);
    }

    if (writeMode) {
//        FatBike *fatBike;
//        fatBike = &FatBike::getInstance();
        write(String("Starting..."));
        while (true) {
            String timeString = String(millis(), DEC);
            //read some sensor data:
            sensors_event_t accel_event;
            sensors_vec_t orientation;

            if (!accel.getEvent(&accel_event)) {
                Serial.println("Error calling getEvent;");
                exit(1);
            }
            if (!dof.accelGetOrientation(&accel_event, &orientation)) {
                Serial.println("Error calling accelGetOrientation;");
                exit(1);
            }
//            String h = String(orientation.heading, 3);
            String p = String(orientation.pitch, 3);
            String r = String(orientation.roll, 3);

            sensors_event_t event;

            if (!gyro.getEvent(&event)) {
                Serial.println("Error calling gyro.getEvent;");
                exit(1);
            }

            String x = String(event.gyro.x, 3);
            String y = String(event.gyro.y, 3);
            String z = String(event.gyro.z, 3);

            int pixelOnGround = getPixelOnGround();
            String pixelOnGroundStr = String(pixelOnGround);
            String bikeSpeedMph = String(getBikeSpeedMph(), 3);
            String bikeSpeedMphRaw = String(getBikeSpeedMphRaw(), 3);

            String toWrite = String(
                    timeString + ',' + p + ',' + r + ',' + x + ',' + y + ',' + z + ',' + pixelOnGroundStr + ',' +
                    bikeSpeedMph + ',' + bikeSpeedMphRaw + ';');

            if (write(toWrite) <= 0) {
                Serial.println("Could not write string!");
                exit(1);
            }
            Serial.print(".");
//            fatBike->leds[pixelOnGround] = CRGB::White;
//            FastLED.show();
//            fatBike->clearAll();
            //        }
            delay(5);

//            file.close();
//            exit(0);
        }
    } else {
        char readBuffer[5000];
        Serial.println();

        for (int i = 0; i < FILE_SIZE; i += 5000) {
            if (file.available() > 0) {
                file.seek(i);
//            Serial.println();
//            Serial.println(i);
                if (file.read(readBuffer, 5000) > 0) {
                    Serial.print(readBuffer);
//                Serial.println();
//                Serial.println();
                }
                else
                    break;
                delay(50);
            }
        }
        file.close();
        exit(0);
    }
}

void read() {
    char readBuffer[10];
    file.seek(0);
    file.read(readBuffer, 10);
    Serial.println(readBuffer);
    // file.close();
}

#endif //TEENSYCMAKE_FLASH_H
