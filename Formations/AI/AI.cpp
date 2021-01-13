#include "../Framework/pch.h"
#include "AI.h"
void AI::Update(float deltaTime)
{
	if (m_IsWandering)
	{
		Seek(deltaTime, m_WanderTarget);
		if ( m_WanderDelay.Update(deltaTime))
		{
			Point2f extra{float(rand()%m_WanderRange),float(rand()%m_WanderRange)};
			if (rand() % 2 == 0) { extra.x *= -1; }
			if (rand() % 2 == 0) { extra.y *= -1; }
			m_WanderTarget = Point2f{ m_StartPoint.x + extra.x,m_StartPoint.y+extra.y };
			m_WanderDelay.SetDelayTime(float((rand()%5)+5));
		}
	}
}

void AI::Draw()const
{
	glPushMatrix();
	glTranslatef(m_Shape.left+m_Shape.width/2, m_Shape.bottom+m_Shape.height/2, 0);
	glRotatef(m_Rotation+180,0,0,1);
	glTranslatef(-m_Shape.left-m_Shape.width/2, -m_Shape.bottom-m_Shape.height/2, 0);

	utils::SetColor(m_Color);
	utils::FillRect(m_Shape);

	m_Texture.Draw(m_Shape);
	utils::SetColor(Color4f{ 0, 0, 0, 1 });
	utils::DrawRect(m_Shape);

	
	glPopMatrix();
}
void AI::Seek(float deltaTime, Point2f target)
{
	Vector2f movement = {};
	movement = target - Point2f{ m_Shape.left + m_Shape.width / 2,m_Shape.bottom + m_Shape.height / 2 };
	movement = movement.Normalized();
	movement *= m_MovementSpeed*deltaTime;

	if ((target - Point2f{ m_Shape.left + m_Shape.width / 2,m_Shape.bottom + m_Shape.height / 2 }).Length() > 2)
	{
		m_Shape.left += movement.x;
		m_Shape.bottom += movement.y;
	}

	if (movement.Length() != 0)
	{
		m_Rotation = (atan2f(movement.x, -movement.y)*180/M_PI) + m_ExtraRotation ;
	}

	
}
