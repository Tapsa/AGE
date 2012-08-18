/* AGEFrame_cpp/Techage.cpp */

#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetTechageName(short &Index)
{
	string Name = "";
	if(GenieFile->Techages[Index].Name != "")
	{
		Name = GenieFile->Techages[Index].Name;
	}
	else
	{
		Name = "New Technology";
	}
	return Name;
}

void AGE_Frame::OnTechageRenameGE2(wxCommandEvent& Event)
{
	short Selections = Techs_Techs_List->GetSelections(Items);
	if(Selections != 0)
	{
		string Name;
		for(short loop = 0;loop < GenieFile->Techages.size();loop++)
		{
			GenieFile->Techages[loop].Name = "Tech";
		}
		ListTechages();
	}
}

void AGE_Frame::OnTechageRename(wxCommandEvent& Event)
{
	short Selections = Techs_Techs_List->GetSelections(Items);
	if(Selections != 0)
	{
		string Name;
		string NewName;
		string CivName;
		short TechEffects = 0;
		for(short loop3 = 0;loop3 < GenieFile->Techages.size();loop3++)
		{
			TechEffects = GenieFile->Techages[loop3].Effects.size();
			if(TechEffects < 1) // empty techs.
			{
				GenieFile->Techages[loop3].Name = "New Technology";
			}
			else // other than empty techs, not researches if research loop doesn't rename them.
			{
				GenieFile->Techages[loop3].Name = "Non-Research";
			}
		}
		short ResearchTechID = 0;
		for(short loop = 0;loop < GenieFile->Researchs.size();loop++) // Rename of techs. Make it reverse loop.
		{
			ResearchTechID = GenieFile->Researchs[loop].TechageID;
			if(ResearchTechID > 0) // Only researches which have techs.
			{
				if(LanguageDllString(GenieFile->Researchs[loop].LanguageDllName) != "") // has a lang dll name
				{
					Name = LanguageDllString(GenieFile->Researchs[loop].LanguageDllName);
				}
				else // use internal name instead
				{
					Name = GenieFile->Researchs[loop].Name;
				}
				NewName = Name.substr(0,31);
				GenieFile->Techages[ResearchTechID].Name = NewName;
			}
		}
		short CivTechTreeID = 0;
		short CivTeamBonusID = 0;
		for(short loop2 = 0;loop2 < GenieFile->Civs.size();loop2++) // Rename of techs. Make it reverse loop.
		{
			CivName = lexical_cast<string>(GenieFile->Civs[loop2].Name); // Civ internal name.
			CivTechTreeID = GenieFile->Civs[loop2].TechTreeID;
			CivTeamBonusID = GenieFile->Civs[loop2].TeamBonusID;
			if(CivTechTreeID > 0)
			{
				Name = CivName;
				Name += " Technology Tree";
				NewName = Name.substr(0,31);
				GenieFile->Techages[CivTechTreeID].Name = NewName;
			}
			if(CivTeamBonusID > 0)
			{
				Name = CivName;
				Name += " Team Bonus";
				NewName = Name.substr(0,31);
				GenieFile->Techages[CivTeamBonusID].Name = NewName;
			}
		}
		ListTechages();
	}
}

void AGE_Frame::OnTechageSearch(wxCommandEvent& Event)
{
	ListTechages(false);
}

