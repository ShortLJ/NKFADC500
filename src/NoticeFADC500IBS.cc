#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "usb3com.h"
#include "NoticeFADC500IBS.h"

// open FADC500IBS
int FADC500IBSopen(int sid, libusb_context *ctx)
{
  int status;
//  char data[0x8000];

  status = USB3Open(FADC500IBS_VENDOR_ID, FADC500IBS_PRODUCT_ID, sid, ctx);
  USB3ClaimInterface(FADC500IBS_VENDOR_ID, FADC500IBS_PRODUCT_ID, sid, 0);

  // readout garbage data on USB endpoint
//  FADC500IBSread_DATA(sid, 32, data);

  printf("Now FADC500IBS is ready.\n");

  return status;
}


// close FADC500IBS
void FADC500IBSclose(int sid)
{
  USB3ReleaseInterface(FADC500IBS_VENDOR_ID, FADC500IBS_PRODUCT_ID, sid, 0);
  USB3Close(FADC500IBS_VENDOR_ID, FADC500IBS_PRODUCT_ID, sid);
}

// Read data buffer count, 1 buffer count = 1 kbyte data
unsigned long FADC500IBSread_BCOUNT(int sid)
{
  return USB3ReadReg(FADC500IBS_VENDOR_ID, FADC500IBS_PRODUCT_ID, sid, 0x30000000);
}


// read data, reads bcount * 1 kbytes data from FADC500IBS DRAM
// returns character raw data, needs sorting after data acquisition
void FADC500IBSread_DATA(int sid, double bcount, unsigned char *data)
{
  int count;

  // maximum data size is 64 Mbyte
  count = int(bcount * 256);
  //extern int USB3Read(uint16_t vendor_id, uint16_t product_id, unsigned char sid, uint32_t count, uint32_t addr, unsigned char *data);
  USB3Read(FADC500IBS_VENDOR_ID, FADC500IBS_PRODUCT_ID, sid, count, 0x40000000, data);
}
