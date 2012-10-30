
#include "../AGE_Frame.h"
using boost::lexical_cast;

const int VERSION_EXTRACT = 4;

bool AGE_Frame::CorrectVersion(int &Version)
{
	if(Version < VERSION_EXTRACT)
	{
		wxMessageBox("Wrong version number on extraction file!");
		return false;
	}
	return true;
}

void AGE_Frame::ExpError(wxFileConfig &Extract)
{
	Extract.DeleteAll();
	wxMessageBox("An error occured!\nAborted extracting.");
}

void AGE_Frame::ImpError()
{
	wxMessageBox("Importing malfunctioned.\nTry again.");
}

void AGE_Frame::OnExtractUnit(wxCommandEvent& Event)
{
	wxFileConfig ExtractUnit(wxEmptyString, "Tapsa", "age2eUnit.txt", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	try
	{
		ExtractUnit.DeleteGroup("Civ*");
		auto CountHolder=0;
		ExtractUnit.Write("Version/Number", VERSION_EXTRACT);
		for(short loop=0; loop < GenieFile->Civs.size(); loop++)
		{
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Type", GenieFile->Civs[loop].Units[UnitIDs[0]].Type);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Class", GenieFile->Civs[loop].Units[UnitIDs[0]].Class);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/LanguageDLLName", GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLName);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/LanguageDLLCreation", GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLCreation);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DyingGraphic1", GenieFile->Civs[loop].Units[UnitIDs[0]].DyingGraphic.first);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DyingGraphic2", GenieFile->Civs[loop].Units[UnitIDs[0]].DyingGraphic.second);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DeathMode", GenieFile->Civs[loop].Units[UnitIDs[0]].DeathMode);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/HitPoints", GenieFile->Civs[loop].Units[UnitIDs[0]].HitPoints);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/LineOfSight", GenieFile->Civs[loop].Units[UnitIDs[0]].LineOfSight);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/GarrisonCapacity", GenieFile->Civs[loop].Units[UnitIDs[0]].GarrisonCapacity);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SizeRadius1", GenieFile->Civs[loop].Units[UnitIDs[0]].SizeRadius.first);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SizeRadius2", GenieFile->Civs[loop].Units[UnitIDs[0]].SizeRadius.second);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/HPBarHeight1", GenieFile->Civs[loop].Units[UnitIDs[0]].HPBarHeight1);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DeadUnitID", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadUnitID);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/PlacementMode", GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementMode);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/AirMode", GenieFile->Civs[loop].Units[UnitIDs[0]].AirMode);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/IconID", GenieFile->Civs[loop].Units[UnitIDs[0]].IconID);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/HideInEditor", GenieFile->Civs[loop].Units[UnitIDs[0]].HideInEditor);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown1", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown1);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Enabled", GenieFile->Civs[loop].Units[UnitIDs[0]].Enabled);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/PlacementBypassTerrain1", GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementBypassTerrain.first);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/PlacementBypassTerrain2", GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementBypassTerrain.second);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/PlacementTerrain1", GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementTerrain.first);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/PlacementTerrain2", GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementTerrain.second);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/EditorRadius1", GenieFile->Civs[loop].Units[UnitIDs[0]].EditorRadius.first);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/EditorRadius2", GenieFile->Civs[loop].Units[UnitIDs[0]].EditorRadius.second);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/BuildingMode", GenieFile->Civs[loop].Units[UnitIDs[0]].BuildingMode);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/VisibleInFog", GenieFile->Civs[loop].Units[UnitIDs[0]].VisibleInFog);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/TerrainRestriction", GenieFile->Civs[loop].Units[UnitIDs[0]].TerrainRestriction);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/FlyMode", GenieFile->Civs[loop].Units[UnitIDs[0]].FlyMode);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/ResourceCapacity", GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceCapacity);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/ResourceDecay", GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceDecay);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/BlastType", GenieFile->Civs[loop].Units[UnitIDs[0]].BlastType);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown2", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown2);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/InteractionMode", GenieFile->Civs[loop].Units[UnitIDs[0]].InteractionMode);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/MinimapMode", GenieFile->Civs[loop].Units[UnitIDs[0]].MinimapMode);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/CommandAttribute", GenieFile->Civs[loop].Units[UnitIDs[0]].CommandAttribute);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown3", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown3B", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3B);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/LanguageDLLHelp", GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLHelp);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/LanguageDLLHotKeyText", GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLHotKeyText);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/HotKey", GenieFile->Civs[loop].Units[UnitIDs[0]].HotKey);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown4", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown4);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown5", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown5);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unselectable", GenieFile->Civs[loop].Units[UnitIDs[0]].Unselectable);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown6", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown6);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionMask", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionMask);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionShape", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionShape);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionRadius1", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionRadius.first);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionRadius2", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionRadius.second);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/HPBarHeight2", GenieFile->Civs[loop].Units[UnitIDs[0]].HPBarHeight2);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionSound", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionSound);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DyingSound", GenieFile->Civs[loop].Units[UnitIDs[0]].DyingSound);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/AttackSound", GenieFile->Civs[loop].Units[UnitIDs[0]].AttackSound);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Name", GenieFile->Civs[loop].Units[UnitIDs[0]].Name);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/NameLength", GenieFile->Civs[loop].Units[UnitIDs[0]].NameLength);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/StandingGraphic1", GenieFile->Civs[loop].Units[UnitIDs[0]].StandingGraphic.first);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/TrainSound1", GenieFile->Civs[loop].Units[UnitIDs[0]].TrainSound.first);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionEffect", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionEffect);
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/EditorSelectionColour", GenieFile->Civs[loop].Units[UnitIDs[0]].EditorSelectionColour);
			if(GameVersion >= 2)
			{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/StandingGraphic2", GenieFile->Civs[loop].Units[UnitIDs[0]].StandingGraphic.second);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/TrainSound2", GenieFile->Civs[loop].Units[UnitIDs[0]].TrainSound.second);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown7", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown7);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown8", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown8);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionShapeType", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionShapeType);
				if(GameVersion >= 3)
				{
					ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Attribute", GenieFile->Civs[loop].Units[UnitIDs[0]].Attribute);
					ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Civilization", GenieFile->Civs[loop].Units[UnitIDs[0]].Civilization);
					ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown9A", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown9[0]);
					ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown9B", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown9[1]);
					if(GameVersion >= 4)
					{
						ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Name2", GenieFile->Civs[loop].Units[UnitIDs[0]].Name2);
						ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/NameLength2", GenieFile->Civs[loop].Units[UnitIDs[0]].NameLength2);
						ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unitline", GenieFile->Civs[loop].Units[UnitIDs[0]].Unitline);
						ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/MinTechLevel", GenieFile->Civs[loop].Units[UnitIDs[0]].MinTechLevel);
					}
				}
			}
			else
			{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown3a", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3a);
			}
			for(short loop2=0; loop2 < 3; loop2++)
			{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Type", GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Type);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Amount", GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Amount);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Enabled", GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Enabled);
			}
			CountHolder = GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics.size();
			ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DamageGraphicCount", CountHolder);
			for(short loop2=0; loop2 < CountHolder; loop2++)
			{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Dama"+lexical_cast<string>(loop2)+"GraphicID", GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].GraphicID);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Dama"+lexical_cast<string>(loop2)+"DamagePercent", GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].DamagePercent);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Dama"+lexical_cast<string>(loop2)+"Unknown1", GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].Unknown1);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Dama"+lexical_cast<string>(loop2)+"Unknown2", GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].Unknown2);
			}
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type != 90)
			{
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 20)
			{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Flag/Speed", GenieFile->Civs[loop].Units[UnitIDs[0]].Speed);
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 30)
			{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/WalkingGraphic1", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.WalkingGraphic.first);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/WalkingGraphic2", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.WalkingGraphic.second);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/RotationSpeed", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.RotationSpeed);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/Unknown11", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown11);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/TrackingUnit", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnit);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/TrackingUnitUsed", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnitUsed);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/TrackingUnitDensity", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnitDensity);
				if(GameVersion >= 2)
				{
					ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/Unknown12", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown12);
					for(short loop2=0; loop2 < 17; loop2++)
					ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/Unknown16_"+lexical_cast<string>(loop2), GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown16[loop2]);
				}
				else
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/Unknown16", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown16[0]);
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 40)
			{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/SheepConversion", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.SheepConversion);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/SearchRadius", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.SearchRadius);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/WorkRate", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.WorkRate);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/DropSite1", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.DropSite.first);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/DropSite2", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.DropSite.second);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/VillagerMode", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.VillagerMode);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/MoveSound", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.MoveSound);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/StopSound", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.StopSound);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/AnimalMode", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.AnimalMode);
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 60)
			{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Unknown20", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown20);
				CountHolder = GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks.size();
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/AttackCount", CountHolder);
				for(short loop2=0; loop2 < CountHolder; loop2++)
				{
					ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Attack"+lexical_cast<string>(loop2)+"Class", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks[loop2].Class);
					ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Attack"+lexical_cast<string>(loop2)+"Amount", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks[loop2].Amount);
				}
				CountHolder = GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours.size();
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/ArmourCount", CountHolder);
				for(short loop2=0; loop2 < CountHolder; loop2++)
				{
					ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Armor"+lexical_cast<string>(loop2)+"Class", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours[loop2].Class);
					ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Armor"+lexical_cast<string>(loop2)+"Amount", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours[loop2].Amount);
				}
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Unknown21", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown21);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/MaxRange", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.MaxRange);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/BlastRadius", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.BlastRadius);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/ProjectileUnitID", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ProjectileUnitID);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/AccuracyPercent", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.AccuracyPercent);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/TowerMode", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.TowerMode);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Delay", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Delay);
				for(short loop2=0; loop2 < 3; loop2++)
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/GraphicDisplacement"+lexical_cast<string>(loop2), GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.GraphicDisplacement[loop2]);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Unknown23", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown23);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/MinRange", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.MinRange);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/AttackGraphic", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.AttackGraphic);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/DisplayedMeleeArmour", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedMeleeArmour);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/DisplayedAttack", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedAttack);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/DisplayedRange", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedRange);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/ReloadTime1", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ReloadTime1);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/ReloadTime2", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ReloadTime2);
				if(GameVersion >= 2)
				{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/GarrisonRecoveryRate", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.GarrisonRecoveryRate);
				if(GameVersion >= 3)
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Unknown20_1", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown20_1);
				}
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 70)
			{
				for(short loop2=0; loop2 < 3; loop2++)
				{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Type", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Type);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Amount", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Amount);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Enabled", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Enabled);
				}
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/TrainTime", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.TrainTime);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/TrainLocationID", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.TrainLocationID);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/ButtonID", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ButtonID);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/DisplayedPierceArmour", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.DisplayedPierceArmour);
				if(GameVersion >= 2)
				{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/Unknown26", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown26);
				for(short loop2=0; loop2 < 3; loop2++)
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/Unknown27_"+lexical_cast<string>(loop2), GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown27[loop2]);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/Unknown28", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown28);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/MissileGraphicDelay", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.MissileGraphicDelay);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/HeroMode", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.HeroMode);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/GarrisonGraphic1", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.GarrisonGraphic.first);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/GarrisonGraphic2", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.GarrisonGraphic.second);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/AttackMissileDuplicationAmount1", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationAmount1);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/AttackMissileDuplicationAmount2", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationAmount2);
				for(short loop2=0; loop2 < 3; loop2++)
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/AttackMissileDuplicationSpawning"+lexical_cast<string>(loop2), GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationSpawning[loop2]);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/AttackMissileDuplicationUnit", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationUnit);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/AttackMissileDuplicationGraphic", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationGraphic);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/Unknown29", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown29);
				}
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 80)
			{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/ConstructionGraphicID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ConstructionGraphicID);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/AdjacentMode", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.AdjacentMode);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown31", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown31);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown31b", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown31b);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/StackUnitID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.StackUnitID);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/TerrainID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.TerrainID);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown32", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown32);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/ResearchID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ResearchID);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/ConstructionSound", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ConstructionSound);
				if(GameVersion >= 2)
				{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown33", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown33);
				for(short loop2=0; loop2 < 4; loop2++)
				{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Annex"+lexical_cast<string>(loop2)+"UnitID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].UnitID);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Annex"+lexical_cast<string>(loop2)+"Misplacement1", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].Misplacement.first);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Annex"+lexical_cast<string>(loop2)+"Misplacement2", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].Misplacement.second);
				}
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/HeadUnit", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.HeadUnit);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/TransformUnit", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.TransformUnit);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown34", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown34);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/GarrisonType", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.GarrisonType);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/GarrisonHealRate", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.GarrisonHealRate);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown35", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown35);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown36", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown36);
				for(short loop2=0; loop2 < 6; loop2++)
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown37_"+lexical_cast<string>(loop2), GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown37[loop2]);
				if(GameVersion >= 3)
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_Building/SnowGraphicID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.SnowGraphicID);
				}
			}}}}}}
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type == 60)
			{
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/StretchMode", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.StretchMode);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/CompensationMode", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.CompensationMode);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/DropAnimationMode", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.DropAnimationMode);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/PenetrationMode", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.PenetrationMode);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/Unknown24", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.Unknown24);
				ExtractUnit.Write("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/ProjectileArc", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.ProjectileArc);
			}}
		}
		if(GameVersion < 2)
		{
		CountHolder = GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands.size();
		ExtractUnit.Write("CivX_Unit_Bird/CommandCount", CountHolder);
		for(short loop2=0; loop2 < CountHolder; loop2++)
		{
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"One", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].One);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown1", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown1);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Type", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Type);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ClassID", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].ClassID);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"UnitID", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].UnitID);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown2", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown2);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ResourceIn", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].ResourceIn);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"SubType", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].SubType);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ResourceOut", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].ResourceOut);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown3", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown3);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"WorkRateMultiplier", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].WorkRateMultiplier);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ExecutionRadius", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].ExecutionRadius);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ExtraRange", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].ExtraRange);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown4", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown4);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown5", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown5);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown6", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown6);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown7", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown7);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown8", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown8);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown9", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown9);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown10", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown10);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown11", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown11);
			for(short loop3=0; loop3 < 6; loop3++)
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Graphic"+lexical_cast<string>(loop3), GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Graphics[loop3]);
		}
		}
		else
		{
		CountHolder = GenieFile->UnitHeaders[UnitIDs[0]].Commands.size();
		ExtractUnit.Write("CivX_Unit_Bird/CommandCount", CountHolder);
		for(short loop2=0; loop2 < CountHolder; loop2++)
		{
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"One", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].One);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown1", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown1);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Type", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Type);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ClassID", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ClassID);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"UnitID", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].UnitID);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown2", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown2);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ResourceIn", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ResourceIn);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"SubType", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].SubType);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ResourceOut", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ResourceOut);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown3", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown3);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"WorkRateMultiplier", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].WorkRateMultiplier);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ExecutionRadius", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ExecutionRadius);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ExtraRange", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ExtraRange);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown4", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown4);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown5", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown5);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown6", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown6);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown7", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown7);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown8", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown8);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown9", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown9);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown10", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown10);
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown11", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown11);
			for(short loop3=0; loop3 < 6; loop3++)
			ExtractUnit.Write("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Graphic"+lexical_cast<string>(loop3), GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Graphics[loop3]);
		}
		}

		ExtractUnit.Flush();
	}
	catch(...)
	{
		ExpError(ExtractUnit);
	}
}

