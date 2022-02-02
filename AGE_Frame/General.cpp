#include "Common.h"
#include "../AGE_Frame.h"

void AGE_Frame::ListMapData()
{
    wxCommandEvent E;
    OnMapsRefresh(E);
}

void AGE_Frame::OnVariableCalc(wxFocusEvent &event)
{
    event.Skip();
    int32_t result = 0;

    if(!General_CalcBoxes[0]->IsEmpty())
    {
        try
        {
            result = lexical_cast<int32_t>(General_CalcBoxes[0]->GetValue()) & 0xFF;
        }
        catch(const bad_lexical_cast&){}
    }

    if(!General_CalcBoxes[1]->IsEmpty())
    {
        try
        {
            result += (lexical_cast<int32_t>(General_CalcBoxes[1]->GetValue()) & 0xFF) << 8;
        }
        catch(const bad_lexical_cast&){}
    }

    if(!General_CalcBoxes[2]->IsEmpty())
    {
        try
        {
            result += (lexical_cast<int32_t>(General_CalcBoxes[2]->GetValue()) & 0xFF) << 16;
        }
        catch(const bad_lexical_cast&){}
    }

    if(!General_CalcBoxes[3]->IsEmpty())
    {
        try
        {
            result += (lexical_cast<int32_t>(General_CalcBoxes[3]->GetValue()) & 0xFF) << 24;
        }
        catch(const bad_lexical_cast&){}
    }

    General_CalcBoxes[4]->ChangeValue(lexical_cast<std::string>(result));
}

void AGE_Frame::OnVariableCalcReverse(wxFocusEvent &event)
{
    event.Skip();
    if(General_CalcBoxes[4]->IsEmpty()) return;

    int32_t result;
    try
    {
        result = lexical_cast<int32_t>(General_CalcBoxes[4]->GetValue());
    }
    catch(const bad_lexical_cast&)
    {
        result = 0;
    }

    General_CalcBoxes[0]->ChangeValue(lexical_cast<std::string>(result & 0xFF));
    result >>= 8;
    General_CalcBoxes[1]->ChangeValue(lexical_cast<std::string>(result & 0xFF));
    result >>= 8;
    General_CalcBoxes[2]->ChangeValue(lexical_cast<std::string>(result & 0xFF));
    result >>= 8;
    General_CalcBoxes[3]->ChangeValue(lexical_cast<std::string>(result & 0xFF));
}

