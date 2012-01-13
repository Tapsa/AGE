/* AGEFrame_cpp/UnitLine.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetUnitLineName(short Index)
{
	string Name = "";
	if(GenieFile->UnitLines[Index].Name != "")
	{
		Name = GenieFile->UnitLines[Index].Name;
	}
	else
	{
		Name = "Unitline "+lexical_cast<string>(Index);
	}
	return Name;
}

void AGE_Frame::OnUnitLinesSearch(wxCommandEvent& Event)
{
	ListUnitLines();
}

void AGE_Frame::ListUnitLines()
{
	string Name;
	SearchText = wxString(UnitLines_UnitLines_Search->GetValue()).Lower();
	ExcludeText = wxString(UnitLines_UnitLines_Search_R->GetValue()).Lower();
	string CompareText;
	
	short Selection = UnitLines_UnitLines_List->GetSelection();
	short UnitIDs = Units_ComboBox_Unitline->GetSelection();

	if(UnitLines_UnitLines_List->GetCount() > 0)
	{
		UnitLines_UnitLines_List->Clear();
	}
	if(Units_ComboBox_Unitline->GetCount() > 0)
	{
		Units_ComboBox_Unitline->Clear();
	}

	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	if(UnitIDs == wxNOT_FOUND)
	{
		UnitIDs = 0;
	}

	Units_ComboBox_Unitline->Append("-1 - None");
	
	for(short loop = 0;loop < GenieFile->UnitLines.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			UnitLines_UnitLines_List->Append(Name, (void*)&GenieFile->UnitLines[loop]);
		}
		Units_ComboBox_Unitline->Append(Name);
	}
	
	UnitLines_UnitLines_List->SetSelection(0);
	UnitLines_UnitLines_List->SetFirstItem(Selection - 3);
	UnitLines_UnitLines_List->SetSelection(Selection);
	Units_ComboBox_Unitline->SetSelection(UnitIDs);
	
	wxCommandEvent E;
	OnUnitLinesSelect(E);
}

void AGE_Frame::OnUnitLinesSelect(wxCommandEvent& Event)
{
	short Selection = UnitLines_UnitLines_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = UnitLines_UnitLines_List->GetCount() - 1;
			UnitLines_UnitLines_List->SetSelection(Selection);
		}
		gdat::UnitLine * LinePointer = (gdat::UnitLine*)UnitLines_UnitLines_List->GetClientData(Selection);
		UnitLineID = LinePointer - (&GenieFile->UnitLines[0]);
		UnitLines_ID->ChangeValue(lexical_cast<string>(LinePointer->ID));
		UnitLines_ID->Container = &LinePointer->ID;
		UnitLines_Name->ChangeValue(LinePointer->Name);
		UnitLines_Name->Container = &LinePointer->Name;
		Added = false;
		ListUnitLineUnits(UnitLineID);
	}
}

void AGE_Frame::OnUnitLinesAdd(wxCommandEvent& Event)
{
	gdat::UnitLine Temp;
	GenieFile->UnitLines.push_back(Temp);
	GenieFile->UnitLines[GenieFile->UnitLines.size() - 1].ID = lexical_cast<short>(GenieFile->UnitLines.size() - 1);	//	ID Fix
	Added = true;
	ListUnitLines();
}

void AGE_Frame::OnUnitLinesDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = UnitLines_UnitLines_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->UnitLines.erase(GenieFile->UnitLines.begin() + UnitLineID);
		for(short loop = UnitLineID;loop < GenieFile->UnitLines.size();loop++)	//	ID Fix
		{
			GenieFile->UnitLines[loop].ID = lexical_cast<short>(loop);
		}
		if(Selection == UnitLines_UnitLines_List->GetCount() - 1)
		UnitLines_UnitLines_List->SetSelection(Selection - 1);
		ListUnitLines();
	}
}

void AGE_Frame::OnUnitLinesCopy(wxCommandEvent& Event)
{
	short Selection = UnitLines_UnitLines_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		UnitLineCopy = *(gdat::UnitLine*)UnitLines_UnitLines_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnUnitLinesPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = UnitLines_UnitLines_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::UnitLine*)UnitLines_UnitLines_List->GetClientData(Selection) = UnitLineCopy;
		GenieFile->UnitLines[UnitLineID].ID = lexical_cast<short>(UnitLineID);	//	ID Fix
		ListUnitLines();
	}
}

string AGE_Frame::GetUnitLineUnitName(short Index, short UnitLineID)
{
	string Name = "";
	Name = lexical_cast<string>(GenieFile->UnitLines[UnitLineID].UnitIDs[Index])+" ";
	if(LanguageDllString(GenieFile->Civs[0].Units[GenieFile->UnitLines[UnitLineID].UnitIDs[Index]].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Civs[0].Units[GenieFile->UnitLines[UnitLineID].UnitIDs[Index]].LanguageDllName);
	}
	else if(GenieFile->Civs[0].Units[GenieFile->UnitLines[UnitLineID].UnitIDs[Index]].Name != "")
	{
		Name += GenieFile->Civs[0].Units[GenieFile->UnitLines[UnitLineID].UnitIDs[Index]].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnUnitLineUnitsSearch(wxCommandEvent& Event)
{
	ListUnitLineUnits(UnitLineID);
}

void AGE_Frame::ListUnitLineUnits(short Index)
{
	string Name;
	SearchText = wxString(UnitLines_UnitLineUnits_Search->GetValue()).Lower();
	ExcludeText = wxString(UnitLines_UnitLineUnits_Search_R->GetValue()).Lower();
	string CompareText;
	short Selection = UnitLines_UnitLineUnits_List->GetSelection();

	if(UnitLines_UnitLineUnits_List->GetCount() > 0)
	{
		UnitLines_UnitLineUnits_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->UnitLines[Index].UnitIDs.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineUnitName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			UnitLines_UnitLineUnits_List->Append(Name, (void*)&GenieFile->UnitLines[Index].UnitIDs[loop]);
		}
	}
	UnitLines_UnitLineUnits_List->SetSelection(0);
	UnitLines_UnitLineUnits_List->SetFirstItem(Selection - 3);
	UnitLines_UnitLineUnits_List->SetSelection(Selection);

	wxCommandEvent E;
	OnUnitLineUnitsSelect(E);
}

void AGE_Frame::OnUnitLineUnitsSelect(wxCommandEvent& Event)
{
	short Selection = UnitLines_UnitLineUnits_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = UnitLines_UnitLineUnits_List->GetCount() - 1;
			UnitLines_UnitLineUnits_List->SetSelection(Selection);
		}
		short * UnitPointer = (short*)UnitLines_UnitLineUnits_List->GetClientData(Selection);
		UnitLineUnitID = UnitPointer - (&GenieFile->UnitLines[UnitLineID].UnitIDs[0]);
		UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*UnitPointer));
		UnitLineUnits_Units->Container = UnitPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*UnitPointer + 1);
		Added = false;
	}
	else
	{
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	}
}

void AGE_Frame::OnUnitLineUnitsAdd(wxCommandEvent& Event)
{
	short Selection = UnitLines_UnitLines_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		short Temp = 0;
		GenieFile->UnitLines[UnitLineID].UnitIDs.push_back(Temp);
		Added = true;
		ListUnitLineUnits(UnitLineID);
	}
}

void AGE_Frame::OnUnitLineUnitsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = UnitLines_UnitLineUnits_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->UnitLines[UnitLineID].UnitIDs.erase(GenieFile->UnitLines[UnitLineID].UnitIDs.begin() + UnitLineUnitID);
		if(Selection == UnitLines_UnitLineUnits_List->GetCount() - 1)
		UnitLines_UnitLineUnits_List->SetSelection(Selection - 1);
		ListUnitLineUnits(UnitLineID);
	}
}

void AGE_Frame::OnUnitLineUnitsCopy(wxCommandEvent& Event)
{
	short Selection = UnitLines_UnitLineUnits_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		UnitLineUnitCopy = *(short*)UnitLines_UnitLineUnits_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnUnitLineUnitsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = UnitLines_UnitLineUnits_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(short*)UnitLines_UnitLineUnits_List->GetClientData(Selection) = UnitLineUnitCopy;
		ListUnitLineUnits(UnitLineID);
	}
}

void AGE_Frame::CreateUnitLineControls()
{
	Tab_UnitLine = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	UnitLines_Main = new wxBoxSizer(wxHORIZONTAL);
	UnitLines_ListArea = new wxBoxSizer(wxVERTICAL);
	UnitLines_UnitLines_Buttons = new wxGridSizer(2, 0, 0);
	UnitLineUnits_ListArea = new wxBoxSizer(wxVERTICAL);
	UnitLines_UnitLineUnits_Buttons = new wxGridSizer(2, 0, 0);
	UnitLines_DataArea = new wxBoxSizer(wxVERTICAL);
	
	UnitLines_UnitLines = new wxStaticBoxSizer(wxVERTICAL, Tab_UnitLine, "Unitlines");
	UnitLines_UnitLines_Search = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLines_Search_R = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLines_List = new wxListBox(Tab_UnitLine, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	UnitLines_Add = new wxButton(Tab_UnitLine, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Delete = new wxButton(Tab_UnitLine, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Copy = new wxButton(Tab_UnitLine, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Paste = new wxButton(Tab_UnitLine, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));

	UnitLines_Holder_ID = new wxBoxSizer(wxVERTICAL);
	UnitLines_Text_ID = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unitline ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLines_ID = new TextCtrl_Short(Tab_UnitLine, "0", NULL);
	UnitLines_Holder_Name = new wxBoxSizer(wxVERTICAL);
	UnitLines_Text_Name = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unitline Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLines_Name = new TextCtrl_String(Tab_UnitLine, "0", NULL);

	UnitLines_UnitLineUnits = new wxStaticBoxSizer(wxVERTICAL, Tab_UnitLine, "Units");
	UnitLines_UnitLineUnits_Search = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLineUnits_Search_R = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLineUnits_List = new wxListBox(Tab_UnitLine, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	UnitLineUnits_Add = new wxButton(Tab_UnitLine, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Delete = new wxButton(Tab_UnitLine, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Copy = new wxButton(Tab_UnitLine, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Paste = new wxButton(Tab_UnitLine, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));

	UnitLineUnits_Holder_Units = new wxBoxSizer(wxVERTICAL);
	UnitLineUnits_Text_Units = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLineUnits_Units = new TextCtrl_Short(Tab_UnitLine, "0", NULL);
	UnitLineUnits_ComboBox_Units = new ComboBox_Short(Tab_UnitLine, UnitLineUnits_Units);

	UnitLines_UnitLines_Buttons->Add(UnitLines_Add, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Delete, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Copy, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Paste, 1, wxEXPAND);

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
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Delete, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Copy, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Paste, 1, wxEXPAND);

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
	
	UnitLines_ID->Enable(false);

	Tab_UnitLine->SetSizer(UnitLines_Main);
	
	Connect(UnitLines_UnitLines_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitLinesSelect));
	Connect(UnitLines_UnitLines_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLinesSearch));
	Connect(UnitLines_UnitLines_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLinesSearch));
	Connect(UnitLines_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesAdd));
	Connect(UnitLines_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesDelete));
	Connect(UnitLines_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesCopy));
	Connect(UnitLines_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesPaste));
	Connect(UnitLines_UnitLineUnits_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsSelect));
	Connect(UnitLines_UnitLineUnits_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsSearch));
	Connect(UnitLines_UnitLineUnits_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsSearch));
	Connect(UnitLineUnits_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsAdd));
	Connect(UnitLineUnits_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsDelete));
	Connect(UnitLineUnits_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsCopy));
	Connect(UnitLineUnits_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsPaste));

	UnitLines_Name->Connect(UnitLines_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	UnitLineUnits_Units->Connect(UnitLineUnits_Units->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxShort), NULL, this);
	UnitLineUnits_ComboBox_Units->Connect(UnitLineUnits_ComboBox_Units->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);

}
