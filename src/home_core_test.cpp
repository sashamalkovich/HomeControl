#include <Arduino.h>
#include "home_core.h"
long timer;

class A : public HomeCore
{
public:
   explicit A()
    {
        e = new int *[7];
        for (int i = 0; i < 7; i++)
        {
            for (int y = 0; y < 7; y++)
            {
                e[i][y] = 0;
            }
        }
    }
    void run();

    void setup();

    int **e;

private:
};

void A::run()
{
    e = runCore();
    e[4] = response();
    pLcd->setCursor(0, 0);
    pLcd->print(e[2][0]);
    pLcd->print(":");
    pLcd->print(e[2][1]);
    pLcd->print(":");
    pLcd->print(e[2][2]);
    pLcd->print(":");
    pLcd->print(e[2][3]);
    pLcd->print(" ");

    pLcd->setCursor(0, 1);
    pLcd->print(e[0][0]);
    pLcd->print(":");
    pLcd->print(e[0][1]);
    pLcd->print(" ");

    pLcd->setCursor(0, 2);
    pLcd->print(e[1][0]);
    pLcd->print(":");
    pLcd->print(e[1][1]);
    pLcd->print(" ");

    pLcd->setCursor(0, 3);
    pLcd->print(e[3][1]);
    pLcd->print(":");
    pLcd->print(e[3][2]);
    pLcd->print(":");
    pLcd->print(e[3][3]);
    pLcd->print(":");
    pLcd->print(e[3][4]);
    pLcd->print(":");
    pLcd->print(e[3][5]);
    pLcd->print(":");
    pLcd->print(e[3][6]);
    pLcd->print(" ");

    pLcd->setCursor(11, 2);
    pLcd->print(e[4][0]);
    pLcd->print(":");
    pLcd->print(e[4][1]);
    pLcd->print(" ");
}

void A::setup()
{
    setupCore();
}

A a;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    a.setup();
}

void loop()
{
    timer = millis();
    a.run();
    a.pLcd->setCursor(12, 0);
    a.pLcd->print("DEL");
    a.pLcd->print(millis() - timer);
    a.pLcd->print("mc");
}
