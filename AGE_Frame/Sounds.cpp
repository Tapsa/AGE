#include "Common.h"
#include "../AGE_Frame.h"
#include "../Loaders.h"

std::vector<std::function<wxString(genie::SoundItem*)>> SoundItemFilterFunctions;

wxString AGE_Frame::GetSoundName(int sound)
{
    if(dataset->Sounds[sound].Items.empty()) return "Empty";
    else if(dataset->Sounds[sound].Items.size() == 1)
    return "File: " + GetSoundItemName(0, sound);
    else
    return "Files: " + FormatInt(dataset->Sounds[sound].Items.size());
}

void AGE_Frame::OnSoundsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListSounds(false);
}

void AGE_Frame::ListSounds(bool all)
{
    InitSounds(all);
    wxCommandEvent e;
    OnSoundSelect(e);
}

void AGE_Frame::InitSounds(bool all)
{
    InitSearch(Sounds_Sounds_Search->GetValue().MakeLower(), Sounds_Sounds_Search_R->GetValue().MakeLower());

    Sounds_Sounds_ListV->Sweep();
    if(all)
    {
        sound_names.Clear();
        sound_names.Alloc(1 + dataset->Sounds.size());
        sound_names.Add("-1 - None");
    }

    for(size_t loop = 0; loop < dataset->Sounds.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetSoundName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Sounds_Sounds_ListV->names.Add(Name);
            Sounds_Sounds_ListV->indexes.push_back(loop);
        }
        if (all)
        {
            sound_names.Add(Name);
        }
    }

    RefreshList(Sounds_Sounds_ListV, &SoundIDs);
    if (all)
    {
        for (AGEComboBox *list : SoundComboBoxList)
        {
            list->Flash();
        }
    }
}

void AGE_Frame::OnSoundSelect(wxCommandEvent &event)
{
    size_t selections = Sounds_Sounds_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Sounds_Sounds_ListV, SoundIDs);

    for (AGETextCtrl *box : uiGroupSound) box->clear();
    Sounds_ID->clear();

    genie::Sound * SoundPointer = 0;
    for(size_t loop = selections; loop--> 0;)
    {
        SoundPointer = &dataset->Sounds[SoundIDs[loop]];

        Sounds_ID->prepend(&SoundPointer->ID);
        Sounds_PlayDelay->prepend(&SoundPointer->PlayDelay);
        if(GenieVersion >= genie::GV_TEST)
        {
            Sounds_CacheTime->prepend(&SoundPointer->CacheTime);
            if(GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap ||
                GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
            {
                Sounds_TotalProbability->prepend(&SoundPointer->TotalProbability);
            }
        }
    }
    SetStatusText(wxString::Format("Selections: %zu    Selected sound: &d",
        selections, selections > 0 ? SoundIDs.front() : -1), 0);

    for (AGETextCtrl *box : uiGroupSound) box->update();
    Sounds_ID->refill();
    ListSoundItems();
}

void AGE_Frame::OnSoundsAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    AddToListIDFix(dataset->Sounds);
    ListSounds();
}

void AGE_Frame::OnSoundsInsert(wxCommandEvent &event)
{
    size_t selections = Sounds_Sounds_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToListIDFix(dataset->Sounds, SoundIDs.front());
    ListSounds();
}

void AGE_Frame::OnSoundsDelete(wxCommandEvent &event)
{
    size_t selections = Sounds_Sounds_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromListIDFix(dataset->Sounds, SoundIDs);
    ListSounds();
}

void AGE_Frame::OnSoundsCopy(wxCommandEvent &event)
{
    size_t selections = Sounds_Sounds_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Sounds, SoundIDs, copies.Sound);
    Sounds_Sounds_ListV->SetFocus();
}

void AGE_Frame::OnSoundsPaste(wxCommandEvent &event)
{
    size_t selections = Sounds_Sounds_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToListIDFix(dataset->Sounds, SoundIDs, copies.Sound);
    ListSounds();
}

void AGE_Frame::OnSoundsPasteInsert(wxCommandEvent &event)
{
    size_t selections = Sounds_Sounds_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListIDFix(dataset->Sounds, SoundIDs.front(), copies.Sound);
    ListSounds();
}

wxString AGE_Frame::GetSoundItemName(int item, int set, bool filter)
{
    wxString name;
    if (filter)
    {
        for (auto &f : SoundItemFilterFunctions)
        {
            name += f(&dataset->Sounds[set].Items[item]) + ", ";
        }
    }
    if (!dataset->Sounds[set].Items[item].FileName.empty())
    {
        return name + dataset->Sounds[set].Items[item].FileName;
    }
    return name + "NewFile.wav";
}

