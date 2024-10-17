#ifndef PKENGINE_PKMATH_H
#define PKENGINE_PKMATH_H

#define GLM_FORCE_XYZW_ONLY // Most geometric functions breaking without this (maybe unions not working? Didnt check)
#define GLM_FORCE_NO_CTOR_INIT // We Init our Math structs' glm members anyway
#define GLM_FORCE_INLINE

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>

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
		static inline FVector3 One() { return FVector3(1.0f, 1.0f, 1.0f); }
		static inline FVector3 Up() { return FVector3(0.0f, 1.0f, 0.0f); }
		static inline FVector3 Down() { return FVector3(0.0f, -1.0f, 0.0f); }
		static inline FVector3 Left() { return FVector3(-1.0f, 0.0f, 0.0f); }
		static inline FVector3 Right() { return FVector3(1.0f, 0.0f, 0.0f); }
		static inline FVector3 Forward() { return FVector3(0.0f, 0.0f, 1.0f); }
		static inline FVector3 Backward() { return FVector3(0.0f, 0.0f, -1.0f); }

		inline float GetX() const { return glmVector.x; }
		inline float GetY() const { return glmVector.y; }
		inline float GetZ() const { return glmVector.z; }

		inline void SetX(float v) { glmVector.x = v; }
		inline void SetY(float v) { glmVector.y = v; }
		inline void SetZ(float v) { glmVector.z = v; }

		#pragma region Constructors

		FVector3(float inX, float inY, float inZ) : glmVector(inX, inY, inZ) {}

		FVector3(float inX, float inY) : glmVector(inX, inY, 0) {}

		FVector3() : glmVector(0.0f, 0.0f, 0.0f) {}

		FVector3(const FVector3& Other) : glmVector(Other.glmVector) {}

		FVector3(FVector3&& Other) noexcept : glmVector(Other.glmVector) {}

		#pragma endregion

		#pragma region Operators

		inline FVector3& operator=(const FVector3& Other)
		{
			glmVector = Other.glmVector;
			return *this;
		}

		inline FVector3& operator=(FVector3&& Other) noexcept
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

		inline FVector3 Cross(const FVector3& other)
		{
			return FVector3(glm::cross(glmVector, other.glmVector));
		}

		inline FVector3 Project(const FVector3& axis)
		{
			return axis * Dot(axis);
		}

		inline FVector3 Reflect(const FVector3& axis)
		{
			return *this - (Project(axis) * 2.0f);
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

		FTransform& operator=(const glm::mat4& OtherGlmMatrix) noexcept
		{
			glmMatrix = OtherGlmMatrix;

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

		FTransform(): FTransform(glm::mat4(1.0f)) {}

		FTransform& operator=(const FTransform& Other)
		{
			glmMatrix = glm::mat4();
			bTransformDirty = Other.bTransformDirty;
			if (Other.bTransformDirty)
			{
				glmPosition = Other.glmPosition;
				glmRotation = Other.glmRotation;
				glmScale = Other.glmScale;
			}
			else
			{
				operator=(Other.glmMatrix);
			}

			return *this;
		}

		FTransform& operator=(FTransform&& Other) noexcept
		{
			glmMatrix = glm::mat4();
			bTransformDirty = Other.bTransformDirty;
			if (Other.bTransformDirty)
			{
				glmPosition = Other.glmPosition;
				glmRotation = Other.glmRotation;
				glmScale = Other.glmScale;
			}
			else
			{
				operator=(Other.glmMatrix);
			}

			return *this;
		}

		FTransform(const FTransform& Other)
		{
			glmMatrix = glm::mat4();
			bTransformDirty = Other.bTransformDirty;
			if (Other.bTransformDirty)
			{
				glmPosition = Other.glmPosition;
				glmRotation = Other.glmRotation;
				glmScale = Other.glmScale;
			}
			else
			{
				operator=(Other.glmMatrix);
			}
		}

		FTransform(FTransform&& Other) noexcept
		{
			glmMatrix = glm::mat4();
			bTransformDirty = Other.bTransformDirty;
			if (Other.bTransformDirty)
			{
				glmPosition = Other.glmPosition;
				glmRotation = Other.glmRotation;
				glmScale = Other.glmScale;
			}
			else
			{
				operator=(Other.glmMatrix);
			}
		}

		inline void SetPosition(const FVector3& InPosition)
		{
			glmPosition = InPosition.glmVector;
			bTransformDirty = true;
		}

		inline void SetScale(const FVector3& InScale)
		{
			glmScale = InScale.glmVector;
			bTransformDirty = true;
		}

		inline void SetRotation(const FVector3& up)
		{
			glmRotation = glm::quatLookAt(glm::vec3(0.0f, 0.0f, 1.0f), up.glmVector);
			bTransformDirty = true;
		}

		inline void SetRotation(const FVector3& forward, const FVector3& up)
		{
			glmRotation = glm::quatLookAt(forward.glmVector, up.glmVector);
			bTransformDirty = true;
		}

		inline void Rotate(float rad, const FVector3& Axis)
		{
			glmRotation = glm::rotate(glmRotation, rad, Axis.glmVector);
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

		inline FVector3 GetUp() const
		{
			return FVector3(glm::mat4(glmRotation) * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
		}

		inline FVector3 GetRight() const
		{
			return FVector3(glm::mat4(glmRotation) * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
		}

		inline FTransform GetInverse()
		{
			CheckedRecalculate();
			return FTransform(glm::inverse(glmMatrix));
		}

		inline const glm::mat4& GetGLM()
		{
			CheckedRecalculate();
			return glmMatrix;
		}
	};

	struct FEdge
	{
		FVector3 a;
		FVector3 b;

		FEdge() : a(), b() {}
	};

	struct FCollision
	{
		class CCollider* collider;
		FVector3 point;
		FVector3 normal;

		FCollision(class CCollider* col, const FVector3& p, const FVector3& n)
			: collider(col), point(p), normal(n)
		{}

		FCollision()
			: collider(nullptr), point(), normal(1.0f, 0.0f)
		{}
	};

	namespace pkfloat
	{
		inline bool IsClose(float a, float b, float threshold = 0.000001f)
		{
			return abs(a - b) < threshold;
		}
	}
}

#endif // !PKENGINE_PKMATH_H
