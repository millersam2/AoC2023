#include <stdio.h> 
#include <string.h>

#define BUFF_SIZE 100
#define NUM_DIGITS 2
#define NUM_VALID_DIGITS 9

int main() {
	int tmp_buffer[NUM_DIGITS], i, sum = 0, strIndex = 0;
	char c, tempStr[BUFF_SIZE] = {'\0'};
	char *digits[NUM_VALID_DIGITS] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	FILE *fd = fopen("test.txt", "r");

	if (fd == NULL) {
		return 1;
	}

	// initialize the buffer
	for (i = 0; i < NUM_DIGITS; i++) {
		tmp_buffer[i] = -1;
	} 

	while ((c = fgetc(fd)) != EOF) {
		if (c >= 97 && c <= 122) { // regular lowercase character
			tempStr[strIndex] = c;
			strIndex++;
			tempStr[strIndex] = '\0';
			for (i = 0; i < NUM_VALID_DIGITS; i++) {
				if (strcmp(tempStr, digits[i]) == 0) {
					if (tmp_buffer[0] == -1) {
						tmp_buffer[0] = i + 1;
					}
					tmp_buffer[1] = i + 1;
					strIndex = 0;
					break;
				}
			}
		} else {
			// was not a regular lowercase character, thus reset the index into tempStr
			strIndex = 0;
			// if character read is a digit
			if (c >= 48 && c <= 57) {
				if (tmp_buffer[0] == -1) {
					tmp_buffer[0] = (int) c - 48;
				}
				tmp_buffer[1] = (int) c - 48;
			} else if (c == '\n') {
				sum += (10 * tmp_buffer[0] + tmp_buffer[1]);
				tmp_buffer[0] = -1;
				tmp_buffer[1] = -1;
			}

		}
	}

	// add last line to sum
	sum += (10 * tmp_buffer[0] + tmp_buffer[1]);

	printf("answer: %d\n", sum);

	fclose(fd);

	return 0;
}
