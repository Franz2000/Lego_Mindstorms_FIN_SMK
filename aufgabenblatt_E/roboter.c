#include <fcntl.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#include <linux/input.h>

#include <ev3.h>
#include <ev3_port.h>
#include <ev3_sensor.h>
#include <ev3_tacho.h>

/*Global variable*/
int is_verbose = 0;
int is_remote_access = 0;

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

void print_verbose(int condition, const char *format, ...)
{
	if(!condition || !is_verbose)
	{
		return;
	}

	va_list args;
	va_start(args, format);
	while(*format != '\0')
	{
		if(*format == '%')
		{
			++format;
			switch(*format)
			{
				case 'i':	printf("%i", va_arg(args, int));
							break;
				case 's':	printf("%s", va_arg(args, char*));
							break;
				default:	printf("NOT FOUND");
			}
			++format;
			continue;
		}
		printf("%c", *format);
		++format;
	}
	va_end(args);
}

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

void move_arm_up(uint8_t sn_motor, uint8_t sn_sensor)
{
	set_sensor_mode(sn_sensor, "COL_REFLECT");
	int sensor_value;
	get_sensor_value(0, sn_sensor, &sensor_value);

	print_verbose(1, "The color sensor value is %i\n", sensor_value);

	if(sensor_value < 71)
	{
		set_tacho_speed_sp(sn_motor, 100);
		set_tacho_stop_action_inx(sn_motor, TACHO_BRAKE);
		set_tacho_position_sp(sn_motor, -20);
		set_tacho_command_inx(sn_motor, TACHO_RUN_TO_REL_POS);
	}
}

void move_arm_down(uint8_t sn_motor, uint8_t sn_sensor)
{
	set_sensor_mode(sn_sensor, "COL_REFLECT");
	int sensor_value;
	get_sensor_value(0, sn_sensor, &sensor_value);

	print_verbose(1, "The color sensor value is %i\n", sensor_value);

	if(sensor_value > 5)
	{
		set_tacho_speed_sp(sn_motor, 100);
		set_tacho_stop_action_inx(sn_motor, TACHO_BRAKE);
		set_tacho_position_sp(sn_motor, 20);
		set_tacho_command_inx(sn_motor, TACHO_RUN_TO_REL_POS);
	}
}

void move_arm_right(uint8_t sn_motor, uint8_t sn_sensor)
{
	set_sensor_mode(sn_sensor, "TOUCH");
	int sensor_value;
	get_sensor_value(0, sn_sensor, &sensor_value);

	print_verbose(1, "The touch sensor value is %i\n", sensor_value);

	if(sensor_value == 1)
	{
		set_tacho_position(sn_motor, 0);
		return;
	}

	set_tacho_speed_sp(sn_motor, 100);
	set_tacho_stop_action_inx(sn_motor, TACHO_BRAKE);
	set_tacho_position_sp(sn_motor, 20);
	set_tacho_command_inx(sn_motor, TACHO_RUN_TO_REL_POS);
}

void move_arm_left(uint8_t sn_motor)
{
	int current_position;
	get_tacho_position(sn_motor, &current_position);

	print_verbose(1, "The current position of Motor L Port C is %i\n", current_position);

	if(current_position > -600)
	{
		set_tacho_speed_sp(sn_motor, 100);
		set_tacho_stop_action_inx(sn_motor, TACHO_BRAKE);
		set_tacho_position_sp(sn_motor, -20);
		set_tacho_command_inx(sn_motor, TACHO_RUN_TO_REL_POS);
	}
}

void _move_grapple_gear_right(uint8_t sn_motor)
{
	int current_position;
	get_tacho_position(sn_motor, &current_position);

	print_verbose(1, "The current position of Motor M is %i\n", current_position);

	if(current_position > -150)
	{
		set_tacho_speed_sp(sn_motor, 100);
		set_tacho_stop_action_inx(sn_motor, TACHO_BRAKE);
		set_tacho_position_sp(sn_motor, -10);
		set_tacho_command_inx(sn_motor, TACHO_RUN_TO_REL_POS);
	}
}

void _move_grapple_gear_left(uint8_t sn_motor)
{
	int current_position;
	get_tacho_position(sn_motor, &current_position);

	print_verbose(1, "The current position of Motor M is %i\n", current_position);

	if(current_position < 0)
	{
		set_tacho_speed_sp(sn_motor, 100);
		set_tacho_stop_action_inx(sn_motor, TACHO_BRAKE);
		set_tacho_position_sp(sn_motor, 10);
		set_tacho_command_inx(sn_motor, TACHO_RUN_TO_REL_POS);
	}
}

void open_grapple(uint8_t sn_motor)
{
	int current_position;
	get_tacho_position(sn_motor, &current_position);

	if(-70 <  current_position)
	{
		_move_grapple_gear_right(sn_motor);
	}
	else if(current_position <= -70)
	{
		_move_grapple_gear_left(sn_motor);
	}
}

void close_grapple(uint8_t sn_motor)
{

	int current_position;
	get_tacho_position(sn_motor, &current_position);

	if(-70 <  current_position)
	{
		_move_grapple_gear_left(sn_motor);
	}
	else if(current_position <= -70)
	{
		_move_grapple_gear_right(sn_motor);
	}
}

void remote_arm_control(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor)
{
	char command;
	do
	{
		printf("Where should the arm  move?: ");
		scanf(" %c", &command);
		switch(command)
		{
			case 'U':	move_arm_up(sn_large_motor_1, sn_color_sensor);
						break;
			case 'D':	move_arm_down(sn_large_motor_1, sn_color_sensor);
						break;
			case 'R':	move_arm_right(sn_large_motor_2, sn_touch_sensor);
						break;
			case 'L':	move_arm_left(sn_large_motor_2);
						break;
			case 'O':	open_grapple(sn_medium_motor);
						break;
			case 'C':	close_grapple(sn_medium_motor);
						break;
		}
	}
	while(command != 'E');
}

void button_arm_control(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor)
{
	int fd = open("/dev/input/by-path/platform-gpio_keys-event", O_RDONLY);
	print_verbose(fd < 0, "Opening the key events failed.\n");

	struct input_event key_event;
	int mode = 0;

	while(1)
	{
		if(read(fd, &key_event, sizeof(struct input_event)) < 0)
		{
			print_verbose(1, "Reading key events failed.\n");
			break;
		}

		if(key_event.code == 105 && key_event.value == 1) //LEFT
		{
			mode = mode == 0 ? 0 : --mode;
		}
		if(key_event.code == 106 && key_event.value == 1) //RIGHT
		{
			mode = mode == 2 ? 2 : ++mode;
		}
		if(key_event.code == 103 && key_event.value == 1) //UP
		{
			switch(mode)
			{
				case 0:	move_arm_up(sn_large_motor_1, sn_color_sensor);
						break;
				case 1: move_arm_right(sn_large_motor_2, sn_touch_sensor);
						break;
				case 2: open_grapple(sn_medium_motor);
			}
		}
		if(key_event.code == 108 && key_event.value == 1) //DOWN
		{
			switch(mode)
			{
				case 0:	move_arm_down(sn_large_motor_1, sn_color_sensor);
						break;
				case 1: move_arm_left(sn_large_motor_2);
						break;
				case 2: close_grapple(sn_medium_motor);
			}
		}
		if(key_event.code == 28 && key_event.value == 1) //ENTER
		{
			break;
		}

	}
	close(fd);
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