void AGE_Frame::OnMapsRefresh(wxCommandEvent &event)
{
    for (AGETextCtrl *box : uiGroupMaps) box->clear();
    General_VFP->prepend(&dataset->TerrainBlock.VirtualFunctionPtr);
    General_MapPointer->prepend(&dataset->TerrainBlock.MapPointer);
    General_MapWidth->prepend(&dataset->TerrainBlock.MapWidth);
    General_MapHeight->prepend(&dataset->TerrainBlock.MapHeight);
    General_WorldWidth->prepend(&dataset->TerrainBlock.WorldWidth);
    General_WorldHeight->prepend(&dataset->TerrainBlock.WorldHeight);
    if(GenieVersion >= genie::GV_AoE)
    {
        General_TileSizesPadding->prepend(&dataset->TerrainBlock.PaddingTS);
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

    MapRowOffset->prepend(&dataset->TerrainBlock.MapRowOffset);
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
    SearchMapPtr->prepend(&dataset->TerrainBlock.SearchMapPtr);
    SearchMapRowsPtr->prepend(&dataset->TerrainBlock.SearchMapRowsPtr);
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
    RMS_MapsPtr->prepend(&dataset->RandomMaps.RandomMapsPtr);
    if(GenieVersion >= genie::GV_AoKA)
    {
        General_TTKnown[0]->prepend(&dataset->TimeSlice);
        General_TTKnown[1]->prepend(&dataset->UnitKillRate);
        General_TTKnown[2]->prepend(&dataset->UnitKillTotal);
        General_TTKnown[3]->prepend(&dataset->UnitHitPointRate);
        General_TTKnown[4]->prepend(&dataset->UnitHitPointTotal);
        General_TTKnown[5]->prepend(&dataset->RazingKillRate);
        General_TTKnown[6]->prepend(&dataset->RazingKillTotal);
        General_TTKnown[7]->prepend(&dataset->TechTree.TotalUnitTechGroups);
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
    for (AGETextCtrl *box : uiGroupMaps) box->update();
}

void AGE_Frame::CreateGeneralControls()
{
    Tab_General = new ATabPage(TabBar_Main);

    General_Main = new wxBoxSizer(wxVERTICAL);
    General_TopRow = new wxBoxSizer(wxHORIZONTAL);
    General_Refresh = new wxButton(Tab_General, wxID_ANY, "Refresh");
    General_CalcBoxes_Text = new SolidText(Tab_General, " Variable Converter *");
    General_CalcBoxes_Text->SetToolTip("From four 8 bit integers to one 32 bit integer or vice versa");
    General_CalcBoxesMiddle_Text = new SolidText(Tab_General, " = ");
    for(size_t loop = 0; loop < 5; ++loop)
    General_CalcBoxes[loop] = new wxTextCtrl(Tab_General, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1));
    General_Scroller = new AScrolled(Tab_General);
    General_ScrollSpace = new wxBoxSizer(wxVERTICAL);

    const wxString SWUNKNOWNSINFO = "Unknowns 2 to 5 are in the beginning of the file,\nright after civilization count (first of the two) and\nbefore terrain tables";
    General_Variables2_Grid = new wxBoxSizer(wxHORIZONTAL);
    General_Variables1_Holder = new wxStaticBoxSizer(wxHORIZONTAL, General_Scroller, "Star Wars Unknowns");
    General_SUnknown2_Holder = new wxBoxSizer(wxVERTICAL);
    General_SUnknown2_Text = new SolidText(General_Scroller, " Unkown 2 *");
    General_SUnknown2 = new NumberControl(CLong, General_Scroller, this, &uiGroupMaps);
    General_SUnknown2->SetToolTip(SWUNKNOWNSINFO);
    General_SUnknown3_Holder = new wxBoxSizer(wxVERTICAL);
    General_SUnknown3_Text = new SolidText(General_Scroller, " Unkown 3 *");
    General_SUnknown3 = new NumberControl(CLong, General_Scroller, this, &uiGroupMaps);
    General_SUnknown3->SetToolTip(SWUNKNOWNSINFO);
    General_SUnknown4_Holder = new wxBoxSizer(wxVERTICAL);
    General_SUnknown4_Text = new SolidText(General_Scroller, " Unkown 4 *");
    General_SUnknown4 = new NumberControl(CLong, General_Scroller, this, &uiGroupMaps);
    General_SUnknown4->SetToolTip(SWUNKNOWNSINFO);
    General_SUnknown5_Holder = new wxBoxSizer(wxVERTICAL);
    General_SUnknown5_Text = new SolidText(General_Scroller, " Unkown 5 *");
    General_SUnknown5 = new NumberControl(CLong, General_Scroller, this, &uiGroupMaps);
    General_SUnknown5->SetToolTip(SWUNKNOWNSINFO);
    General_SUnknown7_Holder = new wxBoxSizer(wxVERTICAL);
    General_SUnknown7_Text = new SolidText(General_Scroller, " Unkown 7 *");
    General_SUnknown7 = new NumberControl(CUByte, General_Scroller, this, &uiGroupMaps);
    General_SUnknown7->SetToolTip("In the file this is\nright after civilizations and\nbefore techs");
    General_SUnknown8_Holder = new wxBoxSizer(wxVERTICAL);
    General_SUnknown8_Text = new SolidText(General_Scroller, " Unkown 8 *");
    General_SUnknown8 = new NumberControl(CUByte, General_Scroller, this, &uiGroupMaps);
    General_SUnknown8->SetToolTip("In the file this is\nright after techs and\nbefore technology trees");

    General_VFP_Holder = new wxBoxSizer(wxVERTICAL);
    General_VFP_Text = new SolidText(General_Scroller, " __vfptr");
    General_VFP = new NumberControl(CULong, General_Scroller, this, &uiGroupMaps);
    General_MapPointer_Holder = new wxBoxSizer(wxVERTICAL);
    General_MapPointer_Text = new SolidText(General_Scroller, " Map Pointer");
    General_MapPointer = new NumberControl(CULong, General_Scroller, this, &uiGroupMaps);
    General_MapWidth_Holder = new wxBoxSizer(wxVERTICAL);
    General_MapWidth_Text = new SolidText(General_Scroller, " Map Width");
    General_MapWidth = new NumberControl(CLong, General_Scroller, this, &uiGroupMaps);
    General_MapHeight_Holder = new wxBoxSizer(wxVERTICAL);
    General_MapHeight_Text = new SolidText(General_Scroller, " Map Height");
    General_MapHeight = new NumberControl(CLong, General_Scroller, this, &uiGroupMaps);
    General_WorldWidth_Holder = new wxBoxSizer(wxVERTICAL);
    General_WorldWidth_Text = new SolidText(General_Scroller, " World Width");
    General_WorldWidth = new NumberControl(CLong, General_Scroller, this, &uiGroupMaps);
    General_WorldHeight_Holder = new wxBoxSizer(wxVERTICAL);
    General_WorldHeight_Text = new SolidText(General_Scroller, " World Height");
    General_WorldHeight = new NumberControl(CLong, General_Scroller, this, &uiGroupMaps);
    General_TileSizesPadding_Holder = new wxBoxSizer(wxVERTICAL);
    General_TileSizesPadding_Text = new SolidText(General_Scroller, " Tile Sizes Padding");
    General_TileSizesPadding = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);

    General_TileSizes_Text = new SolidText(General_Scroller, " Tile Sizes   19 x (Width, Height, Delta Y)   1st is flat tile, then 2 x 8 elevation tiles, then 2 1:1 tiles");
    General_TileSizes_Grid = new wxFlexGridSizer(5, 0, 0);

    MapRowOffset_Sizer = new wxBoxSizer(wxVERTICAL);
    MapRowOffset_Text = new SolidText(General_Scroller, " Map Row Offset");
    MapRowOffset = new NumberControl(CULong, General_Scroller, this, &uiGroupMaps);
    MapMinX_Sizer = new wxBoxSizer(wxVERTICAL);
    MapMinX_Text = new SolidText(General_Scroller, " Map Min X");
    MapMinX = new NumberControl(CFloat, General_Scroller, this, &uiGroupMaps);
    MapMinY_Sizer = new wxBoxSizer(wxVERTICAL);
    MapMinY_Text = new SolidText(General_Scroller, " Map Min Y");
    MapMinY = new NumberControl(CFloat, General_Scroller, this, &uiGroupMaps);
    MapMaxX_Sizer = new wxBoxSizer(wxVERTICAL);
    MapMaxX_Text = new SolidText(General_Scroller, " Map Max X");
    MapMaxX = new NumberControl(CFloat, General_Scroller, this, &uiGroupMaps);
    MapMaxY_Sizer = new wxBoxSizer(wxVERTICAL);
    MapMaxY_Text = new SolidText(General_Scroller, " Map Max Y");
    MapMaxY = new NumberControl(CFloat, General_Scroller, this, &uiGroupMaps);
    MapMaxXplus1_Sizer = new wxBoxSizer(wxVERTICAL);
    MapMaxXplus1_Text = new SolidText(General_Scroller, " Map Max X + 1");
    MapMaxXplus1 = new NumberControl(CFloat, General_Scroller, this, &uiGroupMaps);
    MapMaxYplus1_Sizer = new wxBoxSizer(wxVERTICAL);
    MapMaxYplus1_Text = new SolidText(General_Scroller, " Map Max Y + 1");
    MapMaxYplus1 = new NumberControl(CFloat, General_Scroller, this, &uiGroupMaps);

    MaxTerrain_Sizer = new wxBoxSizer(wxVERTICAL);
    MaxTerrain_Text = new SolidText(General_Scroller, " Max Terrain");
    MaxTerrain = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);
    TileWidth_Sizer = new wxBoxSizer(wxVERTICAL);
    TileWidth_Text = new SolidText(General_Scroller, " Tile Width");
    TileWidth = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);
    TileHeight_Sizer = new wxBoxSizer(wxVERTICAL);
    TileHeight_Text = new SolidText(General_Scroller, " Tile Height");
    TileHeight = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);
    TileHalfHeight_Sizer = new wxBoxSizer(wxVERTICAL);
    TileHalfHeight_Text = new SolidText(General_Scroller, " Tile Half Height");
    TileHalfHeight = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);
    TileHalfWidth_Sizer = new wxBoxSizer(wxVERTICAL);
    TileHalfWidth_Text = new SolidText(General_Scroller, " Tile Half Width");
    TileHalfWidth = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);
    ElevHeight_Sizer = new wxBoxSizer(wxVERTICAL);
    ElevHeight_Text = new SolidText(General_Scroller, " Elevation Height");
    ElevHeight = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);
    CurRow_Sizer = new wxBoxSizer(wxVERTICAL);
    CurRow_Text = new SolidText(General_Scroller, " Current Row");
    CurRow = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);
    CurCol_Sizer = new wxBoxSizer(wxVERTICAL);
    CurCol_Text = new SolidText(General_Scroller, " Current Col");
    CurCol = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);
    BlockBegRow_Sizer = new wxBoxSizer(wxVERTICAL);
    BlockBegRow_Text = new SolidText(General_Scroller, " Block Start Row");
    BlockBegRow = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);
    BlockEndRow_Sizer = new wxBoxSizer(wxVERTICAL);
    BlockEndRow_Text = new SolidText(General_Scroller, " Block End Row");
    BlockEndRow = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);
    BlockBegCol_Sizer = new wxBoxSizer(wxVERTICAL);
    BlockBegCol_Text = new SolidText(General_Scroller, " Block Start Col");
    BlockBegCol = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);
    BlockEndCol_Sizer = new wxBoxSizer(wxVERTICAL);
    BlockEndCol_Text = new SolidText(General_Scroller, " Block End Col");
    BlockEndCol = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps);

    SearchMapPtr_Sizer = new wxBoxSizer(wxVERTICAL);
    SearchMapPtr_Text = new SolidText(General_Scroller, " Search Map Ptr");
    SearchMapPtr = new NumberControl(CULong, General_Scroller, this, &uiGroupMaps);
    SearchMapRowsPtr_Sizer = new wxBoxSizer(wxVERTICAL);
    SearchMapRowsPtr_Text = new SolidText(General_Scroller, " Search Map Rows");
    SearchMapRowsPtr = new NumberControl(CULong, General_Scroller, this, &uiGroupMaps);
    AnyFrameChange_Sizer = new wxBoxSizer(wxVERTICAL);
    AnyFrameChange_Text = new SolidText(General_Scroller, " Any Frame Change");
    AnyFrameChange = new NumberControl(CUByte, General_Scroller, this, &uiGroupMaps);

    MapVisibleFlag_Sizer = new wxBoxSizer(wxVERTICAL);
    MapVisibleFlag_Text = new SolidText(General_Scroller, " Map Visible Flag");
    MapVisibleFlag = new NumberControl(CUByte, General_Scroller, this, &uiGroupMaps);
    FogFlag_Sizer = new wxBoxSizer(wxVERTICAL);
    FogFlag_Text = new SolidText(General_Scroller, " Fog Flag");
    FogFlag = new NumberControl(CUByte, General_Scroller, this, &uiGroupMaps);

    General_TerrainRendering_Text = new SolidText(General_Scroller, " Miscellaneous useless terrain data");
    General_TerrainRendering_Grid = new wxFlexGridSizer(8, 5, 5);
    General_Something_Grid1 = new wxFlexGridSizer(16, 0, 0);
    General_Something_Grid2 = new wxFlexGridSizer(8, 0, 0);
    for (wxBoxSizer *&sizer : General_TileSizes_Sizers)
    sizer = new wxBoxSizer(wxHORIZONTAL);
    for (AGETextCtrl *&box : General_TileSizes)
    box = new NumberControl(CShort, General_Scroller, this, &uiGroupMaps, true, AGETextCtrl::SMALL);
    for (AGETextCtrl *&box : General_SomeBytes)
    box = new NumberControl(CUByte, General_Scroller, this, &uiGroupMaps, true, AGETextCtrl::SMALL);
    for (AGETextCtrl *&box : General_Something)
    box = new NumberControl(CULong, General_Scroller, this, &uiGroupMaps, true, AGETextCtrl::NORMAL);

    General_TopRow->Add(General_Refresh, 0, wxRIGHT, 100);
    for(size_t loop = 0; loop < 4; ++loop)
    General_TopRow->Add(General_CalcBoxes[loop]);
    General_TopRow->Add(General_CalcBoxesMiddle_Text);
    General_TopRow->Add(General_CalcBoxes[4]);
    General_TopRow->Add(General_CalcBoxes_Text);

    for(size_t loop = 0, tile = 0; loop < General_TileSizes.size();)
    {
        General_TileSizes_Sizers[tile]->Add(General_TileSizes[loop++]);
        General_TileSizes_Sizers[tile]->Add(General_TileSizes[loop++]);
        General_TileSizes_Sizers[tile++]->Add(General_TileSizes[loop++]);
    }
    for (wxBoxSizer *&sizer : General_TileSizes_Sizers)
    General_TileSizes_Grid->Add(sizer);

    MapRowOffset_Sizer->Add(MapRowOffset_Text);
    MapMinX_Sizer->Add(MapMinX_Text);
    MapMinY_Sizer->Add(MapMinY_Text);
    MapMaxX_Sizer->Add(MapMaxX_Text);
    MapMaxY_Sizer->Add(MapMaxY_Text);
    MapMaxXplus1_Sizer->Add(MapMaxXplus1_Text);
    MapMaxYplus1_Sizer->Add(MapMaxYplus1_Text);
    MapRowOffset_Sizer->Add(MapRowOffset);
    MapMinX_Sizer->Add(MapMinX);
    MapMinY_Sizer->Add(MapMinY);
    MapMaxX_Sizer->Add(MapMaxX);
    MapMaxY_Sizer->Add(MapMaxY);
    MapMaxXplus1_Sizer->Add(MapMaxXplus1);
    MapMaxYplus1_Sizer->Add(MapMaxYplus1);
    MaxTerrain_Sizer->Add(MaxTerrain_Text);
    TileWidth_Sizer->Add(TileWidth_Text);
    TileHeight_Sizer->Add(TileHeight_Text);
    TileHalfHeight_Sizer->Add(TileHalfHeight_Text);
    TileHalfWidth_Sizer->Add(TileHalfWidth_Text);
    ElevHeight_Sizer->Add(ElevHeight_Text);
    CurRow_Sizer->Add(CurRow_Text);
    MaxTerrain_Sizer->Add(MaxTerrain);
    TileWidth_Sizer->Add(TileWidth);
    TileHeight_Sizer->Add(TileHeight);
    TileHalfHeight_Sizer->Add(TileHalfHeight);
    TileHalfWidth_Sizer->Add(TileHalfWidth);
    ElevHeight_Sizer->Add(ElevHeight);
    CurRow_Sizer->Add(CurRow);
    CurCol_Sizer->Add(CurCol_Text);
    BlockBegRow_Sizer->Add(BlockBegRow_Text);
    BlockEndRow_Sizer->Add(BlockEndRow_Text);
    BlockBegCol_Sizer->Add(BlockBegCol_Text);
    BlockEndCol_Sizer->Add(BlockEndCol_Text);
    SearchMapPtr_Sizer->Add(SearchMapPtr_Text);
    SearchMapRowsPtr_Sizer->Add(SearchMapRowsPtr_Text);
    CurCol_Sizer->Add(CurCol);
    BlockBegRow_Sizer->Add(BlockBegRow);
    BlockEndRow_Sizer->Add(BlockEndRow);
    BlockBegCol_Sizer->Add(BlockBegCol);
    BlockEndCol_Sizer->Add(BlockEndCol);
    SearchMapPtr_Sizer->Add(SearchMapPtr);
    SearchMapRowsPtr_Sizer->Add(SearchMapRowsPtr);
    AnyFrameChange_Sizer->Add(AnyFrameChange_Text);
    MapVisibleFlag_Sizer->Add(MapVisibleFlag_Text);
    FogFlag_Sizer->Add(FogFlag_Text);
    AnyFrameChange_Sizer->Add(AnyFrameChange);
    MapVisibleFlag_Sizer->Add(MapVisibleFlag);
    FogFlag_Sizer->Add(FogFlag);

    General_TerrainRendering_Grid->Add(MapRowOffset_Sizer);
    General_TerrainRendering_Grid->Add(MapMinX_Sizer);
    General_TerrainRendering_Grid->Add(MapMinY_Sizer);
    General_TerrainRendering_Grid->Add(MapMaxX_Sizer);
    General_TerrainRendering_Grid->Add(MapMaxY_Sizer);
    General_TerrainRendering_Grid->Add(MapMaxXplus1_Sizer);
    General_TerrainRendering_Grid->Add(MapMaxYplus1_Sizer);
    General_TerrainRendering_Grid->Add(MaxTerrain_Sizer);
    General_TerrainRendering_Grid->Add(TileWidth_Sizer);
    General_TerrainRendering_Grid->Add(TileHeight_Sizer);
    General_TerrainRendering_Grid->Add(TileHalfHeight_Sizer);
    General_TerrainRendering_Grid->Add(TileHalfWidth_Sizer);
    General_TerrainRendering_Grid->Add(ElevHeight_Sizer);
    General_TerrainRendering_Grid->Add(CurRow_Sizer);
    General_TerrainRendering_Grid->Add(CurCol_Sizer);
    General_TerrainRendering_Grid->Add(BlockBegRow_Sizer);
    General_TerrainRendering_Grid->Add(BlockEndRow_Sizer);
    General_TerrainRendering_Grid->Add(BlockBegCol_Sizer);
    General_TerrainRendering_Grid->Add(BlockEndCol_Sizer);
    General_TerrainRendering_Grid->Add(SearchMapPtr_Sizer);
    General_TerrainRendering_Grid->Add(SearchMapRowsPtr_Sizer);
    General_TerrainRendering_Grid->Add(AnyFrameChange_Sizer);
    General_TerrainRendering_Grid->Add(MapVisibleFlag_Sizer);
    General_TerrainRendering_Grid->Add(FogFlag_Sizer);

    for(size_t loop = 0; loop < General_SomeBytes.size(); ++loop)
    General_Something_Grid1->Add(General_SomeBytes[loop]);
    for(size_t loop = 0; loop < General_Something.size(); ++loop)
    General_Something_Grid2->Add(General_Something[loop]);

    General_SUnknown7_Holder->Add(General_SUnknown7_Text);
    General_SUnknown7_Holder->Add(General_SUnknown7, 1, wxEXPAND);
    General_SUnknown8_Holder->Add(General_SUnknown8_Text);
    General_SUnknown8_Holder->Add(General_SUnknown8, 1, wxEXPAND);
    General_SUnknown2_Holder->Add(General_SUnknown2_Text);
    General_SUnknown2_Holder->Add(General_SUnknown2, 1, wxEXPAND);
    General_SUnknown3_Holder->Add(General_SUnknown3_Text);
    General_SUnknown3_Holder->Add(General_SUnknown3, 1, wxEXPAND);
    General_SUnknown4_Holder->Add(General_SUnknown4_Text);
    General_SUnknown4_Holder->Add(General_SUnknown4, 1, wxEXPAND);
    General_SUnknown5_Holder->Add(General_SUnknown5_Text);
    General_SUnknown5_Holder->Add(General_SUnknown5, 1, wxEXPAND);
    General_Variables1_Holder->Add(General_SUnknown2_Holder);
    General_Variables1_Holder->Add(General_SUnknown3_Holder, 0, wxLEFT, 5);
    General_Variables1_Holder->Add(General_SUnknown4_Holder, 0, wxLEFT, 5);
    General_Variables1_Holder->Add(General_SUnknown5_Holder, 0, wxLEFT, 5);
    General_Variables1_Holder->Add(General_SUnknown7_Holder, 0, wxLEFT, 5);
    General_Variables1_Holder->Add(General_SUnknown8_Holder, 0, wxLEFT, 5);

    General_VFP_Holder->Add(General_VFP_Text);
    General_VFP_Holder->Add(General_VFP);
    General_MapPointer_Holder->Add(General_MapPointer_Text);
    General_MapPointer_Holder->Add(General_MapPointer);
    General_MapWidth_Holder->Add(General_MapWidth_Text);
    General_MapWidth_Holder->Add(General_MapWidth);
    General_MapHeight_Holder->Add(General_MapHeight_Text);
    General_MapHeight_Holder->Add(General_MapHeight);
    General_WorldWidth_Holder->Add(General_WorldWidth_Text);
    General_WorldWidth_Holder->Add(General_WorldWidth);
    General_WorldHeight_Holder->Add(General_WorldHeight_Text);
    General_WorldHeight_Holder->Add(General_WorldHeight);
    General_TileSizesPadding_Holder->Add(General_TileSizesPadding_Text);
    General_TileSizesPadding_Holder->Add(General_TileSizesPadding);
    General_Variables2_Grid->Add(General_VFP_Holder);
    General_Variables2_Grid->Add(General_MapPointer_Holder, 0, wxLEFT, 5);
    General_Variables2_Grid->Add(General_MapWidth_Holder, 0, wxLEFT, 5);
    General_Variables2_Grid->Add(General_MapHeight_Holder, 0, wxLEFT, 5);
    General_Variables2_Grid->Add(General_WorldWidth_Holder, 0, wxLEFT, 5);
    General_Variables2_Grid->Add(General_WorldHeight_Holder, 0, wxLEFT, 5);
    General_Variables2_Grid->Add(General_TileSizesPadding_Holder, 0, wxLEFT, 5);

    General_ScrollSpace->Add(General_Variables1_Holder);
    General_ScrollSpace->Add(General_Variables2_Grid, 0, wxTOP | wxBOTTOM, 5);
    General_ScrollSpace->Add(General_TileSizes_Text);
    General_ScrollSpace->Add(General_TileSizes_Grid);
    General_ScrollSpace->Add(General_TerrainRendering_Grid, 0, wxTOP | wxBOTTOM, 5);
    General_ScrollSpace->Add(General_TerrainRendering_Text);
    General_ScrollSpace->Add(General_Something_Grid1);
    General_ScrollSpace->Add(General_Something_Grid2);

    General_Scroller->SetSizer(General_ScrollSpace);

    General_Main->Add(General_TopRow, 0, wxEXPAND | wxALL, 5);
    General_Main->Add(General_Scroller, 1, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 5);

    Tab_General->SetSizer(General_Main);

    General_Refresh->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapsRefresh, this);
    for(size_t loop = 0; loop < 4; ++loop)
    General_CalcBoxes[loop]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnVariableCalc, this);
    General_CalcBoxes[4]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnVariableCalcReverse, this);
}

