#pragma once
#include "Base.h"

enum Camera_Move {
	MOVEFORWARD,
	MOVEBACK,
	MOVERIGHT,
	MOVELEFT
};

class Camera
{
private:
	glm::vec3 Position;
	glm::vec3 FrontVector;
	glm::vec3 UpVector;

	float MoveSpeed;
	glm::mat4 ViewMatrix;

	float Pitch;
	float Yaw;
	float Roll;
	float RotateSensitivity;

	float xpos;
	float ypos;
	bool IsFirstMove;

public:
	Camera();
	~Camera();

	void LookAt(glm::vec3 _Position, glm::vec3 _Front, glm::vec3 _Up);
	void Update();
	glm::mat4 GetViewMatrix();

	void Move(Camera_Move _MoveType);
	void SetSpeed(float _speed);

	void AddPitch(double _xoffset);
	void AddYaw(double _yoffset);
	void SetSensitivity(float _s);

	void onMouseMove(double _xpos, double _ypos);
};

