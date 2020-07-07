/*#pragma warning(disable:4996)
#include <stdio.h>     
#include <stdlib.h>    
#include <stdbool.h>   
#include <string.h>   


//토큰 종류 열거형
typedef enum _TOKEN_TYPE {
	TOKEN_STRING,//문자열 토큰
	TOKEN_NUMBER,//숫자 토큰
}TOKEN_TYPE;

typedef struct _TOKEN {
	TOKEN_TYPE type; //토큰 종류
	union { //두 종류 중 한 종류만 저장하므로 공용체
		char* string; //문자열 포인터
		double number;// 실수형 숫자
	};
	bool isArray;//현재 토큰이 배열인지 표시
}TOKEN;

#define TOKEN_COUNT 100 //토큰 최대 개수
//JSON 구조체
typedef struct _JSON {
	TOKEN tokens[TOKEN_COUNT];//토큰 배열
}JSON;

char *readFile(char *filename, int *readSize){
//파일을 읽어서 내용을 반환하는 함수
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL) return NULL;

	int size;
	char* buffer;

	fseek(fp, 0, SEEK_END);//파일 크기 구하기
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buffer = malloc(size + 1);//파일 크기 + NULL 공간만큼 메모리를 할당하고 0으로 초기화
	memset(buffer, 0, size + 1);

	if (fread(buffer, size, 1, fp) < 1) { // 파일 내용 읽기
		*readSize = 0;
		free(buffer);
		fclose(fp);
		return NULL;
	}
	*readSize = size; //파일 크기를 넘겨줌
	fclose(fp); //파일 포인터 닫기
	return buffer;
}

void parseJSON(char* doc, int size, JSON* json) { //JSON 파싱 함수
	int tokenIndex = 0;//토큰 인덱스
	int pos = 0;//문자 검색 위치를 저장하는 변수

	if (doc[pos] != '{') // 문서의 시작이 {인지 검사
		return;
	pos++;//다음 문자로
	while (pos < size) {
		//문서 크기만큼 반복
		switch (doc[pos]) { //문자의 종류에 따라서 분기
		case'"':  //문자가 "이면 문자열
		{
			char* begin = doc + pos + 1;//문자열의 시작 위치를 구함. 맨 앞의 "를 제외하기 위해 +1
			char* end = strchr(begin, '"');
			if (end == NULL)//"가 없으면 잘못된 문법
				break;//반복문 탈출 
			int stringLength = end - begin;//문자열의 길이 끝 위치-시작 위치

			json->tokens[tokenIndex].type = TOKEN_STRING; //토큰 배열에 문자열 저장. 토큰 타입은 문자열
			json->tokens[tokenIndex].string = malloc(stringLength + 1);//문자열 길이+ NULL 공간만큼 메모리 할당
			memset(json->tokens[tokenIndex].string, 0, stringLength + 1);//할당 메모리 0으로 초기화
			memcpy(json->tokens[tokenIndex].string, begin, stringLength);//문서에서 문자열을 토큰에 저장하고 문자열 시작 위치에서 문자열 길이만큼 복사
			tokenIndex++;//토큰 인덱스 증가
			pos = pos + stringLength + 1;//현재 위치+문자열 길이+ "
		}
		break;
		case '[':
			pos++;//다음 문자로
			while (doc[pos] != ']') {//닫는 ]가 나오면 반복 종료
				if (doc[pos] == '"') //문자가 "이면 문자열 시작 위치를 구함
				{
					char* begin = doc + pos + 1;
					char* end = strchr(begin, '"'); //문자열의 끝 위치를 구함
					if (end == NULL) break; //"가 없으면 잘못된 문법 

					int stringLength = end - begin; //문자열의 실제 길이= 끝 위치 -시작 위치
					json->tokens[tokenIndex].type = TOKEN_STRING;//토큰 배열에 문자열 저장
					json->tokens[tokenIndex].string = malloc(stringLength + 1); //문자열의 길이+NULL 만큼 메모리 할당
					json->tokens[tokenIndex].isArray = true; //현재 문자열은 배열의 요소
					memset(json->tokens[tokenIndex].string, 0, stringLength + 1);//메모리 0으로 초기화
					memcpy(json->tokens[tokenIndex].string, begin, stringLength);//문자열 시작 위치에서 문자열 길이만큼 복사
					tokenIndex++;//토큰 인덱스 증가
					pos = pos + stringLength + 1;//현재 위치+ 문자열 길이 + "
				}
				pos++;//다음 문자로
			}
			break;
		case '0':case '1': case '2': case '3': case '4': case'5': case'6':
		case '7': case '8': case '9': case '-': {//문자가 숫자일 때
			char* begin = doc + pos;//문자열의 시작 위치를 구함
			char* end;
			char* buffer;

			end = strchr(doc + pos, ','); //문자열의 끝 위치를 구함
			if (end == NULL) {
				end = strchr(doc + pos, '}'); // } 가 나오면 문자열이 끝남
				if (end == NULL) break; // } 가 없으면 잘못된 문법
				}
			int stringLength = end - begin; //문자열의 실제 길이 
			buffer = malloc(stringLength + 1); //문자열 길이 + NULL 만큼 메모리 할당
			memset(buffer, 0, stringLength + 1); //할당한 메모리 0으로 초기화
			memcpy(buffer, begin, stringLength);//문서에서 문자열을 버퍼에 저장하고 문자열 길이만큼 복사
			json->tokens[tokenIndex].type = TOKEN_NUMBER;//토큰 종류는 숫자
			json->tokens[tokenIndex].number = atof(buffer);//문자열을 숫자로 변환
			free(buffer);//버퍼 해제
			tokenIndex++;//토큰 인덱스 증가
			pos = pos + stringLength + 1;//현재 위치 + 문자열 길이 + , 또는 } 
			}
				break;
		}
		pos++;//다음 문자로 
	}
}
void freeJSON(JSON* json) {
	//JSON 해제 함수
	for (int i = 0; i < TOKEN_COUNT; i++) {//토큰 개수 만큼 반복
		if (json->tokens[i].type == TOKEN_STRING) //토큰 종류가 문자열이면
			free(json->tokens[i].string); //동적 메모리 해제
	}
}
char* getString(JSON* json, char* key) {//키에 해당하는 문자열을 가져오는 함수
	for(int i=0;i<TOKEN_COUNT;i++){ //토큰 개수만큼 반복
		if (json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key) == 0) {//토큰의 종류가 문자열이고 토큰의 문자열이 키와 일치하며
			if (json->tokens[i + 1].type == TOKEN_STRING) //바로 뒤의 토큰(i+1) 이 문자열이면
				return json->tokens[i + 1].string; //바로 뒤에 있는 토큰의 문자열 반환
		}	
	}
	return NULL; //키를 찾지 못했으면 NULL 반환
}

char* getArrayString(JSON* json, char* key, int index) {//키에 해당하는 배열 중 인덱스를 지정하여 문자열을 가져오는 함수
	for (int i = 0; i < TOKEN_COUNT; i++) {//토큰 개수만큼 반복
		if (json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key) == 0) {
			//토큰 종류가 문자열이고 토큰의 문자열이 키랑 일치하며
			if (json->tokens[i + 1 + index].type == TOKEN_STRING && json->tokens[i + 1 + index].isArray == true)
				//인덱스를 지정한 토큰(바로 뒤의 토큰에 배열의 요소가 있음)이 문자열이면서 배열일 때
				return json->tokens[i + 1 + index].string;//해당 토큰의 문자열 반환
		}
	}
	return NULL;//키를 찾지 못했으면 NULL 반환
}

int getArrayCount(JSON* json, char* key) {
	//키에 해당하는 배열의 요소 개수를 구하는 함수
	for (int i = 0; i < TOKEN_COUNT; i++) {
		//토큰 개수만큼 반복
		if (json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key) == 0) {//토큰 종류가 문자열이고 키랑 일치하면
			int j = 0; 
			while (json->tokens[i + 1 + j].isArray == true) 
				j++; //바로 뒤의 토큰(i+1) 부터 isArray가 true인 토큰의 개수를 세서 반환
				return j;
			
 		}
	}
	return 0;//키를 찾지 못했으면 0을 반환
}

double getNumber(JSON* json, char* key) {
	//키에 해당하는 숫자를 가져오는 함수
	for (int i = 0; i < TOKEN_COUNT; i++) //토큰 개수만큼 반복 
	{
		if (json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key) == 0) {
			//토큰 종류가 숫자이면서 토큰의 문자열이 키와 일치하고
			if (json->tokens[i + 1].type == TOKEN_NUMBER) return json->tokens[i + 1].number;//바로 뒤의 토큰 (i+1)이 숫자이면 바로 뒤에 있는 토큰 숫자 반환
		}
	}
	return 0.0; //키를 찾지 못했으면 0.0 반환
}


int main() {
	int size;//문서 크기
	char* doc = readFile("example.json", &size);// 파일에서 JSON 문서 읽음, 문서 크기를 구함
	if (doc == NULL) return -1;
	JSON json = { 0, }; //JSON 구조체 변수 선언 및 초기화
	parseJSON(doc, size, &json);//JSON 문서 파싱
	printf("Title: %s\n", getString(&json,"Title"));
	printf("Year: %d\n", (int)getNumber(&json,"Year"));
	printf("Runtime: %d\n",(int)getNumber(&json,"Runtime"));
	printf("Genre: %s\n", getString(&json,"Genre"));
	printf("Director: %s\n",getString(&json,"Director"));
	printf("Actors:\n");
	int actors = getArrayCount(&json, "Actors");
	for (int i = 0; i < actors; i++) printf("  %s\n",getArrayString(&json,"Actors",i));//인덱스를 지정하여 문자열 가져옴
	printf("imdbRating: %f\n",getNumber(&json,"imdbRating"));
	freeJSON(&json); //json에 할당된 동적 메모리 해제
	free(doc);//문서 동적 메모리 해제
	return 0;
}*/