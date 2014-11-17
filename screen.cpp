#include "screen.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>





screen::screen(void)
{
	width=0;
	height=0;
	image = new unsigned char[0];// pointeur vide
}
screen::screen(const screen& model)
{
	width = model.getwidth();
	height = model.getheight();
	printf("%d %d\n",width,height);
	image = new unsigned char[3 *width*height];
	memcpy(image, model.getimage(), 3 *width*height*sizeof(u_char));
}	
unsigned char* screen::getimage(void)
{
	return image;
}
int screen::getwidth(void) const
{
	return width;
}
int screen::getheight(void) const
{
	return height;
}

void screen :: ppm_write_to_file(const char* filename)
{
  FILE* ppm_output = fopen(filename, "wb");
  // Write header
  fprintf(ppm_output, "P6\n%d %d\n255\n", width, height);

  // Write pixels
  fwrite(image, 3, width * height, ppm_output);
  fclose(ppm_output);
  
}

void screen:: ppm_read_from_file(const char* filename)
{
  FILE* ppm_input = fopen(filename, "rb");
  // Read file header
  fscanf(ppm_input, "P6\n%d %d\n255\n", &width, &height);

  // Allocate memory according to width and height
  image  = new unsigned char[3 * width * height];

  // Read the actual image data
  fread(image, 3, (width) * (height), ppm_input);
  fclose(ppm_input);
}

void screen :: ppm_desaturate(void)
{
  int x, y;

  // For each pixel ...
  for (x = 0 ; x < width ; x++)
  {
    for (y = 0 ; y < height ; y++)
    {
      unsigned int grey_lvl = 0;
      int rgb_canal;

      // Compute the grey level
      for (rgb_canal = 0 ; rgb_canal < 3 ; rgb_canal++)
      {
        grey_lvl += image[ 3 * (y * width + x) + rgb_canal ];
      }
      grey_lvl /= 3;
      assert(grey_lvl >= 0 && grey_lvl <=255);

      // Set the corresponding pixel's value in new_image
      memset(&image[3 * (y * width + x)], grey_lvl, 3);
    }
  }
}

void screen :: ppm_shrink(int factor)
{
  // Compute new image size and allocate memory for the new image
  int new_width   = (width) / factor;
  int new_height  = (height) / factor;
  unsigned char* new_image  = new unsigned char[3 * new_width * new_height];

  // Precompute factor^2 (for performance reasons)
  int factor_squared = factor * factor;

  // For each pixel of the new image...
  int x, y;
  for (x = 0 ; x < new_width ; x++)
  {
    for (y = 0 ; y < new_height ; y++)
    {
      // ... compute the average RGB values of the set of pixels (a square of side factor)
      // that correspond to the pixel we are creating.

      // Initialize RGB values for the new image's pixel
      unsigned int red   = 0;
      unsigned int green = 0;
      unsigned int blue  = 0;

      // Compute coordinates and index of the first (top-left) pixel from the
      // model image corresponding to the pixel we are creating
      int x0 = x * factor;
      int y0 = y * factor;
      int i0 = 3 * (y0 * (width) + x0);

      // Compute RGB values for the new pixel
      int dx, dy;
      for (dx = 0 ; dx < factor ; dx++)
      {
        for (dy = 0 ; dy < factor ; dy++)
        {
          // Compute the offset of the current pixel (in the model image)
          // with regard to the top-left pixel of the current "set of pixels"
          int delta_i = 3 * (dy * (width) + dx);

          // Accumulate RGB values
          red   += (image)[i0+delta_i];
          green += (image)[i0+delta_i+1];
          blue  += (image)[i0+delta_i+2];
        }
      }



      // Divide RGB values to get the mean values
      red   /= factor_squared;
      green /= factor_squared;
      blue  /= factor_squared;

      // Set new pixel's RGB values
      new_image[ 3 * (y * new_width + x) ]     = red;
      new_image[ 3 * (y * new_width + x) + 1 ] = green;
      new_image[ 3 * (y * new_width + x) + 2 ] = blue;
    }
  }

  // Update image size
  width  = new_width;
  height = new_height;

  // Update image
  //free(image);
  image = new_image;
}
