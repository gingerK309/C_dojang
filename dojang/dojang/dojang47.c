/*#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#pragma warning (disable:4996)
int main() {

	char s[31];
	bool isPalindrome = false;
	scanf("%[^\n]s", s);
	int start=0;
	int end=strlen(s)-1;
	int mid = (start + end) / 2;
	while(s!=NULL){
		if (s[start] == s[end])
			isPalindrome = true;
		start++;
		end--;
		if (s[mid]) break;
	}
	if (isPalindrome == true) printf("ȸ���Դϴ�!\n");
	else printf("ȸ���� �ƴմϴ�.\n");
	//printf("%d", isPalindrome);

	return 0;
}*/