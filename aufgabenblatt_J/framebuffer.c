
#include "framebuffer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

char *init_framebuffer(int *file_descriptor)
{
	*file_descriptor = open("/dev/fb0", O_RDWR);
	print_verbose(*file_descriptor < 0, "Could not open the /dev/fb0 file\n");
	print_verbose(*file_descriptor > 0, "Open the /dev/fb0 file\n");

	char *framebuffer_ptr = (char *) mmap(0, SCREENSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, *file_descriptor, 0);
	print_verbose((int) framebuffer_ptr  < 0, "Could not create a memmory for the framebuffer\n");
	print_verbose(!((int) framebuffer_ptr < 0), "Create a memory for the framebuffer\n");

	return framebuffer_ptr;
}

void close_framebuffer(int file_descriptor, char *framebuffer_ptr)
{
	munmap(framebuffer_ptr, SCREENSIZE);
	close(file_descriptor);
	print_verbose(1, "Close the framebuffer\n");
}

void _set_pixel_white(int xPos, int yPos, char *framebuffer_ptr)
{
	framebuffer_ptr[yPos * LINE_LENGTH + xPos * 4] = 255;
	framebuffer_ptr[yPos * LINE_LENGTH + xPos * 4 + 1] = 255;
	framebuffer_ptr[yPos * LINE_LENGTH + xPos * 4 + 2] = 255;
	framebuffer_ptr[yPos * LINE_LENGTH + xPos * 4 + 3] = 255;
}

void _set_pixel_black(int xPos, int yPos, char *framebuffer_ptr)
{
	framebuffer_ptr[yPos * LINE_LENGTH + xPos * 4] = 0;
	framebuffer_ptr[yPos * LINE_LENGTH + xPos * 4 + 1] = 0;
	framebuffer_ptr[yPos * LINE_LENGTH + xPos * 4 + 2] = 0;
	framebuffer_ptr[yPos * LINE_LENGTH + xPos * 4 + 3] = 0;
}

void _draw_left_arrow(int x, int y, char *framebuffer_ptr)
{
	int counter = 43 - (y - 20);
	if((counter >= 0 && x >= counter) || (counter < 0 && x >= counter * -1))
	{
		_set_pixel_black(x, y, framebuffer_ptr);
	}
	else
	{
		_set_pixel_white(x, y, framebuffer_ptr);
	}
}

void _draw_right_arrow(int x, int y, char *framebuffer_ptr)
{
	int counter = 134 + (y - 20);
	if((counter <= 177 && x <= counter) || (counter > 177 && x <= 177 - (counter - 177)))
	{
		_set_pixel_black(x, y, framebuffer_ptr);
	}
	else
	{
		_set_pixel_white(x, y, framebuffer_ptr);
	}
}

void _draw_up_arrow(int x, int y, char *framebuffer_ptr)
{
	int counter = 31 - (x - 57);
	if((counter >= 0 && y >= counter) || (counter < 0 && y >= counter * -1))
	{
		_set_pixel_black(x, y, framebuffer_ptr);
	}
	else
	{
		_set_pixel_white(x, y, framebuffer_ptr);
	}
}

void _draw_down_arrow(int x, int y, char *framebuffer_ptr)
{
	int counter = 96 + (x - 57);
	if((counter <= 127 && y <= counter) || (counter > 127 && y <= 127 - (counter - 127)))
	{
		_set_pixel_black(x, y, framebuffer_ptr);
	}
	else
	{
		_set_pixel_white(x, y, framebuffer_ptr);
	}
}

void _draw_vertical_arrow(int x, int y, char *framebuffer_ptr)
{
	if(0 <= x && x < 44)
	{
		_draw_left_arrow(x, y, framebuffer_ptr);
	}
	else if (44 <= x && x < 134)
	{
		if(49 <= y && y < 78)
		{
			_set_pixel_black(x, y, framebuffer_ptr);
		}
		else
		{
			_set_pixel_white(x, y, framebuffer_ptr);
		}
	}
	else if (134 <= x)
	{
		_draw_right_arrow(x, y, framebuffer_ptr);
	}
}