void AGE_Frame::PrepSoundItemSearch()
{
    SoundItemFilterFunctions.clear();
    for (size_t loop = 0; loop < 2; ++loop)
    {
        int selection = Sounds_Items_SearchFilters[loop]->GetSelection();
        if (selection < 1) continue;
        wxString label = soundfile_filters[selection];

        if (label.compare("DRS") == 0)
            SoundItemFilterFunctions.push_back([this](genie::SoundItem *item_ptr)
        {
            return "DRS " + FormatInt(item_ptr->ResourceID);
        });
        else if (label.compare("Probability") == 0)
            SoundItemFilterFunctions.push_back([this](genie::SoundItem *item_ptr)
        {
            return "P " + FormatInt(item_ptr->Probability);
        });
        else if (label.compare("Civilization") == 0)
            SoundItemFilterFunctions.push_back([this](genie::SoundItem *item_ptr)
        {
            return "C " + FormatInt(item_ptr->Civilization);
        });
        else if (label.compare("Icon Set") == 0)
            SoundItemFilterFunctions.push_back([this](genie::SoundItem *item_ptr)
        {
            return "IS " + FormatInt(item_ptr->IconSet);
        });
    }
}

void AGE_Frame::OnSoundItemsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListSoundItems();
}

void AGE_Frame::ListSoundItems()
{
    InitSearch(Sounds_Items_Search->GetValue().MakeLower(), Sounds_Items_Search_R->GetValue().MakeLower());
    SearchAnd = Sounds_Items_UseAnd[0]->GetValue();
    ExcludeAnd = Sounds_Items_UseAnd[1]->GetValue();
    PrepSoundItemSearch();

    Sounds_Items_ListV->Sweep();

    if(SoundIDs.size())
    for(size_t loop = 0; loop < dataset->Sounds[SoundIDs.front()].Items.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetSoundItemName(loop, SoundIDs.front(), true);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Sounds_Items_ListV->names.Add(Name);
            Sounds_Items_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(Sounds_Items_ListV, &SoundItemIDs);

    SearchAnd = ExcludeAnd = false;

    wxCommandEvent e;
    OnSoundItemSelect(e);
}

void AGE_Frame::OnSoundItemSelect(wxCommandEvent &event)
{
    if(!SoundIDs.empty())
    {
        size_t sum = 0;
        for (genie::SoundItem &file : dataset->Sounds[SoundIDs.front()].Items)
        {
            sum += file.Probability;
        }
        Sounds_TotalProbability_Info->SetLabel("Used "+lexical_cast<std::string>(sum)+"/"+lexical_cast<std::string>(dataset->Sounds[SoundIDs.front()].TotalProbability));
    }
    size_t selections = Sounds_Items_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    for (AGETextCtrl *box : uiGroupSoundFile) box->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, Sounds_Items_ListV, SoundItemIDs);

        genie::SoundItem * SoundItemPointer;
        for(size_t loop = selections; loop--> 0;)
        {
            SoundItemPointer = &dataset->Sounds[SoundIDs.front()].Items[SoundItemIDs[loop]];

            SoundItems_Name->prepend(&SoundItemPointer->FileName);
            SoundItems_Resource->prepend(&SoundItemPointer->ResourceID);
            SoundItems_Probability->prepend(&SoundItemPointer->Probability);
            if(GenieVersion >= genie::GV_AoKE3)
            {
                SoundItems_Civ->prepend(&SoundItemPointer->Civilization);
                SoundItems_IconSet->prepend(&SoundItemPointer->IconSet);
            }
        }
    }
    for (AGETextCtrl *box : uiGroupSoundFile) box->update();
}

void AGE_Frame::OnSoundItemsAdd(wxCommandEvent &event)
{
    size_t selections = Sounds_Sounds_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->Sounds[SoundIDs.front()].Items);
    ListSoundItems();
}

void AGE_Frame::OnSoundItemsInsert(wxCommandEvent &event)
{
    size_t selections = Sounds_Items_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->Sounds[SoundIDs.front()].Items, SoundItemIDs.front());
    ListSoundItems();
}

void AGE_Frame::OnSoundItemsDelete(wxCommandEvent &event)
{
    size_t selections = Sounds_Items_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->Sounds[SoundIDs.front()].Items, SoundItemIDs);
    ListSoundItems();
}

