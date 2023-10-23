#pragma once


enum class EPROCESSUNITSTATE
{
	Unknown,
	NotPossible,
	Possible,
	None,
};



// ���� :
class UI_ProcessListUnit : public GameEngineActor
{
	friend class UI_ProcessList;
public:
	// constrcuter destructer
	UI_ProcessListUnit();
	~UI_ProcessListUnit();

	// delete Function
	UI_ProcessListUnit(const UI_ProcessListUnit& _Other) = delete;
	UI_ProcessListUnit(UI_ProcessListUnit&& _Other) noexcept = delete;
	UI_ProcessListUnit& operator=(const UI_ProcessListUnit& _Other) = delete;
	UI_ProcessListUnit& operator=(UI_ProcessListUnit&& _Other) noexcept = delete;

	void Init(std::string_view _ProcessName);

	void RenewRenderer();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineUIRenderer> Panel = nullptr;
	std::shared_ptr<GameEngineUIRenderer> ItemSlot = nullptr;
	std::shared_ptr<GameEngineUIRenderer> ItemImg = nullptr;
	std::shared_ptr<GameEngineUIRenderer> ItemMaskImg = nullptr;
	std::string ItemName = "";
	std::string ItemKRName = "";
	std::string SrcName = "";

	EPROCESSUNITSTATE State = EPROCESSUNITSTATE::None;

	int SrcCount = 0;
	int NeedCount = 0;


};
