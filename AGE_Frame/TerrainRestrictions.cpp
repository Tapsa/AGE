#include "Common.h"
#include "../AGE_Frame.h"

wxString AGE_Frame::GetTerrainRestrictionName(int index)
{
    if (index < TerrainRestrictionNames.size())
        return TerrainRestrictionNames[index];
    else return "Table";
}

void AGE_Frame::OnTerrainRestrictionsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListTerrainRestrictions(false);
}

void AGE_Frame::ListTerrainRestrictions(bool all)
{
    InitTerrainRestrictions(all);
    wxCommandEvent e;
    OnTerrainRestrictionSelect(e);
}

void AGE_Frame::InitTerrainRestrictions(bool all)
{
    InitSearch(TerRestrict_TerRestrict_Search->GetValue().MakeLower(), TerRestrict_TerRestrict_Search_R->GetValue().MakeLower());

    TerRestrict_TerRestrict_ListV->Sweep();
    if(all)
    {
        restriction_names.Clear();
        restriction_names.Alloc(1 + dataset->TerrainRestrictions.size());
        restriction_names.Add("-1 - None");
    }

    for(size_t loop = 0; loop < dataset->TerrainRestrictions.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetTerrainRestrictionName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            TerRestrict_TerRestrict_ListV->names.Add(Name);
            TerRestrict_TerRestrict_ListV->indexes.push_back(loop);
        }
        if (all)
        {
            restriction_names.Add(Name);
        }
    }

    RefreshList(TerRestrict_TerRestrict_ListV, &TerRestrictIDs);
    if (all)
    {
        for (AGEComboBox *list : TerrainRestrictionComboBoxList)
        {
            list->Flash();
        }
    }
}

void AGE_Frame::OnTerrainRestrictionSelect(wxCommandEvent &event)
{
    size_t selections = TerRestrict_TerRestrict_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, TerRestrict_TerRestrict_ListV, TerRestrictIDs);

    SetStatusText(wxString::Format("Selections: %zu    Selected table: %d",
        selections, selections > 0 ? TerRestrictIDs.front() : -1), 0);
    ListTerrains2();
}

void AGE_Frame::OnTerrainRestrictionsTerrainSelect(wxCommandEvent &event)
{
    size_t selections = TerRestrict_Terrains_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, TerRestrict_Terrains_ListV, TerRestrictTerIDs);

    for (AGETextCtrl *box : uiGroupRestriction) box->clear();

    genie::TerrainRestriction * TerRestPointer;
    for(short rest = TerRestrictIDs.size(); rest--> 0;)
    {
        TerRestPointer = &dataset->TerrainRestrictions[TerRestrictIDs[rest]];
        for(size_t loop = selections; loop--> 0;)
        {
            TerRestrict_Accessible->prepend(&TerRestPointer->PassableBuildableDmgMultiplier[TerRestrictTerIDs[loop]]);
            if(GenieVersion >= genie::GV_AoKA || (GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap))
            {
                TerRestrict_Graphics[0]->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].ExitTileSpriteID);
                TerRestrict_Graphics[1]->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].EnterTileSpriteID);
                TerRestrict_Graphics[2]->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].WalkTileSpriteID);
                TerRestrict_Amount->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].WalkSpriteRate);
            }
        }
    }

    for (AGETextCtrl *box : uiGroupRestriction) box->update();
}

