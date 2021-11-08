#include "mode_management.h"

void _remote_arm_control_manual(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor)
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
	while(command != 'B');
}

void _remote_arm_control_automatic(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor)
{
	char command;
	do
	{
		printf("Where should the arm  move?: ");
		scanf(" %c", &command);
		switch(command)
		{
			case 'L':	move_arm_automatically_left(sn_large_motor_1, sn_large_motor_2, sn_medium_motor, sn_color_sensor, sn_touch_sensor);
						break;
			case 'R':	move_arm_automatically_right(sn_large_motor_1, sn_large_motor_2, sn_medium_motor, sn_color_sensor, sn_touch_sensor);
						break;
		}
	}
	while(command != 'B');
}

void remote_arm_control(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor)
{
	char command;
	int framebuffer_fd;
	int mode;

	char *framebuffer_ptr = init_framebuffer(&framebuffer_fd);

	do
	{
		printf("Which mode do you like to choose?: ");
		scanf(" %c", &command);

		switch(command)
		{
			case 'I':	_remote_arm_control_automatic(sn_large_motor_1, sn_large_motor_2, sn_medium_motor, sn_color_sensor, sn_touch_sensor);
						break;
			case 'M':	_remote_arm_control_manual(sn_large_motor_1, sn_large_motor_2, sn_medium_motor, sn_color_sensor, sn_touch_sensor);
						break;
		}
	}
	while(command != 'E');

	reset(sn_large_motor_1, sn_large_motor_2, sn_medium_motor, sn_color_sensor, sn_touch_sensor);
	close_framebuffer(framebuffer_fd, framebuffer_ptr);
}

void _start_automatic_mode(int fd, char *framebuffer_ptr, uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor)
{
	struct input_event key_event;

	while(1)
	{
		if(read(fd, &key_event, sizeof(struct input_event)) < 0)
		{
			print_verbose(1, "Reading key events failed.\n");
			break;
		}

		if(key_event.code == LEFT && key_event.value == PUSHED) //LEFT
		{
			move_arm_automatically_left(sn_large_motor_1, sn_large_motor_2, sn_medium_motor, sn_color_sensor, sn_touch_sensor);
		}
		if(key_event.code == RIGHT && key_event.value == PUSHED) //RIGHT
		{
			move_arm_automatically_right(sn_large_motor_1, sn_large_motor_2, sn_medium_motor, sn_color_sensor, sn_touch_sensor);
		}
		if(key_event.code == ENTER && key_event.value == PUSHED) //ENTER
		{
			break;
		}
	}
}

void _start_manual_mode(int fd, char *framebuffer_ptr, uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor)
{
	struct input_event key_event;
	int mode;

	draw_image("photos/hoehe.bmp", framebuffer_ptr);

	while(1)
	{
		if(read(fd, &key_event, sizeof(struct input_event)) < 0)
		{
			print_verbose(1, "Reading key events failed.\n");
			break;
		}

		switch(mode)
		{
			case GRAPPLE_MODE:	draw_image("photos/greifer.bmp" ,framebuffer_ptr);
								break;
			case HEIGHT_MODE: 	draw_image("photos/hoehe.bmp", framebuffer_ptr);
								break;
			case ROTATE_MODE:	draw_image("photos/drehen.bmp", framebuffer_ptr);
		}

		if(key_event.code == LEFT && key_event.value == PUSHED) //LEFT
		{
			mode = mode == 0 ? 0 : --mode;
		}
		if(key_event.code == RIGHT && key_event.value == PUSHED) //RIGHT
		{
			mode = mode == 2 ? 2 : ++mode;
		}
		if(key_event.code == UP && key_event.value == PUSHED) //UP
		{
			switch(mode)
			{
				case HEIGHT_MODE:	move_arm_up(sn_large_motor_1, sn_color_sensor);
									break;
				case ROTATE_MODE:	move_arm_right(sn_large_motor_2, sn_touch_sensor);
									break;
				case GRAPPLE_MODE:	open_grapple(sn_medium_motor);
			}
		}
		if(key_event.code == DOWN && key_event.value == PUSHED) //DOWN
		{
			switch(mode)
			{
				case HEIGHT_MODE:	move_arm_down(sn_large_motor_1, sn_color_sensor);
									break;
				case ROTATE_MODE: 	move_arm_left(sn_large_motor_2);
									break;
				case GRAPPLE_MODE: 	close_grapple(sn_medium_motor);
			}
		}
		if(key_event.code == ENTER && key_event.value == PUSHED) //ENTER
		{
			reset(sn_large_motor_1, sn_large_motor_2, sn_medium_motor, sn_color_sensor, sn_touch_sensor);
			break;
		}

	}
}

void button_arm_control(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor)
{
	int fd = open("/dev/input/by-path/platform-gpio_keys-event", O_RDONLY);
	print_verbose(fd < 0, "Opening the key events failed.\n");

	struct input_event key_event;
	int mode = 0;
	int framebuffer_fd;

	char *framebuffer_ptr = init_framebuffer(&framebuffer_fd);

	draw_image("photos/Fin2.bmp", framebuffer_ptr);
	sleep(5);
	draw_image("photos/automatik.bmp", framebuffer_ptr);

	while(1)
	{
		if(read(fd, &key_event, sizeof(struct input_event)) < 0)
		{
			print_verbose(1, "Reading key events failed.\n");
			break;
		}

		switch(mode)
		{
			case I_MODE:	draw_image("photos/automatik.bmp" ,framebuffer_ptr);
							break;
			case M_MODE: 	draw_image("photos/manuell.bmp", framebuffer_ptr);
		}

		if(key_event.code == LEFT && key_event.value == PUSHED) //LEFT
		{
			mode = mode == 0 ? 0 : --mode;
		}
		if(key_event.code == RIGHT && key_event.value == PUSHED) //RIGHT
		{
			mode = mode == 1 ? 1 : ++mode;
		}

		if(key_event.code == ENTER && key_event.value == PUSHED) //ENTER
		{
			switch(mode)
			{
				case I_MODE:	_start_automatic_mode(fd, framebuffer_ptr, sn_large_motor_1, sn_large_motor_2,sn_medium_motor, sn_color_sensor, sn_touch_sensor);
								break;
				case M_MODE:	_start_manual_mode(fd, framebuffer_ptr, sn_large_motor_1, sn_large_motor_2,sn_medium_motor, sn_color_sensor, sn_touch_sensor);
			}
		}
		if(key_event.code == BACKSPACE && key_event.value == PUSHED) //BACKSPACE
		{
			break;
		}
	}

	close_framebuffer(framebuffer_fd, framebuffer_ptr);
	close(fd);
}
