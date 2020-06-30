//
// Created by macbook on 2020-03-07.
//

#include "Functions.h"

Functions::Functions() : Menu(), SerRes()
{
    pSerResArr = new int[2];
}

Functions::~Functions()
{
}

void Functions::setupFunc()
{
    setupMenu();
    //eDef();
    //ePut();
    loadParam();
}

void Functions::eGet()
{
    EEPROM.get(0, db);
}

void Functions::ePut()
{
    EEPROM.put(0, db);
}

void Functions::eDef()
{
    db.eBloomTimeMax = 20;
    db.eBloomTimeMin = 8;
    db.eDrenageStop = 24;
    db.eFillStop = 8;
    db.eGrow = false;
    db.eGrowTimeMax = 22;
    db.eGrowTimeMin = 6;
    db.eLight_1 = true;
    db.eLight_2 = true;
    db.eLight_3 = true;
    db.eLights = true;
    db.eSaveMode = false;
    db.eTimer = true;
    db.sHTankMax = 36;
    db.sHTankMin = 4;
    db.sLTankMax = 6;
    db.sLTankMin = 4;
    db.oHourStart = 15;
    db.oMinuteStart = 0;
    db.oMinuteLenght = 10;
    db.oOnOff = false;
}

void Functions::loadParam()
{
    eGet();
    GrowTimeMax = db.eGrowTimeMax;
    GrowTimeMin = db.eGrowTimeMin;
    BloomTimeMax = db.eBloomTimeMax;
    BloomTimeMin = db.eBloomTimeMin;
    DrenageStop = db.eDrenageStop;
    FillStop = db.eFillStop;
    Grow = db.eGrow;
    timerOnOff = db.eTimer;
    light_0 = db.eLight_1;
    light_1 = db.eLight_2;
    light_2 = db.eLight_3;
    timerOnOff ? lights = lights : lights = db.eLights;
    saveMode = db.eSaveMode;
    sHTankMax = db.sHTankMax;
    sHTankMin = db.sHTankMin;
    sLTankMax = db.sLTankMax;
    sLTankMin = db.sLTankMin;
    oHourStart = db.oHourStart;
    oMinuteStart = db.oMinuteStart;
    oMinuteLenght = db.oMinuteLenght;
    oOnOff = db.oOnOff;
}

void Functions::saveParam()
{
    db.eGrowTimeMax = GrowTimeMax;
    db.eGrowTimeMin = GrowTimeMin;
    db.eBloomTimeMax = BloomTimeMax;
    db.eBloomTimeMin = BloomTimeMin;
    db.eDrenageStop = DrenageStop;
    db.eFillStop = FillStop;
    db.eGrow = Grow;
    db.eLight_1 = light_0;
    db.eLight_2 = light_1;
    db.eLight_3 = light_2;
    db.eLights = lights;
    db.eSaveMode = saveMode;
    db.eTimer = timerOnOff;
    db.sHTankMax = sHTankMax;
    db.sHTankMin = sHTankMin;
    db.sLTankMax = sLTankMax;
    db.sLTankMin = sLTankMin;
    db.oHourStart = oHourStart;
    db.oMinuteStart = oMinuteStart;
    db.oMinuteLenght = oMinuteLenght;
    db.oOnOff = oOnOff;
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
    temp = '[' + String(pTime->gettime("H:i:s")) + s + String(pParamArray[1][0]) + s + String(pParamArray[1][1]) + s + String(pParamArray[0][0]) + s + String(pParamArray[0][1]) + s + String(lights) + s + String(light_0) + s + String(light_1) + s + String(light_2) + s + String(drainON) + s + String(drFeedback) + s + String(waterCycleGet()) + ']';
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