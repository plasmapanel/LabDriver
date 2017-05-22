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

std::atomic<bool> control = true;

// begin wxGlade: ::extracode
// end wxGlade


//const float STEPPERMM = STEPPERTURN/25.4; //TODO change this to be se from within the header dialog



MotorController* mot;
//VoltageNI* voltNI;
//VoltageControl* volt;
Voltage* volt;
Panel* panelConfig;
HeaderEdit* HeaderWindow;
Messages* message;
WeinerCounter* nim;
HeaderInfoGen globalHeader;
HeaderInfoGen* pglobalheader;
VoltageFactory* vf;
Readout* readout;
readoutedit* readoutframe;
Histogram* Image;

static bool connected = false;
Offset offsets[4];

BigFrame::BigFrame(wxWindow* parent) : MainFrame(parent)
{
	//mot = new MotorController(3, 9600);
	//volt = new VoltageNI();
	//volt = new VoltageControl(5);
	message = new Messages();
	pglobalheader = &globalHeader;
	vf = new VoltageFactory();
	readout = new Readout();

}

void BigFrame::onQuit(wxCommandEvent& WXUNUSED(event))
{
	if (volt)
	{
		volt->turnOff();
		volt->end();
	}
	delete volt;
	delete nim;
	delete mot;
	delete vf;
	delete message;
	delete readout;
	Close(true);

}

//
void BigFrame::yUpButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	try
	{
		mot->stepMotor(2, distanceToMoveY);
	}
	catch (...)
	{ }

}

void BigFrame::yDownButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->stepMotor(2, -distanceToMoveY);

}

void BigFrame::xLeftButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->stepMotor(1, distanceToMoveX);

}

void BigFrame::xRightButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->stepMotor(1, -distanceToMoveX);

}

void BigFrame::setHome(wxCommandEvent& event)
{
	mot->setZero();
}

void BigFrame::goToHome(wxCommandEvent& event)
{
	int selection = m_radioBox4->GetSelection();
	if (selection == 0)
		mot->goZero();
	else
	{
		mot->goZero();
		mot->goTo(offsets[selection].stepsX, offsets[selection].stepsY);
	}
}

void BigFrame::markButtonClicked(wxCommandEvent & event)
{
	int selection = m_radioBox4->GetSelection();

	if (selection != 0)
	{
		offsets[selection].stepsX = mot->getAbsolutePositionX();
		offsets[selection].stepsY = mot->getAbsolutePositionY();
	}
}

void BigFrame::distanceBoxClicked(wxCommandEvent & event)
{
	distanceToMoveX = convertDistance(distanceBox->GetSelection(), 1);
	distanceToMoveY = convertDistance(distanceBox->GetSelection(), 2);
}


//
int BigFrame::convertDistance(int radioButton, int motor)
{
	int ret;
	int stepsmm = 400;
	if (motor == 1)
		stepsmm = wxAtoi(m_textCtrl41->GetLineText(0));
	if (motor == 2)
		stepsmm = wxAtoi(m_textCtrl29->GetLineText(0));

	switch (radioButton)
	{
	case 0:
		ret = (int)(0.1 * stepsmm);
		break;
	case 1:
		ret = (int)(1.0 * stepsmm);
		break;
	case 2:
		ret = (int)(5.0 * stepsmm);
		break;
	case 3:
		ret = (int)(10.0 * stepsmm);
		break;
	case 4:
		ret = (int)(stepsmm * wxAtof(m_textCtrl28->GetLineText(0)));
		break;
	default:
		ret = 0;
		break;
	}

	return ret;
}

void BigFrame::scanTypeSelected(wxCommandEvent & event)
{
	int scanChosen = m_choice1->GetSelection();
	switch (scanChosen)
	{
	case 0:
		scanType = "Free";
		break;
	case 1:
		scanType = "FreeAP";
		break;
	case 2:
		scanType = "LineScan";
		break;
	case 3:
		scanType = "HexScanX";
		break;
	case 4:
		scanType = "HexScanY";
		break;
	case 5:
		scanType = "XYScan";
		break;
	default:
		scanType = "None";
		break;
	}
}

