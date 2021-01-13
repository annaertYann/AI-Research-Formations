#include "../Framework/pch.h"
#include "Formations.h"
void Formation::Update(float deltaTime)
{
	for (auto &row : m_Place)
	{
		if (row.second != nullptr)
		{
			if ((row.first.rotatedPostion - row.second->GetPosition()).Length() > 5)
			{

				row.second->Seek(deltaTime, row.first.rotatedPostion);
				row.second->SetMovementSpeed(m_MovementSpeed);
			}
			else
			{
				row.second->SetRotation(((m_Rotation*180)/M_PI )+ row.second->GetExtraRotation());
			}
			if ((row.first.rotatedPostion - row.second->GetPosition()).Length() > 20)
			{
				row.second->SetToMaxMovementSpeed();
			}
			
		}
	}
}
void Formation::Draw()const
{
	utils::SetColor(Color4f{ 1,0,0,1 });
	utils::FillEllipse(m_Position, 10, 10);
	for (auto& row : m_Place)
	{
		utils::SetColor(Color4f{ 1,0,0,1 });
		utils::FillEllipse(row.first.rotatedPostion, 5, 5);
		utils::SetColor(Color4f{ 0,1,0,1 });
		utils::FillEllipse(row.first.translatedPostion, 5, 5);
	}

}
void Formation::Seek(Point2f target,float deltaTime)
{
	if ((target - m_Position).Length() > 5||!m_buildOnce)
	{
		Vector2f movement = {};
		movement = target - m_Position;
		movement = movement.Normalized();
		movement *= m_MovementSpeed*deltaTime;
		m_Position += movement;

		//m_Rotation -= (m_Rotation-(atan2f(movement.x, -movement.y)))/(5000*deltaTime);
		m_Rotation = atan2f(movement.x, -movement.y);
		for (auto& row : m_Place)
		{
			
			row.first.translatedPostion.x += movement.x;
			row.first.translatedPostion.y += movement.y;
			row.first.rotatedPostion = utils::rotatePointAroundPoint(row.first.translatedPostion, m_Rotation, m_Position);
		}	
		m_buildOnce = true;
	}
}
Point2f Formation::CalculateAveragePos()
{
	Point2f pos{};
	for (auto pElement : m_AI)
	{
		if (pElement != nullptr)
		{
			Point2f agentPos{ pElement->GetShape().left + pElement->GetShape().width / 2,pElement->GetShape().bottom + pElement->GetShape().height / 2 };
			pos.x += agentPos.x;
			pos.y += agentPos.y;
		}
	}
	pos.x /= m_AI.size();
	pos.y /= m_AI.size();
	return pos;
}





