/* AGEFrame_cpp/Other.cpp */

#include "../AGE_Frame.h"
#include "../AGE_OpenDialog.h"
#include "../AGE_SaveDialog.h"
#include "../AGE_AboutDialog.h"
#include <stdio.h>
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include "wx/filename.h"
#include "windows.h"

void AGE_Frame::OnOpen(wxCommandEvent& Event)
{
	int ErrCode = 0;
	wxCommandEvent Selected;

	if(!SkipOpenDialog)
	{
		AGE_OpenDialog OpenBox (this, NeedDat);

		OpenBox.CheckBox_GenieVer->SetSelection(GameVersion);

		switch(DatUsed)
		{
			case 0:
			{
				OpenBox.Radio_DatFileLocation->SetValue(true);
				Selected.SetEventType(wxEVT_COMMAND_RADIOBUTTON_SELECTED);
				Selected.SetId(OpenBox.Radio_DatFileLocation->GetId());
				Selected.SetInt(true);
				OpenBox.ProcessEvent(Selected);
			}
			break;
			case 1:
			{
				/*OpenBox.Radio_UnzFileLocation->SetValue(true);
				Selected.SetEventType(wxEVT_COMMAND_RADIOBUTTON_SELECTED);
				Selected.SetId(OpenBox.Radio_UnzFileLocation->GetId());
				Selected.SetInt(true);
				OpenBox.ProcessEvent(Selected);*/
			}
			break;
			case 2:
			{
				OpenBox.Radio_ApfFileLocation->SetValue(true);
				Selected.SetEventType(wxEVT_COMMAND_RADIOBUTTON_SELECTED);
				Selected.SetId(OpenBox.Radio_ApfFileLocation->GetId());
				Selected.SetInt(true);
				OpenBox.ProcessEvent(Selected);
			}
			break;
			case 3:
			{
				OpenBox.Radio_NoFile->SetValue(true);
				Selected.SetEventType(wxEVT_COMMAND_RADIOBUTTON_SELECTED);
				Selected.SetId(OpenBox.Radio_NoFile->GetId());
				Selected.SetInt(true);
				OpenBox.ProcessEvent(Selected);
			}
			break;
		}

		OpenBox.DriveLetterBox->ChangeValue(DriveLetter);
		OpenBox.Path_DatFileLocation->SetPath(DatFileName);
//		OpenBox.Path_UnzFileLocation->SetPath(UnzFileName);
		OpenBox.Path_ApfFileLocation->SetPath(ApfFileName);

		if(LangsUsed & 1)
		{
			OpenBox.CheckBox_LangFileLocation->SetValue(true);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangFileLocation->GetId());
			Selected.SetInt(true);
			OpenBox.ProcessEvent(Selected);
		}
		else
		{
			OpenBox.CheckBox_LangFileLocation->SetValue(false);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangFileLocation->GetId());
			Selected.SetInt(false);
			OpenBox.ProcessEvent(Selected);
		}
		if(LangsUsed & 2)
		{
			OpenBox.CheckBox_LangX1FileLocation->SetValue(true);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangX1FileLocation->GetId());
			Selected.SetInt(true);
			OpenBox.ProcessEvent(Selected);
		}
		else
		{
			OpenBox.CheckBox_LangX1FileLocation->SetValue(false);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangX1FileLocation->GetId());
			Selected.SetInt(false);
			OpenBox.ProcessEvent(Selected);
		}
		if(LangsUsed & 4)
		{
			OpenBox.CheckBox_LangX1P1FileLocation->SetValue(true);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangX1P1FileLocation->GetId());
			Selected.SetInt(true);
			OpenBox.ProcessEvent(Selected);
		}
		else
		{
			OpenBox.CheckBox_LangX1P1FileLocation->SetValue(false);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangX1P1FileLocation->GetId());
			Selected.SetInt(false);
			OpenBox.ProcessEvent(Selected);
		}

		OpenBox.Path_LangFileLocation->SetPath(LangFileName);
		OpenBox.Path_LangX1FileLocation->SetPath(LangX1FileName);
		OpenBox.Path_LangX1P1FileLocation->SetPath(LangX1P1FileName);

		if (OpenBox.ShowModal() != wxID_OK)
		{
			return;
		}

		GameVersion = OpenBox.CheckBox_GenieVer->GetSelection();
		if(OpenBox.Radio_DatFileLocation->GetValue())
		{
			DatUsed = 0;
		}
		/*else if(OpenBox.Radio_UnzFileLocation->GetValue())
		{
			DatUsed = 1;
		}*/
		else if(OpenBox.Radio_ApfFileLocation->GetValue())
		{
			DatUsed = 2;
		}
		else
		{
			DatUsed = 3;
		}

		DriveLetter = OpenBox.DriveLetterBox->GetValue();
		DatFileName = OpenBox.Path_DatFileLocation->GetPath();
