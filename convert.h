// по имени кодировки, возвращает ее "номер страницы в юникоде"
UINT GetCharSet(char *name)
{   
	if (_stricmp(name,"DOS") == 0) return CP_OEMCP;
	if (_stricmp(name,"KOI8") == 0) return 20866;
	if (_stricmp(name,"UTF8") == 0) return CP_UTF8;
	if (_stricmp(name,"CP_1251") == 0) return CP_ACP;
	return -1;
};

int Convert( char* argv[])
{
	DWORD s,s1,InSize;
	char * buf;
   	HANDLE h;
    WCHAR * wbuf = 0; 
	UINT CodePage1 = GetCharSet(argv[1]),CodePage2=GetCharSet(argv[2]);

if ((CodePage1 == -1) | (CodePage2 == -1))
{	
	MessageBox(0,"unknow char set\n","ERROR",MB_ICONERROR);
	return -1;
};
//откриваем файл на чтение
	h = CreateFile(argv[3],GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
if (h == INVALID_HANDLE_VALUE) 
{//если не удалось открыть файл, выводим об этом сообщение
  MessageBox(0,"can'nt open file\n","ERROR",MB_ICONERROR);
  return -1;
};
    InSize = s = GetFileSize(h,0);
	buf =(char*) LocalAlloc (LPTR,s+1); buf[s] = 0;
	ReadFile(h,&buf[0],s,&s,0);
	CloseHandle(h);
 // переобразование текста в юникод   
	s1=MultiByteToWideChar(CodePage1,MB_ERR_INVALID_CHARS,buf,-1,0,0);
if (s1 == 0)
{	
	MessageBox(0,"Convert Error","ERROR",MB_ICONERROR);
	return -1;
};
	//получаем память из кучи(локальная память потока)
	wbuf =(WCHAR*) LocalAlloc (LPTR,(s1+1)*sizeof(WORD));		
	wbuf[s1] = 0;
  s1 = MultiByteToWideChar(CodePage1,MB_ERR_INVALID_CHARS,buf,-1,wbuf,s1); 

//переобразование из юникода в заданую кодировку
	BOOL dwFlag = (CodePage2!=CP_UTF8)?(WC_COMPOSITECHECK):(0); //для  CP_UTF8, нужно чтоб dwFlag равнялся 0
	s1 = WideCharToMultiByte(CodePage2,dwFlag,wbuf,-1,0,0,(const char*)0,0);
if (s1 == 0)
{
	MessageBox(0,"Convert Error","ERROR",MB_ICONERROR);
	return -1;
};
//освобождаем память из кучи
	LocalFree(buf);
	 buf =(char*) LocalAlloc (LPTR,s1+1); buf[s1] = 0;
 // само пераобразование из юникода в заданую кодировку
    s1 = WideCharToMultiByte(CodePage2,dwFlag,wbuf,-1,buf,s1,(const char*)0,0);
//запись результата в файл
	h = CreateFile(argv[4],GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
if (h == INVALID_HANDLE_VALUE)
{
	MessageBox(0,"Can'nt create file","ERROR",MB_ICONERROR);
	return -1;
};
//сама запись
   WriteFile(h,(void*)buf,s1,&s1,0);
//закрываем файл
   CloseHandle(h);
//освобождаем память из кучи
LocalFree(wbuf);
LocalFree(buf);
   return InSize; 
}
