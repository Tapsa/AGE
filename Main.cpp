#include "Main.h"

IMPLEMENT_APP(AGE)

bool AGE::OnInit()
{
	{
		wxBusyCursor Wait;
		windows.resize(2);
		windows[0] = new AGE_Frame("Advanced Genie Editor", copies);
		windows[0]->SetSize(900, 720);
		windows[0]->Show(true);
		windows[1] = new AGE_Frame("Advanced Genie Editor", copies);
		windows[1]->SetSize(900, 720);
		windows[1]->Show(true);
		SetTopWindow(windows[0]);
	}
//	windows[0]->Refresh(); // Will be refreshed anyway.
//	windows[0]->Update(); // Immediate refresh.
	wxCommandEvent OpenFiles(wxEVT_COMMAND_MENU_SELECTED, windows[0]->ToolBar_Open);
	windows[0]->GetEventHandler()->ProcessEvent(OpenFiles);
	return true;
}
