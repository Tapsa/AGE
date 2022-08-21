#include "Common.h"
#include "../AGE_Frame.h"

void AGE_Frame::OnCivsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListCivs(false);
}

wxString AGE_Frame::GetCivName(int index)
{
    return (GenieVersion < genie::GV_SWGB ? dataset->Civs[index].Name : dataset->Civs[index].Name2) + " (" + lexical_cast<std::string>((short)dataset->Civs[index].IconSet) + ")";
}

void AGE_Frame::ListCivs(bool all)
{
    InitCivs(all);
    wxCommandEvent e;
    OnCivSelect(e);
}

void AGE_Frame::InitCivs(bool all)
{
    InitSearch(Civs_Civs_Search->GetValue().MakeLower(), Civs_Civs_Search_R->GetValue().MakeLower());

    Civs_Civs_ListV->Sweep();
    if(all)
    {
        civ_names.Clear();
        civ_names_only.Clear();
        civ_names.Alloc(1 + dataset->Civs.size());
        civ_names_only.Alloc(dataset->Civs.size());
        civ_names.Add("-1 - Any");
    }

    for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetCivName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Civs_Civs_ListV->names.Add(Name);
            Civs_Civs_ListV->indexes.push_back(loop);
        }
        if(all)
        {
            civ_names.Add(Name);
            civ_names_only.Add(Name);
        }
    }

    RefreshList(Civs_Civs_ListV, &CivIDs);
    if (all)
    {
        for (AGEComboBox *list : CivComboBoxList)
        {
            list->Flash();
        }
    }
}

void AGE_Frame::OnCivSelect(wxCommandEvent &event)
{
    size_t selections = Civs_Civs_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Civs_Civs_ListV, CivIDs);

    for (AGETextCtrl *box : uiGroupCiv) box->clear();

    genie::Civ * CivPointer;
    for(size_t sel = selections; sel--> 0;)
    {
        CivPointer = &dataset->Civs[CivIDs[sel]];

        Civs_One->prepend(&CivPointer->PlayerType);
        Civs_Name[0]->prepend(&CivPointer->Name);
        if(GenieVersion >= genie::GV_MIK)
        {
            Civs_TechTree->prepend(&CivPointer->TechTreeID);
            if(GenieVersion >= genie::GV_AoKB)
            {
                Civs_TeamBonus->prepend(&CivPointer->TeamBonusID);
                if(GenieVersion >= genie::GV_SWGB)
                {
                    Civs_Name[1]->prepend(&CivPointer->Name2);
                    for(size_t loop = 0; loop < 4; ++loop)
                    Civs_SUnknown1[loop]->prepend(&CivPointer->UniqueUnitsTechs[loop]);
                }
            }
        }
        Civs_GraphicSet->prepend(&CivPointer->IconSet);
    }
    SetStatusText(wxString::Format("Selections: %zu    Selected civilization: %d",
        selections, selections > 0 ? CivIDs.front() : -1), 0);

    for (AGETextCtrl *box : uiGroupCiv) box->update();
    ListResources();
}

void AGE_Frame::OnCivsAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    genie::Civ Temp;
    Temp.setGameVersion(GenieVersion);
    if(dataset->Civs.size() > 0)
    {
        short FillingCiv = (dataset->Civs.size() > 1) ? 1 : 0;
        Temp.Resources = dataset->Civs[FillingCiv].Resources;
        Temp.UnitPointers = dataset->Civs[FillingCiv].UnitPointers;
        Temp.Units = dataset->Civs[FillingCiv].Units;
    }
    dataset->Civs.push_back(Temp);
    How2List = ListMode::ADD;
    OnCivCountChange();
    ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivsInsert(wxCommandEvent &event)
{
    size_t selections = Civs_Civs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    genie::Civ Temp;
    Temp.setGameVersion(GenieVersion);
    if(dataset->Civs.size() > 0)
    {
        short FillingCiv = (dataset->Civs.size() > 1) ? 1 : 0;
        Temp.Resources = dataset->Civs[FillingCiv].Resources;
        Temp.UnitPointers = dataset->Civs[FillingCiv].UnitPointers;
        Temp.Units = dataset->Civs[FillingCiv].Units;
    }
    dataset->Civs.insert(dataset->Civs.begin() + CivIDs.front(), Temp);
    OnCivCountChange();
    How2List = ListMode::INSNEW;
    ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivsDelete(wxCommandEvent &event)
{
    size_t selections = Civs_Civs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->Civs, CivIDs);
    OnCivCountChange();
    ListUnits(0, false);
}

