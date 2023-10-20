#pragma once
#include "ContentsLevel.h"

// ���� :
class LogoLevel : public ContentsLevel
{
public:
	// constrcuter destructer
	LogoLevel();
	~LogoLevel();

	// delete Function
	LogoLevel(const LogoLevel& _Other) = delete;
	LogoLevel(LogoLevel&& _Other) noexcept = delete;
	LogoLevel& operator=(const LogoLevel& _Other) = delete;
	LogoLevel& operator=(LogoLevel&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void LoadTexture();
	void LoadSprite();
	void LoadActor();

private:
	void UpdateFade(float _Delta);

private:
	void ReleaseSprite();
	void ReleaseTexture();


private:
	bool GlobalTextureLoadCheck = false;
	bool GlobalSpriteLoadCheck = false;

	float m_LogoTime = 0.0f;
	bool IsFadeOn = false;
};

