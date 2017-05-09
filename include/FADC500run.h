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
#include "usb3tcbroot.h"
#include "usb3comroot.h"
#include "NoticeTCBIBSROOT.h"
#include "NoticeFADC500IBSROOT.h"

#define PC_DRAM_SIZE      10                           // available PC DRAM size in Mbyte
#define DATA_ARRAY_SIZE   PC_DRAM_SIZE*1024*1024       // array size in byte
#define CHUNK_SIZE        PC_DRAM_SIZE*1024            // array size in kilobyte


class FADC500run
{
	private:
		unsigned char data[16384];
		unsigned char data1[128][128];      // raw data array
		unsigned char data2[64][256];      // raw data array
		unsigned char data4[32][512];      // raw data array
		unsigned char data8[16][1024];      // raw data array
		unsigned char data16[8][2048];      // raw data array
		unsigned char data32[4][4096];      // raw data array
		unsigned char data64[2][8192];      // raw data array
		unsigned char data128[16384];      // raw data array
		unsigned char data256[32768];      // raw data array
//		unsigned char data[6][DATA_ARRAY_SIZE];      // raw data array
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
		unsigned long bcount;            // buffer counter	

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

		usb3comroot *usb;
		NKFADC500IBS *fadc;

	public:
		int datasize[6];
		int smid[6];
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
		void Data1(int &sid, int &smid);
		void Data2(int &sid, int &smid);
		void Data4(int &sid, int &smid);
		void Data8(int &sid, int &smid);
		void Data16(int &sid, int &smid);
		void Data32(int &sid, int &smid);
		void Data64(int &sid, int &smid);
		void Data128(int &sid, int &smid);
		void Data256(int &sid, int &smid);
};
#endif

