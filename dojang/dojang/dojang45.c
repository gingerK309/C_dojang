/*#include<stdio.h>
#include<string.h>
#pragma warning (disable:4996)

int main() {
	char s1[1001];
	
    scanf("%[^\n]s", s1);

	char* ptr = strtok(s1, " .,");
	
    int count = 0;
	
	while (ptr != NULL) {
	 if (ptr != NULL) 
		 if(strcmp(ptr, "the") == 0)
		count++; 
	 ptr = strtok(NULL, " .,");
     }
	printf("%d", count);
	return 0;
		
}*/