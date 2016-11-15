#include <wx/wxprec.h>
#include "LabDriver.h"
#include "LabView.h"
#include "MotorController.h"
#include "VoltageControlNI.h"

wxIMPLEMENT_APP(LabDriver);

MotorController *mot = nullptr;
WeinerCounter *nim = nullptr;
VoltageNI *volt = nullptr;


LabDriver::LabDriver()
{

}

LabDriver::~LabDriver()
{
}

bool LabDriver::OnInit()
{


	mot = new MotorController(3, 9600);
	MainFrame* labView = new MainFrame(nullptr, wxID_ANY, "Title");
	labView->Show(true);
	return true;
}

