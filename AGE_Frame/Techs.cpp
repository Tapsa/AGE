#include "Common.h"
#include "../AGE_Frame.h"
#include "../EditableVersion.h"

wxString AGE_Frame::GetEffectName(int index)
{
    if(!dataset->Effects[index].Name.empty())
        return dataset->Effects[index].Name;
    return "New Effect";
}

void AGE_Frame::OnEffectRenameGE2(wxCommandEvent &event)
{
    if (!dataset) return;

    for (genie::Effect &tech : dataset->Effects)
    {
        tech.Name = "Effect";
    }
    ListEffects();
}

void AGE_Frame::OnEffectRename(wxCommandEvent &event)
{
    if(!dataset) return;

    for (genie::Effect &tech : dataset->Effects)
    {
        if(tech.EffectCommands.size()) // Other than empty techs, not researches if research loop doesn't rename them.
        {
            tech.Name = "Non-Tech";
        }
        else // Empty techs.
        {
            tech.Name = "New Effect";
        }
    }
    short ResearchTechID = 0;
    for(size_t loop=dataset->Techs.size(); loop--> 0;) // Rename of techs. Make it reverse loop.
    {
        ResearchTechID = dataset->Techs[loop].EffectID;
        if(ResearchTechID >= 0) // Only researches which have techs.
        {
            wxString DynamicName = TranslatedText(dataset->Techs[loop].LanguageDLLName, 31);
            if (!DynamicName.empty())
            {
                dataset->Effects[ResearchTechID].Name = DynamicName;
            }
            else // Use internal name instead.
            {
                dataset->Effects[ResearchTechID].Name = dataset->Techs[loop].Name;
            }
        }
    }
    short CivTechTreeID=0, CivTeamBonusID = 0;
    for(size_t loop2=dataset->Civs.size(); loop2--> 0;) // Rename of techs. Make it reverse loop.
    {
        std::string CivName = dataset->Civs[loop2].Name; // Civ internal name.
        CivTechTreeID = dataset->Civs[loop2].TechTreeID;
        CivTeamBonusID = dataset->Civs[loop2].TeamBonusID;
        if(CivTechTreeID >= 0)
        {
            dataset->Effects[CivTechTreeID].Name = CivName+" Tech Tree"; // Under 31 chars.
        }
        if(CivTeamBonusID >= 0)
        {
            dataset->Effects[CivTeamBonusID].Name = CivName+" Team Bonus"; // Under 31 chars.
        }
    }
    ListEffects();
}

void AGE_Frame::OnEffectSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListEffects(false);
}

void AGE_Frame::ListEffects(bool all)
{
    InitTechs(all);
    wxCommandEvent e;
    OnEffectSelect(e);
}

void AGE_Frame::InitTechs(bool all)
{
    InitSearch(Techs_Search->GetValue().MakeLower(), Techs_Search_R->GetValue().MakeLower());
    SearchAnd = Techs_UseAnd[0]->GetValue();
    ExcludeAnd = Techs_UseAnd[1]->GetValue();

    Techs_ListV->Sweep();
    if(all)
    {
        tech_names.Clear();
        tech_names.Alloc(1 + dataset->Effects.size());
        tech_names.Add("-1 - None");
    }

    for(size_t loop = 0; loop < dataset->Effects.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetEffectName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Techs_ListV->names.Add(Name);
            Techs_ListV->indexes.push_back(loop);
        }
        if (all)
        {
            tech_names.Add(Name);
        }
    }

    RefreshList(Techs_ListV, &TechIDs);
    if (all)
    {
        for (AGEComboBox *list : TechComboBoxList)
        {
            list->Flash();
        }
    }

    SearchAnd = ExcludeAnd = false;
}

void AGE_Frame::OnEffectSelect(wxCommandEvent &event)
{
    size_t selections = Techs_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Techs_ListV, TechIDs);

    Techs_Name->clear();

    genie::Effect * TechPointer;
    for(size_t loop = selections; loop--> 0;)
    {
        TechPointer = &dataset->Effects[TechIDs[loop]];
        Techs_Name->prepend(&TechPointer->Name);
    }
    SetStatusText(wxString::Format("Selections: %zu    Selected effect: %d",
        selections, selections > 0 ? TechIDs.front() : -1), 0);

    Techs_Name->update();
    ListEffectCmds();
}

void AGE_Frame::OnEffectAdd(wxCommandEvent &event)    // Works.
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->Effects);
    ListEffects();
}

void AGE_Frame::OnEffectInsert(wxCommandEvent &event) // Works.
{
    size_t selections = Techs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->Effects, TechIDs.front());
    ListEffects();
}

void AGE_Frame::OnEffectDelete(wxCommandEvent &event) // Works.
{
    size_t selections = Techs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->Effects, TechIDs);
    ListEffects();
}

void AGE_Frame::OnEffectCopy(wxCommandEvent &event)   // Works.
{
    size_t selections = Techs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Effects, TechIDs, copies.Effect);
    Techs_ListV->SetFocus();
}

void AGE_Frame::OnEffectPaste(wxCommandEvent &event)  // Works.
{
    size_t selections = Techs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Effects, TechIDs, copies.Effect);
    ListEffects();
}

void AGE_Frame::OnEffectPasteInsert(wxCommandEvent &event)    // Works.
{
    size_t selections = Techs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->Effects, TechIDs.front(), copies.Effect);
    ListEffects();
}

wxString AGE_Frame::Tester(genie::EffectCommand effect, wxString how)
{
    return ((effect.C == 8 || effect.C == 9) ?
        (effect.C == 8 ? "armor type " : "attack type ") +
        (effect.D >= 0 ?
            FormatInt(static_cast<uint16_t>(effect.D) >> 8) + how +
            FormatInt(static_cast<int16_t>(effect.D) & 0xFF) :
            (GameVersion != EV_UP ?
                FormatInt(static_cast<uint16_t>(-effect.D) >> 8) + how +
                FormatInt(-(static_cast<int16_t>(-effect.D) & 0xFF)) :
                FormatInt(static_cast<uint16_t>(effect.D) >> 8) + how +
                FormatInt(static_cast<int16_t>(effect.D) | -256))) :
        "attr " + FormatInt(effect.C) + how + FormatFloat(effect.D)) +
        ((effect.B == -1) ? " for unit " + FormatInt(effect.A) : " for class " + FormatInt(effect.B));
}

