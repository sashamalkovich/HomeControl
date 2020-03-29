#include "home_core.h"

HomeCore::HomeCore()
{
    pLcd = new LiquidCrystal_I2C(0x27, 20, 4);
    pOneWire = new OneWire(ONE_WIRE_BUS);
    pSensor = new DallasTemperature(pOneWire);
    pTemp = new int[2];
    pSS = new int[2];
    pTime = new iarduino_RTC(RTC_DS3231);
    timeArray = new int[4];
    knobON = new bool[6];
    paramArray = new int *[7];
    count = 0;
    actualcount = 0;
    state = 0;
    pinAValue = 0;
    pinBValue = 0;
    fillStop = 7;
    drenageStop = 24;
    sHTankMin = 4;

    lights = false;
    light_0 = false;
    light_1 = false;
    light_2 = false;
    drFeedback = false;

    for (int i = 0; i < 7; i++)
    {
        knobON[i] = false;
    }
    for (int i = 0; i < 7; i++)
    {
        for (int y = 0; y < 7; y++)
        {
            paramArray[i][y] = 0;
        }
    }
}

HomeCore::~HomeCore() = default;

void HomeCore::setupCore()
{
    pLcd->init();
    pLcd->backlight();
    pSensor->begin();
    //pTime->begin();
    _setup();
}

int *HomeCore::getTemp()
{
    static long timer = millis() + 59000;
    if (millis() - timer > 60000)
    {
        pSensor->requestTemperatures();
        pTemp[0] = (int)((pSensor->getTempC(sensor1)) + 0.51);
        pTemp[1] = (int)((pSensor->getTempC(sensor2)) + 0.51);
        timer = millis();
    }
    return pTemp;
}

int HomeCore::superSonic(uint8_t PIN_IN, uint8_t PIN_OUT)
{
    long dur;
    int cm;
    digitalWrite(PIN_OUT, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_OUT, HIGH);
    delayMicroseconds(20);
    digitalWrite(PIN_OUT, LOW);
    dur = pulseIn(PIN_IN, HIGH, 14000);
    cm = dur / 29 / 2;
    return cm;
}

int *HomeCore::getSS()
{
    static int ssTemp1 = 0;
    static int ssTemp2 = 0;
    static uint32_t timer = 998;
    if (millis() - timer > 1000)
    {
        ssTemp1 = superSonic(SS_PIN_IN_0, SS_PIN_OUT_0);
        ssTemp2 = superSonic(SS_PIN_IN_1, SS_PIN_OUT_1);
        timer = millis();
    }
    pSS[0] = ssTemp1;
    pSS[1] = ssTemp2;
    return pSS;
}

int *HomeCore::getTime()
{
    pTime->gettime();
    timeArray[0] = pTime->Hours;
    timeArray[1] = pTime->minutes;
    timeArray[2] = pTime->seconds;
    timeArray[3] = pTime->day;
    return timeArray;
}

uint8_t HomeCore::encoder()
{
    pinAValue = digitalRead(ENCODER_PIN_0); // Получаем состояние пинов A и B
    pinBValue = digitalRead(ENCODER_PIN_1);
    cli(); // Запрещаем обработку прерываний, чтобы не отвлекаться
    if (!pinAValue && pinBValue)
        state = 1; // Если при спаде линии А на линии B лог. единица, то вращение в одну сторону
    if (!pinAValue && !pinBValue)
        state = -1; // Если при спаде линии А на линии B лог. ноль, то вращение в другую сторону
    if (pinAValue && state != 0)
    {
        if (state == 1 && !pinBValue || state == -1 && pinBValue)
        { // Если на линии А снова единица, фиксируем шаг
            count += state;
            state = 0;
        }
    }
    sei(); // Разрешаем обработку прерываний

    return count;
}
void (*HomeCore::resetFunc)(void) = 0;

bool HomeCore::saveMode = false;

bool HomeCore::knob2state(uint8_t knob)
{
    static bool switch_enc = false;
    bool state;
    state = digitalRead(knob);
    while (!state)
    {
        if (!digitalRead(KNOB_0) && (!digitalRead(ESCAPE_KNOB_PIN) && !digitalRead(ENCODER_KNOB)))
        {
            resetFunc();
        }
        if (!digitalRead(KNOB_0) && !digitalRead(ESCAPE_KNOB_PIN))
        {
            saveMode = true;
        }
        state = digitalRead(knob);

        switch_enc = true;
    }
    if (state && switch_enc)
    {
        switch_enc = false;
        state = true;
    }
    else if (state && !switch_enc)
    {
        state = false;
    }

    return state;
}

