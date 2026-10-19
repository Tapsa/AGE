#include "Common.h"
#include "../AGE_Frame.h"

std::vector<std::function<wxString(genie::Tech*)>> TechFilterFunctions;
bool UseTechName;

wxString AGE_Frame::GetResearchName(int index, bool filter)
{
    wxString name;
    if (filter)
    {
        for (auto &f : TechFilterFunctions)
        {
            name += f(&dataset->Techs[index]) + ", ";
        }
    }
    if (UseTechName)
    {
        wxString DynamicName = TranslatedText(dataset->Techs[index].LanguageDLLName, 64);
        if (!DynamicName.empty())
        {
            return name + DynamicName;
        }
    }
    if (!dataset->Techs[index].Name.empty())
    {
        return name + dataset->Techs[index].Name;
    }
    return name + "New Tech";
}

void AGE_Frame::PrepTechSearch()
{
    UseTechName = true;
    TechFilterFunctions.clear();
    for (size_t loop = 0; loop < 2; ++loop)
    {
        int selection = Research_SearchFilters[loop]->GetSelection();
        if (selection < 1) continue;
        wxString label = research_filters[selection];

        if (label.compare("Internal Name") == 0)
        {
            UseTechName = false;
            continue;
        }
        else if (label.compare("Required Techs") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            wxString name;
            bool hasFore = false;
            for (size_t l2 = 0; l2 < tech_ptr->getRequiredTechsSize(); ++l2)
            {
                if (tech_ptr->RequiredTechs[l2] != -1)
                {
                    if (hasFore)
                    {
                        name += ", R";
                    }
                    else
                    {
                        name += "R";
                        hasFore = true;
                    }
                    name += FormatInt(tech_ptr->RequiredTechs[l2]);
                }
            }
            return name.empty() ? "No R" : name;
        });
        else if (label.compare("Min. Req. Techs") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            return "MR " + FormatInt(tech_ptr->RequiredTechCount);
        });
        else if (label.compare("Research Location") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            wxString name = "";
            for (size_t i = 0; i < tech_ptr->ResearchLocations.size(); ++i)
            {
                name += "RL" + FormatInt(tech_ptr->ResearchLocations[i].LocationID) + " ";
            }
            return name;
        });
        else if (label.compare("Research Time") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            wxString name = "";
            for (size_t i = 0; i < tech_ptr->ResearchLocations.size(); ++i)
            {
                name += "RT" + FormatInt(tech_ptr->ResearchLocations[i].QueueTime) + " ";
            }
            return name;
        });
        else if (label.compare("Effect") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            return "E " + FormatInt(tech_ptr->EffectID);
        });
        else if (label.compare("Type") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            return "T " + FormatInt(tech_ptr->Type);
        });
        else if (label.compare("Icon") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            return "I " + FormatInt(tech_ptr->IconID);
        });
        else if (label.compare("Button") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            wxString name = "";
            for (size_t i = 0; i < tech_ptr->ResearchLocations.size(); ++i)
            {
                name += "B" + FormatInt(tech_ptr->ResearchLocations[i].ButtonID) + " ";
            }
            return name;
        });
        else if (label.compare("Lang Help") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            return "LH " + FormatInt(tech_ptr->LanguageDLLHelp);
        });
        else if (label.compare("Lang Tech Tree") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            return "LT " + FormatInt(tech_ptr->LanguageDLLTechTree);
        });
        else if (label.compare("Hotkey") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            wxString name = "";
            for (size_t i = 0; i < tech_ptr->ResearchLocations.size(); ++i)
            {
                name += "HK" + FormatInt(tech_ptr->ResearchLocations[i].HotKeyID) + " ";
            }
            return name;
        });
        else if (label.compare("Cost Types") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            wxString name;
            bool hasFore = false;
            for (size_t l2 = 0; l2 < 3; ++l2)
            {
                if (tech_ptr->ResourceCosts[l2].Type != -1)
                {
                    if (hasFore)
                    {
                        name += ", CT";
                    }
                    else
                    {
                        name += "CT";
                        hasFore = true;
                    }
                    name += FormatInt(tech_ptr->ResourceCosts[l2].Type);
                }
            }
            return name.empty() ? "No CT" : name;
        });
        else if (label.compare("Cost Amounts") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            wxString name;
            bool hasFore = false;
            for (size_t l2 = 0; l2 < 3; ++l2)
            {
                if (hasFore)
                {
                    name += ", CA";
                }
                else
                {
                    name += "CA";
                    hasFore = true;
                }
                name += FormatInt(tech_ptr->ResourceCosts[l2].Amount);
            }
            return name;
        });
        else if (label.compare("Cost Uses") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            wxString name;
            bool hasFore = false;
            for (size_t l2 = 0; l2 < 3; ++l2)
            {
                if (hasFore)
                {
                    name += ", CU";
                }
                else
                {
                    name += "CU";
                    hasFore = true;
                }
                name += FormatInt(tech_ptr->ResourceCosts[l2].Flag);
            }
            return name;
        });
        else if (label.compare("Civilization") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            return "C " + FormatInt(tech_ptr->Civ);
        });
        else if (label.compare("Full Tech Mode") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            return "F " + FormatInt(tech_ptr->FullTechMode);
        });
        else if (label.compare("Internal Name 2") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            return tech_ptr->Name2;
        });
        else if (label.compare("Repeatable") == 0)
            TechFilterFunctions.push_back([this](genie::Tech *tech_ptr)
        {
            return "L " + FormatInt(tech_ptr->Repeatable);
        });
    }
}

