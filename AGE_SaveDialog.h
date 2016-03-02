#pragma once
#include "AGE_OpenSave.h"

class AGE_SaveDialog: public AGE_OpenSave
{
public:
    AGE_SaveDialog(wxWindow *parent, const wxFont &font);

    void OnDefaultAoKHD(wxCommandEvent &event);
    void OnDefaultAoP(wxCommandEvent &event);

    wxCheckBox *SyncWithReadPaths;
};
