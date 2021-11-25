#include <stdio.h>
#include "CP210x.h"


/* For build
gcc .\main.c CP210x.c CP210xManufacturing.lib -o config_CP210x.exe
.\config_CP210x.exe
*/

int main(){
    DWORD dwNumDevices = GetNumDevices();  
    printf("Found %d devices\n", dwNumDevices);
    CP210X* cp = malloc(sizeof(CP210X) * dwNumDevices);
    GetProductString(dwNumDevices, cp);
    for(int i = 0; i < dwNumDevices; i++){
        printf("SERIAL_NUMBER: %s\t", cp[i].ProductString_SERIAL_NUMBER);
        printf("DESCRIPTION: %s\t", cp[i].ProductString_DESCRIPTION);
        printf("FULL_PATH: %s\n", cp[i].ProductString_FULL_PATH);
    }
}