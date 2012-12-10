#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetUnitLineName(short &Index)
{
	if(GenieFile->UnitLines[Index].Name != "")
		return GenieFile->UnitLines[Index].Name;
	return "Unitline "+lexical_cast<string>(Index);
}

void AGE_Frame::OnUnitLinesSearch(wxCommandEvent &Event)
{
	ListUnitLines();
}

void AGE_Frame::ListUnitLines()
{
	wxString Name;
	searchText = UnitLines_UnitLines_Search->GetValue().Lower();
	excludeText = UnitLines_UnitLines_Search_R->GetValue().Lower();

	auto Selections = UnitLines_UnitLines_List->GetSelections(Items);
	short UnitIDs = Units_ComboBox_Unitline->GetSelection();

	if(UnitLines_UnitLines_List->GetCount() > 0)
	{
		UnitLines_UnitLines_List->Clear();
	}
	if(Units_ComboBox_Unitline->GetCount() > 0)
	{
		Units_ComboBox_Unitline->Clear();
	}

	if(UnitIDs == wxNOT_FOUND)
	{
		UnitIDs = 0;
	}

	Units_ComboBox_Unitline->Append("-1 - None");

	for(short loop=0; loop < GenieFile->UnitLines.size(); loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineName(loop);
		if(SearchMatches(Name.Lower()))
		{
			UnitLines_UnitLines_List->Append(Name, (void*)&GenieFile->UnitLines[loop]);
		}
		Units_ComboBox_Unitline->Append(Name);
	}

	ListingFix(Selections, UnitLines_UnitLines_List);
	Units_ComboBox_Unitline->SetSelection(UnitIDs);

	wxCommandEvent E;
	OnUnitLinesSelect(E);
}

void AGE_Frame::OnUnitLinesSelect(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(Selections != 0)
	{
		UnitLineIDs.resize(Selections);
		genie::UnitLine * LinePointer;
		for(short loop = Selections; loop--> 0;)
		{
			LinePointer = (genie::UnitLine*)UnitLines_UnitLines_List->GetClientData(Items.Item(loop));
			UnitLineIDs[loop] = (LinePointer - (&GenieFile->UnitLines[0]));
		}
		UnitLines_ID->ChangeValue(lexical_cast<string>(LinePointer->ID));
		UnitLines_ID->container[0] = &LinePointer->ID;
		UnitLines_Name->ChangeValue(LinePointer->Name);
		UnitLines_Name->container[0] = &LinePointer->Name;
		ListUnitLineUnits();
	}
}

void AGE_Frame::OnUnitLinesAdd(wxCommandEvent &Event)
{
	if(GenieFile != NULL)
	{
		wxBusyCursor WaitCursor;
		genie::UnitLine Temp;
		Temp.setGameVersion(GenieVersion);
		GenieFile->UnitLines.push_back(Temp);
		if(EnableIDFix)
		GenieFile->UnitLines[GenieFile->UnitLines.size()-1].ID = (int16_t)(GenieFile->UnitLines.size()-1); // ID Fix
		Added = true;
		ListUnitLines();
	}
}

void AGE_Frame::OnUnitLinesInsert(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::UnitLine Temp;
		Temp.setGameVersion(GenieVersion);
		GenieFile->UnitLines.insert(GenieFile->UnitLines.begin() + UnitLineIDs[0], Temp);
		if(EnableIDFix)
		for(short loop = UnitLineIDs[0];loop < GenieFile->UnitLines.size(); loop++) // ID Fix
		GenieFile->UnitLines[loop].ID = (int16_t)loop;
		ListUnitLines();
	}
}

void AGE_Frame::OnUnitLinesDelete(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop = Selections; loop--> 0;)
		GenieFile->UnitLines.erase(GenieFile->UnitLines.begin() + UnitLineIDs[loop]);
		if(EnableIDFix)
		for(short loop = UnitLineIDs[0];loop < GenieFile->UnitLines.size(); loop++) // ID Fix
		GenieFile->UnitLines[loop].ID = (int16_t)loop;
		ListUnitLines();
	}
}

void AGE_Frame::OnUnitLinesCopy(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		copies->UnitLine.resize(Selections);
		for(short loop=0; loop < Selections; loop++)
		copies->UnitLine[loop] = GenieFile->UnitLines[UnitLineIDs[loop]];
	}
}