//		UnzFileName = OpenBox.Path_UnzFileLocation->GetPath();
		ApfFileName = OpenBox.Path_ApfFileLocation->GetPath();

		if(OpenBox.CheckBox_LangFileLocation->IsChecked())
		{
			LangsUsed |= 1;
		}
		else
		{
			LangsUsed &= ~1;
		}
		if(OpenBox.CheckBox_LangX1FileLocation->IsChecked())
		{
			LangsUsed |= 2;
		}
		else
		{
			LangsUsed &= ~2;
		}
		if(OpenBox.CheckBox_LangX1P1FileLocation->IsChecked())
		{
			LangsUsed |= 4;
		}
		else
		{
			LangsUsed &= ~4;
		}

		LangFileName = OpenBox.Path_LangFileLocation->GetPath();
		LangX1FileName = OpenBox.Path_LangX1FileLocation->GetPath();
		LangX1P1FileName = OpenBox.Path_LangX1P1FileLocation->GetPath();
	}

	if(LangsUsed & 1)
	{
		LanguageDll[0] = LoadLibrary(LangFileName.c_str());
	}
	if(LangsUsed & 2)
	{
		LanguageDll[1] = LoadLibrary(LangX1FileName.c_str());
	}
	if(LangsUsed & 4)
	{
		LanguageDll[2] = LoadLibrary(LangX1P1FileName.c_str());
	}

	gdat::GameVersion GenieVersion;
	switch(GameVersion)
	{
	case 0:
	    GenieVersion = gdat::GV_AoE;
		break;
	case 1:
	    GenieVersion = gdat::GV_RoR;
		break;
	case 2:
	    GenieVersion = gdat::GV_AoK;
		break;
	case 3:
	    GenieVersion = gdat::GV_TC;
		break;
	case 4:
	    GenieVersion = gdat::GV_SWGB;
		break;
	case 5:
	    GenieVersion = gdat::GV_CC;
		break;
	default:
		GenieVersion = gdat::GV_None;
	}

	switch(DatUsed)
	{
		/*case 1:
		{
			string OutputFile;
			switch(GameVersion)
			{
				case 0:
				{
					OutputFile = "AoE.unz";
				}
				break;
				case 1:
				{
					OutputFile = "RoR.unz";
				}
				break;
				case 2:
				{
					OutputFile = "AoK.unz";
				}
				break;
				case 3:
				{
					OutputFile = "TC.unz";
				}
				break;
				case 4:
				{
					OutputFile = "SWGB.unz";
				}
				break;
				case 5:
				{
					OutputFile = "CC.unz";
				}
				break;
			}

			if(GenieFile != NULL)
			{
				delete GenieFile;
			}

			
		//	GenieFile = new DatObject(OutputFile.c_str(), GameVersion);
			{
				SetStatusText("Reading uncompressed file...", 0);
				wxBusyCursor WaitCursor;
				GenieFile = new gdat::File(UnzFileName.c_str(), GenieVersion, true);
			}
				ErrCode = GenieFile->Read();
			}

			if(ErrCode)
			{
				wxMessageBox(wxT("Error Code: " + lexical_cast<string>(ErrCode)));
			}
		}
		break;*/
		case 0:
		{
			if(GenieFile != NULL)
			{
				delete GenieFile;
			}
			
			{
				SetStatusText("Reading file...", 0);
				wxBusyCursor WaitCursor;
				GenieFile = new gdat::File(DatFileName.c_str(), GenieVersion);
			}
//			{
				

/*				ErrCode = GenieFile->Read();
			}

			if(ErrCode)
			{
				wxMessageBox(wxT("Error Code: " + lexical_cast<string>(ErrCode)));
			}
*/		}
		break;
		case 2:
		{

		}
		break;
	}

	if(GenieFile != NULL)
	{	// As of now, without these, nothing can be edited.
		SetStatusText("Listing...", 0);
		wxBusyCursor WaitCursor;

		Added = false;
		ListGraphics();
		ListSounds();
		ListTerrains();
		ListTerrainRestrictions();
		ListPlayerColors();
		ListCivs();
		ListTechages();
		if(GameVersion > 1)
		{
			ListUnitHeads();	// This needs to happen before unit listing to avoid crash.
		}
		ListUnits();
		ListResearchs();
		
//		ID Fixes
		for(short loop2 = 0;loop2 < GenieFile->Civs.size();loop2++)
		{
			for(short loop = 0;loop < GenieFile->Civs[loop2].Units.size();loop++)
			{
				GenieFile->Civs[loop2].Units[loop].ID1 = lexical_cast<short>(loop);
				GenieFile->Civs[loop2].Units[loop].ID2 = lexical_cast<short>(loop);
				GenieFile->Civs[loop2].Units[loop].ID3 = lexical_cast<short>(loop);
				if(GameVersion < 2)
				for(short loop3 = 0;loop3 < GenieFile->Civs[loop2].Units[loop].Bird->Commands.size();loop3++)
				GenieFile->Civs[loop2].Units[loop].Bird->Commands[loop3].ID = lexical_cast<short>(loop3);
			}
		}
		for(short loop = 0;loop < GenieFile->PlayerColours.size();loop++)
		{
			GenieFile->PlayerColours[loop].ID = lexical_cast<long>(loop);
		}
		for(short loop = 0;loop < GenieFile->Graphics.size();loop++)
		{
			GenieFile->Graphics[loop].ID = lexical_cast<short>(loop);
		}
		for(short loop = 0;loop < GenieFile->Sounds.size();loop++)
		{
			GenieFile->Sounds[loop].ID = lexical_cast<long>(loop);
		}
	}
	
	DataOpened = true;
	OnGameVersionChange();

	NeedDat = false;
	SkipOpenDialog = false;
	SetStatusText("", 0);
}

void AGE_Frame::OnGameVersionChange()
{
	Research_ScrollerWindowsSpace->Layout();
	Research_Scroller->GetSizer()->FitInside(Research_Scroller);
	Research_Scroller->Scroll(0, 0);
	Research_Scroller->GetSizer()->SetDimension(0, 0, Research_Scroller->GetSize().GetWidth() - 15, 1);
//	Research_Scroller->Refresh();
	Civs_DataArea->Layout();
	Units_ScrollerWindowsSpace->Layout();
	Units_Scroller->GetSizer()->FitInside(Units_Scroller);
	Units_Scroller->Scroll(0, 0);
	Units_Scroller->GetSizer()->SetDimension(0, 0, Units_Scroller->GetSize().GetWidth() - 15, 1);
//	Units_Scroller->Refresh();
	Graphics_ScrollerWindowsSpace->Layout();
	Graphics_Scroller->GetSizer()->FitInside(Graphics_Scroller);
	Graphics_Scroller->Scroll(0, 0);
	Graphics_Scroller->GetSizer()->SetDimension(0, 0, Graphics_Scroller->GetSize().GetWidth() - 15, 1);
//	Graphics_Scroller->Refresh();
	Terrains_ScrollerWindowsSpace->Layout();
	Terrains_Scroller->GetSizer()->FitInside(Terrains_Scroller);
	Terrains_Scroller->Scroll(0, 0);
	Terrains_Scroller->GetSizer()->SetDimension(0, 0, Terrains_Scroller->GetSize().GetWidth() - 15, 1);
//	Terrains_Scroller->Refresh();
	TerRestrict_DataArea->Layout();
	Sounds_DataArea->Layout();
	Colors_DataArea->Layout();
//	Refresh();
}

