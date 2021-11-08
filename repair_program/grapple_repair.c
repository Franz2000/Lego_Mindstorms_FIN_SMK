#include <stdio.h>

#include <ev3.h>
#include <ev3_tacho.h>

int main()
{
	uint8_t sn_motor;

	ev3_init();

	if(ev3_search_tacho(LEGO_EV3_M_MOTOR, &sn_motor, 0))
	{
		set_tacho_position(sn_motor, 0);
	}
	else
	{
		printf("No reset!\n");
	}
	ev3_uninit();
}
