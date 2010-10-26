
#ifndef _SIGHT_H_
#define _SIGHT_H_

class Level;
class Entity;

class Sight {
public:
	static Sight* Instance();

	void SetCurrentLevel(Level* l);
	bool CanSee(Entity* e1, Entity* e2);
protected:
	static Sight* sm_instance;

	Sight();
	~Sight();
	Level* m_level;
};

#endif
