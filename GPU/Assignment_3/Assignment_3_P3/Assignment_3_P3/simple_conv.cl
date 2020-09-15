__constant sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE |
CLK_ADDRESS_CLAMP_TO_EDGE |
CLK_FILTER_LINEAR;

// 3x3 Double Pass Blurring filter
__constant float DoublePassBlurringFilterA[3] = {0.27901, 0.44198, 0.27901};

// 5x5 Double Pass Blurring filter
__constant float DoublePassBlurringFilterB[5] = {0.06136, 0.24477, 0.38774, 0.24477, 0.06136};

// 7x7 Double Pass Blurring filter
__constant float DoublePassBlurringFilterC[7] = {0.00598, 0.060626, 0.241843, 0.383103, 0.241843, 0.060626, 0.00598};

__kernel void black(__read_only image2d_t input, __write_only image2d_t output, float bench) {
    int2 gid = (int2)(get_global_id(0), get_global_id(1));
    float4 pixel = read_imagef(input, sampler, gid);
    
    float total = 0.299f * (pixel.x * 255) + 0.587f * (pixel.y * 255) + 0.114f * (pixel.z * 255);
    if (total < bench) {
        pixel.xyz = 0.0f;
    }
    write_imagef(output, gid, pixel);
}

__kernel void passing(read_only image2d_t src_image,
                          write_only image2d_t dst_image, int choice, int pass) {
    
    /* Get work-item’s row and column position */
    int column = get_global_id(0);
    int row = get_global_id(1);
    
    /* Accumulated pixel value */
    float4 sum = (float4)(0.0);
    
    /* Filter's current index */
    int filter_index =  0;
    
    int2 coord = (int2)(column, row);
    float4 pixel;
    
    if (choice == 3) {
	/* Iterate over the rows */
        for(int i = -1; i <= 1; i++) {
            if (pass == 1) {
                coord.x =  column + i;
                
                /* Read value pixel from the image */
                pixel = read_imagef(src_image, sampler, coord);
                
                /* Acculumate weighted sum */
                sum.xyz += pixel.xyz * DoublePassBlurringFilterA[filter_index++];
            }

            if (pass == 2) {
                coord.y =  row + i;
                
                /* Read value pixel from the image */
                pixel = read_imagef(src_image, sampler, coord);
                
                /* Acculumate weighted sum */
                sum.xyz += pixel.xyz * DoublePassBlurringFilterA[filter_index++];
            }
        }
    }
    
    if (choice == 5) {
	/* Iterate over the rows */
        for(int i = -2; i <= 2; i++) {
            if (pass == 1) {
				coord.x =  column + i;
                
                /* Read value pixel from the image */
                pixel = read_imagef(src_image, sampler, coord);
                
                /* Acculumate weighted sum */
                sum.xyz += pixel.xyz * DoublePassBlurringFilterB[filter_index++];
            }

            if (pass == 2) {
                coord.y =  row + i;

                /* Read value pixel from the image */
                pixel = read_imagef(src_image, sampler, coord);
                
                /* Acculumate weighted sum */
                sum.xyz += pixel.xyz * DoublePassBlurringFilterB[filter_index++];
            }
        }
    }
    
    if (choice == 7) {
	/* Iterate over the rows */
        for(int i = -5; i <= 5; i++) {
            if (pass == 1) {
				coord.x =  column + i;
                
                /* Read value pixel from the image */
                pixel = read_imagef(src_image, sampler, coord);
                
                /* Acculumate weighted sum */
                sum.xyz += pixel.xyz * DoublePassBlurringFilterC[filter_index++];
            }

            if (pass == 2) {
                coord.y =  row + i;
                
                /* Read value pixel from the image */
                pixel = read_imagef(src_image, sampler, coord);
                
                /* Acculumate weighted sum */
                sum.xyz += pixel.xyz * DoublePassBlurringFilterC[filter_index++];
            }
        }
    }
    
    /* Write new pixel value to output */
    coord = (int2)(column, row);
    write_imagef(dst_image, coord, sum);
}

__kernel void merge(__read_only image2d_t input, __read_only image2d_t input2, __write_only image2d_t output) {
    int2 gid = (int2)(get_global_id(0), get_global_id(1));
    float4 pixel = read_imagef(input, sampler, gid);
    float4 pixel2 = read_imagef(input2, sampler, gid);
	float4 pp = pixel + pixel2;

    write_imagef(output, gid, pp);
}
