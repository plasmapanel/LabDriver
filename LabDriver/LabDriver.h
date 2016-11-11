#include "WeinerCounter.h"
#include "stdafx.h"
#include <iostream>
#include "LabUtilities.h"
#include "MotorController.h"
#include "messages.h"
#include "windows.h"
#include <wx/wx.h>
//#include "VxmDriver.h" //remove this
using namespace std;

#pragma once

class LabDriver :
	public wxApp
{
public:
	LabDriver();
	virtual ~LabDriver();
	virtual bool OnInit() override;
};