#include "PreCompile.h"
#include "FieldLevel.h"

#include "SkyLerp.h"
#include "TimeManager.h"
#include "BGMManager.h"


FieldLevel::FieldLevel() 
{
	
}

FieldLevel::~FieldLevel() 
{
}


void FieldLevel::Start()
{
	PlayLevel::Start();
	LevelType = ELEVELTYPE::Field;

	m_SkyLerp = CreateActor<SkyLerp>(EUPDATEORDER::Sky);
	m_SkyLerp->Init();
}

void FieldLevel::Update(float _Delta)
{
	PlayLevel::Update(_Delta);

	AutoPlayBGM();
}

void FieldLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelStart(_NextLevel);
}

void FieldLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void FieldLevel::AutoPlayBGM()
{
	if (nullptr != MainPlaySound && nullptr != s_TimeManager)
	{
		int bgmType = MainPlaySound->GetPlayType();
		if (true == s_TimeManager->IsDay() && static_cast<int>(EPLAYBGMTYPE::Day) != bgmType)
		{
			MainPlaySound->PlayBGM(EPLAYBGMTYPE::Day, "0424_Forest_Day.wav", "AMB_GF_Daytime_01.wav");
		}

		if (false == s_TimeManager->IsDay() && static_cast<int>(EPLAYBGMTYPE::Night) != bgmType)
		{
			MainPlaySound->PlayBGM(EPLAYBGMTYPE::Night, "0424_Forest_Night.wav", "AMB_GF_Nighttime_01.wav");
		}
	}
}