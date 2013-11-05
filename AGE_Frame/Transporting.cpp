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

void AGE_Frame::OnExtractUnit(wxCommandEvent &Event)
{/*
	fstream ExtractUnit("age2eUnit.txt", ios_base::trunc | ios_base::binary | ios_base::out);
	ExtractUnit << VERSION_EXTRACT;
	ExtractUnit << GenieFile->Civs.size();
	for(auto loop=0; loop < GenieFile->Civs.size(); ++loop)
	{
		ExtractUnit << GenieFile->Civs[loop].Units[UnitIDs[0]];
	}
	ExtractUnit.flush();
	ExtractUnit.close();
/*	wxFileConfig ExtractUnit(wxEmptyString, "Tapsa", "age2eUnit.txt", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	try
	{
		ExtractUnit.DeleteGroup("Unit");
		auto CountHolder=0, UnitType=10;
		ExtractUnit.Write("Version/Number", VERSION_EXTRACT);

		for(auto loop=0; loop < GenieFile->Civs.size(); ++loop)
		{
			UnitType = GenieFile->Civs[loop].Units[UnitIDs[0]].Type;
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Type", UnitType);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Class", GenieFile->Civs[loop].Units[UnitIDs[0]].Class);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/LanguageDLLName", GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLName);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/LanguageDLLCreation", GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLCreation);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DyingGraphic1", GenieFile->Civs[loop].Units[UnitIDs[0]].DyingGraphic.first);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DyingGraphic2", GenieFile->Civs[loop].Units[UnitIDs[0]].DyingGraphic.second);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DeathMode", GenieFile->Civs[loop].Units[UnitIDs[0]].DeathMode);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/HitPoints", GenieFile->Civs[loop].Units[UnitIDs[0]].HitPoints);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/LineOfSight", GenieFile->Civs[loop].Units[UnitIDs[0]].LineOfSight);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/GarrisonCapacity", GenieFile->Civs[loop].Units[UnitIDs[0]].GarrisonCapacity);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SizeRadius1", GenieFile->Civs[loop].Units[UnitIDs[0]].SizeRadius.first);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SizeRadius2", GenieFile->Civs[loop].Units[UnitIDs[0]].SizeRadius.second);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/HPBarHeight1", GenieFile->Civs[loop].Units[UnitIDs[0]].HPBarHeight1);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DeadUnitID", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadUnitID);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/PlacementMode", GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementMode);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/AirMode", GenieFile->Civs[loop].Units[UnitIDs[0]].AirMode);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/IconID", GenieFile->Civs[loop].Units[UnitIDs[0]].IconID);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/HideInEditor", GenieFile->Civs[loop].Units[UnitIDs[0]].HideInEditor);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown1", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown1);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Enabled", GenieFile->Civs[loop].Units[UnitIDs[0]].Enabled);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/PlacementBypassTerrain1", GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementBypassTerrain.first);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/PlacementBypassTerrain2", GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementBypassTerrain.second);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/PlacementTerrain1", GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementTerrain.first);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/PlacementTerrain2", GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementTerrain.second);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/EditorRadius1", GenieFile->Civs[loop].Units[UnitIDs[0]].EditorRadius.first);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/EditorRadius2", GenieFile->Civs[loop].Units[UnitIDs[0]].EditorRadius.second);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/BuildingMode", GenieFile->Civs[loop].Units[UnitIDs[0]].BuildingMode);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/VisibleInFog", GenieFile->Civs[loop].Units[UnitIDs[0]].VisibleInFog);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/TerrainRestriction", GenieFile->Civs[loop].Units[UnitIDs[0]].TerrainRestriction);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/FlyMode", GenieFile->Civs[loop].Units[UnitIDs[0]].FlyMode);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/ResourceCapacity", GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceCapacity);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/ResourceDecay", GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceDecay);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/BlastType", GenieFile->Civs[loop].Units[UnitIDs[0]].BlastType);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown2", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown2);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/InteractionMode", GenieFile->Civs[loop].Units[UnitIDs[0]].InteractionMode);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/MinimapMode", GenieFile->Civs[loop].Units[UnitIDs[0]].MinimapMode);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/CommandAttribute", GenieFile->Civs[loop].Units[UnitIDs[0]].CommandAttribute);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown3", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown3B", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3B);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/LanguageDLLHelp", GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLHelp);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/LanguageDLLHotKeyText", GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLHotKeyText);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/HotKey", GenieFile->Civs[loop].Units[UnitIDs[0]].HotKey);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown4", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown4);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown5", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown5);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unselectable", GenieFile->Civs[loop].Units[UnitIDs[0]].Unselectable);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown6", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown6);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionMask", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionMask);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionShape", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionShape);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionEffect", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionEffect);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/EditorSelectionColour", GenieFile->Civs[loop].Units[UnitIDs[0]].EditorSelectionColour);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionRadius1", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionRadius.first);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionRadius2", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionRadius.second);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/HPBarHeight2", GenieFile->Civs[loop].Units[UnitIDs[0]].HPBarHeight2);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionSound", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionSound);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DyingSound", GenieFile->Civs[loop].Units[UnitIDs[0]].DyingSound);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/AttackSound", GenieFile->Civs[loop].Units[UnitIDs[0]].AttackSound);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/NameLength", GenieFile->Civs[loop].Units[UnitIDs[0]].NameLength);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Name", GenieFile->Civs[loop].Units[UnitIDs[0]].Name);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/StandingGraphic1", GenieFile->Civs[loop].Units[UnitIDs[0]].StandingGraphic.first);
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/TrainSound1", GenieFile->Civs[loop].Units[UnitIDs[0]].TrainSound.first);
			if(GameVersion >= 2)
			{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/StandingGraphic2", GenieFile->Civs[loop].Units[UnitIDs[0]].StandingGraphic.second);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/TrainSound2", GenieFile->Civs[loop].Units[UnitIDs[0]].TrainSound.second);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown7", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown7);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown8", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown8);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionShapeType", GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionShapeType);
				if(GameVersion >= 3)
				{
					ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Attribute", GenieFile->Civs[loop].Units[UnitIDs[0]].Attribute);
					ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Civilization", GenieFile->Civs[loop].Units[UnitIDs[0]].Civilization);
					ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown9A", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown9[0]);
					ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown9B", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown9[1]);
					if(GameVersion >= 4)
					{
						ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/NameLength2", GenieFile->Civs[loop].Units[UnitIDs[0]].NameLength2);
						ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Name2", GenieFile->Civs[loop].Units[UnitIDs[0]].Name2);
						ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unitline", GenieFile->Civs[loop].Units[UnitIDs[0]].Unitline);
						ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/MinTechLevel", GenieFile->Civs[loop].Units[UnitIDs[0]].MinTechLevel);
					}
				}
			}
			else
			{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown3a", GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3a);
			}
			for(auto loop2=0; loop2 < 3; ++loop2)
			{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Type", GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Type);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Amount", GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Amount);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Enabled", GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Enabled);
			}
			CountHolder = GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics.size();
			ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DamageGraphicCount", CountHolder);
			for(auto loop2=0; loop2 < CountHolder; ++loop2)
			{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Dama"+lexical_cast<string>(loop2)+"GraphicID", GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].GraphicID);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Dama"+lexical_cast<string>(loop2)+"DamagePercent", GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].DamagePercent);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Dama"+lexical_cast<string>(loop2)+"Unknown1", GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].Unknown1);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Dama"+lexical_cast<string>(loop2)+"Unknown2", GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].Unknown2);
			}
			if(UnitType != 90)
			{
			if(UnitType >= 20)
			{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Flag/Speed", GenieFile->Civs[loop].Units[UnitIDs[0]].Speed);
			if(UnitType >= 30)
			{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/WalkingGraphic1", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.WalkingGraphic.first);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/WalkingGraphic2", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.WalkingGraphic.second);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/RotationSpeed", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.RotationSpeed);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/Unknown11", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown11);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/TrackingUnit", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnit);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/TrackingUnitUsed", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnitUsed);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/TrackingUnitDensity", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnitDensity);
				if(GameVersion >= 2)
				{
					ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/Unknown12", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown12);
					for(auto loop2=1; loop2 < 17; ++loop2)
					ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/Unknown16_"+lexical_cast<string>(loop2), GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown16[loop2]);
				}
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/Unknown16_0", GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown16[0]);
			if(UnitType >= 40)
			{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/SheepConversion", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.SheepConversion);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/SearchRadius", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.SearchRadius);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/WorkRate", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.WorkRate);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/DropSite1", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.DropSite.first);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/DropSite2", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.DropSite.second);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/VillagerMode", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.VillagerMode);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/MoveSound", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.MoveSound);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/StopSound", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.StopSound);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/AnimalMode", GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.AnimalMode);
			if(UnitType >= 60)
			{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Unknown20", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown20);
				CountHolder = GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks.size();
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/AttackCount", CountHolder);
				for(auto loop2=0; loop2 < CountHolder; ++loop2)
				{
					ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Attack"+lexical_cast<string>(loop2)+"Class", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks[loop2].Class);
					ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Attack"+lexical_cast<string>(loop2)+"Amount", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks[loop2].Amount);
				}
				CountHolder = GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours.size();
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/ArmourCount", CountHolder);
				for(auto loop2=0; loop2 < CountHolder; ++loop2)
				{
					ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Armor"+lexical_cast<string>(loop2)+"Class", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours[loop2].Class);
					ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Armor"+lexical_cast<string>(loop2)+"Amount", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours[loop2].Amount);
				}
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Unknown21", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown21);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/MaxRange", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.MaxRange);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/BlastRadius", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.BlastRadius);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/ProjectileUnitID", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ProjectileUnitID);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/AccuracyPercent", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.AccuracyPercent);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/TowerMode", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.TowerMode);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Delay", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Delay);
				for(auto loop2=0; loop2 < 3; ++loop2)
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/GraphicDisplacement"+lexical_cast<string>(loop2), GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.GraphicDisplacement[loop2]);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Unknown23", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown23);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/MinRange", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.MinRange);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/AttackGraphic", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.AttackGraphic);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/DisplayedMeleeArmour", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedMeleeArmour);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/DisplayedAttack", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedAttack);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/DisplayedRange", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedRange);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/ReloadTime1", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ReloadTime1);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/ReloadTime2", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ReloadTime2);
				if(GameVersion >= 2)
				{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/GarrisonRecoveryRate", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.GarrisonRecoveryRate);
				if(GameVersion >= 3)
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Unknown20_1", GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown20_1);
				}
			if(UnitType >= 70)
			{
				for(auto loop2=0; loop2 < 3; ++loop2)
				{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Type", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Type);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Amount", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Amount);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Enabled", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Enabled);
				}
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/TrainTime", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.TrainTime);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/TrainLocationID", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.TrainLocationID);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/ButtonID", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ButtonID);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/DisplayedPierceArmour", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.DisplayedPierceArmour);
				if(GameVersion >= 2)
				{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/Unknown26", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown26);
				for(auto loop2=0; loop2 < 3; ++loop2)
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/Unknown27_"+lexical_cast<string>(loop2), GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown27[loop2]);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/Unknown28", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown28);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/MissileGraphicDelay", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.MissileGraphicDelay);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/HeroMode", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.HeroMode);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/GarrisonGraphic1", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.GarrisonGraphic.first);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/GarrisonGraphic2", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.GarrisonGraphic.second);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/AttackMissileDuplicationAmount1", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationAmount1);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/AttackMissileDuplicationAmount2", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationAmount2);
				for(auto loop2=0; loop2 < 3; ++loop2)
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/AttackMissileDuplicationSpawning"+lexical_cast<string>(loop2), GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationSpawning[loop2]);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/AttackMissileDuplicationUnit", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationUnit);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/AttackMissileDuplicationGraphic", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationGraphic);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/Unknown29", GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown29);
				}
			if(UnitType >= 80)
			{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/ConstructionGraphicID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ConstructionGraphicID);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/AdjacentMode", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.AdjacentMode);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown31", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown31);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown31b", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown31b);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/StackUnitID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.StackUnitID);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/TerrainID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.TerrainID);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown32", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown32);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/ResearchID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ResearchID);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/ConstructionSound", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ConstructionSound);
				if(GameVersion >= 2)
				{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown33", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown33);
				for(auto loop2=0; loop2 < 4; ++loop2)
				{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Annex"+lexical_cast<string>(loop2)+"UnitID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].UnitID);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Annex"+lexical_cast<string>(loop2)+"Misplacement1", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].Misplacement.first);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Annex"+lexical_cast<string>(loop2)+"Misplacement2", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].Misplacement.second);
				}
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/HeadUnit", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.HeadUnit);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/TransformUnit", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.TransformUnit);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown34", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown34);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/GarrisonType", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.GarrisonType);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/GarrisonHealRate", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.GarrisonHealRate);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown35", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown35);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown36", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown36);
				for(auto loop2=0; loop2 < 6; ++loop2)
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown37_"+lexical_cast<string>(loop2), GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown37[loop2]);
				if(GameVersion >= 3)
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_Building/SnowGraphicID", GenieFile->Civs[loop].Units[UnitIDs[0]].Building.SnowGraphicID);
				}
			}}}}}}
			if(UnitType == 60)
			{
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/StretchMode", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.StretchMode);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/CompensationMode", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.CompensationMode);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/DropAnimationMode", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.DropAnimationMode);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/PenetrationMode", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.PenetrationMode);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/Unknown24", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.Unknown24);
				ExtractUnit.Write("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/ProjectileArc", GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.ProjectileArc);
			}}
		}
		if(GameVersion < 2) // AoE and RoR
		{
			UnitType = GenieFile->Civs[0].Units[UnitIDs[0]].Type;
			if(UnitType >= 40 && UnitType <= 80)
			{
				CountHolder = GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands.size();
				ExtractUnit.Write("Unit/CivX_Bird/CommandCount", CountHolder);
				for(auto loop2=0; loop2 < CountHolder; ++loop2)
				{
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"One", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].One);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown1", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown1);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Type", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Type);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ClassID", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].ClassID);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"UnitID", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].UnitID);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown2", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown2);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ResourceIn", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].ResourceIn);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"SubType", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].SubType);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ResourceOut", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].ResourceOut);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown3", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown3);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"WorkRateMultiplier", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].WorkRateMultiplier);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ExecutionRadius", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].ExecutionRadius);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ExtraRange", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].ExtraRange);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown4", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown4);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown5", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown5);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown6", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown6);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown7", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown7);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown8", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown8);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown9", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown9);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown10", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown10);
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown11", GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown11);
					for(auto loop3=0; loop3 < 6; ++loop3)
					ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Graphic"+lexical_cast<string>(loop3), GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands[loop2].Graphics[loop3]);
				}
			}
		}
		else // AoK and above
		{
			CountHolder = GenieFile->UnitHeaders[UnitIDs[0]].Commands.size();
			ExtractUnit.Write("Unit/CivX_Bird/CommandCount", CountHolder);
			for(auto loop2=0; loop2 < CountHolder; ++loop2)
			{
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"One", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].One);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown1", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown1);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Type", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Type);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ClassID", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ClassID);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"UnitID", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].UnitID);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown2", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown2);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ResourceIn", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ResourceIn);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"SubType", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].SubType);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ResourceOut", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ResourceOut);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown3", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown3);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"WorkRateMultiplier", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].WorkRateMultiplier);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ExecutionRadius", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ExecutionRadius);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ExtraRange", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ExtraRange);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown4", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown4);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown5", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown5);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown6", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown6);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown7", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown7);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown8", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown8);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown9", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown9);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown10", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown10);
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown11", GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown11);
				for(auto loop3=0; loop3 < 6; ++loop3)
				ExtractUnit.Write("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Graphic"+lexical_cast<string>(loop3), GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Graphics[loop3]);
			}
		}

		ExtractUnit.Flush();
	}
	catch(...)
	{
		ExpError(ExtractUnit);
	}
*/}

