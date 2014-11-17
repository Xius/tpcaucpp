//https://github->com/Xius/tpcaucpp->git
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"




//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille->ppm" into image (width and height)
  //--------------------------------------------------------------------------

  screen* pixel = new screen;
  
  char* filename;
  filename = "gargouille.ppm";
  ppm_read_from_file(filename, pixel);


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW->ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  screen* pixel_bw =  new screen;
  pixel_bw->width  = pixel->width;
  pixel_bw->height = pixel->height;
  pixel_bw->image = new unsigned char[3 * pixel->width * pixel->height];
  memcpy(pixel_bw->image, (pixel->image), 3 * pixel->width * pixel->height * sizeof(unsigned char));

  // Desaturate image_bw
  ppm_desaturate(pixel_bw);

  // Write the desaturated image into "gargouille_BW->ppm"
  filename = "gargouille_BW.ppm";
  ppm_write_to_file(filename,pixel_bw);

  // Free the desaturated image
  free(pixel_bw->image);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small->ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  screen* pixelsmall = new screen;
  pixelsmall->width  = pixel->width;
  pixelsmall->height = pixel->height;
  pixelsmall->image = new unsigned char[3 * pixel->width * pixel->height];
  memcpy(pixelsmall->image, pixel->image, 3 * pixel->width * pixelsmall->height * sizeof(unsigned char));

  // Shrink image_small size 2-fold
  ppm_shrink(pixelsmall, 2);

  // Write the desaturated image into "gargouille_small->ppm"
  filename = "gargouille_small.ppm";
  ppm_write_to_file(filename ,pixelsmall);


  // Free the not yet freed images
  free(pixel->image);
  free(pixelsmall->image);

  return 0;
}





































