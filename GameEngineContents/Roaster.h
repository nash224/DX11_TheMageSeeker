#pragma once
#include "StaticEntity.h"


enum class EROASTERSTATE
{
	None,
	Broken,
	Idle,
	Roasting,
};


// ���� :
class Roaster : public StaticEntity
{
public:
	// constrcuter destructer
	Roaster();
	~Roaster();

	// delete Function
	Roaster(const Roaster& _Other) = delete;
	Roaster(Roaster&& _Other) noexcept = delete;
	Roaster& operator=(const Roaster& _Other) = delete;
	Roaster& operator=(Roaster&& _Other) noexcept = delete;



protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void InitRoaster();

	void CreateRendererAndAnimation();
	void CreateInteractiveCollision();


private:
	void UpdateState(float _Delta);
	void ChangeState(EROASTERSTATE _State);
	void ChangeRoasterCompositionAnimation(std::string_view _StateName);


	void StartBroken();
	void UpdateBroken(float _Delta);

	void StartIdle();
	void UpdateIdle(float _Delta);

	void StartRoasting();
	void UpdateRoasting(float _Delta);

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Shadow;
	std::shared_ptr<GameEngineSpriteRenderer> m_Roaster;
	std::shared_ptr<GameEngineSpriteRenderer> m_RoasterFXSteam;

private:
	EROASTERSTATE m_State = EROASTERSTATE::None;

};
