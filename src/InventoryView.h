
#ifndef _INVENTORY_VIEW_H_
#define _INVENTORY_VIEW_H_

#include "GeneralIncludes.h"
#include "View.h"

class Item;

class InventoryView : public View {
public:
	InventoryView(GameState* gs, int w, int h);
	virtual ~InventoryView();

	virtual bool RequestInput();
	virtual void Inititalize();
	virtual void Update();
	virtual void ResetState();

protected:
	void DrawPaperDollItem(Item* i, int y, int idx);
	void HandleItemSelection();
	bool m_inInventoryArea;
	int m_selectIdx;
};

#endif
