#include "PreCompile.h"
#include "UI_Hub_Calender.h"

#include "PlayLevel.h"
#include "TimeManager.h"


UI_Hub_Calender::UI_Hub_Calender() 
{
	PlayLevel::s_TimeManager;
}

UI_Hub_Calender::~UI_Hub_Calender() 
{
}


void UI_Hub_Calender::Start()
{

}

void UI_Hub_Calender::Update(float _Delta)
{
	UpateCalender();
}

void UI_Hub_Calender::Release()
{
	Calender.UnderLine = nullptr;
	Calender.Symbol = nullptr;
	Calender.Font_Day = nullptr;
	Calender.Font_Week = nullptr;
	Calender.Font_Time = nullptr;
	Calender.Font_Meridiem = nullptr;
}

void UI_Hub_Calender::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void UI_Hub_Calender::LevelEnd(class GameEngineLevel* _NextLevel)
{
	
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_Hub_Calender::Init()
{
	RendererSetting();

}

void UI_Hub_Calender::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Month_Symbol.png"))
	{
		GameEngineSprite::CreateCut("Month_Symbol.png", 4, 1);
	}


	static constexpr const int RendererOrder = 0;
	const float CalenderDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);


	Calender.UnderLine = CreateComponent<GameEngineUIRenderer>(RendererOrder);
	Calender.UnderLine->Transform.SetLocalPosition(float4(0.0f , 0.0f, CalenderDepth));
	Calender.UnderLine->SetSprite("Calender_UnderLine.png");
	Calender.UnderLine->GetImageTransform().SetLocalScale(float4(140.0f, 20.0f));

	Calender.Symbol = CreateComponent<GameEngineUIRenderer>(RendererOrder);
	Calender.Symbol->SetSprite("Month_Symbol.png");

	Calender.Font_Day = CreateComponent<GameEngineUIRenderer>(RendererOrder);
	Calender.Font_Day->GetColorData().MulColor = float4::ONE;

	Calender.Font_Week = CreateComponent<GameEngineUIRenderer>(RendererOrder);
	Calender.Font_Week->GetColorData().MulColor = float4::ONE;

	Calender.Font_Time = CreateComponent<GameEngineUIRenderer>(RendererOrder);
	Calender.Font_Time->GetColorData().MulColor = float4::ONE;

	Calender.Font_Meridiem = CreateComponent<GameEngineUIRenderer>(RendererOrder);
	Calender.Font_Meridiem->GetColorData().MulColor = float4::ONE;
}

void UI_Hub_Calender::UpateCalender()
{
	Calender.UpdateAll();
}

void UI_Hub_Calender::CalenderInfo::UpdateAll()
{
	if (nullptr != PlayLevel::s_TimeManager)
	{
		UpdateRenderDayAndWeek();
		UpdateRenderTime();
		UpdateSymbol();
	}
}

void UI_Hub_Calender::CalenderInfo::UpdateRenderDayAndWeek()
{
	const int CurDayCount = PlayLevel::s_TimeManager->GetDayCount();
	const int WeekNumber = CurDayCount % 7;

	bool isWeekChange = (WeekNumber != RenderDayCount % 7);
	if (isWeekChange)
	{
		DayReset();

		SetCalenderFont(Font_Day, std::to_string(CurDayCount), Day_Font_Scale);

		RenderDayCount = CurDayCount;

		switch (WeekNumber)
		{
		case 0:
			WeekString = "Sun";
			break;
		case 1:
			WeekString = "Mon";
			break;
		case 2:
			WeekString = "Tue";
			break;
		case 3:
			WeekString = "Wed";
			break;
		case 4:
			WeekString = "Thu";
			break;
		case 5:
			WeekString = "Fri";
			break;
		case 6:
			WeekString = "Sat";
			break;
		default:
			break;
		}

		SetCalenderFont(Font_Week, WeekString, Day_Font_Scale);
	}
}

void UI_Hub_Calender::CalenderInfo::UpdateRenderTime()
{
	 const int CurHour = PlayLevel::s_TimeManager->GetHour();
	 const int CurTenMinute = PlayLevel::s_TimeManager->GetMinute() / 10 * 10;
	 int TimeNumber = CurHour + CurTenMinute;

	 bool isTimeChange = (TimeNumber != RenderTime);
	 if (isTimeChange)
	 {
		 RenderTime = TimeNumber;

		 std::string TimeString = std::to_string(CurHour) + ':' + std::to_string(CurTenMinute);
		 SetCalenderFont(Font_Time, TimeString, Time_Font_Scale);
	 }

	 bool ChangePM = (true == RenderAnteMeridiem && TimeNumber >= 12);
	 if (ChangePM)
	 {
		 UpdateMeridiem("PM");
	 }

	 bool ChangeAM = (false == RenderAnteMeridiem && TimeNumber < 12);
	 if (ChangeAM)
	 {
		 UpdateMeridiem("AM");
	 }
}

void UI_Hub_Calender::CalenderInfo::UpdateSymbol()
{
	if (nullptr != PlayLevel::s_TimeManager)
	{
		EDAYSTATE DayState = PlayLevel::s_TimeManager->GetDayState();
		bool isSymbolChange = (DayState != RenderDayState);
		if (isSymbolChange)
		{
			static constexpr const int Day_Symbol_Index = 0;
			static constexpr const int Night_Symbol_Index = 1;

			RenderDayState = DayState;

			switch (RenderDayState)
			{
			case EDAYSTATE::Day:
				Symbol->ChangeCurSprite(Day_Symbol_Index);
				break;
			case EDAYSTATE::Night:
				Symbol->ChangeCurSprite(Night_Symbol_Index);
				break;
			case EDAYSTATE::None:
			{
				MsgBoxAssert("값이 잘못되었습니다.");
				return;
			}
				break;
			default:
				break;
			}
		}
	}
}

void UI_Hub_Calender::CalenderInfo::UpdateMeridiem(std::string_view _Text)
{
	SetCalenderFont(Font_Meridiem, _Text, Meridiem_Font_Scale);
}


void UI_Hub_Calender::CalenderInfo::DayReset()
{
	RenderTime = 0;
	RenderDayState = EDAYSTATE::None;
	RenderAnteMeridiem = true;
	UpdateMeridiem("AM");
}

void UI_Hub_Calender::CalenderInfo::SetCalenderFont(
	const std::shared_ptr<GameEngineUIRenderer>& _FontRenderer, 
	std::string_view _Text, 
	float _Scale)
{
	_FontRenderer->SetText(FontStyle.data(), _Text.data(), _Scale, FontColorWhite);
}