void AGE_Frame::OnSave(wxCommandEvent& Event)
{
	int ErrCode = 0;
	wxCommandEvent Selected;
	
//	if(!QuickSave)
//	{
		AGE_SaveDialog SaveBox (this);

		SaveBox.DriveLetterBox->ChangeValue(DriveLetter);
		SaveBox.CheckBox_GenieVer->SetSelection(SaveGameVersion);

		SaveBox.CheckBox_DatFileLocation->SetValue(SaveDat);
		Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
		Selected.SetId(SaveBox.CheckBox_DatFileLocation->GetId());
		Selected.SetInt(SaveDat);
		SaveBox.ProcessEvent(Selected);

		SaveBox.Path_DatFileLocation->SetPath(SaveDatFileName);

		/*SaveBox.CheckBox_UnzFileLocation->SetValue(SaveUnz);
		Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
		Selected.SetId(SaveBox.CheckBox_UnzFileLocation->GetId());
		Selected.SetInt(SaveUnz);
		SaveBox.ProcessEvent(Selected);

		SaveBox.Path_UnzFileLocation->SetPath(SaveUnzFileName);*/

		SaveBox.CheckBox_ApfFileLocation->SetValue(SaveApf);
		Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
		Selected.SetId(SaveBox.CheckBox_ApfFileLocation->GetId());
		Selected.SetInt(SaveApf);
		SaveBox.ProcessEvent(Selected);

		SaveBox.Path_ApfFileLocation->SetPath(SaveApfFileName);

		if (SaveBox.ShowModal() != wxID_OK)
		{
			return;
		}

		SaveGameVersion = SaveBox.CheckBox_GenieVer->GetSelection();
		SaveDat = SaveBox.CheckBox_DatFileLocation->IsChecked();
//		SaveUnz = SaveBox.CheckBox_UnzFileLocation->IsChecked();
		SaveApf = SaveBox.CheckBox_ApfFileLocation->IsChecked();

		SaveDatFileName = SaveBox.Path_DatFileLocation->GetPath();
//		SaveUnzFileName = SaveBox.Path_UnzFileLocation->GetPath();
		SaveApfFileName = SaveBox.Path_ApfFileLocation->GetPath();
//	}
	
	/*if(SaveUnz && SaveDat)
	{
		{
			SetStatusText("Saving unz file...", 0);
			wxBusyCursor WaitCursor;

			GenieFile->save(std::string(SaveUnzFileName.c_str()), true);
		}
		
		{
			SetStatusText("Saving dat file...", 0);
			wxBusyCursor WaitCursor;

			GenieFile->save(std::string(SaveDatFileName.c_str()));
		}
	}
	else
	{*/
		if(SaveDat)
		{
			{
				SetStatusText("Saving dat file...", 0);
				wxBusyCursor WaitCursor;

				GenieFile->save(std::string(SaveDatFileName.c_str()));
			}
		}
		/*if(SaveUnz)
		{
			SetStatusText("Saving unz file...", 0);
			wxBusyCursor WaitCursor;
			GenieFile->save(std::string(SaveUnzFileName.c_str()), true);
		}*/
		if(SaveApf)
		{
			//	 Not Implemented Yet = Nothing Happens
		}
//	}
	SetStatusText("", 0);
}

