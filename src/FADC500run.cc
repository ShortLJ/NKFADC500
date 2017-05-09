/************************************************************
NKFADC500 GUI system
Made by Byul Moon.
FADC500run.cc source file
Run NKFADC500 DAQ and save data.
May. 1. 2017.
***********************************************************/

#include "TROOT.h"
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "TCanvas.h"
#include "TH1F.h"
#include "FADC500run.h"
#include <vector>
#include "TSystem.h"
#include "TString.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "usb3tcbroot.h"
#include "usb3comroot.h"
#include "NoticeTCBIBSROOT.h"
#include "NoticeFADC500IBSROOT.h"

using namespace std;

#define PC_DRAM_SIZE      10                           // available PC DRAM size in Mbyte
#define DATA_ARRAY_SIZE   PC_DRAM_SIZE*1024*1024       // array size in byte
#define CHUNK_SIZE        PC_DRAM_SIZE*1024            // array size in kilobyte


int FADC500run::FADC500DAQRun(TString ifilename, int nEvent, int nModule)
{
	const int nMod = nModule;
	vector <int> sid;
	for (i = 0; i < nMod; i++)
	{
		sid.push_back(i+1);
		printf("Serial ID : %d\n", sid[i]);
	}

	gSystem->ProcessEvents();
	gSystem->Load("libusb3comroot.so");           // load usb3 library
	gSystem->Load("libNoticeFADC500IBSROOT.so");  // load fadc500ibs library

	usb = new usb3comroot;
	usb->USB3Init(0);

	fadc = new NKFADC500IBS;

	for(i = 0; i< nMod; i++)
	{
		fadc->FADC500IBSopen(sid[i], 0);
	}

	for (i = 0; i < 6; i++)
	{
		cout << "Data size for channel " << i+1 << " : " << datasize[i] << endl;
	}

	TString filename = ifilename;
	TObjArray *decomposedFileNameWithPath = ifilename.Tokenize(".");
	TString filetype = ((TObjString *) decomposedFileNameWithPath -> Last()) -> GetString();
	TString lfilename = ifilename.ReplaceAll(filetype, "log");

	fp = fopen(filename, "wb");
	lfp = fopen(lfilename, "wt");


	flag = 1;
	adcflag = 1;
	tdcflag = 1;
	iEvent = 0;

	while (1)
	{
		gSystem->ProcessEvents();
		for(int imod = 0; imod < nMod; imod++)
		{
			gSystem->ProcessEvents();
			bcount = fadc->FADC500IBSread_BCOUNT(sid[imod]);

			if (bcount)
			{
				if (datasize[smid[imod]] == 128)
				{
					Data1(sid[imod], smid[imod]);
					if (flag == 0)	break;			
					gSystem->ProcessEvents();
				}
				if (datasize[smid[imod]] == 256)
				{
					Data2(sid[imod], smid[imod]);
					if (flag == 0)	break;
					gSystem->ProcessEvents();
				}
				if (datasize[smid[imod]] == 512)
				{
					Data4(sid[imod], smid[imod]);
					if (flag == 0)	break;
					gSystem->ProcessEvents();
				}
				if (datasize[smid[imod]] == 1024)
				{
					Data8(sid[imod], smid[imod]);
					if (flag == 0)	break;
					gSystem->ProcessEvents();
				}
				if (datasize[smid[imod]] == 2048)
				{
					Data16(sid[imod], smid[imod]);
					if (flag == 0)	break;
					gSystem->ProcessEvents();
				}
				if (datasize[smid[imod]] == 4096)
				{
					Data32(sid[imod], smid[imod]);
					if (flag == 0)	break;
					gSystem->ProcessEvents();
				}
				if (datasize[smid[imod]] == 8192)
				{
					Data64(sid[imod], smid[imod]);
					if (flag == 0)	break;
					gSystem->ProcessEvents();
				}
				if (datasize[smid[imod]] == 16384)
				{
					Data128(sid[imod], smid[imod]);
					if (flag == 0)	break;
					gSystem->ProcessEvents();
				}
				if (datasize[smid[imod]] == 32768)
				{
					Data256(sid[imod], smid[imod]);
					if (flag == 0)	break;
					gSystem->ProcessEvents();
				}

			}

			if (flag == 0)	break;			
			gSystem->ProcessEvents();

		}
		iEvent++;
		gSystem->ProcessEvents();

		if (iEvent >= nEvent)	break;
		gSystem->ProcessEvents();

		if (flag == 0)	break;			
		gSystem->ProcessEvents();
	}
	gSystem->ProcessEvents();

	fclose(fp);
	fclose(lfp);
	printf("Data file has been saved.\n");

	for (int imod = 0; imod < nMod; imod++)
	{
		fadc->FADC500IBSclose(sid[imod]);
	}
	usb->USB3Exit(0);

	delete usb;
	delete fadc;

	return 0;

}

