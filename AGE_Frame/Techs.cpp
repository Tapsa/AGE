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

	wxArrayString names;
	if(all) names.Alloc(dataset->Techages.size());

	for(size_t loop = 0; loop < dataset->Techages.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTechName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Techs_ListV->names.Add(Name);
			Techs_ListV->indexes.push_back(loop);
		}
		if(all) names.Add(Name);
	}

	virtualListing(Techs_ListV);
	if(all) FillLists(TechComboBoxList, names);

	SearchAnd = ExcludeAnd = false;
}

void AGE_Frame::OnTechSelect(wxCommandEvent &event)
{
    if(!techTimer.IsRunning())
        techTimer.Start(150);
}

void AGE_Frame::OnTechTimer(wxTimerEvent &event)
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

void AGE_Frame::OnTechAdd(wxCommandEvent &event)	// Works.
{
	if(!dataset) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->Techages);
	ListTechs();
}

void AGE_Frame::OnTechInsert(wxCommandEvent &event)	// Works.
{
	auto selections = Techs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->Techages, TechIDs.front());
	ListTechs();
}

void AGE_Frame::OnTechDelete(wxCommandEvent &event)	// Works.
{
	auto selections = Techs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->Techages, TechIDs);
	ListTechs();
}

void AGE_Frame::OnTechCopy(wxCommandEvent &event)	// Works.
{
	auto selections = Techs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->Techages, TechIDs, copies.Tech);
	Techs_ListV->SetFocus();
}

void AGE_Frame::OnTechPaste(wxCommandEvent &event)	// Works.
{
	auto selections = Techs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Techages, TechIDs, copies.Tech);
    ListTechs();
}

void AGE_Frame::OnTechPasteInsert(wxCommandEvent &event)	// Works.
{
	auto selections = Techs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->Techages, TechIDs.front(), copies.Tech);
	ListTechs();
}

string AGE_Frame::GetEffectName(int effect, int tech)
{
	string Name = "";
	switch(dataset->Techages[tech].Effects[effect].Type)
	{
		case 10:
			Name = "Team ";
		case 0:
			//Name = "Attribute Modifier (Set)";
			Name += "Set attr. "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].C)
			+" to "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].D)+" for ";
			if(dataset->Techages[tech].Effects[effect].B == -1)
				Name += "unit "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A);
			else
				Name += "class "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].B);
			break;
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
			//Name = "Attribute Modifier (+/-)";
			Name += "Change attr. "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].C)
			+" by "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].D)+" for ";
			if(dataset->Techages[tech].Effects[effect].B == -1)
				Name += "unit "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A);
			else
				Name += "class "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].B);
			break;
		case 15:
			Name = "Team ";
		case 5:
			//Name = "Attribute Modifier (Multiply)";
			Name += "Multiply attr. "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].C)
			+" by "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].D)+" for ";
			if(dataset->Techages[tech].Effects[effect].B == -1)
				Name += "unit "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].A);
			else
				Name += "class "+lexical_cast<string>(dataset->Techages[tech].Effects[effect].B);
			break;
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
	virtualListing(Techs_Effects_ListV);

	SearchAnd = ExcludeAnd = false;

	wxTimerEvent E;
	OnEffectsTimer(E);
}

void AGE_Frame::OnEffectsSelect(wxCommandEvent &event)
{
    if(!effectTimer.IsRunning())
        effectTimer.Start(150);
}

