/* AGEFrame_cpp/Research.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetResearchName(int Index)
{
	string Name = "";	
	if(LanguageDllString(GenieFile->Researchs[Index].LanguageDllName) != wxT(""))
	{
		Name = LanguageDllString(GenieFile->Researchs[Index].LanguageDllName);
	}
	else
	{
		Name = GenieFile->Researchs[Index].Name;
	}
	return Name;
}

void AGE_Frame::ListResearchs()
{
	string Name;
	wxString SearchText = wxString(Research_Research_Search->GetValue()).Lower();
	string CompareText;
	
	short Selection = Research_Research_List->GetSelection();
	short ResearchIDs[9];
	ResearchIDs[0] = Effects_ComboBox_ResearchsD->GetSelection();
	ResearchIDs[1] = Effects_ComboBox_ResearchsA->GetSelection();
	ResearchIDs[2] = Units_ComboBox_ResearchID->GetSelection();
	for(short loop = 0;loop < 6;loop++)
	ResearchIDs[loop+3] = Research_ComboBox_RequiredTechs[loop]->GetSelection();

	if(!Research_Research_List->IsEmpty())
	{
		Research_Research_List->Clear();
	}
	if(!Effects_ComboBox_ResearchsD->IsEmpty())
	{
		Effects_ComboBox_ResearchsD->Clear();
	}
	if(!Effects_ComboBox_ResearchsA->IsEmpty())
	{
		Effects_ComboBox_ResearchsA->Clear();
	}
	if(!Units_ComboBox_ResearchID->IsEmpty())
	{
		Units_ComboBox_ResearchID->Clear();
	}
	for(short loop = 0;loop < 6;loop++)
	{
		if(!Research_ComboBox_RequiredTechs[loop]->IsEmpty())
		{
			Research_ComboBox_RequiredTechs[loop]->Clear();
		}
	}
	
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < 9;loop++)
	{
		if(ResearchIDs[loop] == wxNOT_FOUND)
		{
			ResearchIDs[loop] = 0;
		}
	}
	
	Effects_ComboBox_ResearchsD->Append("-1 - None");
	Effects_ComboBox_ResearchsA->Append("-1 - None");
	Units_ComboBox_ResearchID->Append("-1 - None");
	for(short loop = 0;loop < 6;loop++)
	Research_ComboBox_RequiredTechs[loop]->Append("-1 - None");
	
	for(short loop = 0;loop < GenieFile->Researchs.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetResearchName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetResearchName(loop)).Lower();
		if(SearchText.IsEmpty() || CompareText.find(SearchText) != string::npos)
		{
			Research_Research_List->Append(Name, (void*)&GenieFile->Researchs[loop]);
		}
		Effects_ComboBox_ResearchsD->Append(Name);
		Effects_ComboBox_ResearchsA->Append(Name);
		Units_ComboBox_ResearchID->Append(Name);
		for(short loop = 0;loop < 6;loop++)
		Research_ComboBox_RequiredTechs[loop]->Append(Name);
	}
	
	Research_Research_List->SetFirstItem(Selection - 3);
	Research_Research_List->SetSelection(Selection);
	Effects_ComboBox_ResearchsD->SetSelection(ResearchIDs[0]);
	Effects_ComboBox_ResearchsA->SetSelection(ResearchIDs[1]);
	Units_ComboBox_ResearchID->SetSelection(ResearchIDs[2]);
	for(short loop = 0;loop < 6;loop++)
	Research_ComboBox_RequiredTechs[loop]->SetSelection(ResearchIDs[loop+3]);
	
	wxCommandEvent E;
	OnResearchSelect(E);
}

void AGE_Frame::OnResearchSearch(wxCommandEvent& Event)
{
	short Selection = Research_Research_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		ListResearchs();
	}
}

void AGE_Frame::OnResearchSelect(wxCommandEvent& Event)
{
	short Selection = Research_Research_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Research_Research_List->GetCount() - 1;
			Research_Research_List->SetSelection(Selection);
		}
		gdat::Research * ResearchPointer = (gdat::Research*)Research_Research_List->GetClientData(Selection);
		ResearchID = ResearchPointer - (&GenieFile->Researchs[0]);
		short RequiredTechs;
		for(short loop = 0;loop < 2;loop++)
		{
			if(GameVersion >= 2)
			{
				RequiredTechs = 6;
				Research_RequiredTechs[loop+4]->Show(true);
				Research_ComboBox_RequiredTechs[loop+4]->Show(true);
			}
			else
			{
				RequiredTechs = 4;
				Research_RequiredTechs[loop+4]->Show(false);
				Research_ComboBox_RequiredTechs[loop+4]->Show(false);
			}
		}
		for(short loop = 0;loop < RequiredTechs;loop++)
		{
			Research_RequiredTechs[loop]->ChangeValue(lexical_cast<string>(ResearchPointer->RequiredTechs[loop]));
			Research_RequiredTechs[loop]->Container = &ResearchPointer->RequiredTechs[loop];
			Research_ComboBox_RequiredTechs[loop]->SetSelection(ResearchPointer->RequiredTechs[loop] + 1);
		}
		Research_RequiredTechCount->ChangeValue(lexical_cast<string>(ResearchPointer->RequiredTechCount));
		Research_RequiredTechCount->Container = &ResearchPointer->RequiredTechCount;
		Research_Resources[0]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[0].Type));
		Research_Resources[0]->Container = &ResearchPointer->ResourceCosts[0].Type;
		Research_Resources[1]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[1].Type));
		Research_Resources[1]->Container = &ResearchPointer->ResourceCosts[1].Type;
		Research_Resources[2]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[2].Type));
		Research_Resources[2]->Container = &ResearchPointer->ResourceCosts[2].Type;
		Research_ComboBox_Resources[0]->SetSelection(ResearchPointer->ResourceCosts[0].Type + 1);
		Research_ComboBox_Resources[1]->SetSelection(ResearchPointer->ResourceCosts[1].Type + 1);
		Research_ComboBox_Resources[2]->SetSelection(ResearchPointer->ResourceCosts[2].Type + 1);
		Research_Amount[0]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[0].Amount));
		Research_Amount[0]->Container = &ResearchPointer->ResourceCosts[0].Amount;
		Research_Amount[1]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[1].Amount));
		Research_Amount[1]->Container = &ResearchPointer->ResourceCosts[1].Amount;
		Research_Amount[2]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[2].Amount));
		Research_Amount[2]->Container = &ResearchPointer->ResourceCosts[2].Amount;
		Research_Used[0]->ChangeValue(lexical_cast<string>((short)ResearchPointer->ResourceCosts[0].Used));
		Research_Used[0]->Container = &ResearchPointer->ResourceCosts[0].Used;
		Research_CheckBox_Used[0]->SetValue((bool)ResearchPointer->ResourceCosts[0].Used);
		Research_Used[1]->ChangeValue(lexical_cast<string>((short)ResearchPointer->ResourceCosts[1].Used));
		Research_Used[1]->Container = &ResearchPointer->ResourceCosts[1].Used;
		Research_CheckBox_Used[1]->SetValue((bool)ResearchPointer->ResourceCosts[1].Used);
		Research_Used[2]->ChangeValue(lexical_cast<string>((short)ResearchPointer->ResourceCosts[2].Used));
		Research_Used[2]->Container = &ResearchPointer->ResourceCosts[2].Used;
		Research_CheckBox_Used[2]->SetValue((bool)ResearchPointer->ResourceCosts[2].Used);
		if(GameVersion >= 2)
		{
			Research_Holder_Civ->Show(true);
			Research_Holder_FullTechMode->Show(true);
			
			Research_Civ->ChangeValue(lexical_cast<string>(ResearchPointer->Civ));
			Research_Civ->Container = &ResearchPointer->Civ;
			Research_ComboBox_Civ->SetSelection(ResearchPointer->Civ + 1);
			Research_FullTechMode->ChangeValue(lexical_cast<string>(ResearchPointer->FullTechMode));
			Research_FullTechMode->Container = &ResearchPointer->FullTechMode;
			Research_CheckBox_FullTechMode->SetValue((bool)ResearchPointer->FullTechMode);
		}
		else
		{
			Research_Holder_Civ->Show(false);
			Research_Holder_FullTechMode->Show(false);
		}
		Research_ResearchLocation->ChangeValue(lexical_cast<string>(ResearchPointer->ResearchLocation));
		Research_ResearchLocation->Container = &ResearchPointer->ResearchLocation;
		Research_ComboBox_ResearchLocation->SetSelection(ResearchPointer->ResearchLocation + 1);
		Research_LangDllName->ChangeValue(lexical_cast<string>(ResearchPointer->LanguageDllName));
		Research_LangDllName->Container = &ResearchPointer->LanguageDllName;
		Research_DLL_LangDllName->SetLabel(LanguageDllString(lexical_cast<short>(Research_LangDllName->GetValue())));
		Research_LangDllDescription->ChangeValue(lexical_cast<string>(ResearchPointer->LanguageDllDescription));
		Research_LangDllDescription->Container = &ResearchPointer->LanguageDllDescription;
		Research_DLL_LangDllDescription->SetLabel(LanguageDllString(lexical_cast<short>(Research_LangDllDescription->GetValue())));
		Research_ResearchTime->ChangeValue(lexical_cast<string>(ResearchPointer->ResearchTime));
		Research_ResearchTime->Container = &ResearchPointer->ResearchTime;
		Research_TechID->ChangeValue(lexical_cast<string>(ResearchPointer->TechageID));
		Research_TechID->Container = &ResearchPointer->TechageID;
		Research_ComboBox_TechID->SetSelection(ResearchPointer->TechageID + 1);
		Research_Type->ChangeValue(lexical_cast<string>(ResearchPointer->Type));
		Research_Type->Container = &ResearchPointer->Type;
		Research_IconID->ChangeValue(lexical_cast<string>(ResearchPointer->IconID));
		Research_IconID->Container = &ResearchPointer->IconID;
		Research_ButtonID->ChangeValue(lexical_cast<string>((short)ResearchPointer->ButtonID));
		Research_ButtonID->Container = &ResearchPointer->ButtonID;
		Research_Pointers[0]->ChangeValue(lexical_cast<string>(ResearchPointer->Pointers[0]));
		Research_Pointers[0]->Container = &ResearchPointer->Pointers[0];
		Research_Pointers[1]->ChangeValue(lexical_cast<string>(ResearchPointer->Pointers[1]));
		Research_Pointers[1]->Container = &ResearchPointer->Pointers[1];
		Research_Pointers[1]->ChangeValue(lexical_cast<string>(ResearchPointer->Pointers[2]));
		Research_Pointers[2]->Container = &ResearchPointer->Pointers[2];
		Research_Name[0]->ChangeValue(ResearchPointer->Name);
		Research_Name[0]->Container = &ResearchPointer->Name;
		Research_NameLength[0]->ChangeValue(lexical_cast<string>(ResearchPointer->NameLength));
		Research_NameLength[0]->Container = &ResearchPointer->NameLength;
		if(GameVersion >= 4)
		{
			Research_Holder_Name[1]->Show(true);
			Research_Holder_NameLength[1]->Show(true);
			
			Research_Name[1]->ChangeValue(ResearchPointer->Name2);
			Research_Name[1]->Container = &ResearchPointer->Name2;
			Research_NameLength[1]->ChangeValue(lexical_cast<string>(ResearchPointer->NameLength2));
			Research_NameLength[1]->Container = &ResearchPointer->NameLength2;
		}
		else
		{
			Research_Holder_Name[1]->Show(false);
			Research_Holder_NameLength[1]->Show(false);
		}
		Research_DLL_LangDllName->Wrap(Research_DLL_LangDllName->GetSize().GetWidth());
		Research_DLL_LangDllDescription->Wrap(Research_DLL_LangDllDescription->GetSize().GetWidth());
		Added = false;
	}
}

void AGE_Frame::OnResearchAdd(wxCommandEvent& Event)
{
	gdat::Research Temp;
	GenieFile->Researchs.push_back(Temp);
	Added = true;
	ListResearchs();
}

void AGE_Frame::OnResearchDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Research_Research_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->Researchs.erase(GenieFile->Researchs.begin() + ResearchID);
		if(Selection == Research_Research_List->GetCount() - 1)
		Research_Research_List->SetSelection(Selection - 1);
		ListResearchs();
	}
}

void AGE_Frame::OnResearchCopy(wxCommandEvent& Event)
{
	short Selection = Research_Research_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		ResearchCopy = *(gdat::Research*)Research_Research_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnResearchPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Research_Research_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::Research*)Research_Research_List->GetClientData(Selection) = ResearchCopy;
		ListResearchs();
	}
}

void AGE_Frame::CreateResearchControls()
{
	Tab_Research = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(-1, 350));
	
	Research_Main = new wxBoxSizer(wxHORIZONTAL);
	Research_ListArea = new wxBoxSizer(wxVERTICAL);
	Research_Research = new wxStaticBoxSizer(wxVERTICAL, Tab_Research, "Research Slot");
	Research_Research_Search = new wxTextCtrl(Tab_Research, wxID_ANY);
	Research_Research_List = new wxListBox(Tab_Research, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	Research_Research_Buttons = new wxGridSizer(2, 0, 0);
	Research_Add = new wxButton(Tab_Research, wxID_ANY, "Add", wxDefaultPosition, wxSize(-1, 20));
	Research_Delete = new wxButton(Tab_Research, wxID_ANY, "Delete", wxDefaultPosition, wxSize(-1, 20));
	Research_Copy = new wxButton(Tab_Research, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Research_Paste = new wxButton(Tab_Research, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));
	
	Research_DataArea = new wxBoxSizer(wxVERTICAL);
	Research_Scroller = new AGE_ScrolledWindow(Tab_Research, wxVSCROLL | wxTAB_TRAVERSAL);
	Research_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	Research_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	Research_Holder_RequiredTechArea = new wxBoxSizer(wxVERTICAL);
	Research_Holder_RequiredTechs = new wxGridSizer(6, 0, 5);
	Research_Text_RequiredTechArea = new wxStaticText(Research_Scroller, wxID_ANY, " Required Researches", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Holder_MiscArea1 = new wxBoxSizer(wxHORIZONTAL);
	Research_Holder_LangDLLArea = new wxBoxSizer(wxHORIZONTAL);
	Research_Holder_Misc2 = new wxBoxSizer(wxHORIZONTAL);
	Research_Holder_PointerArea = new wxBoxSizer(wxHORIZONTAL);
	Research_Holder_Names = new wxBoxSizer(wxHORIZONTAL);

	for(short loop = 0;loop < 6;loop++){
	Research_RequiredTechs[loop] = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_ComboBox_RequiredTechs[loop] = new ComboBox_Short(Research_Scroller, Research_RequiredTechs[0]);}
	Research_Holder_RequiredTechCount = new wxBoxSizer(wxVERTICAL);
	Research_Text_RequiredTechCount = new wxStaticText(Research_Scroller, wxID_ANY, " Min. Req. Researches", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_RequiredTechCount = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Holder_Civ = new wxBoxSizer(wxVERTICAL);
	Research_Text_Civ = new wxStaticText(Research_Scroller, wxID_ANY, " Civilization", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Civ = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_ComboBox_Civ = new ComboBox_Short(Research_Scroller, Research_Civ);
	Research_Holder_FullTechMode = new wxBoxSizer(wxVERTICAL);
	Research_Text_FullTechMode = new wxStaticText(Research_Scroller, wxID_ANY, " Full Tech Mode", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_FullTechMode = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_CheckBox_FullTechMode = new CheckBox_Short(Research_Scroller, "Available", Research_FullTechMode);
	Research_Holder_ResearchLocation = new wxBoxSizer(wxVERTICAL);
	Research_Text_ResearchLocation = new wxStaticText(Research_Scroller, wxID_ANY, " Research Location", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_ResearchLocation = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_ComboBox_ResearchLocation = new ComboBox_Short(Research_Scroller, Research_ResearchLocation);
	
	Research_Holder_CostHeader = new wxStaticBoxSizer(wxVERTICAL, Research_Scroller, "Cost Slot");
	Research_Holder_CostType = new wxBoxSizer(wxHORIZONTAL);
	Research_Holder_CostAmount = new wxBoxSizer(wxHORIZONTAL);
	Research_Holder_CostUsed = new wxBoxSizer(wxHORIZONTAL);
	Research_Text_Resources = new wxStaticText(Research_Scroller, wxID_ANY, "Cost Type ", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Research_ResourceGrid = new wxGridSizer(3, 0, 5);
	Research_Resources[0] = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Resources[1] = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Resources[2] = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_ComboBox_Resources[0] = new ComboBox_Short(Research_Scroller, Research_Resources[0]);
	Research_ComboBox_Resources[1] = new ComboBox_Short(Research_Scroller, Research_Resources[1]);
	Research_ComboBox_Resources[2] = new ComboBox_Short(Research_Scroller, Research_Resources[2]);
	Research_Text_Amount = new wxStaticText(Research_Scroller, wxID_ANY, "Cost Amount ", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Research_Amount[0] = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Amount[1] = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Amount[2] = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Text_Used = new wxStaticText(Research_Scroller, wxID_ANY, "Cost Used ", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Research_Used[0] = new TextCtrl_Byte(Research_Scroller, "0", NULL);
	Research_Used[1] = new TextCtrl_Byte(Research_Scroller, "0", NULL);
	Research_Used[2] = new TextCtrl_Byte(Research_Scroller, "0", NULL);
	Research_CheckBox_Used[0] = new CheckBox_Byte(Research_Scroller, "Used", Research_Used[0]);
	Research_CheckBox_Used[1] = new CheckBox_Byte(Research_Scroller, "Used", Research_Used[1]);
	Research_CheckBox_Used[2] = new CheckBox_Byte(Research_Scroller, "Used", Research_Used[2]);
	
	Research_Holder_LangDllName = new wxBoxSizer(wxVERTICAL);
	Research_Text_LangDllName = new wxStaticText(Research_Scroller, wxID_ANY, " Language Dll Name", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_LangDllName = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_DLL_LangDllName = new wxStaticText(Research_Scroller, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE | wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);
	Research_Holder_LangDllDescription = new wxBoxSizer(wxVERTICAL);
	Research_Text_LangDllDescription = new wxStaticText(Research_Scroller, wxID_ANY, " Language Dll Description", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_LangDllDescription = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_DLL_LangDllDescription = new wxStaticText(Research_Scroller, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE | wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);
	Research_Holder_ResearchTime = new wxBoxSizer(wxVERTICAL);
	Research_Text_ResearchTime = new wxStaticText(Research_Scroller, wxID_ANY, " Research Time", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_ResearchTime = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Holder_TechID = new wxBoxSizer(wxVERTICAL);
	Research_Text_TechID = new wxStaticText(Research_Scroller, wxID_ANY, " Technology", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_TechID = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_ComboBox_TechID = new ComboBox_Short(Research_Scroller, Research_TechID);
	Research_Holder_Type = new wxBoxSizer(wxVERTICAL);
	Research_Text_Type = new wxStaticText(Research_Scroller, wxID_ANY, " Type", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Type = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Holder_IconID = new wxBoxSizer(wxVERTICAL);
	Research_Text_IconID = new wxStaticText(Research_Scroller, wxID_ANY, " Icon", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_IconID = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Holder_ButtonID = new wxBoxSizer(wxVERTICAL);
	Research_Text_ButtonID = new wxStaticText(Research_Scroller, wxID_ANY, " Button", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_ButtonID = new TextCtrl_Byte(Research_Scroller, "0", NULL);
	Research_Holder_Pointers[0] = new wxBoxSizer(wxVERTICAL);
	Research_Holder_Pointers[1] = new wxBoxSizer(wxVERTICAL);
	Research_Holder_Pointers[2] = new wxBoxSizer(wxVERTICAL);
	Research_Text_Pointers[0] = new wxStaticText(Research_Scroller, wxID_ANY, " Pointer 1", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Text_Pointers[1] = new wxStaticText(Research_Scroller, wxID_ANY, " Pointer 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Text_Pointers[2] = new wxStaticText(Research_Scroller, wxID_ANY, " Pointer 3", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Pointers[0] = new TextCtrl_Long(Research_Scroller, "0", NULL);
	Research_Pointers[1] = new TextCtrl_Long(Research_Scroller, "0", NULL);
	Research_Pointers[2] = new TextCtrl_Long(Research_Scroller, "0", NULL);
	Research_Holder_Name[0] = new wxBoxSizer(wxVERTICAL);
	Research_Holder_Name[1] = new wxBoxSizer(wxVERTICAL);
	Research_Text_Name[0] = new wxStaticText(Research_Scroller, wxID_ANY, " Name ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Text_Name[1] = new wxStaticText(Research_Scroller, wxID_ANY, " Name 2 ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Name[0] = new TextCtrl_String(Research_Scroller, "0", NULL);
	Research_Name[1] = new TextCtrl_String(Research_Scroller, "0", NULL);
	Research_Holder_NameLength[0] = new wxBoxSizer(wxVERTICAL);
	Research_Holder_NameLength[1] = new wxBoxSizer(wxVERTICAL);
	Research_Text_NameLength[0] = new wxStaticText(Research_Scroller, wxID_ANY, " Name Length ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Text_NameLength[1] = new wxStaticText(Research_Scroller, wxID_ANY, " Name Length 2 ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_NameLength[0] = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_NameLength[1] = new TextCtrl_Short(Research_Scroller, "0", NULL);

	Research_Research_Buttons->Add(Research_Add, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_Delete, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_Copy, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_Paste, 1, wxEXPAND);

	Research_Research->Add(Research_Research_Search, 0, wxEXPAND);
	Research_Research->Add(-1, 2);
	Research_Research->Add(Research_Research_List, 1, wxEXPAND);
	Research_Research->Add(-1, 2);
	Research_Research->Add(Research_Research_Buttons, 0, wxEXPAND);

	Research_ListArea->Add(-1, 10);
	Research_ListArea->Add(Research_Research, 1, wxEXPAND);
	Research_ListArea->Add(-1, 10);

	Research_Holder_Name[0]->Add(Research_Text_Name[0], 0, wxEXPAND);
	Research_Holder_Name[0]->Add(-1, 2);
	Research_Holder_Name[0]->Add(Research_Name[0], 1, wxEXPAND);
	Research_Holder_Name[1]->Add(Research_Text_Name[1], 0, wxEXPAND);
	Research_Holder_Name[1]->Add(-1, 2);
	Research_Holder_Name[1]->Add(Research_Name[1], 1, wxEXPAND);

	Research_Holder_NameLength[0]->Add(Research_Text_NameLength[0], 0, wxEXPAND);
	Research_Holder_NameLength[0]->Add(-1, 2);
	Research_Holder_NameLength[0]->Add(Research_NameLength[0], 1, wxEXPAND);
	Research_Holder_NameLength[1]->Add(Research_Text_NameLength[1], 0, wxEXPAND);
	Research_Holder_NameLength[1]->Add(-1, 2);
	Research_Holder_NameLength[1]->Add(Research_NameLength[1], 1, wxEXPAND);

	Research_Holder_Names->Add(Research_Holder_NameLength[0], 1, wxEXPAND);
	Research_Holder_Names->Add(5, -1);
	Research_Holder_Names->Add(Research_Holder_Name[0], 2, wxEXPAND);
	Research_Holder_Names->Add(5, -1);
	Research_Holder_Names->Add(Research_Holder_NameLength[1], 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Research_Holder_Names->Add(5, -1);
	Research_Holder_Names->Add(Research_Holder_Name[1], 2, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Research_Holder_LangDllName->Add(Research_Text_LangDllName, 0, wxEXPAND);
	Research_Holder_LangDllName->Add(-1, 2);
	Research_Holder_LangDllName->Add(Research_LangDllName, 1, wxEXPAND);
	Research_Holder_LangDllName->Add(Research_DLL_LangDllName, 2, wxEXPAND);
	Research_Holder_LangDllDescription->Add(Research_Text_LangDllDescription, 0, wxEXPAND);
	Research_Holder_LangDllDescription->Add(-1, 2);
	Research_Holder_LangDllDescription->Add(Research_LangDllDescription, 1, wxEXPAND);
	Research_Holder_LangDllDescription->Add(Research_DLL_LangDllDescription, 2, wxEXPAND);

	Research_Holder_LangDLLArea->Add(Research_Holder_LangDllName, 1, wxEXPAND);
	Research_Holder_LangDLLArea->Add(5, -1);
	Research_Holder_LangDLLArea->Add(Research_Holder_LangDllDescription, 1, wxEXPAND);
	
	Research_ResourceGrid->Add(Research_Resources[0], 1, wxEXPAND);
	Research_ResourceGrid->Add(Research_Resources[1], 1, wxEXPAND);
	Research_ResourceGrid->Add(Research_Resources[2], 1, wxEXPAND);
	Research_ResourceGrid->Add(Research_ComboBox_Resources[0], 1, wxEXPAND);
	Research_ResourceGrid->Add(Research_ComboBox_Resources[1], 1, wxEXPAND);
	Research_ResourceGrid->Add(Research_ComboBox_Resources[2], 1, wxEXPAND);

	Research_Holder_CostType->Add(Research_Text_Resources, 1, wxEXPAND);
	Research_Holder_CostType->Add(Research_ResourceGrid, 6, wxEXPAND);
	
	Research_Holder_CostAmount->Add(Research_Text_Amount, 2, wxEXPAND);
	Research_Holder_CostAmount->Add(Research_Amount[0], 4, wxEXPAND);
	Research_Holder_CostAmount->Add(5, -1);
	Research_Holder_CostAmount->Add(Research_Amount[1], 4, wxEXPAND);
	Research_Holder_CostAmount->Add(5, -1);
	Research_Holder_CostAmount->Add(Research_Amount[2], 4, wxEXPAND);
	
	Research_Holder_CostUsed->Add(Research_Text_Used, 2, wxEXPAND);
	Research_Holder_CostUsed->Add(Research_Used[0], 3, wxEXPAND);
	Research_Holder_CostUsed->Add(2, -1);
	Research_Holder_CostUsed->Add(Research_CheckBox_Used[0], 1, wxEXPAND);
	Research_Holder_CostUsed->Add(5, -1);
	Research_Holder_CostUsed->Add(Research_Used[1], 3, wxEXPAND);
	Research_Holder_CostUsed->Add(2, -1);
	Research_Holder_CostUsed->Add(Research_CheckBox_Used[1], 1, wxEXPAND);
	Research_Holder_CostUsed->Add(5, -1);
	Research_Holder_CostUsed->Add(Research_Used[2], 3, wxEXPAND);
	Research_Holder_CostUsed->Add(2, -1);
	Research_Holder_CostUsed->Add(Research_CheckBox_Used[2], 1, wxEXPAND);

	Research_Holder_CostHeader->Add(Research_Holder_CostType, 0, wxEXPAND);
	Research_Holder_CostHeader->Add(-1, 5);
	Research_Holder_CostHeader->Add(Research_Holder_CostAmount, 0, wxEXPAND);
	Research_Holder_CostHeader->Add(-1, 5);
	Research_Holder_CostHeader->Add(Research_Holder_CostUsed, 0, wxEXPAND);

	for(short loop = 0;loop < 6;loop++)
	Research_Holder_RequiredTechs->Add(Research_RequiredTechs[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 6;loop++)
	Research_Holder_RequiredTechs->Add(Research_ComboBox_RequiredTechs[loop], 1, wxEXPAND);
	
	Research_Holder_RequiredTechArea->Add(Research_Text_RequiredTechArea, 0, wxEXPAND);
	Research_Holder_RequiredTechArea->Add(-1, 2);
	Research_Holder_RequiredTechArea->Add(Research_Holder_RequiredTechs, 1, wxEXPAND);

	Research_Holder_RequiredTechCount->Add(Research_Text_RequiredTechCount, 0, wxEXPAND);
	Research_Holder_RequiredTechCount->Add(-1, 2);
	Research_Holder_RequiredTechCount->Add(Research_RequiredTechCount, 1, wxEXPAND);
	
	Research_Holder_Civ->Add(Research_Text_Civ, 0, wxEXPAND);
	Research_Holder_Civ->Add(-1, 2);
	Research_Holder_Civ->Add(Research_Civ, 1, wxEXPAND);
	Research_Holder_Civ->Add(Research_ComboBox_Civ, 1, wxEXPAND);
	
	Research_Holder_FullTechMode->Add(Research_Text_FullTechMode, 0, wxEXPAND);
	Research_Holder_FullTechMode->Add(-1, 2);
	Research_Holder_FullTechMode->Add(Research_FullTechMode, 1, wxEXPAND);
	Research_Holder_FullTechMode->Add(Research_CheckBox_FullTechMode, 1, wxEXPAND);
	
	Research_Holder_ResearchLocation->Add(Research_Text_ResearchLocation, 0, wxEXPAND);
	Research_Holder_ResearchLocation->Add(-1, 2);
	Research_Holder_ResearchLocation->Add(Research_ResearchLocation, 1, wxEXPAND);
	Research_Holder_ResearchLocation->Add(Research_ComboBox_ResearchLocation, 1, wxEXPAND);

	Research_Holder_MiscArea1->Add(Research_Holder_TechID, 1, wxEXPAND);
	Research_Holder_MiscArea1->Add(5, -1);
	Research_Holder_MiscArea1->Add(Research_Holder_FullTechMode, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Research_Holder_MiscArea1->Add(5, -1);
	Research_Holder_MiscArea1->Add(Research_Holder_Civ, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Research_Holder_MiscArea1->Add(5, -1);
	Research_Holder_MiscArea1->Add(Research_Holder_ResearchLocation, 1, wxEXPAND);

	Research_Holder_ResearchTime->Add(Research_Text_ResearchTime, 0, wxEXPAND);
	Research_Holder_ResearchTime->Add(-1, 2);
	Research_Holder_ResearchTime->Add(Research_ResearchTime, 1, wxEXPAND);
	
	Research_Holder_TechID->Add(Research_Text_TechID, 0, wxEXPAND);
	Research_Holder_TechID->Add(-1, 2);
	Research_Holder_TechID->Add(Research_TechID, 1, wxEXPAND);
	Research_Holder_TechID->Add(Research_ComboBox_TechID, 1, wxEXPAND);
	
	Research_Holder_Type->Add(Research_Text_Type, 0, wxEXPAND);
	Research_Holder_Type->Add(-1, 2);
	Research_Holder_Type->Add(Research_Type, 1, wxEXPAND);
	
	Research_Holder_IconID->Add(Research_Text_IconID, 0, wxEXPAND);
	Research_Holder_IconID->Add(-1, 2);
	Research_Holder_IconID->Add(Research_IconID, 1, wxEXPAND);
	
	Research_Holder_ButtonID->Add(Research_Text_ButtonID, 0, wxEXPAND);
	Research_Holder_ButtonID->Add(-1, 2);
	Research_Holder_ButtonID->Add(Research_ButtonID, 1, wxEXPAND);

	Research_Holder_Misc2->Add(Research_Holder_RequiredTechCount, 1, wxEXPAND);
	Research_Holder_Misc2->Add(5, -1);
	Research_Holder_Misc2->Add(Research_Holder_Type, 1, wxEXPAND);
	Research_Holder_Misc2->Add(5, -1);
	Research_Holder_Misc2->Add(Research_Holder_ResearchTime, 1, wxEXPAND);
	Research_Holder_Misc2->Add(5, -1);
	Research_Holder_Misc2->Add(Research_Holder_IconID, 1, wxEXPAND);
	Research_Holder_Misc2->Add(5, -1);
	Research_Holder_Misc2->Add(Research_Holder_ButtonID, 1, wxEXPAND);

	Research_Holder_Pointers[0]->Add(Research_Text_Pointers[0], 0, wxEXPAND);
	Research_Holder_Pointers[0]->Add(-1, 2);
	Research_Holder_Pointers[0]->Add(Research_Pointers[0], 1, wxEXPAND);
	Research_Holder_Pointers[1]->Add(Research_Text_Pointers[1], 0, wxEXPAND);
	Research_Holder_Pointers[1]->Add(-1, 2);
	Research_Holder_Pointers[1]->Add(Research_Pointers[1], 1, wxEXPAND);
	Research_Holder_Pointers[2]->Add(Research_Text_Pointers[2], 0, wxEXPAND);
	Research_Holder_Pointers[2]->Add(-1, 2);
	Research_Holder_Pointers[2]->Add(Research_Pointers[2], 1, wxEXPAND);

	Research_Holder_PointerArea->Add(Research_Holder_Pointers[0], 1, wxEXPAND);
	Research_Holder_PointerArea->Add(5, -1);
	Research_Holder_PointerArea->Add(Research_Holder_Pointers[1], 1, wxEXPAND);
	Research_Holder_PointerArea->Add(5, -1);
	Research_Holder_PointerArea->Add(Research_Holder_Pointers[2], 1, wxEXPAND);

	Research_ScrollerWindowsSpace->Add(Research_Holder_Names, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Holder_LangDLLArea, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Holder_RequiredTechArea, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Holder_MiscArea1, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Holder_Misc2, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Holder_CostHeader, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Holder_PointerArea, 0, wxEXPAND);
	
	Research_ScrollerWindows->Add(Research_ScrollerWindowsSpace, 1, wxEXPAND);
	Research_ScrollerWindows->Add(5, -1);

	Research_Scroller->SetSizer(Research_ScrollerWindows);
	Research_Scroller->SetScrollRate(0, 15);

	Research_DataArea->Add(-1, 10);
	Research_DataArea->Add(Research_Scroller, 1, wxEXPAND);
	Research_DataArea->Add(-1, 10);

	Research_Main->Add(10, -1);
	Research_Main->Add(Research_ListArea, 1, wxEXPAND);
	Research_Main->Add(10, -1);
	Research_Main->Add(Research_DataArea, 3, wxEXPAND);
	Research_Main->Add(10, -1);
	
	Research_NameLength[0]->Enable(false);
	Research_NameLength[1]->Enable(false);

	Tab_Research->SetSizer(Research_Main);

	Connect(Research_Research_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResearchSearch));
	Connect(Research_Research_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnResearchSelect));
	Connect(Research_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchAdd));
	Connect(Research_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchDelete));
	Connect(Research_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchCopy));
	Connect(Research_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchPaste));
	
	Research_LangDllName->Connect(Research_LangDllName->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	Research_LangDllDescription->Connect(Research_LangDllDescription->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	Research_Name[0]->Connect(Research_Name[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Research_Name[1]->Connect(Research_Name[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);

}
