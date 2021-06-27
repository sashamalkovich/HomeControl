//
// Created by macbook on 2020-03-07.
//

#include "Menu.h"

Menu::Menu()
{
    pParamArray = new int *[6];
    page = 2;
    for (int i = 0; i < 6; i++)
    {
        for (int y = 0; y < 6; y++)
        {
            pParamArray[i][y] = 0;
        }
    }
}

Menu::~Menu() = default;

void Menu::setupMenu()
{
    setupCore();
}

uint8_t Menu::uniParam(uint8_t encRes, uint8_t posCol, uint8_t posStr)
{
    uint8_t temp, enc;

    while (true)
    {
        sendIter();
        enc = encoder();
        temp = (enc % encRes);
        pLcd->setCursor(posCol, posStr);
        pLcd->print("      ");
        pLcd->setCursor(posCol, posStr);
        pLcd->print(temp);
        if (knob2state(ENCODER_KNOB))
        {
            return temp;
        }
    }
}

uint8_t Menu::uniParam(uint8_t startNum, uint8_t encRes, uint8_t posCol, uint8_t posStr)
{
    uint8_t temp, enc;

    while (true)
    {
        sendIter();
        enc = encoder();
        temp = (enc % encRes) + startNum;
        pLcd->setCursor(posCol, posStr);
        pLcd->print("      ");
        pLcd->setCursor(posCol, posStr);
        pLcd->print(temp);
        if (knob2state(ENCODER_KNOB))
        {
            return temp;
        }
    }
}


void Menu::menu()
{
    static uint32_t timer = millis();

    if(millis() - timer > 300000U){
        pLcd->clear();
        page = 3;
        timer = millis();
    }
    pParamArray = runCore();

    if (pParamArray[3][5] == 1)
    {
        pLcd->clear();
        page = 2;
        timer = millis();
    }
    if (pParamArray[3][6] == 1)
    {
        pLcd->clear();
        page = 1;
        timer = millis();
    }
    if (pParamArray[3][0] == 1)
    {
        int sw = menuState();
        timer = millis();

            if(sw == 0){
                pLcd->clear();
                page = 0;
            }
            else if (sw == 1){
                pLcd->clear();
                page = 3;
            }
            else{
                pLcd->clear();
                page = 2;
            }
    }

    if (lights)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        pLcd->setCursor(4, 3);
        pLcd->print("LI ");
    }
    else
    {
        digitalWrite(LED_BUILTIN, LOW);
        pLcd->setCursor(4, 3);
        pLcd->print("  ");
    }

    if (light_0)
    {
        pLcd->setCursor(19, 0);
        pLcd->print(".");
    }
    else
    {
        pLcd->setCursor(19, 0);
        pLcd->print(" ");
    }

    if (light_1)
    {
        pLcd->setCursor(19, 1);
        pLcd->print(".");
    }
    else
    {
        pLcd->setCursor(19, 1);
        pLcd->print(" ");
    }

    if (light_2)
    {
        pLcd->setCursor(19, 2);
        pLcd->print(".");
    }
    else
    {
        pLcd->setCursor(19, 2);
        pLcd->print(" ");
    }
   
    switch (page)
    {
    case 0:
        
        lcdOnOff(true);
        mainMenu();
        break;
    case 1:
        lcdOnOff(true);
        page0Menu();
        break;
    case 2:
        lcdOnOff(true);
        standbyMenu();
        break;
    case 3:
        lcdOnOff(false);
        break;
    }
}

int Menu::menuState(){

static int count = 0;
    count++;
    return count % 3;
}

void Menu::standbyMenu(){
    pParamArray = runCore();

     pLcd->setCursor(6, 1);
    if (pParamArray[2][0] < 10)
    {
        pLcd->print(0);
        pLcd->print(pParamArray[2][0]);
    }
    else
    {
        pLcd->print(pParamArray[2][0]);
    }
    pLcd->print(":");
    if (pParamArray[2][1] < 10)
    {
        pLcd->print(0);
        pLcd->print(pParamArray[2][1]);
    }
    else
    {
        pLcd->print(pParamArray[2][1]);
    }
    pLcd->print(":");
    if (pParamArray[2][2] < 10)
    {
        pLcd->print(0);
        pLcd->print(pParamArray[2][2]);
    }
    else
    {
        pLcd->print(pParamArray[2][2]);
    }

    pLcd->setCursor(6, 2);
    pLcd->print(pParamArray[2][3]);
    pLcd->setCursor(9, 2);
    pLcd->print(pParamArray[2][4]);
    pLcd->setCursor(12, 2);
    if (pParamArray[2][3] % oDays_Every == 0)
    {
        pLcd->print("!!");
    }else{
        pLcd->print("  ");
    }
    

}

