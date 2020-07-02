/*#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#pragma pack(push,1) // ����ü�� 1����Ʈ ũ��� ����
typedef struct _BITMAPFILEHEADER { // Bmp ��Ʈ�� ���� ��� ����ü
	unsigned short bfType; //Bmp ���� ���� �ѹ�
	unsigned int bfSize; //���� ũ��
	unsigned short bfReserved1; // ����
	unsigned short bfReserved2; // ����
	unsigned int bfOffBits; // ��Ʈ�� �������� ���� ��ġ
}BITMAPFILEHEADER;

typedef struct _BITMAPINFOHEADER { // Bmp ��Ʈ�� ���� ��� ����ü(DIB ���)
	unsigned int biSize; // ���� ����ü�� ũ��
	int biWidth; // ��Ʈ�� �̹����� ���� ũ��
	int biHeight; // ��Ʈ�� �̹����� ���� ũ��
	unsigned short biPlanes; // ����ϴ� �������� ��
	unsigned short biBitCount; // �ȼ� �ϳ��� ǥ���ϴ� ��Ʈ ��
	unsigned int biCompression; // ���� ���
	unsigned int biSizeImage; // ��Ʈ�� �̹����� �ȼ� ������ ũ��
	int biXPelsPerMeter; //�׸��� ���� �ػ�(���ʹ� �ȼ�)
	int biYPelsPerMeter; //�׸��� ���� �ػ�(���ʹ� �ȼ�)
	unsigned int biClrUsed; // ���� ���̺��� ���� ���Ǵ� ���� ��
	unsigned int biClrImportant; // ��Ʈ���� ǥ���ϱ� ���� �ʿ��� ���� �ε��� ��
}BITMAPINFOHEADER;

typedef struct _RGBTRIPLE { //24��Ʈ ��Ʈ�� �̹����� �ȼ� ����ü
	unsigned char rgbtBlue; // �Ķ�
	unsigned char rgbtGreen; // �ʷ�
	unsigned char rgbtRed; // ����
}RGBTRIPLE;
#pragma pack(pop)

#define PIXEL_SIZE 3 // �ȼ� �� ���� ũ�� 3����Ʈ(24��Ʈ)
#define PIXEL_ALIGN 4 // �ȼ� ������ ���� �� ���� 4�� ��� ũ��� �����

int main() {
	FILE* fpBmp; //��Ʈ�� ���� ������
	BITMAPFILEHEADER fileHeader; //��Ʈ�� ���� ��� ����ü ����
	BITMAPINFOHEADER infoHeader; //��Ʈ�� ���� ��� ����ü ����

	unsigned char* image; //�ȼ� ������ ������
	int size; //�ȼ� ������ ũ��
	int width, height; //��Ʈ�� �̹��� ����, ���� ũ��
	int padding;// �ȼ� �������� ���� ũ�Ⱑ 4�� ����� �ƴ� �� ���� ������ ũ��

	char ascii[] = { '#','#','@','%','=','+','*',':','-','.',' ' };
	fpBmp = fopen("moon.bmp", "rb"); // ��Ʈ�� ������ ���̳ʸ� ���� ����
	if (fpBmp == NULL) { 
		printf("���� ���⿡ �����Ͽ����ϴ�.\n");
		return 0; } //���� ���⿡ �����ϸ� ����

	if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp) < 1) {
		fclose(fpBmp); //��Ʈ�� ���� ��� �б�, �����ϸ� ���� �����͸� �ݰ� ���α׷� ����
		printf("��Ʈ�� ���� ��� �б⿡ �����Ͽ����ϴ�.\n");
		return 0;
	}

	if (fileHeader.bfType != 'MB') { //���� �ѹ��� MB�� �´��� Ȯ��
		fclose(fpBmp); //���� ������ ���α׷� ����
		return 0;
	}

	if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp) < 1) {
		fclose(fpBmp); //��Ʈ�� ���� ��� �б�, �����ϸ� ���α׷� ����
		printf("��Ʈ�� ���� ���� ��� �б⿡ �����Ͽ����ϴ�.\n");
		return 0;
	}

	if (infoHeader.biBitCount != 24) //24��Ʈ ��Ʈ���� �ƴϸ� ����
	{
		fclose(fpBmp);
		printf("24��Ʈ ��Ʈ���� �ƴմϴ�.\n");
		return 0;
	}

	size = infoHeader.biSizeImage; //�ȼ� �������� ũ��
	width = infoHeader.biWidth; //��Ʈ�� �̹����� ���� ũ��
	height = infoHeader.biHeight;// ��Ʈ�� �̹����� ���� ũ��
	padding = (PIXEL_ALIGN - ((width * PIXEL_SIZE) % PIXEL_ALIGN)) % PIXEL_ALIGN;
	//�̹��� ����ũ�� * ����ũ�� = ���� �� ���� ũ�⸦ ����
	// �� ���� 4�� �������� ���� , 4���� �������� ���� ���� ���� ���� �� ����
	// ���� ������ 0 �̶��(4-0=4 �� �ǹǷ�) �ѹ� �� 4�� ������ �������� ����

	if (size == 0) { //�ȼ� ������ ũ�Ⱑ 0 �̶��
		size = (width * PIXEL_SIZE + padding) * height;
		//�̹��� ����ũ�� * �ȼ� ũ�� + �е� = ���� ���� ũ��
		//���� ���� ũ�� * ���� ũ�� = �ȼ� �������� ũ��
	}

	image = malloc(size); //�ȼ� �������� ũ�⸸ŭ ���� �޸� �Ҵ�
	fseek(fpBmp, fileHeader.bfOffBits, SEEK_SET); //���� �����͸� �ȼ� �������� ���� ��ġ�� �̵�
	if (fread(image, size, 1, fpBmp) < 1) {
		fclose(fpBmp); //���Ͽ��� �ȼ� ������ ũ�⸸ŭ �а� �����ϸ� ����
		printf("�ȼ� ������ ũ�⸸ŭ �дµ� �����Ͽ����ϴ�.\n");
		return 0;
	}
	fclose(fpBmp); //��Ʈ�� ���� �ݱ�

	

	for (int y = height - 1; y >= 0; y--) { //�ȼ� �����ʹ� ���ϰ� �������� ������ �Ʒ��� ���� �ݺ�
		//���� ũ�⸸ŭ �ݺ�
		for (int x = 0; x < width; x++) { //���� ũ�⸸ŭ �ݺ�
			int index = (x * PIXEL_SIZE) + (y * (width * PIXEL_SIZE)) + (padding * y);
			//�Ϸķ� �� �迭�� ���� -> �ε��� ��� (x*PIXEL_SIZE)�� �ȼ��� ���� ��ġ
			// (y*(width*PIXEL_SIZE))�� �ȼ��� �� ��° ������ ���
			//(padding*y)�� �� ���� ������ ���� ����
			RGBTRIPLE* pixel = (RGBTRIPLE*)&image[index];// ���� �ȼ��� �ּҸ� RGBTRIPLE �����ͷ� ��ȯ�Ͽ� ����

			unsigned char blue = pixel->rgbtBlue;
			unsigned char green = pixel->rgbtGreen;
			unsigned char red = pixel->rgbtRed; //RGBTRIPLE ����ü�� �Ķ� �ʷ� ���� �� ������

			unsigned char gray = (red + green + blue) / PIXEL_SIZE; //�Ķ� �ʷ� ������ ����� ���ؼ� ��� �̹����� ����
			char c = ascii[gray * sizeof(ascii) / 256];
			//��鰪�� ASCII ������ ������ ���� �� 256���� ������ ��鰪�� ���� ASCII ���� �ε����� ���� �� ����

			fprintf(stdout, "%c%c",c,c); //�ܼ� ȭ�鿡 ���� ���
		}
		fprintf(stdout, "\n"); //���� �ȼ� ���� ������ �ٹٲ�
	}
	free(image);//�ȼ� �����͸� ������ ���� �޸� �Ҵ� ����
}*/