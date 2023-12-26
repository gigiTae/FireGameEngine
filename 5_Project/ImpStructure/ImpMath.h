#pragma once

/// <summary>
/// DirectXMath ���� Position, Rotation ���� �����ϱ� ����
/// �ʿ��� Ŭ���� -> Math ���̺귯���� ���� ������ ��
///
/// �ϴ� ������µ� �����غ��ϱ� �̷��� �� �ʿ䰡 �ִ����� �𸣰ڴ�.
/// �׳� Vector3�� ������ְ� xmfloat3�� ����ϸ� �ƴ��� �ƴұ�
/// ��� ������ ������ �ʿ䰡 �ֳ�???
/// </summary>
namespace ImpMath
{
	static constexpr float PI = { 3.14159265358979323846f };
	static constexpr float TwoPI = { 2.f * PI };
	static constexpr float HalfPI = { 1.57079632679f };
	static constexpr float InvPI = { 0.31830988618f };
	
	// ������ ���̾�
	constexpr float DegreeToRadian(float degree);
	
	// ������ ����
	constexpr float RadianToDegree(float radian);

	struct Matrix;

	struct Vector3
	{
		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f); // ������

		Vector3(const Vector3& rhs) = default; // ���� ������
		Vector3& operator=(const Vector3& rhs) = default; // ���� ���� ������

		// ���� ������ �����ε� + +=
		Vector3 operator+(const Vector3& rhs) const;
		void operator+=(const Vector3& rhs);

		// ���� ������ �����ε� - -=
		Vector3 operator-(const Vector3& rhs) const;
		void operator-=(const Vector3& rhs);

		// ��Į�� �� *, *= 
		Vector3 operator*(const float scalar) const;
		void operator*=(const float scalar);
		  
		// ��Į�� ������ /, /=
		Vector3 operator/(const float scalar) const;
		void operator/=(const float scalar);

		// Dot ���� == * ����
		float Dot(const Vector3& other) const;
		float operator*(const Vector3& rhs) const;

		// Cross ����
		Vector3 Cross(const Vector3& other) const;

		// �� ������ �����ε� ==, !=
		bool operator==(const Vector3& rhs) const;
		bool operator!=(const Vector3& rhs) const;

		// ������ ũ�� ���
		float Length() const;
		// �� ���� �� �� ��Ʈ ������ ���̱� ���� ���� ������ ����
		float LengthSquared() const;
		// Normalize ����
		Vector3 Normalize() const;

		// ���� ���հ� ���
		float CosTheta(const Vector3& other) const;

		// ���� ��� ����
		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;

		/// ��� ����
	public:
		float x, y, z;
	};

	// vector3 �� rhs�� ������ ��쵵 ������ ��

	struct Vector4
	{
		Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f); // ������
		Vector4(Vector3 vec3);
		Vector4(Vector3 vec3, float w);

		Vector4(const Vector4& rhs) = default; // ���� ������
		Vector4& operator=(const Vector4& rhs) = default; // ���� ���� ������

		// ���� ������ �����ε� + +=
		Vector4 operator+(const Vector4& rhs) const;
		void operator+=(const Vector4& rhs);

		// ���� ������ �����ε� - -=
		Vector4 operator-(const Vector4& rhs) const;
		void operator-=(const Vector4& rhs);

		// ��Į�� �� *, *=
		Vector4 operator*(const float scalar) const;
		void operator*=(const float scalar);

		// ��Į�� ������ /, /=
		Vector4 operator/(const float scalar) const;
		void operator/=(const float scalar);

		// Dot ���� == * ����
		float Dot(const Vector4& other) const;
		float operator*(const Vector4& rhs) const;

		// �� ������ �����ε� ==, !=
		bool operator==(const Vector4& rhs) const;
		bool operator!=(const Vector4& rhs) const;

		// ������ ũ�� ���
		float Length() const;
		// �� ���� �� �� ��Ʈ ������ ���̱� ���� ���� ������ ����
		float LengthSquared() const;
		// Normalize ����
		Vector4 Normalize() const;

		// ���� ���հ� ���
		float CosTheta(const Vector4& other) const;

		/// ��� ����
	public:
		float x, y, z, w;
	};

	struct Matrix
	{
		Matrix();
		Matrix(const float* array);
		Matrix(const Matrix& rhs);

		static Matrix Identity();

		Matrix& operator=(const Matrix& rhs); // ���� ���� ������

		Matrix operator*(const Matrix& rhs) const;
		void operator*=(const Matrix& rhs);

		// ���Ϸ� �� 3���� ȸ�� ����� ����� �Լ�
		static Matrix MakeRotationMatrixRollPitchYaw(Vector3 rotation);
		
		// �̵� ����� ����� �Լ�
		static Matrix MakeTranslationMatrix(Vector3 postion);

		// ������ ����� ����� �Լ�
		static Matrix MakeScaleMatrix(Vector3 scale);

		// ���� ��� ����
		static const Vector4 UnitX;
		static const Vector4 UnitY;
		static const Vector4 UnitZ;
		static const Vector4 UnitW;
		static const Vector4 One;
		static const Vector4 Zero;

		/// ��� ����
	public:
		union
		{
			float m[4][4];
			Vector4 v[4];
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
		};
	};

	/// <summary>
	/// ȸ���� ��𼭺��� ������
	/// ��� �����ؾ� �ϴ��� �𸣰ڴ�
	/// </summary>
	struct Quaternion
	{
		Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
		Quaternion(Vector3 vec4); // ���Ϸ� ������ Quaternion �����
		Quaternion(Vector4 vec4);

		static void QuaternionMultiply(Quaternion q1, Quaternion q2);

		/// ��� ����
	public:
		Vector4 vec4;
	};
}