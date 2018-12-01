#include "../AGE_Frame.h"

wxString AGE_Frame::GetResearchName(int index, bool Filter)
{
    wxString Name;
    if(Filter)
    {
        short Selection[2];
        for(size_t loop = 0; loop < 2; ++loop)
        Selection[loop] = Research_SearchFilters[loop]->GetSelection();

        if(Selection[0] > 1)
        for(size_t loop = 0; loop < 2; ++loop)
        {
            switch(Selection[loop])
            {
                case 2: // Required Techs
                {
                    bool HasFore = false;
                    for(size_t loop = 0; loop < dataset->Techs[index].getRequiredTechsSize(); ++loop)
                    if(dataset->Techs[index].RequiredTechs[loop] != -1)
                    {
                        if(HasFore) Name += ", R"; else {Name += "R"; HasFore = true;}
                        Name += std::to_string(dataset->Techs[index].RequiredTechs[loop]);
                    }
                }   break;
                case 3: // Min. Req. Techs
                    Name += "MR "+std::to_string(dataset->Techs[index].RequiredTechCount);
                    break;
                case 4: // Research Location
                    Name += "RL "+std::to_string(dataset->Techs[index].ResearchLocation);
                    break;
                case 5: // Research Time
                    Name += "RT "+std::to_string(dataset->Techs[index].ResearchTime);
                    break;
                case 6: // Effect
                    Name += "E "+std::to_string(dataset->Techs[index].EffectID);
                    break;
                case 7: // Type
                    Name += "T "+std::to_string(dataset->Techs[index].Type);
                    break;
                case 8: // Icon
                    Name += "I "+std::to_string(dataset->Techs[index].IconID);
                    break;
                case 9: // Button
                    Name += "B "+std::to_string((short)dataset->Techs[index].ButtonID);
                    break;
                case 10: // Lang File Pointer
                    Name += "LH "+std::to_string(dataset->Techs[index].LanguageDLLHelp);
                    break;
                case 11: // Pointer 2
                    Name += "LT "+std::to_string(dataset->Techs[index].LanguageDLLTechTree);
                    break;
                case 12: // Hot Key
                    Name += "HK "+std::to_string(dataset->Techs[index].HotKey);
                    break;
                case 13: // Cost Types
                {
                    bool HasFore = false;
                    for(size_t loop = 0; loop < 3; ++loop)
                    if(dataset->Techs[index].ResourceCosts[loop].Type != -1)
                    {
                        if(HasFore) Name += ", CT"; else {Name += "CT"; HasFore = true;}
                        Name += std::to_string(dataset->Techs[index].ResourceCosts[loop].Type);
                    }
                }   break;
                case 14: // Cost Amounts
                {
                    bool HasFore = false;
                    for(size_t loop = 0; loop < 3; ++loop)
                    {
                        if(HasFore) Name += ", CA"; else {Name += "CA"; HasFore = true;}
                        Name += std::to_string(dataset->Techs[index].ResourceCosts[loop].Amount);
                    }
                }   break;
                case 15: // Cost Uses
                {
                    bool HasFore = false;
                    for(size_t loop = 0; loop < 3; ++loop)
                    {
                        if(HasFore) Name += ", CU"; else {Name += "CU"; HasFore = true;}
                        Name += std::to_string((short)dataset->Techs[index].ResourceCosts[loop].Paid);
                    }
                }   break;
                if(GenieVersion >= genie::GV_AoKB)
                {
                case 16: // Civilization
                    Name += "C "+std::to_string(dataset->Techs[index].Civ);
                    break;
                case 17: // Full Tech Mode
                    Name += "F "+std::to_string(dataset->Techs[index].FullTechMode);
                    break;
                if(GenieVersion >= genie::GV_SWGB)
                {
                case 18: // Internal Name 2
                    if(!dataset->Techs[index].Name2.empty())
                    return Name + dataset->Techs[index].Name2;
                    else goto InternalName;
                }
                }
            }
            Name += ", ";
            if(Selection[1] < 2) break;
        }
        if(Selection[0] == 1) goto InternalName;
    }

    if(!TranslatedText(dataset->Techs[index].LanguageDLLName, 2).empty())
    {
        return Name + TranslatedText(dataset->Techs[index].LanguageDLLName, 64);
    }
InternalName:
    if(!dataset->Techs[index].Name.empty())
    {
        return Name + dataset->Techs[index].Name;
    }
    return Name + "New Tech";
}

void AGE_Frame::OnResearchSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListResearches(false);
}

void AGE_Frame::ListResearches(bool all)
{
    InitResearches(all);
    wxCommandEvent e;
    OnResearchSelect(e);
}

