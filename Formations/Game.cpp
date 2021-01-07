#include "../../Framework/pch.h"
#include "Game.h"

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
	for (int i{}; i < 78; i++)
	{
		m_AI.push_back(new AI{ Rectf{float(rand() % int(m_Window.width)),float(rand() % int(m_Window.height)),m_Window.width / 20,m_Window.height / 20} });
	}
	m_pFormation = new Triangle{m_AI};
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

void Game::Update( float elapsedSec )
{
	m_FPS.update(elapsedSec);
	m_pCamera->Update(elapsedSec);
	
	for (auto pAI : m_AI)
	{
		pAI->Update(elapsedSec);
	}
	m_pFormation->Seek(m_Target,elapsedSec);
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
}

///////////////////////////////////////////////////////////////////////////////////////
void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	
}
void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}
void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}
void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_Target = m_pCamera->GetMousePos();
		
		break;
	case SDL_BUTTON_RIGHT:
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}
void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}
void Game::ProcessMouseWheel(const SDL_Event& e)
{
	m_pCamera->UpdateScale(e);
}
void Game::ClearBackground( ) const
{
	glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
