#pragma once

#include <cstdint>
#include <cmath>

namespace engine {

	template <typename T>
	class Vec2 {
	public:
		T x;
		T y;

		Vec2(T x, T y);
		Vec2();

		double distance() const;
		T distance_squared() const;
		Vec2<double> normalized() const;
		template <typename E>
		Vec2<E> cast() const;
	};

	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;
	using Vec2i = Vec2<int>;
	using Vec2l = Vec2<long>;

	template <typename T>
	Vec2<T>& zero();

	template <typename T>
	Vec2<T>& operator+(const Vec2<T>& vec1, const Vec2<T>& vec2);

	template <typename T>
	Vec2<T>& operator-(const Vec2<T>& vec1, const Vec2<T>& vec2);

	template <typename T>
	Vec2<T>& operator*(const Vec2<T>& vec1, const Vec2<T>& vec2);

	template <typename T>
	Vec2<T>& operator/(const Vec2<T>& vec1, const Vec2<T>& vec2);

	template <typename T>
	bool operator==(const Vec2<T>& vec1, const Vec2<T>& vec2);

	template <typename T>
	Vec2<T>& operator+(const Vec2<T>& vec, T value);

	template <typename T>
	Vec2<T>& operator-(const Vec2<T>& vec, T value);

	template <typename T>
	Vec2<T>& operator*(const Vec2<T>& vec, T value);

	template <typename T>
	Vec2<T>& operator/(const Vec2<T>& vec, T value);

	template<typename T>
	Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}

	template<typename T>
	Vec2<T>::Vec2() : Vec2<T>::Vec2(0, 0) {}

	template<typename T>
	double Vec2<T>::distance() const
	{
		return std::sqrt(distance_squared());
	}

	template<typename T>
	T Vec2<T>::distance_squared() const
	{
		return T(x * x + y * y);
	}

	template<typename T>
	Vec2<double> Vec2<T>::normalized() const
	{
		return this / distance();
	}

	template<typename T>
	Vec2<T>& zero()
	{
		return Vec2<T>();
	}

	template<typename T>
	Vec2<T>& operator+(const Vec2<T>& vec1, const Vec2<T>& vec2)
	{
		return Vec2<T>{ vec1.x + vec2.x, vec1.y + vec2.y };
	}

	template<typename T>
	Vec2<T>& operator-(const Vec2<T>& vec1, const Vec2<T>& vec2)
	{
		return Vec2<T>{ vec1.x - vec2.x, vec1.x - vec2.x };
	}

	template<typename T>
	Vec2<T>& operator*(const Vec2<T>& vec1, const Vec2<T>& vec2)
	{
		return Vec2<T>{ vec1.x* vec2.x, vec1.x* vec2.x };
	}

	template<typename T>
	Vec2<T>& operator/(const Vec2<T>& vec1, const Vec2<T>& vec2)
	{
		return Vec2<T>{ vec1.x / vec2.x, vec1.y / vec2.y };
	}

	template<typename T>
	bool operator==(const Vec2<T>& vec1, const Vec2<T>& vec2)
	{
		return vec1.x == vec2.x && vec1.y == vec2.y;
	}

	template<typename T>
	Vec2<T>& operator+(const Vec2<T>& vec, T value)
	{
		return Vec2<T>{ vec.x + value, vec.y + value };
	}

	template<typename T>
	Vec2<T>& operator-(const Vec2<T>& vec, T value)
	{
		return Vec2<T>{ vec.x - value, vec.y - value };
	}

	template<typename T>
	Vec2<T>& operator*(const Vec2<T>& vec, T value)
	{
		return Vec2<T>{ vec.x* value, vec.y* value };
	}

	template<typename T>
	Vec2<T>& operator/(const Vec2<T>& vec, T value)
	{
		return Vec2<T>{ vec.x / value, vec.y / value };
	}

	template<typename T>
	template<typename E>
	inline Vec2<E> Vec2<T>::cast() const
	{
		return Vec2<E>(E(x), E(y));
	}

}