#include "../AGE_Frame.h"

string AGE_Frame::GetTechName(int index)
{
    if(!dataset->Techages[index].Name.empty())
        return dataset->Techages[index].Name+" ";
    return "New Technology ";
}

void AGE_Frame::OnTechRenameGE2(wxCommandEvent &event)
{
    if(!dataset) return;

    for(auto &tech: dataset->Techages)
    {
        tech.Name = "Tech";
    }
    ListTechs();
}

void AGE_Frame::OnTechRename(wxCommandEvent &event)
{
    if(!dataset) return;

    for(auto &tech: dataset->Techages)
    {
        if(tech.Effects.size()) // Other than empty techs, not researches if research loop doesn't rename them.
        {
            tech.Name = "Non-Research";
        }
        else // Empty techs.
        {
            tech.Name = "New Technology";
        }
    }
    short ResearchTechID = 0;
    for(size_t loop=dataset->Researchs.size(); loop--> 0;) // Rename of techs. Make it reverse loop.
    {
        ResearchTechID = dataset->Researchs[loop].TechageID;
        if(ResearchTechID >= 0) // Only researches which have techs.
        {
            if(!LangDLLstring(dataset->Researchs[loop].LanguageDLLName, 2).empty()) // has a lang dll name
            {
                dataset->Techages[ResearchTechID].Name = LangDLLstring(dataset->Researchs[loop].LanguageDLLName, 31);
            }
            else // Use internal name instead.
            {
                dataset->Techages[ResearchTechID].Name = dataset->Researchs[loop].Name;
            }
        }
    }
    string CivName;
    short CivTechTreeID=0, CivTeamBonusID = 0;
    for(size_t loop2=dataset->Civs.size(); loop2--> 0;) // Rename of techs. Make it reverse loop.
    {
        string CivName = lexical_cast<string>(dataset->Civs[loop2].Name); // Civ internal name.
        CivTechTreeID = dataset->Civs[loop2].TechTreeID;
        CivTeamBonusID = dataset->Civs[loop2].TeamBonusID;
        if(CivTechTreeID >= 0)
        {
            dataset->Techages[CivTechTreeID].Name = CivName+" Tech. Tree"; // Under 31 chars.
        }
        if(CivTeamBonusID >= 0)
        {
            dataset->Techages[CivTeamBonusID].Name = CivName+" Team Bonus"; // Under 31 chars.
        }
    }
    ListTechs();
}

void AGE_Frame::OnTechSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTechs(false);
}

void AGE_Frame::ListTechs(bool all)
{
    InitTechs(all);
    wxTimerEvent E;
    OnTechTimer(E);
}

void AGE_Frame::InitTechs(bool all)
{
    InitSearch(Techs_Search->GetValue().MakeLower(), Techs_Search_R->GetValue().MakeLower());
    SearchAnd = Techs_UseAnd[0]->GetValue();
    ExcludeAnd = Techs_UseAnd[1]->GetValue();

    Techs_ListV->names.clear();
    Techs_ListV->indexes.clear();
    if(all)
    {
        tech_names.Clear();
        tech_names.Alloc(1 + dataset->Techages.size());
        tech_names.Add("-1 - None");
    }

    for(size_t loop = 0; loop < dataset->Techages.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetTechName(loop);
        if(SearchMatches(Name.Lower()))
        {
            Techs_ListV->names.Add(Name);
            Techs_ListV->indexes.push_back(loop);
        }
        if(all) tech_names.Add(Name);
    }

    RefreshList(Techs_ListV, &TechIDs);
    if(all) for(auto &list: TechComboBoxList) list->Flash();

    SearchAnd = ExcludeAnd = false;
}

void AGE_Frame::OnTechSelect(wxCommandEvent &event)
{
    if(!techTimer.IsRunning())
        techTimer.Start(150);
}

void AGE_Frame::OnTechTimer(wxTimerEvent&)
{
    techTimer.Stop();
    auto selections = Techs_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Techs_ListV, TechIDs);

    Techs_Name->clear();

    genie::Techage * TechPointer;
    for(auto loop = selections; loop--> 0;)
    {
        TechPointer = &dataset->Techages[TechIDs[loop]];
        Techs_Name->prepend(&TechPointer->Name);
    }
    SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected tech: "+lexical_cast<string>(TechIDs.front()), 0);

    Techs_Name->update();
    ListEffects();
}

void AGE_Frame::OnTechAdd(wxCommandEvent &event)    // Works.
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->Techages);
    ListTechs();
}

void AGE_Frame::OnTechInsert(wxCommandEvent &event) // Works.
{
    auto selections = Techs_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->Techages, TechIDs.front());
    ListTechs();
}

void AGE_Frame::OnTechDelete(wxCommandEvent &event) // Works.
{
    auto selections = Techs_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->Techages, TechIDs);
    ListTechs();
}

void AGE_Frame::OnTechCopy(wxCommandEvent &event)   // Works.
{
    auto selections = Techs_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Techages, TechIDs, copies.Tech);
    Techs_ListV->SetFocus();
}

void AGE_Frame::OnTechPaste(wxCommandEvent &event)  // Works.
{
    auto selections = Techs_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Techages, TechIDs, copies.Tech);
    ListTechs();
}

void AGE_Frame::OnTechPasteInsert(wxCommandEvent &event)    // Works.
{
    auto selections = Techs_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->Techages, TechIDs.front(), copies.Tech);
    ListTechs();
}

inline string Tester(genie::TechageEffect effect, string how)
{
    return ((effect.C == 8 || effect.C == 9) ? (effect.C == 8 ? "armor type " : "attack type ")
        + lexical_cast<string>((uint16_t)effect.D >> 8) + how + lexical_cast<string>(uint16_t((uint8_t)effect.D))
        : "attr " + lexical_cast<string>(effect.C) + how + lexical_cast<string>(effect.D))
        + ((effect.B == -1) ? " for unit " + lexical_cast<string>(effect.A) : " for class " + lexical_cast<string>(effect.B));
}