void AGE_Frame::OnCivsCopy(wxCommandEvent &event)
{
    size_t selections = Civs_Civs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Civs, CivIDs, copies.Civ);
    Civs_Civs_ListV->SetFocus();
}

void AGE_Frame::OnCivsPaste(wxCommandEvent &event)
{
    size_t selections = Civs_Civs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Civs, CivIDs, copies.Civ);
    OnCivCountChange();
    ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivsPasteInsert(wxCommandEvent &event)
{
    size_t selections = Civs_Civs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->Civs, CivIDs.front(), copies.Civ);
    OnCivCountChange();
    ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivCountChange()
{
    size_t CivCount = dataset->Civs.size();
//  Unit copying fixes.
//  This messes copying if more than one window is opened!
//  copies.Dat.Civs.resize(CivCount);

    if(Units_CivBoxes.size() < CivCount)
    {
        Units_CivBoxes.reserve(CivCount);
        for(size_t loop = Units_CivBoxes.size(); loop < CivCount; ++loop)
        {
            Units_CivBoxes.push_back(new wxCheckBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(36, -1)));
            Units_CivBoxes[loop]->SetValue(true);
            Units_TopGrid_Holder->Add(Units_CivBoxes[loop], 0, wxRIGHT, 1);
            Units_CivBoxes[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnAutoCopy, this);
        }
    }
    else if(Units_CivBoxes.size() > CivCount)
    {
        for(size_t loop = Units_CivBoxes.size(); loop--> CivCount;)
        {
            Units_CivBoxes[loop]->Destroy();
        }
        Units_CivBoxes.resize(CivCount);
    }
    for(size_t loop = 0; loop < CivCount; ++loop)
    {
        if(GenieVersion < genie::GV_SWGB)
        {
            Units_CivBoxes[loop]->SetLabel(dataset->Civs[loop].Name.substr(0, 2));
            Units_CivBoxes[loop]->SetToolTip(dataset->Civs[loop].Name);
        }
        else
        {
            Units_CivBoxes[loop]->SetLabel(dataset->Civs[loop].Name2.substr(0, 2));
            Units_CivBoxes[loop]->SetToolTip(dataset->Civs[loop].Name2);
        }
    }
    ListCivs();
    Units_DataArea->Layout();
    Refresh();
}

wxString AGE_Frame::GetResourceName(size_t index)
{
    if (index < CivilizationResourceNames.size())
        return CivilizationResourceNames[index];
    else return "Resource";
}

void AGE_Frame::OnResourcesSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListResources(false);
}

void AGE_Frame::ListResources(bool all)
{
    InitSearch(Civs_Resources_Search->GetValue().MakeLower(), Civs_Resources_Search_R->GetValue().MakeLower());

    Civs_Resources_ListV->Sweep();
    if(all)
    {
        resource_names.Clear();
        resource_names.Alloc(1 + dataset->Civs.front().Resources.size());
        resource_names.Add("-1 - None");
    }

    if (CivIDs.size())
    for(size_t loop = 0; loop < dataset->Civs[CivIDs.front()].Resources.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - Value: "+FormatFloat(dataset->Civs[CivIDs.front()].Resources[loop])+" - "+GetResourceName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Civs_Resources_ListV->names.Add(Name);
            Civs_Resources_ListV->indexes.push_back(loop);
        }
        if(all) resource_names.Add(FormatInt(loop)+" - "+GetResourceName(loop));
    }

    RefreshList(Civs_Resources_ListV, &ResourceIDs);
    if (all)
    {
        for (AGEComboBox *list : ResourceComboBoxList)
        {
            list->Flash();
        }
    }

    wxCommandEvent e;
    OnResourceSelect(e);
}

