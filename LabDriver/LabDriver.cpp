#include <wx/wxprec.h>
#include "LabDriver.h"
#include "LabView.h"
#include "MotorController.h"

wxIMPLEMENT_APP(LabDriver);

MotorController *mot = nullptr;


LabDriver::LabDriver()
{

}

LabDriver::~LabDriver()
{
}

bool LabDriver::OnInit()
{

	WeinerCounter *nim = nullptr;
	VoltageControl *volt = nullptr;

	MainFrame* labView = new MainFrame(nullptr, wxID_ANY, "Title");
	labView->Show(true);
	mot = new MotorController(3, 9600);
	return true;
}

