/************************************************************
NKFADC500 GUI system
Made by Byul Moon.
FADC500gui.cc source file
GUI builder for NKFADC500 DAQ.
May. 1. 2017.
***********************************************************/

#include "TROOT.h"
#include "TApplication.h"
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
#include "FADC500gui.h"
#include "FADC500setting.h"
#include "FADC500run.h"
#include <stdio.h>
#include "TStyle.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TString.h"

using namespace std;


const char gAboutNKFADC500[] = "\
				NKFADC500 GUI DAQ Program\n\
Notice Korea Flash ADC 500MHz(NKFADC500).\n\
GUI Program is built by Byul Moon from Korea Univerity.\n\
";

const char gMANUAL[] ="\
				NKFADC500 GUI DAQ Program MANUAL\n\
A. Parameters\n\
	---------------------------Global Parameters--------------------------\n\
	1. Number of Modules : input the number of modules for your work.\n\
	2. Pedestal Trigger Interval : input the time interval in ms scale for your work. 0 is for disable. If you use this fuction, the DAQ will intermittently put a trigger signal to get the pedestal.\n\
	3. Number of Events : input the total number of event that you want. When the DAQ get events as many as you set, it will stop getting data.\n\
	4. Trigger Delay : input the time delay of the trigger. The scale is in ns.\n\
	5. Trigger Coincidence Width : input the coincidence width for your setting trigger. The scale is in ns. From 8 to 32760. This is required only for AND type triggers.\n\
	6. Pulse Count Trigger : activate this fuction if you want to trigger data using the pulse count.\n\
	7. Pulse Width Trigger : activate this fuction if you want to trigger data using the pulse width.\n\
	8. Peak Sum Trigger : activate this function if you want to trigger data using the area of the pulse peak.\n\
	9. Peak Sum OR Trigger : activate this function if you want to trigger data using OR type with the area of the pulse peak.\n\
\n\
	--------------------------Local Parameters---------------------------\n\
	1. Recording Length : set the data length in time scale. The FADC digitize the pulse every 2 ns until the data length. Consistent for each module.\n\
	2. Trigger Type : set the trigger type. Master trigger is using an external trigger. Consistent for each module.\n\
	3. Coincidence Width : input the coincidence width for your work. The scale is in ns. From 8 to 32760. Able to set for every channel.\n\
	4. ADC Threshold : input the threshold for ADC signals. 1 cbt ~ 0.5 mV. Able to set for every channel.\n\
	5. TDC Threshold : input the threshold for TDC signals. 1 cbt ~ 0.5 mV for positive polarity and 1 cbt ~ 0.05 mV for negative polarity. Able to set for every channel.\n\
	6. Pulse Count Threshold : input the threshold for the pulse count trigger. From 1 to 15. Able to set for every channel.\n\
	7. Pulse Count Interval : input the time interval for the pulse count trigger. From 32 ns to 8160 ns. Able to set for every channel.\n\
	8. Pulse Width Threshold : input the threshold for the pulse width trigger. From 2 ns to 1022 ns. Able to set for every channel.\n\
	9. Trigger Deadtime : input the deadtime of the trigger if you want. From 0 to 8355840 ns. Able to set for every channel.\n\
	10. Zero Suppression : activate this function if you want to use zero suppression. Able to set for every channel.\n\
	11. Pulse Polarity : set the polarity of the pulse signal. Able to set for every channel.\n\
	12. ADC Offset : input the offset of ADC signals. 3000 is enough for negative pulses, 500 is enough for positive pulses. Able to set for every channel.\n\
	13. ADC Delay : input the delay of ADC signals. Delay time is between the trigger gate and the ADC signal. The scale is in ns. From 0 to 31992. Able to set for every channel.\n\
	14. Peak Sum Width : input the threshold for the peak sum trigger. From 2 to 16382 ns. Able to set for every channel.\n\
	15. ADC Mode : select the mode of ADCs. Able to set for every channel.\n\
\n\
B. Functions\n\
	1. SET SAME : set all parameters same as those of module#1 & channel#1.\n\
	2. TCB : transfer all parameters to TCB.\n\
	3. RUN : start the DAQ to get data.\n\
	4. STOP : stop the DAQ.\n\
	5. Save data : save the directory and filename for data.\n\
	6. Save setting : save your setting parameters.\n\
	7. Open setting : load your previous setting parameters.\n\
\n\
C. Procedure\n\
	1. Using Save data in the File banner, set the directory and datafile name.\n\
	2. Set all parameters or load the previous setting parameters using Open setting in the File banner.\n\
	3. Click 'TCB' to transfer all parameters to TCB before you start the DAQ.\n\
	4. Click 'RUN' to start the DAQ.\n\
	5. Click 'STOP' to stop getting data.\n\
	6. If you want to terminate this program, use Exit in the File banner or just click the exit button on the left top side.\n\
";

const char gCONTACT[] ="\
				NKFADC500 GUI DAQ Program CONTACT INFORMATION\n\
Please contact via the following e-mail address.\n\
mb0316@nuclear.korea.ac.kr\n\
";

enum EMyMessageTypes
{
	M_FILE_SAVE_DATA,
	M_FILE_SAVE_SETTING,
	M_FILE_OPEN_SETTING,
	M_FILE_EXIT,
	M_HELP_ABOUT,
	M_HELP_MANUAL,
	M_HELP_CONTACT
};

