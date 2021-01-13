#pragma once
class Camera
{
public:
	Camera(Point2f startPos, Window window) { m_Position = startPos; m_Window = window; };
	~Camera()=default;

	void Update(float delataTime);
	void UpdateScale(SDL_Event event);
	Point2f GetMousePos();
	Point2f GetPosition();
	Window GetWindow();
private:
	Point2f m_Position = {};
	float m_Speed = 400;
	float m_Scale = 1;
	Window m_Window;
	Vector2f m_Center = Vector2f{};
};
