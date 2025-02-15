CHAR *__thiscall 
CollectSystemInfo(DWORD *SharedBuff);

char* __fastcall 
TrasStrings(char* src);

PWSTR 
*GetFilePath(wchar_t *Src);

int32_t __fastcall 
ProcessAndSendData(int32_t* inputData);

size_t __cdecl 
ProcessMultipartRequest(void *dataToSend, size_t dataSize, size_t *bufferSize);
