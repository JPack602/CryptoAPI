#include "header.h"

int DumpBin(char* lpComment, void* lpTarget, size_t ullSize)
{
    if (!lpComment) return 1;
    if (!lpTarget)      return 1;
    if (!ullSize)       return 1;

    unsigned char* lpBuf = (unsigned char*)lpTarget;

    printf("%s\n", lpComment);

    for (size_t i = 0; i < ullSize; i++) {
        printf("0x%02X, ", lpBuf[i]);

        if ((i + 1) % 16 == 0) {
            puts("");
        }
    }

    puts("");
    puts("");

    return 0;
}

void* m_malloc(size_t ullSize)
{
    if (!ullSize) return NULL;

    void* lpRet = NULL;

    lpRet = malloc(ullSize);
    if (lpRet)
        memset(lpRet, 0x00, ullSize);

    return lpRet;
}