void FADC500run::Data1(int &sid, int &smid)
{
	fadc->FADC500IBSread_DATA(sid, 16384/1024, data); //the minimum bcount is 16 kB!!
	for (int ibunch = 0; ibunch < 16384/datasize[smid]; ibunch++)
	{
		printf("Mod[%d] bcount = %ld\n",sid,bcount);
		for (int isize = 0; isize < datasize[smid]; isize++)
		{
			data1[ibunch][isize] = data[ibunch*datasize[smid]+isize];
		}
		gSystem->ProcessEvents();

		fwrite(data1[ibunch], 1, datasize[smid], fp);

		data_length =  data1[ibunch][0] & 0xFF;
		itmp = data1[ibunch][1] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 8);
		itmp = data1[ibunch][2] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 16);
		itmp = data1[ibunch][3] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 24);

		run_number = data1[ibunch][4] & 0xFF;
		itmp = data1[ibunch][5] & 0xFF;
		run_number = run_number + (unsigned int)(itmp << 8);

		trigger_type = data1[ibunch][6] & 0x0F;

		itmp = data1[ibunch][6] & 0xF0;
		trigger_destination = itmp >> 4;

		trigger_number = data1[ibunch][7] & 0xFF;
		itmp = data1[ibunch][8] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 8);
		itmp = data1[ibunch][9] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 16);
		itmp = data1[ibunch][10] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 24);					

		ttime = data1[ibunch][11] & 0xFF;
		ttime = ttime*8;

		ltmp = data1[ibunch][12] & 0xFF;
		ttime = ttime + ltmp * 1000;
		ltmp = data1[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		ttime = ttime + ltmp * 1000;
		ltmp = data1[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		ttime = ttime + ltmp * 1000;

		mid = data1[ibunch][15] & 0xFF;

		channel = data1[ibunch][16] & 0xFF;

		local_tnum = data1[ibunch][17] & 0xFF;
		itmp = data1[ibunch][18] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 8);
		itmp = data1[ibunch][19] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 16);
		itmp = data1[ibunch][20] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 24);

		trigger_pattern = data1[ibunch][21] & 0xFF;
		itmp = data1[ibunch][22] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 8);
		itmp = data1[ibunch][23] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 16);
		itmp = data1[ibunch][24] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 24);

		ltime = data1[ibunch][25] & 0xFF;
		ltime = ltime*8;

		ltmp = data1[ibunch][26] & 0xFF;
		ltime = ltime + ltmp*1000;
		ltmp = data1[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		ltime = ltime + ltmp*1000;
		ltmp = data1[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		ltime = ltime + ltmp*1000;

		trig_timel = data1[ibunch][11] & 0xFF;

		ltmp = data1[ibunch][12] & 0xFF;
		trig_timeh = ltmp;
		ltmp = data1[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		trig_timeh = trig_timeh + ltmp;
		ltmp = data1[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		trig_timeh = trig_timeh + ltmp;

		start_timel = data1[ibunch][25] & 0xFF;

		ltmp = data1[ibunch][26] & 0xFF;
		start_timeh = ltmp;
		ltmp = data1[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		start_timeh = start_timeh + ltmp;
		ltmp = data1[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		start_timeh = start_timeh + ltmp;
		hist_point = (data_length - 32)/2;
		hist_range = hist_point * 2;
		gSystem->ProcessEvents();
		if (adcflag == 1)
		{
			if (hoscd1 == 0)
			{
				hoscd1 = new TH1F("hoscd1", "Channel1", hist_point, 0, hist_range);
				hoscd2 = new TH1F("hoscd2", "Channel2", hist_point, 0, hist_range);
				hoscd3 = new TH1F("hoscd3", "Channel3", hist_point, 0, hist_range);
				hoscd4 = new TH1F("hoscd4", "Channel4", hist_point, 0, hist_range);
				c1->cd(1);
				hoscd1->Draw();
				c1->cd(2);
				hoscd2->Draw();
				c1->cd(3);
				hoscd3->Draw();
				c1->cd(4);
				hoscd4->Draw();
				gSystem->ProcessEvents();
			}

			else
			{
				hoscd1->Reset();
				hoscd2->Reset();
				hoscd3->Reset();
				hoscd4->Reset();

				for (int j=0; j<hist_point; j++)
				{
					adc = data1[ibunch][32+j*2] & 0xFF;
					itmp = data1[ibunch][32+j*2+1] & 0x0F;
					adc = adc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hoscd1->Fill(j*2, adc);
					else if (channel == 2)
						hoscd2->Fill(j*2, adc);
					else if (channel == 3)
						hoscd3->Fill(j*2, adc);
					else if (channel == 4)
						hoscd4->Fill(j*2, adc);
				}
				c1->cd(1);
				hoscd1->Draw();
				hoscd1->Sumw2(kFALSE);
				c1->cd(2);
				hoscd2->Draw();
				hoscd2->Sumw2(kFALSE);
				c1->cd(3);
				hoscd3->Draw();
				hoscd3->Sumw2(kFALSE);
				c1->cd(4);
				hoscd4->Draw();
				hoscd4->Sumw2(kFALSE);
				c1->Modified();
				c1->Update();
				gSystem->ProcessEvents();
			}
		}

		if (tdcflag == 1)
		{
			if (hostd1 == 0)
			{
				hostd1 = new TH1F("hostd1", "Channel1", hist_point / 4, 0, hist_range);
				hostd2 = new TH1F("hostd2", "Channel2", hist_point / 4, 0, hist_range);
				hostd3 = new TH1F("hostd3", "Channel3", hist_point / 4, 0, hist_range);
				hostd4 = new TH1F("hostd4", "Channel4", hist_point / 4, 0, hist_range);
				c2->cd(1);
				hostd1->Draw();
				c2->cd(2);
				hostd2->Draw();
				c2->cd(3);
				hostd3->Draw();
				c2->cd(4);
				hostd4->Draw();
				gSystem->ProcessEvents();
			}
			else
			{
				hostd1->Reset();
				hostd2->Reset();
				hostd3->Reset();
				hostd4->Reset();

				for (j=0; j<(hist_point / 4); j++)
				{
					tdc = (data1[ibunch][32+j*8+1] >> 4) & 0xF;
					itmp = (data1[ibunch][32+j*8+3] >> 4) & 0xF;
					tdc = tdc + (unsigned int)(itmp << 4);
					itmp = (data1[ibunch][32+j*8+5] >> 4) & 0x3;
					tdc = tdc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hostd1->Fill(j*8, tdc);
					else if (channel == 2)
						hostd2->Fill(j*8, tdc);
					else if (channel == 3)
						hostd3->Fill(j*8, tdc);
					else if (channel == 4)
						hostd4->Fill(j*8, tdc);
				}
				tdc = hostd1->GetMinimum();
				c2->cd(1);
				hostd1->Draw();
				hostd1->Sumw2(kFALSE);
				c2->cd(2);
				hostd2->Draw();
				hostd2->Sumw2(kFALSE);
				c2->cd(3);
				hostd3->Draw();
				hostd3->Sumw2(kFALSE);
				c2->cd(4);
				hostd4->Draw();
				hostd4->Sumw2(kFALSE);
				c2->Modified();
				c2->Update();
				gSystem->ProcessEvents();
			}
		}
		printf("module ID = %d, channel ID = %d\n", mid, channel);
		printf("data_length = %d, run_number = %d, trigger_type = %d, trigger_destination = %d\n", data_length, run_number, trigger_type, trigger_destination);
		printf("trigger_number = %d, local_tnum = %d, trigger_pattern = %d\n", trigger_number, local_tnum, trigger_pattern);
		printf("trigger time = %ld, local starting time = %ld\n", ttime, ltime);
		printf("-------------------------------------------------------------------------------------------------------\n");
		fprintf(lfp, "%lX  %lX  %lX  %lX  %d\n", trig_timel, trig_timeh, start_timel, start_timeh, adc);

	}

	gSystem->ProcessEvents();


}

void FADC500run::Data2(int &sid, int &smid)
{
	fadc->FADC500IBSread_DATA(sid, 16384/1024, data); //the minimum bcount is 16 kB!!
	for (int ibunch = 0; ibunch < 16384/datasize[smid]; ibunch++)
	{
		printf("Mod[%d] bcount = %ld\n",sid,bcount);
		for (int isize = 0; isize < datasize[smid]; isize++)
		{
			data2[ibunch][isize] = data[ibunch*datasize[smid]+isize];
		}
		gSystem->ProcessEvents();

		fwrite(data2[ibunch], 1, datasize[smid], fp);

		data_length =  data2[ibunch][0] & 0xFF;
		itmp = data2[ibunch][1] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 8);
		itmp = data2[ibunch][2] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 16);
		itmp = data2[ibunch][3] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 24);

		run_number = data2[ibunch][4] & 0xFF;
		itmp = data2[ibunch][5] & 0xFF;
		run_number = run_number + (unsigned int)(itmp << 8);

		trigger_type = data2[ibunch][6] & 0x0F;

		itmp = data2[ibunch][6] & 0xF0;
		trigger_destination = itmp >> 4;

		trigger_number = data2[ibunch][7] & 0xFF;
		itmp = data2[ibunch][8] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 8);
		itmp = data2[ibunch][9] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 16);
		itmp = data2[ibunch][10] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 24);					

		ttime = data2[ibunch][11] & 0xFF;
		ttime = ttime*8;

		ltmp = data2[ibunch][12] & 0xFF;
		ttime = ttime + ltmp * 1000;
		ltmp = data2[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		ttime = ttime + ltmp * 1000;
		ltmp = data2[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		ttime = ttime + ltmp * 1000;

		mid = data2[ibunch][15] & 0xFF;

		channel = data2[ibunch][16] & 0xFF;

		local_tnum = data2[ibunch][17] & 0xFF;
		itmp = data2[ibunch][18] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 8);
		itmp = data2[ibunch][19] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 16);
		itmp = data2[ibunch][20] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 24);

		trigger_pattern = data2[ibunch][21] & 0xFF;
		itmp = data2[ibunch][22] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 8);
		itmp = data2[ibunch][23] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 16);
		itmp = data2[ibunch][24] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 24);

		ltime = data2[ibunch][25] & 0xFF;
		ltime = ltime*8;

		ltmp = data2[ibunch][26] & 0xFF;
		ltime = ltime + ltmp*1000;
		ltmp = data2[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		ltime = ltime + ltmp*1000;
		ltmp = data2[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		ltime = ltime + ltmp*1000;

		trig_timel = data2[ibunch][11] & 0xFF;

		ltmp = data2[ibunch][12] & 0xFF;
		trig_timeh = ltmp;
		ltmp = data2[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		trig_timeh = trig_timeh + ltmp;
		ltmp = data2[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		trig_timeh = trig_timeh + ltmp;

		start_timel = data2[ibunch][25] & 0xFF;

		ltmp = data2[ibunch][26] & 0xFF;
		start_timeh = ltmp;
		ltmp = data2[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		start_timeh = start_timeh + ltmp;
		ltmp = data2[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		start_timeh = start_timeh + ltmp;
		hist_point = (data_length - 32)/2;
		hist_range = hist_point * 2;
		gSystem->ProcessEvents();
		if (adcflag == 1)
		{
			if (hoscd1 == 0)
			{
				hoscd1 = new TH1F("hoscd1", "Channel1", hist_point, 0, hist_range);
				hoscd2 = new TH1F("hoscd2", "Channel2", hist_point, 0, hist_range);
				hoscd3 = new TH1F("hoscd3", "Channel3", hist_point, 0, hist_range);
				hoscd4 = new TH1F("hoscd4", "Channel4", hist_point, 0, hist_range);
				c1->cd(1);
				hoscd1->Draw();
				c1->cd(2);
				hoscd2->Draw();
				c1->cd(3);
				hoscd3->Draw();
				c1->cd(4);
				hoscd4->Draw();
				gSystem->ProcessEvents();
			}

			else
			{
				hoscd1->Reset();
				hoscd2->Reset();
				hoscd3->Reset();
				hoscd4->Reset();

				for (int j=0; j<hist_point; j++)
				{
					adc = data2[ibunch][32+j*2] & 0xFF;
					itmp = data2[ibunch][32+j*2+1] & 0x0F;
					adc = adc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hoscd1->Fill(j*2, adc);
					else if (channel == 2)
						hoscd2->Fill(j*2, adc);
					else if (channel == 3)
						hoscd3->Fill(j*2, adc);
					else if (channel == 4)
						hoscd4->Fill(j*2, adc);
				}
				c1->cd(1);
				hoscd1->Draw();
				hoscd1->Sumw2(kFALSE);
				c1->cd(2);
				hoscd2->Draw();
				hoscd2->Sumw2(kFALSE);
				c1->cd(3);
				hoscd3->Draw();
				hoscd3->Sumw2(kFALSE);
				c1->cd(4);
				hoscd4->Draw();
				hoscd4->Sumw2(kFALSE);
				c1->Modified();
				c1->Update();
				gSystem->ProcessEvents();
			}
		}

		if (tdcflag == 1)
		{
			if (hostd1 == 0)
			{
				hostd1 = new TH1F("hostd1", "Channel1", hist_point / 4, 0, hist_range);
				hostd2 = new TH1F("hostd2", "Channel2", hist_point / 4, 0, hist_range);
				hostd3 = new TH1F("hostd3", "Channel3", hist_point / 4, 0, hist_range);
				hostd4 = new TH1F("hostd4", "Channel4", hist_point / 4, 0, hist_range);
				c2->cd(1);
				hostd1->Draw();
				c2->cd(2);
				hostd2->Draw();
				c2->cd(3);
				hostd3->Draw();
				c2->cd(4);
				hostd4->Draw();
				gSystem->ProcessEvents();
			}
			else
			{
				hostd1->Reset();
				hostd2->Reset();
				hostd3->Reset();
				hostd4->Reset();

				for (j=0; j<(hist_point / 4); j++)
				{
					tdc = (data2[ibunch][32+j*8+1] >> 4) & 0xF;
					itmp = (data2[ibunch][32+j*8+3] >> 4) & 0xF;
					tdc = tdc + (unsigned int)(itmp << 4);
					itmp = (data2[ibunch][32+j*8+5] >> 4) & 0x3;
					tdc = tdc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hostd1->Fill(j*8, tdc);
					else if (channel == 2)
						hostd2->Fill(j*8, tdc);
					else if (channel == 3)
						hostd3->Fill(j*8, tdc);
					else if (channel == 4)
						hostd4->Fill(j*8, tdc);
				}
				tdc = hostd1->GetMinimum();
				c2->cd(1);
				hostd1->Draw();
				hostd1->Sumw2(kFALSE);
				c2->cd(2);
				hostd2->Draw();
				hostd2->Sumw2(kFALSE);
				c2->cd(3);
				hostd3->Draw();
				hostd3->Sumw2(kFALSE);
				c2->cd(4);
				hostd4->Draw();
				hostd4->Sumw2(kFALSE);
				c2->Modified();
				c2->Update();
				gSystem->ProcessEvents();
			}
		}
		printf("module ID = %d, channel ID = %d\n", mid, channel);
		printf("data_length = %d, run_number = %d, trigger_type = %d, trigger_destination = %d\n", data_length, run_number, trigger_type, trigger_destination);
		printf("trigger_number = %d, local_tnum = %d, trigger_pattern = %d\n", trigger_number, local_tnum, trigger_pattern);
		printf("trigger time = %ld, local starting time = %ld\n", ttime, ltime);
		printf("-------------------------------------------------------------------------------------------------------\n");
		fprintf(lfp, "%lX  %lX  %lX  %lX  %d\n", trig_timel, trig_timeh, start_timel, start_timeh, adc);

	}

	gSystem->ProcessEvents();


}

void FADC500run::Data4(int &sid, int &smid)
{
	fadc->FADC500IBSread_DATA(sid, 16384/1024, data); //the minimum bcount is 16 kB!!
	for (int ibunch = 0; ibunch < 16384/datasize[smid]; ibunch++)
	{
		printf("Mod[%d] bcount = %ld\n",sid,bcount);
		for (int isize = 0; isize < datasize[smid]; isize++)
		{
			data4[ibunch][isize] = data[ibunch*datasize[smid]+isize];
		}
		gSystem->ProcessEvents();

		fwrite(data4[ibunch], 1, datasize[smid], fp);

		data_length =  data4[ibunch][0] & 0xFF;
		itmp = data4[ibunch][1] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 8);
		itmp = data4[ibunch][2] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 16);
		itmp = data4[ibunch][3] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 24);

		run_number = data4[ibunch][4] & 0xFF;
		itmp = data4[ibunch][5] & 0xFF;
		run_number = run_number + (unsigned int)(itmp << 8);

		trigger_type = data4[ibunch][6] & 0x0F;

		itmp = data4[ibunch][6] & 0xF0;
		trigger_destination = itmp >> 4;

		trigger_number = data4[ibunch][7] & 0xFF;
		itmp = data4[ibunch][8] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 8);
		itmp = data4[ibunch][9] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 16);
		itmp = data4[ibunch][10] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 24);					

		ttime = data4[ibunch][11] & 0xFF;
		ttime = ttime*8;

		ltmp = data4[ibunch][12] & 0xFF;
		ttime = ttime + ltmp * 1000;
		ltmp = data4[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		ttime = ttime + ltmp * 1000;
		ltmp = data4[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		ttime = ttime + ltmp * 1000;

		mid = data4[ibunch][15] & 0xFF;

		channel = data4[ibunch][16] & 0xFF;

		local_tnum = data4[ibunch][17] & 0xFF;
		itmp = data4[ibunch][18] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 8);
		itmp = data4[ibunch][19] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 16);
		itmp = data4[ibunch][20] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 24);

		trigger_pattern = data4[ibunch][21] & 0xFF;
		itmp = data4[ibunch][22] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 8);
		itmp = data4[ibunch][23] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 16);
		itmp = data4[ibunch][24] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 24);

		ltime = data4[ibunch][25] & 0xFF;
		ltime = ltime*8;

		ltmp = data4[ibunch][26] & 0xFF;
		ltime = ltime + ltmp*1000;
		ltmp = data4[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		ltime = ltime + ltmp*1000;
		ltmp = data4[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		ltime = ltime + ltmp*1000;

		trig_timel = data4[ibunch][11] & 0xFF;

		ltmp = data4[ibunch][12] & 0xFF;
		trig_timeh = ltmp;
		ltmp = data4[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		trig_timeh = trig_timeh + ltmp;
		ltmp = data4[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		trig_timeh = trig_timeh + ltmp;

		start_timel = data4[ibunch][25] & 0xFF;

		ltmp = data4[ibunch][26] & 0xFF;
		start_timeh = ltmp;
		ltmp = data4[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		start_timeh = start_timeh + ltmp;
		ltmp = data4[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		start_timeh = start_timeh + ltmp;
		hist_point = (data_length - 32)/2;
		hist_range = hist_point * 2;
		gSystem->ProcessEvents();
		if (adcflag == 1)
		{
			if (hoscd1 == 0)
			{
				hoscd1 = new TH1F("hoscd1", "Channel1", hist_point, 0, hist_range);
				hoscd2 = new TH1F("hoscd2", "Channel2", hist_point, 0, hist_range);
				hoscd3 = new TH1F("hoscd3", "Channel3", hist_point, 0, hist_range);
				hoscd4 = new TH1F("hoscd4", "Channel4", hist_point, 0, hist_range);
				c1->cd(1);
				hoscd1->Draw();
				c1->cd(2);
				hoscd2->Draw();
				c1->cd(3);
				hoscd3->Draw();
				c1->cd(4);
				hoscd4->Draw();
				gSystem->ProcessEvents();
			}

			else
			{
				hoscd1->Reset();
				hoscd2->Reset();
				hoscd3->Reset();
				hoscd4->Reset();

				for (int j=0; j<hist_point; j++)
				{
					adc = data4[ibunch][32+j*2] & 0xFF;
					itmp = data4[ibunch][32+j*2+1] & 0x0F;
					adc = adc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hoscd1->Fill(j*2, adc);
					else if (channel == 2)
						hoscd2->Fill(j*2, adc);
					else if (channel == 3)
						hoscd3->Fill(j*2, adc);
					else if (channel == 4)
						hoscd4->Fill(j*2, adc);
				}
				c1->cd(1);
				hoscd1->Draw();
				hoscd1->Sumw2(kFALSE);
				c1->cd(2);
				hoscd2->Draw();
				hoscd2->Sumw2(kFALSE);
				c1->cd(3);
				hoscd3->Draw();
				hoscd3->Sumw2(kFALSE);
				c1->cd(4);
				hoscd4->Draw();
				hoscd4->Sumw2(kFALSE);
				c1->Modified();
				c1->Update();
				gSystem->ProcessEvents();
			}
		}

		if (tdcflag == 1)
		{
			if (hostd1 == 0)
			{
				hostd1 = new TH1F("hostd1", "Channel1", hist_point / 4, 0, hist_range);
				hostd2 = new TH1F("hostd2", "Channel2", hist_point / 4, 0, hist_range);
				hostd3 = new TH1F("hostd3", "Channel3", hist_point / 4, 0, hist_range);
				hostd4 = new TH1F("hostd4", "Channel4", hist_point / 4, 0, hist_range);
				c2->cd(1);
				hostd1->Draw();
				c2->cd(2);
				hostd2->Draw();
				c2->cd(3);
				hostd3->Draw();
				c2->cd(4);
				hostd4->Draw();
				gSystem->ProcessEvents();
			}
			else
			{
				hostd1->Reset();
				hostd2->Reset();
				hostd3->Reset();
				hostd4->Reset();

				for (j=0; j<(hist_point / 4); j++)
				{
					tdc = (data4[ibunch][32+j*8+1] >> 4) & 0xF;
					itmp = (data4[ibunch][32+j*8+3] >> 4) & 0xF;
					tdc = tdc + (unsigned int)(itmp << 4);
					itmp = (data4[ibunch][32+j*8+5] >> 4) & 0x3;
					tdc = tdc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hostd1->Fill(j*8, tdc);
					else if (channel == 2)
						hostd2->Fill(j*8, tdc);
					else if (channel == 3)
						hostd3->Fill(j*8, tdc);
					else if (channel == 4)
						hostd4->Fill(j*8, tdc);
				}
				tdc = hostd1->GetMinimum();
				c2->cd(1);
				hostd1->Draw();
				hostd1->Sumw2(kFALSE);
				c2->cd(2);
				hostd2->Draw();
				hostd2->Sumw2(kFALSE);
				c2->cd(3);
				hostd3->Draw();
				hostd3->Sumw2(kFALSE);
				c2->cd(4);
				hostd4->Draw();
				hostd4->Sumw2(kFALSE);
				c2->Modified();
				c2->Update();
				gSystem->ProcessEvents();
			}
		}
		printf("module ID = %d, channel ID = %d\n", mid, channel);
		printf("data_length = %d, run_number = %d, trigger_type = %d, trigger_destination = %d\n", data_length, run_number, trigger_type, trigger_destination);
		printf("trigger_number = %d, local_tnum = %d, trigger_pattern = %d\n", trigger_number, local_tnum, trigger_pattern);
		printf("trigger time = %ld, local starting time = %ld\n", ttime, ltime);
		printf("-------------------------------------------------------------------------------------------------------\n");
		fprintf(lfp, "%lX  %lX  %lX  %lX  %d\n", trig_timel, trig_timeh, start_timel, start_timeh, adc);

	}

	gSystem->ProcessEvents();

}

void FADC500run::Data8(int &sid, int &smid)
{
	fadc->FADC500IBSread_DATA(sid, 16384/1024, data); //the minimum bcount is 16 kB!!
	for (int ibunch = 0; ibunch < 16384/datasize[smid]; ibunch++)
	{
		printf("Mod[%d] bcount = %ld\n",sid,bcount);
		for (int isize = 0; isize < datasize[smid]; isize++)
		{
			data8[ibunch][isize] = data[ibunch*datasize[smid]+isize];
		}
		gSystem->ProcessEvents();

		fwrite(data8[ibunch], 1, datasize[smid], fp);

		data_length =  data8[ibunch][0] & 0xFF;
		itmp = data8[ibunch][1] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 8);
		itmp = data8[ibunch][2] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 16);
		itmp = data8[ibunch][3] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 24);

		run_number = data8[ibunch][4] & 0xFF;
		itmp = data8[ibunch][5] & 0xFF;
		run_number = run_number + (unsigned int)(itmp << 8);

		trigger_type = data8[ibunch][6] & 0x0F;

		itmp = data8[ibunch][6] & 0xF0;
		trigger_destination = itmp >> 4;

		trigger_number = data8[ibunch][7] & 0xFF;
		itmp = data8[ibunch][8] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 8);
		itmp = data8[ibunch][9] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 16);
		itmp = data8[ibunch][10] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 24);					

		ttime = data8[ibunch][11] & 0xFF;
		ttime = ttime*8;

		ltmp = data8[ibunch][12] & 0xFF;
		ttime = ttime + ltmp * 1000;
		ltmp = data8[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		ttime = ttime + ltmp * 1000;
		ltmp = data8[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		ttime = ttime + ltmp * 1000;

		mid = data8[ibunch][15] & 0xFF;

		channel = data8[ibunch][16] & 0xFF;

		local_tnum = data8[ibunch][17] & 0xFF;
		itmp = data8[ibunch][18] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 8);
		itmp = data8[ibunch][19] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 16);
		itmp = data8[ibunch][20] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 24);

		trigger_pattern = data8[ibunch][21] & 0xFF;
		itmp = data8[ibunch][22] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 8);
		itmp = data8[ibunch][23] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 16);
		itmp = data8[ibunch][24] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 24);

		ltime = data8[ibunch][25] & 0xFF;
		ltime = ltime*8;

		ltmp = data8[ibunch][26] & 0xFF;
		ltime = ltime + ltmp*1000;
		ltmp = data8[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		ltime = ltime + ltmp*1000;
		ltmp = data8[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		ltime = ltime + ltmp*1000;

		trig_timel = data8[ibunch][11] & 0xFF;

		ltmp = data8[ibunch][12] & 0xFF;
		trig_timeh = ltmp;
		ltmp = data8[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		trig_timeh = trig_timeh + ltmp;
		ltmp = data8[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		trig_timeh = trig_timeh + ltmp;

		start_timel = data8[ibunch][25] & 0xFF;

		ltmp = data8[ibunch][26] & 0xFF;
		start_timeh = ltmp;
		ltmp = data8[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		start_timeh = start_timeh + ltmp;
		ltmp = data8[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		start_timeh = start_timeh + ltmp;
		hist_point = (data_length - 32)/2;
		hist_range = hist_point * 2;
		gSystem->ProcessEvents();
		if (adcflag == 1)
		{
			if (hoscd1 == 0)
			{
				hoscd1 = new TH1F("hoscd1", "Channel1", hist_point, 0, hist_range);
				hoscd2 = new TH1F("hoscd2", "Channel2", hist_point, 0, hist_range);
				hoscd3 = new TH1F("hoscd3", "Channel3", hist_point, 0, hist_range);
				hoscd4 = new TH1F("hoscd4", "Channel4", hist_point, 0, hist_range);
				c1->cd(1);
				hoscd1->Draw();
				c1->cd(2);
				hoscd2->Draw();
				c1->cd(3);
				hoscd3->Draw();
				c1->cd(4);
				hoscd4->Draw();
				gSystem->ProcessEvents();
			}

			else
			{
				hoscd1->Reset();
				hoscd2->Reset();
				hoscd3->Reset();
				hoscd4->Reset();

				for (int j=0; j<hist_point; j++)
				{
					adc = data8[ibunch][32+j*2] & 0xFF;
					itmp = data8[ibunch][32+j*2+1] & 0x0F;
					adc = adc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hoscd1->Fill(j*2, adc);
					else if (channel == 2)
						hoscd2->Fill(j*2, adc);
					else if (channel == 3)
						hoscd3->Fill(j*2, adc);
					else if (channel == 4)
						hoscd4->Fill(j*2, adc);
				}
				c1->cd(1);
				hoscd1->Draw();
				hoscd1->Sumw2(kFALSE);
				c1->cd(2);
				hoscd2->Draw();
				hoscd2->Sumw2(kFALSE);
				c1->cd(3);
				hoscd3->Draw();
				hoscd3->Sumw2(kFALSE);
				c1->cd(4);
				hoscd4->Draw();
				hoscd4->Sumw2(kFALSE);
				c1->Modified();
				c1->Update();
				gSystem->ProcessEvents();
			}
		}

		if (tdcflag == 1)
		{
			if (hostd1 == 0)
			{
				hostd1 = new TH1F("hostd1", "Channel1", hist_point / 4, 0, hist_range);
				hostd2 = new TH1F("hostd2", "Channel2", hist_point / 4, 0, hist_range);
				hostd3 = new TH1F("hostd3", "Channel3", hist_point / 4, 0, hist_range);
				hostd4 = new TH1F("hostd4", "Channel4", hist_point / 4, 0, hist_range);
				c2->cd(1);
				hostd1->Draw();
				c2->cd(2);
				hostd2->Draw();
				c2->cd(3);
				hostd3->Draw();
				c2->cd(4);
				hostd4->Draw();
				gSystem->ProcessEvents();
			}
			else
			{
				hostd1->Reset();
				hostd2->Reset();
				hostd3->Reset();
				hostd4->Reset();

				for (j=0; j<(hist_point / 4); j++)
				{
					tdc = (data8[ibunch][32+j*8+1] >> 4) & 0xF;
					itmp = (data8[ibunch][32+j*8+3] >> 4) & 0xF;
					tdc = tdc + (unsigned int)(itmp << 4);
					itmp = (data8[ibunch][32+j*8+5] >> 4) & 0x3;
					tdc = tdc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hostd1->Fill(j*8, tdc);
					else if (channel == 2)
						hostd2->Fill(j*8, tdc);
					else if (channel == 3)
						hostd3->Fill(j*8, tdc);
					else if (channel == 4)
						hostd4->Fill(j*8, tdc);
				}
				tdc = hostd1->GetMinimum();
				c2->cd(1);
				hostd1->Draw();
				hostd1->Sumw2(kFALSE);
				c2->cd(2);
				hostd2->Draw();
				hostd2->Sumw2(kFALSE);
				c2->cd(3);
				hostd3->Draw();
				hostd3->Sumw2(kFALSE);
				c2->cd(4);
				hostd4->Draw();
				hostd4->Sumw2(kFALSE);
				c2->Modified();
				c2->Update();
				gSystem->ProcessEvents();
			}
		}
		printf("module ID = %d, channel ID = %d\n", mid, channel);
		printf("data_length = %d, run_number = %d, trigger_type = %d, trigger_destination = %d\n", data_length, run_number, trigger_type, trigger_destination);
		printf("trigger_number = %d, local_tnum = %d, trigger_pattern = %d\n", trigger_number, local_tnum, trigger_pattern);
		printf("trigger time = %ld, local starting time = %ld\n", ttime, ltime);
		printf("-------------------------------------------------------------------------------------------------------\n");
		fprintf(lfp, "%lX  %lX  %lX  %lX  %d\n", trig_timel, trig_timeh, start_timel, start_timeh, adc);

	}

	gSystem->ProcessEvents();

}

void FADC500run::Data16(int &sid, int &smid)
{
	fadc->FADC500IBSread_DATA(sid, 16384/1024, data); //the minimum bcount is 16 kB!!
	for (int ibunch = 0; ibunch < 16384/datasize[smid]; ibunch++)
	{
		printf("Mod[%d] bcount = %ld\n",sid,bcount);
		for (int isize = 0; isize < datasize[smid]; isize++)
		{
			data16[ibunch][isize] = data[ibunch*datasize[smid]+isize];
		}
		gSystem->ProcessEvents();

		fwrite(data16[ibunch], 1, datasize[smid], fp);

		data_length =  data16[ibunch][0] & 0xFF;
		itmp = data16[ibunch][1] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 8);
		itmp = data16[ibunch][2] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 16);
		itmp = data16[ibunch][3] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 24);

		run_number = data16[ibunch][4] & 0xFF;
		itmp = data16[ibunch][5] & 0xFF;
		run_number = run_number + (unsigned int)(itmp << 8);

		trigger_type = data16[ibunch][6] & 0x0F;

		itmp = data16[ibunch][6] & 0xF0;
		trigger_destination = itmp >> 4;

		trigger_number = data16[ibunch][7] & 0xFF;
		itmp = data16[ibunch][8] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 8);
		itmp = data16[ibunch][9] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 16);
		itmp = data16[ibunch][10] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 24);					

		ttime = data16[ibunch][11] & 0xFF;
		ttime = ttime*8;

		ltmp = data16[ibunch][12] & 0xFF;
		ttime = ttime + ltmp * 1000;
		ltmp = data16[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		ttime = ttime + ltmp * 1000;
		ltmp = data16[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		ttime = ttime + ltmp * 1000;

		mid = data16[ibunch][15] & 0xFF;

		channel = data16[ibunch][16] & 0xFF;

		local_tnum = data16[ibunch][17] & 0xFF;
		itmp = data16[ibunch][18] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 8);
		itmp = data16[ibunch][19] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 16);
		itmp = data16[ibunch][20] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 24);

		trigger_pattern = data16[ibunch][21] & 0xFF;
		itmp = data16[ibunch][22] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 8);
		itmp = data16[ibunch][23] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 16);
		itmp = data16[ibunch][24] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 24);

		ltime = data16[ibunch][25] & 0xFF;
		ltime = ltime*8;

		ltmp = data16[ibunch][26] & 0xFF;
		ltime = ltime + ltmp*1000;
		ltmp = data16[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		ltime = ltime + ltmp*1000;
		ltmp = data16[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		ltime = ltime + ltmp*1000;

		trig_timel = data16[ibunch][11] & 0xFF;

		ltmp = data16[ibunch][12] & 0xFF;
		trig_timeh = ltmp;
		ltmp = data16[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		trig_timeh = trig_timeh + ltmp;
		ltmp = data16[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		trig_timeh = trig_timeh + ltmp;

		start_timel = data16[ibunch][25] & 0xFF;

		ltmp = data16[ibunch][26] & 0xFF;
		start_timeh = ltmp;
		ltmp = data16[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		start_timeh = start_timeh + ltmp;
		ltmp = data16[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		start_timeh = start_timeh + ltmp;
		hist_point = (data_length - 32)/2;
		hist_range = hist_point * 2;
		gSystem->ProcessEvents();
		if (adcflag == 1)
		{
			if (hoscd1 == 0)
			{
				hoscd1 = new TH1F("hoscd1", "Channel1", hist_point, 0, hist_range);
				hoscd2 = new TH1F("hoscd2", "Channel2", hist_point, 0, hist_range);
				hoscd3 = new TH1F("hoscd3", "Channel3", hist_point, 0, hist_range);
				hoscd4 = new TH1F("hoscd4", "Channel4", hist_point, 0, hist_range);
				c1->cd(1);
				hoscd1->Draw();
				c1->cd(2);
				hoscd2->Draw();
				c1->cd(3);
				hoscd3->Draw();
				c1->cd(4);
				hoscd4->Draw();
				gSystem->ProcessEvents();
			}

			else
			{
				hoscd1->Reset();
				hoscd2->Reset();
				hoscd3->Reset();
				hoscd4->Reset();

				for (int j=0; j<hist_point; j++)
				{
					adc = data16[ibunch][32+j*2] & 0xFF;
					itmp = data16[ibunch][32+j*2+1] & 0x0F;
					adc = adc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hoscd1->Fill(j*2, adc);
					else if (channel == 2)
						hoscd2->Fill(j*2, adc);
					else if (channel == 3)
						hoscd3->Fill(j*2, adc);
					else if (channel == 4)
						hoscd4->Fill(j*2, adc);
				}
				c1->cd(1);
				hoscd1->Draw();
				hoscd1->Sumw2(kFALSE);
				c1->cd(2);
				hoscd2->Draw();
				hoscd2->Sumw2(kFALSE);
				c1->cd(3);
				hoscd3->Draw();
				hoscd3->Sumw2(kFALSE);
				c1->cd(4);
				hoscd4->Draw();
				hoscd4->Sumw2(kFALSE);
				c1->Modified();
				c1->Update();
				gSystem->ProcessEvents();
			}
		}

		if (tdcflag == 1)
		{
			if (hostd1 == 0)
			{
				hostd1 = new TH1F("hostd1", "Channel1", hist_point / 4, 0, hist_range);
				hostd2 = new TH1F("hostd2", "Channel2", hist_point / 4, 0, hist_range);
				hostd3 = new TH1F("hostd3", "Channel3", hist_point / 4, 0, hist_range);
				hostd4 = new TH1F("hostd4", "Channel4", hist_point / 4, 0, hist_range);
				c2->cd(1);
				hostd1->Draw();
				c2->cd(2);
				hostd2->Draw();
				c2->cd(3);
				hostd3->Draw();
				c2->cd(4);
				hostd4->Draw();
				gSystem->ProcessEvents();
			}
			else
			{
				hostd1->Reset();
				hostd2->Reset();
				hostd3->Reset();
				hostd4->Reset();

				for (j=0; j<(hist_point / 4); j++)
				{
					tdc = (data16[ibunch][32+j*8+1] >> 4) & 0xF;
					itmp = (data16[ibunch][32+j*8+3] >> 4) & 0xF;
					tdc = tdc + (unsigned int)(itmp << 4);
					itmp = (data16[ibunch][32+j*8+5] >> 4) & 0x3;
					tdc = tdc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hostd1->Fill(j*8, tdc);
					else if (channel == 2)
						hostd2->Fill(j*8, tdc);
					else if (channel == 3)
						hostd3->Fill(j*8, tdc);
					else if (channel == 4)
						hostd4->Fill(j*8, tdc);
				}
				tdc = hostd1->GetMinimum();
				c2->cd(1);
				hostd1->Draw();
				hostd1->Sumw2(kFALSE);
				c2->cd(2);
				hostd2->Draw();
				hostd2->Sumw2(kFALSE);
				c2->cd(3);
				hostd3->Draw();
				hostd3->Sumw2(kFALSE);
				c2->cd(4);
				hostd4->Draw();
				hostd4->Sumw2(kFALSE);
				c2->Modified();
				c2->Update();
				gSystem->ProcessEvents();
			}
		}
		printf("module ID = %d, channel ID = %d\n", mid, channel);
		printf("data_length = %d, run_number = %d, trigger_type = %d, trigger_destination = %d\n", data_length, run_number, trigger_type, trigger_destination);
		printf("trigger_number = %d, local_tnum = %d, trigger_pattern = %d\n", trigger_number, local_tnum, trigger_pattern);
		printf("trigger time = %ld, local starting time = %ld\n", ttime, ltime);
		printf("-------------------------------------------------------------------------------------------------------\n");
		fprintf(lfp, "%lX  %lX  %lX  %lX  %d\n", trig_timel, trig_timeh, start_timel, start_timeh, adc);

	}

	gSystem->ProcessEvents();

}

void FADC500run::Data32(int &sid, int &smid)
{
	fadc->FADC500IBSread_DATA(sid, 16384/1024, data); //the minimum bcount is 16 kB!!
	for (int ibunch = 0; ibunch < 16384/datasize[smid]; ibunch++)
	{
		printf("Mod[%d] bcount = %ld\n",sid,bcount);
		for (int isize = 0; isize < datasize[smid]; isize++)
		{
			data32[ibunch][isize] = data[ibunch*datasize[smid]+isize];
		}
		gSystem->ProcessEvents();

		fwrite(data32[ibunch], 1, datasize[smid], fp);

		data_length =  data32[ibunch][0] & 0xFF;
		itmp = data32[ibunch][1] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 8);
		itmp = data32[ibunch][2] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 16);
		itmp = data32[ibunch][3] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 24);

		run_number = data32[ibunch][4] & 0xFF;
		itmp = data32[ibunch][5] & 0xFF;
		run_number = run_number + (unsigned int)(itmp << 8);

		trigger_type = data32[ibunch][6] & 0x0F;

		itmp = data32[ibunch][6] & 0xF0;
		trigger_destination = itmp >> 4;

		trigger_number = data32[ibunch][7] & 0xFF;
		itmp = data32[ibunch][8] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 8);
		itmp = data32[ibunch][9] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 16);
		itmp = data32[ibunch][10] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 24);					

		ttime = data32[ibunch][11] & 0xFF;
		ttime = ttime*8;

		ltmp = data32[ibunch][12] & 0xFF;
		ttime = ttime + ltmp * 1000;
		ltmp = data32[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		ttime = ttime + ltmp * 1000;
		ltmp = data32[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		ttime = ttime + ltmp * 1000;

		mid = data32[ibunch][15] & 0xFF;

		channel = data32[ibunch][16] & 0xFF;

		local_tnum = data32[ibunch][17] & 0xFF;
		itmp = data32[ibunch][18] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 8);
		itmp = data32[ibunch][19] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 16);
		itmp = data32[ibunch][20] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 24);

		trigger_pattern = data32[ibunch][21] & 0xFF;
		itmp = data32[ibunch][22] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 8);
		itmp = data32[ibunch][23] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 16);
		itmp = data32[ibunch][24] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 24);

		ltime = data32[ibunch][25] & 0xFF;
		ltime = ltime*8;

		ltmp = data32[ibunch][26] & 0xFF;
		ltime = ltime + ltmp*1000;
		ltmp = data32[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		ltime = ltime + ltmp*1000;
		ltmp = data32[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		ltime = ltime + ltmp*1000;

		trig_timel = data32[ibunch][11] & 0xFF;

		ltmp = data32[ibunch][12] & 0xFF;
		trig_timeh = ltmp;
		ltmp = data32[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		trig_timeh = trig_timeh + ltmp;
		ltmp = data32[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		trig_timeh = trig_timeh + ltmp;

		start_timel = data32[ibunch][25] & 0xFF;

		ltmp = data32[ibunch][26] & 0xFF;
		start_timeh = ltmp;
		ltmp = data32[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		start_timeh = start_timeh + ltmp;
		ltmp = data32[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		start_timeh = start_timeh + ltmp;
		hist_point = (data_length - 32)/2;
		hist_range = hist_point * 2;
		gSystem->ProcessEvents();
		if (adcflag == 1)
		{
			if (hoscd1 == 0)
			{
				hoscd1 = new TH1F("hoscd1", "Channel1", hist_point, 0, hist_range);
				hoscd2 = new TH1F("hoscd2", "Channel2", hist_point, 0, hist_range);
				hoscd3 = new TH1F("hoscd3", "Channel3", hist_point, 0, hist_range);
				hoscd4 = new TH1F("hoscd4", "Channel4", hist_point, 0, hist_range);
				c1->cd(1);
				hoscd1->Draw();
				c1->cd(2);
				hoscd2->Draw();
				c1->cd(3);
				hoscd3->Draw();
				c1->cd(4);
				hoscd4->Draw();
				gSystem->ProcessEvents();
			}

			else
			{
				hoscd1->Reset();
				hoscd2->Reset();
				hoscd3->Reset();
				hoscd4->Reset();

				for (int j=0; j<hist_point; j++)
				{
					adc = data32[ibunch][32+j*2] & 0xFF;
					itmp = data32[ibunch][32+j*2+1] & 0x0F;
					adc = adc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hoscd1->Fill(j*2, adc);
					else if (channel == 2)
						hoscd2->Fill(j*2, adc);
					else if (channel == 3)
						hoscd3->Fill(j*2, adc);
					else if (channel == 4)
						hoscd4->Fill(j*2, adc);
				}
				c1->cd(1);
				hoscd1->Draw();
				hoscd1->Sumw2(kFALSE);
				c1->cd(2);
				hoscd2->Draw();
				hoscd2->Sumw2(kFALSE);
				c1->cd(3);
				hoscd3->Draw();
				hoscd3->Sumw2(kFALSE);
				c1->cd(4);
				hoscd4->Draw();
				hoscd4->Sumw2(kFALSE);
				c1->Modified();
				c1->Update();
				gSystem->ProcessEvents();
			}
		}

		if (tdcflag == 1)
		{
			if (hostd1 == 0)
			{
				hostd1 = new TH1F("hostd1", "Channel1", hist_point / 4, 0, hist_range);
				hostd2 = new TH1F("hostd2", "Channel2", hist_point / 4, 0, hist_range);
				hostd3 = new TH1F("hostd3", "Channel3", hist_point / 4, 0, hist_range);
				hostd4 = new TH1F("hostd4", "Channel4", hist_point / 4, 0, hist_range);
				c2->cd(1);
				hostd1->Draw();
				c2->cd(2);
				hostd2->Draw();
				c2->cd(3);
				hostd3->Draw();
				c2->cd(4);
				hostd4->Draw();
				gSystem->ProcessEvents();
			}
			else
			{
				hostd1->Reset();
				hostd2->Reset();
				hostd3->Reset();
				hostd4->Reset();

				for (j=0; j<(hist_point / 4); j++)
				{
					tdc = (data32[ibunch][32+j*8+1] >> 4) & 0xF;
					itmp = (data32[ibunch][32+j*8+3] >> 4) & 0xF;
					tdc = tdc + (unsigned int)(itmp << 4);
					itmp = (data32[ibunch][32+j*8+5] >> 4) & 0x3;
					tdc = tdc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hostd1->Fill(j*8, tdc);
					else if (channel == 2)
						hostd2->Fill(j*8, tdc);
					else if (channel == 3)
						hostd3->Fill(j*8, tdc);
					else if (channel == 4)
						hostd4->Fill(j*8, tdc);
				}
				tdc = hostd1->GetMinimum();
				c2->cd(1);
				hostd1->Draw();
				hostd1->Sumw2(kFALSE);
				c2->cd(2);
				hostd2->Draw();
				hostd2->Sumw2(kFALSE);
				c2->cd(3);
				hostd3->Draw();
				hostd3->Sumw2(kFALSE);
				c2->cd(4);
				hostd4->Draw();
				hostd4->Sumw2(kFALSE);
				c2->Modified();
				c2->Update();
				gSystem->ProcessEvents();
			}
		}
		printf("module ID = %d, channel ID = %d\n", mid, channel);
		printf("data_length = %d, run_number = %d, trigger_type = %d, trigger_destination = %d\n", data_length, run_number, trigger_type, trigger_destination);
		printf("trigger_number = %d, local_tnum = %d, trigger_pattern = %d\n", trigger_number, local_tnum, trigger_pattern);
		printf("trigger time = %ld, local starting time = %ld\n", ttime, ltime);
		printf("-------------------------------------------------------------------------------------------------------\n");
		fprintf(lfp, "%lX  %lX  %lX  %lX  %d\n", trig_timel, trig_timeh, start_timel, start_timeh, adc);

	}

	gSystem->ProcessEvents();

}

void FADC500run::Data64(int &sid, int &smid)
{
	fadc->FADC500IBSread_DATA(sid, 16384/1024, data); //the minimum bcount is 16 kB!!
	for (int ibunch = 0; ibunch < 16384/datasize[smid]; ibunch++)
	{
		printf("Mod[%d] bcount = %ld\n",sid,bcount);
		for (int isize = 0; isize < datasize[smid]; isize++)
		{
			data64[ibunch][isize] = data[ibunch*datasize[smid]+isize];
		}
		gSystem->ProcessEvents();

		fwrite(data64[ibunch], 1, datasize[smid], fp);

		data_length =  data64[ibunch][0] & 0xFF;
		itmp = data64[ibunch][1] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 8);
		itmp = data64[ibunch][2] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 16);
		itmp = data64[ibunch][3] & 0xFF;
		data_length = data_length + (unsigned int)(itmp << 24);

		run_number = data64[ibunch][4] & 0xFF;
		itmp = data64[ibunch][5] & 0xFF;
		run_number = run_number + (unsigned int)(itmp << 8);

		trigger_type = data64[ibunch][6] & 0x0F;

		itmp = data64[ibunch][6] & 0xF0;
		trigger_destination = itmp >> 4;

		trigger_number = data64[ibunch][7] & 0xFF;
		itmp = data64[ibunch][8] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 8);
		itmp = data64[ibunch][9] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 16);
		itmp = data64[ibunch][10] & 0xFF;
		trigger_number = trigger_number + (unsigned int)(itmp << 24);					

		ttime = data64[ibunch][11] & 0xFF;
		ttime = ttime*8;

		ltmp = data64[ibunch][12] & 0xFF;
		ttime = ttime + ltmp * 1000;
		ltmp = data64[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		ttime = ttime + ltmp * 1000;
		ltmp = data64[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		ttime = ttime + ltmp * 1000;

		mid = data64[ibunch][15] & 0xFF;

		channel = data64[ibunch][16] & 0xFF;

		local_tnum = data64[ibunch][17] & 0xFF;
		itmp = data64[ibunch][18] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 8);
		itmp = data64[ibunch][19] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 16);
		itmp = data64[ibunch][20] & 0xFF;
		local_tnum = local_tnum + (unsigned int)(itmp << 24);

		trigger_pattern = data64[ibunch][21] & 0xFF;
		itmp = data64[ibunch][22] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 8);
		itmp = data64[ibunch][23] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 16);
		itmp = data64[ibunch][24] & 0xFF;
		trigger_pattern = trigger_pattern + (unsigned int)(itmp << 24);

		ltime = data64[ibunch][25] & 0xFF;
		ltime = ltime*8;

		ltmp = data64[ibunch][26] & 0xFF;
		ltime = ltime + ltmp*1000;
		ltmp = data64[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		ltime = ltime + ltmp*1000;
		ltmp = data64[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		ltime = ltime + ltmp*1000;

		trig_timel = data64[ibunch][11] & 0xFF;

		ltmp = data64[ibunch][12] & 0xFF;
		trig_timeh = ltmp;
		ltmp = data64[ibunch][13] & 0xFF;
		ltmp = ltmp << 8;
		trig_timeh = trig_timeh + ltmp;
		ltmp = data64[ibunch][14] & 0xFF;
		ltmp = ltmp << 16;
		trig_timeh = trig_timeh + ltmp;

		start_timel = data64[ibunch][25] & 0xFF;

		ltmp = data64[ibunch][26] & 0xFF;
		start_timeh = ltmp;
		ltmp = data64[ibunch][27] & 0xFF;
		ltmp = ltmp << 8;
		start_timeh = start_timeh + ltmp;
		ltmp = data64[ibunch][28] & 0xFF;
		ltmp = ltmp << 16;
		start_timeh = start_timeh + ltmp;
		hist_point = (data_length - 32)/2;
		hist_range = hist_point * 2;
		gSystem->ProcessEvents();
		if (adcflag == 1)
		{
			if (hoscd1 == 0)
			{
				hoscd1 = new TH1F("hoscd1", "Channel1", hist_point, 0, hist_range);
				hoscd2 = new TH1F("hoscd2", "Channel2", hist_point, 0, hist_range);
				hoscd3 = new TH1F("hoscd3", "Channel3", hist_point, 0, hist_range);
				hoscd4 = new TH1F("hoscd4", "Channel4", hist_point, 0, hist_range);
				c1->cd(1);
				hoscd1->Draw();
				c1->cd(2);
				hoscd2->Draw();
				c1->cd(3);
				hoscd3->Draw();
				c1->cd(4);
				hoscd4->Draw();
				gSystem->ProcessEvents();
			}

			else
			{
				hoscd1->Reset();
				hoscd2->Reset();
				hoscd3->Reset();
				hoscd4->Reset();

				for (int j=0; j<hist_point; j++)
				{
					adc = data64[ibunch][32+j*2] & 0xFF;
					itmp = data64[ibunch][32+j*2+1] & 0x0F;
					adc = adc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hoscd1->Fill(j*2, adc);
					else if (channel == 2)
						hoscd2->Fill(j*2, adc);
					else if (channel == 3)
						hoscd3->Fill(j*2, adc);
					else if (channel == 4)
						hoscd4->Fill(j*2, adc);
				}
				c1->cd(1);
				hoscd1->Draw();
				hoscd1->Sumw2(kFALSE);
				c1->cd(2);
				hoscd2->Draw();
				hoscd2->Sumw2(kFALSE);
				c1->cd(3);
				hoscd3->Draw();
				hoscd3->Sumw2(kFALSE);
				c1->cd(4);
				hoscd4->Draw();
				hoscd4->Sumw2(kFALSE);
				c1->Modified();
				c1->Update();
				gSystem->ProcessEvents();
			}
		}

		if (tdcflag == 1)
		{
			if (hostd1 == 0)
			{
				hostd1 = new TH1F("hostd1", "Channel1", hist_point / 4, 0, hist_range);
				hostd2 = new TH1F("hostd2", "Channel2", hist_point / 4, 0, hist_range);
				hostd3 = new TH1F("hostd3", "Channel3", hist_point / 4, 0, hist_range);
				hostd4 = new TH1F("hostd4", "Channel4", hist_point / 4, 0, hist_range);
				c2->cd(1);
				hostd1->Draw();
				c2->cd(2);
				hostd2->Draw();
				c2->cd(3);
				hostd3->Draw();
				c2->cd(4);
				hostd4->Draw();
				gSystem->ProcessEvents();
			}
			else
			{
				hostd1->Reset();
				hostd2->Reset();
				hostd3->Reset();
				hostd4->Reset();

				for (j=0; j<(hist_point / 4); j++)
				{
					tdc = (data64[ibunch][32+j*8+1] >> 4) & 0xF;
					itmp = (data64[ibunch][32+j*8+3] >> 4) & 0xF;
					tdc = tdc + (unsigned int)(itmp << 4);
					itmp = (data64[ibunch][32+j*8+5] >> 4) & 0x3;
					tdc = tdc + (unsigned int)(itmp << 8);

					if (channel == 1)
						hostd1->Fill(j*8, tdc);
					else if (channel == 2)
						hostd2->Fill(j*8, tdc);
					else if (channel == 3)
						hostd3->Fill(j*8, tdc);
					else if (channel == 4)
						hostd4->Fill(j*8, tdc);
				}
				tdc = hostd1->GetMinimum();
				c2->cd(1);
				hostd1->Draw();
				hostd1->Sumw2(kFALSE);
				c2->cd(2);
				hostd2->Draw();
				hostd2->Sumw2(kFALSE);
				c2->cd(3);
				hostd3->Draw();
				hostd3->Sumw2(kFALSE);
				c2->cd(4);
				hostd4->Draw();
				hostd4->Sumw2(kFALSE);
				c2->Modified();
				c2->Update();
				gSystem->ProcessEvents();
			}
		}

		printf("module ID = %d, channel ID = %d\n", mid, channel);
		printf("data_length = %d, run_number = %d, trigger_type = %d, trigger_destination = %d\n", data_length, run_number, trigger_type, trigger_destination);
		printf("trigger_number = %d, local_tnum = %d, trigger_pattern = %d\n", trigger_number, local_tnum, trigger_pattern);
		printf("trigger time = %ld, local starting time = %ld\n", ttime, ltime);
		printf("-------------------------------------------------------------------------------------------------------\n");
		fprintf(lfp, "%lX  %lX  %lX  %lX  %d\n", trig_timel, trig_timeh, start_timel, start_timeh, adc);

	}

	gSystem->ProcessEvents();

}