void HomeCore::lcdOnOff()
{
    static bool onOff = false;
    if (!onOff)
    {
        pLcd->display();
        pLcd->setBacklight(true);
        onOff = true;
    }
    else
    {
        pLcd->noDisplay();
        pLcd->setBacklight(false);
        onOff = false;
    }
}

int **HomeCore::runCore()
{
    static int lastData = 0;
    static bool on = false, off = false;
    static bool trig = false, trig1 = false;
    sendIter();

    paramArray[0] = getTemp();
    paramArray[1] = getSS();
    paramArray[2] = getTime();
    paramArray[3] = knobArray();

    paramArray[4][0] = encoder();

    if (paramArray[3][2] == 1)
    {

        lights ? lights = false : lights = true;
    }

    if (lights)
    {
        if (saveMode)
        {
            if (!trig)
            {
                on = true;
                trig = true;
                trig1 = false;
            }
            else
            {
                on = false;
            }
            pLcd->setCursor(0, 0);
            pLcd->print("S");
        }
        else
        {
            if (!trig1)
            {
                off = true;
                trig1 = true;
                trig = false;
            }
            else
            {
                off = false;
            }

            pLcd->setCursor(0, 0);
            pLcd->print(" ");
        }

        if (on)
        {
            light_0 = false;
            light_2 = false;
        }
        if (off)
        {
            light_0 = Pool::eLight_1;
            light_2 = Pool::eLight_3;
        }

        light_0 ? digitalWrite(RELAY_LIGHT_0, ON) : digitalWrite(RELAY_LIGHT_0, OFF);
        light_1 ? digitalWrite(RELAY_LIGHT_1, ON) : digitalWrite(RELAY_LIGHT_1, OFF);
        light_2 ? digitalWrite(RELAY_LIGHT_2, ON) : digitalWrite(RELAY_LIGHT_2, OFF);
    }
    else
    {
        digitalWrite(RELAY_LIGHT_0, OFF);
        digitalWrite(RELAY_LIGHT_1, OFF);
        digitalWrite(RELAY_LIGHT_1, OFF);
    }

    if (paramArray[3][4] == 1)
    {
        saveParam();
    }

    if (paramArray[3][5] == 1)
    {
        escape();
    }

    if (paramArray[3][0] == 1)
    {
        lcdOnOff();
    }

    if (paramArray[3][3] == 1)
    {
        drenageOnOff();
    }

    drenageFUNC();

    waterLevel(paramArray[1][0]);

    waterLevelHT(paramArray[1][1]);

    lightsTimer();

    tempLighsOff();
    //  */
    return paramArray;
}
void HomeCore::saveParam()
{
}

void HomeCore::drenageOnOff()
{
    drenage ? drenage = false : drenage = true;
}

