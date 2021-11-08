#include "mode_management.h"

void remote_arm_control(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor)
{
	char command;
	int framebuffer_fd;

	char *framebuffer_ptr = init_framebuffer(&framebuffer_fd);

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

	reset(sn_large_motor_1, sn_large_motor_2, sn_medium_motor, sn_color_sensor, sn_touch_sensor);
	close_framebuffer(framebuffer_fd, framebuffer_ptr);
}

void button_arm_control(uint8_t sn_large_motor_1, uint8_t sn_large_motor_2, uint8_t sn_medium_motor, uint8_t sn_color_sensor, uint8_t sn_touch_sensor)
{
	int fd = open("/dev/input/by-path/platform-gpio_keys-event", O_RDONLY);
	print_verbose(fd < 0, "Opening the key events failed.\n");

	struct input_event key_event;
	int mode = 0;
	int framebuffer_fd;

	char *framebuffer_ptr = init_framebuffer(&framebuffer_fd);

	while(1)
	{
		if(read(fd, &key_event, sizeof(struct input_event)) < 0)
		{
			print_verbose(1, "Reading key events failed.\n");
			break;
		}

		switch(mode)
		{
			case GRAPPLE_MODE:	draw_left_right_arrow(framebuffer_ptr);
								break;
			case HEIGHT_MODE: 	draw_up_down_arrow(framebuffer_ptr);
								break;
			case ROTATE_MODE:	draw_circle(framebuffer_ptr);
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

	close_framebuffer(framebuffer_fd, framebuffer_ptr);
	close(fd);
}
