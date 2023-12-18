#pragma once
#include "pch.h"
#include "Utility.hpp"

class gui
{
public:
	gui();
	~gui();
	
	void Header(const char* title);
	void Header(const char* title, std::string ytdtexture, const char* filename, const char* picturename, int frame, bool animated);
	void Bar(const char* ytdfile, const char* ytdtexture1, const char* ytdtexture2, const char* ytdtexture3);
	void SubBanner(const char* title);

	void Option(const char* option, const char* info, Function action = [] {});
	void BoolOption(const char* option, bool* b00l, const char* info, Function action = [] {}, const char* ytdmenu = "commonmenu", const char* ytdoff = "common_medal", const char* ytdon = "common_medal");
	void IntOption(const char* option, int* _int, int min, int max, const char* info, int step, Function action = [] {});
	void SubOption(const char* option, _func submenu, const char* info, const char* title, Function action = [] {});
	void Option(const char* option, Function action = [] {});
	void BoolOption(const char* option, bool* b00l, Function action = [] {}, const char* ytdmenu = "commonmenu", const char* ytdoff = "common_medal", const char* ytdon = "common_medal");
	void IntOption(const char* option, int* _int, int min, int max, int step, Function action = [] {});
	void SubOption(const char* option, _func submenu, const char* title, Function action = [] {});
	void IntOption(const char* option, int* _int, int min, int max, const char* info, Function action = [] {});
	void IntOption(const char* option, int* _int, int min, int max, Function action = [] {});


	const char* getMenuTitle();
	const char* getSubTitle();
	void controller();
	void MoveMenu(_func menu, const char* title);
	void BackMenu();
	bool onThis();
	bool isMenuOpen();
	_func getCurrentMenu();
	int getMenuLevel();
	int getOptionCount();
	int getCurrentOption();
	int getMaxOptions();
	int getMouseOptions();
	void setMenuCoords(Vector2 xy);
	void setCurrentOption(int option);
	void setOptionCount(int count);
	void setMenuOpen(bool opened);
	void press(pressType type, bool state);
	void disableControls();
	Vector3 getMenuBounds();
	Vector2 spriteScale(float size);
	void InfoBox(std::string info);

	int menyooX;
	int menyooY;
	int menyooW;
	float menuX;
	float menuY;
	float menuW;
	float scrollX;
	int keyDelay[3];
	bool infoBoxEnabled;
	int maxVisOptions;

	RGBAF titleText{ 255, 255, 255, 255, 7 };
	RGBA titleRect{ 17, 38, 65, 255 };
	RGBA breakrect{ 0, 0, 0, 180 };
	RGBAF optionText{ 255, 255, 255, 255, 0 };
	RGBAF optionText2{ 0, 0, 0, 255, 0 };
	RGBAF breakText{ 255, 255, 255, 255, 0 };
	RGBAF arrow{ 255, 255, 255, 255, 3 };
	RGBA optionRect{ 0, 0, 0, 150 };
	RGBA scroller{ 255, 255, 255, 255 };
	RGBAF integre{ 255, 255, 255, 255, 0 };
	RGBAF invert{ 0, 0, 0, 255, 0 };
	RGBA line{ 255, 255, 255, 255 };
	RGBA primary{ 255, 0, 0, 255 };
	RGBA secondary{ 0, 0, 0, 255 };

private:
	const char* menuTitle;
	const char* infoText;
	bool menuOpened;
	int optionCount;
	int mouseCount;
	int menuLevel;
	_func currentMenu;
	int currentOption;
	const char* currentSubtitle;
	int optionsArray[1000];
	_func menusArray[1000];
	const char* subtitlesArray[1000];
	float textSize;

	bool selectPressed;
	bool backPressed;
	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;
};

inline std::unique_ptr<gui> g_ui;

class Cursor
{
public:
	Cursor();
	~Cursor();

	struct Rectangle
	{
		Vector2 m_Center;
		Vector2 m_Size;
		bool IsInBounds(Vector2 point) {
			auto left = m_Center.x - (m_Size.x / 2.f);
			auto right = m_Center.x + (m_Size.x / 2.f);
			auto top = m_Center.y + (m_Size.y / 2.f);
			auto bottom = m_Center.y - (m_Size.y / 2.f);
			if (point.x > right || point.x < left) return false;
			if (point.y > top || point.y < bottom) return false;
			return true;
		}
	};

	Vector2 get_mouse_pos();
	void show_mouse();
	void set_sprite(int sprite);
	void reset_sprite();
	bool is_in_bounds(Vector2 pos, Vector2 size);
	void disable_controls();
	void tick();
	int get_scroller();

	bool m_enabled{};
	bool reset1{};

private:
	int m_sprite{};
	bool m_on_int{};
	int m_timer{};
	int m_timer_int{};
	int m_scroll_count{};
	bool m_is_scrolling{};
};

inline std::unique_ptr<Cursor> g_cursor;