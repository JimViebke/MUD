/* Jim Viebke
Jun 3 2015 */

#include "npc_enemy.h"

void Hostile_NPC::update(World & world, map<string, shared_ptr<Character>> & actors)
{
	// every time this is called, the NPC executes one action against the world
	// any number of internal plans may be created, updated, or deleted

	cout << "I am " << name << " and I see " << count<PC>(world, actors) << " enemie(s) and "
		<< count<Hostile_NPC>(world, actors) << "friendlie(s).\n";
}