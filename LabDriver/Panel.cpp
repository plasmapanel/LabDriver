#include "Panel.h"


Panel::Panel(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	wxPanel* pixels;
	pixels = new wxPanel();

	
	wxBoxSizer* sizer1;
	sizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* sizer2;
	sizer2 = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* text1;
	text1 = new wxStaticText(this, wxID_ANY, wxT("Number of HV lines"), wxDefaultPosition, wxDefaultSize, 0);

	wxTextCtrl* control1;
	control1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);

	wxStaticText* text2;
	text2 = new wxStaticText(this, wxID_ANY, wxT("Number of RO lines"), wxDefaultPosition, wxDefaultSize, 0);

	wxTextCtrl* control2;
	control2 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);

	sizer2->Add(text1);
	sizer2->Add(control1);
	sizer2->Add(text2);
	sizer2->Add(control2);

	sizer1->Add(pixels);
	sizer1->Add(sizer2);

	
	this->SetSizer(sizer1);
	this->Layout();

}

Panel::~Panel()
{

}