void FADC500run::Data128(int &sid, int &smid)
{
	fadc->FADC500IBSread_DATA(sid, datasize[smid]/1024, data128);
	fwrite(data128, 1, datasize[smid], fp);
	printf("Mod[%d] bcount = %ld\n",sid,bcount);

	gSystem->ProcessEvents();

	data_length =  data128[0] & 0xFF;
	itmp = data128[1] & 0xFF;
	data_length = data_length + (unsigned int)(itmp << 8);
	itmp = data128[2] & 0xFF;
	data_length = data_length + (unsigned int)(itmp << 16);
	itmp = data128[3] & 0xFF;
	data_length = data_length + (unsigned int)(itmp << 24);

	run_number = data128[4] & 0xFF;
	itmp = data128[5] & 0xFF;
	run_number = run_number + (unsigned int)(itmp << 8);

	trigger_type = data128[6] & 0x0F;

	itmp = data128[6] & 0xF0;
	trigger_destination = itmp >> 4;

	trigger_number = data128[7] & 0xFF;
	itmp = data128[8] & 0xFF;
	trigger_number = trigger_number + (unsigned int)(itmp << 8);
	itmp = data128[9] & 0xFF;
	trigger_number = trigger_number + (unsigned int)(itmp << 16);
	itmp = data128[10] & 0xFF;
	trigger_number = trigger_number + (unsigned int)(itmp << 24);					

	ttime = data128[11] & 0xFF;
	ttime = ttime*8;

	ltmp = data128[12] & 0xFF;
	ttime = ttime + ltmp * 1000;
	ltmp = data128[13] & 0xFF;
	ltmp = ltmp << 8;
	ttime = ttime + ltmp * 1000;
	ltmp = data128[14] & 0xFF;
	ltmp = ltmp << 16;
	ttime = ttime + ltmp * 1000;

	mid = data128[15] & 0xFF;

	channel = data128[16] & 0xFF;

	local_tnum = data128[17] & 0xFF;
	itmp = data128[18] & 0xFF;
	local_tnum = local_tnum + (unsigned int)(itmp << 8);
	itmp = data128[19] & 0xFF;
	local_tnum = local_tnum + (unsigned int)(itmp << 16);
	itmp = data128[20] & 0xFF;
	local_tnum = local_tnum + (unsigned int)(itmp << 24);

	trigger_pattern = data128[21] & 0xFF;
	itmp = data128[22] & 0xFF;
	trigger_pattern = trigger_pattern + (unsigned int)(itmp << 8);
	itmp = data128[23] & 0xFF;
	trigger_pattern = trigger_pattern + (unsigned int)(itmp << 16);
	itmp = data128[24] & 0xFF;
	trigger_pattern = trigger_pattern + (unsigned int)(itmp << 24);

	ltime = data128[25] & 0xFF;
	ltime = ltime*8;

	ltmp = data128[26] & 0xFF;
	ltime = ltime + ltmp*1000;
	ltmp = data128[27] & 0xFF;
	ltmp = ltmp << 8;
	ltime = ltime + ltmp*1000;
	ltmp = data128[28] & 0xFF;
	ltmp = ltmp << 16;
	ltime = ltime + ltmp*1000;

	trig_timel = data128[11] & 0xFF;

	ltmp = data128[12] & 0xFF;
	trig_timeh = ltmp;
	ltmp = data128[13] & 0xFF;
	ltmp = ltmp << 8;
	trig_timeh = trig_timeh + ltmp;
	ltmp = data128[14] & 0xFF;
	ltmp = ltmp << 16;
	trig_timeh = trig_timeh + ltmp;

	start_timel = data128[25] & 0xFF;

	ltmp = data128[26] & 0xFF;
	start_timeh = ltmp;
	ltmp = data128[27] & 0xFF;
	ltmp = ltmp << 8;
	start_timeh = start_timeh + ltmp;
	ltmp = data128[28] & 0xFF;
	ltmp = ltmp << 16;
	start_timeh = start_timeh + ltmp;
	hist_point = (data_length - 32)/2;
	hist_range = hist_point * 2;
	gSystem->ProcessEvents();
	if (adcflag == 1)
	{
		if (hoscd1 == 0)
		{
			hoscd1 = new TH1F("hoscd1", "Channel1", hist_point, 0, hist_range);
			hoscd2 = new TH1F("hoscd2", "Channel2", hist_point, 0, hist_range);
			hoscd3 = new TH1F("hoscd3", "Channel3", hist_point, 0, hist_range);
			hoscd4 = new TH1F("hoscd4", "Channel4", hist_point, 0, hist_range);
			c1->cd(1);
			hoscd1->Draw();
			c1->cd(2);
			hoscd2->Draw();
			c1->cd(3);
			hoscd3->Draw();
			c1->cd(4);
			hoscd4->Draw();
			gSystem->ProcessEvents();
		}

		else
		{
			hoscd1->Reset();
			hoscd2->Reset();
			hoscd3->Reset();
			hoscd4->Reset();

			for (int j=0; j<hist_point; j++)
			{
				adc = data128[32+j*2] & 0xFF;
				itmp = data128[32+j*2+1] & 0x0F;
				adc = adc + (unsigned int)(itmp << 8);

				if (channel == 1)
					hoscd1->Fill(j*2, adc);
				else if (channel == 2)
					hoscd2->Fill(j*2, adc);
				else if (channel == 3)
					hoscd3->Fill(j*2, adc);
				else if (channel == 4)
					hoscd4->Fill(j*2, adc);
			}
			c1->cd(1);
			hoscd1->Draw();
			hoscd1->Sumw2(kFALSE);
			c1->cd(2);
			hoscd2->Draw();
			hoscd2->Sumw2(kFALSE);
			c1->cd(3);
			hoscd3->Draw();
			hoscd3->Sumw2(kFALSE);
			c1->cd(4);
			hoscd4->Draw();
			hoscd4->Sumw2(kFALSE);
			c1->Modified();
			c1->Update();
			gSystem->ProcessEvents();
		}
	}

	if (tdcflag == 1)
	{
		if (hostd1 == 0)
		{
			hostd1 = new TH1F("hostd1", "Channel1", hist_point / 4, 0, hist_range);
			hostd2 = new TH1F("hostd2", "Channel2", hist_point / 4, 0, hist_range);
			hostd3 = new TH1F("hostd3", "Channel3", hist_point / 4, 0, hist_range);
			hostd4 = new TH1F("hostd4", "Channel4", hist_point / 4, 0, hist_range);
			c2->cd(1);
			hostd1->Draw();
			c2->cd(2);
			hostd2->Draw();
			c2->cd(3);
			hostd3->Draw();
			c2->cd(4);
			hostd4->Draw();
			gSystem->ProcessEvents();
		}
		else
		{
			hostd1->Reset();
			hostd2->Reset();
			hostd3->Reset();
			hostd4->Reset();

			for (j=0; j<(hist_point / 4); j++)
			{
				tdc = (data128[32+j*8+1] >> 4) & 0xF;
				itmp = (data128[32+j*8+3] >> 4) & 0xF;
				tdc = tdc + (unsigned int)(itmp << 4);
				itmp = (data128[32+j*8+5] >> 4) & 0x3;
				tdc = tdc + (unsigned int)(itmp << 8);

				if (channel == 1)
					hostd1->Fill(j*8, tdc);
				else if (channel == 2)
					hostd2->Fill(j*8, tdc);
				else if (channel == 3)
					hostd3->Fill(j*8, tdc);
				else if (channel == 4)
					hostd4->Fill(j*8, tdc);
			}
			tdc = hostd1->GetMinimum();
			c2->cd(1);
			hostd1->Draw();
			hostd1->Sumw2(kFALSE);
			c2->cd(2);
			hostd2->Draw();
			hostd2->Sumw2(kFALSE);
			c2->cd(3);
			hostd3->Draw();
			hostd3->Sumw2(kFALSE);
			c2->cd(4);
			hostd4->Draw();
			hostd4->Sumw2(kFALSE);
			c2->Modified();
			c2->Update();
			gSystem->ProcessEvents();
		}
	}
	printf("module ID = %d, channel ID = %d\n", mid, channel);
	printf("data_length = %d, run_number = %d, trigger_type = %d, trigger_destination = %d\n", data_length, run_number, trigger_type, trigger_destination);
	printf("trigger_number = %d, local_tnum = %d, trigger_pattern = %d\n", trigger_number, local_tnum, trigger_pattern);
	printf("trigger time = %ld, local starting time = %ld\n", ttime, ltime);
	printf("-------------------------------------------------------------------------------------------------------\n");
	fprintf(lfp, "%lX  %lX  %lX  %lX  %d\n", trig_timel, trig_timeh, start_timel, start_timeh, adc);



}

