#include "mapGenerator.h"

int main()
{


  dimensions image_dimension = getDimensions("background-collision-map.ppm");
  int buffer_size = image_dimension.width * image_dimension.height * 3 * 3;

  create_collision_ppm("background-collision-map.ppm","background-collision-map-rgb-data.txt");

  printf("dimensions: %i %i \n", image_dimension.width, image_dimension.height);

   unsigned char* byte_values = (unsigned char *)malloc(buffer_size * sizeof(unsigned char));

   rgb_value* pixels = malloc((image_dimension.width * image_dimension.height) * sizeof(rgb_value));

   fill_byte_array(byte_values, "background-collision-map.ppm", "background-collision-map-rgb-data.txt");

   int rgb_bytes_total = (image_dimension.width * image_dimension.height) * 3;


   fill_pixel_array(pixels, byte_values, rgb_bytes_total);

   create_collision_map(pixels, "collision_map1.txt", image_dimension);

   

   free(byte_values);
   free(pixels);

  return 0;
}
