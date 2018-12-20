#include <iostream>
#include "UTILS.h"
#include <cassert>
#include <cfloat>
int main() {
	assert(math::abs(-5) == 5);       // the abs value of -5 is 5
	assert(math::pow(2, 2) == 4);      // 2 to the power of 2 is 4
	assert(math::min(-5, 5) == -5);   // the lesser of these two values is -5
	assert(!math::isPowerOfTwo(3));
	assert(math::isPowerOfTwo(64));
	assert(math::isPowerOfTwo(32));
	assert(!math::isPowerOfTwo(0));
	assert(math::moveTowards(0, 10, 5) == 5);
	assert(math::moveTowards(0, -10, 5) == -5);
	assert(math::moveTowards(0, 10, 50) == 10);
	assert(math::moveTowards(0, -10, 50) == -10);
	assert(math::moveTowards(2, 10, 5) == 7);
	assert(math::moveTowards(2, -10, 5) == -3);
	assert(math::moveTowards(2, 10, 50) == 10);
	assert(math::moveTowards(2, -10, 50) == -10);
	assert(math::sqrt(64) == 8);
	math::vec2 alpha = math::vec2(1, 0);
	math::vec2 bravo = math::vec2(0, 1);
	math::vec2 charlie = math::vec2(-1, 0);
	assert(alpha.dot(bravo) == 0);
	assert(bravo.dot(alpha) == 0);
	assert(charlie.dot(alpha) == -1);
	assert(alpha.dot(charlie) == -1);
	alpha = math::vec2(86, 0);
	bravo = math::vec2(0, 22);
	charlie = math::vec2(-11, 0);
	math::vec2 delta = math::vec2(10, 10);
	math::vec2 echo = math::vec2(21, 21);
	math::vec2 foxtroat = math::vec2(21, 21);
	delta.normalize();
	echo.normalize();
	assert(delta == echo);
	assert(echo == foxtroat.getNormalized());
	assert(foxtroat == math::vec2(21, 21));
	assert(foxtroat != delta);
	assert(math::vec2(1, 1).scale(math::vec2(-40, 40)) == math::vec2(-40, 40));
	assert(math::fmod(5.5, 3)==2.5);
	std::cout << math::arcsin(0.5f ) << "\n";
	std::cout << math::arcsin(0.2f ) << "\n";
	std::cout << math::arcsin(1    ) << "\n";
	std::cout << math::arcsin(-0.5f) << "\n";
	std::cout << math::arcsin(-0.2f) << "\n";
	std::cout << math::arcsin(-1   ) << "\n";
	assert(math::abs(math::sin(0.5f) - 0.4794255386f) < FLT_EPSILON*10);
	math::vec2 golf(0, -1);
	math::vec2 Hotel(0, -1);
	std::cout << golf.angleBetween(Hotel);
	return 0;
}