void AGE_Frame::OnUnitLinesPaste(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		if(copies->UnitLine.size()+UnitLineIDs[0] > GenieFile->UnitLines.size())
		GenieFile->UnitLines.resize(copies->UnitLine.size()+UnitLineIDs[0]);
		for(short loop=0; loop < copies->UnitLine.size(); loop++)
		{
			copies->UnitLine[loop].setGameVersion(GenieVersion);
			GenieFile->UnitLines[UnitLineIDs[0]+loop] = copies->UnitLine[loop];
			if(EnableIDFix)
			GenieFile->UnitLines[UnitLineIDs[0]+loop].ID = (int16_t)(UnitLineIDs[0]+loop); // ID Fix
		}
		ListUnitLines();
	}
}

void AGE_Frame::OnUnitLinesPasteInsert(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::UnitLine Temp;
		GenieFile->UnitLines.insert(GenieFile->UnitLines.begin() + UnitLineIDs[0], copies->UnitLine.size(), Temp);
		for(short loop=0; loop < copies->UnitLine.size(); loop++)
		{
			copies->UnitLine[loop].setGameVersion(GenieVersion);
			GenieFile->UnitLines[UnitLineIDs[0]+loop] = copies->UnitLine[loop];
		}
		if(EnableIDFix)
		for(short loop = UnitLineIDs[0];loop < GenieFile->UnitLines.size(); loop++) // ID Fix
		GenieFile->UnitLines[loop].ID = (int16_t)loop;
		ListUnitLines();
	}
}

string AGE_Frame::GetUnitLineUnitName(short &Index)
{
	string Name = lexical_cast<string>(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[Index])+" ";
	if(LangDLLstring(GenieFile->Civs[0].Units[GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[Index]].LanguageDLLName, 2) != "")
	{
		Name += LangDLLstring(GenieFile->Civs[0].Units[GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[Index]].LanguageDLLName, 64);
	}
	else if(GenieFile->Civs[0].Units[GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[Index]].Name != "")
	{
		Name += GenieFile->Civs[0].Units[GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[Index]].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnUnitLineUnitsSearch(wxCommandEvent &Event)
{
	ListUnitLineUnits();
}

void AGE_Frame::ListUnitLineUnits()
{
	wxString Name;
	searchText = UnitLines_UnitLineUnits_Search->GetValue().Lower();
	excludeText = UnitLines_UnitLineUnits_Search_R->GetValue().Lower();

	auto Selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(UnitLines_UnitLineUnits_List->GetCount() > 0) UnitLines_UnitLineUnits_List->Clear();

	for(short loop=0; loop < GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.size(); loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineUnitName(loop);
		if(SearchMatches(Name.Lower()))
		{
			UnitLines_UnitLineUnits_List->Append(Name, (void*)&GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[loop]);
		}
	}
	ListingFix(Selections, UnitLines_UnitLineUnits_List);

	wxCommandEvent E;
	OnUnitLineUnitsSelect(E);
}

void AGE_Frame::OnUnitLineUnitsSelect(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(Selections != 0)
	{
		UnitLineUnitIDs.resize(Selections);
		int16_t * UnitPointer;
		for(short loop = Selections; loop--> 0;)
		{
			UnitPointer = (int16_t*)UnitLines_UnitLineUnits_List->GetClientData(Items.Item(loop));
			UnitLineUnitIDs[loop] = (UnitPointer - (&GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[0]));
		}
		UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*UnitPointer));
		UnitLineUnits_Units->container[0] = UnitPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*UnitPointer + 1);
	}
	else
	{
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	}
}

void AGE_Frame::OnUnitLineUnitsAdd(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.push_back(0);
		Added = true;
		ListUnitLineUnits();
	}
}

void AGE_Frame::OnUnitLineUnitsInsert(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.insert(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.begin() + UnitLineUnitIDs[0], 0);
		ListUnitLineUnits();
	}
}

void AGE_Frame::OnUnitLineUnitsDelete(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop = Selections; loop--> 0;)
		GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.erase(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.begin() + UnitLineUnitIDs[loop]);
		ListUnitLineUnits();
	}
}

