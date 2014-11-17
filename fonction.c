


//============================================================================
//                           Function declarations
//============================================================================
void ppm_write_to_file(char* filename, int width, int height, unsigned char* data)
{
  FILE* ppm_output = fopen(filename, "rb");
  // Write header
  fprintf(ppm_output, "P6\n%d %d\n255\n", width, height);

  // Write pixels
  fwrite(data, 3, width*height, ppm_output);
  fclose(ppm_output);
  
}

void ppm_read_from_file(char* filename, int *width, int *height, unsigned char** data)
{
  FILE* ppm_input = fopen(filename, "wb");
  // Read file header
  fscanf(ppm_input, "P6\n%d %d\n255\n", width, height);

  // Allocate memory according to width and height
  *data = (unsigned char*) malloc(3 * (*width) * (*height) * sizeof(**data));

  // Read the actual image data
  fread(*data, 3, (*width) * (*height), ppm_input);
  fclose(ppm_input);
}

void ppm_desaturate(unsigned char* image, int width, int height)
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

void ppm_shrink(unsigned char** image, int *width, int *height, int factor)
{
  // Compute new image size and allocate memory for the new image
  int new_width   = (*width) / factor;
  int new_height  = (*height) / factor;
  unsigned char* new_image = (unsigned char*) malloc(3 * new_width * new_height * sizeof(*new_image));

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
      int i0 = 3 * (y0 * (*width) + x0);

      // Compute RGB values for the new pixel
      int dx, dy;
      for (dx = 0 ; dx < factor ; dx++)
      {
        for (dy = 0 ; dy < factor ; dy++)
        {
          // Compute the offset of the current pixel (in the model image)
          // with regard to the top-left pixel of the current "set of pixels"
          int delta_i = 3 * (dy * (*width) + dx);

          // Accumulate RGB values
          red   += (*image)[i0+delta_i];
          green += (*image)[i0+delta_i+1];
          blue  += (*image)[i0+delta_i+2];
        }
      }
