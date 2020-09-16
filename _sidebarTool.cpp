#include<Windows.h>
#include<stdio.h>
#include<string.h>


VOID EnumFile(DWORD type, LPCWSTR dir);
//初始化_sidebar.md文件
VOID Init_sidebar() {
	HANDLE hFile = CreateFile(L"_sidebar.md", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开这个文件,如果没有就创建
	char szHeader[MAX_PATH] = "<!-- docs/_sidebar.md created by koko-docsify_sidebarTool -->\r\n\r\n";
	WriteFile(hFile,szHeader,strlen(szHeader)+sizeof(char),NULL,NULL);
	CloseHandle(hFile);
}


//打开_sidebar.md文件写入参数所给定的信息,执行一次写入一行
VOID Write_sidebar(LPCWSTR FileName,LPCWSTR FilePath) {
	//创建文件
	HANDLE hFile =	CreateFile(L"_sidebar.md",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);//打开这个文件,如果没有就创建
	
	//构造文件内容
	WCHAR wcBuf[MAX_PATH] = { 0 };
	wcscat_s(wcBuf, L"- [");
	wcscat_s(wcBuf, FileName);
	wcscat_s(wcBuf, L"](");
	wcscat_s(wcBuf, FilePath);
	wcscat_s(wcBuf, L")\r\n");

	SetFilePointer(hFile,-1,NULL,FILE_END);

	char szTmpBuf[MAX_PATH] = { 0 };
	WideCharToMultiByte(CP_ACP,NULL,wcBuf,-1,szTmpBuf,MAX_PATH,NULL,NULL);
	WriteFile(hFile,szTmpBuf,strlen(szTmpBuf)+sizeof(char),NULL,NULL);

	CloseHandle(hFile);
}

//写入空格
VOID Write_space() {
	HANDLE hFile = CreateFile(L"_sidebar.md", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开这个文件,如果没有就创建
	char szTmpBuf[MAX_PATH] = "  ";
	SetFilePointer(hFile, 0, NULL, FILE_END);
	WriteFile(hFile, szTmpBuf, strlen(szTmpBuf) + sizeof(char), NULL, NULL);
	CloseHandle(hFile);
}


/*
枚举当前文件夹下每个目录
type的值为0,则表示根目录生成模式,路径为文件夹名/README.md
type的值为1,则表示子目录生成模式,进入子目录遍历md文件
*/
VOID EnumDir(DWORD type=0) {
	WIN32_FIND_DATA FileData;
	HANDLE hSearch = FindFirstFile(L"*", &FileData);//获取所在目录的所有文件

	do{
		if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && lstrcmp(FileData.cFileName, L".") != 0 && lstrcmp(FileData.cFileName, L"..") != 0) {
				WCHAR wcFilePath[MAX_PATH] = { 0 };
				lstrcat(wcFilePath, FileData.cFileName);
				lstrcat(wcFilePath, L"/README.md");
				Write_sidebar(FileData.cFileName, wcFilePath);
				if (type == 1) {
					WCHAR wcSubFilePath[MAX_PATH] = { 0 };
					lstrcat(wcSubFilePath, FileData.cFileName);
					EnumFile(1, wcSubFilePath);
				}


		}		
	} while (FindNextFile(hSearch, &FileData));

	//CloseHandle的替代:http://www.heycode.com/a13141.html
	FindClose(hSearch);
}

/*
枚举当前文件夹下每个md文件
type的值为0,则表示根目录生成模式,路径为文件名.md
type的值为1,则表示子目录生成模式,路径为目录/文件名.md,type为1需要指定目录是谁!
*/
VOID EnumFile(DWORD type=0,LPCWSTR dir=L"directory") {
	WIN32_FIND_DATA FileData;
	HANDLE hSearch = NULL;

	switch (type){
		case 0: {
			hSearch = FindFirstFile(L"*.md", &FileData);//获取所在目录的所有文件
			do {
				if (FileData.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE) {
					//拼接文件名
					WCHAR wcFileName[MAX_PATH] = { 0 };
					wcsncpy_s(wcFileName, FileData.cFileName, wcslen(FileData.cFileName) - 3);
					Write_sidebar(wcFileName, FileData.cFileName);
				}
			} while (FindNextFile(hSearch, &FileData));
			break;
		}
		case 1: {
			WCHAR DirPath[MAX_PATH] = { 0 };
			wcscat_s(DirPath, L"./");
			wcscat_s(DirPath, dir);
			wcscat_s(DirPath, L"/*.md");
			hSearch = FindFirstFile(DirPath, &FileData);//获取所在目录的所有文件
			do {
				if (FileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
					//拼接文件名
					WCHAR wcFileName[MAX_PATH] = { 0 };
					wcsncpy_s(wcFileName, FileData.cFileName, wcslen(FileData.cFileName) - 3);
					//拼接路径名
					WCHAR wcFilePath[MAX_PATH] = { 0 };
					wcscat_s(wcFilePath, dir);
					wcscat_s(wcFilePath, L"/");
					wcscat_s(wcFilePath, FileData.cFileName);
					Write_space();
					Write_sidebar(wcFileName, wcFilePath);
				}
			} while (FindNextFile(hSearch, &FileData));
			break;
		}
	default:
		break;
	}
	

	//CloseHandle的替代:http://www.heycode.com/a13141.html
	FindClose(hSearch);
}

int main() {
	Init_sidebar();
	EnumDir(1);
	EnumFile();
	return 0;
}