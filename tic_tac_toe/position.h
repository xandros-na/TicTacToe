#pragma once

namespace position {

	struct Position {
		int x;
		int y;
	};

	struct compare {
	public:
		compare(Position& position);
		bool operator()(Position& position);
	private:
		Position m_pos;
	};

}