wxString AGE_Frame::GetEffectCmdName(int effect, int tech)
{
    wxString Name;
    switch(dataset->Effects[tech].EffectCommands[effect].Type)
    {
        case 40:
            Name = "Gaia ";
            goto AttributeModifierSet;
        case 30:
            Name = "Neutral ";
            goto AttributeModifierSet;
        case 20:
            Name = "Enemy ";
            goto AttributeModifierSet;
        case 10:
            Name = "Team ";
        case 0:
        AttributeModifierSet:
        {
            Name += "Set " + Tester(dataset->Effects[tech].EffectCommands[effect], " to ");
            break;
        }
        case 41:
            Name = "Gaia ";
            goto ResourceModifierSet;
        case 31:
            Name = "Neutral ";
            goto ResourceModifierSet;
        case 21:
            Name = "Enemy ";
            goto ResourceModifierSet;
        case 11:
            Name = "Team ";
        case 1:
        ResourceModifierSet:
            if(dataset->Effects[tech].EffectCommands[effect].B == 0)
            {
                Name += "Set resource "+FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                +" to "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else
            {
                Name += "Change resource "+FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                +" by "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
            {
                if(dataset->Effects[tech].EffectCommands[effect].C >= 0)
                {
                    Name += " times resource "+FormatInt(dataset->Effects[tech].EffectCommands[effect].C);
                }
            }
            break;
        case 42:
            Name = "Gaia ";
            goto DisableEnable;
        case 32:
            Name = "Neutral ";
            goto DisableEnable;
        case 22:
            Name = "Enemy ";
            goto DisableEnable;
        case 12:
            Name = "Team ";
        case 2:
        DisableEnable:
            if(dataset->Effects[tech].EffectCommands[effect].B == 0)
                Name += "Disable";
            else
                Name += "Enable";
            Name += " unit "+FormatInt(dataset->Effects[tech].EffectCommands[effect].A);
            break;
        case 43:
            Name = "Gaia ";
            goto UpgradeUnit;
        case 33:
            Name = "Neutral ";
            goto UpgradeUnit;
        case 23:
            Name = "Enemy ";
            goto UpgradeUnit;
        case 13:
            Name = "Team ";
        case 3:
        UpgradeUnit:
            Name += "Upgrade unit "+FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
            +" to "+FormatInt(dataset->Effects[tech].EffectCommands[effect].B);
            if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
            {
                Name += dataset->Effects[tech].EffectCommands[effect].C == -1 ? ", all" : ", on map";
            }
            break;
        case 44:
            Name = "Gaia ";
            goto AttributeModifier;
        case 34:
            Name = "Neutral ";
            goto AttributeModifier;
        case 24:
            Name = "Enemy ";
            goto AttributeModifier;
        case 14:
            Name = "Team ";
        case 4:
        AttributeModifier:
        {
            Name += "Change " + Tester(dataset->Effects[tech].EffectCommands[effect], " by ");
            break;
        }
        case 45:
            Name = "Gaia ";
            goto AttributeModifierMultiply;
        case 35:
            Name = "Neutral ";
            goto AttributeModifierMultiply;
        case 25:
            Name = "Enemy ";
            goto AttributeModifierMultiply;
        case 15:
            Name = "Team ";
        case 5:
        AttributeModifierMultiply:
        {
            Name += "Multiply " + Tester(dataset->Effects[tech].EffectCommands[effect], " by ");
            break;
        }
        case 46:
            Name = "Gaia ";
            goto ResourceModifierMultiply;
        case 36:
            Name = "Neutral ";
            goto ResourceModifierMultiply;
        case 26:
            Name = "Enemy ";
            goto ResourceModifierMultiply;
        case 16:
            Name = "Team ";
        case 6:
        ResourceModifierMultiply:
            Name += "Multiply resource "+FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
            +" by "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            break;
        case 47:
            Name = "Gaia ";
            goto SpawnUnit;
        case 37:
            Name = "Neutral ";
            goto SpawnUnit;
        case 27:
            Name = "Enemy ";
            goto SpawnUnit;
        case 17:
            Name = "Team ";
        case 7:
        SpawnUnit:
            if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
            {
                Name += "Spawn unit "+FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                +" from "+FormatInt(dataset->Effects[tech].EffectCommands[effect].B)
                +", "+FormatInt(dataset->Effects[tech].EffectCommands[effect].C)+" times";
            }
            if(GameVersion == EV_UP)
            {
                if (dataset->Effects[tech].EffectCommands[effect].B == 1)
                {
                    Name += "Enable tech "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
                }
                else if (dataset->Effects[tech].EffectCommands[effect].B == 2)
                {
                    Name += "Force multi-use tech "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
                }
                else
                {
                    Name += "Disable tech "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
                }
            }
            break;
        case 48:
            Name = "Gaia ";
            goto ModifyTech;
        case 38:
            Name = "Neutral ";
            goto ModifyTech;
        case 28:
            Name = "Enemy ";
            goto ModifyTech;
        case 18:
            Name = "Team ";
        case 8:
        ModifyTech:
        {
            if (dataset->Effects[tech].EffectCommands[effect].B == -1)
            {
                Name += "Set tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                    + " research time to " + FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B == -2)
            {
                Name += "Modify tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                    + " research time by " + FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B >= 0 && dataset->Effects[tech].EffectCommands[effect].B <= 3)
            {
                Name += "Set tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                    + " cost type " + FormatInt(dataset->Effects[tech].EffectCommands[effect].B)
                    + " to " + FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B >= 16384 && dataset->Effects[tech].EffectCommands[effect].B <= 16387)
            {
                Name += "Modify tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                    + " cost type " + FormatInt(dataset->Effects[tech].EffectCommands[effect].B - 16384)
                    + " by " + FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B == 4)
            {
                Name += "Set tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                    + " research location to " + FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B == 5)
            {
                Name += "Set tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                    + " research button to " + FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B == 6)
            {
                Name += "Set tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                    + " icon to " + FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B == 7)
            {
                Name += "Set tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                    + " name to " + FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B == 8)
            {
                Name += "Set tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                    + " description to " + FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B == 9)
            {
                if (dataset->Effects[tech].EffectCommands[effect].D)
                {
                    Name += "Enable tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A) + " stacking";
                }
                else
                {
                    Name += "Disable tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A) + " stacking";
                }
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B == 10)
            {
                Name += "Set tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                    + " stacking cap to " + FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B == 11)
            {
                Name += "Set tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                    + " hotkey to " + FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else if (dataset->Effects[tech].EffectCommands[effect].B == 12)
            {
                switch (static_cast<int>(dataset->Effects[tech].EffectCommands[effect].D))
                {
                    case 0:
                    {
                        Name += "Disable tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A);
                        break;
                    }
                    case 1:
                    {
                        Name += "Enable tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A);
                        break;
                    }
                    case 2:
                    {
                        Name += "Force tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A);
                        break;
                    }
                    case 3:
                    {
                        Name += "Research tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A);
                        break;
                    }
                    default:
                    {
                        Name += "Tech " + FormatInt(dataset->Effects[tech].EffectCommands[effect].A);
                    }
                }
            }
            break;
        }
        case 39:
            Name = "Neutral ";
            goto SetPlayerCivName;
        case 29:
            Name = "Enemy ";
            goto SetPlayerCivName;
        case 19:
            Name = "Team ";
        case 9:
        SetPlayerCivName:
            Name += "Set player civ name to lang id "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            break;
        case 101:
            //Name = "Tech Cost Modifier (Set/+/-)";
            if(dataset->Effects[tech].EffectCommands[effect].C == 0)
            {
                Name = "Set tech "+FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                +" cost type "+FormatInt(dataset->Effects[tech].EffectCommands[effect].B)
                +" to "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else
            {
                Name = "Change tech "+FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                +" cost type "+FormatInt(dataset->Effects[tech].EffectCommands[effect].B)
                +" by "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            break;
        case 102:
            Name = "Disable tech "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            break;
        case 103:
            //Name = "Tech Time Modifier (Set/+/-)";
            if(dataset->Effects[tech].EffectCommands[effect].C == 0)
            {
                Name = "Set tech "+FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                +" time to "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            else
            {
                Name = "Change tech "+FormatInt(dataset->Effects[tech].EffectCommands[effect].A)
                +" time by "+FormatFloat(dataset->Effects[tech].EffectCommands[effect].D);
            }
            break;
        default:
            Name = "No type/Invalid type";
    }
    return Name;
}

void AGE_Frame::OnEffectCmdSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListEffectCmds();
}

void AGE_Frame::ListEffectCmds()
{
    InitSearch(Techs_Effects_Search->GetValue().MakeLower(), Techs_Effects_Search_R->GetValue().MakeLower());
    SearchAnd = Techs_Effects_UseAnd[0]->GetValue();
    ExcludeAnd = Techs_Effects_UseAnd[1]->GetValue();

    Techs_Effects_ListV->Sweep();

    if (dataset->Effects.size() && TechIDs.size())
    for(size_t loop = 0; loop < dataset->Effects[TechIDs.front()].EffectCommands.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetEffectCmdName(loop, TechIDs.front());
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Techs_Effects_ListV->names.Add(Name);
            Techs_Effects_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(Techs_Effects_ListV, &EffectIDs);

    SearchAnd = ExcludeAnd = false;

    wxCommandEvent e;
    OnEffectCmdSelect(e);
}

int32_t AGE_Frame::CombineEffects89(uint16_t type, int16_t amount)
{
    int32_t combination = (type < 0xFF ? type : 0xFF) << 8 | (GameVersion != EV_UP ?
        std::min(std::abs(amount), 0xFF) : amount < 0xFF ? amount > -256 ? amount & 0xFF : 0 : 0xFF);
    return amount >= 0 ? combination : GameVersion != EV_UP ? -combination : combination | -65536;
}

const short plainId = -32768;

void AGE_Frame::OnEffectCmdSelect(wxCommandEvent &event)
{
    size_t selections = Techs_Effects_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    for (AGETextCtrl *box : uiGroupTechEffect)
    {
        box->clear();
    }
    techAttributeNameId = plainId;
    techResearchNameId = plainId;
    bool enableD = true;
    genie::EffectCommand *EffectPointer = nullptr;
    if (selections > 0)
    {
        getSelectedItems(selections, Techs_Effects_ListV, EffectIDs);
        Effects_Type_Holder->Show(true);
        bool NeverHide = Effects_NeverHide->GetValue();

        for (size_t loop = selections; loop-- > 0;)
        {
            EffectPointer = &dataset->Effects[TechIDs.front()].EffectCommands[EffectIDs[loop]];
            Effects_Type->prepend(&EffectPointer->Type);
            Effects_A->prepend(&EffectPointer->A);
            Effects_B->prepend(&EffectPointer->B);
            Effects_C->prepend(&EffectPointer->C);
            Effects_D->prepend(&EffectPointer->D);
        }

        auto Populate89 = [this](float data)
        {
            int16_t amount = static_cast<int16_t>(data >= 0 || GameVersion == EV_UP ? data : -data);
            uint16_t type = static_cast<uint16_t>(amount) >> 8; amount &= 0xFF;
            if (data < 0)
            {
                amount = GameVersion != EV_UP ? -amount : amount | -256;
            }
            Effects_D->Show(false);
            Effects_89_Amount->Show(true);
            Effects_89_Amount->ChangeValue(lexical_cast<std::string>(amount)); // Correct value
            Effects_89_Type->Show(true);
            Effects_89_Type_CB1->Show(true);
            Effects_89_Type->ChangeValue(lexical_cast<std::string>(type)); // Correct class
            Effects_89_Type_CB1->SetChoice(type);
            Effects_89_Type_Text->SetLabel("Type ");
        };

        auto ShowSetAttributeModifier = [&]()
        {
            Effects_A_ComboBox->SwapList(&unit_names);
            Effects_A_ComboBox->Show(true);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->TakeControl();
            Effects_B_ComboBox->SwapList(&class_names);
            Effects_B_ComboBox->Show(true);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->TakeControl();
            Effects_C_ComboBox->SwapList(&effect_attribute_names);
            Effects_C_ComboBox->Show(true);
            techAttributeNameId = EffectPointer->C;
            Effects_D_ComboBox->Show(false);
            Effects_A->Show(true);
            Effects_B->Show(true);
            Effects_C->Show(true);

            Effects_A_Text->SetLabel("Unit ");
            Effects_B_Text->SetLabel("Class ");
            Effects_C_Text->SetLabel("Attribute ");
            Effects_D_Text->SetLabel("Amount [Set] ");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel("");

            if (EffectPointer->C == 8 || EffectPointer->C == 9)
            {
                enableD = NeverHide;
                Populate89(EffectPointer->D);
            }
            else
            {
                Effects_D->Show(true);
                Effects_89_Amount->Show(false);
                Effects_89_Type->Show(false);
                Effects_89_Type_CB1->Show(false);
                Effects_89_Type_Text->SetLabel("");
            }
        };

        auto ShowSetOrChangeResourceModifier = [&]()
        {
            bool DE2 = GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2;
            Effects_A_ComboBox->SwapList(&resource_names);
            Effects_A_ComboBox->Show(true);
            Effects_B_CheckBox->TakeControl();
            Effects_B_CheckBox->Show(true);
            Effects_B_ComboBox->Show(false);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->SwapList(&resource_names);
            Effects_C_ComboBox->Show(DE2);
            Effects_D_ComboBox->Show(false);
            Effects_89_Type_CB1->Show(false);
            Effects_A->Show(true);
            Effects_B->Show(true);
            Effects_C->Show(NeverHide || DE2);
            Effects_D->Show(true);
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);

            Effects_A_Text->SetLabel("Resource ");
            Effects_B_Text->SetLabel("Mode ");
            Effects_C_Text->SetLabel("Resource [*] ");
            if (EffectPointer->B == 0)
            {
                Effects_D_Text->SetLabel("Amount [Set] ");
            }
            else
            {
                Effects_D_Text->SetLabel("Amount [+/-] ");
            }
            Effects_89_Type_Text->SetLabel("");

            Effects_Info_B->SetLabel(" [ ] = Set, [X] = +/-");
            Effects_Info_C->SetLabel(DE2 ? " [>=0] = Multiply with" : "");
        };

        auto ShowEnableDisableUnit = [&]()
        {
            Effects_A_ComboBox->SwapList(&unit_names);
            Effects_A_ComboBox->Show(true);
            Effects_B_CheckBox->TakeControl();
            Effects_B_CheckBox->Show(true);
            Effects_B_ComboBox->Show(false);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->Show(false);
            Effects_D_ComboBox->Show(false);
            Effects_89_Type_CB1->Show(false);
            Effects_A->Show(true);
            Effects_B->Show(true);
            Effects_C->Show(NeverHide);
            Effects_D->Show(NeverHide);
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);

            Effects_A_Text->SetLabel("Unit ");
            Effects_B_Text->SetLabel("Mode ");
            Effects_C_Text->SetLabel("Unused ");
            Effects_D_Text->SetLabel("Unused ");
            Effects_89_Type_Text->SetLabel("");

            Effects_Info_B->SetLabel(" [ ] = Disable, [X] = Enable");
            Effects_Info_C->SetLabel("");
        };

        auto ShowUpgradeUnit = [&]()
        {
            bool DE2 = GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2;
            Effects_A_ComboBox->SwapList(&unit_names);
            Effects_A_ComboBox->Show(true);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->TakeControl();
            Effects_B_ComboBox->SwapList(&unit_names);
            Effects_B_ComboBox->Show(true);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->Show(false);
            Effects_D_ComboBox->Show(false);
            Effects_89_Type_CB1->Show(false);
            Effects_A->Show(true);
            Effects_B->Show(true);
            Effects_C->Show(NeverHide || DE2);
            Effects_D->Show(NeverHide);
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);

            Effects_A_Text->SetLabel("Unit ");
            Effects_B_Text->SetLabel("To Unit ");
            Effects_C_Text->SetLabel("Mode ");
            Effects_D_Text->SetLabel("Unused ");
            Effects_89_Type_Text->SetLabel("");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel(DE2 ? " [-1] = All, [!-1] = On map" : "");
        };

        auto ShowChangeAttributeModifier = [&]()
        {
            Effects_A_ComboBox->SwapList(&unit_names);
            Effects_A_ComboBox->Show(true);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->TakeControl();
            Effects_B_ComboBox->SwapList(&class_names);
            Effects_B_ComboBox->Show(true);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->TakeControl();
            Effects_C_ComboBox->SwapList(&effect_attribute_names);
            Effects_C_ComboBox->Show(true);
            techAttributeNameId = EffectPointer->C;
            Effects_D_ComboBox->Show(false);
            Effects_A->Show(true);
            Effects_B->Show(true);
            Effects_C->Show(true);

            Effects_A_Text->SetLabel("Unit ");
            Effects_B_Text->SetLabel("Class ");
            Effects_C_Text->SetLabel("Attribute ");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel("");

            if (EffectPointer->C == 8 || EffectPointer->C == 9)
            {
                enableD = NeverHide;
                Populate89(EffectPointer->D);
                Effects_D_Text->SetLabel("Amount [+] ");
            }
            else
            {
                Effects_D->Show(true);
                Effects_89_Amount->Show(false);
                Effects_89_Type->Show(false);
                Effects_89_Type_CB1->Show(false);
                Effects_D_Text->SetLabel("Amount [+/-] ");
                Effects_89_Type_Text->SetLabel("");
            }
        };

        auto ShowMultiplyAttributeModifier = [&]()
        {
            Effects_A_ComboBox->SwapList(&unit_names);
            Effects_A_ComboBox->Show(true);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->TakeControl();
            Effects_B_ComboBox->SwapList(&class_names);
            Effects_B_ComboBox->Show(true);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->TakeControl();
            Effects_C_ComboBox->SwapList(&effect_attribute_names);
            Effects_C_ComboBox->Show(true);
            techAttributeNameId = EffectPointer->C;
            Effects_D_ComboBox->Show(false);
            Effects_A->Show(true);
            Effects_B->Show(true);
            Effects_C->Show(true);

            Effects_A_Text->SetLabel("Unit ");
            Effects_B_Text->SetLabel("Class ");
            Effects_C_Text->SetLabel("Attribute ");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel("");

            if (EffectPointer->C == 8 || EffectPointer->C == 9)
            {
                enableD = NeverHide;
                Populate89(EffectPointer->D);
                Effects_D_Text->SetLabel("Amount [%] ");
            }
            else
            {
                Effects_D->Show(true);
                Effects_89_Amount->Show(false);
                Effects_89_Type->Show(false);
                Effects_89_Type_CB1->Show(false);
                Effects_D_Text->SetLabel("Amount [*] ");
                Effects_89_Type_Text->SetLabel("");
            }
        };

        auto ShowMultiplyResourceModifier = [&]()
        {
            Effects_A_ComboBox->SwapList(&resource_names);
            Effects_A_ComboBox->Show(true);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->Show(false);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->Show(false);
            Effects_D_ComboBox->Show(false);
            Effects_89_Type_CB1->Show(false);
            Effects_A->Show(true);
            Effects_B->Show(NeverHide);
            Effects_C->Show(NeverHide);
            Effects_D->Show(true);
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);

            Effects_A_Text->SetLabel("Resource ");
            Effects_B_Text->SetLabel("Unused ");
            Effects_C_Text->SetLabel("Unused ");
            Effects_D_Text->SetLabel("Amount [*] ");
            Effects_89_Type_Text->SetLabel("");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel("");
        };

        auto ShowEnableTech = [&]()
        {
            Effects_A_ComboBox->Show(false);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->Show(false);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->Show(false);
            Effects_D_ComboBox->Show(true);
            Effects_89_Type_CB1->Show(false);
            Effects_A->Show(NeverHide);
            Effects_B->Show(true);
            Effects_B->SetToolTip("0 Disable\n1 Enable\n2 Force enable");
            Effects_C->Show(NeverHide);
            Effects_D->Show(true);
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);

            Effects_A_Text->SetLabel("Unused ");
            Effects_B_Text->SetLabel("Action * ");
            Effects_C_Text->SetLabel("Unused ");
            Effects_D_Text->SetLabel("Tech ");
            Effects_89_Type_Text->SetLabel("");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel("");
        };

        auto ShowSpawnUnit = [&]()
        {
            Effects_A_ComboBox->SwapList(&unit_names);
            Effects_A_ComboBox->Show(true);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->TakeControl();
            Effects_B_ComboBox->SwapList(&unit_names);
            Effects_B_ComboBox->Show(true);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->Show(false);
            Effects_D_ComboBox->Show(false);
            Effects_89_Type_CB1->Show(false);
            Effects_A->Show(true);
            Effects_B->Show(true);
            Effects_C->Show(true);
            Effects_D->Show(NeverHide);
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);

            Effects_A_Text->SetLabel("Unit ");
            Effects_B_Text->SetLabel("From Building ");
            Effects_C_Text->SetLabel("Amount ");
            Effects_D_Text->SetLabel("Unused ");
            Effects_89_Type_Text->SetLabel("");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel("");
        };

        auto ShowModifyTech = [&]()
        {
            Effects_A_ComboBox->SwapList(&research_names);
            Effects_A_ComboBox->Show(true);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->TakeControl();
            Effects_B_ComboBox->SwapList(&modify_research_names);
            Effects_B_ComboBox->Show(true);
            techResearchNameId = EffectPointer->B;
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->Show(false);
            Effects_D_ComboBox->Show(false);
            Effects_A->Show(true);
            Effects_B->Show(true);
            Effects_B->SetToolTip("0-3 and 16384-16387 only work if the tech has the corresponding cost/storage set");
            Effects_C->Show(false);

            Effects_A_Text->SetLabel("Tech ");
            Effects_B_Text->SetLabel("Action * ");
            Effects_C_Text->SetLabel("Unused ");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel("");

            Effects_D->Show(true);
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);
            Effects_89_Type_CB1->Show(false);
            Effects_D_Text->SetLabel("Amount ");
            Effects_89_Type_Text->SetLabel("");
        };

        auto ShowSetPlayerCivName = [&]()
        {
            Effects_A_ComboBox->Show(false);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->Show(false);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->Show(false);
            Effects_D_ComboBox->Show(false);
            Effects_89_Type_CB1->Show(false);
            Effects_A->Show(true);
            Effects_A->SetToolTip("Needs to be 0, do not touch");
            Effects_B->Show(true);
            Effects_B->SetToolTip("Needs to be 0, do not touch");
            Effects_C->Show(NeverHide);
            Effects_D->Show(true);
            Effects_D->SetToolTip("An ID from the language file");
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);

            Effects_A_Text->SetLabel("Data * ");
            Effects_B_Text->SetLabel("Action * ");
            Effects_C_Text->SetLabel("Unused ");
            Effects_D_Text->SetLabel("Lang ID * ");
            Effects_89_Type_Text->SetLabel("");

            Effects_A->SetValue("0");
            Effects_A->SaveEdits();
            Effects_B->SetValue("0");
            Effects_B->SaveEdits();

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel("");
        };

        auto ShowTechCostModifier = [&]()
        {
            Effects_A_ComboBox->SwapList(&research_names);
            Effects_A_ComboBox->Show(true);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->TakeControl();
            Effects_B_ComboBox->SwapList(&resource_names);
            Effects_B_ComboBox->Show(true);
            Effects_C_CheckBox->TakeControl();
            Effects_C_CheckBox->Show(true);
            Effects_C_ComboBox->Show(false);
            Effects_D_ComboBox->Show(false);
            Effects_89_Type_CB1->Show(false);
            Effects_A->Show(true);
            Effects_B->Show(true);
            Effects_C->Show(true);
            Effects_D->Show(true);
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);

            Effects_A_Text->SetLabel("Tech ");
            Effects_B_Text->SetLabel("Resource ");
            Effects_C_Text->SetLabel("Mode ");
            if (EffectPointer->C == 0)
            {
                Effects_D_Text->SetLabel("Amount [Set] ");
            }
            else
            {
                Effects_D_Text->SetLabel("Amount [+/-] ");
            }
            Effects_89_Type_Text->SetLabel("");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel(" [ ] = Set, [X] = +/-");
        };

        auto ShowDisableTech = [&]()
        {
            Effects_A_ComboBox->Show(false);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->Show(false);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->Show(false);
            Effects_D_ComboBox->Show(true);
            Effects_89_Type_CB1->Show(false);
            Effects_A->Show(NeverHide);
            Effects_B->Show(NeverHide);
            Effects_C->Show(NeverHide);
            Effects_D->Show(true);
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);

            Effects_A_Text->SetLabel("Unused ");
            Effects_B_Text->SetLabel("Unused ");
            Effects_C_Text->SetLabel("Unused ");
            Effects_D_Text->SetLabel("Tech ");
            Effects_89_Type_Text->SetLabel("");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel("");
        };

        auto ShowTechTimeModifier = [&]()
        {
            Effects_A_ComboBox->SwapList(&research_names);
            Effects_A_ComboBox->Show(true);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->Show(false);
            Effects_C_CheckBox->TakeControl();
            Effects_C_CheckBox->Show(true);
            Effects_C_ComboBox->Show(false);
            Effects_D_ComboBox->Show(false);
            Effects_89_Type_CB1->Show(false);
            Effects_A->Show(true);
            Effects_B->Show(NeverHide);
            Effects_C->Show(true);
            Effects_D->Show(true);
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);

            Effects_A_Text->SetLabel("Tech ");
            Effects_B_Text->SetLabel("Unused ");
            Effects_C_Text->SetLabel("Mode ");
            if (EffectPointer->C == 0)
            {
                Effects_D_Text->SetLabel("Amount [Set] ");
            }
            else
            {
                Effects_D_Text->SetLabel("Amount [+/-] ");
            }
            Effects_89_Type_Text->SetLabel("");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel(" [ ] = Set, [X] = +/-");
        };

        auto ShowNothing = [&]()
        {
            Effects_A_ComboBox->Show(false);
            Effects_B_CheckBox->Show(false);
            Effects_B_ComboBox->Show(false);
            Effects_C_CheckBox->Show(false);
            Effects_C_ComboBox->Show(false);
            Effects_D_ComboBox->Show(false);
            Effects_89_Type_CB1->Show(false);
            Effects_A->Show(NeverHide);
            Effects_B->Show(NeverHide);
            Effects_C->Show(NeverHide);
            Effects_D->Show(NeverHide);
            Effects_89_Amount->Show(false);
            Effects_89_Type->Show(false);

            Effects_A_Text->SetLabel("Attribute A ");
            Effects_B_Text->SetLabel("Attribute B ");
            Effects_C_Text->SetLabel("Attribute C ");
            Effects_D_Text->SetLabel("Attribute D ");
            Effects_89_Type_Text->SetLabel("");

            Effects_Info_B->SetLabel("");
            Effects_Info_C->SetLabel("");
        };

        switch (EffectPointer->Type)
        {
            case 0:
            {
                ShowSetAttributeModifier();
                break;
            }
            case 1:
            {
                ShowSetOrChangeResourceModifier();
                break;
            }
            case 2:
            {
                ShowEnableDisableUnit();
                break;
            }
            case 3:
            {
                ShowUpgradeUnit();
                break;
            }
            case 4:
            {
                ShowChangeAttributeModifier();
                break;
            }
            case 5:
            {
                ShowMultiplyAttributeModifier();
                break;
            }
            case 6:
            {
                if (GenieVersion >= genie::GV_AoKA || GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap)
                {
                    ShowMultiplyResourceModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 7:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowSpawnUnit();
                }
                else if (GameVersion == EV_UP)
                {
                    ShowEnableTech();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 8:
            case 18:
            case 28:
            case 38:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowModifyTech();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 9:
            case 19:
            case 29:
            case 39:
            {
                if (GameVersion == EV_UP)
                {
                    ShowSetPlayerCivName();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 10:
            {
                if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowSetAttributeModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 11:
            {
                if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowSetOrChangeResourceModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 12:
            {
                if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowEnableDisableUnit();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 13:
            {
                if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowUpgradeUnit();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 14:
            {
                if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowChangeAttributeModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 15:
            {
                if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowMultiplyAttributeModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 16:
            {
                if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowMultiplyResourceModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 17:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowSpawnUnit();
                }
                else if (GameVersion == EV_UP)
                {
                    ShowEnableTech();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 20:
            case 30:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowSetAttributeModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 21:
            case 31:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowSetOrChangeResourceModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 22:
            case 32:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowEnableDisableUnit();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 23:
            case 33:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowUpgradeUnit();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 24:
            case 34:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowChangeAttributeModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 25:
            case 35:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowMultiplyAttributeModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 26:
            case 36:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
                {
                    ShowMultiplyResourceModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 27:
            case 37:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowSpawnUnit();
                }
                else if (GameVersion == EV_UP)
                {
                    ShowEnableTech();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 40:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowSetAttributeModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 41:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowSetOrChangeResourceModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 42:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowEnableDisableUnit();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 43:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowUpgradeUnit();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 44:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowChangeAttributeModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 45:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowMultiplyAttributeModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 46:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowMultiplyResourceModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 47:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowSpawnUnit();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 48:
            {
                if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    ShowModifyTech();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 101:
            {
                if (GenieVersion >= genie::GV_AoKA || GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap)
                {
                    ShowTechCostModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            case 102:
            {
                ShowDisableTech();
                break;
            }
            case 103:
            {
                if (GenieVersion >= genie::GV_AoKA || GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap)
                {
                    ShowTechTimeModifier();
                }
                else
                {
                    ShowNothing();
                }
                break;
            }
            default:
            {
                ShowNothing();
            }
        }
    }
    else
    {
        Effects_Type_Holder->Show(false);
        Effects_A_ComboBox->Show(false);
        Effects_B_CheckBox->Show(false);
        Effects_B_ComboBox->Show(false);
        Effects_C_CheckBox->Show(false);
        Effects_C_ComboBox->Show(false);
        Effects_D_ComboBox->Show(false);
        Effects_89_Type_CB1->Show(false);
        Effects_A->Show(false);
        Effects_B->Show(false);
        Effects_C->Show(false);
        Effects_D->Show(false);
        Effects_89_Amount->Show(false);
        Effects_89_Type->Show(false);
        Effects_A_Text->SetLabel("Select effect first ");
        Effects_B_Text->SetLabel("");
        Effects_C_Text->SetLabel("");
        Effects_D_Text->SetLabel("");
        Effects_89_Type_Text->SetLabel("");
        Effects_Info_B->SetLabel("");
        Effects_Info_C->SetLabel("");
    }
    for (AGETextCtrl *box : uiGroupTechEffect)
    {
        box->update();
    }
    Effects_D->Enable(enableD);
    Effects_Type_Holder->Layout();
    Effects_Data_Holder->Layout();
    if (EffectPointer != nullptr)
    {
        SetEffectTypeChoice(Effects_Type_ComboBox, EffectPointer->Type);
    }
    if (techAttributeNameId != plainId)
    {
        SetEffectAttributeChoice(Effects_C_ComboBox, techAttributeNameId);
    }
    if (techResearchNameId != plainId)
    {
        if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
        {
            if (techResearchNameId == -2)
            {
                Effects_B_ComboBox->SetSelection(1);
            }
            else if (techResearchNameId >= 0 && techResearchNameId <= 12)
            {
                Effects_B_ComboBox->SetSelection(techResearchNameId + 2);
            }
            else if (techResearchNameId >= 16384 && techResearchNameId <= 16387)
            {
                Effects_B_ComboBox->SetSelection(techResearchNameId - 16369);
            }
            else
            {
                Effects_B_ComboBox->SetSelection(0);
            }
        }
        else if (GameVersion == EV_UP)
        {
            if (techResearchNameId == -2)
            {
                Effects_B_ComboBox->SetSelection(1);
            }
            else if (techResearchNameId >= 0 && techResearchNameId <= 3)
            {
                Effects_B_ComboBox->SetSelection(techResearchNameId + 2);
            }
            else if (techResearchNameId >= 16384 && techResearchNameId <= 16387)
            {
                Effects_B_ComboBox->SetSelection(techResearchNameId - 16378);
            }
            else
            {
                Effects_B_ComboBox->SetSelection(0);
            }
        }
    }
//  Refresh(); // Too much lag.
}

void AGE_Frame::OnEffectCmdAdd(wxCommandEvent &event) // Works.
{
    size_t selections = Techs_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->Effects[TechIDs.front()].EffectCommands);
    ListEffectCmds();
}

void AGE_Frame::OnEffectCmdInsert(wxCommandEvent &event)  // Works.
{
    size_t selections = Techs_Effects_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->Effects[TechIDs.front()].EffectCommands, EffectIDs.front());
    ListEffectCmds();
}

void AGE_Frame::OnEffectCmdDelete(wxCommandEvent &event)  // Works.
{
    size_t selections = Techs_Effects_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->Effects[TechIDs.front()].EffectCommands, EffectIDs);
    ListEffectCmds();
}

void AGE_Frame::OnEffectCmdCopy(wxCommandEvent &event)    // Works.
{
    size_t selections = Techs_Effects_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Effects[TechIDs.front()].EffectCommands, EffectIDs, copies.EffectCmd);
    Techs_Effects_ListV->SetFocus();
}

void AGE_Frame::OnEffectCmdPaste(wxCommandEvent &event)   // Works.
{
    size_t selections = Techs_Effects_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Effects[TechIDs.front()].EffectCommands, EffectIDs, copies.EffectCmd);
    ListEffectCmds();
}

void AGE_Frame::OnEffectCmdPasteInsert(wxCommandEvent &event) // Works.
{
    size_t selections = Techs_Effects_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->Effects[TechIDs.front()].EffectCommands, EffectIDs.front(), copies.EffectCmd);
    ListEffectCmds();
}

void AGE_Frame::OnEffectCmdCopyToTechs(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TechIDs.size(); ++loop)
    {
        dataset->Effects[TechIDs[loop]].EffectCommands = dataset->Effects[TechIDs.front()].EffectCommands;
    }
}

void AGE_Frame::LoadAllEffects(wxCommandEvent &event)
{
    InitSearch(Techs_AllEffects_Search->GetValue().MakeLower(), Techs_AllEffects_Search_R->GetValue().MakeLower());
    SearchAnd = Techs_AllEffects_UseAnd[0]->GetValue();
    ExcludeAnd = Techs_AllEffects_UseAnd[1]->GetValue();

    Techs_AllEffects_ListV->Sweep();

    for(short tech = 0; tech < dataset->Effects.size(); ++tech)
    {
        for(short effect = 0; effect < dataset->Effects[tech].EffectCommands.size(); ++effect)
        {
            wxString Name = " T" + lexical_cast<std::string>(tech) +
                " E" + lexical_cast<std::string>(effect) + " - " + GetEffectCmdName(effect, tech);
            if(SearchMatches(" " + Name.Lower() + " "))
            {
                Techs_AllEffects_ListV->names.Add(Name);
            }
        }
    }

    RefreshList(Techs_AllEffects_ListV);

    SearchAnd = ExcludeAnd = false;

    wxCommandEvent e;
    OnAllEffectSelect(e);
}

void AGE_Frame::ClearAllEffects(wxCommandEvent &event)
{
    Techs_Search->SetValue("");
    Techs_Effects_Search->SetValue("");
}

void AGE_Frame::OnAllEffectSelect(wxCommandEvent &event)
{
    SearchAllSubVectors(Techs_AllEffects_ListV, Techs_Search, Techs_Effects_Search);
}

void AGE_Frame::CreateTechControls()
{
    Tab_Techs = new ATabPage(TabBar_Main);

    Techs_Main = new wxBoxSizer(wxHORIZONTAL);
    Techs_Buttons = new wxGridSizer(3, 0, 0);
    Effects_DataArea = new wxBoxSizer(wxVERTICAL);
    Effects_ListArea = new wxBoxSizer(wxVERTICAL);
    Techs_Effects_Buttons = new wxGridSizer(3, 0, 0);
    Effects_DataAreaProperties = new wxBoxSizer(wxVERTICAL);
    Techs_Techs = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Effects");
    Techs_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
    Techs_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
    Techs_Search = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_UseAnd[0] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_Search_R = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_UseAnd[1] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_ListV = new ProperList(Tab_Techs, ASize(200, 100));
    Techs_Add = new wxButton(Tab_Techs, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Techs_Insert = new wxButton(Tab_Techs, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Techs_Delete = new wxButton(Tab_Techs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Techs_Copy = new wxButton(Tab_Techs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Techs_Paste = new wxButton(Tab_Techs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Techs_PasteInsert = new wxButton(Tab_Techs, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Techs_Rename = new wxButton(Tab_Techs, wxID_ANY, "Rename effects");
    Techs_Restore = new wxButton(Tab_Techs, wxID_ANY, "Rename for GeniEd 2");

    Techs_Name_Text = new SolidText(Tab_Techs, " Effect Name");
    Techs_Name = new StringControl(Tab_Techs, this, nullptr, 31, false);

    Techs_Effects = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Effect Commands");
    Techs_Effects_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
    Techs_Effects_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
    Techs_Effects_Search = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_Effects_UseAnd[0] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_Effects_Search_R = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_Effects_UseAnd[1] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_Effects_ListV = new ProperList(Tab_Techs, ASize(200, 100));
    Techs_Effects_Add = new wxButton(Tab_Techs, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_Insert = new wxButton(Tab_Techs, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_Delete = new wxButton(Tab_Techs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_Copy = new wxButton(Tab_Techs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_Paste = new wxButton(Tab_Techs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_PasteInsert = new wxButton(Tab_Techs, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_CopyToTechs = new wxButton(Tab_Techs, wxID_ANY, "Copy all to selected effects", wxDefaultPosition, wxSize(10, -1));

    Effects_Type_Holder = new wxBoxSizer(wxVERTICAL);
    Effects_Type2_Holder = new wxBoxSizer(wxHORIZONTAL);
    Effects_Type_Text = new SolidText(Tab_Techs, " Command Type *");
    Effects_Type = new NumberControl(CUByte, Tab_Techs, this, &uiGroupTechEffect, false);
    Effects_Type->SetToolTip("101 and 103 are only for\ntech tree and team bonus"
        "\n101-103 only work at start of a game\n7-39 are only available with UserPatch 1.5"
        "\n10-16 are also available with AoK HD");
    Effects_Type_ComboBox = new LinkedComboBox(Tab_Techs, Effects_Type, &effect_type_names, false, AGETextCtrl::GIANT);
    Effects_Data_Holder = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Effect Attributes");
    Effects_NeverHide = new wxCheckBox(Tab_Techs, wxID_ANY, "Never hide attributes", wxDefaultPosition, wxDefaultSize);
    Effects_NeverHide->SetValue(NeverHideAttributes);
    Effects_DataA_Holder = new wxBoxSizer(wxHORIZONTAL);
    Effects_DataB_Holder = new wxBoxSizer(wxHORIZONTAL);
    Effects_DataC_Holder = new wxBoxSizer(wxHORIZONTAL);
    Effects_DataD_Holder = new wxBoxSizer(wxHORIZONTAL);
    Effects_DataF_Holder = new wxBoxSizer(wxHORIZONTAL);
    Effects_A_Holder = new wxBoxSizer(wxVERTICAL);
    Effects_B_Holder = new wxBoxSizer(wxVERTICAL);
    Effects_C_Holder = new wxBoxSizer(wxVERTICAL);
    Effects_D_Holder = new wxBoxSizer(wxHORIZONTAL);
    Effects_89_Type_Holder = new wxBoxSizer(wxVERTICAL);
    Effects_A_Text = new SolidText(Tab_Techs, "Attribute A ", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(100, -1));
    Effects_A = new NumberControl(CShort, Tab_Techs, this, &uiGroupTechEffect, false, AGETextCtrl::LARGE);
    Effects_A_ComboBox = new LinkedComboBox(Tab_Techs, Effects_A, &unit_names, false);
    UnitComboBoxList.push_back(Effects_A_ComboBox);
    ResourceComboBoxList.push_back(Effects_A_ComboBox);
    ResearchComboBoxList.push_back(Effects_A_ComboBox);
    Effects_Info_A = new SolidText(Tab_Techs, "");
    Effects_B_Text = new SolidText(Tab_Techs, "Attribute B ", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(100, -1));
    Effects_B = new NumberControl(CShort, Tab_Techs, this, &uiGroupTechEffect, false, AGETextCtrl::LARGE);
    Effects_B_Boxes = new wxBoxSizer(wxHORIZONTAL);
    Effects_B_CheckBox = new LinkedCheckBox(Tab_Techs, "", Effects_B, false);
    Effects_B_ComboBox = new LinkedComboBox(Tab_Techs, Effects_B, &class_names, false);
    UnitComboBoxList.push_back(Effects_B_ComboBox);
    ResourceComboBoxList.push_back(Effects_B_ComboBox);
    Effects_Info_B = new SolidText(Tab_Techs, " Info B");
    Effects_C_Text = new SolidText(Tab_Techs, "Attribute C ", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(100, -1));
    Effects_C = new NumberControl(CShort, Tab_Techs, this, &uiGroupTechEffect, false, AGETextCtrl::LARGE);
    Effects_C_Boxes = new wxBoxSizer(wxHORIZONTAL);
    Effects_C_CheckBox = new LinkedCheckBox(Tab_Techs, "", Effects_C, false);
    Effects_C_ComboBox = new LinkedComboBox(Tab_Techs, Effects_C, &effect_attribute_names, false);
    Effects_Info_C = new SolidText(Tab_Techs, " Info C");
    Effects_D_Text = new SolidText(Tab_Techs, "Attribute D ", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(100, -1));
    Effects_D = new NumberControl(CFloat, Tab_Techs, this, &uiGroupTechEffect, false, AGETextCtrl::LARGE);
    Effects_D_Boxes = new wxBoxSizer(wxHORIZONTAL);
    Effects_D_ComboBox = new LinkedComboBox(Tab_Techs, Effects_D, &research_names, false);
    ResearchComboBoxList.push_back(Effects_D_ComboBox);
    Effects_Info_D = new SolidText(Tab_Techs, "");
    Effects_89_Amount = new NumberControl(CUByte, Tab_Techs, this, nullptr, false, AGETextCtrl::LARGE);
    Effects_89_Type_Text = new SolidText(Tab_Techs, "Type ", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(100, -1));
    Effects_89_Type = new NumberControl(CUByte, Tab_Techs, this, nullptr, false, AGETextCtrl::LARGE);
    Effects_89_Type_CB1 = new LinkedComboBox(Tab_Techs, Effects_89_Type, &armor_names, false);

    Techs_AllEffects = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Commands of all Effects");
    Techs_AllEffects_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
    Techs_AllEffects_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
    Techs_AllEffects_Search = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_AllEffects_UseAnd[0] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_AllEffects_Search_R = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_AllEffects_UseAnd[1] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_AllEffects_ListV = new ProperList(Tab_Techs, ASize(200, 100));
    Techs_AllEffects_Buttons = new wxBoxSizer(wxHORIZONTAL);
    Techs_AllEffects_Load = new wxButton(Tab_Techs, wxID_ANY, "Reload", wxDefaultPosition, wxSize(10, -1));
    Techs_AllEffects_Clear = new wxButton(Tab_Techs, wxID_ANY, "Clear *", wxDefaultPosition, wxSize(10, -1));
    Techs_AllEffects_Clear->SetToolTip("Clear the modified search texts");

    Techs_Buttons->Add(Techs_Add, 1, wxEXPAND);
    Techs_Buttons->Add(Techs_Delete, 1, wxEXPAND);
    Techs_Buttons->Add(Techs_Insert, 1, wxEXPAND);
    Techs_Buttons->Add(Techs_Copy, 1, wxEXPAND);
    Techs_Buttons->Add(Techs_Paste, 1, wxEXPAND);
    Techs_Buttons->Add(Techs_PasteInsert, 1, wxEXPAND);

    Techs_Searches[0]->Add(Techs_Search, 1, wxEXPAND);
    Techs_Searches[0]->Add(Techs_UseAnd[0], 0, wxLEFT, 2);
    Techs_Searches[1]->Add(Techs_Search_R, 1, wxEXPAND);
    Techs_Searches[1]->Add(Techs_UseAnd[1], 0, wxLEFT, 2);
    Techs_Techs->Add(Techs_Searches[0], 0, wxEXPAND);
    Techs_Techs->Add(Techs_Searches[1], 0, wxEXPAND);
    Techs_Techs->Add(Techs_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Techs_Techs->Add(Techs_Buttons, 0, wxEXPAND);

    Techs_Effects_Buttons->Add(Techs_Effects_Add, 1, wxEXPAND);
    Techs_Effects_Buttons->Add(Techs_Effects_Delete, 1, wxEXPAND);
    Techs_Effects_Buttons->Add(Techs_Effects_Insert, 1, wxEXPAND);
    Techs_Effects_Buttons->Add(Techs_Effects_Copy, 1, wxEXPAND);
    Techs_Effects_Buttons->Add(Techs_Effects_Paste, 1, wxEXPAND);
    Techs_Effects_Buttons->Add(Techs_Effects_PasteInsert, 1, wxEXPAND);

    Effects_ListArea->Add(Techs_Name_Text);
    Effects_ListArea->Add(Techs_Name, 0, wxEXPAND);
    Effects_ListArea->Add(Techs_Rename, 0, wxEXPAND);
    Effects_ListArea->Add(Techs_Restore, 0, wxEXPAND);

    Techs_Effects_Searches[0]->Add(Techs_Effects_Search, 1, wxEXPAND);
    Techs_Effects_Searches[0]->Add(Techs_Effects_UseAnd[0], 0, wxLEFT, 2);
    Techs_Effects_Searches[1]->Add(Techs_Effects_Search_R, 1, wxEXPAND);
    Techs_Effects_Searches[1]->Add(Techs_Effects_UseAnd[1], 0, wxLEFT, 2);
    Techs_Effects->Add(Techs_Effects_Searches[0], 0, wxEXPAND);
    Techs_Effects->Add(Techs_Effects_Searches[1], 0, wxEXPAND);
    Techs_Effects->Add(Techs_Effects_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Techs_Effects->Add(Techs_Effects_Buttons, 0, wxEXPAND);
    Techs_Effects->Add(Techs_Effects_CopyToTechs, 0, wxEXPAND | wxTOP, 2);

    Effects_ListArea->Add(Techs_Effects, 1, wxEXPAND | wxTOP, 5);

    Effects_Type2_Holder->Add(Effects_Type, 0, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
    Effects_Type2_Holder->Add(Effects_Type_ComboBox, 0, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
    Effects_Type_Holder->Add(Effects_Type_Text, 0, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
    Effects_Type_Holder->Add(Effects_Type2_Holder);

    Effects_A_Holder->Add(Effects_A, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
    Effects_A_Holder->Add(Effects_A_ComboBox, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);

    Effects_DataA_Holder->Add(Effects_A_Text);
    Effects_DataA_Holder->Add(Effects_A_Holder);
    Effects_DataA_Holder->Add(Effects_Info_A);

    Effects_B_Boxes->Add(Effects_B_CheckBox);
    Effects_B_Boxes->Add(Effects_B_ComboBox);
    Effects_B_Holder->Add(Effects_B, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
    Effects_B_Holder->Add(Effects_B_Boxes, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);

    Effects_DataB_Holder->Add(Effects_B_Text);
    Effects_DataB_Holder->Add(Effects_B_Holder);
    Effects_DataB_Holder->Add(Effects_Info_B);

    Effects_C_Boxes->Add(Effects_C_CheckBox);
    Effects_C_Boxes->Add(Effects_C_ComboBox);
    Effects_C_Holder->Add(Effects_C, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
    Effects_C_Holder->Add(Effects_C_Boxes, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);

    Effects_DataC_Holder->Add(Effects_C_Text);
    Effects_DataC_Holder->Add(Effects_C_Holder);
    Effects_DataC_Holder->Add(Effects_Info_C);

    Effects_D_Boxes->Add(Effects_D_ComboBox);
    Effects_D_Holder->Add(Effects_D);
    Effects_D_Holder->Add(Effects_89_Amount);

    Effects_DataD_Holder->Add(Effects_D_Text);
    Effects_DataD_Holder->Add(Effects_D_Holder, 0, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
    Effects_DataD_Holder->Add(Effects_Info_D);

    Effects_89_Type_Holder->Add(Effects_89_Type, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
    Effects_89_Type_Holder->Add(Effects_89_Type_CB1, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
    Effects_D_Boxes->Add(Effects_89_Type_Holder);

    Effects_DataF_Holder->Add(Effects_89_Type_Text);
    Effects_DataF_Holder->Add(Effects_D_Boxes);

    Effects_Data_Holder->Add(Effects_NeverHide);
    Effects_Data_Holder->Add(Effects_DataA_Holder, 0, wxTOP, 5);
    Effects_Data_Holder->Add(Effects_DataB_Holder, 0, wxTOP, 5);
    Effects_Data_Holder->Add(Effects_DataC_Holder, 0, wxTOP, 5);
    Effects_Data_Holder->Add(Effects_DataD_Holder, 0, wxTOP, 5);
    Effects_Data_Holder->Add(Effects_DataF_Holder);

    Techs_AllEffects_Searches[0]->Add(Techs_AllEffects_Search, 1, wxEXPAND);
    Techs_AllEffects_Searches[0]->Add(Techs_AllEffects_UseAnd[0], 0, wxLEFT, 2);
    Techs_AllEffects_Searches[1]->Add(Techs_AllEffects_Search_R, 1, wxEXPAND);
    Techs_AllEffects_Searches[1]->Add(Techs_AllEffects_UseAnd[1], 0, wxLEFT, 2);
    Techs_AllEffects->Add(Techs_AllEffects_Searches[0], 0, wxEXPAND);
    Techs_AllEffects->Add(Techs_AllEffects_Searches[1], 0, wxEXPAND);
    Techs_AllEffects->Add(Techs_AllEffects_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Techs_AllEffects_Buttons->Add(Techs_AllEffects_Load, 2, wxEXPAND | wxRIGHT, 2);
    Techs_AllEffects_Buttons->Add(Techs_AllEffects_Clear, 1, wxEXPAND);
    Techs_AllEffects->Add(Techs_AllEffects_Buttons, 0, wxEXPAND);

    Effects_DataArea->Add(Effects_Type_Holder, 0, wxEXPAND);
    Effects_DataArea->Add(Effects_Data_Holder, 0, wxEXPAND | wxTOP, 5);
    Effects_DataArea->Add(Techs_AllEffects, 1, wxEXPAND | wxTOP, 5);

    Techs_Main->Add(Techs_Techs, 21, wxEXPAND | wxALL, 5); // 3
    Techs_Main->Add(Effects_ListArea, 29, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5); // 3+1
    Techs_Main->Add(Effects_DataArea, 31, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5); // 6-1

    Effects_89_Amount->Show(false);
    Effects_89_Type->Show(false);
    Effects_A_ComboBox->Show(false);
    Effects_B_CheckBox->Show(false);
    Effects_B_ComboBox->Show(false);
    Effects_C_CheckBox->Show(false);
    Effects_C_ComboBox->Show(false);
    Effects_D_ComboBox->Show(false);
    Effects_89_Type_CB1->Show(false);

    Tab_Techs->SetSizer(Techs_Main);

    for(size_t loop = 0; loop < 2; ++loop)
    {
        Techs_UseAnd[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnEffectSearch, this);
        Techs_Effects_UseAnd[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnEffectCmdSearch, this);
        Techs_AllEffects_UseAnd[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::LoadAllEffects, this);
    }
    Techs_Rename->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectRename, this);
    Techs_Restore->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectRenameGE2, this);
    Techs_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnEffectSelect, this);
    Techs_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnEffectSearch, this);
    Techs_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnEffectSearch, this);
    Techs_Effects_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnEffectCmdSelect, this);
    Techs_Effects_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnEffectCmdSearch, this);
    Techs_Effects_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnEffectCmdSearch, this);
    Techs_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectAdd, this);
    Techs_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectInsert, this);
    Techs_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectDelete, this);
    Techs_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectCopy, this);
    Techs_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectPaste, this);
    Techs_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectPasteInsert, this);
    Techs_Effects_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectCmdAdd, this);
    Techs_Effects_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectCmdInsert, this);
    Techs_Effects_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectCmdDelete, this);
    Techs_Effects_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectCmdCopy, this);
    Techs_Effects_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectCmdPaste, this);
    Techs_Effects_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectCmdPasteInsert, this);
    Techs_Effects_CopyToTechs->Bind(wxEVT_BUTTON, &AGE_Frame::OnEffectCmdCopyToTechs, this);
    Effects_89_Amount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Effects89, this);
    Effects_89_Amount->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Effects89, this);
    Effects_89_Type->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Effects89, this);
    Effects_89_Type->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Effects89, this);
    Techs_AllEffects_Search->Bind(wxEVT_TEXT, &AGE_Frame::LoadAllEffects, this);
    Techs_AllEffects_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::LoadAllEffects, this);
    Techs_AllEffects_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnAllEffectSelect, this);
    Techs_AllEffects_Load->Bind(wxEVT_BUTTON, &AGE_Frame::LoadAllEffects, this);
    Techs_AllEffects_Clear->Bind(wxEVT_BUTTON, &AGE_Frame::ClearAllEffects, this);

    Techs_Name->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListEffects();
        }
    });
    Techs_Name->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListEffects();
    });
    Effects_Type->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_Type->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Techs, this);
    Effects_Type_ComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent &event)
    {
        unsigned selection = static_cast<unsigned>(event.GetSelection() - 1);
        OnChooseEffectType(Effects_Type, selection);
        Effects_Type->SaveEdits();
        ListEffectCmds();
    });
    Effects_A->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_A->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Techs, this);
    Effects_B->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_B->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Techs, this);
    Effects_C->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_C->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Techs, this);
    Effects_D->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_D->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Techs, this);
    Effects_A_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Techs, this);
    Effects_B_CheckBox->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnUpdateCheck_Techs, this);
    Effects_B_ComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent& event)
    {
        if (techResearchNameId != plainId)
        {
            if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
            {
                if (event.GetSelection() == 0)
                {
                    Effects_B->ChangeValue("-1");
                }
                else if (event.GetSelection() == 1)
                {
                    Effects_B->ChangeValue("-2");
                }
                else if (event.GetSelection() < 15)
                {
                    Effects_B->SetAsText(event.GetSelection() - 2);
                }
                else if (event.GetSelection() < 19)
                {
                    Effects_B->SetAsText(event.GetSelection() + 16369);
                }
                else
                {
                    Effects_B->ChangeValue("-1");
                }
            }
            else if (GameVersion == EV_UP)
            {
                if (event.GetSelection() == 0)
                {
                    Effects_B->ChangeValue("-1");
                }
                else if (event.GetSelection() == 1)
                {
                    Effects_B->ChangeValue("-2");
                }
                else if (event.GetSelection() < 6)
                {
                    Effects_B->SetAsText(event.GetSelection() - 2);
                }
                else if (event.GetSelection() < 10)
                {
                    Effects_B->SetAsText(event.GetSelection() + 16378);
                }
                else
                {
                    Effects_B->ChangeValue("-1");
                }
            }
            Effects_B->SaveEdits();
        }
        else
        {
            Effects_B_ComboBox->OnChoose(event);
        }
        ListEffectCmds();
    });
    Effects_C_CheckBox->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnUpdateCheck_Techs, this);
    Effects_C_ComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent& event)
    {
        if (techAttributeNameId != plainId)
        {
            unsigned selection = static_cast<unsigned>(event.GetSelection() - 1);
            OnChooseEffectAttribute(Effects_C, selection);
            Effects_C->SaveEdits();
        }
        else
        {
            Effects_C_ComboBox->OnChoose(event);
        }
        ListEffectCmds();
    });
    Effects_D_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Techs, this);
    Effects_89_Type_CB1->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent& event)
    {
        uint16_t type = static_cast<uint16_t>(event.GetSelection() - 1);
        int16_t amount;
        try
        {
            amount = lexical_cast<int16_t>(Effects_89_Amount->GetValue());
        }
        catch (const bad_lexical_cast &)
        {
            popUp.post("Bad integer. Valid range is from 0 or -255 to 255.", "AGE", Effects_89_Amount);
            return;
        }
        std::string newValue(lexical_cast<std::string>(CombineEffects89(type, amount)));
        if (Effects_D->GetValue() != newValue)
        {
            Effects_D->ChangeValue(newValue);
            Effects_D->SaveEdits();
            ListEffectCmds();
        }
    });
}