void AGE_Frame::OnSoundItemsCopy(wxCommandEvent &event)
{
    size_t selections = Sounds_Items_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Sounds[SoundIDs.front()].Items, SoundItemIDs, copies.SoundItem);
    Sounds_Items_ListV->SetFocus();
}

void AGE_Frame::OnSoundItemsPaste(wxCommandEvent &event)
{
    size_t selections = Sounds_Items_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Sounds[SoundIDs.front()].Items, SoundItemIDs, copies.SoundItem);
    ListSoundItems();
}

void AGE_Frame::OnSoundItemsPasteInsert(wxCommandEvent &event)
{
    size_t selections = Sounds_Items_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->Sounds[SoundIDs.front()].Items, SoundItemIDs.front(), copies.SoundItem);
    ListSoundItems();
}

void AGE_Frame::OnSoundItemsCopyToSounds(wxCommandEvent &event)
{
    for(size_t loop=1; loop < SoundIDs.size(); ++loop)
    {
        dataset->Sounds[SoundIDs[loop]].Items = dataset->Sounds[SoundIDs.front()].Items;
    }
}

void AGE_Frame::LoadAllSoundFiles(wxCommandEvent &event)
{
    InitSearch(Sounds_AllItems_Search->GetValue().MakeLower(), Sounds_AllItems_Search_R->GetValue().MakeLower());
    SearchAnd = Sounds_AllItems_UseAnd[0]->GetValue();
    ExcludeAnd = Sounds_AllItems_UseAnd[1]->GetValue();

    Sounds_AllItems_ListV->Sweep();

    for(short sound = 0; sound < dataset->Sounds.size(); ++sound)
    {
        for(short file = 0; file < dataset->Sounds[sound].Items.size(); ++file)
        {
            wxString Name = " S"+lexical_cast<std::string>(sound)+" F"+lexical_cast<std::string>(file)+" - "+GetSoundItemName(file, sound);
            if(SearchMatches(" " + Name.Lower() + " "))
            {
                Sounds_AllItems_ListV->names.Add(Name);
            }
        }
    }

    RefreshList(Sounds_AllItems_ListV);
    //Sounds_AllItems_ListV->SetFocus(); You need to check if searched or not.

    SearchAnd = ExcludeAnd = false;

    wxCommandEvent e;
    OnAllSoundFileSelect(e);
}

void AGE_Frame::ClearAllSoundFiles(wxCommandEvent &event)
{
    Sounds_Sounds_Search->SetValue("");
    Sounds_Items_Search->SetValue("");
}

void AGE_Frame::OnAllSoundFileSelect(wxCommandEvent &event)
{
    SearchAllSubVectors(Sounds_AllItems_ListV, Sounds_Sounds_Search, Sounds_Items_Search);
}