void AGE_Frame::OnRandomMapSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListRandomMaps();
}

wxString AGE_Frame::GetRandomMapName(int index)
{
    if(GenieVersion >= genie::GV_AoK)
    {
        return "Map "+lexical_cast<std::string>(dataset->RandomMaps.Maps[index].MapID);
    }
    wxString Name;
    switch(index)
    {
        case 0: Name = "Small Islands ("; break;
        case 1: Name = "Large Islands ("; break;
        case 2: Name = "Coastal ("; break;
        case 3: Name = "Inland ("; break;
        case 4: Name = "Highland ("; break;
        case 5: Name = "Continental ("; break;
        case 6: Name = "Mediterranean ("; break;
        case 7: Name = "Hill Country ("; break;
        case 8: Name = "Narrows ("; break;
        case 9: Name = "Gigantic ("; break;
        default: Name = "Map (";
    }
    return Name += lexical_cast<std::string>(dataset->RandomMaps.Maps[index].MapID)+")";
}

void AGE_Frame::ListRandomMaps()
{
    InitRandomMaps();
    wxCommandEvent e;
    OnRandomMapSelect(e);
}

void AGE_Frame::InitRandomMaps()
{
    InitSearch(Unknowns_Search->GetValue().MakeLower(), Unknowns_Search_R->GetValue().MakeLower());

    Unknowns_ListV->Sweep();

    for(size_t loop = 0; loop < dataset->RandomMaps.Maps.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetRandomMapName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Unknowns_ListV->names.Add(Name);
            Unknowns_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(Unknowns_ListV, &RandomMapIDs);
}

void AGE_Frame::OnRandomMapSelect(wxCommandEvent &event)
{
    size_t selections = Unknowns_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Unknowns_ListV, RandomMapIDs);
    for (AGETextCtrl *box : uiGroupRandomMap) box->clear();
    genie::MapInfo *map_ptr;
    for (size_t sel = selections; sel-- > 0;)
    {
        map_ptr = &dataset->RandomMaps.Maps[RandomMapIDs[sel]];

        RMS_MapID->prepend(&map_ptr->MapID);
        RMS_LandData[0]->prepend(&map_ptr->BorderSouthWest);
        RMS_LandData[1]->prepend(&map_ptr->BorderNorthWest);
        RMS_LandData[2]->prepend(&map_ptr->BorderNorthEast);
        RMS_LandData[3]->prepend(&map_ptr->BorderSouthEast);
        RMS_LandData[4]->prepend(&map_ptr->BorderUsage);
        RMS_LandData[5]->prepend(&map_ptr->WaterShape);
        RMS_LandData[6]->prepend(&map_ptr->BaseTerrain);
        RMS_LandData[7]->prepend(&map_ptr->LandCoverage);
        RMS_LandData[8]->prepend(&map_ptr->UnusedID);
        RMS_LandsPtr->prepend(&map_ptr->MapLandsPtr);
        RMS_TerrainsPtr->prepend(&map_ptr->MapTerrainsPtr);
        RMS_UnitsPtr->prepend(&map_ptr->MapUnitsPtr);
        RMS_ElevationsPtr->prepend(&map_ptr->MapElevationsPtr);
    }
    SetStatusText(wxString::Format("Selections: %zu    Selected random map: %d",
        selections, selections > 0 ? RandomMapIDs.front() : -1), 0);
    for (AGETextCtrl *box : uiGroupRandomMap) box->update();
    ListMapLands();
    ListMapTerrains();
    ListMapUnits();
    ListMapElevations();
}

void AGE_Frame::OnRandomMapAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->RandomMaps.Maps);
    ListRandomMaps();
}

void AGE_Frame::OnRandomMapInsert(wxCommandEvent &event)
{
    size_t selections = Unknowns_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->RandomMaps.Maps, RandomMapIDs.front());
    ListRandomMaps();
}

void AGE_Frame::OnRandomMapDelete(wxCommandEvent &event)
{
    size_t selections = Unknowns_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->RandomMaps.Maps, RandomMapIDs);
    ListRandomMaps();
}

void AGE_Frame::OnRandomMapCopy(wxCommandEvent &event)
{
    size_t selections = Unknowns_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->RandomMaps.Maps, RandomMapIDs, copies.Map);
    Unknowns_Paste->Enable(true);
    Unknowns_PasteInsert->Enable(true);
    Unknowns_ListV->SetFocus();
}

void AGE_Frame::OnRandomMapPaste(wxCommandEvent &event)
{
    size_t selections = Unknowns_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->RandomMaps.Maps, RandomMapIDs, copies.Map);
    ListRandomMaps();
}

void AGE_Frame::OnRandomMapPasteInsert(wxCommandEvent &event)
{
    size_t selections = Unknowns_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->RandomMaps.Maps, RandomMapIDs.front(), copies.Map);
    ListRandomMaps();
}