void AGE_Frame::OnResearchSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
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
    PrepTechSearch();

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
        for (AGEComboBox *list : ResearchComboBoxList)
        {
            list->Flash();
        }
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

    for (AGETextCtrl *box : uiGroupResearch) box->clear();

    genie::Tech * ResearchPointer = 0;
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
        Research_Used[0]->prepend(&ResearchPointer->ResourceCosts[0].Flag);
        Research_Used[1]->prepend(&ResearchPointer->ResourceCosts[1].Flag);
        Research_Used[2]->prepend(&ResearchPointer->ResourceCosts[2].Flag);
        if(GenieVersion >= genie::GV_AoKB)
        {
            Research_Civ->prepend(&ResearchPointer->Civ);
            Research_FullTechMode->prepend(&ResearchPointer->FullTechMode);
            if(GenieVersion >= genie::GV_SWGB)
            Research_Name[1]->prepend(&ResearchPointer->Name2);
            if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
            Techs_Repeatable->prepend(&ResearchPointer->Repeatable);
        }
        if(GenieVersion >= genie::GV_MATT)
        {
            Research_LangDLLName->prepend(&ResearchPointer->LanguageDLLName);
            Research_LangDLLDescription->prepend(&ResearchPointer->LanguageDLLDescription);
        }
        Research_TechID->prepend(&ResearchPointer->EffectID);
        Research_Type->prepend(&ResearchPointer->Type);
        Research_IconID->prepend(&ResearchPointer->IconID);
        if(GenieVersion >= genie::GV_AoEB)
        {
            Research_LanguageDLLHelp->prepend(&ResearchPointer->LanguageDLLHelp);
            Research_LanguageDLLName2->prepend(&ResearchPointer->LanguageDLLTechTree);
        }
        Research_Name[0]->prepend(&ResearchPointer->Name);
    }

    ListTechResearchLocations();
    SetStatusText(wxString::Format("Selections: %zu    Selected technology: %d",
        selections, selections > 0 ? ResearchIDs.front() : -1), 0);

    if(ResearchPointer && GenieVersion >= genie::GV_MATT)
    {
        Research_DLL_LangDLLName->index = ResearchPointer->LanguageDLLName;
        Research_DLL_LangDLLName->SetLabel(TranslatedText(ResearchPointer->LanguageDLLName, 64));
        Research_DLL_LangDLLDescription->index = ResearchPointer->LanguageDLLDescription;
        Research_DLL_LangDLLDescription->SetLabel(TranslatedText(ResearchPointer->LanguageDLLDescription, 128));
        Research_DLL_HotKey->index = ResearchPointer->ResearchLocations.front().HotKeyID;
        Research_DLL_HotKey->SetLabel(TranslatedText(Research_DLL_HotKey->index, 16));
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
            Research_LanguageDLLConverter[0]->SetLabel(lexical_cast<std::string>(Research_DLL_LanguageDLLHelp->index));
            Research_DLL_LanguageDLLName2->SetLabel(TranslatedText(Research_DLL_LanguageDLLName2->index, 64));
            Research_LanguageDLLConverter[1]->SetLabel(lexical_cast<std::string>(Research_DLL_LanguageDLLName2->index));
        }
        if(GenieVersion >= genie::GV_CC)
        {
            techSLP.slpID = swgbOffsets.icon_tech + dataset->Civs[UnitCivID].IconSet;
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
    for (AGETextCtrl *box : uiGroupResearch) box->update();
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
    if(techSLP.bitmap.IsOk())
    dc.DrawBitmap(techSLP.bitmap, 0, 0, true);
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
    size_t selections = Research_Research_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->Techs, ResearchIDs.front());
    ListResearches();
}

void AGE_Frame::OnResearchDelete(wxCommandEvent &event)
{
    size_t selections = Research_Research_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->Techs, ResearchIDs);
    ListResearches();
}