void AGE_Frame::OnExit(wxCloseEvent& Event)
{
	Config = new wxFileConfig("AdvancedGenieEditor", wxEmptyString, "age2config.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	Config->Write("Interaction/PromptForFilesOnOpen", PromptForFilesOnOpen);
	Config->Write("Interaction/AutoCopyToAllCivs", AutoCopy);
	Config->Write("Interaction/ExtraSearchFilters", SearchFilters);
	Config->Write("Interface/ShowUnknowns", ShowUnknowns);
	Config->Write("Interface/ShowButtons", ShowButtons);
	Config->Write("DefaultFiles/DriveLetter", DriveLetter);
	Config->Write("DefaultFiles/Version", GameVersion);
	Config->Write("DefaultFiles/SaveVersion", SaveGameVersion);
	Config->Write("DefaultFiles/DatUsed", DatUsed);
	Config->Write("DefaultFiles/DatFilename", DatFileName);
//	Config->Write("DefaultFiles/UnzFilename", UnzFileName);
	Config->Write("DefaultFiles/ApfFilename", ApfFileName);
	Config->Write("DefaultFiles/SaveDatFilename", SaveDatFileName);
//	Config->Write("DefaultFiles/SaveUnzFilename", SaveUnzFileName);
	Config->Write("DefaultFiles/SaveApfFilename", SaveApfFileName);
	Config->Write("DefaultFiles/LangsUsed", LangsUsed);
	Config->Write("DefaultFiles/LangFilename", LangFileName);
	Config->Write("DefaultFiles/LangX1Filename", LangX1FileName);
	Config->Write("DefaultFiles/LangX1P1Filename", LangX1P1FileName);
	Config->Write("DefaultFiles/SaveDat", SaveDat);
//	Config->Write("DefaultFiles/SaveUnz", SaveUnz);
	Config->Write("DefaultFiles/SaveApf", SaveApf);
	delete Config;

	delete GenieFile;
	GenieFile = 0;
	
	TabBar_Main->Show(false);
	TabBar_Main->Destroy();
	Destroy();
}

void AGE_Frame::OnMenuOption(wxCommandEvent& Event)
{
	switch(Event.GetId())
	{
		case MenuOption_Prompt:
		{
			PromptForFilesOnOpen = Event.IsChecked();
		}
		break;
		case MenuOption_Unknowns:
		{
			ShowUnknowns = Event.IsChecked();
			if(ShowUnknowns)
			{
				Units_Holder_UnknownArea->Show(true);
				Units_CommandHolder_Data2->Show(true);
				Graphics_Holder_Unknowns->Show(true);
				Graphics_Grid_Deltas_Data2->Show(true);
				Terrains_Holder_UnknownArea->Show(true);
				Sounds_Holder_Unknown->Show(true);
				SoundItems_Holder_Unknown->Show(true);
				Colors_Holder_UnknownArea->Show(true);
			}
			else
			{
				Units_Holder_UnknownArea->Show(false);
				Units_CommandHolder_Data2->Show(false);
				Graphics_Holder_Unknowns->Show(false);
				Graphics_Grid_Deltas_Data2->Show(false);
				Terrains_Holder_UnknownArea->Show(false);
				Sounds_Holder_Unknown->Show(false);
				SoundItems_Holder_Unknown->Show(false);
				Colors_Holder_UnknownArea->Show(false);
			}
			Units_ScrollerWindowsSpace->Layout();
			Units_Scroller->GetSizer()->FitInside(Units_Scroller);
			Units_Scroller->Scroll(0, 0);
			Units_Scroller->GetSizer()->SetDimension(0, 0, Units_Scroller->GetSize().GetWidth() - 15, 1);
		//	Units_Scroller->Refresh();
			Graphics_ScrollerWindowsSpace->Layout();
			Graphics_Scroller->GetSizer()->FitInside(Graphics_Scroller);
			Graphics_Scroller->Scroll(0, 0);
			Graphics_Scroller->GetSizer()->SetDimension(0, 0, Graphics_Scroller->GetSize().GetWidth() - 15, 1);
		//	Graphics_Scroller->Refresh();
			Terrains_ScrollerWindowsSpace->Layout();
			Terrains_Scroller->GetSizer()->FitInside(Terrains_Scroller);
			Terrains_Scroller->Scroll(0, 0);
			Terrains_Scroller->GetSizer()->SetDimension(0, 0, Terrains_Scroller->GetSize().GetWidth() - 15, 1);
		//	Terrains_Scroller->Refresh();
			Sounds_DataArea->Layout();
			Colors_DataArea->Layout();
		//	Refresh();
			
		//	We don't want to show unknowns that the current game version doesn't use.
			if(DataOpened == true)
			OnGameVersionChange();
		}
		break;
		case MenuOption_Buttons:
		{
			ShowButtons = Event.IsChecked();
			if(ShowButtons)
			{
				Civs_Add->Enable(true); // Adding will seriously damage unit section and does not work in game.
				Civs_Delete->Enable(true);
				Resources_Add->Enable(true);
				Resources_Delete->Enable(true);
				Graphics_Add->Enable(true);
				Graphics_Delete->Enable(true);
				Terrains_Add->Enable(true);
				Terrains_Delete->Enable(true);
			}
			else
			{
				Civs_Add->Enable(false);
				Civs_Delete->Enable(false);
				Resources_Add->Enable(false);
				Resources_Delete->Enable(false);
				Graphics_Add->Enable(false);
				Graphics_Delete->Enable(false);
				Terrains_Add->Enable(false);
				Terrains_Delete->Enable(false);
			}
		}
		break;
		case MenuOption_NoAuto:
		case MenuOption_Include:
		case MenuOption_Exclude:
		{
			AutoCopy = Event.GetId();
			if(AutoCopy == MenuOption_NoAuto)
			{
				Units_AutoCopyState->SetLabel("Auto-copy: Disabled");
			}
			else if(AutoCopy == MenuOption_Include)
			{
				Units_AutoCopyState->SetLabel("Auto-copy: Include graphics");
			}
			else if(AutoCopy == MenuOption_Exclude)
			{
				Units_AutoCopyState->SetLabel("Auto-copy: Exclude graphics");
			}
		}
		case MenuOption_NoExtra:
		case MenuOption_1stFilters:
		case MenuOption_2ndFilters:
//		case MenuOption_3rdFilters:
//		case MenuOption_4rdFilters:
		{
			SearchFilters = Event.GetId();
			if(SearchFilters == MenuOption_NoExtra)
			{
				for(short loop = 0;loop < 2;loop++)
				Units_Units_SearchFilters[loop]->Show(false);
				Units_Units_SearchFilters[0]->SetSelection(0);
			}
			else if(SearchFilters == MenuOption_1stFilters)
			{	
				Units_Units_SearchFilters[0]->Show(true);
				Units_Units_SearchFilters[1]->Show(false);
				Units_Units_SearchFilters[1]->SetSelection(0);
			}
			else if(SearchFilters == MenuOption_2ndFilters)
			{
				for(short loop = 0;loop < 2;loop++)
				Units_Units_SearchFilters[loop]->Show(true);
			}
			Units_Units->Layout();
		}
		break;
		case wxID_EXIT:
		{
			Close(true);
		}
		break;
		case MenuOption_Tips:
		{
			string TipText = "Tips\n\n";
			TipText += "You can have multiple search entries separated with \"|\" letter.\n";
			TipText += "Upper search boxes are inclusive and lower ones exclusive.\n";
			TipText += "Example: \"tower|ship|ram\"\n";
			TipText += "You can switch from or finding to and finding with check boxes.\n";
			TipText += "Meaning that every search entry has to match.\n";
			wxMessageBox(TipText);
		}
		break;
		case MenuOption_About:
		{
			AGE_AboutDialog AGEAbout(this);
			AGEAbout.ShowModal();
		}
		break;
	}
}



/* Check if File Exists */

bool AGE_Frame::FileExists(const char * value)
{
	FILE * handle;
	handle = fopen(value, "rb");
	if(handle)
	{
		fclose(handle);
	 	return true;
	}
	return false;
}

string AGE_Frame::LanguageDllString(int ID)
{
	string Result = "";
	char Buffer[256];
	
	if(LoadString(LanguageDll[2], ID, Buffer, 256) && strlen(Buffer) > 0)
	{
		Result = Buffer;
	}
	else if(LoadString(LanguageDll[1], ID, Buffer, 256) && strlen(Buffer) > 0)
	{
		Result = Buffer;
	}
	else if(LoadString(LanguageDll[0], ID, Buffer, 256) && strlen(Buffer) > 0)
	{
		Result = Buffer;
	}
	return Result;
}

bool AGE_Frame::SearchMatches(string CompareText)
{
	bool Matches = false, And[2] = {true,true};
	short Size = 30; // Maximum pieces for search text to be split.
	short Max = Size;
	wxString SearchEnd[Size]; // Parts.

	if(SearchText == "") // If there is no search text, list normally.
	{
		Matches = true;
	}
	else if(CompareText.find(SearchText) != string::npos) // If search text has a match.
	{
		Matches = true;
	}
	else
	{
		size_t Found; // Founding position.
		Found = SearchText.find("|"); // Searching for separation mark in search text.
		if((Found != string::npos) && Found > 0 && 1 < (SearchText.length() - Found)) // Separation mark found and there is search text on its both sides.
		{
			// Splitting of search.
			SearchEnd[0] = SearchText.substr(0, Found); // Cutting the first part.
			SearchEnd[1] = SearchText.substr((Found+1), SearchText.length() - 1); // Cutting the remaining part.
			
			// Lets look if there are additional separation marks left.
			for(short loop = 2;loop < Size;loop++) // Splits over 2 parts if necessary.
			{
				Found = SearchEnd[loop-1].find("|");
				if((Found != string::npos) && Found > 0 && 1 < (SearchEnd[loop-1].length() - Found))
				{
					SearchEnd[loop] = SearchEnd[loop-1].substr((Found+1), SearchEnd[loop-1].length() - 1);
					SearchEnd[loop-1] = SearchEnd[loop-1].substr(0, Found);
				}
				else
				{
					Size = loop;
					break;
				}
			}
		
			// Searching for matches.
			for(short loop = 0;loop < Size;loop++)
			{
				if(SearchEnd[loop] != "") // Can match only if not empty.
				{
					if(CompareText.find(SearchEnd[loop]) != string::npos)
					Matches = true;
					else And[0] = false;
				}
			}
			if(UseAnd[0] == true && And[0] == false && Matches == true) Matches = false;
		}
	}

	if(Matches == true)	// We don't need to check for excluding if it's not going to be listed.
	if(ExcludeText == "") // If there is no exclude text, list normally.
	{
		// Do nothing.
	}
	else if(CompareText.find(ExcludeText) != string::npos) // If exclude text has a match.
	{
		Matches = false;
	}
	else
	{
		Size = Max;
		size_t Found; // Founding position.
		Found = ExcludeText.find("|"); // Searching for separation mark in exclude text.
		if((Found != string::npos) && Found > 0 && 1 < (ExcludeText.length() - Found)) // Separation mark found and there is exclude text on its both sides.
		{
			// Splitting of exclude.
			SearchEnd[0] = ExcludeText.substr(0, Found); // Cutting the first part.
			SearchEnd[1] = ExcludeText.substr((Found+1), ExcludeText.length() - 1); // Cutting the remaining part.
			
			// Lets look if there are additional separation marks left.
			for(short loop = 2;loop < Size;loop++) // Splits over 2 parts if necessary.
			{
				Found = SearchEnd[loop-1].find("|");
				if((Found != string::npos) && Found > 0 && 1 < (SearchEnd[loop-1].length() - Found))
				{
					SearchEnd[loop] = SearchEnd[loop-1].substr((Found+1), SearchEnd[loop-1].length() - 1);
					SearchEnd[loop-1] = SearchEnd[loop-1].substr(0, Found);
				}
				else
				{
					Size = loop;
					break;
				}
			}
		
			// Searching for matches.
			for(short loop = 0;loop < Size;loop++)
			{
				if(SearchEnd[loop] != "") // Can match only if not empty.
				{
					if(CompareText.find(SearchEnd[loop]) != string::npos)
					Matches = false;
					else And[1] = false;
				}
			}
			if(UseAnd[1] == true && And[1] == false && Matches == false) Matches = true;
		}
	}
	
	return Matches;
}

//	Following kill focuses are used to update lists in user interface

void AGE_Frame::OnKillFocus_TextControls(wxFocusEvent& Event)
{
	if(Event.GetId() == Effects_E->GetId() || Event.GetId() == Effects_F->GetId())
	{
//		wxMessageBox("AGE_Frame::OnKillFocus_TextControls");
		if(!Effects_E->IsEmpty() && !Effects_F->IsEmpty()) // if has something, then update float value.
		{
			float Amount = lexical_cast<float>(Effects_E->GetValue());
			short Class = lexical_cast<short>(Effects_F->GetValue());
			if(Amount > -1 && Amount < 256 && Class > -1 && Class < 256) // positive amount 0 to 255
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount + (Class * 256)));
				wxFocusEvent Temp(wxEVT_KILL_FOCUS);
				Effects_D->OnKillFocus(Temp);
			}
			else if(Amount > -256 && Amount < 0 && Class > -1 && Class < 256) // negative amount -255 to -1
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount - (Class * 256)));
				wxFocusEvent Temp(wxEVT_KILL_FOCUS);
				Effects_D->OnKillFocus(Temp);
			}
		}
		wxCommandEvent E;
		OnEffectsSelect(E);
	}
	if(Event.GetId() == Units_Type->GetId())
	{
		if(!Units_Type->IsEmpty())
		{
			short UnitType = lexical_cast<short>(Units_Type->GetValue());
			switch(UnitType)
			{
				case 10:
				case 20:
				case 25:
				case 30:
				case 40:
				case 60:
				case 70:
				case 80:
				case 90:
				{
					GenieFile->Civs[UnitCivID].Units[UnitID].setType((char)UnitType);
					if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
					{
						for(short loop = 0;loop < GenieFile->Civs.size();loop++)
						GenieFile->Civs[loop].Units[UnitID].setType((char)UnitType);
						
						wxCommandEvent E;
						OnUnitsCopy(E);
						OnUnitsPaste(E);
					}
				}
				break;
				default:
				{
				
				}
			}
		}
		wxCommandEvent E;
		OnUnitsSelect(E);	// Updates unit layout and unit type combo box.
//		ListUnits(UnitCivID);	// For special search filters.
	}
}

