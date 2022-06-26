#include "header.h"

NTERROR ntError[] = {
    STATUS_SUCCESS,                    "STATUS_SUCCESS",
    STATUS_BUFFER_TOO_SMALL, "STATUS_BUFFER_TOO_SMALL",
    STATUS_INVALID_HANDLE,        "STATUS_INVALID_HANDLE",
    STATUS_INVALID_PARAMETER, "STATUS_INVALID_PARAMETER",
    STATUS_NOT_SUPPORTED,       "STATUS_NOT_SUPPORTED",

    -1L,                                             "UnKnown",
};

BYTE lpPublicKey[] = {
    0x52, 0x53, 0x41, 0x31, 0x00, 0x08, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0xC1, 0xC2, 0x83, 0x2B, 0xCD,
    0x06, 0x48, 0x3A, 0x83, 0x29, 0x56, 0xE9, 0xC0, 0x84, 0xF6, 0xAD, 0xF2, 0x94, 0x0D, 0x63, 0xD7,
    0x32, 0xD2, 0x57, 0x23, 0x4B, 0xD2, 0xBF, 0x9E, 0xC5, 0x4C, 0x87, 0x29, 0x68, 0x7C, 0x59, 0x5A,
    0xFA, 0x58, 0x19, 0x6A, 0x79, 0xC7, 0xF0, 0x93, 0xDB, 0x66, 0xFF, 0x1B, 0x61, 0x95, 0x3F, 0xBB,
    0x11, 0xFB, 0x02, 0x21, 0x7A, 0xCE, 0xFB, 0x91, 0x36, 0xF0, 0x5C, 0x71, 0x47, 0xD0, 0xC0, 0x79,
    0x9F, 0x79, 0xF0, 0xAB, 0x4D, 0xB6, 0x47, 0x27, 0x89, 0x80, 0x06, 0x38, 0xD2, 0xD8, 0x67, 0xF4,
    0x68, 0x84, 0x70, 0xA3, 0xCE, 0xB2, 0x2C, 0x3F, 0x86, 0xFD, 0x9C, 0x27, 0x08, 0xEF, 0x7A, 0x2D,
    0x08, 0xDF, 0x79, 0x01, 0x52, 0xD3, 0xB4, 0x63, 0xE2, 0x9B, 0xAA, 0x4C, 0x32, 0xE7, 0xB2, 0xD1,
    0xDB, 0x9F, 0x4E, 0x4D, 0xBA, 0x74, 0xB2, 0xFC, 0x70, 0xC0, 0xDB, 0x84, 0x2B, 0xE6, 0x76, 0x69,
    0x7B, 0x44, 0xFD, 0x8A, 0xC4, 0x9A, 0x36, 0x15, 0xA2, 0x94, 0xAE, 0x94, 0x73, 0x8B, 0x1C, 0x0E,
    0xBC, 0xCC, 0xD7, 0xCF, 0x57, 0x38, 0xA1, 0x00, 0x69, 0xA6, 0x57, 0xFF, 0x2B, 0xEB, 0x99, 0xAC,
    0xA9, 0x6E, 0xF8, 0x32, 0x07, 0x34, 0x72, 0x6E, 0x2C, 0x2D, 0xE4, 0x34, 0x78, 0x49, 0x7B, 0xB3,
    0x3C, 0x8D, 0x32, 0x51, 0x7B, 0x0D, 0x53, 0xF9, 0x7D, 0x09, 0x61, 0x79, 0x92, 0x4E, 0x86, 0xCC,
    0xBB, 0x12, 0x3A, 0xE3, 0xFB, 0xF6, 0x9C, 0xD9, 0x96, 0xF3, 0x6C, 0x57, 0x30, 0xD2, 0xA4, 0xBF,
    0x02, 0x19, 0x8C, 0xB7, 0x14, 0x47, 0x04, 0xF1, 0x6A, 0x7F, 0x1A, 0x7E, 0xD6, 0xD2, 0x2C, 0x0A,
    0xA3, 0xDF, 0x52, 0xD9, 0x66, 0xBF, 0x12, 0x51, 0xDC, 0xD0, 0x3C, 0x6E, 0x5F, 0x5F, 0xD0, 0x84,
    0xA6, 0x6C, 0x12, 0x1A, 0x81, 0x5E, 0x14, 0x24, 0x8F, 0x05, 0x49,
};

