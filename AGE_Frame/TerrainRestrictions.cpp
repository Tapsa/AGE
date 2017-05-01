#include "../AGE_Frame.h"

wxString AGE_Frame::GetTerrainRestrictionName(int index)
{
    if(GenieVersion < genie::GV_AoKA)
    {
        if(index < AoE1TerrainRestrictions.size())
            return AoE1TerrainRestrictions[index];
        else return "Restriction";
    }
    else if(GenieVersion < genie::GV_SWGB)
    {
        if(index < AoE2TerrainRestrictions.size())
            return AoE2TerrainRestrictions[index];
        else return "Restriction";
    }
    else
    {
        if(index < SWGBTerrainRestrictions.size())
            return SWGBTerrainRestrictions[index];
        else return "Restriction";
    }
}

void AGE_Frame::OnTerrainRestrictionsSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTerrainRestrictions(false);
}

void AGE_Frame::ListTerrainRestrictions(bool all)
{
    InitTerrainRestrictions(all);
    wxTimerEvent E;
    OnTerrainRestrictionsTimer(E);
}

void AGE_Frame::InitTerrainRestrictions(bool all)
{
    InitSearch(TerRestrict_TerRestrict_Search->GetValue().MakeLower(), TerRestrict_TerRestrict_Search_R->GetValue().MakeLower());

    TerRestrict_TerRestrict_ListV->names.clear();
    TerRestrict_TerRestrict_ListV->indexes.clear();
    if(all)
    {
        restriction_names.Clear();
        restriction_names.Alloc(dataset->TerrainRestrictions.size());
    }

    for(size_t loop = 0; loop < dataset->TerrainRestrictions.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetTerrainRestrictionName(loop);
        if(SearchMatches(Name.Lower()))
        {
            TerRestrict_TerRestrict_ListV->names.Add(Name);
            TerRestrict_TerRestrict_ListV->indexes.push_back(loop);
        }
        if(all) restriction_names.Add(Name);
    }

    virtualListing(TerRestrict_TerRestrict_ListV, &TerRestrictIDs);
    if(all) FillLists(TerrainRestrictionComboBoxList, restriction_names);
}

void AGE_Frame::OnTerrainRestrictionsSelect(wxCommandEvent &event)
{
    if(!restrictionTimer.IsRunning())
        restrictionTimer.Start(150);
}

void AGE_Frame::OnTerrainRestrictionsTimer(wxTimerEvent&)
{
    restrictionTimer.Stop();
    auto selections = TerRestrict_TerRestrict_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, TerRestrict_TerRestrict_ListV, TerRestrictIDs);

    SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected restriction: "+lexical_cast<string>(TerRestrictIDs.front()), 0);
    ListTerrains2();
}

void AGE_Frame::OnTerrainRestrictionsTerrainSelect(wxCommandEvent &event)
{
    if(!restrictionTerrainTimer.IsRunning())
        restrictionTerrainTimer.Start(150);
}

void AGE_Frame::OnTerrainRestrictionsTerrainTimer(wxTimerEvent&)
{
    restrictionTerrainTimer.Stop();
    auto selections = TerRestrict_Terrains_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, TerRestrict_Terrains_ListV, TerRestrictTerIDs);

    for(auto &box: uiGroupRestriction) box->clear();

    genie::TerrainRestriction * TerRestPointer;
    for(short rest = TerRestrictIDs.size(); rest--> 0;)
    {
        TerRestPointer = &dataset->TerrainRestrictions[TerRestrictIDs[rest]];
        for(size_t loop = selections; loop--> 0;)
        {
            TerRestrict_Accessible->prepend(&TerRestPointer->PassableBuildableDmgMultiplier[TerRestrictTerIDs[loop]]);
            if(GenieVersion >= genie::GV_AoKA)  //  Above AoE and RoR
            {
                TerRestrict_Graphics[0]->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].ExitTileSpriteID);
                TerRestrict_Graphics[1]->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].EnterTileSpriteID);
                TerRestrict_Graphics[2]->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].WalkTileSpriteID);
                TerRestrict_Amount->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].WalkSpriteRate);
            }
        }
    }

    for(auto &box: uiGroupRestriction) box->update();
}