void Square::ConstructFormation()
{
	m_Place.clear();
	m_Position = CalculateAveragePos();
	int counter{};
	for (int j{}; j < m_RowSize; j++)
	{
		for (int i{}; i < m_RowSize; i++)
		{
			if (counter != m_AI.size())
			{
				m_Place.push_back(std::pair<PlaceHolder, AI*>{ PlaceHolder{
				Point2f{ (m_Position.x + i * m_SpaceBetweenUnits.x) - ((m_RowSize * m_SpaceBetweenUnits.x) / 2) + (m_SpaceBetweenUnits.x / 2)
				, m_Position.y + j * m_SpaceBetweenUnits.y - ((m_SpaceBetweenUnits.y * m_RowSize) / 2) + (m_SpaceBetweenUnits.y / 2) } ,{} }
				, m_AI[counter]});
				m_AI[counter]->SetIsWandering(false);
				if (j == 0)
				{
					m_Place[counter].second->SetColor(Color4f{ 1,0,0,1 });
				}
				else
				{
					m_Place[counter].second->SetColor(Color4f{ 0,1,0,1 });
				}
				counter++;
			}
		}
	}

}
void Triangle::ConstructFormation()
{
	m_Place.clear();
	m_Position = CalculateAveragePos();
	int rowSize{};
	int currentY{};
	int counter{};
	int colorCounter{};
	for (int i{}; i < m_AI.size(); i++)
	{
		m_Place.push_back(std::pair<PlaceHolder, AI*>{ PlaceHolder{
				Point2f{ (m_Position.x + counter * m_SpaceBetweenUnits.x) - ((rowSize * m_SpaceBetweenUnits.x) / 2) 
				, m_Position.y + (currentY) * m_SpaceBetweenUnits.y  } ,{} }
		, m_AI[i]});

		m_AI[i]->SetIsWandering(false);
		if (colorCounter < 3)
		{
			m_Place[colorCounter].second->SetColor(Color4f{ 1,0,0,1 });
		}
		else
		{
			m_Place[colorCounter].second->SetColor(Color4f{ 0,1,0,1 });
		}
		colorCounter++;
		counter++;
		if (counter > +currentY)
		{
			counter = 0;
			rowSize++;
			currentY++;
		}
	}

	
}
void Rect::ConstructFormation()
{
	m_Place.clear();
	m_Position = CalculateAveragePos();
	int counter{};
	for (int j{}; j < m_collomSize; j++)
	{
		for (int i{}; i < m_RowSize; i++)
		{
			if (counter != m_AI.size())
			{
				m_Place.push_back(std::pair<PlaceHolder, AI*>{ PlaceHolder{
				Point2f{ (m_Position.x + i * m_SpaceBetweenUnits.x) - ((m_RowSize * m_SpaceBetweenUnits.x) / 2) + (m_SpaceBetweenUnits.x / 2)
				, m_Position.y + j * m_SpaceBetweenUnits.y - ((m_SpaceBetweenUnits.y * m_collomSize) / 2) + (m_SpaceBetweenUnits.y / 2) } ,{} }
				, m_AI[counter]});
				m_AI[counter]->SetIsWandering(false);
				counter++;
			}
		}
	}


}
void HalfTurtle::ConstructFormation()
{
	m_Place.clear();
	m_Position = CalculateAveragePos();
	int counter{};
	for (int j{}; j < m_RowSize; j++)
	{
		for (int i{}; i < m_RowSize; i++)
		{
			if (counter < m_AI.size())
			{
				m_Place.push_back(std::pair<PlaceHolder, AI*>{ PlaceHolder{
				Point2f{ (m_Position.x + i * m_SpaceBetweenUnits.x) - ((m_RowSize * m_SpaceBetweenUnits.x) / 2) + (m_SpaceBetweenUnits.x / 2)
				, m_Position.y + j * m_SpaceBetweenUnits.y - ((m_SpaceBetweenUnits.y * m_RowSize) / 2) + (m_SpaceBetweenUnits.y / 2) } ,{} }
				, m_AI[counter]});
				m_AI[counter]->SetIsWandering(false);
				m_Place[counter].second->SetColor(Color4f{ 0,1,0,1 });
				if (j == 0)
				{
					m_Place[counter].second->SetColor(Color4f{ 1,0,0,1 });
				}
				if (j != 0)
				{
					if (i == 0)
					{
						m_Place[counter].second->SetExtraRotation(-90);
						m_Place[counter].second->SetColor(Color4f{0,0,1,1});
					}
					if (i == m_RowSize-1)
					{
						m_Place[counter].second->SetExtraRotation(90);
						m_Place[counter].second->SetColor(Color4f{ 0,0,1,1 });
					}
				}
				counter++;
			}
		}
	}
}
void Turtle::ConstructFormation()
{
	m_Place.clear();
	m_Position = CalculateAveragePos();
	int counter{};
	for (int j{}; j < m_RowSize; j++)
	{
		for (int i{}; i < m_RowSize; i++)
		{
			if (counter != m_AI.size())
			{
				m_Place.push_back(std::pair<PlaceHolder, AI*>{ PlaceHolder{
				Point2f{ (m_Position.x + i * m_SpaceBetweenUnits.x) - ((m_RowSize * m_SpaceBetweenUnits.x) / 2) + (m_SpaceBetweenUnits.x / 2)
				, m_Position.y + j * m_SpaceBetweenUnits.y - ((m_SpaceBetweenUnits.y * m_RowSize) / 2) + (m_SpaceBetweenUnits.y / 2) } ,{} }
				, m_AI[counter]});
				m_AI[counter]->SetIsWandering(false);
				m_Place[counter].second->SetColor(Color4f{ 0,1,0,1 });
				if (j == 0)
				{
					m_Place[counter].second->SetColor(Color4f{ 1,0,0,1 });
				}
				if (j != 0)
				{
					if (i == 0)
					{
						m_Place[counter].second->SetExtraRotation(-90);
						m_Place[counter].second->SetColor(Color4f{ 0,0,1,1 });
					}
					if (i == m_RowSize - 1)
					{
						m_Place[counter].second->SetExtraRotation(90);
						m_Place[counter].second->SetColor(Color4f{ 0,0,1,1 });
					}
				}
				if (j == m_RowSize-1)
				{
					m_Place[counter].second->SetExtraRotation(180);
					m_Place[counter].second->SetColor(Color4f{ 0,0,1,1 });
				}
				counter++;
			}
		}
	}

}

