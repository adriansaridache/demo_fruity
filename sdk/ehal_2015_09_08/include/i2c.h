/*--------------------------------------------------------------------------
File   : i2c.h

Author : Hoang Nguyen Hoan          Nov. 20, 2011

Desc   : Generic I2C definitions
		 Current implementation
		 	 Master mode
		 	 Polling

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

#include "serialintrf.h"

// I2C Status code
typedef enum _I2C_Status {
	I2CSTATUS_START_COND = 8,		// Start condition transmitted
	I2CSTATUS_RESTART_COND = 0x10,	// Start condition re-transmitted
	I2CSTATUS_SLAW_ACK = 0x18,		// SLA+W has been transmitted; ACK has been received
	I2CSTATUS_SLAW_NACK = 0x20,		// SLA+W has been transmitted; NO ACK has been received
	I2CSTATUS_M_TXDAT_ACK = 0x28,		// Data byte in I2DAT has been transmitted; ACK has been received
	I2CSTATUS_M_TXDAT_NACK = 0x30,	// Data byte in I2DAT has been transmitted; NO ACK has been received
	I2CSTATUS_ARB_LOST = 0x38,		// Arbitration lost in SLA+R/W or Data bytes
	I2CSTATUS_SLAR_ACK = 0x40,		// SLA+R has been transmitted; ACK has been received
	I2CSTATUS_SLAR_NACK = 0x48,		// SLA+R has been transmitted; NO ACK has been received
	I2CSTATUS_RXDATA_ACK = 0x50,	// Data byte has been received; ACK has been returned
	I2CSTATUS_RXDATA_NACK = 0x58,	// ata byte has been received; NO ACK has been returned
	I2CSTATUS_OWNSLAW_ACK = 0x60,	// Own SLA+W has been received; ACK has been returned
	I2CSTATUS_ARB_LOST_OWNSLAW_NACK = 0x68,	// Arbitration lost in SLA+R/W as master; Own SLA+W has been received, ACK returned
	I2CSTATUS_GENCALL_ACK = 0x70,	// General Call address (0x00) has been received; ACK has been returned
	I2CSTATUS_ARB_LOST_GENCALL_NACK = 0x78,	// Arbitration lost in SLA+R/W as master; General Call address has been received, ACK has been returned
	I2CSTATUS_SLA_OWN_DATA_ACK = 0x80,	// Previously addressed with own SLA address; DATA has been received; ACK has been returned
	I2CSTATUS_SLA_OWN_DATA_NACK = 0x88,	// Previously addressed with own SLA address; DATA has been received; NO ACK has been returned
	I2CSTATUS_GENCALL_DATA_ACK = 0x90,	// Previously addressed with General Call; DATA byte has been received; ACK has been returned
	I2CSTATUS_GENCALL_DATA_NACK = 0x98,	// Previously addressed with General Call; DATA byte has been received; NO ACK has been returned
	I2CSTATUS_STOP_COND = 0xA0,	// A STOP condition or repeated START condition has been received while still addressed as Slave Receiver or Slave Transmitter
	I2CSTATUS_OWN_SLAR_ACK = 0xA8,		// Own SLA+R has been received; ACK has been returned
	I2CSTATUS_ARB_LOST_OWN_SLAR_ACK = 0xB0,	// Arbitration lost in SLA+R/W as master; Own SLA+R has been received, ACK has been returned
	I2CSTATUS_S_TXDAT_ACK = 0xB8,	// Data byte in I2DAT has been transmitted; ACK has been received
	I2CSTATUS_S_TXDAT_NACK = 0xC0,	// Data byte in I2DAT has been transmitted; NOT ACK has been received
	I2CSTATUS_S_LAST_TXDAT_ACK = 0xC8,	// Last data byte in I2DAT has been transmitted (AA = 0); ACK has been received
} I2CSTATUS;

typedef enum _I2C_Mode {
	I2CMODE_MASTER,
	I2CMODE_SLAVE
} I2CMODE;

#define I2C_MAX_RETRY		5

#pragma pack(push, 4)

// Configuration data used to initialize device
typedef struct _I2C_Config {
	int I2CNo;			// I2C interface number
	int SdaPortNo;		// I/O port used for SDA
	int SdaPinNo;		// I/O pin used for SDA
	int SdaPinOp;		// I/O pin operating function for SDA
	int SclPortNo;		// I/O port used for SCL
	int SclPinNo;		// I/O pin used for SCL
	int SclPinOp;		// I/O pin operating function for SCL
	int Rate;			// Speed in Hz
	I2CMODE Mode;		// Master/Slave mode
	int SlaveAddr;		// I2C slave address used in slave mode only
	int MaxRetry;		// Max number of retry
} I2CCFG;

// Device driver data require by low level fonctions
typedef struct {
	I2CMODE Mode;				// Operating mode Master/Slave
	int 	Rate;				// Speed in Hz
	int 	SlaveAddr;			// I2C slave address used in slave mode only
	int 	MaxRetry;			// Max number of retry
	SERINTRFDEV	SerIntrf;		// I2C device interface implementation
} I2CDEV;

#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// Require impplementations
bool I2CInit(I2CDEV *pDev, I2CCFG *pCfgData);

#ifdef __cplusplus
}

// C++ class wrapper

class I2C : public SerialIntrf {
public:
	I2C() {
		memset((void*)&vDevData, 0, (int)sizeof(vDevData));
	}

	virtual ~I2C() {
		Disable();
	}

	I2C(I2C&);	// Copy ctor not allowed

	bool Init(I2CCFG &CfgData) { return I2CInit(&vDevData, &CfgData); }
	operator I2CDEV& () { return vDevData; };	// Get config data
	int Rate(int RateHz) { return SerialIntrfSetRate(&vDevData.SerIntrf, RateHz); }
	int Rate(void) { return vDevData.Rate; };	// Get rate in Hz
	void Enable(void) { SerialIntrfEnable(&vDevData.SerIntrf); }
	void Disable(void) { SerialIntrfDisable(&vDevData.SerIntrf); }
	virtual bool StartRx(int DevAddr) {
		return SerialIntrfStartRx(&vDevData.SerIntrf, DevAddr);
	}
	// Receive Data only, no Start/Stop condition
	virtual int RxData(uint8_t *pBuff, int BuffLen) {
		return SerialIntrfRxData(&vDevData.SerIntrf, pBuff, BuffLen);
	}
	virtual void StopRx(void) { SerialIntrfStopRx(&vDevData.SerIntrf); }
	virtual bool StartTx(int DevAddr) {
		return SerialIntrfStartTx(&vDevData.SerIntrf, DevAddr);
	}
	// Send Data only, no Start/Stop condition
	virtual int TxData(uint8_t *pData, int DataLen) {
		return SerialIntrfTxData(&vDevData.SerIntrf, pData, DataLen);
	}
	virtual void StopTx(void) { SerialIntrfStopTx(&vDevData.SerIntrf); }
	
private:
	I2CDEV vDevData;
};

#endif	// __cplusplus

#endif	// __I2C_H__
