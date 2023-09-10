#include "PreCompile.h"
#include "MainMenu_Trains.h"

#include "TrainPart.h"

MainMenu_Trains::MainMenu_Trains() 
	:
	m_State(TrainState::None),
	m_TrainState(0),
	m_StateTime(0.0f),
	m_RattleCycle(0.3f)
{	
}
MainMenu_Trains::~MainMenu_Trains()
{
}


void MainMenu_Trains::Start()
{
	m_TrainState = 0;
	m_State = TrainState::RattleUp;
}

void MainMenu_Trains::Update(float _Delta)
{
	UpdateTrainFSM(_Delta);
}

void MainMenu_Trains::Release()
{

}

void MainMenu_Trains::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void MainMenu_Trains::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


#pragma region ���� ����

void MainMenu_Trains::Init()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	vecTrain.reserve(CONST_TrainCount);

	{
		std::shared_ptr<TrainPart> Object = CurLevel->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("���� ������ �����Ͽ����ϴ�.");
			return;
		}

		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train.png", "Title_Train_Window_0.png");
		Object->SetLocalPosition(CONST_Train0Position, CONST_TrainLight0Position);
		vecTrain.push_back(Object);
	}

	{
		std::shared_ptr<TrainPart> Object = CurLevel->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("���� ������ �����Ͽ����ϴ�.");
			return;
		}

		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train_1.png", "Title_Train_Window_1.png");
		Object->SetLocalPosition(CONST_Train1Position, CONST_TrainLight1Position);
		vecTrain.push_back(Object);
	}

	{
		std::shared_ptr<TrainPart> Object = CurLevel->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("���� ������ �����Ͽ����ϴ�.");
			return;
		}

		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train_2.png", "Title_Train_Window_2.png");
		Object->SetLocalPosition(CONST_Train2Position, CONST_TrainLight2Position);
		vecTrain.push_back(Object);
	}

	{
		std::shared_ptr<TrainPart> Object = CurLevel->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("���� ������ �����Ͽ����ϴ�.");
			return;
		}

		Object->CreateRenderer();
		Object->SetSprite("Title_Train_Train_3.png", "Title_Train_Light.png");
		Object->SetLocalPosition(CONST_Train3Position, CONST_TrainLight3Position);
		vecTrain.push_back(Object);
	}

	{
		std::shared_ptr<TrainPart> Object = CurLevel->CreateActor<TrainPart>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("���� ������ �����Ͽ����ϴ�.");
			return;
		}

		Object->CreateLastTrainRenderer();
		Object->SetSprite("Title_Train_Train_4.png");
		Object->SetLocalPosition(CONST_Train4Position);
		vecTrain.push_back(Object);
	}
}

#pragma endregion 


void MainMenu_Trains::ActorRelease()
{
	for (size_t i = 0; i < vecTrain.size(); i++)
	{
		std::shared_ptr<TrainPart> Train = vecTrain[i];
		if (nullptr == Train)
		{
			MsgBoxAssert("�������� �ʴ� ���͸� �����Ϸ��� �߽��ϴ�.");
			return;
		}

		Train->ActorRelease();
	}

	vecTrain.clear();

	Death();
}



void MainMenu_Trains::SetRattleCycle(float _Value)
{
	m_RattleCycle = _Value;
}





void MainMenu_Trains::UpdateTrainFSM(float _Delta)
{
	switch (m_State)
	{
	case TrainState::None:
	{
		MsgBoxAssert("�ൿ�� ���������� �ʾҽ��ϴ�.");
		return;
	}
		break;
	case TrainState::RattleUp:
		UpdateRattleUp(_Delta);
		break;
	case TrainState::RattleDown:
		UpdateRattleDown(_Delta);
		break;
	case TrainState::Wait:
		UpdateWait(_Delta);
		break;
	default:
		break;
	}


}

void MainMenu_Trains::ChangeState(TrainState _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case TrainState::None:
		{
			MsgBoxAssert("�ൿ�� None ���� �������� �� �����ϴ�.");
			return;
		}
			break;
		case TrainState::RattleUp:
			StartRattleUp();
			break;
		case TrainState::RattleDown:
			StartRattleDown();
			break;
		case TrainState::Wait:
			StartWait();
			break;
		default:
			break;
		}

		m_State = _State;
	}
}



void MainMenu_Trains::StartRattleUp()
{
	m_StateTime = 0.0f;

	std::shared_ptr<TrainPart> Train = vecTrain[m_TrainState];
	if (nullptr == Train)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}
	
	Train->AddLocalPosition(CONST_RattleUpDistance);
}

void MainMenu_Trains::UpdateRattleUp(float _Delta)
{
	m_StateTime += _Delta;
	if (m_StateTime > CONST_RattleTime)
	{
		ChangeState(TrainState::RattleDown);
		return;
	}
}



void MainMenu_Trains::StartRattleDown()
{
	m_StateTime = 0.0f;

	std::shared_ptr<TrainPart> Train = vecTrain[m_TrainState];
	if (nullptr == Train)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	Train->AddLocalPosition(CONST_RattleDownDistance);
}

void MainMenu_Trains::UpdateRattleDown(float _Delta)
{
	m_StateTime += _Delta;
	if (m_StateTime > m_RattleCycle)
	{
		if (m_TrainState < CONST_TrainCount - 1)
		{
			m_TrainState++;
			ChangeState(TrainState::RattleUp);
			return;
		}
		else
		{

			ChangeState(TrainState::Wait);
			return;
		}
	}
}


void MainMenu_Trains::StartWait()
{
	m_StateTime = 0.0f;
	m_TrainState = 0;

}

void MainMenu_Trains::UpdateWait(float _Delta)
{
	m_StateTime += _Delta;

	if (m_StateTime > CONST_WaitTime)
	{
		ChangeState(TrainState::RattleUp);
		return;
	}
}
