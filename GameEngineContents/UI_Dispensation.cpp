#include "PreCompile.h"
#include "UI_Dispensation.h"

#include "UIManager.h"

UI_Dispensation::UI_Dispensation() 
{
}

UI_Dispensation::~UI_Dispensation() 
{
}


void UI_Dispensation::Start()
{
	UI_ToggleActor::Start();

	GameEngineInput::AddInputObject(this);
}

void UI_Dispensation::Update(float _Delta)
{
	UI_ToggleActor::Update(_Delta);

	UpdateKey();
}

void UI_Dispensation::Release()
{
	m_Base = nullptr;
	m_Frame = nullptr;
	m_Empty_Slot = nullptr;
	fire_icon_1 = nullptr;
	fire_icon_2 = nullptr;
	Fire_Gauge = nullptr;
	Fire_Gauge_Pin = nullptr;
	Direction_None = nullptr;
	Direction_CounterClockwise = nullptr;
	Direction_Clockwise = nullptr;

	m_DispensationSlotInfo.clear();
}

void UI_Dispensation::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void UI_Dispensation::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Dispensation::Init()
{
	RendererSetting();
	Off();
}


void UI_Dispensation::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Dispensation_Fire_Gauge.png"))
	{
		GameEngineSprite::CreateCut("Dispensation_Fire_Gauge.png", 5, 1);
		GameEngineSprite::CreateCut("dispensation_fire_gauge_pin.png", 5, 1);
	}

	m_Base = CreateComponent<GameEngineUIRenderer>();
	m_Base->Transform.SetLocalPosition(float4(0.0f, 10.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Base)));
	m_Base->SetSprite("Dispensation_Base.png");

	m_Frame = CreateComponent<GameEngineUIRenderer>();
	m_Frame->Transform.SetLocalPosition(float4(0.0f, 20.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Frame)));
	m_Frame->SetSprite("dispensation_partsb.png");

	m_Empty_Slot = CreateComponent<GameEngineUIRenderer>();
	m_Empty_Slot->Transform.SetLocalPosition(float4(0.0f, 149.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment)));
	m_Empty_Slot->SetSprite("dispensation_itemslot_set.png");

	fire_icon_1 = CreateComponent<GameEngineUIRenderer>();
	fire_icon_1->Transform.SetLocalPosition(float4(-88.0f, 8.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Frame)));
	fire_icon_1->SetSprite("dispensation_fire_icon_1.png");

	fire_icon_2 = CreateComponent<GameEngineUIRenderer>();
	fire_icon_2->Transform.SetLocalPosition(float4(88.0f, 8.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Frame)));
	fire_icon_2->SetSprite("dispensation_fire_icon_2.png");

	Fire_Gauge = CreateComponent<GameEngineUIRenderer>();
	Fire_Gauge->Transform.SetLocalPosition(float4(0.0f, 57.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment)));
	Fire_Gauge->SetSprite("Dispensation_Fire_Gauge.png", static_cast<int>(CurFire));
	
	Fire_Gauge_Pin = CreateComponent<GameEngineUIRenderer>();
	Fire_Gauge_Pin->Transform.SetLocalPosition(float4(0.0f, 30.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component)));
	Fire_Gauge_Pin->SetSprite("dispensation_fire_gauge_pin.png", static_cast<int>(CurFire));

	Direction_None = CreateComponent<GameEngineUIRenderer>();
	Direction_None->Transform.SetLocalPosition(float4(0.0f, -62.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component)));
	Direction_None->SetSprite("Dispensation_Direction_None_Check.png");

	Direction_CounterClockwise = CreateComponent<GameEngineUIRenderer>();
	Direction_CounterClockwise->Transform.SetLocalPosition(float4(-72.0f, -62.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component)));
	Direction_CounterClockwise->SetSprite("Dispensation_Direction_CounterClockwise.png");

	Direction_Clockwise = CreateComponent<GameEngineUIRenderer>();
	Direction_Clockwise->Transform.SetLocalPosition(float4(72.0f, -62.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component)));
	Direction_Clockwise->SetSprite("Dispensation_Direction_Clockwise.png");


	m_DispensationSlotInfo.resize(3);

	for (int i = 0; i < m_DispensationSlotInfo.size(); i++)
	{
		float4 Position = float4(-72.0f + (72.0f * i), 149.0f);
		Position.Z = GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component);

		m_DispensationSlotInfo[i].ItemImg = CreateComponent<GameEngineUIRenderer>();
		m_DispensationSlotInfo[i].ItemImg->Transform.SetLocalPosition(Position);
		m_DispensationSlotInfo[i].ItemImg->Off();
	}
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Dispensation::Open()
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	UIManager::MainUIManager->OpenInventory();
	

	On();
}

