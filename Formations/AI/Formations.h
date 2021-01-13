#pragma once
#include <map>
#include "AI.h"
class Formation
{
public:
	struct PlaceHolder
	{
		PlaceHolder(Point2f x, Point2f y) { translatedPostion = x; rotatedPostion = y; }
		Point2f translatedPostion;
		Point2f rotatedPostion;
	};
	Formation(std::vector<AI*> ai) 
	{
		m_AI = ai;
		for (auto pElement : ai)
		{
			if (pElement != nullptr)
			{
				m_SpaceBetweenUnits.x = pElement->GetShape().width*2;
				m_SpaceBetweenUnits.y = pElement->GetShape().height*2;
				break;
			}
		}
	};
	~Formation()=default;
	Point2f CalculateAveragePos();
	virtual void ConstructFormation() {};
	Point2f GetPosition() { return m_Position; }
	void Update(float deltaTime);
	void Draw()const;
	void Seek(Point2f target,float deltaTime);

	void SetIsSelected(bool x) { m_IsSelected = x; }
	bool GetIsSelected() { return m_IsSelected; }

	std::vector<AI*> GetAI() { return m_AI; }

protected:
	
	std::vector < std::pair< PlaceHolder, AI*> > m_Place;
	std::vector<AI*> m_AI;
	Point2f m_Position = Point2f{500,500};
	float m_Rotation = 0;
	float m_MovementSpeed=400;
	float m_MaxMovementSpeed = 400;
	Vector2f m_SpaceBetweenUnits;
	bool m_IsSelected = false;
};



class Square:public Formation
{
public:
	Square(std::vector<AI*> ai)
		:Formation(ai)
	{
		ConstructFormation();
	}

	~Square()=default;
	void ConstructFormation();
private:
	float m_RowSize = 9;
};

class Triangle :public Formation
{
public:
	Triangle(std::vector<AI*> ai)
		:Formation(ai) 
	{
		ConstructFormation(); 
	}

	~Triangle() = default;

	void ConstructFormation();
private:
};

class Rect:public Formation
{
public:
	Rect(std::vector<AI*> ai)
		:Formation(ai)
	{
		ConstructFormation();
	}
	~Rect()= default;
	void ConstructFormation();
private:
	float m_RowSize = 9;
	float m_collomSize = 5;
};


class Turtle :public Formation
{
public:
	Turtle(std::vector<AI*> ai)
		:Formation(ai)
	{
	}

	~Turtle() = default;

	void ConstructFormation();
private:
	float m_RowSize = 9;
};