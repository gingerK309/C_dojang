#pragma warning(disable:4996)
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#pragma pack(push, 1)

typedef struct _ARCHIVE_HEADER {
    uint16_t magic;
    uint16_t version;
} ARCHIVE_HEADER, * PARCHIVE_HEADER;

typedef struct _FILE_DESC {
    char     name[256];
    uint32_t size;
    uint32_t dataOffset;
} FILE_DESC, * PFILE_DESC;

#pragma pack(pop)

typedef struct _FILE_NODE {
    struct _FILE_NODE* next;
    FILE_DESC desc;
}FILE_NODE,*PFILE_NODE;

typedef struct _ARCHIVE{
    ARCHIVE_HEADER header;
    FILE* fp;
    FILE_NODE fileList;
}ARCHIVE, *PARCHIVE;

#define ARCHIVE_NAME "archive.bin"

uint32_t getFileSize(FILE* fp) {
    uint32_t size;
    uint32_t currPos = ftell(fp);
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, currPos, SEEK_SET);
    return size;
}

void list(PARCHIVE archive) {
    PFILE_NODE curr = archive->fileList.next;
    while (curr != NULL) {
        printf("%s\n", curr->desc.name);
        curr = curr->next;
    }
}

int main() {
    PARCHIVE archive = malloc(sizeof(ARCHIVE));
    memset(archive, 0, sizeof(ARCHIVE));
    PFILE_NODE curr;
    FILE* fp = fopen(ARCHIVE_NAME, "rb");
  
        if (fread(&archive->header, sizeof(ARCHIVE_HEADER), 1, fp) < 1) {
            printf("아카이브 헤더 읽기 실패\n");
            fclose(fp);
            return -1;
        }
    
    if (archive->header.magic != 'XR') {
        printf("아카이브 파일이 아닙니다.\n");
        fclose(fp);
        return -1;
    }
    if (archive->header.version != 2) {
        printf("버전이 맞지 않습니다.\n");
        fclose(fp);
        return -1;
    }
    archive->fp = fp;

    int ret = 0;
    uint32_t size = getFileSize(fp);
    uint32_t currPos = ftell(fp);

    while (size > currPos) {
        PFILE_NODE node = malloc(sizeof(FILE_NODE));
        memset(node, 0, sizeof(FILE_NODE));
        if (fread(&node->desc, sizeof(FILE_DESC), 1, fp) < 1) {
            printf("아카이브 파일 읽기 실패\n");
            free(node);
            ret = -1;
            goto FINALIZE;
        }
        node->next = archive->fileList.next;
        archive->fileList.next = node;
        currPos = ftell(fp) + node->desc.size;
        fseek(fp, currPos, SEEK_SET);
    }
    list(archive);
FINALIZE:
    curr = archive->fileList.next;
    while (curr != NULL) {
        PFILE_NODE next = curr->next;
        free(curr);
        curr = next;
    }
    fclose(archive->fp);
    free(archive);
    return ret;
}