void Menu::mainMenu()
{

    pParamArray = runCore();

    if (saveMode)
    {
        pLcd->setCursor(0, 0);
        pLcd->print("S");
    }
    else
    {
        pLcd->setCursor(0, 0);
        pLcd->print(" ");
    }

    pLcd->setCursor(0, 0);
    pLcd->print("PH ");
    pLcd->print(phTds[0]);
    pLcd->print("   ");
    pLcd->setCursor(10, 0);
    pLcd->print("TD ");
    pLcd->print((int)phTds[1]);
    pLcd->print("   ");
/*
    pLcd->setCursor(6, 0);
    if (pParamArray[2][0] < 10)
    {
        pLcd->print(0);
        pLcd->print(pParamArray[2][0]);
    }
    else
    {
        pLcd->print(pParamArray[2][0]);
    }
    pLcd->print(":");
    if (pParamArray[2][1] < 10)
    {
        pLcd->print(0);
        pLcd->print(pParamArray[2][1]);
    }
    else
    {
        pLcd->print(pParamArray[2][1]);
    }
    pLcd->print(":");
    if (pParamArray[2][2] < 10)
    {
        pLcd->print(0);
        pLcd->print(pParamArray[2][2]);
    }
    else
    {
        pLcd->print(pParamArray[2][2]);
    }
*/
    pLcd->setCursor(0, 1);
    pLcd->print("LT ");
    pLcd->print(pParamArray[1][0]);
    pLcd->print("cm ");
    pLcd->setCursor(10, 1);
    pLcd->print("HT ");
    pLcd->print(pParamArray[1][1]);
    pLcd->print("cm ");
    pLcd->setCursor(0, 2);
    pLcd->print("Ar ");
    pLcd->print(pParamArray[0][0]);
    pLcd->print("C ");
    pLcd->setCursor(10, 2);
    pLcd->print("Wt ");
    pLcd->print(pParamArray[0][1]);
    pLcd->print("C ");
    pLcd->setCursor(14, 3);
    /*
    pLcd->print(phTds[0]);
    pLcd->setCursor(7, 3);
    pLcd->print(phTds[1]);
    */
    
}

void Menu::page0Menu()
{
    bool trg = true;
    uint8_t enc;

    pLcd->clear();
    pLcd->setCursor(5, 0);
    pLcd->print("MENU");
    pLcd->setCursor(5, 1);
    pLcd->print("LIGHTS");
    pLcd->setCursor(5, 2);
    pLcd->print("PROGRAMMS");
    pLcd->setCursor(5, 3);
    pLcd->print("SETTINGS");

    while (trg)
    {
        sendIter();
        enc = encoder() % 4;

        pLcd->setCursor(0, enc);
        pLcd->print("=>");
        pLcd->setCursor(0, (enc - 1) % 4);
        pLcd->print("  ");
        pLcd->setCursor(0, (enc + 1) % 4);
        pLcd->print("  ");
        if (knob2state(ESCAPE_KNOB_PIN))
        {
            page = 0;
            pLcd->clear();
            trg = false;
            mainMenu();
        }
        if (knob2state(ENCODER_KNOB))
        {
            switch (enc)
            {
            case 0:
                page = 0;
                pLcd->clear();
                trg = false;
                mainMenu();
                break;

            case 1:
                pLcd->clear();
                trg = false;
                lightsMenu();
                break;
            case 2:
                pLcd->clear();
                trg = false;
                programsMenu();
                break;
            case 3:
                pLcd->clear();
                trg = false;
                settingsMenu();
                break;
            }
        }
    }
}

void Menu::escape()
{

    pLcd->clear();
    page = 2;
}

