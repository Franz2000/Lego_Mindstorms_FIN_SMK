#ifndef FRAMEBUFFER_HEADER
#define FRAMEBUFFER_HEADER

#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>

#include <linux/fb.h>
#include <sys/mman.h>

#include "verbose.h"

#define SCREENSIZE 91136
#define WIDTH 178
#define HEIGHT 128
#define LINE_LENGTH 712

/*****************************************************************************
* init_framebuffer
*
* @param [out] *file_descriptor		Pointer to the file descriptor of the
*									framebuffer
* @return	returns a char Pointer to the memory space of the framebuffer
*
* The function initialize the framebuffer returns a pointer to the beginning
* of the memory where the pixels can be set black or white.
******************************************************************************/
extern char *init_framebuffer(int *file_descriptor);

/*****************************************************************************
* close_framebuffer
*
* @param [in] file_descriptor		file descriptor
* @param [in] *framebuffer_ptr		Pointer to the beginning of the memory
*									part in which you set the pixels
*
* The function frees the memory and close the file descriptor.
******************************************************************************/
extern void close_framebuffer(int file_descriptor, char *framebuffer_ptr);

extern void draw_left_right_arrow(char *framebuffer_ptr);

extern void draw_up_down_arrow(char *framebuffer_ptr);

extern void draw_circle(char *framebuffer_ptr);

/*****************************************************************************
* draw_image
*
* @param [in] *image_path			path to the image
* @param [in] *framebuffer_ptr		Pointer to the beginning of the memory
*									part in which you set the pixels
*
* This function draws an image in the middle of the LCD Display
******************************************************************************/
extern void draw_image(char *image_path, char *framebuffer_ptr);
#endif
