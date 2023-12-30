#include <stdio.h> 
#include <string.h>

#define BUFF_SIZE 250
#define NUM_VALID_DIGITS 9

int readLine(char *buffer, FILE *fd);
int parseFirstDigit(const char *line, int *firstDigit, int len);
int parseLastDigit(const char *line, int *lastDigit, int len);
int parseWritFirstDigit(const char *line, int *firstDigit, int len);
int writFirstDigitHelper(const char *line, int len, const char *w_digit);

const char *w_digits[NUM_VALID_DIGITS] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main() {
	char buffer[BUFF_SIZE];
	char *fname = "input.txt";
	int firstDigit, lastDigit, len, index, sum = 0, calibrationVal;
	FILE *fd;

	fd = fopen(fname, "r");
	if (!fd) {
		return -1;
	}

	while ((len = readLine(buffer, fd)) != 0) {
		index = parseFirstDigit(buffer, &firstDigit, len);
		if (index == -1) {
			return -1;
		}
		index = parseLastDigit(buffer, &lastDigit, len);
		if (index == -1) {
			return -1;
		}
		// parseWritFirstDigit(buffer, &firstDigit, len);

		calibrationVal = (10 * firstDigit) + lastDigit;
		sum += calibrationVal;
	}

	printf("sum of calibration values = %d\n", sum);

	return 0;
}

int readLine(char *buffer, FILE *fd) {
	char c;
	int len = 0;

	while ((c = fgetc(fd)) != '\n' && c != EOF) {
		buffer[len] = c;
		len++;
	}
	buffer[len] = '\0';
	return len;
}

int parseFirstDigit(const char *line, int *firstDigit, int len) {
	int i = 0;

	while (i < len) {
		if (line[i] >= '0' && line[i] <= '9') {
			*firstDigit = line[i] - '0';
			return i;
		}
		i++;
	}
	return -1;
}

int parseLastDigit(const char *line, int *lastDigit, int len) {
	int i = len - 1;
	
	while (i >= 0) {
		if (line[i] >= '0' && line[i] <= '9') {
			*lastDigit = line[i] - '0';
			return i;
		}
		i--;
	}
	return -1;
}

int parseWritFirstDigit(const char *line, int *firstDigit, int len) {
	int i, firstIndex = BUFF_SIZE, curIndex;

	for (i = 0; i < NUM_VALID_DIGITS; i++) {
		curIndex = writFirstDigitHelper(line, len, w_digits[i]);
		if (curIndex != -1 && curIndex < firstIndex) {
			firstIndex = curIndex;
			*firstDigit = i + 1;
		}
	}
	// check that atleast one match was found
	if (firstIndex != BUFF_SIZE) {
		return firstIndex;
	}
	return -1;
}

int writFirstDigitHelper(const char *line, int len, const char *w_digit) {
	int i = 0, j;
	char *temp;
	
	while (i < len) {
		if (line[i] == *w_digit) {
			j = i;
			temp = w_digit;

			while (1) {
				// written digit found
				if (*temp == '\0') {
					// *firstDigit = 999;
					return i;
				}
				// check for non-success termination condition
				if (j == len || line[j] != *temp) {
					break;
				}
				j++;
				temp++;
			}
		}
		i++;
	}
	return -1;
}