void AGE_Frame::OnSelection_CheckBoxes(wxCommandEvent& Event)
{
	for(short loop = 0;loop < 2;loop++)
	if(Event.GetId() == Units_Units_UseAnd[loop]->GetId())
	{
		if(Units_Units_UseAnd[loop]->GetValue() == true)
		UseAnd[loop] = true; else UseAnd[loop] = false;
		
		wxCommandEvent E;
		OnUnitsSearch(E);
	//	ListUnits(UnitCivID);	muille tulee tällänen, unitseilla kaatuu jos ei oo avattu dataa
	}
}

void AGE_Frame::OnSelection_ComboBoxes(wxCommandEvent& Event)
{
	if(Event.GetId() == Effects_ComboBox_ClassF->GetId())
	{
		short Class = Effects_ComboBox_ClassF->GetSelection();
		if(Class > 0)
		{
			float Amount = lexical_cast<float>(Effects_E->GetValue());
			if(Amount > -1 && Amount < 256) // positive amount 0 to 255
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount + (Class * 256)));
			}
			else if(Amount > -256 && Amount < 0) // negative amount -255 to -1
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount - (Class * 256)));
			}
		}
		else
		{
			Effects_E->ChangeValue("0");
			Effects_F->ChangeValue("0");
			Effects_D->ChangeValue("0");
		}
		wxFocusEvent Temp(wxEVT_KILL_FOCUS);
		Effects_D->OnKillFocus(Temp);

		wxCommandEvent E;
		OnEffectsSelect(E);
	}
	if(Event.GetId() == Units_ComboBox_Type->GetId())
	{
		short Selection = Units_ComboBox_Type->GetSelection();
		if(Selection == 1)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].setType(10);
		}
		else if(Selection == 2)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].setType(20);
		}
		else if(Selection == 3)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].setType(30);
		}
		else if(Selection == 4)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].setType(60);
		}
		else if(Selection == 5)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].setType(70);
		}
		else if(Selection == 6)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].setType(80);
		}
		else
		{
		
		}
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			char UnitType = GenieFile->Civs[UnitCivID].Units[UnitID].getType();
			for(short loop = 0;loop < GenieFile->Civs.size();loop++)
			GenieFile->Civs[loop].Units[UnitID].setType(UnitType);
			
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);	
		}
		
		wxCommandEvent E;
		OnUnitsSelect(E);	// Updates unit layout.
