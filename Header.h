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

PSTR __fastcall 
ProccessingOrMapsTheWideCharacter(wchar16* lpWideCharStr){
{
        if (lpWideCharStr)
        // after searching for WideCharToMultiByte in msdn :
        /*
        int WideCharToMultiByte(
            UINT                               CodePage,
            DWORD                              dwFlags,
            _In_NLS_string_(cchWideChar)LPCWCH lpWideCharStr,
            int                                cchWideChar,
            LPSTR                              lpMultiByteStr,
            int                                cbMultiByte,
            LPCCH                              lpDefaultChar,
            LPBOOL                             lpUsedDefaultChar
        );
        */
        // Maps a UTF-16 (wide character) string to a new
        // character string. The new character string is not
        // necessarily from a multibyte character set.
        {
            // - 0xfde9: code page 65001 (UTF-8)
            // - if there is 65001 (UTF-8) or the code page
            // 54936 (GB18030, Windows Vista and later) :
            // dwFlags must be set to either 0
            int32_t cbMultiByte = WideCharToMultiByte(0xfde9, 0, lpWideCharStr, 0xffffffff, nullptr, 0, nullptr, nullptr);
            
            if (cbMultiByte)
            {
                int32_t edx_1;
                edx_1 = cbMultiByte >= 0xffffffff;
                int32_t var_14_1 = -(edx_1) | (cbMultiByte + 1);
                PSTR lpMultiByteStr = Alloc();
                
                if (lpMultiByteStr)
                {
                    if (WideCharToMultiByte(0xfde9, 0, lpWideCharStr, 0xffffffff, lpMultiByteStr, cbMultiByte, nullptr, nullptr))
                        return lpMultiByteStr;
                    
                    _free(lpMultiByteStr);
                }
            }
        }
        
        return nullptr;
}

}

int __cdecl WinnetDllFuncRelated(const char *postData, int dataSize, int extraParam);