string AGE_Frame::GetEffectName(int effect, int tech)
{
    string Name = "";
    switch(dataset->Techages[tech].Effects[effect].Type)
    {
        case 10:
            Name = "Team ";
        case 0:
        {
            //Name = "Attribute Modifier (Set)";
            Name += "Set " + Tester(dataset->Techages[tech].Effects[effect], " to ");
            break;
        }
        case 11:
            Name = "Team ";
        case 1:
            //Name = "Resource Modifier (Set/+/-)";
            if(dataset->Techages[tech].Effects[effect].B == 0)
            {
                Name += "Set resource "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A)
                +" to "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].D);
            }
            else
            {
                Name += "Change resource "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A)
                +" by "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].D);
            }
            break;
        case 12:
            Name = "Team ";
        case 2:
            if(dataset->Techages[tech].Effects[effect].B == 0)
                Name += "Disable";
            else
                Name += "Enable";
            Name += " unit "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A);
            break;
        case 13:
            Name = "Team ";
        case 3:
            Name += "Upgrade unit "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A)
            +" to "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].B);
            break;
        case 14:
            Name = "Team ";
        case 4:
        {
            //Name = "Attribute Modifier (+/-)";
            Name += "Change " + Tester(dataset->Techages[tech].Effects[effect], " by ");
            break;
        }
        case 15:
            Name = "Team ";
        case 5:
        {
            //Name = "Attribute Modifier (Multiply)";
            Name += "Multiply " + Tester(dataset->Techages[tech].Effects[effect], " by ");
            break;
        }
        case 16:
            Name = "Team ";
        case 6:
            //Name = "Resource Modifier (Multiply)";
            Name += "Multiply resource "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A)
            +" by "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].D);
            break;
        case 101:
            //Name = "Research Cost Modifier (Set/+/-)";
            if(dataset->Techages[tech].Effects[effect].C == 0)
            {
                Name = "Set research "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A)
                +" cost type "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].B)
                +" to "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].D);
            }
            else
            {
                Name = "Change research "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A)
                +" cost type "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].B)
                +" by "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].D);
            }
            break;
        case 102:
            Name = "Disable research "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].D);
            break;
        case 103:
            //Name = "Research Time Modifier (Set/+/-)";
            if(dataset->Techages[tech].Effects[effect].C == 0)
            {
                Name = "Set research "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A)
                +" time to "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].D);
            }
            else
            {
                Name = "Change research "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A)
                +" time by "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].D);
            }
            break;
        default:
            Name = "No type/Invalid type";
    }
    return Name+" ";
}

void AGE_Frame::OnEffectsSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListEffects();
}

