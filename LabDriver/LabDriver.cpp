#include <wx/wxprec.h>
#include "LabDriver.h"
#include "LabView.h"

wxIMPLEMENT_APP(LabDriver);

LabDriver::LabDriver()
{
}

LabDriver::~LabDriver()
{
}

bool LabDriver::OnInit()
{
	MainFrame* labView = new MainFrame(nullptr, wxID_ANY, "Title");
	labView->Show(true);
	return true;
}

