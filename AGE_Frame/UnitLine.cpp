#include "Common.h"
#include "../AGE_Frame.h"

wxString AGE_Frame::GetUnitLineName(int index)
{
    if(!dataset->UnitLines[index].Name.empty())
        return dataset->UnitLines[index].Name;
    return "Unitline "+lexical_cast<std::string>(index);
}

void AGE_Frame::OnUnitLinesSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListUnitLines();
}

void AGE_Frame::ListUnitLines()
{
    InitUnitLines();
    wxCommandEvent e;
    OnUnitLineSelect(e);
}

void AGE_Frame::InitUnitLines()
{
    InitSearch(UnitLines_UnitLines_Search->GetValue().MakeLower(), UnitLines_UnitLines_Search_R->GetValue().MakeLower());

    UnitLines_UnitLines_ListV->Sweep();
    unitline_names.Clear();
    unitline_names.Alloc(1 + dataset->UnitLines.size());
    unitline_names.Add("-1 - None");

    for(size_t loop = 0; loop < dataset->UnitLines.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetUnitLineName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            UnitLines_UnitLines_ListV->names.Add(Name);
            UnitLines_UnitLines_ListV->indexes.push_back(loop);
        }
        unitline_names.Add(Name);
    }

    RefreshList(UnitLines_UnitLines_ListV, &UnitLineIDs);
    Units_Unitline_ComboBox->Flash();
}

void AGE_Frame::OnUnitLineSelect(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLines_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, UnitLines_UnitLines_ListV, UnitLineIDs);

    UnitLines_ID->clear();
    UnitLines_Name->clear();

    genie::UnitLine * LinePointer;
    for(size_t loop = selections; loop--> 0;)
    {
        LinePointer = &dataset->UnitLines[UnitLineIDs[loop]];

        UnitLines_ID->prepend(&LinePointer->ID);
        UnitLines_Name->prepend(&LinePointer->Name);
    }
    SetStatusText(wxString::Format("Selections: %zu    Selected unit line: %d",
        selections, selections > 0 ? UnitLineIDs.front() : -1), 0);

    UnitLines_ID->refill();
    UnitLines_Name->update();
    ListUnitLineUnits();
}

void AGE_Frame::OnUnitLinesAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    AddToListIDFix(dataset->UnitLines);
    ListUnitLines();
}

void AGE_Frame::OnUnitLinesInsert(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLines_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToListIDFix(dataset->UnitLines, UnitLineIDs.front());
    ListUnitLines();
}

void AGE_Frame::OnUnitLinesDelete(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLines_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromListIDFix(dataset->UnitLines, UnitLineIDs);
    ListUnitLines();
}

void AGE_Frame::OnUnitLinesCopy(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLines_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->UnitLines, UnitLineIDs, copies.UnitLine);
    UnitLines_UnitLines_ListV->SetFocus();
}

void AGE_Frame::OnUnitLinesPaste(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLines_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToListIDFix(dataset->UnitLines, UnitLineIDs, copies.UnitLine);
    ListUnitLines();
}

void AGE_Frame::OnUnitLinesPasteInsert(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLines_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListIDFix(dataset->UnitLines, UnitLineIDs.front(), copies.UnitLine);
    ListUnitLines();
}

wxString AGE_Frame::GetUnitLineUnitName(int Unit)
{
    wxString name = FormatInt(Unit) + " ";
    if (dataset->Civs.front().Units.size() <= Unit)
    {
        return name + "Nonexistent Unit";
    }
    wxString DynamicName = TranslatedText(dataset->Civs.front().Units[Unit].LanguageDLLName, 64);
    if (!DynamicName.empty())
    {
        return name + DynamicName;
    }
    if (!dataset->Civs.front().Units[Unit].Name.empty())
    {
        return name + dataset->Civs.front().Units[Unit].Name;
    }
    return name + "New Unit";
}

void AGE_Frame::OnUnitLineUnitsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListUnitLineUnits();
}

void AGE_Frame::ListUnitLineUnits()
{
    InitSearch(UnitLines_UnitLineUnits_Search->GetValue().MakeLower(), UnitLines_UnitLineUnits_Search_R->GetValue().MakeLower());

    UnitLines_UnitLineUnits_ListV->Sweep();

    if (UnitLineIDs.size())
    for(size_t loop = 0; loop < dataset->UnitLines[UnitLineIDs.front()].UnitIDs.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetUnitLineUnitName(dataset->UnitLines[UnitLineIDs.front()].UnitIDs[loop]);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            UnitLines_UnitLineUnits_ListV->names.Add(Name);
            UnitLines_UnitLineUnits_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(UnitLines_UnitLineUnits_ListV, &UnitLineUnitIDs);

    wxCommandEvent e;
    OnUnitLineUnitSelect(e);
}

void AGE_Frame::OnUnitLineUnitSelect(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLineUnits_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    UnitLineUnits_Units->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, UnitLines_UnitLineUnits_ListV, UnitLineUnitIDs);

        int16_t * UnitPointer;
        for(size_t loop = selections; loop--> 0;)
        {
            UnitPointer = &dataset->UnitLines[UnitLineIDs.front()].UnitIDs[UnitLineUnitIDs[loop]];
            UnitLineUnits_Units->prepend(UnitPointer);
        }
    }
    UnitLineUnits_Units->update();
}

