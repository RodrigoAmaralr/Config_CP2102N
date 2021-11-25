#include "Types.h"
#include "CP210xManufacturingDLL.h"


struct cp210x{
    DWORD dwDeviceIndex;
    HANDLE handle;
    DWORD dwFlags;
    CP210x_DEVICE_STRING ProductString_SERIAL_NUMBER;
    CP210x_DEVICE_STRING ProductString_DESCRIPTION;
    CP210x_DEVICE_STRING ProductString_FULL_PATH;
};

typedef struct cp210x CP210X;

CP210x_STATUS status;

void PrintStatusReturnCodesError(CP210x_STATUS Code);
DWORD GetNumDevices();
void GetProductString(DWORD dwDeviceIndex, CP210x_DEVICE_STRING* str, DWORD dwFlags);
void Open(uint32_t DeviceIndex, PHANDLE pcyHandle);
void Close(PHANDLE cyHandle);
void ExitProgramWithFailure();