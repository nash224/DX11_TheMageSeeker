#include "PreCompile.h"
#include "UI_Hub_Tool.h"


ETOOLTYPE UI_Hub_Tool::m_CurrentTool = ETOOLTYPE::None;
UI_Hub_Tool::UI_Hub_Tool() 
{
}

UI_Hub_Tool::~UI_Hub_Tool() 
{
}


void UI_Hub_Tool::Start()
{
	UI_Hub_Actor::Start();
}

void UI_Hub_Tool::Update(float _Delta)
{
	UI_Hub_Actor::Update(_Delta);

	DetectToolChange();
	UpdateToolArrow(_Delta);
}

void UI_Hub_Tool::LevelStart(class GameEngineLevel* _NextLevel)
{
	UI_Hub_Actor::LevelStart(_NextLevel);

	ChangeToolImg();
}

void UI_Hub_Tool::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_Hub_Actor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Hub_Tool::Init()
{
	m_CurrentTool = ETOOLTYPE::Gloves;

	Transform.AddLocalPosition({ -418.0f , -196.0f });

	float4 UIPosition = float4::ZERO;

	m_Tool = CreateComponent<GameEngineUIRenderer>();
	UIPosition = { 0.0f , 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::HUB_Icon) };
	m_Tool->Transform.SetLocalPosition(UIPosition);
	m_Tool->SetSprite("Tool_Icon.png", static_cast<int>(m_CurrentTool));

	m_LeftArrow = CreateComponent<GameEngineUIRenderer>();
	m_LeftArrow->SetSprite("HUD_Arrow_Left.png");
	UIPosition = { -28.0f , 0.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::UIArrow) };
	m_LeftArrow->Transform.AddLocalPosition(UIPosition);

	m_RightArrow = CreateComponent<GameEngineUIRenderer>();
	m_RightArrow->SetSprite("HUD_Arrow_Left.png");
	m_RightArrow->LeftFlip();
	UIPosition = { 26.0f , 0.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::UIArrow) };
	m_RightArrow->Transform.AddLocalPosition({ 26.0f , 0.0f });
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Hub_Tool::DetectToolChange()
{
	if (true == GameEngineInput::IsDown('Q', this))
	{
		PrevTool();
	}

	if (true == GameEngineInput::IsDown('W', this))
	{
		NextTool();
	}
}

void UI_Hub_Tool::NextTool()
{
	int TrueValue = 0;

	// 데이터에 true가 1개면 움직이지 않는다는 것으로 리턴해줍니다.
	for (size_t i = 0; i < EventData::ToolData.size(); i++)
	{
		if (true == EventData::ToolData[i])
		{
			++TrueValue;
		}

		if (TrueValue >= 2)
		{
			break;
		}

		if (i == EventData::ToolData.size() - 1)
		{
			return;
		}
	}

	int ToolValue = static_cast<int>(m_CurrentTool);

	// 얻지 못한 도구는 선택을 못하게 합니다.
	while (true)
	{
		++ToolValue;

		ETOOLTYPE EToolValue = static_cast<ETOOLTYPE>(ToolValue);
		if (ETOOLTYPE::None == EToolValue)
		{
			ToolValue = 0;
		}

		if (true == EventData::ToolData[ToolValue])
		{
			m_CurrentTool = static_cast<ETOOLTYPE>(ToolValue);
			break;
		}
	}

	ChangeToolImg();

	IsChangeTool = true;
}

void UI_Hub_Tool::PrevTool()
{
	int TrueValue = 0;

	// 데이터에 true가 1개면 움직이지 않는다는 것으로 리턴해줍니다.
	for (size_t i = 0; i < EventData::ToolData.size(); i++)
	{
		if (true == EventData::ToolData[i])
		{
			++TrueValue;
		}

		if (TrueValue >= 2)
		{
			break;
		}

		if (i == EventData::ToolData.size() - 1)
		{
			return;
		}
	}

	int ToolValue = static_cast<int>(m_CurrentTool);

	while (true)
	{
		--ToolValue;

		if (-1 == ToolValue)
		{
			ToolValue = static_cast<int>(ETOOLTYPE::None) - 1;
		}

		if (true == EventData::ToolData[ToolValue])
		{
			m_CurrentTool = static_cast<ETOOLTYPE>(ToolValue);
			break;
		}
	}

	ChangeToolImg();

	IsChangeTool = true;
}

// 현재 도구 이미지와 다르면 변경합니다.

void UI_Hub_Tool::ChangeToolImg()
{
	if (m_CurrentToolRenderNumber == static_cast<int>(m_CurrentTool))
	{
		return;
	}

	if (nullptr == m_Tool)
	{
		MsgBoxAssert("존재하지 않은 렌더러를 생성하려 했습니다.");
		return;
	}

	m_Tool->SetSprite("Tool_Icon.png", static_cast<int>(m_CurrentTool));

	m_CurrentToolRenderNumber = static_cast<int>(m_CurrentTool);
}

// 도구 이미지를 변경합니다.
void UI_Hub_Tool::ChangeToolImg(ETOOLTYPE _Type)
{
	if (nullptr == m_Tool)
	{
		MsgBoxAssert("존재하지 않은 렌더러를 생성하려 했습니다.");
		return;
	}

	m_Tool->SetSprite("Tool_Icon.png", static_cast<int>(_Type));

	m_CurrentToolRenderNumber = static_cast<int>(_Type);
}


void UI_Hub_Tool::UpdateToolArrow(float _Delta)
{

}