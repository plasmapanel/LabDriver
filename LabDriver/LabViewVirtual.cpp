///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "LabViewVirtual.h"

///////////////////////////////////////////////////////////////////////////

header::header( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Panel Information") ), wxHORIZONTAL );
	
	wxGridBagSizer* gbSizer3;
	gbSizer3 = new wxGridBagSizer( 0, 0 );
	gbSizer3->SetFlexibleDirection( wxBOTH );
	gbSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Panel Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_textCtrl1 = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_textCtrl1, 0, wxALL, 5 );
	
	
	gbSizer3->Add( bSizer2, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Source"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer30->Add( m_staticText11, 0, wxALL, 5 );
	
	m_textCtrl11 = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer30->Add( m_textCtrl11, 0, wxALL, 5 );
	
	
	gbSizer3->Add( bSizer30, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	wxString m_radioBox1Choices[] = { wxT("Static"), wxT("Dynamic"), wxT("User") };
	int m_radioBox1NChoices = sizeof( m_radioBox1Choices ) / sizeof( wxString );
	m_radioBox1 = new wxRadioBox( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Source Setup"), wxDefaultPosition, wxDefaultSize, m_radioBox1NChoices, m_radioBox1Choices, 1, wxRA_SPECIFY_ROWS );
	m_radioBox1->SetSelection( 1 );
	gbSizer3->Add( m_radioBox1, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	
	sbSizer1->Add( gbSizer3, 1, wxEXPAND, 5 );
	
	
	bSizer21->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Gas Information") ), wxHORIZONTAL );
	
	wxGridBagSizer* gbSizer4;
	gbSizer4 = new wxGridBagSizer( 0, 0 );
	gbSizer4->SetFlexibleDirection( wxBOTH );
	gbSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText14 = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Gas"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer3->Add( m_staticText14, 0, wxALL, 5 );
	
	m_textCtrl13 = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_textCtrl13, 0, wxALL, 5 );
	
	
	gbSizer4->Add( bSizer3, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText141 = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Pressure (Torr)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText141->Wrap( -1 );
	bSizer31->Add( m_staticText141, 0, wxALL, 5 );
	
	m_textCtrl131 = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_textCtrl131, 0, wxALL, 5 );
	
	
	gbSizer4->Add( bSizer31, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	
	sbSizer3->Add( gbSizer4, 1, wxEXPAND, 5 );
	
	
	bSizer21->Add( sbSizer3, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("High Voltage") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 0, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxVERTICAL );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer324;
	bSizer324 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1424 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Number of HV Lines"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1424->Wrap( -1 );
	bSizer324->Add( m_staticText1424, 0, wxALL, 5 );
	
	m_textCtrl1324 = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer324->Add( m_textCtrl1324, 0, wxALL, 5 );
	
	
	fgSizer2->Add( bSizer324, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer325;
	bSizer325 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1425 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("HV Lines"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1425->Wrap( -1 );
	bSizer325->Add( m_staticText1425, 0, wxALL, 5 );
	
	m_textCtrl1325 = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer325->Add( m_textCtrl1325, 0, wxALL, 5 );
	
	
	fgSizer2->Add( bSizer325, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer323;
	bSizer323 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1423 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Trigger Voltage"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1423->Wrap( -1 );
	bSizer323->Add( m_staticText1423, 0, wxALL, 5 );
	
	m_textCtrl1323 = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer323->Add( m_textCtrl1323, 0, wxALL, 5 );
	
	
	fgSizer2->Add( bSizer323, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText142 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Quench Resistance:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText142->Wrap( -1 );
	bSizer32->Add( m_staticText142, 0, wxALL, 5 );
	
	m_textCtrl132 = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_textCtrl132, 0, wxALL, 5 );
	
	
	fgSizer2->Add( bSizer32, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer326;
	bSizer326 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1426 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Attenuation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1426->Wrap( -1 );
	bSizer326->Add( m_staticText1426, 0, wxALL, 5 );
	
	m_textCtrl1326 = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer326->Add( m_textCtrl1326, 0, wxALL, 5 );
	
	
	fgSizer2->Add( bSizer326, 1, wxEXPAND, 5 );
	
	
	sbSizer2->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	
	bSizer21->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Readout Information") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer2;
	gbSizer2 = new wxGridBagSizer( 0, 0 );
	gbSizer2->SetFlexibleDirection( wxBOTH );
	gbSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText13 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Trigger Voltge:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer1->Add( m_staticText13, 0, wxALL, 5 );
	
	m_textCtrl12 = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_textCtrl12, 0, wxALL, 5 );
	
	
	gbSizer2->Add( bSizer1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	wxBoxSizer* bSizer321;
	bSizer321 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1421 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("RO Lines"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1421->Wrap( -1 );
	bSizer321->Add( m_staticText1421, 0, wxALL, 5 );
	
	m_textCtrl1321 = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer321->Add( m_textCtrl1321, 0, wxALL, 5 );
	
	
	gbSizer2->Add( bSizer321, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	wxBoxSizer* bSizer322;
	bSizer322 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1422 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Ro Trigger"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1422->Wrap( -1 );
	bSizer322->Add( m_staticText1422, 0, wxALL, 5 );
	
	m_textCtrl1322 = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer322->Add( m_textCtrl1322, 0, wxALL, 5 );
	
	
	gbSizer2->Add( bSizer322, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText25 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Attenuation (dB):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	bSizer20->Add( m_staticText25, 0, wxALL, 5 );
	
	m_textCtrl24 = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_textCtrl24, 0, wxALL, 5 );
	
	
	gbSizer2->Add( bSizer20, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	
	sbSizer4->Add( gbSizer2, 1, wxEXPAND, 5 );
	
	
	bSizer21->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer44;
	bSizer44 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button1 = new wxButton( this, wxID_ANY, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer44->Add( m_button1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_button2 = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer44->Add( m_button2, 0, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer21->Add( bSizer44, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer21 );
	this->Layout();
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Open Header File") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem1 );
	
	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Preview Header") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem2 );
	
	m_menubar1->Append( m_menu1, wxT("File") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_textCtrl1->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::panelNameChange ), NULL, this );
	m_staticText11->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setPanelName ), NULL, this );
	m_textCtrl11->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setSource ), NULL, this );
	m_textCtrl11->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::setSourceName ), NULL, this );
	m_radioBox1->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( header::setSourceType ), NULL, this );
	m_textCtrl13->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setGas ), NULL, this );
	m_textCtrl13->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::gasEntered ), NULL, this );
	m_textCtrl131->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setPressure ), NULL, this );
	m_textCtrl131->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::pressureEntered ), NULL, this );
	m_textCtrl1324->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setNumHVLines ), NULL, this );
	m_textCtrl1324->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::numberOfHVLinesEntered ), NULL, this );
	m_textCtrl1325->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setHVLines ), NULL, this );
	m_textCtrl1325->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::HVLinesEntered ), NULL, this );
	m_textCtrl1323->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setHVVoltage ), NULL, this );
	m_textCtrl1323->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::HVTriggerVoltageEntered ), NULL, this );
	m_textCtrl132->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setQuench ), NULL, this );
	m_textCtrl132->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::quenceResistanceEntered ), NULL, this );
	m_textCtrl1326->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setHVAtten ), NULL, this );
	m_textCtrl1326->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::attenuationEntered ), NULL, this );
	m_textCtrl12->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setTriggerVoltage ), NULL, this );
	m_textCtrl12->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::triggerVoltageEntered ), NULL, this );
	m_textCtrl1321->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setROLines ), NULL, this );
	m_textCtrl1321->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::readoutLinesEntered ), NULL, this );
	m_textCtrl1322->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setROTrigerVoltage ), NULL, this );
	m_textCtrl1322->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::readoutTriggerEntered ), NULL, this );
	m_textCtrl24->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setROAtten ), NULL, this );
	m_textCtrl24->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::readoutAttenuationTriggered ), NULL, this );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( header::headerOkClicked ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( header::headerCancelClicked ), NULL, this );
}

