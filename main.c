#include <stdio.h>
#include <stdlib.h>
#include "CP210x.h"


/* For build
gcc .\main.c CP210x.c CP210xManufacturing.lib -o config_CP210x.exe
.\config_CP210x.exe
*/
CP210X* cp;

int main(){
    DWORD dwNumDevices = GetNumDevices();  
    printf("Found %d devices\n", dwNumDevices);
    cp = malloc(sizeof(CP210X) * dwNumDevices);
        
    printf("DeviceIndex: %d %d\n", cp->DeviceIndex, &cp->DeviceIndex);
    //printf("DeviceIndex: %d\t", cp.DeviceIndex);

    GetAllCP210xConfig(cp);

    printf("DeviceIndex: %d %d\n", cp->DeviceIndex, &cp->DeviceIndex);
    //printf("DeviceIndex: %d\t", cp.DeviceIndex);
    // printf("SERIAL_NUMBER: %s\t", cp.ProductString_SERIAL_NUMBER);
    // printf("DESCRIPTION: %s\t", cp.ProductString_DESCRIPTION);
    // printf("FULL_PATH: %s\n", cp.ProductString_FULL_PATH);

    // for(int i = 0; i < dwNumDevices; i++){
    //     printf("SERIAL_NUMBER: %s\t", cp[i].ProductString_SERIAL_NUMBER);
    //     printf("DESCRIPTION: %s\t", cp[i].ProductString_DESCRIPTION);
    //     printf("FULL_PATH: %s\n", cp[i].ProductString_FULL_PATH);
    // }
    //free(&cp);
}