#pragma once
#include "OpenSaveDialog.h"

class SaveDialog : public OpenSaveDialog
{
public:
    SaveDialog(wxWindow *parent, const wxFont &font);

    void OnDefaultAoKHD(wxCommandEvent &event);
    void OnDefaultAoP(wxCommandEvent &event);
    void OnDefaultDE2(wxCommandEvent &event);

    wxCheckBox *SyncWithReadPaths;
};
