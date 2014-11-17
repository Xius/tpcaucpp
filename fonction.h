typedef struct
{
        int width, height;
        unsigned char* image;
}screen;

//============================================================================
//                           Function declarations
//============================================================================
// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void ppm_write_to_file(const char* filename, screen* pixel) ;

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(const char* filename, screen* pixel);

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate(screen* pixel);

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink(screen* pixel, int factor);

