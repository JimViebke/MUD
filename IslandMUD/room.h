/* Jim Viebke
Feb 14, 2015 */

#ifndef ROOM_H
#define ROOM_H

#include <map> // for room contents multimap
#include <set> // playerlist

#include "utilities.h"
#include "constants.h"
#include "item.h"
#include "room_side.h" // walls, floor, or ceiling

class Room
{
private:
	bool updated = false; // has the room been updated since it was loaded?
	bool water = false; // is the room dry land or water?
	shared_ptr<Chest> chest; // nullptr if the room does not have a chest
	map<string, Room_Side> room_sides = {}; // the floor, walls, and ceiling in the room (present surfaces only)
	multimap<string, shared_ptr<Item>> contents = {}; // the items in a room
	vector<string> viewing_actor_ids = {}; // the PCs and NPCs who can see this room
	vector<string> actor_ids = {}; // the PCs and NPCs in a room

public:

	Room() {}

	// configuration
	void set_water_status(const bool & is_water) { water = is_water; }

	// room contents
	const multimap<string, shared_ptr<Item>> get_contents() const { return contents; }
	const map<string, Room_Side> get_room_sides() const { return room_sides; }
	const vector<string> get_actor_ids() const { return actor_ids; }

	// room information
	bool has_wall() const;
	bool has_standing_wall() const;
	bool is_standing_wall(const string & surface_ID) const;
	bool has_surface(const string & direction_id) const;
	string can_move_in_direction(const string & direction_ID, const string & faction_ID);
	bool contains_no_items() const;
	bool is_unloadable() const;
	bool contains_item(const string & item_id) const;
	bool contains_item(const string & item_id, const unsigned & count) const;
	bool is_observed_by(const string & actor_id) const;
	bool is_water() const;
	bool is_forest() const;
	bool has_non_mineral_deposit_item() const;
	bool has_mineral_deposit() const;

	// chests
	void add_chest(const string & set_faction_id);
	bool has_chest() const;
	string get_chest_faction_id() const;
	int chest_health() const;
	void add_item_to_chest(const shared_ptr<Item> & item);
	string chest_contents(const string & faction_ID) const;
	void damage_chest();
	bool chest_has(const string & item_id) const;
	shared_ptr<Item> remove_from_chest(const string & item_id);
	shared_ptr<Chest> get_chest() const;
	void set_chest(const shared_ptr<Chest> & set_chest);

	// items
	void add_item(const shared_ptr<Item> item);
	void remove_item(const string & item_id, const int & count = 1);
	bool damage_item(const string & item_id, const int & amount);

	// add surfaces and doors
	void add_surface(const string & surface_ID, const string & material_ID);
	void add_surface(const string & surface_ID, const string & material_ID, const int & surface_health);
	void add_door(const string & directon_ID, const int & health, const string & material_ID, const string & faction_ID);

	// damage surface
	string damage_surface(const string & surface_ID, const shared_ptr<Item> & equipped_item);
	string damage_door(const string & surface_ID, const shared_ptr<Item> & equipped_item);

	// add and remove actors
	void add_actor(const string & actor_id);
	void remove_actor(const string & actor_id);
	void add_viewing_actor(const string & actor_id);
	void remove_viewing_actor(const string & actor_id);

	// printing
	string summary(const string & player_ID) const;

};

#endif