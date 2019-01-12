#pragma once
namespace math
{
	const double PI = 3.14159265358979323;
	const double π = PI;
	const double Tau = PI * 2;
	const double RAD_TO_DEG = 1/(PI/180);
	const double DEG_TO_RAD = PI / 180;

	float sqrt(float f);

	float sin(float angle);

	float arcsin(float ratio);

	float cos(float angle);

	float arccos(float ratio);

	struct vec2
	{
		union {
			struct {
				float x, y;
			};
			struct {
				float arr[2];
			};
		};

		vec2();
		vec2(float x, float y);

		float magnitude() const;
		float dot(const vec2 &rhs) const;

		vec2 &normalize();
		vec2 getNormalized() const;

		vec2 &scale(const vec2 &rhs);
		vec2 getScaled(const vec2 &rhs) const;

		vec2 getPerpCW() const;
		vec2 getPerpCCW() const;

		float angleBetween(const vec2 &rhs) const;

		vec2 operator+(const vec2 &rhs) const;
		vec2 operator-(const vec2 &rhs) const;
		vec2 operator*(const float rhs) const;
		friend vec2 operator*(const float lhs, const vec2 &rhs);
		vec2 operator/(const float rhs) const;

		vec2 &operator+=(const vec2 &rhs);
		vec2 &operator-=(const vec2 &rhs);
		vec2 &operator*=(const float rhs);
		vec2 &operator/=(const float rhs);
		vec2 &operator/=(const vec2 rhs);

		bool operator==(const vec2 &rhs) const;
		bool operator!=(const vec2 &rhs) const;

		vec2 operator-() const;

		operator float *();
		operator const float *() const;
	};

	vec2 operator*(const float lhs, const vec2 &rhs);

	class vec3
	{
	public:
		union{
			struct{
				float x, y, z;
			};
			struct{
				float arr[3];
			};
		};

		vec3();
		vec3(float x, float y, float z);

		float magnitude() const;
		float dot(const vec3 &rhs) const;
		vec3 cross(const vec3 &rhs) const;

		vec3 &normalize();
		vec3 getNormalised() const;

		vec3 &scale(const vec3 &rhs);
		vec3 getScaled(const vec3 &rhs) const;

		vec3 operator+(const vec3 &rhs) const;
		vec3 operator-(const vec3 &rhs) const;
		vec3 operator*(const float rhs) const;
		friend vec3 operator*(const float lhs, const vec3 &rhs);
		vec3 operator/(const float rhs) const;

		vec3 &operator+=(const vec3 &rhs);
		vec3 &operator-=(const vec3 &rhs);
		vec3 &operator*=(const float rhs);
		vec3 &operator/=(const float rhs);

		bool operator==(const vec3 &rhs) const;
		bool operator!=(const vec3 &rhs) const;

		vec3 operator-() const;

		operator float *();
		operator const float *() const;
	};

	vec3 operator*(const float lhs, const vec3 &rhs);

	/*class vec4
	{
	public:
		float x, y, z, w;

		vec4();
		vec4(float x, float y, float z, float w);

		float magnitude() const;
		float dot(const vec4 &rhs) const;
		vec4 cross(const vec4 &rhs) const;

		vec4 &normalize();
		vec4 getNormalised() const;

		vec4 &scale(const vec4 &rhs);
		vec4 getScaled(const vec4 &rhs) const;

		vec4 operator+(const vec4 &rhs) const;
		vec4 operator-(const vec4 &rhs) const;
		vec4 operator*(const float rhs) const;
		friend vec4 operator*(const float lhs, const vec4 &rhs);
		vec4 operator/(const float rhs) const;

		vec4 &operator+=(const vec4 &rhs);
		vec4 &operator-=(const vec4 &rhs);
		vec4 &operator*=(const float rhs);
		vec4 &operator/=(const float rhs);

		bool operator==(const vec4 &rhs) const;
		bool operator!=(const vec4 &rhs) const;

		vec4 operator-() const;

		operator float *();
		operator const float *() const;
	};*/

	//vec4 operator*(const float lhs, const vec4 &rhs);


	
	float fmod(float a, float b);
	float min(float a, float b);
	float max(float a, float b);
	float clamp(float a, float lowerBound, float upperBound);
	float abs(float a);
	int pow(int a, int b);
	bool isPowerOfTwo(int a);
	float moveTowards(float current, float target, float maxDelta);
	
	struct mat3
	{
		union
		{
			struct
			{
				vec3 xAxis;
				vec3 yAxis;
				vec3 zAxis;
			};
			vec3 axis[3];
			struct
			{
				float m1, m2, m3,
					m4, m5, m6,
					m7, m8, m9;
			};
			struct
			{
				float m[9];
			};
			struct
			{
				float mm[3][3];
			};
		};

		mat3();
		mat3(float *ptr);
		mat3(float m1, float m2, float m3,
			float m4, float m5, float m6,
			float m7, float m8, float m9);

		static mat3 identity();
		static mat3 translation(float x, float y);
		static mat3 translation(const vec2 &vec);
		static mat3 rotation(float rot);
		static mat3 scale(float xScale, float yScale);

		// rebuild the matrix
		void set(float m1, float m2, float m3,
			float m4, float m5, float m6,
			float m7, float m8, float m9);

		// rebuild the matrix - expects pointer to array of 9 floats
		void set(float *ptr);

		void transpose();
		mat3 getTranspose() const;

		operator float *();
		operator const float *() const;

		vec3 &operator[](const int index);
		const vec3 &operator[](const int index) const;

		mat3  operator*(const mat3 &rhs) const;
		mat3 &operator*=(const mat3 &rhs);

		// transforms a 3D vector by performing 3x3 x 3x1 matrix multiplication
		vec3 operator*(const vec3 &rhs) const;
		// convenience function for transforming a 2D vector
		vec2 operator*(const vec2 &rhs) const;

		bool operator==(const mat3 &rhs) const;
		bool operator!=(const mat3 &rhs) const;
	};

	/*class vec4
	{
		union {
			struct {
				float x, y, z, w;
			};
			struct {
				float arr[4];
			};
		};

		vec4();
		vec4(float x, float y, float z, float w);

		float magnitude() const;
		float dot(const vec4 &rhs) const;
		vec4 cross(const vec4 &rhs) const;

		vec4 &normalize();
		vec4 getNormalised() const;

		vec4 &scale(const vec4 &rhs);
		vec4 getScaled(const vec4 &rhs) const;

		vec4 operator+(const vec4 &rhs) const;
		vec4 operator-(const vec4 &rhs) const;
		vec4 operator*(const float rhs) const;
		friend vec4 operator*(const float lhs, const vec4 &rhs);
		vec4 operator/(const float rhs) const;

		vec4 &operator+=(const vec4 &rhs);
		vec4 &operator-=(const vec4 &rhs);
		vec4 &operator*=(const float rhs);
		vec4 &operator/=(const float rhs);

		bool operator==(const vec4 &rhs) const;
		bool operator!=(const vec4 &rhs) const;

		vec4 operator-() const;

		operator float *();
		operator const float *() const;
	};*/

	//vec4 operator*(const float lhs, const vec4 &rhs);
}