void AGE_Frame::OnMapLandSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListMapLands();
}

wxString AGE_Frame::GetMapLandName(int index)
{
    return "Land "+lexical_cast<std::string>(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapLands[index].LandID);
}

void AGE_Frame::ListMapLands()
{
    InitSearch(RMS_Land_Search->GetValue().MakeLower(), RMS_Land_Search_R->GetValue().MakeLower());

    RMS_Land_ListV->Sweep();

    if (dataset->RandomMaps.Maps.size() && RandomMapIDs.size())
    for(size_t loop = 0; loop < dataset->RandomMaps.Maps[RandomMapIDs.front()].MapLands.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetMapLandName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            RMS_Land_ListV->names.Add(Name);
            RMS_Land_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(RMS_Land_ListV, &UnknownFSIDs);

    wxCommandEvent e;
    OnMapLandSelect(e);
}

void AGE_Frame::OnMapLandSelect(wxCommandEvent &event)
{
    size_t selections = RMS_Land_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, RMS_Land_ListV, UnknownFSIDs);
    for (AGETextCtrl *box : uiGroupRMBase) box->clear();

    genie::MapLand * land_ptr;
    for(size_t sel = selections; sel--> 0;)
    {
        land_ptr = &dataset->RandomMaps.Maps[RandomMapIDs.front()].MapLands[UnknownFSIDs[sel]];

        RMS_Land_LandID->prepend(&land_ptr->LandID);
        RMS_Land_BaseTerrain->prepend(&land_ptr->Terrain);
        RMS_Land_PlayerSpacing->prepend(&land_ptr->LandSpacing);
        RMS_Land_BaseSize->prepend(&land_ptr->BaseSize);
        RMS_Land_Zone->prepend(&land_ptr->Zone);
        RMS_Land_PlacementType->prepend(&land_ptr->PlacementType);
        RMS_Land_Padding1->prepend(&land_ptr->Padding1);
        RMS_Land_X->prepend(&land_ptr->BaseX);
        RMS_Land_Y->prepend(&land_ptr->BaseY);
        RMS_Land_LandProportion->prepend(&land_ptr->LandProportion);
        RMS_Land_ByPlayerFlag->prepend(&land_ptr->ByPlayerFlag);
        RMS_Land_Padding2->prepend(&land_ptr->Padding2);
        RMS_Land_StartAreaRadius->prepend(&land_ptr->StartAreaRadius);
        RMS_Land_TerrainEdgeFade->prepend(&land_ptr->TerrainEdgeFade);
        RMS_Land_Clumpiness->prepend(&land_ptr->Clumpiness);
    }

    for (AGETextCtrl *box : uiGroupRMBase) box->update();
}

void AGE_Frame::OnMapLandAdd(wxCommandEvent &event)
{
    size_t selections = Unknowns_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapLands);
    ListMapLands();
}

void AGE_Frame::OnMapLandInsert(wxCommandEvent &event)
{
    size_t selections = RMS_Land_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapLands, UnknownFSIDs.front());
    ListMapLands();
}

void AGE_Frame::OnMapLandDelete(wxCommandEvent &event)
{
    size_t selections = RMS_Land_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapLands, UnknownFSIDs);
    ListMapLands();
}

void AGE_Frame::OnMapLandCopy(wxCommandEvent &event)
{
    size_t selections = RMS_Land_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapLands, UnknownFSIDs, copies.MapLand);
    RMS_Land_Paste->Enable(true);
    RMS_Land_PasteInsert->Enable(true);
    RMS_Land_ListV->SetFocus();
}

void AGE_Frame::OnMapLandPaste(wxCommandEvent &event)
{
    size_t selections = RMS_Land_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapLands, UnknownFSIDs, copies.MapLand);
    ListMapLands();
}

void AGE_Frame::OnMapLandPasteInsert(wxCommandEvent &event)
{
    size_t selections = RMS_Land_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapLands, UnknownFSIDs.front(), copies.MapLand);
    ListMapLands();
}

void AGE_Frame::OnMapLandCopyToMaps(wxCommandEvent &event)
{
    for(size_t loop=1; loop < RandomMapIDs.size(); ++loop)
    {
        dataset->RandomMaps.Maps[RandomMapIDs[loop]].MapLands = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapLands;
    }
}

void AGE_Frame::OnMapTerrainSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListMapTerrains();
}

wxString AGE_Frame::GetMapTerrainName(int Terrain)
{
    wxString Name = FormatInt(Terrain) + " ";
    if(dataset->TerrainBlock.Terrains.size() <= Terrain) return Name + "Nonexistent Terrain";
    if(!dataset->TerrainBlock.Terrains[Terrain].Name.empty())
    {
        return Name + dataset->TerrainBlock.Terrains[Terrain].Name;
    }
    return Name + "New Terrain";
}

void AGE_Frame::ListMapTerrains()
{
    InitSearch(RMS_Terrain_Search->GetValue().MakeLower(), RMS_Terrain_Search_R->GetValue().MakeLower());

    RMS_Terrain_ListV->Sweep();

    if (dataset->RandomMaps.Maps.size() && RandomMapIDs.size())
    for(size_t loop = 0; loop < dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetMapTerrainName(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains[loop].Terrain);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            RMS_Terrain_ListV->names.Add(Name);
            RMS_Terrain_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(RMS_Terrain_ListV, &UnknownSSIDs);

    wxCommandEvent e;
    OnMapTerrainSelect(e);
}

void AGE_Frame::OnMapTerrainSelect(wxCommandEvent &event)
{
    size_t selections = RMS_Terrain_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, RMS_Terrain_ListV, UnknownSSIDs);
    for (AGETextCtrl *box : uiGroupRMTerrain) box->clear();

    genie::MapTerrain * terrain_ptr;
    for(size_t sel = selections; sel--> 0;)
    {
        terrain_ptr = &dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains[UnknownSSIDs[sel]];

        RMS_TerrainData[0]->prepend(&terrain_ptr->Proportion);
        RMS_TerrainData[1]->prepend(&terrain_ptr->Terrain);
        RMS_TerrainData[2]->prepend(&terrain_ptr->ClumpCount);
        RMS_TerrainData[3]->prepend(&terrain_ptr->EdgeSpacing);
        RMS_TerrainData[4]->prepend(&terrain_ptr->PlacementTerrain);
        RMS_TerrainData[5]->prepend(&terrain_ptr->Clumpiness);
    }

    for (AGETextCtrl *box : uiGroupRMTerrain) box->update();
}

void AGE_Frame::OnMapTerrainAdd(wxCommandEvent &event)
{
    size_t selections = Unknowns_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains);
    ListMapTerrains();
}

void AGE_Frame::OnMapTerrainInsert(wxCommandEvent &event)
{
    size_t selections = RMS_Terrain_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains, UnknownSSIDs.front());
    ListMapTerrains();
}

void AGE_Frame::OnMapTerrainDelete(wxCommandEvent &event)
{
    size_t selections = RMS_Terrain_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains, UnknownSSIDs);
    ListMapTerrains();
}

void AGE_Frame::OnMapTerrainCopy(wxCommandEvent &event)
{
    size_t selections = RMS_Terrain_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains, UnknownSSIDs, copies.MapTerrain);
    RMS_Terrain_Paste->Enable(true);
    RMS_Terrain_PasteInsert->Enable(true);
    RMS_Terrain_ListV->SetFocus();
}

void AGE_Frame::OnMapTerrainPaste(wxCommandEvent &event)
{
    size_t selections = RMS_Terrain_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains, UnknownSSIDs, copies.MapTerrain);
    ListMapTerrains();
}

void AGE_Frame::OnMapTerrainPasteInsert(wxCommandEvent &event)
{
    size_t selections = RMS_Terrain_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains, UnknownSSIDs.front(), copies.MapTerrain);
    ListMapTerrains();
}

void AGE_Frame::OnMapTerrainCopyToMaps(wxCommandEvent &event)
{
    for(size_t loop=1; loop < RandomMapIDs.size(); ++loop)
    {
        dataset->RandomMaps.Maps[RandomMapIDs[loop]].MapTerrains = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapTerrains;
    }
}

void AGE_Frame::OnMapUnitSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListMapUnits();
}

void AGE_Frame::ListMapUnits()
{
    InitSearch(RMS_Unit_Search->GetValue().MakeLower(), RMS_Unit_Search_R->GetValue().MakeLower());

    RMS_Unit_ListV->Sweep();

    if (dataset->RandomMaps.Maps.size() && RandomMapIDs.size())
    for(size_t loop = 0; loop < dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetUnitLineUnitName(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits[loop].Unit);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            RMS_Unit_ListV->names.Add(Name);
            RMS_Unit_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(RMS_Unit_ListV, &UnknownTSIDs);

    wxCommandEvent e;
    OnMapUnitSelect(e);
}

void AGE_Frame::OnMapUnitSelect(wxCommandEvent &event)
{
    size_t selections = RMS_Unit_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, RMS_Unit_ListV, UnknownTSIDs);
    for (AGETextCtrl *box : uiGroupRMUnit) box->clear();

    genie::MapUnit * object_ptr;
    for(size_t sel = selections; sel--> 0;)
    {
        object_ptr = &dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits[UnknownTSIDs[sel]];

        RMS_Unit_Unit->prepend(&object_ptr->Unit);
        RMS_Unit_HostTerrain->prepend(&object_ptr->HostTerrain);
        RMS_Unit_GroupPlacing->prepend(&object_ptr->GroupPlacing);
        RMS_Unit_ScaleFlag->prepend(&object_ptr->ScaleFlag);
        RMS_Unit_Padding1->prepend(&object_ptr->Padding1);
        RMS_Unit_ObjectsPerPlayer->prepend(&object_ptr->ObjectsPerGroup);
        RMS_Unit_Fluctuation->prepend(&object_ptr->Fluctuation);
        RMS_Unit_GroupsPerPlayer->prepend(&object_ptr->GroupsPerPlayer);
        RMS_Unit_GroupArea->prepend(&object_ptr->GroupArea);
        RMS_Unit_PlayerID->prepend(&object_ptr->PlayerID);
        RMS_Unit_SetPlaceForAllPlayers->prepend(&object_ptr->SetPlaceForAllPlayers);
        RMS_Unit_MinDistanceToPlayers->prepend(&object_ptr->MinDistanceToPlayers);
        RMS_Unit_MaxDistanceToPlayers->prepend(&object_ptr->MaxDistanceToPlayers);
    }

    for (AGETextCtrl *box : uiGroupRMUnit) box->update();
}

