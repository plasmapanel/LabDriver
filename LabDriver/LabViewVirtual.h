///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __LABVIEWVIRTUAL_H__
#define __LABVIEWVIRTUAL_H__

//#include <wx/wx.h>

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/radiobox.h>
#include <wx/gbsizer.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/choice.h>
#include <wx/statusbr.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class header
///////////////////////////////////////////////////////////////////////////////
class header : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_textCtrl1;
		wxStaticText* m_staticText11;
		wxTextCtrl* m_textCtrl11;
		wxRadioBox* m_radioBox1;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_textCtrl13;
		wxStaticText* m_staticText141;
		wxTextCtrl* m_textCtrl131;
		wxStaticText* m_staticText1424;
		wxTextCtrl* m_textCtrl1324;
		wxStaticText* m_staticText1425;
		wxTextCtrl* m_textCtrl1325;
		wxStaticText* m_staticText1423;
		wxTextCtrl* m_textCtrl1323;
		wxStaticText* m_staticText142;
		wxTextCtrl* m_textCtrl132;
		wxStaticText* m_staticText1426;
		wxTextCtrl* m_textCtrl1326;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_textCtrl12;
		wxStaticText* m_staticText1421;
		wxTextCtrl* m_textCtrl1321;
		wxStaticText* m_staticText1422;
		wxTextCtrl* m_textCtrl1322;
		wxStaticText* m_staticText25;
		wxTextCtrl* m_textCtrl24;
		wxButton* m_button1;
		wxButton* m_button2;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void panelNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void setPanelName( wxFocusEvent& event ) { event.Skip(); }
		virtual void setSource( wxFocusEvent& event ) { event.Skip(); }
		virtual void setSourceName( wxCommandEvent& event ) { event.Skip(); }
		virtual void setSourceType( wxCommandEvent& event ) { event.Skip(); }
		virtual void setGas( wxFocusEvent& event ) { event.Skip(); }
		virtual void gasEntered( wxCommandEvent& event ) { event.Skip(); }
		virtual void setPressure( wxFocusEvent& event ) { event.Skip(); }
		virtual void pressureEntered( wxCommandEvent& event ) { event.Skip(); }
		virtual void setNumHVLines( wxFocusEvent& event ) { event.Skip(); }
		virtual void numberOfHVLinesEntered( wxCommandEvent& event ) { event.Skip(); }
		virtual void setHVLines( wxFocusEvent& event ) { event.Skip(); }
		virtual void HVLinesEntered( wxCommandEvent& event ) { event.Skip(); }
		virtual void setHVVoltage( wxFocusEvent& event ) { event.Skip(); }
		virtual void HVTriggerVoltageEntered( wxCommandEvent& event ) { event.Skip(); }
		virtual void setQuench( wxFocusEvent& event ) { event.Skip(); }
		virtual void quenceResistanceEntered( wxCommandEvent& event ) { event.Skip(); }
		virtual void setHVAtten( wxFocusEvent& event ) { event.Skip(); }
		virtual void attenuationEntered( wxCommandEvent& event ) { event.Skip(); }
		virtual void setTriggerVoltage( wxFocusEvent& event ) { event.Skip(); }
		virtual void triggerVoltageEntered( wxCommandEvent& event ) { event.Skip(); }
		virtual void setROLines( wxFocusEvent& event ) { event.Skip(); }
		virtual void readoutLinesEntered( wxCommandEvent& event ) { event.Skip(); }
		virtual void setROTrigerVoltage( wxFocusEvent& event ) { event.Skip(); }
		virtual void readoutTriggerEntered( wxCommandEvent& event ) { event.Skip(); }
		virtual void setROAtten( wxFocusEvent& event ) { event.Skip(); }
		virtual void readoutAttenuationTriggered( wxCommandEvent& event ) { event.Skip(); }
		virtual void headerOkClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void headerCancelClicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		header( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Edit Header"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 968,626 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~header();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar2;
		wxMenu* file;
		wxMenu* edit;
		wxStaticText* m_staticText201;
		wxChoice* m_choice2;
		wxButton* m_button15;
		wxButton* m_button16;
		wxStaticText* m_staticText211;
		wxChoice* hvChoice;
		wxButton* m_button17;
		wxButton* m_button18;
		wxButton* homeAll;
		wxButton* up;
		wxButton* m_button5;
		wxButton* left;
		wxButton* home;
		wxButton* right;
		wxButton* homeX;
		wxButton* down;
		wxButton* homeY;
		wxRadioBox* distanceBox;
		wxChoice* m_choice1;
		wxStaticText* m_staticText18;
		wxTextCtrl* m_textCtrl18;
		wxStaticText* m_staticText19;
		wxTextCtrl* m_textCtrl19;
		wxStaticText* m_staticText20;
		wxTextCtrl* m_textCtrl20;
		wxStaticText* m_staticText21;
		wxTextCtrl* m_textCtrl21;
		wxStaticText* m_staticText22;
		wxTextCtrl* m_textCtrl22;
		wxStaticText* m_staticText23;
		wxTextCtrl* m_textCtrl23;
		wxStaticText* m_staticText45;
		wxTextCtrl* m_textCtrl40;
		wxStaticText* m_staticText46;
		wxTextCtrl* m_textCtrl41;
		wxStaticText* m_staticText47;
		wxTextCtrl* m_textCtrl42;
		wxStaticText* m_staticText48;
		wxTextCtrl* m_textCtrl43;
		wxRadioBox* m_radioBox3;
		wxStaticText* m_staticText49;
		wxTextCtrl* m_textCtrl44;
		wxButton* start;
		wxButton* stop;
		wxButton* preview;
		wxStatusBar* m_statusBar1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void openHeaderFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void portSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void motorControllerConnectClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void motorControllerDisconnectClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void HVConnectClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void HVDisconnectClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void setHome( wxCommandEvent& event ) { event.Skip(); }
		virtual void yUpButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void xLeftButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void goToHome( wxCommandEvent& event ) { event.Skip(); }
		virtual void xRightButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void goToHomeX( wxCommandEvent& event ) { event.Skip(); }
		virtual void yDownButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void goToHomeY( wxCommandEvent& event ) { event.Skip(); }
		virtual void distanceBoxClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void scanTypeSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void setXOffset( wxCommandEvent& event ) { event.Skip(); }
		virtual void setYOffset( wxCommandEvent& event ) { event.Skip(); }
		virtual void setXStepSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void setYStepSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void setStartVoltage( wxCommandEvent& event ) { event.Skip(); }
		virtual void setEndVoltage( wxCommandEvent& event ) { event.Skip(); }
		virtual void setVoltageStepSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void setNumPixels( wxCommandEvent& event ) { event.Skip(); }
		virtual void setDwellTime( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleHV( wxCommandEvent& event ) { event.Skip(); }
		virtual void setOutFilename( wxCommandEvent& event ) { event.Skip(); }
		virtual void startSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void stopSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void previewSelected( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LabDriver"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1298,815 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class Counts
///////////////////////////////////////////////////////////////////////////////
class Counts : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText22;
		wxTextCtrl* m_textCtrl20;
		wxStaticText* m_staticText221;
		wxTextCtrl* m_textCtrl201;
		wxStaticText* m_staticText222;
		wxTextCtrl* m_textCtrl202;
		wxStaticText* m_staticText223;
		wxTextCtrl* m_textCtrl203;
		wxStaticText* m_staticText224;
		wxTextCtrl* m_textCtrl204;
		wxStaticText* m_staticText225;
		wxTextCtrl* m_textCtrl205;
		wxStaticText* m_staticText226;
		wxTextCtrl* m_textCtrl206;
		wxStaticText* m_staticText227;
		wxTextCtrl* m_textCtrl207;
		wxStaticText* m_staticText228;
		wxTextCtrl* m_textCtrl208;
		wxStaticText* m_staticText229;
		wxTextCtrl* m_textCtrl209;
		wxStaticText* m_staticText2210;
		wxTextCtrl* m_textCtrl2010;
		wxStaticText* m_staticText2211;
		wxTextCtrl* m_textCtrl2011;
		wxStaticText* m_staticText2212;
		wxTextCtrl* m_textCtrl2012;
		wxStaticText* m_staticText2213;
		wxTextCtrl* m_textCtrl2013;
		wxStaticText* m_staticText2214;
		wxTextCtrl* m_textCtrl2014;
		wxStaticText* m_staticText2215;
		wxTextCtrl* m_textCtrl2015;
		wxStaticText* m_staticText2216;
		wxTextCtrl* m_textCtrl2016;
		wxStaticText* m_staticText2217;
		wxTextCtrl* m_textCtrl2017;
		wxStaticText* m_staticText2218;
		wxTextCtrl* m_textCtrl2018;
		wxStaticText* m_staticText2219;
		wxTextCtrl* m_textCtrl2019;
	
	public:
		
		Counts( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Counts"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 453,771 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~Counts();
	
};

#endif //__LABVIEWVIRTUAL_H__
