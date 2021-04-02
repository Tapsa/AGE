#include "Common.h"
#include "BaseMainFrame.h"
#include "Main.h"

IMPLEMENT_APP(AGE)

BaseMainFrame *BaseMainFrame::openEditors[4]{0};
Copies BaseMainFrame::copies;

bool AGE::OnInit()
{
    SetVendorName("Tapsa");
    SetAppName("AdvancedGenieEditor3");
    SetAppDisplayName("Advanced Genie Editor");
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxTGAHandler);

    wxToolTip::SetDelay(200);
    wxToolTip::SetAutoPop(32700);
    wxToolTip::SetReshow(1);

    wxString cmd1 = (wxApp::argc > 1) ? wxApp::argv[1] : "";
    BaseMainFrame *window = BaseMainFrame::Create(cmd1);
    SetTopWindow(window);
    wxCommandEvent open;
    window->OnOpen(open);

    return true;
}