void AGE_Frame::OnMapUnitAdd(wxCommandEvent &event)
{
    size_t selections = Unknowns_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits);
    ListMapUnits();
}

void AGE_Frame::OnMapUnitInsert(wxCommandEvent &event)
{
    size_t selections = RMS_Unit_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits, UnknownTSIDs.front());
    ListMapUnits();
}

void AGE_Frame::OnMapUnitDelete(wxCommandEvent &event)
{
    size_t selections = RMS_Unit_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits, UnknownTSIDs);
    ListMapUnits();
}

void AGE_Frame::OnMapUnitCopy(wxCommandEvent &event)
{
    size_t selections = RMS_Unit_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits, UnknownTSIDs, copies.MapUnit);
    RMS_Unit_Paste->Enable(true);
    RMS_Unit_PasteInsert->Enable(true);
    RMS_Unit_ListV->SetFocus();
}

void AGE_Frame::OnMapUnitPaste(wxCommandEvent &event)
{
    size_t selections = RMS_Unit_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits, UnknownTSIDs, copies.MapUnit);
    ListMapUnits();
}

void AGE_Frame::OnMapUnitPasteInsert(wxCommandEvent &event)
{
    size_t selections = RMS_Unit_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits, UnknownTSIDs.front(), copies.MapUnit);
    ListMapUnits();
}

void AGE_Frame::OnMapUnitCopyToMaps(wxCommandEvent &event)
{
    for(size_t loop=1; loop < RandomMapIDs.size(); ++loop)
    {
        dataset->RandomMaps.Maps[RandomMapIDs[loop]].MapUnits = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapUnits;
    }
}

void AGE_Frame::OnMapElevationSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListMapElevations();
}

void AGE_Frame::ListMapElevations()
{
    InitSearch(RMS_Elevation_Search->GetValue().MakeLower(), RMS_Elevation_Search_R->GetValue().MakeLower());

    RMS_Elevation_ListV->Sweep();

    if (dataset->RandomMaps.Maps.size() && RandomMapIDs.size())
    for(size_t loop = 0; loop < dataset->RandomMaps.Maps[RandomMapIDs.front()].MapElevations.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - Elevation (useless)";
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            RMS_Elevation_ListV->names.Add(Name);
            RMS_Elevation_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(RMS_Elevation_ListV, &Unknown4SIDs);

    wxCommandEvent e;
    OnMapElevationSelect(e);
}

void AGE_Frame::OnMapElevationSelect(wxCommandEvent &event)
{
    size_t selections = RMS_Elevation_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, RMS_Elevation_ListV, Unknown4SIDs);
    for (AGETextCtrl *box : uiGroupRMUnknown) box->clear();

    genie::MapElevation * elevation_ptr;
    for(size_t sel = selections; sel--> 0;)
    {
        elevation_ptr = &dataset->RandomMaps.Maps[RandomMapIDs.front()].MapElevations[Unknown4SIDs[sel]];

        RMS_ElevationData[0]->prepend(&elevation_ptr->Proportion);
        RMS_ElevationData[1]->prepend(&elevation_ptr->Terrain);
        RMS_ElevationData[2]->prepend(&elevation_ptr->ClumpCount);
        RMS_ElevationData[3]->prepend(&elevation_ptr->BaseTerrain);
        RMS_ElevationData[4]->prepend(&elevation_ptr->BaseElevation);
        RMS_ElevationData[5]->prepend(&elevation_ptr->TileSpacing);
    }

    for (AGETextCtrl *box : uiGroupRMUnknown) box->update();
}

void AGE_Frame::OnMapElevationAdd(wxCommandEvent &event)
{
    size_t selections = Unknowns_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapElevations);
    ListMapElevations();
}

void AGE_Frame::OnMapElevationInsert(wxCommandEvent &event)
{
    size_t selections = RMS_Elevation_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapElevations, Unknown4SIDs.front());
    ListMapElevations();
}

void AGE_Frame::OnMapElevationDelete(wxCommandEvent &event)
{
    size_t selections = RMS_Elevation_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapElevations, Unknown4SIDs);
    ListMapElevations();
}

void AGE_Frame::OnMapElevationCopy(wxCommandEvent &event)
{
    size_t selections = RMS_Elevation_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapElevations, Unknown4SIDs, copies.MapElevation);
    RMS_Elevation_Paste->Enable(true);
    RMS_Elevation_PasteInsert->Enable(true);
    RMS_Elevation_ListV->SetFocus();
}

void AGE_Frame::OnMapElevationPaste(wxCommandEvent &event)
{
    size_t selections = RMS_Elevation_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapElevations, Unknown4SIDs, copies.MapElevation);
    ListMapElevations();
}

void AGE_Frame::OnMapElevationPasteInsert(wxCommandEvent &event)
{
    size_t selections = RMS_Elevation_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->RandomMaps.Maps[RandomMapIDs.front()].MapElevations, Unknown4SIDs.front(), copies.MapElevation);
    ListMapElevations();
}

void AGE_Frame::OnMapElevationCopyToMaps(wxCommandEvent &event)
{
    for(size_t loop=1; loop < RandomMapIDs.size(); ++loop)
    {
        dataset->RandomMaps.Maps[RandomMapIDs[loop]].MapElevations = dataset->RandomMaps.Maps[RandomMapIDs.front()].MapElevations;
    }
}

