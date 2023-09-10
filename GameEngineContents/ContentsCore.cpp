#include "PreCompile.h"
#include "ContentsCore.h"


#include "MainMenu.h"
#include "TitleTestLevel.h"
#include "PlayLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineSpriteRenderer::SetDefaultSampler("POINT");

	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TitleTestLevel>("TitleTestLevel");
	GameEngineCore::CreateLevel<MainMenu>("MainMenu");
	GameEngineCore::ChangeLevel("MainMenu");

	
	GlobalValue::SetWindowScale(GetStartWindowSize());
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}