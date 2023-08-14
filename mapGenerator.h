#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int width, height;
} dimensions;

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} rgb_value;


dimensions getDimensions(char *ppm_to_read_from);

void create_collision_ppm(char *ppm_file, char *textfile);

void fill_byte_array(unsigned char *byte_values, char *dimension_data,
                     char *image_data);

void fill_pixel_array(rgb_value *pixels, unsigned char *byte_values,
                      int rgb_bytes_total);

void create_collision_map(rgb_value* pixels, char* collision_map_file, dimensions dims);
