#pragma once
#include "UI_Alert_Base.h"

// ���� :
class UI_Alert_Tutorial : public UI_Alert_Base
{
private:
	class UIAlertTutorialInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> ZoneFrame;
		std::shared_ptr<GameEngineUIRenderer> Black;
		std::shared_ptr<GameEngineUIRenderer> Font;

	public:
		static constexpr const float Fade_Change_Time = 1.0f;

		static constexpr const float FontScale = 23.0f;

	};


public:
	// constrcuter destructer
	UI_Alert_Tutorial();
	~UI_Alert_Tutorial();

	// delete Function
	UI_Alert_Tutorial(const UI_Alert_Tutorial& _Other) = delete;
	UI_Alert_Tutorial(UI_Alert_Tutorial&& _Other) noexcept = delete;
	UI_Alert_Tutorial& operator=(const UI_Alert_Tutorial& _Other) = delete;
	UI_Alert_Tutorial& operator=(UI_Alert_Tutorial&& _Other) noexcept = delete;

	static float AlertLevelEnter(GameEngineLevel* _Level, std::string_view _LevelName);

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void Init(std::string_view _LevelName);
	void RendererSetting(std::string_view _LevelName);

	void StartFadeIn(GameEngineState* _Parent) override;

	void UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent) override;
	void UpdateStay(float _DeltaTime, GameEngineState* _Parent) override;
	void UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent) override;


private:
	UIAlertTutorialInfo AlertInfo;

};
