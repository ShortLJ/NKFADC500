#include "NoticeTCBIBSROOT.h"
#include "NoticeTCBIBS.h"
//#include "libusb.h"

ClassImp(NKTCBIBS)

NKTCBIBS::NKTCBIBS()
{
}

NKTCBIBS::~NKTCBIBS()
{
}

int NKTCBIBS::TCBIBSopen(int sid, libusb_context *ctx)
{
    return ::TCBIBSopen(sid, ctx);
}

void NKTCBIBS::TCBIBSclose(int sid)
{
    ::TCBIBSclose(sid);
}

void NKTCBIBS::TCBIBSwrite_LT(int sid, unsigned long mid, char* data, int len)
{
    ::TCBIBSwrite_LT(sid, mid, data, len);
}

void NKTCBIBS::TCBIBSreset(int sid)
{
    ::TCBIBSreset(sid);
}

void NKTCBIBS::TCBIBSresetTIMER(int sid)
{
    ::TCBIBSresetTIMER(sid);
}

void NKTCBIBS::TCBIBSstart(int sid)
{
    ::TCBIBSstart(sid);
}

void NKTCBIBS::TCBIBSstartCAL(int sid)
{
    ::TCBIBSstartCAL(sid);
}

void NKTCBIBS::TCBIBSstop(int sid)
{
    ::TCBIBSstop(sid);
}

unsigned long NKTCBIBS::TCBIBSread_RUN(int sid, unsigned long mid)
{
    return ::TCBIBSread_RUN(sid, mid);
}

