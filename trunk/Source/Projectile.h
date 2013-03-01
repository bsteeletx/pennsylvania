#pragma once
#include "Character.h"
#include "Sprite.h"
#include "Vector.h"
#include <vector>

class Projectile :
	public Sprite
{
public:
	Projectile(void);
	~Projectile(void);
	Projectile(Text SpriteFilename, Vector SpeedInDirection, float sizeOfProj);

	void clone(Point Location);

	int update(std::vector<Character*> Defenders);

private:
	float size;

	static std::vector<Sprite *> ProjectileStack;
	static std::vector<Sprite *> HiddenProjectiles;

	Point Velocity;
	Text Filename;
};

