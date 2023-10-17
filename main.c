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

void _start() {
	signed int file;

	asm volatile("syscall" : "=a"(file) : "a"(2), "D"("/proc/self/cmdline"), "S"(0), "d"(0));
	if (file < 0) {
		asm volatile("syscall" :: "a"(3), "D"(file));
		return;
	}

	signed int c = 0;
	unsigned char read = 1;

	while (read > 0) {
		asm volatile("syscall" : "=a"(read) : "a"(0), "D"(file), "S"(&c), "d"(1));
		if (read == 0) break;

		if ('\0' == c) asm volatile("syscall" :: "a"(1), "D"(1), "S"(str(' ')), "d"(2));
		else {
			if ('0' + c > 147) asm volatile("syscall" :: "a"(1), "D"(1), "S"(str(c)), "d"(3));
			else asm volatile("syscall" :: "a"(1), "D"(1), "S"(str(c)), "d"(2));
		}

		asm volatile("syscall" :: "a"(1), "D"(1), "S"(" "), "d"(1));
	}

	asm volatile("syscall" :: "a"(60), "D"(0));
}
