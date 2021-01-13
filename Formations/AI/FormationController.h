#pragma once
#include "Formations.h"
#include "../Framework/Camera.h"
#include "../Framework/Texture.h"
enum class FormationType
{
Phalanx,
FlyingWedge
,Turtle
,END
};


class FormationController
{
public:
	FormationController(Camera* camera);
	~FormationController();

	void Draw()const;
	void Update(float deltaTime);
	void SetTarget(const Point2f& target) { m_Target = target; }
	void SelectFormation();
	void AddFormation(Formation* formation);
	void ChangeFormationType(bool left);
private:
	Texture m_Texture{ "Formation: ", "Resources/Font.otf",100,Color4f{0,0,0,1} };
	Texture m_TextureInfo{ "Cycle formation: LEFT/RIGHT", "Resources/Font.otf",100,Color4f{1,0,0,1} };
	bool m_DebugMode = false;
	Camera* m_pCamera = nullptr;
	Formation* m_CurrentFormation = nullptr;
	Point2f m_Target = Point2f{};
	std::vector<Formation*>m_Formations;
	FormationType m_FormationType = FormationType::Phalanx;
};