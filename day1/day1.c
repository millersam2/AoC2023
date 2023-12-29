#include <stdio.h> 
#include <string.h>

#define BUFF_SIZE 200
#define NUM_VALID_DIGITS 9

typedef struct written_digit {
	char digit[6];
	int len;
} w_digit;

int main() {
	const w_digit digits[NUM_VALID_DIGITS] = {
		{"one", 3}, {"two", 3}, {"three", 5},
		{"four", 4}, {"five", 4}, {"six", 3},
		{"seven", 5}, {"eight", 5}, {"nine", 4}
	};
	int numCharMatches[NUM_VALID_DIGITS] = {0};
	char lineBuffer[BUFF_SIZE] = {'\0'};
	int firstDigit = -1;
	int lastDigit = -1;
	char c;
	int count = 0, i, j, c_value, k, sum = 0;
	w_digit curDigit;

	FILE *fd = fopen("test.txt", "r");

	if (fd == NULL) {
		return -1;
	}

	// read from entire file
	while ((c = fgetc(fd)) != EOF) {
		count = 0;
		// read line by line
		do {
			lineBuffer[count] = c;
			count++;
		} while ((c = fgetc(fd)) != '\n' && c != EOF);

		// insert a terminating null character to not include characters from
		// a previous line
		lineBuffer[count] = '\0';

		printf("lineBuffer = %s\n", lineBuffer);

		// parse line stored in the buffer backwards
		for (i = count - 1; i >= 0; i--) {
			// printf("%c\n", lineBuffer[i]);

			// check for numeric digit characters
			c_value = lineBuffer[i] - 48;
			if (c_value < 10 && c_value > 0) {
				if (lastDigit == -1) {
					firstDigit = c_value;
					lastDigit = c_value;
				} else {
					firstDigit = c_value;
				}
			}
			
			// check for written digits
			for (j = 0; j < NUM_VALID_DIGITS; j++) {
				curDigit = digits[j];
				// check for character match given current matching sequence
				if (lineBuffer[i] == curDigit.digit[curDigit.len - numCharMatches[j] - 1]) {
					numCharMatches[j]++;
					// check for full written digit match
					if (numCharMatches[j] == curDigit.len) {

						// // match found, reset numCharMatches
						// for (k = 0; k < NUM_VALID_DIGITS; k++) {
						// 	numCharMatches[k] = 0;
						// }

						// update first and/or last digit to reflect full match
						if (lastDigit == -1) {
							firstDigit = j + 1;
							lastDigit = j + 1;
							// printf("first digit = %d\n", firstDigit);
							// printf("last digit = %d\n", lastDigit);
						} else {
							firstDigit = j + 1;
						}
						// printf("first digit = %d\n", firstDigit);
						// printf("last digit = %d\n", lastDigit);
					}
				} else { // not a character match given current matching sequence
					numCharMatches[j] = 0;
					// check if the character is a match for a new sequence
					if (lineBuffer[i] == curDigit.digit[curDigit.len - numCharMatches[j] - 1]) {
						numCharMatches[j]++;
					}
				}
			}
		}
		printf("first digit = %d\n", firstDigit);
		printf("last digit = %d\n", lastDigit);
		sum += (firstDigit * 10 + lastDigit);

		// reset first digit and last digit for next line
		firstDigit = -1;
		lastDigit = -1;
	}

	printf("calibration value sum = %d\n", sum);

	fclose(fd);

	return 0;
}
