/************************************************************
NKFADC500 GUI system
Made by Byul Moon.
FADC500setting.cc source file
Save setting parameters to TCB module.
May. 1. 2017.
***********************************************************/

#include <unistd.h>
#include <stdio.h>
#include "TSystem.h"
#include "FADC500setting.h"
#include "FADC500run.h"
#include "usb3tcbroot.h"
#include "NoticeTCBIBSROOT.h"
#include "NoticeFADC500IBSROOT.h"

void FADC500setting::FADC500ParSetting()
{
	unsigned long tmode = (tep2<<3) | (tep<<2) | (tew<<1) | ten;
	const int nch = 4;
	gSystem->Load("libusb3tcbroot.so");
	gSystem->Load("libNoticeTCBIBSROOT.so");

	usb3tcbroot *usb = new usb3tcbroot;
	usb->USB3TCBInit(0);

	NKTCBIBS *tcb = new NKTCBIBS;
	tcb->TCBIBSopen(sid, 0);
	tcb->TCBIBSread_LNSTAT(sid, data);

	for (int i = 0; i < 32; i++)	linked[i] = (data[0] >> i) & 0x01;

	for (int i = 0; i < 8; i++)		linked[i + 32] = (data[1] >> i) & 0x01;

	tcb->TCBIBSread_MIDS(sid, value);

	link_flag = 0;
	module_count = 0;
	for (int i = 0; i < 40; i++)
	{
		if (linked[i])
		{
			link_flag = 1;
			mid[module_count] = value[i];
			printf("FADC500-IBS(Module ID = %lX) found @ %d\n", value[i], i + 1);
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
	tcb->TCBIBSwrite_RUNNO(sid, run_num);
	printf("TCBIBS run number = %ld\n", tcb->TCBIBSread_RUNNO(sid));
	printf("TCBIBS trigger delay = %ld\n", tcb->TCBIBSread_TRIGDLY(sid));
	printf("TCBIBS pedestal trigger interval = %ld ms\n", tcb->TCBIBSread_PTRIG(sid));
	printf("TCBIBS multiplicity = %ld\n", tcb->TCBIBSread_MTHR(sid));
	printf("TCBIBS prescale = %ld\n", tcb->TCBIBSread_PSCALE(sid));
	printf("TCBIBS trigger coincidence window = %ld\n", tcb->TCBIBSread_CW(sid, 0, 1));

	for (int i = 0; i < module_count; i++)
	{
		printf("Setting module, Module ID = %ld\n", mid[i]);

		tcb->TCBIBS_ADCALIGN(sid, mid[i]);
		tcb->TCBIBSwrite_RL(sid, mid[i], rl[i]);
		tcb->TCBIBSwrite_TLT(sid, mid[i], tlt[i]);
		tcb->TCBIBSwrite_DRAMON(sid, mid[i], 1);

		printf("Data length = %ld\n", tcb->TCBIBSread_RL(sid, mid[i]));
		printf("Trigger type = %lX\n", tcb->TCBIBSread_TLT(sid, mid[i]));
		printf("DRAM ON = %ld\n", tcb->TCBIBSread_DRAMON(sid, mid[i]));

		for (int j = 0; j < nch; j++)
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

		for (int j = 0; j < nch; j++)
		{
			printf("ch%d coincidence window = %ld\n", j+1, tcb->TCBIBSread_CW(sid, mid[i], j+1));
			printf("ch%d ADC offset = %ld\n", j+1, tcb->TCBIBSread_DACOFF(sid, mid[i], j+1));
			printf("ch%d ADC delay = %ld\n", j+1, tcb->TCBIBSread_DLY(sid, mid[i], j+1));
			printf("ch%d ADC threshold = %ld\n", j+1, tcb->TCBIBSread_THR(sid, mid[i], j+1));
			printf("ch%d TDC threshold = %ld\n", j+1, tcb->TCBIBSread_THR(sid, mid[i], j+5));
			printf("ch%d pulse polarity = %ld\n", j+1, tcb->TCBIBSread_POL(sid, mid[i], j+1));
			printf("ch%d pulse sum width = %ld\n", j+1, tcb->TCBIBSread_PSW(sid, mid[i], j+1));
			printf("ch%d ADC mode = %ld\n", j+1, tcb->TCBIBSread_AMODE(sid, mid[i], j+1));
			printf("ch%d pulse count threshold = %ld\n", j+1, tcb->TCBIBSread_PCT(sid, mid[i], j+1));
			printf("ch%d pulse count interval = %ld\n", j+1, tcb->TCBIBSread_PCI(sid, mid[i], j+1));
			printf("ch%d pulse width threshold = %ld\n", j+1, tcb->TCBIBSread_PWT(sid, mid[i], j+1));
			printf("ch%d deadtime = %ld\n", j+1, tcb->TCBIBSread_DT(sid, mid[i], j+1));
			printf("ch%d trigger mode = %ld\n", j+1, tcb->TCBIBSread_TM(sid, mid[i], j+1));
			printf("ch%d zerosuppression = %ld\n", j+1, tcb->TCBIBSread_ZEROSUP(sid, mid[i], j+1));
			printf("ch%d pedestal = %ld\n", j+1, tcb->TCBIBSread_PED(sid, mid[i], j+1));
		}
		printf("TDC pulse polarity = %ld\n", tcb->TCBIBSread_POL(sid, mid[i], 5));
		printf("zero suppression flag duration = %ld\n", tcb->TCBIBSread_ZSFD(sid, mid[i]));
	}
	tcb->TCBIBSreset(sid);
	tcb->TCBIBSstart(sid);

	tcb->TCBIBSclose(sid);
	usb->USB3TCBExit(0);
	printf("All parameter setting has been successfully finished.\n");

	delete usb;
	delete tcb;
}
