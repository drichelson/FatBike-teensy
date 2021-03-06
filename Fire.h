#ifndef FATBIKE_FIRE_H
#define FATBIKE_FIRE_H

#include <FastLED.h>
#include "FatBike.h"

///// Cooling ranges

//const uint16_t cooling = (coolingMin  + coolingMax) / 2;

//const uint16_t sparking = (sparkingMin + sparkingMax) / 2;

///// Palette ranges
//Set pallette based on 0-10MPH scale.
// 0 = cool:
// blue = 160
// or purple = 192
// aqua = 128
// 10 = hot

//red = 255 or 0
//yellow = 64

// Fire2012 with programmable Color Palette
//
// This code is the same fire simulation as the original "Fire2012",
// but each heat cell's temperature is translated to color through a FastLED
// programmable color palette, instead of through the "HeatColor(...)" function.
//
// Four different static color palettes are provided here, plus one dynamic one.
//
// The three static ones are:
//   1. the FastLED built-in HeatColors_p -- this is the default, and it looks
//      pretty much exactly like the original Fire2012.
//
//  To use any of the other palettes below, just "uncomment" the corresponding code.
//
//   2. a gradient from black to red to yellow to white, which is
//      visually similar to the HeatColors_p, and helps to illustrate
//      what the 'heat colors' palette is actually doing,
//   3. a similar gradient, but in blue colors rather than red ones,
//      i.e. from black to blue to aqua to white, which results in
//      an "icy blue" fire effect,
//   4. a simplified three-step gradient, from black to red to white, just to show
//      that these gradients need not have four components; two or
//      three are possible, too, even if they don't look quite as nice for fire.
//
// The dynamic palette shows how you can change the basic 'hue' of the
// color palette every time through the loop, producing "rainbow fire".

CRGBPalette16 gPal;
//
//void setup() {
//    delay(3000); // sanity delay
//    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.setBrightness( BRIGHTNESS );
//
//    // This first palette is the basic 'black body radiation' colors,
//    // which run from black to red to bright yellow to white.
//    gPal = HeatColors_p;
//
//    // These are other ways to set up the color palette for the 'fire'.
//    // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
//gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
//
//    // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
//    //   gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);
//
//    // Third, here's a simpler, three-step gradient, from black to red to white
//    //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
//
//}

//void loop()
//{
//    // Add entropy to random number generator; we use a lot of it.
//    random16_add_entropy( random());
//
//    // Fourth, the most sophisticated: this one sets up a new palette every
//    // time through the loop, based on a hue that changes every time.
//    // The palette is a gradient from black, to a dark color based on the hue,
//    // to a light color based on the hue, to white.
//    //
//    //   static uint8_t hue = 0;
//    //   hue++;
//    //   CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
//    //   CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
//    //   gPal = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);
//
//
//    Fire2012WithPalette(); // run simulation frame, using palette colors
//
//    FastLED.show(); // display this frame
//    FastLED.delay(1000 / FRAMES_PER_SECOND);
//}


// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
////
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation,
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking.
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100

//180 = ~1/4 circum of the wheel
//#define COOLING  500


// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
//#define SPARKING 200

int16_t cooling = 90;
int16_t sparking = 160;

//CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White
CHSV paletteA = rgb2hsv_approximate(CRGB::Black);
CHSV paletteB = rgb2hsv_approximate(CRGB::DarkRed);
CHSV paletteC = rgb2hsv_approximate(CRGB::Yellow);
CHSV paletteD = rgb2hsv_approximate(CRGB::WhiteSmoke);

//CHSV paletteD = CHSV(39, 77, 255);
//CHSV paletteD = rgb2hsv_approximate(CRGB(39, 77, 255));

static byte heat[(int) NUM_LEDS];


class Fire {
public:
    static Fire &getInstance() {
        static Fire instance;
        return instance;
    }

    void makeFire(byte heat[], uint8_t startInclusive, uint8_t endExclusive) {
        uint8_t ledCount = (uint8_t) (endExclusive - startInclusive + 1);
        for (int i = startInclusive; i < endExclusive; i++) {
            heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / ledCount) + 2));
        }

        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for (int k = endExclusive - 3; k > startInclusive; k--) {
            heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
        }

        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if (random8() < sparking) {
            int y = random8(7);
            heat[y + startInclusive] = qadd8(heat[y], random8(160, 255));
        }
    }

    void renderDoubleFire(uint8_t pixelOnGround, float bikeSpeedMph, boolean isMovingMode, long frameCount) {
        //Uncomment this line so we can tell where we think the ground is
//        fatBike.leds[(int) pixelOnGround] = CRGB::Green;


        /*  This snippet tries to simply visualize the current bike speed
        if (bikeSpeedMph < 5.0) {
            for (int i = 1; i < bikeSpeedMph; i++) {
                fatBike.leds[(uint8_t) FatBike::Forward(pixelOnGround, -i)] = CRGB::Red;
            }
        }
        return;
         */

        preRenderStationaryFire(frameCount);

        makeFire(heat, 0, 122);
        makeFire(heat, 122, 244);

        float thisPixel = pixelOnGround;
        // Step 4.  Map from heat cells to LED colors

        //Render one side:
        for (int j = 0; j < 122; j++) {
            // Scale the heat value from 0-255 down to 0-240
            // for best results with color palettes.
            byte colorindex = scale8(heat[j], 240);
            fatBike.leds[(int) thisPixel] = ColorFromPalette(gPal, colorindex);
            thisPixel = FatBike::Back1(thisPixel);
        }

        //Render the other side:
        thisPixel = FatBike::Forward1(pixelOnGround);
        for (int j = 122; j < 244; j++) {
            // Scale the heat value from 0-255 down to 0-240
            // for best results with color palettes.
            byte colorindex = scale8(heat[j], 240);
            fatBike.leds[(int) thisPixel] = ColorFromPalette(gPal, colorindex);
            thisPixel = FatBike::Forward1(thisPixel);
        }
    }

    void preRenderStationaryFire(long frameCount) {
        uint8_t maxCooling = 100;
        uint8_t minCooling = 30;

        uint8_t maxSparking = 200;
        uint8_t minSparking = 50;

        uint8_t rando = random8();
        uint8_t rando1to5 = (rando / 63) + 1;
        cooling = minCooling + scale8(sin8((uint8_t) (frameCount / 5 % 255)), maxCooling - minCooling);
        sparking = minSparking + scale8(cos8((uint8_t) (frameCount / 6 % 255)), maxSparking - minSparking);
//        Serial.print(cooling);
//        Serial.print(",");
//        Serial.print(sparking);
//        Serial.println();

        gPal = CRGBPalette16(paletteA, paletteB, paletteC, paletteD);
    }

private:
    Fire() :
            fatBike(FatBike::getInstance()),
            currentPosition(0.0F) {}

    FatBike &fatBike;
    float currentPosition;

    //These 2 are to keep the singleton pattern intact
    Fire(Fire const &);              // Don't Implement
    void operator=(Fire const &);
};

#endif //FATBIKE_FIRE2012WITHPALLETE_H