BOOL OpenAlgorithmProvide(BCRYPT_ALG_HANDLE *hAlg, wchar_t *lpProvName)
{
    NTSTATUS  status = 0;

    status = BCryptOpenAlgorithmProvider(hAlg, BCRYPT_RSA_ALGORITHM, lpProvName, 0);
    if (NT_SUCCESS(status))
        return TRUE;

    status = BCryptOpenAlgorithmProvider(hAlg, BCRYPT_RSA_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
    if (NT_SUCCESS(status))
        return TRUE;

    *hAlg = NULL;

    return FALSE;
}

void SafeCloseAlgorithmProvider(BCRYPT_ALG_HANDLE hAlg)
{
    if (hAlg)
    {
        BCryptCloseAlgorithmProvider(hAlg, NULL);
        hAlg = NULL;
    }

    return;
}

void SafeDestroyKey(BCRYPT_KEY_HANDLE hKey)
{
    if (hKey)
    {
        BCryptDestroyKey(hKey);
        hKey = NULL;
    }

    return;
}

void GetBCryptError(char *lpFuncName, NTSTATUS  ntErrorCode, DWORD dwLine)
{
    printf("%s ", lpFuncName);

    printf("Error -> ");

    for (int i = 0; i < COUNTOF(ntError); i++)
    {
        if (ntError[i].dwErrorCode == ntErrorCode)
        {
            printf("%s (0x%X) ", ntError[i].lpErrorMessage, ntErrorCode);

            break;
        }

        if (ntError[i].dwErrorCode == -1L)
        {
            printf("%s ", ntError[i].lpErrorMessage);

            break;
        }
    }

    printf("line %lu.\n", dwLine);

    return;
}

int main(int argc, char** argv)
{
    NTSTATUS  status = 0;
    BCRYPT_ALG_HANDLE hAlg            = NULL;
    BCRYPT_KEY_HANDLE hKeyHandle = NULL;

    //  戻り値
    DWORD result                      = 0;
    // 公開鍵のサイズ                    
    DWORD dwPublicKeyLen       = 0;
    // キーオブジェクト      
    UCHAR *lpKeyObject            = 0;
    // キーオブジェクトのサイズ
    DWORD dwKeyObjectLength = BCRYPT_SUPPORTED_PAD_OAEP;

    // 暗号化されたデータを入れるバッファー
    UCHAR* lpEncrypted             = NULL;

    // 暗号化プロバイダーを取得
    OpenAlgorithmProvide(&hAlg, NULL);
    if (!hAlg)
    {
        GetBCryptError("BCryptOpenAlgorithmProvider", status, __LINE__);

        goto BCryptError;
    }



    // キーのインポート
    status = BCryptImportKeyPair(
        hAlg,
        NULL,
        BCRYPT_RSAPUBLIC_BLOB, 
        &hKeyHandle, 
        lpPublicKey,
        sizeof(lpPublicKey),
        0);

    if (!NT_SUCCESS(status))
    {
        GetBCryptError("BCryptImportKeyPair", status, __LINE__);

        goto BCryptError;
    }



    // 元データ
    char* plain = "sample text";
    // データのサイズ
    ULONG cbInput = strlen(plain);
    // 暗号化したデータを書込むバッファーのサイズ
    DWORD dwOutput = 0;

    // 暗号化するデータのバイト数を取得
    status = BCryptEncrypt(hKeyHandle, plain, cbInput, NULL, NULL, 0, NULL, NULL, &dwOutput, BCRYPT_PAD_NONE);
    if (! NT_SUCCESS(status))
    {
        GetBCryptError("BCryptEncrypt", status, __LINE__);

        goto BCryptError;
    }

    // 暗号化したデータを書込むバッファーの確保
    lpEncrypted = m_malloc(dwOutput);
    if (! lpEncrypted)
    {
        printf("m_malloc Error 0x%X line %d\n", status, __LINE__);

        goto BCryptError;
    }


    // lpEncryptedに出力されたバイト数
    DWORD dwResult  = 0;
    // 暗号化するタイプのフラグ
    // BCRYPT_PAD_NONEの場合はブロックサイズの倍数である必要がある
    DWORD dwFlags   = BCRYPT_PAD_PKCS1;

    status = BCryptEncrypt(
        hKeyHandle, 
        plain, 
        cbInput, 
        NULL, 
        NULL, 
        0, 
        lpEncrypted, 
        dwOutput, 
        &dwResult,
        BCRYPT_PAD_PKCS1);

    if (!NT_SUCCESS(status))
    {
        GetBCryptError("BCryptEncrypt", status, __LINE__);

        goto BCryptError;
    }

    // 
    DumpBin("plain text", plain, strlen(plain));

    DumpBin("lpEncrypted", lpEncrypted, dwResult);

    char d = getchar();

    return 0;

BCryptError:
    SafeCloseAlgorithmProvider(hAlg);
    SafeDestroyKey(hKeyHandle);

    SAFE_FREE(lpKeyObject);
    SAFE_FREE(lpEncrypted);

    char c = getchar();

    return -1;
}