void AGE_Frame::OnResearchCopy(wxCommandEvent &event)
{
    size_t selections = Research_Research_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Techs, ResearchIDs, copies.Tech);
    Research_Research_ListV->SetFocus();
}

void AGE_Frame::OnResearchPaste(wxCommandEvent &event)
{
    size_t selections = Research_Research_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Techs, ResearchIDs, copies.Tech);
    ListResearches();
}

void AGE_Frame::OnResearchPasteInsert(wxCommandEvent &event)
{
    size_t selections = Research_Research_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->Techs, ResearchIDs.front(), copies.Tech);
    ListResearches();
}

void AGE_Frame::ResearchLangDLLConverter(wxCommandEvent &event)
{
    int32_t DLLValue;
    try
    {
        DLLValue = lexical_cast<int32_t>(static_cast<wxTextCtrl*>(event.GetEventObject())->GetValue());
    }
    catch(const bad_lexical_cast&)
    {
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
    Tab_Research = new ATabPage(TabBar_Main);

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
    Research_Research_ListV = new ProperList(Tab_Research, ASize(200, 100));
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
    Research_Name[0] = new StringControl(Research_Scroller,  this, &uiGroupResearch, maxStringlength, false);
    Research_Name_Holder[1] = new wxBoxSizer(wxVERTICAL);
    Research_Name_Text[1] = new SolidText(Research_Scroller, " Internal Name 2");
    Research_Name[1] = new StringControl(Research_Scroller,  this, &uiGroupResearch, maxStringlength, false);
    Research_LangDLLName_Holder = new wxBoxSizer(wxVERTICAL);
    Research_LangDLLName_Text = new SolidText(Research_Scroller, " Language File Name *");
    Research_LangDLLName = new NumberControl(CShort, Research_Scroller, this, &uiGroupResearch, false);
    Research_LangDLLName->SetToolTip("Usual Technology File Pattern for The Conquerors\nName: 7000-7999\n"
        "Description: Name +1000\nHelp: Name +100000, in file Name +21000\n"
        "Tech tree: Name +150000, in file Name +10000");
    Research_DLL_LangDLLName = new TextIndexControl(Research_Scroller, ASize(200, 40));
    Research_LangDLLDescription_Holder = new wxBoxSizer(wxVERTICAL);
    Research_LangDLLDescription_Text = new SolidText(Research_Scroller, " Language File Description");
    Research_LangDLLDescription = new NumberControl(CShort, Research_Scroller, this, &uiGroupResearch, false);
    Research_DLL_LangDLLDescription = new TextIndexControl(Research_Scroller, ASize(320, 40));
    Research_DLL_HotKey = new TextIndexControl(Research_Scroller, ASize(100, 40));

    Research_LanguageDLLHelp_Holder = new wxBoxSizer(wxVERTICAL);
    Research_LanguageDLLName2_Holder = new wxBoxSizer(wxVERTICAL);
    Research_LanguageDLLHelp_Text = new SolidText(Research_Scroller, " Language File Help *");
    Research_LanguageDLLHelp = new NumberControl(CLong, Research_Scroller, this, &uiGroupResearch, false);
    Research_LanguageDLLHelp->SetToolTip("100000 + Language File Name");
    Research_LanguageDLLConverter_Holder[0] = new wxBoxSizer(wxVERTICAL);
    Research_LanguageDLLConverter_Text[0] = new SolidText(Research_Scroller, " Help Converter *");
    Research_LanguageDLLConverter[0] = new wxTextCtrl(Research_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    Research_LanguageDLLConverter[0]->SetToolTip("Language popup text in file\nHit enter to get the correction into dat file");
    Research_DLL_LanguageDLLHelp = new TextIndexControl(Research_Scroller, ASize(610, 40));
    Research_LanguageDLLName2_Text = new SolidText(Research_Scroller, " Lang File Tech Tree *");
    Research_LanguageDLLName2 = new NumberControl(CLong, Research_Scroller, this, &uiGroupResearch, false);
    Research_LanguageDLLName2->SetToolTip("150000 + Language File Name");
    Research_LanguageDLLConverter_Holder[1] = new wxBoxSizer(wxVERTICAL);
    Research_LanguageDLLConverter_Text[1] = new SolidText(Research_Scroller, " Tech Tree Converter *");
    Research_LanguageDLLConverter[1] = new wxTextCtrl(Research_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    Research_LanguageDLLConverter[1]->SetToolTip("Language help text in file\nHit enter to get the correction into dat file");
    Research_DLL_LanguageDLLName2 = new TextIndexControl(Research_Scroller, ASize(610, 40));

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
        Research_RequiredTechs[loop] = new NumberControl(CShort, Research_Scroller, this, &uiGroupResearch);
        Research_RequiredTechs_ComboBox[loop] = new LinkedComboBox(Research_Scroller, Research_RequiredTechs[loop], &research_names, true, AGETextCtrl::NORMAL);
        ResearchComboBoxList.push_back(Research_RequiredTechs_ComboBox[loop]);
    }
    Research_RequiredTechCount_Holder = new wxBoxSizer(wxVERTICAL);
    Research_RequiredTechCount_Text = new SolidText(Research_Scroller, " Min Req Techs");
    Research_RequiredTechCount = new NumberControl(CShort, Research_Scroller, this, &uiGroupResearch);
    Research_Type_Holder = new wxBoxSizer(wxVERTICAL);
    Research_Type_Text = new SolidText(Research_Scroller, " Type *");
    Research_Type = new NumberControl(CShort, Research_Scroller, this, &uiGroupResearch);
    Research_Type->SetToolTip("AoK+\n0   Normal\n2   Show progress in age bar.\nAoE/RoR: Used to track similar\ntechnologies for modding purposes,\nwithout actual usage in the game.");
    Research_IconID_Holder = new wxBoxSizer(wxVERTICAL);
    Research_IconID_Text = new SolidText(Research_Scroller, " Icon");
    Research_IconID = new NumberControl(CShort, Research_Scroller, this, &uiGroupResearch, false);
    Research_IconID_SLP = new APanel(Research_Scroller, ASize(55, 50));
    Techs_Repeatable_Holder = new wxBoxSizer(wxVERTICAL);
    Techs_Repeatable_Text = new SolidText(Research_Scroller, " Repeatable");
    Techs_Repeatable = new NumberControl(CUByte, Research_Scroller, this, &uiGroupResearch);
    Research_TechID_Holder = new wxBoxSizer(wxVERTICAL);
    Research_TechID_Text = new SolidText(Research_Scroller, " Effect");
    Research_TechID = new NumberControl(CShort, Research_Scroller, this, &uiGroupResearch);
    Research_TechID_ComboBox = new LinkedComboBox(Research_Scroller, Research_TechID, &tech_names);
    TechComboBoxList.push_back(Research_TechID_ComboBox);
    Research_Civ_Holder = new wxBoxSizer(wxVERTICAL);
    Research_Civ_Text = new SolidText(Research_Scroller, " Civilization");
    Research_Civ = new NumberControl(CShort, Research_Scroller, this, &uiGroupResearch);
    Research_Civ_ComboBox = new LinkedComboBox(Research_Scroller, Research_Civ, &civ_names);
    CivComboBoxList.push_back(Research_Civ_ComboBox);
    Research_FullTechMode_Holder = new wxBoxSizer(wxVERTICAL);
    Research_FullTechMode_Text = new SolidText(Research_Scroller, " Full Tech Mode");
    Research_FullTechMode = new NumberControl(CShort, Research_Scroller, this, &uiGroupResearch);
    Research_FullTechMode_CheckBox = new LinkedCheckBox(Research_Scroller, "Available", Research_FullTechMode);

    Research_CostHeader_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Research_Scroller, "Costs");
    Research_Cost_Texts = new wxBoxSizer(wxVERTICAL);
    for (wxBoxSizer *&sizer : Research_Cost_Sizers)
    sizer = new wxBoxSizer(wxVERTICAL);
    Research_Resources_Text = new SolidText(Research_Scroller, "Type", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Research_Amount_Text = new SolidText(Research_Scroller, "Amount", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Research_Used_Text = new SolidText(Research_Scroller, "Deduct", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    for(size_t loop = 0; loop < 3; ++loop)
    {
        Research_Resources[loop] = new NumberControl(CShort, Research_Scroller, this, &uiGroupResearch);
        Research_Resources_ComboBox[loop] = new LinkedComboBox(Research_Scroller, Research_Resources[loop], &resource_names);
        ResourceComboBoxList.push_back(Research_Resources_ComboBox[loop]);
        Research_Amount[loop] = new NumberControl(CShort, Research_Scroller, this, &uiGroupResearch);
        Research_Used[loop] = new NumberControl(CUByte, Research_Scroller, this, &uiGroupResearch, true, AGETextCtrl::SMALL);
        Research_Used_CheckBox[loop] = new LinkedCheckBox(Research_Scroller, "Paid", Research_Used[loop]);
    }

    Research_ResearchLocations =
        new wxStaticBoxSizer(wxHORIZONTAL, Research_Scroller, "Research Locations");
    Research_ResearchLocations_ListArea = new wxBoxSizer(wxVERTICAL);
    Research_ResearchLocations_DataArea = new wxBoxSizer(wxVERTICAL);
    Research_ResearchLocations_Search = new wxTextCtrl(Research_Scroller, wxID_ANY);
    Research_ResearchLocations_Search_R = new wxTextCtrl(Research_Scroller, wxID_ANY);
    Research_ResearchLocations_ListV = new ProperList(Research_Scroller, ASize(300, 100));
    Research_ResearchLocations_Buttons = new wxGridSizer(3, 0, 0);
    Research_ResearchLocations_Add = new wxButton(Research_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Research_ResearchLocations_Insert = new wxButton(
        Research_Scroller, wxID_ANY, "Ins New", wxDefaultPosition, wxSize(10, -1));
    Research_ResearchLocations_Delete = new wxButton(
        Research_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Research_ResearchLocations_Copy = new wxButton(Research_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Research_ResearchLocations_Paste = new wxButton(
        Research_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Research_ResearchLocations_PasteInsert =
        new wxButton(Research_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition,
            wxSize(10, -1));
    Research_ResearchLocations_CopyToTechs =
        new wxButton(Research_Scroller, wxID_ANY, "Copy all to selected techs",
            wxDefaultPosition, wxSize(10, -1));

    ResearchLocations_UnitID_Holder = new wxBoxSizer(wxVERTICAL);
    ResearchLocations_UnitID_Text = new SolidText(Research_Scroller, " Location");
    ResearchLocations_UnitID = new NumberControl(CShort, Research_Scroller, this, nullptr, false);
    ResearchLocations_UnitID_ComboBox = new LinkedComboBox(Research_Scroller, ResearchLocations_UnitID, &unit_names, false);
    ResearchComboBoxList.push_back(ResearchLocations_UnitID_ComboBox);

    ResearchLocations_ResearchTime_Holder = new wxBoxSizer(wxVERTICAL);
    ResearchLocations_ResearchTime_Text = new SolidText(Research_Scroller, " Research Time");
    ResearchLocations_ResearchTime = new NumberControl(CShort, Research_Scroller, this, nullptr, false);

    ResearchLocations_ButtonID_Holder = new wxBoxSizer(wxVERTICAL);
    ResearchLocations_ButtonID_Text = new SolidText(Research_Scroller, " Button");
    ResearchLocations_ButtonID = new NumberControl(CUByte, Research_Scroller, this, nullptr, false);

    ResearchLocations_HotkeyID_Holder = new wxBoxSizer(wxVERTICAL);
    ResearchLocations_HotkeyID_Text = new SolidText(Research_Scroller, " Hotkey *");
    ResearchLocations_HotkeyID = new NumberControl(CLong, Research_Scroller, this, nullptr, false);
    ResearchLocations_HotkeyID->SetToolTip("Gotta be same as hotkey in units.\nNo idea how this works");

    Research_ResearchLocations_Buttons->Add(Research_ResearchLocations_Add, 1, wxEXPAND);
    Research_ResearchLocations_Buttons->Add(Research_ResearchLocations_Delete, 1, wxEXPAND);
    Research_ResearchLocations_Buttons->Add(Research_ResearchLocations_Insert, 1, wxEXPAND);
    Research_ResearchLocations_Buttons->Add(Research_ResearchLocations_Copy, 1, wxEXPAND);
    Research_ResearchLocations_Buttons->Add(Research_ResearchLocations_Paste, 1, wxEXPAND);
    Research_ResearchLocations_Buttons->Add(Research_ResearchLocations_PasteInsert, 1, wxEXPAND);

    Research_ResearchLocations_ListArea->Add(Research_ResearchLocations_Search, 0, wxEXPAND);
    Research_ResearchLocations_ListArea->Add(Research_ResearchLocations_Search_R, 0, wxEXPAND);
    Research_ResearchLocations_ListArea->Add(Research_ResearchLocations_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Research_ResearchLocations_ListArea->Add(Research_ResearchLocations_Buttons, 0, wxEXPAND);
    Research_ResearchLocations_ListArea->Add(Research_ResearchLocations_CopyToTechs, 0, wxEXPAND | wxTOP, 2);

    ResearchLocations_UnitID_Holder->Add(ResearchLocations_UnitID_Text);
    ResearchLocations_UnitID_Holder->Add(ResearchLocations_UnitID, 0, wxEXPAND);
    ResearchLocations_UnitID_Holder->Add(ResearchLocations_UnitID_ComboBox);

    ResearchLocations_ResearchTime_Holder->Add(ResearchLocations_ResearchTime_Text);
    ResearchLocations_ResearchTime_Holder->Add(ResearchLocations_ResearchTime);

    ResearchLocations_ButtonID_Holder->Add(ResearchLocations_ButtonID_Text);
    ResearchLocations_ButtonID_Holder->Add(ResearchLocations_ButtonID);
    ResearchLocations_HotkeyID_Holder->Add(ResearchLocations_HotkeyID_Text);
    ResearchLocations_HotkeyID_Holder->Add(ResearchLocations_HotkeyID);
    ResearchLocations_HotkeyID_Holder->Add(Research_DLL_HotKey);

    Research_ResearchLocations_DataArea->Add(ResearchLocations_UnitID_Holder);
    Research_ResearchLocations_DataArea->Add(ResearchLocations_ResearchTime_Holder, 0, wxTOP, 5);
    Research_ResearchLocations_DataArea->Add(ResearchLocations_ButtonID_Holder, 0, wxTOP, 5);
    Research_ResearchLocations_DataArea->Add(ResearchLocations_HotkeyID_Holder, 0, wxTOP, 5);

    Research_ResearchLocations->Add(Research_ResearchLocations_ListArea, 1, wxEXPAND);
    Research_ResearchLocations->Add(Research_ResearchLocations_DataArea, 1, wxLEFT, 5);

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
    for (wxBoxSizer *&sizer : Research_Cost_Sizers)
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

    Research_TechID_Holder->Add(Research_TechID_Text);
    Research_TechID_Holder->Add(Research_TechID, 0, wxEXPAND);
    Research_TechID_Holder->Add(Research_TechID_ComboBox);

    Research_Type_Holder->Add(Research_Type_Text);
    Research_Type_Holder->Add(Research_Type);

    Research_IconID_Holder->Add(Research_IconID_Text);
    Research_IconID_Holder->Add(Research_IconID);

    Techs_Repeatable_Holder->Add(Techs_Repeatable_Text);
    Techs_Repeatable_Holder->Add(Techs_Repeatable);

    Research_Misc2_Holder->Add(Research_RequiredTechCount_Holder);
    Research_Misc2_Holder->Add(Research_Type_Holder, 0, wxLEFT, 5);
    Research_Misc2_Holder->Add(Research_IconID_Holder, 0, wxLEFT, 5);
    Research_Misc2_Holder->Add(Techs_Repeatable_Holder, 0, wxLEFT, 5);

    Research_Misc3_Holder->Add(Research_TechID_Holder);
    Research_Misc3_Holder->Add(Research_Civ_Holder, 0, wxLEFT, 5);
    Research_Misc3_Holder->Add(Research_FullTechMode_Holder, 0, wxLEFT, 5);

    Research_LanguageDLLHelp_Holder->Add(Research_LanguageDLLHelp_Text);
    Research_LanguageDLLHelp_Holder->Add(Research_LanguageDLLHelp, 0, wxEXPAND);
    Research_LanguageDLLConverter_Holder[0]->Add(Research_LanguageDLLConverter_Text[0]);
    Research_LanguageDLLConverter_Holder[0]->Add(Research_LanguageDLLConverter[0]);
    Research_LanguageDLLName2_Holder->Add(Research_LanguageDLLName2_Text);
    Research_LanguageDLLName2_Holder->Add(Research_LanguageDLLName2, 0, wxEXPAND);
    Research_LanguageDLLConverter_Holder[1]->Add(Research_LanguageDLLConverter_Text[1]);
    Research_LanguageDLLConverter_Holder[1]->Add(Research_LanguageDLLConverter[1]);

    Research_PointerArea_Holder->Add(Research_LanguageDLLHelp_Holder);
    Research_PointerArea_Holder->Add(Research_LanguageDLLConverter_Holder[0], 0, wxLEFT, 5);
    Research_PointerArea_Holder->Add(Research_LanguageDLLName2_Holder, 0, wxLEFT, 5);
    Research_PointerArea_Holder->Add(Research_LanguageDLLConverter_Holder[1], 0, wxLEFT, 5);

    Research_ScrollSpace->Add(Research_Names_Holder);
    Research_ScrollSpace->Add(Research_LangDLLArea_Holder, 0, wxTOP, 5);
    Research_ScrollSpace->Add(Research_PointerArea_Holder, 0, wxTOP | wxBOTTOM, 5);
    Research_ScrollSpace->Add(Research_DLL_LanguageDLLHelp, 0, wxEXPAND);
    Research_ScrollSpace->Add(Research_DLL_LanguageDLLName2, 0, wxEXPAND);
    Research_ScrollSpace->Add(Research_RequiredTechArea_Holder, 0, wxTOP, 5);
    Research_ScrollSpace->Add(Research_Misc2_Holder, 0, wxTOP, 5);
    Research_ScrollSpace->Add(Research_Misc3_Holder, 0, wxTOP, 5);
    Research_ScrollSpace->Add(Research_CostHeader_Holder, 0, wxTOP, 5);
    Research_ScrollSpace->Add(Research_ResearchLocations, 0, wxTOP, 5);

    Research_Scroller->SetSizer(Research_ScrollSpace);

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

    auto TrySaveThenListResearches = [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListResearches();
        }
    };
    auto SaveThenListResearches = [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListResearches();
    };
    Research_LangDLLName->Bind(wxEVT_KILL_FOCUS, TrySaveThenListResearches);
    Research_LangDLLName->Bind(wxEVT_TEXT_ENTER, SaveThenListResearches);
    Research_LangDLLDescription->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_LangDLLDescription->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_Name[0]->Bind(wxEVT_KILL_FOCUS, TrySaveThenListResearches);
    Research_Name[0]->Bind(wxEVT_TEXT_ENTER, SaveThenListResearches);
    Research_Name[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_Name[1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_LanguageDLLHelp->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_LanguageDLLHelp->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_LanguageDLLName2->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_LanguageDLLName2->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_DLL_LangDLLName->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Research_DLL_LangDLLDescription->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Research_DLL_LanguageDLLHelp->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Research_DLL_LanguageDLLName2->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Research_DLL_HotKey->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Research_IconID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Research, this);
    Research_IconID->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Research, this);
    Research_IconID_SLP->Bind(wxEVT_PAINT, &AGE_Frame::OnDrawTechSLP, this);
    Research_IconID_SLP->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent &) {});

    Research_ResearchLocations_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnTechResearchLocationsSearch, this);
    Research_ResearchLocations_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnTechResearchLocationsSearch, this);
    Research_ResearchLocations_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnTechResearchLocationSelect, this);
    Research_ResearchLocations_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnTechResearchLocationsAdd, this);
    Research_ResearchLocations_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnTechResearchLocationsInsert, this);
    Research_ResearchLocations_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnTechResearchLocationsDelete, this);
    Research_ResearchLocations_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnTechResearchLocationsCopy, this);
    Research_ResearchLocations_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnTechResearchLocationsPaste, this);
    Research_ResearchLocations_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnTechResearchLocationsPasteInsert, this);
    Research_ResearchLocations_CopyToTechs->Bind(wxEVT_BUTTON, &AGE_Frame::OnTechResearchLocationsCopyToTechs, this);

    ResearchLocations_UnitID->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent &event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListTechResearchLocations();
        }
    });
    ResearchLocations_UnitID->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent &event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListTechResearchLocations();
    });
    ResearchLocations_UnitID_ComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent &event)
    {
        static_cast<LinkedComboBox*>(event.GetEventObject())->OnChoose(event);
        ListTechResearchLocations();
    });
    ResearchLocations_ResearchTime->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent &event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListTechResearchLocations();
        }
    });
    ResearchLocations_ResearchTime->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent &event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListTechResearchLocations();
    });
    ResearchLocations_ButtonID->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent &event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListTechResearchLocations();
        }
    });
    ResearchLocations_ButtonID->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent &event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListTechResearchLocations();
    });
    ResearchLocations_HotkeyID->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent &event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListTechResearchLocations();
        }
    });
    ResearchLocations_HotkeyID->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent &event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListTechResearchLocations();
    });
}

