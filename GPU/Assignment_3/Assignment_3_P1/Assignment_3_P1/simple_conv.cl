__constant sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | 
      CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_NEAREST; 

// 3x3 Blurring filter
__constant float BlurringFilterA[9] = {	0.077847, 0.123317, 0.077847,
										0.123317, 0.195346, 0.123317,
										0.077847, 0.123317, 0.077847};

// 5x5 Blurring filter
__constant float BlurringFilterB[25] = {    0.003765, 0.015019, 0.023792, 0.015019, 0.003765,
                                           0.015019, 0.059912, 0.094907, 0.059912, 0.015019,
                                           0.023792, 0.094907, 0.150342, 0.094907, 0.023792,
                                           0.015019, 0.059912, 0.094907, 0.059912, 0.015019,
                                           0.003765, 0.015019, 0.023792, 0.015019, 0.003765};

// 7x7 Blurring filter
__constant float BlurringFilterC[49] = {    0.000036, 0.000363, 0.001446, 0.002291, 0.001446, 0.000363, 0.000036,
                                           0.000363, 0.003676, 0.014662, 0.023226, 0.014662, 0.003676, 0.000363,
                                           0.001446, 0.014662, 0.058488, 0.092651, 0.058488, 0.014662, 0.001446,
                                           0.002291, 0.023226, 0.092651, 0.146768, 0.092651, 0.023226, 0.002291,
                                           0.001446, 0.014662, 0.058488, 0.092651, 0.058488, 0.014662, 0.001446,
                                           0.000363, 0.003676, 0.014662, 0.023226, 0.014662, 0.003676, 0.000363,
                                           0.000036, 0.000363, 0.001446, 0.002291, 0.001446, 0.000363, 0.000036};

// 3x3 Double Pass Blurring filter
__constant float DoublePassBlurringFilterA[3] = {0.27901, 0.44198, 0.27901};

// 5x5 Double Pass Blurring filter
__constant float DoublePassBlurringFilterB[5] = {0.06136, 0.24477, 0.38774, 0.24477, 0.06136};

// 7x7 Double Pass Blurring filter
__constant float DoublePassBlurringFilterC[7] = {0.00598, 0.060626, 0.241843, 0.383103, 0.241843, 0.060626, 0.00598};

__kernel void part_a(read_only image2d_t src_image,
					write_only image2d_t dst_image, int choice) {

   /* Get work-item’s row and column position */
   int column = get_global_id(0); 
   int row = get_global_id(1);

   /* Accumulated pixel value */
   float4 sum = (float4)(0.0);

   /* Filter's current index */
   int filter_index =  0;

   int2 coord;
   float4 pixel;

    if (choice == 3) {
    /* Iterate over the rows */
        for(int i = -1; i <= 1; i++) {
            coord.y =  row + i;
            
            /* Iterate over the columns */
            for(int j = -1; j <= 1; j++) {
                coord.x = column + j;

                /* Read value pixel from the image */
                pixel = read_imagef(src_image, sampler, coord);
                      
                /* Acculumate weighted sum */
                sum.xyz += pixel.xyz * BlurringFilterA[filter_index++];
          }
        }
    }
            
          else if (choice == 5) {
              /* Iterate over the rows */
              for(int i = -2; i <= 2; i++) {
                  coord.y =  row + i;
                  
                  /* Iterate over the columns */
                  for(int j = -2; j <= 2; j++) {
                      coord.x = column + j;
                      
                      /* Read value pixel from the image */
                      pixel = read_imagef(src_image, sampler, coord);
                      
                      /* Acculumate weighted sum */
                      sum.xyz += pixel.xyz * BlurringFilterB[filter_index++];
          }
              }
          }
                  
          else if (choice == 7) {
              /* Iterate over the rows */
              for(int i = -3; i <= 3; i++) {
                  coord.y =  row + i;
                  
                  /* Iterate over the columns */
                  for(int j = -3; j <= 3; j++) {
                      coord.x = column + j;
                      
                      /* Read value pixel from the image */
                      pixel = read_imagef(src_image, sampler, coord);
                      
                      /* Acculumate weighted sum */
                      sum.xyz += pixel.xyz * BlurringFilterC[filter_index++];
          }
      }
   }

   /* Write new pixel value to output */
   coord = (int2)(column, row); 
   write_imagef(dst_image, coord, sum);
}

__kernel void part_b(read_only image2d_t src_image,
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
                coord.y =  row + i;
                
                /* Read value pixel from the image */
                pixel = read_imagef(src_image, sampler, coord);
                
                /* Acculumate weighted sum */
                sum.xyz += pixel.xyz * DoublePassBlurringFilterA[filter_index++];
            }

            if (pass == 2) {
                coord.x =  column + i;
                
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
                coord.y =  row + i;
                
                /* Read value pixel from the image */
                pixel = read_imagef(src_image, sampler, coord);
                
                /* Acculumate weighted sum */
                sum.xyz += pixel.xyz * DoublePassBlurringFilterB[filter_index++];
            }

            if (pass == 2) {
                coord.x =  column + i;
                
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
                coord.y =  row + i;
                
                /* Read value pixel from the image */
                pixel = read_imagef(src_image, sampler, coord);
                
                /* Acculumate weighted sum */
                sum.xyz += pixel.xyz * DoublePassBlurringFilterC[filter_index++];
            }

            if (pass == 2) {
                coord.x =  column + i;
                
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
