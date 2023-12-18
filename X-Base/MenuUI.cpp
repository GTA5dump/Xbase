#include "pch.h"

gui::gui() {
	menyooX = 21;
	menyooY = 4;
	menyooW = 24;
	menuW = (float)(menyooW / 100.0f);
	menuX = (float)(menyooX / 100.0f);
	menuY = (float)((menyooY - 4) / 100.0f);
	scrollX = (float)(menuW / 2) + 0.015f;
	menuTitle = "X-Base";
	infoText = "";
	infoBoxEnabled = true;
	maxVisOptions = 14;
	currentOption = 0;
	optionCount = 0;
	menuLevel = 0;
	mouseCount = 0;
	currentMenu = nullptr;
	textSize = 0.35f;
	selectPressed = false;
	rightPressed = selectPressed;
	leftPressed = selectPressed;
	upPressed = selectPressed;
	downPressed = selectPressed;
	backPressed = selectPressed;
	menuOpened = false;
	keyDelay[0] = 200;
	keyDelay[1] = 100;
	keyDelay[2] = 140;
}

gui::~gui() { }

_func gui::getCurrentMenu() { 
	return currentMenu; 
}

bool gui::isMenuOpen() { 
	return menuOpened; 
}

const char* gui::getMenuTitle() { 
	return menuTitle; 
}

int gui::getMenuLevel() { 
	return menuLevel; 
}

int gui::getMaxOptions() {
	return maxVisOptions;
}

Vector3 gui::getMenuBounds() {
	Vector3 buffer;
	buffer.x = menuX;
	buffer.y = menuY;
	buffer.z = menuW;
	return buffer;
}

void gui::setMenuCoords(Vector2 xy) {
	menyooX = 21;
	menyooY = 4;
	menuX = xy.x;
	menuY = xy.y;
	menyooX = (int)(menyooX * 100.0f);
	menyooY = (int)((menyooY + 4) * 100.0f);
}

int gui::getOptionCount() { 
	return optionCount; 
}

int gui::getCurrentOption() {
	return currentOption;
}

int gui::getMouseOptions() {
	return mouseCount;
}

void gui::setCurrentOption(int option) {
	if (currentOption != option)
		currentOption = option;
}

void gui::setMenuOpen(bool opened) { 
	if (opened != menuOpened) 
		menuOpened = opened; 
}

void gui::setOptionCount(int count) {
	optionCount = count;
}

const char* gui::getSubTitle() {
	return currentSubtitle;
}

void gui::disableControls() {
	HUD::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	HUD::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	HUD::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	HUD::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	HUD::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	HUD::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	PAD::DISABLE_CONTROL_ACTION(2, 0, 1);
	PAD::DISABLE_CONTROL_ACTION(2, 19, 1);
	PAD::DISABLE_CONTROL_ACTION(2, 20, 1);
	PAD::DISABLE_CONTROL_ACTION(2, 27, 1);
	PAD::DISABLE_CONTROL_ACTION(2, 74, 1);
	PAD::DISABLE_CONTROL_ACTION(2, 80, 1);
	PAD::DISABLE_CONTROL_ACTION(2, 85, 1);
	PAD::DISABLE_CONTROL_ACTION(2, 140, 1);
	PAD::DISABLE_CONTROL_ACTION(2, 141, 1);
	PAD::DISABLE_CONTROL_ACTION(2, 142, 1);
	PAD::DISABLE_CONTROL_ACTION(2, 337, 1);
}

Vector2 gui::spriteScale(float size)
{
	int x, y;
	GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);
	return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
}