void AGE_Frame::OnEnter_Research(wxCommandEvent &event)
{
    static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
    wxCommandEvent e;
    OnResearchSelect(e);
}

void AGE_Frame::OnKillFocus_Research(wxFocusEvent &event)
{
    event.Skip();
    if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
    {
        wxCommandEvent e;
        OnResearchSelect(e);
    }
}

wxString AGE_Frame::GetTechResearchLocationName(int index)
{
    return "Unit: " + lexical_cast<std::string>(dataset->Techs[ResearchIDs.front()].ResearchLocations[index].LocationID)
        + " - Time: " + lexical_cast<std::string>(dataset->Techs[ResearchIDs.front()].ResearchLocations[index].QueueTime)
        + " - Button: " + lexical_cast<std::string>(static_cast<short>(dataset->Techs[ResearchIDs.front()].ResearchLocations[index].ButtonID))
        + " - Hotkey: " + lexical_cast<std::string>(dataset->Techs[ResearchIDs.front()].ResearchLocations[index].HotKeyID);
}

void AGE_Frame::OnTechResearchLocationsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListTechResearchLocations();
}

void AGE_Frame::ListTechResearchLocations()
{
    InitSearch(Research_ResearchLocations_Search->GetValue().MakeLower(), Research_ResearchLocations_Search_R->GetValue().MakeLower());

    Research_ResearchLocations_ListV->Sweep();

    if (Techs_ListV->GetSelectedCount())
    {
        Research_ResearchLocations_Add->Enable(true);
        for (size_t loop = 0; loop < dataset->Techs[ResearchIDs.front()].ResearchLocations.size(); ++loop)
        {
            wxString Name = FormatInt(loop) + " - " + GetTechResearchLocationName(loop);
            if (SearchMatches(" " + Name.Lower() + " "))
            {
                Research_ResearchLocations_ListV->names.Add(Name);
                Research_ResearchLocations_ListV->indexes.push_back(loop);
            }
        }
    }
    else
    {
        Research_ResearchLocations_Add->Enable(false);
    }
    RefreshList(Research_ResearchLocations_ListV, &ResearchLocationIDs);

    wxCommandEvent e;
    OnTechResearchLocationSelect(e);
}

