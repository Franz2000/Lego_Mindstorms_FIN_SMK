#include "initializer.h"

uint8_t _search_sensor(INX_T type_inx, const char *name)
{
	uint8_t sn_sensor;
	int found_sensor = ev3_search_sensor(type_inx, &sn_sensor, 0);
	char buf[255];
	ev3_sensor_port_name(sn_sensor, buf);
	print_verbose(found_sensor, "The sensor %s is found at Port %s.\n", ev3_sensor_type(type_inx), buf);
	print_verbose(!found_sensor, "Do not found a %s.\n", name);
	return sn_sensor;
}

void init_sensor(uint8_t *sn_sensor_port_1, uint8_t *sn_sensor_port_3)
{
	int number_of_sensors = ev3_sensor_init();
	print_verbose(1, "The number of found sensors is %i.\n", number_of_sensors);

	/*Init color sensor*/
	*sn_sensor_port_3 = _search_sensor(LEGO_EV3_COLOR, "color sensor");

	/*Init touch sensor*/
	*sn_sensor_port_1 = _search_sensor(LEGO_EV3_TOUCH, "touch sensor");
}

uint8_t _search_actuator(INX_T type_inx, uint8_t port, const char *name)
{
	uint8_t sn_motor;
	int found_actuator = 0;
	char buf[255];
	if(port == EV3_PORT__NONE_)
	{
		found_actuator = ev3_search_tacho(type_inx, &sn_motor, 0);
	}
	else
	{
		found_actuator = ev3_search_tacho_plugged_in(port, EXT_PORT__NONE_, &sn_motor, 0);
	}
	ev3_tacho_port_name(sn_motor, buf);
	print_verbose(found_actuator, "The motor %s is found at Port %s.\n", ev3_tacho_type(type_inx), buf);
	print_verbose(!found_actuator, "Do not found the %s.\n", name);
	return sn_motor;
}

void init_actuator(uint8_t *sn_motor_port_A, uint8_t *sn_motor_port_B, uint8_t *sn_motor_port_C)
{
	int number_of_actuator = ev3_tacho_init();
	print_verbose(1,"The number of found actuators is %i.\n", number_of_actuator);

	/*Init medium motor*/
	*sn_motor_port_A = _search_actuator(LEGO_EV3_M_MOTOR, EV3_PORT__NONE_, "medium motor");
	/*Init large motor 1*/
	*sn_motor_port_B = _search_actuator(LEGO_EV3_L_MOTOR, OUTPUT_B, "large motor 1");

	/*Init large motor 2*/
	*sn_motor_port_C = _search_actuator(LEGO_EV3_L_MOTOR, OUTPUT_C, "large motor 2");
}
