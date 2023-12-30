#include <stdio.h> 
#include <string.h>

#define BUFF_SIZE 250
#define NUM_VALID_DIGITS 9

int readLine(char *buffer, FILE *fd);
int parseFirstDigit(const char *line, int *firstDigit, int len);
int parseLastDigit(const char *line, int *lastDigit, int len);
int parseWritFirstDigit(const char *line, int *firstDigit, int len);
int writFirstDigitHelper(const char *line, int len, const char *w_digit);
int parseWritLastDigit(const char *line, int *lastDigit, int len);
int writLastDigitHelper(const char *line, int len, const char *w_digit, int w_len);

const char *w_digits[NUM_VALID_DIGITS] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main() {
	char buffer[BUFF_SIZE];
	char *fname = "input.txt";
	int firstDigit, lastDigit, len, firstIndex, lastIndex, sum = 0, calibrationVal;
	int w_firstDigit, w_lastDigit, w_firstIndex, w_lastIndex;
	FILE *fd;

	fd = fopen(fname, "r");
	if (!fd) {
		return -1;
	}

	while ((len = readLine(buffer, fd)) != 0) {
		firstIndex = parseFirstDigit(buffer, &firstDigit, len);
		lastIndex = parseLastDigit(buffer, &lastDigit, len);

		w_firstIndex = parseWritFirstDigit(buffer, &w_firstDigit, len);
		// printf("parsed first written digit = %d\n", w_firstDigit);
		w_lastIndex = parseWritLastDigit(buffer, &w_lastDigit, len);
		// printf("parsed last written digit = %d\n", w_lastDigit);

		if (firstIndex == -1) {
			firstDigit = w_firstDigit;
		}
		if (firstIndex != -1 && w_firstIndex != -1) {
			if (firstIndex > w_firstIndex) {
				firstDigit = w_firstDigit;
			}
		}

		if (lastIndex == -1) {
			lastDigit = w_lastDigit;
		}
		if (lastIndex != -1 && w_lastIndex != -1) {
			if (lastIndex < w_lastIndex) {
				lastDigit = w_lastDigit;
			}
		}
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
	const char *temp;
	
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

int parseWritLastDigit(const char *line, int *lastDigit, int len) {
	int i, firstIndex = -1, curIndex;

	for (i = 0; i < NUM_VALID_DIGITS; i++) {
		curIndex = writLastDigitHelper(line, len, w_digits[i], strlen(w_digits[i]));
		if (curIndex != -1 && curIndex > firstIndex) {
			firstIndex = curIndex;
			*lastDigit = i + 1;
		}
	}
	return firstIndex;
}

int writLastDigitHelper(const char *line, int len, const char *w_digit, int w_len) {
	int i = len - 1, j, temp;

	while (i >= 0) {
		if (line[i] == w_digit[w_len - 1]) {
			j = i;
			temp = w_len - 1;

			while (1) {
				// check for success termination condition (match found)
				if (temp == -1) {
					return i - w_len + 1;
				}
				// check for non-success termination condition
				if (j == -1 || line[j] != w_digit[temp]) {
					break;
				}
				j--;
				temp--;
			}
		}
		i--;
	}
	return -1;
}

