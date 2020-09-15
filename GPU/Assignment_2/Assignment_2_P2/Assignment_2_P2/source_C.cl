__constant char crypt[26] = {'G', 'X', 'S', 'Q', 'F', 'A', 'R', 'O', 'W', 'B', 'L', 'M', 'T', 'H', 'C', 'V', 'P', 'N', 'Z', 'U', 'I', 'E', 'Y', 'D', 'K', 'J'};
__constant char letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

__kernel void encrypt(__global char* t,
                         __global char* encOutput) {

	unsigned int i = get_global_id(0);

    // encrypts the text
	int j = 0;
	// checks if letter is found
	// if not keep searching array for the same letter
	// once found replace with crypt letter
	if (t[i] == letters[j]) {
		encOutput[i] = crypt[j];
	}
	
	else {
		j++;
	}
}
    
__kernel void decrypt(__global char* t,
                         __global char* decOutput) {
	
	unsigned int i = get_global_id(0);

    // decrypts the text
    int j = 0;
	// checks if letter is found
	// if not keep searching array for the same letter
	// once found replace with decrypt letter
	if (t[i] == crypt[j]) {
		decOutput[i] = letters[j];
	}
	
	else {
		j++;
	}
}    