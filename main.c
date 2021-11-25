#include <stdio.h>
#include "CP210x.h"


/* For build
gcc .\main.c CP210x.c CP210xManufacturing.lib -o config_CP210x.exe
.\config_CP210x.exe
*/

int main(){
    DWORD dwNumDevices = GetNumDevices();  
    printf("Found %d devices\n", dwNumDevices);
    
    CP210x_DEVICE_STRING str;
    for(int i = 0; i < dwNumDevices; i++){
        GetProductString(i, &str, CP210x_RETURN_SERIAL_NUMBER);
        printf("SERIAL_NUMBER: %s\t", str);

        GetProductString(i, &str, CP210x_RETURN_DESCRIPTION);
        printf("DESCRIPTION: %s\t", str);

        GetProductString(i, &str, CP210x_RETURN_FULL_PATH);
        printf("FULL_PATH: %s\n", str);
    }

    
}