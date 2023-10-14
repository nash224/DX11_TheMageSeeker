#pragma once

enum class EGAMEMODE
{
	None,
	Play,
	Editor,
};


// ���� :
class CameraControler;
class ContentsLevel : public GameEngineLevel
{
public:
	std::shared_ptr<CameraControler> m_LevelCameraControler = nullptr;

public:
	// constrcuter destructer
	ContentsLevel();
	~ContentsLevel();

	// delete Function
	ContentsLevel(const ContentsLevel& _Other) = delete;
	ContentsLevel(ContentsLevel&& _Other) noexcept = delete;
	ContentsLevel& operator=(const ContentsLevel& _Other) = delete;
	ContentsLevel& operator=(ContentsLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
	

protected:
	EGAMEMODE Mode;
	
};