void AGE_Frame::OnImportUnit(wxCommandEvent &Event)
{/*
	wxFileConfig ImportUnit(wxEmptyString, "Tapsa", "age2eUnit.txt", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	try
	{
		int Number, UnitType;
		ImportUnit.Read("Version/Number", &Number, 0);
		if(!CorrectVersion(Number)) return;
		double Decimal; // float in newer wxWidgets!!!
		wxString Text;

		for(auto loop=0; loop < GenieFile->Civs.size(); ++loop)
		{
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Type", &UnitType, 10);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Type = (char)UnitType;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Class", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Class = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/LanguageDLLName", &Number, 5000);
			GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLName = (uint16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/LanguageDLLCreation", &Number, 6000);
			GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLCreation = (uint16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DyingGraphic1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DyingGraphic.first = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DyingGraphic2", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DyingGraphic.second = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DeathMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DeathMode = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/HitPoints", &Number, 1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].HitPoints = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/LineOfSight", &Decimal, 2);
			GenieFile->Civs[loop].Units[UnitIDs[0]].LineOfSight = (float)Decimal;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/GarrisonCapacity", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].GarrisonCapacity = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SizeRadius1", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SizeRadius.first = (float)Decimal;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SizeRadius2", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SizeRadius.second = (float)Decimal;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/HPBarHeight1", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].HPBarHeight1 = (float)Decimal;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DeadUnitID", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DeadUnitID = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/PlacementMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementMode = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/AirMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].AirMode = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/IconID", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].IconID = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/HideInEditor", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].HideInEditor = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown1 = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Enabled", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Enabled = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/PlacementBypassTerrain1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementBypassTerrain.first = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/PlacementBypassTerrain2", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementBypassTerrain.second = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/PlacementTerrain1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementTerrain.first = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/PlacementTerrain2", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].PlacementTerrain.second = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/EditorRadius1", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].EditorRadius.first = (float)Decimal;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/EditorRadius2", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].EditorRadius.second = (float)Decimal;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/BuildingMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].BuildingMode = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/VisibleInFog", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].VisibleInFog = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/TerrainRestriction", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].TerrainRestriction = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/FlyMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].FlyMode = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/ResourceCapacity", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceCapacity = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/ResourceDecay", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceDecay = (float)Decimal;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/BlastType", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].BlastType = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown2", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown2 = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/InteractionMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].InteractionMode = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/MinimapMode", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].MinimapMode = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/CommandAttribute", &Number, 0);
			if(GameVersion >= 2)
			GenieFile->Civs[loop].Units[UnitIDs[0]].CommandAttribute = (int16_t)Number;
			else
			GenieFile->Civs[loop].Units[UnitIDs[0]].CommandAttribute = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown3", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3 = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown3B", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3B = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/LanguageDLLHelp", &Number, 105000);
			GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLHelp = (int32_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/LanguageDLLHotKeyText", &Number, 155000);
			GenieFile->Civs[loop].Units[UnitIDs[0]].LanguageDLLHotKeyText = (int32_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/HotKey", &Number, 16000);
			GenieFile->Civs[loop].Units[UnitIDs[0]].HotKey = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown4", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown4 = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown5", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown5 = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unselectable", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unselectable = (bool)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown6", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown6 = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionMask", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionMask = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionShape", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionShape = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionEffect", &Number, 1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionEffect = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/EditorSelectionColour", &Number, 52);
			GenieFile->Civs[loop].Units[UnitIDs[0]].EditorSelectionColour = (char)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionRadius1", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionRadius.first = (float)Decimal;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionRadius2", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionRadius.second = (float)Decimal;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/HPBarHeight2", &Decimal, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].HPBarHeight2 = (float)Decimal;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionSound", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionSound = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DyingSound", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DyingSound = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/AttackSound", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].AttackSound = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/NameLength", &Number, 13);
			GenieFile->Civs[loop].Units[UnitIDs[0]].NameLength = (uint16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Name", &Text, "Imported Unit");
			GenieFile->Civs[loop].Units[UnitIDs[0]].Name = (string)Text;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/StandingGraphic1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].StandingGraphic.first = (int16_t)Number;
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/TrainSound1", &Number, -1);
			GenieFile->Civs[loop].Units[UnitIDs[0]].TrainSound.first = (int16_t)Number;
			if(GameVersion >= 2)
			{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/StandingGraphic2", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].StandingGraphic.second = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/TrainSound2", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].TrainSound.second = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown7", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown7 = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown8", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown8 = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/SelectionShapeType", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].SelectionShapeType = (char)Number;
				if(GameVersion >= 3)
				{
					ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Attribute", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Attribute = (char)Number;
					ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Civilization", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Civilization = (char)Number;
					ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown9A", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown9[0] = (char)Number;
					ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown9B", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown9[1] = (char)Number;
					if(GameVersion >= 4)
					{
						ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/NameLength2", &Number, 13);
						GenieFile->Civs[loop].Units[UnitIDs[0]].NameLength2 = (uint16_t)Number;
						ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Name2", &Text, "Imported Unit");
						GenieFile->Civs[loop].Units[UnitIDs[0]].Name2 = (string)Text;
						ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unitline", &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Unitline = (int16_t)Number;
						ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/MinTechLevel", &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].MinTechLevel = (char)Number;
					}
				}
			}
			else
			{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Unknown3a", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Unknown3a = (char)Number;
			}
			for(auto loop2=0; loop2 < 3; ++loop2)
			{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Type", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Type = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Amount", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Amount = (float)Decimal;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/ResourceStorage"+lexical_cast<string>(loop2)+"Enabled", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ResourceStorages[loop2].Enabled = (char)Number;
			}
			ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/DamageGraphicCount", &Number, 0);
			GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics.resize(Number);
			for(auto loop2=0; loop2 < Number; ++loop2)
			{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Dama"+lexical_cast<string>(loop2)+"GraphicID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].GraphicID = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Dama"+lexical_cast<string>(loop2)+"DamagePercent", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].DamagePercent = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Dama"+lexical_cast<string>(loop2)+"Unknown1", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].Unknown1 = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Common/Dama"+lexical_cast<string>(loop2)+"Unknown2", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics[loop2].Unknown2 = (char)Number;
			}
			if(UnitType != 90)
			{
			if(UnitType >= 20)
			{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Flag/Speed", &Decimal, 1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Speed = (float)Decimal;
			if(UnitType >= 30)
			{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/WalkingGraphic1", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.WalkingGraphic.first = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/WalkingGraphic2", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.WalkingGraphic.second = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/RotationSpeed", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.RotationSpeed = (float)Decimal;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/Unknown11", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown11 = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/TrackingUnit", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnit = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/TrackingUnitUsed", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnitUsed = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/TrackingUnitDensity", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.TrackingUnitDensity = (float)Decimal;
				if(GameVersion >= 2)
				{
					ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/Unknown12", &Decimal, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown12 = (float)Decimal;
					for(auto loop2=1; loop2 < 17; ++loop2)
					{
					ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/Unknown16_"+lexical_cast<string>(loop2), &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown16[loop2] = (char)Number;
					}
				}
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_DeadFish/Unknown16_0", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].DeadFish.Unknown16[0] = (char)Number;
			if(UnitType >= 40)
			{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/SheepConversion", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.SheepConversion = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/SearchRadius", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.SearchRadius = (float)Decimal;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/WorkRate", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.WorkRate = (float)Decimal;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/DropSite1", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.DropSite.first = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/DropSite2", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.DropSite.second = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/VillagerMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.VillagerMode = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/MoveSound", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.MoveSound = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/StopSound", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.StopSound = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Bird/AnimalMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.AnimalMode = (char)Number;
				if(GameVersion < 2) // AoE and RoR
				{
					ImportUnit.Read("Unit/CivX_Bird/CommandCount", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands.resize(Number);
					for(auto loop2=0; loop2 < Number; ++loop2)
					{
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"One", &Number, 1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].One = (int16_t)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown1", &Number, 0);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown1 = (char)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Type", &Number, 7);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Type = (int16_t)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ClassID", &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ClassID = (int16_t)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"UnitID", &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].UnitID = (int16_t)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown2", &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown2 = (int16_t)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ResourceIn", &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ResourceIn = (int16_t)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"SubType", &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].SubType = (int16_t)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ResourceOut", &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ResourceOut = (int16_t)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown3", &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown3 = (int16_t)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"WorkRateMultiplier", &Decimal, 0);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].WorkRateMultiplier = (float)Decimal;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ExecutionRadius", &Decimal, 0);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ExecutionRadius = (float)Decimal;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ExtraRange", &Decimal, 0);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ExtraRange = (float)Decimal;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown4", &Number, 1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown4 = (char)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown5", &Decimal, 3);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown5 = (float)Decimal;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown6", &Number, 1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown6 = (char)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown7", &Number, 1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown7 = (char)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown8", &Number, 1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown8 = (int32_t)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown9", &Number, 5);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown9 = (char)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown10", &Number, 0);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown10 = (char)Number;
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown11", &Number, 0);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Unknown11 = (char)Number;
						for(auto loop3=0; loop3 < 6; ++loop3)
						{
						ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Graphic"+lexical_cast<string>(loop3), &Number, -1);
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].Graphics[loop3] = (int16_t)Number;
						}
						GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ID = loop2; // ID Fix
					}
				}
			if(UnitType >= 60)
			{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Unknown20", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown20 = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/AttackCount", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks.resize(Number);
				for(auto loop2=0; loop2 < Number; ++loop2)
				{
					ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Attack"+lexical_cast<string>(loop2)+"Class", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks[loop2].Class = (int16_t)Number;
					ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Attack"+lexical_cast<string>(loop2)+"Amount", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks[loop2].Amount = (int16_t)Number;
				}
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/ArmourCount", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours.resize(Number);
				for(auto loop2=0; loop2 < Number; ++loop2)
				{
					ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Armor"+lexical_cast<string>(loop2)+"Class", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours[loop2].Class = (int16_t)Number;
					ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Armor"+lexical_cast<string>(loop2)+"Amount", &Number, 0);
					GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours[loop2].Amount = (int16_t)Number;
				}
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Unknown21", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown21 = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/MaxRange", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.MaxRange = (float)Decimal;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/BlastRadius", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.BlastRadius = (float)Decimal;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/ProjectileUnitID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ProjectileUnitID = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/AccuracyPercent", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.AccuracyPercent = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/TowerMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.TowerMode = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Delay", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Delay = (int16_t)Number;
				for(auto loop2=0; loop2 < 3; ++loop2)
				{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/GraphicDisplacement"+lexical_cast<string>(loop2), &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.GraphicDisplacement[loop2] = (float)Decimal;
				}
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Unknown23", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown23 = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/MinRange", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.MinRange = (float)Decimal;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/AttackGraphic", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.AttackGraphic = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/DisplayedMeleeArmour", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedMeleeArmour = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/DisplayedAttack", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedAttack = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/DisplayedRange", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.DisplayedRange = (float)Decimal;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/ReloadTime1", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ReloadTime1 = (float)Decimal;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/ReloadTime2", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.ReloadTime2 = (float)Decimal;
				if(GameVersion >= 2)
				{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/GarrisonRecoveryRate", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.GarrisonRecoveryRate = (float)Decimal;
				if(GameVersion >= 3)
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Projectile/Unknown20_1", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Unknown20_1 = (char)Number;
				}
			if(UnitType >= 70)
			{
				for(auto loop2=0; loop2 < 3; ++loop2)
				{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Type", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Type = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Amount", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Amount = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/ResourceCost"+lexical_cast<string>(loop2)+"Enabled", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ResourceCosts[loop2].Enabled = (int16_t)Number;
				}
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/TrainTime", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.TrainTime = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/TrainLocationID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.TrainLocationID = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/ButtonID", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.ButtonID = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/DisplayedPierceArmour", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.DisplayedPierceArmour = (int16_t)Number;
				if(GameVersion >= 2)
				{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/Unknown26", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown26 = (char)Number;
				for(auto loop2=0; loop2 < 3; ++loop2)
				{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/Unknown27_"+lexical_cast<string>(loop2), &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown27[loop2] = (int16_t)Number;
				}
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/Unknown28", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown28 = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/MissileGraphicDelay", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.MissileGraphicDelay = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/HeroMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.HeroMode = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/GarrisonGraphic1", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.GarrisonGraphic.first = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/GarrisonGraphic1", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.GarrisonGraphic.second = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/AttackMissileDuplicationAmount1", &Decimal, 1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationAmount1 = (float)Decimal;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/AttackMissileDuplicationAmount2", &Number, 1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationAmount2 = (char)Number;
				for(auto loop2=0; loop2 < 3; ++loop2)
				{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/AttackMissileDuplicationSpawning"+lexical_cast<string>(loop2), &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationSpawning[loop2] = (float)Decimal;
				}
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/AttackMissileDuplicationUnit", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationUnit = (int32_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/AttackMissileDuplicationGraphic", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.AttackMissileDuplicationGraphic = (int32_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Creatable/Unknown29", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Creatable.Unknown29 = (char)Number;
				}
			if(UnitType >= 80)
			{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/ConstructionGraphicID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ConstructionGraphicID = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/AdjacentMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.AdjacentMode = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown31", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown31 = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown31b", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown31b = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/StackUnitID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.StackUnitID = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/TerrainID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.TerrainID = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown32", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown32 = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/ResearchID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ResearchID = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/ConstructionSound", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.ConstructionSound = (int16_t)Number;
				if(GameVersion >= 2)
				{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown33", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown33 = (char)Number;
				for(auto loop2=0; loop2 < 4; ++loop2)
				{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Annex"+lexical_cast<string>(loop2)+"UnitID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].UnitID = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Annex"+lexical_cast<string>(loop2)+"Misplacement1", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].Misplacement.first = (float)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Annex"+lexical_cast<string>(loop2)+"Misplacement2", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Annexes[loop2].Misplacement.second = (float)Number;
				}
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/HeadUnit", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.HeadUnit = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/TransformUnit", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.TransformUnit = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown34", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown34 = (int16_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/GarrisonType", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.GarrisonType = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/GarrisonHealRate", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.GarrisonHealRate = (float)Decimal;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown35", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown35 = (int32_t)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown36", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown36 = (int16_t)Number;
				for(auto loop2=0; loop2 < 6; ++loop2)
				{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/Unknown37_"+lexical_cast<string>(loop2), &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.Unknown37[loop2] = (char)Number;
				}
				if(GameVersion >= 3)
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_Building/SnowGraphicID", &Number, -1);
				GenieFile->Civs[loop].Units[UnitIDs[0]].Building.SnowGraphicID = (int16_t)Number;
				}
			}}}}}}
			if(UnitType == 60)
			{
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/StretchMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.StretchMode = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/CompensationMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.CompensationMode = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/DropAnimationMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.DropAnimationMode = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/PenetrationMode", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.PenetrationMode = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/Unknown24", &Number, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.Unknown24 = (char)Number;
				ImportUnit.Read("Unit/Civ"+lexical_cast<string>(loop)+"_ProjectileOnly/ProjectileArc", &Decimal, 0);
				GenieFile->Civs[loop].Units[UnitIDs[0]].ProjectileOnly.ProjectileArc = (float)Decimal;
			}}
		}
		if(GameVersion >= 2) // AoK and above
		{
			ImportUnit.Read("Unit/CivX_Bird/CommandCount", &Number, 0);
			GenieFile->UnitHeaders[UnitIDs[0]].Commands.resize(Number);
			for(auto loop2=0; loop2 < Number; ++loop2)
			{
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"One", &Number, 1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].One = (int16_t)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown1", &Number, 0);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown1 = (char)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Type", &Number, 7);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Type = (int16_t)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ClassID", &Number, -1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ClassID = (int16_t)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"UnitID", &Number, -1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].UnitID = (int16_t)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown2", &Number, -1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown2 = (int16_t)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ResourceIn", &Number, -1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ResourceIn = (int16_t)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"SubType", &Number, -1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].SubType = (int16_t)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ResourceOut", &Number, -1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ResourceOut = (int16_t)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown3", &Number, -1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown3 = (int16_t)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"WorkRateMultiplier", &Decimal, 0);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].WorkRateMultiplier = (float)Decimal;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ExecutionRadius", &Decimal, 0);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ExecutionRadius = (float)Decimal;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"ExtraRange", &Decimal, 0);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ExtraRange = (float)Decimal;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown4", &Number, 1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown4 = (char)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown5", &Decimal, 3);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown5 = (float)Decimal;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown6", &Number, 1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown6 = (char)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown7", &Number, 1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown7 = (char)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown8", &Number, 1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown8 = (int32_t)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown9", &Number, 5);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown9 = (char)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown10", &Number, 0);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown10 = (char)Number;
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Unknown11", &Number, 0);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Unknown11 = (char)Number;
				for(auto loop3=0; loop3 < 6; ++loop3)
				{
				ImportUnit.Read("Unit/CivX_Bird/Command"+lexical_cast<string>(loop2)+"Graphic"+lexical_cast<string>(loop3), &Number, -1);
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].Graphics[loop3] = (int16_t)Number;
				}
				GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ID = loop2; // ID Fix
			}
		}

		wxCommandEvent E;
		OnUnitsSelect(E);
	}
	catch(...)
	{
		ImpError();
	}
*/}

