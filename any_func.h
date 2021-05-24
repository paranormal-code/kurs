void WriteTime(char *file,char *text)
{ 
 DWORD s1;	
 HANDLE h = CreateFile(file,GENERIC_WRITE,0,0,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
if (h == INVALID_HANDLE_VALUE)
	return ;
 SetFilePointer(h,0,0,FILE_END);
//сама запись
   WriteFile(h,(void*)text,strlen(text),&s1,0);
//закрываем файл
   CloseHandle(h);
};