void FADC500run::Data256(int &sid, int &smid)
{
	fadc->FADC500IBSread_DATA(sid, datasize[smid]/1024, data256);
	fwrite(data256, 1, datasize[smid], fp);
	printf("Mod[%d] bcount = %ld\n",sid,bcount);

	gSystem->ProcessEvents();

	data_length =  data256[0] & 0xFF;
	itmp = data256[1] & 0xFF;
	data_length = data_length + (unsigned int)(itmp << 8);
	itmp = data256[2] & 0xFF;
	data_length = data_length + (unsigned int)(itmp << 16);
	itmp = data256[3] & 0xFF;
	data_length = data_length + (unsigned int)(itmp << 24);

	run_number = data256[4] & 0xFF;
	itmp = data256[5] & 0xFF;
	run_number = run_number + (unsigned int)(itmp << 8);

	trigger_type = data256[6] & 0x0F;

	itmp = data256[6] & 0xF0;
	trigger_destination = itmp >> 4;

	trigger_number = data256[7] & 0xFF;
	itmp = data256[8] & 0xFF;
	trigger_number = trigger_number + (unsigned int)(itmp << 8);
	itmp = data256[9] & 0xFF;
	trigger_number = trigger_number + (unsigned int)(itmp << 16);
	itmp = data256[10] & 0xFF;
	trigger_number = trigger_number + (unsigned int)(itmp << 24);					

	ttime = data256[11] & 0xFF;
	ttime = ttime*8;

	ltmp = data256[12] & 0xFF;
	ttime = ttime + ltmp * 1000;
	ltmp = data256[13] & 0xFF;
	ltmp = ltmp << 8;
	ttime = ttime + ltmp * 1000;
	ltmp = data256[14] & 0xFF;
	ltmp = ltmp << 16;
	ttime = ttime + ltmp * 1000;

	mid = data256[15] & 0xFF;

	channel = data256[16] & 0xFF;

	local_tnum = data256[17] & 0xFF;
	itmp = data256[18] & 0xFF;
	local_tnum = local_tnum + (unsigned int)(itmp << 8);
	itmp = data256[19] & 0xFF;
	local_tnum = local_tnum + (unsigned int)(itmp << 16);
	itmp = data256[20] & 0xFF;
	local_tnum = local_tnum + (unsigned int)(itmp << 24);

	trigger_pattern = data256[21] & 0xFF;
	itmp = data256[22] & 0xFF;
	trigger_pattern = trigger_pattern + (unsigned int)(itmp << 8);
	itmp = data256[23] & 0xFF;
	trigger_pattern = trigger_pattern + (unsigned int)(itmp << 16);
	itmp = data256[24] & 0xFF;
	trigger_pattern = trigger_pattern + (unsigned int)(itmp << 24);

	ltime = data256[25] & 0xFF;
	ltime = ltime*8;

	ltmp = data256[26] & 0xFF;
	ltime = ltime + ltmp*1000;
	ltmp = data256[27] & 0xFF;
	ltmp = ltmp << 8;
	ltime = ltime + ltmp*1000;
	ltmp = data256[28] & 0xFF;
	ltmp = ltmp << 16;
	ltime = ltime + ltmp*1000;

	trig_timel = data256[11] & 0xFF;

	ltmp = data256[12] & 0xFF;
	trig_timeh = ltmp;
	ltmp = data256[13] & 0xFF;
	ltmp = ltmp << 8;
	trig_timeh = trig_timeh + ltmp;
	ltmp = data256[14] & 0xFF;
	ltmp = ltmp << 16;
	trig_timeh = trig_timeh + ltmp;

	start_timel = data256[25] & 0xFF;

	ltmp = data256[26] & 0xFF;
	start_timeh = ltmp;
	ltmp = data256[27] & 0xFF;
	ltmp = ltmp << 8;
	start_timeh = start_timeh + ltmp;
	ltmp = data256[28] & 0xFF;
	ltmp = ltmp << 16;
	start_timeh = start_timeh + ltmp;
	hist_point = (data_length - 32)/2;
	hist_range = hist_point * 2;
	gSystem->ProcessEvents();
	if (adcflag == 1)
	{
		if (hoscd1 == 0)
		{
			hoscd1 = new TH1F("hoscd1", "Channel1", hist_point, 0, hist_range);
			hoscd2 = new TH1F("hoscd2", "Channel2", hist_point, 0, hist_range);
			hoscd3 = new TH1F("hoscd3", "Channel3", hist_point, 0, hist_range);
			hoscd4 = new TH1F("hoscd4", "Channel4", hist_point, 0, hist_range);
			c1->cd(1);
			hoscd1->Draw();
			c1->cd(2);
			hoscd2->Draw();
			c1->cd(3);
			hoscd3->Draw();
			c1->cd(4);
			hoscd4->Draw();
			gSystem->ProcessEvents();
		}

		else
		{
			hoscd1->Reset();
			hoscd2->Reset();
			hoscd3->Reset();
			hoscd4->Reset();

			for (int j=0; j<hist_point; j++)
			{
				adc = data256[32+j*2] & 0xFF;
				itmp = data256[32+j*2+1] & 0x0F;
				adc = adc + (unsigned int)(itmp << 8);

				if (channel == 1)
					hoscd1->Fill(j*2, adc);
				else if (channel == 2)
					hoscd2->Fill(j*2, adc);
				else if (channel == 3)
					hoscd3->Fill(j*2, adc);
				else if (channel == 4)
					hoscd4->Fill(j*2, adc);
			}
			c1->cd(1);
			hoscd1->Draw();
			hoscd1->Sumw2(kFALSE);
			c1->cd(2);
			hoscd2->Draw();
			hoscd2->Sumw2(kFALSE);
			c1->cd(3);
			hoscd3->Draw();
			hoscd3->Sumw2(kFALSE);
			c1->cd(4);
			hoscd4->Draw();
			hoscd4->Sumw2(kFALSE);
			c1->Modified();
			c1->Update();
			gSystem->ProcessEvents();
		}
	}

	if (tdcflag == 1)
	{
		if (hostd1 == 0)
		{
			hostd1 = new TH1F("hostd1", "Channel1", hist_point / 4, 0, hist_range);
			hostd2 = new TH1F("hostd2", "Channel2", hist_point / 4, 0, hist_range);
			hostd3 = new TH1F("hostd3", "Channel3", hist_point / 4, 0, hist_range);
			hostd4 = new TH1F("hostd4", "Channel4", hist_point / 4, 0, hist_range);
			c2->cd(1);
			hostd1->Draw();
			c2->cd(2);
			hostd2->Draw();
			c2->cd(3);
			hostd3->Draw();
			c2->cd(4);
			hostd4->Draw();
			gSystem->ProcessEvents();
		}
		else
		{
			hostd1->Reset();
			hostd2->Reset();
			hostd3->Reset();
			hostd4->Reset();

			for (j=0; j<(hist_point / 4); j++)
			{
				tdc = (data256[32+j*8+1] >> 4) & 0xF;
				itmp = (data256[32+j*8+3] >> 4) & 0xF;
				tdc = tdc + (unsigned int)(itmp << 4);
				itmp = (data256[32+j*8+5] >> 4) & 0x3;
				tdc = tdc + (unsigned int)(itmp << 8);

				if (channel == 1)
					hostd1->Fill(j*8, tdc);
				else if (channel == 2)
					hostd2->Fill(j*8, tdc);
				else if (channel == 3)
					hostd3->Fill(j*8, tdc);
				else if (channel == 4)
					hostd4->Fill(j*8, tdc);
			}
			tdc = hostd1->GetMinimum();
			c2->cd(1);
			hostd1->Draw();
			hostd1->Sumw2(kFALSE);
			c2->cd(2);
			hostd2->Draw();
			hostd2->Sumw2(kFALSE);
			c2->cd(3);
			hostd3->Draw();
			hostd3->Sumw2(kFALSE);
			c2->cd(4);
			hostd4->Draw();
			hostd4->Sumw2(kFALSE);
			c2->Modified();
			c2->Update();
			gSystem->ProcessEvents();
		}
	}
	printf("module ID = %d, channel ID = %d\n", mid, channel);
	printf("data_length = %d, run_number = %d, trigger_type = %d, trigger_destination = %d\n", data_length, run_number, trigger_type, trigger_destination);
	printf("trigger_number = %d, local_tnum = %d, trigger_pattern = %d\n", trigger_number, local_tnum, trigger_pattern);
	printf("trigger time = %ld, local starting time = %ld\n", ttime, ltime);
	printf("-------------------------------------------------------------------------------------------------------\n");
	fprintf(lfp, "%lX  %lX  %lX  %lX  %d\n", trig_timel, trig_timeh, start_timel, start_timeh, adc);



}