void AGE_Frame::ListTechages(bool Sized)
{
	string Name, CompareText;
	SearchText = wxString(Techs_Techs_Search->GetValue()).Lower();
	ExcludeText = wxString(Techs_Techs_Search_R->GetValue()).Lower();

	short Selections = Techs_Techs_List->GetSelections(Items);
	if(Techs_Techs_List->GetCount() > 0) Techs_Techs_List->Clear();

	short IDCount = 3, TechIDs[IDCount];
	if(Sized)
	{
		TechIDs[0] = Research_ComboBox_TechID->GetSelection();
		TechIDs[1] = Civs_ComboBox_TechTree->GetSelection();
		TechIDs[2] = Civs_ComboBox_TeamBonus->GetSelection();

		if(Research_ComboBox_TechID->GetCount() > 0)
		{
			Research_ComboBox_TechID->Clear();
		}
		if(Civs_ComboBox_TechTree->GetCount() > 0)
		{
			Civs_ComboBox_TechTree->Clear();
		}
		if(Civs_ComboBox_TeamBonus->GetCount() > 0)
		{
			Civs_ComboBox_TeamBonus->Clear();
		}

		for(short loop = 0;loop < IDCount;loop++)
		{
			if(TechIDs[loop] == wxNOT_FOUND)
			{
				TechIDs[loop] = 0;
			}
		}

		Research_ComboBox_TechID->Append("-1 - None");
		Civs_ComboBox_TechTree->Append("-1 - None");
		Civs_ComboBox_TeamBonus->Append("-1 - None");
	}

	for(short loop = 0;loop < GenieFile->Techages.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTechageName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText))
		{
			Techs_Techs_List->Append(Name, (void*)&GenieFile->Techages[loop]);
		}
		if(Sized)
		{
			Research_ComboBox_TechID->Append(Name);
			Civs_ComboBox_TechTree->Append(Name);
			Civs_ComboBox_TeamBonus->Append(Name);
		}
	}

	ListingFix(Selections, Techs_Techs_List);
	if(Sized)
	{
		Research_ComboBox_TechID->SetSelection(TechIDs[0]);
		Civs_ComboBox_TechTree->SetSelection(TechIDs[1]);
		Civs_ComboBox_TeamBonus->SetSelection(TechIDs[2]);
	}

	wxCommandEvent E;
	OnTechageSelect(E);
}

void AGE_Frame::OnTechageSelect(wxCommandEvent& Event)
{
	short Selections = Techs_Techs_List->GetSelections(Items);
	if(Selections != 0)
	{
		TechIDs.resize(Selections);
		genie::Techage * TechPointer;
		for(short loop = Selections-1;loop >= 0;loop--)
		{
			TechPointer = (genie::Techage*)Techs_Techs_List->GetClientData(Items.Item(loop));
			TechIDs[loop] = (TechPointer - (&GenieFile->Techages[0]));
		}
		Techs_Name->ChangeValue(TechPointer->Name);
		Techs_Name->Container = &TechPointer->Name;
		ListEffects();
	}
}

void AGE_Frame::OnTechageAdd(wxCommandEvent& Event)	// Works.
{
	if(GenieFile != NULL)
	{
		wxBusyCursor WaitCursor;
		genie::Techage Temp;
		GenieFile->Techages.push_back(Temp);
		Added = true;
		ListTechages();
	}
}

void AGE_Frame::OnTechageInsert(wxCommandEvent& Event)	// Works.
{
	short Selections = Techs_Techs_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::Techage Temp;
		GenieFile->Techages.insert(GenieFile->Techages.begin() + TechIDs[0], Temp);
		ListTechages();
	}
}

void AGE_Frame::OnTechageDelete(wxCommandEvent& Event)	// Works.
{
	short Selections = Techs_Techs_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop = Selections-1;loop >= 0;loop--)
		GenieFile->Techages.erase(GenieFile->Techages.begin() + TechIDs[loop]);
		ListTechages();
	}
}

void AGE_Frame::OnTechageCopy(wxCommandEvent& Event)	// Works.
{
	short Selections = Techs_Techs_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		TechCopies.resize(Selections);
		for(short loop = 0;loop < Selections;loop++)
		TechCopies[loop] = GenieFile->Techages[TechIDs[loop]];
	}
}

void AGE_Frame::OnTechagePaste(wxCommandEvent& Event)	// Works.
{
	short Selections = Techs_Techs_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		if(TechCopies.size()+TechIDs[0] > GenieFile->Techages.size())
		GenieFile->Techages.resize(TechCopies.size()+TechIDs[0]);
		for(short loop = 0;loop < TechCopies.size();loop++)
		GenieFile->Techages[TechIDs[0]+loop] = TechCopies[loop];
		ListTechages();
	}
}

void AGE_Frame::OnTechagePasteInsert(wxCommandEvent& Event)	// Works.
{
	short Selections = Techs_Techs_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::Techage Temp;
		GenieFile->Techages.insert(GenieFile->Techages.begin() + TechIDs[0], TechCopies.size(), Temp);
		for(short loop = 0;loop < TechCopies.size();loop++)
		GenieFile->Techages[TechIDs[0]+loop] = TechCopies[loop];
		ListTechages();
	}
}