void _draw_horizontal_arrow(int x, int y, char *framebuffer_ptr)
{
	if(0 <= y && y < 32)
	{
		_draw_up_arrow(x, y, framebuffer_ptr);
	}
	else if (32 <= y && y < 96)
	{
		if(78 <= x && x < 99)
		{
			_set_pixel_black(x, y, framebuffer_ptr);
		}
		else
		{
			_set_pixel_white(x, y, framebuffer_ptr);
		}
	}
	else if (96 <= y)
	{
		_draw_down_arrow(x, y, framebuffer_ptr);
	}
}

void draw_left_right_arrow(char *framebuffer_ptr)
{
	/*white line above arrow*/
	for(int y = 0; y < 20; y++)
	{
		for(int x = 0; x < WIDTH; x++)
		{
			_set_pixel_white(x, y, framebuffer_ptr);
		}
	}

	/*Draw Arrow*/
	for(int y = 20; y < 107; y++)
	{
		for(int x = 0; x < WIDTH; x++)
		{
			_draw_vertical_arrow(x, y, framebuffer_ptr);
		}
	}

	/*White line below arrow*/
	for(int y = 107; y < HEIGHT; y++)
	{
		for(int x = 0; x < WIDTH; x++)
		{
			_set_pixel_white(x, y, framebuffer_ptr);
		}
	}
}

void draw_up_down_arrow(char *framebuffer_ptr)
{
	/*Draw line at the left side of the arrow*/
	for(int x = 0; x < 57; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			_set_pixel_white(x, y, framebuffer_ptr);
		}
	}

	/*Draw arrow*/
	for(int x = 57; x < 120; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			_draw_horizontal_arrow(x, y, framebuffer_ptr);
		}
	}

	/*Draw white line at the left side of the arrow*/
	for(int x = 120; x < WIDTH; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			_set_pixel_white(x, y, framebuffer_ptr);
		}
	}
}

void _draw_circle(int radius, char *framebuffer_ptr)
{
	double mx = 89.0;
	double my = 64.0;

	for(int x = 89 - radius; x < 89 + radius; x++)
	{
		double y1 = sqrt(pow(radius, 2) - pow((x - mx), 2)) + my;
		double y2 = my - sqrt(pow(radius, 2) - pow((x - mx), 2));

		_set_pixel_black(x, (int) y1, framebuffer_ptr);
		_set_pixel_black(x, (int) y2, framebuffer_ptr);
	}
}

void draw_circle(char *framebuffer_ptr)
{
	for(int y = 0; y < HEIGHT; y++)
	{
		for(int x = 0; x < WIDTH; x++)
		{
			_set_pixel_white(x, y, framebuffer_ptr);
		}
	}
	for(int r = 48; r < 64; r ++)
	{
		_draw_circle(r, framebuffer_ptr);
	}
}

void draw_image(char *image_path, char *framebuffer_ptr)
{
	int width, height, channels;
	unsigned char *img = stbi_load(image_path, &width, &height, &channels, 0);

	print_verbose(img == NULL, "I did not find the photo at %s", image_path);
	print_verbose(img != NULL, "I found the photo at %s", image_path);

	int y_start = 0;
	int x_start = 0;
	if(height < HEIGHT)
	{
		y_start = (HEIGHT - height) / 2;
	}

	if(width < WIDTH)
	{
		x_start = (WIDTH - width) / 2;
	}

	for(int i = 0; i < HEIGHT * WIDTH * 4; i++)
	{
		framebuffer_ptr[i] = 255;
	}

	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			int img_index = (y * width + x) * channels;
			if(img[img_index] == 255 && img[img_index + 1] == 255 && img[img_index + 2] == 255 && img[img_index + 3] == 255)
			{
				_set_pixel_white(x + x_start, y + y_start, framebuffer_ptr);
			}
			else
			{
				_set_pixel_black(x + x_start, y + y_start, framebuffer_ptr);
			}
		}
	}
}