header::~header()
{
	// Disconnect Events
	m_textCtrl1->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::panelNameChange ), NULL, this );
	m_staticText11->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setPanelName ), NULL, this );
	m_textCtrl11->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setSource ), NULL, this );
	m_textCtrl11->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::setSourceName ), NULL, this );
	m_radioBox1->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( header::setSourceType ), NULL, this );
	m_textCtrl13->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setGas ), NULL, this );
	m_textCtrl13->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::gasEntered ), NULL, this );
	m_textCtrl131->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setPressure ), NULL, this );
	m_textCtrl131->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::pressureEntered ), NULL, this );
	m_textCtrl1324->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setNumHVLines ), NULL, this );
	m_textCtrl1324->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::numberOfHVLinesEntered ), NULL, this );
	m_textCtrl1325->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setHVLines ), NULL, this );
	m_textCtrl1325->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::HVLinesEntered ), NULL, this );
	m_textCtrl1323->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setHVVoltage ), NULL, this );
	m_textCtrl1323->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::HVTriggerVoltageEntered ), NULL, this );
	m_textCtrl132->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setQuench ), NULL, this );
	m_textCtrl132->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::quenceResistanceEntered ), NULL, this );
	m_textCtrl1326->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setHVAtten ), NULL, this );
	m_textCtrl1326->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::attenuationEntered ), NULL, this );
	m_textCtrl12->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setTriggerVoltage ), NULL, this );
	m_textCtrl12->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::triggerVoltageEntered ), NULL, this );
	m_textCtrl1321->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setROLines ), NULL, this );
	m_textCtrl1321->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::readoutLinesEntered ), NULL, this );
	m_textCtrl1322->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setROTrigerVoltage ), NULL, this );
	m_textCtrl1322->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::readoutTriggerEntered ), NULL, this );
	m_textCtrl24->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setROAtten ), NULL, this );
	m_textCtrl24->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::readoutAttenuationTriggered ), NULL, this );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( header::headerOkClicked ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( header::headerCancelClicked ), NULL, this );
	
}

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar2 = new wxMenuBar( 0 );
	file = new wxMenu();
	wxMenuItem* menu_quit;
	menu_quit = new wxMenuItem( file, wxID_EXIT, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	file->Append( menu_quit );
	
	m_menubar2->Append( file, wxT("File") ); 
	
	edit = new wxMenu();
	wxMenuItem* menuHeader;
	menuHeader = new wxMenuItem( edit, wxID_ANY, wxString( wxT("Header") ) , wxEmptyString, wxITEM_NORMAL );
	edit->Append( menuHeader );
	
	wxMenuItem* m_menuItem5;
	m_menuItem5 = new wxMenuItem( edit, wxID_ANY, wxString( wxT("Panel") ) , wxEmptyString, wxITEM_NORMAL );
	edit->Append( m_menuItem5 );
	
	m_menubar2->Append( edit, wxT("Edit") ); 
	
	this->SetMenuBar( m_menubar2 );
	
	wxGridBagSizer* gbSizer4;
	gbSizer4 = new wxGridBagSizer( 0, 0 );
	gbSizer4->SetFlexibleDirection( wxBOTH );
	gbSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Motor Controller Setup") ), wxHORIZONTAL );
	
	m_staticText201 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Port"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText201->Wrap( -1 );
	sbSizer6->Add( m_staticText201, 0, wxALL, 5 );
	
	wxArrayString m_choice2Choices;
	m_choice2 = new wxChoice( sbSizer6->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice2Choices, 0 );
	m_choice2->SetSelection( 0 );
	sbSizer6->Add( m_choice2, 0, wxALL, 5 );
	
	m_button15 = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer6->Add( m_button15, 0, wxALL, 5 );
	
	m_button16 = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Disconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer6->Add( m_button16, 0, wxALL, 5 );
	
	
	fgSizer3->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("High Voltage Setup") ), wxHORIZONTAL );
	
	m_staticText211 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	sbSizer10->Add( m_staticText211, 0, wxALL, 5 );
	
	wxString hvChoiceChoices[] = { wxT("NI"), wxT("Yellow") };
	int hvChoiceNChoices = sizeof( hvChoiceChoices ) / sizeof( wxString );
	hvChoice = new wxChoice( sbSizer10->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, hvChoiceNChoices, hvChoiceChoices, 0 );
	hvChoice->SetSelection( 0 );
	sbSizer10->Add( hvChoice, 0, wxALL, 5 );
	
	m_button17 = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( m_button17, 0, wxALL, 5 );
	
	m_button18 = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Disconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( m_button18, 0, wxALL, 5 );
	
	
	fgSizer3->Add( sbSizer10, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 3, 0, 0 );
	
	homeAll = new wxButton( this, wxID_ANY, wxT("Set Home"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( homeAll, 0, wxALL, 5 );
	
	up = new wxButton( this, wxID_ANY, wxT("Y+"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( up, 0, wxALL, 5 );
	
	m_button5 = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_button5, 0, wxALL, 5 );
	
	left = new wxButton( this, wxID_ANY, wxT("X-"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( left, 0, wxALL, 5 );
	
	home = new wxButton( this, wxID_ANY, wxT("Home XY"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( home, 0, wxALL, 5 );
	
	right = new wxButton( this, wxID_ANY, wxT("X+"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( right, 0, wxALL, 5 );
	
	homeX = new wxButton( this, wxID_ANY, wxT("Home X"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( homeX, 0, wxALL, 5 );
	
	down = new wxButton( this, wxID_ANY, wxT("Y-"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( down, 0, wxALL, 5 );
	
	homeY = new wxButton( this, wxID_ANY, wxT("Home Y"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( homeY, 0, wxALL, 5 );
	
	
	bSizer19->Add( gSizer1, 1, wxEXPAND, 5 );
	
	wxString distanceBoxChoices[] = { wxT("0.1"), wxT("1.0"), wxT("5.0"), wxT("10.0") };
	int distanceBoxNChoices = sizeof( distanceBoxChoices ) / sizeof( wxString );
	distanceBox = new wxRadioBox( this, wxID_ANY, wxT("Travel Distance"), wxDefaultPosition, wxDefaultSize, distanceBoxNChoices, distanceBoxChoices, 4, wxRA_SPECIFY_COLS );
	distanceBox->SetSelection( 2 );
	bSizer19->Add( distanceBox, 0, wxALL, 5 );
	
	
	fgSizer3->Add( bSizer19, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Scan Type") ), wxVERTICAL );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxHORIZONTAL );
	
	
	sbSizer5->Add( bSizer40, 1, wxEXPAND, 5 );
	
	wxString m_choice1Choices[] = { wxT("Free"), wxT("PixelScan"), wxT("PixelMap") };
	int m_choice1NChoices = sizeof( m_choice1Choices ) / sizeof( wxString );
	m_choice1 = new wxChoice( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	sbSizer5->Add( m_choice1, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText18 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("X Offset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer2->Add( m_staticText18, 0, wxALL, 5 );
	
	m_textCtrl18 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl18, 0, wxALL, 5 );
	
	m_staticText19 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Y Offset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer2->Add( m_staticText19, 0, wxALL, 5 );
	
	m_textCtrl19 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl19, 0, wxALL, 5 );
	
	m_staticText20 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("X Step Size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer2->Add( m_staticText20, 0, wxALL, 5 );
	
	m_textCtrl20 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl20, 0, wxALL, 5 );
	
	m_staticText21 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Y Step Size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer2->Add( m_staticText21, 0, wxALL, 5 );
	
	m_textCtrl21 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl21, 0, wxALL, 5 );
	
	m_staticText22 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Start Voltage"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALL, 5 );
	
	m_textCtrl22 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl22, 0, wxALL, 5 );
	
	m_staticText23 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("End Voltage"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer2->Add( m_staticText23, 0, wxALL, 5 );
	
	m_textCtrl23 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl23, 0, wxALL, 5 );
	
	m_staticText45 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Voltage Step Size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	fgSizer2->Add( m_staticText45, 0, wxALL, 5 );
	
	m_textCtrl40 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl40, 0, wxALL, 5 );
	
	m_staticText46 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Number of Pixels"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	fgSizer2->Add( m_staticText46, 0, wxALL, 5 );
	
	m_textCtrl41 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl41, 0, wxALL, 5 );
	
	m_staticText47 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Measurement Time"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47->Wrap( -1 );
	fgSizer2->Add( m_staticText47, 0, wxALL, 5 );
	
	m_textCtrl42 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl42, 0, wxALL, 5 );
	
	m_staticText48 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	fgSizer2->Add( m_staticText48, 0, wxALL, 5 );
	
	m_textCtrl43 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl43, 0, wxALL, 5 );
	
	wxString m_radioBox3Choices[] = { wxT("On"), wxT("Off") };
	int m_radioBox3NChoices = sizeof( m_radioBox3Choices ) / sizeof( wxString );
	m_radioBox3 = new wxRadioBox( sbSizer5->GetStaticBox(), wxID_ANY, wxT("High Voltage"), wxDefaultPosition, wxDefaultSize, m_radioBox3NChoices, m_radioBox3Choices, 2, wxRA_SPECIFY_COLS );
	m_radioBox3->SetSelection( 0 );
	fgSizer2->Add( m_radioBox3, 0, wxALL, 5 );
	
	m_staticText49 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Output File Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText49->Wrap( -1 );
	fgSizer2->Add( m_staticText49, 0, wxALL, 5 );
	
	m_textCtrl44 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl44, 0, wxALL, 5 );
	
	
	sbSizer5->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	
	fgSizer3->Add( sbSizer5, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );
	
	start = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( start, 0, wxALIGN_CENTER|wxALL, 5 );
	
	stop = new wxButton( this, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( stop, 0, wxALIGN_CENTER|wxALL, 5 );
	
	preview = new wxButton( this, wxID_ANY, wxT("Run Preview"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( preview, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_button19 = new wxButton( this, wxID_ANY, wxT("Connect NIM"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( m_button19, 0, wxALL, 5 );
	
	
	fgSizer3->Add( bSizer17, 1, wxEXPAND, 5 );
	
	
	gbSizer4->Add( fgSizer3, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), 0, 5 );
	
	
	this->SetSizer( gbSizer4 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 5, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( menu_quit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::onQuit ) );
	this->Connect( menuHeader->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::openHeaderFrame ) );
	this->Connect( m_menuItem5->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::openPanelFrame ) );
	m_choice2->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::portSelected ), NULL, this );
	m_button15->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::motorControllerConnectClicked ), NULL, this );
	m_button16->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::motorControllerDisconnectClicked ), NULL, this );
	m_button17->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::HVConnectClicked ), NULL, this );
	m_button18->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::HVDisconnectClicked ), NULL, this );
	homeAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::setHome ), NULL, this );
	up->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::yUpButtonClicked ), NULL, this );
	left->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::xLeftButtonClicked ), NULL, this );
	home->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::goToHome ), NULL, this );
	right->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::xRightButtonClicked ), NULL, this );
	homeX->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::goToHomeX ), NULL, this );
	down->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::yDownButtonClicked ), NULL, this );
	homeY->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::goToHomeY ), NULL, this );
	distanceBox->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MainFrame::distanceBoxClicked ), NULL, this );
	m_choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::scanTypeSelected ), NULL, this );
	m_textCtrl18->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setXOffset ), NULL, this );
	m_textCtrl19->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setYOffset ), NULL, this );
	m_textCtrl20->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setXStepSize ), NULL, this );
	m_textCtrl21->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setYStepSize ), NULL, this );
	m_textCtrl22->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setStartVoltage ), NULL, this );
	m_textCtrl23->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setEndVoltage ), NULL, this );
	m_textCtrl40->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setVoltageStepSize ), NULL, this );
	m_textCtrl41->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setNumPixels ), NULL, this );
	m_textCtrl42->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setDwellTime ), NULL, this );
	m_radioBox3->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MainFrame::toggleHV ), NULL, this );
	m_textCtrl44->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setOutFilename ), NULL, this );
	start->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::startSelected ), NULL, this );
	stop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::stopSelected ), NULL, this );
	preview->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::previewSelected ), NULL, this );
	m_button19->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::connectNIMClicked ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::onQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::openHeaderFrame ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::openPanelFrame ) );
	m_choice2->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::portSelected ), NULL, this );
	m_button15->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::motorControllerConnectClicked ), NULL, this );
	m_button16->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::motorControllerDisconnectClicked ), NULL, this );
	m_button17->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::HVConnectClicked ), NULL, this );
	m_button18->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::HVDisconnectClicked ), NULL, this );
	homeAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::setHome ), NULL, this );
	up->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::yUpButtonClicked ), NULL, this );
	left->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::xLeftButtonClicked ), NULL, this );
	home->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::goToHome ), NULL, this );
	right->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::xRightButtonClicked ), NULL, this );
	homeX->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::goToHomeX ), NULL, this );
	down->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::yDownButtonClicked ), NULL, this );
	homeY->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::goToHomeY ), NULL, this );
	distanceBox->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MainFrame::distanceBoxClicked ), NULL, this );
	m_choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::scanTypeSelected ), NULL, this );
	m_textCtrl18->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setXOffset ), NULL, this );
	m_textCtrl19->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setYOffset ), NULL, this );
	m_textCtrl20->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setXStepSize ), NULL, this );
	m_textCtrl21->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setYStepSize ), NULL, this );
	m_textCtrl22->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setStartVoltage ), NULL, this );
	m_textCtrl23->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setEndVoltage ), NULL, this );
	m_textCtrl40->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setVoltageStepSize ), NULL, this );
	m_textCtrl41->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setNumPixels ), NULL, this );
	m_textCtrl42->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setDwellTime ), NULL, this );
	m_radioBox3->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MainFrame::toggleHV ), NULL, this );
	m_textCtrl44->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setOutFilename ), NULL, this );
	start->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::startSelected ), NULL, this );
	stop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::stopSelected ), NULL, this );
	preview->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::previewSelected ), NULL, this );
	m_button19->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::connectNIMClicked ), NULL, this );
	
}

