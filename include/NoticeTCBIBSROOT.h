#ifndef TCBIBSROOT_H
#define TCBIBSROOT_H

#include "TObject.h"
//#include "nkusbconst.hh"

struct libusb_context;
//struct libusb_device;
//struct libusb_device_handle;

class NKTCBIBS : public TObject {
public:

    NKTCBIBS();
    virtual ~NKTCBIBS();

    int TCBIBSopen(int sid, libusb_context *ctx);
    void TCBIBSclose(int sid);
    void TCBIBSwrite_LT(int sid, unsigned long mid, char* data, int len);
    void TCBIBSreset(int sid);
    void TCBIBSresetTIMER(int sid);
    void TCBIBSstart(int sid);
    void TCBIBSstartCAL(int sid);
    void TCBIBSstop(int sid);
    unsigned long TCBIBSread_RUN(int sid, unsigned long mid);

    void TCBIBSwrite_CW(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_CW(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_RL(int sid, unsigned long mid, unsigned long data);
    unsigned long TCBIBSread_RL(int sid, unsigned long mid);
    void TCBIBSwrite_DRAMON(int sid, unsigned long mid, unsigned long data);
    unsigned long TCBIBSread_DRAMON(int sid, unsigned long mid);
    void TCBIBSwrite_DACOFF(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_DACOFF(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSmeasure_PED(int sid, unsigned long mid, unsigned long ch);
    unsigned long TCBIBSread_PED(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_DLY(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_DLY(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_THR(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_THR(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_POL(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_POL(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_PSW(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_PSW(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_AMODE(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_AMODE(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_PCT(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_PCT(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_PCI(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_PCI(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_PWT(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_PWT(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_DT(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_DT(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_TM(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_TM(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSwrite_TLT(int sid, unsigned long mid, unsigned long data);
    unsigned long TCBIBSread_TLT(int sid, unsigned long mid);
    void TCBIBSwrite_ZEROSUP(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    unsigned long TCBIBSread_ZEROSUP(int sid, unsigned long mid, unsigned long ch);
    void TCBIBSsend_ADCRST(int sid, unsigned long mid);
    void TCBIBSsend_ADCCAL(int sid, unsigned long mid);
    void TCBIBSwrite_ADCDLY(int sid, unsigned long mid, unsigned long ch, unsigned long data);
    void TCBIBSwrite_ADCALIGN(int sid, unsigned long mid, unsigned long data);
    unsigned long TCBIBSread_ADCSTAT(int sid, unsigned long mid);
    void TCBIBSwrite_ZSFD(int sid, unsigned long mid, unsigned long data);
    unsigned long TCBIBSread_ZSFD(int sid, unsigned long mid);
    void TCBIBS_ADCALIGN(int sid, unsigned long mid);
    void TCBIBSwrite_RUNNO(int sid, unsigned long data);
    unsigned long TCBIBSread_RUNNO(int sid);
    void TCBIBSwrite_TRIGDLY(int sid, unsigned long data);
    unsigned long TCBIBSread_TRIGDLY(int sid);
    void TCBIBSsend_TRIG(int sid);
    void TCBIBSread_LNSTAT(int sid, unsigned long *data);
    void TCBIBSread_MIDS(int sid, unsigned long *data);
    void TCBIBSwrite_PTRIG(int sid, unsigned long data);
    unsigned long TCBIBSread_PTRIG(int sid);
    void TCBIBSwrite_MTHR(int sid, unsigned long data);
    unsigned long TCBIBSread_MTHR(int sid);
    void TCBIBSwrite_PSCALE(int sid, unsigned long data);
    unsigned long TCBIBSread_PSCALE(int sid);
    unsigned long TCBIBSread_BCOUNT(int sid);
    void TCBIBSread_DATA(int sid, unsigned long bcount, unsigned char *data);

    ClassDef(NKTCBIBS, 0) // NKTCBIBS wrapper class for root
};

#endif
