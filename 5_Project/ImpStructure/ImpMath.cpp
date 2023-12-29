#include "pch.h"
#include "ImpMath.h"

#define WIN32_LEAN_AND_MEAN

using namespace ImpMath;
#pragma region Util

constexpr float DegreeToRadian(float degree)
{
	return degree * PI / 180.f;
}

constexpr float RadianToDegree(float radian)
{
	return radian * 180.f * InvPI;
}

#pragma endregion Util

#pragma region Vector2

Vector2::Vector2(float x /*= 0.0f*/, float y /*= 0.0f*/)
	:x(x), y(y)
{
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

void Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y - rhs.y);
}

void Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

ImpMath::Vector2 Vector2::operator*(const float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

void Vector2::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
}

ImpMath::Vector2 Vector2::operator/(const float scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

void Vector2::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
}

bool Vector2::operator==(const Vector2& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

bool Vector2::operator!=(const Vector2& rhs) const
{
	return !operator==(rhs);
}

float Vector2::Length() const
{
	return sqrt(x * x + y * y);
}

float Vector2::LengthSquared() const
{
	return x * x + y * y;
}

ImpMath::Vector2 Vector2::Normalize() const
{
	return Vector2(x / Length(), y / Length());
}

const ImpMath::Vector2 ImpMath::Vector2::Zero = {0, 0};

#pragma endregion Vector2

#pragma region Vector3
Vector3::Vector3(float x /*= 0.0f*/, float y /*= 0.0f*/, float z /*= 0.0f*/)
	:x(x), y(y), z(z)
{
}

ImpMath::Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

void Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

ImpMath::Vector3 Vector3::operator-(const Vector3& rhs) const
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

void Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
}

ImpMath::Vector3 Vector3::operator*(const float scalar) const
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}

void Vector3::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

ImpMath::Vector3 Vector3::operator/(const float scalar) const
{
	return Vector3(x / scalar, y / scalar, z / scalar);
}

void Vector3::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
}

