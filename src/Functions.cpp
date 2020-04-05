//
// Created by macbook on 2020-03-07.
//

#include "Functions.h"

Functions::Functions() : Menu(), SerRes()
{
    pSerResArr = new int[2];
    loadParam();
}

Functions::~Functions()
{
}

void Functions::setupFunc()
{
    setupMenu();
}

void Functions::loadParam()
{
    eGet();
    GrowTimeMax = Pool::eGrowTimeMax;
    GrowTimeMin = Pool::eGrowTimeMin;
    BloomTimeMax = Pool::eBloomTimeMax;
    BloomTimeMin = Pool::eBloomTimeMin;
    DrenageStop = Pool::eDrenageStop;
    FillStop = Pool::eFillStop;
    Grow = Pool::eGrow;
    timerOnOff = Pool::eTimer;
    light_0 = Pool::eLight_1;
    light_1 = Pool::eLight_2;
    light_2 = Pool::eLight_3;
    timerOnOff ? lights = lights : lights = Pool::eLights;
    saveMode = Pool::eSaveMode;
    sHTankMax = Pool::sHTankMax;
    sHTankMin = Pool::sHTankMin;
    sLTankMax = Pool::sLTankMax;
    sLTankMin = Pool::sLTankMin;
}

void Functions::saveParam()
{
    Pool::eGrowTimeMax = GrowTimeMax;
    Pool::eGrowTimeMin = GrowTimeMin;
    Pool::eBloomTimeMax = BloomTimeMax;
    Pool::eBloomTimeMin = BloomTimeMin;
    Pool::eDrenageStop = DrenageStop;
    Pool::eFillStop = FillStop;
    Pool::eGrow = Grow;
    Pool::eLight_1 = light_0;
    Pool::eLight_2 = light_1;
    Pool::eLight_3 = light_2;
    Pool::eLights = lights;
    Pool::eSaveMode = saveMode;
    Pool::eTimer = timerOnOff;
    Pool::sHTankMax = sHTankMax;
    Pool::sHTankMin = sHTankMin;
    Pool::sLTankMax = sLTankMax;
    Pool::sLTankMin = sLTankMin;
    ePut();
    pLcd->setCursor(10, 3);
    pLcd->print("SAVE");
    delay(500);
    pLcd->setCursor(10, 3);
    pLcd->print("    ");
}

void Functions::exec()
{
    pSerResArr = response();

    RunProg::exec(pSerResArr);

    menu();
}

void Functions::sendParam()
{
    String temp;
    const char s = ',';
    temp = '[' + String(pTime->gettime("H:i:s")) + s + String(pParamArray[1][0]) + s + String(pParamArray[1][1]) + s + String(pParamArray[0][0]) + s + String(pParamArray[0][1]) + s + String(lights) + s + String(light_0) + s + String(light_1) + s + String(light_2) + s + String(drainON) + s + String(drFeedback) + s + String(waterCycleGet() + ']');
    SERIAL.println(temp);
    Serial.println(temp);
}

void Functions::exe_0(int in)
{
    if (in == 1)
    {

        lights = true;
        Serial1.println("<ON>");
    }
    else if ((in == 0))
    {

        lights = false;
        Serial1.println("<OFF>");
    }
}

void Functions::exe_1(int in)
{
    if (in == 1)
    {
        light_0 = true;
        Serial1.println("<ON>");
    }
    else if ((in == 0))
    {
        light_0 = false;
        Serial1.println("<OFF>");
    }
}

void Functions::exe_2(int in)
{

    if (in == 1)
    {
        light_1 = true;
        Serial1.println("<ON>");
    }
    else if ((in == 0))
    {
        light_1 = false;
        Serial1.println("<OFF>");
    }
}

void Functions::exe_3(int in)
{
    if (in == 1)
    {
        light_2 = true;
        Serial1.println("<ON>");
    }
    else if ((in == 0))
    {
        light_2 = false;
        Serial1.println("<OFF>");
    }
}

void Functions::exe_6(int in)
{
    drainON = 0;
    if (in == 1)
    {
        drenage = true;
        Serial1.println("<" + String(drainON) + "ON>");
    }
    else if (in == 0)
    {
        drenage = false;
        Serial1.println("<" + String(drainON) + "OFF>");
    }
}

void Functions::exe_7(int in)
{

    drainON = 1;
    if (in == 1)
    {
        drenage = true;
        Serial1.println("<" + String(drainON) + "ON>");
    }
    else if (in == 0)
    {
        drenage = false;
        Serial1.println("<" + String(drainON) + "OFF>");
    }
}

void Functions::exe_8(int in)
{
    drainON = 2;
    if (in == 1)
    {
        drenage = true;
        Serial1.println("<" + String(drainON) + "ON>");
    }
    else if (in == 0)
    {
        drenage = false;
        Serial1.println("<" + String(drainON) + "OFF>");
    }
}
void Functions::exe_9(int in)
{
    drainON = 3;
    if (in == 1)
    {
        drenage = true;
        Serial1.println("<" + String(drainON) + "ON>");
    }
    else if (in == 0)
    {
        drenage = false;
        Serial1.println("<" + String(drainON) + "OFF>");
    }
}

void Functions::exe_10(int in)
{
    loadParam();
    pLcd->setCursor(10, 3);
    pLcd->print("LOAD");
    Serial1.println("<LOAD>");
    delay(500);
    pLcd->setCursor(10, 3);
    pLcd->print("    ");
}

void Functions::exe_11(int in)
{
    saveParam();
    pLcd->setCursor(10, 3);
    pLcd->print("SAVE");
    Serial1.println("<SAVE>");
    delay(500);
    pLcd->setCursor(10, 3);
    pLcd->print("    ");
}

void Functions::exe_12(int in)
{
    sendParam(); 
}

void Functions::exe_13(int in)
{ 
    resetFunc();   
}