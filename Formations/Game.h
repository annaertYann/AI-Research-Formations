#pragma once
#include "Framework/FpsCheck.h"
#include "Framework/Camera.h"
#include "AI/FormationController.h"
class Game
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessMouseWheel(const SDL_Event& e);
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	
	const Window m_Window;
	FPSChecker m_FPS;
	Camera* m_pCamera = nullptr;
	std::vector<AI*> m_AI;
	Point2f m_Target = Point2f{ 500,500 };
	FormationController* m_pFormation{};
	//SELECTION
	std::vector<AI*>m_SelectedAI;
	Rectf m_SelectSquare{};
	bool m_IsSelecting = false;
	// FUNCTIONS
	void Initialize( );
	void SelectAgents();
	void Cleanup( );
	void ClearBackground( ) const;
	

};