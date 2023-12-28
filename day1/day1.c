#include <stdio.h> 
#include <string.h>

#define BUFF_SIZE 200
//#define NUM_DIGITS 2
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
	int count = 0, i, j;
	w_digit curDigit;

	FILE *fd = fopen("test.txt", "r");

	if (fd == NULL) {
		return -1;
	}

	// read from entire file
	while ((c = fgetc(fd)) != EOF) {
		count = 0;
		// note: ideally would want to check if c == '\n' indicating an empty line, but
		// this case is not represented in the given input

		// read line by line
		do {
			lineBuffer[count] = c;
			count++;
		} while ((c = fgetc(fd)) != '\n' && c != EOF);

		// insert a terminating null character to protect against including characters from
		// a previous line
		lineBuffer[count] = '\0';

		// parse line stored in the buffer backwards

		// check for written digits

		// printf("%s\n", lineBuffer);

		for (i = count - 1; i >= 0; i--) {
			// printf("%c\n", lineBuffer[i]);
			
			// iterate through digits to update numCharMatches
			for (j = 0; j < NUM_VALID_DIGITS; j++) {
				curDigit = digits[j];
				// check for character match
				if (lineBuffer[i] == curDigit.digit[curDigit.len - numCharMatches[j] - 1]) {
					numCharMatches[j]++;
					// check for full written digit match
					if (numCharMatches[j] == curDigit.len) {
						// update first and/or last digit to reflect full match
						if (lastDigit == -1) {
							firstDigit = j + 1;
							lastDigit = j + 1;
							// printf("first digit = %d\n", firstDigit);
							// printf("last digit = %d\n", lastDigit);
						} else {
							firstDigit = j + 1;
						}
						printf("first digit = %d\n", firstDigit);
						printf("last digit = %d\n", lastDigit);
					}
				} else { // not a character match
					numCharMatches[j] = 0;
				}
			}
		}
	}

	fclose(fd);

	return 0;
}
