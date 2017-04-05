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
	
	m_staticText1 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Panel Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	sbSizer1->Add( m_staticText1, 0, wxALL, 5 );
	
	m_textCtrl1 = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Test"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer1->Add( m_textCtrl1, 0, wxALL, 5 );
	
	
	bSizer21->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("label") ), wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Source"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	sbSizer9->Add( m_staticText11, 0, wxALL, 5 );
	
	m_textCtrl11 = new wxTextCtrl( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Sr90"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer9->Add( m_textCtrl11, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	
	sbSizer9->Add( bSizer22, 1, wxEXPAND, 5 );
	
	wxString m_radioBox1Choices[] = { wxT("Static"), wxT("Dynamic"), wxT("User") };
	int m_radioBox1NChoices = sizeof( m_radioBox1Choices ) / sizeof( wxString );
	m_radioBox1 = new wxRadioBox( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Source Setup"), wxDefaultPosition, wxDefaultSize, m_radioBox1NChoices, m_radioBox1Choices, 1, wxRA_SPECIFY_ROWS );
	m_radioBox1->SetSelection( 0 );
	sbSizer9->Add( m_radioBox1, 0, wxALL, 5 );
	
	m_staticText29 = new wxStaticText( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Collimator (mm)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	sbSizer9->Add( m_staticText29, 0, wxALL, 5 );
	
	m_textCtrl29 = new wxTextCtrl( sbSizer9->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer9->Add( m_textCtrl29, 0, wxALL, 5 );
	
	m_staticText30 = new wxStaticText( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Source Height (mm)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	sbSizer9->Add( m_staticText30, 0, wxALL, 5 );
	
	m_textCtrl30 = new wxTextCtrl( sbSizer9->GetStaticBox(), wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer9->Add( m_textCtrl30, 0, wxALL, 5 );
	
	
	bSizer21->Add( sbSizer9, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Gas Information") ), wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Mix") ), wxHORIZONTAL );
	
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxVERTICAL );
	
	m_comboBox1 = new wxComboBox( sbSizer8->GetStaticBox(), wxID_ANY, wxT("CF4"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_comboBox1->Append( wxT("Ar") );
	m_comboBox1->Append( wxT("He") );
	m_comboBox1->Append( wxT("CO2") );
	m_comboBox1->Append( wxT("CF4") );
	m_comboBox1->Append( wxT("Xe") );
	m_comboBox1->Append( wxT("N2") );
	m_comboBox1->Append( wxT("SF6") );
	m_comboBox1->Append( wxT("Ne") );
	m_comboBox1->Append( wxT("C2F6") );
	m_comboBox1->Append( wxT("C3F8") );
	m_comboBox1->Append( wxT("C4F8") );
	m_comboBox1->SetSelection( 3 );
	bSizer33->Add( m_comboBox1, 0, wxALL, 5 );
	
	m_textCtrl49 = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxT("50"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer33->Add( m_textCtrl49, 0, wxALL, 5 );
	
	
	sbSizer8->Add( bSizer33, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxVERTICAL );
	
	m_comboBox2 = new wxComboBox( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Ne"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_comboBox2->Append( wxT("Ar") );
	m_comboBox2->Append( wxT("He") );
	m_comboBox2->Append( wxT("CO2") );
	m_comboBox2->Append( wxT("CF4") );
	m_comboBox2->Append( wxT("Xe") );
	m_comboBox2->Append( wxT("N2") );
	m_comboBox2->Append( wxT("SF6") );
	m_comboBox2->Append( wxT("Ne") );
	m_comboBox2->Append( wxT("C2F6") );
	m_comboBox2->Append( wxT("C3F8") );
	m_comboBox2->Append( wxT("C4F8") );
	m_comboBox2->SetSelection( 7 );
	bSizer34->Add( m_comboBox2, 0, wxALL, 5 );
	
	m_textCtrl50 = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxT("49"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer34->Add( m_textCtrl50, 0, wxALL, 5 );
	
	
	sbSizer8->Add( bSizer34, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxVERTICAL );
	
	m_comboBox3 = new wxComboBox( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Ar"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_comboBox3->Append( wxT("Ar") );
	m_comboBox3->Append( wxT("He") );
	m_comboBox3->Append( wxT("CO2") );
	m_comboBox3->Append( wxT("CF4") );
	m_comboBox3->Append( wxT("Xe") );
	m_comboBox3->Append( wxT("N2") );
	m_comboBox3->Append( wxT("SF6") );
	m_comboBox3->Append( wxT("Ne") );
	m_comboBox3->Append( wxT("C2F6") );
	m_comboBox3->Append( wxT("C3F8") );
	m_comboBox3->Append( wxT("C4F8") );
	m_comboBox3->SetSelection( 0 );
	bSizer35->Add( m_comboBox3, 0, wxALL, 5 );
	
	m_textCtrl51 = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer35->Add( m_textCtrl51, 0, wxALL, 5 );
	
	
	sbSizer8->Add( bSizer35, 1, wxEXPAND, 5 );
	
	
	sbSizer3->Add( sbSizer8, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText14 = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Gas"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer36->Add( m_staticText14, 0, wxALL, 5 );
	
	m_textCtrl13 = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxT("1Ar-49Ne-50CF4"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer36->Add( m_textCtrl13, 0, wxALL, 5 );
	
	m_staticText51 = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Total Percentage"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	bSizer36->Add( m_staticText51, 0, wxALL, 5 );
	
	m_textCtrl52 = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxT("100"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer36->Add( m_textCtrl52, 0, wxALL, 5 );
	
	
	bSizer3->Add( bSizer36, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText141 = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Pressure (Torr)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText141->Wrap( -1 );
	bSizer37->Add( m_staticText141, 0, wxALL, 5 );
	
	m_textCtrl131 = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxT("740"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer37->Add( m_textCtrl131, 0, wxALL, 5 );
	
	
	bSizer3->Add( bSizer37, 1, wxEXPAND, 5 );
	
	
	sbSizer3->Add( bSizer3, 1, wxEXPAND, 5 );
	
	
	bSizer21->Add( sbSizer3, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("High Voltage") ), wxVERTICAL );
	
	wxBoxSizer* bSizer324;
	bSizer324 = new wxBoxSizer( wxHORIZONTAL );
	
	
	sbSizer2->Add( bSizer324, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer326;
	bSizer326 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText142 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Quench Resistance (MOhm):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText142->Wrap( -1 );
	bSizer326->Add( m_staticText142, 0, wxALL, 5 );
	
	m_textCtrl132 = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxT("1000"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer326->Add( m_textCtrl132, 0, wxALL, 5 );
	
	m_staticText1424 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Number of HV Lines"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1424->Wrap( -1 );
	bSizer326->Add( m_staticText1424, 0, wxALL, 5 );
	
	m_textCtrl1324 = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxT("20"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer326->Add( m_textCtrl1324, 0, wxALL, 5 );
	
	m_staticText1425 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("HV Lines"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1425->Wrap( -1 );
	bSizer326->Add( m_staticText1425, 0, wxALL, 5 );
	
	m_textCtrl1325 = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxT("1-20"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer326->Add( m_textCtrl1325, 0, wxALL, 5 );
	
	
	sbSizer2->Add( bSizer326, 1, wxEXPAND, 5 );
	
	
	bSizer21->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Readout Information") ), wxVERTICAL );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	
	sbSizer4->Add( bSizer1, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer322;
	bSizer322 = new wxBoxSizer( wxHORIZONTAL );
	
	
	sbSizer4->Add( bSizer322, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText25 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Attenuation (dB):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	bSizer20->Add( m_staticText25, 0, wxALL, 5 );
	
	m_textCtrl24 = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxT("20"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_textCtrl24, 0, wxALL, 5 );
	
	discThr = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Discriminator Threshold (mV)"), wxDefaultPosition, wxDefaultSize, 0 );
	discThr->Wrap( -1 );
	bSizer20->Add( discThr, 0, wxALL, 5 );
	
	m_textCtrl48 = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_textCtrl48, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText33 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Numerator Channel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	bSizer25->Add( m_staticText33, 0, wxALL, 5 );
	
	m_textCtrl33 = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_textCtrl33, 0, wxALL, 5 );
	
	
	bSizer20->Add( bSizer25, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText34 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Denominator Channel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	bSizer26->Add( m_staticText34, 0, wxALL, 5 );
	
	m_textCtrl34 = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( m_textCtrl34, 0, wxALL, 5 );
	
	
	bSizer20->Add( bSizer26, 1, wxEXPAND, 5 );
	
	
	sbSizer4->Add( bSizer20, 1, wxEXPAND, 5 );
	
	
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
	
	wxMenuItem* m_menuItem6;
	m_menuItem6 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Save Header File") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem6 );
	
	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Preview Header") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem2 );
	
	m_menubar1->Append( m_menu1, wxT("File") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_staticText11->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setPanelName ), NULL, this );
	m_textCtrl11->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setSource ), NULL, this );
	m_comboBox1->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( header::updateGas ), NULL, this );
	m_textCtrl49->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::updateGas ), NULL, this );
	m_comboBox2->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( header::updateGas ), NULL, this );
	m_comboBox3->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( header::updateGas ), NULL, this );
	m_textCtrl51->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( header::updateGas ), NULL, this );
	m_textCtrl13->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setGas ), NULL, this );
	m_textCtrl131->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setPressure ), NULL, this );
	m_textCtrl132->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setQuench ), NULL, this );
	m_textCtrl1324->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setNumHVLines ), NULL, this );
	m_textCtrl1325->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setHVLines ), NULL, this );
	m_textCtrl24->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setROAtten ), NULL, this );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( header::headerOkClicked ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( header::headerCancelClicked ), NULL, this );
	this->Connect( m_menuItem1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( header::openHeader ) );
	this->Connect( m_menuItem6->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( header::saveHeader ) );
}

