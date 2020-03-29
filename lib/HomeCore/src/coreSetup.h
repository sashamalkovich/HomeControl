//
// Created by macbook on 08/03/2020.
//

#ifndef HOMECORE_CORESETUP_H
#define HOMECORE_CORESETUP_H

#include "coreDef.h"

inline void  _setup() {

    pinMode(SS_PIN_OUT_0, OUTPUT);
    pinMode(SS_PIN_IN_0, INPUT);
    pinMode(SS_PIN_OUT_1, OUTPUT);
    pinMode(SS_PIN_IN_1, INPUT);

    pinMode(RELAY_VALVE_0, OUTPUT);
    pinMode(RELAY_VALVE_1, OUTPUT);
    pinMode(RELAY_VALVE_2, OUTPUT);
    pinMode(RELAY_VALVE_3, OUTPUT);
    pinMode(RELAY_VALVE_4, OUTPUT);
    pinMode(RELAY_VALVE_5, OUTPUT);
    pinMode(RELAY_VALVE_6, OUTPUT);
    pinMode(RELAY_LIGHT_0, OUTPUT);
    pinMode(RELAY_LIGHT_1, OUTPUT);
    pinMode(RELAY_LIGHT_2, OUTPUT);
    pinMode(RELAY_PUMP,    OUTPUT);

    pinMode(ENCODER_PIN_0,   INPUT_PULLUP);
    pinMode(ENCODER_PIN_1,   INPUT_PULLUP);
    pinMode(ENCODER_KNOB,    INPUT_PULLUP);
    pinMode(KNOB_0,          INPUT_PULLUP);
    pinMode(KNOB_1,          INPUT_PULLUP);
    pinMode(KNOB_2,          INPUT_PULLUP);
    pinMode(SAVE_KNOB_PIN,   INPUT_PULLUP);
    pinMode(ESCAPE_KNOB_PIN, INPUT_PULLUP);

    pinMode(_12_V_OUT_0, OUTPUT);
    pinMode(_12_V_OUT_1, OUTPUT);
    pinMode(_12_V_OUT_2, OUTPUT);
    pinMode(_12_V_OUT_3, OUTPUT);


    pinMode(SS_PIN_IN_1, INPUT);
    pinMode(SS_PIN_OUT_1, OUTPUT);

    digitalWrite(RELAY_VALVE_0, LOW);
    digitalWrite(RELAY_VALVE_1, LOW);
    digitalWrite(RELAY_VALVE_2, LOW);
    digitalWrite(RELAY_VALVE_3, LOW);
    digitalWrite(RELAY_VALVE_4, OFF);
    digitalWrite(RELAY_VALVE_5, OFF);
    digitalWrite(RELAY_VALVE_6, OFF);
    digitalWrite(RELAY_LIGHT_0, OFF);
    digitalWrite(RELAY_LIGHT_1, OFF);
    digitalWrite(RELAY_LIGHT_2, OFF);
    digitalWrite(RELAY_PUMP, OFF);
}

#endif //HOMECORE_CORESETUP_H
