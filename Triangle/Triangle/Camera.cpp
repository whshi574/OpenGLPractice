#include "Camera.h"

Camera::Camera()
{
	Position = glm::vec3(1.0f);
	FrontVector = glm::vec3(1.0f);
	UpVector = glm::vec3(1.0f);

	ViewMatrix = glm::mat4(1.0f);
	MoveSpeed = 0.08f;

	IsFirstMove = true;
	RotateSensitivity = 0.1f;
	Pitch = 0.0f;
	Yaw = -90.0f;

	xpos = 0.0f;
	ypos = 0.0f;
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

void Camera::AddPitch(double _yoffset)
{
	Pitch += _yoffset * RotateSensitivity;

	if (Pitch >= 89.0f)
	{
		Pitch = 89.0f;
	}

	if (Pitch <= -89.0f)
	{
		Pitch = -89.0f;
	}

	FrontVector.y = sin(glm::radians(Pitch));
	FrontVector.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	FrontVector.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	FrontVector = glm::normalize(FrontVector);

	Update();
}

void Camera::AddYaw(double _xoffset)
{
	Yaw += _xoffset * RotateSensitivity;

	FrontVector.y = sin(glm::radians(Pitch));
	FrontVector.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	FrontVector.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	FrontVector = glm::normalize(FrontVector);
	Update();
}

void Camera::SetSensitivity(float _s)
{
	RotateSensitivity = _s;
}

void Camera::onMouseMove(double _xpos, double _ypos)
{
	if (IsFirstMove) 
	{
		IsFirstMove = false;
		xpos = _xpos;
		ypos = _ypos;
		return;
	}

	double xoffset = _xpos - xpos;
	double yoffset = -(_ypos - ypos);

	std::cout << "Xoffset:" << xoffset << std::endl;
	std::cout << "Yoffset:" << yoffset << std::endl;

	xpos = _xpos;
	ypos = _ypos;

	AddPitch(yoffset);
	AddYaw(xoffset);
}