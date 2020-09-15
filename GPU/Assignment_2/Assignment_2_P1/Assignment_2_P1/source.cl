__kernel void A2_P1(__global int4* array1,		// index 0
                    __global int* array2,       // index 1
                    __global int* output)       // index 2
{
    int8 v, v1, v2, results;

    v = (int8)(array1[0], array1[1]);
    v1 = vload8(0, array2);
    v2 = vload8(1, array2);
    
    bool check = false;
    
    for (int j = 0; j < 8; j++) {
        if (v[j] > 5) {
            check = true;
        }
    }
    
    if (check == true) {
        for (int x = 0; x < 8; x++) {
            if (v[x] == 5) {
                results[x] = 0;
            }
            else {
                results[x] = select (v2[x], v1[x], v[x] > 5);
            }
        }
    }
    else {
        for (int x = 0; x < 4; x++) {
            results[x] = v1[x];
            results[x+4] = v2[x];
        }
    }
    
    vstore8(v, 0, output);
    vstore8(v1, 1, output);
    vstore8(v2, 2, output);
    vstore8(results, 3, output);
}