string AGE_Frame::GetEffectName(short &Index)
{
	string Name = "";
	switch(GenieFile->Techages[TechIDs[0]].Effects[Index].Type)
	{
		case 0:
		{
			//Name = "Attribute Modifier (Set)";
			Name = "Set Attribute "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].C)+" To "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D)+" For ";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].B == -1)
				Name += "Unit "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A);
			else
				Name += "Class "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B);
		}
		break;
		case 1:
		{
			//Name = "Resource Modifier (Set/+/-)";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].B == 0)
				Name = "Set Resource "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)+" To "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
			else
				Name = "Change Resource "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)+" By "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
		}
		break;
		case 2:
		{
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].B == 0)
				Name = "Disable";
			else
				Name = "Enable";
			Name += " Unit "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A);
		}
		break;
		case 3:
		{
			Name = "Upgrade Unit "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)+" To "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B);
		}
		break;
		case 4:
		{
			//Name = "Attribute Modifier (+/-)";
			Name = "Change Attribute "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].C)+" By "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D)+" For ";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].B == -1)
				Name += "Unit "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A);
			else
				Name += "Class "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B);
		}
		break;
		case 5:
		{
			//Name = "Attribute Modifier (Multiply)";
			Name = "Multiply Attribute "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].C)+" By "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D)+" For ";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].B == -1)
				Name += "Unit "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A);
			else
				Name += "Class "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B);
		}
		break;
		case 6:
		{
			//Name = "Resource Modifier (Multiply)";
			Name = "Multiply Resource "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)+" By "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
		}
		break;
		case 101:
		{
			//Name = "Research Cost Modifier (Set/+/-)";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].C == 0)
				Name = "Set Research "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)+" Cost Type "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B)+" To "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
			else
				Name = "Change Research "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)+" Cost Type "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].B)+" By "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
		}
		break;
		case 102:
		{
			Name = "Disable Research "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
		}
		break;
		case 103:
		{
			//Name = "Research Time Modifier (Set/+/-)";
			if(GenieFile->Techages[TechIDs[0]].Effects[Index].C == 0)
				Name = "Set Research "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)+" Time To "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
			else
				Name = "Change Research "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].A)+" Time By "+lexical_cast<string>(GenieFile->Techages[TechIDs[0]].Effects[Index].D);
		}
		break;
		default:
		{
			Name = "No Type/Invalid Type";
		}
	}
	return Name;
}

void AGE_Frame::OnEffectsSearch(wxCommandEvent& Event)
{
	ListEffects();
}

void AGE_Frame::ListEffects()
{
	string Name, CompareText;
	SearchText = wxString(Techs_Effects_Search->GetValue()).Lower();
	ExcludeText = wxString(Techs_Effects_Search_R->GetValue()).Lower();
	
	short Selections = Techs_Effects_List->GetSelections(Items);
	if(Techs_Effects_List->GetCount() > 0) Techs_Effects_List->Clear();
		
	for(short loop = 0;loop < GenieFile->Techages[TechIDs[0]].Effects.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetEffectName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText))
		{
			Techs_Effects_List->Append(Name, (void*)&GenieFile->Techages[TechIDs[0]].Effects[loop]);
		}
	}
	ListingFix(Selections, Techs_Effects_List);

	wxCommandEvent E;
	OnEffectsSelect(E);
}

