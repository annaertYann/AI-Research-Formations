#pragma once
#include "../Framework/Texture.h"
class AI
{
public:
	AI(Rectf shape) { m_Shape = shape; m_StartPoint = Point2f{ m_Shape.left + m_Shape.width / 2,m_Shape.bottom + m_Shape.height / 2 }; m_WanderTarget = m_StartPoint; };
	~AI()=default;

	void Update(float deltaTime);
	void Draw()const;

	void Seek(float deltaTime, Point2f target);
	void SetIsWandering(bool x) { m_IsWandering = x; }

	void SetRotation(float rotation) { m_Rotation = rotation; }
	float GetRotation() { return m_Rotation; }

	void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }
	void SetToMaxMovementSpeed() { m_MovementSpeed = m_MaxMovementSpeed; }

	Point2f GetPosition() { return  Point2f{ m_Shape.left + m_Shape.width / 2,m_Shape.bottom + m_Shape.height / 2 }; }
	Rectf GetShape() { return m_Shape; }

	void SetExtraRotation(float x) { m_ExtraRotation = x; }
	float GetExtraRotation() { return m_ExtraRotation; }

	void SetColor(Color4f x) { m_Color = x; }
private:
	Texture m_Texture{"Resources/Arrow.png"};
	//Wandering
	Delay m_WanderDelay = Delay{ float((rand() % 5 ) + 5)};
	Point2f m_StartPoint;
	Point2f m_WanderTarget = Point2f{};
	bool m_IsWandering = true;
	int m_WanderRange = 400;
	//////////////////////////////////////
	//(rand() % 3) + 2
	Rectf m_Shape;
	float m_MovementSpeed = 400;
	float m_ExtraRotation = 0;
	float m_MaxMovementSpeed = 800;
	Color4f m_Color = Color4f{1,1,1,1};
	float m_Rotation = 0;
};