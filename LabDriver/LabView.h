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

#ifndef __LABVIEW_H
#define __LABVIEW_H

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <string>
#include "LabViewVirtual.h"
#include "headers.h"

#include "MotorController.h"
//#include "VoltageControl.h"
//#include "VoltageControlNI.h"
#include "Panel.h"
#include "messages.h"
#include "Readout.h"
#include "LabUtilities.h"
#include "Offset.h"
#include "TApplication.h"
//#include "json/json.h"

#ifndef APP_CATALOG
#define APP_CATALOG "app"  // replace with the appropriate catalog name
#endif

//#define TRAVELPERSTEP 0.0050

//const double MMPERSTEP = TRAVELPERSTEP;
// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode
// end wxGlade

class BigFrame : public MainFrame
{
public:
	BigFrame(wxWindow* parent );
	void distanceBoxClicked(wxCommandEvent& event);
	int convertDistance(int, int);
	void onQuit(wxCommandEvent& WXUNUSED(event)); 
	void yUpButtonClicked(wxCommandEvent & event);
	void yDownButtonClicked(wxCommandEvent & event);
	void xLeftButtonClicked(wxCommandEvent & event);
	void xRightButtonClicked(wxCommandEvent & event);
	void homeButtonClicked(wxCommandEvent & event);
	void goToHomeButtonClicked(wxCommandEvent & event);
	void toggleHV(wxCommandEvent& event);
	void setStartVoltage(wxCommandEvent& event);
	void motorControllerConnectClicked(wxCommandEvent & event);
	void motorControllerDisconnectClicked(wxCommandEvent & event);
	void HVConnectClicked(wxCommandEvent & event);
	void BigFrame::openPanelFrame(wxCommandEvent& event);
	void scanTypeSelected(wxCommandEvent & event);
	void setEndVoltage(wxCommandEvent & event);
	void updateButtonClicked(wxCommandEvent& event);
	void setHome(wxCommandEvent& event);
	void goToHome(wxCommandEvent& event);
	void openHeaderFrame(wxCommandEvent& event);
	void connectNIMClicked(wxCommandEvent& event);
  void disconnectNIM(wxCommandEvent& event);
	void startSelected(wxCommandEvent& event);
	void HVDisconnectClicked(wxCommandEvent& event);
	void setScanType();
	std::string scanType;
	void openReadoutPane(wxCommandEvent& event);
	void stopSelected(wxCommandEvent& event);
	void markButtonClicked(wxCommandEvent& event);
	void startCamera(wxCommandEvent& event);

	atomic<bool> run = false;

private:
	int distanceToMoveX = 400;
	int distanceToMoveY = 400;




};

class HeaderEdit : public header
{
public:
	HeaderEdit(wxWindow* parent);
	//HeaderInfoGen headerInfo;
	void headerOkClicked(wxCommandEvent& event);
	void headerCancelClicked(wxCommandEvent& event);
	void saveHeader(wxCommandEvent& event);
	void openHeader(wxCommandEvent& event);
	void copyData(HeaderInfoGen &);
	void putData(HeaderInfoGen &);
	void updateGas(wxCommandEvent& event);
	void updateGas();
	

private:
	string getSourceConfig();
	void setSourceConfig(string type);
};


class readoutedit : public MyFrame4
{
public:
	readoutedit(wxWindow* parent);

	void okbuttonclicked(wxCommandEvent& event);
	void update();

};

class Histogram : public ImageFrame
{
public:
	Histogram(wxWindow* parent);
	wxPanel* display;
	void OnPaint();
	void OnSize();
	void OnMouseMove();
	void OnLMouseDown();
	void OnRefreshTimer();
};


#endif // ..PY_H