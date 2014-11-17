//https://github.com/Xius/tpcaucpp.git
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fonction.h>




//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------

  screen pixel;
  char* filename;
  filename = "gargouille.ppm";
  ppm_read_from_file(filename, &pixel.width, &pixel.height, &pixel.image);


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  screen pixel_bw;
  pixel_bw.width  = pixel.width;
  pixel_bw.height = pixel.height;
  pixel_bw.image = (unsigned char*) malloc(3 * pixel.width * pixel.height * sizeof(*pixel_bw.image));
  memcpy(pixel_bw.image, pixel.image, 3 * pixel.width * pixel.height * sizeof(*pixel_bw.image));

  // Desaturate image_bw
  ppm_desaturate(pixel_bw.image, pixel.width, pixel.height);

  // Write the desaturated image into "gargouille_BW.ppm"
  filename = "gargouille_BW.ppm";
  FILE* ppm_output = fopen("gargouille_BW.ppm", "wb");
  ppm_write_to_file(filename,pixel.width, pixel.height, pixel_bw.image);
  fclose(ppm_output);

  // Free the desaturated image
  free(pixel_bw.image);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  screen pixelsmall;
  pixelsmall.width  = pixel.width;
  pixelsmall.height = pixel.height;
  pixelsmall.image = (unsigned char*) malloc(3 * pixel.width * pixel.height * sizeof(*pixelsmall.image));
  memcpy(pixelsmall.image, pixel.image, 3 * pixel.width * pixelsmall.height * sizeof(pixelsmall.image));

  // Shrink image_small size 2-fold
  ppm_shrink(&pixelsmall.image, &pixelsmall.width, &pixelsmall.height, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  filename = "gargouille_small.ppm";
  ppm_write_to_file(filename ,pixelsmall.width, pixelsmall.height, pixelsmall.image);


  // Free the not yet freed images
  free(pixel.image);
  free(pixelsmall.image);

  return 0;
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
  *width  = new_width;
  *height = new_height;

  // Update image
  free(*image);
  *image = new_image;
}



































