#include "MyList.h"
#include <iostream>

int main() {
	MyList<int> aboba;
	for (int i = 0; i < 4; ++i) {
		aboba.PushBack(i);
	}

	MyList<int> amogus(aboba);
	for (auto it = amogus.begin(); it != amogus.end(); ++it) {
		std::cout << it->value << std::endl;
	}
}