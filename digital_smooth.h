#ifndef FATBIKE_DIGITAL_SMOOTH_H_H
#define FATBIKE_DIGITAL_SMOOTH_H_H

#include <Arduino.h>
/* digitalSmooth
 Paul Badger 2007
 A digital smoothing filter for smoothing sensor jitter
 This filter accepts one new piece of data each time through a loop, which the
 filter inputs into a rolling array, replacing the oldest data with the latest reading.
 The array is then transferred to another array, and that array is sorted from low to high.
 Then the highest and lowest %15 of samples are thrown out. The remaining data is averaged
 and the result is returned.

 Every sensor used with the digitalSmooth function needs to have its own array to hold
 the raw sensor values. This array is then passed to the function, for it's use.
 This is done with the name of the array associated with the particular sensor.
 */

//#define SensorPin1      0
//#define SensorPin2      0
#define filterSamples   13              // filterSamples should  be an odd number, no smaller than 3
//int sensSmoothArray1 [filterSamples];   // array for holding raw sensor values for sensor1
//int sensSmoothArray2 [filterSamples];   // array for holding raw sensor values for sensor2
//
//int rawData1, smoothData1;  // variables for sensor1 data
//int rawData2, smoothData2;  // variables for sensor2 data

//void setup(){
//    Serial.begin(9600);
//}
//void loop(){       // test the digitalSmooth function
//    rawData1 = analogRead(SensorPin1);                        // read sensor 1
//    smoothData1 = digitalSmooth(rawData1, sensSmoothArray1);  // every sensor you use with digitalSmooth needs its own array
//
//    Serial.print(rawData1);
//    Serial.print("   ");
//    Serial.println(smoothData1);
//
//    rawData2 = analogRead(SensorPin2);                        // read sensor 2
//    smoothData2 = digitalSmooth(rawData2, sensSmoothArray2);  // every sensor you use with digitalSmooth needs its own array
//
//}

int digitalSmooth(int rawIn,
                  int *sensSmoothArray) {     // "int *sensSmoothArray" passes an array to the function - the asterisk indicates the array name is a pointer
    int j, k, temp, top, bottom;
    long total;
    static int i;
    // static int raw[filterSamples];
    static int sorted[filterSamples];
    boolean done;

    i = (i + 1) %
        filterSamples;    // increment counter and roll over if necc. -  % (modulo operator) rolls over variable
    sensSmoothArray[i] = rawIn;                 // input new data into the oldest slot

    // Serial.print("raw = ");

    for (j = 0; j < filterSamples; j++) {     // transfer data array into anther array for sorting and averaging
        sorted[j] = sensSmoothArray[j];
    }

    done = 0;                // flag to know when we're done sorting
    while (done != 1) {        // simple swap sort, sorts numbers from lowest to highest
        done = 1;
        for (j = 0; j < (filterSamples - 1); j++) {
            if (sorted[j] > sorted[j + 1]) {     // numbers are out of order - swap
                temp = sorted[j + 1];
                sorted[j + 1] = sorted[j];
                sorted[j] = temp;
                done = 0;
            }
        }
    }

/*
  for (j = 0; j < (filterSamples); j++){    // print the array to debug
    Serial.print(sorted[j]);
    Serial.print("   ");
  }
  Serial.println();
*/

    // throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
    bottom = max(((filterSamples * 15) / 100), 1);
    top = min((((filterSamples * 85) / 100) + 1),
              (filterSamples - 1));   // the + 1 is to make up for asymmetry caused by integer rounding
    k = 0;
    total = 0;
    for (j = bottom; j < top; j++) {
        total += sorted[j];  // total remaining indices
        k++;
        // Serial.print(sorted[j]);
        // Serial.print("   ");
    }

//  Serial.println();
//  Serial.print("average = ");
//  Serial.println(total/k);
    return total / k;    // divide by number of samples
}

#endif //FATBIKE_DIGITAL_SMOOTH_H_H
