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
#include "VoltageControlNI.h"

// begin wxGlade: ::extracode
// end wxGlade

const float STEPPERTURN = 400;
const float STEPPERMM = STEPPERTURN/25.4; //TODO change this to be se from within the header dialog

//MotorController mot(6, 9600);
extern MotorController* mot;
extern VoltageNI* volt;

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, style)
{
    // begin wxGlade: MainFrame::MainFrame
    button_8 = new wxButton(this, wxID_ANY, _("Set Home"));
    up = new wxButton(this, wxID_ANY, _("Y+"));
	up->Bind(wxEVT_BUTTON, &MainFrame::yUpButtonClicked, this);
    button_2 = new wxButton(this, wxID_ANY, _("X-"));
	button_2->Bind(wxEVT_BUTTON, &MainFrame::xLeftButtonClicked, this);
	button_5 = new wxButton(this, wxID_ANY, _("Home XY"));	
	button_5->Bind(wxEVT_BUTTON, &MainFrame::homeButtonClicked, this);
	button_4 = new wxButton(this, wxID_ANY, _("X+"));
	button_4->Bind(wxEVT_BUTTON, &MainFrame::xRightButtonClicked, this);
    button_6 = new wxButton(this, wxID_ANY, _("Home X"));
	//up->Bind(wxEVT_BUTTON, &MainFrame::goToXHomeButtonClicked, this);
	button_3 = new wxButton(this, wxID_ANY, _("Y-"));
	button_3->Bind(wxEVT_BUTTON, &MainFrame::yDownButtonClicked, this);
    button_7 = new wxButton(this, wxID_ANY, _("Home Y"));
	//up->Bind(wxEVT_BUTTON, &MainFrame::goToYHomeButtonClicked, this);
    const wxString combo_box_1_choices[3] = {"Free","Pixel Scan", "Pixel Map"};
	combo_box_1 = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 3, combo_box_1_choices, 0L, wxDefaultValidator, wxT("Scan Type"));
	combo_box_1->Bind(wxEVT_CHOICE, &MainFrame::scanChooser, this);
	wxArrayString distanceBoxLabels;
	distanceBoxLabels.Add("0.01");
	distanceBoxLabels.Add("0.10");
	distanceBoxLabels.Add("1.00");
	distanceBoxLabels.Add("5.00");
	distanceBoxLabels.Add("10.00");

	distanceBox = new wxRadioBox(this, wxID_ANY, "Distance (mm)", wxDefaultPosition, wxDefaultSize,
		distanceBoxLabels, 5, wxRA_SPECIFY_COLS);
	distanceBox->Bind(wxEVT_RADIOBOX, &MainFrame::distanceBoxClicked, this);
	// own code
	menubar = new wxMenuBar;
	file = new wxMenu;
	edit = new wxMenu;
	
	wxStatusBar* m_statusBar2;
	//wxStatusBar status = new wxStatusBar(this, wxID_ANY);
	m_statusBar2 = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);
	//int x;
	//int y;

	//int* w = &x;
	//int* h = &y;


	//GetSize(w, h);
	//wxSize frameSize(x, y);
	//SetMinSize(size);

	set_properties();
	do_events();
	do_layout();
    // end wxGlade
}


void MainFrame::set_properties()
{
    // begin wxGlade: MainFrame::set_properties
    SetTitle(_("frame_1"));
    // end wxGlade
}


void MainFrame::do_layout()
{
    // begin wxGlade: MainFrame::do_layout
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* chosenType = new wxBoxSizer(wxHORIZONTAL);
    wxGridSizer* grid_sizer_1 = new wxGridSizer(2, 2, 0, 0);
	wxBoxSizer* leftSide = new wxBoxSizer(wxVERTICAL);
    wxGridSizer* grid_sizer_2 = new wxGridSizer(3, 3, 0, 0);
	wxGridSizer* distance = new wxGridSizer(1, 3, 0, 0);
    grid_sizer_2->Add(button_8, 0, wxALIGN_CENTER, 0);
    grid_sizer_2->Add(up, 0, wxEXPAND, 0);
	grid_sizer_2->Add(0, 0);
    grid_sizer_2->Add(button_2, 0, wxEXPAND, 0);
    grid_sizer_2->Add(button_5, 0, wxALIGN_CENTER, 0);
    grid_sizer_2->Add(button_4, 0, wxALIGN_CENTER, 0);// |wxEXPAND
    grid_sizer_2->Add(button_6, 0, wxALIGN_CENTER, 0);
    grid_sizer_2->Add(button_3, 0, wxEXPAND, 0);
    grid_sizer_2->Add(button_7, 0, wxALIGN_CENTER, 0);
	chosenType->Add(combo_box_1);



	//leftSide->Add(grid_sizer_2);
	//leftSide->Add(distanceBox);
	//leftSide->Add(chosenType);
	//sizer_1->Add(leftSide);

    grid_sizer_1->Add(grid_sizer_2, 1, 0, 0);
	grid_sizer_1->Add(0, 0);
	grid_sizer_1->Add(distanceBox, 0, 0, 0);


    //grid_sizer_1->Add(chosenType, 1, 0);
   sizer_1->Add(grid_sizer_1, 1, 0, 0);
    //SetSizer(sizer_1);
    //sizer_1->Fit(this);

	wxMenuItem* pref;
	pref = new wxMenuItem(edit, wxID_ANY, wxString(wxT("pref")), wxEmptyString, wxITEM_NORMAL);
	edit->Append(pref);

	file->Append(wxID_EXIT, wxT("&Quit"));
	//edit->Append(pref, _("Item1"));
	//edit->Append(header);
	menubar->Append(file, wxT("&File"));
	menubar->Append(edit, wxT("&Edit"));


	//pref = new wxMenuItem(edit, wxID_ANY, wxT("&Preferences"));
	//header = new wxMenuItem(edit, wxID_ANY, wxT("&Edit Header"));
	SetMenuBar(menubar);

	Fit();
    Layout();
    // end wxGlade
}

void MainFrame::do_events()
{
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(MainFrame::onQuit));
}

void MainFrame::onQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void MainFrame::yUpButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->stepMotor(2, distanceToMove);

}

void MainFrame::yDownButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->stepMotor(2, -distanceToMove);

}

void MainFrame::xLeftButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->stepMotor(1, distanceToMove);

}

void MainFrame::xRightButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->stepMotor(1, -distanceToMove);

}

void MainFrame::homeButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->setZeroX();
	mot->setZeroY();
}

void MainFrame::goToHomeButtonClicked(wxCommandEvent & event)
{
	//distanceToMove = distanceBox->GetSelection();
	mot->goZero();
}

void MainFrame::distanceBoxClicked(wxCommandEvent & event)
{
	distanceToMove = convertDistance(distanceBox->GetSelection());
}

int MainFrame::convertDistance(int radioButton)
{
	int ret;
	switch (radioButton)
	{
	case 0:
		ret = (int) (0.01 * STEPPERMM);
		break;
	case 1:
		ret = (int)(0.1 * STEPPERMM);
		break;
	case 2:
		ret = (int)(1.0 * STEPPERMM);
		break;
	case 3:
		ret = (int)(5.0 * STEPPERMM);
		break;
	case 4:
		ret = (int)(10.0 * STEPPERMM);
		break;
	default:
		ret = -100;
		break;
	}

	return ret;
}

void MainFrame::scanChooser(wxCommandEvent & event)
{
	static int scanChosen = combo_box_1->GetSelection();

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
	default:
		scanType = "None";
		break;
	}
}
	