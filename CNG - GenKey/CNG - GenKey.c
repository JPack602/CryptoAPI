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

    // �L�[�v���o�C�_�[���I�[�v��
    hAlg = OpenAlgorithmProvide(NULL);
    if (!hAlg)
    {
        printf("OpenAlgorithmProvide Error line %d\n", __LINE__);

        char c = getchar();

        return 1;
    }





    // �Í����̃I�v�V������ݒ�
    BCRYPT_KEY_HANDLE   hKey = NULL;
    // �Í����Ɏg�p���錮�̒���
    ULONG  dwLength = RSAKEYLEN;

    // �L�[�y�A���쐬
    status = BCryptGenerateKeyPair(*hAlg, &hKey, dwLength, 0);
    if (!NT_SUCCESS(status))
    {
        printf("BCryptGenerateKeyPair Error 0x%X line %d\n", status, __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        char c = getchar();

        return 1;
    }





    // �L�[�y�A������������
    status = BCryptFinalizeKeyPair(hKey, 0);
    if (!NT_SUCCESS(status))
    {
        printf("BCryptFinalizeKeyPair Error 0x%X line %d\n", status, __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        char c = getchar();

        return 1;
    }




    // �K�v�ȃ������̃T�C�Y���󂯎��
    DWORD dwBlobSize;

    // �Í����Ɏg�p���錮
    PBYTE lpPublicKey   = NULL;
    PBYTE lpPrivateKey = NULL;

    // ���J���̃T�C�Y���擾
    status = BCryptExportKey(hKey, NULL, BCRYPT_RSAPUBLIC_BLOB, NULL, 0, &dwBlobSize, 0);
    if (! NT_SUCCESS(status))
    {
        printf("BCryptExportKey Error 0x%X line %d\n", status, __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        char c = getchar();

        return 1;
    }

    // ���J���p�������m��
    lpPublicKey = m_malloc(dwBlobSize);
    if (! lpPublicKey)
    {
        printf("m_malloc Error line %d\n", __LINE__);

        SafeCloseProv(hAlg);
        SafetDestroyKey(hKey);

        char c = getchar();

        return 1;
    }

    // ���J�����擾
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

    // �擾���������o��
    DumpBin("lpPublicKey", lpPublicKey, dwBlobSize);





    // �閧���̃T�C�Y���擾
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

    // �閧���p�������m��
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

    // �閧�����擾
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

    // �擾���������o��
    DumpBin("lpPrivateKey", lpPrivateKey, dwBlobSize);





    // �A���S���Y���v���o�C�_�[�����
    SafeCloseProv(hAlg);
    // �L�[�n���h����j��
    SafetDestroyKey(hKey);

    // ���������
    SAFE_FREE(lpPublicKey);
    SAFE_FREE(lpPrivateKey);

    char c = getchar();

    return 0;
}