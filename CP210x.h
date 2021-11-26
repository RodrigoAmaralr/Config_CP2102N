#include "Types.h"
#include "CP210xManufacturingDLL.h"

struct cp210x{
    DWORD DeviceIndex;
    HANDLE handle;
    CP210x_DEVICE_STRING ProductString_SERIAL_NUMBER;
    CP210x_DEVICE_STRING ProductString_DESCRIPTION;
    CP210x_DEVICE_STRING ProductString_FULL_PATH;
    CP210x_MANUFACTURER_STRING DeviceManufacturerString; 
    CP210x_PRODUCT_STRING Deviceproductstring;
    CP210x_SERIAL_STRING Deviceserialstring;
};
typedef struct cp210x CP210X;

CP210x_STATUS status;

void PrintStatusReturnCodesError(CP210x_STATUS Code);
DWORD GetNumDevices();
void GetProductString(DWORD DeviceIndex, CP210X* cp);
void Open(DWORD DeviceIndex, PHANDLE pcyHandle);
void Close(PHANDLE cyHandle);
void ExitProgramWithFailure();
void GetDeviceProductString(DWORD i, CP210X* cp);
void GetDeviceSerialNumber(DWORD i, CP210X* cp);
void GetAllCP210xConfig(DWORD dwNumDevices, CP210X* cp);