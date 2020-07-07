/*#pragma warning(disable:4996)
#include <stdio.h>     
#include <stdlib.h>    
#include <stdbool.h>   
#include <string.h>   


//��ū ���� ������
typedef enum _TOKEN_TYPE {
	TOKEN_STRING,//���ڿ� ��ū
	TOKEN_NUMBER,//���� ��ū
}TOKEN_TYPE;

typedef struct _TOKEN {
	TOKEN_TYPE type; //��ū ����
	union { //�� ���� �� �� ������ �����ϹǷ� ����ü
		char* string; //���ڿ� ������
		double number;// �Ǽ��� ����
	};
	bool isArray;//���� ��ū�� �迭���� ǥ��
}TOKEN;

#define TOKEN_COUNT 100 //��ū �ִ� ����
//JSON ����ü
typedef struct _JSON {
	TOKEN tokens[TOKEN_COUNT];//��ū �迭
}JSON;

char *readFile(char *filename, int *readSize){
//������ �о ������ ��ȯ�ϴ� �Լ�
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL) return NULL;

	int size;
	char* buffer;

	fseek(fp, 0, SEEK_END);//���� ũ�� ���ϱ�
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buffer = malloc(size + 1);//���� ũ�� + NULL ������ŭ �޸𸮸� �Ҵ��ϰ� 0���� �ʱ�ȭ
	memset(buffer, 0, size + 1);

	if (fread(buffer, size, 1, fp) < 1) { // ���� ���� �б�
		*readSize = 0;
		free(buffer);
		fclose(fp);
		return NULL;
	}
	*readSize = size; //���� ũ�⸦ �Ѱ���
	fclose(fp); //���� ������ �ݱ�
	return buffer;
}

void parseJSON(char* doc, int size, JSON* json) { //JSON �Ľ� �Լ�
	int tokenIndex = 0;//��ū �ε���
	int pos = 0;//���� �˻� ��ġ�� �����ϴ� ����

	if (doc[pos] != '{') // ������ ������ {���� �˻�
		return;
	pos++;//���� ���ڷ�
	while (pos < size) {
		//���� ũ�⸸ŭ �ݺ�
		switch (doc[pos]) { //������ ������ ���� �б�
		case'"':  //���ڰ� "�̸� ���ڿ�
		{
			char* begin = doc + pos + 1;//���ڿ��� ���� ��ġ�� ����. �� ���� "�� �����ϱ� ���� +1
			char* end = strchr(begin, '"');
			if (end == NULL)//"�� ������ �߸��� ����
				break;//�ݺ��� Ż�� 
			int stringLength = end - begin;//���ڿ��� ���� �� ��ġ-���� ��ġ

			json->tokens[tokenIndex].type = TOKEN_STRING; //��ū �迭�� ���ڿ� ����. ��ū Ÿ���� ���ڿ�
			json->tokens[tokenIndex].string = malloc(stringLength + 1);//���ڿ� ����+ NULL ������ŭ �޸� �Ҵ�
			memset(json->tokens[tokenIndex].string, 0, stringLength + 1);//�Ҵ� �޸� 0���� �ʱ�ȭ
			memcpy(json->tokens[tokenIndex].string, begin, stringLength);//�������� ���ڿ��� ��ū�� �����ϰ� ���ڿ� ���� ��ġ���� ���ڿ� ���̸�ŭ ����
			tokenIndex++;//��ū �ε��� ����
			pos = pos + stringLength + 1;//���� ��ġ+���ڿ� ����+ "
		}
		break;
		case '[':
			pos++;//���� ���ڷ�
			while (doc[pos] != ']') {//�ݴ� ]�� ������ �ݺ� ����
				if (doc[pos] == '"') //���ڰ� "�̸� ���ڿ� ���� ��ġ�� ����
				{
					char* begin = doc + pos + 1;
					char* end = strchr(begin, '"'); //���ڿ��� �� ��ġ�� ����
					if (end == NULL) break; //"�� ������ �߸��� ���� 

					int stringLength = end - begin; //���ڿ��� ���� ����= �� ��ġ -���� ��ġ
					json->tokens[tokenIndex].type = TOKEN_STRING;//��ū �迭�� ���ڿ� ����
					json->tokens[tokenIndex].string = malloc(stringLength + 1); //���ڿ��� ����+NULL ��ŭ �޸� �Ҵ�
					json->tokens[tokenIndex].isArray = true; //���� ���ڿ��� �迭�� ���
					memset(json->tokens[tokenIndex].string, 0, stringLength + 1);//�޸� 0���� �ʱ�ȭ
					memcpy(json->tokens[tokenIndex].string, begin, stringLength);//���ڿ� ���� ��ġ���� ���ڿ� ���̸�ŭ ����
					tokenIndex++;//��ū �ε��� ����
					pos = pos + stringLength + 1;//���� ��ġ+ ���ڿ� ���� + "
				}
				pos++;//���� ���ڷ�
			}
			break;
		case '0':case '1': case '2': case '3': case '4': case'5': case'6':
		case '7': case '8': case '9': case '-': {//���ڰ� ������ ��
			char* begin = doc + pos;//���ڿ��� ���� ��ġ�� ����
			char* end;
			char* buffer;

			end = strchr(doc + pos, ','); //���ڿ��� �� ��ġ�� ����
			if (end == NULL) {
				end = strchr(doc + pos, '}'); // } �� ������ ���ڿ��� ����
				if (end == NULL) break; // } �� ������ �߸��� ����
				}
			int stringLength = end - begin; //���ڿ��� ���� ���� 
			buffer = malloc(stringLength + 1); //���ڿ� ���� + NULL ��ŭ �޸� �Ҵ�
			memset(buffer, 0, stringLength + 1); //�Ҵ��� �޸� 0���� �ʱ�ȭ
			memcpy(buffer, begin, stringLength);//�������� ���ڿ��� ���ۿ� �����ϰ� ���ڿ� ���̸�ŭ ����
			json->tokens[tokenIndex].type = TOKEN_NUMBER;//��ū ������ ����
			json->tokens[tokenIndex].number = atof(buffer);//���ڿ��� ���ڷ� ��ȯ
			free(buffer);//���� ����
			tokenIndex++;//��ū �ε��� ����
			pos = pos + stringLength + 1;//���� ��ġ + ���ڿ� ���� + , �Ǵ� } 
			}
				break;
		}
		pos++;//���� ���ڷ� 
	}
}
void freeJSON(JSON* json) {
	//JSON ���� �Լ�
	for (int i = 0; i < TOKEN_COUNT; i++) {//��ū ���� ��ŭ �ݺ�
		if (json->tokens[i].type == TOKEN_STRING) //��ū ������ ���ڿ��̸�
			free(json->tokens[i].string); //���� �޸� ����
	}
}
char* getString(JSON* json, char* key) {//Ű�� �ش��ϴ� ���ڿ��� �������� �Լ�
	for(int i=0;i<TOKEN_COUNT;i++){ //��ū ������ŭ �ݺ�
		if (json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key) == 0) {//��ū�� ������ ���ڿ��̰� ��ū�� ���ڿ��� Ű�� ��ġ�ϸ�
			if (json->tokens[i + 1].type == TOKEN_STRING) //�ٷ� ���� ��ū(i+1) �� ���ڿ��̸�
				return json->tokens[i + 1].string; //�ٷ� �ڿ� �ִ� ��ū�� ���ڿ� ��ȯ
		}	
	}
	return NULL; //Ű�� ã�� �������� NULL ��ȯ
}

char* getArrayString(JSON* json, char* key, int index) {//Ű�� �ش��ϴ� �迭 �� �ε����� �����Ͽ� ���ڿ��� �������� �Լ�
	for (int i = 0; i < TOKEN_COUNT; i++) {//��ū ������ŭ �ݺ�
		if (json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key) == 0) {
			//��ū ������ ���ڿ��̰� ��ū�� ���ڿ��� Ű�� ��ġ�ϸ�
			if (json->tokens[i + 1 + index].type == TOKEN_STRING && json->tokens[i + 1 + index].isArray == true)
				//�ε����� ������ ��ū(�ٷ� ���� ��ū�� �迭�� ��Ұ� ����)�� ���ڿ��̸鼭 �迭�� ��
				return json->tokens[i + 1 + index].string;//�ش� ��ū�� ���ڿ� ��ȯ
		}
	}
	return NULL;//Ű�� ã�� �������� NULL ��ȯ
}

int getArrayCount(JSON* json, char* key) {
	//Ű�� �ش��ϴ� �迭�� ��� ������ ���ϴ� �Լ�
	for (int i = 0; i < TOKEN_COUNT; i++) {
		//��ū ������ŭ �ݺ�
		if (json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key) == 0) {//��ū ������ ���ڿ��̰� Ű�� ��ġ�ϸ�
			int j = 0; 
			while (json->tokens[i + 1 + j].isArray == true) 
				j++; //�ٷ� ���� ��ū(i+1) ���� isArray�� true�� ��ū�� ������ ���� ��ȯ
				return j;
			
 		}
	}
	return 0;//Ű�� ã�� �������� 0�� ��ȯ
}

double getNumber(JSON* json, char* key) {
	//Ű�� �ش��ϴ� ���ڸ� �������� �Լ�
	for (int i = 0; i < TOKEN_COUNT; i++) //��ū ������ŭ �ݺ� 
	{
		if (json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key) == 0) {
			//��ū ������ �����̸鼭 ��ū�� ���ڿ��� Ű�� ��ġ�ϰ�
			if (json->tokens[i + 1].type == TOKEN_NUMBER) return json->tokens[i + 1].number;//�ٷ� ���� ��ū (i+1)�� �����̸� �ٷ� �ڿ� �ִ� ��ū ���� ��ȯ
		}
	}
	return 0.0; //Ű�� ã�� �������� 0.0 ��ȯ
}


int main() {
	int size;//���� ũ��
	char* doc = readFile("example.json", &size);// ���Ͽ��� JSON ���� ����, ���� ũ�⸦ ����
	if (doc == NULL) return -1;
	JSON json = { 0, }; //JSON ����ü ���� ���� �� �ʱ�ȭ
	parseJSON(doc, size, &json);//JSON ���� �Ľ�
	printf("Title: %s\n", getString(&json,"Title"));
	printf("Year: %d\n", (int)getNumber(&json,"Year"));
	printf("Runtime: %d\n",(int)getNumber(&json,"Runtime"));
	printf("Genre: %s\n", getString(&json,"Genre"));
	printf("Director: %s\n",getString(&json,"Director"));
	printf("Actors:\n");
	int actors = getArrayCount(&json, "Actors");
	for (int i = 0; i < actors; i++) printf("  %s\n",getArrayString(&json,"Actors",i));//�ε����� �����Ͽ� ���ڿ� ������
	printf("imdbRating: %f\n",getNumber(&json,"imdbRating"));
	freeJSON(&json); //json�� �Ҵ�� ���� �޸� ����
	free(doc);//���� ���� �޸� ����
	return 0;
}*/