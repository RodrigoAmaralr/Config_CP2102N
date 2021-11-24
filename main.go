package main

import (
	"fmt"
	"log"
	"syscall"
	"unsafe"
)

/* Config
$Env:GOARCH = "386"
$Env:GOARCH = "amd64"
*/

var (
	StatusSISUCCESS = 0x00
	//SiUSBXp         = syscall.MustLoadDLL("x86/CP210xManufacturing.dll")
	SiUSBXp              = syscall.MustLoadDLL("x64/CP210xManufacturing.dll")
	CP210x_GetNumDevices = SiUSBXp.MustFindProc("CP210x_GetNumDevices")
)

// GetNumDevices gets the number of USB devices recognized
func GetNumDevices() int {
	var lpdwNumDevices int
	r1, _, _ := CP210x_GetNumDevices.Call(uintptr(unsafe.Pointer(&lpdwNumDevices)))

	if int(r1) == StatusSISUCCESS {
		if lpdwNumDevices == 1 {
			log.Println("Encontrado 1 Eletro")
		} else {
			if lpdwNumDevices > 1 {
				log.Println("Encontrados ", lpdwNumDevices, " Eletros")
			}
		}
		return lpdwNumDevices
	}

	return -1
}

func main() {
	fmt.Printf("*********************************************************\n")
	fmt.Printf("**                                                     **\n")
	fmt.Printf("**                 PROGRAMADOR CP2102N                 **\n")
	fmt.Printf("**                                                     **\n")
	fmt.Printf("*********************************************************\n")

	numDevices := GetNumDevices()
	if numDevices == 0 {
		log.Fatalln("Eletro não encontrado")
	}

}
