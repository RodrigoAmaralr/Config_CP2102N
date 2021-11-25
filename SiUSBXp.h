#ifndef HOST_LIB_SIUSBXP_INCLUDE_SIUSBXP_H_INCLUDED_9QM3BKN3FX
#define HOST_LIB_SIUSBXP_INCLUDE_SIUSBXP_H_INCLUDED_9QM3BKN3FX

/// @addtogroup DirectAccess CP201x DirectAccess (nee USBXpress) Library
///
/// @{

#include	"silabs_defs.h"
#include	"silabs_sal.h"


#ifdef _WIN32
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SI_USB_XP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SI_USB_XP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef SI_USB_XP_EXPORTS
#define SI_USB_XP_API
#else
#define SI_USB_XP_API __declspec(dllimport)
#pragma comment (lib, "SiUSBXp.lib")
#endif
#else // !_WIN32
#define __declspec(n)
#define SI_USB_XP_API
#define WINAPI
#endif // !_WIN32

 
/// API Status return codes
typedef enum _SI_STATUS {
	SI_SUCCESS = SILABS_STATUS_SUCCESS	///< @ref SILABS_STATUS no error
	, SI_INVALID_HANDLE = 0x01			///< an handle parameter was not valid
	, SI_READ_ERROR = 0x02
	, SI_RX_QUEUE_NOT_READY = 0x03
	, SI_WRITE_ERROR = 0x04
	, SI_RESET_ERROR = 0x05
	, SI_INVALID_PARAMETER = 0x06		///< a parameter was not valid
	, SI_INVALID_REQUEST_LENGTH = 0x07
	, SI_DEVICE_IO_FAILED = 0x08
	, SI_INVALID_BAUDRATE = 0x09
	, SI_FUNCTION_NOT_SUPPORTED = 0x0A
	, SI_GLOBAL_DATA_ERROR = 0x0B
	, SI_SYSTEM_ERROR_CODE = 0x0C		///< an unexpected, unrecoverable error happened while interacting with the operating system
	, SI_READ_TIMED_OUT = 0x0D
	, SI_WRITE_TIMED_OUT = 0x0E
	, SI_IO_PENDING = 0x0F
	, SI_NOTHING_TO_CANCEL = 0xA0
	, SI_DEVICE_NOT_FOUND = 0xFF		///< the specified device was not found
} SI_STATUS, *PSI_STATUS;

// GetProductString() function flags
#define		SI_RETURN_SERIAL_NUMBER		0x00
#define		SI_RETURN_DESCRIPTION		0x01
#define		SI_RETURN_LINK_NAME			0x02
#define		SI_RETURN_VID				0x03
#define		SI_RETURN_PID				0x04

// RX Queue status flags
#define		SI_RX_NO_OVERRUN			0x00
#define		SI_RX_EMPTY					0x00
#define		SI_RX_OVERRUN				0x01
#define		SI_RX_READY					0x02

// Buffer size limits
#define		SI_MAX_DEVICE_STRLEN		256
#define		SI_MAX_READ_SIZE			4096*16
#define		SI_MAX_WRITE_SIZE			4096

// Type definitions
typedef		char	SI_DEVICE_STRING[SI_MAX_DEVICE_STRLEN];

// Input and Output pin Characteristics
#define		SI_HELD_INACTIVE			0x00
#define		SI_HELD_ACTIVE				0x01
#define		SI_FIRMWARE_CONTROLLED		0x02		
#define		SI_RECEIVE_FLOW_CONTROL		0x02
#define		SI_TRANSMIT_ACTIVE_SIGNAL	0x03
#define		SI_STATUS_INPUT				0x00
#define		SI_HANDSHAKE_LINE			0x01

// Mask and Latch value bit definitions
#define		SI_GPIO_0					(1<<0)
#define		SI_GPIO_1					(1<<1) 
#define		SI_GPIO_2					(1<<2)
#define		SI_GPIO_3					0x0008
#define		SI_GPIO_4					0x0010
#define		SI_GPIO_5					0x0020
#define		SI_GPIO_6					0x0040
#define		SI_GPIO_7					0x0080
#define		SI_GPIO_8					0x0100
#define		SI_GPIO_9					0x0200
#define		SI_GPIO_10					0x0400
#define		SI_GPIO_11					0x0800
#define		SI_GPIO_12					0x1000
#define		SI_GPIO_13					0x2000
#define		SI_GPIO_14					0x4000
#define		SI_GPIO_15					0x8000

