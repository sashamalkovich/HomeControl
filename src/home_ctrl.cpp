#include "home_ctrl.h"

HomeCtrl::HomeCtrl()
{
    pinMode(LED_BUILTIN, HIGH);
}

HomeCtrl::~HomeCtrl() = default;

void HomeCtrl::setup()
{
    setupFunc();
}

void HomeCtrl::run()
{
    exec();
}
