// -*- C++ -*-
//
// generated by wxGlade 0.7.2 on Thu Oct 20 13:35:21 2016
//
// Example for compiling a single file project under Linux using g++:
//  g++ MyApp.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp
//
// Example for compiling a multi file project under Linux using g++:
//  g++ main.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp Dialog1.cpp Frame1.cpp
//

#include "LabView.h"
#include "MotorController.h"
#include "VoltageControl.h"
#include "VoltageControlNI.h"
#include "Panel.h"
#include "messages.h"
#include "LabUtilities.h"

// begin wxGlade: ::extracode
// end wxGlade


//const float STEPPERMM = STEPPERTURN/25.4; //TODO change this to be se from within the header dialog



MotorController* mot;
//VoltageNI* volt;
VoltageControl* volt;
Panel* panelConfig;
HeaderEdit* HeaderWindow;
Messages* message;
WeinerCounter* nim;
HeaderInfoGen globalHeader;
HeaderInfoGen* pglobalheader;



BigFrame::BigFrame(wxWindow* parent) : MainFrame(parent)
{
	//mot = new MotorController(3, 9600);
	//volt = new VoltageNI();
	//volt = new VoltageControl(5);
	message = new Messages();
	pglobalheader = &globalHeader;
}

void BigFrame::onQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}
//
void BigFrame::yUpButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	try
	{
		mot->stepMotor(2, distanceToMove);
	}
	catch (...)
	{ }

}

void BigFrame::yDownButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->stepMotor(2, -distanceToMove);

}

void BigFrame::xLeftButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->stepMotor(1, distanceToMove);

}

void BigFrame::xRightButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->stepMotor(1, -distanceToMove);

}

void BigFrame::homeButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->setZeroX();
	mot->setZeroY();
}

void BigFrame::goToHomeButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->goZero();
}

void BigFrame::distanceBoxClicked(wxCommandEvent & event)
{
	distanceToMove = convertDistance(distanceBox->GetSelection());
}
//
int BigFrame::convertDistance(int radioButton)
{
	int ret;
	switch (radioButton)
	{
	case 0:
		ret = (int) (0.01 / MMPERSTEP);
		break;
	case 1:
		ret = (int)(0.1 / MMPERSTEP);
		break;
	case 2:
		ret = (int)(1.0 / MMPERSTEP);
		break;
	case 3:
		ret = (int)(5.0 / MMPERSTEP);
		break;
	case 4:
		ret = (int)(10.0 / MMPERSTEP);
		break;
	default:
		ret = 0;
		break;
	}

	return ret;
}

void BigFrame::scanTypeSelected(wxCommandEvent & event)
{
	static int scanChosen = m_choice1->GetSelection();
	switch (scanChosen)
	{
	case 0:
		scanType = "Free";
		break;
	case 1:
		scanType = "PixelScan";
		break;
	case 2:
		scanType = "PixelMap";
		break;
	case 3:
		scanType = "LineScan";
		break;
	default:
		scanType = "None";
		break;
	}
}

//wxStaticBoxSizer* test;

void BigFrame::toggleHV(wxCommandEvent& event)
{
	int voltageStatus = m_radioBox3->GetSelection();
	if (voltageStatus == 0)
	{
		string voltage = m_textCtrl22->GetLineText(0);

			volt->setVoltage(stoi(voltage));
			volt->turnOn();

	}
	if (voltageStatus == 1)
		volt->turnOff();
}

void BigFrame::setStartVoltage(wxCommandEvent& event)
{
	//string voltage = m_textCtrl22->GetLineText(0);
	
}

void BigFrame::motorControllerConnectClicked(wxCommandEvent & event)
{
	static bool connected = false;

	if (!connected)
	{
		mot = new MotorController(3, 9600);
		connected = true;
	}
}

void BigFrame::motorControllerDisconnectClicked(wxCommandEvent & event)
{
	//mot->portClose();
}

void BigFrame::HVConnectClicked(wxCommandEvent & event)
{
	volt = new VoltageControl(5);
	//volt = new VoltageNI();

	volt->turnOff();
}

void BigFrame::openPanelFrame(wxCommandEvent& event) 
{ 
	panelConfig = new Panel(this);
	panelConfig->Show(true);
}

void BigFrame::setEndVoltage(wxCommandEvent & event)
{
	//m_textCtrl23->SelectAll();
	//if (wxAtoi(m_textCtrl22->GetLineText(0)) >= wxAtoi(m_textCtrl23->GetLineText(0)))
	//{
	//	m_textCtrl23->WriteText(m_textCtrl22->GetLineText(0));
	//}
}