void Menu::lightsMenu()
{
    uint8_t enc;
    bool trg = true;
    pLcd->clear();
    pLcd->setCursor(0, 0);
    pLcd->print("       LIGHTS    ");
    pLcd->setCursor(5, 1);
    light_0 ? pLcd->print("1 LIGHT ON ") : pLcd->print("1 LIGHT OFF ");
    pLcd->setCursor(5, 2);
    light_1 ? pLcd->print("2 LIGHT ON ") : pLcd->print("2 LIGHT OFF ");
    pLcd->setCursor(5, 3);
    light_2 ? pLcd->print("3 LIGHT ON ") : pLcd->print("3 LIGHT OFF ");

    while (trg)
    {
        sendIter();
        enc = encoder() % 4;

        pLcd->setCursor(0, enc);
        pLcd->print("=>");
        pLcd->setCursor(0, (enc - 1) % 4);
        pLcd->print("  ");
        pLcd->setCursor(0, (enc + 1) % 4);
        pLcd->print("  ");
        if (knob2state(ESCAPE_KNOB_PIN))
        {
            page = 0;
            pLcd->clear();
            trg = false;
            mainMenu();
        }
        if (knob2state(ENCODER_KNOB))
        {
            switch (enc)
            {
            case 0:
                page = 0;
                trg = false;
                pLcd->clear();
                page0Menu();
                break;

            case 1:

                if (light_0)
                {
                    pLcd->setCursor(5, 1);
                    light_0 = false;
                    pLcd->print("1 LIGHT OFF ");
                }
                else
                {
                    pLcd->setCursor(5, 1);
                    light_0 = true;
                    pLcd->print("1 LIGHT ON ");
                }
                break;
            case 2:

                if (light_1)
                {
                    pLcd->setCursor(5, 2);
                    light_1 = false;
                    pLcd->print("2 LIGHT OFF ");
                }
                else
                {
                    pLcd->setCursor(5, 2);
                    light_1 = true;
                    pLcd->print("2 LIGHT ON ");
                }
                break;
            case 3:

                if (light_2)
                {
                    pLcd->setCursor(5, 3);
                    light_2 = false;
                    pLcd->print("3 LIGHT OFF ");
                }
                else
                {
                    pLcd->setCursor(5, 3);
                    light_2 = true;
                    pLcd->print("3 LIGHT ON ");
                }
                break;
            }
        }
    }
}

void Menu::programsMenu()
{
    uint8_t enc;
    bool trg = true;

    while (trg)
    {
        sendIter();
        enc = encoder() % 5;
        if (enc < 4)
        {
            pLcd->setCursor(0, enc);
            pLcd->print("=>");
            pLcd->setCursor(0, (enc - 1) % 4);
            pLcd->print("  ");
            pLcd->setCursor(0, (enc + 1) % 4);
            pLcd->print("  ");
            pLcd->setCursor(5, 0);
            pLcd->print("PROGRAMMS");
            pLcd->setCursor(5, 1);
            pLcd->print("MODE ");
            pLcd->setCursor(14, 0);
            pLcd->print("     ");
            pLcd->setCursor(14, 1);
            Grow ? pLcd->print("GROW ") : pLcd->print("BLOOM ");
            pLcd->setCursor(14, 2);
            timerOnOff ? pLcd->print("ON   ") : pLcd->print("OFF   ");
            pLcd->setCursor(5, 2);
            pLcd->print("TIMER ");
            pLcd->setCursor(5, 3);
            pLcd->print("WATER ");
            pLcd->setCursor(14, 3);
            if (drainON == 0)
        {
            pLcd->setCursor(14, 3);
            pLcd->print("DRAIN ");
        }
        else if (drainON == 1)
        {
            pLcd->setCursor(14, 3);
            pLcd->print("FILL  ");
        }
        else if (drainON == 2)
        {
            pLcd->setCursor(14, 3);
            pLcd->print("FL HT ");
        }
        else if (drainON == 3)
        {
            pLcd->setCursor(14, 3);
            pLcd->print("DR HT ");
        }
        }
        else
        {
            pLcd->setCursor(0, 3);
            pLcd->print("=>");
            pLcd->setCursor(0, 0);
            pLcd->print("  ");
            pLcd->setCursor(0, 2);
            pLcd->print("  ");
            pLcd->setCursor(5, 0);
            pLcd->print("MODE      ");
            pLcd->setCursor(14, 0);
            Grow ? pLcd->print("GROW ") : pLcd->print("BLOOM ");
            pLcd->setCursor(14, 1);
            timerOnOff ? pLcd->print("ON ") : pLcd->print("OFF ");
            pLcd->setCursor(5, 1);
            pLcd->print("TIMER ");
            pLcd->setCursor(5, 2);
            pLcd->print("WATER ");
            pLcd->setCursor(5, 3);
            pLcd->print("W OUT ");
            pLcd->setCursor(14, 3);
            pLcd->print("     ");

            if (drainON == 0)
            {
                pLcd->setCursor(14, 2);
                pLcd->print("DRAIN ");
            }
            else if (drainON == 1)
            {
                pLcd->setCursor(14, 2);
                pLcd->print("FILL  ");
            }
            else if (drainON == 2)
            {
                pLcd->setCursor(14, 2);
                pLcd->print("FL HT ");
            }
            else if (drainON == 3)
            {
                pLcd->setCursor(14, 2);
                pLcd->print("DR HT ");
            }
        }

        if (knob2state(ESCAPE_KNOB_PIN))
        {
            page = 0;
            pLcd->clear();
            trg = false;
            mainMenu();
        }
        if (knob2state(ENCODER_KNOB))
        {
            switch (enc)
            {
            case 0:
                page = 0;
                trg = false;
                pLcd->clear();
                page0Menu();
                break;

            case 1:

                if (Grow)
                    Grow = false;
                else
                    Grow = true;
                break;
            case 2:

                if (timerOnOff)
                    timerOnOff = false;
                else
                    timerOnOff = true;
                break;
            case 3:
                ++drainON;
                drainON = drainON % 4;
                break;
            case 4:
                wateringOut();
                break;
            }
        }
    }
}

