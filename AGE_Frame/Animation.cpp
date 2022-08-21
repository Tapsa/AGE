#include "Common.h"
#include "../AGE_Frame.h"
#include "../EditableVersion.h"
#include "../Loaders.h"
#include "../Villager32.xpm"

const genie::Color ColorNotFound(74, 65, 42, 255);

void AGE_Frame::OnAnimationMenuOption(wxCommandEvent &event)
{
    switch (event.GetId())
    {
        case eShowSLP:
        {
            ShowSLP = event.IsChecked();
            setbearing = 0u;
            bearing = 0.f;

            Units_Main->Layout();
            Research_Main->Layout();
            Refresh();

            if (ShowSLP)
            {
                wxPoint parentPos = GetPosition();
                parentPos.x += minWindowWidth;
                slp_window = new wxFrame(this, wxID_ANY, "Sprites", parentPos, ASize(512, 600), KeepViewOnTop ? (wxSTAY_ON_TOP | wxDEFAULT_FRAME_STYLE) : wxDEFAULT_FRAME_STYLE);
                //slp_window->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
                slp_window->SetBackgroundColour(wxColour(240, 240, 240));
                slp_window->SetIcon(wxIcon(Villager32_xpm));
                slp_window->SetFont(font);
                APanel *panel = new APanel(slp_window);
                slp_view = new APanel(panel);//, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
                slp_next = new wxButton(panel, eNextFrame, "Show -> frame");
                slp_prev = new wxButton(panel, ePrevFrame, "Show <- frame");
                slp_first = new wxButton(panel, eFirstFrame, "Show first frame");
                wxColour back(ViewBackR, ViewBackG, ViewBackB);
                slp_background = new wxColourPickerCtrl(panel, ePickBgColor, back, wxDefaultPosition, wxDefaultSize, wxCLRP_SHOW_LABEL);
                slp_frame_export = new wxButton(panel, eExportFrame, "Export frame to PNGs");
                slp_frame_import = new wxButton(panel, eImportFrame, "Import PNGs to frame");
                slp_save = new wxButton(panel, eSaveSLP, "Save SLP");
                slp_tool = new wxButton(panel, eSLPTool, "SLP Tool");
                slp_zoom_btn = new wxButton(panel, eZoom, "Zoom: " + lexical_cast<std::string>(int(slp_zoom * 100)) + " %");
                slp_merge_shadow = new wxButton(panel, eSLPMergeShadow, "Merge shadow from 2 to 1");
                slp_tool_layout = new wxFlexGridSizer(2, 2, 2);
                SolidText *text_source1 = new SolidText(panel, " Source SLP 1");
                SolidText *text_source2 = new SolidText(panel, " Source SLP 2");
                SolidText *text_target1 = new SolidText(panel, " Target SLP");
                slp_source1 = new wxFilePickerCtrl(panel, wxID_ANY, "", "Select a file", "SLP|*.slp", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
                slp_source2 = new wxFilePickerCtrl(panel, wxID_ANY, "", "Select a file", "SLP|*.slp", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
                slp_target1 = new wxFilePickerCtrl(panel, wxID_ANY, "", "Select a file", "SLP|*.slp", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
                slp_hotspot = new wxCheckBox(panel, eShowHotspot, "Hotspot");
                slp_show_angles = new wxCheckBox(panel, eShowAngles, "Show angles");
                slp_show_angles->SetValue(DrawAngles);
                slp_animate = new wxCheckBox(panel, eAnimSLP, "Animate");
                slp_animate->SetValue(AnimSLP);
                slp_shadow = new wxCheckBox(panel, eShowShadows, "Shadow");
                slp_shadow->SetValue(ShowShadows);
                slp_outline = new wxCheckBox(panel, eShowOutline, "Outline");
                slp_outline->SetValue(ShowOutline);
                slp_delta = new wxCheckBox(panel, eShowDeltas, "Delta");
                slp_delta->SetValue(ShowDeltas);
                slp_stack = new wxCheckBox(panel, eShowStack, "Stack");
                slp_stack->SetValue(ShowStack);
                slp_annex = new wxCheckBox(panel, eShowAnnexes, "Annex");
                slp_annex->SetValue(ShowAnnexes);
                slp_terrain = new wxCheckBox(panel, eShowTerrain, "Terrain");
                slp_terrain->SetValue(DrawTerrain);
                slp_angles = new wxCheckBox(panel, eRotateAngles, "Rotate angles *");
                slp_angles->SetValue(RotateAngles);
                slp_collision = new wxCheckBox(panel, eCollisionShape, "Collision Shape");
                slp_collision->SetValue(DrawCollisionShape);
                slp_clearance = new wxCheckBox(panel, eClearanceShape, "Clearance Shape");
                slp_clearance->SetValue(DrawClearanceShape);
                slp_selection = new wxCheckBox(panel, eOutline, "Selection Shape");
                slp_selection->SetValue(DrawOutline);
                slp_sounds = new wxCheckBox(panel, ePlaySounds, "Play Sounds");
                slp_sounds->SetValue(PlaySounds);
                slp_angles->SetToolTip("Right click image to manually set angle");
                slp_sizer = new wxBoxSizer(wxVERTICAL);
                wxSizer *sizer2 = new wxBoxSizer(wxHORIZONTAL);
                wxSizer *sizer3 = new wxBoxSizer(wxHORIZONTAL);
                wxSizer *sizer4 = new wxBoxSizer(wxHORIZONTAL);
                wxSizer *sizer5 = new wxBoxSizer(wxHORIZONTAL);

                slp_sizer->Add(slp_view, 1, wxEXPAND);
                sizer5->Add(slp_show_angles, 0, wxALL, 2);
                sizer5->Add(slp_sounds, 0, wxALL, 2);
                sizer5->Add(slp_collision, 0, wxALL, 2);
                sizer5->Add(slp_clearance, 0, wxALL, 2);
                sizer5->Add(slp_selection, 0, wxALL, 2);
                sizer3->Add(slp_animate, 0, wxALL, 2);
                sizer3->Add(slp_shadow, 0, wxALL, 2);
                sizer3->Add(slp_outline, 0, wxALL, 2);
                sizer3->Add(slp_delta, 0, wxALL, 2);
                sizer3->Add(slp_stack, 0, wxALL, 2);
                sizer3->Add(slp_annex, 0, wxALL, 2);
                sizer3->Add(slp_terrain, 0, wxALL, 2);
                sizer2->Add(slp_angles, 0, wxALL, 2);
                sizer2->Add(slp_first);
                sizer2->Add(slp_prev);
                sizer2->Add(slp_next);
                sizer2->Add(slp_background);
                sizer4->Add(slp_frame_export);
                sizer4->Add(slp_frame_import);
                sizer4->Add(slp_save);
                sizer4->Add(slp_tool);
                sizer4->Add(slp_zoom_btn);
                sizer3->Add(slp_hotspot, 0, wxALL, 2);
                slp_tool_layout->Add(text_source1, 1, wxEXPAND);
                slp_tool_layout->Add(slp_source1, 1, wxEXPAND);
                slp_tool_layout->Add(text_source2, 1, wxEXPAND);
                slp_tool_layout->Add(slp_source2, 1, wxEXPAND);
                slp_tool_layout->Add(text_target1, 1, wxEXPAND);
                slp_tool_layout->Add(slp_target1, 1, wxEXPAND);
                slp_tool_layout->AddSpacer(1);
                slp_tool_layout->Add(slp_merge_shadow);
                slp_sizer->Add(slp_tool_layout, 0, wxEXPAND);
                slp_sizer->Add(sizer3, 0, wxEXPAND);
                slp_sizer->Add(sizer5, 0, wxEXPAND);
                slp_sizer->Add(sizer2, 0, wxEXPAND);
                slp_sizer->Add(sizer4, 0, wxEXPAND);
                slp_tool_layout->AddGrowableCol(1, 1);
                slp_tool_layout->Show(slp_tool_on);
                panel->SetSizer(slp_sizer);

                slp_view->Bind(wxEVT_PAINT, &AGE_Frame::OnDrawGraphicSLP, this);
                slp_view->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent &) {});
                slp_view->Bind(wxEVT_RIGHT_DOWN, &AGE_Frame::OnFrameMouse, this);
                slp_view->Bind(wxEVT_KEY_DOWN, &AGE_Frame::OnFrameKey, this);
                slp_window->Bind(wxEVT_CLOSE_WINDOW, &AGE_Frame::OnExitSLP, this);
                slp_first->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_next->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_prev->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_frame_export->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_frame_import->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_save->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_tool->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_zoom_btn->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_merge_shadow->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_hotspot->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_animate->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_shadow->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_outline->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_delta->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_stack->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_annex->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_angles->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_sounds->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_terrain->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_collision->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_clearance->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_selection->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_background->Bind(wxEVT_COLOURPICKER_CHANGED, &AGE_Frame::OnFrameButton, this);
                slp_show_angles->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_window->Show();
            }
            else
            {
                if (slp_window) // What if users manage to close this?
                {
                    slp_window->Destroy();
                    slp_window = 0;
                }
            }
            break;
        }
        case eShowIcons:
        {
            ShowIcons = event.IsChecked();

            Units_IconID_SLP->Show(ShowIcons);
            Research_IconID_SLP->Show(ShowIcons);
            break;
        }
        case eSlpPals:
        {
            wxFileDialog pd(this, "Open palette configuration file", "", "palettes.conf",
                "Configuration files (*.conf)|*.conf", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
            if (pd.ShowModal() == wxID_OK)
            {
                PathPalettes = pd.GetPath();
                GG::LoadPalettes(palettes, PathPalettes);
            }
            break;
        }
        case eSlpPCPal:
        {
            wxFileDialog pd(this, "Open palette file", "", "playercolor_blue.pal",
                "Palette files (*.pal)|*.pal", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
            if (pd.ShowModal() == wxID_OK)
            {
                PathPlayerColorPalette = pd.GetPath();
                GG::LoadPalettes(pc_palettes, PathPlayerColorPalette);
            }
            break;
        }
        case eStayOnTopSLP:
        {
            if (slp_window) slp_window->ToggleWindowStyle(wxSTAY_ON_TOP);
            KeepViewOnTop = event.IsChecked();
            break;
        }
        case eCacheDepth:
        {
            wxTextEntryDialog ted(this, "Enter new cache size in megabytes",
                "Set Cache Size", lexical_cast<std::string>(GG::cache_size / 1000000u));
            ted.SetTextValidator(wxFILTER_DIGITS);
            if (ted.ShowModal() == wxID_OK)
            {
                int temp = lexical_cast<int>(ted.GetValue());
                GG::cache_size = std::min(std::max(temp, 100), 3000) * 1000000u;
            }
            break;
        }
        case eSlpZoom:
        {
            wxTextEntryDialog ted(this, "Replace <x#> with", "Set Zoom Level", AlexZoom);
            ted.SetTextValidator(wxFILTER_ALPHANUMERIC);
            if (ted.ShowModal() == wxID_OK)
            {
                wxString input = ted.GetValue();
                AlexZoom = input.length() >= 2 ? input : "x1";
            }
            break;
        }
        default: wxMessageBox("ID " + lexical_cast<std::string>(event.GetId()) + "\nType " + lexical_cast<std::string>(event.GetEventType()), "Unhandled Event");
    }
}

bool AGE_Frame::loadPalette(const wxString &folder)
{
    if (!wxDir::Exists(folder)) return false;
    genie::PalFile pal;
    wxString name = folder + "\\interface\\50500.bina";
    try
    {
        pal.load(name.c_str());
        palettes.push_back(pal.getColors());
        return true;
    }
    catch (const std::ios_base::failure &) {}
    return false;
}

void AGE_Frame::addSLPFolders4SLPs(wxArrayString &folders, wxString folder)
{
    if (folder.empty()) return;
    folder.Replace("drs", "slp", false);
    if (!wxDir::Exists(folder)) return;
    folders.Add(folder + "\\");
}

void AGE_Frame::addDRSFolders4SLPs(wxArrayString &folders, const wxString &folder)
{
    if (folder.empty()) return;
    if (wxDir::Exists(folder + "\\gamedata_x2"))
        folders.Add(folder + "\\gamedata_x2\\");
    if (wxDir::Exists(folder + "\\gamedata_x1"))
        folders.Add(folder + "\\gamedata_x1\\");
    if (wxDir::Exists(folder + "\\interface"))
        folders.Add(folder + "\\interface\\");
    if (wxDir::Exists(folder + "\\graphics"))
        folders.Add(folder + "\\graphics\\");
    if (wxDir::Exists(folder + "\\terrain"))
        folders.Add(folder + "\\terrain\\");
}

bool AGE_Frame::LoadSLP(AGE_SLP *graphic)
{
    if (graphic->slpID == graphic->lastSlpID)
    {
        return true;
    }
    graphic->lastSlpID = graphic->slpID;

    if (UseLooseSLP || UseLooseModSLP)
    {
        if (!graphic->filename.empty())
        {
            if (GameVersion == EV_Tapsa)
            {
                graphic->filename.Replace("<x#>", AlexZoom, false);
            }
            if (GameVersion == EV_DE2)
            {
                size_t nameLength = graphic->filename.length();
                if (nameLength >= 3 &&
                    graphic->filename[nameLength - 2] == 'x' &&
                    graphic->filename[nameLength - 1] == '1')
                {
                    graphic->filename[nameLength - 1] = AlexZoom[1];
                }
            }
            bool (*TryOpen)(wxString, genie::SpriteFilePtr &) = [](wxString name, genie::SpriteFilePtr &sprite)
            {
                if (wxFileName(name + ".smx").FileExists())
                {
                    sprite = GG::LoadSMX(name + ".smx");
                    if (sprite) return true;
                }
                if (wxFileName(name + ".smp").FileExists())
                {
                    sprite = GG::LoadSMP(name + ".smp");
                    if (sprite) return true;
                }
                if (wxFileName(name + ".slp").FileExists())
                {
                    sprite = GG::LoadSLP(name + ".slp");
                    if (sprite) return true;
                }
                return false;
            };
            if (UseLooseModSLP && TryOpen(wxString(PathModSLP + "\\" + graphic->filename), graphic->slp))
            {
                return true;
            }
            if (UseLooseSLP && TryOpen(wxString(PathSLP + "\\" + graphic->filename), graphic->slp))
            {
                return true;
            }
        }
    }
    if (LooseHD)
    {
        wxArrayString folders;
        if (!graphic->filename.empty())
        {
            if (UseMod) addSLPFolders4SLPs(folders, FolderDRS2);
            addSLPFolders4SLPs(folders, FolderDRS);
            for (int i = 0; i < folders.size(); ++i)
            {
                graphic->slp = GG::LoadSLP(folders[i] + graphic->filename + ".slp");
                if (graphic->slp) return true;
            }
            folders.clear();
        }
        if (UseMod) addDRSFolders4SLPs(folders, FolderDRS2);
        addDRSFolders4SLPs(folders, FolderDRS);
        for (int i = 0; i < folders.size(); ++i)
        {
            // HD uses slp ID instead
            graphic->slp = GG::LoadSLP(folders[i] + lexical_cast<std::string>(graphic->slpID) + ".slp");
            if (graphic->slp) return true;
        }
    }
    else
    {
        for (genie::DrsFile *file : datafiles)
        {
            graphic->slp = GG::LoadSLP(*file, graphic->slpID);
            if (graphic->slp) return true;
        }
    }
    graphic->slp.reset();
    graphic->bitmap = wxNullBitmap;
    return false;
}

void AGE_Frame::FrameToBitmap(AGE_SLP *graphic, bool centralize)
{
    if (graphic->slp == nullptr)
    {
        graphic->bitmap = wxNullBitmap; SetStatusText("No sprite to load", 1); return;
    }
    uint32_t numFrames = graphic->slp->getFrameCount();
    if (graphic->frameID < 0 || graphic->frameID >= numFrames)
    {
        graphic->bitmap = wxNullBitmap;
        SetStatusText(wxString::Format("No frame %d within %u frames to load", graphic->frameID, numFrames), 1);
        return;
    }
    if (palettes.empty())
    {
        graphic->bitmap = wxNullBitmap; SetStatusText("No palettes loaded", 1); return;
    }
    SetStatusText(wxString::Format("Looking for frame %d", graphic->frameID), 1);
    if (graphic->slp->isSMX())
    {
        genie::SmxFramePtr frame;
        try
        {
            genie::SmxFile *smx = static_cast<genie::SmxFile *>(graphic->slp.get());
            frame = smx->getFrame(graphic->frameID);
        }
        catch (const std::out_of_range &) {}

        const int width = frame->getWidth();
        const int height = frame->getHeight();
        graphic->xpos = -frame->getHotspotX();
        graphic->ypos = -frame->getHotspotY();
        const int area = width * height;
        std::vector<uint8_t> rgbdata(area * 4, 0);
        const genie::SmxFrameData *imgdata = &frame->img_data;
        const std::vector<genie::Color> *pal = &palettes.front();
        size_t pal_chooser = frame->palette_id;
        if (pal_chooser < palettes.size())
        {
            pal = &palettes[pal_chooser];
        }
        if (!pal->empty())
        {
            int32_t mainOffX = frame->getMainLayerOffsetX();
            int32_t mainOffY = frame->getMainLayerOffsetY();
            size_t mainWidth = frame->getMainLayerWidth();
            for (size_t i = 0; i < imgdata->pixel_indexes.size(); ++i)
            {
                int flat = (i / mainWidth + mainOffY) * width + i % mainWidth + mainOffX;
                int loc = 3 * flat;
                int locA = 3 * area + flat;
                uint16_t colorId = 0x3FF & imgdata->pixel_indexes[i];
                genie::Color rgba = colorId < pal->size() ? (*pal)[colorId] : ColorNotFound;
                rgbdata[loc] = rgba.r;
                rgbdata[loc + 1] = rgba.g;
                rgbdata[loc + 2] = rgba.b;
                rgbdata[locA] = imgdata->alpha_channel[i];
            }
            // In case of using separate player color palette
            bool sep_pcp = pc_palettes.size();
            if (sep_pcp)
            {
                pal = &pc_palettes.front();
            }
            // Apply shadows
            if (ShowShadows)
            {
                int32_t offX = frame->getShadowLayerOffsetX();
                int32_t offY = frame->getShadowLayerOffsetY();
                for (size_t i = 0; i < imgdata->shadow_mask.size(); ++i)
                {
                    int flat = (imgdata->shadow_mask[i].y + offY) * width + imgdata->shadow_mask[i].x + offX;
                    int loc = 3 * flat;
                    int locA = 3 * area + flat;
                    rgbdata[loc] = 0;
                    rgbdata[loc + 1] = 0;
                    rgbdata[loc + 2] = 0;
                    rgbdata[locA] = static_cast<uint8_t>(imgdata->shadow_mask[i].index);
                }
            }
            // Apply player color
            for (size_t i = 0; i < imgdata->player_color_mask.size(); ++i)
            {
                int flat = (imgdata->player_color_mask[i].y + mainOffY) * width + imgdata->player_color_mask[i].x + mainOffX;
                int loc = 3 * flat;
                int locA = 3 * area + flat;
                uint16_t colorId = 0x3FF & imgdata->player_color_mask[i].index;
                genie::Color rgba = colorId < pal->size() ? (*pal)[colorId] : ColorNotFound;
                rgbdata[loc] = rgba.r;
                rgbdata[loc + 1] = rgba.g;
                rgbdata[loc + 2] = rgba.b;
                rgbdata[locA] = 255;
            }
            // Apply outlines
            if (ShowOutline)
            {
                int32_t offX = frame->getOutlineLayerOffsetX();
                int32_t offY = frame->getOutlineLayerOffsetY();
                // Player color
                for (size_t i = 0; i < imgdata->outline_pc_mask.size(); ++i)
                {
                    int flat = (imgdata->outline_pc_mask[i].y + offY) * width + imgdata->outline_pc_mask[i].x + offX;
                    int loc = 3 * flat;
                    int locA = 3 * area + flat;
                    genie::Color rgba = sep_pcp ? pal->front() : (*pal)[playerColorID];
                    rgbdata[loc] = rgba.r;
                    rgbdata[loc + 1] = rgba.g;
                    rgbdata[loc + 2] = rgba.b;
                    rgbdata[locA] = exportFrame ? 200 : 255;
                }
            }
        }
        unsigned char *pic = (unsigned char *)rgbdata.data();
        unsigned char *trans = pic + area * 3;
        wxImage img(width, height, pic, trans, true);
        if (centralize)
        {
            int left = frame->getHotspotX(), right = width - left,
                top = frame->getHotspotY(), bottom = height - top;
            int half_width = left > right ? left : right;
            int half_height = top > bottom ? top : bottom;
            img.Resize(wxSize(half_width * 2, half_height * 2), wxPoint(std::min(half_width, half_width - left), std::min(half_height, half_height - top)));
        }
        graphic->bitmap = wxBitmap(img, 32);
        return;
    }
    if (graphic->slp->isSMP())
    {
        genie::SmpFramePtr frame;
        try
        {
            genie::SmpFile *smp = static_cast<genie::SmpFile *>(graphic->slp.get());
            frame = smp->getFrame(graphic->frameID);
        }
        catch (const std::out_of_range &) {}

        const int width = frame->getWidth();
        const int height = frame->getHeight();
        graphic->xpos = -frame->getHotspotX();
        graphic->ypos = -frame->getHotspotY();
        const int area = width * height;
        std::vector<uint8_t> rgbdata(area * 4, 0);
        uint8_t *val = rgbdata.data();
        uint8_t *alpha = val + area * 3;
        const genie::SmpFrameData *imgdata = &frame->img_data;
        const std::vector<genie::Color> *pal = &palettes.front();
        if (!pal->empty())
        {
            for (int i = 0; i < area; ++i)
            {
                size_t pal_chooser = 0x3F & imgdata->pixel_indexes[i] >> 10;
                if (pal_chooser < palettes.size())
                {
                    pal = &palettes[pal_chooser];
                }
                genie::Color rgba = (*pal)[0x3FF & imgdata->pixel_indexes[i]];
                *val++ = rgba.r;
                *val++ = rgba.g;
                *val++ = rgba.b;
                *alpha++ = imgdata->alpha_channel[i];
            }
            // In case of using separate player color palette
            bool sep_pcp = pc_palettes.size();
            if (sep_pcp)
            {
                pal = &pc_palettes.front();
            }
            // Apply player color
            for (int i = 0; i < imgdata->player_color_mask.size(); ++i)
            {
                int flat = imgdata->player_color_mask[i].y * width + imgdata->player_color_mask[i].x;
                int loc = 3 * flat;
                int locA = 3 * area + flat;
                genie::Color rgba = (*pal)[0x3FF & imgdata->player_color_mask[i].index];
                rgbdata[loc] = rgba.r;
                rgbdata[loc + 1] = rgba.g;
                rgbdata[loc + 2] = rgba.b;
                rgbdata[locA] = 255;
            }
        }
        unsigned char *pic = (unsigned char *)rgbdata.data();
        unsigned char *trans = pic + area * 3;
        wxImage img(width, height, pic, trans, true);
        if (centralize)
        {
            int left = frame->getHotspotX(), right = width - left,
                top = frame->getHotspotY(), bottom = height - top;
            int half_width = left > right ? left : right;
            int half_height = top > bottom ? top : bottom;
            img.Resize(wxSize(half_width * 2, half_height * 2), wxPoint(std::min(half_width, half_width - left), std::min(half_height, half_height - top)));
        }
        graphic->bitmap = wxBitmap(img, 32);
        return;
    }
    if (!graphic->slp->isSLP())
    {
        graphic->bitmap = wxNullBitmap;
        SetStatusText("Impossible", 1);
        return;
    }
    genie::SlpFramePtr frame;
    try
    {
        genie::SlpFile *slp = static_cast<genie::SlpFile *>(graphic->slp.get());
        frame = slp->getFrame(graphic->frameID);
    }
    catch (const std::out_of_range &) {}

    const int width = frame->getWidth();
    const int height = frame->getHeight();
    const short pal_chooser = frame->getProperties() >> 16 & 255;
    graphic->xpos = graphic->flip ? frame->getHotspotX() - width : -frame->getHotspotX();
    graphic->ypos = -frame->getHotspotY();
    const int area = width * height;
    std::vector<uint8_t> rgbdata(area * 4, 0);
    const genie::SlpFrameData *imgdata = &frame->img_data;
    graphic->is32 = frame->is32bit();
    if (graphic->is32)
    {
        uint8_t *val = rgbdata.data();
        uint8_t *alpha = val + area * 3;
        for (int i = 0; i < area; ++i)
        {
            uint32_t bgra = imgdata->bgra_channels[i];
            *val++ = uint8_t(bgra >> 16);
            *val++ = uint8_t(bgra >> 8);
            *val++ = uint8_t(bgra);
            *alpha++ = uint8_t(bgra >> 24);
        }
        // Apply transparency
        for (int i = 0; i < imgdata->transparency_mask.size(); ++i)
        {
            int flat = imgdata->transparency_mask[i].y * width + imgdata->transparency_mask[i].x;
            int locA = 3 * area + flat;
            rgbdata[locA] = 255 - rgbdata[locA];
        }
        // Hack for interface files
        if (!graphic->xpos && !graphic->ypos)
        {
            graphic->xpos = -width / 2;
            graphic->ypos = -height / 3 * 2;
        }
    }
    else
    {
        bool simpleShadows = imgdata->special_shadow_mask.empty();
        const std::vector<genie::Color> *pal = &palettes.front();
        if (imgdata->palette.size())
        {
            pal = &imgdata->palette;
        }
        else if (pal_chooser != 0 && pal_chooser < palettes.size())
        {
            pal = &palettes[pal_chooser];
        }
        if (!pal->empty())
        {
            int32_t mainOffX = frame->getMainLayerOffsetX();
            int32_t mainOffY = frame->getMainLayerOffsetY();
            size_t mainWidth = frame->getMainLayerWidth();
            for (size_t i = 0; i < imgdata->pixel_indexes.size(); ++i)
            {
                int flat = (i / mainWidth + mainOffY) * width + i % mainWidth + mainOffX;
                int loc = 3 * flat;
                int locA = 3 * area + flat;
                uint16_t colorId = imgdata->pixel_indexes[i];
                genie::Color rgba = colorId < pal->size() ? (*pal)[colorId] : ColorNotFound;
                rgbdata[loc] = rgba.r;
                rgbdata[loc + 1] = rgba.g;
                rgbdata[loc + 2] = rgba.b;
                rgbdata[locA] = imgdata->alpha_channel[i];
            }
            // In case of using separate player color palette
            bool sep_pcp = pc_palettes.size();
            if (sep_pcp)
            {
                pal = &pc_palettes.front();
            }
            // Apply shadows
            if (ShowShadows)
            {
                if (simpleShadows)
                {
                    for (int i = 0; i < imgdata->shadow_mask.size(); ++i)
                    {
                        int flat = (imgdata->shadow_mask[i].y + mainOffY) * width + imgdata->shadow_mask[i].x + mainOffX;
                        int loc = 3 * flat;
                        int locA = 3 * area + flat;
                        rgbdata[loc] = 0;
                        rgbdata[loc + 1] = 0;
                        rgbdata[loc + 2] = 0;
                        rgbdata[locA] = 127;
                    }
                }
                else
                {
                    int32_t offX = frame->getShadowLayerOffsetX();
                    int32_t offY = frame->getShadowLayerOffsetY();
                    for (size_t i = 0; i < imgdata->special_shadow_mask.size(); ++i)
                    {
                        int flat = (imgdata->special_shadow_mask[i].y + offY) * width + imgdata->special_shadow_mask[i].x + offX;
                        int loc = 3 * flat;
                        int locA = 3 * area + flat;
                        rgbdata[loc] = 0;
                        rgbdata[loc + 1] = 0;
                        rgbdata[loc + 2] = 0;
                        rgbdata[locA] = static_cast<uint8_t>(imgdata->special_shadow_mask[i].index);
                    }
                }
            }
            // Apply player color
            for (int i = 0; i < imgdata->player_color_mask.size(); ++i)
            {
                int flat = (imgdata->player_color_mask[i].y + mainOffY) * width + imgdata->player_color_mask[i].x + mainOffX;
                int loc = 3 * flat;
                int locA = 3 * area + flat;
                genie::Color rgba = (*pal)[imgdata->player_color_mask[i].index + (sep_pcp ? 0 : playerColorStart)];
                rgbdata[loc] = rgba.r;
                rgbdata[loc + 1] = rgba.g;
                rgbdata[loc + 2] = rgba.b;
                if (exportFrame)
                {
                    rgbdata[locA] = 230 + imgdata->player_color_mask[i].index;
                }
                else
                {
                    rgbdata[locA] = 255;
                }
            }
            // Apply outlines
            if (ShowOutline)
            {
                // Shield
                for (int i = 0; i < imgdata->shield_mask.size(); ++i)
                {
                    int flat = imgdata->shield_mask[i].y * width + imgdata->shield_mask[i].x;
                    int loc = 3 * flat;
                    int locA = 3 * area + flat;
                    rgbdata[loc] = 0;
                    rgbdata[loc + 1] = 255;
                    rgbdata[loc + 2] = 0;
                    rgbdata[locA] = exportFrame ? 201 : 255;
                }
                // Player color
                for (int i = 0; i < imgdata->outline_pc_mask.size(); ++i)
                {
                    int flat = (imgdata->outline_pc_mask[i].y + mainOffY) * width + imgdata->outline_pc_mask[i].x + mainOffX;
                    int loc = 3 * flat;
                    int locA = 3 * area + flat;
                    genie::Color rgba = sep_pcp ? pal->front() : (*pal)[playerColorID];
                    rgbdata[loc] = rgba.r;
                    rgbdata[loc + 1] = rgba.g;
                    rgbdata[loc + 2] = rgba.b;
                    rgbdata[locA] = exportFrame ? 200 : 255;
                }
            }
        }
    }
    unsigned char *pic = (unsigned char *)rgbdata.data();
    unsigned char *trans = pic + area * 3;
    wxImage img(width, height, pic, trans, true);
    if (graphic->flip) img = img.Mirror();
    if (centralize)
    {
        int left = frame->getHotspotX(), right = width - left,
            top = frame->getHotspotY(), bottom = height - top;
        int half_width = left > right ? left : right;
        int half_height = top > bottom ? top : bottom;
        img.Resize(wxSize(half_width * 2, half_height * 2), wxPoint(std::min(half_width, half_width - left), std::min(half_height, half_height - top)));
    }
    graphic->bitmap = wxBitmap(img, 32);
}

void AGE_Frame::BitmapToSLP(AGE_SLP *graphic)
{
    wxImage img("Testi.png", wxBITMAP_TYPE_PNG);
    unsigned char *pic = img.GetData();
    if (!img.HasAlpha()) img.InitAlpha();
    if (!img.HasAlpha())
    {
        wxMessageBox("Alpha channel missing", "Aborting...");
        return;
    }
    unsigned char *trans = img.GetAlpha();
    if (!graphic->slp || !graphic->slp->isSLP())
    {
        wxMessageBox("Congrats seeing this message", "No SLP");
        return;
    }
    genie::SlpFramePtr frame;
    try
    {
        genie::SlpFile *slp = static_cast<genie::SlpFile *>(graphic->slp.get());
        frame = slp->getFrame(graphic->frameID);
    }
    catch (const std::out_of_range &) {}
    if (!frame)
    {
        wxMessageBox("Congrats seeing this message", "No SLP frame " + lexical_cast<std::string>(graphic->frameID));
        return;
    }
    genie::SlpFrameData *imgdata = &frame->img_data;
    if (frame->is32bit())
    {
        frame->setSize(img.GetWidth(), img.GetHeight());
        uint32_t *val = imgdata->bgra_channels.data();
        for (int p = 0, max = img.GetHeight() * img.GetWidth(); p < max; ++p)
        {
            unsigned char red = *pic++;
            unsigned char green = *pic++;
            unsigned char blue = *pic++;
            unsigned char alpha = *trans++;
            *val++ = (red << 16) + (green << 8) + blue + (alpha << 24);
        }
        wxMessageBox("Frame image filled from PNG", "SLP");
    }
    else
    {
        wxMessageBox("No 8-bit frame support yet", "SLP");
    }
}

AGE_SLPs *AGE_Frame::getCurrentGraphics()
{
    AGE_SLPs *graphic = 0;
    if (currentDisplay == SHOW::GRAPHIC)
    {
        graphic = &gallery;
    }
    else if (currentDisplay == SHOW::UNIT)
    {
        graphic = &museum;
    }
    return graphic;
}

void AGE_Frame::OnFrameButton(wxCommandEvent &event)
{
    switch (event.GetId())
    {
        case eNextFrame:
        {
            AGE_SLPs *graphic = getCurrentGraphics();
            if (graphic)
            {
                bool framesleft = false;
                if (graphic->slp)
                {
                    ChooseNextFrame(*graphic, framesleft);
                }
                for (auto &delta : graphic->deltas)
                {
                    if (!delta.second.slp) continue;
                    ChooseNextFrame(delta.second, framesleft);
                }
                HandleLastFrame(graphic->angles, framesleft, 1u);
            }
            break;
        }
        case ePrevFrame:
        {
            AGE_SLPs *graphic = getCurrentGraphics();
            if (graphic)
            {
                bool framesleft = false;
                if (graphic->slp)
                {
                    ChoosePreviousFrame(*graphic, framesleft);
                }
                for (auto &delta : graphic->deltas)
                {
                    if (!delta.second.slp) continue;
                    ChoosePreviousFrame(delta.second, framesleft);
                }
                HandleLastFrame(graphic->angles, framesleft, 2u);
            }
            break;
        }
        case eFirstFrame:
        {
            bearing = 0.f;
            setbearing = 1u;
            break;
        }
        case eExportFrame:
        {
            exportFrame = true;
            if (currentDisplay == SHOW::GRAPHIC)
            {
                if (LoadSLP(&gallery))
                {
                    FrameToBitmap(&gallery, true);
                }
                if (gallery.bitmap.IsOk())
                {
                    if (!gallery.bitmap.SaveFile(gallery.filename + ".png", wxBITMAP_TYPE_PNG))
                        wxMessageBox("Saving frame as PNG failed", "SLP");
                }
            }
            else wxMessageBox("Choose a graphic from graphics tab", "SLP");
            exportFrame = false;
            return;
        }
        case eImportFrame:
        {
            if (currentDisplay == SHOW::GRAPHIC)
            {
                BitmapToSLP(&gallery);
            }
            animater.Start(100);
            return;
        }
        case eSaveSLP:
        {
            if (currentDisplay == SHOW::GRAPHIC)
            {
                if (!gallery.slp || !gallery.slp->isSLP())
                {
                    wxMessageBox("No SLP to save", "SLP");
                    return;
                }
                if (gallery.filename.empty())
                {
                    wxMessageBox("No SLP filename", "SLP");
                    return;
                }
                wxString name = gallery.filename + ".slp";
                try
                {
                    genie::SlpFile *slp = static_cast<genie::SlpFile *>(gallery.slp.get());
                    slp->saveAs(name.c_str());
                    wxMessageBox("Saved SLP " + name, "SLP");
                }
                catch (const std::ios_base::failure &)
                {
                    wxMessageBox("Saving SLP failed", "SLP");
                }
            }
            else wxMessageBox("Look at some graphic", "SLP");
            return;
        }
        case eSLPTool:
        {
            slp_tool_on = !slp_tool_on;
            slp_tool_layout->Show(slp_tool_on);
            slp_sizer->Layout();
            slp_window->Fit();
            return;
        }
        case eZoom:
        {
            wxTextEntryDialog ted(this, "Enter new zooming %", "Set Scale Factor", lexical_cast<std::string>(int(slp_zoom * 100)));
            ted.SetTextValidator(wxFILTER_DIGITS);
            if (ted.ShowModal() == wxID_OK)
            {
                int zoom_percent = std::min(800, lexical_cast<int>(ted.GetValue()));
                slp_zoom = zoom_percent / 100.f;
                slp_zoom_btn->SetLabel("Zoom: " + lexical_cast<std::string>(zoom_percent) + " %");
            }
            break;
        }
        case eSLPMergeShadow:
        {
            genie::SlpFilePtr slp_src1(new genie::SlpFile());
            genie::SlpFilePtr slp_src2(new genie::SlpFile());
            try
            {
                slp_src1->load(slp_source1->GetPath().c_str());
                slp_src1->freelock();
                slp_src2->load(slp_source2->GetPath().c_str());
                slp_src2->freelock();
            }
            catch (const std::ios_base::failure &)
            {
                wxMessageBox("Error reading SLP files", "SLP");
                return;
            }
            for (uint32_t frame = 0; frame < slp_src1->getFrameCount(); ++frame)
            {
                genie::SlpFramePtr frame1, frame2;
                try
                {
                    frame1 = slp_src1->getFrame(frame);
                    frame2 = slp_src2->getFrame(frame);
                }
                catch (const std::out_of_range &)
                {
                    wxMessageBox("Frame count mismatch", "SLP");
                    break;
                }

                int32_t offset_x, offset_y;
                // Resize frame if the other frame is bigger in some dimension.
                frame1->enlargeForMerge(*frame2, offset_x, offset_y);
                uint32_t width = frame1->getWidth(), height = frame1->getHeight();

                genie::SlpFrameData *imgdata = &frame1->img_data;
                imgdata->shadow_mask.clear();
                for (genie::XY16 const &shadow_pixel : frame2->img_data.shadow_mask)
                {
                    const uint32_t x = shadow_pixel.x + offset_x,
                        y = shadow_pixel.y + offset_y,
                        slot = y * width + x;
                    if (x < width && y < height)
                    {
                        if (imgdata->alpha_channel[slot] == 0)
                        {
                            imgdata->shadow_mask.emplace_back(x, y);
                        }
                    }
                }
            }
            try
            {
                slp_src1->saveAs(slp_target1->GetPath().c_str());
                wxMessageBox("Merged SLP files", "SLP");
            }
            catch (const std::ios_base::failure &)
            {
                wxMessageBox("Saving SLP failed", "SLP");
            }
            return;
        }
        case eShowHotspot:
        {
            DrawHot = event.IsChecked();
            break;
        }
        case eShowAngles:
        {
            DrawAngles = event.IsChecked();
            break;
        }
        case eAnimSLP:
        {
            AnimSLP = event.IsChecked();
            break;
        }
        case eShowShadows:
        {
            ShowShadows = event.IsChecked();
            break;
        }
        case eShowOutline:
        {
            ShowOutline = event.IsChecked();
            break;
        }
        case eShowDeltas:
        {
            ShowDeltas = event.IsChecked();
            gallery.reload();
            museum.reload();
            break;
        }
        case eShowStack:
        {
            ShowStack = event.IsChecked();
            gallery.reload();
            museum.reload();
            break;
        }
        case eShowAnnexes:
        {
            ShowAnnexes = event.IsChecked();
            gallery.reload();
            museum.reload();
            break;
        }
        case eRotateAngles:
        {
            RotateAngles = event.IsChecked();
            break;
        }
        case eShowTerrain:
        {
            DrawTerrain = event.IsChecked();
            break;
        }
        case ePickBgColor:
        {
            wxColour back(slp_background->GetColour());
            ViewBackR = back.Red();
            ViewBackG = back.Green();
            ViewBackB = back.Blue();
            slp_background_brush = wxBrush(back);
            break;
        }
        case eCollisionShape:
        {
            DrawCollisionShape = event.IsChecked();
            break;
        }
        case eClearanceShape:
        {
            DrawClearanceShape = event.IsChecked();
            break;
        }
        case eOutline:
        {
            DrawOutline = event.IsChecked();
            break;
        }
        case ePlaySounds:
        {
            PlaySounds = event.IsChecked();
            break;
        }
    }
    slp_view->Refresh();
}

void AGE_Frame::OnFrameMouse(wxMouseEvent &event)
{
    int centerX, centerY;
    CalcDrawCenter(slp_view, centerX, centerY);
    wxPoint coords(slp_view->ScreenToClient(wxGetMousePosition()));
    coords.x -= centerX;
    coords.y -= centerY;
    float anchor = FillMissingFrames ? 3.1416f : 4.7124f;
    bearing = atan2(coords.x, -coords.y << 1) + anchor;
    if (bearing >= PI2A)
    {
        assert(!FillMissingFrames);
        bearing -= PI2A;
    }
    assert(bearing >= 0.f && PI2 > bearing);
    setbearing = 1u;
    slp_view->Refresh();
}

void AGE_Frame::OnFrameKey(wxKeyEvent &event)
{
    if (!dataset) return;
    std::vector<int16_t *> dx(DeltaIDs.size()), dy(DeltaIDs.size());
    if (GraphicIDs.size())
    {
        for (size_t i = 0; i < DeltaIDs.size(); ++i)
        {
            dx[i] = &dataset->Graphics[GraphicIDs.front()].Deltas[DeltaIDs[i]].OffsetX;
            dy[i] = &dataset->Graphics[GraphicIDs.front()].Deltas[DeltaIDs[i]].OffsetY;
        }
    }
    switch (event.GetKeyCode())
    {
        case 'A':
        {
            slp_extra_info = "X - 1";
            for (size_t i = 0; i < dx.size(); ++i)-- *dx[i];
            break;
        }
        case 'D':
        {
            slp_extra_info = "X + 1";
            for (size_t i = 0; i < dx.size(); ++i)++ *dx[i];
            break;
        }
        case 'S':
        {
            slp_extra_info = "Y + 1";
            for (size_t i = 0; i < dy.size(); ++i)++ *dy[i];
            break;
        }
        case 'W':
        {
            slp_extra_info = "Y - 1";
            for (size_t i = 0; i < dy.size(); ++i)-- *dy[i];
            break;
        }
        default: return;
    }
    popUp.unSaved += DeltaIDs.size();
    wxCommandEvent e;
    OnGraphicDeltaSelect(e);
    gallery.reload();
    slp_view->Refresh();
}

void AGE_Frame::OnExitSLP(wxCloseEvent &event)
{
    SubMenu_SLP->Check(eShowSLP, false);
    wxCommandEvent closeSLP(wxEVT_MENU, eShowSLP);
    closeSLP.SetInt(false);
    OnAnimationMenuOption(closeSLP);
}
