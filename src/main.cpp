#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10;
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "Hello Philip ";
int wait = 50; // In milliseconds

int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels

// MOSI (11) -> DIN
// SCK  (13)-> CLK
// SS (10) -> CS

void setup()
{
  matrix.setIntensity(7);
  matrix.setPosition(0, 0, 0);
  matrix.setRotation(0, 1); // Rotate 90
}

void loop()
{
  for (unsigned int i = 0; i < width * tape.length() + matrix.width() - 1 - spacer; i++)
  {

    matrix.fillScreen(LOW);

    unsigned int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while (x + width - spacer >= 0 && letter >= 0)
    {
      if (letter < tape.length())
      {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }

    matrix.write(); // Send bitmap to display

    delay(wait);
  }
}