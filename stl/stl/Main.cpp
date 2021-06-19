#include "MyList.h"
#include <iostream>

int main() {
	MyList<int> aboba;
	for (int i = 0; i < 4; ++i) {
		aboba.PushBack(i);
	}

	for (auto it = aboba.begin(); it != aboba.end(); ++it) {
		std::cout << *it << std::endl;
	}
}