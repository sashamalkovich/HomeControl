#include <Arduino.h>

#define ONE_WIRE_BUS 12
#define ON LOW
#define OFF HIGH
#define SS_PIN_OUT_0 11
#define SS_PIN_IN_0 10
#define SS_PIN_OUT_1 A0
#define SS_PIN_IN_1 A3
#define RELAY_VALVE_0 2
#define RELAY_VALVE_1 5
#define RELAY_VALVE_2 4
#define RELAY_VALVE_3 3
#define RELAY_VALVE_4 30
#define RELAY_VALVE_5 33
#define RELAY_VALVE_6 31
#define RELAY_VALVE_7 37

#define RELAY_PUMP    28
#define RELAY_PUMP_OUT    35


#define KNOB_0 32
#define KNOB_1 38
#define KNOB_2 40
#define ENCODER_PIN_0 42
#define ENCODER_PIN_1 44
#define ENCODER_KNOB  46
#define SAVE_KNOB_PIN 36
#define ESCAPE_KNOB_PIN 34

#define RELAY_LIGHT_0 22
#define RELAY_LIGHT_1 24
#define RELAY_LIGHT_2 31//26


#define _12_V_OUT_0 23
#define _12_V_OUT_1 25
#define _12_V_OUT_2 27
#define _12_V_OUT_3 29