__kernel void encrypt(__global char* t,					// text
                         int numb,						// encryption number
                         __global char* encOutput) {	//output

	// sets i = 0
	unsigned int i = get_global_id(0);

	// text ASCII code is between 65 and 90
	// add num to the letter's ASCII code
	if((t[i] + numb) >= 65 && (t[i] + numb) <= 90) {
		encOutput[i] = t[i] + numb;
	}

	// if it is bigger than 90
	// add num and then subtract 26
	// so that letter falls back in range
	else if ((t[i] + numb) > 90) {
		encOutput[i] = (t[i]+numb) - 26;
    }
    
	// else it is smaller
	// add num and then add 26
	else if ((t[i] + numb) < 65) {
		encOutput[i] = (t[i]+numb) + 26;
    }
}

// similar to the above but moves in the negative direction
// as seen in the first if statement
// it is subtracted rather than added to
__kernel void decrypt(__global char* t,
                         int numb,
                         __global char* decOutput) {

	unsigned int i = get_global_id(0);
    
	if((t[i] - numb) >= 65 && (t[i] - numb) <= 90) {
		decOutput[i] = t[i] - numb;
	}
	
	else if ((t[i] - numb) > 90) {
		decOutput[i] = (t[i]-numb) -  26;
    }

    else if ((t[i] - numb)  < 65) {
		decOutput[i] = (t[i]-numb) +  26;
    }
}