void AGE_Frame::CreateSoundControls()
{
    Sounds_Main = new wxBoxSizer(wxHORIZONTAL);
    Sounds_Sounds_Buttons = new wxGridSizer(3, 0, 0);
    Sounds_Items_Buttons = new wxGridSizer(3, 0, 0);
    Sounds_DataArea = new wxBoxSizer(wxVERTICAL);

    Tab_Sounds = new ATabPage(TabBar_Main);
    Sounds_Sounds = new wxStaticBoxSizer(wxVERTICAL, Tab_Sounds, "Sounds");
    Sounds_Sounds_Search = new wxTextCtrl(Tab_Sounds, wxID_ANY);
    Sounds_Sounds_Search_R = new wxTextCtrl(Tab_Sounds, wxID_ANY);
    Sounds_Sounds_ListV = new ProperList(Tab_Sounds, ASize(200, 100));
    Sounds_Add = new wxButton(Tab_Sounds, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Sounds_Insert = new wxButton(Tab_Sounds, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Sounds_Delete = new wxButton(Tab_Sounds, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Sounds_Copy = new wxButton(Tab_Sounds, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Sounds_Paste = new wxButton(Tab_Sounds, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Sounds_PasteInsert = new wxButton(Tab_Sounds, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));

    Sounds_Items = new wxStaticBoxSizer(wxVERTICAL, Tab_Sounds, "Sound Files");
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Sounds_Items_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
        Sounds_Items_SearchFilters[loop] = new AGEComboBox(Tab_Sounds, &soundfile_filters);
    }
    Sounds_Items_Search = new wxTextCtrl(Tab_Sounds, wxID_ANY);
    Sounds_Items_UseAnd[0] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And");
    Sounds_Items_Search_R = new wxTextCtrl(Tab_Sounds, wxID_ANY);
    Sounds_Items_UseAnd[1] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And");
    Sounds_Items_ListV = new ProperList(Tab_Sounds, ASize(200, 100));
    SoundItems_Add = new wxButton(Tab_Sounds, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    SoundItems_Insert = new wxButton(Tab_Sounds, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    SoundItems_Delete = new wxButton(Tab_Sounds, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    SoundItems_Copy = new wxButton(Tab_Sounds, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    SoundItems_Paste = new wxButton(Tab_Sounds, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    SoundItems_PasteInsert = new wxButton(Tab_Sounds, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    SoundItems_CopyToSounds = new wxButton(Tab_Sounds, wxID_ANY, "Copy all to selected sounds", wxDefaultPosition, wxSize(10, -1));

    Sounds_ID_Holder = new wxBoxSizer(wxVERTICAL);
    Sounds_ID_Text = new SolidText(Tab_Sounds, " Sound ID");
    Sounds_ID = new NumberControl(CShort, Tab_Sounds, this, nullptr);
    Sounds_PlayDelay_Holder = new wxBoxSizer(wxVERTICAL);
    Sounds_PlayDelay_Text = new SolidText(Tab_Sounds, " Play Delay");
    Sounds_PlayDelay = new NumberControl(CShort, Tab_Sounds, this, &uiGroupSound);
    Sounds_CacheTime_Holder = new wxBoxSizer(wxVERTICAL);
    Sounds_CacheTime_Text = new SolidText(Tab_Sounds, " Cache Time");
    Sounds_CacheTime = new NumberControl(CLong, Tab_Sounds, this, &uiGroupSound);
    Sounds_TotalProbability_Holder = new wxBoxSizer(wxHORIZONTAL);
    Sounds_TotalProbability_Text = new SolidText(Tab_Sounds, " Total Probability");
    Sounds_TotalProbability_Info = new SolidText(Tab_Sounds, " Used 0/100");
    Sounds_TotalProbability = new NumberControl(CShort, Tab_Sounds, this, &uiGroupSound);

    SoundItems_Name_Holder = new wxBoxSizer(wxVERTICAL);
    SoundItems_Name_Text = new SolidText(Tab_Sounds, " Filename");
    SoundItems_Name = new StringControl(Tab_Sounds, this, &uiGroupSoundFile, false);
    SoundItems_Resource_Holder = new wxBoxSizer(wxHORIZONTAL);
    SoundItems_Resource_Text = new SolidText(Tab_Sounds, " File DRS Resource");
    SoundItems_Resource = new NumberControl(CLong, Tab_Sounds, this, &uiGroupSoundFile, false);
    SoundFile_AutoIncrement = new wxButton(Tab_Sounds, wxID_ANY, "Auto # from 1st", wxDefaultPosition, wxSize(10, -1));
    SoundItems_Probability_Holder = new wxBoxSizer(wxHORIZONTAL);
    SoundItems_Probability_Text = new SolidText(Tab_Sounds, " File Probability");
    SoundItems_Probability = new NumberControl(CShort, Tab_Sounds, this, &uiGroupSoundFile, false);
    SoundFile_AutoProbability = new wxButton(Tab_Sounds, wxID_ANY, "Auto odds", wxDefaultPosition, wxSize(10, -1));
    SoundItems_Civ_Holder = new wxBoxSizer(wxVERTICAL);
    SoundItems_Civ_Text = new SolidText(Tab_Sounds, " File Civilization");
    SoundItems_Civ = new NumberControl(CShort, Tab_Sounds, this, &uiGroupSoundFile, false);
    SoundItems_Civ_ComboBox = new LinkedComboBox(Tab_Sounds, SoundItems_Civ, &civ_names);
    CivComboBoxList.push_back(SoundItems_Civ_ComboBox);
    SoundItems_IconSet_Holder = new wxBoxSizer(wxVERTICAL);
    SoundItems_IconSet_Text = new SolidText(Tab_Sounds, " File Icon Set");
    SoundItems_IconSet = new NumberControl(CShort, Tab_Sounds, this, &uiGroupSoundFile, false);
    wxSizer *SoundFile_Holder = new wxBoxSizer(wxHORIZONTAL);
    SoundFile_Loop = new wxCheckBox(Tab_Sounds, wxID_ANY, "Loop");
    SoundFile_Play = new wxButton(Tab_Sounds, wxID_ANY, "Play WAV", wxDefaultPosition, wxSize(10, -1));
    SoundFile_Stop = new wxButton(Tab_Sounds, wxID_ANY, "Stop WAV", wxDefaultPosition, wxSize(10, -1));
    SoundFile_Loop->SetValue(true);
    SoundFile_CopyCivToCiv = new wxButton(Tab_Sounds, wxID_ANY, "Copy sounds from civ to civ *", wxDefaultPosition, wxSize(10, -1));
    SoundFile_CopyCivToCiv->SetToolTip("Applies to all sounds");
    SourceCiv_Holder = new wxBoxSizer(wxHORIZONTAL);
    TargetCiv_Holder = new wxBoxSizer(wxHORIZONTAL);
    SolidText *SourceCiv_Text = new SolidText(Tab_Sounds, " Source ");
    SolidText *TargetCiv_Text = new SolidText(Tab_Sounds, " Target ");
    SoundFile_Source_Civ = new AGEComboBox(Tab_Sounds, &civ_names_only);
    SoundFile_Target_Civ = new AGEComboBox(Tab_Sounds, &civ_names_only);
    CivComboBoxList.push_back(SoundFile_Source_Civ);
    CivComboBoxList.push_back(SoundFile_Target_Civ);

    Sounds_AllItems = new wxStaticBoxSizer(wxVERTICAL, Tab_Sounds, "Files of all Sounds");
    Sounds_AllItems_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
    Sounds_AllItems_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
    Sounds_AllItems_Search = new wxTextCtrl(Tab_Sounds, wxID_ANY);
    Sounds_AllItems_UseAnd[0] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And");
    Sounds_AllItems_Search_R = new wxTextCtrl(Tab_Sounds, wxID_ANY);
    Sounds_AllItems_UseAnd[1] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And");
    Sounds_AllItems_ListV = new ProperList(Tab_Sounds, ASize(200, 100));
    Sounds_AllItems_Buttons = new wxBoxSizer(wxHORIZONTAL);
    Sounds_AllItems_Load = new wxButton(Tab_Sounds, wxID_ANY, "Reload", wxDefaultPosition, wxSize(10, -1));
    Sounds_AllItems_Clear = new wxButton(Tab_Sounds, wxID_ANY, "Clear *", wxDefaultPosition, wxSize(10, -1));
    Sounds_AllItems_Clear->SetToolTip("Clear the modified search texts");

    Sounds_Sounds_Buttons->Add(Sounds_Add, 1, wxEXPAND);
    Sounds_Sounds_Buttons->Add(Sounds_Delete, 1, wxEXPAND);
    Sounds_Sounds_Buttons->Add(Sounds_Insert, 1, wxEXPAND);
    Sounds_Sounds_Buttons->Add(Sounds_Copy, 1, wxEXPAND);
    Sounds_Sounds_Buttons->Add(Sounds_Paste, 1, wxEXPAND);
    Sounds_Sounds_Buttons->Add(Sounds_PasteInsert, 1, wxEXPAND);

    Sounds_Sounds->Add(Sounds_Sounds_Search, 0, wxEXPAND);
    Sounds_Sounds->Add(Sounds_Sounds_Search_R, 0, wxEXPAND);
    Sounds_Sounds->Add(Sounds_Sounds_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Sounds_Sounds->Add(Sounds_Sounds_Buttons, 0, wxEXPAND);

    Sounds_Items_Buttons->Add(SoundItems_Add, 1, wxEXPAND);
    Sounds_Items_Buttons->Add(SoundItems_Delete, 1, wxEXPAND);
    Sounds_Items_Buttons->Add(SoundItems_Insert, 1, wxEXPAND);
    Sounds_Items_Buttons->Add(SoundItems_Copy, 1, wxEXPAND);
    Sounds_Items_Buttons->Add(SoundItems_Paste, 1, wxEXPAND);
    Sounds_Items_Buttons->Add(SoundItems_PasteInsert, 1, wxEXPAND);

    Sounds_Items_Searches[0]->Add(Sounds_Items_Search, 1, wxEXPAND);
    Sounds_Items_Searches[0]->Add(Sounds_Items_UseAnd[0], 0, wxLEFT, 2);
    Sounds_Items_Searches[1]->Add(Sounds_Items_Search_R, 1, wxEXPAND);
    Sounds_Items_Searches[1]->Add(Sounds_Items_UseAnd[1], 0, wxLEFT, 2);
    Sounds_Items->Add(Sounds_Items_Searches[0], 0, wxEXPAND);
    Sounds_Items->Add(Sounds_Items_Searches[1], 0, wxEXPAND);
    Sounds_Items->Add(Sounds_Items_SearchFilters[0], 0, wxEXPAND);
    Sounds_Items->Add(Sounds_Items_SearchFilters[1], 0, wxEXPAND);
    Sounds_Items->Add(Sounds_Items_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Sounds_Items->Add(Sounds_Items_Buttons, 0, wxEXPAND);
    Sounds_Items->Add(SoundItems_CopyToSounds, 0, wxEXPAND | wxTOP, 2);

    Sounds_ID_Holder->Add(Sounds_ID_Text);
    Sounds_ID_Holder->Add(Sounds_ID);
    Sounds_PlayDelay_Holder->Add(Sounds_PlayDelay_Text);
    Sounds_PlayDelay_Holder->Add(Sounds_PlayDelay);
    Sounds_CacheTime_Holder->Add(Sounds_CacheTime_Text);
    Sounds_CacheTime_Holder->Add(Sounds_CacheTime);
    Sounds_TotalProbability_Holder->Add(Sounds_TotalProbability);
    Sounds_TotalProbability_Holder->Add(Sounds_TotalProbability_Info, 1, wxEXPAND | wxLEFT, 5);
    SoundItems_Name_Holder->Add(SoundItems_Name_Text);
    SoundItems_Name_Holder->Add(SoundItems_Name, 0, wxEXPAND);
    SoundItems_Resource_Holder->Add(SoundItems_Resource);
    SoundItems_Resource_Holder->Add(SoundFile_AutoIncrement, 1, wxEXPAND | wxLEFT, 5);
    SoundItems_Probability_Holder->Add(SoundItems_Probability);
    SoundItems_Probability_Holder->Add(SoundFile_AutoProbability, 1, wxEXPAND | wxLEFT, 5);
    SoundItems_Civ_Holder->Add(SoundItems_Civ_Text);
    SoundItems_Civ_Holder->Add(SoundItems_Civ, 0, wxEXPAND);
    SoundItems_Civ_Holder->Add(SoundItems_Civ_ComboBox);
    SoundItems_IconSet_Holder->Add(SoundItems_IconSet_Text);
    SoundItems_IconSet_Holder->Add(SoundItems_IconSet);

    Sounds_AllItems_Searches[0]->Add(Sounds_AllItems_Search, 1, wxEXPAND);
    Sounds_AllItems_Searches[0]->Add(Sounds_AllItems_UseAnd[0], 0, wxLEFT, 2);
    Sounds_AllItems_Searches[1]->Add(Sounds_AllItems_Search_R, 1, wxEXPAND);
    Sounds_AllItems_Searches[1]->Add(Sounds_AllItems_UseAnd[1], 0, wxLEFT, 2);
    Sounds_AllItems->Add(Sounds_AllItems_Searches[0], 0, wxEXPAND);
    Sounds_AllItems->Add(Sounds_AllItems_Searches[1], 0, wxEXPAND);
    Sounds_AllItems->Add(Sounds_AllItems_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Sounds_AllItems_Buttons->Add(Sounds_AllItems_Load, 2, wxEXPAND | wxRIGHT, 2);
    Sounds_AllItems_Buttons->Add(Sounds_AllItems_Clear, 1, wxEXPAND);
    Sounds_AllItems->Add(Sounds_AllItems_Buttons, 0, wxEXPAND);

    SourceCiv_Holder->Add(SourceCiv_Text);
    SourceCiv_Holder->Add(SoundFile_Source_Civ, 1, wxEXPAND);
    TargetCiv_Holder->Add(TargetCiv_Text);
    TargetCiv_Holder->Add(SoundFile_Target_Civ, 1, wxEXPAND);

    Sounds_DataArea->Add(Sounds_ID_Holder, 0, wxTOP, 5);
    Sounds_DataArea->Add(Sounds_PlayDelay_Holder, 0, wxTOP, 5);
    Sounds_DataArea->Add(Sounds_CacheTime_Holder, 0, wxTOP, 5);
    Sounds_DataArea->Add(Sounds_TotalProbability_Text, 0, wxTOP, 5);
    Sounds_DataArea->Add(Sounds_TotalProbability_Holder, 0, wxEXPAND);
    Sounds_DataArea->Add(SoundItems_Name_Holder, 0, wxEXPAND | wxTOP, 5);
    Sounds_DataArea->Add(SoundItems_Resource_Text, 0, wxTOP, 5);
    Sounds_DataArea->Add(SoundItems_Resource_Holder, 0, wxEXPAND);
    Sounds_DataArea->Add(SoundItems_Probability_Text, 0, wxTOP, 5);
    Sounds_DataArea->Add(SoundItems_Probability_Holder, 0, wxEXPAND);
    Sounds_DataArea->Add(SoundItems_Civ_Holder, 0, wxTOP, 5);
    Sounds_DataArea->Add(SoundItems_IconSet_Holder, 0, wxTOP, 5);
    SoundFile_Holder->Add(SoundFile_Loop);
    SoundFile_Holder->Add(SoundFile_Play, 1, wxEXPAND | wxLEFT, 5);
    SoundFile_Holder->Add(SoundFile_Stop, 1, wxEXPAND | wxLEFT, 5);
    Sounds_DataArea->Add(SoundFile_Holder, 0, wxEXPAND | wxTOP, 5);
    Sounds_DataArea->Add(SoundFile_CopyCivToCiv, 0, wxEXPAND | wxTOP, 5);
    Sounds_DataArea->Add(SourceCiv_Holder, 0, wxEXPAND | wxTOP, 5);
    Sounds_DataArea->Add(TargetCiv_Holder, 0, wxEXPAND | wxTOP, 5);

    Sounds_Main->Add(Sounds_Sounds, 1, wxEXPAND | wxALL, 5);
    Sounds_Main->Add(Sounds_Items, 1, wxEXPAND | wxRIGHT | wxTOP | wxBOTTOM, 5);
    Sounds_Main->Add(Sounds_DataArea, 0, wxRIGHT, 5);
    Sounds_Main->Add(Sounds_AllItems, 1, wxEXPAND | wxRIGHT | wxTOP | wxBOTTOM, 5);

    Sounds_ID->Enable(false);

    Tab_Sounds->SetSizer(Sounds_Main);

    for(size_t loop = 0; loop < 2; ++loop)
    {
        Sounds_Items_UseAnd[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnSoundItemsSearch, this);
        Sounds_Items_SearchFilters[loop]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnSelection_SearchFilters, this);
        Sounds_AllItems_UseAnd[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::LoadAllSoundFiles, this);
    }
    Sounds_Sounds_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnSoundSelect, this);
    Sounds_Sounds_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnSoundsSearch, this);
    Sounds_Sounds_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnSoundsSearch, this);
    Sounds_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundsAdd, this);
    Sounds_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundsInsert, this);
    Sounds_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundsDelete, this);
    Sounds_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundsCopy, this);
    Sounds_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundsPaste, this);
    Sounds_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundsPasteInsert, this);
    Sounds_Items_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnSoundItemSelect, this);
    Sounds_Items_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnSoundItemsSearch, this);
    Sounds_Items_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnSoundItemsSearch, this);
    SoundItems_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundItemsAdd, this);
    SoundItems_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundItemsInsert, this);
    SoundItems_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundItemsDelete, this);
    SoundItems_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundItemsCopy, this);
    SoundItems_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundItemsPaste, this);
    SoundItems_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundItemsPasteInsert, this);
    SoundItems_CopyToSounds->Bind(wxEVT_BUTTON, &AGE_Frame::OnSoundItemsCopyToSounds, this);
    Sounds_AllItems_Search->Bind(wxEVT_TEXT, &AGE_Frame::LoadAllSoundFiles, this);
    Sounds_AllItems_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::LoadAllSoundFiles, this);
    Sounds_AllItems_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnAllSoundFileSelect, this);
    Sounds_AllItems_Load->Bind(wxEVT_BUTTON, &AGE_Frame::LoadAllSoundFiles, this);
    Sounds_AllItems_Clear->Bind(wxEVT_BUTTON, &AGE_Frame::ClearAllSoundFiles, this);
    SoundFile_Play->Bind(wxEVT_BUTTON, &AGE_Frame::playWAV, this);
    SoundFile_Stop->Bind(wxEVT_BUTTON, &AGE_Frame::playWAV, this);
    SoundFile_AutoProbability->Bind(wxEVT_BUTTON, &AGE_Frame::autoOdds, this);
    SoundFile_AutoIncrement->Bind(wxEVT_BUTTON, &AGE_Frame::autoDrsIncrement, this);
    SoundFile_CopyCivToCiv->Bind(wxEVT_BUTTON, &AGE_Frame::copySoundsFromCivToCiv, this);

    for (AGETextCtrl *box : uiGroupSoundFile)
    {
        box->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Sounds, this);
        box->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Sounds, this);
    }
}