void AGE_Frame::OnUnitLineUnitsCopy(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		copies->UnitLineUnit.resize(Selections);
		for(short loop=0; loop < Selections; loop++)
		copies->UnitLineUnit[loop] = GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[UnitLineUnitIDs[loop]];
	}
}

void AGE_Frame::OnUnitLineUnitsPaste(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		if(copies->UnitLineUnit.size()+UnitLineUnitIDs[0] > GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.size())
		GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.resize(copies->UnitLineUnit.size()+UnitLineUnitIDs[0]);
		for(short loop=0; loop < copies->UnitLineUnit.size(); loop++)
		GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[UnitLineUnitIDs[0]+loop] = copies->UnitLineUnit[loop];
		ListUnitLineUnits();
	}
}

void AGE_Frame::OnUnitLineUnitsPasteInsert(wxCommandEvent &Event)
{
	auto Selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.insert(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.begin() + UnitLineUnitIDs[0], copies->UnitLineUnit.size(), 0);
		for(short loop=0; loop < copies->UnitLineUnit.size(); loop++)
		GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[UnitLineUnitIDs[0]+loop] = copies->UnitLineUnit[loop];
		ListUnitLineUnits();
	}
}

void AGE_Frame::CreateUnitLineControls()
{
	Tab_UnitLine = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	UnitLines_Main = new wxBoxSizer(wxHORIZONTAL);
	UnitLines_ListArea = new wxBoxSizer(wxVERTICAL);
	UnitLines_UnitLines_Buttons = new wxGridSizer(3, 0, 0);
	UnitLineUnits_ListArea = new wxBoxSizer(wxVERTICAL);
	UnitLines_UnitLineUnits_Buttons = new wxGridSizer(3, 0, 0);
	UnitLines_DataArea = new wxBoxSizer(wxVERTICAL);

	UnitLines_UnitLines = new wxStaticBoxSizer(wxVERTICAL, Tab_UnitLine, "Unitlines");
	UnitLines_UnitLines_Search = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLines_Search_R = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLines_List = new wxListBox(Tab_UnitLine, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	UnitLines_Add = new wxButton(Tab_UnitLine, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Insert = new wxButton(Tab_UnitLine, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Delete = new wxButton(Tab_UnitLine, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Copy = new wxButton(Tab_UnitLine, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Paste = new wxButton(Tab_UnitLine, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnitLines_PasteInsert = new wxButton(Tab_UnitLine, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	UnitLines_UnitLineUnits = new wxStaticBoxSizer(wxVERTICAL, Tab_UnitLine, "Units");
	UnitLines_UnitLineUnits_Search = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLineUnits_Search_R = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLineUnits_List = new wxListBox(Tab_UnitLine, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	UnitLineUnits_Add = new wxButton(Tab_UnitLine, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Insert = new wxButton(Tab_UnitLine, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Delete = new wxButton(Tab_UnitLine, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Copy = new wxButton(Tab_UnitLine, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Paste = new wxButton(Tab_UnitLine, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_PasteInsert= new wxButton(Tab_UnitLine, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	UnitLines_Holder_ID = new wxBoxSizer(wxVERTICAL);
	UnitLines_Text_ID = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unitline ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLines_ID = new TextCtrl_Short(Tab_UnitLine);
	UnitLines_Holder_Name = new wxBoxSizer(wxVERTICAL);
	UnitLines_Text_Name = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unitline Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLines_Name = new TextCtrl_String(Tab_UnitLine, 30);

	UnitLineUnits_Holder_Units = new wxBoxSizer(wxVERTICAL);
	UnitLineUnits_Text_Units = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLineUnits_Units = new TextCtrl_Short(Tab_UnitLine);
	UnitLineUnits_ComboBox_Units = new ComboBox_Short(Tab_UnitLine, UnitLineUnits_Units);

	UnitLines_UnitLines_Buttons->Add(UnitLines_Add, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Insert, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Delete, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Copy, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Paste, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_PasteInsert, 1, wxEXPAND);

	UnitLines_UnitLines->Add(UnitLines_UnitLines_Search, 0, wxEXPAND);
	UnitLines_UnitLines->Add(UnitLines_UnitLines_Search_R, 0, wxEXPAND);
	UnitLines_UnitLines->Add(-1, 2);
	UnitLines_UnitLines->Add(UnitLines_UnitLines_List, 1, wxEXPAND);
	UnitLines_UnitLines->Add(-1, 2);
	UnitLines_UnitLines->Add(UnitLines_UnitLines_Buttons, 0, wxEXPAND);

	UnitLines_ListArea->Add(-1, 10);
	UnitLines_ListArea->Add(UnitLines_UnitLines, 1, wxEXPAND);
	UnitLines_ListArea->Add(-1, 10);

	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Add, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Insert, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Delete, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Copy, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Paste, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_PasteInsert, 1, wxEXPAND);

	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Search, 0, wxEXPAND);
	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Search_R, 0, wxEXPAND);
	UnitLines_UnitLineUnits->Add(-1, 2);
	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_List, 1, wxEXPAND);
	UnitLines_UnitLineUnits->Add(-1, 2);
	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Buttons, 0, wxEXPAND);

	UnitLineUnits_ListArea->Add(-1, 10);
	UnitLineUnits_ListArea->Add(UnitLines_UnitLineUnits, 1, wxEXPAND);
	UnitLineUnits_ListArea->Add(-1, 10);

	UnitLines_Holder_ID->Add(UnitLines_Text_ID, 0, wxEXPAND);
	UnitLines_Holder_ID->Add(UnitLines_ID, 1, wxEXPAND);
	UnitLines_Holder_Name->Add(UnitLines_Text_Name, 0, wxEXPAND);
	UnitLines_Holder_Name->Add(UnitLines_Name, 1, wxEXPAND);
	UnitLineUnits_Holder_Units->Add(UnitLineUnits_Text_Units, 0, wxEXPAND);
	UnitLineUnits_Holder_Units->Add(UnitLineUnits_Units, 1, wxEXPAND);
	UnitLineUnits_Holder_Units->Add(UnitLineUnits_ComboBox_Units, 1, wxEXPAND);

	UnitLines_DataArea->Add(-1, 10);
	UnitLines_DataArea->Add(UnitLines_Holder_ID, 0, wxEXPAND);
	UnitLines_DataArea->Add(-1, 5);
	UnitLines_DataArea->Add(UnitLines_Holder_Name, 0, wxEXPAND);
	UnitLines_DataArea->Add(-1, 5);
	UnitLines_DataArea->Add(UnitLineUnits_Holder_Units, 0, wxEXPAND);

	UnitLines_Main->Add(10, -1);
	UnitLines_Main->Add(UnitLines_ListArea, 1, wxEXPAND);
	UnitLines_Main->Add(10, -1);
	UnitLines_Main->Add(UnitLineUnits_ListArea, 1, wxEXPAND);
	UnitLines_Main->Add(10, -1);
	UnitLines_Main->Add(UnitLines_DataArea, 1, wxEXPAND);
	UnitLines_Main->AddStretchSpacer(1);

	if(EnableIDFix)
	UnitLines_ID->Enable(false);

	Tab_UnitLine->SetSizer(UnitLines_Main);

	Connect(UnitLines_UnitLines_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitLinesSelect));
	Connect(UnitLines_UnitLines_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLinesSearch));
	Connect(UnitLines_UnitLines_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLinesSearch));
	Connect(UnitLines_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesAdd));
	Connect(UnitLines_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesInsert));
	Connect(UnitLines_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesDelete));
	Connect(UnitLines_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesCopy));
	Connect(UnitLines_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesPaste));
	Connect(UnitLines_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesPasteInsert));
	Connect(UnitLines_UnitLineUnits_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsSelect));
	Connect(UnitLines_UnitLineUnits_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsSearch));
	Connect(UnitLines_UnitLineUnits_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsSearch));
	Connect(UnitLineUnits_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsAdd));
	Connect(UnitLineUnits_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsInsert));
	Connect(UnitLineUnits_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsDelete));
	Connect(UnitLineUnits_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsCopy));
	Connect(UnitLineUnits_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsPaste));
	Connect(UnitLineUnits_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsPasteInsert));

	UnitLines_Name->Connect(UnitLines_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	UnitLineUnits_Units->Connect(UnitLineUnits_Units->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxShort), NULL, this);
	UnitLineUnits_ComboBox_Units->Connect(UnitLineUnits_ComboBox_Units->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);

}
