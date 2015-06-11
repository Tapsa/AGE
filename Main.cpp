#include "Main.h"

IMPLEMENT_APP(AGE)

bool AGE::OnInit()
{
	argPath = (wxApp::argc > 1) ? wxApp::argv[1] : "";
	{
		wxBusyCursor Wait;
		windows.resize(1);
		windows[0] = new AGE_Frame("Advanced Genie Editor " + AGE_AboutDialog::AGE_VER, argPath, copies, 0);
		FixSize(windows[0]);
		SetTopWindow(windows[0]);
	}
//	windows[0]->Refresh(); // Will be refreshed anyway.
//	windows[0]->Update(); // Immediate refresh.
	wxCommandEvent OpenFiles(wxEVT_COMMAND_MENU_SELECTED, windows[0]->ToolBar_Open);
	windows[0]->GetEventHandler()->ProcessEvent(OpenFiles);

	if(windows[0]->SimultaneousFiles > 1)
	{
		windows.resize(windows[0]->SimultaneousFiles);
		for(short loop=1; loop < windows[0]->SimultaneousFiles; ++loop)
		{
			{
				wxBusyCursor Wait;
				windows[loop] = new AGE_Frame("AGE " + AGE_AboutDialog::AGE_VER + " window "+lexical_cast<string>(loop+1), argPath, copies, loop);
				FixSize(windows[loop]);
			}
			wxCommandEvent OpenFiles2(wxEVT_COMMAND_MENU_SELECTED, windows[loop]->ToolBar_Open);
			windows[loop]->GetEventHandler()->ProcessEvent(OpenFiles2);
		}
	}
	return true;
}

// Fancy scaling :)
void AGE::FixSize(AGE_Frame *window)
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