void AGE_Frame::InitResearches(bool all)
{
    InitSearch(Research_Research_Search->GetValue().MakeLower(), Research_Research_Search_R->GetValue().MakeLower());
    SearchAnd = Research_Research_UseAnd[0]->GetValue();
    ExcludeAnd = Research_Research_UseAnd[1]->GetValue();

    Research_Research_ListV->Sweep();
    if(all)
    {
        research_names.Clear();
        research_names.Alloc(1 + dataset->Techs.size());
        research_names.Add("-1 - None");
    }

    for(size_t loop = 0; loop < dataset->Techs.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetResearchName(loop, true);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Research_Research_ListV->names.Add(Name);
            Research_Research_ListV->indexes.push_back(loop);
        }
        if(all) research_names.Add(FormatInt(loop)+" - "+GetResearchName(loop));
    }

    RefreshList(Research_Research_ListV, &ResearchIDs);
    if(all)
    {
        for(auto &list: ResearchComboBoxList) list->Flash();
        if(GenieVersion >= genie::GV_AoKA)
        {
            TechTrees_Ages_Items.ItemCombo->Flash();
            TechTrees_Buildings_Items.ItemCombo->Flash();
            TechTrees_Units_Items.ItemCombo->Flash();
            TechTrees_Researches_Items.ItemCombo->Flash();
        }
    }

    SearchAnd = ExcludeAnd = false;
}

void AGE_Frame::OnResearchSelect(wxCommandEvent &event)
{
    // If trying to select an existing item, don't deselect?
    size_t selections = Research_Research_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Research_Research_ListV, ResearchIDs);

    for(auto &box: uiGroupResearch) box->clear();

    genie::Tech * ResearchPointer = nullptr;
    for(size_t loop = selections; loop--> 0;)
    {
        ResearchPointer = &dataset->Techs[ResearchIDs[loop]];

        for(size_t loop2 = 0; loop2 < ResearchPointer->getRequiredTechsSize(); ++loop2)
        {
            Research_RequiredTechs[loop2]->prepend(&ResearchPointer->RequiredTechs[loop2]);
        }
        Research_RequiredTechCount->prepend(&ResearchPointer->RequiredTechCount);
        Research_Resources[0]->prepend(&ResearchPointer->ResourceCosts[0].Type);
        Research_Resources[1]->prepend(&ResearchPointer->ResourceCosts[1].Type);
        Research_Resources[2]->prepend(&ResearchPointer->ResourceCosts[2].Type);
        Research_Amount[0]->prepend(&ResearchPointer->ResourceCosts[0].Amount);
        Research_Amount[1]->prepend(&ResearchPointer->ResourceCosts[1].Amount);
        Research_Amount[2]->prepend(&ResearchPointer->ResourceCosts[2].Amount);
        Research_Used[0]->prepend(&ResearchPointer->ResourceCosts[0].Paid);
        Research_Used[1]->prepend(&ResearchPointer->ResourceCosts[1].Paid);
        Research_Used[2]->prepend(&ResearchPointer->ResourceCosts[2].Paid);
        if(GenieVersion >= genie::GV_AoKB)
        {
            Research_Civ->prepend(&ResearchPointer->Civ);
            Research_FullTechMode->prepend(&ResearchPointer->FullTechMode);
            if(GenieVersion >= genie::GV_SWGB)
            Research_Name[1]->prepend(&ResearchPointer->Name2);
        }
        Research_ResearchLocation->prepend(&ResearchPointer->ResearchLocation);
        if(GenieVersion >= genie::GV_MATT)
        {
            Research_LangDLLName->prepend(&ResearchPointer->LanguageDLLName);
            Research_LangDLLDescription->prepend(&ResearchPointer->LanguageDLLDescription);
        }
        Research_ResearchTime->prepend(&ResearchPointer->ResearchTime);
        Research_TechID->prepend(&ResearchPointer->EffectID);
        Research_Type->prepend(&ResearchPointer->Type);
        Research_IconID->prepend(&ResearchPointer->IconID);
        Research_ButtonID->prepend(&ResearchPointer->ButtonID);
        if(GenieVersion >= genie::GV_AoEB)
        {
            Research_LanguageDLLHelp->prepend(&ResearchPointer->LanguageDLLHelp);
            Research_LanguageDLLName2->prepend(&ResearchPointer->LanguageDLLTechTree);
            Research_HotKey->prepend(&ResearchPointer->HotKey);
        }
        Research_Name[0]->prepend(&ResearchPointer->Name);
    }
    SetStatusText("Selections: "+std::to_string(selections)+"    Selected technology: "+std::to_string(ResearchIDs.front()), 0);

    if(ResearchPointer && GenieVersion >= genie::GV_MATT)
    {
        Research_DLL_LangDLLName->index = ResearchPointer->LanguageDLLName;
        Research_DLL_LangDLLName->SetLabel(TranslatedText(ResearchPointer->LanguageDLLName, 64));
        Research_DLL_LangDLLDescription->index = ResearchPointer->LanguageDLLDescription;
        Research_DLL_LangDLLDescription->SetLabel(TranslatedText(ResearchPointer->LanguageDLLDescription, 128));
        Research_DLL_HotKey->index = ResearchPointer->HotKey;
        Research_DLL_HotKey->SetLabel(TranslatedText(ResearchPointer->HotKey, 16));
        if(GenieVersion >= genie::GV_AoEB)
        {
            if(GenieVersion < genie::GV_AoKB)
            {
                Research_DLL_LanguageDLLHelp->index = (uint16_t)ResearchPointer->LanguageDLLHelp;
                Research_DLL_LanguageDLLName2->index = (uint16_t)ResearchPointer->LanguageDLLTechTree;
            }
            else
            {
                Research_DLL_LanguageDLLHelp->index = ResearchPointer->LanguageDLLHelp - 79000;
                Research_DLL_LanguageDLLName2->index = ResearchPointer->LanguageDLLTechTree - 140000;
            }
            Research_DLL_LanguageDLLHelp->SetLabel(TranslatedText(Research_DLL_LanguageDLLHelp->index, 512));
            Research_LanguageDLLConverter[0]->SetLabel(std::to_string(Research_DLL_LanguageDLLHelp->index));
            Research_DLL_LanguageDLLName2->SetLabel(TranslatedText(Research_DLL_LanguageDLLName2->index, 64));
            Research_LanguageDLLConverter[1]->SetLabel(std::to_string(Research_DLL_LanguageDLLName2->index));
        }
        if(GenieVersion == genie::GV_CC)
        {
            techSLP.slpID = 53260 + dataset->Civs[UnitCivID].IconSet;
        }
        else if(GenieVersion == genie::GV_SWGB)
        {
            techSLP.slpID = 50689 + dataset->Civs[UnitCivID].IconSet;
        }
        else
        {
            techSLP.slpID = 50729;
        }
        techSLP.frameID = ResearchPointer->IconID; // frame
    }
    else
    {
        techSLP.slpID = -1;
    }
    for(auto &box: uiGroupResearch) box->update();
    Research_IconID_SLP->Refresh();
}

