/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable:4996)

int main() {
	FILE* fp;
	fp = fopen("words.txt", "r");
	int size;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
   char* buffer=malloc(size+1);
   memset(buffer, 0, size + 1);
   fseek(fp,7,SEEK_SET);
   fread(buffer,4, 1, fp); 
   printf("%s", buffer);
   memset(buffer, 0, size+1);
   fseek(fp, -6, SEEK_END);
   fread(buffer, 2, 1, fp);
   printf("%s", buffer);
   free(buffer);
	return 0;
}*/