#pragma once

/// <summary>
///  ī�޶� ������Ʈ 
/// 
/// 
/// </summary>
class CameraObject
{
public:
	CameraObject();
	~CameraObject();
	void Initialize(int width, int hegiht, XMVECTOR position);
	void Update();
	void Finalize();

	DirectX::XMVECTOR GetPosition() const { return m_position; }
public:
	DirectX::XMMATRIX GetViewMatrix() const { return m_viewMatrix; }
	DirectX::XMMATRIX GetProjectMatrix() const { return m_projectMatrix; }
	void SetFovAngleY(float val) { m_fovAngleY = val; }
	float GetFovAngleY() const { return m_fovAngleY; }
	void SetNearZ(float val) { m_nearZ = val; }
	float GetNearZ() const { return m_nearZ; }
	void SetFarZ(float val) { m_farZ = val; }
	float GetFarZ() const { return m_farZ; }

	void MoveCameraZ(float distace);
	void MoveCameraX(float distace);
	void MoveCameraY(float distace);
	void RotateCameraY(float angle);
	void RotateCameraX(float angle);

private:
	DirectX::XMMATRIX m_viewMatrix; // ī�޶� ��ȯ ��� 
	DirectX::XMMATRIX m_projectMatrix; // ���� ���

	XMVECTOR m_position;  // ī�޶� ��ġ 
	XMVECTOR m_rotation;  // ī�޶� ����

	XMVECTOR m_cameraDirection; // ī�޶� �ٶ󺸴� ���� ���� z��
	XMVECTOR m_worldUp;


	float m_fovAngleY;   // �þ߰� 
	float m_aspectRatio;
	float m_nearZ;
	float m_farZ;

};