void AGE_Frame::OnEnter_Sounds(wxCommandEvent &event)
{
    static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
    ListSoundItems();
}

void AGE_Frame::OnKillFocus_Sounds(wxFocusEvent &event)
{
    event.Skip();
    if(static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() != 0) return;
    ListSoundItems();
}

void echo(sf::SoundBuffer &waves, sf::Sound &speaker, bool loop)
{
    if(waves.getSampleCount())
    {
        speaker.setBuffer(waves);
        speaker.play();
        speaker.setLoop(loop);
    }
}

void AGE_Frame::playWAV(wxCommandEvent &event)
{
    if(Sounds_Items_ListV->GetItemCount() > 1)
    Sounds_Items_ListV->SetFocus();
    else Sounds_Sounds_ListV->SetFocus();

    if(event.GetId() == SoundFile_Stop->GetId())
    {
        speaker.stop();
        return;
    }
    if(SoundItemIDs.size() && dataset && SoundItemIDs.front() < dataset->Sounds[SoundIDs.front()].Items.size())
    {
        bool loop = SoundFile_Loop->GetValue();
        genie::SoundItem &sound_item = dataset->Sounds[SoundIDs.front()].Items[SoundItemIDs.front()];
        if(LooseHD)
        {
            std::string soundname = GG::LoadSound(soundfolders, sound_item.FileName, sound_item.ResourceID);
            if("" != soundname && waves.loadFromFile(soundname))
            {
                echo(waves, speaker, loop); return;
            }
        }
        else
        {
            // Terrain sounds may be loose files.
            std::string soundname = GG::LoadSound(soundfolders, sound_item.FileName, sound_item.ResourceID);
            if("" != soundname && waves.loadFromFile(soundname))
            {
                echo(waves, speaker, loop); return;
            }
            const unsigned char* sounddata = GG::LoadSound(datafiles, sound_item.ResourceID);
            if(0 != sounddata)
            {
                size_t size = *((uint32_t*)sounddata + 1) + 8;
                if(waves.loadFromMemory(sounddata, size))
                {
                    echo(waves, speaker, loop); return;
                }
                wxMessageBox("Cannot load sound");
            }
        }
        wxMessageBox("No such sound");
    }
}

