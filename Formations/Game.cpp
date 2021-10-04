#include "../../AI-Research-Formations/Formations/Framework/pch.h"
#include "Game.h"


#include "Framework/Defines.h"
#include "Framework/structs.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_FPS{}
	, m_pCamera{ new Camera{{},window} }
	, m_pFormation{  }
{
	Initialize( );

}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pFormation = new FormationController{m_pCamera};
	for (int i{}; i < 25; i++)
	{
		m_AI.push_back(new AI{ Rectf{float(rand() % int(m_Window.width)),float(rand() % int(m_Window.height)),m_Window.width / 20,m_Window.height / 20} });
	}
}

void Game::Cleanup( )
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pFormation);
	for (auto pAI : m_AI)
	{
		SAFE_DELETE(pAI);
	}
}
void Game::SelectAgents()
{

}
void Game::Update( float elapsedSec )
{
	m_FPS.update(elapsedSec);
	m_pCamera->Update(elapsedSec);
	
	for (auto pAI : m_AI)
	{
		pAI->Update(elapsedSec);
	}
	m_pFormation->Update(elapsedSec);
	
}

void Game::Draw( ) const
{
	ClearBackground( );
	for (auto pAI : m_AI)
	{
		pAI->Draw();
	}
	m_pFormation->Draw();
	utils::SetColor(Color4f{1,1,1,1});
	utils::DrawRect(m_SelectSquare);
}

///////////////////////////////////////////////////////////////////////////////////////
void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	
}
void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		m_pFormation->ChangeFormationType(true);
		break;
	case SDLK_RIGHT:
		m_pFormation->ChangeFormationType(false);
		//std::cout << "`Right arrow key released\n";
		break;
	case SDLK_1:
	case SDLK_KP_1:
		//std::cout << "Key 1 released\n";
		break;
	}
}
void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	if (m_IsSelecting)
	{
		m_SelectSquare.width = m_pCamera->GetMousePos().x-m_SelectSquare.left ;
		m_SelectSquare.height = m_pCamera->GetMousePos().y - m_SelectSquare.bottom;
	}
}
void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		if (!m_IsSelecting)
		{
			m_SelectSquare.left = m_pCamera->GetMousePos().x;
			m_SelectSquare.bottom = m_pCamera->GetMousePos().y;
			m_IsSelecting = true;
		}
		m_pFormation->SelectFormation();
		break;
	case SDL_BUTTON_RIGHT:
		m_pFormation->SetTarget(m_pCamera->GetMousePos());
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}
void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	Formation* f{};
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_IsSelecting= false;
		m_SelectedAI.clear();
		//ADJUST SELECT SQUARE IF NEEDED
		if (m_SelectSquare.width < 0)
		{
			m_SelectSquare.width *= -1;
			m_SelectSquare.left = m_SelectSquare.left - m_SelectSquare.width;
		}
		if (m_SelectSquare.height < 0)
		{
			m_SelectSquare.height *= -1;
			m_SelectSquare.bottom = m_SelectSquare.bottom - m_SelectSquare.height;
		}
		//ADD SELECTED AI
		for (auto& pAI : m_AI)
		{
			if (pAI != nullptr)
			{
				if (utils::IsOverlapping(m_SelectSquare, pAI->GetShape()))
				{
					m_SelectedAI.push_back(pAI);
				}
			}
		}
		m_SelectSquare = Rectf{};
		//MAKE FORMATION
		if (m_SelectedAI.size() > 0)
		{
			f = new Loose{ m_SelectedAI };
			m_pFormation->AddFormation(f);
		}
		break;
	case SDL_BUTTON_RIGHT:
		
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}
void Game::ProcessMouseWheel(const SDL_Event& e)
{
	m_pCamera->UpdateScale(e);
}
void Game::ClearBackground( ) const
{
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