float Vector3::Dot(const Vector3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float Vector3::operator*(const Vector3& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

ImpMath::Vector3 Vector3::Cross(const Vector3& other) const
{
	return Vector3(y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

bool Vector3::operator==(const Vector3& rhs) const
{
	return (x == rhs.x && y == rhs.y) && z == rhs.z;
}

bool Vector3::operator!=(const Vector3& rhs) const
{
	return !operator==(rhs);
}

float Vector3::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::LengthSquared() const
{
	return x * x + y * y + z * z;
}

ImpMath::Vector3 Vector3::Normalize() const
{
	return Vector3(x / Length(), y / Length(), z / Length());
}

float Vector3::CosTheta(const Vector3& other) const
{
	float cos = Dot(other);
	cos /= Length() * other.Length();

	return cos;
}

const ImpMath::Vector3 ImpMath::Vector3::Zero(0.f, 0.f, 0.f);
const ImpMath::Vector3 ImpMath::Vector3::One(1.f, 1.f, 1.f);
const ImpMath::Vector3 ImpMath::Vector3::UnitX(1.f, 0.f, 0.f);
const ImpMath::Vector3 ImpMath::Vector3::UnitY(0.f, 1.f, 0.f);
const ImpMath::Vector3 ImpMath::Vector3::UnitZ(0.f, 0.f, 1.f);


#pragma endregion Vector3

#pragma region Vector4
Vector4::Vector4(float x /*= 0.0f*/, float y /*= 0.0f*/, float z /*= 0.0f*/, float w /*= 0.0f*/)
	:x(x), y(y), z(z), w(w)
{
}

Vector4::Vector4(Vector3 vec3)
	:x(vec3.x), y(vec3.y), z(vec3.z), w(0)
{
}

Vector4::Vector4(Vector3 vec3, float w)
	:x(vec3.x), y(vec3.y), z(vec3.z), w(w)
{
}

ImpMath::Vector4 Vector4::operator+(const Vector4& rhs) const
{
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

void Vector4::operator+=(const Vector4& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
}

ImpMath::Vector4 Vector4::operator-(const Vector4& rhs) const
{
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

void Vector4::operator-=(const Vector4& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
}

ImpMath::Vector4 Vector4::operator*(const float scalar) const
{
	return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

void Vector4::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
}

ImpMath::Vector4 Vector4::operator/(const float scalar) const
{
	return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

void Vector4::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
}

float Vector4::Dot(const Vector4& other) const
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

float Vector4::operator*(const Vector4& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

bool Vector4::operator==(const Vector4& rhs) const
{
	return (x == rhs.x && y == rhs.y) && (z == rhs.z && w == rhs.w);
}

bool Vector4::operator!=(const Vector4& rhs) const
{
	return !operator==(rhs);
}

float Vector4::Length() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::LengthSquared() const
{
	return x * x + y * y + z * z + w * w;
}

ImpMath::Vector4 Vector4::Normalize() const
{
	return Vector4(x / Length(), y / Length(), z / Length(), w / Length());
}

float Vector4::CosTheta(const Vector4& other) const
{
	float cos = Dot(other);
	cos /= Length() * other.Length();

	return cos;
}
#pragma endregion Vector4

#pragma region Quaternion
void Quaternion::QuaternionMultiply(Quaternion q1, Quaternion q2)
{
	OutputDebugString(L"Quaternion Multiply는 아직 미구현\n");
}
#pragma endregion Quaternion

#pragma region Matrix
// Todo:
// _11 분기문 말고 따로 값을 넣어주는 게 속도가 더 빠를 것으로 예상
Matrix::Matrix()
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (i == j)
			{
				m[i][j] = 1;
				continue;
			}
			m[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix& rhs)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m[i][j] = rhs.m[i][j];
		}
	}
}

Matrix::Matrix(const float* array)
{
	m[0][0] = array[0];
	m[0][1] = array[1];
	m[0][2] = array[2];
	m[0][3] = array[3];

	m[1][0] = array[4];
	m[1][1] = array[5];
	m[1][2] = array[6];
	m[1][3] = array[7];

	m[2][0] = array[8];
	m[2][1] = array[9];
	m[2][2] = array[10];
	m[2][3] = array[11];

	m[3][0] = array[12];
	m[3][1] = array[13];
	m[3][2] = array[14];
	m[3][3] = array[15];
}

Matrix Matrix::Identity()
{
	return Matrix();
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
	// 	DirectX::XMFLOAT4X4 lhs4x4(&_11);
	// 	DirectX::XMFLOAT4X4 rhs4x4(&rhs._11);

	DirectX::XMMATRIX lhsM(&_11);
	DirectX::XMMATRIX rhsM(&rhs._11);

	DirectX::XMFLOAT4X4 result;
	XMStoreFloat4x4(&result, lhsM * rhsM);

	return Matrix(&result._11);
}

void Matrix::operator*=(const Matrix& rhs)
{
	DirectX::XMMATRIX lhsM(&_11);
	DirectX::XMMATRIX rhsM(&rhs._11);

	DirectX::XMFLOAT4X4 result;
	XMStoreFloat4x4(&result, lhsM * rhsM);

	*this = Matrix(&result._11);
}

ImpMath::Matrix& Matrix::operator=(const Matrix& rhs)
{
	m[0][0] = rhs.m[0][0];
	m[0][1] = rhs.m[0][1];
	m[0][2] = rhs.m[0][2];
	m[0][3] = rhs.m[0][3];

	m[1][0] = rhs.m[1][0];
	m[1][1] = rhs.m[1][1];
	m[1][2] = rhs.m[1][2];
	m[1][3] = rhs.m[1][3];

	m[2][0] = rhs.m[2][0];
	m[2][1] = rhs.m[2][1];
	m[2][2] = rhs.m[2][2];
	m[2][3] = rhs.m[2][3];

	m[3][0] = rhs.m[3][0];
	m[3][1] = rhs.m[3][1];
	m[3][2] = rhs.m[3][2];
	m[3][3] = rhs.m[3][3];

	return *this;
}

Matrix Matrix::MakeRotationMatrixRollPitchYaw(Vector3 rotation)
{
	float pitch = DirectX::XMConvertToRadians(rotation.x);
	float yaw = DirectX::XMConvertToRadians(rotation.y);
	float roll = DirectX::XMConvertToRadians(rotation.z);

	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	DirectX::XMFLOAT4X4 result;
	XMStoreFloat4x4(&result, rotationMatrix);

	return Matrix(&result._11);
}

ImpMath::Matrix Matrix::MakeTranslationMatrix(Vector3 postion)
{
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(postion.x, postion.y, postion.z);

	DirectX::XMFLOAT4X4 result;

	XMStoreFloat4x4(&result, translation);

	return Matrix(&result._11);
}

ImpMath::Matrix Matrix::MakeScaleMatrix(Vector3 scale)
{
	DirectX::XMMATRIX scaleMatrix = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	DirectX::XMFLOAT4X4 result;

	XMStoreFloat4x4(&result, scaleMatrix);

	return Matrix(&result._11);
}

const ImpMath::Vector4 ImpMath::Matrix::UnitX(1.f, 0.f, 0.f, 0.f);
const ImpMath::Vector4 ImpMath::Matrix::UnitY(0.f, 1.f, 0.f, 0.f);
const ImpMath::Vector4 ImpMath::Matrix::UnitZ(0.f, 0.f, 1.f, 0.f);
const ImpMath::Vector4 ImpMath::Matrix::UnitW(0.f, 0.f, 0.f, 1.f);
const ImpMath::Vector4 ImpMath::Matrix::One(1.f, 1.f, 1.f, 1.f);
const ImpMath::Vector4 ImpMath::Matrix::Zero(0.f, 0.f, 0.f, 0.f);

#pragma endregion Matrix