#include "../AGE_Frame.h"

void AGE_Frame::ListMapData()
{
	wxCommandEvent E;
	OnMapsRefresh(E);
}

void AGE_Frame::OnVariableCalc(wxFocusEvent &event)
{
	event.Skip();
	int32_t Result, Temp;

	if(!General_CalcBoxes[0]->IsEmpty())
	{
		try{Result = lexical_cast<int32_t>(General_CalcBoxes[0]->GetValue());}
		catch(bad_lexical_cast e){return;}
	}
	else Result = 0;
	Result = (uint8_t)Result;

	if(!General_CalcBoxes[1]->IsEmpty())
	{
		try{Temp = lexical_cast<int32_t>(General_CalcBoxes[1]->GetValue());}
		catch(bad_lexical_cast e){return;}
	}
	else Temp = 0;
	Result += (uint8_t)Temp << 8;

	if(!General_CalcBoxes[2]->IsEmpty())
	{
		try{Temp = lexical_cast<int32_t>(General_CalcBoxes[2]->GetValue());}
		catch(bad_lexical_cast e){return;}
	}
	else Temp = 0;
	Result += (uint8_t)Temp << 16;

	if(!General_CalcBoxes[3]->IsEmpty())
	{
		try{Temp = lexical_cast<int32_t>(General_CalcBoxes[3]->GetValue());}
		catch(bad_lexical_cast e){return;}
	}
	else Temp = 0;
	Result += (uint8_t)Temp << 24;

	General_CalcBoxes[4]->ChangeValue(lexical_cast<string>(Result));
}

void AGE_Frame::OnVariableCalcReverse(wxFocusEvent &event)
{
	event.Skip();
	if(General_CalcBoxes[4]->IsEmpty()) return;

	int32_t Result;
	try{Result = lexical_cast<int32_t>(General_CalcBoxes[4]->GetValue());}
	catch(bad_lexical_cast e){return;}

	General_CalcBoxes[0]->ChangeValue(lexical_cast<string>((short)(int8_t)Result));
	Result >>= 8;
	General_CalcBoxes[1]->ChangeValue(lexical_cast<string>((short)(int8_t)Result));
	Result >>= 8;
	General_CalcBoxes[2]->ChangeValue(lexical_cast<string>((short)(int8_t)Result));
	Result >>= 8;
	General_CalcBoxes[3]->ChangeValue(lexical_cast<string>((short)(int8_t)Result));
}

void AGE_Frame::OnMapsRefresh(wxCommandEvent &event)
{
    for(auto &box: uiGroupMaps) box->clear();
	General_MapPointer->prepend(&dataset->TerrainBlock.MapPointer);
	General_Unknown1->prepend(&dataset->TerrainBlock.Unknown1);
	General_MapWidth->prepend(&dataset->TerrainBlock.MapWidth);
	General_MapHeight->prepend(&dataset->TerrainBlock.MapHeight);
	General_WorldWidth->prepend(&dataset->TerrainBlock.WorldWidth);
	General_WorldHeight->prepend(&dataset->TerrainBlock.WorldHeight);
	if(GenieVersion >= genie::GV_AoE)
	{
		General_Unknown2->prepend(&dataset->TerrainBlock.Unknown2);
	}
	for(size_t loop = 0, slot = 0; loop < genie::SharedTerrain::TILE_TYPE_COUNT; ++loop)
	{
		General_TileSizes[slot++]->prepend(&dataset->TerrainBlock.TileSizes[loop].Width);
		General_TileSizes[slot++]->prepend(&dataset->TerrainBlock.TileSizes[loop].Height);
		if(GenieVersion >= genie::GV_AoE)
		{
			General_TileSizes[slot++]->prepend(&dataset->TerrainBlock.TileSizes[loop].DeltaY);
		}
		else
		{
			++slot;
		}
	}

	UnknownPointer1->prepend(&dataset->TerrainBlock.UnknownPointer1);
	if(GenieVersion >= genie::GV_AoKA)
	{
		MapMinX->prepend(&dataset->TerrainBlock.MapMinX);
		MapMinY->prepend(&dataset->TerrainBlock.MapMinY);
		MapMaxX->prepend(&dataset->TerrainBlock.MapMaxX);
		MapMaxY->prepend(&dataset->TerrainBlock.MapMaxY);
	}
	if(GenieVersion >= genie::GV_AoK)
	{
		MapMaxXplus1->prepend(&dataset->TerrainBlock.MapMaxXplus1);
		MapMaxYplus1->prepend(&dataset->TerrainBlock.MapMaxYplus1);
	}
	MaxTerrain->prepend(&dataset->TerrainBlock.MaxTerrain);
	TileWidth->prepend(&dataset->TerrainBlock.TileWidth);
	TileHeight->prepend(&dataset->TerrainBlock.TileHeight);
	TileHalfHeight->prepend(&dataset->TerrainBlock.TileHalfHeight);
	TileHalfWidth->prepend(&dataset->TerrainBlock.TileHalfWidth);
	ElevHeight->prepend(&dataset->TerrainBlock.ElevHeight);
	CurRow->prepend(&dataset->TerrainBlock.CurRow);
	CurCol->prepend(&dataset->TerrainBlock.CurCol);
	BlockBegRow->prepend(&dataset->TerrainBlock.BlockBegRow);
	BlockEndRow->prepend(&dataset->TerrainBlock.BlockEndRow);
	BlockBegCol->prepend(&dataset->TerrainBlock.BlockBegCol);
	BlockEndCol->prepend(&dataset->TerrainBlock.BlockEndCol);
	UnknownPointer2->prepend(&dataset->TerrainBlock.UnknownPointer2);
	UnknownPointer3->prepend(&dataset->TerrainBlock.UnknownPointer3);
	AnyFrameChange->prepend(&dataset->TerrainBlock.AnyFrameChange);
	MapVisibleFlag->prepend(&dataset->TerrainBlock.MapVisibleFlag);
	FogFlag->prepend(&dataset->TerrainBlock.FogFlag);

	for(size_t loop = 0; loop < dataset->TerrainBlock.SomeBytes.size(); ++loop)
	{
		General_SomeBytes[loop]->prepend(&dataset->TerrainBlock.SomeBytes[loop]);
	}
	for(size_t loop = 0; loop < dataset->TerrainBlock.SomeInt32.size(); ++loop)
	{
		General_Something[loop]->prepend(&dataset->TerrainBlock.SomeInt32[loop]);
	}
	Unknown_UnknownPointer->prepend(&dataset->RandomMaps.RandomMapPointer);
	if(GenieVersion >= genie::GV_AoKA)
    {
        for(long loop = 0;loop < General_TTUnknown.size(); ++loop)
        {
            General_TTUnknown[loop]->prepend(&dataset->UnknownPreTechTree[loop]);
        }
        General_TTUnknown[7]->prepend(&dataset->TechTree.Unknown2);
        if(GenieVersion >= genie::GV_SWGB)
        {
            General_SUnknown2->prepend(&dataset->SUnknown2);
            General_SUnknown3->prepend(&dataset->SUnknown3);
            General_SUnknown4->prepend(&dataset->SUnknown4);
            General_SUnknown5->prepend(&dataset->SUnknown5);
            General_SUnknown7->prepend(&dataset->SUnknown7);
            General_SUnknown8->prepend(&dataset->SUnknown8);
        }
	}
    for(auto &box: uiGroupMaps) box->update();
}

