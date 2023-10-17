static unsigned char* str(unsigned char c) {
	static unsigned char buffer[4];
	unsigned char i = 0;

	if (c == 0) buffer[i++] = '0';
	else while (c != 0) {
		signed int digit = c % 10;
		buffer[i++] = '0' + digit;
		c /= 10;
	}

	buffer[i] = '\0';

	unsigned char start = 0;
	unsigned char end = i - 1;

	while (start < end) {
		unsigned char temp = buffer[start];
		buffer[start] = buffer[end];
		buffer[end] = temp;
		start++;
		end--;
	}

	return buffer;
}
