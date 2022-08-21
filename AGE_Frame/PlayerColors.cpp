#include "Common.h"
#include "../AGE_Frame.h"
#include "genie/resource/Color.h"

void AGE_Frame::OnPlayerColorsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListPlayerColors();
}

wxString AGE_Frame::GetPlayerColorName(int index)
{
    if(GenieVersion < genie::GV_AoKE3)
        return dataset->PlayerColours[index].Name;
    return "Color "+lexical_cast<std::string>(index);
}

void AGE_Frame::ListPlayerColors()
{
    InitPlayerColors();
    wxCommandEvent e;
    OnPlayerColorSelect(e);
}

void AGE_Frame::InitPlayerColors()
{
    InitSearch(Colors_Colors_Search->GetValue().MakeLower(), Colors_Colors_Search_R->GetValue().MakeLower());

    Colors_Colors_ListV->Sweep();
    color_names.Clear();
    color_names.Alloc(1 + dataset->PlayerColours.size());
    color_names.Add("-1 - None");

    for(size_t loop = 0; loop < dataset->PlayerColours.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetPlayerColorName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Colors_Colors_ListV->names.Add(Name);
            Colors_Colors_ListV->indexes.push_back(loop);
        }
        color_names.Add(Name);
    }

    RefreshList(Colors_Colors_ListV, &ColorIDs);
    Graphics_PlayerColor_ComboBox->Flash();
    Colors_ReferenceID_ComboBox->Flash();
}

void AGE_Frame::OnPlayerColorSelect(wxCommandEvent &event)
{
    size_t selections = Colors_Colors_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Colors_Colors_ListV, ColorIDs);

    for (AGETextCtrl *box : uiGroupColor) box->clear();
    Colors_ID->clear();

    genie::PlayerColour * PlayerColorPointer = 0;
    for(size_t loop = selections; loop--> 0;)
    {
        PlayerColorPointer = &dataset->PlayerColours[ColorIDs[loop]];

        Colors_ID->prepend(&PlayerColorPointer->ID);
        Colors_MinimapColor->prepend(&PlayerColorPointer->MinimapColour);
        if(GenieVersion < genie::GV_AoKE3)  //  AoE and RoR
        {
            Colors_Name->prepend(&PlayerColorPointer->Name);
            Colors_ResourceID->prepend(&PlayerColorPointer->ResourceID);
            Colors_Type->prepend(&PlayerColorPointer->Type);
        }
        else    //  Above AoE and RoR
        {
            Colors_PlayerPalette->prepend(&PlayerColorPointer->PlayerColorBase);
            Colors_OutlineColor->prepend(&PlayerColorPointer->UnitOutlineColor);
            Colors_SelectionColor1->prepend(&PlayerColorPointer->UnitSelectionColor1);
            Colors_SelectionColor2->prepend(&PlayerColorPointer->UnitSelectionColor2);
            Colors_MinimapColor2->prepend(&PlayerColorPointer->MinimapColor2);
            Colors_MinimapColor3->prepend(&PlayerColorPointer->MinimapColor3);
            Colors_ReferenceID->prepend(&PlayerColorPointer->StatisticsText);
        }
    }
    SetStatusText(wxString::Format("Selections: %zu    Selected color: %d",
        selections, selections > 0 ? ColorIDs.front() : -1), 0);

    for (AGETextCtrl *box : uiGroupColor) box->update();
    Colors_ID->refill();
    if(PlayerColorPointer && !palettes.empty() && !palettes.front().empty())
    {
        genie::Color minimap = palettes.front()[(uint8_t)PlayerColorPointer->MinimapColour];
        setForeAndBackColors(Colors_MinimapColor, wxColour(minimap.r, minimap.g, minimap.b));

        if(GenieVersion < genie::GV_AoKE3)
        {
            playerColorStart = uint8_t(16 * (1 + ColorIDs.front()));
        }
        else
        {
            playerColorID = (uint8_t)PlayerColorPointer->UnitOutlineColor;
            playerColorStart = (uint8_t)PlayerColorPointer->PlayerColorBase;

            genie::Color playerColor = palettes.front()[playerColorID];
            genie::Color paletteStart = palettes.front()[playerColorStart];
            genie::Color minimap2 = palettes.front()[(uint8_t)PlayerColorPointer->MinimapColor2];
            genie::Color minimap3 = palettes.front()[(uint8_t)PlayerColorPointer->MinimapColor3];
            genie::Color selection1 = palettes.front()[(uint8_t)PlayerColorPointer->UnitSelectionColor1];
            genie::Color selection2 = palettes.front()[(uint8_t)PlayerColorPointer->UnitSelectionColor2];

            setForeAndBackColors(Colors_OutlineColor, wxColour(playerColor.r, playerColor.g, playerColor.b));
            setForeAndBackColors(Colors_PlayerPalette, wxColour(paletteStart.r, paletteStart.g, paletteStart.b));
            setForeAndBackColors(Colors_SelectionColor1, wxColour(selection1.r, selection1.g, selection1.b));
            setForeAndBackColors(Colors_SelectionColor2, wxColour(selection2.r, selection2.g, selection2.b));
            setForeAndBackColors(Colors_MinimapColor2, wxColour(minimap2.r, minimap2.g, minimap2.b));
            setForeAndBackColors(Colors_MinimapColor3, wxColour(minimap3.r, minimap3.g, minimap3.b));
        }
    }
}

