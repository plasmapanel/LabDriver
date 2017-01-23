///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __LABVIEWVIRTUAL_H__
#define __LABVIEWVIRTUAL_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/radiobox.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/choice.h>
#include <wx/gbsizer.h>
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
		wxComboBox* m_comboBox1;
		wxTextCtrl* m_textCtrl49;
		wxComboBox* m_comboBox2;
		wxTextCtrl* m_textCtrl50;
		wxComboBox* m_comboBox3;
		wxTextCtrl* m_textCtrl51;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_textCtrl13;
		wxStaticText* m_staticText51;
		wxTextCtrl* m_textCtrl52;
		wxStaticText* m_staticText141;
		wxTextCtrl* m_textCtrl131;
		wxStaticText* m_staticText142;
		wxTextCtrl* m_textCtrl132;
		wxStaticText* m_staticText1424;
		wxTextCtrl* m_textCtrl1324;
		wxStaticText* m_staticText1425;
		wxTextCtrl* m_textCtrl1325;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_textCtrl12;
		wxStaticText* m_staticText49;
		wxTextCtrl* m_textCtrl47;
		wxStaticText* m_staticText1421;
		wxTextCtrl* m_textCtrl1321;
		wxStaticText* m_staticText25;
		wxTextCtrl* m_textCtrl24;
		wxStaticText* m_staticText1422;
		wxTextCtrl* m_textCtrl1322;
		wxStaticText* discThr;
		wxTextCtrl* m_textCtrl48;
		wxButton* m_button1;
		wxButton* m_button2;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void setPanelName( wxFocusEvent& event ) { event.Skip(); }
		virtual void setSource( wxFocusEvent& event ) { event.Skip(); }
		virtual void updateGas( wxCommandEvent& event ) { event.Skip(); }
		virtual void setGas( wxFocusEvent& event ) { event.Skip(); }
		virtual void setPressure( wxFocusEvent& event ) { event.Skip(); }
		virtual void setQuench( wxFocusEvent& event ) { event.Skip(); }
		virtual void setNumHVLines( wxFocusEvent& event ) { event.Skip(); }
		virtual void setHVLines( wxFocusEvent& event ) { event.Skip(); }
		virtual void setTriggerVoltage( wxFocusEvent& event ) { event.Skip(); }
		virtual void setROLines( wxFocusEvent& event ) { event.Skip(); }
		virtual void setROAtten( wxFocusEvent& event ) { event.Skip(); }
		virtual void setROTrigerVoltage( wxFocusEvent& event ) { event.Skip(); }
		virtual void headerOkClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void headerCancelClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void openHeader( wxCommandEvent& event ) { event.Skip(); }
		virtual void saveHeader( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		header( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Edit Header"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 905,626 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
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
		wxButton* m_button20;
		wxStaticText* m_staticText471;
		wxTextCtrl* m_textCtrl45;
		wxStaticText* m_staticText481;
		wxTextCtrl* m_textCtrl46;
		wxButton* start;
		wxButton* stop;
		wxButton* preview;
		wxButton* m_button19;
		wxStatusBar* m_statusBar1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void openHeaderFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void openPanelFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void portSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void motorControllerConnectClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void motorControllerDisconnectClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void HVConnectClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void HVDisconnectClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void setHome( wxCommandEvent& event ) { event.Skip(); }
		virtual void yUpButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void markButtonClicked( wxCommandEvent& event ) { event.Skip(); }
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
		virtual void setEndVoltage( wxFocusEvent& event ) { event.Skip(); }
		virtual void setVoltageStepSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void setNumPixels( wxCommandEvent& event ) { event.Skip(); }
		virtual void setDwellTime( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleHV( wxCommandEvent& event ) { event.Skip(); }
		virtual void setOutFilename( wxCommandEvent& event ) { event.Skip(); }
		virtual void updateButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void startSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void stopSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void previewSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void connectNIMClicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LabDriver"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1298,815 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class UserEnd
///////////////////////////////////////////////////////////////////////////////
class UserEnd : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText50;
		wxButton* m_button21;
		
		// Virtual event handlers, overide them in your derived class
		virtual void StopClicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		UserEnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Stop Button"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 223,188 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~UserEnd();
	
};

#endif //__LABVIEWVIRTUAL_H__
