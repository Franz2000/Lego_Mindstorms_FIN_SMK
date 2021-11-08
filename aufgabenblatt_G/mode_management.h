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

/*****************************************************************************
* remote_arm_control
*
* @param [in] sn_large_motor_1	Sequence number of the large motor at Port B
* @param [in] sn_large_motor_2	Sequence number of the large motor at Port C
* @param [in] sn_medium_motor	Sequence number of the medium motor at Port A
* @param [in] sn_color_sensor	Sequence number of the color sensor at Port 3
* @param [in] sn_touch_sensor	Sequence number of the toucn sensor at Port 1
*
* The control function enable the remote access to control the arm with the
* console of the SSH connection.
******************************************************************************/
extern void remote_arm_control(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor);

/*****************************************************************************
* button_arm_control
*
* @param [in] sn_large_motor_1	Sequence number of the large motor at Port B
* @param [in] sn_large_motor_2	Sequence number of the large motor at Port C
* @param [in] sn_medium_motor	Sequence number of the medium motor at Port A
* @param [in] sn_color_sensor	Sequence number of the color sensor at Port 3
* @param [in] sn_touch_sensor	Sequence number of the toucn sensor at Port 1
*
* The control function enable the buttons to control the arm.
* => With the LEFT and RIGHT Button you can change the mode of the arm.
*	(Modes: up/down, left/right, open/close)
* => The Buttons UP and DOWN controls the movements of the arm e.g. move
*	arm up.
* => The ENTER-Button stops the program.
******************************************************************************/
extern void button_arm_control(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor);

#endif
