#include <string.h>

#include <ev3.h>

#include "initializer.h"
#include "mode_management.h"
#include "verbose.h"
/*Global variable*/
int is_remote_access = 0;
int is_verbose = 0;

void set_flag(int argc, char *argv[])
{
	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "-v") == 0)
		{
			is_verbose = 1;
		}
		else  if (strcmp(argv[i], "-ra") == 0)
		{
			is_remote_access = 1;
		}
	}
}

int main(int argc, char *argv[])
{
	/*Verbose Mode*/
	set_flag(argc, argv);

	/*Initialize Remote Access*/
	int remote_access_state = ev3_init();

	print_verbose(remote_access_state == 0, "EV3-Brick is not found!\n");
	print_verbose(remote_access_state == 1, "EV3-Brick is found!\n");
	print_verbose(remote_access_state == -1, "Error-finding EV3-Brick!\n");

	/*Sensor initialization*/
	uint8_t sn_touch_sensor;
	uint8_t sn_color_sensor;

	init_sensor(&sn_touch_sensor, &sn_color_sensor);

	/*Actuator initialization*/
	uint8_t sn_medium_motor;
	uint8_t sn_large_motor_1;
	uint8_t sn_large_motor_2;

	init_actuator(&sn_medium_motor, &sn_large_motor_1, &sn_large_motor_2);

	/*control of the arm*/
	if(is_remote_access)
	{
		remote_arm_control(sn_large_motor_1, sn_large_motor_2, sn_medium_motor, sn_color_sensor, sn_touch_sensor);
	}
	else
	{
		button_arm_control(sn_large_motor_1, sn_large_motor_2, sn_medium_motor, sn_color_sensor, sn_touch_sensor);
	}
	ev3_uninit();
	return 0;
}