void gui::controller() {
	g_ui->press(right, false);
	g_ui->press(left, false);
	g_ui->press(selct, false);
	static int keyPressed[3] = { 0, 0, 0 };
	if (GetTickCount() - keyPressed[0] > keyDelay[0]) {
		if (GetTickCount() - keyPressed[1] > keyDelay[1]) {
			if (GetTickCount() - keyPressed[2] > keyDelay[2]) {
				if (GetAsyncKeyState(VK_MULTIPLY)) {
					if (!g_ui->isMenuOpen()) {
						g_ui->MoveMenu(&submenus::MainMenu, "Main Menu");					
						g_ui->setMenuOpen(true);
					}
					else if (g_ui->getMenuLevel() == 1) {
						g_ui->BackMenu();
						g_ui->setMenuOpen(false);
					}
					keyPressed[0] = GetTickCount();
				}
				else if (GetAsyncKeyState(VK_NUMPAD0)) {
					if (g_ui->getMenuLevel() > 0) g_ui->BackMenu();
					if (g_ui->getMenuLevel() == 0) g_ui->setMenuOpen(false);
					keyPressed[0] = GetTickCount();
				}
				else if (GetAsyncKeyState(VK_NUMPAD8)) {
					if (g_ui->getCurrentOption() > 1)
						g_ui->setCurrentOption(g_ui->getCurrentOption() - 1);
					else
						g_ui->setCurrentOption(g_ui->getOptionCount());
					keyPressed[1] = GetTickCount();
				}
				else if (GetAsyncKeyState(VK_NUMPAD2)) {
					if (g_ui->getCurrentOption() < g_ui->getOptionCount())
						g_ui->setCurrentOption(g_ui->getCurrentOption() + 1);
					else
						g_ui->setCurrentOption(1);
					keyPressed[1] = GetTickCount();
				}
				else if (GetAsyncKeyState(VK_NUMPAD6)) {
					g_ui->press(right, true);
					keyPressed[2] = GetTickCount();
				}
				else if (GetAsyncKeyState(VK_NUMPAD4)) {
					g_ui->press(left, true);
					keyPressed[2] = GetTickCount();
				}
				else if (GetAsyncKeyState(VK_NUMPAD5)) {
					g_ui->press(selct, true);
					keyPressed[0] = GetTickCount();
				}
			}
		}
	}
}

void gui::press(pressType type, bool state) {
	switch (type) {
	case left: 
		if(leftPressed != state)
			leftPressed = state;
		break;
	case right: 
		if (rightPressed != state)
			rightPressed = state;
		break;
	case selct: 
		if (selectPressed != state)
			selectPressed = state;
		break;
	case up: 
		if (upPressed != state)
			upPressed = state;
		break;
	case down: 
		if (downPressed != state)
			downPressed = state;
		break;
	case back: 
		if (backPressed != state)
			backPressed = state;
		break;
	}
}


void gui::Header(const char* title) {
	g_drawing->Text(title, titleText, { menuX, menuY + 0.065f }, { 0.50f, 0.50f }, true);
	g_drawing->Rect(titleRect, { menuX, menuY + 0.0820f }, { menuW, 0.085f });
}

void gui::Header(const char* title, std::string ytdpath, const char* filename, const char* picturename, int frame, bool animated) {
	g_drawing->Text(title, titleText, { menuX, menuY + 0.065f }, { 0.50f, 0.50f }, true);
	g_drawing->Frame(filename, picturename, frame, menuX, menuY, 0.24f, 0.100f, 0.f);
	if (animated) {
		g_drawing->Frame(filename, picturename, frame, menuX, menuY, 0.24f, 0.100f, 0.f);
	}
	else {
		g_drawing->Spriter(filename, picturename, menuX, menuY + 0.0820f, menuW, 0.085f, 0.0f, titleRect.r, titleRect.g, titleRect.b, titleRect.a);
	}
	g_drawing->YTD(ytdpath);
}

void gui::MoveMenu(_func menu, const char* title) {
	menusArray[menuLevel] = currentMenu;
	subtitlesArray[menuLevel] = currentSubtitle;
	optionsArray[menuLevel] = currentOption;
	menuLevel++;
	currentMenu = menu;
	currentSubtitle = title;
	currentOption = 1;
}

void gui::BackMenu() {
	menuLevel--;
	currentMenu = menusArray[menuLevel];
	currentSubtitle = subtitlesArray[menuLevel];
	currentOption = optionsArray[menuLevel];
}

bool gui::onThis() {
	return currentOption == optionCount;
}

