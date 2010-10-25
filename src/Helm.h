
#ifndef _HELM_H_
#define _HELM_H_

#include "ArmorItem.h"

class Helm : public ArmorItem {
public:
	Helm();
	virtual ~Helm();

	virtual void Update();
	virtual void Activate();
};

#endif
