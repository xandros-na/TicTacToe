#include "position.h"

namespace position {

	/*
	Cool functors!!
	*/
	position::compare::compare(position::Position& position) : m_pos{ position.x, position.y } {}

	bool compare::operator()(Position& position) {
		return m_pos.x == position.x && m_pos.y == position.y;
	}
}