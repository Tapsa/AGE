#pragma once
#include "OpenSaveDialog.h"

class SaveDialog : public OpenSaveDialog
{
public:
    SaveDialog(wxWindow *parent, const wxFont &font);

    void OnDefaultDE1(wxCommandEvent &event) override;
    void OnDefaultAoKHD(wxCommandEvent &event) override;
    void OnDefaultAoP(wxCommandEvent &event) override;
    void OnDefaultDE2(wxCommandEvent &event) override;

    wxCheckBox *SyncWithReadPaths;
};