void UI_Dispensation::Close()
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	UIManager::MainUIManager->CloseInventory();

	Off();

	Clear();
}

void UI_Dispensation::Clear()
{

}


void UI_Dispensation::UpdateKey()
{
	if (true == GameEngineInput::IsDown('X', this))
	{
		Close();
		return;
	}

	if (true == GameEngineInput::IsDown('Q', this))
	{
		LowHit();
		return;
	}

	if (true == GameEngineInput::IsDown('W', this))
	{
		HighHit();
		return;
	}

	if (true == GameEngineInput::IsDown('E', this))
	{
		PrevDirection();
		return;
	}

	if (true == GameEngineInput::IsDown('R', this))
	{
		NextDirection();
		return;
	}
}



void UI_Dispensation::LowHit()
{
	if (EBREWING_FIRE::One == CurFire)
	{
		return;
	}

	int iFire = static_cast<int>(CurFire);
	--iFire;
	
	if (nullptr == Fire_Gauge)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}
	
	Fire_Gauge->SetSprite("Dispensation_Fire_Gauge.png", iFire);

	if (nullptr == Fire_Gauge_Pin)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Fire_Gauge_Pin->SetSprite("dispensation_fire_gauge_pin.png", iFire);

	CurFire = static_cast<EBREWING_FIRE>(iFire);
}

void UI_Dispensation::HighHit()
{
	if (EBREWING_FIRE::Five == CurFire)
	{
		return;
	}


	int iFire = static_cast<int>(CurFire);
	++iFire;

	if (nullptr == Fire_Gauge)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Fire_Gauge->SetSprite("Dispensation_Fire_Gauge.png", iFire);

	if (nullptr == Fire_Gauge_Pin)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Fire_Gauge_Pin->SetSprite("dispensation_fire_gauge_pin.png", iFire);

	CurFire = static_cast<EBREWING_FIRE>(iFire);
}

void UI_Dispensation::PrevDirection()
{
	if (EBREWING_DIRECTION::StirLeft == CurDirection)
	{
		return;
	}

	ChangeAllDirectionReset();

	if (EBREWING_DIRECTION::StirNone == CurDirection)
	{
		Direction_CounterClockwise->SetSprite("Dispensation_Direction_CounterClockwise_Check.png");
		CurDirection = EBREWING_DIRECTION::StirLeft;
	}

	if (EBREWING_DIRECTION::StirRight == CurDirection)
	{
		Direction_None->SetSprite("Dispensation_Direction_None_Check.png");
		CurDirection = EBREWING_DIRECTION::StirNone;
	}
}

void UI_Dispensation::NextDirection()
{
	if (EBREWING_DIRECTION::StirRight == CurDirection)
	{
		return;
	}

	ChangeAllDirectionReset();

	if (EBREWING_DIRECTION::StirNone == CurDirection)
	{
		Direction_Clockwise->SetSprite("Dispensation_Direction_Clockwise_Check.png");
		CurDirection = EBREWING_DIRECTION::StirRight;
	}

	if (EBREWING_DIRECTION::StirLeft == CurDirection)
	{
		Direction_None->SetSprite("Dispensation_Direction_None_Check.png");
		CurDirection = EBREWING_DIRECTION::StirNone;
	}
}


// �������� ���� ������ ��������Ʈ �̸��� 
void UI_Dispensation::ChangeAllDirectionReset()
{
	if (nullptr == Direction_None)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Direction_None->SetSprite("Dispensation_Direction_None.png");

	if (nullptr == Direction_CounterClockwise)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Direction_CounterClockwise->SetSprite("Dispensation_Direction_CounterClockwise.png");

	if (nullptr == Direction_Clockwise)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Direction_Clockwise->SetSprite("Dispensation_Direction_Clockwise.png");
}