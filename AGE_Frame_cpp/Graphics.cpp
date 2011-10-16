/* AGEFrame_cpp/Graphics.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetGraphicName(int Index)
{
	string Name = "";
	if(GenieFile->Graphics.getPointerAt(Index))
	{
		Name = GenieFile->Graphics[Index].Name;
	
	}
	else
	{
		Name = "*Disabled*";
	}
	return Name;
}

void AGE_Frame::ListGraphics()
{
	string Name;
	wxString SearchText = wxString(Graphics_Graphics_Search->GetValue()).Lower();
	string CompareText;
	
	short GraphicID = Graphics_Graphics_List->GetSelection();
	short GraphicID1 = Units_ComboBox_ConstructionGraphicID->GetSelection();
	short GraphicID2 = Units_ComboBox_SnowGraphicID->GetSelection();
	short GraphicID3 = Units_ComboBox_AttackGraphic->GetSelection();
	short GraphicID4 = Units_ComboBox_StandingGraphic[0]->GetSelection();
	short GraphicID5 = Units_ComboBox_StandingGraphic[1]->GetSelection();
	short GraphicID6 = Units_ComboBox_GarrisonGraphic[0]->GetSelection();
	short GraphicID7 = Units_ComboBox_GarrisonGraphic[1]->GetSelection();
	short GraphicID8 = Units_ComboBox_WalkingGraphic[0]->GetSelection();
	short GraphicID9 = Units_ComboBox_WalkingGraphic[1]->GetSelection();
	short GraphicID10 = Units_ComboBox_DyingGraphic[0]->GetSelection();
	short GraphicID11 = Units_ComboBox_DyingGraphic[1]->GetSelection();
	short GraphicID12 = Units_ComboBox_AttackMissileDuplicationGraphic->GetSelection();
	short GraphicID13 = UnitCommands_ComboBox_Graphics[0]->GetSelection();
	short GraphicID14 = UnitCommands_ComboBox_Graphics[1]->GetSelection();
	short GraphicID15 = UnitCommands_ComboBox_Graphics[2]->GetSelection();
	short GraphicID16 = UnitCommands_ComboBox_Graphics[3]->GetSelection();
	short GraphicID17 = UnitCommands_ComboBox_Graphics[4]->GetSelection();
	short GraphicID18 = UnitCommands_ComboBox_Graphics[5]->GetSelection();
	short GraphicID19 = DamageGraphics_ComboBox_GraphicID->GetSelection();
	short GraphicID20 = TerrainLimits_ComboBox_Graphics[0]->GetSelection();
	short GraphicID21 = TerrainLimits_ComboBox_Graphics[1]->GetSelection();

	if(!Graphics_Graphics_List->IsEmpty())
	{
		Graphics_Graphics_List->Clear();
	}
	if(!Units_ComboBox_ConstructionGraphicID->IsEmpty())
	{
		Units_ComboBox_ConstructionGraphicID->Clear();
	}
	if(!Units_ComboBox_SnowGraphicID->IsEmpty())
	{
		Units_ComboBox_SnowGraphicID->Clear();
	}
	if(!Units_ComboBox_AttackGraphic->IsEmpty())
	{
		Units_ComboBox_AttackGraphic->Clear();
	}
	if(!Units_ComboBox_StandingGraphic[0]->IsEmpty())
	{
		Units_ComboBox_StandingGraphic[0]->Clear();
	}
	if(!Units_ComboBox_StandingGraphic[1]->IsEmpty())
	{
		Units_ComboBox_StandingGraphic[1]->Clear();
	}
	if(!Units_ComboBox_GarrisonGraphic[0]->IsEmpty())
	{
		Units_ComboBox_GarrisonGraphic[0]->Clear();
	}
	if(!Units_ComboBox_GarrisonGraphic[1]->IsEmpty())
	{
		Units_ComboBox_GarrisonGraphic[1]->Clear();
	}
	if(!Units_ComboBox_WalkingGraphic[0]->IsEmpty())
	{
		Units_ComboBox_WalkingGraphic[0]->Clear();
	}
	if(!Units_ComboBox_WalkingGraphic[1]->IsEmpty())
	{
		Units_ComboBox_WalkingGraphic[1]->Clear();
	}
	if(!Units_ComboBox_DyingGraphic[0]->IsEmpty())
	{
		Units_ComboBox_DyingGraphic[0]->Clear();
	}
	if(!Units_ComboBox_DyingGraphic[1]->IsEmpty())
	{
		Units_ComboBox_DyingGraphic[1]->Clear();
	}
	if(!Units_ComboBox_AttackMissileDuplicationGraphic->IsEmpty())
	{
		Units_ComboBox_AttackMissileDuplicationGraphic->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[0]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[0]->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[1]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[1]->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[2]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[2]->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[3]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[3]->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[4]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[4]->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[5]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[5]->Clear();
	}
	if(!DamageGraphics_ComboBox_GraphicID->IsEmpty())
	{
		DamageGraphics_ComboBox_GraphicID->Clear();
	}
	if(!TerrainLimits_ComboBox_Graphics[0]->IsEmpty())
	{
		TerrainLimits_ComboBox_Graphics[0]->Clear();
	}
	if(!TerrainLimits_ComboBox_Graphics[1]->IsEmpty())
	{
		TerrainLimits_ComboBox_Graphics[1]->Clear();
	}
	
	if(GraphicID == wxNOT_FOUND)
	{
		GraphicID = 0;
	}
	if(GraphicID1 == wxNOT_FOUND)
	{
		GraphicID1 = 0;
	}
	if(GraphicID2 == wxNOT_FOUND)
	{
		GraphicID2 = 0;
	}
	if(GraphicID3 == wxNOT_FOUND)
	{
		GraphicID3 = 0;
	}
	if(GraphicID4 == wxNOT_FOUND)
	{
		GraphicID4 = 0;
	}
	if(GraphicID5 == wxNOT_FOUND)
	{
		GraphicID5 = 0;
	}
	if(GraphicID6 == wxNOT_FOUND)
	{
		GraphicID6 = 0;
	}
	if(GraphicID7 == wxNOT_FOUND)
	{
		GraphicID7 = 0;
	}
	if(GraphicID8 == wxNOT_FOUND)
	{
		GraphicID8 = 0;
	}
	if(GraphicID9 == wxNOT_FOUND)
	{
		GraphicID9 = 0;
	}
	if(GraphicID10 == wxNOT_FOUND)
	{
		GraphicID10 = 0;
	}
	if(GraphicID11 == wxNOT_FOUND)
	{
		GraphicID11 = 0;
	}
	if(GraphicID12 == wxNOT_FOUND)
	{
		GraphicID12 = 0;
	}
	if(GraphicID13 == wxNOT_FOUND)
	{
		GraphicID13 = 0;
	}
	if(GraphicID14 == wxNOT_FOUND)
	{
		GraphicID14 = 0;
	}
	if(GraphicID15 == wxNOT_FOUND)
	{
		GraphicID15 = 0;
	}
	if(GraphicID16 == wxNOT_FOUND)
	{
		GraphicID16 = 0;
	}
	if(GraphicID17 == wxNOT_FOUND)
	{
		GraphicID17 = 0;
	}
	if(GraphicID18 == wxNOT_FOUND)
	{
		GraphicID18 = 0;
	}
	if(GraphicID19 == wxNOT_FOUND)
	{
		GraphicID19 = 0;
	}
	if(GraphicID20 == wxNOT_FOUND)
	{
		GraphicID20 = 0;
	}
	if(GraphicID21 == wxNOT_FOUND)
	{
		GraphicID21 = 0;
	}
	
	Units_ComboBox_ConstructionGraphicID->Append("-1 - None");
	Units_ComboBox_SnowGraphicID->Append("-1 - None");
	Units_ComboBox_AttackGraphic->Append("-1 - None");
	Units_ComboBox_StandingGraphic[0]->Append("-1 - None");
	Units_ComboBox_StandingGraphic[1]->Append("-1 - None");
	Units_ComboBox_GarrisonGraphic[0]->Append("-1 - None");
	Units_ComboBox_GarrisonGraphic[1]->Append("-1 - None");
	Units_ComboBox_WalkingGraphic[0]->Append("-1 - None");
	Units_ComboBox_WalkingGraphic[1]->Append("-1 - None");
	Units_ComboBox_DyingGraphic[0]->Append("-1 - None");
	Units_ComboBox_DyingGraphic[1]->Append("-1 - None");
	Units_ComboBox_AttackMissileDuplicationGraphic->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[0]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[1]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[2]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[3]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[4]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[5]->Append("-1 - None");
	DamageGraphics_ComboBox_GraphicID->Append("-1 - None");
	TerrainLimits_ComboBox_Graphics[0]->Append("-1 - None");
	TerrainLimits_ComboBox_Graphics[1]->Append("-1 - None");
	
	for(short loop = 0;loop < GenieFile->Graphics.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetGraphicName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetGraphicName(loop)).Lower();
		if((SearchText.IsEmpty()) || (CompareText.find(SearchText) != string::npos))
		{
			Graphics_Graphics_List->Append(Name, (void*)&GenieFile->Graphics[loop]);
		}
		Units_ComboBox_ConstructionGraphicID->Append(Name);
		Units_ComboBox_SnowGraphicID->Append(Name);
		Units_ComboBox_AttackGraphic->Append(Name);
		Units_ComboBox_StandingGraphic[0]->Append(Name);
		Units_ComboBox_StandingGraphic[1]->Append(Name);
		Units_ComboBox_GarrisonGraphic[0]->Append(Name);
		Units_ComboBox_GarrisonGraphic[1]->Append(Name);
		Units_ComboBox_WalkingGraphic[0]->Append(Name);
		Units_ComboBox_WalkingGraphic[1]->Append(Name);
		Units_ComboBox_DyingGraphic[0]->Append(Name);
		Units_ComboBox_DyingGraphic[1]->Append(Name);
		Units_ComboBox_AttackMissileDuplicationGraphic->Append(Name);
		UnitCommands_ComboBox_Graphics[0]->Append(Name);
		UnitCommands_ComboBox_Graphics[1]->Append(Name);
		UnitCommands_ComboBox_Graphics[2]->Append(Name);
		UnitCommands_ComboBox_Graphics[3]->Append(Name);
		UnitCommands_ComboBox_Graphics[4]->Append(Name);
		UnitCommands_ComboBox_Graphics[5]->Append(Name);
		DamageGraphics_ComboBox_GraphicID->Append(Name);
		TerrainLimits_ComboBox_Graphics[0]->Append(Name);
		TerrainLimits_ComboBox_Graphics[1]->Append(Name);
	}
	
	Graphics_Graphics_List->SetSelection(0);
	Graphics_Graphics_List->SetSelection(GraphicID);
	Units_ComboBox_ConstructionGraphicID->SetSelection(GraphicID1);
	Units_ComboBox_SnowGraphicID->SetSelection(GraphicID2);
	Units_ComboBox_AttackGraphic->SetSelection(GraphicID3);
	Units_ComboBox_StandingGraphic[0]->SetSelection(GraphicID4);
	Units_ComboBox_StandingGraphic[1]->SetSelection(GraphicID5);
	Units_ComboBox_GarrisonGraphic[0]->SetSelection(GraphicID6);
	Units_ComboBox_GarrisonGraphic[1]->SetSelection(GraphicID7);
	Units_ComboBox_WalkingGraphic[0]->SetSelection(GraphicID8);
	Units_ComboBox_WalkingGraphic[1]->SetSelection(GraphicID9);
	Units_ComboBox_DyingGraphic[0]->SetSelection(GraphicID10);
	Units_ComboBox_DyingGraphic[1]->SetSelection(GraphicID11);
	Units_ComboBox_AttackMissileDuplicationGraphic->SetSelection(GraphicID12);
	UnitCommands_ComboBox_Graphics[0]->SetSelection(GraphicID13);
	UnitCommands_ComboBox_Graphics[1]->SetSelection(GraphicID14);
	UnitCommands_ComboBox_Graphics[2]->SetSelection(GraphicID15);
	UnitCommands_ComboBox_Graphics[3]->SetSelection(GraphicID16);
	UnitCommands_ComboBox_Graphics[4]->SetSelection(GraphicID17);
	UnitCommands_ComboBox_Graphics[5]->SetSelection(GraphicID18);
	DamageGraphics_ComboBox_GraphicID->SetSelection(GraphicID19);
	TerrainLimits_ComboBox_Graphics[0]->SetSelection(GraphicID20);
	TerrainLimits_ComboBox_Graphics[1]->SetSelection(GraphicID21);
	
	wxCommandEvent E;
	OnGraphicsSelect(E);
}

void AGE_Frame::OnGraphicsSearch(wxCommandEvent& Event)
{
	ListGraphics();
}

void AGE_Frame::OnGraphicsSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnGraphicsAdd(wxCommandEvent& Event)
{

}

void AGE_Frame::OnGraphicsDelete(wxCommandEvent& Event)
{

}

void AGE_Frame::OnGraphicsCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnGraphicsPaste(wxCommandEvent& Event)
{

}

void AGE_Frame::CreateGraphicsControls()
{

	Tab_Graphics = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(-1, 350));
	Graphics_Main = new wxBoxSizer(wxHORIZONTAL);
	Graphics_ListArea = new wxBoxSizer(wxVERTICAL);
	Graphics_Graphics_Buttons = new wxGridSizer(2, 0, 0);

	Graphics_Graphics = new wxStaticBoxSizer(wxVERTICAL, Tab_Graphics, "Graphic Slot");
	Graphics_Graphics_Search = new wxTextCtrl(Tab_Graphics, wxID_ANY);
	Graphics_Graphics_List = new wxListBox(Tab_Graphics, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	Graphics_Add = new wxButton(Tab_Graphics, wxID_ANY, "Add", wxDefaultPosition, wxSize(-1, 20));
	Graphics_Delete = new wxButton(Tab_Graphics, wxID_ANY, "Delete", wxDefaultPosition, wxSize(-1, 20));
	Graphics_Copy = new wxButton(Tab_Graphics, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Graphics_Paste = new wxButton(Tab_Graphics, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));

	Graphics_Graphics_Buttons->Add(Graphics_Add, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Delete, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Copy, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Paste, 1, wxEXPAND);

	Graphics_Graphics->Add(Graphics_Graphics_Search, 0, wxEXPAND);
	Graphics_Graphics->Add(-1, 2);
	Graphics_Graphics->Add(Graphics_Graphics_List, 1, wxEXPAND);
	Graphics_Graphics->Add(-1, 2);
	Graphics_Graphics->Add(Graphics_Graphics_Buttons, 0, wxEXPAND);

	Graphics_ListArea->Add(-1, 10);
	Graphics_ListArea->Add(Graphics_Graphics, 1, wxEXPAND);
	Graphics_ListArea->Add(-1, 10);

	Graphics_Main->Add(10, -1);
	Graphics_Main->Add(Graphics_ListArea, 1, wxEXPAND);
	Graphics_Main->Add(10, -1);
	Graphics_Main->Add(-1, -1, 3, wxEXPAND);
	Graphics_Main->Add(10, -1);

	Tab_Graphics->SetSizer(Graphics_Main);
	
	Connect(Graphics_Graphics_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
	Connect(Graphics_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsAdd));
	Connect(Graphics_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsDelete));
	Connect(Graphics_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsCopy));
	Connect(Graphics_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsPaste));

}
