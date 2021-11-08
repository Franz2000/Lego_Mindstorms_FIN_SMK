#ifndef INITIALIZER_HEADER
#define INITIALIZER_HEADER

#include <ev3.h>
#include <ev3_port.h>
#include <ev3_sensor.h>
#include <ev3_tacho.h>

#include "verbose.h"

/*****************************************************************************
* init_sensor
*
* @param [out] *sn_sensor_port_1	Sequence number of the sensor at Port 1
* @param [out] *sn_sensor_port_3	Sequence number of the sensor at Port 3
*
* The function searchs for sensors and gives them with sequence numbers as
* ID.
******************************************************************************/
extern void init_sensor(uint8_t *sn_sensor_port_1, uint8_t *sn_sensor_port_3);

/*****************************************************************************
* init_actuator
*
* @param [out] *sn_motor_port_A		Sequence number of the motor at Port A
* @param [out] *sn_motor_port_B		Sequence number of the motor at Port B
* @param [out] *sn_motor_port_C		Sequence number of the motor at Port C
*
* The function searchs for actuator (specially motors) and gives the
* sequence numbers as ID
******************************************************************************/
extern void init_actuator(uint8_t *sn_motor_port_A, uint8_t *sn_motor_port_B, uint8_t *sn_motor_port_C);
#endif