void NKTCBIBS::TCBIBSwrite_CW(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_CW(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_CW(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_CW(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_RL(int sid, unsigned long mid, unsigned long data)
{
    ::TCBIBSwrite_RL(sid, mid, data);
}
unsigned long NKTCBIBS::TCBIBSread_RL(int sid, unsigned long mid)
{
    return ::TCBIBSread_RL(sid, mid);
}

void NKTCBIBS::TCBIBSwrite_DRAMON(int sid, unsigned long mid, unsigned long data)
{
    ::TCBIBSwrite_DRAMON(sid, mid, data);
}

unsigned long NKTCBIBS::TCBIBSread_DRAMON(int sid, unsigned long mid)
{
    return ::TCBIBSread_DRAMON(sid, mid);
}

void NKTCBIBS::TCBIBSwrite_DACOFF(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_DACOFF(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_DACOFF(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_DACOFF(sid, mid, ch);
}

void NKTCBIBS::TCBIBSmeasure_PED(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSmeasure_PED(sid, mid, ch);
}

unsigned long NKTCBIBS::TCBIBSread_PED(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_PED(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_DLY(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_DLY(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_DLY(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_DLY(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_THR(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_THR(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_THR(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_THR(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_POL(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_POL(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_POL(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_POL(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_PSW(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_PSW(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_PSW(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_PSW(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_AMODE(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_AMODE(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_AMODE(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_AMODE(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_PCT(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_PCT(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_PCT(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_PCT(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_PCI(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_PCI(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_PCI(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_PCI(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_PWT(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_PWT(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_PWT(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_PWT(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_DT(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_DT(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_DT(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_DT(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_TM(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_TM(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_TM(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_TM(sid, mid, ch);
}

void NKTCBIBS::TCBIBSwrite_TLT(int sid, unsigned long mid, unsigned long data)
{
    ::TCBIBSwrite_TLT(sid, mid, data);
}
unsigned long NKTCBIBS::TCBIBSread_TLT(int sid, unsigned long mid)
{
    return ::TCBIBSread_TLT(sid, mid);
}

void NKTCBIBS::TCBIBSwrite_ZEROSUP(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_ZEROSUP(sid, mid, ch, data);
}
unsigned long NKTCBIBS::TCBIBSread_ZEROSUP(int sid, unsigned long mid, unsigned long ch)
{
    return ::TCBIBSread_ZEROSUP(sid, mid, ch);
}

void NKTCBIBS::TCBIBSsend_ADCRST(int sid, unsigned long mid)
{
    ::TCBIBSsend_ADCRST(sid, mid);
}

void NKTCBIBS::TCBIBSsend_ADCCAL(int sid, unsigned long mid)
{
    ::TCBIBSsend_ADCCAL(sid, mid);
}

void NKTCBIBS::TCBIBSwrite_ADCDLY(int sid, unsigned long mid, unsigned long ch, unsigned long data)
{
    ::TCBIBSwrite_ADCDLY(sid, mid, ch, data);
}

void NKTCBIBS::TCBIBSwrite_ADCALIGN(int sid, unsigned long mid, unsigned long data)
{
    ::TCBIBSwrite_ADCALIGN(sid, mid, data);
}

unsigned long NKTCBIBS::TCBIBSread_ADCSTAT(int sid, unsigned long mid)
{
    return ::TCBIBSread_ADCSTAT(sid, mid);
}

void NKTCBIBS::TCBIBSwrite_ZSFD(int sid, unsigned long mid, unsigned long data)
{
    ::TCBIBSwrite_ZSFD(sid, mid, data);
}

unsigned long NKTCBIBS::TCBIBSread_ZSFD(int sid, unsigned long mid)
{
    return ::TCBIBSread_ZSFD(sid, mid);
}

void NKTCBIBS::TCBIBS_ADCALIGN(int sid, unsigned long mid)
{
	::TCBIBS_ADCALIGN(sid, mid);
}

void NKTCBIBS::TCBIBSwrite_RUNNO(int sid, unsigned long data)
{
    ::TCBIBSwrite_RUNNO(sid, data);
}

unsigned long NKTCBIBS::TCBIBSread_RUNNO(int sid)
{
    return ::TCBIBSread_RUNNO(sid);
}

void NKTCBIBS::TCBIBSwrite_TRIGDLY(int sid, unsigned long data)
{
    ::TCBIBSwrite_TRIGDLY(sid, data);
}

unsigned long NKTCBIBS::TCBIBSread_TRIGDLY(int sid)
{
    return ::TCBIBSread_TRIGDLY(sid);
}

void NKTCBIBS::TCBIBSsend_TRIG(int sid)
{
    ::TCBIBSsend_TRIG(sid);
}

void NKTCBIBS::TCBIBSread_LNSTAT(int sid, unsigned long *data)
{
    ::TCBIBSread_LNSTAT(sid, data);
}

void NKTCBIBS::TCBIBSread_MIDS(int sid, unsigned long *data)
{
    ::TCBIBSread_MIDS(sid, data);
}

void NKTCBIBS::TCBIBSwrite_PTRIG(int sid, unsigned long data)
{
    ::TCBIBSwrite_PTRIG(sid, data);
}

unsigned long NKTCBIBS::TCBIBSread_PTRIG(int sid)
{
    return ::TCBIBSread_PTRIG(sid);
}

void NKTCBIBS::TCBIBSwrite_MTHR(int sid, unsigned long data)
{
    ::TCBIBSwrite_MTHR(sid, data);
}

unsigned long NKTCBIBS::TCBIBSread_MTHR(int sid)
{
    return ::TCBIBSread_MTHR(sid);
}

void NKTCBIBS::TCBIBSwrite_PSCALE(int sid, unsigned long data)
{
    ::TCBIBSwrite_PSCALE(sid, data);
}

unsigned long NKTCBIBS::TCBIBSread_PSCALE(int sid)
{
    return ::TCBIBSread_PSCALE(sid);
}

unsigned long NKTCBIBS::TCBIBSread_BCOUNT(int sid)
{
    return ::TCBIBSread_BCOUNT(sid);
}

void NKTCBIBS::TCBIBSread_DATA(int sid, unsigned long bcount, unsigned char *data)
{
    ::TCBIBSread_DATA(sid, bcount, data);
}
