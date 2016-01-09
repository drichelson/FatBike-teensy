#ifndef TEENSYCMAKE_FLASH_H
#define TEENSYCMAKE_FLASH_H

#define CS_PIN 10
#define SI_PIN 11
#define SO_PIN 12
#define SCK_PIN 13
#define FILE_NAME "log.txt"

#include <SerialFlash.h>
#include <SPI.h>

SerialFlashFile file;

void initFlash() {
    SPI.setCS(CS_PIN);
    SPI.setMOSI(SI_PIN);
    SPI.setMISO(SO_PIN);
    SPI.setSCK(SCK_PIN);

    if (!SerialFlash.begin(CS_PIN)) {
        Serial.println("Unable to access SPI Flash chip");
    }

    SerialFlash.opendir();

    if (SerialFlash.exists(FILE_NAME)) {
        Serial.println(F("File exists, so we'll delete it"));
        SerialFlash.remove(FILE_NAME);
    }
    //create 1MBit file
    if (!SerialFlash.createErasable(FILE_NAME, 1000000)) {
        Serial.println(F("Could not create file"));
    }

    file = SerialFlash.open(FILE_NAME);
    if (file) {  // true if the file exists
        Serial.println(F("Found file"));
        Serial.println(file.size());
    }
    else {
        Serial.println("Unable to access file");
    }
    char bufferA[1] = {'a'};
    char bufferB[2] = {'b', 'b'};
    char bufferC[3] = {'c', 'c', 'c'};

    Serial.println(file.write(bufferA, 1));
    Serial.println(file.write(bufferB, 2));
    Serial.println(file.write(bufferC, 3));

//    char readBuffer[6];
//    file.seek(0);
//    file.read(readBuffer, 6);
//    Serial.println(readBuffer);
    file.close();
}

#endif //TEENSYCMAKE_FLASH_H
