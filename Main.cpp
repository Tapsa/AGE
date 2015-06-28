#include "Main.h"

IMPLEMENT_APP(AGE)

vector<bool> AGE_Frame::openEditors;
Copies AGE_Frame::copies;

bool AGE::OnInit()
{
	AGE_Frame* window;
	wxString argPath = (wxApp::argc > 1) ? wxApp::argv[1] : "";
	{
		wxBusyCursor Wait;
		window = new AGE_Frame("Advanced Genie Editor " + AGE_AboutDialog::AGE_VER, 0, argPath);
		AGE_Frame::FixSize(window);
		SetTopWindow(window);
	}
	wxCommandEvent OpenFiles(wxEVT_COMMAND_MENU_SELECTED, window->ToolBar_Open);
	window->GetEventHandler()->ProcessEvent(OpenFiles);

	return true;
}

// Fancy scaling :)
void AGE_Frame::FixSize(AGE_Frame *window)
{
	int ScrollerWidth = window->Units_ScrollArea->GetMinSize().GetWidth();
	if(ScrollerWidth > 630)
	{
		int NewWidth = 270.0 * (ScrollerWidth / 630.0) + ScrollerWidth;
		window->MinWindowWidth = NewWidth;
		window->SetSize(NewWidth, 720);
	}
	else
	{
		window->MinWindowWidth = 900;
		window->SetSize(900, 720);
	}
	window->Show(true);
	window->FixSizes();
}