void AGE_Frame::OnEffectsTimer(wxTimerEvent &event)
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
				Effects_UnitsA_ComboBox->Show(true);	// for Effects 0, 2, 3, 4, 5
				Effects_ResourcesA_ComboBox->Show(false);	// for Effects 1, 6
				Effects_ResearchsA_ComboBox->Show(false);	// for Effects 101, 103
				Effects_ModeB_CheckBox->Show(false);	// for Effects 1, 2
				Units_Class_ComboBox[2]->Show(true);	// for Effects 0, 4, 5
				Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
				Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
				Effects_ModeC_CheckBox->Show(false);	// for Effects 101, 103
				Effects_AttributesC_ComboBox->Show(true);	// for Effects 0, 4, 5
				Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(true);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3

				Effects_A_Text->SetLabel("Unit ");
				Effects_B_Text->SetLabel("Class ");
				Effects_C_Text->SetLabel("Attribute ");
				Effects_D_Text->SetLabel("Amount [Set] ");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");

				if(EffectPointer->C == 8 || EffectPointer->C == 9)
				{
					enableD = NeverHide;
					Effects_E->Show(true);
					Effects_E->ChangeValue(lexical_cast<string>(fmod(EffectPointer->D, 256))); // Correct value
					Effects_F->Show(true);
					Attacks_Class_ComboBox[2]->Show(true);
					Attacks_Class_ComboBox[2]->SetSelection(0);
					if(EffectPointer->D < 0)
					{
						Effects_F->ChangeValue(lexical_cast<string>(-(short)EffectPointer->D / 256)); // Correct class
						Attacks_Class_ComboBox[2]->SetSelection(-(short)EffectPointer->D / 256 + 1);
					}
					else
					{
						Effects_F->ChangeValue(lexical_cast<string>((short)EffectPointer->D / 256)); // Correct class
						Attacks_Class_ComboBox[2]->SetSelection((short)EffectPointer->D / 256 + 1);
					}
					Effects_E_Text->SetLabel("Amount [Set] ");
					Effects_F_Text->SetLabel("Type ");
					Effects_Info_E->SetLabel(" [0 to 255]");
					Effects_Info_F->SetLabel("");
				}
				else
				{
					Effects_E->Show(false);
					Effects_F->Show(false);
					Attacks_Class_ComboBox[2]->Show(false);
					Effects_E_Text->SetLabel("");
					Effects_F_Text->SetLabel("");
					Effects_Info_E->SetLabel("");
					Effects_Info_F->SetLabel("");
				}
			}
			break;
			case 1:
			case 11:
			{
				Effects_UnitsA_ComboBox->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ResourcesA_ComboBox->Show(true);	// for Effects 1, 6
				Effects_ResearchsA_ComboBox->Show(false);	// for Effects 101, 103
				Effects_ModeB_CheckBox->Show(true);	// for Effects 1, 2
				Units_Class_ComboBox[2]->Show(false);	// for Effects 0, 4, 5
				Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
				Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
				Effects_ModeC_CheckBox->Show(false);	// for Effects 101, 103
				Effects_AttributesC_ComboBox->Show(false);	// for Effects 0, 4, 5
				Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
				Attacks_Class_ComboBox[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_A_Text->SetLabel("Resource ");	/* add combo box */
				Effects_B_Text->SetLabel("Mode ");	/* add boolean [X]=1=Set [ ]=0=+/- */
				Effects_C_Text->SetLabel("Unused ");
				if(EffectPointer->B == 0) // unchecked
				{
					Effects_D_Text->SetLabel("Amount [Set] ");
				}
				else
				{
					Effects_D_Text->SetLabel("Amount [+/-] ");
				}
				Effects_E_Text->SetLabel("");
				Effects_F_Text->SetLabel("");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel(" [ ] = Set, [X] = +/-");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");
				Effects_Info_E->SetLabel("");
				Effects_Info_F->SetLabel("");
			}
			break;
			case 2:
			case 12:
			{
				Effects_UnitsA_ComboBox->Show(true);	// for Effects 0, 2, 3, 4, 5
				Effects_ResourcesA_ComboBox->Show(false);	// for Effects 1, 6
				Effects_ResearchsA_ComboBox->Show(false);	// for Effects 101, 103
				Effects_ModeB_CheckBox->Show(true);	// for Effects 1, 2
				Units_Class_ComboBox[2]->Show(false);	// for Effects 0, 4, 5
				Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
				Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
				Effects_ModeC_CheckBox->Show(false);	// for Effects 101, 103
				Effects_AttributesC_ComboBox->Show(false);	// for Effects 0, 4, 5
				Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
				Attacks_Class_ComboBox[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(NeverHide);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_A_Text->SetLabel("Unit ");	/* add combo box */
				Effects_B_Text->SetLabel("Mode ");	/* add boolean */
				Effects_C_Text->SetLabel("Unused ");
				Effects_D_Text->SetLabel("Unused ");
				Effects_E_Text->SetLabel("");
				Effects_F_Text->SetLabel("");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel(" [ ] = Disable, [X] = Enable");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");
				Effects_Info_E->SetLabel("");
				Effects_Info_F->SetLabel("");
			}
			break;
			case 3:
			case 13:
			{
				Effects_UnitsA_ComboBox->Show(true);	// for Effects 0, 2, 3, 4, 5
				Effects_ResourcesA_ComboBox->Show(false);	// for Effects 1, 6
				Effects_ResearchsA_ComboBox->Show(false);	// for Effects 101, 103
				Effects_ModeB_CheckBox->Show(false);	// for Effects 1, 2
				Units_Class_ComboBox[2]->Show(false);	// for Effects 0, 4, 5
				Effects_UnitsB_ComboBox->Show(true);	// for Effects 3
				Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
				Effects_ModeC_CheckBox->Show(false);	// for Effects 101, 103
				Effects_AttributesC_ComboBox->Show(false);	// for Effects 0, 4, 5
				Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
				Attacks_Class_ComboBox[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(NeverHide);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_A_Text->SetLabel("Unit ");	/* add combo box */
				Effects_B_Text->SetLabel("To Unit ");	/* add combo box */
				Effects_C_Text->SetLabel("Unused ");
				Effects_D_Text->SetLabel("Unused ");
				Effects_E_Text->SetLabel("");
				Effects_F_Text->SetLabel("");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");
				Effects_Info_E->SetLabel("");
				Effects_Info_F->SetLabel("");
			}
			break;
			case 4:
			case 14:
			{
				Effects_UnitsA_ComboBox->Show(true);	// for Effects 0, 2, 3, 4, 5
				Effects_ResourcesA_ComboBox->Show(false);	// for Effects 1, 6
				Effects_ResearchsA_ComboBox->Show(false);	// for Effects 101, 103
				Effects_ModeB_CheckBox->Show(false);	// for Effects 1, 2
				Units_Class_ComboBox[2]->Show(true);	// for Effects 0, 4, 5
				Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
				Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
				Effects_ModeC_CheckBox->Show(false);	// for Effects 101, 103
				Effects_AttributesC_ComboBox->Show(true);	// for Effects 0, 4, 5
				Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(true);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3

				Effects_A_Text->SetLabel("Unit ");	/* add combo box */
				Effects_B_Text->SetLabel("Class ");	/* add combo box */
				Effects_C_Text->SetLabel("Attribute ");	/* add combo box */
				Effects_D_Text->SetLabel("Amount [+/-] ");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");

				if(EffectPointer->C == 8 || EffectPointer->C == 9)
				{
					enableD = NeverHide;
					Effects_E->Show(true);
					Effects_E->ChangeValue(lexical_cast<string>(fmod(EffectPointer->D, 256))); // Correct value
					Effects_F->Show(true);
					Attacks_Class_ComboBox[2]->Show(true);
					Attacks_Class_ComboBox[2]->SetSelection(0);
					if(EffectPointer->D < 0)
					{
						Effects_F->ChangeValue(lexical_cast<string>(-(short)EffectPointer->D / 256)); // Correct class
						Attacks_Class_ComboBox[2]->SetSelection(-(short)EffectPointer->D / 256 + 1);
					}
					else
					{
						Effects_F->ChangeValue(lexical_cast<string>((short)EffectPointer->D / 256)); // Correct class
						Attacks_Class_ComboBox[2]->SetSelection((short)EffectPointer->D / 256 + 1);
					}
					Effects_E_Text->SetLabel("Amount [+/-] ");
					Effects_F_Text->SetLabel("Type ");
					Effects_Info_E->SetLabel(" [0 to 255]");
					Effects_Info_F->SetLabel("");
				}
				else
				{
					Effects_E->Show(false);
					Effects_F->Show(false);
					Attacks_Class_ComboBox[2]->Show(false);
					Effects_E_Text->SetLabel("");
					Effects_F_Text->SetLabel("");
					Effects_Info_E->SetLabel("");
					Effects_Info_F->SetLabel("");
				}
			}
			break;
			case 5:
			case 15:
			{
				Effects_UnitsA_ComboBox->Show(true);	// for Effects 0, 2, 3, 4, 5
				Effects_ResourcesA_ComboBox->Show(false);	// for Effects 1, 6
				Effects_ResearchsA_ComboBox->Show(false);	// for Effects 101, 103
				Effects_ModeB_CheckBox->Show(false);	// for Effects 1, 2
				Units_Class_ComboBox[2]->Show(true);	// for Effects 0, 4, 5
				Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
				Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
				Effects_ModeC_CheckBox->Show(false);	// for Effects 101, 103
				Effects_AttributesC_ComboBox->Show(true);	// for Effects 0, 4, 5
				Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(true);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3

				Effects_A_Text->SetLabel("Unit ");	/* add combo box */
				Effects_B_Text->SetLabel("Class ");	/* add combo box */
				Effects_C_Text->SetLabel("Attribute ");	/* add combo box */
				Effects_D_Text->SetLabel("Amount [*] ");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");

				if(EffectPointer->C == 8 || EffectPointer->C == 9)
				{
					enableD = NeverHide;
					Effects_E->Show(true);
					Effects_E->ChangeValue(lexical_cast<string>(fmod(EffectPointer->D, 256))); // Correct value
					Effects_F->Show(true);
					Attacks_Class_ComboBox[2]->Show(true);
					Attacks_Class_ComboBox[2]->SetSelection(0);
					if(EffectPointer->D < 0)
					{
						Effects_F->ChangeValue(lexical_cast<string>(-(short)EffectPointer->D / 256)); // Correct class
						Attacks_Class_ComboBox[2]->SetSelection(-(short)EffectPointer->D / 256 + 1);
					}
					else
					{
						Effects_F->ChangeValue(lexical_cast<string>((short)EffectPointer->D / 256)); // Correct class
						Attacks_Class_ComboBox[2]->SetSelection((short)EffectPointer->D / 256 + 1);
					}
					Effects_E_Text->SetLabel("Amount [%] ");
					Effects_F_Text->SetLabel("Type ");
					Effects_Info_E->SetLabel(" % [0 to 255]");
					Effects_Info_F->SetLabel("");
				}
				else
				{
					Effects_E->Show(false);
					Effects_F->Show(false);
					Attacks_Class_ComboBox[2]->Show(false);
					Effects_E_Text->SetLabel("");
					Effects_F_Text->SetLabel("");
					Effects_Info_E->SetLabel("");
					Effects_Info_F->SetLabel("");
				}
			}
			break;
			case 6:
			case 16:
			{
				Effects_UnitsA_ComboBox->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ResourcesA_ComboBox->Show(true);	// for Effects 1, 6
				Effects_ResearchsA_ComboBox->Show(false);	// for Effects 101, 103
				Effects_ModeB_CheckBox->Show(false);	// for Effects 1, 2
				Units_Class_ComboBox[2]->Show(false);	// for Effects 0, 4, 5
				Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
				Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
				Effects_ModeC_CheckBox->Show(false);	// for Effects 101, 103
				Effects_AttributesC_ComboBox->Show(false);	// for Effects 0, 4, 5
				Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
				Attacks_Class_ComboBox[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(NeverHide);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_A_Text->SetLabel("Resource ");	/* add combo box */
				Effects_B_Text->SetLabel("Unused ");
				Effects_C_Text->SetLabel("Unused ");
				Effects_D_Text->SetLabel("Amount [*] ");
				Effects_E_Text->SetLabel("");
				Effects_F_Text->SetLabel("");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");
				Effects_Info_E->SetLabel("");
				Effects_Info_F->SetLabel("");
			}
			break;
			case 101:
			{
				Effects_UnitsA_ComboBox->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ResourcesA_ComboBox->Show(false);	// for Effects 1, 6
				Effects_ResearchsA_ComboBox->Show(true);	// for Effects 101, 103
				Effects_ModeB_CheckBox->Show(false);	// for Effects 1, 2
				Units_Class_ComboBox[2]->Show(false);	// for Effects 0, 4, 5
				Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
				Effects_ResourcesB_ComboBox->Show(true);	// for Effects 101
				Effects_ModeC_CheckBox->Show(true);	// for Effects 101, 103
				Effects_AttributesC_ComboBox->Show(false);	// for Effects 0, 4, 5
				Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
				Attacks_Class_ComboBox[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(true);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_A_Text->SetLabel("Research ");	/* add combo box */
				Effects_B_Text->SetLabel("Resource ");	/* add combo box */
				Effects_C_Text->SetLabel("Mode ");
				if(EffectPointer->C == 0) // unchecked
				{
					Effects_D_Text->SetLabel("Amount [Set] ");
				}
				else
				{
					Effects_D_Text->SetLabel("Amount [+/-] ");
				}
				Effects_E_Text->SetLabel("");
				Effects_F_Text->SetLabel("");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel(" [ ] = Set, [X] = +/-");
				Effects_Info_D->SetLabel("");
				Effects_Info_E->SetLabel("");
				Effects_Info_F->SetLabel("");
			}
			break;
			case 102:
			{
				Effects_UnitsA_ComboBox->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ResourcesA_ComboBox->Show(false);	// for Effects 1, 6
				Effects_ResearchsA_ComboBox->Show(false);	// for Effects 101, 103
				Effects_ModeB_CheckBox->Show(false);	// for Effects 1, 2
				Units_Class_ComboBox[2]->Show(false);	// for Effects 0, 4, 5
				Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
				Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
				Effects_ModeC_CheckBox->Show(false);	// for Effects 101, 103
				Effects_AttributesC_ComboBox->Show(false);	// for Effects 0, 4, 5
				Effects_ResearchsD_ComboBox->Show(true);	// for Effects 102
				Attacks_Class_ComboBox[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(NeverHide);	// not for Effects 102
				Effects_B->Show(NeverHide);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_A_Text->SetLabel("Unused ");
				Effects_B_Text->SetLabel("Unused ");
				Effects_C_Text->SetLabel("Unused ");
				Effects_D_Text->SetLabel("Research ");	/* add combo box */
				Effects_E_Text->SetLabel("");
				Effects_F_Text->SetLabel("");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");
				Effects_Info_E->SetLabel("");
				Effects_Info_F->SetLabel("");
			}
			break;
			case 103:
			{
				Effects_UnitsA_ComboBox->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ResourcesA_ComboBox->Show(false);	// for Effects 1, 6
				Effects_ResearchsA_ComboBox->Show(true);	// for Effects 101, 103
				Effects_ModeB_CheckBox->Show(false);	// for Effects 1, 2
				Units_Class_ComboBox[2]->Show(false);	// for Effects 0, 4, 5
				Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
				Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
				Effects_ModeC_CheckBox->Show(true);	// for Effects 101, 103
				Effects_AttributesC_ComboBox->Show(false);	// for Effects 0, 4, 5
				Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
				Attacks_Class_ComboBox[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(NeverHide);	// not for Effects 6, 102, 103
				Effects_C->Show(true);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_A_Text->SetLabel("Research ");	/* add combo box */
				Effects_B_Text->SetLabel("Unused ");
				Effects_C_Text->SetLabel("Mode ");	/* add boolean */
				if(EffectPointer->C == 0) // unchecked
				{
					Effects_D_Text->SetLabel("Amount [Set] ");
				}
				else
				{
					Effects_D_Text->SetLabel("Amount [+/-] ");
				}
				Effects_E_Text->SetLabel("");
				Effects_F_Text->SetLabel("");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel(" [ ] = Set, [X] = +/-");
				Effects_Info_D->SetLabel("");
				Effects_Info_E->SetLabel("");
				Effects_Info_F->SetLabel("");
			}
			break;
			default:
			{
				Effects_UnitsA_ComboBox->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ResourcesA_ComboBox->Show(false);	// for Effects 1, 6
				Effects_ResearchsA_ComboBox->Show(false);	// for Effects 101, 103
				Effects_ModeB_CheckBox->Show(false);	// for Effects 1, 2
				Units_Class_ComboBox[2]->Show(false);	// for Effects 0, 4, 5
				Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
				Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
				Effects_ModeC_CheckBox->Show(false);	// for Effects 101, 103
				Effects_AttributesC_ComboBox->Show(false);	// for Effects 0, 4, 5
				Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
				Attacks_Class_ComboBox[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(NeverHide);	// not for Effects 102
				Effects_B->Show(NeverHide);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(NeverHide);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_A_Text->SetLabel("Attribute A ");
				Effects_B_Text->SetLabel("Attribute B ");
				Effects_C_Text->SetLabel("Attribute C ");
				Effects_D_Text->SetLabel("Attribute D ");
				Effects_E_Text->SetLabel("");
				Effects_F_Text->SetLabel("");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");
				Effects_Info_E->SetLabel("");
				Effects_Info_F->SetLabel("");
			}
		}
	}
	else
	{
		Effects_Type_Holder->Show(false);
		Effects_UnitsA_ComboBox->Show(false);	// for Effects 0, 2, 3, 4, 5
		Effects_ResourcesA_ComboBox->Show(false);	// for Effects 1, 6
		Effects_ResearchsA_ComboBox->Show(false);	// for Effects 101, 103
		Effects_ModeB_CheckBox->Show(false);	// for Effects 1, 2
		Units_Class_ComboBox[2]->Show(false);	// for Effects 0, 4, 5
		Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
		Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
		Effects_ModeC_CheckBox->Show(false);	// for Effects 101, 103
		Effects_AttributesC_ComboBox->Show(false);	// for Effects 0, 4, 5
		Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
		Attacks_Class_ComboBox[2]->Show(false);	// only for attributes 8, 9
		Effects_A->Show(false);	// not for Effects 102
		Effects_B->Show(false);	// not for Effects 6, 102, 103
		Effects_C->Show(false);	// not for Effects 1, 2, 3, 6, 102
		Effects_D->Show(false);	// not for Effects 2, 3
		Effects_E->Show(false);	// only for attributes 8, 9
		Effects_F->Show(false);	// only for attributes 8, 9
		Effects_A_Text->SetLabel("Select effect first ");
		Effects_B_Text->SetLabel("");
		Effects_C_Text->SetLabel("");
		Effects_D_Text->SetLabel("");
		Effects_E_Text->SetLabel("");
		Effects_F_Text->SetLabel("");
		Effects_Info_A->SetLabel("");
		Effects_Info_B->SetLabel("");
		Effects_Info_C->SetLabel("");
		Effects_Info_D->SetLabel("");
		Effects_Info_E->SetLabel("");
		Effects_Info_F->SetLabel("");
	}
    for(auto &box: uiGroupTechEffect) box->update();
    Effects_D->Enable(enableD);
	Effects_Type_Holder->Layout();
	Effects_Data_Holder->Layout();
//	Refresh(); // Too much lag.
}

void AGE_Frame::OnEffectsAdd(wxCommandEvent &event)	// Works.
{
	auto selections = Techs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->Techages[TechIDs.front()].Effects);
	ListEffects();
}

void AGE_Frame::OnEffectsInsert(wxCommandEvent &event)	// Works.
{
	auto selections = Techs_Effects_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->Techages[TechIDs.front()].Effects, EffectIDs.front());
	ListEffects();
}

void AGE_Frame::OnEffectsDelete(wxCommandEvent &event)	// Works.
{
	auto selections = Techs_Effects_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->Techages[TechIDs.front()].Effects, EffectIDs);
	ListEffects();
}

void AGE_Frame::OnEffectsCopy(wxCommandEvent &event)	// Works.
{
	auto selections = Techs_Effects_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->Techages[TechIDs.front()].Effects, EffectIDs, copies.Effect);
	Techs_Effects_ListV->SetFocus();
}

void AGE_Frame::OnEffectsPaste(wxCommandEvent &event)	// Works.
{
	auto selections = Techs_Effects_ListV->GetSelectedItemCount();
	if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Techages[TechIDs.front()].Effects, EffectIDs, copies.Effect);
    ListEffects();
}