header::~header()
{
	// Disconnect Events
	m_staticText11->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setPanelName ), NULL, this );
	m_textCtrl11->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setSource ), NULL, this );
	m_comboBox1->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( header::updateGas ), NULL, this );
	m_textCtrl49->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( header::updateGas ), NULL, this );
	m_comboBox2->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( header::updateGas ), NULL, this );
	m_comboBox3->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( header::updateGas ), NULL, this );
	m_textCtrl51->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( header::updateGas ), NULL, this );
	m_textCtrl13->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setGas ), NULL, this );
	m_textCtrl131->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setPressure ), NULL, this );
	m_textCtrl132->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setQuench ), NULL, this );
	m_textCtrl1324->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setNumHVLines ), NULL, this );
	m_textCtrl1325->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setHVLines ), NULL, this );
	m_textCtrl24->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( header::setROAtten ), NULL, this );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( header::headerOkClicked ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( header::headerCancelClicked ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( header::openHeader ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( header::saveHeader ) );
	
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
	
	wxMenuItem* m_menuItem7;
	m_menuItem7 = new wxMenuItem( edit, wxID_ANY, wxString( wxT("Readout") ) , wxEmptyString, wxITEM_NORMAL );
	edit->Append( m_menuItem7 );
	
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
	
	wxString m_choice2Choices[] = { wxT("1"), wxT("3"), wxT("6") };
	int m_choice2NChoices = sizeof( m_choice2Choices ) / sizeof( wxString );
	m_choice2 = new wxChoice( sbSizer6->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice2NChoices, m_choice2Choices, 0 );
	m_choice2->SetSelection( 1 );
	sbSizer6->Add( m_choice2, 0, wxALL, 5 );
	
	m_button15 = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer6->Add( m_button15, 0, wxALL, 5 );
	
	m_button16 = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Disconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button16->Enable( false );
	
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
	m_button18->Enable( false );
	
	sbSizer10->Add( m_button18, 0, wxALL, 5 );
	
	
	fgSizer3->Add( sbSizer10, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );
	
	wxString m_radioBox4Choices[] = { wxT("H"), wxT("M1"), wxT("M2"), wxT("M3"), wxT("M4") };
	int m_radioBox4NChoices = sizeof( m_radioBox4Choices ) / sizeof( wxString );
	m_radioBox4 = new wxRadioBox( this, wxID_ANY, wxT("Marks"), wxDefaultPosition, wxDefaultSize, m_radioBox4NChoices, m_radioBox4Choices, 1, wxRA_SPECIFY_COLS );
	m_radioBox4->SetSelection( 0 );
	bSizer25->Add( m_radioBox4, 0, wxALL, 5 );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 3, 0, 0 );
	
	homeAll = new wxButton( this, wxID_ANY, wxT("Set Home"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( homeAll, 0, wxALL, 5 );
	
	up = new wxButton( this, wxID_ANY, wxT("Y+"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( up, 0, wxALL, 5 );
	
	m_button5 = new wxButton( this, wxID_ANY, wxT("Mark"), wxDefaultPosition, wxDefaultSize, 0 );
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
	
	
	bSizer25->Add( gSizer1, 1, wxEXPAND, 5 );
	
	
	bSizer19->Add( bSizer25, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	wxString distanceBoxChoices[] = { wxT("0.1"), wxT("1.0"), wxT("5.0"), wxT("10.0"), wxT("User") };
	int distanceBoxNChoices = sizeof( distanceBoxChoices ) / sizeof( wxString );
	distanceBox = new wxRadioBox( this, wxID_ANY, wxT("Travel Distance"), wxDefaultPosition, wxDefaultSize, distanceBoxNChoices, distanceBoxChoices, 4, wxRA_SPECIFY_COLS );
	distanceBox->SetSelection( 3 );
	bSizer21->Add( distanceBox, 0, wxALL, 5 );
	
	m_staticText28 = new wxStaticText( this, wxID_ANY, wxT("User Distance (mm)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	bSizer21->Add( m_staticText28, 0, wxALL, 5 );
	
	m_textCtrl28 = new wxTextCtrl( this, wxID_ANY, wxT("2.54"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer21->Add( m_textCtrl28, 0, wxALL, 5 );
	
	
	bSizer19->Add( bSizer21, 1, wxEXPAND, 5 );
	
	
	fgSizer3->Add( bSizer19, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Scan Type") ), wxVERTICAL );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxHORIZONTAL );
	
	
	sbSizer5->Add( bSizer40, 1, wxEXPAND, 5 );
	
	wxString m_choice1Choices[] = { wxT("Free"), wxT("FreeAP"), wxT("Line Scan"), wxT("Hex Scan X"), wxT("Hex Scan Y"), wxT("X Y Scan") };
	int m_choice1NChoices = sizeof( m_choice1Choices ) / sizeof( wxString );
	m_choice1 = new wxChoice( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	m_choice1->SetToolTip( wxT("Sets the type of scan. \nFree: Control the position of the drive and voltage settings manually.\nVoltage Scan: Do a voltage scan across multiple pixels") );
	
	sbSizer5->Add( m_choice1, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText18 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("X Offset (mm)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer2->Add( m_staticText18, 0, wxALL, 5 );
	
	m_textCtrl18 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("8"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl18, 0, wxALL, 5 );
	
	m_staticText19 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Y Offset (mm)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer2->Add( m_staticText19, 0, wxALL, 5 );
	
	m_textCtrl19 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("8"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl19, 0, wxALL, 5 );
	
	m_staticText32 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Num Pixels"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	m_staticText32->Hide();
	
	fgSizer2->Add( m_staticText32, 0, wxALL, 5 );
	
	m_textCtrl32 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl32->Hide();
	
	fgSizer2->Add( m_textCtrl32, 0, wxALL, 5 );
	
	m_staticText33 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Num Pixels"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	m_staticText33->Hide();
	
	fgSizer2->Add( m_staticText33, 0, wxALL, 5 );
	
	m_textCtrl33 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl33->Hide();
	
	fgSizer2->Add( m_textCtrl33, 0, wxALL, 5 );
	
	m_staticText20 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("X Step Size (mm)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer2->Add( m_staticText20, 0, wxALL, 5 );
	
	m_textCtrl20 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("0.1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl20, 0, wxALL, 5 );
	
	m_staticText21 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Y Step Size (mm)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer2->Add( m_staticText21, 0, wxALL, 5 );
	
	m_textCtrl21 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("0.1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl21, 0, wxALL, 5 );
	
	m_staticText46 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("X (steps/mm)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	fgSizer2->Add( m_staticText46, 0, wxALL, 5 );
	
	m_textCtrl41 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("398"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl41, 0, wxALL, 5 );
	
	m_staticText29 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Y (steps/mm)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizer2->Add( m_staticText29, 0, wxALL, 5 );
	
	m_textCtrl29 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("400"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl29, 0, wxALL, 5 );
	
	m_staticText22 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Start Voltage (V)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALL, 5 );
	
	m_textCtrl22 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("800"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl22->SetToolTip( wxT("The test will start at this voltage") );
	
	fgSizer2->Add( m_textCtrl22, 0, wxALL, 5 );
	
	m_staticText23 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("End Voltage (V)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer2->Add( m_staticText23, 0, wxALL, 5 );
	
	m_textCtrl23 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("1000"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl23->SetToolTip( wxT("The last voltage that will be tested") );
	
	fgSizer2->Add( m_textCtrl23, 0, wxALL, 5 );
	
	m_staticText45 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Voltage Step Size (V)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	fgSizer2->Add( m_staticText45, 0, wxALL, 5 );
	
	m_textCtrl40 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("50"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl40, 0, wxALL, 5 );
	
	m_staticText47 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Measurement Time (s)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47->Wrap( -1 );
	fgSizer2->Add( m_staticText47, 0, wxALL, 5 );
	
	m_textCtrl42 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("120"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl42->SetToolTip( wxT("Dwell time in seconds") );
	
	fgSizer2->Add( m_textCtrl42, 0, wxALL, 5 );
	
	m_staticText48 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Sample Frequency"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	fgSizer2->Add( m_staticText48, 0, wxALL, 5 );
	
	m_textCtrl43 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl43, 0, wxALL, 5 );
	
	wxString m_radioBox3Choices[] = { wxT("On"), wxT("Off") };
	int m_radioBox3NChoices = sizeof( m_radioBox3Choices ) / sizeof( wxString );
	m_radioBox3 = new wxRadioBox( sbSizer5->GetStaticBox(), wxID_ANY, wxT("High Voltage"), wxDefaultPosition, wxDefaultSize, m_radioBox3NChoices, m_radioBox3Choices, 2, wxRA_SPECIFY_COLS );
	m_radioBox3->SetSelection( 1 );
	fgSizer2->Add( m_radioBox3, 0, wxALL, 5 );
	
	m_button20 = new wxButton( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_button20, 0, wxALL, 5 );
	
	m_staticText471 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Number of voltage steps"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText471->Wrap( -1 );
	fgSizer2->Add( m_staticText471, 0, wxALL, 5 );
	
	m_textCtrl45 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer2->Add( m_textCtrl45, 0, wxALL, 5 );
	
	m_staticText481 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Total test time (hr)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText481->Wrap( -1 );
	fgSizer2->Add( m_staticText481, 0, wxALL, 5 );
	
	m_textCtrl46 = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer2->Add( m_textCtrl46, 0, wxALL, 5 );
	
	
	sbSizer5->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	
	fgSizer3->Add( sbSizer5, 1, wxEXPAND, 5 );
	
	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 0, 3, 0, 0 );
	
	start = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( start, 0, wxALL, 5 );
	
	m_button19 = new wxButton( this, wxID_ANY, wxT("Connect NIM"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_button19, 0, wxALL, 5 );
	
	preview = new wxButton( this, wxID_ANY, wxT("Run Preview"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( preview, 0, wxALL, 5 );
	
	stop = new wxButton( this, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( stop, 0, wxALL, 5 );
	
	m_button23 = new wxButton( this, wxID_ANY, wxT("Disconnet NIM"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_button23, 0, wxALL, 5 );
	
	m_button24 = new wxButton( this, wxID_ANY, wxT("Camera"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_button24, 0, wxALL, 5 );
	
	
	fgSizer3->Add( gSizer3, 1, wxEXPAND, 5 );
	
	
	gbSizer4->Add( fgSizer3, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), 0, 5 );
	
	
	this->SetSizer( gbSizer4 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 5, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( menu_quit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::onQuit ) );
	this->Connect( menuHeader->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::openHeaderFrame ) );
	this->Connect( m_menuItem5->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::openPanelFrame ) );
	this->Connect( m_menuItem7->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::openReadoutPane ) );
	m_choice2->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::portSelected ), NULL, this );
	m_button15->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::motorControllerConnectClicked ), NULL, this );
	m_button16->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::motorControllerDisconnectClicked ), NULL, this );
	m_button17->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::HVConnectClicked ), NULL, this );
	m_button18->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::HVDisconnectClicked ), NULL, this );
	homeAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::setHome ), NULL, this );
	up->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::yUpButtonClicked ), NULL, this );
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::markButtonClicked ), NULL, this );
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
	m_textCtrl41->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setNumPixels ), NULL, this );
	m_textCtrl22->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setStartVoltage ), NULL, this );
	m_textCtrl23->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MainFrame::setEndVoltage ), NULL, this );
	m_textCtrl40->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setVoltageStepSize ), NULL, this );
	m_textCtrl42->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setDwellTime ), NULL, this );
	m_radioBox3->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MainFrame::toggleHV ), NULL, this );
	m_button20->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::updateButtonClicked ), NULL, this );
	start->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::startSelected ), NULL, this );
	m_button19->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::connectNIMClicked ), NULL, this );
	preview->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::previewSelected ), NULL, this );
	stop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::stopSelected ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::onQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::openHeaderFrame ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::openPanelFrame ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::openReadoutPane ) );
	m_choice2->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::portSelected ), NULL, this );
	m_button15->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::motorControllerConnectClicked ), NULL, this );
	m_button16->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::motorControllerDisconnectClicked ), NULL, this );
	m_button17->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::HVConnectClicked ), NULL, this );
	m_button18->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::HVDisconnectClicked ), NULL, this );
	homeAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::setHome ), NULL, this );
	up->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::yUpButtonClicked ), NULL, this );
	m_button5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::markButtonClicked ), NULL, this );
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
	m_textCtrl41->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setNumPixels ), NULL, this );
	m_textCtrl22->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setStartVoltage ), NULL, this );
	m_textCtrl23->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MainFrame::setEndVoltage ), NULL, this );
	m_textCtrl40->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setVoltageStepSize ), NULL, this );
	m_textCtrl42->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::setDwellTime ), NULL, this );
	m_radioBox3->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MainFrame::toggleHV ), NULL, this );
	m_button20->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::updateButtonClicked ), NULL, this );
	start->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::startSelected ), NULL, this );
	m_button19->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::connectNIMClicked ), NULL, this );
	preview->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::previewSelected ), NULL, this );
	stop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::stopSelected ), NULL, this );
	
}