void BigFrame::setScanType()
{
	int scanChosen = m_choice1->GetSelection();
	switch (scanChosen)
	{
	case 0:
		scanType = "Free";
		break;
	case 1:
		scanType = "FreeAP";
		break;
	case 2:
		scanType = "LineScan";
		break;
	case 3:
		scanType = "HexScanX";
		break;
	case 4:
		scanType = "HexScanY";
		break;
	case 5:
		scanType = "XYScan";
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
	//static bool connected = false;
	static int portnum;

	if (!connected)
	{
		portnum = wxAtoi(m_choice2->GetStringSelection());
		mot = new MotorController(portnum, 9600);
		connected = true;
		m_button15->Disable();
		m_button16->Enable();
	}
}

void BigFrame::motorControllerDisconnectClicked(wxCommandEvent & event)
{
	mot->portClose();
	mot = nullptr;
	m_button15->Enable();
	m_button16->Disable();
	delete(mot);
	connected = false;
}

void BigFrame::HVConnectClicked(wxCommandEvent & event)
{
	string hv = hvChoice->GetStringSelection();

		volt = vf->newVolt(hv);
		volt->init(5);
		volt->turnOff();
		hvChoice->Disable();
		m_button17->Disable();
		m_button18->Enable();
}

void BigFrame::HVDisconnectClicked(wxCommandEvent& event)
{
	volt = nullptr;
	hvChoice->Enable();
	m_button17->Enable();
	m_button18->Enable();
}

void BigFrame::openPanelFrame(wxCommandEvent& event) 
{ 
	if (panelConfig == nullptr)
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
	int motorstepx, motorstepy;

	double xoffsetmm, yoffsetmm, xstepsizemm, ystepsizemm;
	double totaltime;
	//string filename;

	startvoltage = wxAtoi(m_textCtrl22->GetLineText(0));
	endvoltage = wxAtoi(m_textCtrl23->GetLineText(0));
	voltagestepsize = wxAtoi(m_textCtrl40->GetLineText(0));
	numsteps = (endvoltage - startvoltage) / voltagestepsize;
	
	m_textCtrl45->SelectAll();
	m_textCtrl45->WriteText(wxString::Format(wxT("%i"), numsteps));

	xoffsetmm = wxAtof(m_textCtrl18->GetLineText(0));
	yoffsetmm = wxAtof(m_textCtrl19->GetLineText(0));
	xstepsizemm = wxAtof(m_textCtrl20->GetLineText(0));
	ystepsizemm = wxAtof(m_textCtrl21->GetLineText(0));
	motorstepx = wxAtoi(m_textCtrl41->GetLineText(0));
	motorstepy = wxAtoi(m_textCtrl29->GetLineText(0));

	dwelltime = wxAtoi(m_textCtrl42->GetLineText(0));
	if (xstepsizemm && ystepsizemm != 0)
	{
		xoffset = motorstepx * xoffsetmm;
		xstepsize = motorstepx * xstepsizemm;

		yoffset = motorstepy * yoffsetmm;
		ystepsize = motorstepy * ystepsizemm;

		if (endvoltage != startvoltage)
			totaltime = xoffset / xstepsize * yoffset / ystepsize * (endvoltage - startvoltage) / voltagestepsize*dwelltime;
		else
			totaltime = xoffset / xstepsize * yoffset / ystepsize / dwelltime;
	}
	else
	{
		if (endvoltage != startvoltage)
			totaltime = (endvoltage - startvoltage) / voltagestepsize*dwelltime;
		else
		{
			totaltime = dwelltime;
		}

	}
	frequency = wxAtoi(m_textCtrl43->GetLineText(0));

	m_textCtrl46->SelectAll();
	m_textCtrl46->WriteText(wxString::Format(wxT("%f"), totaltime / 3600));

	setScanType();

	message->frequency = frequency;
	message->maxOffsetX = xoffset;
	message->maxStepX = xstepsize;
	message->maxStepY = ystepsize;
	message ->maxOffsetY = yoffset;
	message->numPix = 1;
	message->time = dwelltime;
	message->voltageStart = startvoltage;
	message->voltageEnd = endvoltage;
	message->voltageStep = voltagestepsize;
	//message->temp = m_textCtrl44->GetLineText(0);
	message->runtype = scanType;
	//message->motorstepx = motorstepx;
	//message->motorstepy = motorstepy;
	globalHeader.motorstepx = motorstepx;
	globalHeader.motorstepy = motorstepy;

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

		fullpath = OpenDialog->GetPath();
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
		gasMix += gasPercent.back() + "_";
		gasTotal += wxAtoi(gasPercent.back());
		gasMix += gasTypes.back() + "-";
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
	//headerInfo.triggerSetup = m_textCtrl1322->GetLineText(0);
	headerInfo.gas = m_textCtrl13->GetLineText(0);
	headerInfo.pressure = wxAtof(m_textCtrl131->GetLineText(0));
	headerInfo.discThresh = wxAtof(m_textCtrl48->GetLineText(0));
	headerInfo.quench = wxAtof(m_textCtrl132->GetLineText(0));
	//headerInfo.numRO = wxAtoi(m_textCtrl47->GetLineText(0));
	//headerInfo.roLines = m_textCtrl1321->GetLineText(0);
	//headerInfo.triggerRO = m_textCtrl12->GetLineText(0);
	headerInfo.attenRO = wxAtof(m_textCtrl24->GetLineText(0));
	headerInfo.numHV = wxAtoi(m_textCtrl1324->GetLineText(0));
	headerInfo.linesHV = m_textCtrl1325->GetLineText(0);
	//headerInfo.triggerHV = m_textCtrl1323->GetLineText(0);
	//headerInfo.attenHV = wxAtof(m_textCtrl1326->GetLineText(0));
}

void HeaderEdit::putData(HeaderInfoGen &headerInfo)
{
	m_textCtrl1->Clear();
	m_textCtrl1->WriteText(headerInfo.panelName);
	m_textCtrl11->Clear();
	m_textCtrl11->WriteText(headerInfo.sourceName);
	//m_textCtrl1322->WriteText(headerInfo.triggerSetup);
	m_textCtrl13->Clear();
	m_textCtrl13->WriteText(headerInfo.gas);
	m_textCtrl131->Clear();
	m_textCtrl131->WriteText(wxString::Format(wxT("%f"), headerInfo.pressure));
	m_textCtrl48->Clear();
	m_textCtrl48->WriteText(wxString::Format(wxT("%f"), headerInfo.discThresh));
	m_textCtrl132->Clear();
	m_textCtrl132->WriteText(wxString::Format(wxT("%f"), headerInfo.quench));
	//m_textCtrl47->WriteText(wxString::Format(wxT("%i"), headerInfo.numRO));
	//m_textCtrl1321->WriteText(headerInfo.roLines);
	//m_textCtrl12->WriteText(headerInfo.triggerRO);
	m_textCtrl24->Clear();
	m_textCtrl24->WriteText(wxString::Format(wxT("%f"), headerInfo.attenRO));
	m_textCtrl1324->Clear();
	m_textCtrl1324->WriteText(wxString::Format(wxT("%i"), headerInfo.numHV));
	m_textCtrl1325->Clear();
	m_textCtrl1325->WriteText(headerInfo.linesHV);
	//m_textCtrl1323->WriteText(headerInfo.triggerHV);
	//m_textCtrl1326->WriteText(wxString::Format(wxT("%f"), headerInfo.attenHV));
	setSourceConfig(headerInfo.sourceConfig);
}

void BigFrame::connectNIMClicked(wxCommandEvent& event)
{
	nim = new WeinerCounter(0);
	m_button19->Disable();
}

void BigFrame::stopSelected(wxCommandEvent& event)
{
	run = false;
}

void BigFrame::startSelected(wxCommandEvent& event)
{
	fstream runfile;
	runfile.open("runfile.txt", std::fstream::in | std::fstream::out);
	char temp[200];
	runfile.getline(temp, 200);
	long int tempNum = atol(temp);
	globalHeader.runNumber = tempNum;
	tempNum++;
	runfile.seekg(0, ios::beg);
	runfile << tempNum;
	runfile.close();

	if (!volt)
	{
		wxMessageBox("Voltage controller not connected");
		run = true;
	}

	if (!nim)
	{
		wxMessageBox("NIMBox not connected");
		run = true;
	}

	if (!mot && !(scanType == "Free" || scanType == "FreeAP"))
	{
		wxMessageBox("X-Y controller not connected");
		run = true;
	}

	if (!pglobalheader)
	{
		wxMessageBox("Header information not found");
		run = true;
	}

	if (!message)
	{
		wxMessageBox("Please update run type information");
		run = true;
	}

	if (!readout)
	{
		wxMessageBox("Readout information not found");
		run = true;
	}

	if (scanType == "LineScan" && run == false)
	{
		run = true;
		thread t1(doLineScan, mot, nim, volt, message, pglobalheader, &run);
		t1.detach();
	}
	else if (scanType == "Free" && run == false)
	{
		run = true;
    //cant use default params for some reason
    vector<int> activeReadout;
    for (size_t i = 0; i < readout->active.size(); ++i){
      if (readout->active[i]){
        activeReadout.push_back(i + 1);
      }
    }
    //void doWeinerCounta(WeinerCounter *nim, double volt, string runType, string runName, HeaderInfoGen* header, Messages* message, Readout* readout, atomic<bool> *run)
    //doWeinerCount(nim, pglobalheader, message, readout, &run);
    thread t1(doWeinerCounta, nim, "", pglobalheader, message, readout, &run);
    //thread t1(doWeinerCountInf, nim, message->voltageStart, pglobalheader, "free", "", &run, readout->lines);
		t1.detach();
	}
	else if (scanType == "FreeAP" && run == false)
	{
		run = true;
    thread t1(doAfterScanGraphMultiFree, nim, pglobalheader, volt, message, readout, &run);
    //run = true;
    t1.detach();
	}
	else if (scanType == "ScanAP" && run == false)
	{
		run = true;
		thread t1(doAfterScanGraphMultiFree, nim, pglobalheader, volt, message, readout, &run);
		//run = true;
		t1.detach();
	}

	//run = false;
	//messagebox.Show(false);
	//messagebox.Destroy();

	else if (scanType == "HexScanX" && run == false)
	{
		run = true;
		thread t1(doHexScanX, mot, nim, volt, message, pglobalheader, &run);
		t1.detach();
	}

	else if (scanType == "XYScan" && run == false)
	{
		run = true;
		thread t1(doXYScan, mot, nim, volt, message, pglobalheader, &run);
		t1.detach();
	}
}

void BigFrame::openReadoutPane(wxCommandEvent& event)
{
	if (!readoutframe)
		readoutframe = new readoutedit(this);
	readoutframe->update();
	readoutframe->Show(true);

}

readoutedit::readoutedit(wxWindow* parent) : MyFrame4(parent)
{

}

void readoutedit::okbuttonclicked(wxCommandEvent &event)
{
	while(!readout->active.empty())
	{
		readout->active.pop_back();
	}
	while (!readout->lines.empty())
	{
		readout->lines.pop_back();
	}

	if (m_checkBox77->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox78->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox79->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox80->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox81->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox82->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox83->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox84->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox85->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox86->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox771->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox781->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox791->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox801->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox811->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox821->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox831->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox841->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox851->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);
	if (m_checkBox861->IsChecked())
		readout->active.push_back(true);
	else
		readout->active.push_back(false);

	int j = 1;

	readout->numActive = 0;
	for (int i = 0; i < 20; i++)
	{
		if (readout->active[i] == true)
		{
			readout->numActive++;
			readout->lines.push_back(i+1);
			//readout->lines[j] = i;
			j++;
		}
	}

	readoutframe->Show(false);
}

void readoutedit::update()
{
	if (readout->active[0] == true)
		m_checkBox77->SetValue(true);
	else
		m_checkBox77->SetValue(false);

	if (readout->active[1] == true)
		m_checkBox78->SetValue(true);
	else
		m_checkBox78->SetValue(false);

	if (readout->active[2] == true)
		m_checkBox79->SetValue(true);
	else
		m_checkBox79->SetValue(false);

	if (readout->active[3] == true)
		m_checkBox80->SetValue(true);
	else
		m_checkBox80->SetValue(false);

	if (readout->active[4] == true)
		m_checkBox81->SetValue(true);
	else
		m_checkBox81->SetValue(false);

	if (readout->active[5] == true)
		m_checkBox82->SetValue(true);
	else
		m_checkBox82->SetValue(false);

	if (readout->active[6] == true)
		m_checkBox83->SetValue(true);
	else
		m_checkBox83->SetValue(false);

	if (readout->active[7] == true)
		m_checkBox84->SetValue(true);
	else
		m_checkBox84->SetValue(false);

	if (readout->active[8] == true)
		m_checkBox85->SetValue(true);
	else
		m_checkBox85->SetValue(false);

	if (readout->active[9] == true)
		m_checkBox86->SetValue(true);
	else
		m_checkBox86->SetValue(false);

	if (readout->active[10] == true)
		m_checkBox771->SetValue(true);
	else
		m_checkBox771->SetValue(false);

	if (readout->active[11] == true)
		m_checkBox781->SetValue(true);
	else
		m_checkBox781->SetValue(false);

	if (readout->active[12] == true)
		m_checkBox791->SetValue(true);
	else
		m_checkBox791->SetValue(false);

	if (readout->active[13] == true)
		m_checkBox801->SetValue(true);
	else
		m_checkBox801->SetValue(false);

	if (readout->active[14] == true)
		m_checkBox811->SetValue(true);
	else
		m_checkBox811->SetValue(false);

	if (readout->active[15] == true)
		m_checkBox821->SetValue(true);
	else
		m_checkBox821->SetValue(false);

	if (readout->active[16] == true)
		m_checkBox831->SetValue(true);
	else
		m_checkBox831->SetValue(false);

	if (readout->active[17] == true)
		m_checkBox841->SetValue(true);
	else
		m_checkBox841->SetValue(false);

	if (readout->active[18] == true)
		m_checkBox851->SetValue(true);
	else
		m_checkBox851->SetValue(false);

	if (readout->active[19] == true)
		m_checkBox861->SetValue(true);
	else
		m_checkBox861->SetValue(false);
}

Histogram::Histogram(wxWindow* parent) : ImageFrame(parent)
{
	display = new wxPanel();
	wxBoxSizer* sizer1;
	sizer1 = new wxBoxSizer(wxVERTICAL);

	sizer1->Add(display);
	this->SetSizer(sizer1);
	this->Layout();
	// run updateimage in a thread


	//display->Connect(wxEVT_PAINT, wxCommandEventHandler(Histogram::paint);

}

void Histogram::updateImage(string filename, atomic<bool> run)
{

	while (run == true)
	{
		//delay 1 second
		this_thread::sleep_for(chrono::microseconds(1000));

		image.LoadFile(filename);
		Update();
		//display image
	}


}

void Histogram::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void Histogram::render(wxDC& dc)
{
	dc.DrawBitmap(image, 0, 0, false);
}

