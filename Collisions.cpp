#include "Collisions.h"
#include "Character.h"

Collisions* Collisions::mInstance = NULL;

Collisions::Collisions() {

}
Collisions::~Collisions() {
	mInstance = NULL;
}
Collisions* Collisions::Instance() {
	if (!mInstance)
	{
		mInstance = new Collisions;

	}
	return mInstance;
}
bool Collisions::Circle(Character* myCharacterMario, Character* myCharacterLuigi) {
	Vector2D vec = Vector2D( (myCharacterMario->GetPosition().x - myCharacterLuigi->GetPosition().x),
							 (myCharacterMario->GetPosition().y - myCharacterLuigi->GetPosition().y));
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	double combinedDistance = (myCharacterMario->GetCollisionRadius() + myCharacterLuigi->GetCollisionRadius());
	return distance < combinedDistance;
}
bool Collisions::Box(Rect2D rect1, Rect2D rect2) {
	if (rect1.x + (rect1.width / 2) > rect2.x &&
		rect1.x + (rect1.width / 2) < rect2.x + rect2.width &&
		rect1.y + (rect1.height / 2) > rect2.y &&
		rect1.y + (rect1.height / 2) < rect2.y + rect2.height) {
		return true;
	}
	return false;
}
