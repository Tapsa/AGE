#include "../AGE_Frame.h"

string AGE_Frame::GetTechName(short Index)
{
	if(!GenieFile->Techages[Index].Name.empty())
		return GenieFile->Techages[Index].Name+" ";
	return "New Technology ";
}

void AGE_Frame::OnTechRenameGE2(wxCommandEvent &Event)
{
	auto selections = Techs_List->GetSelections(Items);
	if(selections < 1) return;

	string Name;
	for(short loop = 0; loop < GenieFile->Techages.size(); ++loop)
	{
		GenieFile->Techages[loop].Name = "Tech";
	}
	ListTechs();
}

void AGE_Frame::OnTechRename(wxCommandEvent &Event)
{
	auto selections = Techs_List->GetSelections(Items);
	if(selections < 1) return;

	for(short loop3 = 0; loop3 < GenieFile->Techages.size(); ++loop3)
	{
		if(GenieFile->Techages[loop3].Effects.size() < 1) // Empty techs.
		{
			GenieFile->Techages[loop3].Name = "New Technology";
		}
		else // Other than empty techs, not researches if research loop doesn't rename them.
		{
			GenieFile->Techages[loop3].Name = "Non-Research";
		}
	}
	short ResearchTechID = 0;
	for(short loop=GenieFile->Researchs.size(); loop--> 0;) // Rename of techs. Make it reverse loop.
	{
		ResearchTechID = GenieFile->Researchs[loop].TechageID;
		if(ResearchTechID > 0) // Only researches which have techs.
		{
			if(!LangDLLstring(GenieFile->Researchs[loop].LanguageDLLName, 2).empty()) // has a lang dll name
			{
				GenieFile->Techages[ResearchTechID].Name = LangDLLstring(GenieFile->Researchs[loop].LanguageDLLName, 31);
			}
			else // Use internal name instead.
			{
				GenieFile->Techages[ResearchTechID].Name = GenieFile->Researchs[loop].Name;
			}
		}
	}
	string CivName;
	short CivTechTreeID=0, CivTeamBonusID = 0;
	for(short loop2=GenieFile->Civs.size(); loop2--> 0;) // Rename of techs. Make it reverse loop.
	{
		string CivName = lexical_cast<string>(GenieFile->Civs[loop2].Name); // Civ internal name.
		CivTechTreeID = GenieFile->Civs[loop2].TechTreeID;
		CivTeamBonusID = GenieFile->Civs[loop2].TeamBonusID;
		if(CivTechTreeID > 0)
		{
			GenieFile->Techages[CivTechTreeID].Name = CivName+" Tech. Tree"; // Under 31 chars.
		}
		if(CivTeamBonusID > 0)
		{
			GenieFile->Techages[CivTeamBonusID].Name = CivName+" Team Bonus"; // Under 31 chars.
		}
	}
	ListTechs();
}

void AGE_Frame::OnTechSearch(wxCommandEvent &Event)
{
	ListTechs(false);
}

void AGE_Frame::ListTechs(bool all)
{
	searchText = Techs_Search->GetValue().Lower();
	excludeText = Techs_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = Techs_UseAnd[loop]->GetValue();


	list<void*> dataPointers;
	wxArrayString filteredNames;

	wxArrayString names;
	if(all) names.Alloc(GenieFile->Techages.size());

	for(short loop = 0; loop < GenieFile->Techages.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTechName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->Techages[loop]);
		}
		if(all) names.Add(Name);
	}

	Listing(Techs_List, filteredNames, dataPointers);
	if(all) FillLists(TechComboBoxList, names);

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;

	wxCommandEvent E;
	OnTechSelect(E);
}

void AGE_Frame::OnTechSelect(wxCommandEvent &Event)
{
	auto selections = Techs_List->GetSelections(Items);
	if(selections < 1) return;

	TechIDs.resize(selections);
	Techs_Name->resize(selections);

	genie::Techage * TechPointer;
	for(auto loop = selections; loop--> 0;)
	{
		TechPointer = (genie::Techage*)Techs_List->GetClientData(Items.Item(loop));
		TechIDs[loop] = (TechPointer - (&GenieFile->Techages[0]));
		Techs_Name->container[loop] = &TechPointer->Name;
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected tech: "+lexical_cast<string>(TechIDs[0]), 0);

	Techs_Name->ChangeValue(TechPointer->Name);
	ListEffects();
}

void AGE_Frame::OnTechAdd(wxCommandEvent &Event)	// Works.
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->Techages);
	ListTechs();
}

void AGE_Frame::OnTechInsert(wxCommandEvent &Event)	// Works.
{
	auto selections = Techs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->Techages, TechIDs[0]);
	ListTechs();
}

void AGE_Frame::OnTechDelete(wxCommandEvent &Event)	// Works.
{
	auto selections = Techs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Techages, TechIDs);
	ListTechs();
}

void AGE_Frame::OnTechCopy(wxCommandEvent &Event)	// Works.
{
	auto selections = Techs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Techages, TechIDs, copies->Tech);
}

void AGE_Frame::OnTechPaste(wxCommandEvent &Event)	// Works.
{
	auto selections = Techs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->Techages, TechIDs[0], copies->Tech);
	ListTechs();
}

void AGE_Frame::OnTechPasteInsert(wxCommandEvent &Event)	// Works.
{
	auto selections = Techs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->Techages, TechIDs[0], copies->Tech);
	ListTechs();
}

string AGE_Frame::GetEffectName(short Index)
{
	string Name = "";
	switch(GenieFile->Techages[TechIDs[0]].Effects[Index].Type)
	{
		case 0:
			//Name = "Attribute Modifier (Set)";
			Name = "Set attr. "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].C)
			+" to "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D)+" for ";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].B == -1)
				Name += "unit "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A);
			else
				Name += "class "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B);
			break;
		case 1:
			//Name = "Resource Modifier (Set/+/-)";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].B == 0)
			{
				Name = "Set resource "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)
				+" to "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
			}
			else
			{
				Name = "Change resource "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)
				+" by "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
			}
			break;
		case 2:
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].B == 0)
				Name = "Disable";
			else
				Name = "Enable";
			Name += " unit "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A);
			break;
		case 3:
			Name = "Upgrade unit "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)
			+" to "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B);
			break;
		case 4:
			//Name = "Attribute Modifier (+/-)";
			Name = "Change attr. "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].C)
			+" by "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D)+" for ";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].B == -1)
				Name += "unit "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A);
			else
				Name += "class "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B);
			break;
		case 5:
			//Name = "Attribute Modifier (Multiply)";
			Name = "Multiply attr. "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].C)
			+" by "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D)+" for ";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].B == -1)
				Name += "unit "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A);
			else
				Name += "class "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B);
			break;
		case 6:
			//Name = "Resource Modifier (Multiply)";
			Name = "Multiply resource "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)
			+" by "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
			break;
		case 101:
			//Name = "Research Cost Modifier (Set/+/-)";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].C == 0)
			{
				Name = "Set research "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)
				+" cost type "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B)
				+" to "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
			}
			else
			{
				Name = "Change research "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)
				+" cost type "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B)
				+" by "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
			}
			break;
		case 102:
			Name = "Disable research "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
			break;
		case 103:
			//Name = "Research Time Modifier (Set/+/-)";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].C == 0)
			{
				Name = "Set research "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)
				+" time to "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
			}
			else
			{
				Name = "Change research "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)
				+" time by "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
			}
			break;
		default:
			Name = "No type/Invalid type";
	}
	return Name+" ";
}