void AGE_Frame::CreateGeneralControls()
{
	Tab_General = new wxPanel(TabBar_Main);

	General_Main = new wxBoxSizer(wxVERTICAL);
	General_TopRow = new wxBoxSizer(wxHORIZONTAL);
	General_Refresh = new wxButton(Tab_General, wxID_ANY, "Refresh");
	General_CalcBoxes_Text = new wxStaticText(Tab_General, wxID_ANY, " Variable Converter *");
	General_CalcBoxes_Text->SetToolTip("From four 8 bit integers to one 32 bit integer or vice versa");
	General_CalcBoxesMiddle_Text = new wxStaticText(Tab_General, wxID_ANY, " = ");
	for(size_t loop = 0; loop < 5; ++loop)
	General_CalcBoxes[loop] = new wxTextCtrl(Tab_General, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1));
	General_Scroller = new wxScrolledWindow(Tab_General, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
	General_ScrollSpace = new wxBoxSizer(wxVERTICAL);

	const wxString SWUNKNOWNSINFO = "Unknowns 2 to 5 are in the beginning of the file,\nright after civilization count (first of the two) and\nbefore terrain restrictions";
	General_Variables_Grid = new wxGridSizer(6, 5, 5);
	General_Variables2_Grid = new wxGridSizer(7, 5, 5);
	General_Variables1_Holder = new wxStaticBoxSizer(wxVERTICAL, General_Scroller, "Star Wars Unknowns");
	General_SUnknown2_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown2_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 2 *");
	General_SUnknown2 = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	General_SUnknown2->SetToolTip(SWUNKNOWNSINFO);
	General_SUnknown3_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown3_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 3 *");
	General_SUnknown3 = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	General_SUnknown3->SetToolTip(SWUNKNOWNSINFO);
	General_SUnknown4_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown4_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 4 *");
	General_SUnknown4 = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	General_SUnknown4->SetToolTip(SWUNKNOWNSINFO);
	General_SUnknown5_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown5_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 5 *");
	General_SUnknown5 = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	General_SUnknown5->SetToolTip(SWUNKNOWNSINFO);
	General_SUnknown7_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown7_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 7 *");
	General_SUnknown7 = AGETextCtrl::init(CByte, &uiGroupMaps, this, &popUp, General_Scroller);
	General_SUnknown7->SetToolTip("In the file this is\nright after civilizations and\nbefore researches");
	General_SUnknown8_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown8_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 8 *");
	General_SUnknown8 = AGETextCtrl::init(CByte, &uiGroupMaps, this, &popUp, General_Scroller);
	General_SUnknown8->SetToolTip("In the file this is\nright after researches and\nbefore technology trees");

	General_MapPointer_Holder = new wxBoxSizer(wxVERTICAL);
	General_MapPointer_Text = new wxStaticText(General_Scroller, wxID_ANY, " Map Pointer");
	General_MapPointer = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	General_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	General_Unknown1_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unknown 1");
	General_Unknown1 = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	General_MapWidth_Holder = new wxBoxSizer(wxVERTICAL);
	General_MapWidth_Text = new wxStaticText(General_Scroller, wxID_ANY, " Map Width");
	General_MapWidth = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	General_MapHeight_Holder = new wxBoxSizer(wxVERTICAL);
	General_MapHeight_Text = new wxStaticText(General_Scroller, wxID_ANY, " Map Height");
	General_MapHeight = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	General_WorldWidth_Holder = new wxBoxSizer(wxVERTICAL);
	General_WorldWidth_Text = new wxStaticText(General_Scroller, wxID_ANY, " World Width");
	General_WorldWidth = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	General_WorldHeight_Holder = new wxBoxSizer(wxVERTICAL);
	General_WorldHeight_Text = new wxStaticText(General_Scroller, wxID_ANY, " World Height");
	General_WorldHeight = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	General_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	General_Unknown2_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 2");
	General_Unknown2 = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);

	General_TileSizes_Text = new wxStaticText(General_Scroller, wxID_ANY, " Tile Sizes   19 x (Width, Height, Delta Y)   1st is flat tile, then 2 x 8 elevation tiles, then 2 1:1 tiles");
	General_TileSizes_Grid = new wxGridSizer(15, 0, 0);

	UnknownPointer1_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unknown Pointer 1");
	UnknownPointer1 = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	MapMinX_Text = new wxStaticText(General_Scroller, wxID_ANY, " Map Min X");
	MapMinX = AGETextCtrl::init(CFloat, &uiGroupMaps, this, &popUp, General_Scroller);
	MapMinY_Text = new wxStaticText(General_Scroller, wxID_ANY, " Map Min Y");
	MapMinY = AGETextCtrl::init(CFloat, &uiGroupMaps, this, &popUp, General_Scroller);
	MapMaxX_Text = new wxStaticText(General_Scroller, wxID_ANY, " Map Max X");
	MapMaxX = AGETextCtrl::init(CFloat, &uiGroupMaps, this, &popUp, General_Scroller);
	MapMaxY_Text = new wxStaticText(General_Scroller, wxID_ANY, " Map Max Y");
	MapMaxY = AGETextCtrl::init(CFloat, &uiGroupMaps, this, &popUp, General_Scroller);
	MapMaxXplus1_Text = new wxStaticText(General_Scroller, wxID_ANY, " Map Max X + 1");
	MapMaxXplus1 = AGETextCtrl::init(CFloat, &uiGroupMaps, this, &popUp, General_Scroller);
	MapMaxYplus1_Text = new wxStaticText(General_Scroller, wxID_ANY, " Map Max Y + 1");
	MapMaxYplus1 = AGETextCtrl::init(CFloat, &uiGroupMaps, this, &popUp, General_Scroller);

	MaxTerrain_Text = new wxStaticText(General_Scroller, wxID_ANY, " Max Terrain");
	MaxTerrain = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);
	TileWidth_Text = new wxStaticText(General_Scroller, wxID_ANY, " Tile Width");
	TileWidth = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);
	TileHeight_Text = new wxStaticText(General_Scroller, wxID_ANY, " Tile Height");
	TileHeight = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);
	TileHalfHeight_Text = new wxStaticText(General_Scroller, wxID_ANY, " Tile Half Height");
	TileHalfHeight = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);
	TileHalfWidth_Text = new wxStaticText(General_Scroller, wxID_ANY, " Tile Half Width");
	TileHalfWidth = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);
	ElevHeight_Text = new wxStaticText(General_Scroller, wxID_ANY, " Elevation Height");
	ElevHeight = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);
	CurRow_Text = new wxStaticText(General_Scroller, wxID_ANY, " Current Row");
	CurRow = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);
	CurCol_Text = new wxStaticText(General_Scroller, wxID_ANY, " Current Col");
	CurCol = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);
	BlockBegRow_Text = new wxStaticText(General_Scroller, wxID_ANY, " Block Start Row");
	BlockBegRow = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);
	BlockEndRow_Text = new wxStaticText(General_Scroller, wxID_ANY, " Block End Row");
	BlockEndRow = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);
	BlockBegCol_Text = new wxStaticText(General_Scroller, wxID_ANY, " Block Start Col");
	BlockBegCol = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);
	BlockEndCol_Text = new wxStaticText(General_Scroller, wxID_ANY, " Block End Col");
	BlockEndCol = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller);

	UnknownPointer2_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unknown Pointer 2");
	UnknownPointer2 = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	UnknownPointer3_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unknown Pointer 3");
	UnknownPointer3 = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);
	AnyFrameChange_Text = new wxStaticText(General_Scroller, wxID_ANY, " Any Frame Change");
	AnyFrameChange = AGETextCtrl::init(CByte, &uiGroupMaps, this, &popUp, General_Scroller);

	MapVisibleFlag_Text = new wxStaticText(General_Scroller, wxID_ANY, " Map Visible Flag");
	MapVisibleFlag = AGETextCtrl::init(CByte, &uiGroupMaps, this, &popUp, General_Scroller);
	FogFlag_Text = new wxStaticText(General_Scroller, wxID_ANY, " Fog Flag");
	FogFlag = AGETextCtrl::init(CByte, &uiGroupMaps, this, &popUp, General_Scroller);

	General_TerrainRendering_Text = new wxStaticText(General_Scroller, wxID_ANY, " Miscellaneous useless terrain data");
	General_TerrainRendering_Grid = new wxGridSizer(7, 0, 5);
	General_Something_Grid = new wxGridSizer(8, 0, 0);
	General_SomeBytes_Grid = new wxGridSizer(16, 0, 0);
	for(size_t loop = 0; loop < General_TileSizes.size(); ++loop)
	General_TileSizes[loop] = AGETextCtrl::init(CShort, &uiGroupMaps, this, &popUp, General_Scroller, 2);
	for(size_t loop = 0; loop < General_SomeBytes.size(); ++loop)
	General_SomeBytes[loop] = AGETextCtrl::init(CByte, &uiGroupMaps, this, &popUp, General_Scroller);
	for(size_t loop = 0; loop < General_Something.size(); ++loop)
	General_Something[loop] = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, General_Scroller);

	General_TopRow->Add(General_Refresh, 0, wxEXPAND | wxRIGHT, 100);
	for(size_t loop = 0; loop < 4; ++loop)
	General_TopRow->Add(General_CalcBoxes[loop], 0, wxEXPAND);
	General_TopRow->Add(General_CalcBoxesMiddle_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_TopRow->Add(General_CalcBoxes[4], 0, wxEXPAND);
	General_TopRow->Add(General_CalcBoxes_Text, 0, wxEXPAND | wxBOTTOM, 2);

	for(size_t loop = 0; loop < General_TileSizes.size(); ++loop)
	General_TileSizes_Grid->Add(General_TileSizes[loop], 0, wxEXPAND);

    General_TerrainRendering_Grid->Add(UnknownPointer1_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(MapMinX_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(MapMinY_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(MapMaxX_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(MapMaxY_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(MapMaxXplus1_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(MapMaxYplus1_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(UnknownPointer1, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(MapMinX, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(MapMinY, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(MapMaxX, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(MapMaxY, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(MapMaxXplus1, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(MapMaxYplus1, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(MaxTerrain_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(TileWidth_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(TileHeight_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(TileHalfHeight_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(TileHalfWidth_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(ElevHeight_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(CurRow_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(MaxTerrain, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(TileWidth, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(TileHeight, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(TileHalfHeight, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(TileHalfWidth, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(ElevHeight, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(CurRow, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(CurCol_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(BlockBegRow_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(BlockEndRow_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(BlockBegCol_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(BlockEndCol_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(UnknownPointer2_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(UnknownPointer3_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(CurCol, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(BlockBegRow, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(BlockEndRow, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(BlockBegCol, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(BlockEndCol, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(UnknownPointer2, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(UnknownPointer3, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(AnyFrameChange_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(MapVisibleFlag_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(FogFlag_Text, 0, wxEXPAND | wxTOP, 5);
    General_TerrainRendering_Grid->Add(0, 0);
    General_TerrainRendering_Grid->Add(0, 0);
    General_TerrainRendering_Grid->Add(0, 0);
    General_TerrainRendering_Grid->Add(0, 0);
    General_TerrainRendering_Grid->Add(AnyFrameChange, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(MapVisibleFlag, 0, wxEXPAND);
    General_TerrainRendering_Grid->Add(FogFlag, 0, wxEXPAND);

	for(size_t loop = 0; loop < General_Something.size(); ++loop)
	General_Something_Grid->Add(General_Something[loop], 0, wxEXPAND);
	for(size_t loop = 0; loop < General_SomeBytes.size(); ++loop)
	General_SomeBytes_Grid->Add(General_SomeBytes[loop], 0, wxEXPAND);

	General_SUnknown7_Holder->Add(General_SUnknown7_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_SUnknown7_Holder->Add(General_SUnknown7, 1, wxEXPAND);
	General_SUnknown8_Holder->Add(General_SUnknown8_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_SUnknown8_Holder->Add(General_SUnknown8, 1, wxEXPAND);
	General_SUnknown2_Holder->Add(General_SUnknown2_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_SUnknown2_Holder->Add(General_SUnknown2, 1, wxEXPAND);
	General_SUnknown3_Holder->Add(General_SUnknown3_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_SUnknown3_Holder->Add(General_SUnknown3, 1, wxEXPAND);
	General_SUnknown4_Holder->Add(General_SUnknown4_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_SUnknown4_Holder->Add(General_SUnknown4, 1, wxEXPAND);
	General_SUnknown5_Holder->Add(General_SUnknown5_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_SUnknown5_Holder->Add(General_SUnknown5, 1, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown2_Holder, 0, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown3_Holder, 0, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown4_Holder, 0, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown5_Holder, 0, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown7_Holder, 0, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown8_Holder, 0, wxEXPAND);
	General_Variables1_Holder->Add(General_Variables_Grid, 0, wxEXPAND);

	General_MapPointer_Holder->Add(General_MapPointer_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_MapPointer_Holder->Add(General_MapPointer, 0, wxEXPAND);
	General_Unknown1_Holder->Add(General_Unknown1_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_Unknown1_Holder->Add(General_Unknown1, 0, wxEXPAND);
	General_MapWidth_Holder->Add(General_MapWidth_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_MapWidth_Holder->Add(General_MapWidth, 0, wxEXPAND);
	General_MapHeight_Holder->Add(General_MapHeight_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_MapHeight_Holder->Add(General_MapHeight, 0, wxEXPAND);
	General_WorldWidth_Holder->Add(General_WorldWidth_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_WorldWidth_Holder->Add(General_WorldWidth, 0, wxEXPAND);
	General_WorldHeight_Holder->Add(General_WorldHeight_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_WorldHeight_Holder->Add(General_WorldHeight, 0, wxEXPAND);
	General_Unknown2_Holder->Add(General_Unknown2_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_Unknown2_Holder->Add(General_Unknown2, 0, wxEXPAND);
	General_Variables2_Grid->Add(General_MapPointer_Holder, 0, wxEXPAND);
	General_Variables2_Grid->Add(General_Unknown1_Holder, 0, wxEXPAND);
	General_Variables2_Grid->Add(General_MapWidth_Holder, 0, wxEXPAND);
	General_Variables2_Grid->Add(General_MapHeight_Holder, 0, wxEXPAND);
	General_Variables2_Grid->Add(General_WorldWidth_Holder, 0, wxEXPAND);
	General_Variables2_Grid->Add(General_WorldHeight_Holder, 0, wxEXPAND);
	General_Variables2_Grid->Add(General_Unknown2_Holder, 0, wxEXPAND);

	General_ScrollSpace->Add(General_Variables1_Holder, 0, wxEXPAND);
	General_ScrollSpace->Add(General_Variables2_Grid, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
	General_ScrollSpace->Add(General_TileSizes_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_ScrollSpace->Add(General_TileSizes_Grid, 0, wxEXPAND);
	General_ScrollSpace->Add(General_TerrainRendering_Grid, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
	General_ScrollSpace->Add(General_TerrainRendering_Text, 0, wxEXPAND | wxBOTTOM, 2);
	General_ScrollSpace->Add(General_SomeBytes_Grid, 0, wxEXPAND);
	General_ScrollSpace->Add(General_Something_Grid, 0, wxEXPAND);

	General_Scroller->SetSizer(General_ScrollSpace);
	General_Scroller->SetScrollRate(0, 15);

	General_Main->Add(General_TopRow, 0, wxEXPAND | wxALL, 5);
	General_Main->Add(General_Scroller, 1, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 5);

	Tab_General->SetSizer(General_Main);

	Connect(General_Refresh->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnMapsRefresh));
    Connect(TechTrees_Ages_Items.ModeCombo->GetId(), wxEVT_MOUSEWHEEL, wxMouseEventHandler(AGE_Frame::wheelParent));
    Connect(TechTrees_Buildings_Items.ModeCombo->GetId(), wxEVT_MOUSEWHEEL, wxMouseEventHandler(AGE_Frame::wheelParent));
    Connect(TechTrees_Units_Items.ModeCombo->GetId(), wxEVT_MOUSEWHEEL, wxMouseEventHandler(AGE_Frame::wheelParent));
    Connect(TechTrees_Researches_Items.ModeCombo->GetId(), wxEVT_MOUSEWHEEL, wxMouseEventHandler(AGE_Frame::wheelParent));
	for(size_t loop = 0; loop < 4; ++loop)
	General_CalcBoxes[loop]->Connect(General_CalcBoxes[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnVariableCalc), NULL, this);
	General_CalcBoxes[4]->Connect(General_CalcBoxes[4]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnVariableCalcReverse), NULL, this);
}

void AGE_Frame::OnRandomMapSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListRandomMaps();
}

string AGE_Frame::GetRandomMapName(int index)
{
	if(GenieVersion >= genie::GV_AoK)
	{
		return "Map "+lexical_cast<string>(dataset->RandomMaps.MapHeaders[index].ScriptNumber)+" ";
	}
	string Name = "";
	switch(index)
	{
		case 0: Name += "Small Islands ("; break;
		case 1: Name += "Large Islands ("; break;
		case 2: Name += "Coastal ("; break;
		case 3: Name += "Inland ("; break;
		case 4: Name += "Highland ("; break;
		case 5: Name += "Continental ("; break;
		case 6: Name += "Mediterranean ("; break;
		case 7: Name += "Hill Country ("; break;
		case 8: Name += "Narrows ("; break;
		case 9: Name += "Gigantic ("; break;
		default: Name += "Map (";
	}
	return Name += lexical_cast<string>(dataset->RandomMaps.MapHeaders[index].ScriptNumber)+")";
}

void AGE_Frame::ListRandomMaps()
{
	InitRandomMaps();
	wxTimerEvent E;
	OnRandomMapTimer(E);
}

void AGE_Frame::InitRandomMaps()
{
	searchText = Unknowns_Search->GetValue().MakeLower();
	excludeText = Unknowns_Search_R->GetValue().MakeLower();

	Unknowns_ListV->names.clear();
	Unknowns_ListV->indexes.clear();

	for(size_t loop = 0; loop < dataset->RandomMaps.MapHeaders.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetRandomMapName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Unknowns_ListV->names.Add(Name);
			Unknowns_ListV->indexes.push_back(loop);
		}
	}
	virtualListing(Unknowns_ListV);
}

void AGE_Frame::OnRandomMapSelect(wxCommandEvent &event)
{
    if(!randomMapTimer.IsRunning())
        randomMapTimer.Start(150);
}

void AGE_Frame::OnRandomMapTimer(wxTimerEvent &event)
{
    randomMapTimer.Stop();
	auto selections = Unknowns_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Unknowns_ListV, RandomMapIDs);
    for(auto &box: uiGroupRandomMap) box->clear();
	if(selections > 0)
	{
		genie::MapHeader * MapPointer1;
		genie::Map * MapPointer2;
		for(auto sel = selections; sel--> 0;)
		{
			MapPointer1 = &dataset->RandomMaps.MapHeaders[RandomMapIDs[sel]];
			MapPointer2 = &dataset->RandomMaps.Maps[RandomMapIDs[sel]];

			Unknowns_UnknownLevel->prepend(&MapPointer1->ScriptNumber);
			Unknowns_Unknown1[0]->prepend(&MapPointer1->BorderSouthWest);
			Unknowns_Unknown1[0]->prepend(&MapPointer2->BorderSouthWest);
			Unknowns_Unknown1[1]->prepend(&MapPointer1->BorderNorthWest);
			Unknowns_Unknown1[1]->prepend(&MapPointer2->BorderNorthWest);
			Unknowns_Unknown1[2]->prepend(&MapPointer1->BorderNorthEast);
			Unknowns_Unknown1[2]->prepend(&MapPointer2->BorderNorthEast);
			Unknowns_Unknown1[3]->prepend(&MapPointer1->BorderSouthEast);
			Unknowns_Unknown1[3]->prepend(&MapPointer2->BorderSouthEast);
			Unknowns_Unknown1[4]->prepend(&MapPointer1->BorderUsage);
			Unknowns_Unknown1[4]->prepend(&MapPointer2->BorderUsage);
			Unknowns_Unknown1[5]->prepend(&MapPointer1->WaterShape);
			Unknowns_Unknown1[5]->prepend(&MapPointer2->WaterShape);
			Unknowns_Unknown1[6]->prepend(&MapPointer1->NonBaseTerrain);
			Unknowns_Unknown1[6]->prepend(&MapPointer2->NonBaseTerrain);
			Unknowns_Unknown1[7]->prepend(&MapPointer1->BaseZoneCoverage);
			Unknowns_Unknown1[7]->prepend(&MapPointer2->BaseZoneCoverage);
			Unknowns_Unknown1[8]->prepend(&MapPointer1->Unknown9);
			Unknowns_Unknown1[8]->prepend(&MapPointer2->Unknown9);
			Unknowns_Pointer1->prepend(&MapPointer1->BaseZonePointer);
			Unknowns_Pointer1->prepend(&MapPointer2->BaseZonePointer);
			Unknowns_Pointer2->prepend(&MapPointer1->MapTerrainPointer);
			Unknowns_Pointer2->prepend(&MapPointer2->MapTerrainPointer);
			Unknowns_Pointer3->prepend(&MapPointer1->MapUnitPointer);
			Unknowns_Pointer3->prepend(&MapPointer2->MapUnitPointer);
			Unknowns_Pointer4->prepend(&MapPointer1->MapUnknownPointer);
			Unknowns_Pointer4->prepend(&MapPointer2->MapUnknownPointer);
		}
		SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected random map: "+lexical_cast<string>(RandomMapIDs.front()), 0);
	}
    for(auto &box: uiGroupRandomMap) box->update();
    ListRMSBaseZones();
    ListRMSTerrains();
    ListRMSUnits();
    ListRMSUnknowns();
}

void AGE_Frame::OnRandomMapAdd(wxCommandEvent &event)
{
	if(!dataset) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->RandomMaps.MapHeaders);
	AddToList(dataset->RandomMaps.Maps);
	ListRandomMaps();
}

void AGE_Frame::OnRandomMapInsert(wxCommandEvent &event)
{
	auto selections = Unknowns_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->RandomMaps.MapHeaders, RandomMapIDs.front());
	InsertToList(dataset->RandomMaps.Maps, RandomMapIDs.front());
	ListRandomMaps();
}

void AGE_Frame::OnRandomMapDelete(wxCommandEvent &event)
{
	auto selections = Unknowns_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->RandomMaps.MapHeaders, RandomMapIDs);
	DeleteFromList(dataset->RandomMaps.Maps, RandomMapIDs);
	ListRandomMaps();
}

void AGE_Frame::OnRandomMapCopy(wxCommandEvent &event)
{
	auto selections = Unknowns_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->RandomMaps.MapHeaders, RandomMapIDs, copies.MapHeader);
	CopyFromList(dataset->RandomMaps.Maps, RandomMapIDs, copies.Map);
	Unknowns_Paste->Enable(true);
	Unknowns_PasteInsert->Enable(true);
	Unknowns_ListV->SetFocus();
}

void AGE_Frame::OnRandomMapPaste(wxCommandEvent &event)
{
	auto selections = Unknowns_ListV->GetSelectedItemCount();
	if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->RandomMaps.MapHeaders, RandomMapIDs, copies.MapHeader);
    PasteToList(dataset->RandomMaps.Maps, RandomMapIDs, copies.Map);
    ListRandomMaps();
}

void AGE_Frame::OnRandomMapPasteInsert(wxCommandEvent &event)
{
	auto selections = Unknowns_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->RandomMaps.MapHeaders, RandomMapIDs.front(), copies.MapHeader);
	PasteInsertToList(dataset->RandomMaps.Maps, RandomMapIDs.front(), copies.Map);
	ListRandomMaps();
}

void AGE_Frame::OnRMSBaseZoneSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListRMSBaseZones();
}

string AGE_Frame::GetRMSBaseZonesName(int index)
{
	return "Base Zone "+lexical_cast<string>(dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones[index].Unknown1)+" ";
}

void AGE_Frame::ListRMSBaseZones()
{
	searchText = RMSBaseZones_Search->GetValue().MakeLower();
	excludeText = RMSBaseZones_Search_R->GetValue().MakeLower();

	RMSBaseZones_ListV->names.clear();
	RMSBaseZones_ListV->indexes.clear();

    if(dataset->RandomMaps.Maps.size())
	for(size_t loop = 0; loop < dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetRMSBaseZonesName(loop);
		if(SearchMatches(Name.Lower()))
		{
			RMSBaseZones_ListV->names.Add(Name);
			RMSBaseZones_ListV->indexes.push_back(loop);
		}
	}
	virtualListing(RMSBaseZones_ListV);

	wxTimerEvent E;
	OnRMSBaseZoneTimer(E);
}

void AGE_Frame::OnRMSBaseZoneSelect(wxCommandEvent &event)
{
    if(!rmBaseTimer.IsRunning())
        rmBaseTimer.Start(150);
}

void AGE_Frame::OnRMSBaseZoneTimer(wxTimerEvent &event)
{
    rmBaseTimer.Stop();
	auto selections = RMSBaseZones_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, RMSBaseZones_ListV, UnknownFSIDs);
    for(auto &box: uiGroupRMBase) box->clear();

	genie::BaseZone * UnknownPointer;
	for(auto sel = selections; sel--> 0;)
	{
		UnknownPointer = &dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones[UnknownFSIDs[sel]];

		RMSBaseZones_Unknown1->prepend(&UnknownPointer->Unknown1);
		RMSBaseZones_BaseTerrain->prepend(&UnknownPointer->BaseTerrain);
		RMSBaseZones_SpacingBetweenPlayers->prepend(&UnknownPointer->SpacingBetweenPlayers);
		RMSBaseZones_Unknown4->prepend(&UnknownPointer->Unknown4);
		for(size_t loop = 0; loop < RMSBaseZones_Unknown5.size(); ++loop)
		RMSBaseZones_Unknown5[loop]->prepend(&UnknownPointer->Unknown5[loop]);
		RMSBaseZones_Unknown6->prepend(&UnknownPointer->Unknown6);
		RMSBaseZones_Unknown7->prepend(&UnknownPointer->Unknown7);
		for(size_t loop = 0; loop < RMSBaseZones_Unknown8.size(); ++loop)
		RMSBaseZones_Unknown8[loop]->prepend(&UnknownPointer->Unknown8[loop]);
		RMSBaseZones_StartAreaRadius->prepend(&UnknownPointer->StartAreaRadius);
		RMSBaseZones_Unknown10->prepend(&UnknownPointer->Unknown10);
		RMSBaseZones_Unknown11->prepend(&UnknownPointer->Unknown11);
	}

    for(auto &box: uiGroupRMBase) box->update();
}

void AGE_Frame::OnRMSBaseZoneAdd(wxCommandEvent &event)
{
	auto selections = Unknowns_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].BaseZoneCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones.size();
	ListRMSBaseZones();
}

void AGE_Frame::OnRMSBaseZoneInsert(wxCommandEvent &event)
{
	auto selections = RMSBaseZones_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones, UnknownFSIDs.front());
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].BaseZoneCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones.size();
	ListRMSBaseZones();
}

void AGE_Frame::OnRMSBaseZoneDelete(wxCommandEvent &event)
{
	auto selections = RMSBaseZones_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones, UnknownFSIDs);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].BaseZoneCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones.size();
	ListRMSBaseZones();
}

void AGE_Frame::OnRMSBaseZoneCopy(wxCommandEvent &event)
{
	auto selections = RMSBaseZones_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones, UnknownFSIDs, copies.BaseZone);
	RMSBaseZones_Paste->Enable(true);
	RMSBaseZones_PasteInsert->Enable(true);
	RMSBaseZones_ListV->SetFocus();
}

void AGE_Frame::OnRMSBaseZonePaste(wxCommandEvent &event)
{
	auto selections = RMSBaseZones_ListV->GetSelectedItemCount();
	if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones, UnknownFSIDs, copies.BaseZone);
    dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].BaseZoneCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones.size();
    ListRMSBaseZones();
}

void AGE_Frame::OnRMSBaseZonePasteInsert(wxCommandEvent &event)
{
	auto selections = RMSBaseZones_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones, UnknownFSIDs.front(), copies.BaseZone);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].BaseZoneCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones.size();
	ListRMSBaseZones();
}

void AGE_Frame::OnRMSBaseZoneCopyToMaps(wxCommandEvent &event)
{
	for(size_t loop=1; loop < RandomMapIDs.size(); ++loop)
	{
		dataset->RandomMaps.Maps[RandomMapIDs[loop]].BaseZones = dataset->RandomMaps.Maps[RandomMapIDs.front()].BaseZones;
	}
}

void AGE_Frame::OnRMSTerrainSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListRMSTerrains();
}

string AGE_Frame::GetRMSTerrainName(int Terrain)
{
	string Name = lexical_cast<string>(Terrain)+" ";
	if(dataset->TerrainBlock.Terrains.size() <= Terrain) return Name + "Nonexistent Terrain";
	if(!dataset->TerrainBlock.Terrains[Terrain].Name.empty())
	{
		return Name + dataset->TerrainBlock.Terrains[Terrain].Name;
	}
	return Name + "New Terrain";
}

void AGE_Frame::ListRMSTerrains()
{
	searchText = RMSTerrain_Search->GetValue().MakeLower();
	excludeText = RMSTerrain_Search_R->GetValue().MakeLower();

	RMSTerrain_ListV->names.clear();
	RMSTerrain_ListV->indexes.clear();

    if(dataset->RandomMaps.Maps.size())
	for(size_t loop = 0; loop < dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetRMSTerrainName(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains[loop].Terrain);
		if(SearchMatches(Name.Lower()))
		{
			RMSTerrain_ListV->names.Add(Name);
			RMSTerrain_ListV->indexes.push_back(loop);
		}
	}
	virtualListing(RMSTerrain_ListV);

	wxTimerEvent E;
	OnRMSTerrainTimer(E);
}

void AGE_Frame::OnRMSTerrainSelect(wxCommandEvent &event)
{
    if(!rmTerrainTimer.IsRunning())
        rmTerrainTimer.Start(150);
}

void AGE_Frame::OnRMSTerrainTimer(wxTimerEvent &event)
{
    rmTerrainTimer.Stop();
	auto selections = RMSTerrain_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, RMSTerrain_ListV, UnknownSSIDs);
	for(auto &box: uiGroupRMTerrain) box->clear();

	genie::MapTerrain * UnknownPointer;
	for(auto sel = selections; sel--> 0;)
	{
		UnknownPointer = &dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains[UnknownSSIDs[sel]];

		RMSTerrain_Unknown1[0]->prepend(&UnknownPointer->Proportion);
		RMSTerrain_Unknown1[1]->prepend(&UnknownPointer->Terrain);
		RMSTerrain_Unknown1[2]->prepend(&UnknownPointer->NumberOfClumps);
		RMSTerrain_Unknown1[3]->prepend(&UnknownPointer->SpacingToOtherTerrains);
		RMSTerrain_Unknown1[4]->prepend(&UnknownPointer->PlacementZone);
		RMSTerrain_Unknown1[5]->prepend(&UnknownPointer->Unknown6);
	}

	for(auto &box: uiGroupRMTerrain) box->update();
}

void AGE_Frame::OnRMSTerrainAdd(wxCommandEvent &event)
{
	auto selections = Unknowns_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapTerrainCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainInsert(wxCommandEvent &event)
{
	auto selections = RMSTerrain_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains, UnknownSSIDs.front());
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapTerrainCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainDelete(wxCommandEvent &event)
{
	auto selections = RMSTerrain_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains, UnknownSSIDs);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapTerrainCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainCopy(wxCommandEvent &event)
{
	auto selections = RMSTerrain_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains, UnknownSSIDs, copies.MapTerrain);
	RMSTerrain_Paste->Enable(true);
	RMSTerrain_PasteInsert->Enable(true);
	RMSTerrain_ListV->SetFocus();
}

void AGE_Frame::OnRMSTerrainPaste(wxCommandEvent &event)
{
	auto selections = RMSTerrain_ListV->GetSelectedItemCount();
	if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains, UnknownSSIDs, copies.MapTerrain);
    dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapTerrainCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains.size();
    ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainPasteInsert(wxCommandEvent &event)
{
	auto selections = RMSTerrain_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains, UnknownSSIDs.front(), copies.MapTerrain);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapTerrainCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainCopyToMaps(wxCommandEvent &event)
{
	for(size_t loop=1; loop < RandomMapIDs.size(); ++loop)
	{
		dataset->RandomMaps.Maps[RandomMapIDs[loop]].MapTerrains = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains;
	}
}

void AGE_Frame::OnRMSUnitSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListRMSUnits();
}

void AGE_Frame::ListRMSUnits()
{
	searchText = RMSUnit_Search->GetValue().MakeLower();
	excludeText = RMSUnit_Search_R->GetValue().MakeLower();

	RMSUnit_ListV->names.clear();
	RMSUnit_ListV->indexes.clear();

    if(dataset->RandomMaps.Maps.size())
	for(size_t loop = 0; loop < dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits[loop].Unit);
		if(SearchMatches(Name.Lower()))
		{
			RMSUnit_ListV->names.Add(Name);
			RMSUnit_ListV->indexes.push_back(loop);
		}
	}
	virtualListing(RMSUnit_ListV);

	wxTimerEvent E;
	OnRMSUnitTimer(E);
}

void AGE_Frame::OnRMSUnitSelect(wxCommandEvent &event)
{
    if(!rmUnitTimer.IsRunning())
        rmUnitTimer.Start(150);
}

void AGE_Frame::OnRMSUnitTimer(wxTimerEvent &event)
{
    rmUnitTimer.Stop();
	auto selections = RMSUnit_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, RMSUnit_ListV, UnknownTSIDs);
	for(auto &box: uiGroupRMUnit) box->clear();

	genie::MapUnit * UnknownPointer;
	for(auto sel = selections; sel--> 0;)
	{
		UnknownPointer = &dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits[UnknownTSIDs[sel]];

		RMSUnit_Unit->prepend(&UnknownPointer->Unit);
		RMSUnit_HostTerrain->prepend(&UnknownPointer->HostTerrain);
		for(size_t loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
		RMSUnit_Unknown3[loop]->prepend(&UnknownPointer->Unknown3[loop]);
		RMSUnit_ObjectsPerPlayer->prepend(&UnknownPointer->ObjectsPerGroup);
		RMSUnit_Unknown5->prepend(&UnknownPointer->Fluctuation);
		RMSUnit_GroupsPerPlayer->prepend(&UnknownPointer->GroupsPerPlayer);
		RMSUnit_Unknown7->prepend(&UnknownPointer->GroupRadius);
		RMSUnit_OwnAtStart->prepend(&UnknownPointer->OwnAtStart);
		RMSUnit_SetPlaceForAllPlayers->prepend(&UnknownPointer->SetPlaceForAllPlayers);
		RMSUnit_MinDistanceToPlayers->prepend(&UnknownPointer->MinDistanceToPlayers);
		RMSUnit_MaxDistanceToPlayers->prepend(&UnknownPointer->MaxDistanceToPlayers);
	}

	for(auto &box: uiGroupRMUnit) box->update();
}

void AGE_Frame::OnRMSUnitAdd(wxCommandEvent &event)
{
	auto selections = Unknowns_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapUnitCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitInsert(wxCommandEvent &event)
{
	auto selections = RMSUnit_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits, UnknownTSIDs.front());
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapUnitCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitDelete(wxCommandEvent &event)
{
	auto selections = RMSUnit_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits, UnknownTSIDs);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapUnitCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitCopy(wxCommandEvent &event)
{
	auto selections = RMSUnit_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits, UnknownTSIDs, copies.MapUnit);
	RMSUnit_Paste->Enable(true);
	RMSUnit_PasteInsert->Enable(true);
	RMSUnit_ListV->SetFocus();
}

void AGE_Frame::OnRMSUnitPaste(wxCommandEvent &event)
{
	auto selections = RMSUnit_ListV->GetSelectedItemCount();
	if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits, UnknownTSIDs, copies.MapUnit);
    dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapUnitCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits.size();
    ListRMSUnits();
}

void AGE_Frame::OnRMSUnitPasteInsert(wxCommandEvent &event)
{
	auto selections = RMSUnit_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits, UnknownTSIDs.front(), copies.MapUnit);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapUnitCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitCopyToMaps(wxCommandEvent &event)
{
	for(size_t loop=1; loop < RandomMapIDs.size(); ++loop)
	{
		dataset->RandomMaps.Maps[RandomMapIDs[loop]].MapUnits = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits;
	}
}

void AGE_Frame::OnRMSUnknownSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListRMSUnknowns();
}

string AGE_Frame::GetRMSUnknownName(int Terrain)
{
	string Name = lexical_cast<string>(Terrain)+" ";
	if(dataset->TerrainBlock.Terrains.size() <= Terrain) return Name + "Nonexistent Terrain";
	if(!dataset->TerrainBlock.Terrains[Terrain].Name.empty())
	{
		return Name + dataset->TerrainBlock.Terrains[Terrain].Name;
	}
	return Name + "New Terrain";
}

void AGE_Frame::ListRMSUnknowns()
{
	searchText = RMSUnknown_Search->GetValue().MakeLower();
	excludeText = RMSUnknown_Search_R->GetValue().MakeLower();

	RMSUnknown_ListV->names.clear();
	RMSUnknown_ListV->indexes.clear();

    if(dataset->RandomMaps.Maps.size())
	for(size_t loop = 0; loop < dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetRMSUnknownName(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns[loop].Unknown2);
		if(SearchMatches(Name.Lower()))
		{
			RMSUnknown_ListV->names.Add(Name);
			RMSUnknown_ListV->indexes.push_back(loop);
		}
	}
	virtualListing(RMSUnknown_ListV);

	wxTimerEvent E;
	OnRMSUnknownTimer(E);
}

void AGE_Frame::OnRMSUnknownSelect(wxCommandEvent &event)
{
    if(!rmUnknownTimer.IsRunning())
        rmUnknownTimer.Start(150);
}

void AGE_Frame::OnRMSUnknownTimer(wxTimerEvent &event)
{
    rmUnknownTimer.Stop();
	auto selections = RMSUnknown_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, RMSUnknown_ListV, Unknown4SIDs);
	for(auto &box: uiGroupRMUnknown) box->clear();

	genie::MapUnknown * UnknownPointer;
	for(auto sel = selections; sel--> 0;)
	{
		UnknownPointer = &dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns[Unknown4SIDs[sel]];

		RMSUnknown_Unknown1[0]->prepend(&UnknownPointer->Unknown1);
		RMSUnknown_Unknown1[1]->prepend(&UnknownPointer->Unknown2);
		RMSUnknown_Unknown1[2]->prepend(&UnknownPointer->Unknown3);
		RMSUnknown_Unknown1[3]->prepend(&UnknownPointer->Unknown4);
		RMSUnknown_Unknown1[4]->prepend(&UnknownPointer->Unknown5);
		RMSUnknown_Unknown1[5]->prepend(&UnknownPointer->Unknown6);
	}

	for(auto &box: uiGroupRMUnknown) box->update();
}

void AGE_Frame::OnRMSUnknownAdd(wxCommandEvent &event)
{
	auto selections = Unknowns_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapUnknownCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns.size();
	ListRMSUnknowns();
}

void AGE_Frame::OnRMSUnknownInsert(wxCommandEvent &event)
{
	auto selections = RMSUnknown_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns, Unknown4SIDs.front());
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapUnknownCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns.size();
	ListRMSUnknowns();
}

void AGE_Frame::OnRMSUnknownDelete(wxCommandEvent &event)
{
	auto selections = RMSUnknown_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns, Unknown4SIDs);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapUnknownCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns.size();
	ListRMSUnknowns();
}

void AGE_Frame::OnRMSUnknownCopy(wxCommandEvent &event)
{
	auto selections = RMSUnknown_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns, Unknown4SIDs, copies.MapUnknown);
	RMSUnknown_Paste->Enable(true);
	RMSUnknown_PasteInsert->Enable(true);
	RMSUnknown_ListV->SetFocus();
}

void AGE_Frame::OnRMSUnknownPaste(wxCommandEvent &event)
{
	auto selections = RMSUnknown_ListV->GetSelectedItemCount();
	if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns, Unknown4SIDs, copies.MapUnknown);
    dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapUnknownCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns.size();
    ListRMSUnknowns();
}

void AGE_Frame::OnRMSUnknownPasteInsert(wxCommandEvent &event)
{
	auto selections = RMSUnknown_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns, Unknown4SIDs.front(), copies.MapUnknown);
	dataset->RandomMaps.MapHeaders[RandomMapIDs.front()].MapUnknownCount = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns.size();
	ListRMSUnknowns();
}

void AGE_Frame::OnRMSUnknownCopyToMaps(wxCommandEvent &event)
{
	for(size_t loop=1; loop < RandomMapIDs.size(); ++loop)
	{
		dataset->RandomMaps.Maps[RandomMapIDs[loop]].MapUnknowns = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnknowns;
	}
}

void AGE_Frame::CreateUnknownControls()
{
	Tab_Unknown = new wxPanel(TabBar_Main);

	Unknown_Main = new wxBoxSizer(wxVERTICAL);
	Unknown_Scroller = new wxScrolledWindow(Tab_Unknown, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
	Unknown_ScrollSpace = new wxBoxSizer(wxVERTICAL);

	Unknown_UnknownPointer_Text = new wxStaticText(Tab_Unknown, wxID_ANY, " Random Map Pointer");
	Unknown_UnknownPointer = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, Tab_Unknown);

	Unknowns = new wxStaticBoxSizer(wxHORIZONTAL, Tab_Unknown, "Random Map Scripts (Required in AoE/RoR)");
	Unknowns_ListArea = new wxBoxSizer(wxVERTICAL);
	Unknowns_Search = new wxTextCtrl(Tab_Unknown, wxID_ANY);
	Unknowns_Search_R = new wxTextCtrl(Tab_Unknown, wxID_ANY);
	Unknowns_ListV = new AGEListView(Tab_Unknown, wxSize(200, 220));
	Unknowns_Buttons = new wxGridSizer(3, 0, 0);
	Unknowns_Add = new wxButton(Tab_Unknown, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Insert = new wxButton(Tab_Unknown, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Delete = new wxButton(Tab_Unknown, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Copy = new wxButton(Tab_Unknown, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Paste = new wxButton(Tab_Unknown, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Unknowns_PasteInsert = new wxButton(Tab_Unknown, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	Unknowns_Space_UnknownLevel = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_UnknownLevel_Holder = new wxBoxSizer(wxVERTICAL);
	Unknowns_UnknownLevel_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Script Number");
	Unknowns_UnknownLevel = AGETextCtrl::init(CLong, &uiGroupRandomMap, this, &popUp, Unknown_Scroller);
	Unknowns_Unknown1_Grid = new wxGridSizer(5, 5, 5);
	for(size_t loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
	{
		Unknowns_Unknown1_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		Unknowns_Unknown1[loop] = AGETextCtrl::init(CLong, &uiGroupRandomMap, this, &popUp, Unknown_Scroller);
	}
	Unknowns_Unknown1_Text[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Southwest Border *");
	Unknowns_Unknown1[0]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Unknown1_Text[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Northwest Border *");
	Unknowns_Unknown1[1]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Unknown1_Text[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Northeast Border *");
	Unknowns_Unknown1[2]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Unknown1_Text[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Southeast Border *");
	Unknowns_Unknown1[3]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Unknown1_Text[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Border Usage % *");
	Unknowns_Unknown1[4]->SetToolTip("% of border area covered with non-base terrain");
	Unknowns_Unknown1_Text[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Water Shape?");
	Unknowns_Unknown1_Text[6] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Non-base Terrain *");
	Unknowns_Unknown1[6]->SetToolTip("Used on the borders as well");
	Unknowns_Unknown1_Text[7] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Zone Cover % *");
	Unknowns_Unknown1[7]->SetToolTip("Can be over 100");
	Unknowns_Unknown1_Text[8] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 9");
	Unknowns_Space_Pointer1 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Pointer1_Holder = new wxBoxSizer(wxVERTICAL);
	Unknowns_Pointer1_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Zone Pointer");
	Unknowns_Pointer1 = AGETextCtrl::init(CLong, &uiGroupRandomMap, this, &popUp, Unknown_Scroller);

	RMSBaseZones = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Base Zone Data");
	RMSBaseZones_ListArea = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_DataArea = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSBaseZones_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSBaseZones_ListV = new AGEListView(Unknown_Scroller, wxSize(140, 100));
	RMSBaseZones_Buttons = new wxGridSizer(3, 0, 0);
	RMSBaseZones_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_CopyToMaps = new wxButton(Unknown_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(5, 20));

	RMSBaseZones_Unknown1_Grid = new wxGridSizer(3, 5, 5);

	RMSBaseZones_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown1_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 1");
	RMSBaseZones_Unknown1 = AGETextCtrl::init(CLong, &uiGroupRMBase, this, &popUp, Unknown_Scroller);
	RMSBaseZones_BaseTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_BaseTerrain_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Terrain");
	RMSBaseZones_BaseTerrain = AGETextCtrl::init(CLong, &uiGroupRMBase, this, &popUp, Unknown_Scroller);
	RMSBaseZones_SpacingBetweenPlayers_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_SpacingBetweenPlayers_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Spacing Between Players *");
	RMSBaseZones_SpacingBetweenPlayers = AGETextCtrl::init(CLong, &uiGroupRMBase, this, &popUp, Unknown_Scroller);
	RMSBaseZones_SpacingBetweenPlayers->SetToolTip("Non-base terrain (like rivers) space between players\nIf too large, they won't be created");
	RMSBaseZones_Unknown4_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown4_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 4");
	RMSBaseZones_Unknown4 = AGETextCtrl::init(CLong, &uiGroupRMBase, this, &popUp, Unknown_Scroller);

	RMSBaseZones_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown5_Grid = new wxGridSizer(4, 0, 0);
	RMSBaseZones_Unknown5_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Min Dist. Between Players *");
	for(size_t loop = 0; loop < RMSBaseZones_Unknown5.size(); ++loop)
	RMSBaseZones_Unknown5[loop] = AGETextCtrl::init(CByte, &uiGroupRMBase, this, &popUp, Unknown_Scroller, 3);
	RMSBaseZones_Unknown5[1]->SetToolTip("Minimum distance in tiles between \"player initial zones\"");

	RMSBaseZones_Unknown6_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown6_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6");
	RMSBaseZones_Unknown6 = AGETextCtrl::init(CLong, &uiGroupRMBase, this, &popUp, Unknown_Scroller);
	RMSBaseZones_Unknown7_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown7_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 7");
	RMSBaseZones_Unknown7 = AGETextCtrl::init(CLong, &uiGroupRMBase, this, &popUp, Unknown_Scroller);

	RMSBaseZones_Unknown8_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown8_Grid = new wxGridSizer(4, 0, 0);
	RMSBaseZones_Unknown8_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Zone Radius *");
	for(size_t loop = 0; loop < RMSBaseZones_Unknown8.size(); ++loop)
	RMSBaseZones_Unknown8[loop] = AGETextCtrl::init(CByte, &uiGroupRMBase, this, &popUp, Unknown_Scroller, 3);
	RMSBaseZones_Unknown8[1]->SetToolTip("Base zone is created for every player");

	RMSBaseZones_StartAreaRadius_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_StartAreaRadius_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Players' Start Area Radius *");
	RMSBaseZones_StartAreaRadius = AGETextCtrl::init(CLong, &uiGroupRMBase, this, &popUp, Unknown_Scroller);
	RMSBaseZones_StartAreaRadius->SetToolTip("This area cannot contain different elevations or terrains\nUnknown 10 affects this too");
	RMSBaseZones_Unknown10_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown10_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 10 *");
	RMSBaseZones_Unknown10 = AGETextCtrl::init(CLong, &uiGroupRMBase, this, &popUp, Unknown_Scroller);
	RMSBaseZones_Unknown10->SetToolTip("Has something to do with players' starting area");
	RMSBaseZones_Unknown11_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown11_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 11");
	RMSBaseZones_Unknown11 = AGETextCtrl::init(CLong, &uiGroupRMBase, this, &popUp, Unknown_Scroller);

	Unknowns_Space_Pointer2 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Pointer2_Holder = new wxBoxSizer(wxVERTICAL);
	Unknowns_Pointer2_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Map Terrain Pointer");
	Unknowns_Pointer2 = AGETextCtrl::init(CLong, &uiGroupRandomMap, this, &popUp, Unknown_Scroller);

	RMSTerrain = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Terrains Placed on the Map");
	RMSTerrain_ListArea = new wxBoxSizer(wxVERTICAL);
	RMSTerrain_DataArea = new wxBoxSizer(wxVERTICAL);
	RMSTerrain_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSTerrain_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSTerrain_ListV = new AGEListView(Unknown_Scroller, wxSize(140, 100));
	RMSTerrain_Buttons = new wxGridSizer(3, 0, 0);
	RMSTerrain_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_CopyToMaps = new wxButton(Unknown_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(5, 20));

	RMSTerrain_Unknown1_Grid = new wxGridSizer(3, 5, 5);
	for(size_t loop = 0; loop < RMSTerrain_Unknown1.size(); ++loop)
	{
		RMSTerrain_Unknown1_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		RMSTerrain_Unknown1[loop] = AGETextCtrl::init(CLong, &uiGroupRMTerrain, this, &popUp, Unknown_Scroller);
	}
	RMSTerrain_Unknown1_Text[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Proportion *");
	RMSTerrain_Unknown1[0]->SetToolTip("% of the total map area");
	RMSTerrain_Unknown1_Text[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Terrain");
	RMSTerrain_Unknown1_Text[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Number of Clumps *");
	RMSTerrain_Unknown1[2]->SetToolTip("Clusters in the map");
	RMSTerrain_Unknown1_Text[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Spacing to Other Terrains *");
	RMSTerrain_Unknown1[3]->SetToolTip("Minimum distance to base terrain (or non-base terrain)");
	RMSTerrain_Unknown1_Text[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Placement Terrain");
	RMSTerrain_Unknown1_Text[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6");

	Unknowns_Space_Pointer3 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Pointer3_Holder = new wxBoxSizer(wxVERTICAL);
	Unknowns_Pointer3_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Map Unit Pointer");
	Unknowns_Pointer3 = AGETextCtrl::init(CLong, &uiGroupRandomMap, this, &popUp, Unknown_Scroller);

	RMSUnit = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Units Placed on the Map (Some may appear anyway)");
	RMSUnit_ListArea = new wxBoxSizer(wxVERTICAL);
	RMSUnit_DataArea = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSUnit_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSUnit_ListV = new AGEListView(Unknown_Scroller, wxSize(140, 250));
	RMSUnit_Buttons = new wxGridSizer(3, 0, 0);
	RMSUnit_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_CopyToMaps = new wxButton(Unknown_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(5, 20));

	RMSUnit_Unknown1_Grid = new wxGridSizer(3, 5, 5);
	RMSUnit_Unit_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Unit_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unit");
	RMSUnit_Unit = AGETextCtrl::init(CLong, &uiGroupRMUnit, this, &popUp, Unknown_Scroller);
	RMSUnit_HostTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_HostTerrain_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Placement Terrain");
	RMSUnit_HostTerrain = AGETextCtrl::init(CLong, &uiGroupRMUnit, this, &popUp, Unknown_Scroller);
	RMSUnit_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Unknown3_Grid = new wxGridSizer(4, 0, 0);
	RMSUnit_Unknown3_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Group Mode *");
	for(size_t loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
	RMSUnit_Unknown3[loop] = AGETextCtrl::init(CByte, &uiGroupRMUnit, this, &popUp, Unknown_Scroller, 3);
	RMSUnit_Unknown3[0]->SetToolTip("0 Only 1 unit is placed from group\n1 & 2 All units are placed from group");
	RMSUnit_ObjectsPerPlayer_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_ObjectsPerPlayer_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Objects per Group");
	RMSUnit_ObjectsPerPlayer = AGETextCtrl::init(CLong, &uiGroupRMUnit, this, &popUp, Unknown_Scroller);
	RMSUnit_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Unknown5_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Fluctuation *");
	RMSUnit_Unknown5 = AGETextCtrl::init(CLong, &uiGroupRMUnit, this, &popUp, Unknown_Scroller);
	RMSUnit_Unknown5->SetToolTip("Max random variation in the number of objects in the group");
	RMSUnit_GroupsPerPlayer_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_GroupsPerPlayer_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Groups per Player");
	RMSUnit_GroupsPerPlayer = AGETextCtrl::init(CLong, &uiGroupRMUnit, this, &popUp, Unknown_Scroller);
	RMSUnit_Unknown7_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Unknown7_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Group Radius *");
	RMSUnit_Unknown7 = AGETextCtrl::init(CLong, &uiGroupRMUnit, this, &popUp, Unknown_Scroller);
	RMSUnit_Unknown7->SetToolTip("Max distance in tiles, for each object of the group, to the central location of the group");
	RMSUnit_OwnAtStart_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_OwnAtStart_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Own at Start (-1=Yes) *");
	RMSUnit_OwnAtStart = AGETextCtrl::init(CLong, &uiGroupRMUnit, this, &popUp, Unknown_Scroller);
	RMSUnit_OwnAtStart->SetToolTip("Doesn't work if the unit isn't placed for all players");
	RMSUnit_SetPlaceForAllPlayers_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_SetPlaceForAllPlayers_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Set Place for All Players *");
	RMSUnit_SetPlaceForAllPlayers = AGETextCtrl::init(CLong, &uiGroupRMUnit, this, &popUp, Unknown_Scroller);
	RMSUnit_SetPlaceForAllPlayers->SetToolTip("1 = Done once per player\n-1 = Done once, whatever the number of players is\n-2 = same as -1 ? Cannot find a difference");
	RMSUnit_MinDistanceToPlayers_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_MinDistanceToPlayers_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Min Distance to Players");
	RMSUnit_MinDistanceToPlayers = AGETextCtrl::init(CLong, &uiGroupRMUnit, this, &popUp, Unknown_Scroller);
	RMSUnit_MaxDistanceToPlayers_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_MaxDistanceToPlayers_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Max Distance to Players *");
	RMSUnit_MaxDistanceToPlayers = AGETextCtrl::init(CLong, &uiGroupRMUnit, this, &popUp, Unknown_Scroller);
	RMSUnit_MaxDistanceToPlayers->SetToolTip("- Don't use 0 here for units that are own at start\n- 0 is OK for other units (gold/bushes/gazelle/etc)\n- You can use -1 as a wildcard for units that are own at start");

	Unknowns_Space_Pointer4 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Pointer4_Holder = new wxBoxSizer(wxVERTICAL);
	Unknowns_Pointer4_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Map Unknown Pointer");
	Unknowns_Pointer4 = AGETextCtrl::init(CLong, &uiGroupRandomMap, this, &popUp, Unknown_Scroller);

	RMSUnknown = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Unknowns Placed on the Map");
	RMSUnknown_ListArea = new wxBoxSizer(wxVERTICAL);
	RMSUnknown_DataArea = new wxBoxSizer(wxVERTICAL);
	RMSUnknown_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSUnknown_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSUnknown_ListV = new AGEListView(Unknown_Scroller, wxSize(140, 100));
	RMSUnknown_Buttons = new wxGridSizer(3, 0, 0);
	RMSUnknown_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_CopyToMaps = new wxButton(Unknown_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(5, 20));

	RMSUnknown_Unknown1_Grid = new wxGridSizer(3, 5, 5);
	for(size_t loop = 0; loop < RMSUnknown_Unknown1.size(); ++loop)
	{
		RMSUnknown_Unknown1_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		RMSUnknown_Unknown1[loop] = AGETextCtrl::init(CLong, &uiGroupRMUnknown, this, &popUp, Unknown_Scroller);
	}
	RMSUnknown_Unknown1_Text[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Proportion *");
	RMSUnknown_Unknown1[0]->SetToolTip("% of the total map area");
	RMSUnknown_Unknown1_Text[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Terrain");
	RMSUnknown_Unknown1_Text[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Number of Clumps *");
	RMSUnknown_Unknown1[2]->SetToolTip("Clusters in the map");
	RMSUnknown_Unknown1_Text[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Spacing to Other Terrains *");
	RMSUnknown_Unknown1[3]->SetToolTip("Minimum distance to base terrain (or non-base terrain)");
	RMSUnknown_Unknown1_Text[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Placement Terrain");
	RMSUnknown_Unknown1_Text[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6");

	Unknowns_Buttons->Add(Unknowns_Add, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Delete, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Insert, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Copy, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Paste, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_PasteInsert, 1, wxEXPAND);

	Unknowns_ListArea->Add(Unknowns_Search, 0, wxEXPAND);
	Unknowns_ListArea->Add(Unknowns_Search_R, 0, wxEXPAND);
	Unknowns_ListArea->Add(Unknowns_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Unknowns_ListArea->Add(Unknowns_Buttons, 0, wxEXPAND);

	Unknowns_UnknownLevel_Holder->Add(Unknowns_UnknownLevel_Text, 0, wxEXPAND | wxBOTTOM, 2);
	Unknowns_UnknownLevel_Holder->Add(Unknowns_UnknownLevel, 1, wxEXPAND);
	Unknowns_Space_UnknownLevel->Add(Unknowns_UnknownLevel_Holder, 1, wxEXPAND);
	Unknowns_Space_UnknownLevel->AddStretchSpacer(3);

	for(size_t loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
	{
		Unknowns_Unknown1_Holder[loop]->Add(Unknowns_Unknown1_Text[loop], 0, wxEXPAND | wxBOTTOM, 2);
		Unknowns_Unknown1_Holder[loop]->Add(Unknowns_Unknown1[loop], 1, wxEXPAND);
		Unknowns_Unknown1_Grid->Add(Unknowns_Unknown1_Holder[loop], 1, wxEXPAND);
	}

	Unknowns_Pointer1_Holder->Add(Unknowns_Pointer1_Text, 0, wxEXPAND | wxBOTTOM, 2);
	Unknowns_Pointer1_Holder->Add(Unknowns_Pointer1, 1, wxEXPAND);
	Unknowns_Space_Pointer1->Add(Unknowns_Pointer1_Holder, 1, wxEXPAND);
	Unknowns_Space_Pointer1->AddStretchSpacer(3);

	RMSBaseZones_Buttons->Add(RMSBaseZones_Add, 1, wxEXPAND);
	RMSBaseZones_Buttons->Add(RMSBaseZones_Delete, 1, wxEXPAND);
	RMSBaseZones_Buttons->Add(RMSBaseZones_Insert, 1, wxEXPAND);
	RMSBaseZones_Buttons->Add(RMSBaseZones_Copy, 1, wxEXPAND);
	RMSBaseZones_Buttons->Add(RMSBaseZones_Paste, 1, wxEXPAND);
	RMSBaseZones_Buttons->Add(RMSBaseZones_PasteInsert, 1, wxEXPAND);

	RMSBaseZones_ListArea->Add(RMSBaseZones_Search, 0, wxEXPAND);
	RMSBaseZones_ListArea->Add(RMSBaseZones_Search_R, 0, wxEXPAND);
	RMSBaseZones_ListArea->Add(RMSBaseZones_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	RMSBaseZones_ListArea->Add(RMSBaseZones_Buttons, 0, wxEXPAND);
	RMSBaseZones_ListArea->Add(RMSBaseZones_CopyToMaps, 0, wxEXPAND | wxTOP, 2);

	RMSBaseZones_Unknown1_Holder->Add(RMSBaseZones_Unknown1_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSBaseZones_Unknown1_Holder->Add(RMSBaseZones_Unknown1, 1, wxEXPAND);
	RMSBaseZones_BaseTerrain_Holder->Add(RMSBaseZones_BaseTerrain_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSBaseZones_BaseTerrain_Holder->Add(RMSBaseZones_BaseTerrain, 1, wxEXPAND);
	RMSBaseZones_SpacingBetweenPlayers_Holder->Add(RMSBaseZones_SpacingBetweenPlayers_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSBaseZones_SpacingBetweenPlayers_Holder->Add(RMSBaseZones_SpacingBetweenPlayers, 1, wxEXPAND);
	RMSBaseZones_Unknown4_Holder->Add(RMSBaseZones_Unknown4_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSBaseZones_Unknown4_Holder->Add(RMSBaseZones_Unknown4, 1, wxEXPAND);
	for(size_t loop = 0; loop < RMSBaseZones_Unknown5.size(); ++loop)
	RMSBaseZones_Unknown5_Grid->Add(RMSBaseZones_Unknown5[loop], 1, wxEXPAND);
	RMSBaseZones_Unknown5_Holder->Add(RMSBaseZones_Unknown5_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSBaseZones_Unknown5_Holder->Add(RMSBaseZones_Unknown5_Grid, 1, wxEXPAND);
	RMSBaseZones_Unknown6_Holder->Add(RMSBaseZones_Unknown6_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSBaseZones_Unknown6_Holder->Add(RMSBaseZones_Unknown6, 1, wxEXPAND);
	RMSBaseZones_Unknown7_Holder->Add(RMSBaseZones_Unknown7_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSBaseZones_Unknown7_Holder->Add(RMSBaseZones_Unknown7, 1, wxEXPAND);
	for(size_t loop = 0; loop < RMSBaseZones_Unknown8.size(); ++loop)
	RMSBaseZones_Unknown8_Grid->Add(RMSBaseZones_Unknown8[loop], 1, wxEXPAND);
	RMSBaseZones_Unknown8_Holder->Add(RMSBaseZones_Unknown8_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSBaseZones_Unknown8_Holder->Add(RMSBaseZones_Unknown8_Grid, 1, wxEXPAND);
	RMSBaseZones_StartAreaRadius_Holder->Add(RMSBaseZones_StartAreaRadius_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSBaseZones_StartAreaRadius_Holder->Add(RMSBaseZones_StartAreaRadius, 1, wxEXPAND);
	RMSBaseZones_Unknown10_Holder->Add(RMSBaseZones_Unknown10_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSBaseZones_Unknown10_Holder->Add(RMSBaseZones_Unknown10, 1, wxEXPAND);
	RMSBaseZones_Unknown11_Holder->Add(RMSBaseZones_Unknown11_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSBaseZones_Unknown11_Holder->Add(RMSBaseZones_Unknown11, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown1_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_BaseTerrain_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_SpacingBetweenPlayers_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown4_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown5_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown6_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown7_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown8_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_StartAreaRadius_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown10_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown11_Holder, 1, wxEXPAND);
	RMSBaseZones_DataArea->Add(RMSBaseZones_Unknown1_Grid, 0, wxEXPAND);

	RMSBaseZones->Add(RMSBaseZones_ListArea, 1, wxEXPAND);
	RMSBaseZones->Add(RMSBaseZones_DataArea, 3, wxEXPAND | wxLEFT, 5);

	Unknowns_Pointer2_Holder->Add(Unknowns_Pointer2_Text, 0, wxEXPAND | wxBOTTOM, 2);
	Unknowns_Pointer2_Holder->Add(Unknowns_Pointer2, 1, wxEXPAND);
	Unknowns_Space_Pointer2->Add(Unknowns_Pointer2_Holder, 1, wxEXPAND);
	Unknowns_Space_Pointer2->AddStretchSpacer(3);

	RMSTerrain_Buttons->Add(RMSTerrain_Add, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_Delete, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_Insert, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_Copy, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_Paste, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_PasteInsert, 1, wxEXPAND);

	RMSTerrain_ListArea->Add(RMSTerrain_Search, 0, wxEXPAND);
	RMSTerrain_ListArea->Add(RMSTerrain_Search_R, 0, wxEXPAND);
	RMSTerrain_ListArea->Add(RMSTerrain_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	RMSTerrain_ListArea->Add(RMSTerrain_Buttons, 0, wxEXPAND);
	RMSTerrain_ListArea->Add(RMSTerrain_CopyToMaps, 0, wxEXPAND | wxTOP, 2);

	for(size_t loop = 0; loop < RMSTerrain_Unknown1.size(); ++loop)
	{
		RMSTerrain_Unknown1_Holder[loop]->Add(RMSTerrain_Unknown1_Text[loop], 0, wxEXPAND | wxBOTTOM, 2);
		RMSTerrain_Unknown1_Holder[loop]->Add(RMSTerrain_Unknown1[loop], 1, wxEXPAND);
		RMSTerrain_Unknown1_Grid->Add(RMSTerrain_Unknown1_Holder[loop], 1, wxEXPAND);
	}
	RMSTerrain_DataArea->Add(RMSTerrain_Unknown1_Grid, 0, wxEXPAND);

	RMSTerrain->Add(RMSTerrain_ListArea, 1, wxEXPAND);
	RMSTerrain->Add(RMSTerrain_DataArea, 3, wxEXPAND | wxLEFT, 5);

	Unknowns_Pointer3_Holder->Add(Unknowns_Pointer3_Text, 0, wxEXPAND | wxBOTTOM, 2);
	Unknowns_Pointer3_Holder->Add(Unknowns_Pointer3, 1, wxEXPAND);
	Unknowns_Space_Pointer3->Add(Unknowns_Pointer3_Holder, 1, wxEXPAND);
	Unknowns_Space_Pointer3->AddStretchSpacer(3);

	RMSUnit_Buttons->Add(RMSUnit_Add, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_Delete, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_Insert, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_Copy, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_Paste, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_PasteInsert, 1, wxEXPAND);

	RMSUnit_ListArea->Add(RMSUnit_Search, 0, wxEXPAND);
	RMSUnit_ListArea->Add(RMSUnit_Search_R, 0, wxEXPAND);
	RMSUnit_ListArea->Add(RMSUnit_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	RMSUnit_ListArea->Add(RMSUnit_Buttons, 0, wxEXPAND);
	RMSUnit_ListArea->Add(RMSUnit_CopyToMaps, 0, wxEXPAND | wxTOP, 2);

	RMSUnit_Unit_Holder->Add(RMSUnit_Unit_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSUnit_Unit_Holder->Add(RMSUnit_Unit, 1, wxEXPAND);
	RMSUnit_HostTerrain_Holder->Add(RMSUnit_HostTerrain_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSUnit_HostTerrain_Holder->Add(RMSUnit_HostTerrain, 1, wxEXPAND);
	for(size_t loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
	RMSUnit_Unknown3_Grid->Add(RMSUnit_Unknown3[loop], 1, wxEXPAND);
	RMSUnit_Unknown3_Holder->Add(RMSUnit_Unknown3_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSUnit_Unknown3_Holder->Add(RMSUnit_Unknown3_Grid, 1, wxEXPAND);
	RMSUnit_ObjectsPerPlayer_Holder->Add(RMSUnit_ObjectsPerPlayer_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSUnit_ObjectsPerPlayer_Holder->Add(RMSUnit_ObjectsPerPlayer, 1, wxEXPAND);
	RMSUnit_Unknown5_Holder->Add(RMSUnit_Unknown5_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSUnit_Unknown5_Holder->Add(RMSUnit_Unknown5, 1, wxEXPAND);
	RMSUnit_GroupsPerPlayer_Holder->Add(RMSUnit_GroupsPerPlayer_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSUnit_GroupsPerPlayer_Holder->Add(RMSUnit_GroupsPerPlayer, 1, wxEXPAND);
	RMSUnit_Unknown7_Holder->Add(RMSUnit_Unknown7_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSUnit_Unknown7_Holder->Add(RMSUnit_Unknown7, 1, wxEXPAND);
	RMSUnit_OwnAtStart_Holder->Add(RMSUnit_OwnAtStart_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSUnit_OwnAtStart_Holder->Add(RMSUnit_OwnAtStart, 1, wxEXPAND);
	RMSUnit_SetPlaceForAllPlayers_Holder->Add(RMSUnit_SetPlaceForAllPlayers_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSUnit_SetPlaceForAllPlayers_Holder->Add(RMSUnit_SetPlaceForAllPlayers, 1, wxEXPAND);
	RMSUnit_MinDistanceToPlayers_Holder->Add(RMSUnit_MinDistanceToPlayers_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSUnit_MinDistanceToPlayers_Holder->Add(RMSUnit_MinDistanceToPlayers, 1, wxEXPAND);
	RMSUnit_MaxDistanceToPlayers_Holder->Add(RMSUnit_MaxDistanceToPlayers_Text, 0, wxEXPAND | wxBOTTOM, 2);
	RMSUnit_MaxDistanceToPlayers_Holder->Add(RMSUnit_MaxDistanceToPlayers, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_Unit_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_HostTerrain_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_Unknown3_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_ObjectsPerPlayer_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_Unknown5_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_GroupsPerPlayer_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_Unknown7_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_OwnAtStart_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_SetPlaceForAllPlayers_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_MinDistanceToPlayers_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_MaxDistanceToPlayers_Holder, 1, wxEXPAND);
	RMSUnit_DataArea->Add(RMSUnit_Unknown1_Grid, 0, wxEXPAND);

	RMSUnit->Add(RMSUnit_ListArea, 1, wxEXPAND);
	RMSUnit->Add(RMSUnit_DataArea, 3, wxEXPAND | wxLEFT, 5);

	Unknowns_Pointer4_Holder->Add(Unknowns_Pointer4_Text, 0, wxEXPAND | wxBOTTOM, 2);
	Unknowns_Pointer4_Holder->Add(Unknowns_Pointer4, 1, wxEXPAND);
	Unknowns_Space_Pointer4->Add(Unknowns_Pointer4_Holder, 1, wxEXPAND);
	Unknowns_Space_Pointer4->AddStretchSpacer(3);

	RMSUnknown_Buttons->Add(RMSUnknown_Add, 1, wxEXPAND);
	RMSUnknown_Buttons->Add(RMSUnknown_Delete, 1, wxEXPAND);
	RMSUnknown_Buttons->Add(RMSUnknown_Insert, 1, wxEXPAND);
	RMSUnknown_Buttons->Add(RMSUnknown_Copy, 1, wxEXPAND);
	RMSUnknown_Buttons->Add(RMSUnknown_Paste, 1, wxEXPAND);
	RMSUnknown_Buttons->Add(RMSUnknown_PasteInsert, 1, wxEXPAND);

	RMSUnknown_ListArea->Add(RMSUnknown_Search, 0, wxEXPAND);
	RMSUnknown_ListArea->Add(RMSUnknown_Search_R, 0, wxEXPAND);
	RMSUnknown_ListArea->Add(RMSUnknown_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	RMSUnknown_ListArea->Add(RMSUnknown_Buttons, 0, wxEXPAND);
	RMSUnknown_ListArea->Add(RMSUnknown_CopyToMaps, 0, wxEXPAND | wxTOP, 2);

	for(size_t loop = 0; loop < RMSUnknown_Unknown1.size(); ++loop)
	{
		RMSUnknown_Unknown1_Holder[loop]->Add(RMSUnknown_Unknown1_Text[loop], 0, wxEXPAND | wxBOTTOM, 2);
		RMSUnknown_Unknown1_Holder[loop]->Add(RMSUnknown_Unknown1[loop], 1, wxEXPAND);
		RMSUnknown_Unknown1_Grid->Add(RMSUnknown_Unknown1_Holder[loop], 1, wxEXPAND);
	}
	RMSUnknown_DataArea->Add(RMSUnknown_Unknown1_Grid, 0, wxEXPAND);

	RMSUnknown->Add(RMSUnknown_ListArea, 1, wxEXPAND);
	RMSUnknown->Add(RMSUnknown_DataArea, 3, wxEXPAND | wxLEFT, 5);

	Unknown_ScrollSpace->Add(Unknowns_Space_UnknownLevel, 0, wxEXPAND);
	Unknown_ScrollSpace->Add(Unknowns_Unknown1_Grid, 0, wxEXPAND | wxTOP, 5);
	Unknown_ScrollSpace->Add(Unknowns_Space_Pointer1, 0, wxEXPAND | wxTOP, 5);
	Unknown_ScrollSpace->Add(RMSBaseZones, 0, wxEXPAND | wxTOP, 5);
	Unknown_ScrollSpace->Add(Unknowns_Space_Pointer2, 0, wxEXPAND | wxTOP, 5);
	Unknown_ScrollSpace->Add(RMSTerrain, 0, wxEXPAND | wxTOP, 5);
	Unknown_ScrollSpace->Add(Unknowns_Space_Pointer3, 0, wxEXPAND | wxTOP, 5);
	Unknown_ScrollSpace->Add(RMSUnit, 0, wxEXPAND | wxTOP, 5);
	Unknown_ScrollSpace->Add(Unknowns_Space_Pointer4, 0, wxEXPAND | wxTOP, 5);
	Unknown_ScrollSpace->Add(RMSUnknown, 0, wxEXPAND | wxTOP, 5);

	Unknown_Scroller->SetSizer(Unknown_ScrollSpace);
	Unknown_Scroller->SetScrollRate(0, 15);

	Unknowns->Add(Unknowns_ListArea, 21, wxEXPAND | wxRIGHT, 5);
	Unknowns->Add(Unknown_Scroller, 65, wxEXPAND);

	Unknown_Main->Add(Unknown_UnknownPointer_Text, 0, wxTOP | wxLEFT, 5);
	Unknown_Main->Add(Unknown_UnknownPointer, 0, wxLEFT, 5);
	Unknown_Main->Add(Unknowns, 1, wxEXPAND | wxALL, 5);

	Unknowns_Paste->Enable(false);
	Unknowns_PasteInsert->Enable(false);
	RMSBaseZones_Paste->Enable(false);
	RMSBaseZones_PasteInsert->Enable(false);
	RMSTerrain_Paste->Enable(false);
	RMSTerrain_PasteInsert->Enable(false);
	RMSUnit_Paste->Enable(false);
	RMSUnit_PasteInsert->Enable(false);
	RMSUnknown_Paste->Enable(false);
	RMSUnknown_PasteInsert->Enable(false);

	Tab_Unknown->SetSizer(Unknown_Main);

	Connect(Unknowns_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRandomMapSearch));
	Connect(Unknowns_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRandomMapSearch));
	Connect(Unknowns_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnRandomMapSelect));
	Connect(Unknowns_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnRandomMapSelect));
	Connect(Unknowns_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnRandomMapSelect));
	Connect(Unknowns_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRandomMapAdd));
	Connect(Unknowns_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRandomMapInsert));
	Connect(Unknowns_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRandomMapDelete));
	Connect(Unknowns_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRandomMapCopy));
	Connect(Unknowns_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRandomMapPaste));
	Connect(Unknowns_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRandomMapPasteInsert));
	Connect(RMSBaseZones_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneSearch));
	Connect(RMSBaseZones_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneSearch));
	Connect(RMSBaseZones_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneSelect));
	Connect(RMSBaseZones_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneSelect));
	Connect(RMSBaseZones_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneSelect));
	Connect(RMSBaseZones_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneAdd));
	Connect(RMSBaseZones_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneInsert));
	Connect(RMSBaseZones_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneDelete));
	Connect(RMSBaseZones_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneCopy));
	Connect(RMSBaseZones_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZonePaste));
	Connect(RMSBaseZones_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZonePasteInsert));
	Connect(RMSBaseZones_CopyToMaps->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneCopyToMaps));
	Connect(RMSTerrain_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainSearch));
	Connect(RMSTerrain_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainSearch));
	Connect(RMSTerrain_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainSelect));
	Connect(RMSTerrain_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainSelect));
	Connect(RMSTerrain_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainSelect));
	Connect(RMSTerrain_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainAdd));
	Connect(RMSTerrain_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainInsert));
	Connect(RMSTerrain_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainDelete));
	Connect(RMSTerrain_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainCopy));
	Connect(RMSTerrain_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainPaste));
	Connect(RMSTerrain_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainPasteInsert));
	Connect(RMSTerrain_CopyToMaps->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainCopyToMaps));
	Connect(RMSUnit_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSUnitSearch));
	Connect(RMSUnit_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSUnitSearch));
	Connect(RMSUnit_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnRMSUnitSelect));
	Connect(RMSUnit_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnRMSUnitSelect));
	Connect(RMSUnit_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnRMSUnitSelect));
	Connect(RMSUnit_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitAdd));
	Connect(RMSUnit_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitInsert));
	Connect(RMSUnit_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitDelete));
	Connect(RMSUnit_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitCopy));
	Connect(RMSUnit_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitPaste));
	Connect(RMSUnit_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitPasteInsert));
	Connect(RMSUnit_CopyToMaps->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitCopyToMaps));
	Connect(RMSUnknown_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownSearch));
	Connect(RMSUnknown_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownSearch));
	Connect(RMSUnknown_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownSelect));
	Connect(RMSUnknown_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownSelect));
	Connect(RMSUnknown_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownSelect));
	Connect(RMSUnknown_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownAdd));
	Connect(RMSUnknown_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownInsert));
	Connect(RMSUnknown_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownDelete));
	Connect(RMSUnknown_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownCopy));
	Connect(RMSUnknown_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownPaste));
	Connect(RMSUnknown_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownPasteInsert));
	Connect(RMSUnknown_CopyToMaps->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownCopyToMaps));

    randomMapTimer.Connect(randomMapTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnRandomMapTimer), NULL, this);
    rmBaseTimer.Connect(rmBaseTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnRMSBaseZoneTimer), NULL, this);
    rmTerrainTimer.Connect(rmTerrainTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnRMSTerrainTimer), NULL, this);
    rmUnitTimer.Connect(rmUnitTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnRMSUnitTimer), NULL, this);
    rmUnknownTimer.Connect(rmUnknownTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnRMSUnknownTimer), NULL, this);
	Unknowns_UnknownLevel->Connect(Unknowns_UnknownLevel->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSBaseZones_Unknown1->Connect(RMSBaseZones_Unknown1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSTerrain_Unknown1[1]->Connect(RMSTerrain_Unknown1[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSUnknown_Unknown1[1]->Connect(RMSUnknown_Unknown1[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSUnit_Unit->Connect(RMSUnit_Unit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
}

void AGE_Frame::OnKillFocus_Unknown(wxFocusEvent &event)
{
	event.Skip();
	if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
	if(event.GetId() == Unknowns_UnknownLevel->GetId())
	{
		ListRandomMaps();
	}
	else if(event.GetId() == RMSBaseZones_Unknown1->GetId())
	{
		ListRMSBaseZones();
	}
	else if(event.GetId() == RMSTerrain_Unknown1[1]->GetId())
	{
		ListRMSTerrains();
	}
	else if(event.GetId() == RMSUnit_Unit->GetId())
	{
		ListRMSUnits();
	}
	else if(event.GetId() == RMSUnknown_Unknown1[1]->GetId())
	{
		ListRMSUnknowns();
	}
}
