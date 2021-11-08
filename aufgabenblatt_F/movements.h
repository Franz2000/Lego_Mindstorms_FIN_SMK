#ifndef MOVEMENTS_HEADER
#define MOVEMENTS_HEADER

#include <ev3.h>
#include <ev3_sensor.h>
#include <ev3_tacho.h>

#include "verbose.h"

#define UPPER_HEIGHT_LIMIT 71
#define LOWER_HEIGHT_LIMIT 5
#define LEFT_LIMIT -600
#define SENSOR_TOUCHED 1
#define RIGHT_GEAR_LIMIT -150
#define LEFT_GEAR_LIMIT 0
#define OPENED_GRAPPLE -70

extern void move_arm_up(uint8_t sn_motor, uint8_t sn_sensor);

extern void move_arm_down(uint8_t sn_motor, uint8_t sn_sensor);

extern void move_arm_right(uint8_t sn_motor, uint8_t sn_sensor);

extern void move_arm_left(uint8_t sn_motor);

extern void open_grapple(uint8_t sn_motor);

extern void close_grapple(uint8_t sn_motor);

#endif