void BigFrame::updateButtonClicked(wxCommandEvent& event)
{
	int startvoltage, endvoltage, xoffset, yoffset, xstepsize, ystepsize, voltagestepsize, dwelltime;
	int numsteps, frequency;
	double totaltime;
	//string filename;

	startvoltage = wxAtoi(m_textCtrl22->GetLineText(0));
	endvoltage = wxAtoi(m_textCtrl23->GetLineText(0));
	voltagestepsize = wxAtoi(m_textCtrl40->GetLineText(0));
	numsteps = (endvoltage - startvoltage) / voltagestepsize;
	
	m_textCtrl45->SelectAll();
	m_textCtrl45->WriteText(wxString::Format(wxT("%i"), numsteps));

	xoffset = wxAtoi(m_textCtrl18->GetLineText(0));
	yoffset = wxAtoi(m_textCtrl19->GetLineText(0));
	xstepsize = wxAtoi(m_textCtrl20->GetLineText(0));
	ystepsize = wxAtoi(m_textCtrl21->GetLineText(0));

	dwelltime = wxAtoi(m_textCtrl42->GetLineText(0));
	totaltime = xoffset / xstepsize * yoffset / ystepsize * (endvoltage - startvoltage) / voltagestepsize*dwelltime;

	frequency = wxAtoi(m_textCtrl43->GetLineText(0));

	m_textCtrl46->SelectAll();
	m_textCtrl46->WriteText(wxString::Format(wxT("%f"), totaltime / 3600));

	message->frequency = frequency;
	message->maxOffsetX = xoffset;
	message->maxStepX = xstepsize;
	message->maxStepY = ystepsize;
	message->numPix = 1;
	message->time = dwelltime;
	message->voltageStart = startvoltage;
	message->voltageEnd = endvoltage;
	message->voltageStep = voltagestepsize;
}

void markButtonClicked(wxCommandEvent& event)
{

}

void BigFrame::setHome(wxCommandEvent& event)
{
	mot->setZero();
}

void BigFrame::goToHome(wxCommandEvent& event)
{
	mot->goZero();
}

HeaderEdit::HeaderEdit(wxWindow* parent) : header(parent)
{

}

void BigFrame::openHeaderFrame(wxCommandEvent& event)
{
	if (!HeaderWindow)
		HeaderWindow = new HeaderEdit(this);
	HeaderWindow->Show(true);
}

string HeaderEdit::getSourceConfig()
{
	switch (m_radioBox1->GetSelection())
	{
	case 0:
		return string("Dynamic");
		break;
	case 1:
		return string("Static");
		break;
	case 2:
		return string("User");
		break;
	default:
		return string("Not Selected");
		break;
	}
}

void HeaderEdit::setSourceConfig(string type)
{
	if (type.compare("Dynamic"))
	{
		m_radioBox1->SetSelection(0);
	}

	else if (type.compare("Static"))
	{
		m_radioBox1->SetSelection(1);
	}
	else if (type.compare("User"))
	{
		m_radioBox1->SetSelection(2);
	}
	else
		wxMessageBox(wxT("No Source Type Found!"));
}

void HeaderEdit::headerOkClicked(wxCommandEvent& event)
{
	copyData(globalHeader);
	Show(false);
}
void HeaderEdit::headerCancelClicked(wxCommandEvent& event)
{
	Show(false);
}

