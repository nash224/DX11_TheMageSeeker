#pragma once

enum class EQUESTTYPE
{
	Find_Letter,
	Letter_Read,
	House_Dust,
	Clean_Dust,
	Craft_Potion,
	Repair_Extractor,
	Aurea_Find,
	Aurea_Cure,
	Crow_Meet,
	Dian_Catalogue,
	Dian_BadWeedPotion,
	Dian_Cracker_Recipe,
	Max,
};


// 설명 : Bool자료형의 이벤트 변수를 전역으로 제공합니다. 
class ContentsEvent
{
public:
	class QuestUnitBase
	{
	public:
		virtual bool CheckPrerequisiteQuest() 
		{
			return false;
		}

		bool isQuestComplete() const
		{
			return isQuestCompleted;
		}

		virtual void QuestComplete()
		{
			isQuestAccepted = true;
			isQuestCompleted = true;
		}


		bool IsQuestAccepted() const
		{
			return isQuestAccepted;
		}

		virtual void QuestAccept() 
		{
			isQuestAccepted = true;
		}

	private:
		virtual bool QuestClearPrerequisite() { return false; }
			

	public:
		// ContentsGUI에서 요구합니다. 
		// 절때 외부로 공개할 일은 없지만
		// friend 선언을 해도 안먹혀서 public으로 둡니다.
		bool isQuestCompleted = false;

	protected:
		bool isQuestAccepted = false;

	};

	class Letter_Read : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Aurea_Find : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class House_Dust : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Craft_Potion : public QuestUnitBase
	{
	public:
		void QuestAccept() override;
		void QuestComplete() override;
		bool CheckPrerequisiteQuest() override;

	};

	class Repair_Extractor : public QuestUnitBase
	{
	public:
		void QuestAccept() override;
		void QuestComplete() override;
		bool CheckPrerequisiteQuest() override;

	};

	class Aurea_Cure : public QuestUnitBase
	{
	public:
		void QuestAccept() override;
		void QuestComplete() override;
		bool CheckPrerequisiteQuest() override;

	};

	class Crow_Meet : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Catalogue : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_BadWeedPotion : public QuestUnitBase
	{
	public:
		void QuestAccept() override;
		void QuestComplete() override;
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Cracker : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;
		void QuestComplete() override;
	};


public:
	// constrcuter destructer
	ContentsEvent();
	~ContentsEvent();

	// delete Function
	ContentsEvent(const ContentsEvent& _Other) = delete;
	ContentsEvent(ContentsEvent&& _Other) noexcept = delete;
	ContentsEvent& operator=(const ContentsEvent& _Other) = delete;
	ContentsEvent& operator=(ContentsEvent&& _Other) noexcept = delete;

	static void Init();

	template<typename QuestType>
	static void CreateQuest(std::string_view _QuestName)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_QuestName);

		std::shared_ptr<QuestUnitBase> questUnit = std::make_shared<QuestType>();
		QuestData.insert(std::make_pair(UpperName, questUnit));
	}

	static const std::shared_ptr<ContentsEvent::QuestUnitBase> FindQuest(std::string_view _QuestName);


	static void Release();

protected:

public:
	static std::vector<bool> ToolData;
	static bool HasWitchBroom;
	static std::map<std::string, std::shared_ptr<QuestUnitBase>> QuestData;

};

