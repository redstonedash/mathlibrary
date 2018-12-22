#include <iostream>
#include "UTILS.h"
#include <cassert>
#include <cfloat>
#include <string>
#define TEST(a,b,c) std::cout<<"TEST: " << a << " " << (( b == c) ? ("[PASS]") : ("[FAIL]")) << "\n"; 
#define Vector2 math::vec2
#define Vector3 math::vec3
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
	std::cout << golf.angleBetween(Hotel) << "\n";
	math::vec2 v2a(13.5f, -48.23f), v2b(5, 3.99f), v2c;
	v2c = v2a + v2b;
	math::vec3 v3a(13.5f, -48.23f, 862), v3b(5, 3.99f, -12), v3c;
	v3c = v3a + v3b;

	std::cout << v2c.x << " " << v2c.y << "\n";
	std::cout << 18.5f << " " << -44.24f << "\n";

	TEST("vec2 addition", v2c, math::vec2(18.5f, -44.24f));
	TEST("vec3 addition", v3c, math::vec3(18.5f, -44.24f, 850));

	v2a = math::vec2(13.5f, -48.23f);
	v2b = math::vec2(5, 3.99f);
	v2c = v2a - v2b;
	v3a = math::vec3(13.5f, -48.23f, 862);
	v3b = math::vec3(5, 3.99f, -12);
	v3c = v3a - v3b;
	TEST("Vector2 subtraction", v2c, math::vec2(8.5f, -52.22f));
	TEST("Vector3 subtraction", v3c, math::vec3(8.5f, -52.22f, 874));
	v2a = math::vec2(13.5f, -48.23f);
	v2c = v2a * 2.482f;
	v3a = math::vec3(13.5f, -48.23f, 862);
	v3c = v3a * 0.256f;
	TEST("Vector2 post-scale", v2c, math::vec2(33.5069999695f, -119.706863403f));
	TEST("Vector3 post-scale", v3c, math::vec3(3.45600008965f, -12.3468809128f, 220.672012329f));
	v2a = Vector2(13.5f, -48.23f);
	v2c = 2.482f * v2a;
	v3a = Vector3(13.5f, -48.23f, 862);
	v3c = 0.256f * v3a;
	TEST("Vector2 pre-scale", v2c, Vector2(33.5069999695f, -119.706863403f));
	TEST("Vector3 pre-scale", v3c, Vector3(3.45600008965f, -12.3468809128f, 220.672012329f));
	v2a = Vector2(13.5f, -48.23f);
	v2b = Vector2(5, 3.99f);
	float dot2 = v2a.dot(v2b);
	v3a = Vector3(13.5f, -48.23f, 862);
	v3b = Vector3(5, 3.99f, -12);
	float dot3 = v3a.dot(v3b);

	TEST("Vector2 dot", dot2, -124.937698364f);
	TEST("Vector3 dot", dot3, -10468.9375f);

	v3a = Vector3(13.5f, -48.23f, 862);
	v3b = Vector3(5, 3.99f, -12);
	v3c = v3a.cross(v3b);

	TEST("Vector3 cross", v3c, Vector3(-2860.62011719f, 4472.00000000f, 295.01498413f));

	// vector magnitude
	v2a = Vector2(13.5f, -48.23f);
	float mag2 = v2a.magnitude();
	v3a = Vector3(13.5f, -48.23f, 862);
	float mag3 = v3a.magnitude();

	std::cout << std::to_string(mag2) << "\n";
	TEST("Vector2 magnitude", mag2, 50.0837593079f);
	TEST("Vector3 magnitude", mag3, 863.453735352f);

	v2a = Vector2(-13.5f, -48.23f);
	v2a.normalize();
	v3a = Vector3(13.5f, -48.23f, 862);
	v3a.normalize();

	TEST("Vector2 normalize", v2a, Vector2(-0.269548f, -0.962987f));
	TEST("Vector3 normalize", v3a, Vector3(0.0156349f, -0.0558571f, 0.998316f));
	math::mat3 india = math::mat3(
		1,2,3,
		4,5,6,
		7,8,9);
	math::mat3 julliet = math::mat3(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	);
	TEST("matrix multiplication with idnetity", india, india*julliet)
	return 0;
}