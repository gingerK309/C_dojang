/*#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)

int main() {
	int m, n;
	scanf("%d %d", &m, &n);
	char** matrix = malloc(sizeof(char*) * m);
	for (int row = 0; row < m; row++) {
		matrix[row] = malloc(sizeof(char) * (n + 1));
	}
	for (int i = 0; i < m; i++) {
		scanf("%s", matrix[i]);
	}
    for (int y = 0; y < m; y++) {
		for (int x = 0; x < n; x++) {
			if (matrix[y][x] == '*') {
				printf("*");
				continue;
			}
			else matrix[y][x] = '0';
			for (int row = y - 1; row <= y + 1; row++) {
				for (int col = x - 1; col <= x + 1; col++) {
					if (row < 0 || row >= m || col < 0 || col >= n) 
						continue;
				   else if (matrix[row][col] == '*') matrix[y][x]++;
					}
				}
			printf("%c", matrix[y][x]);
        }
		printf("\n");
	}
	for (int i = 0; i < m; i++) {
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}*/

	