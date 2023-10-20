#include "PreCompile.h"
#include "BackDrop_PlayLevel.h"


#include "Prop.h"
#include "Props.h"
#include "StaticEntity.h"
#include "PortalObject.h"

#include "LootedItem.h"



BackDrop_PlayLevel* BackDrop_PlayLevel::MainBackDrop = nullptr;
DayStatus  BackDrop_PlayLevel::TimeOfDay = DayStatus::None;
BackDrop_PlayLevel::BackDrop_PlayLevel() 
{
}

BackDrop_PlayLevel::~BackDrop_PlayLevel() 
{
}


void BackDrop_PlayLevel::Start()
{
	BackDrop::Start();
}

void BackDrop_PlayLevel::Update(float _Delta)
{
	BackDrop::Update(_Delta);
}

void BackDrop_PlayLevel::Release()
{
	BackDrop::Release();
}

void BackDrop_PlayLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelStart(_NextLevel);

	MainBackDrop = this;
}

void BackDrop_PlayLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelEnd(_NextLevel);

	m_BackProp.clear();
	vecPixelProps.clear();
	PixelVec.clear();
	vecPortalObject.clear();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void BackDrop_PlayLevel::CreatePropInCurBackDrop(ERENDERDEPTH _RenderDepth, std::string_view _SpriteName, const float4& _Position, const float _Depth /*= 0.0f*/)
{
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	Renderer->SetSprite(_SpriteName);

	float4 Position = _Position;
	if (ERENDERDEPTH::Object == _RenderDepth)
	{
		Position.Z = ZSort(Position.Y + _Depth);
	}
	else
	{
		GlobalUtils::CalculateDepth(_RenderDepth);
	}

	Renderer->Transform.SetLocalPosition(Position);

	m_BackProp.push_back(Renderer);
}


// 배경의 디버깅 모드로 일반 텍스처와 픽셀 충돌 텍스처를 전환시켜줍니다.
void BackDrop_PlayLevel::EnableDebugMode(bool _Value)
{
	for (size_t i = 0; i < vecProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		Object->EnableDebugMode(_Value);
	}


	for (size_t i = 0; i < vecPixelProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecPixelProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		Object->EnableDebugMode(_Value);
	}

	EnableBackDropElemnetDebugMode(_Value);
}



// 특정 위치에 픽셀데이터가 있는지 반환해줍니다.
bool BackDrop_PlayLevel::IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor)
{
	if (false == vecPixelProps.empty())
	{
		for (size_t i = 0; i < vecPixelProps.size(); i++)
		{
			std::shared_ptr<Prop> Object = vecPixelProps[i];
			if (nullptr == Object)
			{
				MsgBoxAssert("생성되지 않은 액터를 참조하려고 했습니다.");
				return false;
			}

			if (false == Object->PixelRendererCheck)
			{
				continue;
			}

			if (_CheckColor == Object->GetColor(_Position))
			{
				return true;
			}
		}
	}



	for (size_t i = 0; i < PixelVec.size(); i++)
	{
		std::shared_ptr<Props> Object = PixelVec[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("생성되지 않은 액터를 참조하려고 했습니다.");
			return false;
		}

		if (false == Object->GetPixelCheck())
		{
			continue;
		}

		if (_CheckColor == Object->GetColor(_Position))
		{
			return true;
		}
	}

	return false;
}

// 깊이버퍼 계산
float BackDrop_PlayLevel::ZSort(const float _PositionY) const
{
	float4 BackGroundScale = GetBackGroundScale();
	if (float4::ZERO == BackGroundScale)
	{
		BackGroundScale = GlobalValue::GetWindowScale();
	}

	float Depth = (BackGroundScale.Y + _PositionY) ;
	return Depth;
}

// 아이템생성
void BackDrop_PlayLevel::CreateItem(std::string_view _ItemName, const float4& _Position, const int _Stack /*= 1*/, const float _FallYPosition /*= 0.0f*/)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	if (this != MainBackDrop)
	{
		MsgBoxAssert("현재 배경매니저가 아닙니다.");
		return;
	}

	std::shared_ptr<LootedItem> Item = CurLevel->CreateActor<LootedItem>(EUPDATEORDER::Objects);
	if (nullptr == Item)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	Item->BackManager = this;
	float4 Position = _Position;
	Position.Z = GlobalUtils::CalculateDepth(ERENDERDEPTH::RootedItem);
	Item->Transform.SetLocalPosition(Position);
	Item->SetStack(_Stack);
	if (0.0f != _FallYPosition)
	{
		Item->SetFallingTargetPosition(_FallYPosition);
	}
	Item->Init(_ItemName);
	LootedItemList.push_back(Item);
}



// 아이템 전용
std::list<std::shared_ptr<class LootedItem>>& BackDrop_PlayLevel::GetLootedItemList() 
{
	return LootedItemList;
}

std::list<std::shared_ptr<StaticEntity>>& BackDrop_PlayLevel::GetStaticEntityList()
{
	return StaticEntityList;
}