void AGE_Frame::OnTechResearchLocationSelect(wxCommandEvent &event)
{
    size_t selections = Research_ResearchLocations_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;

    ResearchLocations_UnitID->clear();
    ResearchLocations_ResearchTime->clear();
    ResearchLocations_ButtonID->clear();
    ResearchLocations_HotkeyID->clear();

    if (selections > 0)
    {
        getSelectedItems(selections, Research_ResearchLocations_ListV, ResearchLocationIDs);

        genie::ResearchLocation *ResearchLocationPointer;
        for (size_t sel = selections; sel-- > 0;)
        {
            ResearchLocationPointer = &dataset->Techs[ResearchIDs.front()].ResearchLocations[ResearchLocationIDs[sel]];

            ResearchLocations_UnitID->prepend(&ResearchLocationPointer->LocationID);
            ResearchLocations_ResearchTime->prepend(&ResearchLocationPointer->QueueTime);
            ResearchLocations_ButtonID->prepend(&ResearchLocationPointer->ButtonID);
            ResearchLocations_HotkeyID->prepend(&ResearchLocationPointer->HotKeyID);
        }
    }

    ResearchLocations_UnitID->update();
    ResearchLocations_ResearchTime->update();
    ResearchLocations_ButtonID->update();
    ResearchLocations_HotkeyID->update();
}

