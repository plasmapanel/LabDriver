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
#include <wx/windowid.h>

#include <wx/panel.h>
//#include <wx/stattext.h>

class Panel: public wxFrame
{
public:
	Panel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Panel Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(453, 771), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
		~Panel();
private:

};