void AGE_Frame::ListEffects()
{
    InitSearch(Techs_Effects_Search->GetValue().MakeLower(), Techs_Effects_Search_R->GetValue().MakeLower());
    SearchAnd = Techs_Effects_UseAnd[0]->GetValue();
    ExcludeAnd = Techs_Effects_UseAnd[1]->GetValue();

    Techs_Effects_ListV->names.clear();
    Techs_Effects_ListV->indexes.clear();

    if(dataset->Techages.size())
    for(size_t loop = 0; loop < dataset->Techages[TechIDs.front()].Effects.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetEffectName(loop, TechIDs.front());
        if(SearchMatches(Name.Lower()))
        {
            Techs_Effects_ListV->names.Add(Name);
            Techs_Effects_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(Techs_Effects_ListV, &EffectIDs);

    SearchAnd = ExcludeAnd = false;

    wxTimerEvent E;
    OnEffectsTimer(E);
}

void AGE_Frame::OnEffectsSelect(wxCommandEvent &event)
{
    if(!effectTimer.IsRunning())
        effectTimer.Start(150);
}

void AGE_Frame::OnEffectsTimer(wxTimerEvent&)
{
    effectTimer.Stop();
    auto selections = Techs_Effects_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    for(auto &box: uiGroupTechEffect) box->clear();
    bool enableD = true;
    if(selections > 0)
    {
        getSelectedItems(selections, Techs_Effects_ListV, EffectIDs);
        Effects_Type_Holder->Show(true);

        genie::TechageEffect * EffectPointer;
        for(auto loop = selections; loop--> 0;)
        {
            EffectPointer = &dataset->Techages[TechIDs.front()].Effects[EffectIDs[loop]];
            Effects_Type->prepend(&EffectPointer->Type);
            Effects_A->prepend(&EffectPointer->A);
            Effects_B->prepend(&EffectPointer->B);
            Effects_C->prepend(&EffectPointer->C);
            Effects_D->prepend(&EffectPointer->D);
        }

        bool NeverHide = Effects_NeverHide->GetValue();
        switch(EffectPointer->Type)
        {
            case 0:
            case 10:
            {
                Effects_A_ComboBox->SwapList(&unit_names);
                Effects_A_ComboBox->Show(true);    // for effects 0, 2, 3, 4, 5
                Effects_B_CheckBox->Show(false);    // for effects 1, 2
                Effects_B_ComboBox->SwapList(&class_names);
                Effects_B_ComboBox->Show(true);    // for effects 0, 4, 5
                Effects_C_CheckBox->Show(false);    // for effects 101, 103
                Effects_C_ComboBox->Show(true);   // for effects 0, 4, 5
                Effects_D_ComboBox->Show(false);   // for effect 102
                Effects_A->Show(true);  // not for effect 102
                Effects_B->Show(true);  // not for effects 6, 102, 103
                Effects_C->Show(true);  // not for effects 1, 2, 3, 6, 102

                Effects_A_Text->SetLabel("Unit ");
                Effects_B_Text->SetLabel("Class ");
                Effects_C_Text->SetLabel("Attribute ");
                Effects_D_Text->SetLabel("Amount [Set] ");

                Effects_Info_B->SetLabel("");
                Effects_Info_C->SetLabel("");

                if(EffectPointer->C == 8 || EffectPointer->C == 9)
                {
                    enableD = NeverHide;
                    Effects_D->Show(false);
                    Effects_89_Amount->Show(true);
                    Effects_89_Amount->ChangeValue(lexical_cast<string>(uint16_t((uint8_t)EffectPointer->D))); // Correct value
                    Effects_89_Type->Show(true);
                    Effects_89_Type_CB1->Show(true);
                    uint16_t attack_type = (uint16_t)EffectPointer->D >> 8;
                    Effects_89_Type->ChangeValue(lexical_cast<string>(attack_type)); // Correct class
                    Effects_89_Type_CB1->SetSelection(attack_type);
                    Effects_89_Type_Text->SetLabel("Type ");
                }
                else
                {
                    Effects_D->Show(true);
                    Effects_89_Amount->Show(false);
                    Effects_89_Type->Show(false);
                    Effects_89_Type_CB1->Show(false);
                    Effects_89_Type_Text->SetLabel("");
                }
            }
            break;
            case 1:
            case 11:
            {
                Effects_A_ComboBox->SwapList(&resource_names);
                Effects_A_ComboBox->Show(true);    // for effects 1, 6
                Effects_B_CheckBox->Show(true); // for effects 1, 2
                Effects_B_ComboBox->Show(false);   // for effects 0, 3, 4, 5, 101
                Effects_C_CheckBox->Show(false);    // for effects 101, 103
                Effects_C_ComboBox->Show(false);  // for effects 0, 4, 5
                Effects_D_ComboBox->Show(false);   // for effect 102
                Effects_89_Type_CB1->Show(false); // only for attributes 8, 9
                Effects_A->Show(true);  // not for effect 102
                Effects_B->Show(true);  // not for effects 6, 102, 103
                Effects_C->Show(NeverHide); // not for effects 1, 2, 3, 6, 102
                Effects_D->Show(true);  // not for effects 2, 3
                Effects_89_Amount->Show(false); // only for attributes 8, 9
                Effects_89_Type->Show(false); // only for attributes 8, 9

                Effects_A_Text->SetLabel("Resource ");  /* add combo box */
                Effects_B_Text->SetLabel("Mode ");  /* add boolean [X]=1=Set [ ]=0=+/- */
                Effects_C_Text->SetLabel("Unused ");
                if(EffectPointer->B == 0) // unchecked
                {
                    Effects_D_Text->SetLabel("Amount [Set] ");
                }
                else
                {
                    Effects_D_Text->SetLabel("Amount [+/-] ");
                }
                Effects_89_Type_Text->SetLabel("");

                Effects_Info_B->SetLabel(" [ ] = Set, [X] = +/-");
                Effects_Info_C->SetLabel("");
            }
            break;
            case 2:
            case 12:
            {
                Effects_A_ComboBox->SwapList(&unit_names);
                Effects_A_ComboBox->Show(true);    // for effects 0, 2, 3, 4, 5
                Effects_B_CheckBox->Show(true); // for effects 1, 2
                Effects_B_ComboBox->Show(false);   // for effects 0, 3, 4, 5, 101
                Effects_C_CheckBox->Show(false);    // for effects 101, 103
                Effects_C_ComboBox->Show(false);  // for effects 0, 4, 5
                Effects_D_ComboBox->Show(false);   // for effect 102
                Effects_89_Type_CB1->Show(false); // only for attributes 8, 9
                Effects_A->Show(true);  // not for effect 102
                Effects_B->Show(true);  // not for effects 6, 102, 103
                Effects_C->Show(NeverHide); // not for effects 1, 2, 3, 6, 102
                Effects_D->Show(NeverHide); // not for effects 2, 3
                Effects_89_Amount->Show(false); // only for attributes 8, 9
                Effects_89_Type->Show(false); // only for attributes 8, 9

                Effects_A_Text->SetLabel("Unit ");  /* add combo box */
                Effects_B_Text->SetLabel("Mode ");  /* add boolean */
                Effects_C_Text->SetLabel("Unused ");
                Effects_D_Text->SetLabel("Unused ");
                Effects_89_Type_Text->SetLabel("");

                Effects_Info_B->SetLabel(" [ ] = Disable, [X] = Enable");
                Effects_Info_C->SetLabel("");
            }
            break;
            case 3:
            case 13:
            {
                Effects_A_ComboBox->SwapList(&unit_names);
                Effects_A_ComboBox->Show(true);    // for effects 0, 2, 3, 4, 5
                Effects_B_CheckBox->Show(false);    // for effects 1, 2
                Effects_B_ComboBox->SwapList(&unit_names);
                Effects_B_ComboBox->Show(true);    // for effect 3
                Effects_C_CheckBox->Show(false);    // for effects 101, 103
                Effects_C_ComboBox->Show(false);  // for effects 0, 4, 5
                Effects_D_ComboBox->Show(false);   // for effect 102
                Effects_89_Type_CB1->Show(false); // only for attributes 8, 9
                Effects_A->Show(true);  // not for effect 102
                Effects_B->Show(true);  // not for effects 6, 102, 103
                Effects_C->Show(NeverHide); // not for effects 1, 2, 3, 6, 102
                Effects_D->Show(NeverHide); // not for effects 2, 3
                Effects_89_Amount->Show(false); // only for attributes 8, 9
                Effects_89_Type->Show(false); // only for attributes 8, 9

                Effects_A_Text->SetLabel("Unit ");  /* add combo box */
                Effects_B_Text->SetLabel("To Unit ");   /* add combo box */
                Effects_C_Text->SetLabel("Unused ");
                Effects_D_Text->SetLabel("Unused ");
                Effects_89_Type_Text->SetLabel("");

                Effects_Info_B->SetLabel("");
                Effects_Info_C->SetLabel("");
            }
            break;
            case 4:
            case 14:
            {
                Effects_A_ComboBox->SwapList(&unit_names);
                Effects_A_ComboBox->Show(true);    // for effects 0, 2, 3, 4, 5
                Effects_B_CheckBox->Show(false);    // for effects 1, 2
                Effects_B_ComboBox->SwapList(&class_names);
                Effects_B_ComboBox->Show(true);    // for effects 0, 4, 5
                Effects_C_CheckBox->Show(false);    // for effects 101, 103
                Effects_C_ComboBox->Show(true);   // for effects 0, 4, 5
                Effects_D_ComboBox->Show(false);   // for effect 102
                Effects_A->Show(true);  // not for effect 102
                Effects_B->Show(true);  // not for effects 6, 102, 103
                Effects_C->Show(true);  // not for effects 1, 2, 3, 6, 102

                Effects_A_Text->SetLabel("Unit ");  /* add combo box */
                Effects_B_Text->SetLabel("Class "); /* add combo box */
                Effects_C_Text->SetLabel("Attribute "); /* add combo box */

                Effects_Info_B->SetLabel("");
                Effects_Info_C->SetLabel("");

                if(EffectPointer->C == 8 || EffectPointer->C == 9)
                {
                    enableD = NeverHide;
                    Effects_D->Show(false);
                    Effects_89_Amount->Show(true);
                    Effects_89_Amount->ChangeValue(lexical_cast<string>(uint16_t((uint8_t)EffectPointer->D))); // Correct value
                    Effects_89_Type->Show(true);
                    Effects_89_Type_CB1->Show(true);
                    uint16_t attack_type = (uint16_t)EffectPointer->D >> 8;
                    Effects_89_Type->ChangeValue(lexical_cast<string>(attack_type)); // Correct class
                    Effects_89_Type_CB1->SetSelection(attack_type);
                    Effects_D_Text->SetLabel("Amount [+] ");
                    Effects_89_Type_Text->SetLabel("Type ");
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
            }
            break;
            case 5:
            case 15:
            {
                Effects_A_ComboBox->SwapList(&unit_names);
                Effects_A_ComboBox->Show(true);    // for effects 0, 2, 3, 4, 5
                Effects_B_CheckBox->Show(false);    // for effects 1, 2
                Effects_B_ComboBox->SwapList(&class_names);
                Effects_B_ComboBox->Show(true);    // for effects 0, 4, 5
                Effects_C_CheckBox->Show(false);    // for effects 101, 103
                Effects_C_ComboBox->Show(true);   // for effects 0, 4, 5
                Effects_D_ComboBox->Show(false);   // for effect 102
                Effects_A->Show(true);  // not for effect 102
                Effects_B->Show(true);  // not for effects 6, 102, 103
                Effects_C->Show(true);  // not for effects 1, 2, 3, 6, 102

                Effects_A_Text->SetLabel("Unit ");  /* add combo box */
                Effects_B_Text->SetLabel("Class "); /* add combo box */
                Effects_C_Text->SetLabel("Attribute "); /* add combo box */

                Effects_Info_B->SetLabel("");
                Effects_Info_C->SetLabel("");

                if(EffectPointer->C == 8 || EffectPointer->C == 9)
                {
                    enableD = NeverHide;
                    Effects_D->Show(false);
                    Effects_89_Amount->Show(true);
                    Effects_89_Amount->ChangeValue(lexical_cast<string>(uint16_t((uint8_t)EffectPointer->D))); // Correct value
                    Effects_89_Type->Show(true);
                    Effects_89_Type_CB1->Show(true);
                    uint16_t attack_type = (uint16_t)EffectPointer->D >> 8;
                    Effects_89_Type->ChangeValue(lexical_cast<string>(attack_type)); // Correct class
                    Effects_89_Type_CB1->SetSelection(attack_type);
                    Effects_D_Text->SetLabel("Amount [%] ");
                    Effects_89_Type_Text->SetLabel("Type ");
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
            }
            break;
            case 6:
            case 16:
            {
                Effects_A_ComboBox->SwapList(&resource_names);
                Effects_A_ComboBox->Show(true);    // for effects 1, 6
                Effects_B_CheckBox->Show(false);    // for effects 1, 2
                Effects_B_ComboBox->Show(false);   // for effects 0, 3, 4, 5, 101
                Effects_C_CheckBox->Show(false);    // for effects 101, 103
                Effects_C_ComboBox->Show(false);  // for effects 0, 4, 5
                Effects_D_ComboBox->Show(false);   // for effect 102
                Effects_89_Type_CB1->Show(false); // only for attributes 8, 9
                Effects_A->Show(true);  // not for effect 102
                Effects_B->Show(NeverHide); // not for effects 6, 102, 103
                Effects_C->Show(NeverHide); // not for effects 1, 2, 3, 6, 102
                Effects_D->Show(true);  // not for effects 2, 3
                Effects_89_Amount->Show(false); // only for attributes 8, 9
                Effects_89_Type->Show(false); // only for attributes 8, 9

                Effects_A_Text->SetLabel("Resource ");  /* add combo box */
                Effects_B_Text->SetLabel("Unused ");
                Effects_C_Text->SetLabel("Unused ");
                Effects_D_Text->SetLabel("Amount [*] ");
                Effects_89_Type_Text->SetLabel("");

                Effects_Info_B->SetLabel("");
                Effects_Info_C->SetLabel("");
            }
            break;
            case 101:
            {
                Effects_A_ComboBox->SwapList(&research_names);
                Effects_A_ComboBox->Show(true);    // for effects 101, 103
                Effects_B_CheckBox->Show(false);    // for effects 1, 2
                Effects_B_ComboBox->SwapList(&resource_names);
                Effects_B_ComboBox->Show(true);    // for effect 101
                Effects_C_CheckBox->Show(true); // for effects 101, 103
                Effects_C_ComboBox->Show(false);  // for effects 0, 4, 5
                Effects_D_ComboBox->Show(false);   // for effect 102
                Effects_89_Type_CB1->Show(false); // only for attributes 8, 9
                Effects_A->Show(true);  // not for effect 102
                Effects_B->Show(true);  // not for effects 6, 102, 103
                Effects_C->Show(true);  // not for effects 1, 2, 3, 6, 102
                Effects_D->Show(true);  // not for effects 2, 3
                Effects_89_Amount->Show(false); // only for attributes 8, 9
                Effects_89_Type->Show(false); // only for attributes 8, 9

                Effects_A_Text->SetLabel("Research ");  /* add combo box */
                Effects_B_Text->SetLabel("Resource ");  /* add combo box */
                Effects_C_Text->SetLabel("Mode ");
                if(EffectPointer->C == 0) // unchecked
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
            }
            break;
            case 102:
            {
                Effects_A_ComboBox->Show(false);   // for effects 0 - 6, 101, 103
                Effects_B_CheckBox->Show(false);    // for effects 1, 2
                Effects_B_ComboBox->Show(false);   // for effects 0, 3, 4, 5, 101
                Effects_C_CheckBox->Show(false);    // for effects 101, 103
                Effects_C_ComboBox->Show(false);  // for effects 0, 4, 5
                Effects_D_ComboBox->Show(true);    // for effect 102
                Effects_89_Type_CB1->Show(false); // only for attributes 8, 9
                Effects_A->Show(NeverHide); // not for effect 102
                Effects_B->Show(NeverHide); // not for effects 6, 102, 103
                Effects_C->Show(NeverHide); // not for effects 1, 2, 3, 6, 102
                Effects_D->Show(true);  // not for effects 2, 3
                Effects_89_Amount->Show(false); // only for attributes 8, 9
                Effects_89_Type->Show(false); // only for attributes 8, 9

                Effects_A_Text->SetLabel("Unused ");
                Effects_B_Text->SetLabel("Unused ");
                Effects_C_Text->SetLabel("Unused ");
                Effects_D_Text->SetLabel("Research ");  /* add combo box */
                Effects_89_Type_Text->SetLabel("");

                Effects_Info_B->SetLabel("");
                Effects_Info_C->SetLabel("");
            }
            break;
            case 103:
            {
                Effects_A_ComboBox->SwapList(&research_names);
                Effects_A_ComboBox->Show(true);    // for effects 101, 103
                Effects_B_CheckBox->Show(false);    // for effects 1, 2
                Effects_B_ComboBox->Show(false);   // for effects 0, 3, 4, 5, 101
                Effects_C_CheckBox->Show(true); // for effects 101, 103
                Effects_C_ComboBox->Show(false);  // for effects 0, 4, 5
                Effects_D_ComboBox->Show(false);   // for effect 102
                Effects_89_Type_CB1->Show(false); // only for attributes 8, 9
                Effects_A->Show(true);  // not for effect 102
                Effects_B->Show(NeverHide); // not for effects 6, 102, 103
                Effects_C->Show(true);  // not for effects 1, 2, 3, 6, 102
                Effects_D->Show(true);  // not for effects 2, 3
                Effects_89_Amount->Show(false); // only for attributes 8, 9
                Effects_89_Type->Show(false); // only for attributes 8, 9

                Effects_A_Text->SetLabel("Research ");  /* add combo box */
                Effects_B_Text->SetLabel("Unused ");
                Effects_C_Text->SetLabel("Mode ");  /* add boolean */
                if(EffectPointer->C == 0) // unchecked
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
            }
            break;
            default:
            {
                Effects_A_ComboBox->Show(false);   // for effects 0 - 6, 101, 103
                Effects_B_CheckBox->Show(false);    // for effects 1, 2
                Effects_B_ComboBox->Show(false);   // for effects 0, 3, 4, 5, 101
                Effects_C_CheckBox->Show(false);    // for effects 101, 103
                Effects_C_ComboBox->Show(false);  // for effects 0, 4, 5
                Effects_D_ComboBox->Show(false);   // for effect 102
                Effects_89_Type_CB1->Show(false); // only for attributes 8, 9
                Effects_A->Show(NeverHide); // not for effect 102
                Effects_B->Show(NeverHide); // not for effects 6, 102, 103
                Effects_C->Show(NeverHide); // not for effects 1, 2, 3, 6, 102
                Effects_D->Show(NeverHide); // not for effects 2, 3
                Effects_89_Amount->Show(false); // only for attributes 8, 9
                Effects_89_Type->Show(false); // only for attributes 8, 9

                Effects_A_Text->SetLabel("Attribute A ");
                Effects_B_Text->SetLabel("Attribute B ");
                Effects_C_Text->SetLabel("Attribute C ");
                Effects_D_Text->SetLabel("Attribute D ");
                Effects_89_Type_Text->SetLabel("");

                Effects_Info_B->SetLabel("");
                Effects_Info_C->SetLabel("");
            }
        }
    }
    else
    {
        Effects_Type_Holder->Show(false);
        Effects_A_ComboBox->Show(false);   // for effects 0 - 6, 101, 103
        Effects_B_CheckBox->Show(false);    // for effects 1, 2
        Effects_B_ComboBox->Show(false);   // for effects 0, 3, 4, 5, 101
        Effects_C_CheckBox->Show(false);    // for effects 101, 103
        Effects_C_ComboBox->Show(false);  // for effects 0, 4, 5
        Effects_D_ComboBox->Show(false);   // for effect 102
        Effects_89_Type_CB1->Show(false); // only for attributes 8, 9
        Effects_A->Show(false); // not for effect 102
        Effects_B->Show(false); // not for effects 6, 102, 103
        Effects_C->Show(false); // not for effects 1, 2, 3, 6, 102
        Effects_D->Show(false); // not for effects 2, 3
        Effects_89_Amount->Show(false); // only for attributes 8, 9
        Effects_89_Type->Show(false); // only for attributes 8, 9
        Effects_A_Text->SetLabel("Select effect first ");
        Effects_B_Text->SetLabel("");
        Effects_C_Text->SetLabel("");
        Effects_D_Text->SetLabel("");
        Effects_89_Type_Text->SetLabel("");
        Effects_Info_B->SetLabel("");
        Effects_Info_C->SetLabel("");
    }
    for(auto &box: uiGroupTechEffect) box->update();
    Effects_D->Enable(enableD);
    Effects_Type_Holder->Layout();
    Effects_Data_Holder->Layout();
//  Refresh(); // Too much lag.
}

void AGE_Frame::OnEffectsAdd(wxCommandEvent &event) // Works.
{
    auto selections = Techs_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->Techages[TechIDs.front()].Effects);
    ListEffects();
}

void AGE_Frame::OnEffectsInsert(wxCommandEvent &event)  // Works.
{
    auto selections = Techs_Effects_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->Techages[TechIDs.front()].Effects, EffectIDs.front());
    ListEffects();
}

void AGE_Frame::OnEffectsDelete(wxCommandEvent &event)  // Works.
{
    auto selections = Techs_Effects_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->Techages[TechIDs.front()].Effects, EffectIDs);
    ListEffects();
}

void AGE_Frame::OnEffectsCopy(wxCommandEvent &event)    // Works.
{
    auto selections = Techs_Effects_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Techages[TechIDs.front()].Effects, EffectIDs, copies.Effect);
    Techs_Effects_ListV->SetFocus();
}

