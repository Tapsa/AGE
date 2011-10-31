# Makefile.mak #

CompilerC = @gcc
CompilerCPP = @g++
Res = @windres

# -Wl,-u,_WinMain@16 -Wl,--enable-runtime-pseudo-reloc

Bin = AdvancedGenieEditor2
ResFile = Resources
Libs = -lwxmsw28_adv -lwxmsw28_core -lwxbase28 -lz -ladvapi32 -lole32 -loleaut32 -mwindows -lcomctl32 -luuid
# -lgeniedat -L.

Inc = C:/Cpp/MinGW/include
IncCPP = C:/Cpp/MinGW/include/c++
IncWx = C:/Cpp/wxWidgets/include
IncWxMS = C:/Cpp/wxWidgets/lib/gcc_lib/msw

ObjDir = ../obj
BinDir = ../bin

CompileFlags = -O2 -I$(Inc) -I$(IncCPP) -I$(IncWx) -I$(IncWxMS) -O0 -ggdb
ResourceFlags = -I$(IncWx)
LinkFlags = -LC:/Cpp/wxWidgets/lib/gcc_lib -static

ObjList = ../bin/libgeniedat.dll $(ObjDir)/Main.o $(ObjDir)/AGE_FrameConstructor.o $(ObjDir)/AGE_FrameOther.o $(ObjDir)/AGE_FrameResearch.o $(ObjDir)/AGE_FrameTechage.o $(ObjDir)/AGE_FrameCivs.o $(ObjDir)/AGE_FrameUnits.o $(ObjDir)/AGE_FrameGraphics.o $(ObjDir)/AGE_FrameTerrains.o $(ObjDir)/AGE_FrameTerrainRestrictions.o $(ObjDir)/AGE_FrameSounds.o $(ObjDir)/AGE_FrameColors.o $(ObjDir)/AGE_OpenDialog.o $(ObjDir)/AGE_SaveDialog.o $(ObjDir)/AGE_AboutDialog.o $(ObjDir)/AGE_TextControls.o $(ObjDir)/AGE_ComboBoxes.o $(ObjDir)/AGE_CheckBoxes.o $(ObjDir)/AGE_ScrolledWindow.o $(ObjDir)/$(ResFile).o
AGE_FrameDepends = AGE_Frame.h AGE_ScrolledWindow.h AGE_ComboBoxes.h AGE_CheckBoxes.h AGE_TextControls.h AGE_OpenDialog.h AGE_SaveDialog.h AGE_AboutDialog.h geniedat/File.h AppIcon.xpm

all:	$(BinDir)/$(Bin).exe

$(BinDir)/$(Bin).exe:	$(ObjList)
	@echo Linking $(Bin).exe...
	$(CompilerCPP) -o $@ $(LinkFlags) $(ObjList) $(Libs)
	@echo Finished!

$(ObjDir)/main.o:  main.cpp main.h AGE_Frame.h AGE_TextControls.h
	@echo Compiling Main.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<
	
#	Start of user interface.
	
$(ObjDir)/AGE_FrameConstructor.o:  AGE_Frame_cpp/Constructor.cpp $(AGE_FrameDepends)
	@echo Compiling AGE_FrameConstructor.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_FrameOther.o:  AGE_Frame_cpp/Other.cpp $(AGE_FrameDepends)
	@echo Compiling AGE_FrameOther.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_FrameResearch.o:  AGE_Frame_cpp/Research.cpp $(AGE_FrameDepends)
	@echo Compiling AGE_FrameResearch.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_FrameTechage.o:  AGE_Frame_cpp/Techage.cpp $(AGE_FrameDepends)
	@echo Compiling AGE_FrameTechage.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_FrameCivs.o:  AGE_Frame_cpp/Civs.cpp $(AGE_FrameDepends)
	@echo Compiling AGE_FrameCivs.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_FrameUnits.o:  AGE_Frame_cpp/Units.cpp $(AGE_FrameDepends)
	@echo Compiling AGE_FrameUnits.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_FrameGraphics.o:  AGE_Frame_cpp/Graphics.cpp $(AGE_FrameDepends)
	@echo Compiling AGE_FrameGraphics.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_FrameTerrains.o:  AGE_Frame_cpp/Terrains.cpp $(AGE_FrameDepends)
	@echo Compiling AGE_FrameTerrains.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_FrameTerrainRestrictions.o:  AGE_Frame_cpp/TerrainRestrictions.cpp $(AGE_FrameDepends)
	@echo Compiling AGE_FrameTerrainRestrictions.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_FrameSounds.o:  AGE_Frame_cpp/Sounds.cpp $(AGE_FrameDepends)
	@echo Compiling AGE_FrameSounds.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_FrameColors.o:  AGE_Frame_cpp/PlayerColors.cpp $(AGE_FrameDepends)
	@echo Compiling AGE_FrameColors.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

#	End of user interface.
	
$(ObjDir)/AGE_OpenDialog.o:  AGE_OpenDialog.cpp AGE_OpenDialog.h
	@echo Compiling AGE_OpenDialog.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_SaveDialog.o:  AGE_SaveDialog.cpp AGE_SaveDialog.h
	@echo Compiling AGE_SaveDialog.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_AboutDialog.o:  AGE_AboutDialog.cpp AGE_AboutDialog.h
	@echo Compiling AGE_AboutDialog.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_TextControls.o:  AGE_TextControls.cpp AGE_TextControls.h
	@echo Compiling AGE_TextControls.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_ComboBoxes.o:  AGE_ComboBoxes.cpp AGE_ComboBoxes.h
	@echo Compiling AGE_ComboBoxes.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_CheckBoxes.o:  AGE_CheckBoxes.cpp AGE_CheckBoxes.h
	@echo Compiling AGE_CheckBoxes.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<

$(ObjDir)/AGE_ScrolledWindow.o:  AGE_ScrolledWindow.cpp AGE_ScrolledWindow.h
	@echo Compiling AGE_ScrolledWindow.o...
	$(CompilerCPP) -c $(CompileFlags) -o $@ $<
	
$(ObjDir)/$(ResFile).o:  Resources.rc Resources.h AppIcon.ico
	@echo Compiling Resources.o...
	$(Res) $(ResourceFlags) $(ResFile).rc $(ObjDir)/$(ResFile).o