//		ListUnits(UnitCivID);	// For special search filters.
	}
	if(Event.GetId() == UnitCommands_ComboBox_Types->GetId())
	{
		short Selection = UnitCommands_ComboBox_Types->GetSelection();
		if(Selection == 1)
		{
			UnitCommands_Type->ChangeValue("3");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 2)
		{
			UnitCommands_Type->ChangeValue("5");
			UnitCommands_SubType->ChangeValue("47");
		}
		else if(Selection == 3)
		{
			UnitCommands_Type->ChangeValue("5");
			UnitCommands_SubType->ChangeValue("79");
		}
		else if(Selection == 4)
		{
			UnitCommands_Type->ChangeValue("5");
			UnitCommands_SubType->ChangeValue("190");
		}
		else if(Selection == 5)
		{
			UnitCommands_Type->ChangeValue("5");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 6)
		{
			UnitCommands_Type->ChangeValue("6");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 7)
		{
			UnitCommands_Type->ChangeValue("7");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 8)
		{
			UnitCommands_Type->ChangeValue("10");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 9)
		{
			UnitCommands_Type->ChangeValue("11");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 10)
		{
			UnitCommands_Type->ChangeValue("12");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 11)
		{
			UnitCommands_Type->ChangeValue("13");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 12)
		{
			UnitCommands_Type->ChangeValue("21");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 12)
		{
			UnitCommands_Type->ChangeValue("21");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 13)
		{
			UnitCommands_Type->ChangeValue("101");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 14)
		{
			UnitCommands_Type->ChangeValue("104");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 15)
		{
			UnitCommands_Type->ChangeValue("105");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 16)
		{
			UnitCommands_Type->ChangeValue("106");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 17)
		{
			UnitCommands_Type->ChangeValue("107");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 18)
		{
			UnitCommands_Type->ChangeValue("109");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 19)
		{
			UnitCommands_Type->ChangeValue("110");
			UnitCommands_SubType->ChangeValue("189");
		}
		else if(Selection == 20)
		{
			UnitCommands_Type->ChangeValue("110");
			UnitCommands_SubType->ChangeValue("190");
		}
		else if(Selection == 21)
		{
			UnitCommands_Type->ChangeValue("110");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 22)
		{
			UnitCommands_Type->ChangeValue("111");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 23)
		{
			UnitCommands_Type->ChangeValue("120");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 24)
		{
			UnitCommands_Type->ChangeValue("121");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 25)
		{
			UnitCommands_Type->ChangeValue("122");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 26)
		{
			UnitCommands_Type->ChangeValue("125");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 27)
		{
			UnitCommands_Type->ChangeValue("131");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 28)
		{
			UnitCommands_Type->ChangeValue("132");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 29)
		{
			UnitCommands_Type->ChangeValue("135");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 30)
		{
			UnitCommands_Type->ChangeValue("136");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else
		{
			UnitCommands_Type->ChangeValue("-1");
			UnitCommands_SubType->ChangeValue("-1");
		}
		
		wxFocusEvent Temp(wxEVT_KILL_FOCUS);
		UnitCommands_Type->OnKillFocus(Temp);
		UnitCommands_SubType->OnKillFocus(Temp);
		
		if(GameVersion > 1)
		{
			ListUnitCommands(UnitID, 0);
		}
		else
		{
			if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
			{
				wxCommandEvent E;
				OnUnitsCopy(E);
				OnUnitsPaste(E);
			}
			ListUnitCommands(UnitID, UnitCivID);
		}
	}
	for(short loop = 0;loop < 2;loop++)
	if(Event.GetId() == Units_Units_SearchFilters[loop]->GetId())
	{
		ListUnits(UnitCivID);
		Units_Units_Search->SetFocus();
	}
}

void AGE_Frame::OnKillFocus_Byte(wxFocusEvent& Event)
{
	((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Civs_GraphicSet->GetId())
		{
			ListCivs();
		}
	}
}

void AGE_Frame::OnKillFocus_ComboBoxByteEffectType(wxFocusEvent& Event)
{
	((ComboBox_Byte_EffectType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Effects_Type->GetId())
		{
			ListEffects(TechID);
		}
	}
}

void AGE_Frame::OnKillFocus_CheckBoxByte(wxFocusEvent& Event)
{
	((CheckBox_Byte*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Graphics_AttackSoundUsed->GetId())
		{
			if((GenieFile->Graphics[GraphicID].AttackSounds.size() != GenieFile->Graphics[GraphicID].AngleCount) && GenieFile->Graphics[GraphicID].AttackSoundUsed == 1)
			{
				GenieFile->Graphics[GraphicID].AttackSounds.resize(GenieFile->Graphics[GraphicID].AngleCount);
				
				wxCommandEvent E;
				OnGraphicsSelect(E);
			}
		}
	}
}

