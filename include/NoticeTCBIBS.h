#ifndef TCBIBS_H
#define TCBIBS_H

#define TM_COUNT 		(0x1)
#define TM_WIDTH 		(0x2)
#define TM_PEAKSUM  	(0x4)
#define TM_ORPEAKSUM  	(0x8)

#include <libusb.h>
#ifdef __cplusplus
extern "C" {
#endif

#define TCBIBS_VENDOR_ID (0x0547)
#define TCBIBS_PRODUCT_ID (0x1307)

extern int TCBIBSopen(int sid, libusb_context *ctx);
extern void TCBIBSclose(int sid);

extern void TCBIBSwrite_LT(int sid, unsigned long mid, char* data, int len);
extern void TCBIBSreset(int sid);
extern void TCBIBSresetTIMER(int sid);
extern void TCBIBSstart(int sid);
extern void TCBIBSstartCAL(int sid);
extern void TCBIBSstop(int sid);
extern unsigned long TCBIBSread_RUN(int sid, unsigned long mid);
extern void TCBIBSwrite_CW(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_CW(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_RL(int sid, unsigned long mid, unsigned long data);
extern unsigned long TCBIBSread_RL(int sid, unsigned long mid);
extern void TCBIBSwrite_DRAMON(int sid, unsigned long mid, unsigned long data);
extern unsigned long TCBIBSread_DRAMON(int sid, unsigned long mid);
extern void TCBIBSwrite_DACOFF(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_DACOFF(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSmeasure_PED(int sid, unsigned long mid, unsigned long ch);
extern unsigned long TCBIBSread_PED(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_DLY(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_DLY(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_THR(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_THR(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_POL(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_POL(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_PSW(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_PSW(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_AMODE(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_AMODE(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_PCT(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_PCT(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_PCI(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_PCI(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_PWT(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_PWT(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_DT(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_DT(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_TM(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_TM(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSwrite_TLT(int sid, unsigned long mid, unsigned long data);
extern unsigned long TCBIBSread_TLT(int sid, unsigned long mid);
extern void TCBIBSwrite_ZEROSUP(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long TCBIBSread_ZEROSUP(int sid, unsigned long mid, unsigned long ch);
extern void TCBIBSsend_ADCRST(int sid, unsigned long mid);
extern void TCBIBSsend_ADCCAL(int sid, unsigned long mid);
extern void TCBIBSwrite_ADCDLY(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern void TCBIBSwrite_ADCALIGN(int sid, unsigned long mid, unsigned long data);
extern unsigned long TCBIBSread_ADCSTAT(int sid, unsigned long mid);
extern void TCBIBSwrite_ZSFD(int sid, unsigned long mid, unsigned long data);
extern unsigned long TCBIBSread_ZSFD(int sid, unsigned long mid);

// utility functions
extern void TCBIBS_ADCALIGN(int sid, unsigned long mid);

extern void TCBIBSwrite_RUNNO(int sid, unsigned long data);
extern unsigned long TCBIBSread_RUNNO(int sid);
extern void TCBIBSwrite_TRIGDLY(int sid, unsigned long data);
extern unsigned long TCBIBSread_TRIGDLY(int sid);
extern void TCBIBSsend_TRIG(int sid);
extern void TCBIBSread_LNSTAT(int sid, unsigned long *data);
extern void TCBIBSread_MIDS(int sid, unsigned long *data);
extern void TCBIBSwrite_PTRIG(int sid, unsigned long data);
extern unsigned long TCBIBSread_PTRIG(int sid);
extern void TCBIBSwrite_MTHR(int sid, unsigned long data);
extern unsigned long TCBIBSread_MTHR(int sid);
extern void TCBIBSwrite_PSCALE(int sid, unsigned long data);
extern unsigned long TCBIBSread_PSCALE(int sid);
extern unsigned long TCBIBSread_BCOUNT(int sid);
extern void TCBIBSread_DATA(int sid, unsigned long bcount, unsigned char *data);

#ifdef __cplusplus
}
#endif

#endif