void HeaderEdit::saveHeader(wxCommandEvent& event)
{
	copyData(globalHeader);
	string fullpath;
	wxFileDialog* SaveDialog = new wxFileDialog(
		this, _("Choose a location to save to"), wxEmptyString, wxString(pglobalheader->panelName), wxT("Text File (*.txt) | *.txt"),
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	//if (SaveDialog->ShowModal() == wxID_CANCEL)
	//	SaveDialog->Destroy();     // the user changed idea...


	if (SaveDialog->ShowModal() == wxID_OK) // if the user click "Save" instead of "Cancel"
	{

		fullpath = SaveDialog->GetFilename();
		//wxMessageBox(fullpath);

		ofstream file;
		file.open(fullpath);

		file << globalHeader;
		file.close();
		//makeGenHeadFile(headerInfo, fullpath);
	}
	else
		SaveDialog->Destroy();
}

void HeaderEdit::openHeader(wxCommandEvent& event)
{
	string fullpath;
	wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Choose header file to open"), wxT("Text File (*.txt) | *.txt"));

	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Save" instead of "Cancel"
	{

		fullpath = OpenDialog->GetFilename();
		//wxMessageBox(fullpath);

		makeGenHeadFile(globalHeader, fullpath);
		putData(globalHeader);
	}
	else
		OpenDialog->Destroy();
}

void HeaderEdit::updateGas(wxCommandEvent& event)
{
	wxString gasMix;
	int gasTotal = 0;

	vector<wxString> gasTypes;
	vector<wxString> gasPercent;

	gasTypes.push_back(m_comboBox3->GetStringSelection());
	gasTypes.push_back(m_comboBox2->GetStringSelection());
	gasTypes.push_back(m_comboBox1->GetStringSelection());

	gasPercent.push_back(m_textCtrl51->GetLineText(0));
	gasPercent.push_back(m_textCtrl50->GetLineText(0));
	gasPercent.push_back(m_textCtrl49->GetLineText(0));

	while (!gasTypes.empty())
	{
		gasMix += gasPercent.back() + "% ";
		gasTotal += wxAtoi(gasPercent.back());
		gasMix += gasTypes.back() + " ";
		gasPercent.pop_back();
		gasTypes.pop_back();
	}

	m_textCtrl13->SelectAll();
	m_textCtrl13->WriteText(gasMix);

	m_textCtrl52->SelectAll();
	m_textCtrl52->WriteText(wxString::Format(wxT("%i",gasTotal)));
}

void HeaderEdit::copyData(HeaderInfoGen &headerInfo)
{
	headerInfo.panelName = m_textCtrl1->GetLineText(0);
	headerInfo.sourceName = m_textCtrl11->GetLineText(0);
	headerInfo.sourceConfig = getSourceConfig();
	headerInfo.triggerSetup = m_textCtrl1322->GetLineText(0);
	headerInfo.gas = m_textCtrl13->GetLineText(0);
	headerInfo.pressure = wxAtof(m_textCtrl131->GetLineText(0));
	headerInfo.discThresh = wxAtof(m_textCtrl48->GetLineText(0));
	headerInfo.quench = wxAtof(m_textCtrl132->GetLineText(0));
	headerInfo.numRO = wxAtoi(m_textCtrl47->GetLineText(0));
	headerInfo.roLines = m_textCtrl1321->GetLineText(0);
	headerInfo.triggerRO = m_textCtrl12->GetLineText(0);
	headerInfo.attenRO = wxAtof(m_textCtrl24->GetLineText(0));
	headerInfo.numHV = wxAtoi(m_textCtrl1324->GetLineText(0));
	headerInfo.linesHV = m_textCtrl1325->GetLineText(0);
	headerInfo.triggerHV = m_textCtrl1323->GetLineText(0);
	headerInfo.attenHV = wxAtof(m_textCtrl1326->GetLineText(0));
}

void HeaderEdit::putData(HeaderInfoGen &headerInfo)
{
	m_textCtrl1->WriteText(headerInfo.panelName);
	m_textCtrl11->WriteText(headerInfo.sourceName);
	m_textCtrl1322->WriteText(headerInfo.triggerSetup);
	m_textCtrl13->WriteText(headerInfo.gas);
	m_textCtrl131->WriteText(wxString::Format(wxT("%f"), headerInfo.pressure));
	m_textCtrl48->WriteText(wxString::Format(wxT("%f"), headerInfo.discThresh));
	m_textCtrl132->WriteText(wxString::Format(wxT("%f"), headerInfo.quench));
	m_textCtrl47->WriteText(wxString::Format(wxT("%i"), headerInfo.numRO));
	m_textCtrl1321->WriteText(headerInfo.roLines);
	m_textCtrl12->WriteText(headerInfo.triggerRO);
	m_textCtrl24->WriteText(wxString::Format(wxT("%f"), headerInfo.attenRO));
	m_textCtrl1324->WriteText(wxString::Format(wxT("%i"), headerInfo.numHV));
	m_textCtrl1325->WriteText(headerInfo.linesHV);
	m_textCtrl1323->WriteText(headerInfo.triggerHV);
	m_textCtrl1326->WriteText(wxString::Format(wxT("%f"), headerInfo.attenHV));
	setSourceConfig(headerInfo.sourceConfig);
}

void BigFrame::connectNIMClicked(wxCommandEvent& event)
{
	nim = new WeinerCounter(0);
}

void BigFrame::startSelected(wxCommandEvent& event)
{
	if (scanType.compare("LineScan"))
	{
		doLineScan(mot, nim, volt, message, pglobalheader);
	}
}