void gui::InfoBox(std::string info) {
	if (strlen(info.c_str()) > 40 || strcmp(info.c_str(), "null") == 0 || strcmp(info.c_str(), "") == 0) return;
	auto spriteSize = spriteScale(0.025f);
	auto fontSize = (HUD::_GET_TEXT_SCALE_HEIGHT(0.28f, 0) / 1.5f);
	if (optionCount <= maxVisOptions) {
		g_drawing->Rect(optionRect, { menuX, menuY + (optionCount + 2) * 0.035f + 0.1415f }, { menuW, 0.033f });
		g_drawing->Spriter("shared", "info_icon_32", menuX - (menuW / 2.1f) + (spriteSize.x / 2.0f), menuY + (optionCount + 2) * 0.035f + 0.1415f, spriteSize.x, spriteSize.y, 0.0f, 255, 255, 255, 255);
		g_drawing->Text(info.c_str(), optionText, { menuX - (menuW / 2.1f) + (spriteSize.x * 1.15f), menuY + (optionCount + 2) * 0.035f + 0.1415f - fontSize }, { 0.28f, 0.28f }, 0, 0, 0);
	}
	else {
		g_drawing->Rect(optionRect, { menuX, menuY + (maxVisOptions + 2) * 0.035f + 0.1415f }, { menuW, 0.033f });
		g_drawing->Spriter("shared", "info_icon_32", menuX - (menuW / 2.1f) + (spriteSize.x / 2.0f), menuY + (maxVisOptions + 2) * 0.035f + 0.1415f, spriteSize.x, spriteSize.y, 0.0f, 255, 255, 255, 255);
		g_drawing->Text(info.c_str(), optionText, { menuX - (menuW / 2.1f) + (spriteSize.x * 1.15f), menuY + (maxVisOptions + 2) * 0.035f + 0.1415f - fontSize }, { 0.28f, 0.28f }, 0, 0, 0);
	}
}

void gui::Bar(const char* ytdfile, const char* ytdtexture1, const char* ytdtexture2, const char* ytdtexture3)
{
	g_drawing->Text(_strdup((std::to_string(currentOption) + "/" + std::to_string(optionCount)).c_str()), { 255, 255, 255, 255, 0 }, { menuX + 0.087f + (scrollX - 0.12f), menuY + 0.128f }, { 0.3f, 0.3f }, true);
	if (optionCount >= maxVisOptions) {
		mouseCount = maxVisOptions;
		g_drawing->Rect(breakrect, { menuX, menuY + (maxVisOptions + 1) * 0.035f + 0.1365f }, { menuW, 0.025f });
		if (currentOption <= 1) {
			Vector2 size = spriteScale(0.025f * 0.8f);
			g_drawing->Spriter(ytdfile, ytdtexture3, menuX, menuY + ((maxVisOptions + 1) * 0.035f + 0.136f), size.x, size.y, 90, arrow.r, arrow.g, arrow.b, arrow.a);
		}
		else if (currentOption == optionCount) {
			Vector2 size = spriteScale(0.025f * 0.8f);
			g_drawing->Spriter(ytdfile, ytdtexture2, menuX, menuY + ((maxVisOptions + 1) * 0.035f + 0.136f), size.x, size.y, 90, arrow.r, arrow.g, arrow.b, arrow.a);
		}
		else {
			Vector2 size = spriteScale(0.025f);
			g_drawing->Spriter(ytdfile, ytdtexture1, menuX, menuY + ((maxVisOptions + 1) * 0.035f + 0.136f), size.x, size.y, 180, arrow.r, arrow.g, arrow.b, arrow.a);
		}
	}
	else if (optionCount > 0) {
		mouseCount = optionCount;
		g_drawing->Rect(breakrect, { menuX, menuY + (optionCount + 1) * 0.035f + 0.1365f }, { menuW, 0.025f });
		if (currentOption <= 1) {
			Vector2 size = spriteScale(0.025f * 0.8f);
			g_drawing->Spriter(ytdfile, ytdtexture3, menuX, menuY + ((optionCount + 1) * 0.035f + 0.136f), size.x, size.y, 90, arrow.r, arrow.g, arrow.b, arrow.a);
		}
		else if (currentOption == optionCount) {
			Vector2 size = spriteScale(0.025f * 0.8f);
			g_drawing->Spriter(ytdfile, ytdtexture2, menuX, menuY + ((optionCount + 1) * 0.035f + 0.136f), size.x, size.y, 90, arrow.r, arrow.g, arrow.b, arrow.a);
		}
		else {
			Vector2 size = spriteScale(0.025f);
			g_drawing->Spriter(ytdfile, ytdtexture1, menuX, menuY + ((optionCount + 1) * 0.035f + 0.136f), size.x, size.y, 180, arrow.r, arrow.g, arrow.b, arrow.a);
		}
	}
	if (infoBoxEnabled)
		InfoBox(infoText);
}

void gui::SubBanner(const char* title)
{
	bool onThis = currentOption == optionCount ? true : false;
	g_drawing->Text(title, breakText, { menuX, menuY + (optionCount)*0.035f + 0.128f }, { 0.3f, 0.3f }, true);
	g_drawing->Rect(breakrect, { menuX, menuY + (optionCount)*0.035f + 0.1415f }, { menuW, 0.035f });
}