void Menu::wateringOut()
{
    bool trg = true;
    uint8_t enc;
    pLcd->clear();

    while (trg)
    {
        sendIter();

        enc = (encoder() % 6);

        if (enc < 4)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("WATERING ");
            pLcd->setCursor(15, 0);
            pLcd->print("  ");
            pLcd->setCursor(5, 1);
            pLcd->print("HOUR     ");
            pLcd->setCursor(15, 1);
            pLcd->print(oHourStart);
            pLcd->print(" ");
            pLcd->setCursor(5, 2);
            pLcd->print("MIN START");
            pLcd->setCursor(15, 2);
            pLcd->print(oMinuteStart);
            pLcd->print(" ");
            pLcd->setCursor(5, 3);
            pLcd->print("LENGTH   ");
            pLcd->setCursor(15, 3);
            pLcd->print(oMinuteLenght);
            pLcd->print(" ");
        }
        else if (enc == 4)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("HOUR       ");
            pLcd->setCursor(15, 0);
            pLcd->print(oHourStart);
            pLcd->print(" ");
            pLcd->setCursor(5, 1);
            pLcd->print("MIN        ");
            pLcd->setCursor(15, 1);
            pLcd->print(oMinuteStart);
            pLcd->print(" ");
            pLcd->setCursor(5, 2);
            pLcd->print("LENGTH     ");
            pLcd->setCursor(15, 2);
            pLcd->print(oMinuteLenght);
            pLcd->print(" ");
            pLcd->setCursor(5, 3);
            pLcd->print("ON/OFF     ");
            pLcd->setCursor(15, 3);
            oOnOff ? pLcd->print("ON ") : pLcd->print("OFF");
            pLcd->print(" ");
        }
        else if (enc == 5)
        {
            
            pLcd->setCursor(5, 0);
            pLcd->print("MIN     ");
            pLcd->setCursor(15, 0);
            pLcd->print(oMinuteStart);
            pLcd->print(" ");
            pLcd->setCursor(5, 1);
            pLcd->print("LENGTH   ");
            pLcd->setCursor(15, 1);
            pLcd->print(oMinuteLenght);
            pLcd->print(" ");
            pLcd->setCursor(5, 2);
            pLcd->print("ON/OFF    ");
            pLcd->setCursor(15, 2);
            oOnOff ? pLcd->print("ON ") : pLcd->print("OFF");
            pLcd->print(" ");
            pLcd->setCursor(5, 3);
            pLcd->print("EVERY     ");
            pLcd->setCursor(15, 3);
            pLcd->print(oDays_Every);
            pLcd->print(" ");
            
        }

        if (enc < 4)
        {
            pLcd->setCursor(0, enc);
            pLcd->print("=>");
            pLcd->setCursor(0, (enc - 1) % 4);
            pLcd->print("  ");
            pLcd->setCursor(0, (enc + 1) % 4);
            pLcd->print("  ");
            pLcd->setCursor(0, (enc + 2) % 4);
            pLcd->print("  ");
        }
        else
        {
            pLcd->setCursor(0, 3);
            pLcd->print("=>");
            pLcd->setCursor(0, 2);
            pLcd->print("  ");
            pLcd->setCursor(0, 0);
            pLcd->print("  ");
            pLcd->setCursor(0, 1);
            pLcd->print("  ");
        }
        if (knob2state(ESCAPE_KNOB_PIN))
        {
            page = 0;
            trg = false;
            pLcd->clear();
            mainMenu();
        }
        if (knob2state(ENCODER_KNOB))
        {
            switch (enc)
            {
            case 0:
                page = 0;
                trg = false;
                pLcd->clear();
                settingsMenu();
                break;
            case 1:
                oHourStart = uniParam(24, 15, 1);
                break;
            case 2:
                oMinuteStart = uniParam(60, 15, 2);
                break;
            case 3:
                oMinuteLenght = uniParam(60, 15, 3);
                break;
            case 4:
                oOnOff ? oOnOff = false : oOnOff = true;
                break;
            case 5:
                oDays_Every= uniParam(1, 5, 15, 3);
                break;
            }
        }
    }
}

