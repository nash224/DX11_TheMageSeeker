#include "PreCompile.h"
#include "ContentsActor.h"

#include "BackDrop_PlayLevel.h"
#include "CameraControler.h"
#include "ContentsMath.h"
#include "Ellie.h"

ContentsActor::ContentsActor() 
{
}

ContentsActor::~ContentsActor() 
{
}


// ��ġ ���� (���� ����)
void ContentsActor::ApplyMovement(float _Delta)
{
	ApplyOnlyMovement(_Delta);
	ApplyDepth();
}

void ContentsActor::ApplyOnlyMovement(float _Delta)
{
	const float4 Vector = m_MoveVector * _Delta; // Ȯ�ο�
	Transform.AddLocalPosition(Vector);
}

void ContentsActor::ApplyDepth()
{
	float4 MyPosition = Transform.GetLocalPosition();

	float BackYScale = 0.0f;
	const std::shared_ptr<BackDrop>& BackPtr = PlayLevel::GetCurLevel()->GetBackDropPtr();
	if (nullptr != BackPtr)
	{
		BackYScale = BackPtr->GetBackGroundScale().Y;
	}
	else
	{
		BackYScale = GlobalValue::GetWindowScale().Y;
	}

	float Depth = DepthFunction::CalculateObjectDepth(BackYScale, MyPosition.Y + PlusDepth);
	MyPosition.Z = Depth;

	Transform.SetLocalPosition(MyPosition);
}

bool ContentsActor::IsPlayerAround(float _Range) const
{
	const float4 PlayerPosition = PlayLevel::GetCurLevel()->GetPlayerPtr()->Transform.GetLocalPosition();

	return ContentMathFunction::IsAround2D(Transform.GetLocalPosition(), PlayerPosition, _Range);
}


void ContentsActor::StopSFX()
{
	if (true == SoundPlayer.IsPlaying())
	{
		SoundPlayer.Stop();
	}
}

void ContentsActor::UpdateSoundVolumeByDistance()
{
	if (true == SoundPlayer.IsPlaying())
	{
		const float Volume = GlobalValue::GetSFXVolume() * GetVolumeReductionByDistance();
		SoundPlayer.SetVolume(Volume);
	}
}

float ContentsActor::GetVolumeReductionByDistance() const
{
	const float MaxVolume = 150.0f;
	const float MinVolume = 370.0f;

	const float4 VectorToCamera = Transform.GetLocalPosition() - PlayLevel::GetCurLevel()->GetLevelCameraPtr()->GetCameraCurrentPostion();
	const float4 Size = DirectX::XMVector2Length(VectorToCamera.DirectXVector);
	const float Distance = Size.X;

	if (MaxVolume > Distance)
	{
		return 1.0f;
	}
	else if (MaxVolume < Distance && Distance < MinVolume)
	{
		float VolumeRatio = (MinVolume - Distance) / (MinVolume - MaxVolume);
		return VolumeRatio;
	}

	return 0.0f;
}