void AGE_Frame::OnEnter_Techs(wxCommandEvent &event)
{
    static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
    ListEffectCmds();
}

void AGE_Frame::OnKillFocus_Techs(wxFocusEvent &event)
{
    event.Skip();
    if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
    {
        ListEffectCmds();
    }
}

void AGE_Frame::UpdateEffects89(bool forced)
{
    // if has something, then update float value.
    if (!Effects_89_Amount->IsEmpty() && !Effects_89_Type->IsEmpty())
    {
        uint16_t type;
        try
        {
            type = lexical_cast<uint16_t>(Effects_89_Type->GetValue());
        }
        catch (const bad_lexical_cast &)
        {
            popUp.post("Bad integer. Valid range is from 0 to 255.", "AGE", Effects_89_Type);
            return;
        }
        int16_t amount;
        try
        {
            amount = lexical_cast<int16_t>(Effects_89_Amount->GetValue());
        }
        catch (const bad_lexical_cast &)
        {
            popUp.post("Bad integer. Valid range is from 0 or -255 to 255.", "AGE", Effects_89_Amount);
            return;
        }
        std::string newValue(lexical_cast<std::string>(CombineEffects89(type, amount)));
        if (Effects_D->GetValue() != newValue)
        {
            Effects_D->ChangeValue(newValue);
            Effects_D->SaveEdits(forced);
        }
        else return;
    }
    ListEffectCmds();
}

void AGE_Frame::OnEnter_Effects89(wxCommandEvent &event)
{
    UpdateEffects89(true);
}

void AGE_Frame::OnKillFocus_Effects89(wxFocusEvent &event)
{
    event.Skip();
    UpdateEffects89(false);
}

void AGE_Frame::OnUpdateCheck_Techs(wxCommandEvent &event)
{
    static_cast<LinkedCheckBox*>(event.GetEventObject())->OnChoose(event);
    ListEffectCmds();
}

void AGE_Frame::OnUpdateCombo_Techs(wxCommandEvent &event)
{
    static_cast<LinkedComboBox*>(event.GetEventObject())->OnChoose(event);
    ListEffectCmds();
}
