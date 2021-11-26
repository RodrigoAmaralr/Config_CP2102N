#include <stdio.h>
#include <stdlib.h>
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
    ExitProgramWithFailure();
}

void ExitProgramWithFailure(){
    printf("Program terminated due to error in program execution\n");
    exit(EXIT_FAILURE);
}

DWORD GetNumDevices(){
    DWORD dwNumDevices = 0;
    status = CP210x_GetNumDevices(&dwNumDevices);
    if (status != CP210x_SUCCESS){
        printf("Erro GetNumDevices: ");
        PrintStatusReturnCodesError(status);
    }
    return dwNumDevices;
}

void GetProductString(DWORD DeviceIndex, CP210X* cp){
    cp[DeviceIndex].DeviceIndex = DeviceIndex;
    status = CP210x_GetProductString(DeviceIndex, &cp[DeviceIndex].ProductString_SERIAL_NUMBER, CP210x_RETURN_SERIAL_NUMBER);
    if (status != CP210x_SUCCESS){
        printf("Erro GetProductString: ");
        PrintStatusReturnCodesError(status);
    }
    status = CP210x_GetProductString(DeviceIndex, &cp[DeviceIndex].ProductString_DESCRIPTION, CP210x_RETURN_DESCRIPTION);
    if (status != CP210x_SUCCESS){
        printf("Erro GetProductString: ");
        PrintStatusReturnCodesError(status);
    }
    status = CP210x_GetProductString(DeviceIndex, &cp[DeviceIndex].ProductString_FULL_PATH, CP210x_RETURN_FULL_PATH);
    if (status != CP210x_SUCCESS){
        printf("Erro GetProductString: ");
        PrintStatusReturnCodesError(status);
    }
}

void Open(DWORD DeviceIndex, PHANDLE pcyHandle){
    status = CP210x_Open(DeviceIndex, pcyHandle);
    if (status != CP210x_SUCCESS){
        printf("Erro Open: ");
        PrintStatusReturnCodesError(status);
    }
}

void Close(PHANDLE cyHandle){
    status = CP210x_Close(cyHandle);
    if (status != CP210x_SUCCESS){
        printf("Erro Close: ");
        PrintStatusReturnCodesError(status);
    }
}

void GetDeviceProductString(DWORD i, CP210X* cp){
    BYTE length;
    status = CP210x_GetDeviceProductString(cp[i].handle, &cp[i].Deviceproductstring, &length, TRUE);
    if (status != CP210x_SUCCESS){
        printf("Erro GetDeviceManufacturerString: ");
        PrintStatusReturnCodesError(status);
    }
}

void GetDeviceSerialNumber(DWORD i, CP210X* cp){
    BYTE length;
    status = CP210x_GetDeviceSerialNumber(cp[i].handle, &cp[i].Deviceserialstring, &length, TRUE);
    if (status != CP210x_SUCCESS){
        printf("Erro GetDeviceManufacturerString: ");
        PrintStatusReturnCodesError(status);
    }
}

void GetAllCP210xConfig(DWORD dwNumDevices, CP210X* cp){
    https://github.com/etactica/cp210xmanufacturing/blob/master/main.cpp
    for(int i = 0; i < dwNumDevices; i++){
        Open(i, &cp[i].handle);
        GetProductString(i, cp);
        GetDeviceProductString(i, cp);
        GetDeviceSerialNumber(i, cp);
        
        Close(cp[i].handle);
    }
//     HANDLE h;
//     CP210x_PRODUCT_STRING productString;
//     BYTE length;

//     Open(0, &h);
//     status = CP210x_GetDeviceProductString(h, &productString, &length, TRUE);
//     printf("%i %s \t %d", status, productString, length);
//     Close(h);
}
