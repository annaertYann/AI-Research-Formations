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
				pElement->SetExtraRotation(0);
				pElement->SetColor(Color4f{1,1,1,1});
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
	bool m_buildOnce = false;
};



class Square:public Formation
{
public:
	Square(std::vector<AI*> ai)
		:Formation(ai)
	{
		m_RowSize = int(sqrt( m_AI.size() ) ) ;
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


class HalfTurtle :public Formation
{
public:
	HalfTurtle(std::vector<AI*> ai)
		:Formation(ai)
	{
		m_RowSize = int(sqrt(m_AI.size()));
		ConstructFormation();
	}

	~HalfTurtle() = default;

	void ConstructFormation();
private:
	float m_RowSize = 9;
};
class Turtle :public Formation
{
public:
	Turtle(std::vector<AI*> ai)
		:Formation(ai)
	{
		m_RowSize = int(sqrt(m_AI.size())) ;
		ConstructFormation();
	}

	~Turtle() = default;

	void ConstructFormation();
private:
	float m_RowSize = 9;
};
class Line :public Formation
{
public:
	Line(std::vector<AI*> ai)
		:Formation(ai)
	{
		ConstructFormation();
		
	}

	~Line() = default;

	void ConstructFormation();
private:
};
class Column :public Formation
{
public:
	Column(std::vector<AI*> ai)
		:Formation(ai)
	{
		ConstructFormation();

	}

	~Column() = default;

	void ConstructFormation();
private:
};

class Loose :public Formation
{
public:
	Loose(std::vector<AI*> ai)
		:Formation(ai)
	{
		ConstructFormation();

	}

	~Loose() = default;

	void ConstructFormation();
private:
};
class Circle :public Formation
{
public:
	Circle(std::vector<AI*> ai)
		:Formation(ai)
	{
		m_Degree = 360 / float(m_AI.size());
		ConstructFormation();
		
	}

	~Circle() = default;

	void ConstructFormation();
private:
	float m_Degree = 0;
};
class HalfCircle :public Formation
{
public:
	HalfCircle(std::vector<AI*> ai)
		:Formation(ai)
	{
		m_Degree = 360 / float(m_AI.size() + 1);
		ConstructFormation();

	}

	~HalfCircle() = default;

	void ConstructFormation();
private:
	float m_Degree = 0;
};