#ifndef MOVEMENTS_HEADER
#define MOVEMENTS_HEADER

#include <unistd.h>

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

extern int reset_rotation;
extern int reset_height;
extern int reset_grapple;

/*****************************************************************************
* move_arm_up
*
* @param [in] sn_motor		Sequence number of the large motor at Port B
* @param [in] sn_sensor		Sequence number of the color sensor at Port 3
*
* The function moves the arm up until a special sensor value is met.
******************************************************************************/
extern void move_arm_up(uint8_t sn_motor, uint8_t sn_sensor);

/*****************************************************************************
* move_arm_down
*
* @param [in] sn_motor		Sequence number of the large motor at Port B
* @param [in] sn_sensor		Sequence number of the color sensor at Port 3
*
* The function moves the arm down until a special sensor value is met.
******************************************************************************/
extern void move_arm_down(uint8_t sn_motor, uint8_t sn_sensor);

/*****************************************************************************
* move_arm_right
*
* @param [in] sn_motor		Sequence number of the large motor at Port C
* @param [in] sn_sensor		Sequence number of the touch sensor at Port 1
*
* The arm to the right until the touch sensor is pushed.
******************************************************************************/
extern void move_arm_right(uint8_t sn_motor, uint8_t sn_sensor);

/*****************************************************************************
* move_arm_left
*
* @param [in] sn_motor		Sequence number of the large motor at Port C
*
* The arm rotate to the left until it meets a special position.
******************************************************************************/
extern void move_arm_left(uint8_t sn_motor);

/*****************************************************************************
* open grapple
*
* @param [in] sn_motor		Sequence number of the medium motor at Port A
*
* Open the grapple until a special position occurs.
******************************************************************************/
extern void open_grapple(uint8_t sn_motor);

/*****************************************************************************
* close grapple
*
* @param [in] sn_motor		Sequence number of the medium motor at Port A
*
* Close the grapple until a special position occurs.
******************************************************************************/
extern void close_grapple(uint8_t sn_motor);

/****************************************************************************
* reset
*
* @param [in] sn_large_motor_1	Sequence number of large motor at Port B
* @param [in] sn_large_motor_2	Sequence number of large motor at Port C
* @param [in] sn_medium_motor	Sequence number of medium motor at Port A
* @param [in] sn_color_sensor	Sequence number of the color sensor at Port 3
* @param [in] sn_touch_sensor	Sequence number of the touch sensor at Port 1
*
* The motor drives back into its start position.
* The start position:
* 	=> grapple is closed
*	=> the arm is down
*	=> the arm rotates until the touch sensor is pushed
*****************************************************************************/
extern void reset(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor);


/****************************************************************************
* move arm automatically left
*
* @param [in] sn_large_motor_1	Sequence number of large motor at Port B
* @param [in] sn_large_motor_2	Sequence number of large motor at Port C
* @param [in] sn_medium_motor	Sequence number of medium motor at Port A
* @param [in] sn_color_sensor	Sequence number of the color sensor at Port 3
* @param [in] sn_touch_sensor	Sequence number of the touch sensor at Port 1
*
* The arm take a thing on the left side an put it on the right side and
* return to its start position
*****************************************************************************/
extern void move_arm_automatically_left(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor);


/****************************************************************************
* move arm automatically left
*
* @param [in] sn_large_motor_1	Sequence number of large motor at Port B
* @param [in] sn_large_motor_2	Sequence number of large motor at Port C
* @param [in] sn_medium_motor	Sequence number of medium motor at Port A
* @param [in] sn_color_sensor	Sequence number of the color sensor at Port 3
* @param [in] sn_touch_sensor	Sequence number of the touch sensor at Port 1
*
* The arm take a thing on the right side an put it on the left side and
* return to its start position
*****************************************************************************/
extern void move_arm_automatically_right(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor);
#endif
