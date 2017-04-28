#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "usb3tcb.h"
#include "NoticeTCBIBS.h"

// open TCBIBS
int TCBIBSopen(int sid, libusb_context* ctx)
{
  int status;

  status = USB3TCBOpen(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, ctx);
  USB3TCBClaimInterface(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0);

  return status;
}

// close TCBIBS
void TCBIBSclose(int sid)
{
  USB3TCBReleaseInterface(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0);
  USB3TCBClose(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid);
}

// write lookup table ; TFADC500, TFADC64, AMOREADC, TCBIBS
void TCBIBSwrite_LT(int sid, unsigned long mid, char* data, int len)
{
  int nword = len/4;
  uint32_t buffer;
  int loop;

  for(loop=0; loop<nword; loop++) {
    memcpy(&buffer, data + loop*4, 4);
    USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, loop, buffer);
  }

}

// reset data acquisition
void TCBIBSreset(int sid)
{
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000000, 1<<2);
}

// reset timer
void TCBIBSresetTIMER(int sid)
{
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000000, 1);
}

// start data acquisition
void TCBIBSstart(int sid)
{
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000000, 1<<3);
}

// start calibration acquisition
void TCBIBSstartCAL(int sid)
{
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000000, 1<<4);
}

// stop data acquisition
void TCBIBSstop(int sid)
{
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000000, 0<<3);
}

