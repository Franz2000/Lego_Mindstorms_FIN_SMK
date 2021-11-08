#ifndef MODE_MANAGEMENT_HEADER
#define MODE_MANAGEMENT_HEADER

#include <fcntl.h>
#include <unistd.h>

#include <linux/input.h>

#include "movements.h"
#include "verbose.h"

#define LEFT 105
#define RIGHT 106
#define UP 103
#define DOWN 108
#define ENTER 28

#define HEIGHT_MODE 0
#define ROTATE_MODE 1
#define GRAPPLE_MODE 2

#define PUSHED 1

extern void remote_arm_control(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor);

extern void button_arm_control(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor);

#endif