// SI_GetPartNumber() returned PartNums (deprecated, see silabs_defs.h::CP210X_PARTNUM)
#define     SI_USBXPRESS_EFM8			CP210x_PARTNUM_USBXPRESS_EFM8
#define     SI_USBXPRESS_EFM32			CP210x_PARTNUM_USBXPRESS_EFM32
#define		SI_CP2101_VERSION			0x01
#define		SI_CP2102_VERSION			0x02
#define		SI_CP2103_VERSION			0x03
#define		SI_CP2104_VERSION			0x04
#define		SI_CP2105_VERSION			0x05
#define		SI_CP2108_VERSION			0x08
#define		SI_CP2109_VERSION			0x09
#define		SI_CP2102N_QFN28_VERSION		0x20
#define		SI_CP2102N_QFN24_VERSION		0x21
#define		SI_CP2102N_QFN20_VERSION		0x22

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Determines the number of CP210x devices configured as USBXpress devices connected to the system
///
/// @param[out] lpdwNumDevices a pointer to a DWORD/4-byte location to hold the returned device count
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
///	\retval			SI_INVALID_PARAMETER -- lpdwNumDevices is an unexpected value
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_GetNumDevices(
	_Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ LPDWORD lpdwNumDevices
	);

/// @brief Gets a Product String
///
/// @param[in] dwDeviceNum is the desired device's index into the device list used to determine @ref SI_GetNumDevices()
/// @param[out] lpvDeviceString points at a buffer into which the Product String will be copied and returned
/// @param[in] dwFlags is the indication of which Product String to return 
///
/// @note Deprecated. Use SI_GetProductStringSafe instead
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	@retval	SI_SUCCESS -- success
///	@retval			SI_DEVICE_IO_FAILED -- a driver-internal error occurred
//__declspec(deprecated)
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_GetProductString(
	_In_ _Pre_defensive_ const DWORD dwDeviceNum,
	LPVOID lpvDeviceString,
	_In_ _Pre_defensive_ const DWORD dwFlags
	);

/// @brief Gets a Product String
///
/// @param[in] dwDeviceNum is the desired device's index into the device list used to determine @ref SI_GetNumDevices()
/// @param[out] lpvDeviceString points at a buffer into which the Product String will be copied and returned
/// @param[in] DeviceStringLenInBytes the length in bytes of lpvDeviceString the buffer into which the Product String will be copied and returned
/// @param[in] dwFlags is the indication of which Product String to return 
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
///	\retval			SI_DEVICE_IO_FAILED -- a driver-internal error occurred
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_GetProductStringSafe(
	_In_ _Pre_defensive_ const DWORD dwDeviceNum,
	_Out_writes_bytes_(DeviceStringLenInBytes) LPVOID lpvDeviceString,
	_In_ _Pre_defensive_ const size_t DeviceStringLenInBytes,
	_In_ _Pre_defensive_ const DWORD dwFlags
	);


/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_Open(
	_In_ _Pre_defensive_ const DWORD dwDevice,
	_Out_writes_bytes_(sizeof(HANDLE)) _Pre_defensive_ PHANDLE pHandle
	); 