void AGE_Frame::OnTechResearchLocationsAdd(wxCommandEvent &event)
{
    if (!Techs_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::ResearchLocation Temp;
    Temp.setGameVersion(GenieVersion);
    dataset->Techs[ResearchIDs.front()].ResearchLocations.push_back(Temp);
    How2List = ListMode::ADD;
    ListTechResearchLocations();
}

void AGE_Frame::OnTechResearchLocationsInsert(wxCommandEvent &event)
{
    if (!Research_ResearchLocations_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::ResearchLocation Temp;
    Temp.setGameVersion(GenieVersion);
    dataset->Techs[ResearchIDs.front()].ResearchLocations.insert(dataset->Techs[ResearchIDs.front()].ResearchLocations.begin() + ResearchLocationIDs.front(), Temp);
    How2List = ListMode::INSNEW;
    ListTechResearchLocations();
}

void AGE_Frame::OnTechResearchLocationsDelete(wxCommandEvent &event)
{
    size_t selections = Research_ResearchLocations_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;

    if (dataset->Techs[ResearchIDs.front()].ResearchLocations.size())
    {
        DeleteFromList(dataset->Techs[ResearchIDs.front()].ResearchLocations, ResearchLocationIDs);
    }

    ListTechResearchLocations();
}

void AGE_Frame::OnTechResearchLocationsCopy(wxCommandEvent &event)
{
    if (!Research_ResearchLocations_ListV->GetSelectedCount()) return;

    CopyFromList(dataset->Techs[ResearchIDs.front()].ResearchLocations, ResearchLocationIDs, copies.ResearchLocations);

    Research_ResearchLocations_ListV->SetFocus();
}

void AGE_Frame::OnTechResearchLocationsPaste(wxCommandEvent &event)
{
    if (!Research_ResearchLocations_ListV->GetSelectedCount()) return;

    PasteToList(dataset->Techs[ResearchIDs.front()].ResearchLocations, ResearchLocationIDs, copies.ResearchLocations);

    ListTechResearchLocations();
}

void AGE_Frame::OnTechResearchLocationsPasteInsert(wxCommandEvent &event)
{
    if (!Research_ResearchLocations_ListV->GetSelectedCount()) return;

    PasteInsertToList(dataset->Techs[ResearchIDs.front()].ResearchLocations, ResearchLocationIDs.front(), copies.ResearchLocations);

    ListTechResearchLocations();
}

void AGE_Frame::OnTechResearchLocationsCopyToTechs(wxCommandEvent &event)
{
    for (size_t loop = 1; loop < ResearchIDs.size(); ++loop)
    {
        dataset->Techs[ResearchIDs[loop]].ResearchLocations = dataset->Techs[ResearchIDs.front()].ResearchLocations;
    }
}