void Menu::settingsMenu()
{

    uint8_t enc;
    bool trg = true;
    pLcd->setCursor(5, 0);
    pLcd->print("SETTINGS");
    pLcd->setCursor(5, 1);
    pLcd->print("TIME    ");
    pLcd->setCursor(5, 2);
    pLcd->print("WATER   ");
    pLcd->setCursor(5, 3);
    pLcd->print("S. MODE ");

    while (trg)
    {

        pLcd->setCursor(14, 3);
        saveMode ? pLcd->print("ON ") : pLcd->print("OFF");

        sendIter();
        enc = encoder() % 4;

        pLcd->setCursor(0, enc);
        pLcd->print("=>");
        pLcd->setCursor(0, (enc - 1) % 4);
        pLcd->print("  ");
        pLcd->setCursor(0, (enc + 1) % 4);
        pLcd->print("  ");
        pLcd->setCursor(0, (enc + 2) % 4);
        pLcd->print("  ");

        if (knob2state(ESCAPE_KNOB_PIN))
        {
            page = 0;
            pLcd->clear();
            trg = false;
            mainMenu();
        }
        if (knob2state(ENCODER_KNOB))
        {
            switch (enc)
            {
            case 0:
                page = 0;
                trg = false;
                pLcd->clear();
                page0Menu();
                break;

            case 1:
                pLcd->clear();
                trg = false;
                timeMenu();
                break;
            case 2:
                pLcd->clear();
                trg = false;
                waterMenu();
                break;
            case 3:
                saveMode ? saveMode = false : saveMode = true;
                break;
            }
        }
    }
}

void Menu::timeMenu()
{
    uint8_t enc;
    bool trg = true;
    pLcd->setCursor(5, 0);
    pLcd->print("TIME");

    while (trg)
    {
        pLcd->setCursor(5, 1);
        pLcd->print("TIME SET ");
        pLcd->setCursor(5, 2);
        pLcd->print("TIMER SET");
        pLcd->setCursor(5, 3);

        sendIter();
        enc = encoder() % 3;

        pLcd->setCursor(0, enc);
        pLcd->print("=>");
        pLcd->setCursor(0, (enc - 1) % 3);
        pLcd->print("  ");
        pLcd->setCursor(0, (enc + 1) % 3);
        pLcd->print("  ");
        pLcd->setCursor(0, (enc + 2) % 3);
        pLcd->print("  ");
        if (knob2state(ESCAPE_KNOB_PIN))
        {
            page = 0;
            pLcd->clear();
            trg = false;
            mainMenu();
        }
        if (knob2state(ENCODER_KNOB))
        {
            switch (enc)
            {
            case 0:
                page = 0;
                trg = false;
                pLcd->clear();
                page0Menu();
                break;

            case 1:
                trg = false;
                pLcd->clear();
                timeSet();
                break;
            case 2:
                trg = false;
                pLcd->clear();
                timerSet();
                break;
            }
        }
    }
}

