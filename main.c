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
        

    GetAllCP210xConfig(dwNumDevices, cp);

    for(int i = 0; i < dwNumDevices; i++){
        printf("\n********** DEVICE %d**********\n", dwNumDevices);
        printf("DeviceIndex: %d\t",     cp[i].DeviceIndex);
        printf("SERIAL_NUMBER: %s\t",   cp[i].ProductString_SERIAL_NUMBER);
        printf("DESCRIPTION: %s\t",     cp[i].ProductString_DESCRIPTION);
        printf("FULL_PATH: %s\n",       cp[i].ProductString_FULL_PATH);

        printf("DeviceManufacturerString: %s\n",    cp[i].Deviceproductstring);
        printf("Deviceserialstring: %s\n",          cp[i].Deviceserialstring);

    }
    free(cp);
}