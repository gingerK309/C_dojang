/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable:4996)

int getFileSize(FILE* fp)
{
    int size;
    int currPos = ftell(fp);

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    fseek(fp, currPos, SEEK_SET);

    return size;
}

char* getData(int offset, int size, int* count, FILE* fp)
{
    
    char* buffer = malloc(size + 1);
    memset(buffer, 0, size + 1);
    fread(buffer, size, 1, fp);
    if (feof(fp) == 1) return 0;
    fseek(fp, offset, SEEK_SET);
    *count = fread(buffer,sizeof(char),size,fp);
     
    return buffer;
}

int main()
{
    char* buffer;
    int size;
    int count;

    FILE* fp = fopen("words.txt", "r");

    size = getFileSize(fp);
    buffer = getData(0, size, &count, fp);

    printf("%s\n", buffer);
    printf("%d", count);

    fclose(fp);

    free(buffer);

    return 0;
}*/