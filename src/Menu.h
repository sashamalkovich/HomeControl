//
// Created by macbook on 2020-03-07.
//

#ifndef HOME_CTRL_MENU_H
#define HOME_CTRL_MENU_H

//#include <LiquidCrystal_I2C.h>
#include "home_core.h"

class Menu : public HomeCore
{
public:
    explicit Menu();
    ~Menu();
    void menu();

protected:
    virtual void setupMenu();
    void escape() override;

    int **pParamArray;

    

private:
    int menuState();
    void standbyMenu();
    void mainMenu();
    void page0Menu();
    void lightsMenu();
    void programsMenu();
    void settingsMenu();

    void timeMenu();
    void waterMenu();
    void wateringOut();
    void timeSet();
    void timerSet();
    void saveTime(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

    uint8_t uniParam(uint8_t, uint8_t, uint8_t);

    uint8_t page;
};

#endif //HOME_CTRL_MENU_H