FADC500gui::FADC500gui()
{

	// main frame
	TGMainFrame *fMainFrame1073 = new TGMainFrame(gClient->GetRoot(),1200,650,kMainFrame | kVerticalFrame);
	fMainFrame1073->SetName("NKFADC500");
	fMainFrame1073->SetLayoutBroken(kTRUE);

	TGMenuBar* fMenuBar = new TGMenuBar(fMainFrame1073, 1200, 25, kHorizontalFrame);
	TGPopupMenu* fMenuFile = new TGPopupMenu(gClient->GetRoot());
	fMenuFile->AddEntry(" Save &Data", M_FILE_SAVE_DATA, 0, gClient->GetPicture("bld_save.png")); 
	fMenuFile->AddEntry(" &Save Setting", M_FILE_SAVE_SETTING, 0, gClient->GetPicture("bld_save.png")); 
	fMenuFile->AddEntry(" &Open Setting", M_FILE_OPEN_SETTING, 0, gClient->GetPicture("bld_open.png")); 
	fMenuFile->AddSeparator();
	fMenuFile->AddEntry(" E&xit", M_FILE_EXIT, 0, gClient->GetPicture("bld_exit.png"));
	fMenuFile->Connect("Activated(Int_t)", "FADC500gui", this, "HandleMenu(Int_t)");
	fMenuBar->AddPopup("&File", fMenuFile, new TGLayoutHints(kLHintsTop|kLHintsLeft, 0, 4, 0, 0));

	TGPopupMenu* fMenuHelp = new TGPopupMenu(gClient->GetRoot());
	fMenuHelp->AddEntry(" &About NKFADC500", M_HELP_ABOUT, 0, gClient->GetPicture("about.xpm"));
	fMenuHelp->AddEntry(" NKFADC500 &Manual", M_HELP_MANUAL);
	fMenuHelp->AddEntry(" NKFADC500 &Contact Info.", M_HELP_CONTACT);
	fMenuHelp->Connect("Activated(Int_t)", "FADC500gui", this, "HandleMenu(Int_t)");
	fMenuBar->AddPopup("&Help", fMenuHelp, new TGLayoutHints(kLHintsTop|kLHintsLeft));

	fMainFrame1073 -> AddFrame(fMenuBar, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 5));
	fMenuBar->MoveResize(0,0,1200,25);

	// tab widget
	TGTab *fTab1 = new TGTab(fMainFrame1073, 1180, 550);

	// container of "Tab1"
	TGCompositeFrame *fCompositeFrame1;
	fCompositeFrame1 = fTab1 -> AddTab("Setting");
	fCompositeFrame1 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame1));
	fCompositeFrame1 ->SetLayoutBroken(kTRUE);

	// global parameters
	TGLabel *lTitle1 = new TGLabel(fCompositeFrame1, "Global Parameters");
	lTitle1 -> SetTextJustify(kTextLeft);
	lTitle1 -> SetMargins(0, 0, 0, 0);
	lTitle1 -> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lTitle1, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lTitle1 -> MoveResize(20,10,170,20);

	lNMODULE = new TGLabel(fCompositeFrame1, "Number of Modules");
	lNMODULE -> SetTextJustify(kTextLeft);
	lNMODULE -> SetMargins(0, 0, 0, 0);
	lNMODULE -> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lNMODULE, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lNMODULE -> MoveResize(20,40,170,20);

	fNMODULE = new TGNumberEntryField(fCompositeFrame1, 0, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 100);
	fNMODULE->MoveResize(200,40,100,20);
	fCompositeFrame1->AddFrame(fNMODULE, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fNMODULE -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetNModule(const Char_t *)");

	lPTRIGGER = new TGLabel(fCompositeFrame1, "Pedestal Trigger Interval(ms)");
	lPTRIGGER -> SetTextJustify(kTextLeft);
	lPTRIGGER -> SetMargins(0, 0, 0, 0);
	lPTRIGGER -> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lPTRIGGER, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lPTRIGGER -> MoveResize(20,70,170,20);

	fPTRIGGER = new TGNumberEntryField(fCompositeFrame1, 0, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
	fPTRIGGER->MoveResize(200,70,100,20);
	fCompositeFrame1->AddFrame(fPTRIGGER, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fPTRIGGER -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetPTrigger(const Char_t *)");

	lNEVENT = new TGLabel(fCompositeFrame1, "Number of Events");
    lNEVENT -> SetTextJustify(kTextLeft);
    lNEVENT -> SetMargins(0, 0, 0, 0);
    lNEVENT -> SetWrapLength(-1);
    fCompositeFrame1 -> AddFrame(lNEVENT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lNEVENT -> MoveResize(20,100,170,20);

    fNEVENT = new TGNumberEntryField(fCompositeFrame1, 0, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 100000000);
    fNEVENT->MoveResize(200,100,100,20);
    fCompositeFrame1->AddFrame(fNEVENT, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fNEVENT -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetNEvent(const Char_t *)");

    lTRIGDELAY = new TGLabel(fCompositeFrame1, "Trigger Delay(ns)");
    lTRIGDELAY -> SetTextJustify(kTextLeft);
    lTRIGDELAY -> SetMargins(0, 0, 0, 0);
    lTRIGDELAY -> SetWrapLength(-1);
    fCompositeFrame1 -> AddFrame(lTRIGDELAY, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lTRIGDELAY -> MoveResize(20,160,170,20);

    fTRIGDELAY = new TGNumberEntryField(fCompositeFrame1, 0, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 32768);
    fTRIGDELAY->MoveResize(200,160,100,20);
    fCompositeFrame1->AddFrame(fTRIGDELAY, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fTRIGDELAY -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetTrigDelay(const Char_t *)");

    lTRIGCOINWIDTH = new TGLabel(fCompositeFrame1, "Trigger Coincidence Width(ns)");
    lTRIGCOINWIDTH -> SetTextJustify(kTextLeft);
    lTRIGCOINWIDTH -> SetMargins(0, 0, 0, 0);
    lTRIGCOINWIDTH -> SetWrapLength(-1);
    fCompositeFrame1 -> AddFrame(lTRIGCOINWIDTH, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lTRIGCOINWIDTH -> MoveResize(20,190,170,20);

    fTRIGCOINWIDTH = new TGNumberEntryField(fCompositeFrame1, 0, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 8, 32760);
    fTRIGCOINWIDTH->MoveResize(200,190,100,20);
    fCompositeFrame1->AddFrame(fTRIGCOINWIDTH, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fTRIGCOINWIDTH -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetTrigCoinWidth(const Char_t *)");

	lTEN = new TGLabel(fCompositeFrame1, "Pulse Count Trigger");
	lTEN -> SetTextJustify(kTextLeft);
	lTEN -> SetMargins(0, 0, 0, 0);
	lTEN -> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lTEN, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lTEN -> MoveResize(20,220,170,20);

	fTEN = new TGComboBox(fCompositeFrame1,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fTEN->SetName("Pulse Count Trigger");
	fTEN->AddEntry("Yes",0);
	fTEN->AddEntry("No",1);
	fTEN->Resize(100,20);
	fTEN->Select(-1);
	fCompositeFrame1->AddFrame(fTEN, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fTEN->MoveResize(200,220,100,20);
	fTEN->Connect("Selected(Int_t)", "FADC500gui", this, "SetTEN(Int_t)");

	lTEW = new TGLabel(fCompositeFrame1, "Pulse Width Trigger");
	lTEW -> SetTextJustify(kTextLeft);
	lTEW -> SetMargins(0, 0, 0, 0); 
	lTEW -> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lTEW, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lTEW -> MoveResize(20,250,170,20);

	fTEW = new TGComboBox(fCompositeFrame1,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fTEW->SetName("Pulse Width Trigger");
	fTEW->AddEntry("Yes",0);
	fTEW->AddEntry("No",1);
	fTEW->Resize(100,20);
	fTEW->Select(-1);
	fCompositeFrame1->AddFrame(fTEW, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fTEW->MoveResize(200,250,100,20);
	fTEW->Connect("Selected(Int_t)", "FADC500gui", this, "SetTEW(Int_t)");

	lTEP = new TGLabel(fCompositeFrame1, "Peak Sum Trigger");
	lTEP -> SetTextJustify(kTextLeft);
	lTEP -> SetMargins(0, 0, 0, 0);
	lTEP -> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lTEP, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lTEP -> MoveResize(20,280,170,20);

	fTEP = new TGComboBox(fCompositeFrame1,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fTEP->SetName("Peak Sum Trigger");
	fTEP->AddEntry("Yes",0);
	fTEP->AddEntry("No",1);
	fTEP->Resize(100,20);
	fTEP->Select(-1);
	fCompositeFrame1->AddFrame(fTEP, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fTEP->MoveResize(200,280,100,20);
	fTEP->Connect("Selected(Int_t)", "FADC500gui", this, "SetTEP(Int_t)");

	lTEPO = new TGLabel(fCompositeFrame1, "Peak Sum OR Trigger");
	lTEPO -> SetTextJustify(kTextLeft);
	lTEPO -> SetMargins(0, 0, 0, 0);
	lTEPO -> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lTEPO, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lTEPO -> MoveResize(20,310,170,20);

	fTEPO = new TGComboBox(fCompositeFrame1,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fTEPO->SetName("Peak Sum OR Trigger");
	fTEPO->AddEntry("Yes",0);
	fTEPO->AddEntry("No",1);
	fTEPO->Resize(100,20);
	fTEPO->Select(-1);
	fCompositeFrame1->AddFrame(fTEPO, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fTEPO->MoveResize(200,310,100,20);
	fTEPO->Connect("Selected(Int_t)", "FADC500gui", this, "SetTEPO(Int_t)");

	// function buttons

	TGTextButton *SET = new TGTextButton(fCompositeFrame1,"SET SAME",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    SET -> Connect("Clicked()", "FADC500gui", this, "SetSame()");
    SET->SetTextJustify(36);
    SET->SetMargins(0,0,0,0);
    SET->SetWrapLength(-1);
    SET->Resize(100,35);
    fCompositeFrame1->AddFrame(SET, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    SET->MoveResize(20,450,100,35);

	TGTextButton *TCB = new TGTextButton(fCompositeFrame1,"TCB",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    TCB -> Connect("Clicked()", "FADC500gui", this, "SetTCB()");
    TCB->SetTextJustify(36);
    TCB->SetMargins(0,0,0,0);
    TCB->SetWrapLength(-1);
    TCB->Resize(100,35);
    fCompositeFrame1->AddFrame(TCB, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    TCB->MoveResize(150,450,100,35);

	TGTextButton *RUN = new TGTextButton(fCompositeFrame1,"RUN",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    RUN -> Connect("Clicked()", "FADC500gui", this, "RunDAQ()");
    RUN->SetTextJustify(36);
    RUN->SetMargins(0,0,0,0);
    RUN->SetWrapLength(-1);
    RUN->Resize(100,35);
    fCompositeFrame1->AddFrame(RUN, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    RUN->MoveResize(280,450,100,35);

    TGTextButton *STOP = new TGTextButton(fCompositeFrame1,"STOP",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    STOP -> Connect("Clicked()", "FADC500gui", this, "StopDAQ()");
    STOP->SetTextJustify(36);
    STOP->SetMargins(0,0,0,0);
    STOP->SetWrapLength(-1);
    STOP->Resize(100,35);
    fCompositeFrame1->AddFrame(STOP, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    STOP->MoveResize(410,450,100,35);



	// subtab for module setting

	TGTab *fSubTab = new TGTab(fCompositeFrame1, 590, 550);
	TGTab *fSSubTab[6];

	// container of "SubTab"
	TGCompositeFrame *fModuleFrame[6];
	TGCompositeFrame *fChannelFrame[6][4];
	for (int i = 0; i < 6; i++)
	{
		fModuleFrame[i] = fSubTab -> AddTab(Form("Module#%d",i+1));
		fModuleFrame[i] -> SetLayoutManager(new TGVerticalLayout(fModuleFrame[i]));
		fModuleFrame[i] ->SetLayoutBroken(kTRUE);


		lDATARANGE = new TGLabel(fModuleFrame[i], "Recording Length");
		lDATARANGE -> SetTextJustify(kTextLeft);
		lDATARANGE -> SetMargins(0, 0, 0, 0);
		lDATARANGE -> SetWrapLength(-1);
		fModuleFrame[i] -> AddFrame(lDATARANGE, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
		lDATARANGE -> MoveResize(20,10,170,20);

		fDATARANGE[i] = new TGComboBox(fModuleFrame[i],i);
		fDATARANGE[i]->SetName("Recording Length");
		fDATARANGE[i]->AddEntry("128 ns",0);
		fDATARANGE[i]->AddEntry("256 ns",1);
		fDATARANGE[i]->AddEntry("512 ns",2);
		fDATARANGE[i]->AddEntry("1 us",3);
		fDATARANGE[i]->AddEntry("2 us",4);
		fDATARANGE[i]->AddEntry("4 us",5);
		fDATARANGE[i]->AddEntry("8 us",6);
		fDATARANGE[i]->AddEntry("16 us",7);
		fDATARANGE[i]->AddEntry("32 us",8);
		fDATARANGE[i]->Resize(100,20);
		fDATARANGE[i]->Select(-1);
		fModuleFrame[i]->AddFrame(fDATARANGE[i], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
		fDATARANGE[i]->MoveResize(200,10,100,20);
		fDATARANGE[i]->Connect("Selected(Int_t)", "FADC500gui", this, "SetDataRange(Int_t)");

		lTRIGTYPE = new TGLabel(fModuleFrame[i], "Trigger Type");
		lTRIGTYPE -> SetTextJustify(kTextLeft);
		lTRIGTYPE -> SetMargins(0, 0, 0, 0);
		lTRIGTYPE -> SetWrapLength(-1);
		fModuleFrame[i] -> AddFrame(lTRIGTYPE, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
		lTRIGTYPE -> MoveResize(20,40,170,20);

		fTRIGTYPE[i] = new TGComboBox(fModuleFrame[i],i);
		fTRIGTYPE[i]->SetName("Trigger Type");
		fTRIGTYPE[i]->AddEntry("Master",0);
		fTRIGTYPE[i]->AddEntry("1|2|3|4",1);
		fTRIGTYPE[i]->AddEntry("Only 1",2);
		fTRIGTYPE[i]->AddEntry("Only 2",3);
		fTRIGTYPE[i]->AddEntry("Only 3",4);
		fTRIGTYPE[i]->AddEntry("Only 4",5);
		fTRIGTYPE[i]->AddEntry("1|2",6);
		fTRIGTYPE[i]->AddEntry("1|3",7);
		fTRIGTYPE[i]->AddEntry("1|4",8);
		fTRIGTYPE[i]->AddEntry("2|3",9);
		fTRIGTYPE[i]->AddEntry("2|4",10);
		fTRIGTYPE[i]->AddEntry("3|4",11);
		fTRIGTYPE[i]->AddEntry("1&2",12);
		fTRIGTYPE[i]->AddEntry("1&3",13);
		fTRIGTYPE[i]->AddEntry("1&4",14);
		fTRIGTYPE[i]->AddEntry("2&3",15);
		fTRIGTYPE[i]->AddEntry("2&4",16);
		fTRIGTYPE[i]->AddEntry("3&4",17);
		fTRIGTYPE[i]->AddEntry("(1&2)|(3&4)",18);
		fTRIGTYPE[i]->AddEntry("1|(2&3&4)",19);
		fTRIGTYPE[i]->AddEntry("1&2&3&4",20);
		fModuleFrame[i]->AddFrame(fTRIGTYPE[i], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
		fTRIGTYPE[i]->MoveResize(200,40,100,20);
		fTRIGTYPE[i]->Connect("Selected(Int_t)", "FADC500gui", this, "SetTrigType(Int_t)");


		fSSubTab[i] = new TGTab(fModuleFrame[i], 580, 450);


		// local parameters : channels
		for (int j = 0; j < 4; j++)
		{
			int widgetID = i*100 + j*10;
			fChannelFrame[i][j] = fSSubTab[i] -> AddTab(Form("Channel#%d",j+1));
			fChannelFrame[i][j] -> SetLayoutManager(new TGVerticalLayout(fChannelFrame[i][j]));
			fChannelFrame[i][j] ->SetLayoutBroken(kTRUE);

			lCOINWIDTH = new TGLabel(fChannelFrame[i][j], "Coincidence Width(ns)");
			lCOINWIDTH -> SetTextJustify(kTextLeft);
			lCOINWIDTH -> SetMargins(0, 0, 0, 0);
			lCOINWIDTH -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lCOINWIDTH, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lCOINWIDTH -> MoveResize(20,10,170,20);

			fCOINWIDTH[i][j] = new TGNumberEntryField(fChannelFrame[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 8, 32760);
			fCOINWIDTH[i][j]->MoveResize(200,10,100,20);
			fChannelFrame[i][j]->AddFrame(fCOINWIDTH[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fCOINWIDTH[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetCoinWidth(const Char_t *)");

			lADCTHR = new TGLabel(fChannelFrame[i][j], "ADC Threshold");
			lADCTHR -> SetTextJustify(kTextLeft);
			lADCTHR -> SetMargins(0, 0, 0, 0);
			lADCTHR -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lADCTHR, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lADCTHR -> MoveResize(20,40,170,20);

			fADCTHR[i][j] = new TGNumberEntryField(fChannelFrame[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
			fADCTHR[i][j]->MoveResize(200,40,100,20);
			fChannelFrame[i][j]->AddFrame(fADCTHR[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fADCTHR[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetADCThr(const Char_t *)");

			lTDCTHR = new TGLabel(fChannelFrame[i][j], "TDC Threshold");
			lTDCTHR -> SetTextJustify(kTextLeft);
			lTDCTHR -> SetMargins(0, 0, 0, 0);
			lTDCTHR -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lTDCTHR, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lTDCTHR -> MoveResize(20,70,170,20);

			fTDCTHR[i][j] = new TGNumberEntryField(fChannelFrame[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 40960);
			fTDCTHR[i][j]->MoveResize(200,70,100,20);
			fChannelFrame[i][j]->AddFrame(fTDCTHR[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fTDCTHR[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetTDCThr(const Char_t *)");

			lPCT = new TGLabel(fChannelFrame[i][j], "Pulse Count Threshold");
			lPCT -> SetTextJustify(kTextLeft);
			lPCT -> SetMargins(0, 0, 0, 0);
			lPCT -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lPCT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lPCT -> MoveResize(20,100,170,20);

			fPCT[i][j] = new TGNumberEntryField(fChannelFrame[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 1, 15);
			fPCT[i][j]->MoveResize(200,100,100,20);
			fChannelFrame[i][j]->AddFrame(fPCT[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fPCT[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetPCT(const Char_t *)");

			lPCI = new TGLabel(fChannelFrame[i][j], "Pulse Count Interval(ns)");
			lPCI -> SetTextJustify(kTextLeft);
			lPCI -> SetMargins(0, 0, 0, 0);
			lPCI -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lPCI, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lPCI -> MoveResize(20,130,170,20);

			fPCI[i][j] = new TGNumberEntryField(fChannelFrame[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 32, 8160);
			fPCI[i][j]->MoveResize(200,130,100,20);
			fChannelFrame[i][j]->AddFrame(fPCI[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fPCI[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetPCI(const Char_t *)");

			lPWT = new TGLabel(fChannelFrame[i][j], "Pulse Width Threshold(ns)");
			lPWT -> SetTextJustify(kTextLeft);
			lPWT -> SetMargins(0, 0, 0, 0);
			lPWT -> SetWrapLength(-1);
			fChannelFrame[i][j]-> AddFrame(lPWT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lPWT -> MoveResize(20,160,170,20);

			fPWT[i][j] = new TGNumberEntryField(fChannelFrame[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 2, 1022);
			fPWT[i][j]->MoveResize(200,160,100,20);
			fChannelFrame[i][j]->AddFrame(fPWT[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fPWT[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetPWT(const Char_t *)");

			lTRIGDEAD = new TGLabel(fChannelFrame[i][j], "Trigger Deadtime(ns)");
			lTRIGDEAD -> SetTextJustify(kTextLeft);
			lTRIGDEAD -> SetMargins(0, 0, 0, 0);
			lTRIGDEAD -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lTRIGDEAD, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lTRIGDEAD -> MoveResize(20,190,170,20);

			fTRIGDEAD[i][j] = new TGNumberEntryField(fChannelFrame[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 8355840);
			fTRIGDEAD[i][j]->MoveResize(200,190,100,20);
			fChannelFrame[i][j]->AddFrame(fTRIGDEAD[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fTRIGDEAD[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetTrigDead(const Char_t *)");

			lZEROSUP = new TGLabel(fChannelFrame[i][j], "Zero Suppression");
			lZEROSUP -> SetTextJustify(kTextLeft);
			lZEROSUP -> SetMargins(0, 0, 0, 0);
			lZEROSUP -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lZEROSUP, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lZEROSUP -> MoveResize(20,220,170,20);

			fZEROSUP[i][j] = new TGComboBox(fChannelFrame[i][j],widgetID);
			fZEROSUP[i][j]->SetName("Zero Suppression");
			fZEROSUP[i][j]->AddEntry("Yes",0);
			fZEROSUP[i][j]->AddEntry("No",1);
			fZEROSUP[i][j]->Resize(100,20);
			fZEROSUP[i][j]->Select(-1);
			fChannelFrame[i][j]->AddFrame(fZEROSUP[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fZEROSUP[i][j]->MoveResize(200,220,100,20);
			fZEROSUP[i][j]->Connect("Selected(Int_t)", "FADC500gui", this, "SetZeroSup(Int_t)");

			lPOL = new TGLabel(fChannelFrame[i][j], "Pulse Polarity");
			lPOL -> SetTextJustify(kTextLeft);
			lPOL -> SetMargins(0, 0, 0, 0);
			lPOL -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lPOL, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lPOL -> MoveResize(20,250,170,20);

			fPOL[i][j] = new TGComboBox(fChannelFrame[i][j],widgetID);
			fPOL[i][j]->SetName("Pulse Polarity");
			fPOL[i][j]->AddEntry("Negative",0);
			fPOL[i][j]->AddEntry("Positive",1);
			fPOL[i][j]->Resize(100,20);
			fPOL[i][j]->Select(-1);
			fChannelFrame[i][j]->AddFrame(fPOL[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fPOL[i][j]->MoveResize(200,250,100,20);
			fPOL[i][j]->Connect("Selected(Int_t)", "FADC500gui", this, "SetPol(Int_t)");

			lOFFSET = new TGLabel(fChannelFrame[i][j], "ADC Offset");
			lOFFSET -> SetTextJustify(kTextLeft);
			lOFFSET -> SetMargins(0, 0, 0, 0);
			lOFFSET -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lOFFSET, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lOFFSET -> MoveResize(20,280,170,20);

			fOFFSET[i][j] = new TGNumberEntryField(fChannelFrame[i][j],widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4095);
			fOFFSET[i][j]->MoveResize(200,280,100,20);
			fChannelFrame[i][j]->AddFrame(fOFFSET[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fOFFSET[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetOffset(const Char_t *)");

			lADELAY = new TGLabel(fChannelFrame[i][j], "ADC Delay(ns)");
			lADELAY -> SetTextJustify(kTextLeft);
			lADELAY -> SetMargins(0, 0, 0, 0);
			lADELAY -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lADELAY, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lADELAY -> MoveResize(20,310,170,20);

			fADELAY[i][j] = new TGNumberEntryField(fChannelFrame[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 31992);
			fADELAY[i][j]->MoveResize(200,310,100,20);
			fChannelFrame[i][j]->AddFrame(fADELAY[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fADELAY[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetADCDelay(const Char_t *)");

			lPSUMWIDTH = new TGLabel(fChannelFrame[i][j], "Peak Sum Width(ns)");
			lPSUMWIDTH -> SetTextJustify(kTextLeft);
			lPSUMWIDTH -> SetMargins(0, 0, 0, 0);
			lPSUMWIDTH -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lPSUMWIDTH, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lPSUMWIDTH -> MoveResize(20,340,170,20);

			fPSUMWIDTH[i][j] = new TGNumberEntryField(fChannelFrame[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 2, 16382);
			fPSUMWIDTH[i][j]->MoveResize(200,340,100,20);
			fChannelFrame[i][j]->AddFrame(fPSUMWIDTH[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fPSUMWIDTH[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500gui", this, "SetPSumWidth(const Char_t *)");

			lADCMODE = new TGLabel(fChannelFrame[i][j], "ADC Mode");
			lADCMODE -> SetTextJustify(kTextLeft);
			lADCMODE -> SetMargins(0, 0, 0, 0);
			lADCMODE -> SetWrapLength(-1);
			fChannelFrame[i][j] -> AddFrame(lADCMODE, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
			lADCMODE -> MoveResize(20,370,170,20);

			fADCMODE[i][j] = new TGComboBox(fChannelFrame[i][j],widgetID,kHorizontalFrame | kSunkenFrame | kOwnBackground);
			fADCMODE[i][j]->SetName("ADC Mode");
			fADCMODE[i][j]->AddEntry("Raw",0);
			fADCMODE[i][j]->AddEntry("Filtered",1);
			fADCMODE[i][j]->Resize(100,20);
			fADCMODE[i][j]->Select(-1);
			fChannelFrame[i][j]->AddFrame(fADCMODE[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			fADCMODE[i][j]->MoveResize(200,370,100,20);
			fADCMODE[i][j]->Connect("Selected(Int_t)", "FADC500gui", this, "SetADCMode(Int_t)");
		}
	}

	// container for tab2
	TGCompositeFrame *fCompositeFrame2;
	fCompositeFrame2 = fTab1 -> AddTab("Online ADC Monitoring");
	fCompositeFrame2 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame2));
	fCompositeFrame2 ->SetLayoutBroken(kTRUE);

	TRootEmbeddedCanvas *monitorADC = new TRootEmbeddedCanvas(0,fCompositeFrame2,1000,500,kSunkenFrame);
	monitorADC->SetName("monitorADC");
	Int_t wmonitorADC = monitorADC->GetCanvasWindowId();
	frun.c1 = new TCanvas("cvs1", 10, 10, wmonitorADC);
	frun.c1 -> Divide(2,2);
	monitorADC->AdoptCanvas(frun.c1);
	fCompositeFrame2->AddFrame(monitorADC, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	monitorADC->MoveResize(10,10,1000,500);

	TGTextButton *ADCON = new TGTextButton(fCompositeFrame2,"HIST ON",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    ADCON -> Connect("Clicked()", "FADC500gui", this, "ADCOn()");
    ADCON->SetTextJustify(36);
    ADCON->SetMargins(0,0,0,0);
    ADCON->SetWrapLength(-1);
    ADCON->Resize(100,35);
    fCompositeFrame2->AddFrame(ADCON, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    ADCON->MoveResize(1050,100,100,35);

	TGTextButton *ADCOFF = new TGTextButton(fCompositeFrame2,"HIST OFF",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    ADCOFF -> Connect("Clicked()", "FADC500gui", this, "ADCOff()");
    ADCOFF->SetTextJustify(36);
    ADCOFF->SetMargins(0,0,0,0);
    ADCOFF->SetWrapLength(-1);
    ADCOFF->Resize(100,35);
    fCompositeFrame2->AddFrame(ADCOFF, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    ADCOFF->MoveResize(1050,150,100,35);


	// container for tab3
	TGCompositeFrame *fCompositeFrame3;
	fCompositeFrame3 = fTab1 -> AddTab("Online TDC Monitoring");
	fCompositeFrame3 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame2));
	fCompositeFrame3 ->SetLayoutBroken(kTRUE);

	TRootEmbeddedCanvas *monitorTDC = new TRootEmbeddedCanvas(0,fCompositeFrame3,1000,500,kSunkenFrame);
	monitorTDC->SetName("monitorTDC");
	Int_t wmonitorTDC = monitorTDC->GetCanvasWindowId();
	frun.c2 = new TCanvas("cvs2", 10, 10, wmonitorTDC);
	frun.c2 -> Divide(2,2);
	monitorTDC->AdoptCanvas(frun.c2);
	fCompositeFrame3->AddFrame(monitorTDC, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	monitorTDC->MoveResize(10,10,1000,500);

	TGTextButton *TDCON = new TGTextButton(fCompositeFrame3,"HIST ON",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    TDCON -> Connect("Clicked()", "FADC500gui", this, "TDCOn()");
    TDCON->SetTextJustify(36);
    TDCON->SetMargins(0,0,0,0);
    TDCON->SetWrapLength(-1);
    TDCON->Resize(100,35);
    fCompositeFrame3->AddFrame(TDCON, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    TDCON->MoveResize(1050,100,100,35);

	TGTextButton *TDCOFF = new TGTextButton(fCompositeFrame3,"HIST OFF",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    TDCOFF -> Connect("Clicked()", "FADC500gui", this, "TDCOff()");
    TDCOFF->SetTextJustify(36);
    TDCOFF->SetMargins(0,0,0,0);
    TDCOFF->SetWrapLength(-1);
    TDCOFF->Resize(100,35);
    fCompositeFrame3->AddFrame(TDCOFF, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    TDCOFF->MoveResize(1050,150,100,35);



	TGLabel *lCOPYRIGHT = new TGLabel(fMainFrame1073, "Copyright 2017. B. Moon");
    lCOPYRIGHT -> SetTextJustify(kTextLeft);
    lCOPYRIGHT -> SetMargins(0, 0, 0, 0);
    lCOPYRIGHT -> SetWrapLength(-1);
    fMainFrame1073 -> AddFrame(lCOPYRIGHT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lCOPYRIGHT -> MoveResize(1050, 590, 200, 20);




	fTab1 -> SetTab(0);
	fTab1->Resize(fTab1->GetDefaultSize());
	fMainFrame1073->AddFrame(fTab1, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fTab1->MoveResize(10,25,1180,560);

	fSubTab -> SetTab(0);
	fSubTab->Resize(fSubTab->GetDefaultSize());
	fCompositeFrame1->AddFrame(fSubTab, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fSubTab->MoveResize(580,10,590,520);

	for (int i = 0; i < 6; i++)
	{
		fSSubTab[i] -> SetTab(0);
		fSSubTab[i]->Resize(fSSubTab[i]->GetDefaultSize());
		fModuleFrame[i]->AddFrame(fSSubTab[i], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
		fSSubTab[i]->MoveResize(10,70,570,420);
	}

	fMainFrame1073->SetMWMHints(kMWMDecorAll, kMWMFuncAll, kMWMInputModeless);
	fMainFrame1073->MapSubwindows();

	fMainFrame1073->Resize(fMainFrame1073->GetDefaultSize());
	fMainFrame1073->MapWindow();
	fMainFrame1073->Resize(1200,620);

	fMainFrame1073->SetWindowName("NKFADC500 PROTOTYPE");
	fMainFrame1073->MapSubwindows();
	fMainFrame1073->Connect("CloseWindow()", "FADC500gui", this, "TerminatePro()");

}

void FADC500gui::Savefile()
{
	TGFileInfo fileInfo;
	const Char_t *fileType[4] = {"Data File", "*.dat", 0, 0};
	fileInfo.fFileTypes = fileType;
	new TGFileDialog(gClient -> GetRoot(), 0, kFDSave, &fileInfo);

	// If user clicks cancel, do nothing.
	if (fileInfo.fFilename == NULL)
		return;

	// Get the file name with path
	TString filenameWithPath = fileInfo.fFilename;
	TObjArray *decomposedFileNameWithPath = filenameWithPath.Tokenize("/");
	saveFile = ((TObjString *) decomposedFileNameWithPath -> Last()) -> GetString();
	directory = filenameWithPath.ReplaceAll(saveFile, "");

	cout << "Directory : " << directory << endl;
	cout << "Filename : " << saveFile << endl;

	delete decomposedFileNameWithPath;
}

void FADC500gui::SaveSetting()
{
	TGFileInfo fileInfo;
    const Char_t *fileType[4] = {"Setting Data File", "*.parsetdat", 0, 0};
    fileInfo.fFileTypes = fileType;
    new TGFileDialog(gClient -> GetRoot(), 0, kFDSave, &fileInfo);
    
    // If user clicks cancel, do nothing.
    if (fileInfo.fFilename == NULL)
        return;
    
    // Get the file name with path
    TString filenameWithPath = fileInfo.fFilename;
    TObjArray *decomposedFileNameWithPath = filenameWithPath.Tokenize("/");
    TString savesettingFile = ((TObjString *) decomposedFileNameWithPath -> Last()) -> GetString();
    TString settingdirectory = filenameWithPath.ReplaceAll(saveFile, "");
    
    cout << "Directory : " << settingdirectory << endl;
    cout << "Filename : " << savesettingFile << endl;
    
    delete decomposedFileNameWithPath;

	ofstream savesetting(filenameWithPath.Data());

	savesetting << nModule << endl;
	savesetting << nEvent << endl;
	savesetting << fset.ptrig_interval << endl;
	savesetting << fset.trigdly << endl;
	savesetting << fset.cw_tcb << endl;
	savesetting << fset.ten << endl;
	savesetting << fset.tew << endl;
	savesetting << fset.tep << endl;
	savesetting << fset.tep2 << endl;
	for (int i = 0; i < 6; i++)
	{
		savesetting << fset.rl[i] << endl;
		savesetting << fset.tlt[i] << endl;
		for (int j = 0; j < 4; j++)
		{
			savesetting << fset.cw[i][j] << endl;
			savesetting << fset.offset[i][j] << endl;
			savesetting << fset.dly[i][j] << endl;
			savesetting << fset.thr[i][j] << endl;
			savesetting << fset.tdc_thr[i][j] << endl;
			savesetting << fset.pol[i][j] << endl;
			savesetting << fset.psw[i][j] << endl;
			savesetting << fset.amode[i][j] << endl;
			savesetting << fset.pct[i][j] << endl;
			savesetting << fset.pci[i][j] << endl;
			savesetting << fset.pwt[i][j] << endl;
			savesetting << fset.dt[i][j] << endl;
			savesetting << fset.zerosup[i][j] << endl;
		}
	}
	savesetting.close();
}

void FADC500gui::OpenSetting()
{
	TGFileInfo fileInfo;
    const Char_t *fileType[4] = {"Setting Data File", "*.parsetdat", 0, 0};
    fileInfo.fFileTypes = fileType;
    new TGFileDialog(gClient -> GetRoot(), 0, kFDOpen, &fileInfo);

    // If user clicks cancel, do nothing.
    if (fileInfo.fFilename == NULL)
        return;

    // Get the file name with path
    TString filenameWithPath = fileInfo.fFilename;
    TObjArray *decomposedFileNameWithPath = filenameWithPath.Tokenize("/");
    TString savesettingFile = ((TObjString *) decomposedFileNameWithPath -> Last()) -> GetString();
    TString settingdirectory = filenameWithPath.ReplaceAll(saveFile, "");

    cout << "Directory : " << settingdirectory << endl;
    cout << "Filename : " << savesettingFile << endl;
   
    delete decomposedFileNameWithPath;

	cout << "Start to read the setting parameters." << endl;


	fstream savesetting(filenameWithPath.Data());

    savesetting >> nModule;
    savesetting >> nEvent;
    savesetting >> fset.ptrig_interval;
    savesetting >> fset.trigdly;
    savesetting >> fset.cw_tcb;
    savesetting >> fset.ten;
    savesetting >> fset.tew;
    savesetting >> fset.tep;
    savesetting >> fset.tep2;
	for (int i = 0; i < 6; i++)
	{
	    savesetting >> fset.rl[i];
	    savesetting >> fset.tlt[i];
		for (int j = 0; j < 4; j++)
		{
		    savesetting >> fset.cw[i][j];
		    savesetting >> fset.offset[i][j];
		    savesetting >> fset.dly[i][j];
		    savesetting >> fset.thr[i][j];
		    savesetting >> fset.tdc_thr[i][j];
		    savesetting >> fset.pol[i][j];
		    savesetting >> fset.psw[i][j];
		    savesetting >> fset.amode[i][j];
		    savesetting >> fset.pct[i][j];
		    savesetting >> fset.pci[i][j];
		    savesetting >> fset.pwt[i][j];
		    savesetting >> fset.dt[i][j];
		    savesetting >> fset.zerosup[i][j];
		}
	}
    savesetting.close();

    cout << "Number of modules : " << nModule << endl;
    cout << "Number of events : " << nEvent << endl;
	cout << "Pedestal trigger interval : " << fset.ptrig_interval << endl;
	cout << "Trigger delay : " << fset.trigdly << endl;
	cout << "Trigger coincidence time window : " << fset.cw_tcb << endl;
	cout << "Pulse count trigger : " << fset.ten << endl;
	cout << "Pulse width trigger : " << fset.tew << endl;
	cout << "Peak sum trigger : " << fset.tep << endl;
	cout << "Peak sum OR trigger : " << fset.tep2 << endl;

	for (int i = 0; i < 6; i++)
	{
		cout << "*************** Module #" << i+1 << " ****************" << endl;
		cout << "Digitizing length type : " << fset.rl[i] << endl;
		cout << "Trigger type : " << fset.tlt[i] << endl;
		for (int j = 0; j < 4; j++)
		{
			cout << "*************** Channel #" << j+1 << " ****************" << endl;
			cout << "Coincidnece time window : " << fset.cw[i][j] << endl;
			cout << "ADC offset : " << fset.offset[i][j] << endl;
			cout << "ADC delay : " << fset.dly[i][j] << endl;
			cout << "ADC threshold : " << fset.thr[i][j] << endl;
			cout << "TDC threshold : " << fset.tdc_thr[i][j] << endl;
			cout << "Pulse polarity : " << fset.pol[i][j] << endl;
			cout << "Peak sum width : " << fset.psw[i][j] << endl;
			cout << "ADC mode : " << fset.amode[i][j] << endl;
			cout << "Pulse count threshold : " << fset.pct[i][j] << endl;
			cout << "Pulse count interval : " << fset.pci[i][j] << endl;
			cout << "Pulse width threshold : " << fset.pwt[i][j] << endl;
			cout << "Trigger deadtime : " << fset.dt[i][j] << endl;
			cout << "Zero suppression : " << fset.zerosup[i][j] << endl;
		}
	}
	cout << "***** Finished loading parameters. *****" << endl;

	SetParGUI();
}

void FADC500gui::SetParGUI()
{
	fNMODULE -> SetText(Form("%d", nModule), kFALSE);
	fPTRIGGER -> SetText(Form("%lu", fset.ptrig_interval), kFALSE);
	fNEVENT -> SetText(Form("%d", nEvent), kFALSE);
	fTRIGDELAY -> SetText(Form("%lu", fset.trigdly), kFALSE);
	fTRIGCOINWIDTH -> SetText(Form("%lu", fset.cw_tcb), kFALSE);
	
	if (fset.ten == 1) fTEN -> Select(0);
	if (fset.ten == 0) fTEN -> Select(1);
	
	if (fset.tew == 1) fTEW -> Select(0);
	if (fset.tew == 0) fTEW -> Select(1);
	
	if (fset.tep == 1) fTEP -> Select(0);
	if (fset.tep == 0) fTEP -> Select(1);
	
	if (fset.tep2 == 1) fTEPO -> Select(0);
	if (fset.tep2 == 0) fTEPO -> Select(1);
	
	for (int i = 0; i < 6;  i++)
	{
		if (fset.rl[i] == 1)	fDATARANGE[i] -> Select(0);
		if (fset.rl[i] == 2)	fDATARANGE[i] -> Select(1);
		if (fset.rl[i] == 4)	fDATARANGE[i] -> Select(2);
		if (fset.rl[i] == 8)	fDATARANGE[i] -> Select(3);
		if (fset.rl[i] == 16)	fDATARANGE[i] -> Select(4);
		if (fset.rl[i] == 32)	fDATARANGE[i] -> Select(5);
		if (fset.rl[i] == 64)	fDATARANGE[i] -> Select(6);
		if (fset.rl[i] == 128)	fDATARANGE[i] -> Select(7);
		if (fset.rl[i] == 256)	fDATARANGE[i] -> Select(8);

	    if (fset.tlt[i] == 0x0000) fTRIGTYPE[i] -> Select(0);
	    if (fset.tlt[i] == 0xFFFE) fTRIGTYPE[i] -> Select(1);
	    if (fset.tlt[i] == 0xAAAA) fTRIGTYPE[i] -> Select(2);
	    if (fset.tlt[i] == 0xDDDD) fTRIGTYPE[i] -> Select(3);
	    if (fset.tlt[i] == 0xF0F0) fTRIGTYPE[i] -> Select(4);
	    if (fset.tlt[i] == 0xFF00) fTRIGTYPE[i] -> Select(5);
	    if (fset.tlt[i] == 0xEEEE) fTRIGTYPE[i] -> Select(6);
	    if (fset.tlt[i] == 0xF2F2) fTRIGTYPE[i] -> Select(7);
	    if (fset.tlt[i] == 0xFFA2) fTRIGTYPE[i] -> Select(8);
	    if (fset.tlt[i] == 0xFCFC) fTRIGTYPE[i] -> Select(9);
	    if (fset.tlt[i] == 0xFFCC) fTRIGTYPE[i] -> Select(10);
	    if (fset.tlt[i] == 0xFFF0) fTRIGTYPE[i] -> Select(11);
	    if (fset.tlt[i] == 0x8888) fTRIGTYPE[i] -> Select(12);
	    if (fset.tlt[i] == 0xA0A0) fTRIGTYPE[i] -> Select(13);
	    if (fset.tlt[i] == 0xAA00) fTRIGTYPE[i] -> Select(14);
	    if (fset.tlt[i] == 0xD0D0) fTRIGTYPE[i] -> Select(15);
	    if (fset.tlt[i] == 0xDD00) fTRIGTYPE[i] -> Select(16);
	    if (fset.tlt[i] == 0xF000) fTRIGTYPE[i] -> Select(17);
	    if (fset.tlt[i] == 0xF888) fTRIGTYPE[i] -> Select(18);
	    if (fset.tlt[i] == 0xEAAA) fTRIGTYPE[i] -> Select(19);
	    if (fset.tlt[i] == 0x8000) fTRIGTYPE[i] -> Select(20);


		for (int j = 0; j < 4; j++)
		{
			fCOINWIDTH[i][j] -> SetText(Form("%lu", fset.cw[i][j]), kFALSE);
			fADCTHR[i][j] -> SetText(Form("%lu", fset.thr[i][j]), kFALSE);
			fTDCTHR[i][j] -> SetText(Form("%lu", fset.tdc_thr[i][j]), kFALSE);
			fPCT[i][j] -> SetText(Form("%lu", fset.pct[i][j]), kFALSE);
			fPCI[i][j] -> SetText(Form("%lu", fset.pci[i][j]), kFALSE);
			fPWT[i][j] -> SetText(Form("%lu", fset.pwt[i][j]), kFALSE);
			fTRIGDEAD[i][j] -> SetText(Form("%lu", fset.dt[i][j]), kFALSE);
			fOFFSET[i][j] -> SetText(Form("%lu", fset.offset[i][j]), kFALSE);
			fADELAY[i][j] -> SetText(Form("%lu", fset.dly[i][j]), kFALSE);
			fPSUMWIDTH[i][j] -> SetText(Form("%lu", fset.psw[i][j]), kFALSE);

			if (fset.zerosup[i][j] == 1) fZEROSUP[i][j] -> Select(0);
			if (fset.zerosup[i][j] == 0) fZEROSUP[i][j] -> Select(1);

			if (fset.pol[i][j] == 1) fPOL[i][j] -> Select(1);
			if (fset.pol[i][j] == 0) fPOL[i][j] -> Select(0);

			if (fset.amode[i][j] == 1) fADCMODE[i][j] -> Select(1);
			if (fset.amode[i][j] == 0) fADCMODE[i][j] -> Select(0);

		}
	}
}

void FADC500gui::HandleMenu(Int_t menu_id)
{
	// Handle menu events.
	TRootHelpDialog *hd;
	switch (menu_id) {
		case M_FILE_EXIT:
			// close the window and quit application
			gApplication->Terminate(0);
			break;
		case M_FILE_SAVE_DATA:
			Savefile();
			break;
		case M_FILE_SAVE_SETTING:
			SaveSetting();
			break;
		case M_FILE_OPEN_SETTING:
			OpenSetting();
			break;
		case M_HELP_ABOUT:
			hd = new TRootHelpDialog(0, "About NKFADC500", 750, 250);
			hd->SetText(gAboutNKFADC500);
			hd->Popup();
			break;
		case M_HELP_MANUAL:
			hd = new TRootHelpDialog(0, "NKFADC500 Manual", 1000, 500);
			hd->SetText(gMANUAL);
			hd->Popup();
			break;
		case M_HELP_CONTACT:
			hd = new TRootHelpDialog(0, "NKFADC500 Contact Information", 750, 250);
			hd->SetText(gCONTACT);
			hd->Popup();
			break;
	}
}

void FADC500gui::TerminatePro()
{
	gApplication->Terminate(0);
}

void FADC500gui::SetNModule(char* value)
{
	fset.module_count = atoi(value)-1;
	nModule = atoi(value);
	cout << "***** Number of Modules : " << nModule << " *****" << endl;
}

void FADC500gui::SetPTrigger(char* value)
{
	fset.ptrig_interval = atoi(value);
	cout << "***** Pedestal Trigger interval : " << fset.ptrig_interval << " ms *****" << endl;
}

void FADC500gui::SetDataRange(int value)
{
	TGComboBox *object = (TGComboBox *) gTQSender;
  	Int_t module = object -> WidgetId();
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	if (value == 0)
	{
		fset.rl[module] = 1;
		cout << "***** Data Range : " << "128 ns" << " *****" << endl;
	}
	if (value == 1)
	{
		fset.rl[module] = 2;
		cout << "***** Data Range : " << "256 ns" << " *****" << endl;
	}
	if (value == 2)
	{
		fset.rl[module] = 4;
		cout << "***** Data Range : " << "512 ns" << " *****" << endl;
	}
	if (value == 3)
	{
		fset.rl[module] = 8;
		cout << "***** Data Range : " << "1 us" << " *****" << endl;
	}
	if (value == 4)
	{
		fset.rl[module] = 16;
		cout << "***** Data Range : " << "2 us" << " *****" << endl;
	}
	if (value == 5)
	{
		fset.rl[module] = 32;
		cout << "***** Data Range : " << "4 us" << " *****" << endl;
	}
	if (value == 6)
	{
		fset.rl[module] = 64;
		cout << "***** Data Range : " << "8 us" << " *****" << endl;
	}
	if (value == 7)
	{
		fset.rl[module] = 128;
		cout << "***** Data Range : " << "16 us" << " *****" << endl;
	}
	if (value == 8)
	{
		fset.rl[module] = 256;
		cout << "***** Data Range : " << "32 us" << " *****" << endl;
	}

}

void FADC500gui::SetNEvent(char* value)
{
	nEvent  = atoi(value);
	cout << "***** Total Event Number : " << nEvent << " *****" << endl;
}

void FADC500gui::SetTrigType(int value)
{
	TGComboBox *object = (TGComboBox *) gTQSender;
  	Int_t module = object -> WidgetId();
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	if (value == 0)
	{
		fset.tlt[module] = 0x0000;
		cout << "***** Trigger Type : Master = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 1)
	{
		fset.tlt[module] = 0xFFFE;
		cout << "***** Trigger Type : 1 | 2 | 3 | 4 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 2)
	{
		fset.tlt[module] = 0xAAAA;
		cout << "***** Trigger Type : Only 1 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 3)
	{
		fset.tlt[module] = 0xDDDD;
		cout << "***** Trigger Type : Only 2 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 4)
	{
		fset.tlt[module] = 0xF0F0;
		cout << "***** Trigger Type : Only 3 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 5)
	{
		fset.tlt[module] = 0xFF00;
		cout << "***** Trigger Type : Only 4 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 6)
	{
		fset.tlt[module] = 0xEEEE;
		cout << "***** Trigger Type : 1 | 2 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 7)
	{
		fset.tlt[module] = 0xF2F2;
		cout << "***** Trigger Type : 1 | 3 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 8)
	{
		fset.tlt[module] = 0xFFA2;
		cout << "***** Trigger Type : 1 | 4 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 9)
	{
		fset.tlt[module] = 0xFCFC;
		cout << "***** Trigger Type : 2 | 3 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 10)
	{
		fset.tlt[module] = 0xFFCC;
		cout << "***** Trigger Type : 2 | 4 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 11)
	{
		fset.tlt[module] = 0xFFF0;
		cout << "***** Trigger Type : 3 | 4 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 12)
	{
		fset.tlt[module] = 0x8888;
		cout << "***** Trigger Type : 1 & 2 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 13)
	{
		fset.tlt[module] = 0xA0A0;
		cout << "***** Trigger Type : 1 & 3 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 14)
	{
		fset.tlt[module] = 0xAA00;
		cout << "***** Trigger Type : 1 & 4 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 15)
	{
		fset.tlt[module] = 0xD0D0;
		cout << "***** Trigger Type : 2 & 3 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 16)
	{
		fset.tlt[module] = 0xDD00;
		cout << "***** Trigger Type : 2 & 4 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 17)
	{
		fset.tlt[module] = 0xF000;
		cout << "***** Trigger Type : 3 & 4 = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 18)
	{
		fset.tlt[module] = 0xF888;
		cout << "***** Trigger Type : (1 & 2) | (3 & 4) = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 19)
	{
		fset.tlt[module] = 0xEAAA;
		cout << "***** Trigger Type : 1 | (2 & 3 & 4) = " << fset.tlt[module] << " *****" << endl;
	}
	if (value == 20)
	{
		fset.tlt[module] = 0x8000;
		cout << "***** Trigger Type : 1 & 2 & 3 & 4 = " << fset.tlt[module] << " *****" << endl;
	}


}

void FADC500gui::SetTrigDelay(char* value)
{
	fset.trigdly = atoi(value);
	cout << "***** Trigger Delay : " << fset.trigdly << " ns *****" << endl;
}

void FADC500gui::SetTrigCoinWidth(char* value)
{
	fset.cw_tcb = atoi(value);
	cout << "***** Trigger Coincidence Width : " << fset.cw_tcb << " ns *****" << endl;
}


void FADC500gui::SetCoinWidth(char* value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	fset.cw[module][channel] = atoi(value);
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;
	cout << "***** Coincidence Width : " << fset.cw[module][channel] << " ns *****" << endl;
}

void FADC500gui::SetADCThr(char* value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	fset.thr[module][channel] = atoi(value);
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;
	cout << "***** ADC Threshold : " << fset.thr[module][channel]*0.5 << " mV *****" << endl;
}

void FADC500gui::SetTDCThr(char* value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	fset.tdc_thr[module][channel] = atoi(value);
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;
	cout << "***** Pedestal Trigger interval : " << fset.tdc_thr[module][channel]*0.5 << " mV *****" << endl;
}

void FADC500gui::SetPCT(char* value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	fset.pct[module][channel] = atoi(value);
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;
	cout << "***** Pulse Count Threshold : " << fset.pct[module][channel] << " *****" << endl;
}

void FADC500gui::SetPCI(char* value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	fset.pci[module][channel] = atoi(value);
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;
	cout << "***** Pulse Count Interval : " << fset.pci[module][channel] << " ns *****" << endl;
}

void FADC500gui::SetPWT(char* value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	fset.pwt[module][channel] = atoi(value);
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;
	cout << "***** Pulse Width Threshold : " << fset.pwt[module][channel] << " ns *****" << endl;
}

void FADC500gui::SetTrigDead(char* value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	fset.dt[module][channel] = atoi(value);
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;
	cout << "***** Trigger Deadtime : " << fset.dt[module][channel] << " ns *****" << endl;
}

void FADC500gui::SetZeroSup(int value)
{
	TGComboBox *object = (TGComboBox *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;

	if (value == 0)
	{
		fset.zerosup[module][channel] = 1;
		cout << "***** Zero Suppression : " << "Able" << " *****" << endl;
	}
	if (value == 1)
	{
		fset.zerosup[module][channel] = 0;	
		cout << "***** Zero Suppression : " << "Disable" << " *****" << endl;
	}
}

void FADC500gui::SetTEN(int value)
{
	if (value == 0)
	{
		fset.ten = 1;
		cout << "***** Pulse Count Trigger : " << "Able" << " *****" << endl;
	}
	if (value == 1)
	{
		fset.ten = 0;	
		cout << "***** Pulse Count Trigger : " << "Disable" << " *****" << endl;
	}
}

void FADC500gui::SetTEW(int value)
{
	if (value == 0)
	{
		fset.tew = 1;
		cout << "***** Pulse Width Trigger : " << "Able" << " *****" << endl;
	}
	if (value == 1)
	{
		fset.tew = 0;	
		cout << "***** Pulse Width Trigger : " << "Disable" << " *****" << endl;
	}
}

void FADC500gui::SetTEP(int value)
{
	if (value == 0)
	{
		fset.tep = 1;
		cout << "***** Peak Sum Trigger : " << "Able" << " *****" << endl;
	}
	if (value == 1)
	{
		fset.tep = 0;	
		cout << "***** Peak Sum Trigger : " << "Disable" << " *****" << endl;
	}
}

void FADC500gui::SetTEPO(int value)
{
	if (value == 0)
	{
		fset.tep2 = 1;
		cout << "***** Peak Sum OR Trigger : " << "Able" << " *****" << endl;
	}
	if (value == 1)
	{
		fset.tep2 = 0;	
		cout << "***** Peak Sum OR Trigger : " << "Disable" << " *****" << endl;
	}
}

void FADC500gui::SetPol(int value)
{
	TGComboBox *object = (TGComboBox *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;


	if (value == 0)
	{
		fset.pol[module][channel] = 0;
		cout << "***** Pulse Polarity : " << "Negative" << " *****" << endl;
	}
	if (value == 1)
	{
		fset.pol[module][channel] = 1;	
		cout << "***** Pulse Polarity : " << "Positive" << " *****" << endl;
	}
}

void FADC500gui::SetOffset(char* value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;


	fset.offset[module][channel] = atoi(value);
	cout << "***** ADC Offset : " << fset.offset[module][channel]*0.5 << " mV *****" << endl;
}

void FADC500gui::SetADCDelay(char* value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;


	fset.dly[module][channel] = atoi(value);
	cout << "***** ADC Delay Time : " << fset.dly[module][channel] << " ns *****" << endl;
}

void FADC500gui::SetPSumWidth(char* value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;


	fset.psw[module][channel] = atoi(value);
	cout << "***** Peak Sum Width : " << fset.psw[module][channel] << " ns *****" << endl;
}

void FADC500gui::SetADCMode(int value)
{
	TGComboBox *object = (TGComboBox *) gTQSender;
  	Int_t widgetID = object -> WidgetId();
	Int_t module = widgetID/100;
	Int_t channel = (widgetID%100)/10;
	cout << "***** Module ID : " << module+1 << " *****" << endl;
	cout << "***** Channel ID : " << channel+1 << " *****" << endl;


	if (value == 0)
	{
		fset.amode[module][channel] = 0;
		cout << "***** ADC Mode : " << "Raw" << " *****" << endl;
	}
	if (value == 1)
	{
		fset.amode[module][channel] = 1;	
		cout << "***** ADC Mode : " << "Filtered" << " *****" << endl;
	}
}

void FADC500gui::SetSame()
{
	for (int i = 1; i < 6; i++)
	{
		fset.rl[i] = fset.rl[0];
		fset.tlt[i] = fset.tlt[0];
		if (fset.rl[i] == 1)   fDATARANGE[i] -> Select(0);
	    if (fset.rl[i] == 2)   fDATARANGE[i] -> Select(1);
	    if (fset.rl[i] == 4)   fDATARANGE[i] -> Select(2);
	    if (fset.rl[i] == 8)   fDATARANGE[i] -> Select(3);
	    if (fset.rl[i] == 16)  fDATARANGE[i] -> Select(4);
	    if (fset.rl[i] == 32)  fDATARANGE[i] -> Select(5);
	    if (fset.rl[i] == 64)  fDATARANGE[i] -> Select(6);
	    if (fset.rl[i] == 128) fDATARANGE[i] -> Select(7);
	    if (fset.rl[i] == 256) fDATARANGE[i] -> Select(8);

	    if (fset.tlt[i] == 0x0000) fTRIGTYPE[i] -> Select(0);
	    if (fset.tlt[i] == 0xFFFE) fTRIGTYPE[i] -> Select(1);
	    if (fset.tlt[i] == 0xAAAA) fTRIGTYPE[i] -> Select(2);
	    if (fset.tlt[i] == 0xDDDD) fTRIGTYPE[i] -> Select(3);
	    if (fset.tlt[i] == 0xF0F0) fTRIGTYPE[i] -> Select(4);
	    if (fset.tlt[i] == 0xFF00) fTRIGTYPE[i] -> Select(5);
	    if (fset.tlt[i] == 0xEEEE) fTRIGTYPE[i] -> Select(6);
	    if (fset.tlt[i] == 0xF2F2) fTRIGTYPE[i] -> Select(7);
	    if (fset.tlt[i] == 0xFFA2) fTRIGTYPE[i] -> Select(8);
	    if (fset.tlt[i] == 0xFCFC) fTRIGTYPE[i] -> Select(9);
	    if (fset.tlt[i] == 0xFFCC) fTRIGTYPE[i] -> Select(10);
	    if (fset.tlt[i] == 0xFFF0) fTRIGTYPE[i] -> Select(11);
	    if (fset.tlt[i] == 0x8888) fTRIGTYPE[i] -> Select(12);
	    if (fset.tlt[i] == 0xA0A0) fTRIGTYPE[i] -> Select(13);
	    if (fset.tlt[i] == 0xAA00) fTRIGTYPE[i] -> Select(14);
	    if (fset.tlt[i] == 0xD0D0) fTRIGTYPE[i] -> Select(15);
	    if (fset.tlt[i] == 0xDD00) fTRIGTYPE[i] -> Select(16);
	    if (fset.tlt[i] == 0xF000) fTRIGTYPE[i] -> Select(17);
	    if (fset.tlt[i] == 0xF888) fTRIGTYPE[i] -> Select(18);
	    if (fset.tlt[i] == 0xEAAA) fTRIGTYPE[i] -> Select(19);
	    if (fset.tlt[i] == 0x8000) fTRIGTYPE[i] -> Select(20);
	}

	for (int i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			for (int j = 1; j < 4; j++)
			{
				fset.cw[i][j] = fset.cw[0][0];
				fset.thr[i][j] = fset.thr[0][0];
				fset.tdc_thr[i][j] = fset.tdc_thr[0][0];
				fset.pct[i][j] = fset.pct[0][0];
				fset.pci[i][j] = fset.pci[0][0];
				fset.pwt[i][j] = fset.pwt[0][0];
				fset.dt[i][j] = fset.dt[0][0];
				fset.offset[i][j] = fset.offset[0][0];
				fset.dly[i][j] = fset.dly[0][0];
				fset.psw[i][j] = fset.psw[0][0];
				fset.zerosup[i][j] = fset.zerosup[0][0];
				fset.pol[i][j] = fset.pol[0][0];
				fset.amode[i][j] = fset.amode[0][0];

				fCOINWIDTH[i][j] -> SetText(Form("%lu", fset.cw[i][j]), kFALSE);
    	        fADCTHR[i][j] -> SetText(Form("%lu", fset.thr[i][j]), kFALSE);
	            fTDCTHR[i][j] -> SetText(Form("%lu", fset.tdc_thr[i][j]), kFALSE);
	            fPCT[i][j] -> SetText(Form("%lu", fset.pct[i][j]), kFALSE);
	            fPCI[i][j] -> SetText(Form("%lu", fset.pci[i][j]), kFALSE);
	            fPWT[i][j] -> SetText(Form("%lu", fset.pwt[i][j]), kFALSE);
	            fTRIGDEAD[i][j] -> SetText(Form("%lu", fset.dt[i][j]), kFALSE);
	            fOFFSET[i][j] -> SetText(Form("%lu", fset.offset[i][j]), kFALSE);
	            fADELAY[i][j] -> SetText(Form("%lu", fset.dly[i][j]), kFALSE);
	            fPSUMWIDTH[i][j] -> SetText(Form("%lu", fset.psw[i][j]), kFALSE);
    
	            if (fset.zerosup[i][j] == 1) fZEROSUP[i][j] -> Select(0);
	            if (fset.zerosup[i][j] == 0) fZEROSUP[i][j] -> Select(1);

				if (fset.pol[i][j] == 1) fPOL[i][j] -> Select(1);
	            if (fset.pol[i][j] == 0) fPOL[i][j] -> Select(0);

				if (fset.amode[i][j] == 1) fADCMODE[i][j] -> Select(1);
	            if (fset.amode[i][j] == 0) fADCMODE[i][j] -> Select(0);	
			}
		}
		else
		{
			for (int j = 0; j < 4; j++)
			{
				fset.cw[i][j] = fset.cw[0][0];
				fset.thr[i][j] = fset.thr[0][0];
				fset.tdc_thr[i][j] = fset.tdc_thr[0][0];
				fset.pct[i][j] = fset.pct[0][0];
				fset.pci[i][j] = fset.pci[0][0];
				fset.pwt[i][j] = fset.pwt[0][0];
				fset.dt[i][j] = fset.dt[0][0];
				fset.offset[i][j] = fset.offset[0][0];
				fset.dly[i][j] = fset.dly[0][0];
				fset.psw[i][j] = fset.psw[0][0];
				fset.zerosup[i][j] = fset.zerosup[0][0];
				fset.pol[i][j] = fset.pol[0][0];
				fset.amode[i][j] = fset.amode[0][0];

				fCOINWIDTH[i][j] -> SetText(Form("%lu", fset.cw[i][j]), kFALSE);
    	        fADCTHR[i][j] -> SetText(Form("%lu", fset.thr[i][j]), kFALSE);
	            fTDCTHR[i][j] -> SetText(Form("%lu", fset.tdc_thr[i][j]), kFALSE);
	            fPCT[i][j] -> SetText(Form("%lu", fset.pct[i][j]), kFALSE);
	            fPCI[i][j] -> SetText(Form("%lu", fset.pci[i][j]), kFALSE);
	            fPWT[i][j] -> SetText(Form("%lu", fset.pwt[i][j]), kFALSE);
	            fTRIGDEAD[i][j] -> SetText(Form("%lu", fset.dt[i][j]), kFALSE);
	            fOFFSET[i][j] -> SetText(Form("%lu", fset.offset[i][j]), kFALSE);
	            fADELAY[i][j] -> SetText(Form("%lu", fset.dly[i][j]), kFALSE);
	            fPSUMWIDTH[i][j] -> SetText(Form("%lu", fset.psw[i][j]), kFALSE);
    
	            if (fset.zerosup[i][j] == 1) fZEROSUP[i][j] -> Select(0);
	            if (fset.zerosup[i][j] == 0) fZEROSUP[i][j] -> Select(1);

				if (fset.pol[i][j] == 1) fPOL[i][j] -> Select(1);
	            if (fset.pol[i][j] == 0) fPOL[i][j] -> Select(0);

				if (fset.amode[i][j] == 1) fADCMODE[i][j] -> Select(1);
	            if (fset.amode[i][j] == 0) fADCMODE[i][j] -> Select(0);	
			}
		}
	}
}				

void FADC500gui::SetTCB()
{
	fset.FADC500ParSetting();
	for (int i = 0; i < 6; i++)
	{
		frun.datasize[i] = int(fset.rl[i]*128);
	}
	tcbflag = 1;
}

void FADC500gui::RunDAQ()
{
	TString datafile = directory + saveFile;

	if (datafile.Length() >= 1 && tcbflag == 1)
	{
		frun.FADC500DAQRun(datafile, nEvent, nModule);
		tcbflag = 0;
	}	
	if (datafile.Length() == 0)
	{
		cout << "Please save your directory and filename for data." << endl;
	}
	if (tcbflag == 0)
	{
		cout << "Please activate TCB first." << endl;
	}

}

void FADC500gui::StopDAQ()
{
	frun.flag = 0;
	gSystem -> ProcessEvents();
}

void FADC500gui::ADCOn()
{
	frun.adcflag = 1;
	gSystem -> ProcessEvents();
}

void FADC500gui::ADCOff()
{
	frun.adcflag = 0;
	gSystem -> ProcessEvents();
}

void FADC500gui::TDCOn()
{
	frun.tdcflag = 1;
	gSystem -> ProcessEvents();
}

void FADC500gui::TDCOff()
{
	frun.tdcflag = 0;
	gSystem -> ProcessEvents();
}