void AGE_Frame::OnDrawTechSLP(wxPaintEvent &event)
{
    wxBufferedPaintDC dc(Research_IconID_SLP);
    dc.Clear();
    if(techSLP.slpID == -1)
    {
        dc.DrawLabel("No tech", wxNullBitmap, wxRect(0, 0, 100, 40));
        return;
    }
    if(techSLP.frameID == -1)
    {
        dc.DrawLabel("No icon", wxNullBitmap, wxRect(0, 0, 100, 40));
        return;
    }
    if(UseDRS && LoadSLP(&techSLP)) FrameToBitmap(&techSLP);
    if(techSLP.image.IsOk())
    dc.DrawBitmap(wxBitmap(techSLP.image, 24), 0, 0, true);
}

void AGE_Frame::OnResearchAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->Techs);
    ListResearches();
}

void AGE_Frame::OnResearchInsert(wxCommandEvent &event)
{
    auto selections = Research_Research_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->Techs, ResearchIDs.front());
    ListResearches();
}

void AGE_Frame::OnResearchDelete(wxCommandEvent &event)
{
    auto selections = Research_Research_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->Techs, ResearchIDs);
    ListResearches();
}

void AGE_Frame::OnResearchCopy(wxCommandEvent &event)
{
    auto selections = Research_Research_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Techs, ResearchIDs, copies.Tech);
    Research_Research_ListV->SetFocus();
}

void AGE_Frame::OnResearchPaste(wxCommandEvent &event)
{
    auto selections = Research_Research_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Techs, ResearchIDs, copies.Tech);
    ListResearches();
}

void AGE_Frame::OnResearchPasteInsert(wxCommandEvent &event)
{
    auto selections = Research_Research_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->Techs, ResearchIDs.front(), copies.Tech);
    ListResearches();
}

void AGE_Frame::ResearchLangDLLConverter(wxCommandEvent &event)
{
    long DLLValue;
    if (!static_cast<wxTextCtrl*>(event.GetEventObject())->GetValue().ToLong(&DLLValue)) {
        wxMessageBox("Incorrect input!");
        return;
    }
    if(event.GetId() == Research_LanguageDLLConverter[0]->GetId())
    {
        if(GenieVersion < genie::GV_AoKA) DLLValue += 0x10000;
        else DLLValue += 79000;
        dataset->Techs[ResearchIDs.front()].LanguageDLLHelp = DLLValue;
    }
    else
    {
        if(GenieVersion < genie::GV_AoKA) DLLValue += 0x20000;
        else DLLValue += 140000;
        dataset->Techs[ResearchIDs.front()].LanguageDLLTechTree = DLLValue;
    }
    wxCommandEvent e;
    OnResearchSelect(e);
}

