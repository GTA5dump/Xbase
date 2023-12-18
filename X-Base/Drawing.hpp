#pragma once
#include "pch.h"

class Drawing
{
public:
	explicit Drawing() { };
	~Drawing() { }

	inline void Text(const char * text, RGBAF rgbaf, Vector2 position, Vector2 size, bool center, bool rightAlign = false, bool outline = false)
	{
		HUD::SET_TEXT_CENTRE(center);
		HUD::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
		HUD::SET_TEXT_FONT(rgbaf.f);
		HUD::SET_TEXT_SCALE(size.x, size.y);
		if (outline) {
			HUD::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
			HUD::SET_TEXT_EDGE(1, 0, 0, 0, 0);
			HUD::SET_TEXT_OUTLINE();
		}
		if (rightAlign) {
			HUD::SET_TEXT_RIGHT_JUSTIFY(TRUE);
			HUD::SET_TEXT_WRAP(position.x, position.x + 0.085f);
		}
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, 0);
	}

	inline void Frame(const char* filename, const char* picturename, int frame, float x, float y, float width, float height, float rotation)
	{
		Drawing::Spriter(filename, (char*)("picturename" , " (" , frame , ")"), x, y, width, height, rotation, 255, 255, 255, 255);
	}


	inline void Spriter(const char* filename, const char* picturename, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(filename))
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(filename, false);
		else
			GRAPHICS::DRAW_SPRITE(filename,picturename, x, y, width, height, rotation, r, g, b, a);
	}

	inline void Rect(RGBA rgba, Vector2 position, Vector2 size)
	{
		GRAPHICS::DRAW_RECT(position.x, position.y, size.x, size.y, rgba.r, rgba.g, rgba.b, rgba.a);
	}

	inline void YTD(std::string path) {
		struct stat buffer; int textureID;
		const std::string fullPath = path;
		if (stat(fullPath.c_str(), &buffer) == 0)
			g_pointers->file_register(&textureID, fullPath.c_str(), true, "", false);
	}
};

inline std::unique_ptr<Drawing> g_drawing;