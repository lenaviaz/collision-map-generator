#include "mapGenerator.h"

dimensions getDimensions(char *ppm_to_read_from)
{


  dimensions dims;

  dims.width = 0;
  dims.height = 0;

  FILE *ppm_data = fopen(ppm_to_read_from, "r");

  int max_size = 200;

  char line[max_size]; // max size
  int line_count = 0;

  while (fgets(line, max_size, ppm_data)) {

    if (line[0] == 'P') {
      line_count += 1;
      continue;
    }

    if (line_count == 1) {

      printf("printing line");
      printf(line);

      if (sscanf(line, "%d %d", &dims.width, &dims.height) == 2) {

        line_count += 1;
        continue;
      }

      else {
        // Parsing failed; the buffer does not contain two valid integers
        // Handle the error here
        printf("Error: Unable to parse width and height from the buffer.\n");
        line_count += 1;
      }

      return dims;
    }
  }
  // end of while loop

  return dims;

}


void create_collision_ppm(char *ppm_file, char *textfile) {
  dimensions dims;

  dims.width = 0;
  dims.height = 0;

  FILE *sample_data_1 = fopen(ppm_file, "r");
  FILE *image_data = fopen(textfile, "w");

  int max_size = 200;

  char line[max_size]; // max size
  int line_count = 0;

  while (fgets(line, max_size, sample_data_1)) {

    if (line[0] == 'P') {
      line_count += 1;
      continue;
    }

    if (line[0] == '#') {
      // don't copy comments
      continue;
    }

    if (line_count == 1) {

      printf("printing line");
      printf(line);

      if (sscanf(line, "%d %d", &dims.width, &dims.height) == 2) {

        line_count += 1;
        continue;
      }

      else {
        // Parsing failed; the buffer does not contain two valid integers
        // Handle the error here
        printf("Error: Unable to parse width and height from the buffer.\n");
        line_count += 1;
      }
    }

    /* if(line[4] == '\0' && line[1] == ' ') */
    /*   { */
    /*     //set matrix width and height */
    /*     width = line[0] - '0'; */
    /*     height = line[2] - '0'; */
    /*     continue; */
    /*   } */

    if (line[4] == '\0' && line[1] != ' ') {
      // skip final line before image data
      continue;
    }

    fputs(line, image_data);
  }

  // fputc('a', image_data);
  fclose(image_data);
  fclose(sample_data_1);
}

void fill_byte_array(unsigned char *byte_values, char *dimension_data,
                     char *image_data) {

  dimensions thing;
  thing = getDimensions(dimension_data);

  int width = thing.width;
  int height = thing.height;

  FILE *sample_data = fopen(image_data, "rb");
  int c;
  int buffer_size = width * height * 3 * 3;
  int index = 0;

  int value = 0;
  int digit_count = 0;
  // copy to text without any spaces

  while ((c = fgetc(sample_data)) != EOF) {

    if ((c >= 48) && (c <= 57)) // check if its a digit value
    {
      value = (value * 10) + (c - '0');
      digit_count += 1;
    } else if ((c == ' ') || (c == '\t') || (c == '\n')) {
      if (digit_count > 0) {
        byte_values[index] = (unsigned char)value;
        index += 1;
        value = 0;
        digit_count = 0;
      }
    }
    // this only case is the end of the file?
    byte_values[index] = (unsigned char)value;
    // index += 1;
    // value = 0;
    //  digit_count = 0;

  } // end of while

  int rbg_bytes_total = (width * height) * 3;

  for (int i = 0; i < rbg_bytes_total; i++) {
    unsigned char a = byte_values[i];
    int b = (int)a;
    printf("\n%i", b);
  }
  printf("\n\n\n");

  fclose(sample_data);
}


void fill_pixel_array(rgb_value *pixels, unsigned char *byte_values,
                      int rgb_bytes_total) {
  int increment = 0;
  for (int i = 0; i < rgb_bytes_total; i += 3) {
    rgb_value one_pixel;
    one_pixel.r = byte_values[i];
    one_pixel.g = byte_values[i + 1];
    one_pixel.b = byte_values[i + 2];

    pixels[increment] = one_pixel;
    increment += 1;

    printf("\n\n%i\n\n", increment);
  }
} 

void create_collision_map(rgb_value* pixels, char* collision_map_file, dimensions dims)
{

  FILE *image_data = fopen(collision_map_file, "w");

  int array_position = 0;

  for(int i = 0; i < dims.height; i++)
    {

      for(int j = 0; j < dims.width; j++)
	{

	  rgb_value one_pixel = pixels[array_position];

	  //white
	  if((one_pixel.r == 255) && (one_pixel.g == 255) && (one_pixel.b == 255))
	    {

	      fputc('O', image_data);

	      if((j != (dims.width - 1)))
		{
		  fputc(' ', image_data);
		}
	    }

	    if((one_pixel.r == 0) && (one_pixel.g == 0) && (one_pixel.b == 0))
	    {

	      fputc('X', image_data);

	      if((j != (dims.width - 1)))
		{
		  fputc(' ', image_data);
		}
	    }

	    if(j == (dims.width - 1))
	      {
		fputc('\n', image_data);
		
	      }

	    array_position = array_position + 1;

	}
    }

  fclose(image_data);
}