void Menu::timeSet()
{
    bool trg = true;
    uint8_t enc;
    pLcd->clear();
    uint8_t sHour, sMinutes, sDate, sMonth, sYear;

    sHour = pTime->Hours;
    sMinutes = pTime->minutes;
    sDate = pTime->day;
    sMonth = pTime->month;
    sYear = pTime->year;

    while (trg)
    {
        sendIter();

        enc = (encoder() % 7);

        if (enc < 4)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("TIME SET ");
            pLcd->setCursor(5, 1);
            pLcd->print("HOUR     ");
            pLcd->setCursor(12, 1);
            pLcd->print(sHour);
            pLcd->setCursor(5, 2);
            pLcd->print("MIN      ");
            pLcd->setCursor(12, 2);
            pLcd->print(sMinutes);
            pLcd->setCursor(5, 3);
            pLcd->print("DATE     ");
            pLcd->setCursor(12, 3);
            pLcd->print(sDate);
        }
        else if (enc == 4)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("HOUR     ");
            pLcd->setCursor(12, 0);
            pLcd->print(sHour);
            pLcd->setCursor(5, 1);
            pLcd->print("MIN      ");
            pLcd->setCursor(12, 1);
            pLcd->print(sMinutes);
            pLcd->setCursor(5, 2);
            pLcd->print("DATE     ");
            pLcd->setCursor(12, 2);
            pLcd->print(sDate);
            pLcd->setCursor(5, 3);
            pLcd->print("MONTH   ");
            pLcd->setCursor(12, 3);
            pLcd->print(sMonth);
        }
        else if (enc == 5)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("MIN      ");
            pLcd->setCursor(12, 0);
            pLcd->print(sMinutes);
            pLcd->setCursor(5, 1);
            pLcd->print("DATE     ");
            pLcd->setCursor(12, 1);
            pLcd->print(sDate);
            pLcd->setCursor(5, 2);
            pLcd->print("MONTH   ");
            pLcd->setCursor(12, 2);
            pLcd->print(sMonth);
            pLcd->setCursor(5, 3);
            pLcd->print("YEAR   ");
            pLcd->setCursor(12, 3);
            pLcd->print(sYear);
        }

        else if (enc == 6)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("DATE     ");
            pLcd->setCursor(12, 0);
            pLcd->print(sDate);
            pLcd->setCursor(5, 1);
            pLcd->print("MONTH    ");
            pLcd->setCursor(12, 1);
            pLcd->print(sMonth);
            pLcd->setCursor(5, 2);
            pLcd->print("YEAR     ");
            pLcd->setCursor(12, 2);
            pLcd->print(sYear);
            pLcd->setCursor(5, 3);
            pLcd->print("SAVE     ");
        }
        if (enc < 4)
        {
            pLcd->setCursor(0, enc);
            pLcd->print("=>");
            pLcd->setCursor(0, (enc - 1) % 4);
            pLcd->print("  ");
            pLcd->setCursor(0, (enc + 1) % 4);
            pLcd->print("  ");
        }
        else
        {
            pLcd->setCursor(0, 3);
            pLcd->print("=>");
            pLcd->setCursor(0, 2);
            pLcd->print("  ");
            pLcd->setCursor(0, 0);
            pLcd->print("  ");
        }
        if (knob2state(ESCAPE_KNOB_PIN))
        {
            page = 0;
            trg = false;
            pLcd->clear();
            mainMenu();
        }
        if (knob2state(ENCODER_KNOB))
        {
            switch (enc)
            {
            case 0:
                page = 0;
                trg = false;
                pLcd->clear();
                settingsMenu();
                break;

            case 1:
                sHour = uniParam(24, 12, 1);
                break;
            case 2:
                sMinutes = uniParam(60, 12, 2);
                break;
            case 3:
                sDate = uniParam(31, 12, 3);
                break;
            case 4:
                sMonth = uniParam(12, 12, 3);
                break;
            case 5:
                sMonth = uniParam(30, 12, 3);
                break;
            case 6:
                trg = false;
                saveTime(sMinutes, sHour, sDate, sMonth, sYear);
                pLcd->clear();
                settingsMenu();
                break;
            }
        }
    }
}