void AGE_Frame::CreateResearchControls()
{
    Tab_Research = new APanel(TabBar_Main);

    Research_Main = new wxBoxSizer(wxHORIZONTAL);
    Research_Research = new wxStaticBoxSizer(wxVERTICAL, Tab_Research, "Technologies");
    Research_Research_Search = new wxTextCtrl(Tab_Research, wxID_ANY);
    Research_Research_UseAnd[0] = new wxCheckBox(Tab_Research, wxID_ANY, "And");
    Research_Research_Search_R = new wxTextCtrl(Tab_Research, wxID_ANY);
    Research_Research_UseAnd[1] = new wxCheckBox(Tab_Research, wxID_ANY, "And");
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Research_Research_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
        Research_SearchFilters[loop] = new AGEComboBox(Tab_Research, &research_filters);
    }
    Research_Research_ListV = new ProperList(Tab_Research, wxSize(200, 100));
    Research_Research_Buttons = new wxGridSizer(3, 0, 0);
    Research_Add = new wxButton(Tab_Research, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Research_Insert = new wxButton(Tab_Research, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Research_Delete = new wxButton(Tab_Research, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Research_Copy = new wxButton(Tab_Research, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Research_Paste = new wxButton(Tab_Research, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Research_PasteInsert = new wxButton(Tab_Research, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));

    Research_Scroller = new AScrolled(Tab_Research);
    Research_ScrollSpace = new wxBoxSizer(wxVERTICAL);
    Research_Name_Holder[0] = new wxBoxSizer(wxVERTICAL);
    Research_Name_Text[0] = new SolidText(Research_Scroller, " Internal Name");
    Research_Name[0] = AGETextCtrl::init(CString, &uiGroupResearch, this, &popUp, Research_Scroller, lengthiest);
    Research_Name_Holder[1] = new wxBoxSizer(wxVERTICAL);
    Research_Name_Text[1] = new SolidText(Research_Scroller, " Internal Name 2");
    Research_Name[1] = AGETextCtrl::init(CString, &uiGroupResearch, this, &popUp, Research_Scroller, lengthiest);
    Research_LangDLLName_Holder = new wxBoxSizer(wxVERTICAL);
    Research_LangDLLName_Text = new SolidText(Research_Scroller, " Language File Name *");
    Research_LangDLLName = AGETextCtrl::init(CUShort, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_LangDLLName->SetToolTip("Usual Technology File Pattern for The Conquerors\nName: 7000-7999\n"
        "Description: Name +1000\nHelp: Name +100000, in file Name +21000\n"
        "Tech tree: Name +150000, in file Name +10000");
    Research_DLL_LangDLLName = new TextCtrl_DLL(Research_Scroller, wxSize(AGETextCtrl::GIANT, 40));
    Research_LangDLLDescription_Holder = new wxBoxSizer(wxVERTICAL);
    Research_LangDLLDescription_Text = new SolidText(Research_Scroller, " Language File Description");
    Research_LangDLLDescription = AGETextCtrl::init(CUShort, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_DLL_LangDLLDescription = new TextCtrl_DLL(Research_Scroller, wxSize(320, 40));
    Research_HotKey_Holder = new wxBoxSizer(wxVERTICAL);
    Research_HotKey_Text = new SolidText(Research_Scroller, " Hotkey *");
    Research_HotKey = AGETextCtrl::init(CLong, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_HotKey->SetToolTip("Gotta be same as hotkey in units.\nNo idea how this works.");
    Research_DLL_HotKey = new TextCtrl_DLL(Research_Scroller, wxSize(100, 40));

    Research_LanguageDLLHelp_Holder = new wxBoxSizer(wxVERTICAL);
    Research_LanguageDLLName2_Holder = new wxBoxSizer(wxVERTICAL);
    Research_LanguageDLLHelp_Text = new SolidText(Research_Scroller, " Language File Help *");
    Research_LanguageDLLHelp = AGETextCtrl::init(CLong, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_LanguageDLLHelp->SetToolTip("100000 + Language File Name");
    Research_LanguageDLLConverter_Holder[0] = new wxBoxSizer(wxVERTICAL);
    Research_LanguageDLLConverter_Text[0] = new SolidText(Research_Scroller, " Help Converter *");
    Research_LanguageDLLConverter[0] = new wxTextCtrl(Research_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    Research_LanguageDLLConverter[0]->SetToolTip("Language popup text in file\nHit enter to get the correction into dat file");
    Research_DLL_LanguageDLLHelp = new TextCtrl_DLL(Research_Scroller, wxSize(610, 40));
    Research_LanguageDLLName2_Text = new SolidText(Research_Scroller, " Lang File Tech Tree *");
    Research_LanguageDLLName2 = AGETextCtrl::init(CLong, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_LanguageDLLName2->SetToolTip("150000 + Language File Name");
    Research_LanguageDLLConverter_Holder[1] = new wxBoxSizer(wxVERTICAL);
    Research_LanguageDLLConverter_Text[1] = new SolidText(Research_Scroller, " Tech Tree Converter *");
    Research_LanguageDLLConverter[1] = new wxTextCtrl(Research_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    Research_LanguageDLLConverter[1]->SetToolTip("Language help text in file\nHit enter to get the correction into dat file");
    Research_DLL_LanguageDLLName2 = new TextCtrl_DLL(Research_Scroller, wxSize(610, 40));

    Research_RequiredTechArea_Holder = new wxBoxSizer(wxVERTICAL);
    Research_RequiredTechs_Holder = new wxGridSizer(6, 0, 5);
    Research_RequiredTechArea_Text = new SolidText(Research_Scroller, " Required Techs");
    Research_LangDLLArea_Holder = new wxBoxSizer(wxHORIZONTAL);
    Research_Misc2_Holder = new wxBoxSizer(wxHORIZONTAL);
    Research_Misc3_Holder = new wxBoxSizer(wxHORIZONTAL);
    Research_PointerArea_Holder = new wxBoxSizer(wxHORIZONTAL);
    Research_Names_Holder = new wxBoxSizer(wxHORIZONTAL);

    for(size_t loop = 0; loop < 6; ++loop)
    {
        Research_RequiredTechs[loop] = AGETextCtrl::init(CShort, &uiGroupResearch, this, &popUp, Research_Scroller);
        Research_RequiredTechs_ComboBox[loop] = new ComboBox_Plus1(Research_Scroller, Research_RequiredTechs[loop], &research_names, AGETextCtrl::NORMAL);
        ResearchComboBoxList.push_back(Research_RequiredTechs_ComboBox[loop]);
    }
    Research_RequiredTechCount_Holder = new wxBoxSizer(wxVERTICAL);
    Research_RequiredTechCount_Text = new SolidText(Research_Scroller, " Min Req Techs");
    Research_RequiredTechCount = AGETextCtrl::init(CShort, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_Type_Holder = new wxBoxSizer(wxVERTICAL);
    Research_Type_Text = new SolidText(Research_Scroller, " Type *");
    Research_Type = AGETextCtrl::init(CShort, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_Type->SetToolTip("AoK+\n0   Normal\n2   Show progress in age bar.\nAoE/RoR: Used to track similar\ntechnologies for modding purposes,\nwithout actual usage in the game.");
    Research_ResearchTime_Holder = new wxBoxSizer(wxVERTICAL);
    Research_ResearchTime_Text = new SolidText(Research_Scroller, " Research Time");
    Research_ResearchTime = AGETextCtrl::init(CShort, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_IconID_Holder = new wxBoxSizer(wxVERTICAL);
    Research_IconID_Text = new SolidText(Research_Scroller, " Icon");
    Research_IconID = AGETextCtrl::init(CShort, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_IconID_SLP = new APanel(Research_Scroller, wxSize(55, 50));
    Research_ButtonID_Holder = new wxBoxSizer(wxVERTICAL);
    Research_ButtonID_Text = new SolidText(Research_Scroller, " Button");
    Research_ButtonID = AGETextCtrl::init(CByte, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_TechID_Holder = new wxBoxSizer(wxVERTICAL);
    Research_TechID_Text = new SolidText(Research_Scroller, " Effect");
    Research_TechID = AGETextCtrl::init(CShort, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_TechID_ComboBox = new ComboBox_Plus1(Research_Scroller, Research_TechID, &tech_names);
    TechComboBoxList.push_back(Research_TechID_ComboBox);
    Research_ResearchLocation_Holder = new wxBoxSizer(wxVERTICAL);
    Research_ResearchLocation_Text = new SolidText(Research_Scroller, " Research Location");
    Research_ResearchLocation = AGETextCtrl::init(CShort, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_ResearchLocation_ComboBox = new ComboBox_Plus1(Research_Scroller, Research_ResearchLocation, &unit_names);
    UnitComboBoxList.push_back(Research_ResearchLocation_ComboBox);
    Research_Civ_Holder = new wxBoxSizer(wxVERTICAL);
    Research_Civ_Text = new SolidText(Research_Scroller, " Civilization");
    Research_Civ = AGETextCtrl::init(CShort, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_Civ_ComboBox = new ComboBox_Plus1(Research_Scroller, Research_Civ, &civ_names);
    CivComboBoxList.push_back(Research_Civ_ComboBox);
    Research_FullTechMode_Holder = new wxBoxSizer(wxVERTICAL);
    Research_FullTechMode_Text = new SolidText(Research_Scroller, " Full Tech Mode");
    Research_FullTechMode = AGETextCtrl::init(CShort, &uiGroupResearch, this, &popUp, Research_Scroller);
    Research_FullTechMode_CheckBox = new CheckBox_2State(Research_Scroller, "Available", Research_FullTechMode);

    Research_CostHeader_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Research_Scroller, "Costs");
    Research_Cost_Texts = new wxBoxSizer(wxVERTICAL);
    for(auto &sizer: Research_Cost_Sizers)
    sizer = new wxBoxSizer(wxVERTICAL);
    Research_Resources_Text = new SolidText(Research_Scroller, "Type", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Research_Amount_Text = new SolidText(Research_Scroller, "Amount", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Research_Used_Text = new SolidText(Research_Scroller, "Deduct", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    for(size_t loop = 0; loop < 3; ++loop)
    {
        Research_Resources[loop] = AGETextCtrl::init(CShort, &uiGroupResearch, this, &popUp, Research_Scroller);
        Research_Resources_ComboBox[loop] = new ComboBox_Plus1(Research_Scroller, Research_Resources[loop], &resource_names);
        ResourceComboBoxList.push_back(Research_Resources_ComboBox[loop]);
        Research_Amount[loop] = AGETextCtrl::init(CShort, &uiGroupResearch, this, &popUp, Research_Scroller);
        Research_Used[loop] = AGETextCtrl::init(CByte, &uiGroupResearch, this, &popUp, Research_Scroller, AGETextCtrl::SMALL);
        Research_Used_CheckBox[loop] = new CheckBox_2State(Research_Scroller, "Paid", Research_Used[loop]);
    }

    /*Translations.Write("Global/And", langGlobalAnd);
    Translations.Write("Global/Add", langGlobalAdd);
    Translations.Write("Global/InsertNew", langGlobalInsNew);
    Translations.Write("Global/Delete", langGlobalDel);
    Translations.Write("Global/Copy", langGlobalCopy);
    Translations.Write("Global/Paste", langGlobalPaste);
    Translations.Write("Global/InsertCopies", langGlobalInsCopies);
    Translations.Write("Tech/Tab", langTabResearch);
    Translations.Write("Global/Name", langGlobalName);*/

    Research_Research_Buttons->Add(Research_Add, 1, wxEXPAND);
    Research_Research_Buttons->Add(Research_Delete, 1, wxEXPAND);
    Research_Research_Buttons->Add(Research_Insert, 1, wxEXPAND);
    Research_Research_Buttons->Add(Research_Copy, 1, wxEXPAND);
    Research_Research_Buttons->Add(Research_Paste, 1, wxEXPAND);
    Research_Research_Buttons->Add(Research_PasteInsert, 1, wxEXPAND);

    Research_Research_Searches[0]->Add(Research_Research_Search, 1, wxEXPAND);
    Research_Research_Searches[0]->Add(Research_Research_UseAnd[0], 0, wxLEFT, 2);
    Research_Research_Searches[1]->Add(Research_Research_Search_R, 1, wxEXPAND);
    Research_Research_Searches[1]->Add(Research_Research_UseAnd[1], 0, wxLEFT, 2);
    for(size_t loop = 0; loop < 2; ++loop)
    Research_Research->Add(Research_Research_Searches[loop], 0, wxEXPAND);
    for(size_t loop = 0; loop < 2; ++loop)
    Research_Research->Add(Research_SearchFilters[loop], 0, wxEXPAND);
    Research_Research->Add(Research_Research_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Research_Research->Add(Research_Research_Buttons, 0, wxEXPAND);

    for(size_t loop = 0; loop < 2; ++loop)
    {
        Research_Name_Holder[loop]->Add(Research_Name_Text[loop]);
        Research_Name_Holder[loop]->Add(Research_Name[loop]);
    }

    Research_Names_Holder->Add(Research_IconID_SLP);
    Research_Names_Holder->Add(Research_Name_Holder[0], 0, wxLEFT, 5);
    Research_Names_Holder->Add(Research_Name_Holder[1], 0, wxLEFT, 5);

    Research_LangDLLName_Holder->Add(Research_LangDLLName_Text);
    Research_LangDLLName_Holder->Add(Research_LangDLLName, 0, wxEXPAND);
    Research_LangDLLName_Holder->Add(Research_DLL_LangDLLName);
    Research_LangDLLDescription_Holder->Add(Research_LangDLLDescription_Text);
    Research_LangDLLDescription_Holder->Add(Research_LangDLLDescription, 0, wxEXPAND);
    Research_LangDLLDescription_Holder->Add(Research_DLL_LangDLLDescription);

    Research_LangDLLArea_Holder->Add(Research_LangDLLName_Holder);
    Research_LangDLLArea_Holder->Add(Research_LangDLLDescription_Holder, 0, wxLEFT, 5);

    Research_Cost_Texts->Add(Research_Resources_Text);
    Research_Cost_Texts->AddSpacer(35);
    Research_Cost_Texts->Add(Research_Amount_Text);
    Research_Cost_Texts->AddSpacer(15);
    Research_Cost_Texts->Add(Research_Used_Text);
    for(size_t loop = 0; loop < 3; ++loop)
    {
        wxBoxSizer *sizer_cost = new wxBoxSizer(wxHORIZONTAL);
        sizer_cost->Add(Research_Used[loop]);
        sizer_cost->Add(Research_Used_CheckBox[loop], 0, wxLEFT, 5);
        Research_Cost_Sizers[loop]->Add(Research_Resources[loop], 0, wxEXPAND);
        Research_Cost_Sizers[loop]->Add(Research_Resources_ComboBox[loop]);
        Research_Cost_Sizers[loop]->Add(Research_Amount[loop], 0, wxEXPAND | wxTOP, 5);
        Research_Cost_Sizers[loop]->Add(sizer_cost, 0, wxEXPAND | wxTOP, 5);
    }
    Research_CostHeader_Holder->Add(Research_Cost_Texts);
    for(auto &sizer: Research_Cost_Sizers)
    Research_CostHeader_Holder->Add(sizer, 0, wxLEFT, 5);

    for(size_t loop = 0; loop < 6; ++loop)
    Research_RequiredTechs_Holder->Add(Research_RequiredTechs[loop], 0, wxEXPAND);
    for(size_t loop = 0; loop < 6; ++loop)
    Research_RequiredTechs_Holder->Add(Research_RequiredTechs_ComboBox[loop]);

    Research_RequiredTechArea_Holder->Add(Research_RequiredTechArea_Text);
    Research_RequiredTechArea_Holder->Add(Research_RequiredTechs_Holder);

    Research_RequiredTechCount_Holder->Add(Research_RequiredTechCount_Text);
    Research_RequiredTechCount_Holder->Add(Research_RequiredTechCount);

    Research_Civ_Holder->Add(Research_Civ_Text);
    Research_Civ_Holder->Add(Research_Civ, 0, wxEXPAND);
    Research_Civ_Holder->Add(Research_Civ_ComboBox);

    Research_FullTechMode_Holder->Add(Research_FullTechMode_Text);
    Research_FullTechMode_Holder->Add(Research_FullTechMode);
    Research_FullTechMode_Holder->Add(Research_FullTechMode_CheckBox);

    Research_ResearchLocation_Holder->Add(Research_ResearchLocation_Text);
    Research_ResearchLocation_Holder->Add(Research_ResearchLocation, 0, wxEXPAND);
    Research_ResearchLocation_Holder->Add(Research_ResearchLocation_ComboBox);

    Research_ResearchTime_Holder->Add(Research_ResearchTime_Text);
    Research_ResearchTime_Holder->Add(Research_ResearchTime);

    Research_TechID_Holder->Add(Research_TechID_Text);
    Research_TechID_Holder->Add(Research_TechID, 0, wxEXPAND);
    Research_TechID_Holder->Add(Research_TechID_ComboBox);

    Research_Type_Holder->Add(Research_Type_Text);
    Research_Type_Holder->Add(Research_Type);

    Research_IconID_Holder->Add(Research_IconID_Text);
    Research_IconID_Holder->Add(Research_IconID);

    Research_ButtonID_Holder->Add(Research_ButtonID_Text);
    Research_ButtonID_Holder->Add(Research_ButtonID);

    Research_Misc2_Holder->Add(Research_RequiredTechCount_Holder, 0, wxRIGHT, 5);
    Research_Misc2_Holder->Add(Research_Type_Holder, 0, wxRIGHT, 5);
    Research_Misc2_Holder->Add(Research_ResearchTime_Holder, 0, wxRIGHT, 5);
    Research_Misc2_Holder->Add(Research_IconID_Holder, 0, wxRIGHT, 5);
    Research_Misc2_Holder->Add(Research_ButtonID_Holder);

    Research_Misc3_Holder->Add(Research_TechID_Holder, 0, wxRIGHT, 5);
    Research_Misc3_Holder->Add(Research_ResearchLocation_Holder, 0, wxRIGHT, 5);
    Research_Misc3_Holder->Add(Research_Civ_Holder, 0, wxRIGHT, 5);
    Research_Misc3_Holder->Add(Research_FullTechMode_Holder);

    Research_LanguageDLLHelp_Holder->Add(Research_LanguageDLLHelp_Text);
    Research_LanguageDLLHelp_Holder->Add(Research_LanguageDLLHelp, 0, wxEXPAND);
    Research_LanguageDLLConverter_Holder[0]->Add(Research_LanguageDLLConverter_Text[0]);
    Research_LanguageDLLConverter_Holder[0]->Add(Research_LanguageDLLConverter[0]);
    Research_LanguageDLLName2_Holder->Add(Research_LanguageDLLName2_Text);
    Research_LanguageDLLName2_Holder->Add(Research_LanguageDLLName2, 0, wxEXPAND);
    Research_LanguageDLLConverter_Holder[1]->Add(Research_LanguageDLLConverter_Text[1]);
    Research_LanguageDLLConverter_Holder[1]->Add(Research_LanguageDLLConverter[1]);
    Research_HotKey_Holder->Add(Research_HotKey_Text);
    Research_HotKey_Holder->Add(Research_HotKey);
    Research_HotKey_Holder->Add(Research_DLL_HotKey);

    Research_PointerArea_Holder->Add(Research_LanguageDLLHelp_Holder);
    Research_PointerArea_Holder->Add(Research_LanguageDLLConverter_Holder[0], 0, wxLEFT, 5);
    Research_PointerArea_Holder->Add(Research_LanguageDLLName2_Holder, 0, wxLEFT, 5);
    Research_PointerArea_Holder->Add(Research_LanguageDLLConverter_Holder[1], 0, wxLEFT, 5);
    Research_LangDLLArea_Holder->Add(Research_HotKey_Holder, 0, wxLEFT, 5);

    Research_ScrollSpace->Add(Research_Names_Holder);
    Research_ScrollSpace->Add(Research_LangDLLArea_Holder, 0, wxTOP, 5);
    Research_ScrollSpace->Add(Research_PointerArea_Holder, 0, wxTOP | wxBOTTOM, 5);
    Research_ScrollSpace->Add(Research_DLL_LanguageDLLHelp, 0, wxEXPAND);
    Research_ScrollSpace->Add(Research_DLL_LanguageDLLName2, 0, wxEXPAND);
    Research_ScrollSpace->Add(Research_RequiredTechArea_Holder, 0, wxTOP, 5);
    Research_ScrollSpace->Add(Research_Misc2_Holder, 0, wxTOP, 5);
    Research_ScrollSpace->Add(Research_Misc3_Holder, 0, wxTOP, 5);
    Research_ScrollSpace->Add(Research_CostHeader_Holder, 0, wxTOP, 5);

    Research_Scroller->SetSizer(Research_ScrollSpace);
    Research_Scroller->SetScrollRate(0, 15);

    Research_Main->Add(Research_Research, 21, wxEXPAND | wxALL, 5);
    Research_Main->Add(Research_Scroller, 65, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

    Tab_Research->SetSizer(Research_Main);

    Research_Research_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnResearchSearch, this);
    Research_Research_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnResearchSearch, this);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Research_Research_UseAnd[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnResearchSearch, this);
        Research_SearchFilters[loop]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnSelection_SearchFilters, this);
    }
    Research_Research_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnResearchSelect, this);
    Research_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnResearchAdd, this);
    Research_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnResearchInsert, this);
    Research_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnResearchDelete, this);
    Research_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnResearchCopy, this);
    Research_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnResearchPaste, this);
    Research_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnResearchPasteInsert, this);
    Research_LanguageDLLConverter[0]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::ResearchLangDLLConverter, this);
    Research_LanguageDLLConverter[1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::ResearchLangDLLConverter, this);

    Research_LangDLLName->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_LangDLLName->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_LangDLLDescription->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_LangDLLDescription->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_Name[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_Name[0]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_Name[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_Name[1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_LanguageDLLHelp->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_LanguageDLLHelp->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_LanguageDLLName2->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_LanguageDLLName2->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_HotKey->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_HotKey->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_DLL_LangDLLName->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Research_DLL_LangDLLDescription->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Research_DLL_LanguageDLLHelp->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Research_DLL_LanguageDLLName2->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Research_DLL_HotKey->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Research_IconID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_IconID->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_IconID_SLP->Bind(wxEVT_PAINT, &AGE_Frame::OnDrawTechSLP, this);
    Research_IconID_SLP->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&){});
}

void AGE_Frame::OnSaveEdits_Research(int id)
{
    if(id == Research_Name[0]->GetId() || id == Research_LangDLLName->GetId())
    {
        ListResearches();
    }
    else
    {
        wxCommandEvent e;
        OnResearchSelect(e);
    }
}

void AGE_Frame::OnEnter_Research(wxCommandEvent &event)
{
    static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
    OnSaveEdits_Research(event.GetId());
}

void AGE_Frame::OnKillFocus_Research(wxFocusEvent &event)
{
    event.Skip();
    if(static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() != 0) return;
    OnSaveEdits_Research(event.GetId());
}