void AGE_Frame::OnKillFocus_ComboBoxShort(wxFocusEvent& Event)
{
	((ComboBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == GraphicDeltas_GraphicID->GetId())
		{
			ListGraphicDeltas(GraphicID);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_Byte(wxFocusEvent& Event)
{
	((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_ComboBoxByte(wxFocusEvent& Event)
{
	((ComboBox_Byte*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte(wxFocusEvent& Event)
{
	((CheckBox_Byte*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
	}
}

void AGE_Frame::OnKillFocus_Short(wxFocusEvent& Event)
{
	((TextCtrl_Short*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Research_LangDllName->GetId())
		{
			ListResearchs();
		}
		if(Event.GetId() == Research_LangDllDescription->GetId())
		{
			wxCommandEvent E;
			OnResearchSelect(E);
		}
		if(Event.GetId() == Effects_A->GetId())
		{
			wxCommandEvent E;
			OnEffectsSelect(E);
		}
		if(Event.GetId() == Effects_B->GetId())
		{
			wxCommandEvent E;
			OnEffectsSelect(E);
		}
		if(Event.GetId() == Effects_C->GetId())
		{
			wxCommandEvent E;
			OnEffectsSelect(E);
		}
	}
}

void AGE_Frame::OnKillFocus_UnShort(wxFocusEvent& Event)
{
	((TextCtrl_UnShort*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_UnShort*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Graphics_AngleCount->GetId())
		{
			if((GenieFile->Graphics[GraphicID].AttackSounds.size() != GenieFile->Graphics[GraphicID].AngleCount) && GenieFile->Graphics[GraphicID].AttackSoundUsed == 1)
			{
				GenieFile->Graphics[GraphicID].AttackSounds.resize(GenieFile->Graphics[GraphicID].AngleCount);
				
				wxCommandEvent E;
				OnGraphicsSelect(E);
			}
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_Short(wxFocusEvent& Event)
{
	((TextCtrl_Short*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
		if(Event.GetId() == Units_LanguageDllName->GetId())
		{
			ListUnits(UnitCivID);
		}
		if(Event.GetId() == Units_LanguageDllCreation->GetId())
		{
			wxCommandEvent E;
			OnUnitsSelect(E);
		}
		if(Event.GetId() == Units_LanguageDllHelp->GetId())
		{
			wxCommandEvent E;
			OnUnitsSelect(E);
		}
		if(Event.GetId() == DamageGraphics_DamagePercent->GetId())
		{
			ListUnitDamageGraphics(UnitID, UnitCivID);
		}
		if(Event.GetId() == Attacks_Amount->GetId())
		{
			ListUnitAttacks(UnitID, UnitCivID);
		}
		if(Event.GetId() == Armors_Amount->GetId())
		{
			ListUnitArmors(UnitID, UnitCivID);
		}
		if(Event.GetId() == UnitCommands_Type->GetId())
		{
			ListUnitCommands(UnitID, UnitCivID);
		}
		if(Event.GetId() == UnitCommands_SubType->GetId())
		{
			ListUnitCommands(UnitID, UnitCivID);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort(wxFocusEvent& Event)
{
	((ComboBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
		if(Event.GetId() == DamageGraphics_GraphicID->GetId())
		{
			ListUnitDamageGraphics(UnitID, UnitCivID);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_CheckBoxShort(wxFocusEvent& Event)
{
	((CheckBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_CheckBoxShortUnitSheepConversion(wxFocusEvent& Event)
{
	((CheckBox_Short_ZeroIsYes*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShortAttackType(wxFocusEvent& Event)
{
	((ComboBox_Short_AttackType*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
		if(Event.GetId() == Attacks_Class->GetId())
		{
			ListUnitAttacks(UnitID, UnitCivID);
		}
		if(Event.GetId() == Armors_Class->GetId())
		{
			ListUnitArmors(UnitID, UnitCivID);
		}
	}
}

void AGE_Frame::OnKillFocus_Long(wxFocusEvent& Event)
{
	((TextCtrl_Long*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Long*)Event.GetEventObject())->NoLoadList)
	{
		
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_Long(wxFocusEvent& Event)
{
	((TextCtrl_Long*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Long*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_ComboBoxLong(wxFocusEvent& Event)
{
	((ComboBox_Long*)((TextCtrl_Long*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Long*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
	}
}

void AGE_Frame::OnKillFocus_Float(wxFocusEvent& Event)
{
	((TextCtrl_Float*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Float*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Civs_ResourceValue->GetId())
		{
			ListResources(CivID);
		}
		if(Event.GetId() == Effects_D->GetId())
		{
			wxCommandEvent E;
			OnEffectsSelect(E);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_Float(wxFocusEvent& Event)
{
	((TextCtrl_Float*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Float*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
	}
}

void AGE_Frame::OnKillFocus_String(wxFocusEvent& Event)
{
	((TextCtrl_String*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_String*)Event.GetEventObject())->NoLoadList)
	{
		string ReducedName;
		if(Event.GetId() == Research_Name[0]->GetId())
		{
			ReducedName = GenieFile->Researchs[ResearchID].Name;
			ReducedName = ReducedName.substr(0, 29);
			GenieFile->Researchs[ResearchID].Name = ReducedName;
	
			ListResearchs();
		}
		if(Event.GetId() == Research_Name[1]->GetId())
		{
			ReducedName = GenieFile->Researchs[ResearchID].Name2;
			ReducedName = ReducedName.substr(0, 29);
			GenieFile->Researchs[ResearchID].Name2 = ReducedName;
	
		//	ListResearchs();
			wxCommandEvent E;
			OnResearchSelect(E);
		}
		if(Event.GetId() == Techs_Name->GetId())
		{
			ReducedName = GenieFile->Techages[TechID].Name;
			ReducedName = ReducedName.substr(0, GenieFile->Techages[TechID].getNameSize() - 1);
			GenieFile->Techages[TechID].Name = ReducedName;
			
			ListTechages();
		}
		if(Event.GetId() == Civs_Name[0]->GetId())
		{
			ReducedName = GenieFile->Civs[CivID].Name;
			ReducedName = ReducedName.substr(0, GenieFile->Civs[CivID].getNameSize() - 1);
			GenieFile->Civs[CivID].Name = ReducedName;
			
			ListCivs();
		}
		if(Event.GetId() == Civs_Name[1]->GetId())
		{
			ReducedName = GenieFile->Civs[CivID].Name2;
			ReducedName = ReducedName.substr(0, GenieFile->Civs[CivID].getNameSize() - 1);
			GenieFile->Civs[CivID].Name2 = ReducedName;
			
		//	ListCivs();
			wxCommandEvent E;
			OnCivsSelect(E);
		}
		if(Event.GetId() == Graphics_Name->GetId())
		{
			ReducedName = GenieFile->Graphics[GraphicID].Name;
			ReducedName = ReducedName.substr(0, GenieFile->Graphics[GraphicID].getNameSize() - 1);
			GenieFile->Graphics[GraphicID].Name = ReducedName;
			
			ListGraphics();
		}
		if(Event.GetId() == Graphics_Name2->GetId())
		{
			ReducedName = GenieFile->Graphics[GraphicID].Name2;
			ReducedName = ReducedName.substr(0, GenieFile->Graphics[GraphicID].getName2Size() - 1);
			GenieFile->Graphics[GraphicID].Name2 = ReducedName;
			
		//	ListGraphics();
			wxCommandEvent E;
			OnGraphicsSelect(E);
		}
		if(Event.GetId() == Terrains_Name->GetId())
		{
			ReducedName = GenieFile->Terrains[TerrainID].Name;
			ReducedName = ReducedName.substr(0, GenieFile->Terrains[TerrainID].getNameSize() - 1);
			GenieFile->Terrains[TerrainID].Name = ReducedName;
			
			ListTerrains();
		}
		if(Event.GetId() == Terrains_Name2->GetId())
		{
			ReducedName = GenieFile->Terrains[TerrainID].Name2;
			ReducedName = ReducedName.substr(0, GenieFile->Terrains[TerrainID].getNameSize() - 1);
			GenieFile->Terrains[TerrainID].Name2 = ReducedName;
			
		//	ListTerrains();
			wxCommandEvent E;
			OnTerrainsSelect(E);
		}
		if(Event.GetId() == SoundItems_Name->GetId())
		{
			ReducedName = GenieFile->Sounds[SoundID].Items[SoundItemID].FileName;
			ReducedName = ReducedName.substr(0, GenieFile->Sounds[SoundID].Items[SoundItemID].getFileNameSize() - 1);
			GenieFile->Sounds[SoundID].Items[SoundItemID].FileName = ReducedName;
			
			ListSoundItems(SoundID);
		}
		if(Event.GetId() == Colors_Name->GetId())
		{
			ListPlayerColors();
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_String(wxFocusEvent& Event)
{
	((TextCtrl_String*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_String*)Event.GetEventObject())->NoLoadList)
	{
		string ReducedName;
		if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
		{
			wxCommandEvent E;
			OnUnitsCopy(E);
			OnUnitsPaste(E);
		}
		if(Event.GetId() == Units_Name->GetId())
		{
			ReducedName = GenieFile->Civs[UnitCivID].Units[UnitID].Name;
			ReducedName = ReducedName.substr(0, 29);
			GenieFile->Civs[UnitCivID].Units[UnitID].Name = ReducedName;
	
			ListUnits(UnitCivID);
		}
		if(Event.GetId() == Units_Name2->GetId())
		{
			ReducedName = GenieFile->Civs[UnitCivID].Units[UnitID].Name2;
			ReducedName = ReducedName.substr(0, 29);
			GenieFile->Civs[UnitCivID].Units[UnitID].Name2 = ReducedName;
	
		//	ListUnits(UnitCivID);
			wxCommandEvent E;
			OnUnitsSelect(E);
		}
	}
}

void AGE_Frame::OnUpdate_ComboBoxByteEffectType(wxCommandEvent& Event)
{
	((ComboBox_Byte_EffectType*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == Effects_ComboBox_Type->GetId())
	{
		ListEffects(TechID);
	}
}

void AGE_Frame::OnUpdate_CheckBoxByte(wxCommandEvent& Event)
{
	((CheckBox_Byte*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == Graphics_CheckBox_AttackSoundUsed->GetId())
	{
		if((GenieFile->Graphics[GraphicID].AttackSounds.size() != GenieFile->Graphics[GraphicID].AngleCount) && GenieFile->Graphics[GraphicID].AttackSoundUsed == 1)
		{
			GenieFile->Graphics[GraphicID].AttackSounds.resize(GenieFile->Graphics[GraphicID].AngleCount);
			
			wxCommandEvent E;
			OnGraphicsSelect(E);
		}
	}
}

void AGE_Frame::OnUpdate_AutoCopy_ComboBoxByte(wxCommandEvent& Event)
{
	((ComboBox_Byte*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
	{
		wxCommandEvent E;
		OnUnitsCopy(E);
		OnUnitsPaste(E);
	}
}

void AGE_Frame::OnUpdate_ComboBoxShort(wxCommandEvent& Event)
{
	((ComboBox_Short*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == Effects_ComboBox_AttributesC->GetId())
	{
		wxCommandEvent E;
		OnEffectsSelect(E);
	}
	if(Event.GetId() == GraphicDeltas_ComboBox_GraphicID->GetId())
	{
		ListGraphicDeltas(GraphicID);
	}
}

void AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort(wxCommandEvent& Event)
{
	((ComboBox_Short*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
	{
		wxCommandEvent E;
		OnUnitsCopy(E);
		OnUnitsPaste(E);
	}
	if(Event.GetId() == DamageGraphics_ComboBox_GraphicID->GetId())
	{
		ListUnitDamageGraphics(UnitID, UnitCivID);
	}
}

void AGE_Frame::OnUpdate_AutoCopy_ComboBoxShortAttackType(wxCommandEvent& Event)
{
	((ComboBox_Short_AttackType*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
	{
		wxCommandEvent E;
		OnUnitsCopy(E);
		OnUnitsPaste(E);
	}
	if(Event.GetId() == Attacks_ComboBox_Class->GetId())
	{
		ListUnitAttacks(UnitID, UnitCivID);
	}
	if(Event.GetId() == Armors_ComboBox_Class->GetId())
	{
		ListUnitArmors(UnitID, UnitCivID);
	}
}

void AGE_Frame::OnUpdate_AutoCopy_ComboBoxLong(wxCommandEvent& Event)
{
	((ComboBox_Long*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
	{
		wxCommandEvent E;
		OnUnitsCopy(E);
		OnUnitsPaste(E);
	}
}

void AGE_Frame::OnUpdate_AutoCopy_CheckBoxByte(wxCommandEvent& Event)
{
	((CheckBox_Byte*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
	{
		wxCommandEvent E;
		OnUnitsCopy(E);
		OnUnitsPaste(E);
	}
}

void AGE_Frame::OnUpdate_CheckBoxShort(wxCommandEvent& Event)
{
	((CheckBox_Short*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == Effects_CheckBox_ModeB->GetId())
	{
		wxCommandEvent E;
		OnEffectsSelect(E);
	}
	if(Event.GetId() == Effects_CheckBox_ModeC->GetId())
	{
		wxCommandEvent E;
		OnEffectsSelect(E);
	}
}

void AGE_Frame::OnUpdate_AutoCopy_CheckBoxShort(wxCommandEvent& Event)
{
	((CheckBox_Short*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
	{
		wxCommandEvent E;
		OnUnitsCopy(E);
		OnUnitsPaste(E);
	}
}

void AGE_Frame::OnUpdate_AutoCopy_CheckBoxShortUnitSheepConversion(wxCommandEvent& Event)
{
	((CheckBox_Short_ZeroIsYes*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy == MenuOption_Include || AutoCopy == MenuOption_Exclude)
	{
		wxCommandEvent E;
		OnUnitsCopy(E);
		OnUnitsPaste(E);
	}
}

AGE_Frame::~AGE_Frame()
{
}
