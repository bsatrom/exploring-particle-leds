/*
 * Project RGB_LED_Tester
 * Description:  Example project for controlling the onboard Particle RGB LED with potentiometers
 * Author: Brandon Satrom <brandon@particle.io>
 * Date: 04/17/2018
 */

// Potentiometer pins
#define RED_POT A0
#define GREEN_POT A1
#define BLUE_POT A2
#define BRIGHTNESS_POT A3
#define BLINK_RATE_POT A4

// Variables for
int isAppControlled = 0;
int redValue = 0;
int greenValue = 0;
int blueValue = 0;
int blinkRateValue = 0;

// Particle class for controling the LED
LEDStatus blinkLED;

void setup()
{
  Particle.function("setRed", setRed);
  Particle.function("setGreen", setGreen);
  Particle.function("setBlue", setBlue);
  Particle.function("setBlinkRate", setBlink);
  Particle.function("toggleCtrl", toggleCtrl);

  Particle.variable("red", redValue);
  Particle.variable("green", greenValue);
  Particle.variable("blue", blueValue);
  Particle.variable("blinkRate", blinkRateValue);
  Particle.variable("controlled", isAppControlled);
}

void loop()
{
  if (isAppControlled) {
    // Use the Particle Variable values
    useLEDStatusClass(redValue, greenValue, blueValue, blinkRateValue);
  } else {
    useRGBClass();
  }
}

int setRed(String val) {
  redValue = val.toInt();

  return 1;
}

int setGreen(String val) {
  greenValue = val.toInt();

  return 1;
}

int setBlue(String val) {
  blueValue = val.toInt();

  return 1;
}

int setBlink(String val) {
  blinkRateValue = val.toInt();

  return 1;
}

int toggleCtrl(String val) {
  isAppControlled = val.toInt();

  return 1;
}

void useRGBClass() {
  // Physical position is flipped on board to provide a more natual left to right feel,
  // so we subtract our final value from 255 to "flip" it.
  // analogRead values are divided by 16 to convert from a 4095 max to 255.
  int red = 255 - analogRead(RED_POT) / 16;
  int green = 255 - analogRead(GREEN_POT) / 16;
  int blue = 255 - analogRead(BLUE_POT) / 16;

  RGB.control(true);

  int brightnessPotVal = 255 - analogRead(BRIGHTNESS_POT) / 16;

  // Map R, G, B Pots to R, G, B values for the LED
  RGB.color(red, blue, green);

  // Use mirrorTo and just map the pins
  // RGB.mirrorTo(RED_POT, GREEN_POT, BLUE_POT);

  // Map brightness pot to value
  RGB.brightness(brightnessPotVal);
}

void useLEDStatusClass(int red, int green, int blue, int blinkRate) {
  // Set to false in case we're switching between modes
  RGB.control(false);

  LEDSpeed blinkSpeed = LED_SPEED_SLOW;

  // Convert the R, G, B values to Hex with some fancy bit shifting
  long RGBHex = (red << 16) | (green << 8) | blue;

  // Set the blink rate
  switch(blinkRate) {
    case 0:
      blinkSpeed = LED_SPEED_SLOW;
      break;
    case 1:
      blinkSpeed = LED_SPEED_NORMAL;
      break;
    case 2:
      blinkSpeed = LED_SPEED_FAST;
      break;
  }

  // Set the color, pattern and speed and activate our LED
  blinkLED.setColor(RGBHex);
  blinkLED.setPattern(LED_PATTERN_BLINK);
  blinkLED.setSpeed(blinkSpeed);
  // blinkLED.setSpeed((LEDSpeed)blinkRate);
  if (!blinkLED.isActive()) blinkLED.setActive(true);
}
