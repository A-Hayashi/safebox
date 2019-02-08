#ifndef DEBUG
#define DEBUG

#include "Arduino.h"
#include "LED.h"
#include "SW.h"
#include "mp3.h"
#include "FelicaID.h"
#include "RY.h"

void led_check();
void mp3_check();
void power_latch_check();
void Felica_check();
void sw_check();
void lock_check();
void Felica_id_check();
void eink_check();


#define USING   0
#define CAN_USE 1

void eink_init();
void eink_disp(byte disp);
void Felica_id_clear();

#endif