Counts::Counts( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText22 = new wxStaticText( this, wxID_ANY, wxT("CH1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer19->Add( m_staticText22, 0, wxALL, 5 );
	
	m_textCtrl20 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_textCtrl20, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer19, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer191;
	bSizer191 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText221 = new wxStaticText( this, wxID_ANY, wxT("CH2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText221->Wrap( -1 );
	bSizer191->Add( m_staticText221, 0, wxALL, 5 );
	
	m_textCtrl201 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( m_textCtrl201, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer191, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer192;
	bSizer192 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText222 = new wxStaticText( this, wxID_ANY, wxT("CH3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText222->Wrap( -1 );
	bSizer192->Add( m_staticText222, 0, wxALL, 5 );
	
	m_textCtrl202 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer192->Add( m_textCtrl202, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer192, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer193;
	bSizer193 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText223 = new wxStaticText( this, wxID_ANY, wxT("CH4"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText223->Wrap( -1 );
	bSizer193->Add( m_staticText223, 0, wxALL, 5 );
	
	m_textCtrl203 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer193->Add( m_textCtrl203, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer193, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer194;
	bSizer194 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText224 = new wxStaticText( this, wxID_ANY, wxT("CH5"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText224->Wrap( -1 );
	bSizer194->Add( m_staticText224, 0, wxALL, 5 );
	
	m_textCtrl204 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer194->Add( m_textCtrl204, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer194, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer195;
	bSizer195 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText225 = new wxStaticText( this, wxID_ANY, wxT("CH6"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText225->Wrap( -1 );
	bSizer195->Add( m_staticText225, 0, wxALL, 5 );
	
	m_textCtrl205 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer195->Add( m_textCtrl205, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer195, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer196;
	bSizer196 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText226 = new wxStaticText( this, wxID_ANY, wxT("CH7"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText226->Wrap( -1 );
	bSizer196->Add( m_staticText226, 0, wxALL, 5 );
	
	m_textCtrl206 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer196->Add( m_textCtrl206, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer196, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer197;
	bSizer197 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText227 = new wxStaticText( this, wxID_ANY, wxT("CH8"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText227->Wrap( -1 );
	bSizer197->Add( m_staticText227, 0, wxALL, 5 );
	
	m_textCtrl207 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer197->Add( m_textCtrl207, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer197, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer198;
	bSizer198 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText228 = new wxStaticText( this, wxID_ANY, wxT("CH9"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText228->Wrap( -1 );
	bSizer198->Add( m_staticText228, 0, wxALL, 5 );
	
	m_textCtrl208 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer198->Add( m_textCtrl208, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer198, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer199;
	bSizer199 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText229 = new wxStaticText( this, wxID_ANY, wxT("CH10"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText229->Wrap( -1 );
	bSizer199->Add( m_staticText229, 0, wxALL, 5 );
	
	m_textCtrl209 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer199->Add( m_textCtrl209, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer199, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1910;
	bSizer1910 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2210 = new wxStaticText( this, wxID_ANY, wxT("CH11"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2210->Wrap( -1 );
	bSizer1910->Add( m_staticText2210, 0, wxALL, 5 );
	
	m_textCtrl2010 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1910->Add( m_textCtrl2010, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer1910, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1911;
	bSizer1911 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2211 = new wxStaticText( this, wxID_ANY, wxT("CH12"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2211->Wrap( -1 );
	bSizer1911->Add( m_staticText2211, 0, wxALL, 5 );
	
	m_textCtrl2011 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1911->Add( m_textCtrl2011, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer1911, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1912;
	bSizer1912 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2212 = new wxStaticText( this, wxID_ANY, wxT("CH13"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2212->Wrap( -1 );
	bSizer1912->Add( m_staticText2212, 0, wxALL, 5 );
	
	m_textCtrl2012 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1912->Add( m_textCtrl2012, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer1912, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1913;
	bSizer1913 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2213 = new wxStaticText( this, wxID_ANY, wxT("CH14"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2213->Wrap( -1 );
	bSizer1913->Add( m_staticText2213, 0, wxALL, 5 );
	
	m_textCtrl2013 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1913->Add( m_textCtrl2013, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer1913, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1914;
	bSizer1914 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2214 = new wxStaticText( this, wxID_ANY, wxT("CH15"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2214->Wrap( -1 );
	bSizer1914->Add( m_staticText2214, 0, wxALL, 5 );
	
	m_textCtrl2014 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1914->Add( m_textCtrl2014, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer1914, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1915;
	bSizer1915 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2215 = new wxStaticText( this, wxID_ANY, wxT("CH16"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2215->Wrap( -1 );
	bSizer1915->Add( m_staticText2215, 0, wxALL, 5 );
	
	m_textCtrl2015 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1915->Add( m_textCtrl2015, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer1915, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1916;
	bSizer1916 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2216 = new wxStaticText( this, wxID_ANY, wxT("CH17"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2216->Wrap( -1 );
	bSizer1916->Add( m_staticText2216, 0, wxALL, 5 );
	
	m_textCtrl2016 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1916->Add( m_textCtrl2016, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer1916, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1917;
	bSizer1917 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2217 = new wxStaticText( this, wxID_ANY, wxT("CH18"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2217->Wrap( -1 );
	bSizer1917->Add( m_staticText2217, 0, wxALL, 5 );
	
	m_textCtrl2017 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1917->Add( m_textCtrl2017, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer1917, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1918;
	bSizer1918 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2218 = new wxStaticText( this, wxID_ANY, wxT("CH19"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2218->Wrap( -1 );
	bSizer1918->Add( m_staticText2218, 0, wxALL, 5 );
	
	m_textCtrl2018 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1918->Add( m_textCtrl2018, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer1918, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1919;
	bSizer1919 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2219 = new wxStaticText( this, wxID_ANY, wxT("CH20"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2219->Wrap( -1 );
	bSizer1919->Add( m_staticText2219, 0, wxALL, 5 );
	
	m_textCtrl2019 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1919->Add( m_textCtrl2019, 0, wxALL, 5 );
	
	
	bSizer18->Add( bSizer1919, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer18 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

Counts::~Counts()
{
}