void AGE_Frame::OnEffectsPaste(wxCommandEvent &event)   // Works.
{
    auto selections = Techs_Effects_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Techages[TechIDs.front()].Effects, EffectIDs, copies.Effect);
    ListEffects();
}

void AGE_Frame::OnEffectsPasteInsert(wxCommandEvent &event) // Works.
{
    auto selections = Techs_Effects_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->Techages[TechIDs.front()].Effects, EffectIDs.front(), copies.Effect);
    ListEffects();
}

void AGE_Frame::OnEffectsCopyToTechs(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TechIDs.size(); ++loop)
    {
        dataset->Techages[TechIDs[loop]].Effects = dataset->Techages[TechIDs.front()].Effects;
    }
}

void AGE_Frame::LoadAllTechEffects(wxCommandEvent &event)
{
    wxString Name;
    InitSearch(Techs_AllEffects_Search->GetValue().MakeLower(), Techs_AllEffects_Search_R->GetValue().MakeLower());
    SearchAnd = Techs_AllEffects_UseAnd[0]->GetValue();
    ExcludeAnd = Techs_AllEffects_UseAnd[1]->GetValue();

    Techs_AllEffects_ListV->names.clear();

    for(short tech = 0; tech < dataset->Techages.size(); ++tech)
    {
        for(short effect = 0; effect < dataset->Techages[tech].Effects.size(); ++effect)
        {
            Name = " T"+lexical_cast<string>(tech)+" E"+lexical_cast<string>(effect)+" - "+GetEffectName(effect, tech);
            if(SearchMatches(Name.Lower()))
            {
                Techs_AllEffects_ListV->names.Add(Name);
            }
        }
    }

    RefreshList(Techs_AllEffects_ListV);
    //Techs_AllEffects_ListV->SetFocus(); You need to check if searched or not.

    SearchAnd = ExcludeAnd = false;

    wxTimerEvent E;
    OnAllTechEffectTimer(E);
}

