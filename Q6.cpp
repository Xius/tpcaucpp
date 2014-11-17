//https://github->com/Xius/tpcaucpp->git
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"




//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
	screen image = image;

//--------------------------------------------------------------------------
// Read file "gargouille->ppm" into image (width and height)
//--------------------------------------------------------------------------
	char* filename;
	filename = "gargouille.ppm";
	image.ppm_read_from_file(filename);



//--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW->ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw

	screen image_bw = image_bw;



	return 0;
}
