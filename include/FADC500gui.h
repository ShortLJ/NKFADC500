#ifndef FADC500GUI_H
#define FADC500GUI_H

#include "TGDockableFrame.h"
#include "TGMenu.h"
#include "TGMdiDecorFrame.h"
#include "TG3DLine.h"
#include "TGMdiFrame.h"
#include "TGMdiMainFrame.h"
#include "TGMdiMenu.h"
#include "TGListBox.h"
#include "TGNumberEntry.h"
#include "TGHtml.h"
#include "TGScrollBar.h"
#include "TGComboBox.h"
#include "TGuiBldHintsEditor.h"
#include "TGuiBldNameFrame.h"
#include "TGFrame.h"
#include "TGFileDialog.h"
#include "TGShutter.h"
#include "TGButtonGroup.h"
#include "TGCanvas.h"
#include "TGFSContainer.h"
#include "TGuiBldEditor.h"
#include "TGColorSelect.h"
#include "TGButton.h"
#include "TGFSComboBox.h"
#include "TGLabel.h"
#include "TGView.h"
#include "TRootGuiBuilder.h"
#include "TGTab.h"
#include "TGListView.h"
#include "TGSplitter.h"
#include "TGTextView.h"
#include "TGStatusBar.h"
#include "TGListTree.h"
#include "TGuiBldGeometryFrame.h"
#include "TGToolTip.h"
#include "TGToolBar.h"
#include "TGuiBldDragManager.h"
#include "TRootEmbeddedCanvas.h"
#include "TGLabel.h"
#include "TGFileDialog.h"
#include "TRootHelpDialog.h"

#include "Riostream.h"
#include "FADC500setting.h"
#include "FADC500run.h"
#include <stdio.h>
#include "TStyle.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>

class FADC500gui
{
	private :
		FADC500setting fset;
		FADC500run frun;

		int nEvent;
		int nModule;

		int module_id;
		int channel_id;
		unsigned long rl;
		unsigned long tlt;
		unsigned long cw;
		unsigned long offset;
		unsigned long dly;
		unsigned long thr;
		unsigned long tdc_thr;
		unsigned long pol;
		unsigned long psw;
		unsigned long amode;
		unsigned long pct;
		unsigned long pci;
		unsigned long pwt;
		unsigned long dt;
        unsigned long zerosup;


		TString saveFile;
		TString directory;

		TGLabel *lNMODULE;
		TGLabel *lPTRIGGER;
		TGLabel *lNEVENT;
		TGLabel *lTRIGDELAY;
		TGLabel *lTRIGCOINWIDTH;
		TGLabel *lCOINWIDTH;
		TGLabel *lADCTHR;
		TGLabel *lTDCTHR;
		TGLabel *lPCT;
		TGLabel *lPCI;
		TGLabel *lPWT;
		TGLabel *lTRIGDEAD;
		TGLabel *lOFFSET;
		TGLabel *lADELAY;
		TGLabel *lPSUMWIDTH;
		TGLabel *lDATARANGE;
		TGLabel *lTRIGTYPE;
		TGLabel *lZEROSUP;
		TGLabel *lTEN;
		TGLabel *lTEW;
		TGLabel *lTEP;
		TGLabel *lTEPO;
		TGLabel *lPOL;
		TGLabel *lADCMODE;

		TGNumberEntryField *fNMODULE;
		TGNumberEntryField *fPTRIGGER;
		TGNumberEntryField *fNEVENT;
		TGNumberEntryField *fTRIGDELAY;
		TGNumberEntryField *fTRIGCOINWIDTH;

		TGNumberEntryField *fCOINWIDTH[6][4];
		TGNumberEntryField *fADCTHR[6][4];
		TGNumberEntryField *fTDCTHR[6][4];
		TGNumberEntryField *fPCT[6][4];
		TGNumberEntryField *fPCI[6][4];
		TGNumberEntryField *fPWT[6][4];
		TGNumberEntryField *fTRIGDEAD[6][4];
		TGNumberEntryField *fOFFSET[6][4];
		TGNumberEntryField *fADELAY[6][4];
		TGNumberEntryField *fPSUMWIDTH[6][4];

		TGComboBox *fDATARANGE[6];
		TGComboBox *fTRIGTYPE[6];
		TGComboBox *fZEROSUP[6][4];
		TGComboBox *fTEN;
		TGComboBox *fTEW;
		TGComboBox *fTEP;
		TGComboBox *fTEPO;
		TGComboBox *fPOL[6][4];
		TGComboBox *fADCMODE[6][4];


	public :
		FADC500gui();
		void Savefile();
		void SaveSetting();
		void OpenSetting();
		void SetParGUI();
		void HandleMenu(Int_t menu_id);
		void TerminatePro();
		void SetNModule(char*);
		void SetPTrigger(char*);
		void SetDataRange(int);
		void SetNEvent(char*);
		void SetTrigType(int);
		void SetTrigDelay(char*);
		void SetTrigCoinWidth(char*);
		void SetCoinWidth(char*);
		void SetADCThr(char*);
		void SetTDCThr(char*);
		void SetPCT(char*);
		void SetPCI(char*);
		void SetPWT(char*);
		void SetTrigDead(char*);
		void SetZeroSup(int);
		void SetTEN(int);
		void SetTEW(int);
		void SetTEP(int);
		void SetTEPO(int);
		void SetPol(int);
		void SetOffset(char*);
		void SetADCDelay(char*);
		void SetPSumWidth(char*);
		void SetADCMode(int);
		void SetSame();
		void SetTCB();
		void RunDAQ();
		void StopDAQ();
};
#endif

