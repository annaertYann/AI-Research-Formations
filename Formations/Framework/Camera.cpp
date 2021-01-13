#include "pch.h"
#include "Camera.h"
#include "utils.h"
#include <cmath>
void Camera::UpdateScale(SDL_Event event)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	float scale = 1;
	if (event.wheel.y < 0)
	{
		scale -= 0.05f;
		m_Speed /= scale;
		m_Scale *= scale;
		Point2f temp{ GetMousePos() };

		auto temp2{ temp };

		temp.x *= scale;
		temp.y *= scale;
		auto diff{ temp - temp2 };

		glTranslatef(-diff.x, -diff.y, 0);
		m_Position += diff;
		m_Position.x /= scale;
		m_Position.y /= scale;
	}
	else if (event.wheel.y > 0)
	{
		scale += 0.05f;
		m_Scale *= scale;
		m_Speed /= scale;
		Point2f temp{GetMousePos() };

		auto temp2{temp};

		temp.x *= scale;
		temp.y *= scale;

		auto diff{ temp - temp2  };
		glTranslatef(-diff.x, -diff.y, 0);
		m_Position += diff;
		m_Position.x /= scale;
		m_Position.y /= scale;
	}

	glScalef(scale, scale, 1);
}
void Camera::Update(float delataTime)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_W] || pStates[SDL_SCANCODE_S] || pStates[SDL_SCANCODE_A] || pStates[SDL_SCANCODE_D])
	{
		if (pStates[SDL_SCANCODE_W])
		{
			float diff = m_Speed * delataTime;
			m_Position.y += diff;
			glTranslatef(0,-diff,0);
		}
		if (pStates[SDL_SCANCODE_S])
		{
			float diff = m_Speed * delataTime;
			m_Position.y -= diff;
			glTranslatef(0, diff, 0);
		}
		if (pStates[SDL_SCANCODE_A])
		{
			float diff = m_Speed * delataTime;
			m_Position.x -= diff;
			glTranslatef(diff, 0, 0);
		}
		if (pStates[SDL_SCANCODE_D])
		{
			float diff = m_Speed * delataTime;
			m_Position.x += diff;
			glTranslatef(-diff, 0, 0);
		}
	}


}
Point2f Camera::GetMousePos()
{
	Point2f mousePos{};
	int x{};
	int y{ };
	SDL_GetMouseState(&x, &y);

	x = (x) * (1 / m_Scale);
	y = (y) * (1 / m_Scale);

	float height = m_Window.height / m_Scale;

	
	mousePos = Point2f{float(x) +m_Position.x , (height-float(y) )+m_Position.y};
	return mousePos;
}
Point2f Camera::GetPosition()
{
	return m_Position;
}
Window Camera::GetWindow()
{
	Window window = m_Window;
	window.width /= m_Scale;
	window.height /= m_Scale;
	return window;
}