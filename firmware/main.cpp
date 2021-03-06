#include "Particle.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

void startupTasks()
{
        RGB.control(true);
        RGB.brightness(255);
}

STARTUP(startupTasks());

int red, green, blue;
int lastRed, lastGreen, lastBlue;

int setColorCloud(const char* args) // dim to off and then dim to new color
{
        int fadeRed, fadeGreen, fadeBlue;

        lastRed = red;
        lastGreen = green;
        lastBlue = blue;

        // parse arguments to get red,green,blue
        if (sscanf(args, "%d,%d,%d", &red, &green, &blue) < 3) {
                return -1; // bail if not all 3 colors are provided
        }

        for (int i = 0; i <= max(max(lastRed,lastGreen),lastBlue); i++) // fade out
        {
                fadeRed = constrain(lastRed - i, 0, 255);
                fadeGreen = constrain(lastGreen - i, 0, 255);
                fadeBlue = constrain(lastBlue - i, 0, 255);

                RGB.color(fadeRed, fadeGreen, fadeBlue);
                delay(1);
        }

        for (int i = max(max(red,green),blue); i>=0; i--) // fade in
        {
                fadeRed = constrain(red - i, 0, red);
                fadeGreen = constrain(green - i, 0, green);
                fadeBlue = constrain(blue - i, 0, blue);

                RGB.color(fadeRed, fadeGreen, fadeBlue);
                delay(1);
        }

        return red * 1000000 + green * 1000 + blue;
}

int setColor(int redF, int greenF, int blueF) // dim to off and then dim to new color
{
        char message[50];
        snprintf(message, sizeof(message), "%d,%d,%d", redF, greenF, blueF);

        Serial.println("Happy New Year!");

        return setColorCloud(message);
}

void setup() // Put setup code here to run once
{
  Serial.begin(115200);
}

void loop() // Put code here to loop forever
{
        setColor(255, 0, 0);   // RED
        setColor(255, 255, 0); // YELLOW
        setColor(0, 255, 0);   // GREEN
        setColor(0, 255, 255); // CYAN
        setColor(0, 0, 255);   // BLUE
        setColor(255, 0, 255); // MAGENTA
}
