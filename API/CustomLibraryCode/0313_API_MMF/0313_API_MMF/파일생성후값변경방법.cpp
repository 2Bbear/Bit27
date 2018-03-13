#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
void main() {
	// 1. 파일 생성
	HANDLE hFile = CreateFile(TEXT("a.txt"), GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	
	// 2. 화일 매핑 KO 생성
	HANDLE hMap = CreateFileMapping(hFile, 0,PAGE_READWRITE,0, 100,TEXT("map"));
	/*
	HANDLE CreateFileMaping ( HANDLE hFile, LPSECURITY_ATTRIBUTES lpAttrs, DWORD flProtect,DWORD dwMaxSizeHigh,DWORD dwMaxSizeLow,LPCTSTR lpName);
	hFile			파일 핸들 (-1로 둘경우 페이징 파일을 사용하게 됨)
	lpAttrs			보안 속성
	flProtect		접근 허가
	dwMaxSizeHigh	매핑할 크기의 상위 32비트
	dwMaxSizeLow	매핑할 크기의 하위 32비트
	lpName			객체명
	*/

	// 3. 값 변경 ,매핑 객체를 사용해서 가상 주소와 파일 연결
	char* p = (char*)MapViewOfFileEx(hMap, FILE_MAP_WRITE,0, 0, 0,	(void*)0x10000000); 
	if (p == 0)
	{
		printf("error");
	}
	else 
	{
		printf("매핑된 주소 : %p\n", p);
		strcpy(p, "hello");
		p[50] = 'a';
		p[100] = 'b';
	}
	/*
	반환값은 뷰 메모리 영역의 포인터
	LPVOID MapViewOfFile( HANDLE hFileMapObj, DWORD dwDesiredAccess, DWORD dwFileOfsHigh, DWORD dwFileOfsLow, SIZE_T dwBytesToMap);
	hFileMapObj				파일 매핑 객체 핸들
	dwDesiredAccess			필요한 접근 권한
	dwFileOfsHigh			뷰를 실행할 범위의 시작 오프셋 상위32비트
	dwFileOfsLow			뷰를 실행할 범위의 시작 오프셋 하위32비트
	dwBytesToMap			뷰를 실행할 범위의 크기
	*/
	UnmapViewOfFile(p);
	CloseHandle(hMap);
	CloseHandle(hFile);
}
