#include "movements.h"

void move_arm_up(uint8_t sn_motor, uint8_t sn_sensor)
{
	set_sensor_mode(sn_sensor, "COL_REFLECT");
	int sensor_value;
	get_sensor_value(0, sn_sensor, &sensor_value);

	print_verbose(1, "The color sensor value is %i\n", sensor_value);

	if(sensor_value < UPPER_HEIGHT_LIMIT)
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

	if(sensor_value > LOWER_HEIGHT_LIMIT)
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

	if(sensor_value == SENSOR_TOUCHED)
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

	if(current_position > LEFT_LIMIT)
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

	if(current_position > RIGHT_GEAR_LIMIT)
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

	if(current_position < LEFT_GEAR_LIMIT)
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
		_move_grapple_gear_left(sn_motor);
	}
	else if(current_position <= OPENED_GRAPPLE)
	{
		_move_grapple_gear_right(sn_motor);
	}
}
