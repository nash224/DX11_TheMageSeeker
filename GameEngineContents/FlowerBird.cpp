#include "PreCompile.h"
#include "FlowerBird.h"

FlowerBird::FlowerBird() 
{
}

FlowerBird::~FlowerBird() 
{
}


// �ɻ� �ൿ 
// �⺻������ ���ְ�(Idle), �������� ����(Position ���� �ٲ��� ����)
// �� ������ �ٲ� (Turn)
// Turn�Ҷ� �������� 1,2,4 �� �ٲܶ��� ����
// �ٴ��� �̶� 2���� 2��

// ���� ���ֹٲٰ� �ٴ��� �ɴ� �ൿ�� ���� �ǿ�� �ൿ�� ����
// �ൿ�� �ٲٴ°� Idle���� ����ǰ� ������ 1:1:1:1:1 ��������

// ���� �ǿﶧ, ���� ���� �õ�� �ൿ�� ���� ��񵿾� ������ �� �ൿ�� ����
// ���� �õ鶩, ���츮���� ��� ���� �ִٰ� ���� �ǿ���� �õ�
// ���� �õ鶧 0.5~2s ���� ���

// ���� Ȯ��(1/3 ����?)�� ���� ������ �ǰԵǴµ�
// ���� ������ �ʶ�, 1�ʵ��� �ǰ� �ٽ� �ٸ� �ൿ


// ���ǰ� ��ȣ�ۿ��ؼ� ���� ������ ����߸��� �ൿ�� ����
// ����


void FlowerBird::Start()
{
	DynamicEntity::Start();
}

void FlowerBird::Update(float _Delta)
{
	DynamicEntity::Update(_Delta);
}

void FlowerBird::Release()
{
	DynamicEntity::Release();

	m_Shadow = nullptr;
}

void FlowerBird::LevelStart(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelStart(_NextLevel);
}

void FlowerBird::LevelEnd(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void FlowerBird::Init()
{
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Gloves);
	ApplyDepth(Transform.GetLocalPosition());
	AnimationSetting();
	DirectionSetting();
}

void FlowerBird::AnimationSetting()
{
	m_Body = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	if (nullptr == m_Body)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_Body->CreateAnimation("Idle", "FlowerBird_Standing.png");
	m_Body->CreateAnimation("Turn", "FlowerBird_IdleA.png", 0.06f, 3, 5, false);
	m_Body->CreateAnimation("Pick", "FlowerBird_IdleC.png", 0.06f, 4, 5, true);

	m_Body->CreateAnimation("Bloom", "FlowerBird_Bloom.png", 0.06f, 2, 10, false);
	m_Body->CreateAnimation("BloomFake", "FlowerBird_BloomC.png", 0.06f, 2, 10, false);

	m_Body->CreateAnimation("Fly", "FlowerBird_Fly.png", 0.06f, 1, 4, true);
	m_Body->CreateAnimation("Fly_Bloom", "FlowerBird_FlyB.png", 0.06f, 1, 4, true);


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Shadow);
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_Shadow->SetSprite("FlowerBird_Standing.png", 1);


	m_Body->SetFrameEvent("Pick", 4, [=](GameEngineSpriteRenderer* _Renderer)
		{
			m_Shadow->SetSprite("FlowerBird_IdleC.png", 2);
			++m_PickCount;
		});


	m_Body->SetEndEvent("Pick", [=](GameEngineSpriteRenderer* _Renderer)
		{
			m_Shadow->SetSprite("FlowerBird_Standing.png", 1);
		});


	m_Body->SetStartEvent("Fly", [=](GameEngineSpriteRenderer* _Renderer)
		{
			m_Shadow->Off();
		});

	m_Body->SetStartEvent("Fly_Bloom", [=](GameEngineSpriteRenderer* _Renderer)
		{
			m_Shadow->Off();
		});
}


void FlowerBird::DirectionSetting()
{
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());
	int Value = RandomClass.RandomInt(0, 1);

	switch (Value)
	{
	case 0:
		m_Dir = EDIRECTION::LEFT;
		break;
	case 1:
		m_Dir = EDIRECTION::RIGHT;
		break;
	default:
		break;
	}
}


void FlowerBird::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EFLOWERBIRDSTATE::Idle:						UpdateIdle(_Delta); 									break;
	case EFLOWERBIRDSTATE::Turn:						UpdateTurn(_Delta); 									break;
	case EFLOWERBIRDSTATE::Pick:						UpdatePick(_Delta); 									break;
	case EFLOWERBIRDSTATE::Bloom:						UpdateBloom(_Delta); 									break;
	case EFLOWERBIRDSTATE::BloomFake:					UpdateBloomFake(_Delta); 								break;
	case EFLOWERBIRDSTATE::BloomFlowers:				UpdateBloomFlowers(_Delta); 							break;
	case EFLOWERBIRDSTATE::Fly:							UpdateFly(_Delta); 										break;
	case EFLOWERBIRDSTATE::None:
		break;
	default:
		break;
	}
}

void FlowerBird::ChangeState(EFLOWERBIRDSTATE _State)
{
	if (_State != m_State)
	{
		switch (m_State)
		{
		case EFLOWERBIRDSTATE::Idle:					EndIdle(); 												break;
		case EFLOWERBIRDSTATE::Turn:					 														break;
		case EFLOWERBIRDSTATE::Pick:					 														break;
		case EFLOWERBIRDSTATE::Bloom:					 														break;
		case EFLOWERBIRDSTATE::BloomFake:				 														break;
		case EFLOWERBIRDSTATE::BloomFlowers:			 														break;
		case EFLOWERBIRDSTATE::Fly:							 													break;
		case EFLOWERBIRDSTATE::None:
		{
			MsgBoxAssert("�ش� �ൿ���� ��ȯ�� �� �����ϴ�.");
			return;
		}
		break;
		default:
			break;
		}

		switch (_State)
		{
		case EFLOWERBIRDSTATE::Idle:					StartIdle(); 											break;
		case EFLOWERBIRDSTATE::Turn:					StartTurn(); 											break;
		case EFLOWERBIRDSTATE::Pick:					StartPick(); 											break;
		case EFLOWERBIRDSTATE::Bloom:					StartBloom(); 											break;
		case EFLOWERBIRDSTATE::BloomFake:				StartBloomFake(); 										break;
		case EFLOWERBIRDSTATE::BloomFlowers:			StartBloomFlowers(); 									break;
		case EFLOWERBIRDSTATE::Fly:						StartFly(); 											break;
		case EFLOWERBIRDSTATE::None:
		{
			MsgBoxAssert("�ش� �ൿ���� ��ȯ�� �� �����ϴ�.");
			return;
		}
			break;
		default:
			break;
		}

		m_State = _State;
	}
}

void FlowerBird::ChangeFlowerBirdAnimation(std::string_view _AnimationName)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	m_Body->ChangeAnimation(_AnimationName);
}