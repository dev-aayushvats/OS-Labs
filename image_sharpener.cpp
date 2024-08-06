#include <iostream>
#include "libppm.h"
#include <cstdint>

using namespace std;

struct image_t* S1_smoothen(struct image_t *input_image)
{
	//cout << input_image->width << input_image->height << " " <<  input_image->image_pixels << endl;
	int width = input_image->width;
	int height = input_image->height;
	
	// memory allocation
	struct image_t* smoother = new struct image_t;
	smoother->height = height;
	smoother->width = width;
	smoother->image_pixels = new uint8_t**[height];
		for(int i = 0; i < height; i++)
		{
			smoother->image_pixels[i] = new uint8_t*[width];
			for(int j = 0; j < width; j++)
				smoother->image_pixels[i][j] = new uint8_t[3];
		}
	
	for(int i = 1; i < height-1; i++)
		{
			for(int j = 1; j < width-1; j++)
			{
				for(int k = 0; k < 3; k++)
				{
					//image->image_pixels[i][j][k] = val;
					//cout << unsigned( input_image->image_pixels[i][j][k]) << endl;
					//break;
					// edge cases
					if(i == 0 && j == 0) { // i-1 and j - 1 doesnt exist
						smoother->image_pixels[i][j][k] =  ( input_image->image_pixels[i][j][k] / 9+  input_image->image_pixels[i][j+1][k] / 9 +  input_image->image_pixels[i+1][j][k] / 9 +  input_image->image_pixels[i+1][j+1][k] / 9);
						
					}
					else if(i == height - 1 && j == 0) { // i+1 and j-1 does not exist
						smoother->image_pixels[i][j][k] = ( input_image->image_pixels[i-1][j][k] / 9 +  input_image->image_pixels[i-1][j+1][k] / 9+  input_image->image_pixels[i][j][k] / 9+  input_image->image_pixels[i][j+1][k] / 9);
					}
					
					else if(i == 0 && j == width - 1) { // i-1 and j+1 does not exist
						smoother->image_pixels[i][j][k] = ( input_image->image_pixels[i][j-1][k] / 9 +  input_image->image_pixels[i][j][k] / 9+   input_image->image_pixels[i+1][j-1][k] / 9 +  input_image->image_pixels[i+1][j][k] / 9);
					}
					else if(i == height - 1 && j == width - 1) { // i+1 and j+1 does not exist
						smoother->image_pixels[i][j][k] = ( input_image->image_pixels[i-1][j-1][k] / 9 +  input_image->image_pixels[i-1][j][k] / 9 +  input_image->image_pixels[i][j-1][k] / 9 +  input_image->image_pixels[i][j][k] / 9);
					}
					else if (i == 0) {  // i - 1 does not exist
							smoother->image_pixels[i][j][k] = ( input_image->image_pixels[i][j-1][k] / 9 +  input_image->image_pixels[i][j][k] / 9+  input_image->image_pixels[i][j+1][k] / 9+  input_image->image_pixels[i+1][j-1][k] / 9+  input_image->image_pixels[i+1][j][k] / 9+  input_image->image_pixels[i+1][j+1][k] / 9);
						}
					
					else if(j == 0) { // j -1 does not exist
						smoother->image_pixels[i][j][k] = ( input_image->image_pixels[i-1][j][k] / 9+  input_image->image_pixels[i-1][j+1][k]  / 9+  input_image->image_pixels[i][j][k] / 9+  input_image->image_pixels[i][j+1][k] / 9+   input_image->image_pixels[i+1][j][k] / 9+  input_image->image_pixels[i+1][j+1][k]/ 9);
					}
					
					else if(i == height - 1) { // i+1 does not exist
						smoother->image_pixels[i][j][k] = ( input_image->image_pixels[i-1][j-1][k] / 9+  input_image->image_pixels[i-1][j][k] / 9+  input_image->image_pixels[i-1][j+1][k] / 9+  input_image->image_pixels[i][j-1][k] / 9+  input_image->image_pixels[i][j][k] / 9+  input_image->image_pixels[i][j+1][k]/ 9);
					}		
					else if(j == width - 1) { // j + 1 does not exist
						smoother->image_pixels[i][j][k] = ( input_image->image_pixels[i-1][j-1][k] / 9+  input_image->image_pixels[i-1][j][k] / 9+  input_image->image_pixels[i][j-1][k] / 9+  input_image->image_pixels[i][j][k]/ 9 +   input_image->image_pixels[i+1][j-1][k] / 9+  input_image->image_pixels[i+1][j][k] / 9);
					}	
					else {
					smoother->image_pixels[i][j][k] = ( input_image->image_pixels[i-1][j-1][k] / 9 +  input_image->image_pixels[i-1][j][k] / 9 +  input_image->image_pixels[i-1][j+1][k]/9 +  input_image->image_pixels[i][j-1][k]/9 +  input_image->image_pixels[i][j][k] / 9 +  input_image->image_pixels[i][j+1][k] / 9 +  input_image->image_pixels[i+1][j-1][k] / 9 +  input_image->image_pixels[i+1][j][k] / 9 +  input_image->image_pixels[i+1][j+1][k] / 9);
					cout << unsigned(smoother->image_pixels[i][j][k]) << endl;
					}
				}
			}
		}
		
		for(int i = 0; i < height; ++i) {
		break;
			for(int j = 0; j < width; ++j) {
				cout << unsigned(smoother->image_pixels[i][j][0]) << "" ;
			}
			cout << endl;
		}
	return smoother;
}

struct image_t* S2_find_details(struct image_t *input_image, struct image_t *smoothened_image)
{
	// TODO
	return 0;
}

struct image_t* S3_sharpen(struct image_t *input_image, struct image_t *details_image)
{
	// TODO
	return input_image; //TODO remove this line when adding your code
}

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		cout << "usage: ./a.out <path-to-original-image> <path-to-transformed-image>\n\n";
		exit(0);
	}
	
	struct image_t *input_image = read_ppm_file(argv[1]);
	
	struct image_t *smoothened_image = S1_smoothen(input_image);
	
	struct image_t *details_image = S2_find_details(input_image, smoothened_image);
	
	struct image_t *sharpened_image = S3_sharpen(input_image, details_image);
	
	write_ppm_file(argv[2], smoothened_image);
	
	return 0;
}
