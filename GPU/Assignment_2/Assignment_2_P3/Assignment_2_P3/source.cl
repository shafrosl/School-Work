__constant int code = 96098253;

bool checkPasscode(int i) {
    if (i == code) {
        return true;
    }
    else {
        return false;
    }
}

__kernel void passCrack(__global int* a, __global int* b, __global int* c) {
		// checks whether each global id is equal to code
        if (checkPasscode(get_global_id(0))) {
			//if true print number and store info
            printf("Passcode found: %d\n", get_global_id(0));
            a[0] = get_global_id(0);
            b[0] = get_group_id(0);
            c[0] = get_local_id(0);
        }
}
