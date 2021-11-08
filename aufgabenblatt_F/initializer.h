#ifndef INITIALIZER_HEADER
#define INITIALIZER_HEADER

#include <ev3.h>
#include <ev3_port.h>
#include <ev3_sensor.h>
#include <ev3_tacho.h>

#include "verbose.h"

extern void init_sensor(uint8_t *sn_sensor_port_1, uint8_t *sn_sensor_port_3);

extern void init_actuator(uint8_t *sn_motor_port_A, uint8_t *sn_motor_port_B, uint8_t *sn_motor_port_C);
#endif
