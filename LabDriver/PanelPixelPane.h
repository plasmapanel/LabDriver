#pragma once

#include <wx/panel.h>

class PanelPixelPane :
	public wxPanel
{
public:
	PanelPixelPane();
	~PanelPixelPane();
	void BasicDrawPane(wxFrame* parent);

	void paintEvent(wxPaintEvent & evt);
	void paintNow();

	void render(wxDC& dc);
};