/// @brief Closes an open handle to the device
///
/// @param[in] cyHandle is an open handle to the device
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
///	\retval			SI_INVALID_HANDLE -- pHandle is invalid
///	\retval			SI_SYSTEM_ERROR_CODE -- a device context could not be determined for the device. Internal OS error?
///	\retval			SI_GLOBAL_DATA_ERROR -- driver globals could not be found. Internal OS error?
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_Close(
	_In_ _Pre_defensive_ const HANDLE cyHandle
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_Read(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_Out_writes_bytes_(dwBytesToRead) LPVOID lpBuffer,
	_In_range_(0, SI_MAX_READ_SIZE) const DWORD dwBytesToRead, 
	_Out_range_(0,dwBytesToRead) LPDWORD lpdwBytesReturned,
	//_In_opt_ LPOVERLAPPED o = NULL
    _In_opt_ LPOVERLAPPED o
	);

/// @brief Write buffer to device
///
/// @param[in] cyHandle is an open handle to the device
/// @param[in] lpBuffer points at a buffer containing the data to be written to the device
/// @param[in] dwBytesToWrite is the number of bytes in that buffer to be written to the device
/// @param[out] lpdwBytesWritten is the number of bytes from that buffer successfully written to the device
/// @param[in] o is ...
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
///	\retval			SI_DEVICE_IO_FAILED -- a driver-internal error occurred
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_Write(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_In_reads_bytes_(dwBytesToWrite) _Pre_defensive_ LPVOID lpBuffer,
	_In_range_(0, SI_MAX_WRITE_SIZE) _Pre_defensive_ const DWORD dwBytesToWrite,
	_Out_range_(0, dwBytesToWrite) _Pre_defensive_ LPDWORD lpdwBytesWritten,
	//_In_opt_ LPOVERLAPPED o = NULL
    _In_opt_ LPOVERLAPPED o
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_DeviceIOControl(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_In_ _Pre_defensive_ const DWORD dwIoControlCode,
	LPVOID lpInBuffer,
	_In_ _Pre_defensive_ const DWORD dwBytesToRead,
	LPVOID lpOutBuffer,
	_In_ _Pre_defensive_ const DWORD dwBytesToWrite,
	LPDWORD lpdwBytesSucceeded
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_FlushBuffers(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_In_ _Pre_defensive_ const BYTE FlushTransmit,
	_In_ _Pre_defensive_ const BYTE FlushReceive
	);

/// @brief Set the Read- and Write-timeouts
///
/// @param[in] dwReadTimeoutInMilliseconds is the read timeout in milliseconds
/// @param[in] dwWriteTimeoutInMilliseconds is the write timeout in milliseconds
/// @note a value of ~0 (0xFFFFFFFF) means an infinite-timeout
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
///	\retval			SI_DEVICE_IO_FAILED -- a driver-internal error occurred
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_SetTimeouts(
	_In_ _Pre_defensive_ const DWORD dwReadTimeoutInMilliseconds,
	_In_ _Pre_defensive_ const DWORD dwWriteTimeoutInMilliseconds
	);

/// @brief Reads and returns the Read- and Write-timeouts
///
/// @param[out] lpdwReadTimeout points at a buffer into which the read timeout value in milliseconds will be written 
/// @param[out] lpdwWriteTimeout points at a buffer into which the write timeout value in milliseconds will be written
/// @note a value of ~0 (0xFFFFFFFF) means an infinite-timeout
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
///	\retval			SI_INVALID_PARAMETER -- lpdwReadTimeout or lpdwWriteTimeout are an unexpected value
///	\retval			SI_GLOBAL_DATA_ERROR -- driver globals could not be found. Internal OS error?
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_GetTimeouts(
	_Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ LPDWORD lpdwReadTimeout,
	_Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ LPDWORD lpdwWriteTimeout
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_CheckRXQueue(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ LPDWORD lpdwNumBytesInQueue,
	_Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ LPDWORD lpdwQueueStatus
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
SI_USB_XP_API SI_STATUS WINAPI
SI_SetBaudRate(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_In_ _Pre_defensive_ const DWORD dwBaudRate
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_SetBaudDivisor(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_In_ _Pre_defensive_ const WORD wBaudDivisor
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_SetLineControl(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_In_ _Pre_defensive_ const WORD wLineControl
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_SetFlowControl(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_In_ _Pre_defensive_ const BYTE bCTS_MaskCode,
	_In_ _Pre_defensive_ const BYTE bRTS_MaskCode,
	_In_ _Pre_defensive_ const BYTE bDTR_MaskCode,
	_In_ _Pre_defensive_ const BYTE bDSR_MaskCode,
	_In_ _Pre_defensive_ const BYTE bDCD_MaskCode,
	_In_ _Pre_defensive_ const BOOL bFlowXonXoff
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_GetModemStatus(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ PBYTE ModemStatus
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_SetBreak(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_In_ _Pre_defensive_ const WORD wBreakState
	);

/// @brief Reads and returns the current port latch value from the device
///
/// @param[in] cyHandle is an open handle to the device
/// @param[out] lpwLatch points at a buffer into which the port latch value will be written
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
///	\retval			SI_INVALID_HANDLE -- cyHandle is invalid
///	\retval			SI_INVALID_PARAMETER -- lpwLatch is an unexpected value
///	\retval			SI_SYSTEM_ERROR_CODE -- a device context could not be determined for the device. Internal OS error?
///	\retval			SI_GLOBAL_DATA_ERROR -- driver globals could not be found. Internal OS error?
///	\retval			SI_FUNCTION_NOT_SUPPORTED -- the device does not support port latch
///	\retval			SI_DEVICE_IO_FAILED -- the device failed to respond to I/O in any expected manner
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_ReadLatch(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ LPWORD	lpwLatch
	);

/// @brief Writes a new port latch value to the device
///
/// @param[in] cyHandle is an open handle to the device
/// @param[in] Mask the TBD
/// @param[in] Latch the new port latch value to be written to the device
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
///	\retval			SI_INVALID_HANDLE -- cyHandle is invalid
///	\retval			SI_INVALID_PARAMETER -- lpwLatch is an unexpected value
///	\retval			SI_SYSTEM_ERROR_CODE -- a device context could not be determined for the device. Internal OS error?
///	\retval			SI_GLOBAL_DATA_ERROR -- driver globals could not be found. Internal OS error?
///	\retval			SI_FUNCTION_NOT_SUPPORTED -- the device does not support port latch
///	\retval			SI_DEVICE_IO_FAILED -- the device failed to respond to I/O in any expected manner
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_WriteLatch(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_In_ _Pre_defensive_ const WORD Mask,
	_In_ _Pre_defensive_ const WORD Latch
	);


/// @brief Reads and returns the Part Number from the device
///
/// @param[in] cyHandle is an open handle to the device
/// @param[out] lpbPartNum points at a buffer into which the @ref silabs_defs.h::CP210X_PARTNUM Part Number value will be written
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
///	\retval			SI_INVALID_HANDLE -- cyHandle is invalid
///	\retval			SI_INVALID_PARAMETER -- lpbPartNum is an unexpected value
///	\retval			SI_SYSTEM_ERROR_CODE -- a device context could not be determined for the device. Internal OS error?
///	\retval			SI_GLOBAL_DATA_ERROR -- driver globals could not be found. Internal OS error?
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_GetPartNumber(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_  LPBYTE lpbPartNum
	);

/// @brief Reads and returns the firmware library version from the device
///
/// @param[in] cyHandle is an open handle to the device
/// @param[out] pLibraryVersion points at a two-byte buffer into which the Firmware Library Version value will be written
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
///	\retval			SI_INVALID_HANDLE -- cyHandle is invalid
///	\retval			SI_INVALID_PARAMETER -- pLibraryVersion is an unexpected value
///	\retval			SI_SYSTEM_ERROR_CODE -- a device context could not be determined for the device. Internal OS error?
///	\retval			SI_GLOBAL_DATA_ERROR -- driver globals could not be found. Internal OS error?
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_GetPartLibraryVersion(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_Out_writes_bytes_(2 * sizeof(BYTE)) _Pre_defensive_ BYTE pLibraryVersion[2]
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_GetInterfaceNumber(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ LPBYTE	lpbInterfaceNum
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_GetDeviceProductString(
	_In_ _Pre_defensive_ const HANDLE	cyHandle,
	LPVOID	lpProduct,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ LPBYTE	lpbLength,
	//_In_ _Pre_defensive_ const BOOL bConvertToASCII = TRUE
    _In_ _Pre_defensive_ const BOOL bConvertToASCII
	);

/// @brief Reads and returns the DLL library version from the DLL
///
/// @param[out] HighVersion points at a 4-byte-sized buffer into which the high-byte of the DLL Version value will be written
/// @param[out] LowVersion points at a 4-byte-sized buffer into which the low-byte of the DLL Version value will be written
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
///	\retval			SI_INVALID_PARAMETER -- HighVersion or LowVersion are an unexpected value
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_GetDLLVersion(
	_Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ DWORD* HighVersion,
	_Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ DWORD* LowVersion
	);

/// @brief Reads and returns the kernel-mode driver version from the driver (deprecated (architecture no longer uses a kernel-mode driver))
///
/// @param[out] HighVersion points at a byte-sized buffer into which the high-byte of the Driver Version value will be written
/// @param[out] LowVersion points at a byte-sized buffer into which the low-byte of the Driver Version value will be written
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
__declspec(deprecated)
SI_USB_XP_API SI_STATUS WINAPI
SI_GetDriverVersion(
	_Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ DWORD* HighVersion,
	_Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ DWORD* LowVersion
	);

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_CancelIo(
	_In_ _Pre_defensive_ const HANDLE cyHandle
    );

/// @brief tbd
///
/// @param[in]  TBD
///
/// @returns Returns SI_SUCCESS on success, or another @ref SI_STATUS Return value if there is an error.
///	\retval	SI_SUCCESS -- success
_Check_return_
_Ret_range_(SI_SUCCESS, SI_DEVICE_NOT_FOUND)
_Success_(return == SI_SUCCESS)
SI_USB_XP_API SI_STATUS WINAPI
SI_CancelIoEx(
	_In_ _Pre_defensive_ const HANDLE cyHandle,
    LPOVERLAPPED lpOverlapped
    );

#ifdef __cplusplus
}
#endif

/// @}

#endif //HOST_LIB_SIUSBXP_INCLUDE_SIUSBXP_H_INCLUDED_9QM3BKN3FX
