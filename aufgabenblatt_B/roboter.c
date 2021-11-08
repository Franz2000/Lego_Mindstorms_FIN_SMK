#include <string.h>
#include <stdio.h>

#include <ev3.h>
#include <ev3_port.h>
#include <ev3_sensor.h>
#include <ev3_tacho.h>

int main(int argc, char* argv[])
{
	/*Verbose Mode*/
	int is_verbose = 0;
	if(argc > 1)
	{
		if(strcmp(argv[1], "-v") == 0)
		{
			is_verbose = 1;
		}
	}

	/*Initialize Remote Access*/
	int remote_access_state = ev3_init();
	if(is_verbose)
	{
		switch(remote_access_state)
		{
			case 0: 	printf("EV3-Brick is not found!\n");
						break;
			case 1: 	printf("EV3-Brick is found!\n");
						break;
			case - 1: 	printf("Error-finding EV3-Brick!\n");
		}
	}

	/*Sensor initialization*/
	int number_of_sensors = ev3_sensor_init();
	if(is_verbose)
	{
		printf("The number of found sensors is %i.\n", number_of_sensors);
	}

	uint8_t sn_color_sensor;
	if(ev3_search_sensor(LEGO_EV3_COLOR, &sn_color_sensor, 0) && is_verbose)
	{
		char buf[255];
		ev3_sensor_port_name(sn_color_sensor, buf);
		printf("The sensor %s is found at Port %s.\n", ev3_sensor_type(LEGO_EV3_COLOR), buf);
	}
	else if(is_verbose)
	{
		printf("Do not found a color sensor.\n");
	}

	uint8_t sn_touch_sensor;
	if(ev3_search_sensor(LEGO_EV3_TOUCH, &sn_touch_sensor, 0) && is_verbose)
	{
		char buf[255];
		ev3_sensor_port_name(sn_touch_sensor, buf);
		printf("The sensor %s is found at Port %s.\n", ev3_sensor_type(LEGO_EV3_TOUCH), buf);
	}
	else if(is_verbose)
	{
		printf("Do not found a color sensor.\n");
	}

	/*Actuator initialization*/
	int number_of_actuator = ev3_tacho_init();
	if(is_verbose)
	{
		printf("The number of found actuators is %i.\n", number_of_actuator);
	}

	uint8_t sn_medium_motor;
	if(ev3_search_tacho(LEGO_EV3_M_MOTOR, &sn_medium_motor, 0) && is_verbose)
	{
		char buf[255];
		ev3_tacho_port_name(sn_medium_motor, buf);
		printf("The motor %s is found at Port %s.\n", ev3_tacho_type(LEGO_EV3_M_MOTOR), buf);
	}
	else if(is_verbose)
	{
		printf("Do not found the medium motor.\n");
	}

	uint8_t sn_large_motor_1;
	if(ev3_search_tacho_plugged_in(OUTPUT_B, EXT_PORT__NONE_, &sn_large_motor_1, 0) && is_verbose)
	{
		char buf[255];
		ev3_tacho_port_name(sn_large_motor_1, buf);
		printf("The motor %s is found at Port %s.\n", ev3_tacho_type(LEGO_EV3_L_MOTOR), buf);
	}
	else if(is_verbose)
	{
		printf("Do not found the large motor.\n");
	}

	uint8_t sn_large_motor_2;
	if(ev3_search_tacho_plugged_in(OUTPUT_C, EXT_PORT__NONE_, &sn_large_motor_2, 0) && is_verbose)
	{
		char buf[255];
		ev3_tacho_port_name(sn_large_motor_2, buf);
		printf("The motor %s is found at Port %s.\n", ev3_tacho_type(LEGO_EV3_L_MOTOR), buf);
	}
	else if(is_verbose)
	{
		printf("Do not found the large motor.\n");
	}
	ev3_uninit();
	return 0;
}
