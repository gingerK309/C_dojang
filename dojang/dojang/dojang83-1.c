/*#include<stdio.h>
#pragma warning(disable:4996)

int main() {
	//JSON 문서에 저장할 데이터
	char* title = "Inception";
	int year = 2010;
	int runtime = 148;
	char* genre = "Sci-Fi";
	char* director = "Christopher Nolan";
	char actors[5][30] = {
		 "Leonardo DiCaprio",
		 "Joseph Gordon-Levitt",
		 "Ellen Page",
		 "Tom Hardy",
		 "Ken Watanabe"
	};
	double imdbRating = 8.8;
	FILE* fp = fopen("inception.json", "w"); //쓰기 모드로 파일 열기
	fprintf(fp, "{\n");
	fprintf(fp, "	\"Title\": \"%s\",\n", title);
	fprintf(fp, "	\"Year\": %d,\n", year);
	fprintf(fp, "	\"Runtime\": %d,\n", runtime);
	fprintf(fp, "	\"Genre\": \"%s\",\n", genre);
	fprintf(fp, "	\"Director\": \"%s\",\n", director);
	fprintf(fp, "	\"Actors\": [\n");
	fprintf(fp, "	\"%s\",\n", actors[0]);
	fprintf(fp, "	\"%s\",\n", actors[1]);
	fprintf(fp, "	\"%s\",\n", actors[2]);
	fprintf(fp, "	\"%s\",\n", actors[3]);
	fprintf(fp, "	\"%s\"\n", actors[4]);
	fprintf(fp, "	],\n");
	fprintf(fp, "	\"imdbRating\": %.1f\n", imdbRating);
	fprintf(fp, "}\n");
	fclose(fp);
	return 0;
}*/