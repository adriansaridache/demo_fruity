/*--------------------------------------------------------------------------
File   : uart.h

Author : Hoang Nguyen Hoan          Nov. 20, 2011

Desc   : Generic uart definitions
		 Current implementation

Copyright (c) 2011, I-SYST inc., all rights reserved

Permission to use, copy, modify, and distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright
notice and this permission notice appear in all copies, and none of the
names : I-SYST or its contributors may be used to endorse or
promote products derived from this software without specific prior written
permission.

For info or contributing contact : hnhoan at i-syst dot com

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------
Modified by          Date              Description

----------------------------------------------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#include <stdint.h>
#include <string.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#include "iopincfg.h"
#include "serialintrf.h"

// Possible baudrate values
// 110, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200,
// 230400, 460800, 921600 1000000


typedef enum {
	UART_PARITY_NONE 	= -1,
	UART_PARITY_ODD 	= 0,
	UART_PARITY_EVEN 	= 1,
	UART_PARITY_MARK	= 2,
	UART_PARITY_SPACE	= 3
} UART_PARITY;

typedef enum {
	UART_FLWCTRL_NONE,
	UART_FLWCTRL_XONXOFF,
	UART_FLWCTRL_HW,
} UART_FLWCTRL;

#define UART_NB_PINS			8

#pragma pack(push, 4)

// Configuration data used to initialize device
typedef struct {
	int DevNo;					// UART device number
	IOPINCFG PinCfg[UART_NB_PINS];	// I/O pin to configure for UART
	int Rate;					// Baudrate, set to 0 for auto baudrate
	int DataBits;				// Number of data bits
	UART_PARITY Parity;			// Data parity
	int StopBits;				// Number of stop bits
	UART_FLWCTRL FlowControl;	//
	bool DMAMode;				// DMA transfer support
	bool IrDAMode;				// Enable IrDA
	bool IrDAInvert;			// IrDA input inverted
	bool IrDAFixPulse;			// Enable IrDA fix pulse
	int	IrDAPulseDiv;			// Fix pulse divider
} UARTCFG;

// Device driver data require by low level fonctions
typedef struct {
//	UARTCFG Cfg;
	int Rate;					// Baudrate, set to 0 for auto baudrate
	int DataBits;				// Number of data bits
	UART_PARITY Parity;			// Data parity
	int StopBits;				// Number of stop bits
	UART_FLWCTRL FlowControl;	//
	bool IrDAMode;				// Enable IrDA
	bool IrDAInvert;			// IrDA input inverted
	bool IrDAFixPulse;			// Enable IrDA fix pulse
	int	IrDAPulseDiv;			// Fix pulse divider
	SERINTRFDEV	SerIntrf;		// I2C device interface implementation
} UARTDEV;

#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// Require impplementations
bool UARTInit(UARTDEV *pDev, const UARTCFG *pCfgData);

inline int UARTGetRate(UARTDEV *pDev) { return pDev->SerIntrf.GetRate(&pDev->SerIntrf); }
inline int UARTSetRate(UARTDEV *pDev, int Rate) { return pDev->SerIntrf.SetRate(&pDev->SerIntrf, Rate); }
int UARTRx(UARTDEV *pDev, uint8_t *pBuff, int Bufflen);
int UARTTx(UARTDEV *pDev, uint8_t *pData, int Datalen);
void UARTprintf(UARTDEV *pDev, char *pFormat, ...);
void UARTvprintf(UARTDEV *pDev, char *pFormat, va_list vl);

#ifdef __cplusplus
}

// C++ class wrapper

// C++ class wrapper
class UART: public SerialIntrf {
public:
	UART() {
		memset(&vDevData, 0, sizeof(vDevData));
	}
	virtual ~UART() {}
	UART(UART&);

	bool Init(const UARTCFG &CfgData) {
		return UARTInit(&vDevData, &CfgData);
	}
	// ++ ** Require implementation
	// Set data baudrate
	virtual int Rate(int DataRate) { return UARTSetRate(&vDevData, DataRate); }
	// Get current data baudrate
	virtual int Rate(void) { return UARTGetRate(&vDevData); }
	virtual int Rx(uint8_t *pBuff, uint32_t Len) { return ((SerialIntrf *)this)->Rx(0, pBuff, Len); }
	// Initiate receive
	virtual bool StartRx(int DevAddr) { return true; }
	// Receive Data only, no Start/Stop condition
	virtual int RxData(uint8_t *pBuff, int BuffLen) {
		return SerialIntrfRxData(&vDevData.SerIntrf, pBuff, BuffLen);
	}
	// Stop receive
	virtual void StopRx(void) {}
	virtual int Tx(uint8_t *pData, uint32_t Len) { return ((SerialIntrf*)this)->Tx(0, pData, Len); }
	// Initiate transmit
	virtual bool StartTx(int DevAddr) { return SerialIntrfStartTx(&vDevData.SerIntrf, 0); }
	// Transmit Data only, no Start/Stop condition
	virtual int TxData(uint8_t *pData, int DataLen) {
		return SerialIntrfTxData(&vDevData.SerIntrf, pData, DataLen);
	}
	// Stop transmit
	virtual void StopTx(void) { SerialIntrfStopTx(&vDevData.SerIntrf); }
	// -- **
	void printf(char *pFormat, ...) {
		va_list vl;
	    va_start(vl, pFormat);
	    UARTvprintf(&vDevData, pFormat, vl);
	    va_end(vl);
	}

	operator UARTDEV * () { return &vDevData; }

private:
	UARTDEV	vDevData;
};


#endif	// __cplusplus

#endif	// __I2C_H__