// read RUN status
unsigned long TCBIBSread_RUN(int sid, unsigned long mid)
{
  unsigned long data;
  unsigned long addr = 0x20000000;

  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write coincidence window
void TCBIBSwrite_CW(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x20000001;

  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_CW(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x20000001;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write segment setting
void TCBIBSwrite_RL(int sid, unsigned long mid, unsigned long data)
{
  unsigned long addr = 0x20000002;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_RL(int sid, unsigned long mid)
{
  unsigned long data;
  unsigned long addr = 0x20000002;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// turn on/off DRAM
// 0 = off, 1 = on
void TCBIBSwrite_DRAMON(int sid, unsigned long mid, unsigned long data)
{
  unsigned long addr = 0x20000003;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_DRAMON(int sid, unsigned long mid)
{
  unsigned long data;
  unsigned long addr = 0x20000003;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write offset adjustment
void TCBIBSwrite_DACOFF(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x20000004;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
  sleep(1);
}
unsigned long TCBIBSread_DACOFF(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x20000004;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// measure pedestal
void TCBIBSmeasure_PED(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long addr = 0x20000005;

  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;

  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, 0);
}
unsigned long TCBIBSread_PED(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x20000006;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write input delay
void TCBIBSwrite_DLY(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x20000007;
  unsigned long value;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  value = ((data / 1000) << 10) | (data % 1000);

  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, value);
}
unsigned long TCBIBSread_DLY(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long value;
  unsigned long data;
  unsigned long addr = 0x20000007;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  value = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  data = (value >> 10)*1000 + (value&0X3FF);

  return data;
}

// write discriminator threshold, when setting TDC threshold put ch = ch + 4
void TCBIBSwrite_THR(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x20000008;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_THR(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x20000008;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write input pulse polarity, when setting TDC polarity put ch = ch + 4, TDC polarity should be same for all ch
void TCBIBSwrite_POL(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x20000009;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_POL(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x20000009;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write pulse sum trigger width
void TCBIBSwrite_PSW(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x2000000A;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_PSW(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x2000000A;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write ADC mode
void TCBIBSwrite_AMODE(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x2000000B;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_AMODE(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x2000000B;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write pulse count threshold
void TCBIBSwrite_PCT(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x2000000C;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_PCT(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x2000000C;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write pulse count interval
void TCBIBSwrite_PCI(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x2000000D;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_PCI(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x2000000D;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write pulse width threshold
void TCBIBSwrite_PWT(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x2000000E;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_PWT(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x2000000E;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write deadtime
void TCBIBSwrite_DT(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x2000000F;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_DT(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x2000000F;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write trigger mode
void TCBIBSwrite_TM(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x20000014;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_TM(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x20000014;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write trigger lookup table
void TCBIBSwrite_TLT(int sid, unsigned long mid, unsigned long data)
{
  unsigned long addr = 0x20000015;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_TLT(int sid, unsigned long mid)
{
  unsigned long data;
  unsigned long addr = 0x20000015;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write zero suppression
void TCBIBSwrite_ZEROSUP(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x20000016;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_ZEROSUP(int sid, unsigned long mid, unsigned long ch)
{
  unsigned long data;
  unsigned long addr = 0x20000016;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// send ADC reset signal
void TCBIBSsend_ADCRST(int sid, unsigned long mid)
{
  unsigned long addr = 0x20000017;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, 0);
}

// send ADC calibration signal
void TCBIBSsend_ADCCAL(int sid, unsigned long mid)
{
  unsigned long addr = 0x20000018;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, 0);
}

// write ADC calibration delay
void TCBIBSwrite_ADCDLY(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
  unsigned long addr = 0x20000019;
  if(mid>0)
    addr += ((ch-1) & 0xFF) << 16;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}

// write ADC align delay
void TCBIBSwrite_ADCALIGN(int sid, unsigned long mid, unsigned long data)
{
  unsigned long addr = 0x2000001A;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}

// read ADC status
unsigned long TCBIBSread_ADCSTAT(int sid, unsigned long mid)
{
  unsigned long data;
  unsigned long addr = 0x2000001A;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// write zerosuppression flag duration (in ns 8 ~ 65532)
void TCBIBSwrite_ZSFD(int sid, unsigned long mid, unsigned long data)
{
  unsigned long addr = 0x2000001E;
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr, data);
}
unsigned long TCBIBSread_ZSFD(int sid, unsigned long mid)
{
  unsigned long data;
  unsigned long addr = 0x2000001E;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, mid, addr);
  return data;
}

// align ADC for NKFADC500
void TCBIBS_ADCALIGN(int sid, unsigned long mid)
{
  unsigned long ch, dly, value;
  int count, sum, center;
  unsigned long gdly;
  int flag;

  TCBIBSsend_ADCRST(sid, mid);
  usleep(500000);
  TCBIBSsend_ADCCAL(sid, mid);
  TCBIBSwrite_ADCALIGN(sid, mid, 1);

  for (ch = 1; ch <= 4; ch++) {
    count = 0;
    sum = 0;
    flag = 0;

    for (dly = 0; dly < 32; dly++) {
      TCBIBSwrite_ADCDLY(sid, mid, ch, dly);
      value = (TCBIBSread_ADCSTAT(sid, mid) >> (ch -1)) & 0x1;

      // count bad delay
      if (!value) {
        flag = 1;
        count = count + 1;
        sum = sum + dly;
      }
      else {
        if (flag)
          dly = 32;
      }
    }

    // get bad delay center
    center = sum / count;

    // set good delay
    if (center < 11)
      gdly = center + 11;
    else
      gdly = center - 11;

    // set delay
    TCBIBSwrite_ADCDLY(sid, mid, ch, gdly);
    printf("ch%ld calibration delay = %ld\n", ch, gdly);
  }

  TCBIBSwrite_ADCALIGN(sid, mid, 0);
  TCBIBSsend_ADCCAL(sid, mid);
}

// write run number ; TCBIBS
void TCBIBSwrite_RUNNO(int sid, unsigned long data)
{
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000002, data);
}
unsigned long TCBIBSread_RUNNO(int sid)
{
  unsigned long data;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000002);
  return data;
}

// write trigger delay ; TCBIBS
void TCBIBSwrite_TRIGDLY(int sid, unsigned long data)
{
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000003, data);
}
unsigned long TCBIBSread_TRIGDLY(int sid)
{
  unsigned long data;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000003);
  return data;
}

// send trigger ; TCBIBS
void TCBIBSsend_TRIG(int sid)
{
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000004, 0);
}

// read link status ; TCBIBS
void TCBIBSread_LNSTAT(int sid, unsigned long *data)
{
  unsigned long addr = 0x20000005;
  unsigned char rdat[8];
  unsigned long ltmp;
  int i;

  USB3TCBRead(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 2, addr, rdat);
  for (i=0; i <2; i++) {
    data[i] = rdat[i * 4] & 0xFF;
    ltmp = rdat[i * 4 + 1] & 0xFF;
    data[i] = data[i] + (unsigned long)(ltmp << 8);
    ltmp = rdat[i * 4 + 2] & 0xFF;
    data[i] = data[i] + (unsigned long)(ltmp << 16);
    ltmp = rdat[i * 4 + 3] & 0xFF;
    data[i] = data[i] + (unsigned long)(ltmp << 24);
  }
}

// read mids ; TCBIBS
void TCBIBSread_MIDS(int sid, unsigned long *data)
{
  unsigned long addr = 0x20000007;
  unsigned char rdat[160];
  unsigned long ltmp;
  int i;

  USB3TCBRead(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 40, addr, rdat);
  for (i = 0; i < 40; i ++) {
    data[i] = rdat[i * 4] & 0xFF;
    ltmp = rdat[i * 4 + 1] & 0xFF;
    data[i] = data[i] + (unsigned long)(ltmp << 8);
    ltmp = rdat[i * 4 + 2] & 0xFF;
    data[i] = data[i] + (unsigned long)(ltmp << 16);
    ltmp = rdat[i * 4 + 3] & 0xFF;
    data[i] = data[i] + (unsigned long)(ltmp << 24);
  }
}

// write pedestal trigger interval in ms; TCBIBS
void TCBIBSwrite_PTRIG(int sid, unsigned long data)
{
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x2000002F, data);
}
unsigned long TCBIBSread_PTRIG(int sid)
{
  unsigned long data;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x2000002F);
  return data;
}

// write multiplicity threshold
void TCBIBSwrite_MTHR(int sid, unsigned long data)
{
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000031, data);
}
unsigned long TCBIBSread_MTHR(int sid)
{
  unsigned long data;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000031);
  return data;
}

// write trigger prescale
void TCBIBSwrite_PSCALE(int sid, unsigned long data)
{
  USB3TCBWrite(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000032, data);
}
unsigned long TCBIBSread_PSCALE(int sid)
{
  unsigned long data;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x20000032);
  return data;
}

// read block counts of data, 1 buffer count = 1 kbyte ; TCBIBS
unsigned long TCBIBSread_BCOUNT(int sid)
{
  unsigned long data;
  data = USB3TCBReadReg(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, 0x30000000);
  return data;
}

// read data, reads bcount * 1KB ; TCBIBS
void TCBIBSread_DATA(int sid, unsigned long bcount, unsigned char* data)
{
  unsigned long count = bcount * 256;
  USB3TCBRead(TCBIBS_VENDOR_ID, TCBIBS_PRODUCT_ID, sid, 0, count, 0x40000000, data);
}
