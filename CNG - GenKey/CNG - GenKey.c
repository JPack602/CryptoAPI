#include "header.h"

void SafeCloseProv(BCRYPT_ALG_HANDLE* phAlgProc)
{
    if (phAlgProc)
    {
        BCryptCloseAlgorithmProvider(phAlgProc, 0);
        phAlgProc = NULL;
    }

    return;
}

void SafetDestroyKey(BCRYPT_KEY_HANDLE hKey)
{
    if (hKey)
    {
        BCryptDestroyKey(hKey);
        hKey = NULL;
    }

    return;
}

BCRYPT_ALG_HANDLE* OpenAlgorithmProvide(wchar_t *lpProvName)
{
    NTSTATUS  status = 0;
    BCRYPT_ALG_HANDLE* hAlg = NULL;

    hAlg = m_malloc(sizeof(BCRYPT_ALG_HANDLE));
    if (!hAlg)
        return NULL;

    status = BCryptOpenAlgorithmProvider(hAlg, BCRYPT_RSA_ALGORITHM, lpProvName, 0);
    if (NT_SUCCESS(status))
        return hAlg;

    status = BCryptOpenAlgorithmProvider(hAlg, BCRYPT_RSA_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
    if (NT_SUCCESS(status))
        return hAlg;

    return NULL;
}

int main(int argc, char **argv)
{
    BCRYPT_ALG_HANDLE   *hAlg = NULL;
    NTSTATUS                       status;

    // キープロバイダーをオープン
    hAlg = OpenAlgorithmProvide(NULL);
    if (!hAlg)
    {
        printf("OpenAlgorithmProvide Error line %d\n", __LINE__);

        char c = getchar();

        return 1;
    }





    // 暗号化のオプションを設定
    BCRYPT_KEY_HANDLE   hKey = NULL;
    // 暗号化に使用する鍵の長さ
    ULONG  dwLength = RSAKEYLEN;

    // キーペアを作成
    status = BCryptGenerateKeyPair(*hAlg, &hKey, dwLength, 0);
    if (!NT_SUCCESS(status))
    {
        printf("BCryptGenerateKeyPair Error 0x%X line %d\n", status, __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        char c = getchar();

        return 1;
    }





    // キーペアを完成させる
    status = BCryptFinalizeKeyPair(hKey, 0);
    if (!NT_SUCCESS(status))
    {
        printf("BCryptFinalizeKeyPair Error 0x%X line %d\n", status, __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        char c = getchar();

        return 1;
    }




    // 必要なメモリのサイズを受け取る
    DWORD dwBlobSize;

    // 暗号化に使用する鍵
    PBYTE lpPublicKey   = NULL;
    PBYTE lpPrivateKey = NULL;

    // 公開鍵のサイズを取得
    status = BCryptExportKey(hKey, NULL, BCRYPT_RSAPUBLIC_BLOB, NULL, 0, &dwBlobSize, 0);
    if (! NT_SUCCESS(status))
    {
        printf("BCryptExportKey Error 0x%X line %d\n", status, __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        char c = getchar();

        return 1;
    }

    // 公開鍵用メモリ確保
    lpPublicKey = m_malloc(dwBlobSize);
    if (! lpPublicKey)
    {
        printf("m_malloc Error line %d\n", __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        char c = getchar();

        return 1;
    }

    // 公開鍵を取得
    status = BCryptExportKey(hKey, NULL, BCRYPT_RSAPUBLIC_BLOB, lpPublicKey, dwBlobSize, &dwBlobSize, 0);
    if (!NT_SUCCESS(status))
    {
        printf("BCryptExportKey Error 0x%X line %d\n", status, __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        SAFE_FREE(lpPublicKey);

        char c = getchar();

        return 1;
    }

    // 取得した鍵を出力
    DumpBin("lpPublicKey", lpPublicKey, dwBlobSize);





    // 秘密鍵のサイズを取得
    status = BCryptExportKey(hKey, NULL, BCRYPT_PRIVATE_KEY_BLOB, NULL, 0, &dwBlobSize, 0);
    if (! NT_SUCCESS(status))
    {
        printf("BCryptExportKey Error 0x%X line %d\n", status, __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        SAFE_FREE(lpPublicKey);

        char c = getchar();

        return 1;
    }

    // 秘密鍵用メモリ確保
    lpPrivateKey = m_malloc(dwBlobSize);
    if (! lpPrivateKey)
    {
        printf("m_malloc Error line %d\n", __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        SAFE_FREE(lpPublicKey);

        char c = getchar();

        return 1;
    }

    // 秘密鍵を取得
    status = BCryptExportKey(hKey, NULL, BCRYPT_PRIVATE_KEY_BLOB, lpPrivateKey, dwBlobSize, &dwBlobSize, 0);
    if (!NT_SUCCESS(status))
    {
        printf("BCryptExportKey Error 0x%X line %d\n", status, __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        SAFE_FREE(lpPublicKey);
        SAFE_FREE(lpPrivateKey);

        char c = getchar();

        return 1;
    }

    // 取得した鍵を出力
    DumpBin("lpPrivateKey", lpPrivateKey, dwBlobSize);





    // アルゴリズムプロバイダーを閉じる
    SafeCloseProv(hAlg);
    // キーハンドルを破棄
    SafetDestroyKey(hKey);

    // メモリ解放
    SAFE_FREE(lpPublicKey);
    SAFE_FREE(lpPrivateKey);

    char c = getchar();

    return 0;
}