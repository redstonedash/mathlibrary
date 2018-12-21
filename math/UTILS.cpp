﻿#include "UTILS.h"
#include <cfloat>
namespace math
{
	bool aprox(float lhs, float rhs) {
		return abs(lhs - rhs) < FLT_EPSILON;
	}

	float sin(float angle) { //SOH: sine = oposite / hyp; hyp = 1;
		if (angle < 0) {
			angle *= -1;
			angle += PI;
		}
		angle = fmod(angle, PI*2);
		bool half = angle >= PI;
		angle = fmod(angle, PI);
		bool sign = angle >= PI/2;
		angle = fmod(angle, PI/2);
		double tempAngle = PI / 2; //quarter rotation
		vec2 point = vec2(0, 0);
		vec2 CWBound = vec2(0, 1);
		vec2 CCWBound = vec2(1, 0);
		float angleUpperBound = PI / 2;
		float angleLowerBound = 0;
		if (aprox(angle, angleUpperBound)) {
			point = CCWBound;
			return -((!half) ? ((sign) ? -point.y : -point.x) : ((sign) ? point.y : point.x));
		}
		if (aprox(angle,angleLowerBound)) {
			point = CWBound;
			return -((!half) ? ((sign) ? -point.y : -point.x) : ((sign) ? point.y : point.x));
		}
		for (int i = 0; i < 100; i++) { //50 should be more than good enough
			point = ((CWBound + CCWBound) ).getNormalized();
			tempAngle = (angleUpperBound + angleLowerBound) / 2;
			if (tempAngle == angle) {
				break;
			}
			if (tempAngle>angle) {
				angleUpperBound = tempAngle;
				CCWBound = point;
			}
			else {
				angleLowerBound = tempAngle;
				CWBound = point;
			}
		}
		point = ((CWBound + CCWBound) ).getNormalized();
		return -((!half) ? ( (sign) ? -point.y : -point.x )  : ((sign) ? point.y : point.x));
	}

	float cos(float angle) {
		return(sin(angle - PI / 2));
	}

	float arcsin(float ratio) {
		bool sign = false;
		if(ratio < 0){
			sign = true;
			ratio *= -1;
		}
		ratio = clamp(ratio, 0, 1);
		float averageAngle;
		float CWBound = -PI / 2;
		averageAngle = CWBound;

		{
			float tempRatio = sin(averageAngle);
			if (aprox(tempRatio,ratio)) {
				if (sign) {
					averageAngle *= -1;
				}
				return(averageAngle);
			}
		}
		float CCWBound = PI / 2;

		averageAngle = CCWBound;

		{
			float tempRatio = sin(averageAngle);
			if (aprox(tempRatio, ratio)) {
				if (sign) {
					averageAngle *= -1;
				}
				return(averageAngle);
			}
		}

		for (int i = 0; i < 50; i++)//50 itterations should be more than accurate enough
		{
			averageAngle = (CCWBound + CWBound) / 2;
			float tempRatio = sin(averageAngle);
			if (aprox(tempRatio, ratio)) {
				if (sign) {
					averageAngle *= -1;
				}
				return(averageAngle);
			} else if (tempRatio > ratio) {
				CCWBound = averageAngle;
			} else {
				CWBound = averageAngle;
			}
		}
		if (sign) {
			averageAngle *= -1;
		}
		return(averageAngle);
	}

	float arccos(float ratio) {
		return PI/2 - arcsin(ratio);
	}

	vec2 operator*(const float lhs, const vec2 & rhs)
	{
		return vec2(lhs*rhs.x, lhs*rhs.y);
	}

	vec3 operator*(const float lhs, const vec3 & rhs)
	{
		lh
		return vec3();
	}

	float vec2::angleBetween(const vec2 &rhs)const {
		return arccos(this->dot(rhs) / (this->magnitude()*rhs.magnitude()));
	}

	float min(float a, float b) {
		return (a < b) ? (a) : (b);
	}

	float max(float a, float b) {
		return (a > b) ? (a) : (b);
	}

	float clamp(float a, float lowerBound, float upperBound) {
		return min(max(a, lowerBound), upperBound);
	}

	float abs(float a) {
		return max(a, -a);
	}
	int pow(int a, int b)
	{
		int temp = 1;
		for (int i = 0; i < b; i++) {
			temp*=a;
		}
		return temp;
	}

	unsigned int countSetBits(int a)
	{
		unsigned int count = 0;
		while (a)
		{
			a &= (a - 1);
			count++;
		}
		return count;
	}

	bool isPowerOfTwo(int a)
	{
		return (a > 0 && ((a & (a - 1)) == 0));
	}

	float moveTowards(float current, float target, float maxDelta)
	{
		float tempCurrent = current;
		if (current == target) {
			return target;
		}
		if (current > target) {
			maxDelta *= -1;
		}
		current += maxDelta;
		if (target < max(tempCurrent,current) && target > min(tempCurrent, current)) {
			return target;
		}
		return current;
	}

