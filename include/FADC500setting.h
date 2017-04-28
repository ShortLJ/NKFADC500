#ifndef FADC500setting_H
#define FADC500setting_H

#include <unistd.h>
#include <stdio.h>
#include "TStyle.h"


class FADC500setting
{
	public:
		int module_count;
		int sid = 0;				//TCB USB3 SID
		unsigned long mid[40];			//NKFADC500 mid found by TCB
		unsigned long ptrig_interval;	//pedestal trigger interval in ms, 00 for disable
		unsigned long rl[6];			//recording length: 1=128ns, 2=256ns, 4=512ns, 8=1us, 16=2us, 32=4us, 64=8us, 128=16us, 256=32us
		unsigned long tlt[6];			//trigger lookup table value
		unsigned long trigdly;			//tcb trigger delay in ns
		unsigned long cw_tcb;		//tcb coincidence width (8~32760)
		unsigned long cw[6][4];		//coincidence width (8~32760)
		unsigned long offset[6][4];			//ADC offset value (0~4095)
		unsigned long dly[6][4];			//ADC waveform delay from trigger (0~31992)
		unsigned long thr[6][4];			//ADC threshold 1 cbt ~ 0.5mV
		unsigned long tdc_thr[6][4];			//TDC threshold 1cnt ~ 0.5mV
		unsigned long pol[6][4];			//pulse polarity, 0=negative, 1=positive
		unsigned long psw[6][4];			//peak sum width in ns (2~16382)
		unsigned long amode[6][4];		//ADC mode, 0=raw, 1=filtered
		unsigned long pct[6][4];			//pulse count threshold (1~15)
		unsigned long pci[6][4];			//pusle count interval (32~8160 ns)
		unsigned long pwt[6][4];		//pulse width threshold (2 ~ 1022 ns)
		unsigned long dt[6][4];			//trigger deadtime (0 ~ 8355840 ns)
		unsigned long ten;			//when 1 enables pulse count trigger 
		unsigned long tew;			//when 1 enables pulse width trigger
		unsigned long tep;			//when 1 enables peak sum trigger
		unsigned long tep2;			//when 1 enables peak sum OR trigger
		unsigned long zerosup[6][4];		//zero-suppression, 0 = not use, 1 = use
		unsigned long mthr=1;
		unsigned long pscale=1;

		unsigned long data[2];			// to get NKFADC500 mid
		int link_flag;
		int linked[40];
		unsigned long value[40];

		void FADC500ParSetting();

};
#endif

