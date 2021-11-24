#include <stdio.h>
#include "dll/Types.h"
#include "dll/SiUSBXp.h"

/* For build
gcc .\main.c dll\x86\SiUSBXp.lib -o bin\config_CP210x.exe
.\bin\config_CP210x.exe
*/


int main(){
    SI_STATUS status;
    DWORD dwNumDevices = 0;

    status = SI_GetNumDevices(&dwNumDevices);
    if (status == SI_SUCCESS)
    {
        printf("Found %d devices\n", dwNumDevices);
    }

}