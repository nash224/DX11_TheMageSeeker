#pragma once

enum class EQUESTTYPE
{
	Crow_Meet,
	Dian_Quest_1,
	Dian_Quest_2,
	Dian_Quest_3,
	Dian_Cracker,
	Aurea_Find,
	Aurea_UnCurse,
	Aurea_Curse,
	Aurea_Quest_3,
	Aurea_Quest_4,
	Max,
};

enum class EEVENTTYPE
{
	Aurea_UnCurse,
	Aurea_Curse,
	Crow_Meet,
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
			isQuestCompleted = true;
		}

	public:
		// ContentsGUI에서 요구합니다. 
		// 절때 외부로 공개할 일은 없지만
		// friend 선언을 해도 안먹혀서 public으로 둡니다.
		bool isQuestCompleted = false;

	};

	class Crow_Meet : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Quest_1 : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Quest_2 : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Quest_3 : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Cracker : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;
		void QuestComplete() override;
	};



	class Aurea_Find : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Aurea_UnCurse : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Aurea_Curse : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

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
	static std::vector<bool> EventData;
	static std::map<std::string, std::shared_ptr<QuestUnitBase>> QuestData;

};

