#include "Main.h"

IMPLEMENT_APP(AGE)

wxWindow* AGE_Frame::openEditors[4]{0};
Copies AGE_Frame::copies;

bool AGE::OnInit()
{
	AGE_Frame* window;
    wxImage::AddHandler(new wxPNGHandler);
	wxString argPath = (wxApp::argc > 1) ? wxApp::argv[1] : "";
	{
		wxBusyCursor Wait;
		window = new AGE_Frame("Advanced Genie Editor " + AGE_AboutDialog::AGE_VER, 0, argPath);
		AGE_Frame::FixSize(window);
		SetTopWindow(window);
	}
	wxCommandEvent OpenFiles(wxEVT_COMMAND_MENU_SELECTED, window->eOpen);
	window->GetEventHandler()->ProcessEvent(OpenFiles);

	return true;
}

// Fancy scaling :)
void AGE_Frame::FixSize(AGE_Frame *window)
{
	int ScrollerWidth = window->Units_ScrollSpace->GetMinSize().GetWidth();
	if(ScrollerWidth > 630)
	{
		int NewWidth = 270.0f * (ScrollerWidth / 630.0f) + ScrollerWidth;
		window->MinWindowWidth = NewWidth;
		window->SetSize(NewWidth, 870);
	}
	else
	{
		window->MinWindowWidth = 900;
		window->SetSize(900, 870);
	}
	window->Show(true);
	window->FixSizes();
}
