#include <stdio.h>
#include "CP210x.h"

void PrintStatusReturnCodesError(CP210x_STATUS Code){
    switch (Code)
    {
    case CP210x_INVALID_HANDLE:
        printf("An handle parameter was not valid\n");
        break;
    case CP210x_INVALID_PARAMETER:
        printf("A parameter was not valid\n");
        break;
    case CP210x_DEVICE_IO_FAILED:
        printf("Device I/O failed\n");
        break;
    case CP210x_FUNCTION_NOT_SUPPORTED:
        printf("The specified function is not supported\n");
        break;
    case CP210x_GLOBAL_DATA_ERROR:
        printf("Global data error\n");
        break;
    case CP210x_FILE_ERROR:
        printf("File error\n");
        break;
    case CP210x_COMMAND_FAILED:
        printf("Command failed\n");
        break;
    case CP210x_INVALID_ACCESS_TYPE:
        printf("Invalid access type\n");
        break;
    case CP210x_DEVICE_NOT_FOUND:
        printf("The specified device was not found\n");
        break;
    default:
        printf("Unknown error");
        break;
    }
}

DWORD GetNumDevices(){
    DWORD dwNumDevices = 0;
    status = CP210x_GetNumDevices(&dwNumDevices);
    if (status == CP210x_SUCCESS){
        return dwNumDevices;
    }else{
        PrintStatusReturnCodesError(status);
        ExitProgramWithFailure();
    }
}

void GetProductString(DWORD dwDeviceIndex, CP210x_DEVICE_STRING* str, DWORD dwFlags){
    status = CP210x_GetProductString(dwDeviceIndex, str, dwFlags);
    if (status != CP210x_SUCCESS){
        PrintStatusReturnCodesError(status);
        ExitProgramWithFailure();
    }
}

void Open(uint32_t DeviceIndex, PHANDLE pcyHandle){
    status = CP210x_Open(DeviceIndex, pcyHandle);
    if (status != CP210x_SUCCESS){
        PrintStatusReturnCodesError(status);
        ExitProgramWithFailure();
    }
}

void Close(PHANDLE cyHandle){
    status = CP210x_Close(cyHandle);
    if (status != CP210x_SUCCESS){
        PrintStatusReturnCodesError(status);
        ExitProgramWithFailure();
    }
}
void ExitProgramWithFailure(){
    printf("Program terminated due to error in program execution\n");
    exit(EXIT_FAILURE);
}