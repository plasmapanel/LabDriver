#include <wx/wxprec.h>
#include "LabDriver.h"
#include "LabView.h"

LabDriver::LabDriver()
{
}

LabDriver::~LabDriver()
{
}

bool LabDriver::OnInit()
{
	wxFrame* mainFrame = new wxFrame(nullptr, wxID_ANY, L"MyProject");
	mainFrame->Show(true);
	return true;
}

wxIMPLEMENT_APP(LabDriver);