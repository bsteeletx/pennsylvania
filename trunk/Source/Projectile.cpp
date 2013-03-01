#include "Projectile.h"

std::vector<Sprite *> Projectile::ProjectileStack;
std::vector<Sprite *> Projectile::HiddenProjectiles;

Projectile::Projectile(void)
	: Sprite()
{
}


Projectile::~Projectile(void)
{
}

Projectile::Projectile(Text SpriteFilename, Vector Speed, float sizeOfProj)
{
	Filename = SpriteFilename;
	Velocity = Speed.getVelocity();
	size = sizeOfProj;
	//ProjectileStack.push_back(new Sprite(Filename, true));
	//setVisible(false);
}

void Projectile::clone(Point Location)
{
	//reuse projectiles, if available
	if (HiddenProjectiles.size() == 0)
	{
		//none available, create a new one
		ProjectileStack.push_back(new Sprite(Filename, true));

		ProjectileStack.back()->setDepth(8000);
		ProjectileStack.back()->setSize(size);
	}
	else
	{
		for (unsigned int i = 0; i < HiddenProjectiles.size(); i++)
		{
			//make sure they are the same
			if (HiddenProjectiles[i]->getFilename() == Filename)
			{
				//reuse old one
				ProjectileStack.push_back(HiddenProjectiles[i]);
				HiddenProjectiles.pop_back();
				break;
			}
		}

		//didn't find anything that was the same projectile, create a new one
		ProjectileStack.push_back(new Sprite(Filename, true));

		ProjectileStack.back()->setDepth(8000);
		ProjectileStack.back()->setSize(size);
	}

	//set position and set visible
	ProjectileStack.back()->setPosition(Location);
	ProjectileStack.back()->setVisible(true);	
}

int Projectile::update(std::vector<Character*> Defenders)
{
	//default is no collision (-1)
	int temp = -1;
	bool moved = false;

	///go through all Projectiles and defenders for collisions
	for (unsigned int j = 0; j < Defenders.size(); j++)
	{
		for (unsigned int i = 0; i < ProjectileStack.size(); i++)
		{
			if ((ProjectileStack[i]->getX() > 100.0f) || (ProjectileStack[i]->getX() < -25.0f))
			{
				//off the screen, push the projectile to the hidden stack
				HiddenProjectiles.push_back(ProjectileStack.at(i));
				//erase the projectile from the visibile stack
				ProjectileStack.erase(ProjectileStack.begin() + i--);
			}
			else if (ProjectileStack[i]->collidedWith(Defenders[j]->getSpriteNumber()))
			{
				//collided with another sprite, currently only allows one collision
				//this may need to be changed
				//for now, take note of the collision, add the projectile to the
				//hidden projectiles, and remove from visible projectiles
				temp = j;
				ProjectileStack[i]->setVisible(false);
				HiddenProjectiles.push_back(ProjectileStack.at(i));
				ProjectileStack.erase(ProjectileStack.begin() + i--);
			}
			else if (!moved)
				//move the projectiles by their velocity
				ProjectileStack[i]->move(Velocity);
		}

		moved = true;
	}

	//return which creature got hit by the projectile
	return temp;
}