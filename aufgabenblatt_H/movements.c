#include "movements.h"

/*variables for the reset method*/
int reset_height = 0;
int reset_grapple = 0;
int reset_rotation = 0;

void move_arm_up(uint8_t sn_motor, uint8_t sn_sensor)
{
	set_sensor_mode(sn_sensor, "COL_REFLECT");
	int sensor_value;
	get_sensor_value(0, sn_sensor, &sensor_value);

	print_verbose(1, "The color sensor value is %i\n", sensor_value);

	if(sensor_value < UPPER_HEIGHT_LIMIT)
	{
		reset_height = 0;
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

	if(sensor_value > LOWER_HEIGHT_LIMIT)
	{
		set_tacho_speed_sp(sn_motor, 100);
		set_tacho_stop_action_inx(sn_motor, TACHO_BRAKE);
		set_tacho_position_sp(sn_motor, 20);
		set_tacho_command_inx(sn_motor, TACHO_RUN_TO_REL_POS);
	}
	else
	{
		reset_height = 1;
	}
}

void move_arm_right(uint8_t sn_motor, uint8_t sn_sensor)
{
	set_sensor_mode(sn_sensor, "TOUCH");
	int sensor_value;
	get_sensor_value(0, sn_sensor, &sensor_value);

	print_verbose(1, "The touch sensor value is %i\n", sensor_value);

	if(sensor_value == SENSOR_TOUCHED)
	{
		set_tacho_position(sn_motor, 0);
		reset_rotation = 1;
		return;
	}
	reset_rotation = 0;
	set_tacho_speed_sp(sn_motor, 100);
	set_tacho_stop_action_inx(sn_motor, TACHO_BRAKE);
	set_tacho_position_sp(sn_motor, 20);
	set_tacho_command_inx(sn_motor, TACHO_RUN_TO_REL_POS);
}

void move_arm_left(uint8_t sn_motor)
{
	int current_position;
	get_tacho_position(sn_motor, &current_position);
	reset_rotation = 0;

	print_verbose(1, "The current position of Motor L Port C is %i\n", current_position);

	if(current_position > LEFT_LIMIT)
	{
		set_tacho_speed_sp(sn_motor, 100);
		set_tacho_stop_action_inx(sn_motor, TACHO_BRAKE);
		set_tacho_position_sp(sn_motor, -20);
		set_tacho_command_inx(sn_motor, TACHO_RUN_TO_REL_POS);
	}
}

int  _move_grapple_gear_right(uint8_t sn_motor)
{
	int current_position;
	get_tacho_position(sn_motor, &current_position);

	print_verbose(1, "The current position of Motor M is %i\n", current_position);

	if(current_position > RIGHT_GEAR_LIMIT)
	{
		set_tacho_speed_sp(sn_motor, 100);
		set_tacho_stop_action_inx(sn_motor, TACHO_BRAKE);
		set_tacho_position_sp(sn_motor, -10);
		set_tacho_command_inx(sn_motor, TACHO_RUN_TO_REL_POS);
		return 0;
	}
	return 1;
}

int _move_grapple_gear_left(uint8_t sn_motor)
{
	int current_position;
	get_tacho_position(sn_motor, &current_position);

	print_verbose(1, "The current position of Motor M is %i\n", current_position);

	if(current_position < LEFT_GEAR_LIMIT)
	{
		set_tacho_speed_sp(sn_motor, 100);
		set_tacho_stop_action_inx(sn_motor, TACHO_BRAKE);
		set_tacho_position_sp(sn_motor, 10);
		set_tacho_command_inx(sn_motor, TACHO_RUN_TO_REL_POS);
		return 0;
	}
	return 1;
}

void open_grapple(uint8_t sn_motor)
{
	int current_position;
	get_tacho_position(sn_motor, &current_position);

	if(OPENED_GRAPPLE <  current_position)
	{
		_move_grapple_gear_right(sn_motor);
	}
	else if(current_position <= OPENED_GRAPPLE)
	{
		_move_grapple_gear_left(sn_motor);
	}
}

void close_grapple(uint8_t sn_motor)
{

	int current_position;
	get_tacho_position(sn_motor, &current_position);

	if(OPENED_GRAPPLE <  current_position)
	{
		reset_grapple = _move_grapple_gear_left(sn_motor);
	}
	else if(current_position <= OPENED_GRAPPLE)
	{
		reset_grapple = _move_grapple_gear_right(sn_motor);
	}
}

void reset(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor)
{
	/*Move the arm completly to the right*/
	while(!reset_rotation)
	{
		move_arm_right(sn_large_motor_2, sn_touch_sensor);
		usleep(200000);
	}

	/*Close grapple completely*/
	while(!reset_grapple)
	{
		close_grapple(sn_medium_motor);
		usleep(200000);
	}

	/*Move the arm down completely*/
	while(!reset_height)
	{
		move_arm_down(sn_large_motor_1, sn_color_sensor);
		usleep(200000);
	}
}
