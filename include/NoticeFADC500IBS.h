
#ifndef FADC500IBS_H
#define FADC500IBS_H

#include <libusb.h>
#ifdef __cplusplus
extern "C" {
#endif

#define FADC500IBS_VENDOR_ID (0x0547)
#define FADC500IBS_PRODUCT_ID (0x1308)

extern int FADC500IBSopen(int sid, libusb_context *ctx);
extern void FADC500IBSclose(int sid);
extern unsigned long FADC500IBSread_BCOUNT(int sid);
extern void FADC500IBSread_DATA(int sid, double bcount, unsigned char *data);

#ifdef __cplusplus
}
#endif

#endif
