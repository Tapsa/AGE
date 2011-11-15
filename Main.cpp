/* Main.cpp */

#include "Main.h"
#include "wx/busyinfo.h"

IMPLEMENT_APP(AGE)

bool AGE::OnInit()
{
//	wxBusyInfo Working("Initializing...");
	wxBusyCursor Wait;
	MainWindow = new AGE_Frame("Advanced Genie Editor");
	MainWindow->SetSize(900, 700);
	MainWindow->Show(true);
	SetTopWindow(MainWindow);
//	MainWindow->Refresh();
	MainWindow->Update();
	wxCommandEvent OpenFiles(wxEVT_COMMAND_MENU_SELECTED, MainWindow->ToolBar_Open);
	MainWindow->ProcessEvent(OpenFiles);
	return true;
}