void Menu::saveTime(uint8_t sMinutes, uint8_t sHour, uint8_t sDate, uint8_t sMonth, uint8_t sYear)
{
    pTime->settime(0, sMinutes, sHour, sDate, sMonth, sYear, 2);
}

void Menu::timerSet()
{
    bool trg = true;
    uint8_t enc;
    pLcd->clear();

    while (trg)
    {
        sendIter();

        enc = (encoder() % 5);

        if (enc < 4)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("TIMER SET");
            pLcd->setCursor(15, 0);
            pLcd->print("  ");
            pLcd->setCursor(5, 1);
            pLcd->print("GROW MIN ");
            pLcd->setCursor(15, 1);
            pLcd->print(GrowTimeMin);
            pLcd->print(" ");
            pLcd->setCursor(5, 2);
            pLcd->print("GROW MAX ");
            pLcd->setCursor(15, 2);
            pLcd->print(GrowTimeMax);
            pLcd->print(" ");
            pLcd->setCursor(5, 3);
            pLcd->print("BLOOM MIN");
            pLcd->setCursor(15, 3);
            pLcd->print(BloomTimeMin);
            pLcd->print(" ");
        }
        else if (enc == 4)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("GROW MIN ");
            pLcd->setCursor(15, 0);
            pLcd->print(GrowTimeMin);
            pLcd->print(" ");
            pLcd->setCursor(5, 1);
            pLcd->print("GROW MAX ");
            pLcd->setCursor(15, 1);
            pLcd->print(GrowTimeMax);
            pLcd->print(" ");
            pLcd->setCursor(5, 2);
            pLcd->print("BLOOM MIM");
            pLcd->setCursor(15, 2);
            pLcd->print(BloomTimeMin);
            pLcd->print(" ");
            pLcd->setCursor(5, 3);
            pLcd->print("BLOOM MAX");
            pLcd->setCursor(15, 3);
            pLcd->print(BloomTimeMax);
            pLcd->print(" ");
        }

        if (enc < 4)
        {
            pLcd->setCursor(0, enc);
            pLcd->print("=>");
            pLcd->setCursor(0, (enc - 1) % 4);
            pLcd->print("  ");
            pLcd->setCursor(0, (enc + 1) % 4);
            pLcd->print("  ");
        }
        else
        {
            pLcd->setCursor(0, 3);
            pLcd->print("=>");
            pLcd->setCursor(0, 2);
            pLcd->print("  ");
            pLcd->setCursor(0, 0);
            pLcd->print("  ");
        }
        if (knob2state(ESCAPE_KNOB_PIN))
        {
            page = 0;
            trg = false;
            pLcd->clear();
            mainMenu();
        }
        if (knob2state(ENCODER_KNOB))
        {
            switch (enc)
            {
            case 0:
                page = 0;
                trg = false;
                pLcd->clear();
                settingsMenu();
                break;
            case 1:
                GrowTimeMin = uniParam(24, 15, 1);
                break;
            case 2:
                GrowTimeMax = uniParam(24, 15, 2);
                break;
            case 3:
                BloomTimeMin = uniParam(24, 15, 3);
                break;
            case 4:
                BloomTimeMax = uniParam(24, 15, 3);
                break;
            }
        }
    }
}