void AGE_Frame::OnExtractGraphic(wxCommandEvent &Event)
{/*
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
		for(auto loop=0; loop < CountHolder; ++loop)
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
		for(auto loop=0; loop < GenieFile->Graphics[GraphicIDs[0]].AngleCount; ++loop)
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
*/}

void AGE_Frame::OnImportGraphic(wxCommandEvent &Event)
{/*
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
		ImportGraphic.Read("Graphic/SoundID", &Number, -1);
		GenieFile->Graphics[GraphicIDs[0]].SoundID = (int16_t)Number;
		ImportGraphic.Read("Graphic/FrameCount", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].FrameCount = (uint16_t)Number;
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
		ImportGraphic.Read("Graphic/DeltaCount", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].Deltas.resize(Number);
		for(auto loop=0; loop < Number; ++loop)
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
		ImportGraphic.Read("Graphic/AttackSoundUsed", &Number, 0);
		GenieFile->Graphics[GraphicIDs[0]].AttackSoundUsed = (char)Number;
		if(Number != 0)
		{
			ImportGraphic.Read("Graphic/AngleCount", &Number, 0);
			GenieFile->Graphics[GraphicIDs[0]].AngleCount = (uint16_t)Number;
			GenieFile->Graphics[GraphicIDs[0]].AttackSounds.resize(Number);
			for(auto loop=0; loop < Number; ++loop)
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
*/}