void AGE_Frame::ClearAllTechEffects(wxCommandEvent &event)
{
    Techs_Search->SetValue("");
    Techs_Effects_Search->SetValue("");
}

void AGE_Frame::OnAllTechEffectSelect(wxCommandEvent &event)
{
    if(!allEffectsTimer.IsRunning())
        allEffectsTimer.Start(150);
}

void AGE_Frame::OnAllTechEffectTimer(wxTimerEvent&)
{
    allEffectsTimer.Stop();
    SearchAllSubVectors(Techs_AllEffects_ListV, Techs_Search, Techs_Effects_Search);
}

void AGE_Frame::CreateTechControls()
{
    Tab_Techs = new wxPanel(TabBar_Main);

    Techs_Main = new wxBoxSizer(wxHORIZONTAL);
    Techs_Buttons = new wxGridSizer(3, 0, 0);
    Effects_DataArea = new wxBoxSizer(wxVERTICAL);
    Effects_ListArea = new wxBoxSizer(wxVERTICAL);
    Techs_Effects_Buttons = new wxGridSizer(3, 0, 0);
    Effects_DataAreaProperties = new wxBoxSizer(wxVERTICAL);
    Techs_Techs = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Technologies");
    Techs_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
    Techs_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
    Techs_Search = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_UseAnd[0] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_Search_R = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_UseAnd[1] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_ListV = new AGEListView(Tab_Techs, wxSize(200, 100));
    Techs_Add = new wxButton(Tab_Techs, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Techs_Insert = new wxButton(Tab_Techs, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Techs_Delete = new wxButton(Tab_Techs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Techs_Copy = new wxButton(Tab_Techs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Techs_Paste = new wxButton(Tab_Techs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Techs_PasteInsert = new wxButton(Tab_Techs, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Techs_Rename = new wxButton(Tab_Techs, wxID_ANY, "Rename technologies");
    Techs_Restore = new wxButton(Tab_Techs, wxID_ANY, "Rename for GeniEd 2");

    Techs_Name_Text = new SolidText(Tab_Techs, " Technology Name");
    Techs_Name = AGETextCtrl::init(CString, NULL, this, &popUp, Tab_Techs, 31);

    Techs_Effects = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Effects");
    Techs_Effects_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
    Techs_Effects_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
    Techs_Effects_Search = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_Effects_UseAnd[0] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_Effects_Search_R = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_Effects_UseAnd[1] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_Effects_ListV = new AGEListView(Tab_Techs, wxSize(200, 100));
    Techs_Effects_Add = new wxButton(Tab_Techs, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_Insert = new wxButton(Tab_Techs, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_Delete = new wxButton(Tab_Techs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_Copy = new wxButton(Tab_Techs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_Paste = new wxButton(Tab_Techs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_PasteInsert = new wxButton(Tab_Techs, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Techs_Effects_CopyToTechs = new wxButton(Tab_Techs, wxID_ANY, "Copy all to selected techs", wxDefaultPosition, wxSize(10, -1));

    Effects_Type_Holder = new wxBoxSizer(wxVERTICAL);
    Effects_Type2_Holder = new wxBoxSizer(wxHORIZONTAL);
    Effects_Type_Text = new SolidText(Tab_Techs, " Effect Type *");
    Effects_Type = AGETextCtrl::init(CByte, &uiGroupTechEffect, this, &popUp, Tab_Techs);
    Effects_Type->SetToolTip("101 and 103 are only for\ntech tree and team bonus");
    Effects_Type_ComboBox = new ComboBox_EffectType(Tab_Techs, Effects_Type, &effect_type_names);
    Effects_Data_Holder = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Effect Attributes");
    Effects_NeverHide = new wxCheckBox(Tab_Techs, wxID_ANY, "Never hide attributes", wxDefaultPosition, wxDefaultSize);
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
    Effects_A = AGETextCtrl::init(CShort, &uiGroupTechEffect, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
    Effects_A_ComboBox = new ComboBox_Plus1(Tab_Techs, Effects_A, &unit_names);
    UnitComboBoxList.push_back(Effects_A_ComboBox);
    ResourceComboBoxList.push_back(Effects_A_ComboBox);
    ResearchComboBoxList.push_back(Effects_A_ComboBox);
    Effects_Info_A = new SolidText(Tab_Techs, "");
    Effects_B_Text = new SolidText(Tab_Techs, "Attribute B ", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(100, -1));
    Effects_B = AGETextCtrl::init(CShort, &uiGroupTechEffect, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
    Effects_B_Boxes = new wxBoxSizer(wxHORIZONTAL);
    Effects_B_CheckBox = new CheckBox_2State(Tab_Techs, "", Effects_B);
    Effects_B_ComboBox = new ComboBox_Plus1(Tab_Techs, Effects_B, &class_names);
    UnitComboBoxList.push_back(Effects_B_ComboBox);
    ResourceComboBoxList.push_back(Effects_B_ComboBox);
    Effects_Info_B = new SolidText(Tab_Techs, " Info B");
    Effects_C_Text = new SolidText(Tab_Techs, "Attribute C ", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(100, -1));
    Effects_C = AGETextCtrl::init(CShort, &uiGroupTechEffect, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
    Effects_C_Boxes = new wxBoxSizer(wxHORIZONTAL);
    Effects_C_CheckBox = new CheckBox_2State(Tab_Techs, "", Effects_C);
    Effects_C_ComboBox = new ComboBox_EffectAttribute(Tab_Techs, Effects_C, &effect_attribute_names);
    Effects_Info_C = new SolidText(Tab_Techs, " Info C");
    Effects_D_Text = new SolidText(Tab_Techs, "Attribute D ", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(100, -1));
    Effects_D = AGETextCtrl::init(CFloat, &uiGroupTechEffect, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
    Effects_D_Boxes = new wxBoxSizer(wxHORIZONTAL);
    Effects_D_ComboBox = new ComboBox_Plus1(Tab_Techs, Effects_D, &research_names);
    ResearchComboBoxList.push_back(Effects_D_ComboBox);
    Effects_Info_D = new SolidText(Tab_Techs, "");
    Effects_89_Amount = AGETextCtrl::init(CUByte, NULL, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
    Effects_89_Type_Text = new SolidText(Tab_Techs, "Type ", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(100, -1));
    Effects_89_Type = AGETextCtrl::init(CUByte, 0, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
    Effects_89_Type_CB1 = new ComboBox_Plus1(Tab_Techs, Effects_89_Type, &armor_names);

    Techs_AllEffects = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Effects of all Technologies");
    Techs_AllEffects_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
    Techs_AllEffects_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
    Techs_AllEffects_Search = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_AllEffects_UseAnd[0] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_AllEffects_Search_R = new wxTextCtrl(Tab_Techs, wxID_ANY);
    Techs_AllEffects_UseAnd[1] = new wxCheckBox(Tab_Techs, wxID_ANY, "And");
    Techs_AllEffects_ListV = new AGEListView(Tab_Techs, wxSize(200, 100));
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
    Techs_Searches[0]->Add(Techs_UseAnd[0], 0, wxEXPAND | wxLEFT, 2);
    Techs_Searches[1]->Add(Techs_Search_R, 1, wxEXPAND);
    Techs_Searches[1]->Add(Techs_UseAnd[1], 0, wxEXPAND | wxLEFT, 2);
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
    Techs_Effects_Searches[0]->Add(Techs_Effects_UseAnd[0], 0, wxEXPAND | wxLEFT, 2);
    Techs_Effects_Searches[1]->Add(Techs_Effects_Search_R, 1, wxEXPAND);
    Techs_Effects_Searches[1]->Add(Techs_Effects_UseAnd[1], 0, wxEXPAND | wxLEFT, 2);
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
    Techs_AllEffects_Searches[0]->Add(Techs_AllEffects_UseAnd[0], 0, wxEXPAND | wxLEFT, 2);
    Techs_AllEffects_Searches[1]->Add(Techs_AllEffects_Search_R, 1, wxEXPAND);
    Techs_AllEffects_Searches[1]->Add(Techs_AllEffects_UseAnd[1], 0, wxEXPAND | wxLEFT, 2);
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

    Effects_89_Amount->Show(false); // only for attributes 8, 9
    Effects_89_Type->Show(false); // only for attributes 8, 9
    Effects_A_ComboBox->Show(false);   // for effects 0 - 6, 101, 103
    Effects_B_CheckBox->Show(false);    // for effects 1, 2
    Effects_B_ComboBox->Show(false);   // for effects 0, 3, 4, 5, 101
    Effects_C_CheckBox->Show(false);    // for effects 101, 103
    Effects_C_ComboBox->Show(false);  // for effects 0, 4, 5
    Effects_D_ComboBox->Show(false);   // for effect 102
    Effects_89_Type_CB1->Show(false); // only for attributes 8, 9

    Tab_Techs->SetSizer(Techs_Main);

    for(size_t loop = 0; loop < 2; ++loop)
    {
        Techs_UseAnd[loop]->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &AGE_Frame::OnTechSearch, this);
        Techs_Effects_UseAnd[loop]->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &AGE_Frame::OnEffectsSearch, this);
        Techs_AllEffects_UseAnd[loop]->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &AGE_Frame::LoadAllTechEffects, this);
    }
    Techs_Rename->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTechRename, this);
    Techs_Restore->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTechRenameGE2, this);
    Techs_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTechSelect, this);
    Techs_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTechSelect, this);
    Techs_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTechSelect, this);
    Techs_Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTechSearch, this);
    Techs_Search_R->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTechSearch, this);
    Techs_Effects_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnEffectsSelect, this);
    Techs_Effects_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnEffectsSelect, this);
    Techs_Effects_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnEffectsSelect, this);
    Techs_Effects_Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnEffectsSearch, this);
    Techs_Effects_Search_R->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnEffectsSearch, this);
    Techs_Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTechAdd, this);
    Techs_Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTechInsert, this);
    Techs_Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTechDelete, this);
    Techs_Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTechCopy, this);
    Techs_Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTechPaste, this);
    Techs_PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTechPasteInsert, this);
    Techs_Effects_Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnEffectsAdd, this);
    Techs_Effects_Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnEffectsInsert, this);
    Techs_Effects_Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnEffectsDelete, this);
    Techs_Effects_Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnEffectsCopy, this);
    Techs_Effects_Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnEffectsPaste, this);
    Techs_Effects_PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnEffectsPasteInsert, this);
    Techs_Effects_CopyToTechs->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnEffectsCopyToTechs, this);
    Effects_89_Amount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_89_Type->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Techs_AllEffects_Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::LoadAllTechEffects, this);
    Techs_AllEffects_Search_R->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::LoadAllTechEffects, this);
    Techs_AllEffects_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnAllTechEffectSelect, this);
    Techs_AllEffects_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnAllTechEffectSelect, this);
    Techs_AllEffects_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnAllTechEffectSelect, this);
    Techs_AllEffects_Load->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::LoadAllTechEffects, this);
    Techs_AllEffects_Clear->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::ClearAllTechEffects, this);

    techTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTechTimer, this);
    effectTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnEffectsTimer, this);
    allEffectsTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnAllTechEffectTimer, this);
    Techs_Name->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_Type->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_Type_ComboBox->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_Techs, this);
    Effects_A->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_B->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_C->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_D->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Techs, this);
    Effects_A_ComboBox->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_Techs, this);
    Effects_B_CheckBox->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &AGE_Frame::OnUpdateCheck_Techs, this);
    Effects_B_ComboBox->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_Techs, this);
    Effects_C_CheckBox->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &AGE_Frame::OnUpdateCheck_Techs, this);
    Effects_C_ComboBox->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_Techs, this);
    Effects_D_ComboBox->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_Techs, this);
    Effects_89_Type_CB1->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_Techs, this);
}

