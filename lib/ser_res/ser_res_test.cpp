//#include <Arduino.h>
#include "ser_res.h"

char sym = '~';
SerRes sr;

void print(int *);
void ledBlimk();



void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);


}

void loop() {
    int *a;
    int b;
    a = sr.response();
    b = a[0];
    if (b >= 0) {
        print(a);
        ledBlimk();
    }

}

void print(int *a) {
    Serial.print("a[0] -> ");
    Serial.println(a[0]);
    Serial.print("a[1] -> ");
    Serial.println(a[1]);

}

void ledBlimk(){
   static bool on = false;
   if(!on) {
       digitalWrite(LED_BUILTIN, HIGH);
       on = true;
   }else{
       digitalWrite(LED_BUILTIN, LOW);
       on = false;
   }
}