void AGE_Frame::OnTerrainRestrictionsAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    dataset->FloatPtrTerrainTables.push_back(1);
    if(GenieVersion >= genie::GV_AoKA)
    dataset->TerrainPassGraphicPointers.push_back(1);
    AddToList(dataset->TerrainRestrictions);
    ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsInsert(wxCommandEvent &event)
{
    if(!TerRestrict_TerRestrict_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    dataset->FloatPtrTerrainTables.insert(dataset->FloatPtrTerrainTables.begin() + TerRestrictIDs.front(), 1);
    if(GenieVersion >= genie::GV_AoKA)
    dataset->TerrainPassGraphicPointers.insert(dataset->TerrainPassGraphicPointers.begin() + TerRestrictIDs.front(), 1);
    InsertToList(dataset->TerrainRestrictions, TerRestrictIDs.front());
    ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsDelete(wxCommandEvent &event)
{
    if(!TerRestrict_TerRestrict_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->FloatPtrTerrainTables, TerRestrictIDs);
    if(GenieVersion >= genie::GV_AoKA)
    DeleteFromList(dataset->TerrainPassGraphicPointers, TerRestrictIDs);
    DeleteFromList(dataset->TerrainRestrictions, TerRestrictIDs);
    ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsCopy(wxCommandEvent &event)
{
    if(!TerRestrict_TerRestrict_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->FloatPtrTerrainTables, TerRestrictIDs, copies.TRptr1);
    if(GenieVersion >= genie::GV_AoKA)
    CopyFromList(dataset->TerrainPassGraphicPointers, TerRestrictIDs, copies.TRptr2);
    CopyFromList(dataset->TerrainRestrictions, TerRestrictIDs, copies.TerrainRestriction);
    TerRestrict_TerRestrict_ListV->SetFocus();
}

void AGE_Frame::OnTerrainRestrictionsPaste(wxCommandEvent &event)
{
    if(!TerRestrict_TerRestrict_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    // Argh. So much redundancy.
    PasteToListNoGV(dataset->FloatPtrTerrainTables, TerRestrictIDs, copies.TRptr1);
    if(GenieVersion >= genie::GV_AoKA)
    PasteToListNoGV(dataset->TerrainPassGraphicPointers, TerRestrictIDs, copies.TRptr2);
    PasteToList(dataset->TerrainRestrictions, TerRestrictIDs, copies.TerrainRestriction);
    ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsPasteInsert(wxCommandEvent &event)
{
    if(!TerRestrict_TerRestrict_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->FloatPtrTerrainTables, TerRestrictIDs.front(), copies.TRptr1);
    if(GenieVersion >= genie::GV_AoKA)
    PasteInsertToListNoGV(dataset->TerrainPassGraphicPointers, TerRestrictIDs.front(), copies.TRptr2);
    PasteInsertToList(dataset->TerrainRestrictions, TerRestrictIDs.front(), copies.TerrainRestriction);
    ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsTerrainCopy(wxCommandEvent &event)
{
    size_t selections = TerRestrict_TerRestrict_ListV->GetSelectedCount();
    size_t Selections2 = TerRestrict_Terrains_ListV->GetSelectedCount();
    if(selections < 1 || Selections2 < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TerrainRestrictions[TerRestrictIDs.front()].PassableBuildableDmgMultiplier, TerRestrictTerIDs, copies.TerrainRestrictionSubAccess);
    if(GenieVersion >= genie::GV_AoKA || (GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap))
    CopyFromList(dataset->TerrainRestrictions[TerRestrictIDs.front()].TerrainPassGraphics, TerRestrictTerIDs, copies.TerrainRestrictionSubGraphics);
    TerRestrict_Terrains_ListV->SetFocus();
}

void AGE_Frame::OnTerrainRestrictionsTerrainPaste(wxCommandEvent &event)
{
    size_t selections = TerRestrict_TerRestrict_ListV->GetSelectedCount();
    size_t Selections2 = TerRestrict_Terrains_ListV->GetSelectedCount();
    if(selections < 1 || Selections2 < 1) return;

    wxBusyCursor WaitCursor;
    size_t CopyCount = copies.TerrainRestrictionSubAccess.size();
    if(Paste11)
    {
        if(Paste11Check(TerRestrictTerIDs.size(), copies.TerrainRestrictionSubGraphics.size()))
        {
            for(size_t loop = 0; loop < CopyCount; ++loop)
            dataset->TerrainRestrictions[TerRestrictIDs.front()].PassableBuildableDmgMultiplier[TerRestrictTerIDs[loop]] = copies.TerrainRestrictionSubAccess[loop];
            if(GenieVersion >= genie::GV_AoKA || (GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap))
            {
                for(size_t loop = 0; loop < CopyCount; ++loop)
                {
                    copies.TerrainRestrictionSubGraphics[loop].setGameVersion(GenieVersion);
                    dataset->TerrainRestrictions[TerRestrictIDs.front()].TerrainPassGraphics[TerRestrictTerIDs[loop]] = copies.TerrainRestrictionSubGraphics[loop];
                }
            }
        }
    }
    else
    {
        if(CopyCount+TerRestrictTerIDs.front() > dataset->TerrainRestrictions[TerRestrictIDs.front()].PassableBuildableDmgMultiplier.size())
        CopyCount -= CopyCount+TerRestrictTerIDs.front() - dataset->TerrainRestrictions[TerRestrictIDs.front()].PassableBuildableDmgMultiplier.size();
        for(size_t loop = 0; loop < CopyCount; ++loop)
        dataset->TerrainRestrictions[TerRestrictIDs.front()].PassableBuildableDmgMultiplier[TerRestrictTerIDs.front()+loop] = copies.TerrainRestrictionSubAccess[loop];
        if(GenieVersion >= genie::GV_AoKA || (GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap))
        {
            for(size_t loop = 0; loop < CopyCount; ++loop)
            {
                copies.TerrainRestrictionSubGraphics[loop].setGameVersion(GenieVersion);
                dataset->TerrainRestrictions[TerRestrictIDs.front()].TerrainPassGraphics[TerRestrictTerIDs.front()+loop] = copies.TerrainRestrictionSubGraphics[loop];
            }
        }
    }
    ListTerrains2();
}

void AGE_Frame::CreateTerrainRestrictionControls()
{
    Tab_TerrainRestrictions = new ATabPage(TabBar_Main);

    TerRestrict_Main = new wxBoxSizer(wxHORIZONTAL);
    TerRestrict_TerRestrict_Buttons = new wxGridSizer(3, 0, 0);
    TerRestrict_TerRestrict = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainRestrictions, "Terrain Tables");
    TerRestrict_TerRestrict_Search = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
    TerRestrict_TerRestrict_Search_R = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
    TerRestrict_TerRestrict_ListV = new ProperList(Tab_TerrainRestrictions, ASize(200, 100));
    TerRestrict_Add = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    TerRestrict_Insert = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    TerRestrict_Delete = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    TerRestrict_Copy = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    TerRestrict_Paste = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    TerRestrict_PasteInsert = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));

    TerRestrict_Terrains = new wxBoxSizer(wxVERTICAL);
    TerRestrict_DataArea = new wxBoxSizer(wxVERTICAL);
    TerRestrict_Terrains_Search = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
    TerRestrict_Terrains_Search_R = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
    TerRestrict_Terrains_ListV = new ProperList(Tab_TerrainRestrictions, ASize(200, 100));
    TerRestrict_Terrains_Buttons = new wxGridSizer(2, 0, 0);
    TerRestrict_Terrains_Copy = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    TerRestrict_Terrains_Paste = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    TerRestrict_Accessible_Text = new SolidText(Tab_TerrainRestrictions, " Accessibility and Damage Multiplier *");
    TerRestrict_Accessible = new NumberControl(CFloat, Tab_TerrainRestrictions, this, &uiGroupRestriction, false, AGETextCtrl::NORMAL);
    TerRestrict_Accessible->SetToolTip("See unit -> terrain defense bonus\nPass-ability:\n 0  Not passable\n > 0  Passable\nBuild-ability:"
        "\n <= 0.05  You cannot build on it.\n > 0.05  You can build on it.\nDamage Multiplier:\n 0  Damage multiplier is 1."
        "\n > 0  Damage multipler is as specified.\nStar Wars: < 1  Damage multiplier is 1.");
    TerRestrict_Graphics_Holder = new wxBoxSizer(wxVERTICAL);
    TerRestrict_Graphics_Text[0] = new SolidText(Tab_TerrainRestrictions, " Exit Tile Graphic");
    TerRestrict_Graphics_Text[1] = new SolidText(Tab_TerrainRestrictions, " Enter Tile Graphic");
    TerRestrict_Graphics_Text[2] = new SolidText(Tab_TerrainRestrictions, " Walk Tile Graphic");
    for(size_t loop = 0; loop < 3; ++loop)
    {
        TerRestrict_Graphics[loop] = new NumberControl(CLong, Tab_TerrainRestrictions, this, &uiGroupRestriction, true, AGETextCtrl::LARGE);
        TerRestrict_Graphics_ComboBox[loop] = new LinkedComboBox(Tab_TerrainRestrictions, TerRestrict_Graphics[loop], &graphic_names);
        GraphicComboBoxList.push_back(TerRestrict_Graphics_ComboBox[loop]);
    }
    TerRestrict_Amount_Text = new SolidText(Tab_TerrainRestrictions, " Walk Graphic Rate");
    TerRestrict_Amount = new NumberControl(CFloat, Tab_TerrainRestrictions, this, &uiGroupRestriction);

    TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Add, 1, wxEXPAND);
    TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Delete, 1, wxEXPAND);
    TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Insert, 1, wxEXPAND);
    TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Copy, 1, wxEXPAND);
    TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Paste, 1, wxEXPAND);
    TerRestrict_TerRestrict_Buttons->Add(TerRestrict_PasteInsert, 1, wxEXPAND);

    TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_Search, 0, wxEXPAND);
    TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_Search_R, 0, wxEXPAND);
    TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_Buttons, 0, wxEXPAND);

    TerRestrict_Terrains_Buttons->Add(TerRestrict_Terrains_Copy, 1, wxEXPAND);
    TerRestrict_Terrains_Buttons->Add(TerRestrict_Terrains_Paste, 1, wxEXPAND);

    TerRestrict_Terrains->Add(TerRestrict_Terrains_Search, 0, wxEXPAND);
    TerRestrict_Terrains->Add(TerRestrict_Terrains_Search_R, 0, wxEXPAND);
    TerRestrict_Terrains->Add(TerRestrict_Terrains_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    TerRestrict_Terrains->Add(TerRestrict_Terrains_Buttons, 0, wxEXPAND);

    for(size_t loop = 0; loop < 3; ++loop)
    {
        TerRestrict_Graphics_Holder->Add(TerRestrict_Graphics_Text[loop]);
        TerRestrict_Graphics_Holder->Add(TerRestrict_Graphics[loop]);
        TerRestrict_Graphics_Holder->Add(TerRestrict_Graphics_ComboBox[loop], 0, wxBOTTOM, 5);
    }
    TerRestrict_Graphics_Holder->Add(TerRestrict_Amount_Text);
    TerRestrict_Graphics_Holder->Add(TerRestrict_Amount);

    TerRestrict_DataArea->Add(TerRestrict_Accessible_Text, 0, wxTOP, 5);
    TerRestrict_DataArea->Add(TerRestrict_Accessible, 0, wxTOP, 5);
    TerRestrict_DataArea->Add(TerRestrict_Graphics_Holder, 0, wxTOP, 5);

    TerRestrict_Main->Add(TerRestrict_TerRestrict, 1, wxEXPAND | wxALL, 5);
    TerRestrict_Main->Add(TerRestrict_Terrains, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);
    TerRestrict_Main->Add(TerRestrict_DataArea, 1, wxEXPAND);
    TerRestrict_Main->AddStretchSpacer(1);

    Tab_TerrainRestrictions->SetSizer(TerRestrict_Main);

    TerRestrict_TerRestrict_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainRestrictionsSearch, this);
    TerRestrict_TerRestrict_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainRestrictionsSearch, this);
    TerRestrict_TerRestrict_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnTerrainRestrictionSelect, this);
    TerRestrict_Terrains_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainsSearch, this);
    TerRestrict_Terrains_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainsSearch, this);
    TerRestrict_Terrains_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnTerrainRestrictionsTerrainSelect, this);
    TerRestrict_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainRestrictionsAdd, this);
    TerRestrict_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainRestrictionsInsert, this);
    TerRestrict_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainRestrictionsDelete, this);
    TerRestrict_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainRestrictionsCopy, this);
    TerRestrict_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainRestrictionsPaste, this);
    TerRestrict_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainRestrictionsPasteInsert, this);
    TerRestrict_Terrains_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainRestrictionsTerrainCopy, this);
    TerRestrict_Terrains_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainRestrictionsTerrainPaste, this);

    TerRestrict_Accessible->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TerRestrict, this);
    TerRestrict_Accessible->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_TerRestrict, this);
}

void AGE_Frame::OnEnter_TerRestrict(wxCommandEvent &event)
{
    static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
    ListTerrains2();
}

void AGE_Frame::OnKillFocus_TerRestrict(wxFocusEvent &event)
{
    event.Skip();
    if(static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() != 0) return;
    ListTerrains2();
}
