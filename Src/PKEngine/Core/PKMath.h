#ifndef PKENGINE_PKMATH_H
#define PKENGINE_PKMATH_H

#define GLM_FORCE_XYZW_ONLY // Most geometric functions breaking without this (maybe unions not working? Didnt check)
#define GLM_FORCE_NO_CTOR_INIT // We Init our Math structs' glm members anyway
#define GLM_FORCE_INLINE

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace pkengine
{
	struct FVector3
	{
		friend struct FTransform;

	private:
		glm::vec3 glmVector;
		FVector3(const glm::vec3& InGlmVector) : glmVector(InGlmVector) {}

	public:
		static inline FVector3 Zero() { return FVector3(); }
		static inline FVector3 Up() { return FVector3(0.0f, 1.0f, 0.0f); }
		static inline FVector3 Down() { return FVector3(0.0f, -1.0f, 0.0f); }
		static inline FVector3 Left() { return FVector3(-1.0f, 0.0f, 0.0f); }
		static inline FVector3 Right() { return FVector3(1.0f, 0.0f, 0.0f); }
		static inline FVector3 Forward() { return FVector3(0.0f, 0.0f, 1.0f); }
		static inline FVector3 Backward() { return FVector3(0.0f, 0.0f, -1.0f); }

		inline float GetX() { return glmVector.x; }
		inline float GetY() { return glmVector.y; }
		inline float GetZ() { return glmVector.z; }

		#pragma region Constructors

		FVector3(float inX, float inY, float inZ) : glmVector(inX, inY, inZ) {}

		FVector3(float inX, float inY) : glmVector(inX, inY, 0) {}

		FVector3() : glmVector(0.0f, 0.0f, 0.0f) {}

		FVector3(const FVector3& Other) : glmVector(Other.glmVector) {}

		#pragma endregion

		#pragma region Operators

		inline FVector3& operator=(const FVector3& Other)
		{
			glmVector = Other.glmVector;
			return *this;
		}

		inline FVector3& operator+=(const FVector3& Other)
		{
			glmVector += Other.glmVector;
			return *this;
		}

		inline FVector3& operator-=(const FVector3& Other)
		{
			glmVector -= Other.glmVector;
			return *this;
		}

		// Component wise multiply
		inline FVector3& operator*=(const FVector3& Other)
		{
			glmVector *= Other.glmVector;
			return *this;
		}

		// Component wise divide
		inline FVector3& operator/=(const FVector3& Other)
		{
			glmVector /= Other.glmVector;
			return *this;
		}

		inline FVector3& operator*=(const float Scale)
		{
			glmVector *= Scale;
			return *this;
		}

		inline FVector3& operator/=(const float Scale)
		{
			glmVector *= (1.0f / Scale);
			return *this;
		}

		inline FVector3 operator-() const
		{
			return FVector3(-glmVector);
		}

		inline FVector3 operator+(const FVector3& Other) const
		{
			return FVector3(glmVector + Other.glmVector);
		}

		inline FVector3 operator-(const FVector3& Other) const
		{
			return FVector3(glmVector - Other.glmVector);
		}

		inline FVector3 operator*(const FVector3& Other) const
		{
			return FVector3(glmVector * Other.glmVector);
		}

		inline FVector3 operator/(const FVector3& Other) const
		{
			return FVector3(glmVector / Other.glmVector);
		}

		inline FVector3 operator*(const float Scale) const
		{
			return FVector3(glmVector * Scale);
		}

		inline FVector3 operator/(const float Scale) const
		{
			return FVector3(glmVector * (1 / Scale));
		}

		inline bool operator==(const FVector3& Other) const
		{
			return glmVector == Other.glmVector;
		}

		#pragma endregion

		#pragma region Geometic Functions

		inline float Dot(const FVector3& Other) const
		{
			return glm::dot(glmVector, Other.glmVector);
		}

		inline float MagnitudeSquared() const
		{
			return glm::dot(glmVector, glmVector);
		}

		inline float Magnitude() const
		{
			return glm::length(glmVector);
		}

		inline void Normalize()
		{
			glm::normalize(glmVector);
		}

		#pragma endregion

		inline std::string ToString() const
		{
			std::string ToRet =
				"x=" + std::to_string(glmVector.x) +
				", y=" + std::to_string(glmVector.y) +
				", z=" + std::to_string(glmVector.z);

			return ToRet;
		}
	};

	inline FVector3 operator*(float Scale, const FVector3& InVector)
	{
		return InVector * Scale;
	}

	struct FTransform
	{
	private:
		glm::mat4 glmMatrix;
		glm::vec3 glmPosition;
		glm::vec3 glmScale;
		glm::quat glmRotation;
		bool bTransformDirty;

		void CheckedRecalculate()
		{
			if (bTransformDirty)
			{
				Recalculate();
			}
		}

		void Recalculate()
		{
			glmMatrix = glm::translate(glm::mat4(1.0f), glmPosition);
			glmMatrix *= glm::mat4(glmRotation);
			glmMatrix = glm::scale(glmMatrix, glmScale);

			bTransformDirty = false;
		}

		FTransform& operator=(const glm::mat4& OtherGlmMatrix)
		{
			glmMatrix = OtherGlmMatrix;
			glmPosition = glmMatrix * glm::vec4(0.0f);

			glm::vec3 perspective;
			glm::vec4 skew;
			glm::decompose(glmMatrix, glmScale, glmRotation, glmPosition, perspective, skew);

			bTransformDirty = false;
			return *this;
		}

		FTransform(const glm::mat4& OtherGlmMatrix)
		{
			operator=(OtherGlmMatrix);
		}

	public:
		
		FTransform() : FTransform(glm::mat4(1.0f)) {}

		FTransform& operator=(const FTransform& Other)
		{
			glmPosition = Other.glmPosition;
			glmRotation = Other.glmRotation;
			glmScale = Other.glmScale;
			Recalculate();
			return *this;
		}

		FTransform(const FTransform& Other)
		{
			operator=(Other);
		}

		inline void SetPosition(FVector3 InPosition)
		{
			glmPosition = InPosition.glmVector;
			bTransformDirty = true;
		}

		inline void SetScale(FVector3 InScale)
		{
			glmScale = InScale.glmVector;
			bTransformDirty = true;
		}

		inline void Rotate(float Degrees, FVector3 Axis)
		{
			glmRotation = glm::rotate(glmRotation, Degrees, Axis.glmVector);
			bTransformDirty = true;
		}

		inline FVector3 GetPosition()
		{
			return FVector3(glmPosition);
		}

		inline FVector3 GetScale()
		{
			return FVector3(glmScale);
		}

		inline FVector3 operator*(const FVector3& Vector)
		{
			CheckedRecalculate();

			return FVector3(glmMatrix * glm::vec4(Vector.glmVector, 1.0f));
		}

		inline FVector3 GetUp()
		{
			return FVector3(glm::mat4(glmRotation) * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
		}
	};
}

#endif // !PKENGINE_PKMATH_H
