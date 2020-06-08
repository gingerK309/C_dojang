#include<stdio.h>

#pragma warning (disable:4996)
int main() {
	
	int num;
	scanf("%d", &num);
	
	for (int i = 0; i < num; i++) {
		for (int j =num; j > 0; j--) {
			if (i+1<j) printf(" ");
			else printf("*");
			if (2 * j <2*i+1) printf("*");
		}printf("\n");
	}
	
	for (int i = 0; i < num; i++) {
		for (int j = num - 1; j > i; j--) printf(" ");
		
		for (int j = 0; j < 2 * i + 1; j++) printf("*");
		
		printf("\n");
	}
	
	
	//코딩 도장 해설
	
	for (int i = 0; i < num; i++) {
		for (int j = num - 1; j >= 0; j--) {
			if (j > i) printf(" ");
			else printf("*");
		}
		for (int j = 0; j < num - 1; j++) {
			if (j < i) printf("*");
		}
		printf("\n");
	}


return 0;

}
	