void AGE_Frame::OnUnitLineUnitsAdd(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLines_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    AddToListNoGV(dataset->UnitLines[UnitLineIDs.front()].UnitIDs);
    ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsInsert(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLineUnits_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToListNoGV(dataset->UnitLines[UnitLineIDs.front()].UnitIDs, UnitLineUnitIDs.front());
    ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsDelete(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLineUnits_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->UnitLines[UnitLineIDs.front()].UnitIDs, UnitLineUnitIDs);
    ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsCopy(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLineUnits_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->UnitLines[UnitLineIDs.front()].UnitIDs, UnitLineUnitIDs, copies.UnitLineUnit);
    UnitLines_UnitLineUnits_ListV->SetFocus();
}

void AGE_Frame::OnUnitLineUnitsPaste(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLineUnits_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->UnitLines[UnitLineIDs.front()].UnitIDs, UnitLineUnitIDs, copies.UnitLineUnit);
    ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsPasteInsert(wxCommandEvent &event)
{
    size_t selections = UnitLines_UnitLineUnits_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->UnitLines[UnitLineIDs.front()].UnitIDs, UnitLineUnitIDs.front(), copies.UnitLineUnit);
    ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsCopyToUnitLines(wxCommandEvent &event)
{
    for(size_t loop=1; loop < UnitLineIDs.size(); ++loop)
    {
        dataset->UnitLines[UnitLineIDs[loop]].UnitIDs = dataset->UnitLines[UnitLineIDs.front()].UnitIDs;
    }
}

void AGE_Frame::CreateUnitLineControls()
{
    Tab_UnitLine = new ATabPage(TabBar_Main);
    UnitLines_Main = new wxBoxSizer(wxHORIZONTAL);
    UnitLines_UnitLines_Buttons = new wxGridSizer(3, 0, 0);
    UnitLines_UnitLineUnits_Buttons = new wxGridSizer(3, 0, 0);
    UnitLines_DataArea = new wxBoxSizer(wxVERTICAL);

    UnitLines_UnitLines = new wxStaticBoxSizer(wxVERTICAL, Tab_UnitLine, "Unitlines (Used by AIs)");
    UnitLines_UnitLines_Search = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
    UnitLines_UnitLines_Search_R = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
    UnitLines_UnitLines_ListV = new ProperList(Tab_UnitLine, ASize(200, 100));
    UnitLines_Add = new wxButton(Tab_UnitLine, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    UnitLines_Insert = new wxButton(Tab_UnitLine, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    UnitLines_Delete = new wxButton(Tab_UnitLine, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    UnitLines_Copy = new wxButton(Tab_UnitLine, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    UnitLines_Paste = new wxButton(Tab_UnitLine, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    UnitLines_PasteInsert = new wxButton(Tab_UnitLine, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));

    UnitLines_UnitLineUnits = new wxStaticBoxSizer(wxVERTICAL, Tab_UnitLine, "Units");
    UnitLines_UnitLineUnits_Search = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
    UnitLines_UnitLineUnits_Search_R = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
    UnitLines_UnitLineUnits_ListV = new ProperList(Tab_UnitLine, ASize(200, 100));
    UnitLineUnits_Add = new wxButton(Tab_UnitLine, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    UnitLineUnits_Insert = new wxButton(Tab_UnitLine, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    UnitLineUnits_Delete = new wxButton(Tab_UnitLine, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    UnitLineUnits_Copy = new wxButton(Tab_UnitLine, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    UnitLineUnits_Paste = new wxButton(Tab_UnitLine, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    UnitLineUnits_PasteInsert = new wxButton(Tab_UnitLine, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    UnitLineUnits_CopyToUnitLines = new wxButton(Tab_UnitLine, wxID_ANY, "Copy all to selected unitlines", wxDefaultPosition, wxSize(10, -1));

    UnitLines_ID_Holder = new wxBoxSizer(wxVERTICAL);
    UnitLines_ID_Text = new SolidText(Tab_UnitLine, " Unitline ID");
    UnitLines_ID = new NumberControl(CShort, Tab_UnitLine, this, nullptr);
    UnitLines_Name_Holder = new wxBoxSizer(wxVERTICAL);
    UnitLines_Name_Text = new SolidText(Tab_UnitLine, " Unitline Name");
    UnitLines_Name = new StringControl(Tab_UnitLine, this, nullptr, maxStringlength, false);

    UnitLineUnits_Holder = new wxBoxSizer(wxVERTICAL);
    UnitLineUnits_Text = new SolidText(Tab_UnitLine, " Unit");
    UnitLineUnits_Units = new NumberControl(CShort, Tab_UnitLine, this, nullptr, false);
    UnitLineUnits_ComboBox = new LinkedComboBox(Tab_UnitLine, UnitLineUnits_Units, &unit_names, false);
    UnitComboBoxList.push_back(UnitLineUnits_ComboBox);

    UnitLines_UnitLines_Buttons->Add(UnitLines_Add, 1, wxEXPAND);
    UnitLines_UnitLines_Buttons->Add(UnitLines_Delete, 1, wxEXPAND);
    UnitLines_UnitLines_Buttons->Add(UnitLines_Insert, 1, wxEXPAND);
    UnitLines_UnitLines_Buttons->Add(UnitLines_Copy, 1, wxEXPAND);
    UnitLines_UnitLines_Buttons->Add(UnitLines_Paste, 1, wxEXPAND);
    UnitLines_UnitLines_Buttons->Add(UnitLines_PasteInsert, 1, wxEXPAND);

    UnitLines_UnitLines->Add(UnitLines_UnitLines_Search, 0, wxEXPAND);
    UnitLines_UnitLines->Add(UnitLines_UnitLines_Search_R, 0, wxEXPAND);
    UnitLines_UnitLines->Add(UnitLines_UnitLines_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    UnitLines_UnitLines->Add(UnitLines_UnitLines_Buttons, 0, wxEXPAND);

    UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Add, 1, wxEXPAND);
    UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Delete, 1, wxEXPAND);
    UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Insert, 1, wxEXPAND);
    UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Copy, 1, wxEXPAND);
    UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Paste, 1, wxEXPAND);
    UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_PasteInsert, 1, wxEXPAND);

    UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Search, 0, wxEXPAND);
    UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Search_R, 0, wxEXPAND);
    UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Buttons, 0, wxEXPAND);
    UnitLines_UnitLineUnits->Add(UnitLineUnits_CopyToUnitLines, 0, wxEXPAND | wxTOP, 2);

    UnitLines_ID_Holder->Add(UnitLines_ID_Text);
    UnitLines_ID_Holder->Add(UnitLines_ID);
    UnitLines_Name_Holder->Add(UnitLines_Name_Text);
    UnitLines_Name_Holder->Add(UnitLines_Name);
    UnitLineUnits_Holder->Add(UnitLineUnits_Text);
    UnitLineUnits_Holder->Add(UnitLineUnits_Units, 0, wxEXPAND);
    UnitLineUnits_Holder->Add(UnitLineUnits_ComboBox);

    UnitLines_DataArea->Add(UnitLines_ID_Holder, 0, wxTOP, 5);
    UnitLines_DataArea->Add(UnitLines_Name_Holder, 0, wxTOP, 5);
    UnitLines_DataArea->Add(UnitLineUnits_Holder, 0, wxTOP, 5);

    UnitLines_Main->Add(UnitLines_UnitLines, 1, wxEXPAND | wxALL, 5);
    UnitLines_Main->Add(UnitLines_UnitLineUnits, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);
    UnitLines_Main->Add(UnitLines_DataArea);
    UnitLines_Main->AddStretchSpacer(1);

    UnitLines_ID->Enable(false);

    Tab_UnitLine->SetSizer(UnitLines_Main);

    UnitLines_UnitLines_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnUnitLineSelect, this);
    UnitLines_UnitLines_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitLinesSearch, this);
    UnitLines_UnitLines_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitLinesSearch, this);
    UnitLines_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLinesAdd, this);
    UnitLines_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLinesInsert, this);
    UnitLines_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLinesDelete, this);
    UnitLines_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLinesCopy, this);
    UnitLines_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLinesPaste, this);
    UnitLines_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLinesPasteInsert, this);
    UnitLines_UnitLineUnits_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnUnitLineUnitSelect, this);
    UnitLines_UnitLineUnits_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitLineUnitsSearch, this);
    UnitLines_UnitLineUnits_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitLineUnitsSearch, this);
    UnitLineUnits_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLineUnitsAdd, this);
    UnitLineUnits_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLineUnitsInsert, this);
    UnitLineUnits_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLineUnitsDelete, this);
    UnitLineUnits_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLineUnitsCopy, this);
    UnitLineUnits_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLineUnitsPaste, this);
    UnitLineUnits_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLineUnitsPasteInsert, this);
    UnitLineUnits_CopyToUnitLines->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitLineUnitsCopyToUnitLines, this);

    UnitLines_Name->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListUnitLines();
        }
    });
    UnitLines_Name->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListUnitLines();
    });
    UnitLineUnits_Units->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListUnitLineUnits();
        }
    });
    UnitLineUnits_Units->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListUnitLineUnits();
    });
    UnitLineUnits_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_UnitLines, this);
}

void AGE_Frame::OnUpdateCombo_UnitLines(wxCommandEvent &event)
{
    static_cast<LinkedComboBox*>(event.GetEventObject())->OnChoose(event);
    ListUnitLineUnits();
}
