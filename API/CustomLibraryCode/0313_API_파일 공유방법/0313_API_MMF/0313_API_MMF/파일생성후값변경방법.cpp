#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
void main() {
	// 1. ���� ����
	HANDLE hFile = CreateFile(TEXT("a.txt"), GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	
	// 2. ȭ�� ���� KO ����
	HANDLE hMap = CreateFileMapping(hFile, 0,PAGE_READWRITE,0, 100,TEXT("map"));
	/*
	HANDLE CreateFileMaping ( HANDLE hFile, LPSECURITY_ATTRIBUTES lpAttrs, DWORD flProtect,DWORD dwMaxSizeHigh,DWORD dwMaxSizeLow,LPCTSTR lpName);
	hFile			���� �ڵ� (-1�� �Ѱ�� ����¡ ������ ����ϰ� ��)
	lpAttrs			���� �Ӽ�
	flProtect		���� �㰡
	dwMaxSizeHigh	������ ũ���� ���� 32��Ʈ
	dwMaxSizeLow	������ ũ���� ���� 32��Ʈ
	lpName			��ü��
	*/

	// 3. �� ���� ,���� ��ü�� ����ؼ� ���� �ּҿ� ���� ����
	char* p = (char*)MapViewOfFileEx(hMap, FILE_MAP_WRITE,0, 0, 0,	(void*)0x10000000); 
	if (p == 0)
	{
		printf("error");
	}
	else 
	{
		printf("���ε� �ּ� : %p\n", p);
		strcpy(p, "hello");
		p[50] = 'a';
		p[100] = 'b';
	}
	/*
	��ȯ���� �� �޸� ������ ������
	LPVOID MapViewOfFile( HANDLE hFileMapObj, DWORD dwDesiredAccess, DWORD dwFileOfsHigh, DWORD dwFileOfsLow, SIZE_T dwBytesToMap);
	hFileMapObj				���� ���� ��ü �ڵ�
	dwDesiredAccess			�ʿ��� ���� ����
	dwFileOfsHigh			�並 ������ ������ ���� ������ ����32��Ʈ
	dwFileOfsLow			�並 ������ ������ ���� ������ ����32��Ʈ
	dwBytesToMap			�並 ������ ������ ũ��
	*/
	UnmapViewOfFile(p);
	CloseHandle(hMap);
	CloseHandle(hFile);
}
