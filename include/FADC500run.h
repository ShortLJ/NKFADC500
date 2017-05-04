/************************************************************
NKFADC500 GUI system
Made by Byul Moon.
FADC500run.h header file
Run NKFADC500 DAQ and save data.
May. 1. 2017.
***********************************************************/

#ifndef NFADCrun_H
#define NFADCrun_H

#include <unistd.h>
#include <stdio.h>
#include "TCanvas.h"
#include "TH1F.h"

#define PC_DRAM_SIZE      10                           // available PC DRAM size in Mbyte
#define DATA_ARRAY_SIZE   PC_DRAM_SIZE*1024*1024       // array size in byte
#define CHUNK_SIZE        PC_DRAM_SIZE*1024            // array size in kilobyte


class FADC500run
{
	private:
		unsigned char data[6][DATA_ARRAY_SIZE];      // raw data array
		int adc;                         // ADC data
		int tdc;                         // TDC data
		int data_length;                 // data length
		int run_number;                  // run number
		int trigger_type;                // trigger type
		int trigger_destination;         // trigger destination
		int trigger_number;              // trigger number from TCB
		unsigned long ttime;             // trigger time from TCB in ns
		int mid;                         // module id in data packet header
		int channel;                     // channel number of data header
		int local_tnum;                  // local trigger # from fadc500-ibs
		int trigger_pattern;             // trigger pattern from fadc500-ibs
		unsigned long ltime;             // starting time of waveform
		unsigned int evtn;               // event number counter
		unsigned int iEvent;               // event number counter
		unsigned long bcount[6];            // buffer counter	

		int rl;
		int hist_point;                  // number of samples to show
		float hist_range;                // histogram range

		FILE *fp;                        // data file
		int bufcnt;                      // size of buffer data to be read
		int chunk, slice;
		unsigned long ltmp;
		unsigned int itmp;

		unsigned long trig_timel;
		unsigned long trig_timeh;
		unsigned long start_timel;
		unsigned long start_timeh;

		FILE *lfp;

		int i, j, k;


	public:
		int flag;
		int adcflag;
		int tdcflag;
		TCanvas* c1;
		TCanvas* c2;

		TH1F *hoscd1 = 0;
		TH1F *hoscd2 = 0;
		TH1F *hoscd3 = 0;
		TH1F *hoscd4 = 0;

		TH1F *hostd1 = 0;
		TH1F *hostd2 = 0;
		TH1F *hostd3 = 0;
		TH1F *hostd4 = 0;

		int FADC500DAQRun(TString ifilename, int nEvent, int nModule);
};
#endif

