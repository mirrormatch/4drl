
#include "Inventory.h"

Inventory::Inventory() {
}

Inventory::~Inventory() {
}

void Inventory::AddItem(Item* toAdd) {
	// Don't want to add the same item twice
	for(ItemList::iterator i = m_items.begin(); i != m_items.end(); i++) {
		Item* toCheck = *i;
		if(toAdd == toCheck) {
			return;
		}
	}

	m_items.push_back(toAdd);
}

void Inventory::RemoveItem(Item* toRemove) {
	m_items.remove(toRemove);
}

void Inventory::RemoveItemAtIndex(unsigned int idx) {
	if(idx < m_items.size()) {
		unsigned int counter = 0;
		ItemList::iterator i = m_items.begin();
		while(counter < idx) {
			i++;
			counter++;
		}
		m_items.erase(i);
	}
}

const ItemList& Inventory::GetItems() {
	return m_items;
}

int Inventory::NumItems() {
	return m_items.size();
}

Item* Inventory::ItemAtIndex(unsigned int idx) {
	if(idx < m_items.size()) {
		unsigned int counter = 0;
		ItemList::iterator i = m_items.begin();
		while(counter < idx) {
			i++;
			counter++;
		}
		return *i;
	}

	return NULL;
}