void AGE_Frame::OnImportUnit(wxCommandEvent& Event)
{
	wxFileConfig ImportUnit(wxEmptyString, "Tapsa", "age2eUnit.txt", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	try
	{
		int Number;
		ImportUnit.Read("Version/Number", &Number, 0);
		if(!CorrectVersion(Number)) return;
		double Decimal; // float in newer wxWidgets!!!
		wxString Text;

		for(short loop=0; loop < GenieFile->Civs.size(); loop++)
		{
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Type", &Number, 10);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Type = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Class", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Class = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/LanguageDLLName", &Number, 5000);
			GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLName = (uint16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/LanguageDLLCreation", &Number, 6000);
			GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLCreation = (uint16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DyingGraphic1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DyingGraphic.first = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DyingGraphic2", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DyingGraphic.second = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DeathMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DeathMode = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/HitPoints", &Number, 1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].HitPoints = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/LineOfSight", &Decimal, 2);
			GenieFile->Civs[loop].Units[UnitIDs[0]].LineOfSight = (float)Decimal;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/GarrisonCapacity", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].GarrisonCapacity = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SizeRadius1", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SizeRadius.first = (float)Decimal;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SizeRadius2", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SizeRadius.second = (float)Decimal;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/HPBarHeight1", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].HPBarHeight1 = (float)Decimal;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DeadUnitID", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DeadUnitID = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/PlacementMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementMode = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/AirMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].AirMode = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/IconID", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].IconID = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/HideInEditor", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].HideInEditor = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown1 = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Enabled", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Enabled = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/PlacementBypassTerrain1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementBypassTerrain.first = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/PlacementBypassTerrain2", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementBypassTerrain.second = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/PlacementTerrain1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementTerrain.first = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/PlacementTerrain2", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementTerrain.second = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/EditorRadius1", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].EditorRadius.first = (float)Decimal;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/EditorRadius2", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].EditorRadius.second = (float)Decimal;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/BuildingMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].BuildingMode = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/VisibleInFog", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].VisibleInFog = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/TerrainRestriction", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].TerrainRestriction = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/FlyMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].FlyMode = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/ResourceCapacity", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceCapacity = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/ResourceDecay", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceDecay = (float)Decimal;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/BlastType", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].BlastType = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown2", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown2 = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/InteractionMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].InteractionMode = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/MinimapMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].MinimapMode = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/CommandAttribute", &Number, 0);
			if(GameVersion >= 2)
			GenieFile->Civs[loop].Units[UnitIDs[0]].CommandAttribute = (int16_t)Number;
			else
			GenieFile->Civs[loop].Units[UnitIDs[0]].CommandAttribute = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown3", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3 = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown3B", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3B = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/LanguageDLLHelp", &Number, 105000);
			GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLHelp = (int32_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/LanguageDLLHotKeyText", &Number, 155000);
			GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLHotKeyText = (int32_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/HotKey", &Number, 16000);
			GenieFile->Civs[loop].Units[UnitIDs[0]].HotKey = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown4", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown4 = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown5", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown5 = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unselectable", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unselectable = (bool)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown6", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown6 = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionMask", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionMask = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionShape", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionShape = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionRadius1", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionRadius.first = (float)Decimal;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionRadius2", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionRadius.second = (float)Decimal;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/HPBarHeight2", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].HPBarHeight2 = (float)Decimal;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionSound", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionSound = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DyingSound", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DyingSound = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/AttackSound", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].AttackSound = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Name", &Text, "Imported Unit");
			GenieFile->Civs[loop].Units[UnitIDs[0]].Name = (string)Text;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/NameLength", &Number, 13);
			GenieFile->Civs[loop].Units[UnitIDs[0]].NameLength = (uint16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/StandingGraphic1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].StandingGraphic.first = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/TrainSound1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].TrainSound.first = (int16_t)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionEffect", &Number, 1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionEffect = (char)Number;
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/EditorSelectionColour", &Number, 52);
			GenieFile->Civs[loop].Units[UnitIDs[0]].EditorSelectionColour = (char)Number;
			if(GameVersion >= 2)
			{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/StandingGraphic2", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].StandingGraphic.second = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/TrainSound2", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].TrainSound.second = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown7", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown7 = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown8", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown8 = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/SelectionShapeType", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionShapeType = (char)Number;
				if(GameVersion >= 3)
				{
					ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Attribute", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Attribute = (char)Number;
					ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Civilization", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Civilization = (char)Number;
					ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown9A", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown9[0] = (char)Number;
					ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown9B", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown9[1] = (char)Number;
					if(GameVersion >= 4)
					{
						ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Name2", &Text, "Imported Unit");
						GenieFile->Civs[loop].Units[UnitIDs[0]].Name2 = (string)Text;
						ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/NameLength2", &Number, 13);
						GenieFile->Civs[loop].Units[UnitIDs[0]].NameLength2 = (uint16_t)Number;
						ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unitline", &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Unitline = (int16_t)Number;
						ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/MinTechLevel", &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].MinTechLevel = (char)Number;
					}
				}
			}
			else
			{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Unknown3a", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3a = (char)Number;
			}
			for(short loop2=0; loop2 < 3; loop2++)
			{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Type", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Type = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Amount", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Amount = (float)Decimal;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Enabled", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Enabled = (char)Number;
			}
			ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/DamageGraphicCount", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics.resize(Number);
			for(short loop2=0; loop2 < GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics.size(); loop2++)
			{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Dama"+lexical_cast<string>(loop2)+"GraphicID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].GraphicID = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Dama"+lexical_cast<string>(loop2)+"DamagePercent", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].DamagePercent = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Dama"+lexical_cast<string>(loop2)+"Unknown1", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].Unknown1 = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Common/Dama"+lexical_cast<string>(loop2)+"Unknown2", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].Unknown2 = (char)Number;
			}
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type != 90)
			{
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 20)
			{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Flag/Speed", &Decimal, 1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Speed = (float)Decimal;
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 30)
			{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/WalkingGraphic1", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.WalkingGraphic.first = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/WalkingGraphic2", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.WalkingGraphic.second = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/RotationSpeed", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.RotationSpeed = (float)Decimal;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/Unknown11", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown11 = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/TrackingUnit", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnit = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/TrackingUnitUsed", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnitUsed = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/TrackingUnitDensity", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnitDensity = (float)Decimal;
				if(GameVersion >= 2)
				{
					ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/Unknown12", &Decimal, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown12 = (float)Decimal;
					for(short loop2=0; loop2 < 17; loop2++)
					{
					ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/Unknown16_"+lexical_cast<string>(loop2), &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown16[loop2] = (char)Number;
					}
				}
				else
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_DeadFish/Unknown16", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown16[0] = (char)Number;
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 40)
			{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/SheepConversion", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.SheepConversion = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/SearchRadius", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.SearchRadius = (float)Decimal;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/WorkRate", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.WorkRate = (float)Decimal;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/DropSite1", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.DropSite.first = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/DropSite2", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.DropSite.second = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/VillagerMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.VillagerMode = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/MoveSound", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.MoveSound = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/StopSound", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.StopSound = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Bird/AnimalMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.AnimalMode = (char)Number;
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 60)
			{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Unknown20", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown20 = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/AttackCount", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks.resize(Number);
				for(short loop2=0; loop2 < GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks.size(); loop2++)
				{
					ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Attack"+lexical_cast<string>(loop2)+"Class", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks[loop2].Class = (int16_t)Number;
					ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Attack"+lexical_cast<string>(loop2)+"Amount", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks[loop2].Amount = (int16_t)Number;
				}
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/ArmourCount", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours.resize(Number);
				for(short loop2=0; loop2 < GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours.size(); loop2++)
				{
					ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Armor"+lexical_cast<string>(loop2)+"Class", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours[loop2].Class = (int16_t)Number;
					ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Armor"+lexical_cast<string>(loop2)+"Amount", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours[loop2].Amount = (int16_t)Number;
				}
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Unknown21", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown21 = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/MaxRange", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.MaxRange = (float)Decimal;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/BlastRadius", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.BlastRadius = (float)Decimal;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/ProjectileUnitID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ProjectileUnitID = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/AccuracyPercent", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.AccuracyPercent = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/TowerMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.TowerMode = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Delay", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Delay = (int16_t)Number;
				for(short loop2=0; loop2 < 3; loop2++)
				{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/GraphicDisplacement"+lexical_cast<string>(loop2), &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.GraphicDisplacement[loop2] = (float)Decimal;
				}
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Unknown23", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown23 = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/MinRange", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.MinRange = (float)Decimal;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/AttackGraphic", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.AttackGraphic = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/DisplayedMeleeArmour", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedMeleeArmour = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/DisplayedAttack", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedAttack = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/DisplayedRange", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedRange = (float)Decimal;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/ReloadTime1", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ReloadTime1 = (float)Decimal;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/ReloadTime2", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ReloadTime2 = (float)Decimal;
				if(GameVersion >= 2)
				{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/GarrisonRecoveryRate", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.GarrisonRecoveryRate = (float)Decimal;
				if(GameVersion >= 3)
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Projectile/Unknown20_1", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown20_1 = (char)Number;
				}
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 70)
			{
				for(short loop2=0; loop2 < 3; loop2++)
				{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Type", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Type = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Amount", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Amount = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Enabled", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Enabled = (int16_t)Number;
				}
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/TrainTime", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.TrainTime = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/TrainLocationID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.TrainLocationID = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/ButtonID", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ButtonID = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/DisplayedPierceArmour", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.DisplayedPierceArmour = (int16_t)Number;
				if(GameVersion >= 2)
				{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/Unknown26", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown26 = (char)Number;
				for(short loop2=0; loop2 < 3; loop2++)
				{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/Unknown27_"+lexical_cast<string>(loop2), &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown27[loop2] = (int16_t)Number;
				}
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/Unknown28", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown28 = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/MissileGraphicDelay", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.MissileGraphicDelay = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/HeroMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.HeroMode = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/GarrisonGraphic1", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.GarrisonGraphic.first = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/GarrisonGraphic1", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.GarrisonGraphic.second = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/AttackMissileDuplicationAmount1", &Decimal, 1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationAmount1 = (float)Decimal;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/AttackMissileDuplicationAmount2", &Number, 1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationAmount2 = (char)Number;
				for(short loop2=0; loop2 < 3; loop2++)
				{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/AttackMissileDuplicationSpawning"+lexical_cast<string>(loop2), &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationSpawning[loop2] = (float)Decimal;
				}
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/AttackMissileDuplicationUnit", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationUnit = (int32_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/AttackMissileDuplicationGraphic", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationGraphic = (int32_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Creatable/Unknown29", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown29 = (char)Number;
				}
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type >= 80)
			{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/ConstructionGraphicID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ConstructionGraphicID = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/AdjacentMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.AdjacentMode = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown31", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown31 = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown31b", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown31b = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/StackUnitID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.StackUnitID = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/TerrainID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.TerrainID = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown32", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown32 = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/ResearchID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ResearchID = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/ConstructionSound", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ConstructionSound = (int16_t)Number;
				if(GameVersion >= 2)
				{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown33", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown33 = (char)Number;
				for(short loop2=0; loop2 < 4; loop2++)
				{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Annex"+lexical_cast<string>(loop2)+"UnitID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].UnitID = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Annex"+lexical_cast<string>(loop2)+"Misplacement1", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].Misplacement.first = (float)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Annex"+lexical_cast<string>(loop2)+"Misplacement2", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].Misplacement.second = (float)Number;
				}
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/HeadUnit", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.HeadUnit = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/TransformUnit", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.TransformUnit = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown34", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown34 = (int16_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/GarrisonType", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.GarrisonType = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/GarrisonHealRate", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.GarrisonHealRate = (float)Decimal;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown35", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown35 = (int32_t)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown36", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown36 = (int16_t)Number;
				for(short loop2=0; loop2 < 6; loop2++)
				{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/Unknown37_"+lexical_cast<string>(loop2), &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown37[loop2] = (char)Number;
				}
				if(GameVersion >= 3)
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_Building/SnowGraphicID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.SnowGraphicID = (int16_t)Number;
				}
			}}}}}}
			if(GenieFile->Civs[loop].Units[UnitIDs[0]].Type == 60)
			{
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/StretchMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.StretchMode = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/CompensationMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.CompensationMode = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/DropAnimationMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.DropAnimationMode = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/PenetrationMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.PenetrationMode = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/Unknown24", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.Unknown24 = (char)Number;
				ImportUnit.Read("Civ"+lexical_cast<string>(loop)+"_Unit_ProjectileOnly/ProjectileArc", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.ProjectileArc = (float)Decimal;
			}}
			if(GameVersion < 2)
			{
			ImportUnit.Read("CivX_Unit_Bird/CommandCount", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands.resize(Number);
			for(short loop2=0; loop2 < GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands.size(); loop2++)
			{
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"One", &Number, 1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].One = (int16_t)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown1", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown1 = (char)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Type", &Number, 7);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Type = (int16_t)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ClassID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ClassID = (int16_t)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"UnitID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].UnitID = (int16_t)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown2", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown2 = (int16_t)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ResourceIn", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ResourceIn = (int16_t)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"SubType", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].SubType = (int16_t)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ResourceOut", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ResourceOut = (int16_t)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown3", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown3 = (int16_t)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"WorkRateMultiplier", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].WorkRateMultiplier = (float)Decimal;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ExecutionRadius", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ExecutionRadius = (float)Decimal;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ExtraRange", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ExtraRange = (float)Decimal;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown4", &Number, 1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown4 = (char)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown5", &Decimal, 3);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown5 = (float)Decimal;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown6", &Number, 1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown6 = (char)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown7", &Number, 1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown7 = (char)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown8", &Number, 1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown8 = (int32_t)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown9", &Number, 5);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown9 = (char)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown10", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown10 = (char)Number;
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown11", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown11 = (char)Number;
				for(short loop3=0; loop3 < 6; loop3++)
				{
				ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Graphic"+lexical_cast<string>(loop3), &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Graphics[loop3] = (int16_t)Number;
				}
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ID = (int16_t)loop2;	//	ID Fix
			}
			}
		}
		if(GameVersion >= 2)
		{
		ImportUnit.Read("CivX_Unit_Bird/CommandCount", &Number, 0);
		GenieFile->UnitHeaders[UnitIDs[0]].Commands.resize(Number);
		for(short loop2=0; loop2 < GenieFile->UnitHeaders[UnitIDs[0]].Commands.size(); loop2++)
		{
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"One", &Number, 1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].One = (int16_t)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown1", &Number, 0);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown1 = (char)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Type", &Number, 7);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Type = (int16_t)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ClassID", &Number, -1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ClassID = (int16_t)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"UnitID", &Number, -1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].UnitID = (int16_t)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown2", &Number, -1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown2 = (int16_t)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ResourceIn", &Number, -1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ResourceIn = (int16_t)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"SubType", &Number, -1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].SubType = (int16_t)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ResourceOut", &Number, -1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ResourceOut = (int16_t)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown3", &Number, -1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown3 = (int16_t)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"WorkRateMultiplier", &Decimal, 0);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].WorkRateMultiplier = (float)Decimal;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ExecutionRadius", &Decimal, 0);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ExecutionRadius = (float)Decimal;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"ExtraRange", &Decimal, 0);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ExtraRange = (float)Decimal;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown4", &Number, 1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown4 = (char)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown5", &Decimal, 3);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown5 = (float)Decimal;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown6", &Number, 1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown6 = (char)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown7", &Number, 1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown7 = (char)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown8", &Number, 1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown8 = (int32_t)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown9", &Number, 5);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown9 = (char)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown10", &Number, 0);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown10 = (char)Number;
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Unknown11", &Number, 0);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown11 = (char)Number;
			for(short loop3=0; loop3 < 6; loop3++)
			{
			ImportUnit.Read("CivX_Unit_Bird/Command"+lexical_cast<string>(loop2)+"Graphic"+lexical_cast<string>(loop3), &Number, -1);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Graphics[loop3] = (int16_t)Number;
			}
			GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ID = (int16_t)loop2;	//	ID Fix
		}
		}

		wxCommandEvent E;
		OnUnitsSelect(E);
	}
	catch(...)
	{
		ImpError();
	}
}