void gui::Option(const char* option, const char* info, Function action)
{
	optionCount++;
	if (onThis() && strcmp(infoText, info) != 0 && infoBoxEnabled) infoText = info;
	if (currentOption <= maxVisOptions && optionCount <= maxVisOptions)
	{
		g_drawing->Text(option, onThis() ? optionText2 : optionText, { menuX - (scrollX - 0.02f), menuY + (optionCount)*0.035f + 0.128f }, { textSize, textSize }, false);
		g_drawing->Rect(optionRect, { menuX, menuY + (optionCount)*0.035f + 0.1415f }, { menuW, 0.035f });
		if (onThis()) {
			g_drawing->Rect(scroller, { menuX, menuY + (optionCount)*0.035f + 0.1415f }, { menuW, 0.035f });
		}
	}
	else if (optionCount > (currentOption - maxVisOptions) && optionCount <= currentOption)
	{
		g_drawing->Text(option, onThis() ? optionText2 : optionText, { menuX - (scrollX - 0.02f), menuY + (optionCount - (currentOption - maxVisOptions))*0.035f + 0.128f }, { textSize, textSize }, false);
		g_drawing->Rect(optionRect, { menuX, menuY + (optionCount - (currentOption - maxVisOptions))*0.035f + 0.1415f }, { menuW, 0.035f });
		if (onThis()) {
			g_drawing->Rect(scroller, { menuX, menuY + (optionCount - (currentOption - maxVisOptions))*0.035f + 0.1415f }, { menuW, 0.035f });
		}
	}
	if (onThis() && selectPressed) action();
}

void gui::SubOption(const char* option, _func submenu, const char* info, const char* title, Function action)
{
	Option(option, info);
	if (currentOption <= maxVisOptions && optionCount <= maxVisOptions)
		g_drawing->Spriter("commonmenu", "arrowright", menuX + (scrollX - 0.023f), menuY + optionCount * 0.035f + 0.142f, 0.01f, 0.02f, 0.0f, onThis() ? 0 : 255, onThis() ? 0 : 255, onThis() ? 0 : 255, 255);
	else if (optionCount > currentOption - maxVisOptions && optionCount <= currentOption)
		g_drawing->Spriter("commonmenu", "arrowright", menuX + (scrollX - 0.023f), menuY + (optionCount - (currentOption - maxVisOptions)) * 0.035f + 0.142f, 0.01f, 0.02f, 0.0f, onThis() ? 0 : 255, onThis() ? 0 : 255, onThis() ? 0 : 255, 255);
	if (onThis() && selectPressed) {
		action();
		MoveMenu(submenu, title);
	}
}

void gui::BoolOption(const char* option, bool* b00l, const char* info, Function action, const char* ytdmenu, const char* ytdoff, const char* ytdon)
{
	Option(option, info);
	if ((*b00l)) {
		if (currentOption <= maxVisOptions && optionCount <= maxVisOptions)
			g_drawing->Spriter(ytdmenu, ytdon, menuX + (scrollX - 0.028f), menuY + (optionCount * 0.035f + 0.141f), 0.03f, 0.05f, 0, 0, 255, 0, 255);
		else if (optionCount > currentOption - maxVisOptions && optionCount <= currentOption)
			g_drawing->Spriter(ytdmenu, ytdon, menuX + (scrollX - 0.028f), menuY + ((optionCount - (currentOption - maxVisOptions)) * 0.035f + 0.141f), 0.03f, 0.05f, 0, 0, 255, 0, 255);
	}
	else {
		if (currentOption <= maxVisOptions && optionCount <= maxVisOptions)
			g_drawing->Spriter(ytdmenu, ytdoff, menuX + (scrollX - 0.028f), menuY + (optionCount * 0.035f + 0.141f), 0.03f, 0.05f, 0, 255, 0, 0, 255);
		else if (optionCount > currentOption - maxVisOptions && optionCount <= currentOption)
			g_drawing->Spriter(ytdmenu, ytdoff, menuX + (scrollX - 0.028f), menuY + ((optionCount - (currentOption - maxVisOptions)) * 0.035f + 0.141f), 0.03f, 0.05f, 0, 255, 0, 0, 255);
	}
	if (onThis() && selectPressed) {
		(*b00l) ^= 1;
		action();
		return;
	}
}

