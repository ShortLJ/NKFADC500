#include <unistd.h>
#include <stdio.h>
#include "TStyle.h"
#include "TSystem.h"
#include "FADC500setting.h"
#include "usb3tcbroot.h"
#include "NoticeTCBIBSROOT.h"
#include "NoticeFADC500IBSROOT.h"

void FADC500setting::FADC500ParSetting()
{
	unsigned long tmode = (tep2<<3) | (tep<<2) | (tew<<1) | ten;
	gSystem->Load("libusb3tcbroot.so");
	gSystem->Load("libNoticeTCBIBSROOT.so");

	usb3tcbroot *usb = new usb3tcbroot;
	usb->USB3TCBInit(0);

	NKTCBIBS *tcb = new NKTCBIBS;
	tcb->TCBIBSopen(sid, 0);
	tcb->TCBIBSread_LNSTAT(sid, data);

	for (int i = 0; i < 32; i++)
		linked[i] = (data[0] >> i) & 0x01;

	for (int i = 0; i < 8; i++)
		linked[i + 32] = (data[1] >> i) & 0x01;

	tcb->TCBIBSread_MIDS(sid, value);

	link_flag = 0;
	module_count = 0;
	for (int i = 0; i < 40; i++)
	{
		if (linked[i])
		{
			link_flag = 1;
			mid[module_count] = value[i];
			printf("FADC500-IBS(mid = %lX) found @ %d\n", value[i], i + 1);
			module_count = module_count + 1;
		}
	}

	if (link_flag == 0) 
	{
		tcb->TCBIBSclose(sid);
		usb->USB3TCBExit(0);
	}

	tcb->TCBIBSreset(sid);
	tcb->TCBIBSwrite_TRIGDLY(sid, trigdly);
	tcb->TCBIBSwrite_PTRIG(sid, ptrig_interval);
	tcb->TCBIBSwrite_MTHR(sid, mthr);
	tcb->TCBIBSwrite_PSCALE(sid, pscale);
	tcb->TCBIBSwrite_CW(sid, 0, 1, cw_tcb);

	for (int i = 0; i < module_count; i++)
	{
		printf("setting module, mid = %ld\n", mid[i]);

		tcb->TCBIBS_ADCALIGN(sid, mid[i]);
		tcb->TCBIBSwrite_RL(sid, mid[i], rl[i]);
		tcb->TCBIBSwrite_TLT(sid, mid[i], tlt[i]);
		tcb->TCBIBSwrite_DRAMON(sid, mid[i], 1);

		printf("TCBIBS trigger delay = %ld\n", tcb->TCBIBSread_TRIGDLY(sid));
		printf("TCBIBS pedestal trigger interval = %ld ms\n", tcb->TCBIBSread_PTRIG(sid));
		printf("TCBIBS multiplicity = %ld\n", tcb->TCBIBSread_MTHR(sid));
		printf("TCBIBS prescale = %ld\n", tcb->TCBIBSread_PSCALE(sid));
		printf("TCBIBS cw = %ld\n", tcb->TCBIBSread_CW(sid, 0, 1));
		printf("rl = %ld\n", tcb->TCBIBSread_RL(sid, mid[i]));
		printf("tlt = %lX\n", tcb->TCBIBSread_TLT(sid, mid[i]));
		printf("dramon = %ld\n", tcb->TCBIBSread_DRAMON(sid, mid[i]));

		for (int j = 0; j < 4; j++)
		{
			tcb->TCBIBSwrite_CW(sid, mid[i], j+1, cw[i][j]);
			tcb->TCBIBSwrite_DACOFF(sid, mid[i], j+1, offset[i][j]);
			tcb->TCBIBSmeasure_PED(sid, mid[i], j+1);
			tcb->TCBIBSwrite_DLY(sid, mid[i], j+1, dly[i][j]);
			tcb->TCBIBSwrite_THR(sid, mid[i], j+1, thr[i][j]);
			tcb->TCBIBSwrite_THR(sid, mid[i], j+5, tdc_thr[i][j]);
			tcb->TCBIBSwrite_POL(sid, mid[i], j+1, pol[i][j]);
			tcb->TCBIBSwrite_PSW(sid, mid[i], j+1, psw[i][j]);
			tcb->TCBIBSwrite_AMODE(sid, mid[i], j+1, amode[i][j]);
			tcb->TCBIBSwrite_PCT(sid, mid[i], j+1, pct[i][j]);
			tcb->TCBIBSwrite_PCI(sid, mid[i], j+1, pci[i][j]);
			tcb->TCBIBSwrite_PWT(sid, mid[i], j+1, pwt[i][j]);
			tcb->TCBIBSwrite_DT(sid, mid[i], j+1, dt[i][j]);
			tcb->TCBIBSwrite_ZEROSUP(sid, mid[i], j+1, zerosup[i][j]);
			tcb->TCBIBSwrite_TM(sid, mid[i], j+1, tmode);
		}
		tcb->TCBIBSwrite_POL(sid, mid[i], 5, pol[i][0]);
		tcb->TCBIBSwrite_ZSFD(sid, mid[i], 1000);

		printf("ch1 cw = %ld\n", tcb->TCBIBSread_CW(sid, mid[i], 1));
		printf("ch2 cw = %ld\n", tcb->TCBIBSread_CW(sid, mid[i], 2));
		printf("ch3 cw = %ld\n", tcb->TCBIBSread_CW(sid, mid[i], 3));
		printf("ch4 cw = %ld\n", tcb->TCBIBSread_CW(sid, mid[i], 4));
		printf("ch1 offset = %ld\n", tcb->TCBIBSread_DACOFF(sid, mid[i], 1));
		printf("ch2 offset = %ld\n", tcb->TCBIBSread_DACOFF(sid, mid[i], 2));
		printf("ch3 offset = %ld\n", tcb->TCBIBSread_DACOFF(sid, mid[i], 3));
		printf("ch4 offset = %ld\n", tcb->TCBIBSread_DACOFF(sid, mid[i], 4));
		printf("ch1 dly = %ld\n", tcb->TCBIBSread_DLY(sid, mid[i], 1));
		printf("ch2 dly = %ld\n", tcb->TCBIBSread_DLY(sid, mid[i], 2));
		printf("ch3 dly = %ld\n", tcb->TCBIBSread_DLY(sid, mid[i], 3));
		printf("ch4 dly = %ld\n", tcb->TCBIBSread_DLY(sid, mid[i], 4));
		printf("ch1 thr = %ld\n", tcb->TCBIBSread_THR(sid, mid[i], 1));
		printf("ch2 thr = %ld\n", tcb->TCBIBSread_THR(sid, mid[i], 2));
		printf("ch3 thr = %ld\n", tcb->TCBIBSread_THR(sid, mid[i], 3));
		printf("ch4 thr = %ld\n", tcb->TCBIBSread_THR(sid, mid[i], 4));
		printf("ch1 TDC thr = %ld\n", tcb->TCBIBSread_THR(sid, mid[i], 5));
		printf("ch2 TDC thr = %ld\n", tcb->TCBIBSread_THR(sid, mid[i], 6));
		printf("ch3 TDC thr = %ld\n", tcb->TCBIBSread_THR(sid, mid[i], 7));
		printf("ch4 TDC thr = %ld\n", tcb->TCBIBSread_THR(sid, mid[i], 8));
		printf("ch1 pol = %ld\n", tcb->TCBIBSread_POL(sid, mid[i], 1));
		printf("ch2 pol = %ld\n", tcb->TCBIBSread_POL(sid, mid[i], 2));
		printf("ch3 pol = %ld\n", tcb->TCBIBSread_POL(sid, mid[i], 3));
		printf("ch4 pol = %ld\n", tcb->TCBIBSread_POL(sid, mid[i], 4));
		printf("TDC pol = %ld\n", tcb->TCBIBSread_POL(sid, mid[i], 5));
		printf("ch1 psw = %ld\n", tcb->TCBIBSread_PSW(sid, mid[i], 1));
		printf("ch2 psw = %ld\n", tcb->TCBIBSread_PSW(sid, mid[i], 2));
		printf("ch3 psw = %ld\n", tcb->TCBIBSread_PSW(sid, mid[i], 3));
		printf("ch4 psw = %ld\n", tcb->TCBIBSread_PSW(sid, mid[i], 4));
		printf("ch1 amode = %ld\n", tcb->TCBIBSread_AMODE(sid, mid[i], 1));
		printf("ch2 amode = %ld\n", tcb->TCBIBSread_AMODE(sid, mid[i], 2));
		printf("ch3 amode = %ld\n", tcb->TCBIBSread_AMODE(sid, mid[i], 3));
		printf("ch4 amode = %ld\n", tcb->TCBIBSread_AMODE(sid, mid[i], 4));
		printf("ch1 pct = %ld\n", tcb->TCBIBSread_PCT(sid, mid[i], 1));
		printf("ch2 pct = %ld\n", tcb->TCBIBSread_PCT(sid, mid[i], 2));
		printf("ch3 pct = %ld\n", tcb->TCBIBSread_PCT(sid, mid[i], 3));
		printf("ch4 pct = %ld\n", tcb->TCBIBSread_PCT(sid, mid[i], 4));
		printf("ch1 pci = %ld\n", tcb->TCBIBSread_PCI(sid, mid[i], 1));
		printf("ch2 pci = %ld\n", tcb->TCBIBSread_PCI(sid, mid[i], 2));
		printf("ch3 pci = %ld\n", tcb->TCBIBSread_PCI(sid, mid[i], 3));
		printf("ch4 pci = %ld\n", tcb->TCBIBSread_PCI(sid, mid[i], 4));
		printf("ch1 pwt = %ld\n", tcb->TCBIBSread_PWT(sid, mid[i], 1));
		printf("ch2 pwt = %ld\n", tcb->TCBIBSread_PWT(sid, mid[i], 2));
		printf("ch3 pwt = %ld\n", tcb->TCBIBSread_PWT(sid, mid[i], 3));
		printf("ch4 pwt = %ld\n", tcb->TCBIBSread_PWT(sid, mid[i], 4));
		printf("ch1 dt = %ld\n", tcb->TCBIBSread_DT(sid, mid[i], 1));
		printf("ch2 dt = %ld\n", tcb->TCBIBSread_DT(sid, mid[i], 2));
		printf("ch3 dt = %ld\n", tcb->TCBIBSread_DT(sid, mid[i], 3));
		printf("ch4 dt = %ld\n", tcb->TCBIBSread_DT(sid, mid[i], 4));
		printf("ch1 tm = %ld\n", tcb->TCBIBSread_TM(sid, mid[i], 1));
		printf("ch2 tm = %ld\n", tcb->TCBIBSread_TM(sid, mid[i], 2));
		printf("ch3 tm = %ld\n", tcb->TCBIBSread_TM(sid, mid[i], 3));
		printf("ch4 tm = %ld\n", tcb->TCBIBSread_TM(sid, mid[i], 4));
		printf("ch1 zerosup = %ld\n", tcb->TCBIBSread_ZEROSUP(sid, mid[i], 1));
		printf("ch2 zerosup = %ld\n", tcb->TCBIBSread_ZEROSUP(sid, mid[i], 2));
		printf("ch3 zerosup = %ld\n", tcb->TCBIBSread_ZEROSUP(sid, mid[i], 3));
		printf("ch4 zerosup = %ld\n", tcb->TCBIBSread_ZEROSUP(sid, mid[i], 4));
		printf("ch1 pedestal = %ld\n", tcb->TCBIBSread_PED(sid, mid[i], 1));
		printf("ch2 pedestal = %ld\n", tcb->TCBIBSread_PED(sid, mid[i], 2));
		printf("ch3 pedestal = %ld\n", tcb->TCBIBSread_PED(sid, mid[i], 3));
		printf("ch4 pedestal = %ld\n", tcb->TCBIBSread_PED(sid, mid[i], 4));

		printf("zero suppression flag duration = %ld\n", tcb->TCBIBSread_ZSFD(sid, mid[i]));
	}
	tcb->TCBIBSreset(sid);
	tcb->TCBIBSstart(sid);

	tcb->TCBIBSclose(sid);
	usb->USB3TCBExit(0);
	printf("All parameter setting has been successfully finished.\n");
}