void AGE_Frame::CreateUnknownControls()
{
    Tab_Unknown = new ATabPage(TabBar_Main);

    Unknown_Main = new wxBoxSizer(wxVERTICAL);
    RMS_Scroller = new AScrolled(Tab_Unknown);
    Unknown_ScrollSpace = new wxBoxSizer(wxVERTICAL);

    wxString OVERWRITTEN = "Is overwritten";

    RMS_MapsPtr_Text = new SolidText(Tab_Unknown, " Random Maps Pointer *");
    RMS_MapsPtr = new NumberControl(CLong, Tab_Unknown, this, &uiGroupMaps, true, AGETextCtrl::LARGE);
    RMS_MapsPtr->SetToolTip(OVERWRITTEN);

    Unknowns = new wxStaticBoxSizer(wxHORIZONTAL, Tab_Unknown, "Random Map Scripts (Required in AoE/RoR)");
    Unknowns_ListArea = new wxBoxSizer(wxVERTICAL);
    Unknowns_Search = new wxTextCtrl(Tab_Unknown, wxID_ANY);
    Unknowns_Search_R = new wxTextCtrl(Tab_Unknown, wxID_ANY);
    Unknowns_ListV = new ProperList(Tab_Unknown, ASize(200, 220));
    Unknowns_Buttons = new wxGridSizer(3, 0, 0);
    Unknowns_Add = new wxButton(Tab_Unknown, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Unknowns_Insert = new wxButton(Tab_Unknown, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Unknowns_Delete = new wxButton(Tab_Unknown, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Unknowns_Copy = new wxButton(Tab_Unknown, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Unknowns_Paste = new wxButton(Tab_Unknown, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Unknowns_PasteInsert = new wxButton(Tab_Unknown, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));

    RMS_MapID_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_MapID_Text = new SolidText(RMS_Scroller, " Script Number");
    RMS_MapID = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRandomMap, false);
    RMS_LandData_Grid = new wxFlexGridSizer(5, 5, 5);
    for(size_t loop = 0; loop < RMS_LandData.size(); ++loop)
    {
        RMS_LandData_Holder[loop] = new wxBoxSizer(wxVERTICAL);
        RMS_LandData[loop] = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRandomMap);
    }
    wxString MAPEDGEBUFFER = "Map Edge Buffer";
    RMS_LandData_Text[0] = new SolidText(RMS_Scroller, " Border SW *");
    RMS_LandData[0]->SetToolTip(MAPEDGEBUFFER);
    RMS_LandData_Text[1] = new SolidText(RMS_Scroller, " Border NW *");
    RMS_LandData[1]->SetToolTip(MAPEDGEBUFFER);
    RMS_LandData_Text[2] = new SolidText(RMS_Scroller, " Border NE *");
    RMS_LandData[2]->SetToolTip(MAPEDGEBUFFER);
    RMS_LandData_Text[3] = new SolidText(RMS_Scroller, " Border SE *");
    RMS_LandData[3]->SetToolTip(MAPEDGEBUFFER);
    RMS_LandData_Text[4] = new SolidText(RMS_Scroller, " Border Usage % *");
    RMS_LandData[4]->SetToolTip("Fuzzy map edges\n% of border area covered with non-base terrain");
    RMS_LandData_Text[5] = new SolidText(RMS_Scroller, " Water Shape *");
    RMS_LandData[5]->SetToolTip("Land Placement Edge");
    RMS_LandData_Text[6] = new SolidText(RMS_Scroller, " Base Terrain *");
    RMS_LandData[6]->SetToolTip("Used on the borders as well");
    RMS_LandData_Text[7] = new SolidText(RMS_Scroller, " Land Cover % *");
    RMS_LandData[7]->SetToolTip("Can be over 100");
    RMS_LandData_Text[8] = new SolidText(RMS_Scroller, " Unused ID");

    RMSMapLands = new wxStaticBoxSizer(wxHORIZONTAL, RMS_Scroller, "Base Land Data");
    RMS_Land_ListArea = new wxBoxSizer(wxVERTICAL);
    RMS_Land_Search = new wxTextCtrl(RMS_Scroller, wxID_ANY);
    RMS_Land_Search_R = new wxTextCtrl(RMS_Scroller, wxID_ANY);
    RMS_Land_ListV = new ProperList(RMS_Scroller, ASize(140, 100));
    RMS_Land_Buttons = new wxGridSizer(3, 0, 0);
    RMS_Land_Add = new wxButton(RMS_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    RMS_Land_Insert = new wxButton(RMS_Scroller, wxID_ANY, "Ins New", wxDefaultPosition, wxSize(10, -1));
    RMS_Land_Delete = new wxButton(RMS_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    RMS_Land_Copy = new wxButton(RMS_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    RMS_Land_Paste = new wxButton(RMS_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    RMS_Land_PasteInsert = new wxButton(RMS_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    RMS_Land_CopyToMaps = new wxButton(RMS_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(10, -1));

    RMS_Land_LandID_Grid = new wxFlexGridSizer(4, 5, 5);

    RMS_Land_LandID_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_LandID_Text = new SolidText(RMS_Scroller, " Land ID");
    RMS_Land_LandID = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMBase, false);
    RMS_Land_BaseTerrain_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_BaseTerrain_Text = new SolidText(RMS_Scroller, " Base Terrain");
    RMS_Land_BaseTerrain = new NumberControl(CUByte, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_PlayerSpacing_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_PlayerSpacing_Text = new SolidText(RMS_Scroller, " Land Spacing *");
    RMS_Land_PlayerSpacing = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_PlayerSpacing->SetToolTip("Non-base terrain (like river) space between players.\nIf too large, they won't be created.");
    RMS_Land_BaseSize_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_BaseSize_Text = new SolidText(RMS_Scroller, " Base Size");
    RMS_Land_BaseSize = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMBase);

    RMS_Land_Zone_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_Zone_Text = new SolidText(RMS_Scroller, " Zone");
    RMS_Land_Zone = new NumberControl(CUByte, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_PlacementType_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_PlacementType_Text = new SolidText(RMS_Scroller, " Placement Type *");
    RMS_Land_PlacementType = new NumberControl(CUByte, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_PlacementType->SetToolTip("Base placement\n0   Random\n1   Given\n2   Spaced");

    RMS_Land_X_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_X_Text = new SolidText(RMS_Scroller, " Base X");
    RMS_Land_X = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_Y_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_Y_Text = new SolidText(RMS_Scroller, " Base Y");
    RMS_Land_Y = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMBase);

    RMS_Land_LandProportion_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_LandProportion_Text = new SolidText(RMS_Scroller, " Land Proportion");
    RMS_Land_LandProportion = new NumberControl(CUByte, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_ByPlayerFlag_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_ByPlayerFlag_Text = new SolidText(RMS_Scroller, " Player Placement *");
    RMS_Land_ByPlayerFlag = new NumberControl(CUByte, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_ByPlayerFlag->SetToolTip("0   Not by player\n1   By player, overlap\n2   By player, seperate");

    RMS_Land_StartAreaRadius_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_StartAreaRadius_Text = new SolidText(RMS_Scroller, " Player Base Size *");
    RMS_Land_StartAreaRadius = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_StartAreaRadius->SetToolTip("This area cannot contain different elevations or terrains\nTerrain edge fading affects this");
    RMS_Land_TerrainEdgeFade_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_TerrainEdgeFade_Text = new SolidText(RMS_Scroller, " Terrain Edge Fade *");
    RMS_Land_TerrainEdgeFade = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_TerrainEdgeFade->SetToolTip("Used to fuzz edges");
    RMS_Land_Clumpiness_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_Clumpiness_Text = new SolidText(RMS_Scroller, " Clumpiness Factor");
    RMS_Land_Clumpiness = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_Padding1_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_Padding1_Text = new SolidText(RMS_Scroller, " Padding 1 *");
    RMS_Land_Padding1 = new NumberControl(CShort, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_Padding1->SetToolTip("Completely useless");
    RMS_Land_Padding2_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Land_Padding2_Text = new SolidText(RMS_Scroller, " Padding 2 *");
    RMS_Land_Padding2 = new NumberControl(CShort, RMS_Scroller, this, &uiGroupRMBase);
    RMS_Land_Padding2->SetToolTip("Completely useless");

    RMSTerrain = new wxStaticBoxSizer(wxHORIZONTAL, RMS_Scroller, "Terrains placed on the map");
    RMS_Terrain_ListArea = new wxBoxSizer(wxVERTICAL);
    RMS_Terrain_Search = new wxTextCtrl(RMS_Scroller, wxID_ANY);
    RMS_Terrain_Search_R = new wxTextCtrl(RMS_Scroller, wxID_ANY);
    RMS_Terrain_ListV = new ProperList(RMS_Scroller, ASize(140, 100));
    RMS_Terrain_Buttons = new wxGridSizer(3, 0, 0);
    RMS_Terrain_Add = new wxButton(RMS_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    RMS_Terrain_Insert = new wxButton(RMS_Scroller, wxID_ANY, "Ins New", wxDefaultPosition, wxSize(10, -1));
    RMS_Terrain_Delete = new wxButton(RMS_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    RMS_Terrain_Copy = new wxButton(RMS_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    RMS_Terrain_Paste = new wxButton(RMS_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    RMS_Terrain_PasteInsert = new wxButton(RMS_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    RMS_Terrain_CopyToMaps = new wxButton(RMS_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(10, -1));

    RMS_TerrainData_Grid = new wxFlexGridSizer(4, 5, 5);
    for(size_t loop = 0; loop < RMS_TerrainData.size(); ++loop)
    {
        RMS_TerrainData_Holder[loop] = new wxBoxSizer(wxVERTICAL);
        RMS_TerrainData[loop] = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMTerrain, false);
    }
    RMS_TerrainData_Text[0] = new SolidText(RMS_Scroller, " Proportion *");
    RMS_TerrainData[0]->SetToolTip("% of the total map area");
    RMS_TerrainData_Text[1] = new SolidText(RMS_Scroller, " Terrain");
    RMS_TerrainData_Text[2] = new SolidText(RMS_Scroller, " Clump Count *");
    RMS_TerrainData[2]->SetToolTip("Clusters in the map");
    RMS_TerrainData_Text[3] = new SolidText(RMS_Scroller, " Terrain Spacing *");
    RMS_TerrainData[3]->SetToolTip("Minimum distance to another terrain");
    RMS_TerrainData_Text[4] = new SolidText(RMS_Scroller, " Placement Terrain");
    RMS_TerrainData_Text[5] = new SolidText(RMS_Scroller, " Clumpiness Factor");

    RMSUnit = new wxStaticBoxSizer(wxHORIZONTAL, RMS_Scroller, "Units placed on the map (Some may appear anyway)");
    RMS_Unit_ListArea = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_Search = new wxTextCtrl(RMS_Scroller, wxID_ANY);
    RMS_Unit_Search_R = new wxTextCtrl(RMS_Scroller, wxID_ANY);
    RMS_Unit_ListV = new ProperList(RMS_Scroller, ASize(140, 250));
    RMS_Unit_Buttons = new wxGridSizer(3, 0, 0);
    RMS_Unit_Add = new wxButton(RMS_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    RMS_Unit_Insert = new wxButton(RMS_Scroller, wxID_ANY, "Ins New", wxDefaultPosition, wxSize(10, -1));
    RMS_Unit_Delete = new wxButton(RMS_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    RMS_Unit_Copy = new wxButton(RMS_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    RMS_Unit_Paste = new wxButton(RMS_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    RMS_Unit_PasteInsert = new wxButton(RMS_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    RMS_Unit_CopyToMaps = new wxButton(RMS_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(10, -1));

    RMS_Unit_Unknown1_Grid = new wxFlexGridSizer(4, 5, 5);
    RMS_Unit_Unit_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_Unit_Text = new SolidText(RMS_Scroller, " Unit");
    RMS_Unit_Unit = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMUnit, false);
    RMS_Unit_HostTerrain_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_HostTerrain_Text = new SolidText(RMS_Scroller, " Placement Terrain");
    RMS_Unit_HostTerrain = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_GroupPlacing_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_GroupPlacing_Text = new SolidText(RMS_Scroller, " Group Mode *");
    RMS_Unit_GroupPlacing = new NumberControl(CUByte, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_GroupPlacing->SetToolTip("0   Single unit\n1   Place group\n2   Place cluster");
    RMS_Unit_ScaleFlag_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_ScaleFlag_Text = new SolidText(RMS_Scroller, " Scale by Map Size");
    RMS_Unit_ScaleFlag = new NumberControl(CUByte, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_ObjectsPerPlayer_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_ObjectsPerPlayer_Text = new SolidText(RMS_Scroller, " Units per Group");
    RMS_Unit_ObjectsPerPlayer = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_Fluctuation_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_Fluctuation_Text = new SolidText(RMS_Scroller, " Fluctuation *");
    RMS_Unit_Fluctuation = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_Fluctuation->SetToolTip("Max randomness in the number of units per group");
    RMS_Unit_GroupsPerPlayer_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_GroupsPerPlayer_Text = new SolidText(RMS_Scroller, " Groups per Player");
    RMS_Unit_GroupsPerPlayer = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_GroupArea_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_GroupArea_Text = new SolidText(RMS_Scroller, " Group Radius *");
    RMS_Unit_GroupArea = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_GroupArea->SetToolTip("Max distance from the center of the group");
    RMS_Unit_PlayerID_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_PlayerID_Text = new SolidText(RMS_Scroller, " Player # *");
    RMS_Unit_PlayerID = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_PlayerID->SetToolTip("-1 for every player");
    RMS_Unit_SetPlaceForAllPlayers_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_SetPlaceForAllPlayers_Text = new SolidText(RMS_Scroller, " Base Land # *");
    RMS_Unit_SetPlaceForAllPlayers = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_SetPlaceForAllPlayers->SetToolTip("0+  Place on all matching lands\n-1   Place anywhere\n-2   Avoid land spots");
    RMS_Unit_MinDistanceToPlayers_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_MinDistanceToPlayers_Text = new SolidText(RMS_Scroller, " Min Dist to Players");
    RMS_Unit_MinDistanceToPlayers = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_MaxDistanceToPlayers_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_MaxDistanceToPlayers_Text = new SolidText(RMS_Scroller, " Max Dist to Players *");
    RMS_Unit_MaxDistanceToPlayers = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_MaxDistanceToPlayers->SetToolTip("Don't use 0 here for units that are owned at start.\n0 is okay for other units (gold/bushes/gazelle/etc).\nYou can use -1 as a wildcard for units that are owned at start.");
    RMS_Unit_Padding1_Holder = new wxBoxSizer(wxVERTICAL);
    RMS_Unit_Padding1_Text = new SolidText(RMS_Scroller, " Padding 1 *");
    RMS_Unit_Padding1 = new NumberControl(CShort, RMS_Scroller, this, &uiGroupRMUnit);
    RMS_Unit_Padding1->SetToolTip("Completely useless");

    RMSUnknown = new wxStaticBoxSizer(wxHORIZONTAL, RMS_Scroller, "Elevations placed on the map (These are ignored)");
    RMS_Elevation_ListArea = new wxBoxSizer(wxVERTICAL);
    RMS_Elevation_Search = new wxTextCtrl(RMS_Scroller, wxID_ANY);
    RMS_Elevation_Search_R = new wxTextCtrl(RMS_Scroller, wxID_ANY);
    RMS_Elevation_ListV = new ProperList(RMS_Scroller, ASize(140, 100));
    RMS_Elevation_Buttons = new wxGridSizer(3, 0, 0);
    RMS_Elevation_Add = new wxButton(RMS_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    RMS_Elevation_Insert = new wxButton(RMS_Scroller, wxID_ANY, "Ins New", wxDefaultPosition, wxSize(10, -1));
    RMS_Elevation_Delete = new wxButton(RMS_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    RMS_Elevation_Copy = new wxButton(RMS_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    RMS_Elevation_Paste = new wxButton(RMS_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    RMS_Elevation_PasteInsert = new wxButton(RMS_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    RMS_Elevation_CopyToMaps = new wxButton(RMS_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(10, -1));

    RMS_ElevationData_Grid = new wxFlexGridSizer(4, 5, 5);
    for(size_t loop = 0; loop < RMS_ElevationData.size(); ++loop)
    {
        RMS_ElevationData_Holder[loop] = new wxBoxSizer(wxVERTICAL);
        RMS_ElevationData[loop] = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRMUnknown, false);
    }
    RMS_ElevationData_Text[0] = new SolidText(RMS_Scroller, " Proportion *");
    RMS_ElevationData[0]->SetToolTip("% of the total map area");
    RMS_ElevationData_Text[1] = new SolidText(RMS_Scroller, " Terrain");
    RMS_ElevationData_Text[2] = new SolidText(RMS_Scroller, " Clump Count *");
    RMS_ElevationData[2]->SetToolTip("Clusters in the map");
    RMS_ElevationData_Text[3] = new SolidText(RMS_Scroller, " Base Terrain");
    RMS_ElevationData_Text[4] = new SolidText(RMS_Scroller, " Base Elevation");
    RMS_ElevationData_Text[5] = new SolidText(RMS_Scroller, " Tile Spacing");

    wxGridSizer *pointers_box = new wxFlexGridSizer(4, 0, 5);
    RMS_LandsPtr_Text = new SolidText(RMS_Scroller, " Lands Pointer *");
    RMS_LandsPtr = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRandomMap);
    RMS_LandsPtr->SetToolTip(OVERWRITTEN);

    RMS_TerrainsPtr_Text = new SolidText(RMS_Scroller, " Terrains Pointer *");
    RMS_TerrainsPtr = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRandomMap);
    RMS_TerrainsPtr->SetToolTip(OVERWRITTEN);

    RMS_UnitsPtr_Text = new SolidText(RMS_Scroller, " Units Pointer *");
    RMS_UnitsPtr = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRandomMap);
    RMS_UnitsPtr->SetToolTip(OVERWRITTEN);

    RMS_ElevationsPtr_Text = new SolidText(RMS_Scroller, " Elevations Pointer *");
    RMS_ElevationsPtr = new NumberControl(CLong, RMS_Scroller, this, &uiGroupRandomMap);
    RMS_ElevationsPtr->SetToolTip(OVERWRITTEN);

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

    RMS_MapID_Holder->Add(RMS_MapID_Text);
    RMS_MapID_Holder->Add(RMS_MapID);
    RMS_LandData_Grid->Add(RMS_MapID_Holder);
    for(size_t loop = 0; loop < RMS_LandData.size(); ++loop)
    {
        RMS_LandData_Holder[loop]->Add(RMS_LandData_Text[loop]);
        RMS_LandData_Holder[loop]->Add(RMS_LandData[loop]);
        RMS_LandData_Grid->Add(RMS_LandData_Holder[loop]);
    }

    RMS_Land_Buttons->Add(RMS_Land_Add, 1, wxEXPAND);
    RMS_Land_Buttons->Add(RMS_Land_Delete, 1, wxEXPAND);
    RMS_Land_Buttons->Add(RMS_Land_Insert, 1, wxEXPAND);
    RMS_Land_Buttons->Add(RMS_Land_Copy, 1, wxEXPAND);
    RMS_Land_Buttons->Add(RMS_Land_Paste, 1, wxEXPAND);
    RMS_Land_Buttons->Add(RMS_Land_PasteInsert, 1, wxEXPAND);

    RMS_Land_ListArea->Add(RMS_Land_Search, 0, wxEXPAND);
    RMS_Land_ListArea->Add(RMS_Land_Search_R, 0, wxEXPAND);
    RMS_Land_ListArea->Add(RMS_Land_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    RMS_Land_ListArea->Add(RMS_Land_Buttons, 0, wxEXPAND);
    RMS_Land_ListArea->Add(RMS_Land_CopyToMaps, 0, wxEXPAND | wxTOP, 2);

    RMS_Land_LandID_Holder->Add(RMS_Land_LandID_Text);
    RMS_Land_LandID_Holder->Add(RMS_Land_LandID);
    RMS_Land_BaseTerrain_Holder->Add(RMS_Land_BaseTerrain_Text);
    RMS_Land_BaseTerrain_Holder->Add(RMS_Land_BaseTerrain);
    RMS_Land_PlayerSpacing_Holder->Add(RMS_Land_PlayerSpacing_Text);
    RMS_Land_PlayerSpacing_Holder->Add(RMS_Land_PlayerSpacing);
    RMS_Land_BaseSize_Holder->Add(RMS_Land_BaseSize_Text);
    RMS_Land_BaseSize_Holder->Add(RMS_Land_BaseSize);
    RMS_Land_Zone_Holder->Add(RMS_Land_Zone_Text);
    RMS_Land_Zone_Holder->Add(RMS_Land_Zone);
    RMS_Land_PlacementType_Holder->Add(RMS_Land_PlacementType_Text);
    RMS_Land_PlacementType_Holder->Add(RMS_Land_PlacementType);
    RMS_Land_Padding1_Holder->Add(RMS_Land_Padding1_Text);
    RMS_Land_Padding1_Holder->Add(RMS_Land_Padding1);
    RMS_Land_X_Holder->Add(RMS_Land_X_Text);
    RMS_Land_X_Holder->Add(RMS_Land_X);
    RMS_Land_Y_Holder->Add(RMS_Land_Y_Text);
    RMS_Land_Y_Holder->Add(RMS_Land_Y);
    RMS_Land_LandProportion_Holder->Add(RMS_Land_LandProportion_Text);
    RMS_Land_LandProportion_Holder->Add(RMS_Land_LandProportion);
    RMS_Land_ByPlayerFlag_Holder->Add(RMS_Land_ByPlayerFlag_Text);
    RMS_Land_ByPlayerFlag_Holder->Add(RMS_Land_ByPlayerFlag);
    RMS_Land_Padding2_Holder->Add(RMS_Land_Padding2_Text);
    RMS_Land_Padding2_Holder->Add(RMS_Land_Padding2);
    RMS_Land_StartAreaRadius_Holder->Add(RMS_Land_StartAreaRadius_Text);
    RMS_Land_StartAreaRadius_Holder->Add(RMS_Land_StartAreaRadius);
    RMS_Land_TerrainEdgeFade_Holder->Add(RMS_Land_TerrainEdgeFade_Text);
    RMS_Land_TerrainEdgeFade_Holder->Add(RMS_Land_TerrainEdgeFade);
    RMS_Land_Clumpiness_Holder->Add(RMS_Land_Clumpiness_Text);
    RMS_Land_Clumpiness_Holder->Add(RMS_Land_Clumpiness);
    RMS_Land_LandID_Grid->Add(RMS_Land_LandID_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_BaseTerrain_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_PlayerSpacing_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_BaseSize_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_Zone_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_PlacementType_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_X_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_Y_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_LandProportion_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_ByPlayerFlag_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_StartAreaRadius_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_TerrainEdgeFade_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_Clumpiness_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_Padding1_Holder);
    RMS_Land_LandID_Grid->Add(RMS_Land_Padding2_Holder);

    RMSMapLands->Add(RMS_Land_ListArea, 1, wxEXPAND);
    RMSMapLands->Add(RMS_Land_LandID_Grid, 3, wxEXPAND | wxLEFT, 5);

    RMS_Terrain_Buttons->Add(RMS_Terrain_Add, 1, wxEXPAND);
    RMS_Terrain_Buttons->Add(RMS_Terrain_Delete, 1, wxEXPAND);
    RMS_Terrain_Buttons->Add(RMS_Terrain_Insert, 1, wxEXPAND);
    RMS_Terrain_Buttons->Add(RMS_Terrain_Copy, 1, wxEXPAND);
    RMS_Terrain_Buttons->Add(RMS_Terrain_Paste, 1, wxEXPAND);
    RMS_Terrain_Buttons->Add(RMS_Terrain_PasteInsert, 1, wxEXPAND);

    RMS_Terrain_ListArea->Add(RMS_Terrain_Search, 0, wxEXPAND);
    RMS_Terrain_ListArea->Add(RMS_Terrain_Search_R, 0, wxEXPAND);
    RMS_Terrain_ListArea->Add(RMS_Terrain_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    RMS_Terrain_ListArea->Add(RMS_Terrain_Buttons, 0, wxEXPAND);
    RMS_Terrain_ListArea->Add(RMS_Terrain_CopyToMaps, 0, wxEXPAND | wxTOP, 2);

    for(size_t loop = 0; loop < RMS_TerrainData.size(); ++loop)
    {
        RMS_TerrainData_Holder[loop]->Add(RMS_TerrainData_Text[loop]);
        RMS_TerrainData_Holder[loop]->Add(RMS_TerrainData[loop]);
        RMS_TerrainData_Grid->Add(RMS_TerrainData_Holder[loop]);
    }

    RMSTerrain->Add(RMS_Terrain_ListArea, 1, wxEXPAND);
    RMSTerrain->Add(RMS_TerrainData_Grid, 3, wxEXPAND | wxLEFT, 5);

    RMS_Unit_Buttons->Add(RMS_Unit_Add, 1, wxEXPAND);
    RMS_Unit_Buttons->Add(RMS_Unit_Delete, 1, wxEXPAND);
    RMS_Unit_Buttons->Add(RMS_Unit_Insert, 1, wxEXPAND);
    RMS_Unit_Buttons->Add(RMS_Unit_Copy, 1, wxEXPAND);
    RMS_Unit_Buttons->Add(RMS_Unit_Paste, 1, wxEXPAND);
    RMS_Unit_Buttons->Add(RMS_Unit_PasteInsert, 1, wxEXPAND);

    RMS_Unit_ListArea->Add(RMS_Unit_Search, 0, wxEXPAND);
    RMS_Unit_ListArea->Add(RMS_Unit_Search_R, 0, wxEXPAND);
    RMS_Unit_ListArea->Add(RMS_Unit_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    RMS_Unit_ListArea->Add(RMS_Unit_Buttons, 0, wxEXPAND);
    RMS_Unit_ListArea->Add(RMS_Unit_CopyToMaps, 0, wxEXPAND | wxTOP, 2);

    RMS_Unit_Unit_Holder->Add(RMS_Unit_Unit_Text);
    RMS_Unit_Unit_Holder->Add(RMS_Unit_Unit);
    RMS_Unit_HostTerrain_Holder->Add(RMS_Unit_HostTerrain_Text);
    RMS_Unit_HostTerrain_Holder->Add(RMS_Unit_HostTerrain);
    RMS_Unit_GroupPlacing_Holder->Add(RMS_Unit_GroupPlacing_Text);
    RMS_Unit_GroupPlacing_Holder->Add(RMS_Unit_GroupPlacing);
    RMS_Unit_ScaleFlag_Holder->Add(RMS_Unit_ScaleFlag_Text);
    RMS_Unit_ScaleFlag_Holder->Add(RMS_Unit_ScaleFlag);
    RMS_Unit_Padding1_Holder->Add(RMS_Unit_Padding1_Text);
    RMS_Unit_Padding1_Holder->Add(RMS_Unit_Padding1);
    RMS_Unit_ObjectsPerPlayer_Holder->Add(RMS_Unit_ObjectsPerPlayer_Text);
    RMS_Unit_ObjectsPerPlayer_Holder->Add(RMS_Unit_ObjectsPerPlayer);
    RMS_Unit_Fluctuation_Holder->Add(RMS_Unit_Fluctuation_Text);
    RMS_Unit_Fluctuation_Holder->Add(RMS_Unit_Fluctuation);
    RMS_Unit_GroupsPerPlayer_Holder->Add(RMS_Unit_GroupsPerPlayer_Text);
    RMS_Unit_GroupsPerPlayer_Holder->Add(RMS_Unit_GroupsPerPlayer);
    RMS_Unit_GroupArea_Holder->Add(RMS_Unit_GroupArea_Text);
    RMS_Unit_GroupArea_Holder->Add(RMS_Unit_GroupArea);
    RMS_Unit_PlayerID_Holder->Add(RMS_Unit_PlayerID_Text);
    RMS_Unit_PlayerID_Holder->Add(RMS_Unit_PlayerID);
    RMS_Unit_SetPlaceForAllPlayers_Holder->Add(RMS_Unit_SetPlaceForAllPlayers_Text);
    RMS_Unit_SetPlaceForAllPlayers_Holder->Add(RMS_Unit_SetPlaceForAllPlayers);
    RMS_Unit_MinDistanceToPlayers_Holder->Add(RMS_Unit_MinDistanceToPlayers_Text);
    RMS_Unit_MinDistanceToPlayers_Holder->Add(RMS_Unit_MinDistanceToPlayers);
    RMS_Unit_MaxDistanceToPlayers_Holder->Add(RMS_Unit_MaxDistanceToPlayers_Text);
    RMS_Unit_MaxDistanceToPlayers_Holder->Add(RMS_Unit_MaxDistanceToPlayers);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_Unit_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_HostTerrain_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_GroupPlacing_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_ScaleFlag_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_ObjectsPerPlayer_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_Fluctuation_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_GroupsPerPlayer_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_GroupArea_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_PlayerID_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_SetPlaceForAllPlayers_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_MinDistanceToPlayers_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_MaxDistanceToPlayers_Holder);
    RMS_Unit_Unknown1_Grid->Add(RMS_Unit_Padding1_Holder);

    RMSUnit->Add(RMS_Unit_ListArea, 1, wxEXPAND);
    RMSUnit->Add(RMS_Unit_Unknown1_Grid, 3, wxEXPAND | wxLEFT, 5);

    RMS_Elevation_Buttons->Add(RMS_Elevation_Add, 1, wxEXPAND);
    RMS_Elevation_Buttons->Add(RMS_Elevation_Delete, 1, wxEXPAND);
    RMS_Elevation_Buttons->Add(RMS_Elevation_Insert, 1, wxEXPAND);
    RMS_Elevation_Buttons->Add(RMS_Elevation_Copy, 1, wxEXPAND);
    RMS_Elevation_Buttons->Add(RMS_Elevation_Paste, 1, wxEXPAND);
    RMS_Elevation_Buttons->Add(RMS_Elevation_PasteInsert, 1, wxEXPAND);

    RMS_Elevation_ListArea->Add(RMS_Elevation_Search, 0, wxEXPAND);
    RMS_Elevation_ListArea->Add(RMS_Elevation_Search_R, 0, wxEXPAND);
    RMS_Elevation_ListArea->Add(RMS_Elevation_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    RMS_Elevation_ListArea->Add(RMS_Elevation_Buttons, 0, wxEXPAND);
    RMS_Elevation_ListArea->Add(RMS_Elevation_CopyToMaps, 0, wxEXPAND | wxTOP, 2);

    for(size_t loop = 0; loop < RMS_ElevationData.size(); ++loop)
    {
        RMS_ElevationData_Holder[loop]->Add(RMS_ElevationData_Text[loop]);
        RMS_ElevationData_Holder[loop]->Add(RMS_ElevationData[loop]);
        RMS_ElevationData_Grid->Add(RMS_ElevationData_Holder[loop]);
    }

    RMSUnknown->Add(RMS_Elevation_ListArea, 1, wxEXPAND);
    RMSUnknown->Add(RMS_ElevationData_Grid, 3, wxEXPAND | wxLEFT, 5);

    Unknown_ScrollSpace->Add(RMS_LandData_Grid, 0, wxEXPAND | wxBOTTOM, 5);
    pointers_box->Add(RMS_LandsPtr_Text);
    pointers_box->Add(RMS_TerrainsPtr_Text);
    pointers_box->Add(RMS_UnitsPtr_Text);
    pointers_box->Add(RMS_ElevationsPtr_Text);
    Unknown_ScrollSpace->Add(RMSMapLands, 0, wxEXPAND | wxBOTTOM, 5);
    Unknown_ScrollSpace->Add(RMSTerrain, 0, wxEXPAND | wxBOTTOM, 5);
    Unknown_ScrollSpace->Add(RMSUnit, 0, wxEXPAND | wxBOTTOM, 5);
    pointers_box->Add(RMS_LandsPtr);
    pointers_box->Add(RMS_TerrainsPtr);
    pointers_box->Add(RMS_UnitsPtr);
    pointers_box->Add(RMS_ElevationsPtr);
    Unknown_ScrollSpace->Add(RMSUnknown, 0, wxEXPAND | wxBOTTOM, 5);
    Unknown_ScrollSpace->Add(pointers_box);

    RMS_Scroller->SetSizer(Unknown_ScrollSpace);

    Unknowns->Add(Unknowns_ListArea, 21, wxEXPAND | wxRIGHT, 5);
    Unknowns->Add(RMS_Scroller, 65, wxEXPAND);

    Unknown_Main->Add(RMS_MapsPtr_Text, 0, wxTOP | wxLEFT, 5);
    Unknown_Main->Add(RMS_MapsPtr, 0, wxLEFT, 5);
    Unknown_Main->Add(Unknowns, 1, wxEXPAND | wxALL, 5);

    Unknowns_Paste->Enable(false);
    Unknowns_PasteInsert->Enable(false);
    RMS_Land_Paste->Enable(false);
    RMS_Land_PasteInsert->Enable(false);
    RMS_Terrain_Paste->Enable(false);
    RMS_Terrain_PasteInsert->Enable(false);
    RMS_Unit_Paste->Enable(false);
    RMS_Unit_PasteInsert->Enable(false);
    RMS_Elevation_Paste->Enable(false);
    RMS_Elevation_PasteInsert->Enable(false);

    Tab_Unknown->SetSizer(Unknown_Main);

    Unknowns_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnRandomMapSearch, this);
    Unknowns_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnRandomMapSearch, this);
    Unknowns_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnRandomMapSelect, this);
    Unknowns_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnRandomMapAdd, this);
    Unknowns_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnRandomMapInsert, this);
    Unknowns_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnRandomMapDelete, this);
    Unknowns_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnRandomMapCopy, this);
    Unknowns_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnRandomMapPaste, this);
    Unknowns_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnRandomMapPasteInsert, this);
    RMS_Land_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnMapLandSearch, this);
    RMS_Land_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnMapLandSearch, this);
    RMS_Land_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnMapLandSelect, this);
    RMS_Land_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapLandAdd, this);
    RMS_Land_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapLandInsert, this);
    RMS_Land_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapLandDelete, this);
    RMS_Land_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapLandCopy, this);
    RMS_Land_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapLandPaste, this);
    RMS_Land_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapLandPasteInsert, this);
    RMS_Land_CopyToMaps->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapLandCopyToMaps, this);
    RMS_Terrain_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnMapTerrainSearch, this);
    RMS_Terrain_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnMapTerrainSearch, this);
    RMS_Terrain_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnMapTerrainSelect, this);
    RMS_Terrain_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapTerrainAdd, this);
    RMS_Terrain_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapTerrainInsert, this);
    RMS_Terrain_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapTerrainDelete, this);
    RMS_Terrain_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapTerrainCopy, this);
    RMS_Terrain_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapTerrainPaste, this);
    RMS_Terrain_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapTerrainPasteInsert, this);
    RMS_Terrain_CopyToMaps->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapTerrainCopyToMaps, this);
    RMS_Unit_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnMapUnitSearch, this);
    RMS_Unit_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnMapUnitSearch, this);
    RMS_Unit_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnMapUnitSelect, this);
    RMS_Unit_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapUnitAdd, this);
    RMS_Unit_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapUnitInsert, this);
    RMS_Unit_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapUnitDelete, this);
    RMS_Unit_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapUnitCopy, this);
    RMS_Unit_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapUnitPaste, this);
    RMS_Unit_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapUnitPasteInsert, this);
    RMS_Unit_CopyToMaps->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapUnitCopyToMaps, this);
    RMS_Elevation_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnMapElevationSearch, this);
    RMS_Elevation_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnMapElevationSearch, this);
    RMS_Elevation_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnMapElevationSelect, this);
    RMS_Elevation_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapElevationAdd, this);
    RMS_Elevation_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapElevationInsert, this);
    RMS_Elevation_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapElevationDelete, this);
    RMS_Elevation_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapElevationCopy, this);
    RMS_Elevation_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapElevationPaste, this);
    RMS_Elevation_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapElevationPasteInsert, this);
    RMS_Elevation_CopyToMaps->Bind(wxEVT_BUTTON, &AGE_Frame::OnMapElevationCopyToMaps, this);

    RMS_MapID->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListRandomMaps();
        }
    });
    RMS_MapID->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListRandomMaps();
    });
    RMS_Land_LandID->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListMapLands();
        }
    });
    RMS_Land_LandID->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListMapLands();
    });
    RMS_TerrainData[1]->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListMapTerrains();
        }
    });
    RMS_TerrainData[1]->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListMapTerrains();
    });
    RMS_ElevationData[1]->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListMapElevations();
        }
    });
    RMS_ElevationData[1]->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListMapElevations();
    });
    RMS_Unit_Unit->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListMapUnits();
        }
    });
    RMS_Unit_Unit->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListMapUnits();
    });
}
