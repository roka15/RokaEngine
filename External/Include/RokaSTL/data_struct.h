#pragma once
#include "CommonInclude.h"


//struct ImVec2;
//struct ImVec4;
//
//struct Vector2;
//struct Vector4;
//struct Matrix;
//struct Quaternion;
//struct Plane;
//
//struct Vector2 : public XMFLOAT2
//{
//	Vector2() noexcept : XMFLOAT2(0.f, 0.f) {}
//	XM_CONSTEXPR explicit Vector2(float x) : XMFLOAT2(x, x) {}
//	XM_CONSTEXPR Vector2(float _x, float _y) : XMFLOAT2(_x, _y) {}
//	XM_CONSTEXPR Vector2(int _x, int _y) : XMFLOAT2((float)_x, (float)_y) {}
//	XM_CONSTEXPR Vector2(UINT _x, UINT _y) : XMFLOAT2((float)_x, (float)_y) {}
//	explicit Vector2(_In_reads_(2) const float* pArray) : XMFLOAT2(pArray) {}
//	Vector2(FXMVECTOR V) { XMStoreFloat2(this, V); }
//	Vector2(const XMFLOAT2& V) { this->x = V.x; this->y = V.y; }
//	explicit Vector2(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; }
//
//	Vector2(const Vector2&) = default;
//	Vector2& operator=(const Vector2&) = default;
//	Vector2& operator =(FXMVECTOR V) { XMStoreFloat2(this, V); return *this; }
//	Vector2& operator = (const ImVec2 & _imv2);
//
//	Vector2(Vector2&&) = default;
//	Vector2& operator=(Vector2&&) = default;
//
//	operator XMVECTOR() const { return XMLoadFloat2(this); }
//
//
//	// Conversion
//	operator ImVec2() const;
//
//	// Comparison operators
//	bool operator == (const Vector2 & V) const;
//	bool operator != (const Vector2 & V) const;
//
//	// Assignment operators
//	Vector2& operator= (const XMVECTORF32 & F) { x = F.f[0]; y = F.f[1]; return *this; }
//	Vector2& operator+= (const Vector2 & V);
//	Vector2& operator+= (float _f);
//	Vector2& operator-= (const Vector2 & V);
//	Vector2& operator-= (float _f);
//	Vector2& operator*= (const Vector2 & V);
//	Vector2& operator*= (float S);
//	Vector2& operator/= (float S);
//	Vector2& operator/= (const Vector2 & V);
//
//	// Unary operators
//	Vector2 operator+ () const { return *this; }
//	Vector2 operator- () const { return Vector2(-x, -y); }
//
//	// Vector operations
//	bool InBounds(const Vector2 & Bounds) const;
//
//	float Length() const;
//	float LengthSquared() const;
//
//	float Dot(const Vector2 & V) const;
//	void Cross(const Vector2 & V, Vector2 & result) const;
//	Vector2 Cross(const Vector2 & V) const;
//
//	void Normalize();
//	void Normalize(Vector2 & result) const;
//
//	void Clamp(const Vector2 & vmin, const Vector2 & vmax);
//	void Clamp(const Vector2 & vmin, const Vector2 & vmax, Vector2 & result) const;
//
//	// Static functions
//	static float Distance(const Vector2 & v1, const Vector2 & v2);
//	static float DistanceSquared(const Vector2 & v1, const Vector2 & v2);
//
//	static void Min(const Vector2 & v1, const Vector2 & v2, Vector2 & result);
//	static Vector2 Min(const Vector2 & v1, const Vector2 & v2);
//
//	static void Max(const Vector2 & v1, const Vector2 & v2, Vector2 & result);
//	static Vector2 Max(const Vector2 & v1, const Vector2 & v2);
//
//	static void Lerp(const Vector2 & v1, const Vector2 & v2, float t, Vector2 & result);
//	static Vector2 Lerp(const Vector2 & v1, const Vector2 & v2, float t);
//
//	static void SmoothStep(const Vector2 & v1, const Vector2 & v2, float t, Vector2 & result);
//	static Vector2 SmoothStep(const Vector2 & v1, const Vector2 & v2, float t);
//
//	static void Barycentric(const Vector2 & v1, const Vector2 & v2, const Vector2 & v3, float f, float g, Vector2 & result);
//	static Vector2 Barycentric(const Vector2 & v1, const Vector2 & v2, const Vector2 & v3, float f, float g);
//
//	static void CatmullRom(const Vector2 & v1, const Vector2 & v2, const Vector2 & v3, const Vector2 & v4, float t, Vector2 & result);
//	static Vector2 CatmullRom(const Vector2 & v1, const Vector2 & v2, const Vector2 & v3, const Vector2 & v4, float t);
//
//	static void Hermite(const Vector2 & v1, const Vector2 & t1, const Vector2 & v2, const Vector2 & t2, float t, Vector2 & result);
//	static Vector2 Hermite(const Vector2 & v1, const Vector2 & t1, const Vector2 & v2, const Vector2 & t2, float t);
//
//	static void Reflect(const Vector2 & ivec, const Vector2 & nvec, Vector2 & result);
//	static Vector2 Reflect(const Vector2 & ivec, const Vector2 & nvec);
//
//	static void Refract(const Vector2 & ivec, const Vector2 & nvec, float refractionIndex, Vector2 & result);
//	static Vector2 Refract(const Vector2 & ivec, const Vector2 & nvec, float refractionIndex);
//
//	static void Transform(const Vector2 & v, const Quaternion & quat, Vector2 & result);
//	static Vector2 Transform(const Vector2 & v, const Quaternion & quat);
//
//	static void Transform(const Vector2 & v, const Matrix & m, Vector2 & result);
//	static Vector2 Transform(const Vector2 & v, const Matrix & m);
//	static void Transform(_In_reads_(count) const Vector2 * varray, size_t count, const Matrix & m, _Out_writes_(count) Vector2 * resultArray);
//
//	static void Transform(const Vector2 & v, const Matrix & m, Vector4 & result);
//	static void Transform(_In_reads_(count) const Vector2 * varray, size_t count, const Matrix & m, _Out_writes_(count) Vector4 * resultArray);
//
//	static void TransformNormal(const Vector2 & v, const Matrix & m, Vector2 & result);
//	static Vector2 TransformNormal(const Vector2 & v, const Matrix & m);
//	static void TransformNormal(_In_reads_(count) const Vector2 * varray, size_t count, const Matrix & m, _Out_writes_(count) Vector2 * resultArray);
//
//	// Constants
//	static const Vector2 Zero;
//	static const Vector2 One;
//	static const Vector2 UnitX;
//	static const Vector2 UnitY;
//};
//// Binary operators
//Vector2 operator+ (const Vector2& V1, const Vector2& V2);
//Vector2 operator- (const Vector2& V1, const Vector2& V2);
//Vector2 operator* (const Vector2& V1, const Vector2& V2);
//Vector2 operator* (const Vector2& V, float S);
//Vector2 operator/ (const Vector2& V1, const Vector2& V2);
//Vector2 operator* (float S, const Vector2& V);
//
//struct Vector3 : public XMFLOAT3
//{
//
//	Vector3() noexcept : XMFLOAT3(0.f, 0.f, 0.f) {}
//	XM_CONSTEXPR explicit Vector3(float x) : XMFLOAT3(x, x, x) {}
//	XM_CONSTEXPR Vector3(float _x, float _y, float _z) : XMFLOAT3(_x, _y, _z) {}
//	explicit Vector3(_In_reads_(3) const float* pArray) : XMFLOAT3(pArray) {}
//	Vector3(FXMVECTOR V) { XMStoreFloat3(this, V); }
//	Vector3(const XMFLOAT3& V) { this->x = V.x; this->y = V.y; this->z = V.z; }
//	explicit Vector3(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; }
//
//	Vector3(const Vector3&) = default;
//	Vector3& operator=(const Vector3&) = default;
//
//	Vector3(Vector3&&) = default;
//	Vector3& operator=(Vector3&&) = default;
//
//
//	Vector2 XY() { return Vector2(x, y); }
//	operator XMVECTOR() const { return XMLoadFloat3(this); }
//
//	typedef float(&f3)[3];
//	operator f3() const { return (f3)x; }
//
//
//	// Comparison operators
//	bool operator == (const Vector3 & V) const;
//	bool operator != (const Vector3 & V) const;
//
//	float& operator[](int _iIdx)
//	{
//		return *((float*)this + _iIdx);
//	}
//
//	// Assignment operators
//	Vector3& operator= (const XMVECTORF32 & F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; return *this; }
//	Vector3& operator+= (const Vector3 & V);
//	Vector3& operator-= (const Vector3 & V);
//	Vector3& operator*= (const Vector3 & V);
//	Vector3& operator*= (float S);
//	Vector3& operator/= (float S);
//
//	// Unary operators
//	Vector3 operator+ () const { return *this; }
//	Vector3 operator- () const;
//
//	// Vector operations
//	bool InBounds(const Vector3 & Bounds) const;
//
//	float Length() const;
//	float LengthSquared() const;
//
//	float Dot(const Vector3 & V) const;
//	void Cross(const Vector3 & V, Vector3 & result) const;
//	Vector3 Cross(const Vector3 & V) const;
//
//	Vector3& Normalize();
//	void Normalize(Vector3 & result) const;
//
//	void ToDegree();
//	void ToRadian();
//
//	void Clamp(const Vector3 & vmin, const Vector3 & vmax);
//	void Clamp(const Vector3 & vmin, const Vector3 & vmax, Vector3 & result) const;
//
//	// Static functions
//	static float Distance(const Vector3 & v1, const Vector3 & v2);
//	static float DistanceSquared(const Vector3 & v1, const Vector3 & v2);
//
//	static void Min(const Vector3 & v1, const Vector3 & v2, Vector3 & result);
//	static Vector3 Min(const Vector3 & v1, const Vector3 & v2);
//
//	static void Max(const Vector3 & v1, const Vector3 & v2, Vector3 & result);
//	static Vector3 Max(const Vector3 & v1, const Vector3 & v2);
//
//	static void Lerp(const Vector3 & v1, const Vector3 & v2, float t, Vector3 & result);
//	static Vector3 Lerp(const Vector3 & v1, const Vector3 & v2, float t);
//
//	static void SmoothStep(const Vector3 & v1, const Vector3 & v2, float t, Vector3 & result);
//	static Vector3 SmoothStep(const Vector3 & v1, const Vector3 & v2, float t);
//
//	static void Barycentric(const Vector3 & v1, const Vector3 & v2, const Vector3 & v3, float f, float g, Vector3 & result);
//	static Vector3 Barycentric(const Vector3 & v1, const Vector3 & v2, const Vector3 & v3, float f, float g);
//
//	static void CatmullRom(const Vector3 & v1, const Vector3 & v2, const Vector3 & v3, const Vector3 & v4, float t, Vector3 & result);
//	static Vector3 CatmullRom(const Vector3 & v1, const Vector3 & v2, const Vector3 & v3, const Vector3 & v4, float t);
//
//	static void Hermite(const Vector3 & v1, const Vector3 & t1, const Vector3 & v2, const Vector3 & t2, float t, Vector3 & result);
//	static Vector3 Hermite(const Vector3 & v1, const Vector3 & t1, const Vector3 & v2, const Vector3 & t2, float t);
//
//	static void Reflect(const Vector3 & ivec, const Vector3 & nvec, Vector3 & result);
//	static Vector3 Reflect(const Vector3 & ivec, const Vector3 & nvec);
//
//	static void Refract(const Vector3 & ivec, const Vector3 & nvec, float refractionIndex, Vector3 & result);
//	static Vector3 Refract(const Vector3 & ivec, const Vector3 & nvec, float refractionIndex);
//
//	static void Transform(const Vector3 & v, const Quaternion & quat, Vector3 & result);
//	static Vector3 Transform(const Vector3 & v, const Quaternion & quat);
//
//	static void Transform(const Vector3 & v, const Matrix & m, Vector3 & result);
//	static Vector3 Transform(const Vector3 & v, const Matrix & m);
//	static void Transform(_In_reads_(count) const Vector3 * varray, size_t count, const Matrix & m, _Out_writes_(count) Vector3 * resultArray);
//
//	static void Transform(const Vector3 & v, const Matrix & m, Vector4 & result);
//	static void Transform(_In_reads_(count) const Vector3 * varray, size_t count, const Matrix & m, _Out_writes_(count) Vector4 * resultArray);
//
//	static void TransformNormal(const Vector3 & v, const Matrix & m, Vector3 & result);
//	static Vector3 TransformNormal(const Vector3 & v, const Matrix & m);
//	static void TransformNormal(_In_reads_(count) const Vector3 * varray, size_t count, const Matrix & m, _Out_writes_(count) Vector3 * resultArray);
//
//	// Constants
//	static const Vector3 Zero;
//	static const Vector3 One;
//	static const Vector3 UnitX;
//	static const Vector3 UnitY;
//	static const Vector3 UnitZ;
//	static const Vector3 Up;
//	static const Vector3 Down;
//	static const Vector3 Right;
//	static const Vector3 Left;
//	static const Vector3 Forward;
//	static const Vector3 Front;
//	static const Vector3 Backward;
//};
//
//// Binary operators
//Vector3 operator+ (const Vector3& V1, const Vector3& V2);
//Vector3 operator- (const Vector3& V1, const Vector3& V2);
//Vector3 operator* (const Vector3& V1, const Vector3& V2);
//Vector3 operator* (const Vector3& V, float S);
//Vector3 operator/ (const Vector3& V1, const Vector3& V2);
//Vector3 operator* (float S, const Vector3& V);
//
//struct Vector4 : public XMFLOAT4
//{
//	Vector4() noexcept : XMFLOAT4(0.f, 0.f, 0.f, 0.f) {}
//	XM_CONSTEXPR explicit Vector4(float x) : XMFLOAT4(x, x, x, x) {}
//	XM_CONSTEXPR Vector4(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
//	explicit Vector4(_In_reads_(4) const float* pArray) : XMFLOAT4(pArray) {}
//	Vector4(FXMVECTOR V) { XMStoreFloat4(this, V); }
//	Vector4(const XMFLOAT4& V) { this->x = V.x; this->y = V.y; this->z = V.z; this->w = V.w; }
//	explicit Vector4(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }
//
//	Vector4(const Vector4&) = default;
//	Vector4(const Vector3 & vec3, float _w)
//		: XMFLOAT4(vec3.x, vec3.y, vec3.z, _w)
//	{}
//
//	Vector4& operator=(const Vector4&) = default;
//	Vector4& operator=(FXMVECTOR _v) { XMStoreFloat4(this, _v); return *this; }
//	Vector4& operator=(const ImVec4 & _v);
//
//	Vector4(Vector4&&) = default;
//	Vector4& operator=(Vector4&&) = default;
//
//	// Conversion
//	operator XMVECTOR() const { return XMLoadFloat4(this); }
//
//	typedef float(&float4)[4];
//	operator float4() const { return (float4)x; }
//
//	operator ImVec4() const;
//
//
//	// Comparison operators
//	bool operator == (const Vector4 & V) const;
//	bool operator != (const Vector4 & V) const;
//
//	// Assignment operators
//	Vector4& operator= (const XMVECTORF32 & F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }
//	Vector4& operator+= (const Vector4 & V);
//	Vector4& operator-= (const Vector4 & V);
//	Vector4& operator*= (const Vector4 & V);
//	Vector4& operator*= (float S);
//	Vector4& operator/= (float S);
//	Vector4& operator = (const Vector3 _vec3) { x = _vec3.x; y = _vec3.y; z = _vec3.z; return *this; }
//
//
//	// Unary operators
//	Vector4 operator+ () const { return *this; }
//	Vector4 operator- () const;
//	operator Vector3 () { return Vector3(x, y, z); }
//
//
//	// Vector operations
//	bool InBounds(const Vector4 & Bounds) const;
//
//	float Length() const;
//	float LengthSquared() const;
//
//	float Dot(const Vector4 & V) const;
//	void Cross(const Vector4 & v1, const Vector4 & v2, Vector4 & result) const;
//	Vector4 Cross(const Vector4 & v1, const Vector4 & v2) const;
//
//	void Normalize();
//	void Normalize(Vector4 & result) const;
//
//	void Clamp(const Vector4 & vmin, const Vector4 & vmax);
//	void Clamp(const Vector4 & vmin, const Vector4 & vmax, Vector4 & result) const;
//
//	// Static functions
//	static float Distance(const Vector4 & v1, const Vector4 & v2);
//	static float DistanceSquared(const Vector4 & v1, const Vector4 & v2);
//
//	static void Min(const Vector4 & v1, const Vector4 & v2, Vector4 & result);
//	static Vector4 Min(const Vector4 & v1, const Vector4 & v2);
//
//	static void Max(const Vector4 & v1, const Vector4 & v2, Vector4 & result);
//	static Vector4 Max(const Vector4 & v1, const Vector4 & v2);
//
//	static void Lerp(const Vector4 & v1, const Vector4 & v2, float t, Vector4 & result);
//	static Vector4 Lerp(const Vector4 & v1, const Vector4 & v2, float t);
//
//	static void SmoothStep(const Vector4 & v1, const Vector4 & v2, float t, Vector4 & result);
//	static Vector4 SmoothStep(const Vector4 & v1, const Vector4 & v2, float t);
//
//	static void Barycentric(const Vector4 & v1, const Vector4 & v2, const Vector4 & v3, float f, float g, Vector4 & result);
//	static Vector4 Barycentric(const Vector4 & v1, const Vector4 & v2, const Vector4 & v3, float f, float g);
//
//	static void CatmullRom(const Vector4 & v1, const Vector4 & v2, const Vector4 & v3, const Vector4 & v4, float t, Vector4 & result);
//	static Vector4 CatmullRom(const Vector4 & v1, const Vector4 & v2, const Vector4 & v3, const Vector4 & v4, float t);
//
//	static void Hermite(const Vector4 & v1, const Vector4 & t1, const Vector4 & v2, const Vector4 & t2, float t, Vector4 & result);
//	static Vector4 Hermite(const Vector4 & v1, const Vector4 & t1, const Vector4 & v2, const Vector4 & t2, float t);
//
//	static void Reflect(const Vector4 & ivec, const Vector4 & nvec, Vector4 & result);
//	static Vector4 Reflect(const Vector4 & ivec, const Vector4 & nvec);
//
//	static void Refract(const Vector4 & ivec, const Vector4 & nvec, float refractionIndex, Vector4 & result);
//	static Vector4 Refract(const Vector4 & ivec, const Vector4 & nvec, float refractionIndex);
//
//	static void Transform(const Vector2 & v, const Quaternion & quat, Vector4 & result);
//	static Vector4 Transform(const Vector2 & v, const Quaternion & quat);
//
//	static void Transform(const Vector3 & v, const Quaternion & quat, Vector4 & result);
//	static Vector4 Transform(const Vector3 & v, const Quaternion & quat);
//
//	static void Transform(const Vector4 & v, const Quaternion & quat, Vector4 & result);
//	static Vector4 Transform(const Vector4 & v, const Quaternion & quat);
//
//	static void Transform(const Vector4 & v, const Matrix & m, Vector4 & result);
//	static Vector4 Transform(const Vector4 & v, const Matrix & m);
//	static void Transform(_In_reads_(count) const Vector4 * varray, size_t count, const Matrix & m, _Out_writes_(count) Vector4 * resultArray);
//
//	// Constants
//	static const Vector4 Zero;
//	static const Vector4 One;
//	static const Vector4 UnitX;
//	static const Vector4 UnitY;
//	static const Vector4 UnitZ;
//	static const Vector4 UnitW;
//};