void AGE_Frame::OnEffectsSearch(wxCommandEvent &Event)
{
	ListEffects();
}

void AGE_Frame::ListEffects()
{
	searchText = Techs_Effects_Search->GetValue().Lower();
	excludeText = Techs_Effects_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = Techs_Effects_UseAnd[loop]->GetValue();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->Techages[TechIDs[0]].Effects.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetEffectName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->Techages[TechIDs[0]].Effects[loop]);
		}
	}
	Listing(Techs_Effects_List, filteredNames, dataPointers);

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;

	wxCommandEvent E;
	OnEffectsSelect(E);
}

void AGE_Frame::OnEffectsSelect(wxCommandEvent &Event)
{
	auto selections = Techs_Effects_List->GetSelections(Items);
	if(selections > 0)
	{
		Effects_Holder_Type->Show(true);
		Effects_D->Enable(true);
		EffectIDs.resize(selections);
		Effects_Type->resize(selections);
		Effects_A->resize(selections);
		Effects_B->resize(selections);
		Effects_C->resize(selections);
		Effects_D->resize(selections);

		genie::TechageEffect * EffectPointer;
		for(auto loop = selections; loop--> 0;)
		{
			EffectPointer = (genie::TechageEffect*)Techs_Effects_List->GetClientData(Items.Item(loop));
			EffectIDs[loop] = (EffectPointer - (&GenieFile->Techages[TechIDs[0]].Effects[0]));
			Effects_Type->container[loop] = &EffectPointer->Type;
			Effects_A->container[loop] = &EffectPointer->A;
			Effects_B->container[loop] = &EffectPointer->B;
			Effects_C->container[loop] = &EffectPointer->C;
			Effects_D->container[loop] = &EffectPointer->D;
		}

		Effects_Type->ChangeValue(lexical_cast<string>((short)(EffectPointer->Type)));
		if(EffectPointer->Type >= 0 && EffectPointer->Type <= 6)
		{
			Effects_ComboBox_Type->SetSelection(EffectPointer->Type + 1);
		}
		else if(EffectPointer->Type >= 101 && EffectPointer->Type <= 103)
		{
			Effects_ComboBox_Type->SetSelection(EffectPointer->Type - 93);
		}
		else
		{
			Effects_ComboBox_Type->SetSelection(0);
		}
		Effects_A->ChangeValue(lexical_cast<string>(EffectPointer->A));
		Effects_ComboBox_UnitsA->SetSelection(0);
		Effects_ComboBox_UnitsA->SetSelection(EffectPointer->A + 1);
		Effects_ComboBox_ResourcesA->SetSelection(0);
		Effects_ComboBox_ResourcesA->SetSelection(EffectPointer->A + 1);
		Effects_ComboBox_ResearchsA->SetSelection(0);
		Effects_ComboBox_ResearchsA->SetSelection(EffectPointer->A + 1);
		Effects_B->ChangeValue(lexical_cast<string>(EffectPointer->B));
		Effects_CheckBox_ModeB->SetValue((bool)EffectPointer->B);
		Units_ComboBox_Class[2]->SetSelection(0);
		Units_ComboBox_Class[2]->SetSelection(EffectPointer->B + 1);
		Effects_ComboBox_UnitsB->SetSelection(0);
		Effects_ComboBox_UnitsB->SetSelection(EffectPointer->B + 1);
		Effects_ComboBox_ResourcesB->SetSelection(0);
		Effects_ComboBox_ResourcesB->SetSelection(EffectPointer->B + 1);
		Effects_C->ChangeValue(lexical_cast<string>(EffectPointer->C));
		Effects_CheckBox_ModeC->SetValue((bool)EffectPointer->C);
		Effects_ComboBox_AttributesC->SetSelection(0);
		Effects_ComboBox_AttributesC->SetSelection(EffectPointer->C + 1);
		Effects_D->ChangeValue(lexical_cast<string>(EffectPointer->D));
		Effects_ComboBox_ResearchsD->SetSelection(0);
		Effects_ComboBox_ResearchsD->SetSelection(EffectPointer->D + 1);

		bool NeverHide = Effects_NeverHide->GetValue();
		switch(EffectPointer->Type)
		{
			case 0:
			{
				Effects_ComboBox_UnitsA->Show(true);	// for Effects 0, 2, 3, 4, 5
				Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
				Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
				Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
				Units_ComboBox_Class[2]->Show(true);	// for Effects 0, 4, 5
				Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
				Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
				Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
				Effects_ComboBox_AttributesC->Show(true);	// for Effects 0, 4, 5
				Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(true);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3

				Effects_Text_A->SetLabel("Unit ");
				Effects_Text_B->SetLabel("Class ");
				Effects_Text_C->SetLabel("Attribute ");
				Effects_Text_D->SetLabel("Value [Set] ");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");

				if(EffectPointer->C == 8 || EffectPointer->C == 9)
				{
					Effects_D->Enable(false);
					Effects_E->Show(true);
					Effects_E->ChangeValue(lexical_cast<string>(fmod(EffectPointer->D, 256))); // Correct value
					Effects_F->Show(true);
					Attacks_ComboBox_Class[2]->Show(true);
					Attacks_ComboBox_Class[2]->SetSelection(0);
					if(EffectPointer->D < 0)
					{
						Effects_F->ChangeValue(lexical_cast<string>(-(short)EffectPointer->D / 256)); // Correct class
						Attacks_ComboBox_Class[2]->SetSelection(-(short)EffectPointer->D / 256 + 1);
					}
					else
					{
						Effects_F->ChangeValue(lexical_cast<string>((short)EffectPointer->D / 256)); // Correct class
						Attacks_ComboBox_Class[2]->SetSelection((short)EffectPointer->D / 256 + 1);
					}
					Effects_Text_E->SetLabel("Value [Set] ");
					Effects_Text_F->SetLabel("Class ");
					Effects_Info_E->SetLabel(" [-255 to 255]");
					Effects_Info_F->SetLabel("");
				}
				else
				{
					Effects_D->Enable(true);
					Effects_E->Show(false);
					Effects_F->Show(false);
					Attacks_ComboBox_Class[2]->Show(false);
					Effects_Text_E->SetLabel("");
					Effects_Text_F->SetLabel("");
					Effects_Info_E->SetLabel("");
					Effects_Info_F->SetLabel("");
				}
			}
			break;
			case 1:
			{
				Effects_ComboBox_UnitsA->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ComboBox_ResourcesA->Show(true);	// for Effects 1, 6
				Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
				Effects_CheckBox_ModeB->Show(true);	// for Effects 1, 2
				Units_ComboBox_Class[2]->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
				Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
				Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
				Effects_ComboBox_AttributesC->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
				Attacks_ComboBox_Class[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_Text_A->SetLabel("Resource ");	/* add combo box */
				Effects_Text_B->SetLabel("Mode ");	/* add boolean [X]=1=Set [ ]=0=+/- */
				Effects_Text_C->SetLabel("Unused ");
				if(EffectPointer->B == 0) // unchecked
				{
					Effects_Text_D->SetLabel("Value [Set] ");
				}
				else
				{
					Effects_Text_D->SetLabel("Value [+/-] ");
				}
				Effects_Text_E->SetLabel("");
				Effects_Text_F->SetLabel("");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel(" [ ] = Set, [X] = +/-");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");
				Effects_Info_E->SetLabel("");
				Effects_Info_F->SetLabel("");
			}
			break;
			case 2:
			{
				Effects_ComboBox_UnitsA->Show(true);	// for Effects 0, 2, 3, 4, 5
				Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
				Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
				Effects_CheckBox_ModeB->Show(true);	// for Effects 1, 2
				Units_ComboBox_Class[2]->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
				Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
				Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
				Effects_ComboBox_AttributesC->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
				Attacks_ComboBox_Class[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(NeverHide);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_Text_A->SetLabel("Unit ");	/* add combo box */
				Effects_Text_B->SetLabel("Mode ");	/* add boolean */
				Effects_Text_C->SetLabel("Unused ");
				Effects_Text_D->SetLabel("Unused ");
				Effects_Text_E->SetLabel("");
				Effects_Text_F->SetLabel("");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel(" [ ] = Disable, [X] = Enable");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");
				Effects_Info_E->SetLabel("");
				Effects_Info_F->SetLabel("");
			}
			break;
			case 3:
			{
				Effects_ComboBox_UnitsA->Show(true);	// for Effects 0, 2, 3, 4, 5
				Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
				Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
				Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
				Units_ComboBox_Class[2]->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_UnitsB->Show(true);	// for Effects 3
				Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
				Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
				Effects_ComboBox_AttributesC->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
				Attacks_ComboBox_Class[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(NeverHide);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_Text_A->SetLabel("Unit ");	/* add combo box */
				Effects_Text_B->SetLabel("To Unit ");	/* add combo box */
				Effects_Text_C->SetLabel("Unused ");
				Effects_Text_D->SetLabel("Unused ");
				Effects_Text_E->SetLabel("");
				Effects_Text_F->SetLabel("");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");
				Effects_Info_E->SetLabel("");
				Effects_Info_F->SetLabel("");
			}
			break;
			case 4:
			{
				Effects_ComboBox_UnitsA->Show(true);	// for Effects 0, 2, 3, 4, 5
				Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
				Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
				Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
				Units_ComboBox_Class[2]->Show(true);	// for Effects 0, 4, 5
				Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
				Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
				Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
				Effects_ComboBox_AttributesC->Show(true);	// for Effects 0, 4, 5
				Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(true);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3

				Effects_Text_A->SetLabel("Unit ");	/* add combo box */
				Effects_Text_B->SetLabel("Class ");	/* add combo box */
				Effects_Text_C->SetLabel("Attribute ");	/* add combo box */
				Effects_Text_D->SetLabel("Value [+/-] ");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");

				if(EffectPointer->C == 8 || EffectPointer->C == 9)
				{
					Effects_D->Enable(false);
					Effects_E->Show(true);
					Effects_E->ChangeValue(lexical_cast<string>(fmod(EffectPointer->D, 256))); // Correct value
					Effects_F->Show(true);
					Attacks_ComboBox_Class[2]->Show(true);
					Attacks_ComboBox_Class[2]->SetSelection(0);
					if(EffectPointer->D < 0)
					{
						Effects_F->ChangeValue(lexical_cast<string>(-(short)EffectPointer->D / 256)); // Correct class
						Attacks_ComboBox_Class[2]->SetSelection(-(short)EffectPointer->D / 256 + 1);
					}
					else
					{
						Effects_F->ChangeValue(lexical_cast<string>((short)EffectPointer->D / 256)); // Correct class
						Attacks_ComboBox_Class[2]->SetSelection((short)EffectPointer->D / 256 + 1);
					}
					Effects_Text_E->SetLabel("Value [+/-] ");
					Effects_Text_F->SetLabel("Class ");
					Effects_Info_E->SetLabel(" [-255 to 255]");
					Effects_Info_F->SetLabel("");
				}
				else
				{
					Effects_D->Enable(true);
					Effects_E->Show(false);
					Effects_F->Show(false);
					Attacks_ComboBox_Class[2]->Show(false);
					Effects_Text_E->SetLabel("");
					Effects_Text_F->SetLabel("");
					Effects_Info_E->SetLabel("");
					Effects_Info_F->SetLabel("");
				}
			}
			break;
			case 5:
			{
				Effects_ComboBox_UnitsA->Show(true);	// for Effects 0, 2, 3, 4, 5
				Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
				Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
				Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
				Units_ComboBox_Class[2]->Show(true);	// for Effects 0, 4, 5
				Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
				Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
				Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
				Effects_ComboBox_AttributesC->Show(true);	// for Effects 0, 4, 5
				Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(true);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3

				Effects_Text_A->SetLabel("Unit ");	/* add combo box */
				Effects_Text_B->SetLabel("Class ");	/* add combo box */
				Effects_Text_C->SetLabel("Attribute ");	/* add combo box */
				Effects_Text_D->SetLabel("Value [*] ");

				Effects_Info_A->SetLabel("");
				Effects_Info_B->SetLabel("");
				Effects_Info_C->SetLabel("");
				Effects_Info_D->SetLabel("");

				if(EffectPointer->C == 8 || EffectPointer->C == 9)
				{
					Effects_D->Enable(false);
					Effects_E->Show(true);
					Effects_E->ChangeValue(lexical_cast<string>(fmod(EffectPointer->D, 256))); // Correct value
					Effects_F->Show(true);
					Attacks_ComboBox_Class[2]->Show(true);
					Attacks_ComboBox_Class[2]->SetSelection(0);
					if(EffectPointer->D < 0)
					{
						Effects_F->ChangeValue(lexical_cast<string>(-(short)EffectPointer->D / 256)); // Correct class
						Attacks_ComboBox_Class[2]->SetSelection(-(short)EffectPointer->D / 256 + 1);
					}
					else
					{
						Effects_F->ChangeValue(lexical_cast<string>((short)EffectPointer->D / 256)); // Correct class
						Attacks_ComboBox_Class[2]->SetSelection((short)EffectPointer->D / 256 + 1);
					}
					Effects_Text_E->SetLabel("Value [%] ");
					Effects_Text_F->SetLabel("Class ");
					Effects_Info_E->SetLabel(" % [0 to 255]");
					Effects_Info_F->SetLabel("");
				}
				else
				{
					Effects_D->Enable(true);
					Effects_E->Show(false);
					Effects_F->Show(false);
					Attacks_ComboBox_Class[2]->Show(false);
					Effects_Text_E->SetLabel("");
					Effects_Text_F->SetLabel("");
					Effects_Info_E->SetLabel("");
					Effects_Info_F->SetLabel("");
				}
			}
			break;
			case 6:
			{
				Effects_ComboBox_UnitsA->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ComboBox_ResourcesA->Show(true);	// for Effects 1, 6
				Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
				Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
				Units_ComboBox_Class[2]->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
				Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
				Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
				Effects_ComboBox_AttributesC->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
				Attacks_ComboBox_Class[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(NeverHide);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_Text_A->SetLabel("Resource ");	/* add combo box */
				Effects_Text_B->SetLabel("Unused ");
				Effects_Text_C->SetLabel("Unused ");
				Effects_Text_D->SetLabel("Value [*] ");
				Effects_Text_E->SetLabel("");
				Effects_Text_F->SetLabel("");

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
				Effects_ComboBox_UnitsA->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
				Effects_ComboBox_ResearchsA->Show(true);	// for Effects 101, 103
				Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
				Units_ComboBox_Class[2]->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
				Effects_ComboBox_ResourcesB->Show(true);	// for Effects 101
				Effects_CheckBox_ModeC->Show(true);	// for Effects 101, 103
				Effects_ComboBox_AttributesC->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
				Attacks_ComboBox_Class[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(true);	// not for Effects 6, 102, 103
				Effects_C->Show(true);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_Text_A->SetLabel("Research ");	/* add combo box */
				Effects_Text_B->SetLabel("Resource ");	/* add combo box */
				Effects_Text_C->SetLabel("Mode ");
				if(EffectPointer->C == 0) // unchecked
				{
					Effects_Text_D->SetLabel("Value [Set] ");
				}
				else
				{
					Effects_Text_D->SetLabel("Value [+/-] ");
				}
				Effects_Text_E->SetLabel("");
				Effects_Text_F->SetLabel("");

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
				Effects_ComboBox_UnitsA->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
				Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
				Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
				Units_ComboBox_Class[2]->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
				Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
				Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
				Effects_ComboBox_AttributesC->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_ResearchsD->Show(true);	// for Effects 102
				Attacks_ComboBox_Class[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(NeverHide);	// not for Effects 102
				Effects_B->Show(NeverHide);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_Text_A->SetLabel("Unused ");
				Effects_Text_B->SetLabel("Unused ");
				Effects_Text_C->SetLabel("Unused ");
				Effects_Text_D->SetLabel("Research ");	/* add combo box */
				Effects_Text_E->SetLabel("");
				Effects_Text_F->SetLabel("");

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
				Effects_ComboBox_UnitsA->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
				Effects_ComboBox_ResearchsA->Show(true);	// for Effects 101, 103
				Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
				Units_ComboBox_Class[2]->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
				Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
				Effects_CheckBox_ModeC->Show(true);	// for Effects 101, 103
				Effects_ComboBox_AttributesC->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
				Attacks_ComboBox_Class[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(true);	// not for Effects 102
				Effects_B->Show(NeverHide);	// not for Effects 6, 102, 103
				Effects_C->Show(true);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(true);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_Text_A->SetLabel("Research ");	/* add combo box */
				Effects_Text_B->SetLabel("Unused ");
				Effects_Text_C->SetLabel("Mode ");	/* add boolean */
				if(EffectPointer->C == 0) // unchecked
				{
					Effects_Text_D->SetLabel("Value [Set] ");
				}
				else
				{
					Effects_Text_D->SetLabel("Value [+/-] ");
				}
				Effects_Text_E->SetLabel("");
				Effects_Text_F->SetLabel("");

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
				Effects_ComboBox_UnitsA->Show(false);	// for Effects 0, 2, 3, 4, 5
				Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
				Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
				Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
				Units_ComboBox_Class[2]->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
				Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
				Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
				Effects_ComboBox_AttributesC->Show(false);	// for Effects 0, 4, 5
				Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
				Attacks_ComboBox_Class[2]->Show(false);	// only for attributes 8, 9
				Effects_A->Show(NeverHide);	// not for Effects 102
				Effects_B->Show(NeverHide);	// not for Effects 6, 102, 103
				Effects_C->Show(NeverHide);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(NeverHide);	// not for Effects 2, 3
				Effects_E->Show(false);	// only for attributes 8, 9
				Effects_F->Show(false);	// only for attributes 8, 9

				Effects_Text_A->SetLabel("Attribute A ");
				Effects_Text_B->SetLabel("Attribute B ");
				Effects_Text_C->SetLabel("Attribute C ");
				Effects_Text_D->SetLabel("Attribute D ");
				Effects_Text_E->SetLabel("");
				Effects_Text_F->SetLabel("");

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
		Effects_Holder_Type->Show(false);
		Effects_ComboBox_UnitsA->Show(false);	// for Effects 0, 2, 3, 4, 5
		Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
		Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
		Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
		Units_ComboBox_Class[2]->Show(false);	// for Effects 0, 4, 5
		Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
		Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
		Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
		Effects_ComboBox_AttributesC->Show(false);	// for Effects 0, 4, 5
		Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
		Attacks_ComboBox_Class[2]->Show(false);	// only for attributes 8, 9
		Effects_A->Show(false);	// not for Effects 102
		Effects_B->Show(false);	// not for Effects 6, 102, 103
		Effects_C->Show(false);	// not for Effects 1, 2, 3, 6, 102
		Effects_D->Show(false);	// not for Effects 2, 3
		Effects_E->Show(false);	// only for attributes 8, 9
		Effects_F->Show(false);	// only for attributes 8, 9
		Effects_Text_A->SetLabel("Add Effect ");
		Effects_Text_B->SetLabel("");
		Effects_Text_C->SetLabel("");
		Effects_Text_D->SetLabel("");
		Effects_Text_E->SetLabel("");
		Effects_Text_F->SetLabel("");
		Effects_Info_A->SetLabel("");
		Effects_Info_B->SetLabel("");
		Effects_Info_C->SetLabel("");
		Effects_Info_D->SetLabel("");
		Effects_Info_E->SetLabel("");
		Effects_Info_F->SetLabel("");
	}
	Effects_Holder_Type->Layout();
	Effects_Holder_A->Layout();
	Effects_Holder_B->Layout();
	Effects_Holder_C->Layout();
	Effects_Holder_D->Layout();
//	Refresh(); // Too much lag.
}

void AGE_Frame::OnEffectsAdd(wxCommandEvent &Event)	// Works.
{
	auto selections = Techs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->Techages[TechIDs[0]].Effects);
	ListEffects();
}

void AGE_Frame::OnEffectsInsert(wxCommandEvent &Event)	// Works.
{
	auto selections = Techs_Effects_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->Techages[TechIDs[0]].Effects, EffectIDs[0]);
	ListEffects();
}

void AGE_Frame::OnEffectsDelete(wxCommandEvent &Event)	// Works.
{
	auto selections = Techs_Effects_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Techages[TechIDs[0]].Effects, EffectIDs);
	ListEffects();
}

void AGE_Frame::OnEffectsCopy(wxCommandEvent &Event)	// Works.
{
	auto selections = Techs_Effects_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Techages[TechIDs[0]].Effects, EffectIDs, copies->Effect);
}

void AGE_Frame::OnEffectsPaste(wxCommandEvent &Event)	// Works.
{
	auto selections = Techs_Effects_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->Techages[TechIDs[0]].Effects, EffectIDs[0], copies->Effect);
	ListEffects();
}

void AGE_Frame::OnEffectsPasteInsert(wxCommandEvent &Event)	// Works.
{
	auto selections = Techs_Effects_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->Techages[TechIDs[0]].Effects, EffectIDs[0], copies->Effect);
	ListEffects();
}

void AGE_Frame::OnEffectsCopyToTechs(wxCommandEvent &Event)
{
	for(short loop=1; loop < TechIDs.size(); ++loop)
	{
		GenieFile->Techages[TechIDs[loop]].Effects = GenieFile->Techages[TechIDs[0]].Effects;
	}
}

void AGE_Frame::LoadAllTechEffects(wxCommandEvent &Event)
{
	wxString Name;
	searchText = Techs_AllEffects_Search->GetValue().Lower();
	excludeText = Techs_AllEffects_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = Techs_AllEffects_UseAnd[loop]->GetValue();

	auto selections = Techs_AllEffects_List->GetSelections(Items);
	Techs_AllEffects_List->Clear();

	short Store = TechIDs[0];
	for(short tech = 0; tech < GenieFile->Techages.size(); ++tech)
	{
		TechIDs[0] = tech;
		for(short effect = 0; effect < GenieFile->Techages[tech].Effects.size(); ++effect)
		{
			Name = " T"+lexical_cast<string>(tech)+" E"+lexical_cast<string>(effect)+" - "+GetEffectName(effect);
			if(SearchMatches(Name.Lower()))
			{
				Techs_AllEffects_List->Append(Name);
			}
		}
	}
	TechIDs[0] = Store;

	Techs_AllEffects_List->SetSelection(Items.Item(0));

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;

	wxCommandEvent E;
	OnAllTechEffectSelect(E);
}

void AGE_Frame::ClearAllTechEffects(wxCommandEvent &Event)
{
	Techs_Search->SetValue("");
	Techs_Effects_Search->SetValue("");
}

void AGE_Frame::OnAllTechEffectSelect(wxCommandEvent &Event)
{
	SearchAllSubVectors(Techs_AllEffects_List, Techs_Search, Techs_Effects_Search);
}

void AGE_Frame::CreateTechControls()
{
	Tab_Techs = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Techs_Main = new wxBoxSizer(wxHORIZONTAL);
	Techs_ListArea = new wxBoxSizer(wxVERTICAL);
	Techs_Buttons = new wxGridSizer(3, 0, 0);
	Effects_DataArea = new wxBoxSizer(wxVERTICAL);
	Effects_ListArea = new wxBoxSizer(wxVERTICAL);
	Techs_Effects_Buttons = new wxGridSizer(3, 0, 0);
	Effects_DataAreaProperties = new wxBoxSizer(wxVERTICAL);
	Techs_Techs = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Technologies");
	Techs_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
	Techs_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
	Techs_Search = new wxTextCtrl(Tab_Techs, wxID_ANY);
	Techs_UseAnd[0] = new wxCheckBox(Tab_Techs, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Techs_Search_R = new wxTextCtrl(Tab_Techs, wxID_ANY);
	Techs_UseAnd[1] = new wxCheckBox(Tab_Techs, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Techs_List = new wxListBox(Tab_Techs, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Techs_Add = new wxButton(Tab_Techs, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Techs_Insert = new wxButton(Tab_Techs, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Techs_Delete = new wxButton(Tab_Techs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Techs_Copy = new wxButton(Tab_Techs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Techs_Paste = new wxButton(Tab_Techs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Techs_PasteInsert = new wxButton(Tab_Techs, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	Techs_Rename = new wxButton(Tab_Techs, wxID_ANY, "Rename technologies", wxDefaultPosition, wxSize(0, 20));
	Techs_Restore = new wxButton(Tab_Techs, wxID_ANY, "Rename for GeniEd 2", wxDefaultPosition, wxSize(0, 20));

	Techs_Holder_Name = new wxBoxSizer(wxVERTICAL);
	Techs_Text_Name = new wxStaticText(Tab_Techs, wxID_ANY, " Technology Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Techs_Name = new TextCtrl_String(Tab_Techs, 31);

	Techs_Effects = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Effects");
	Techs_Effects_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
	Techs_Effects_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
	Techs_Effects_Search = new wxTextCtrl(Tab_Techs, wxID_ANY);
	Techs_Effects_UseAnd[0] = new wxCheckBox(Tab_Techs, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Techs_Effects_Search_R = new wxTextCtrl(Tab_Techs, wxID_ANY);
	Techs_Effects_UseAnd[1] = new wxCheckBox(Tab_Techs, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Techs_Effects_List = new wxListBox(Tab_Techs, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Techs_Effects_Add = new wxButton(Tab_Techs, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Techs_Effects_Insert = new wxButton(Tab_Techs, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Techs_Effects_Delete = new wxButton(Tab_Techs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Techs_Effects_Copy = new wxButton(Tab_Techs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Techs_Effects_Paste = new wxButton(Tab_Techs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Techs_Effects_PasteInsert = new wxButton(Tab_Techs, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	Techs_Effects_CopyToTechs = new wxButton(Tab_Techs, wxID_ANY, "Copy all to selected techs", wxDefaultPosition, wxSize(5, 20));

	Effects_Holder_Type = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_Type2 = new wxBoxSizer(wxHORIZONTAL);
	Effects_Text_Type = new wxStaticText(Tab_Techs, wxID_ANY, " Effect Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Type = new TextCtrl_Byte(Tab_Techs);
	Effects_ComboBox_Type = new ComboBox_EffectType(Tab_Techs, Effects_Type);
	Effects_Holder_Data = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Effect Attributes");
	Effects_NeverHide = new wxCheckBox(Tab_Techs, wxID_ANY, "Never hide attributes", wxDefaultPosition, wxSize(40, 20));
	Effects_Holder_DataA = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_DataB = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_DataC = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_DataD = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_DataE = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_DataF = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_A = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_B = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_C = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_D = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_E = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_F = new wxBoxSizer(wxVERTICAL);
	Effects_Text_A = new wxStaticText(Tab_Techs, wxID_ANY, "Attribute A ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_A = new TextCtrl_Short(Tab_Techs);
	Effects_ComboBox_A = new wxBoxSizer(wxHORIZONTAL);
	Effects_ComboBox_UnitsA = new ComboBox_Plus1(Tab_Techs, Effects_A);
	UnitComboBoxList.push_back(Effects_ComboBox_UnitsA);
	Effects_ComboBox_ResourcesA = new ComboBox_Plus1(Tab_Techs, Effects_A);
	ResourceComboBoxList.push_back(Effects_ComboBox_ResourcesA);
	Effects_ComboBox_ResearchsA = new ComboBox_Plus1(Tab_Techs, Effects_A);
	ResearchComboBoxList.push_back(Effects_ComboBox_ResearchsA);
	Effects_Info_A = new wxStaticText(Tab_Techs, wxID_ANY, " Info A", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_B = new wxStaticText(Tab_Techs, wxID_ANY, "Attribute B ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_B = new TextCtrl_Short(Tab_Techs);
	Effects_ComboBox_B = new wxBoxSizer(wxHORIZONTAL);
	Effects_CheckBox_ModeB = new CheckBox_2State(Tab_Techs, "", Effects_B);
	Units_ComboBox_Class[2] = new ComboBox_Plus1(Tab_Techs, Effects_B);
	Effects_ComboBox_UnitsB = new ComboBox_Plus1(Tab_Techs, Effects_B);
	UnitComboBoxList.push_back(Effects_ComboBox_UnitsB);
	Effects_ComboBox_ResourcesB = new ComboBox_Plus1(Tab_Techs, Effects_B);
	ResourceComboBoxList.push_back(Effects_ComboBox_ResourcesB);
	Effects_Info_B = new wxStaticText(Tab_Techs, wxID_ANY, " Info B", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_C = new wxStaticText(Tab_Techs, wxID_ANY, "Attribute C ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_C = new TextCtrl_Short(Tab_Techs);
	Effects_ComboBox_C = new wxBoxSizer(wxHORIZONTAL);
	Effects_CheckBox_ModeC = new CheckBox_2State(Tab_Techs, "", Effects_C);
	Effects_ComboBox_AttributesC = new ComboBox_Plus1(Tab_Techs, Effects_C);
	Effects_Info_C = new wxStaticText(Tab_Techs, wxID_ANY, " Info C", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_D = new wxStaticText(Tab_Techs, wxID_ANY, "Attribute D ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_D = new TextCtrl_Float(Tab_Techs);
	Effects_ComboBox_D = new wxBoxSizer(wxHORIZONTAL);
	Effects_ComboBox_ResearchsD = new ComboBox_Plus1(Tab_Techs, Effects_D);
	ResearchComboBoxList.push_back(Effects_ComboBox_ResearchsD);
	Effects_Info_D = new wxStaticText(Tab_Techs, wxID_ANY, " Info D", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_E = new wxStaticText(Tab_Techs, wxID_ANY, "Amount or % ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_E = new wxTextCtrl(Tab_Techs, wxID_ANY);
	Effects_Info_E = new wxStaticText(Tab_Techs, wxID_ANY, " Attack | Armor", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_F = new wxStaticText(Tab_Techs, wxID_ANY, "Class ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_F = new TextCtrl_Short(Tab_Techs);
	Attacks_ComboBox_Class[2] = new ComboBox_Plus1(Tab_Techs, Effects_F);
	Effects_Info_F = new wxStaticText(Tab_Techs, wxID_ANY, " Attack | Armor", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Link = new wxHyperlinkCtrl(Tab_Techs, wxID_ANY, "GenieWiki Effect Types", "http://www.digitization.org/wiki/index.php?title=Genie_technology#Effects");

	Techs_AllEffects = new wxStaticBoxSizer(wxVERTICAL, Tab_Techs, "Effects of all Technologies");
	Techs_AllEffects_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
	Techs_AllEffects_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
	Techs_AllEffects_Search = new wxTextCtrl(Tab_Techs, wxID_ANY);
	Techs_AllEffects_UseAnd[0] = new wxCheckBox(Tab_Techs, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Techs_AllEffects_Search_R = new wxTextCtrl(Tab_Techs, wxID_ANY);
	Techs_AllEffects_UseAnd[1] = new wxCheckBox(Tab_Techs, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Techs_AllEffects_List = new wxListBox(Tab_Techs, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Techs_AllEffects_Buttons = new wxBoxSizer(wxHORIZONTAL);
	Techs_AllEffects_Load = new wxButton(Tab_Techs, wxID_ANY, "Reload", wxDefaultPosition, wxSize(5, 20));
	Techs_AllEffects_Clear = new wxButton(Tab_Techs, wxID_ANY, "Clear *", wxDefaultPosition, wxSize(5, 20));
	Techs_AllEffects_Clear->SetToolTip("Clear the modified search texts");

	Effects_ComboBox_Type->Append("No Type/Invalid Type");	// Selection 0
	Effects_ComboBox_Type->Append("0 - Attribute Modifier (Set)");	// Selection 1
	Effects_ComboBox_Type->Append("1 - Resource Modifier (Set/+/-)");
	Effects_ComboBox_Type->Append("2 - Enable/Disable Unit");
	Effects_ComboBox_Type->Append("3 - Upgrade Unit");
	Effects_ComboBox_Type->Append("4 - Attribute Modifier (+/-)");
	Effects_ComboBox_Type->Append("5 - Attribute Modifier (Multiply)");
	Effects_ComboBox_Type->Append("6 - Resource Modifier (Multiply)");
	Effects_ComboBox_Type->Append("101 - Research Cost Modifier (Set/+/-)");
	Effects_ComboBox_Type->Append("102 - Disable Research");
	Effects_ComboBox_Type->Append("103 - Research Time Modifier (Set/+/-)");	// Selection 10
	Effects_ComboBox_Type->SetSelection(0);

	Techs_Buttons->Add(Techs_Add, 1, wxEXPAND);
	Techs_Buttons->Add(Techs_Insert, 1, wxEXPAND);
	Techs_Buttons->Add(Techs_Delete, 1, wxEXPAND);
	Techs_Buttons->Add(Techs_Copy, 1, wxEXPAND);
	Techs_Buttons->Add(Techs_Paste, 1, wxEXPAND);
	Techs_Buttons->Add(Techs_PasteInsert, 1, wxEXPAND);

	Techs_Searches[0]->Add(Techs_Search, 1, wxEXPAND);
	Techs_Searches[0]->Add(2, -1);
	Techs_Searches[0]->Add(Techs_UseAnd[0], 0, wxEXPAND);
	Techs_Searches[1]->Add(Techs_Search_R, 1, wxEXPAND);
	Techs_Searches[1]->Add(2, -1);
	Techs_Searches[1]->Add(Techs_UseAnd[1], 0, wxEXPAND);
	Techs_Techs->Add(Techs_Searches[0], 0, wxEXPAND);
	Techs_Techs->Add(Techs_Searches[1], 0, wxEXPAND);
	Techs_Techs->Add(-1, 2);
	Techs_Techs->Add(Techs_List, 1, wxEXPAND);
	Techs_Techs->Add(-1, 2);
	Techs_Techs->Add(Techs_Buttons, 0, wxEXPAND);

	Techs_ListArea->Add(-1, 10);
	Techs_ListArea->Add(Techs_Techs, 1, wxEXPAND);
	Techs_ListArea->Add(-1, 10);

	Techs_Effects_Buttons->Add(Techs_Effects_Add, 1, wxEXPAND);
	Techs_Effects_Buttons->Add(Techs_Effects_Insert, 1, wxEXPAND);
	Techs_Effects_Buttons->Add(Techs_Effects_Delete, 1, wxEXPAND);
	Techs_Effects_Buttons->Add(Techs_Effects_Copy, 1, wxEXPAND);
	Techs_Effects_Buttons->Add(Techs_Effects_Paste, 1, wxEXPAND);
	Techs_Effects_Buttons->Add(Techs_Effects_PasteInsert, 1, wxEXPAND);

	Techs_Holder_Name->Add(Techs_Text_Name, 0, wxEXPAND);
	Techs_Holder_Name->Add(Techs_Name, 1, wxEXPAND);
	Techs_Holder_Name->Add(Techs_Rename, 1, wxEXPAND);
	Techs_Holder_Name->Add(Techs_Restore, 1, wxEXPAND);

	Techs_Effects_Searches[0]->Add(Techs_Effects_Search, 1, wxEXPAND);
	Techs_Effects_Searches[0]->Add(2, -1);
	Techs_Effects_Searches[0]->Add(Techs_Effects_UseAnd[0], 0, wxEXPAND);
	Techs_Effects_Searches[1]->Add(Techs_Effects_Search_R, 1, wxEXPAND);
	Techs_Effects_Searches[1]->Add(2, -1);
	Techs_Effects_Searches[1]->Add(Techs_Effects_UseAnd[1], 0, wxEXPAND);
	Techs_Effects->Add(Techs_Effects_Searches[0], 0, wxEXPAND);
	Techs_Effects->Add(Techs_Effects_Searches[1], 0, wxEXPAND);
	Techs_Effects->Add(-1, 2);
	Techs_Effects->Add(Techs_Effects_List, 1, wxEXPAND);
	Techs_Effects->Add(-1, 2);
	Techs_Effects->Add(Techs_Effects_Buttons, 0, wxEXPAND);
	Techs_Effects->Add(-1, 2);
	Techs_Effects->Add(Techs_Effects_CopyToTechs, 0, wxEXPAND);

	Effects_ListArea->Add(-1, 10);
	Effects_ListArea->Add(Techs_Holder_Name, 0, wxEXPAND);
	Effects_ListArea->Add(-1, 5);
	Effects_ListArea->Add(Techs_Effects, 1, wxEXPAND);
	Effects_ListArea->Add(-1, 10);

	Effects_Holder_Type2->Add(Effects_Type, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_Type2->Add(Effects_ComboBox_Type, 2, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_Type->Add(Effects_Text_Type, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_Type->Add(Effects_Holder_Type2, 1, wxEXPAND);

	Effects_ComboBox_A->Add(Effects_ComboBox_UnitsA, 1, wxEXPAND);
	Effects_ComboBox_A->Add(Effects_ComboBox_ResourcesA, 1, wxEXPAND);
	Effects_ComboBox_A->Add(Effects_ComboBox_ResearchsA, 1, wxEXPAND);
	Effects_Holder_A->Add(Effects_A, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_A->Add(Effects_ComboBox_A, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Effects_Holder_DataA->Add(Effects_Text_A, 1, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataA->Add(Effects_Holder_A, 2, wxEXPAND);
	Effects_Holder_DataA->Add(Effects_Info_A, 2, wxEXPAND);

	Effects_ComboBox_B->Add(Effects_CheckBox_ModeB, 1, wxEXPAND);
	Effects_ComboBox_B->Add(Units_ComboBox_Class[2], 1, wxEXPAND);
	Effects_ComboBox_B->Add(Effects_ComboBox_UnitsB, 1, wxEXPAND);
	Effects_ComboBox_B->Add(Effects_ComboBox_ResourcesB, 1, wxEXPAND);
	Effects_Holder_B->Add(Effects_B, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_B->Add(Effects_ComboBox_B, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Effects_Holder_DataB->Add(Effects_Text_B, 1, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataB->Add(Effects_Holder_B, 2, wxEXPAND);
	Effects_Holder_DataB->Add(Effects_Info_B, 2, wxEXPAND);

	Effects_ComboBox_C->Add(Effects_CheckBox_ModeC, 1, wxEXPAND);
	Effects_ComboBox_C->Add(Effects_ComboBox_AttributesC, 1, wxEXPAND);
	Effects_Holder_C->Add(Effects_C, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_C->Add(Effects_ComboBox_C, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Effects_Holder_DataC->Add(Effects_Text_C, 1, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataC->Add(Effects_Holder_C, 2, wxEXPAND);
	Effects_Holder_DataC->Add(Effects_Info_C, 2, wxEXPAND);

	Effects_ComboBox_D->Add(Effects_ComboBox_ResearchsD, 1, wxEXPAND);
	Effects_Holder_D->Add(Effects_D, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_D->Add(Effects_ComboBox_D, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Effects_Holder_DataD->Add(Effects_Text_D, 1, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataD->Add(Effects_Holder_D, 2, wxEXPAND);
	Effects_Holder_DataD->Add(Effects_Info_D, 2, wxEXPAND);

	Effects_Holder_E->Add(Effects_E, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Effects_Holder_DataE->Add(Effects_Text_E, 1, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataE->Add(Effects_Holder_E, 2, wxEXPAND);
	Effects_Holder_DataE->Add(Effects_Info_E, 2, wxEXPAND);

	Effects_Holder_F->Add(Effects_F, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_F->Add(Attacks_ComboBox_Class[2], 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Effects_Holder_DataF->Add(Effects_Text_F, 1, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataF->Add(Effects_Holder_F, 2, wxEXPAND);
	Effects_Holder_DataF->Add(Effects_Info_F, 2, wxEXPAND);

	Effects_Holder_Data->Add(Effects_NeverHide, 0, wxEXPAND);
	Effects_Holder_Data->Add(-1, 5);
	Effects_Holder_Data->Add(Effects_Holder_DataA, 0, wxEXPAND);
	Effects_Holder_Data->Add(-1, 5);
	Effects_Holder_Data->Add(Effects_Holder_DataB, 0, wxEXPAND);
	Effects_Holder_Data->Add(-1, 5);
	Effects_Holder_Data->Add(Effects_Holder_DataC, 0, wxEXPAND);
	Effects_Holder_Data->Add(-1, 5);
	Effects_Holder_Data->Add(Effects_Holder_DataD, 0, wxEXPAND);
	Effects_Holder_Data->Add(-1, 5);
	Effects_Holder_Data->Add(Effects_Holder_DataE, 0, wxEXPAND);
	Effects_Holder_Data->Add(Effects_Holder_DataF, 0, wxEXPAND);

	Techs_AllEffects_Searches[0]->Add(Techs_AllEffects_Search, 1, wxEXPAND);
	Techs_AllEffects_Searches[0]->Add(2, -1);
	Techs_AllEffects_Searches[0]->Add(Techs_AllEffects_UseAnd[0], 0, wxEXPAND);
	Techs_AllEffects_Searches[1]->Add(Techs_AllEffects_Search_R, 1, wxEXPAND);
	Techs_AllEffects_Searches[1]->Add(2, -1);
	Techs_AllEffects_Searches[1]->Add(Techs_AllEffects_UseAnd[1], 0, wxEXPAND);
	Techs_AllEffects->Add(Techs_AllEffects_Searches[0], 0, wxEXPAND);
	Techs_AllEffects->Add(Techs_AllEffects_Searches[1], 0, wxEXPAND);
	Techs_AllEffects->Add(-1, 2);
	Techs_AllEffects->Add(Techs_AllEffects_List, 1, wxEXPAND);
	Techs_AllEffects->Add(-1, 2);
	Techs_AllEffects_Buttons->Add(Techs_AllEffects_Load, 2, wxEXPAND);
	Techs_AllEffects_Buttons->Add(2, -1);
	Techs_AllEffects_Buttons->Add(Techs_AllEffects_Clear, 1, wxEXPAND);
	Techs_AllEffects->Add(Techs_AllEffects_Buttons, 0, wxEXPAND);

	Effects_DataArea->Add(-1, 10);
	Effects_DataArea->Add(Effects_Holder_Type, 0, wxEXPAND);
	Effects_DataArea->Add(-1, 5);
	Effects_DataArea->Add(Effects_Holder_Data, 0, wxEXPAND);
	Effects_DataArea->Add(-1, 5);
	Effects_DataArea->Add(Effects_Link, 0, wxEXPAND);
	Effects_DataArea->Add(-1, 5);
	Effects_DataArea->Add(Techs_AllEffects, 1, wxEXPAND);
	Effects_DataArea->Add(-1, 10);

	Techs_Main->Add(10, -1);
	Techs_Main->Add(Techs_ListArea, 3, wxEXPAND); // 3
	Techs_Main->Add(10, -1);
	Techs_Main->Add(Effects_ListArea, 4, wxEXPAND); // 3+1
	Techs_Main->Add(10, -1);
	Techs_Main->Add(Effects_DataArea, 5, wxEXPAND); // 6-1
	Techs_Main->Add(10, -1);

	Effects_E->Show(false);	// only for attributes 8, 9
	Effects_F->Show(false);	// only for attributes 8, 9
	Effects_ComboBox_A->Show(false);
	Effects_ComboBox_B->Show(false);
	Effects_ComboBox_C->Show(false);
	Effects_ComboBox_D->Show(false);
	Effects_ComboBox_UnitsA->Show(false);	// for Effects 0, 2, 3, 4, 5
	Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
	Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
	Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
	Units_ComboBox_Class[2]->Show(false);	// for Effects 0, 4, 5
	Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
	Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
	Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
	Effects_ComboBox_AttributesC->Show(false);	// for Effects 0, 4, 5
	Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
	Attacks_ComboBox_Class[2]->Show(false);	// only for attributes 8, 9

	Tab_Techs->SetSizer(Techs_Main);

	for(short loop = 0; loop < 2; ++loop)
	{
		Connect(Techs_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechSearch));
		Connect(Techs_Effects_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsSearch));
		Connect(Techs_AllEffects_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::LoadAllTechEffects));
	}
	Connect(Techs_Rename->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechRename));
	Connect(Techs_Restore->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechRenameGE2));
	Connect(Techs_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTechSelect));
	Connect(Techs_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTechSearch));
	Connect(Techs_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTechSearch));
	Connect(Techs_Effects_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnEffectsSelect));
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
	Connect(Techs_AllEffects_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnAllTechEffectSelect));
	Connect(Techs_AllEffects_Load->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::LoadAllTechEffects));
	Connect(Techs_AllEffects_Clear->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::ClearAllTechEffects));

	Techs_Name->Connect(Techs_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_Type->Connect(Effects_Type->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_ComboBox_Type->Connect(Effects_ComboBox_Type->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_A->Connect(Effects_A->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_B->Connect(Effects_B->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_C->Connect(Effects_C->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_D->Connect(Effects_D->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Techs), NULL, this);
	Effects_ComboBox_UnitsA->Connect(Effects_ComboBox_UnitsA->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_ComboBox_ResourcesA->Connect(Effects_ComboBox_ResourcesA->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_ComboBox_ResearchsA->Connect(Effects_ComboBox_ResearchsA->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_CheckBox_ModeB->Connect(Effects_CheckBox_ModeB->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_Techs), NULL, this);
	Units_ComboBox_Class[2]->Connect(Units_ComboBox_Class[2]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_ComboBox_UnitsB->Connect(Effects_ComboBox_UnitsB->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_ComboBox_ResourcesB->Connect(Effects_ComboBox_ResourcesB->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_CheckBox_ModeC->Connect(Effects_CheckBox_ModeC->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_Techs), NULL, this);
	Effects_ComboBox_AttributesC->Connect(Effects_ComboBox_AttributesC->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Effects_ComboBox_ResearchsD->Connect(Effects_ComboBox_ResearchsD->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
	Attacks_ComboBox_Class[2]->Connect(Attacks_ComboBox_Class[2]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Techs), NULL, this);
}

void AGE_Frame::OnKillFocus_Techs(wxFocusEvent &Event)
{
	if(Event.GetId() == Effects_E->GetId() || Event.GetId() == Effects_F->GetId())
	{
		if(!Effects_E->IsEmpty() && !Effects_F->IsEmpty()) // if has something, then update float value.
		{
			float Amount = lexical_cast<float>(Effects_E->GetValue());
			short Class = lexical_cast<short>(Effects_F->GetValue());
			if(Amount > -1 && Amount < 256 && Class > -1 && Class < 256) // positive amount 0 to 255
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount + Class * 256));
				Effects_D->SaveEdits();
			}
			else if(Amount > -256 && Amount < 0 && Class > -1 && Class < 256) // negative amount -255 to -1
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount - Class * 256));
				Effects_D->SaveEdits();
			}
		}
		ListEffects();
		return;
	}
	if(((AGETextCtrl*)Event.GetEventObject())->SaveEdits() != 0) return;
	if(Event.GetId() == Techs_Name->GetId())
	{
		ListTechs();
	}
	else
	{
		ListEffects();
	}
	Event.Skip();
}

void AGE_Frame::OnUpdateCheck_Techs(wxCommandEvent &Event)
{
	((AGECheckBox*)Event.GetEventObject())->OnUpdate(Event);
	ListEffects();
}

void AGE_Frame::OnUpdateCombo_Techs(wxCommandEvent &Event)
{
	if(Event.GetId() == Attacks_ComboBox_Class[2]->GetId())
	{
		short Class = Attacks_ComboBox_Class[2]->GetSelection() - 1;
		if(Class >= 0)
		{
			float Amount = lexical_cast<float>(Effects_E->GetValue());
			if(Amount > -1 && Amount < 256) // positive amount 0 to 255
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount + Class * 256));
			}
			else if(Amount > -256 && Amount < 0) // negative amount -255 to -1
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount - Class * 256));
			}
		}
		else
		{
			Effects_E->ChangeValue("0");
			Effects_F->ChangeValue("0");
			Effects_D->ChangeValue("0");
		}
		Effects_D->SaveEdits();

		ListEffects();
		return;
	}
	((AGEComboBox*)Event.GetEventObject())->OnUpdate(Event);
	ListEffects();
}