void AGE_Frame::OnResourceSelect(wxCommandEvent &event)
{
    size_t selections = Civs_Resources_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Civs_Resources_ListV, ResourceIDs);

    Civs_ResourceValue->clear();

    float * CivResourcePointer;
    for(size_t loop = selections; loop--> 0;)
    {
        CivResourcePointer = &dataset->Civs[CivIDs.front()].Resources[ResourceIDs[loop]];
        Civs_ResourceValue->prepend(CivResourcePointer);
    }

    Civs_ResourceValue->update();
}

void AGE_Frame::OnResourcesAdd(wxCommandEvent &event)
{
    size_t selections = Civs_Civs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
    dataset->Civs[loop].Resources.push_back(0);
    How2List = ListMode::ADD;
    ListResources();
}

void AGE_Frame::OnResourcesInsert(wxCommandEvent &event)
{
    size_t selections = Civs_Resources_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
    dataset->Civs[loop].Resources.insert(dataset->Civs[loop].Resources.begin() + ResourceIDs.front(), 0);
    How2List = ListMode::INSNEW;
    ListResources();
}

void AGE_Frame::OnResourcesDelete(wxCommandEvent &event)
{
    size_t selections = Civs_Resources_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    for(size_t loop2 = 0; loop2 < dataset->Civs.size(); ++loop2)
    {
        DeleteFromList(dataset->Civs[loop2].Resources, ResourceIDs);
    }
    ListResources();
}

void AGE_Frame::OnResourcesCopy(wxCommandEvent &event)
{
    size_t selections = Civs_Resources_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Civs[CivIDs.front()].Resources, ResourceIDs, copies.Resource);
    Civs_Resources_ListV->SetFocus();
}

void AGE_Frame::OnResourcesPaste(wxCommandEvent &event)
{
    size_t selections = Civs_Resources_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->Civs[CivIDs.front()].Resources, ResourceIDs, copies.Resource, false);
    ListResources();
}

void AGE_Frame::OnResourcesPasteInsert(wxCommandEvent &event)
{
    size_t selections = Civs_Resources_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->Civs[CivIDs.front()].Resources, ResourceIDs.front(), copies.Resource);
    ListResources();
}

void AGE_Frame::OnResourcesCopyToAll(wxCommandEvent &event)
{
    size_t selections = Civs_Resources_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    for(size_t loop = 0; loop < selections; ++loop)
    {
        float Copy = dataset->Civs[CivIDs.front()].Resources[ResourceIDs[loop]];
        for(size_t loop2 = 0; loop2 < dataset->Civs.size(); ++loop2)
        dataset->Civs[loop2].Resources[ResourceIDs[loop]] = Copy;
    }
}

