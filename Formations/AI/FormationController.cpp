#include "../Framework/pch.h"
#include "FormationController.h"
FormationController::FormationController(Camera* camera)
{
	m_pCamera = camera;
}
FormationController::~FormationController()
{
	for (auto& pFormation : m_Formations)
	{
		SAFE_DELETE(pFormation);
	}
}
void FormationController::Draw()const
{
	//DRAW DEBUG
	if (m_CurrentFormation != nullptr && m_DebugMode)
	{
		m_CurrentFormation->Draw();
	}
	utils::FillEllipse(m_Target, 10, 10);
	//DRAW UI 
	Point2f pos{ m_pCamera->GetPosition() };
	Rectf shapeUI{ pos.x,pos.y,m_pCamera->GetWindow().width / 5,m_pCamera->GetWindow().height };
	Rectf formationUIShape{ shapeUI.left + (shapeUI.width / 8) , (shapeUI.bottom + shapeUI.height) - (shapeUI.height / 10),(shapeUI.width - shapeUI.width / 4),shapeUI.height / 20 };
	Rectf formationCloseButton{ (formationUIShape.left + formationUIShape.width) - (formationUIShape.width / 4) , formationUIShape.bottom ,(formationUIShape.width / 4),formationUIShape.height };
	Rectf formationName{formationCloseButton};
	Rectf formationInfo{ pos.x,pos.y,shapeUI.width,shapeUI.height / 20 };
	formationName.left -= formationCloseButton.width * 3;
	formationName.width *= 2;
	utils::SetColor(Color4f{ 0.1f,0.1f,0.1f,1 });
	utils::FillRect(shapeUI);
	for (auto& pFormation : m_Formations)
	{
		utils::SetColor(Color4f{ 0.3f,0.3f,0.3f,1 });
		utils::FillRect(formationUIShape);
		utils::SetColor(Color4f{ 0.9f,0.3f,0.3f,1 });
		utils::FillRect(formationCloseButton);
		if (pFormation->GetIsSelected())
		{
			utils::SetColor(Color4f{ 0.0f,1.0f,0.0f,1 });
			utils::DrawRect(formationUIShape);
		}

		m_Texture.Draw(formationName);
		m_TextureInfo.Draw(formationInfo);
		formationUIShape.bottom -= shapeUI.height / 10;
		formationCloseButton.bottom -= shapeUI.height / 10;
		formationName.bottom -= shapeUI.height / 10;
		
	}
	
}
void FormationController::Update(float deltaTime)
{
	if (m_CurrentFormation != nullptr) 
	{ 
		m_CurrentFormation->Update(deltaTime);
		m_CurrentFormation->Seek(m_Target,deltaTime); 
	}

}
void FormationController::SelectFormation()
{
	Point2f pos{ m_pCamera->GetPosition() };
	Rectf shapeUI{ pos.x,pos.y,m_pCamera->GetWindow().width / 5,m_pCamera->GetWindow().height };
	Rectf formationUIShape{ shapeUI.left + (shapeUI.width / 8) , (shapeUI.bottom + shapeUI.height) - (shapeUI.height / 10),(shapeUI.width - shapeUI.width / 4),shapeUI.height / 20 };
	Rectf formationCloseButton{ (formationUIShape.left + formationUIShape.width) - (formationUIShape.width / 4) , formationUIShape.bottom ,(formationUIShape.width / 4),formationUIShape.height };
	Rectf formationName{ formationCloseButton };
	formationName.left -= formationCloseButton.width * 3;
	formationName.width *= 2;
	utils::SetColor(Color4f{ 0.1f,0.1f,0.1f,1 });
	utils::FillRect(shapeUI);
	m_Formations.erase(std::remove_if(m_Formations.begin(), m_Formations.end(), [&](Formation* element)
	{
		if (utils::IsPointInRect(m_pCamera->GetMousePos(), formationCloseButton))
		{
			SAFE_DELETE(element);
			return true;
		}
		if (utils::IsPointInRect(m_pCamera->GetMousePos(), formationUIShape))
		{
			for (auto f : m_Formations)
			{
				f->SetIsSelected(false);
			}
			m_CurrentFormation = element;
			m_CurrentFormation->SetIsSelected(true);
			m_Target = m_CurrentFormation->GetPosition();
		}
		formationUIShape.bottom -= shapeUI.height / 10;
		formationCloseButton.bottom -= shapeUI.height / 10;
		formationName.bottom -= shapeUI.height / 10;
		return false;
	}),m_Formations.end());

}
void FormationController::AddFormation(Formation* formation)
{
	for (auto f : m_Formations)
	{
		f->SetIsSelected(false);
	}
	m_Formations.push_back(formation); 
	m_CurrentFormation = formation;
	m_CurrentFormation->SetIsSelected(true);
	
}
void FormationController::ChangeFormationType(bool left)
{
	if (m_Formations.size() > 0)
	{
		if (left && int(m_FormationType) > 0)
		{
			m_FormationType = FormationType(int(m_FormationType) - 1);
		}
		if (!left && int(m_FormationType) < int(FormationType::END) - 1)
		{
			m_FormationType = FormationType(int(m_FormationType) + 1);
		}
		std::vector<AI*> ai = m_CurrentFormation->GetAI();
		switch (m_FormationType)
		{
		case FormationType::Phalanx:
			m_Formations.erase(std::remove_if(m_Formations.begin(), m_Formations.end(), [&](Formation* element)
			{
				return element->GetIsSelected();
			}), m_Formations.end());
			SAFE_DELETE(m_CurrentFormation);
			m_CurrentFormation = new Square{ ai };
			m_Formations.push_back(m_CurrentFormation);
			m_CurrentFormation->SetIsSelected(true);
			break;
		case FormationType::FlyingWedge:
			m_Formations.erase(std::remove_if(m_Formations.begin(), m_Formations.end(), [&](Formation* element)
			{
				return element->GetIsSelected();
			}), m_Formations.end());
			SAFE_DELETE(m_CurrentFormation);
			m_CurrentFormation = new Triangle{ ai };
			m_Formations.push_back(m_CurrentFormation);
			m_CurrentFormation->SetIsSelected(true);
			break;
		case FormationType::Turtle:
			m_Formations.erase(std::remove_if(m_Formations.begin(), m_Formations.end(), [&](Formation* element)
			{
				return element->GetIsSelected();
			}), m_Formations.end());
			SAFE_DELETE(m_CurrentFormation);
			m_CurrentFormation = new Turtle{ ai };
			m_Formations.push_back(m_CurrentFormation);
			m_CurrentFormation->SetIsSelected(true);
			break;
		case FormationType::END:
			break;
		default:
			break;
		}
	}
}