void AGE_Frame::OnExtractGraphic(wxCommandEvent& Event)
{
	wxFileConfig ExtractGraphic(wxEmptyString, "Tapsa", "age2eGraphic.txt", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	try
	{
		ExtractGraphic.DeleteGroup("Graphic");
		auto CountHolder=0;
		ExtractGraphic.Write("Version/Number", VERSION_EXTRACT);

		ExtractGraphic.Write("Graphic/Name", GenieFile->Graphics[GraphicIDs[0]].Name);
		ExtractGraphic.Write("Graphic/Name2", GenieFile->Graphics[GraphicIDs[0]].Name2);
		ExtractGraphic.Write("Graphic/SLP", GenieFile->Graphics[GraphicIDs[0]].SLP);
		ExtractGraphic.Write("Graphic/Unknown1", GenieFile->Graphics[GraphicIDs[0]].Unknown1);
		ExtractGraphic.Write("Graphic/Unknown2", GenieFile->Graphics[GraphicIDs[0]].Unknown2);
		ExtractGraphic.Write("Graphic/Layer", GenieFile->Graphics[GraphicIDs[0]].Layer);
		ExtractGraphic.Write("Graphic/Unknown3", GenieFile->Graphics[GraphicIDs[0]].Unknown3);
		ExtractGraphic.Write("Graphic/Unknown4", GenieFile->Graphics[GraphicIDs[0]].Unknown4);
		ExtractGraphic.Write("Graphic/Replay", GenieFile->Graphics[GraphicIDs[0]].Replay);
		ExtractGraphic.Write("Graphic/Coordinate1", GenieFile->Graphics[GraphicIDs[0]].Coordinates[0]);
		ExtractGraphic.Write("Graphic/Coordinate2", GenieFile->Graphics[GraphicIDs[0]].Coordinates[1]);
		ExtractGraphic.Write("Graphic/Coordinate3", GenieFile->Graphics[GraphicIDs[0]].Coordinates[2]);
		ExtractGraphic.Write("Graphic/Coordinate4", GenieFile->Graphics[GraphicIDs[0]].Coordinates[3]);
		CountHolder = GenieFile->Graphics[GraphicIDs[0]].Deltas.size();
		ExtractGraphic.Write("Graphic/DeltaCount", CountHolder);
		ExtractGraphic.Write("Graphic/SoundID", GenieFile->Graphics[GraphicIDs[0]].SoundID);
		ExtractGraphic.Write("Graphic/AttackSoundUsed", GenieFile->Graphics[GraphicIDs[0]].AttackSoundUsed);
		ExtractGraphic.Write("Graphic/FrameCount", GenieFile->Graphics[GraphicIDs[0]].FrameCount);
		ExtractGraphic.Write("Graphic/AngleCount", GenieFile->Graphics[GraphicIDs[0]].AngleCount);
		ExtractGraphic.Write("Graphic/Unknown13", GenieFile->Graphics[GraphicIDs[0]].Unknown13);
		ExtractGraphic.Write("Graphic/FrameRate", GenieFile->Graphics[GraphicIDs[0]].FrameRate);
		ExtractGraphic.Write("Graphic/ReplayDelay", GenieFile->Graphics[GraphicIDs[0]].ReplayDelay);
		ExtractGraphic.Write("Graphic/SequenceType", GenieFile->Graphics[GraphicIDs[0]].SequenceType);
		ExtractGraphic.Write("Graphic/Type", GenieFile->Graphics[GraphicIDs[0]].Type);
		for(auto loop=0; loop < CountHolder; loop++)
		{
			ExtractGraphic.Write("Graphic/Delta"+lexical_cast<string>(loop)+"GraphicID", GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].GraphicID);
			ExtractGraphic.Write("Graphic/Delta"+lexical_cast<string>(loop)+"Unknown1", GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].Unknown1);
			ExtractGraphic.Write("Graphic/Delta"+lexical_cast<string>(loop)+"Unknown2", GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].Unknown2);
			ExtractGraphic.Write("Graphic/Delta"+lexical_cast<string>(loop)+"Unknown3", GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].Unknown3);
			ExtractGraphic.Write("Graphic/Delta"+lexical_cast<string>(loop)+"DirectionX", GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].DirectionX);
			ExtractGraphic.Write("Graphic/Delta"+lexical_cast<string>(loop)+"DirectionY", GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].DirectionY);
			ExtractGraphic.Write("Graphic/Delta"+lexical_cast<string>(loop)+"Unknown4", GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].Unknown4);
			ExtractGraphic.Write("Graphic/Delta"+lexical_cast<string>(loop)+"Unknown5", GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].Unknown5);
		}
		if(GenieFile->Graphics[GraphicIDs[0]].AttackSoundUsed != 0)
		for(auto loop=0; loop < GenieFile->Graphics[GraphicIDs[0]].AngleCount; loop++)
		{
			ExtractGraphic.Write("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundDelay", GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundDelay);
			ExtractGraphic.Write("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundID", GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundID);
			ExtractGraphic.Write("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundDelay2", GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundDelay2);
			ExtractGraphic.Write("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundID2", GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundID2);
			ExtractGraphic.Write("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundDelay3", GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundDelay3);
			ExtractGraphic.Write("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundID3", GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundID3);
		}

		ExtractGraphic.Flush();
	}
	catch(...)
	{
		ExpError(ExtractGraphic);
	}
}

