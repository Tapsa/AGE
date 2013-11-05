#include "Main.h"
using boost::lexical_cast;

IMPLEMENT_APP(AGE)

bool AGE::OnInit()
{
	{
		wxBusyCursor Wait;
		windows.resize(1);
		windows[0] = new AGE_Frame("Advanced Genie Editor", copies, true);
		windows[0]->SetSize(900, 720);
		windows[0]->Show(true);
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
				windows[loop] = new AGE_Frame("AGE window "+lexical_cast<string>(loop+1), copies, (loop+1));
				windows[loop]->SetSize(900, 720);
				windows[loop]->Show(true);
			}
			wxCommandEvent OpenFiles2(wxEVT_COMMAND_MENU_SELECTED, windows[loop]->ToolBar_Open);
			windows[loop]->GetEventHandler()->ProcessEvent(OpenFiles2);
		}
	}
	return true;
}