void Menu::waterMenu()
{
    bool trg = true;
    uint8_t enc;
    pLcd->clear();

    while (trg)
    {
        sendIter();

        enc = (encoder() % 7);

        if (enc < 4)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("WATER SET");
            pLcd->setCursor(15, 0);
            pLcd->print("  ");
            pLcd->setCursor(5, 1);
            pLcd->print("LT MIN ");
            pLcd->setCursor(15, 1);
            pLcd->print(sLTankMin);
            pLcd->print(" ");
            pLcd->setCursor(5, 2);
            pLcd->print("LT MAX ");
            pLcd->setCursor(15, 2);
            pLcd->print(sLTankMax);
            pLcd->print(" ");
            pLcd->setCursor(5, 3);
            pLcd->print("HT MIN");
            pLcd->setCursor(15, 3);
            pLcd->print(sHTankMin);
            pLcd->print(" ");
        }
        else if (enc == 4)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("LT MIN ");
            pLcd->setCursor(15, 0);
            pLcd->print(sLTankMin);
            pLcd->print(" ");
            pLcd->setCursor(12, 0);
            pLcd->print("  ");
            pLcd->setCursor(5, 1);
            pLcd->print("LT MAX ");
            pLcd->setCursor(15, 1);
            pLcd->print(sLTankMax);
            pLcd->print(" ");
            pLcd->setCursor(5, 2);
            pLcd->print("HT MIM");
            pLcd->setCursor(15, 2);
            pLcd->print(sHTankMin);
            pLcd->print(" ");
            pLcd->setCursor(5, 3);
            pLcd->print("HT MAX");
            pLcd->setCursor(15, 3);
            pLcd->print(sHTankMax);
            pLcd->print(" ");
        }
        else if (enc == 5)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("LT MAX ");
            pLcd->setCursor(12, 0);
            pLcd->print("  ");
            pLcd->setCursor(15, 0);
            pLcd->print(sLTankMin);
            pLcd->print(" ");
            pLcd->setCursor(5, 1);
            pLcd->print("HT MIN ");
            pLcd->setCursor(15, 1);
            pLcd->print(sLTankMax);
            pLcd->print(" ");
            pLcd->setCursor(5, 2);
            pLcd->print("HT MAX");
            pLcd->setCursor(15, 2);
            pLcd->print(sHTankMin);
            pLcd->print(" ");
            pLcd->setCursor(5, 3);
            pLcd->print("DR STP");
            pLcd->setCursor(15, 3);
            pLcd->print(drenageStop);
            pLcd->print(" ");
        }
        else if (enc == 6)
        {
            pLcd->setCursor(5, 0);
            pLcd->print("HT MIN ");
            pLcd->setCursor(12, 0);
            pLcd->print("  ");
            pLcd->setCursor(15, 0);
            pLcd->print(sHTankMin);
            pLcd->print(" ");
            pLcd->setCursor(5, 1);
            pLcd->print("HT MAX ");
            pLcd->setCursor(15, 1);
            pLcd->print(sHTankMax);
            pLcd->print(" ");
            pLcd->setCursor(5, 2);
            pLcd->print("DR STP");
            pLcd->setCursor(15, 2);
            pLcd->print(drenageStop);
            pLcd->print(" ");
            pLcd->setCursor(5, 3);
            pLcd->print("FL STP");
            pLcd->setCursor(15, 3);
            pLcd->print(fillStop);
            pLcd->print(" ");
        }

        if (enc < 4)
        {
            pLcd->setCursor(0, enc);
            pLcd->print("=>");
            pLcd->setCursor(0, (enc - 1) % 4);
            pLcd->print("  ");
            pLcd->setCursor(0, (enc + 1) % 4);
            pLcd->print("  ");
        }
        else
        {
            pLcd->setCursor(0, 3);
            pLcd->print("=>");
            pLcd->setCursor(0, 2);
            pLcd->print("  ");
            pLcd->setCursor(0, 0);
            pLcd->print("  ");
        }
        if (knob2state(ESCAPE_KNOB_PIN))
        {
            page = 0;
            trg = false;
            pLcd->clear();
            mainMenu();
        }
        if (knob2state(ENCODER_KNOB))
        {
            switch (enc)
            {
            case 0:
                page = 0;
                trg = false;
                pLcd->clear();
                settingsMenu();
                break;
            case 1:
                sLTankMin = uniParam(42, 15, 1);
                break;
            case 2:
                sLTankMax = uniParam(42, 15, 2);
                break;
            case 3:
                sHTankMin = uniParam(42, 15, 3);
                break;
            case 4:
                sHTankMax = uniParam(42, 15, 3);
                break;
            case 5:
                drenageStop = uniParam(42, 15, 3);
                break;
            case 6:
                fillStop = uniParam(42, 15, 3);
                break;
            }
        }
    }
}