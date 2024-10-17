#pragma once
#ifndef PKENGINE_PKCAMERA_H
#define PKENGINE_PKCAMERA_H

#include <Core/PKBase.h>

namespace pkengine
{
	class CCamera
	{
	private:
		FTransform transform;

	public:
		CCamera() :
			transform()
		{}

		inline FVector3 GetPosition() { return transform.GetPosition(); }
		inline void SetPosition(const FVector3& pos) { transform.SetPosition(pos); }

		inline FVector3 GetUpDir() { return transform.GetUp(); }
		inline void SetRotation(const FVector3& up) { transform.SetRotation(FVector3::Backward(), up); }

		inline float GetScale() { return transform.GetScale().GetX(); }
		inline void SetScale(const float scale) { transform.SetScale(FVector3(scale, scale, 1.0f)); }

		inline FTransform* GetTransform() { return &transform; }
	};
}

#endif // !PKENGINE_PKCAMERA_H