void AGE_Frame::CreateCivControls()
{
    Civs_Main = new wxBoxSizer(wxHORIZONTAL);
    Civs_Civs_Buttons = new wxGridSizer(3, 0, 0);
    Tab_Civs = new ATabPage(TabBar_Main);

    Civs_Civs = new wxStaticBoxSizer(wxVERTICAL, Tab_Civs, "Civilizations");
    Civs_Civs_Search = new wxTextCtrl(Tab_Civs, wxID_ANY);
    Civs_Civs_Search_R = new wxTextCtrl(Tab_Civs, wxID_ANY);
    Civs_Civs_ListV = new ProperList(Tab_Civs, ASize(200, 100));
    Civs_Add = new wxButton(Tab_Civs, wxID_ANY, "Add *", wxDefaultPosition, wxSize(10, -1));
    Civs_Add->SetToolTip("I highly recommend you to download UserPatch\nfrom xOmicron, if you play The Conquerors.\nWith it you can use added civilizations.\nStar Wars versions can already have more civilizations.");
    Civs_Insert = new wxButton(Tab_Civs, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Civs_Delete = new wxButton(Tab_Civs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Civs_Copy = new wxButton(Tab_Civs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Civs_Paste = new wxButton(Tab_Civs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Civs_PasteInsert = new wxButton(Tab_Civs, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));

    Civs_DataArea = new wxBoxSizer(wxVERTICAL);
    Civs_DataGrid1 = new wxBoxSizer(wxHORIZONTAL);
    Civs_DataGrid2 = new wxBoxSizer(wxHORIZONTAL);
    Civs_DataGrid3 = new wxGridSizer(2, 0, 0);
    Civs_Name_Holder[0] = new wxBoxSizer(wxVERTICAL);
    Civs_Name_Text[0] = new SolidText(Tab_Civs, " Internal Name");
    Civs_Name[0] = new StringControl(Tab_Civs, this, &uiGroupCiv, 20, false);
    Civs_Name_Holder[1] = new wxBoxSizer(wxVERTICAL);
    Civs_Name_Text[1] = new SolidText(Tab_Civs, " Internal Name 2");
    Civs_Name[1] = new StringControl(Tab_Civs, this, &uiGroupCiv, 20, false);
    Civs_One_Holder = new wxBoxSizer(wxVERTICAL);
    Civs_One_Text = new SolidText(Tab_Civs, " Player Type *");
    Civs_One = new NumberControl(CUByte, Tab_Civs, this, &uiGroupCiv);
    Civs_One->SetToolTip("Forced to use 1\n0   Default\n1   Player\n2   Gaia Player\n3   AI Player");
    Civs_GraphicSet_Holder = new wxBoxSizer(wxVERTICAL);
    Civs_GraphicSet_Text = new SolidText(Tab_Civs, " Icon Set *");
    Civs_GraphicSet = new NumberControl(CUByte, Tab_Civs, this, &uiGroupCiv, false);
    Civs_GraphicSet->SetToolTip("Building icon set (and trade cart graphics?)\nThis is actually an offset used to look up SLPs inside the DRS file\nAoE 1: also determines the interface graphics used\nStar Wars: also determines unit and tech icons");
    Civs_TechTree_Holder = new wxBoxSizer(wxVERTICAL);
    Civs_TechTree_Text = new SolidText(Tab_Civs, " Technology Tree");
    Civs_TechTree = new NumberControl(CShort, Tab_Civs, this, &uiGroupCiv);
    Civs_TechTree_ComboBox = new LinkedComboBox(Tab_Civs, Civs_TechTree, &tech_names);
    TechComboBoxList.push_back(Civs_TechTree_ComboBox);
    Civs_TeamBonus_Holder = new wxBoxSizer(wxVERTICAL);
    Civs_TeamBonus_Text = new SolidText(Tab_Civs, " Team Bonus");
    Civs_TeamBonus = new NumberControl(CShort, Tab_Civs, this, &uiGroupCiv);
    Civs_TeamBonus_ComboBox = new LinkedComboBox(Tab_Civs, Civs_TeamBonus, &tech_names);
    TechComboBoxList.push_back(Civs_TeamBonus_ComboBox);
    Civs_SUnknown1_Holder = new wxBoxSizer(wxVERTICAL);
    Civs_SUnknown1_Text = new SolidText(Tab_Civs, " Unique Units / Techs");
    for(size_t loop = 0; loop < 4; ++loop)
    Civs_SUnknown1[loop] = new NumberControl(CShort, Tab_Civs, this, &uiGroupCiv);

    Civs_Resources = new wxStaticBoxSizer(wxVERTICAL, Tab_Civs, "Initial Resources");
    Civs_Resources_Search = new wxTextCtrl(Tab_Civs, wxID_ANY);
    Civs_Resources_Search_R = new wxTextCtrl(Tab_Civs, wxID_ANY);
    Civs_ResourceValue_Holder = new wxBoxSizer(wxVERTICAL);
    Civs_ResourceValue_Text = new SolidText(Tab_Civs, " Resource Value");
    Civs_ResourceValue = new NumberControl(CFloat, Tab_Civs, this, nullptr, false);
    Civs_Resources_ListV = new ProperList(Tab_Civs, ASize(200, 100));
    Civs_Resources_Buttons = new wxGridSizer(3, 0, 0);
    Resources_Add = new wxButton(Tab_Civs, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Resources_Insert = new wxButton(Tab_Civs, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Resources_Delete = new wxButton(Tab_Civs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Resources_Copy = new wxButton(Tab_Civs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Resources_Paste = new wxButton(Tab_Civs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Resources_PasteInsert = new wxButton(Tab_Civs, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Resources_CopyToAll = new wxButton(Tab_Civs, wxID_ANY, "Copy to all civs", wxDefaultPosition, wxSize(10, -1));
    Civs_Resources_Data = new wxBoxSizer(wxVERTICAL);

    Civs_Civs_Buttons->Add(Civs_Add, 1, wxEXPAND);
    Civs_Civs_Buttons->Add(Civs_Delete, 1, wxEXPAND);
    Civs_Civs_Buttons->Add(Civs_Insert, 1, wxEXPAND);
    Civs_Civs_Buttons->Add(Civs_Copy, 1, wxEXPAND);
    Civs_Civs_Buttons->Add(Civs_Paste, 1, wxEXPAND);
    Civs_Civs_Buttons->Add(Civs_PasteInsert, 1, wxEXPAND);

    Civs_Civs->Add(Civs_Civs_Search, 0, wxEXPAND);
    Civs_Civs->Add(Civs_Civs_Search_R, 0, wxEXPAND);
    Civs_Civs->Add(Civs_Civs_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Civs_Civs->Add(Civs_Civs_Buttons, 0, wxEXPAND);

    Civs_One_Holder->Add(Civs_One_Text);
    Civs_One_Holder->Add(Civs_One);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Civs_Name_Holder[loop]->Add(Civs_Name_Text[loop]);
        Civs_Name_Holder[loop]->Add(Civs_Name[loop], 0, wxEXPAND);
    }
    Civs_SUnknown1_Holder->Add(Civs_SUnknown1_Text);
    Civs_SUnknown1_Holder->Add(Civs_DataGrid3);
    for(size_t loop = 0; loop < 4; ++loop)
    Civs_DataGrid3->Add(Civs_SUnknown1[loop]);
    Civs_TechTree_Holder->Add(Civs_TechTree_Text);
    Civs_TechTree_Holder->Add(Civs_TechTree, 0, wxEXPAND);
    Civs_TechTree_Holder->Add(Civs_TechTree_ComboBox);
    Civs_TeamBonus_Holder->Add(Civs_TeamBonus_Text);
    Civs_TeamBonus_Holder->Add(Civs_TeamBonus, 0, wxEXPAND);
    Civs_TeamBonus_Holder->Add(Civs_TeamBonus_ComboBox);
    Civs_GraphicSet_Holder->Add(Civs_GraphicSet_Text);
    Civs_GraphicSet_Holder->Add(Civs_GraphicSet);

    Civs_DataGrid1->Add(Civs_One_Holder);
    Civs_DataGrid1->Add(Civs_GraphicSet_Holder, 0, wxLEFT, 5);
    Civs_DataGrid2->Add(Civs_TechTree_Holder);
    Civs_DataGrid2->Add(Civs_TeamBonus_Holder, 0, wxLEFT, 5);

    Civs_DataArea->Add(Civs_Name_Holder[0], 0, wxEXPAND | wxTOP, 5);
    Civs_DataArea->Add(Civs_Name_Holder[1], 0, wxEXPAND | wxTOP, 5);
    Civs_DataArea->Add(Civs_DataGrid1, 0, wxTOP, 5);
    Civs_DataArea->Add(Civs_DataGrid2, 0, wxTOP, 5);
    Civs_DataArea->Add(Civs_SUnknown1_Holder, 0, wxTOP, 5);

    Civs_Resources_Buttons->Add(Resources_Add, 1, wxEXPAND);
    Civs_Resources_Buttons->Add(Resources_Delete, 1, wxEXPAND);
    Civs_Resources_Buttons->Add(Resources_Insert, 1, wxEXPAND);
    Civs_Resources_Buttons->Add(Resources_Copy, 1, wxEXPAND);
    Civs_Resources_Buttons->Add(Resources_Paste, 1, wxEXPAND);
    Civs_Resources_Buttons->Add(Resources_PasteInsert, 1, wxEXPAND);
    Civs_Resources_Buttons->Add(Resources_CopyToAll, 1, wxEXPAND);

    Civs_ResourceValue_Holder->Add(Civs_ResourceValue_Text);
    Civs_ResourceValue_Holder->Add(Civs_ResourceValue, 1, wxEXPAND);

    Civs_Resources_Data->Add(Civs_ResourceValue_Holder, 0, wxEXPAND);

    Civs_Resources->Add(Civs_Resources_Search, 0, wxEXPAND);
    Civs_Resources->Add(Civs_Resources_Search_R, 0, wxEXPAND);
    Civs_Resources->Add(Civs_Resources_Data, 0, wxEXPAND);
    Civs_Resources->Add(Civs_Resources_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Civs_Resources->Add(Civs_Resources_Buttons, 0, wxEXPAND);

    Civs_Main->Add(Civs_Civs, 21, wxEXPAND | wxALL, 5);
    Civs_Main->Add(Civs_DataArea);
    Civs_Main->Add(Civs_Resources, 30, wxEXPAND | wxALL, 5);

    Tab_Civs->SetSizer(Civs_Main);

    Civs_Civs_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnCivsSearch, this);
    Civs_Civs_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnCivsSearch, this);
    Civs_Civs_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnCivSelect, this);
    Civs_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnCivsAdd, this);
    Civs_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnCivsInsert, this);
    Civs_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnCivsDelete, this);
    Civs_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnCivsCopy, this);
    Civs_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnCivsPaste, this);
    Civs_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnCivsPasteInsert, this);
    Civs_Resources_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnResourcesSearch, this);
    Civs_Resources_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnResourcesSearch, this);
    Civs_Resources_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnResourceSelect, this);
    Resources_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnResourcesCopy, this);
    Resources_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnResourcesPaste, this);
    Resources_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnResourcesPasteInsert, this);
    Resources_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnResourcesAdd, this);
    Resources_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnResourcesInsert, this);
    Resources_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnResourcesDelete, this);
    Resources_CopyToAll->Bind(wxEVT_BUTTON, &AGE_Frame::OnResourcesCopyToAll, this);

    for(size_t loop = 0; loop < 2; ++loop)
    {
        Civs_Name[loop]->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
        {
            event.Skip();
            if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
            {
                for (int ID : CivIDs)
                {
                    if (GenieVersion < genie::GV_SWGB)
                        Units_CivBoxes[ID]->SetLabel(dataset->Civs[ID].Name.substr(0, 2));
                    else
                        Units_CivBoxes[ID]->SetLabel(dataset->Civs[ID].Name2.substr(0, 2));
                }
                ListCivs();
            }
        });
        Civs_Name[loop]->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
        {
            static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
            for (int ID : CivIDs)
            {
                if (GenieVersion < genie::GV_SWGB)
                    Units_CivBoxes[ID]->SetLabel(dataset->Civs[ID].Name.substr(0, 2));
                else
                    Units_CivBoxes[ID]->SetLabel(dataset->Civs[ID].Name2.substr(0, 2));
            }
            ListCivs();
        });
    }
    Civs_GraphicSet->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListCivs();
        }
    });
    Civs_GraphicSet->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListCivs();
    });
    Civs_ResourceValue->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListResources();
        }
    });
    Civs_ResourceValue->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListResources();
    });
}