void gui::IntOption(const char* option, int* _int, int min, int max, const char* info, int step, Function action)
{
	Option(option, info);
	if (onThis()) {
		if (rightPressed) (*_int) < max ? (*_int) += step : (*_int) = min;
		if (leftPressed) (*_int) > min ? (*_int) -= step : (*_int) = max;
	}
	if (currentOption <= maxVisOptions && optionCount <= maxVisOptions)
		g_drawing->Text(_strdup(("< " + std::to_string(*_int) + " >").c_str()), onThis() ? invert : integre, { menuX + (scrollX - 0.052f), menuY + optionCount * 0.035f + 0.128f }, { textSize - 0.003f, textSize - 0.003f }, true);
	else if (optionCount > currentOption - maxVisOptions && optionCount <= currentOption)
		g_drawing->Text(_strdup(("< " + std::to_string(*_int) + " >").c_str()), onThis() ? invert : integre, { menuX + (scrollX - 0.052f), menuY + (optionCount - (currentOption - maxVisOptions)) * 0.035f + 0.12f }, { textSize - 0.003f, textSize - 0.003f }, true);
	if (onThis() && (selectPressed || rightPressed || leftPressed)) action();
}

void gui::Option(const char* option, Function action)
{
	Option(option, "", action);
}

void gui::BoolOption(const char* option, bool* b00l, Function action, const char* ytdmenu, const char* ytdoff, const char* ytdon)
{
	BoolOption(option, b00l, "", action, ytdmenu, ytdoff, ytdon);
}

void gui::IntOption(const char* option, int* _int, int min, int max, int step, Function action)
{
	IntOption(option, _int, min, max, "", step, action);
}

void gui::SubOption(const char* option, _func submenu, const char* title, Function action)
{
	SubOption(option, submenu, "", title, action);
}

void gui::IntOption(const char* option, int* _int, int min, int max, const char* info, Function action)
{
	IntOption(option, _int, min, max, info, 1, action);
}

void gui::IntOption(const char* option, int* _int, int min, int max, Function action)
{
	IntOption(option, _int, min, max, 1, action);
}




Cursor::Cursor() {
	m_sprite = 1;
	m_enabled = false;
	m_on_int = false;
	m_timer = 0;
	m_timer_int = 0;
	m_scroll_count = 0;
	m_is_scrolling = false;
	reset1 = true;
}

Cursor::~Cursor() {

}

Vector2 Cursor::get_mouse_pos() {
	Vector2 result;
	result.x = PAD::GET_DISABLED_CONTROL_NORMAL(2, 239);
	result.y = PAD::GET_DISABLED_CONTROL_NORMAL(2, 240);
	return result;
}

void Cursor::show_mouse() {
	HUD::_SET_MOUSE_CURSOR_ACTIVE_THIS_FRAME();
	HUD::_SET_MOUSE_CURSOR_SPRITE(m_sprite);
}

void Cursor::set_sprite(int sprite) {
	if (m_sprite != sprite) m_sprite = sprite;
}

void Cursor::reset_sprite() {
	set_sprite(1);
}

bool Cursor::is_in_bounds(Vector2 pos, Vector2 size) {
	Rectangle rect;
	rect.m_Center = pos;
	rect.m_Size = size;
	return rect.IsInBounds(get_mouse_pos());
}

void Cursor::disable_controls() {
	PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
	PAD::DISABLE_ALL_CONTROL_ACTIONS(1);
	PAD::DISABLE_ALL_CONTROL_ACTIONS(2);
}

int Cursor::get_scroller() {
	int result = 0;
	if (PAD::GET_DISABLED_CONTROL_NORMAL(2, 242)) //Up
		result = 1;
	if (PAD::GET_DISABLED_CONTROL_NORMAL(2, 241)) //Down
		result = -1;
	return result;
}

void Cursor::tick() {
	if (!m_enabled) return;
	disable_controls();
	if (reset1) reset_sprite();
	else if (!reset1) show_mouse();
	if (g_ui->isMenuOpen()) {
		if (is_in_bounds({ g_ui->getMenuBounds().x, g_ui->getMenuBounds().y + 0.0820f }, { g_ui->getMenuBounds().z, 0.085f })) {
			reset1 = false;
			if (GetAsyncKeyState(VK_LBUTTON)) {
				set_sprite(4);
				Vector2 m_pos = get_mouse_pos();
				g_ui->setMenuCoords({ m_pos.x, m_pos.y - 0.082f });
			}
			else set_sprite(5);
		}
		else reset1 = true;
	}
}