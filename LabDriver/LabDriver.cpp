#include <wx/wxprec.h>
#include "LabDriver.h"
#include "LabView.h"
#include "MotorController.h"
#include "VoltageControlNI.h"

wxIMPLEMENT_APP(LabDriver);

//MotorController *mot = nullptr;
WeinerCounter *nim = nullptr;
//VoltageNI *volt = nullptr;


LabDriver::LabDriver()
{

}

LabDriver::~LabDriver()
{
}

bool LabDriver::OnInit()
{
	BigFrame* thisFrame = new BigFrame(nullptr);
	thisFrame->Show(true);
	return true;
}