void AGE_Frame::OnEffectsPasteInsert(wxCommandEvent &event)	// Works.
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

    virtualListing(Techs_AllEffects_ListV);
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

void AGE_Frame::OnAllTechEffectTimer(wxTimerEvent &event)
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

	Techs_Name_Text = new wxStaticText(Tab_Techs, wxID_ANY, " Technology Name", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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
	Effects_Type_Text = new wxStaticText(Tab_Techs, wxID_ANY, " Effect Type *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Type = AGETextCtrl::init(CByte, &uiGroupTechEffect, this, &popUp, Tab_Techs);
	Effects_Type->SetToolTip("101 and 103 are only for\ntech tree and team bonus");
	Effects_Type_ComboBox = new ComboBox_EffectType(Tab_Techs, Effects_Type);
	Effects_Data_Holder = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Effect Attributes");
	Effects_NeverHide = new wxCheckBox(Tab_Techs, wxID_ANY, "Never hide attributes", wxDefaultPosition, wxDefaultSize);
	Effects_DataA_Holder = new wxBoxSizer(wxHORIZONTAL);
	Effects_DataB_Holder = new wxBoxSizer(wxHORIZONTAL);
	Effects_DataC_Holder = new wxBoxSizer(wxHORIZONTAL);
	Effects_DataD_Holder = new wxBoxSizer(wxHORIZONTAL);
	Effects_DataE_Holder = new wxBoxSizer(wxHORIZONTAL);
	Effects_DataF_Holder = new wxBoxSizer(wxHORIZONTAL);
	Effects_A_Holder = new wxBoxSizer(wxVERTICAL);
	Effects_B_Holder = new wxBoxSizer(wxVERTICAL);
	Effects_C_Holder = new wxBoxSizer(wxVERTICAL);
	Effects_D_Holder = new wxBoxSizer(wxVERTICAL);
	Effects_F_Holder = new wxBoxSizer(wxVERTICAL);
	Effects_A_Text = new wxStaticText(Tab_Techs, wxID_ANY, "Attribute A ", wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_A = AGETextCtrl::init(CShort, &uiGroupTechEffect, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
	Effects_A_ComboBox = new wxBoxSizer(wxHORIZONTAL);
	Effects_UnitsA_ComboBox = new ComboBox_Plus1(Tab_Techs, Effects_A);
	UnitComboBoxList.push_back(Effects_UnitsA_ComboBox);
	Effects_ResourcesA_ComboBox = new ComboBox_Plus1(Tab_Techs, Effects_A);
	ResourceComboBoxList.push_back(Effects_ResourcesA_ComboBox);
	Effects_ResearchsA_ComboBox = new ComboBox_Plus1(Tab_Techs, Effects_A);
	ResearchComboBoxList.push_back(Effects_ResearchsA_ComboBox);
	Effects_Info_A = new wxStaticText(Tab_Techs, wxID_ANY, " Info A", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_B_Text = new wxStaticText(Tab_Techs, wxID_ANY, "Attribute B ", wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_B = AGETextCtrl::init(CShort, &uiGroupTechEffect, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
	Effects_B_ComboBox = new wxBoxSizer(wxHORIZONTAL);
	Effects_ModeB_CheckBox = new CheckBox_2State(Tab_Techs, "", Effects_B);
	Units_Class_ComboBox[2] = new ComboBox_Plus1(Tab_Techs, Effects_B);
	Effects_UnitsB_ComboBox = new ComboBox_Plus1(Tab_Techs, Effects_B);
	UnitComboBoxList.push_back(Effects_UnitsB_ComboBox);
	Effects_ResourcesB_ComboBox = new ComboBox_Plus1(Tab_Techs, Effects_B);
	ResourceComboBoxList.push_back(Effects_ResourcesB_ComboBox);
	Effects_Info_B = new wxStaticText(Tab_Techs, wxID_ANY, " Info B", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_C_Text = new wxStaticText(Tab_Techs, wxID_ANY, "Attribute C ", wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_C = AGETextCtrl::init(CShort, &uiGroupTechEffect, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
	Effects_C_ComboBox = new wxBoxSizer(wxHORIZONTAL);
	Effects_ModeC_CheckBox = new CheckBox_2State(Tab_Techs, "", Effects_C);
	Effects_AttributesC_ComboBox = new ComboBox_EffectAttribute(Tab_Techs, Effects_C);
	Effects_Info_C = new wxStaticText(Tab_Techs, wxID_ANY, " Info C", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_D_Text = new wxStaticText(Tab_Techs, wxID_ANY, "Attribute D ", wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_D = AGETextCtrl::init(CFloat, &uiGroupTechEffect, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
	Effects_D_ComboBox = new wxBoxSizer(wxHORIZONTAL);
	Effects_ResearchsD_ComboBox = new ComboBox_Plus1(Tab_Techs, Effects_D);
	ResearchComboBoxList.push_back(Effects_ResearchsD_ComboBox);
	Effects_Info_D = new wxStaticText(Tab_Techs, wxID_ANY, " Info D", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_E_Text = new wxStaticText(Tab_Techs, wxID_ANY, "Amount or % ", wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_E = AGETextCtrl::init(CUByte, NULL, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
	Effects_Info_E = new wxStaticText(Tab_Techs, wxID_ANY, " Attack | Armor", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_F_Text = new wxStaticText(Tab_Techs, wxID_ANY, "Type ", wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_F = AGETextCtrl::init(CUByte, NULL, this, &popUp, Tab_Techs, AGETextCtrl::LARGE);
	Attacks_Class_ComboBox[2] = new ComboBox_Plus1(Tab_Techs, Effects_F);
	Effects_Info_F = new wxStaticText(Tab_Techs, wxID_ANY, " Attack | Armor", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);

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

	Effects_A_ComboBox->Add(Effects_UnitsA_ComboBox);
	Effects_A_ComboBox->Add(Effects_ResourcesA_ComboBox);
	Effects_A_ComboBox->Add(Effects_ResearchsA_ComboBox);
	Effects_A_Holder->Add(Effects_A, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_A_Holder->Add(Effects_A_ComboBox, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Effects_DataA_Holder->Add(Effects_A_Text);
	Effects_DataA_Holder->Add(Effects_A_Holder);
	Effects_DataA_Holder->Add(Effects_Info_A);

	Effects_B_ComboBox->Add(Effects_ModeB_CheckBox);
	Effects_B_ComboBox->Add(Units_Class_ComboBox[2]);
	Effects_B_ComboBox->Add(Effects_UnitsB_ComboBox);
	Effects_B_ComboBox->Add(Effects_ResourcesB_ComboBox);
	Effects_B_Holder->Add(Effects_B, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_B_Holder->Add(Effects_B_ComboBox, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Effects_DataB_Holder->Add(Effects_B_Text);
	Effects_DataB_Holder->Add(Effects_B_Holder);
	Effects_DataB_Holder->Add(Effects_Info_B);

	Effects_C_ComboBox->Add(Effects_ModeC_CheckBox);
	Effects_C_ComboBox->Add(Effects_AttributesC_ComboBox);
	Effects_C_Holder->Add(Effects_C, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_C_Holder->Add(Effects_C_ComboBox, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Effects_DataC_Holder->Add(Effects_C_Text);
	Effects_DataC_Holder->Add(Effects_C_Holder);
	Effects_DataC_Holder->Add(Effects_Info_C);

	Effects_D_ComboBox->Add(Effects_ResearchsD_ComboBox);
	Effects_D_Holder->Add(Effects_D, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_D_Holder->Add(Effects_D_ComboBox, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Effects_DataD_Holder->Add(Effects_D_Text);
	Effects_DataD_Holder->Add(Effects_D_Holder);
	Effects_DataD_Holder->Add(Effects_Info_D);

	Effects_DataE_Holder->Add(Effects_E_Text);
	Effects_DataE_Holder->Add(Effects_E, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_DataE_Holder->Add(Effects_Info_E);

	Effects_F_Holder->Add(Effects_F, 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_F_Holder->Add(Attacks_Class_ComboBox[2], 1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Effects_DataF_Holder->Add(Effects_F_Text);
	Effects_DataF_Holder->Add(Effects_F_Holder);
	Effects_DataF_Holder->Add(Effects_Info_F);

	Effects_Data_Holder->Add(Effects_NeverHide);
	Effects_Data_Holder->Add(Effects_DataA_Holder, 0, wxTOP, 5);
	Effects_Data_Holder->Add(Effects_DataB_Holder, 0, wxTOP, 5);
	Effects_Data_Holder->Add(Effects_DataC_Holder, 0, wxTOP, 5);
	Effects_Data_Holder->Add(Effects_DataD_Holder, 0, wxTOP, 5);
	Effects_Data_Holder->Add(Effects_DataE_Holder, 0, wxTOP, 5);
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
	Techs_Main->Add(Effects_ListArea, 27, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5); // 3+1
	Techs_Main->Add(Effects_DataArea, 33, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5); // 6-1

	Effects_E->Show(false);	// only for attributes 8, 9
	Effects_F->Show(false);	// only for attributes 8, 9
	Effects_A_ComboBox->Show(false);
	Effects_B_ComboBox->Show(false);
	Effects_C_ComboBox->Show(false);
	Effects_D_ComboBox->Show(false);
	Effects_UnitsA_ComboBox->Show(false);	// for Effects 0, 2, 3, 4, 5
	Effects_ResourcesA_ComboBox->Show(false);	// for Effects 1, 6
	Effects_ResearchsA_ComboBox->Show(false);	// for Effects 101, 103
	Effects_ModeB_CheckBox->Show(false);	// for Effects 1, 2
	Units_Class_ComboBox[2]->Show(false);	// for Effects 0, 4, 5
	Effects_UnitsB_ComboBox->Show(false);	// for Effects 3
	Effects_ResourcesB_ComboBox->Show(false);	// for Effects 101
	Effects_ModeC_CheckBox->Show(false);	// for Effects 101, 103
	Effects_AttributesC_ComboBox->Show(false);	// for Effects 0, 4, 5
	Effects_ResearchsD_ComboBox->Show(false);	// for Effects 102
	Attacks_Class_ComboBox[2]->Show(false);	// only for attributes 8, 9

	Tab_Techs->SetSizer(Techs_Main);

	for(size_t loop = 0; loop < 2; ++loop)
	{
		Connect(Techs_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechSearch));
		Connect(Techs_Effects_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsSearch));
		Connect(Techs_AllEffects_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::LoadAllTechEffects));
	}
	Connect(Techs_Rename->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechRename));
	Connect(Techs_Restore->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechRenameGE2));
	Connect(Techs_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTechSelect));
	Connect(Techs_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTechSelect));
	Connect(Techs_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTechSelect));
	Connect(Techs_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTechSearch));
	Connect(Techs_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTechSearch));
	Connect(Techs_Effects_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnEffectsSelect));
	Connect(Techs_Effects_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnEffectsSelect));
	Connect(Techs_Effects_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnEffectsSelect));
	Connect(Techs_Effects_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnEffectsSearch));
	Connect(Techs_Effects_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnEffectsSearch));
	Connect(Techs_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechAdd));
	Connect(Techs_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechInsert));
	Connect(Techs_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechDelete));
	Connect(Techs_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechCopy));
	Connect(Techs_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechPaste));
	Connect(Techs_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechPasteInsert));
	Connect(Techs_Effects_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsAdd));
	Connect(Techs_Effects_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsInsert));
	Connect(Techs_Effects_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsDelete));
	Connect(Techs_Effects_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsCopy));
	Connect(Techs_Effects_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsPaste));
	Connect(Techs_Effects_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsPasteInsert));
	Connect(Techs_Effects_CopyToTechs->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsCopyToTechs));
	Effects_E->Connect(Effects_E->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_F->Connect(Effects_F->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Connect(Techs_AllEffects_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::LoadAllTechEffects));
	Connect(Techs_AllEffects_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::LoadAllTechEffects));
	Connect(Techs_AllEffects_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnAllTechEffectSelect));
	Connect(Techs_AllEffects_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnAllTechEffectSelect));
	Connect(Techs_AllEffects_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnAllTechEffectSelect));
	Connect(Techs_AllEffects_Load->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::LoadAllTechEffects));
	Connect(Techs_AllEffects_Clear->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::ClearAllTechEffects));

    techTimer.Connect(techTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTechTimer), NULL, this);
    effectTimer.Connect(effectTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnEffectsTimer), NULL, this);
    allEffectsTimer.Connect(allEffectsTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnAllTechEffectTimer), NULL, this);
	Techs_Name->Connect(Techs_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_Type->Connect(Effects_Type->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_Type_ComboBox->Connect(Effects_Type_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_A->Connect(Effects_A->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_B->Connect(Effects_B->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_C->Connect(Effects_C->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_D->Connect(Effects_D->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_UnitsA_ComboBox->Connect(Effects_UnitsA_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_ResourcesA_ComboBox->Connect(Effects_ResourcesA_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_ResearchsA_ComboBox->Connect(Effects_ResearchsA_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_ModeB_CheckBox->Connect(Effects_ModeB_CheckBox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_Techs), NULL, this);
	Units_Class_ComboBox[2]->Connect(Units_Class_ComboBox[2]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_UnitsB_ComboBox->Connect(Effects_UnitsB_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_ResourcesB_ComboBox->Connect(Effects_ResourcesB_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_ModeC_CheckBox->Connect(Effects_ModeC_CheckBox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_Techs), NULL, this);
	Effects_AttributesC_ComboBox->Connect(Effects_AttributesC_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_ResearchsD_ComboBox->Connect(Effects_ResearchsD_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Attacks_Class_ComboBox[2]->Connect(Attacks_Class_ComboBox[2]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
}

void AGE_Frame::OnKillFocus_Techs(wxFocusEvent &event)
{
	event.Skip();
	if(event.GetId() == Effects_E->GetId() || event.GetId() == Effects_F->GetId())
	{
		if(!Effects_E->IsEmpty() && !Effects_F->IsEmpty()) // if has something, then update float value.
		{
            uint16_t Class = lexical_cast<int>(Effects_F->GetValue()) << 8;
            uint8_t Amount = lexical_cast<int>(Effects_E->GetValue());
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
	((AGECheckBox*)event.GetEventObject())->OnUpdate(event);
	ListEffects();
}

void AGE_Frame::OnUpdateCombo_Techs(wxCommandEvent &event)
{
	if(event.GetId() == Attacks_Class_ComboBox[2]->GetId())
	{
        uint16_t Class = (Attacks_Class_ComboBox[2]->GetSelection() - 1) << 8;
        uint8_t Amount = lexical_cast<int>(Effects_E->GetValue());
        Effects_D->ChangeValue(lexical_cast<string>(Amount + Class));
        Effects_D->SaveEdits();

		ListEffects();
		return;
	}
	((AGEComboBox*)event.GetEventObject())->OnUpdate(event);
	ListEffects();
}