void AGE_Frame::setForeAndBackColors(AGETextCtrl *box, wxColour color)
{
    box->SetBackgroundColour(color);
    if(color.Red() / 2 + 2 * color.Green() + color.Blue() > 384)
    box->SetForegroundColour(wxColour(0, 0, 0));
    else box->SetForegroundColour(wxColour(255, 255, 255));
}

void AGE_Frame::OnDrawPalette(wxPaintEvent &event)
{
    wxBufferedPaintDC dc(Colors_Palette_Display);
    dc.Clear();
    if (paletteView >= palettes.size() || palettes[paletteView].size() < 256)
        return;

    std::vector<uint8_t> rgbdata(768);
    uint8_t *val = rgbdata.data();
    for (int i = 0; i < 256; ++i)
    {
        genie::Color rgba = palettes[paletteView][i];
        *val++ = rgba.r;
        *val++ = rgba.g;
        *val++ = rgba.b;
    }
    unsigned char *pic = (unsigned char *)rgbdata.data();
    wxBitmap bitmap = wxBitmap(wxImage(16, 16, pic, true).Scale(320, 320), 24);
    assert(bitmap.IsOk());
    dc.DrawBitmap(bitmap, 15, 15, true);
}

void AGE_Frame::OnPlayerColorsAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    AddToListIDFix(dataset->PlayerColours);
    ListPlayerColors();
}

void AGE_Frame::OnPlayerColorsInsert(wxCommandEvent &event)
{
    size_t selections = Colors_Colors_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToListIDFix(dataset->PlayerColours, ColorIDs.front());
    ListPlayerColors();
}

void AGE_Frame::OnPlayerColorsDelete(wxCommandEvent &event)
{
    size_t selections = Colors_Colors_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromListIDFix(dataset->PlayerColours, ColorIDs);
    ListPlayerColors();
}

void AGE_Frame::OnPlayerColorsCopy(wxCommandEvent &event)
{
    size_t selections = Colors_Colors_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->PlayerColours, ColorIDs, copies.PlayerColor);
    Colors_Colors_ListV->SetFocus();
    if(palettes.size())
    {
        paletteView = (paletteView + 1) % palettes.size();
        Colors_Palette_Display->Refresh();
    }
}

