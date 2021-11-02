#include <iostream>
#include <array>

#include "../include/mouse/mouse.h"
#include "../include/api/api.h"

int main() {
	rwa2::Mouse mouse;
	mouse.display_walls();
	API::setColor(0, 0, 'G');
	API::setText(0, 0, "abc");
}