	vec2::vec2()
	{
	}

	vec2::vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float vec2::magnitude() const
	{
		return math::sqrt(this->x*this->x + this->y*this->y);
	}

	float vec2::dot(const vec2 & rhs) const
	{
		return this->x * rhs.x + this->y * rhs.y;
	}

	vec2 & vec2::normalize()
	{
		*this /= this->magnitude();
		return *this;
	}

	vec2 vec2::getNormalized() const
	{
		vec2 vec = *this;
		vec.normalize();
		return vec;
	}

	vec2 & vec2::scale(const vec2 & rhs){
		this->x *= rhs.x;
		this->y *= rhs.y;
		return *this;
	}

	vec2 vec2::getScaled(const vec2 & rhs) const
	{
		vec2 vec = *this;
		vec.scale(rhs);
		return vec;
	}

	vec2 vec2::getPerpCW() const
	{
		vec2 vec = *this;
		vec.x = this->y;
		vec.y = -this->x;
		return vec;
	}

	vec2 vec2::getPerpCCW() const
	{
		vec2 vec = *this;
		vec.x = -this->y;
		vec.y = this->x;
		return vec;
	}
	float fmod(const float num, const float deno) {
		int x = num / deno;
		return num - x*deno;
	}

	float sqrt(float f)
	{
		float upperBound = f;
		float lowerBound = 0;
		float tempSqrt = f / 2;
		float ans = tempSqrt*tempSqrt;
		if (f < 0)
			throw "undefined squareRoot";
		for(int i = 0; i < 35; i++) {
			if (ans > f) {
				upperBound = tempSqrt;
				tempSqrt = (upperBound + lowerBound) / 2;
			}else if (ans < f) {
				lowerBound = tempSqrt;
				tempSqrt = (upperBound + lowerBound) / 2;
			}
			ans = tempSqrt * tempSqrt;
		}
		return tempSqrt;
	}

	vec2 & vec2::operator/=(const float rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}

	vec2 & vec2::operator/=(const vec2 rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		return *this;
	}

	bool vec2::operator==(const vec2 & rhs) const
	{
		return
			aprox(this->x, rhs.x) &&
			aprox(this->y, rhs.y);
		
	}

	bool vec2::operator!=(const vec2 & rhs) const
	{
		return !(*this == rhs);
	}

	vec2 vec2::operator-() const
	{
		return vec2(-this->x,-this->y);
	}


	vec2::operator float*()
	{
		return &this->x;
	}
	vec2::operator const float*() const
	{
		return &this->x;
	}
	vec2 vec2::operator+(const vec2 & rhs) const
	{
		return vec2(rhs.x+this->x, rhs.y+this->y);
	}

	vec2 vec2::operator-(const vec2 & rhs) const
	{
		return vec2(this->x-rhs.x,this->y-rhs.y);
	}

	vec2 vec2::operator*(const float rhs) const
	{
		return vec2(this->x * rhs, this->y * rhs);
	}

	vec2 vec2::operator/(const float rhs) const
	{
		return vec2(this->x/rhs, this->y/rhs);
	}

	vec2 & vec2::operator+=(const vec2 & rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	vec2 & vec2::operator-=(const vec2 & rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	vec2 & vec2::operator*=(const float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}

	vec3::vec3()
	{
	}

	vec3::vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float vec3::magnitude() const
	{
		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	}

	float vec3::dot(const vec3 & rhs) const
	{
		return (this->x*rhs.x + this->y*rhs.y + this->z*rhs.z);
	}

	vec3 vec3::cross(const vec3 & rhs) const
	{
		return vec3(this->y * rhs.z - this->z * rhs.y, this->x * rhs.z - this->z * rhs.x, this->x * rhs.z - this->z * rhs.x);
	}

	vec3 & vec3::normalize()
	{
		*this /= this->magnitude();
		return *this;
	}

	vec3 vec3::getNormalised() const
	{
		return *this/this->magnitude();
	}

	vec3 & vec3::scale(const vec3 & rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		return *this;
	}

	vec3 vec3::getScaled(const vec3 & rhs) const
	{
		return ;
	}

	vec3 vec3::operator+(const vec3 & rhs) const
	{
		return vec3(this->x+rhs.x, this->y + rhs.y, this->z + rhs.z);
	}

	vec3 vec3::operator-(const vec3 & rhs) const
	{
		return vec3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
	}

	vec3 vec3::operator*(const float rhs) const
	{
		return vec3(this->x * rhs, this->y * rhs, this->z * rhs);
	}

	vec3 vec3::operator/(const float rhs) const
	{
		return vec3(this->x/rhs, this->y/rhs, this->z/rhs);
	}

	/*
	float pow(float a, float b){
		float temp;
		if (b == 0)
			return 1;
		temp = pow(a, b / 2);
		if (b % 2 == 0)
			return temp * temp;
		else
		{
			if (b > 0)
				return a * temp*temp;
			else
				return (temp*temp) / b;
		}
	}(*/
}