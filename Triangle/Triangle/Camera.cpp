#include "Camera.h"

Camera::Camera()
{
	Position = glm::vec3(1.0f);
	FrontVector = glm::vec3(1.0f);
	UpVector = glm::vec3(1.0f);
	ViewMatrix = glm::mat4(1.0f);
	MoveSpeed = 0.01f;
}

Camera::~Camera()
{

}

void Camera::LookAt(glm::vec3 _Position, glm::vec3 _Front, glm::vec3 _Up)
{
	Position = _Position;
	FrontVector = glm::normalize(_Front);
	UpVector = glm::normalize(_Up);//? do not normalize?

	ViewMatrix = glm::lookAt(Position, Position + FrontVector, UpVector);
}

void Camera::Update()
{
	ViewMatrix = glm::lookAt(Position, Position + FrontVector, UpVector);
}

glm::mat4 Camera::GetViewMatrix()
{
	return ViewMatrix;
}

void Camera::Move(Camera_Move _MoveType)
{
	switch (_MoveType)
	{
	case MOVEFORWARD:
		Position = Position + FrontVector * MoveSpeed;
		Update();
		break;
	case MOVEBACK:
		Position = Position - FrontVector * MoveSpeed;
		Update();
		break;
	case MOVERIGHT:
		Position = Position + glm::cross(FrontVector, UpVector) * MoveSpeed;
		Update();
		break;
	case MOVELEFT:
		Position = Position - glm::cross(FrontVector, UpVector) * MoveSpeed;
		Update();
		break;
	}
}

void Camera::SetSpeed(float _speed)
{
	MoveSpeed = _speed;
}