void AGE_Frame::OnImportGraphic(wxCommandEvent& Event)
{
	wxFileConfig ImportGraphic(wxEmptyString, "Tapsa", "age2eGraphic.txt", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	try
	{
		int Number;
		ImportGraphic.Read("Version/Number", &Number, 0);
		if(!CorrectVersion(Number)) return;
		double Decimal;
		wxString Text;

		ImportGraphic.Read("Graphic/Name", &Text, "Imported Graphic");
		GenieFile->Graphics[GraphicIDs[0]].Name = ((string)Text).substr(0, GenieFile->Graphics[GraphicIDs[0]].getNameSize());
		ImportGraphic.Read("Graphic/Name2", &Text, "Imported Graphic");
		GenieFile->Graphics[GraphicIDs[0]].Name2 = ((string)Text).substr(0, GenieFile->Graphics[GraphicIDs[0]].getName2Size());
		ImportGraphic.Read("Graphic/SLP", &Number, -1);
		GenieFile->Graphics[GraphicIDs[0]].SLP = (int32_t)Number;
		ImportGraphic.Read("Graphic/Unknown1", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Unknown1 = (char)Number;
		ImportGraphic.Read("Graphic/Unknown2", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Unknown2 = (char)Number;
		ImportGraphic.Read("Graphic/Layer", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Layer = (char)Number;
		ImportGraphic.Read("Graphic/Unknown3", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Unknown3 = (char)Number;
		ImportGraphic.Read("Graphic/Unknown4", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Unknown4 = (char)Number;
		ImportGraphic.Read("Graphic/Replay", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Replay = (char)Number;
		ImportGraphic.Read("Graphic/Coordinate1", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Coordinates[0] = (int16_t)Number;
		ImportGraphic.Read("Graphic/Coordinate2", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Coordinates[1] = (int16_t)Number;
		ImportGraphic.Read("Graphic/Coordinate3", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Coordinates[2] = (int16_t)Number;
		ImportGraphic.Read("Graphic/Coordinate4", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Coordinates[3] = (int16_t)Number;
		ImportGraphic.Read("Graphic/DeltaCount", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Deltas.resize(Number);
		ImportGraphic.Read("Graphic/SoundID", &Number, -1);
		GenieFile->Graphics[GraphicIDs[0]].SoundID = (int16_t)Number;
		ImportGraphic.Read("Graphic/AttackSoundUsed", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].AttackSoundUsed = (char)Number;
		ImportGraphic.Read("Graphic/FrameCount", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].FrameCount = (uint16_t)Number;
		ImportGraphic.Read("Graphic/AngleCount", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].AngleCount = (uint16_t)Number;
		ImportGraphic.Read("Graphic/Unknown13", &Decimal, 0);
		GenieFile->Graphics[GraphicIDs[0]].Unknown13 = (float)Decimal;
		ImportGraphic.Read("Graphic/FrameRate", &Decimal, 0);
		GenieFile->Graphics[GraphicIDs[0]].FrameRate = (float)Decimal;
		ImportGraphic.Read("Graphic/ReplayDelay", &Decimal, 0);
		GenieFile->Graphics[GraphicIDs[0]].ReplayDelay = (float)Decimal;
		ImportGraphic.Read("Graphic/SequenceType", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].SequenceType = (char)Number;
		ImportGraphic.Read("Graphic/Type", &Number, 0);
		if(GameVersion >= 2)
		GenieFile->Graphics[GraphicIDs[0]].Type = (int16_t)Number;
		else
		GenieFile->Graphics[GraphicIDs[0]].Type = (char)Number;
		for(auto loop=0; loop < GenieFile->Graphics[GraphicIDs[0]].Deltas.size(); loop++)
		{
			ImportGraphic.Read("Graphic/Delta"+lexical_cast<string>(loop)+"GraphicID", &Number, -1);
			GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].GraphicID = (int16_t)Number;
			ImportGraphic.Read("Graphic/Delta"+lexical_cast<string>(loop)+"Unknown1", &Number, 0);
			GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].Unknown1 = (int16_t)Number;
			ImportGraphic.Read("Graphic/Delta"+lexical_cast<string>(loop)+"Unknown2", &Number, 0);
			GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].Unknown2 = (int16_t)Number;
			ImportGraphic.Read("Graphic/Delta"+lexical_cast<string>(loop)+"Unknown3", &Number, 0);
			GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].Unknown3 = (int16_t)Number;
			ImportGraphic.Read("Graphic/Delta"+lexical_cast<string>(loop)+"DirectionX", &Number, 0);
			GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].DirectionX = (int16_t)Number;
			ImportGraphic.Read("Graphic/Delta"+lexical_cast<string>(loop)+"DirectionY", &Number, 0);
			GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].DirectionY = (int16_t)Number;
			ImportGraphic.Read("Graphic/Delta"+lexical_cast<string>(loop)+"Unknown4", &Number, -1);
			GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].Unknown4 = (int16_t)Number;
			ImportGraphic.Read("Graphic/Delta"+lexical_cast<string>(loop)+"Unknown5", &Number, 0);
			GenieFile->Graphics[GraphicIDs[0]].Deltas[loop].Unknown5 = (int16_t)Number;
		}
		if(GenieFile->Graphics[GraphicIDs[0]].AttackSoundUsed != 0)
		{
			GenieFile->Graphics[GraphicIDs[0]].AttackSounds.resize(GenieFile->Graphics[GraphicIDs[0]].AngleCount);
			for(auto loop=0; loop < GenieFile->Graphics[GraphicIDs[0]].AngleCount; loop++)
			{
				ImportGraphic.Read("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundDelay", &Number, 0);
				GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundDelay = (int16_t)Number;
				ImportGraphic.Read("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundID", &Number, -1);
				GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundID = (int16_t)Number;
				ImportGraphic.Read("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundDelay2", &Number, 0);
				GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundDelay2 = (int16_t)Number;
				ImportGraphic.Read("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundID2", &Number, -1);
				GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundID2 = (int16_t)Number;
				ImportGraphic.Read("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundDelay3", &Number, 0);
				GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundDelay3 = (int16_t)Number;
				ImportGraphic.Read("Graphic/AttackSound"+lexical_cast<string>(loop)+"SoundID3", &Number, -1);
				GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop].SoundID3 = (int16_t)Number;
			}
		}

		wxCommandEvent E;
		OnGraphicsSelect(E);
	}
	catch(...)
	{
		ImpError();
	}
}