void AGE_Frame::OnEffectsSelect(wxCommandEvent& Event)
{
	short Selections = Techs_Effects_List->GetSelections(Items);
	if(Selections != 0)
	{
		Effects_Holder_Type->Show(true);
		Effects_D->Enable(true);
		EffectIDs.resize(Selections);
		genie::TechageEffect * EffectPointer;
		for(short loop = Selections-1;loop >= 0;loop--)
		{
			EffectPointer = (genie::TechageEffect*)Techs_Effects_List->GetClientData(Items.Item(loop));
			EffectIDs[loop] = (EffectPointer - (&GenieFile->Techages[TechIDs[0]].Effects[0]));
		}
		Effects_Type->ChangeValue(lexical_cast<string>((short)(EffectPointer->Type)));
		Effects_Type->Container = &EffectPointer->Type;
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
		Effects_A->Container = &EffectPointer->A;
		Effects_ComboBox_UnitsA->SetSelection(0);
		Effects_ComboBox_UnitsA->SetSelection(EffectPointer->A + 1);
		Effects_ComboBox_ResourcesA->SetSelection(0);
		Effects_ComboBox_ResourcesA->SetSelection(EffectPointer->A + 1);
		Effects_ComboBox_ResearchsA->SetSelection(0);
		Effects_ComboBox_ResearchsA->SetSelection(EffectPointer->A + 1);
		Effects_B->ChangeValue(lexical_cast<string>(EffectPointer->B));
		Effects_B->Container = &EffectPointer->B;
		Effects_CheckBox_ModeB->SetValue((bool)EffectPointer->B);
		Units_ComboBox_Class[2]->SetSelection(0);
		Units_ComboBox_Class[2]->SetSelection(EffectPointer->B + 1);
		Effects_ComboBox_UnitsB->SetSelection(0);
		Effects_ComboBox_UnitsB->SetSelection(EffectPointer->B + 1);
		Effects_ComboBox_ResourcesB->SetSelection(0);
		Effects_ComboBox_ResourcesB->SetSelection(EffectPointer->B + 1);
		Effects_C->ChangeValue(lexical_cast<string>(EffectPointer->C));
		Effects_C->Container = &EffectPointer->C;
		Effects_CheckBox_ModeC->SetValue((bool)EffectPointer->C);
		Effects_ComboBox_AttributesC->SetSelection(0);
		Effects_ComboBox_AttributesC->SetSelection(EffectPointer->C + 1);
		Effects_D->ChangeValue(lexical_cast<string>(EffectPointer->D));
		Effects_D->Container = &EffectPointer->D;
		Effects_ComboBox_ResearchsD->SetSelection(0);
		Effects_ComboBox_ResearchsD->SetSelection(EffectPointer->D + 1);
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
				Effects_C->Show(false);	// not for Effects 1, 2, 3, 6, 102
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
				Effects_C->Show(false);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(false);	// not for Effects 2, 3
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
				Effects_C->Show(false);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(false);	// not for Effects 2, 3
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
				Effects_B->Show(false);	// not for Effects 6, 102, 103
				Effects_C->Show(false);	// not for Effects 1, 2, 3, 6, 102
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
				Effects_A->Show(false);	// not for Effects 102
				Effects_B->Show(false);	// not for Effects 6, 102, 103
				Effects_C->Show(false);	// not for Effects 1, 2, 3, 6, 102
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
				Effects_B->Show(false);	// not for Effects 6, 102, 103
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
				Effects_A->Show(false);	// not for Effects 102
				Effects_B->Show(false);	// not for Effects 6, 102, 103
				Effects_C->Show(false);	// not for Effects 1, 2, 3, 6, 102
				Effects_D->Show(false);	// not for Effects 2, 3
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

void AGE_Frame::OnEffectsAdd(wxCommandEvent& Event)	// Works.
{
	short Selections = Techs_Techs_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::TechageEffect Temp;
		GenieFile->Techages[TechIDs[0]].Effects.push_back(Temp);
		Added = true;
		ListEffects();
	}
}

void AGE_Frame::OnEffectsInsert(wxCommandEvent& Event)	// Works.
{
	short Selections = Techs_Effects_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::TechageEffect Temp;
		GenieFile->Techages[TechIDs[0]].Effects.insert(GenieFile->Techages[TechIDs[0]].Effects.begin() + EffectIDs[0], Temp);
		ListEffects();
	}
}

void AGE_Frame::OnEffectsDelete(wxCommandEvent& Event)	// Works.
{
	short Selections = Techs_Effects_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop = Selections-1;loop >= 0;loop--)
		GenieFile->Techages[TechIDs[0]].Effects.erase(GenieFile->Techages[TechIDs[0]].Effects.begin() + EffectIDs[loop]);
		ListEffects();
	}
}

void AGE_Frame::OnEffectsCopy(wxCommandEvent& Event)	// Works.
{
	short Selections = Techs_Effects_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		EffectCopies.resize(Selections);
		for(short loop = 0;loop < Selections;loop++)
		EffectCopies[loop] = GenieFile->Techages[TechIDs[0]].Effects[EffectIDs[loop]];
	}
}

void AGE_Frame::OnEffectsPaste(wxCommandEvent& Event)	// Works.
{
	short Selections = Techs_Effects_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		if(EffectCopies.size()+EffectIDs[0] > GenieFile->Techages[TechIDs[0]].Effects.size())
		GenieFile->Techages[TechIDs[0]].Effects.resize(EffectCopies.size()+EffectIDs[0]);
		for(short loop = 0;loop < EffectCopies.size();loop++)
		GenieFile->Techages[TechIDs[0]].Effects[EffectIDs[0]+loop] = EffectCopies[loop];
		ListEffects();
	}
}

