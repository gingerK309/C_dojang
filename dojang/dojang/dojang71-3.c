/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable:4996)

int main() {
	FILE* fp = fopen("words.txt", "r");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	rewind(fp);

	char* buffer = malloc(size + 1);
	memset(buffer, 0, size + 1);

	for (int i = size - 1; i >= 0; i--) {
		fseek(fp, i, SEEK_SET);
		fread(buffer, 1, 1, fp);
		fwrite(buffer, 1, 1, stdout);
	}

	free(buffer);
 return 0;
}*/