UserEnd::UserEnd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText50 = new wxStaticText( this, wxID_ANY, wxT("Click button to end run"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText50->Wrap( -1 );
	bSizer38->Add( m_staticText50, 0, wxALL, 5 );
	
	m_button21 = new wxButton( this, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer38->Add( m_button21, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer38 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_button21->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UserEnd::StopClicked ), NULL, this );
}

UserEnd::~UserEnd()
{
	// Disconnect Events
	m_button21->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UserEnd::StopClicked ), NULL, this );
	
}

MyFrame4::MyFrame4( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBox77 = new wxCheckBox( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox77->SetValue(true); 
	bSizer41->Add( m_checkBox77, 0, wxALL, 5 );
	
	m_checkBox78 = new wxCheckBox( this, wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox78->SetValue(true); 
	bSizer41->Add( m_checkBox78, 0, wxALL, 5 );
	
	m_checkBox79 = new wxCheckBox( this, wxID_ANY, wxT("3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox79->SetValue(true); 
	bSizer41->Add( m_checkBox79, 0, wxALL, 5 );
	
	m_checkBox80 = new wxCheckBox( this, wxID_ANY, wxT("4"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox80->SetValue(true); 
	bSizer41->Add( m_checkBox80, 0, wxALL, 5 );
	
	m_checkBox81 = new wxCheckBox( this, wxID_ANY, wxT("5"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox81->SetValue(true); 
	bSizer41->Add( m_checkBox81, 0, wxALL, 5 );
	
	m_checkBox82 = new wxCheckBox( this, wxID_ANY, wxT("6"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox82->SetValue(true); 
	bSizer41->Add( m_checkBox82, 0, wxALL, 5 );
	
	m_checkBox83 = new wxCheckBox( this, wxID_ANY, wxT("7"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox83->SetValue(true); 
	bSizer41->Add( m_checkBox83, 0, wxALL, 5 );
	
	m_checkBox84 = new wxCheckBox( this, wxID_ANY, wxT("8"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox84->SetValue(true); 
	bSizer41->Add( m_checkBox84, 0, wxALL, 5 );
	
	m_checkBox85 = new wxCheckBox( this, wxID_ANY, wxT("9"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox85->SetValue(true); 
	bSizer41->Add( m_checkBox85, 0, wxALL, 5 );
	
	m_checkBox86 = new wxCheckBox( this, wxID_ANY, wxT("10"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox86->SetValue(true); 
	bSizer41->Add( m_checkBox86, 0, wxALL, 5 );
	
	
	bSizer40->Add( bSizer41, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer411;
	bSizer411 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBox771 = new wxCheckBox( this, wxID_ANY, wxT("11"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox771->SetValue(true); 
	bSizer411->Add( m_checkBox771, 0, wxALL, 5 );
	
	m_checkBox781 = new wxCheckBox( this, wxID_ANY, wxT("12"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox781->SetValue(true); 
	bSizer411->Add( m_checkBox781, 0, wxALL, 5 );
	
	m_checkBox791 = new wxCheckBox( this, wxID_ANY, wxT("13"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox791->SetValue(true); 
	bSizer411->Add( m_checkBox791, 0, wxALL, 5 );
	
	m_checkBox801 = new wxCheckBox( this, wxID_ANY, wxT("14"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox801->SetValue(true); 
	bSizer411->Add( m_checkBox801, 0, wxALL, 5 );
	
	m_checkBox811 = new wxCheckBox( this, wxID_ANY, wxT("15"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox811->SetValue(true); 
	bSizer411->Add( m_checkBox811, 0, wxALL, 5 );
	
	m_checkBox821 = new wxCheckBox( this, wxID_ANY, wxT("16"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox821->SetValue(true); 
	bSizer411->Add( m_checkBox821, 0, wxALL, 5 );
	
	m_checkBox831 = new wxCheckBox( this, wxID_ANY, wxT("17"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox831->SetValue(true); 
	bSizer411->Add( m_checkBox831, 0, wxALL, 5 );
	
	m_checkBox841 = new wxCheckBox( this, wxID_ANY, wxT("18"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox841->SetValue(true); 
	bSizer411->Add( m_checkBox841, 0, wxALL, 5 );
	
	m_checkBox851 = new wxCheckBox( this, wxID_ANY, wxT("19"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox851->SetValue(true); 
	bSizer411->Add( m_checkBox851, 0, wxALL, 5 );
	
	m_checkBox861 = new wxCheckBox( this, wxID_ANY, wxT("20"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox861->SetValue(true); 
	bSizer411->Add( m_checkBox861, 0, wxALL, 5 );
	
	
	bSizer40->Add( bSizer411, 1, wxEXPAND, 5 );
	
	m_button22 = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( m_button22, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer40 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_button22->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::okbuttonclicked ), NULL, this );
}

MyFrame4::~MyFrame4()
{
	// Disconnect Events
	m_button22->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame4::okbuttonclicked ), NULL, this );
	
}

ImageFrame::ImageFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	
	this->Centre( wxBOTH );
}

ImageFrame::~ImageFrame()
{
}
