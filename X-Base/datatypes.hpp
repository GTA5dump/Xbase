#pragma once
#include "pch.h"
#include "lists.hpp"

using _func = void(*)();
typedef std::unordered_map<uint64_t, uint64_t> nMap;
typedef char* pchar;
typedef std::function<void()> Function;
typedef void* Void;
typedef void* Any;
typedef unsigned int uint;
typedef uint32_t Hash;
typedef uint32_t Entity;
typedef uint32_t Player;
typedef uint32_t FireId;
typedef uint32_t Ped;
typedef uint32_t Vehicle;
typedef uint32_t Cam;
typedef uint32_t CarGenerator;
typedef uint32_t Group;
typedef uint32_t Train;
typedef uint32_t Pickup;
typedef uint32_t Object;
typedef uint32_t Weapon;
typedef uint32_t Interior;
typedef uint32_t Blip;
typedef uint32_t Texture;
typedef uint32_t TextureDict;
typedef uint32_t CoverPoint;
typedef uint32_t Camera;
typedef uint32_t TaskSequence;
typedef uint32_t ColourIndex;
typedef uint32_t Sphere;
typedef uint32_t ScrHandle;

struct twoBytes
{
	BYTE byte[2];
};
struct threeBytes
{
	BYTE byte[3];
};
struct twentyfourBytes
{
	BYTE byte[24];
};

struct Vector3
{
	float x;
	DWORD _paddingx;
	float y;
	DWORD _paddingy;
	float z;
	DWORD _paddingz;

	void Normalize() {
		float length = static_cast<float>(sqrt((x*x) + (y*y) + (z*z)));
		if (length == 0.0f) return;
		float num = 1.0f / length;
		x *= num; y *= num; z *= num;
	}
};

struct Vector3_t
{
	float x, y, z;
	void Normalize() {
		float length = static_cast<float>(sqrt((x*x) + (y*y) + (z*z)));
		if (length == 0.0f) return;
		float num = 1.0f / length;
		x *= num; y *= num; z *= num;
	}
};

struct Vector2
{
	float x, y;
};

struct RGB
{
	int r, g, b;
};

struct RGBA
{
	int r, g, b, a;
};

struct RGBAF
{
	int r, g, b, a, f;
};