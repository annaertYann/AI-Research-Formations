#pragma once
enum class ActionState
{
	Idle,
	Running,
	BasicAttack,
	Special1,
	Special2,
	Special3,
	Special4,
	Jump,
	Dodge,
	Death,
	Hit
};

enum class Race
{
	Human,
	Slime
};
enum class WP
{
	Sword
};
enum class Faction
{
	Enemy,
	Neutral,
	Friendly,
	Object
};
enum class NaturalObject
{
	ground,
	tree,
	bush,
	rock
};
enum class Direction
{
	up, down, right, left, upRight, upLeft, downRight, downLeft
};
enum class LandType
{
	GreenLands
};