void AGE_Frame::OnTerrainRestrictionsAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    dataset->TerrainRestrictionPointers1.push_back(1);
    if(GenieVersion >= genie::GV_AoKA)
    dataset->TerrainRestrictionPointers2.push_back(1);
    AddToList(dataset->TerrainRestrictions);
    ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsInsert(wxCommandEvent &event)
{
    if(TerRestrict_TerRestrict_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    dataset->TerrainRestrictionPointers1.insert(dataset->TerrainRestrictionPointers1.begin() + TerRestrictIDs.front(), 1);
    if(GenieVersion >= genie::GV_AoKA)
    dataset->TerrainRestrictionPointers2.insert(dataset->TerrainRestrictionPointers2.begin() + TerRestrictIDs.front(), 1);
    InsertToList(dataset->TerrainRestrictions, TerRestrictIDs.front());
    ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsDelete(wxCommandEvent &event)
{
    if(TerRestrict_TerRestrict_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->TerrainRestrictionPointers1, GraphicIDs);
    if(GenieVersion >= genie::GV_AoKA)
    DeleteFromList(dataset->TerrainRestrictionPointers2, GraphicIDs);
    DeleteFromList(dataset->TerrainRestrictions, GraphicIDs);
    ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsCopy(wxCommandEvent &event)
{
    if(TerRestrict_TerRestrict_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TerrainRestrictionPointers1, TerRestrictIDs, copies.TRptr1);
    if(GenieVersion >= genie::GV_AoKA)
    CopyFromList(dataset->TerrainRestrictionPointers2, TerRestrictIDs, copies.TRptr2);
    CopyFromList(dataset->TerrainRestrictions, TerRestrictIDs, copies.TerrainRestriction);
    TerRestrict_TerRestrict_ListV->SetFocus();
}

void AGE_Frame::OnTerrainRestrictionsPaste(wxCommandEvent &event)
{
    if(TerRestrict_TerRestrict_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    // Argh. So much redundancy.
    PasteToListNoGV(dataset->TerrainRestrictionPointers1, TerRestrictIDs, copies.TRptr1);
    if(GenieVersion >= genie::GV_AoKA)
    PasteToListNoGV(dataset->TerrainRestrictionPointers2, TerRestrictIDs, copies.TRptr2);
    PasteToList(dataset->TerrainRestrictions, TerRestrictIDs, copies.TerrainRestriction);
    ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsPasteInsert(wxCommandEvent &event)
{
    if(TerRestrict_TerRestrict_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->TerrainRestrictionPointers1, TerRestrictIDs.front(), copies.TRptr1);
    if(GenieVersion >= genie::GV_AoKA)
    PasteInsertToListNoGV(dataset->TerrainRestrictionPointers2, TerRestrictIDs.front(), copies.TRptr2);
    PasteInsertToList(dataset->TerrainRestrictions, TerRestrictIDs.front(), copies.TerrainRestriction);
    ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsTerrainCopy(wxCommandEvent &event)
{
    auto selections = TerRestrict_TerRestrict_ListV->GetSelectedItemCount();
    auto Selections2 = TerRestrict_Terrains_ListV->GetSelectedItemCount();
    if(selections < 1 || Selections2 < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TerrainRestrictions[TerRestrictIDs.front()].PassableBuildableDmgMultiplier, TerRestrictTerIDs, copies.TerrainRestrictionSubAccess);
    if(GenieVersion >= genie::GV_AoKA)  // not AoE nor RoR
    CopyFromList(dataset->TerrainRestrictions[TerRestrictIDs.front()].TerrainPassGraphics, TerRestrictTerIDs, copies.TerrainRestrictionSubGraphics);
    TerRestrict_Terrains_ListV->SetFocus();
}

void AGE_Frame::OnTerrainRestrictionsTerrainPaste(wxCommandEvent &event)
{
    auto selections = TerRestrict_TerRestrict_ListV->GetSelectedItemCount();
    auto Selections2 = TerRestrict_Terrains_ListV->GetSelectedItemCount();
    if(selections < 1 || Selections2 < 1) return;

    wxBusyCursor WaitCursor;
    short CopyCount = TerrainRestrictionSubCopyAccess.size();
    if(Paste11)
    {
        if(Paste11Check(TerRestrictTerIDs.size(), copies.TerrainRestrictionSubGraphics.size()))
        {
            for(size_t loop = 0; loop < CopyCount; ++loop)
            dataset->TerrainRestrictions[TerRestrictIDs.front()].PassableBuildableDmgMultiplier[TerRestrictTerIDs[loop]] = TerrainRestrictionSubCopyAccess[loop];
            if(GenieVersion >= genie::GV_AoKA)  // not AoE nor RoR
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
        dataset->TerrainRestrictions[TerRestrictIDs.front()].PassableBuildableDmgMultiplier[TerRestrictTerIDs.front()+loop] = TerrainRestrictionSubCopyAccess[loop];
        if(GenieVersion >= genie::GV_AoKA)  // not AoE nor RoR
        {
            for(size_t loop = 0; loop < CopyCount; ++loop)
            {
                copies.TerrainRestrictionSubGraphics[loop].setGameVersion(GenieVersion);
                dataset->TerrainRestrictions[TerRestrictIDs.front()].TerrainPassGraphics[TerRestrictTerIDs.front()+loop] = copies.TerrainRestrictionSubGraphics[loop];
            }
        }
    }
    wxTimerEvent E;
    OnTerrainRestrictionsTerrainTimer(E);
}

void AGE_Frame::CreateTerrainRestrictionControls()
{
    Tab_TerrainRestrictions = new wxPanel(TabBar_Main);

    TerRestrict_Main = new wxBoxSizer(wxHORIZONTAL);
    TerRestrict_TerRestrict_Buttons = new wxGridSizer(3, 0, 0);
    TerRestrict_TerRestrict = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainRestrictions, "Terrain Restrictions");
    TerRestrict_TerRestrict_Search = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
    TerRestrict_TerRestrict_Search_R = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
    TerRestrict_TerRestrict_ListV = new AGEListView(Tab_TerrainRestrictions, wxSize(200, 100));
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
    TerRestrict_Terrains_ListV = new AGEListView(Tab_TerrainRestrictions, wxSize(200, 100));
    TerRestrict_Terrains_Buttons = new wxGridSizer(2, 0, 0);
    TerRestrict_Terrains_Copy = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    TerRestrict_Terrains_Paste = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    TerRestrict_Accessible_Text = new SolidText(Tab_TerrainRestrictions, " Accessibility and Damage Multiplier *");
    TerRestrict_Accessible = AGETextCtrl::init(CFloat, &uiGroupRestriction, this, &popUp, Tab_TerrainRestrictions, AGETextCtrl::NORMAL);
    TerRestrict_Accessible->SetToolTip("See unit armor terrain restriction\nPass-ability:\n 0  Not passable\n > 0  Passable\nBuild-ability:\n <= 0.05  You cannot build on it.\n > 0.05  You can build on it.\nDamage Multiplier:\n 0  Damage multiplier is 1.\n > 0  Damage multipler is as specified.\nStar Wars: < 1  Damage multiplier is 1.");
    TerRestrict_Graphics_Holder = new wxBoxSizer(wxVERTICAL);
    TerRestrict_Graphics_Text[0] = new SolidText(Tab_TerrainRestrictions, " Exit Tile Sprite ID");
    TerRestrict_Graphics_Text[1] = new SolidText(Tab_TerrainRestrictions, " Enter Tile Sprite ID");
    TerRestrict_Graphics_Text[2] = new SolidText(Tab_TerrainRestrictions, " Walk Tile Sprite ID");
    for(size_t loop = 0; loop < 3; ++loop)
    {
        TerRestrict_Graphics[loop] = AGETextCtrl::init(CLong, &uiGroupRestriction, this, &popUp, Tab_TerrainRestrictions, AGETextCtrl::LARGE);
        TerRestrict_Graphics_ComboBox[loop] = new ComboBox_Plus1(Tab_TerrainRestrictions, TerRestrict_Graphics[loop], &graphic_names);
        GraphicComboBoxList.push_back(TerRestrict_Graphics_ComboBox[loop]);
    }
    TerRestrict_Amount_Text = new SolidText(Tab_TerrainRestrictions, " Walk Sprite Rate");
    TerRestrict_Amount = AGETextCtrl::init(CFloat, &uiGroupRestriction, this, &popUp, Tab_TerrainRestrictions);

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

    TerRestrict_TerRestrict_Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTerrainRestrictionsSearch, this);
    TerRestrict_TerRestrict_Search_R->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTerrainRestrictionsSearch, this);
    TerRestrict_TerRestrict_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTerrainRestrictionsSelect, this);
    TerRestrict_TerRestrict_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTerrainRestrictionsSelect, this);
    TerRestrict_TerRestrict_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTerrainRestrictionsSelect, this);
    TerRestrict_Terrains_Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTerrainsSearch, this);
    TerRestrict_Terrains_Search_R->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTerrainsSearch, this);
    TerRestrict_Terrains_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTerrainRestrictionsTerrainSelect, this);
    TerRestrict_Terrains_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTerrainRestrictionsTerrainSelect, this);
    TerRestrict_Terrains_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTerrainRestrictionsTerrainSelect, this);
    TerRestrict_Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainRestrictionsAdd, this);
    TerRestrict_Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainRestrictionsInsert, this);
    TerRestrict_Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainRestrictionsDelete, this);
    TerRestrict_Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainRestrictionsCopy, this);
    TerRestrict_Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainRestrictionsPaste, this);
    TerRestrict_PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainRestrictionsPasteInsert, this);
    TerRestrict_Terrains_Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainRestrictionsTerrainCopy, this);
    TerRestrict_Terrains_Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainRestrictionsTerrainPaste, this);

    restrictionTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTerrainRestrictionsTimer, this);
    restrictionTerrainTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTerrainRestrictionsTerrainTimer, this);
    TerRestrict_Accessible->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TerRestrict, this);
}

void AGE_Frame::OnKillFocus_TerRestrict(wxFocusEvent &event)
{
    event.Skip();
    if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
    ListTerrains2();
}