void AGE_Frame::OnKillFocus_Techs(wxFocusEvent &event)
{
    event.Skip();
    if(event.GetId() == Effects_89_Amount->GetId() || event.GetId() == Effects_89_Type->GetId())
    {
        if(!Effects_89_Amount->IsEmpty() && !Effects_89_Type->IsEmpty()) // if has something, then update float value.
        {
            uint16_t Class = lexical_cast<int>(Effects_89_Type->GetValue()) << 8;
            uint8_t Amount = lexical_cast<int>(Effects_89_Amount->GetValue());
            Effects_D->ChangeValue(lexical_cast<string>(Amount + Class));
            Effects_D->SaveEdits();
        }
        ListEffects();
        return;
    }
    if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
    if(event.GetId() == Techs_Name->GetId())
    {
        ListTechs();
    }
    else
    {
        ListEffects();
    }
}

void AGE_Frame::OnUpdateCheck_Techs(wxCommandEvent &event)
{
    ((AGELinkedBox*)event.GetEventObject())->OnChoose(event);
    ListEffects();
}

void AGE_Frame::OnUpdateCombo_Techs(wxCommandEvent &event)
{
    if(event.GetId() == Effects_89_Type_CB1->GetId())
    {
        uint16_t Class = (Effects_89_Type_CB1->GetSelection() - 1) << 8;
        uint8_t Amount = lexical_cast<int>(Effects_89_Amount->GetValue());
        Effects_D->ChangeValue(lexical_cast<string>(Amount + Class));
        Effects_D->SaveEdits();

        ListEffects();
        return;
    }
    ((AGELinkedBox*)event.GetEventObject())->OnChoose(event);
    ListEffects();
}
