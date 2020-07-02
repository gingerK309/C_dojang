/*#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#pragma pack(push,1) // 구조체를 1바이트 크기로 정렬
typedef struct _BITMAPFILEHEADER { // Bmp 비트맵 파일 헤더 구조체
	unsigned short bfType; //Bmp 파일 매직 넘버
	unsigned int bfSize; //파일 크기
	unsigned short bfReserved1; // 예약
	unsigned short bfReserved2; // 예약
	unsigned int bfOffBits; // 비트맵 데이터의 시작 위치
}BITMAPFILEHEADER;

typedef struct _BITMAPINFOHEADER { // Bmp 비트맵 정보 헤더 구조체(DIB 헤더)
	unsigned int biSize; // 현재 구조체의 크기
	int biWidth; // 비트맵 이미지의 가로 크기
	int biHeight; // 비트맵 이미지의 세로 크기
	unsigned short biPlanes; // 사용하는 색상판의 수
	unsigned short biBitCount; // 픽셀 하나를 표현하는 비트 수
	unsigned int biCompression; // 압축 방식
	unsigned int biSizeImage; // 비트맵 이미지의 픽셀 데이터 크기
	int biXPelsPerMeter; //그림의 가로 해상도(미터당 픽셀)
	int biYPelsPerMeter; //그림의 세로 해상도(미터당 픽셀)
	unsigned int biClrUsed; // 색상 테이블에서 실제 사용되는 색상 수
	unsigned int biClrImportant; // 비트맵을 표현하기 위해 필요한 색상 인덱스 수
}BITMAPINFOHEADER;

typedef struct _RGBTRIPLE { //24비트 비트맵 이미지의 픽셀 구조체
	unsigned char rgbtBlue; // 파랑
	unsigned char rgbtGreen; // 초록
	unsigned char rgbtRed; // 빨강
}RGBTRIPLE;
#pragma pack(pop)

#define PIXEL_SIZE 3 // 픽셀 한 개의 크기 3바이트(24비트)
#define PIXEL_ALIGN 4 // 픽셀 데이터 가로 한 줄은 4의 배수 크기로 저장됨

int main() {
	FILE* fpBmp; //비트맵 파일 포인터
	BITMAPFILEHEADER fileHeader; //비트맵 파일 헤더 구조체 변수
	BITMAPINFOHEADER infoHeader; //비트맵 정보 헤더 구조체 변수

	unsigned char* image; //픽셀 데이터 포인터
	int size; //픽셀 데이터 크기
	int width, height; //비트맵 이미지 가로, 세로 크기
	int padding;// 픽셀 데이터의 가로 크기가 4의 배수가 아닐 때 남는 공간의 크기

	char ascii[] = { '#','#','@','%','=','+','*',':','-','.',' ' };
	fpBmp = fopen("moon.bmp", "rb"); // 비트맵 파일을 바이너리 모드로 열기
	if (fpBmp == NULL) { 
		printf("파일 열기에 실패하였습니다.\n");
		return 0; } //파일 열기에 실패하면 종료

	if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp) < 1) {
		fclose(fpBmp); //비트맵 파일 헤더 읽기, 실패하면 파일 포인터를 닫고 프로그램 종료
		printf("비트맵 파일 헤더 읽기에 실패하였습니다.\n");
		return 0;
	}

	if (fileHeader.bfType != 'MB') { //매직 넘버가 MB가 맞는지 확인
		fclose(fpBmp); //맞지 않으면 프로그램 종료
		return 0;
	}

	if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp) < 1) {
		fclose(fpBmp); //비트맵 정보 헤더 읽기, 실패하면 프로그램 종료
		printf("비트맵 파일 정보 헤더 읽기에 실패하였습니다.\n");
		return 0;
	}

	if (infoHeader.biBitCount != 24) //24비트 비트맵이 아니면 종료
	{
		fclose(fpBmp);
		printf("24비트 비트맵이 아닙니다.\n");
		return 0;
	}

	size = infoHeader.biSizeImage; //픽셀 데이터의 크기
	width = infoHeader.biWidth; //비트맵 이미지의 가로 크기
	height = infoHeader.biHeight;// 비트맵 이미지의 세로 크기
	padding = (PIXEL_ALIGN - ((width * PIXEL_SIZE) % PIXEL_ALIGN)) % PIXEL_ALIGN;
	//이미지 가로크기 * 세로크기 = 가로 한 줄의 크기를 구함
	// 이 다음 4로 나머지를 구함 , 4에서 나머지를 빼면 남는 공간 구할 수 있음
	// 남는 공간이 0 이라면(4-0=4 가 되므로) 한번 더 4로 나눠서 나머지를 구함

	if (size == 0) { //픽셀 데이터 크기가 0 이라면
		size = (width * PIXEL_SIZE + padding) * height;
		//이미지 가로크기 * 픽셀 크기 + 패딩 = 가로 한줄 크기
		//가로 한줄 크기 * 세로 크기 = 픽셀 데이터의 크기
	}

	image = malloc(size); //픽셀 데이터의 크기만큼 동적 메모리 할당
	fseek(fpBmp, fileHeader.bfOffBits, SEEK_SET); //파일 포인터를 픽셀 데이터의 시작 위치로 이동
	if (fread(image, size, 1, fpBmp) < 1) {
		fclose(fpBmp); //파일에서 픽셀 데이터 크기만큼 읽고 실패하면 종료
		printf("픽셀 데이터 크기만큼 읽는데 실패하였습니다.\n");
		return 0;
	}
	fclose(fpBmp); //비트맵 파일 닫기

	

	for (int y = height - 1; y >= 0; y--) { //픽셀 데이터는 상하가 뒤집혔기 때문에 아래쪽 부터 반복
		//세로 크기만큼 반복
		for (int x = 0; x < width; x++) { //가로 크기만큼 반복
			int index = (x * PIXEL_SIZE) + (y * (width * PIXEL_SIZE)) + (padding * y);
			//일렬로 된 배열에 접근 -> 인덱스 계산 (x*PIXEL_SIZE)는 픽셀의 가로 위치
			// (y*(width*PIXEL_SIZE))는 픽셀이 몇 번째 줄인지 계산
			//(padding*y)은 줄 별로 누적된 남는 공간
			RGBTRIPLE* pixel = (RGBTRIPLE*)&image[index];// 현재 픽셀의 주소를 RGBTRIPLE 포인터로 변환하여 저장

			unsigned char blue = pixel->rgbtBlue;
			unsigned char green = pixel->rgbtGreen;
			unsigned char red = pixel->rgbtRed; //RGBTRIPLE 구조체로 파랑 초록 빨강 값 가져옴

			unsigned char gray = (red + green + blue) / PIXEL_SIZE; //파랑 초록 빨강의 평균을 구해서 흑백 이미지를 얻음
			char c = ascii[gray * sizeof(ascii) / 256];
			//흑백값에 ASCII 문자의 개수를 곱한 후 256으로 나누면 흑백값에 따른 ASCII 문자 인덱스를 얻을 수 있음

			fprintf(stdout, "%c%c",c,c); //콘솔 화면에 문자 출력
		}
		fprintf(stdout, "\n"); //가로 픽셀 저장 끝나면 줄바꿈
	}
	free(image);//픽셀 데이터를 저장한 동적 메모리 할당 해제
}*/