void AGE_Frame::OnPlayerColorsPaste(wxCommandEvent &event)
{
    size_t selections = Colors_Colors_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToListIDFix(dataset->PlayerColours, ColorIDs, copies.PlayerColor);
    ListPlayerColors();
}

void AGE_Frame::OnPlayerColorsPasteInsert(wxCommandEvent &event)
{
    size_t selections = Colors_Colors_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListIDFix(dataset->PlayerColours, ColorIDs.front(), copies.PlayerColor);
    ListPlayerColors();
}

void AGE_Frame::CreatePlayerColorControls()
{
    Colors_Main = new wxBoxSizer(wxHORIZONTAL);
    Tab_PlayerColors = new ATabPage(TabBar_Main);

    Colors_Colors = new wxStaticBoxSizer(wxVERTICAL, Tab_PlayerColors, "Player Colors");
    Colors_Colors_Search = new wxTextCtrl(Tab_PlayerColors, wxID_ANY);
    Colors_Colors_Search_R = new wxTextCtrl(Tab_PlayerColors, wxID_ANY);
    Colors_Colors_ListV = new ProperList(Tab_PlayerColors, ASize(200, 100));
    Colors_Colors_Buttons = new wxGridSizer(3, 0, 0);
    Colors_Add = new wxButton(Tab_PlayerColors, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Colors_Insert = new wxButton(Tab_PlayerColors, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Colors_Delete = new wxButton(Tab_PlayerColors, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Colors_Copy = new wxButton(Tab_PlayerColors, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Colors_Paste = new wxButton(Tab_PlayerColors, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Colors_PasteInsert = new wxButton(Tab_PlayerColors, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));

    const wxString COL_TT = "Index of the main color palette";
    Colors_DataArea = new wxBoxSizer(wxVERTICAL);
    Colors_WrapArea = new wxWrapSizer();
    Colors_Name_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_ID_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_ResourceID_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_PlayerPalette_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_OutlineColor_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_MinimapColor_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_SelectionColor1_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_SelectionColor2_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_MinimapColor2_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_MinimapColor3_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_Type_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_ReferenceID_Holder = new wxBoxSizer(wxVERTICAL);
    Colors_Name_Text = new SolidText(Tab_PlayerColors, " Filename");
    Colors_ID_Text = new SolidText(Tab_PlayerColors, " ID");
    Colors_ResourceID_Text = new SolidText(Tab_PlayerColors, "DRS Resource *");
    Colors_PlayerPalette_Text = new SolidText(Tab_PlayerColors, " Player Color Base *");
    Colors_OutlineColor_Text = new SolidText(Tab_PlayerColors, " Outline Color *");
    Colors_SelectionColor1_Text = new SolidText(Tab_PlayerColors, " Select Color 1 *");
    Colors_SelectionColor2_Text = new SolidText(Tab_PlayerColors, " Select Color 2 *");
    Colors_MinimapColor_Text = new SolidText(Tab_PlayerColors, " Minimap Color *");
    Colors_MinimapColor2_Text = new SolidText(Tab_PlayerColors, " Minimap Color 2 *");
    Colors_MinimapColor3_Text = new SolidText(Tab_PlayerColors, " Minimap Color 3 *");
    Colors_Type_Text = new SolidText(Tab_PlayerColors, " Type *");
    Colors_ReferenceID_Text = new SolidText(Tab_PlayerColors, " Statistics Text");
    Colors_Name = new StringControl(Tab_PlayerColors, this, &uiGroupColor, 30, false);
    Colors_ID = new NumberControl(CLong, Tab_PlayerColors, this, nullptr);
    Colors_ResourceID = new NumberControl(CShort, Tab_PlayerColors, this, &uiGroupColor);
    Colors_ResourceID->SetToolTip("Unused");
    Colors_PlayerPalette = new NumberControl(CLong, Tab_PlayerColors, this, &uiGroupColor);
    Colors_PlayerPalette->SetToolTip("Starting index of the main color palette\nfrom where 8 colors are dedicated to this player color");
    Colors_OutlineColor = new NumberControl(CLong, Tab_PlayerColors, this, &uiGroupColor);
    Colors_OutlineColor->SetToolTip(COL_TT);
    Colors_MinimapColor = new NumberControl(CLong, Tab_PlayerColors, this, &uiGroupColor);
    Colors_MinimapColor->SetToolTip(COL_TT);
    Colors_MinimapColor2 = new NumberControl(CLong, Tab_PlayerColors, this, &uiGroupColor);
    Colors_MinimapColor2->SetToolTip("Unused");
    Colors_MinimapColor3 = new NumberControl(CLong, Tab_PlayerColors, this, &uiGroupColor);
    Colors_MinimapColor3->SetToolTip("Unused");
    Colors_SelectionColor1 = new NumberControl(CLong, Tab_PlayerColors, this, &uiGroupColor);
    Colors_SelectionColor1->SetToolTip("Unused");
    Colors_SelectionColor2 = new NumberControl(CLong, Tab_PlayerColors, this, &uiGroupColor);
    Colors_SelectionColor2->SetToolTip("Unused");
    Colors_Type = new NumberControl(CUByte, Tab_PlayerColors, this, &uiGroupColor);
    Colors_Type->SetToolTip("0   Transform\n1   Transform player color\n2   Shadow\n3   Translucent");
    Colors_ReferenceID = new NumberControl(CLong, Tab_PlayerColors, this, &uiGroupColor);
    Colors_ReferenceID_ComboBox = new LinkedComboBox(Tab_PlayerColors, Colors_ReferenceID, &color_names);
    Colors_Palette_Display = new APanel(Tab_PlayerColors, ASize(256, 256));

    Colors_Colors_Buttons->Add(Colors_Add, 1, wxEXPAND);
    Colors_Colors_Buttons->Add(Colors_Delete, 1, wxEXPAND);
    Colors_Colors_Buttons->Add(Colors_Insert, 1, wxEXPAND);
    Colors_Colors_Buttons->Add(Colors_Copy, 1, wxEXPAND);
    Colors_Colors_Buttons->Add(Colors_Paste, 1, wxEXPAND);
    Colors_Colors_Buttons->Add(Colors_PasteInsert, 1, wxEXPAND);

    Colors_Colors->Add(Colors_Colors_Search, 0, wxEXPAND);
    Colors_Colors->Add(Colors_Colors_Search_R, 0, wxEXPAND);
    Colors_Colors->Add(Colors_Colors_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Colors_Colors->Add(Colors_Colors_Buttons, 0, wxEXPAND);

    Colors_Name_Holder->Add(Colors_Name_Text);
    Colors_Name_Holder->Add(Colors_Name, 0, wxRESERVE_SPACE_EVEN_IF_HIDDEN | wxRIGHT, 5);
    Colors_ID_Holder->Add(Colors_ID_Text);
    Colors_ID_Holder->Add(Colors_ID);
    Colors_ResourceID_Holder->Add(Colors_ResourceID_Text);
    Colors_ResourceID_Holder->Add(Colors_ResourceID);
    Colors_PlayerPalette_Holder->Add(Colors_PlayerPalette_Text);
    Colors_PlayerPalette_Holder->Add(Colors_PlayerPalette);
    Colors_OutlineColor_Holder->Add(Colors_OutlineColor_Text);
    Colors_OutlineColor_Holder->Add(Colors_OutlineColor);
    Colors_MinimapColor_Holder->Add(Colors_MinimapColor_Text);
    Colors_MinimapColor_Holder->Add(Colors_MinimapColor);
    Colors_SelectionColor1_Holder->Add(Colors_SelectionColor1_Text);
    Colors_SelectionColor1_Holder->Add(Colors_SelectionColor1);
    Colors_SelectionColor2_Holder->Add(Colors_SelectionColor2_Text);
    Colors_SelectionColor2_Holder->Add(Colors_SelectionColor2);
    Colors_MinimapColor2_Holder->Add(Colors_MinimapColor2_Text);
    Colors_MinimapColor2_Holder->Add(Colors_MinimapColor2);
    Colors_MinimapColor3_Holder->Add(Colors_MinimapColor3_Text);
    Colors_MinimapColor3_Holder->Add(Colors_MinimapColor3);
    Colors_Type_Holder->Add(Colors_Type_Text);
    Colors_Type_Holder->Add(Colors_Type);
    Colors_ReferenceID_Holder->Add(Colors_ReferenceID_Text);
    Colors_ReferenceID_Holder->Add(Colors_ReferenceID, 1, wxEXPAND);
    Colors_ReferenceID_Holder->Add(Colors_ReferenceID_ComboBox);

    Colors_DataArea->Add(Colors_Name_Holder, 0, wxTOP | wxRIGHT | wxLEFT, 5);
    Colors_WrapArea->Add(Colors_ID_Holder, 0, wxTOP | wxLEFT, 5);
    Colors_WrapArea->Add(Colors_ResourceID_Holder, 0, wxTOP | wxLEFT, 5);
    Colors_WrapArea->Add(Colors_PlayerPalette_Holder, 0, wxTOP | wxLEFT, 5);
    Colors_WrapArea->Add(Colors_OutlineColor_Holder, 0, wxTOP | wxLEFT, 5);
    Colors_WrapArea->Add(Colors_MinimapColor_Holder, 0, wxTOP | wxLEFT, 5);
    Colors_WrapArea->Add(Colors_MinimapColor2_Holder, 0, wxTOP | wxLEFT, 5);
    Colors_WrapArea->Add(Colors_MinimapColor3_Holder, 0, wxTOP | wxLEFT, 5);
    Colors_WrapArea->Add(Colors_SelectionColor1_Holder, 0, wxTOP | wxLEFT, 5);
    Colors_WrapArea->Add(Colors_SelectionColor2_Holder, 0, wxTOP | wxLEFT, 5);
    Colors_WrapArea->Add(Colors_Type_Holder, 0, wxTOP | wxLEFT, 5);
    Colors_WrapArea->Add(Colors_ReferenceID_Holder, 0, wxTOP | wxLEFT, 5);
    Colors_DataArea->Add(Colors_WrapArea, 0, wxTOP, 5);

    Colors_Main->Add(Colors_Colors, 1, wxEXPAND | wxTOP | wxLEFT | wxBOTTOM, 5);
    Colors_Main->Add(Colors_DataArea);
    Colors_Main->Add(Colors_Palette_Display, 2, wxEXPAND);

    Colors_ID->Enable(false);

    Tab_PlayerColors->SetSizer(Colors_Main);

    Colors_Colors_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnPlayerColorsSearch, this);
    Colors_Colors_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnPlayerColorsSearch, this);
    Colors_Colors_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnPlayerColorSelect, this);
    Colors_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnPlayerColorsAdd, this);
    Colors_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnPlayerColorsInsert, this);
    Colors_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnPlayerColorsDelete, this);
    Colors_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnPlayerColorsCopy, this);
    Colors_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnPlayerColorsPaste, this);
    Colors_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnPlayerColorsPasteInsert, this);
    Colors_Name->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Colors, this);
    Colors_Name->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Colors, this);
    Colors_Palette_Display->Bind(wxEVT_PAINT, &AGE_Frame::OnDrawPalette, this);
    Colors_Palette_Display->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&){});
}

void AGE_Frame::OnEnter_Colors(wxCommandEvent &event)
{
    static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
    ListPlayerColors();
}

void AGE_Frame::OnKillFocus_Colors(wxFocusEvent &event)
{
    event.Skip();
    if(static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() != 0) return;
    ListPlayerColors();
}