void Line::ConstructFormation()
{
	
	m_Place.clear();
	m_Position = CalculateAveragePos();
	int counter{};
	while (counter < m_AI.size())
	{
		if (counter != m_AI.size())
		{
			m_Place.push_back(std::pair<PlaceHolder, AI*>{ PlaceHolder{
			Point2f{ (m_Position.x + counter * m_SpaceBetweenUnits.x) - (((m_AI.size()) * m_SpaceBetweenUnits.x) / 2) + (m_SpaceBetweenUnits.x / 2)
			, m_Position.y +(m_SpaceBetweenUnits.y / 2) } ,{} }
			, m_AI[counter]});
			m_AI[counter]->SetIsWandering(false);
			m_Place[counter].second->SetColor(Color4f{ 1,0,0,1 });
			counter++;
		}
	}
}


void Column::ConstructFormation()
{

	m_Place.clear();
	m_Position = CalculateAveragePos();
	int counter{};
	while (counter < m_AI.size())
	{
		if (counter != m_AI.size())
		{
			m_Place.push_back(std::pair<PlaceHolder, AI*>{ PlaceHolder{
			Point2f{ m_Position.x 
			, m_Position.y + counter * m_SpaceBetweenUnits.y - ((m_SpaceBetweenUnits.y * m_AI.size()) / 2) + (m_SpaceBetweenUnits.y / 2) } ,{} }
			, m_AI[counter]});
			m_AI[counter]->SetIsWandering(false);
			if (counter == 0)
			{
				m_Place[counter].second->SetColor(Color4f{ 1,0,0,1 });
			}
			else
			{
				m_Place[counter].second->SetColor(Color4f{ 0,1,0,1 });
			}
			counter++;
		}
	}
}

void Loose::ConstructFormation()
{
	m_Place.clear();
	m_Position = CalculateAveragePos();
	for (int i{}; i < m_AI.size(); i++)
	{
		m_Place.push_back(std::pair<PlaceHolder, AI*>{ PlaceHolder{
				Point2f{ m_AI[i]->GetShape().left+ m_AI[i]->GetShape().width/2
				, m_AI[i]->GetShape().bottom + m_AI[i]->GetShape().height / 2 } ,{} }
		, m_AI[i]});

		m_AI[i]->SetIsWandering(false);
		m_AI[i]->SetColor(Color4f{1,0,0,1});
	}


}
void Circle::ConstructFormation()
{
	m_Place.clear();
	m_Position = CalculateAveragePos();

	for (int i{}; i < m_AI.size(); i++)
	{
		m_Place.push_back(std::pair<PlaceHolder, AI*>{ PlaceHolder{
				Point2f{ m_Position.x + ((cos(m_Degree*i)* m_SpaceBetweenUnits.x*(m_AI.size()/4)) )
				, m_Position.y + ((sin(m_Degree * i) * m_SpaceBetweenUnits.x * (m_AI.size()/4))) } ,{} }
		, m_AI[i]});

		m_AI[i]->SetIsWandering(false);
		m_AI[i]->SetColor(Color4f{ 0,0,1,1 });
	}
}
void HalfCircle::ConstructFormation()
{
	m_Place.clear();
	m_Position = CalculateAveragePos();

	for (int i{}; i < m_AI.size(); i++)
	{
		m_Place.push_back(std::pair<PlaceHolder, AI*>{ PlaceHolder{
				Point2f{ m_Position.x + ((cos(m_Degree * i) * m_SpaceBetweenUnits.x * (m_AI.size() / 4)))
				, m_Position.y + ((sin(m_Degree * i) * m_SpaceBetweenUnits.x * (m_AI.size() / 4))) } ,{} }
		, m_AI[i]});

		m_AI[i]->SetIsWandering(false);
		m_AI[i]->SetColor(Color4f{ 0,0,1,1 });
	}
}