void AGE_Frame::OnEffectsPasteInsert(wxCommandEvent& Event)	// Works.
{
	short Selections = Techs_Effects_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::TechageEffect Temp;
		GenieFile->Techages[TechIDs[0]].Effects.insert(GenieFile->Techages[TechIDs[0]].Effects.begin() + EffectIDs[0], EffectCopies.size(), Temp);
		for(short loop = 0;loop < EffectCopies.size();loop++)
		GenieFile->Techages[TechIDs[0]].Effects[EffectIDs[0]+loop] = EffectCopies[loop];
		ListEffects();
	}
}

void AGE_Frame::CreateTechageControls()
{
	Tab_Techage = new wxPanel(TabBar_Data, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Techs_Main = new wxBoxSizer(wxHORIZONTAL);
	Techs_ListArea = new wxBoxSizer(wxVERTICAL);
	Techs_Techs_Buttons = new wxGridSizer(3, 0, 0);
	Effects_DataArea = new wxBoxSizer(wxVERTICAL);
	Effects_ListArea = new wxBoxSizer(wxVERTICAL);
	Techs_Effects_Buttons = new wxGridSizer(3, 0, 0);
	Effects_DataAreaProperties = new wxBoxSizer(wxVERTICAL);
	Techs_Techs = new wxStaticBoxSizer(wxVERTICAL, Tab_Techage, "Technologies");
	Techs_Techs_Search = new wxTextCtrl(Tab_Techage, wxID_ANY);
	Techs_Techs_Search_R = new wxTextCtrl(Tab_Techage, wxID_ANY);
	Techs_Techs_List = new wxListBox(Tab_Techage, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, wxLB_EXTENDED);
	Techs_Techs_Add = new wxButton(Tab_Techage, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Techs_Techs_Insert = new wxButton(Tab_Techage, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Techs_Techs_Delete = new wxButton(Tab_Techage, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Techs_Techs_Copy = new wxButton(Tab_Techage, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Techs_Techs_Paste = new wxButton(Tab_Techage, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Techs_Techs_PasteInsert = new wxButton(Tab_Techage, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	Techs_Techs_Rename = new wxButton(Tab_Techage, wxID_ANY, "Rename technologies", wxDefaultPosition, wxSize(0, 20));
	Techs_Techs_Restore = new wxButton(Tab_Techage, wxID_ANY, "Rename for GeniEd 2", wxDefaultPosition, wxSize(0, 20));

	Techs_Holder_Name = new wxBoxSizer(wxVERTICAL);
	Techs_Text_Name = new wxStaticText(Tab_Techage, wxID_ANY, " Technology Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Techs_Name = new TextCtrl_String(Tab_Techage, "0", NULL);

	Techs_Effects = new wxStaticBoxSizer(wxVERTICAL, Tab_Techage, "Effects");
	Techs_Effects_Search = new wxTextCtrl(Tab_Techage, wxID_ANY);
	Techs_Effects_Search_R = new wxTextCtrl(Tab_Techage, wxID_ANY);
//	Techs_Effects_UseAnd = new wxCheckBox(Tab_Techage, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20), 0, wxDefaultValidator);
	Techs_Effects_List = new wxListBox(Tab_Techage, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, wxLB_EXTENDED);
	Techs_Effects_Add = new wxButton(Tab_Techage, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Techs_Effects_Insert = new wxButton(Tab_Techage, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Techs_Effects_Delete = new wxButton(Tab_Techage, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Techs_Effects_Copy = new wxButton(Tab_Techage, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Techs_Effects_Paste = new wxButton(Tab_Techage, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Techs_Effects_PasteInsert = new wxButton(Tab_Techage, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	Effects_Holder_Type = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_Type2 = new wxBoxSizer(wxHORIZONTAL);
	Effects_Text_Type = new wxStaticText(Tab_Techage, wxID_ANY, " Effect Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Type = new TextCtrl_Byte(Tab_Techage, "0", NULL);
	Effects_ComboBox_Type = new ComboBox_Byte_EffectType(Tab_Techage, Effects_Type);
	Effects_Holder_Data = new wxStaticBoxSizer(wxVERTICAL, Tab_Techage, "Effect Attributes");
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
	Effects_Text_A = new wxStaticText(Tab_Techage, wxID_ANY, "Attribute A ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_A = new TextCtrl_Short(Tab_Techage, "0", NULL);
	Effects_ComboBox_A = new wxBoxSizer(wxHORIZONTAL);
	Effects_ComboBox_UnitsA = new ComboBox_Short(Tab_Techage, Effects_A);
	Effects_ComboBox_ResourcesA = new ComboBox_Short(Tab_Techage, Effects_A);
	Effects_ComboBox_ResearchsA = new ComboBox_Short(Tab_Techage, Effects_A);
	Effects_Info_A = new wxStaticText(Tab_Techage, wxID_ANY, " Info A", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_B = new wxStaticText(Tab_Techage, wxID_ANY, "Attribute B ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_B = new TextCtrl_Short(Tab_Techage, "0", NULL);
	Effects_ComboBox_B = new wxBoxSizer(wxHORIZONTAL);
	Effects_CheckBox_ModeB = new CheckBox_Short(Tab_Techage, "", Effects_B);
	Units_ComboBox_Class[2] = new ComboBox_Short(Tab_Techage, Effects_B);
	Effects_ComboBox_UnitsB = new ComboBox_Short(Tab_Techage, Effects_B);
	Effects_ComboBox_ResourcesB = new ComboBox_Short(Tab_Techage, Effects_B);
	Effects_Info_B = new wxStaticText(Tab_Techage, wxID_ANY, " Info B", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_C = new wxStaticText(Tab_Techage, wxID_ANY, "Attribute C ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_C = new TextCtrl_Short(Tab_Techage, "0", NULL);
	Effects_ComboBox_C = new wxBoxSizer(wxHORIZONTAL);
	Effects_CheckBox_ModeC = new CheckBox_Short(Tab_Techage, "", Effects_C);
	Effects_ComboBox_AttributesC = new ComboBox_Short(Tab_Techage, Effects_C);
	Effects_Info_C = new wxStaticText(Tab_Techage, wxID_ANY, " Info C", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_D = new wxStaticText(Tab_Techage, wxID_ANY, "Attribute D ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_D = new TextCtrl_Float(Tab_Techage, "0", NULL);
	Effects_ComboBox_D = new wxBoxSizer(wxHORIZONTAL);
	Effects_ComboBox_ResearchsD = new ComboBox_Float(Tab_Techage, Effects_D);
	Effects_Info_D = new wxStaticText(Tab_Techage, wxID_ANY, " Info D", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_E = new wxStaticText(Tab_Techage, wxID_ANY, "Amount or % ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_E = new wxTextCtrl(Tab_Techage, wxID_ANY);
	Effects_Info_E = new wxStaticText(Tab_Techage, wxID_ANY, " Attack | Armor", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_F = new wxStaticText(Tab_Techage, wxID_ANY, "Class ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_F = new TextCtrl_Short(Tab_Techage, "0", NULL);
	Attacks_ComboBox_Class[2] = new ComboBox_Short(Tab_Techage, Effects_F);
	Effects_Info_F = new wxStaticText(Tab_Techage, wxID_ANY, " Attack | Armor", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Link = new wxHyperlinkCtrl(Tab_Techage, wxID_ANY, "GenieWiki Effect Types", "http://www.digitization.org/wiki/index.php?title=Genie_technology#Effects");

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

	Techs_Techs_Buttons->Add(Techs_Techs_Add, 1, wxEXPAND);
	Techs_Techs_Buttons->Add(Techs_Techs_Insert, 1, wxEXPAND);
	Techs_Techs_Buttons->Add(Techs_Techs_Delete, 1, wxEXPAND);
	Techs_Techs_Buttons->Add(Techs_Techs_Copy, 1, wxEXPAND);
	Techs_Techs_Buttons->Add(Techs_Techs_Paste, 1, wxEXPAND);
	Techs_Techs_Buttons->Add(Techs_Techs_PasteInsert, 1, wxEXPAND);

	Techs_Techs->Add(Techs_Techs_Search, 0, wxEXPAND);
	Techs_Techs->Add(Techs_Techs_Search_R, 0, wxEXPAND);
	Techs_Techs->Add(-1, 2);
	Techs_Techs->Add(Techs_Techs_List, 1, wxEXPAND);
	Techs_Techs->Add(-1, 2);
	Techs_Techs->Add(Techs_Techs_Buttons, 0, wxEXPAND);

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
	Techs_Holder_Name->Add(Techs_Techs_Rename, 1, wxEXPAND);
	Techs_Holder_Name->Add(Techs_Techs_Restore, 1, wxEXPAND);

	Techs_Effects->Add(Techs_Effects_Search, 0, wxEXPAND);
	Techs_Effects->Add(Techs_Effects_Search_R, 0, wxEXPAND);
//	Techs_Effects->Add(Techs_Effects_UseAnd, 0, wxEXPAND);
	Techs_Effects->Add(-1, 2);
	Techs_Effects->Add(Techs_Effects_List, 1, wxEXPAND);
	Techs_Effects->Add(-1, 2);
	Techs_Effects->Add(Techs_Effects_Buttons, 0, wxEXPAND);

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

	Effects_DataArea->Add(-1, 10);
	Effects_DataArea->Add(Effects_Holder_Type, 0, wxEXPAND);
	Effects_DataArea->Add(-1, 5);
	Effects_DataArea->Add(Effects_Holder_Data, 0, wxEXPAND);
	Effects_DataArea->Add(-1, 5);
	Effects_DataArea->Add(Effects_Link, 0, wxEXPAND);

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
//	Techs_Effects_UseAnd->Show(false);

	Tab_Techage->SetSizer(Techs_Main);

	Connect(Techs_Techs_Rename->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechageRename));
	Connect(Techs_Techs_Restore->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechageRenameGE2));
	Connect(Techs_Techs_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTechageSelect));
	Connect(Techs_Techs_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTechageSearch));
	Connect(Techs_Techs_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTechageSearch));
	Connect(Techs_Effects_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnEffectsSelect));
	Connect(Techs_Effects_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnEffectsSearch));
	Connect(Techs_Effects_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnEffectsSearch));
	Connect(Techs_Techs_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechageAdd));
	Connect(Techs_Techs_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechageInsert));
	Connect(Techs_Techs_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechageDelete));
	Connect(Techs_Techs_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechageCopy));
	Connect(Techs_Techs_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechagePaste));
	Connect(Techs_Techs_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechagePasteInsert));
	Connect(Techs_Effects_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsAdd));
	Connect(Techs_Effects_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsInsert));
	Connect(Techs_Effects_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsDelete));
	Connect(Techs_Effects_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsCopy));
	Connect(Techs_Effects_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsPaste));
	Connect(Techs_Effects_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsPasteInsert));
	Effects_E->Connect(Effects_E->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TextControls), NULL, this);
	Effects_F->Connect(Effects_F->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TextControls), NULL, this);

	Techs_Name->Connect(Techs_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Effects_Type->Connect(Effects_Type->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxByteEffectType), NULL, this);
	Effects_ComboBox_Type->Connect(Effects_ComboBox_Type->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxByteEffectType), NULL, this);
	Effects_A->Connect(Effects_A->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	Effects_B->Connect(Effects_B->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	Effects_C->Connect(Effects_C->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	Effects_D->Connect(Effects_D->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Float), NULL, this);
	Effects_ComboBox_UnitsA->Connect(Effects_ComboBox_UnitsA->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);
	Effects_ComboBox_ResourcesA->Connect(Effects_ComboBox_ResourcesA->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);
	Effects_ComboBox_ResearchsA->Connect(Effects_ComboBox_ResearchsA->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);
	Effects_CheckBox_ModeB->Connect(Effects_CheckBox_ModeB->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_CheckBoxShort), NULL, this);
	Units_ComboBox_Class[2]->Connect(Units_ComboBox_Class[2]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);
	Effects_ComboBox_UnitsB->Connect(Effects_ComboBox_UnitsB->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);
	Effects_ComboBox_ResourcesB->Connect(Effects_ComboBox_ResourcesB->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);
	Effects_CheckBox_ModeC->Connect(Effects_CheckBox_ModeC->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_CheckBoxShort), NULL, this);
	Effects_ComboBox_AttributesC->Connect(Effects_ComboBox_AttributesC->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);
	Effects_ComboBox_ResearchsD->Connect(Effects_ComboBox_ResearchsD->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxFloat), NULL, this);
	Attacks_ComboBox_Class[2]->Connect(Attacks_ComboBox_Class[2]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes), NULL, this);

}