void AGE_Frame::autoOdds(wxCommandEvent &event)
{
    if(SoundIDs.empty() || dataset->Sounds[SoundIDs.front()].Items.empty()) return;
    wxBusyCursor WaitCursor;
    size_t fileCount = dataset->Sounds[SoundIDs.front()].Items.size();
    short odds = 100 / fileCount, extra = 100 - fileCount * odds;
    for(size_t file = 0; file < fileCount; ++file)
    dataset->Sounds[SoundIDs.front()].Items[file].Probability = odds;
    for(size_t file = 0; file < extra; ++file)
    ++dataset->Sounds[SoundIDs.front()].Items[file].Probability;
    ListSoundItems();
}

void AGE_Frame::autoDrsIncrement(wxCommandEvent &event)
{
    if(SoundIDs.empty() || dataset->Sounds[SoundIDs.front()].Items.empty()) return;
    wxBusyCursor WaitCursor;
    int32_t resourceID = dataset->Sounds[SoundIDs.front()].Items.front().ResourceID;
    for(size_t file = 1; file < dataset->Sounds[SoundIDs.front()].Items.size(); ++file)
    dataset->Sounds[SoundIDs.front()].Items[file].ResourceID = ++resourceID;
    ListSoundItems();
}

void AGE_Frame::copySoundsFromCivToCiv(wxCommandEvent &event)
{
    int16_t sourceCiv = SoundFile_Source_Civ->GetSelection(),
        targetCiv = SoundFile_Target_Civ->GetSelection();
    if(sourceCiv == targetCiv) return;
    wxBusyCursor WaitCursor;
    for (genie::Sound &sound : dataset->Sounds)
    {
        std::vector<size_t> targets;
        std::vector<genie::SoundItem> soundCopies;
        for(size_t file = 0; file < sound.Items.size(); ++file)
        {
            if(sound.Items[file].Civilization == sourceCiv)
            {
                soundCopies.emplace_back(sound.Items[file]);
                soundCopies.back().Civilization = targetCiv;
            }
            else if(sound.Items[file].Civilization == targetCiv)
            {
                targets.emplace_back(file);
            }
        }
        if(soundCopies.size() == targets.size())
        {
            for(size_t file = 0; file < targets.size(); ++file)
            {
                sound.Items[targets[file]] = soundCopies[file];
            }
        }
        else
        {
            DeleteFromList(sound.Items, targets);
            sound.Items.insert(sound.Items.end(), soundCopies.begin(), soundCopies.end());
        }
    }
    ListSoundItems();
}