int HomeCore::bool2int(bool in)
{
    if (in)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int *HomeCore::knobArray()
{
    static int _paramArray[7];
    _paramArray[0] = bool2int(knob2state(KNOB_0));
    _paramArray[1] = bool2int(knob2state(KNOB_0));
    _paramArray[2] = bool2int(knob2state(KNOB_1));
    _paramArray[3] = bool2int(knob2state(KNOB_2));
    _paramArray[4] = bool2int(knob2state(SAVE_KNOB_PIN));
    _paramArray[5] = bool2int(knob2state(ESCAPE_KNOB_PIN));
    _paramArray[6] = bool2int(knob2state(ENCODER_KNOB));
    return _paramArray;
}

void HomeCore::escape()
{
}

void HomeCore::sendIter()
{
    static long timer;
    static uint8_t iter;
    if ((millis() - timer) > 1000)
    {
        Serial2.print("~I" + String(iter++) + "i\n");
        timer = millis();
    }
}

void HomeCore::lightsTimer()
{
    int hourLightsMin;
    int hourLightsMax;
    static bool on = false;
    static bool off = false;
    static bool trig = false, trig1 = false;
    if (Grow)
    {
        hourLightsMin = GrowTimeMin;
        hourLightsMax = GrowTimeMax;
    }
    else
    {
        hourLightsMin = BloomTimeMin;
        hourLightsMax = BloomTimeMax;
    }
    if (timerOnOff)
    {
        if ((paramArray[2][0] >= hourLightsMin) && (paramArray[2][0] < hourLightsMax))
        {
            if (!trig)
            {
                on = true;
                trig = true;
                trig1 = false;
            }
            else
            {
                on = false;
            }
        }
        else
        {
            if (!trig1)
            {
                off = true;
                trig1 = true;
                trig = false;
            }
            else
            {
                off = false;
            }
        }
        if (on)
            lights = true;
        if (off)
            lights = false;
    }
}

void HomeCore::tempLighsOff()
{
    static long timer = millis();
    static bool sw = false;

    if (millis() - timer > 900000)
    {
        if (paramArray[0][0] <= 28 && paramArray[0][1] <= 26)
        {
            light_0 = Pool::eLight_1;
            light_1 = Pool::eLight_2;
            light_2 = Pool::eLight_3;
        }
        else if (paramArray[0][0] == 29 || paramArray[0][1] == 27)
        {
            light_0 = Pool::eLight_1;
            light_1 = false;
            light_2 = Pool::eLight_3;
        }
        else
        {
            light_0 = false;
            light_1 = true;
            light_2 = false;
        }
        timer = millis();
    }
}

void HomeCore::drenageFUNC()
{
    uint8_t SS_1 = paramArray[1][0];
    uint8_t SS_2 = paramArray[1][1];

    static bool trg = false;

    if (paramArray[3][5])
    {
        knobON[0] = false;
        digitalWrite(RELAY_VALVE_1, LOW);
        digitalWrite(RELAY_VALVE_2, LOW);
        digitalWrite(RELAY_VALVE_3, LOW);
        digitalWrite(RELAY_VALVE_4, OFF);
        digitalWrite(RELAY_VALVE_5, OFF);
        digitalWrite(RELAY_PUMP, OFF);
        drenage = false;
        pLcd->setCursor(10, 3);
        pLcd->print("   ");
        drainON = 0;
        pLcd->clear();
        escape();
    }

    if (drainON == 0)
    {
        if (drenage && SS_1 < drenageStop && SS_2 > sLTankMin && !trg)
        {
            digitalWrite(RELAY_VALVE_1, HIGH); // Выход на слив
            //digitalWrite(RELAY_VALVE_2, HIGH); // Выход в бак
            //digitalWrite(RELAY_VALVE_3, HIGH); // Вход чистой воды
            //digitalWrite(RELAY_VALVE_4, ON);   // Вход водопровод
            digitalWrite(RELAY_VALVE_5, ON); // Вход с нижнего бака
            digitalWrite(RELAY_PUMP, ON);
            pLcd->setCursor(10, 3);
            pLcd->print("DR ");
            trg = true;
            drFeedback = true;
        }
        else if (!drenage && SS_1 < drenageStop && SS_2 > sLTankMin && trg)
        {
            digitalWrite(RELAY_VALVE_1, LOW);
            // digitalWrite(RELAY_VALVE_2, LOW);
            //digitalWrite(RELAY_VALVE_3, LOW);
            //digitalWrite(RELAY_VALVE_4, OFF);
            digitalWrite(RELAY_VALVE_5, OFF);
            digitalWrite(RELAY_PUMP, OFF);
            drenage = false;
            trg = false;
            drFeedback = false;
            pLcd->setCursor(10, 3);
            pLcd->print("   ");
        }
    }
    else if (drainON == 1)
    {
        if (drenage && SS_1 > fillStop && !trg)
        {
            //digitalWrite(RELAY_VALVE_1, HIGH);
            digitalWrite(RELAY_VALVE_2, HIGH);
            //digitalWrite(RELAY_VALVE_3, HIGH);
            digitalWrite(RELAY_VALVE_4, ON);
            //digitalWrite(RELAY_VALVE_5, ON);
            digitalWrite(RELAY_PUMP, ON);
            pLcd->setCursor(10, 3);
            pLcd->print("FL ");
            trg = true;
            drFeedback = true;
        }
        else if (!drenage && SS_1 > fillStop && trg)
        {
            //digitalWrite(RELAY_VALVE_1, LOW);
            digitalWrite(RELAY_VALVE_2, LOW);
            //digitalWrite(RELAY_VALVE_3, LOW);
            digitalWrite(RELAY_VALVE_4, OFF);
            digitalWrite(RELAY_PUMP, OFF);
            pLcd->setCursor(10, 3);
            drenage = false;
            trg = false;
            drFeedback = false;
            pLcd->print("   ");
        }
    }
    else if (drainON == 2)
    {
        if (drenage && SS_1 > fillStop && SS_2 < 42 && !trg)
        {
            //digitalWrite(RELAY_VALVE_1, HIGH);
            digitalWrite(RELAY_VALVE_2, HIGH);
            digitalWrite(RELAY_VALVE_3, HIGH);
            //digitalWrite(RELAY_VALVE_4, ON);
            //digitalWrite(RELAY_VALVE_5, ON);
            digitalWrite(RELAY_PUMP, ON);
            pLcd->setCursor(10, 3);
            pLcd->print("FT ");
            trg = true;
            drFeedback = true;
        }
        else if (!drenage && SS_1 > fillStop && SS_2 < 42 && trg)
        {
            //digitalWrite(RELAY_VALVE_1, LOW);
            digitalWrite(RELAY_VALVE_2, LOW);
            digitalWrite(RELAY_VALVE_3, LOW);
            //digitalWrite(RELAY_VALVE_4, OFF);
            //digitalWrite(RELAY_VALVE_5, ON);
            digitalWrite(RELAY_PUMP, OFF);
            pLcd->setCursor(10, 3);
            drenage = false;
            trg = false;
            drFeedback = false;
            pLcd->print("   ");
        }
    }
    else if (drainON == 3)
    {
        if (drenage && SS_2 < 42 && !trg)
        {
            digitalWrite(RELAY_VALVE_1, HIGH);
            //digitalWrite(RELAY_VALVE_2, HIGH);
            digitalWrite(RELAY_VALVE_3, HIGH);
            //digitalWrite(RELAY_VALVE_4, ON);
            //digitalWrite(RELAY_VALVE_5, ON);
            digitalWrite(RELAY_PUMP, ON);
            pLcd->setCursor(10, 3);
            pLcd->print("DT");
            pLcd->setCursor(3, 1);
            trg = true;
            drFeedback = true;
        }
        else if (!drenage && SS_2 < 42 && trg)
        {
            digitalWrite(RELAY_VALVE_1, LOW);
            //digitalWrite(RELAY_VALVE_2, LOW);
            digitalWrite(RELAY_VALVE_3, LOW);
            //digitalWrite(RELAY_VALVE_4, OFF);
            //digitalWrite(RELAY_VALVE_5, ON);
            digitalWrite(RELAY_PUMP, OFF);
            pLcd->setCursor(10, 3);
            drenage = false;
            trg = false;
            drFeedback = false;
            pLcd->print("   ");
        }
    }
}

void HomeCore::waterLevel(uint8_t cm)
{
    if (!drenage)
    {
        if ((cm > sLTankMax + 2) || (cm < sLTankMin - 1))
        {
            digitalWrite(RELAY_VALVE_2, LOW);
            digitalWrite(RELAY_VALVE_3, LOW);
            digitalWrite(RELAY_PUMP, OFF);
            pLcd->setCursor(0, 3);
            pLcd->print("ERR");
        }
        else
        {

            if (cm > sLTankMax)
            {
                digitalWrite(RELAY_VALVE_2, HIGH);
                digitalWrite(RELAY_VALVE_3, HIGH);
                digitalWrite(RELAY_PUMP, ON);
                pLcd->setCursor(0, 3);
                pLcd->print("W  ");
                delay(100);
            }

            else if (cm < sLTankMax)
            {
                digitalWrite(RELAY_VALVE_2, LOW);
                digitalWrite(RELAY_VALVE_3, LOW);
                digitalWrite(RELAY_PUMP, OFF);
                pLcd->setCursor(0, 3);
                pLcd->print("   ");
            }
        }
    }
}

void HomeCore::waterLevelHT(uint8_t cm)
{
    static bool trig = false;

    if ((cm > sHTankMax + 2) || (cm < sHTankMin - 1))
    {
        digitalWrite(RELAY_VALVE_6, OFF);
        pLcd->setCursor(3, 3);
        pLcd->print("E1");
    }
    else
    {

        if (cm > sHTankMin) //36
        {
            if (!trig)
            {
                digitalWrite(RELAY_VALVE_6, ON);
                pLcd->setCursor(0, 3);
                pLcd->print("W ");
                trig = true;
            }
        }

        else if (cm < sHTankMax)
        {
            if (trig)
            {
                digitalWrite(RELAY_VALVE_6, OFF);
                pLcd->setCursor(3, 3);
                pLcd->print("  ");
                trig = false;
            }
        }
    }
}