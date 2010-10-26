
#ifndef _SIGHT_H_
#define _SIGHT_H_

class Level;
class Entity;

class Sight {
public:
	static Sight* Instance();

	void SetCurrentLevel(Level* l);
	bool CanSee(Entity* e1, Entity* e2, bool debug = false);
	bool CanSee(int x0, int y0, int x1, int y1, bool debug = false);
protected:
	static Sight* sm_instance;

	Sight();
	~Sight();
	Level* m_level;
};

#endif
