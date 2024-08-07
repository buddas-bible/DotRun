#include "OutputManager.h"
#include "DotRunDef.h"
#include "PixelObject.h"

OutputManager::OutputManager() :
	charBoard(vector<vector<char>>(SCREEN_SIZE_Y, vector<char>(SCREEN_SIZE_X, CHAR_BASE))),
	colorBoard(vector<vector<int>>(SCREEN_SIZE_Y, vector<int>(SCREEN_SIZE_X, COLOR_BASE))),
	layerBoard(vector<vector<int>>(SCREEN_SIZE_Y, vector<int>(SCREEN_SIZE_X, LAYER_BASE))),
	lastCharBoard(vector<vector<char>>(SCREEN_SIZE_Y, vector<char>(SCREEN_SIZE_X, CHAR_BASE))),
	lastColorBoard(vector<vector<int>>(SCREEN_SIZE_Y, vector<int>(SCREEN_SIZE_X, COLOR_BASE)))
{
	// 콘솔 창의 커서표시 제거
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void OutputManager::setColor(WORD Fontcolor, WORD BGcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Fontcolor + BGcolor);
}

// 콘솔 창에서 (x, y)지점에 ch를 출력
void OutputManager::printChar(int x, int y, char ch)
{
	// 커서 이동
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << ch;
}

void OutputManager::init()
{
	for (int i = 0; i < charBoard.size(); i++) {
		for (int j = 0; j < charBoard[i].size(); j++) {
			lastCharBoard[i][j] = charBoard[i][j];
			charBoard[i][j] = CHAR_BASE;
		}
	}

	for (int i = 0; i < colorBoard.size(); i++) {
		for (int j = 0; j < colorBoard[i].size(); j++) {
			lastColorBoard[i][j] = colorBoard[i][j];
			colorBoard[i][j] = COLOR_BASE;
		}
	}

	for (int i = 0; i < layerBoard.size(); i++) {
		for (int j = 0; j < layerBoard[i].size(); j++) {
			layerBoard[i][j] = LAYER_BASE;
		}
	}
}

void OutputManager::paintScreen()
{
	for (int j = 0; j < SCREEN_SIZE_Y; j++) {
		for (int i = 0; i < SCREEN_SIZE_X; i++) {
			char ch = charBoard[j][i];
			int color = colorBoard[j][i];

			// 이전 출력했던 것과 같은 경우 무시
			if (ch == lastCharBoard[j][i] && color == lastColorBoard[j][i]) continue;

			setColor(color, COLOR_BG_BLACK);
			printChar(i, j, ch);
		}
	}
}

void OutputManager::paintObject(const PixelObject& pixelobject)
{
	int locationX = pixelobject.locationX;
	int locationY = pixelobject.locationY;
	int layer = pixelobject.layer;

	// pixelobject.isVisible 이 false인 경우 그리지 않음
	if (!pixelobject.getVisible()) return;

	for (int j = 0; j < pixelobject.sizeY; j++) {
		for (int i = 0; i < pixelobject.sizeX; i++) {
			// 그려야될 위치 계산
			int x = locationX + i;
			int y = locationY + j;
			char ch = pixelobject.Chars[j][i];
			int color = pixelobject.Colors[j][i];

			// x, y가 화면을 벗어난다면 continue
			if (x < 0) continue;
			if (y < 0) continue;
			if (x >= SCREEN_SIZE_X) continue;
			if (y >= SCREEN_SIZE_Y) continue;

			// 그릴 문자가 CHAR_BASE이고 color가 COLOR_BG_BLACK라면 continue
			//if (ch == CHAR_BASE && color == COLOR_BG_BLACK) continue;

			// 공백에 font, bg가 모두 white인 경우 continue
			if (ch == CHAR_BASE && color == COLOR_FONT_WHITE + COLOR_BG_WHITE) continue;

			// 레이어 체크
			if (layerBoard[y][x] < layer)
			{
				// 문자, 색, 레이어 저장
				charBoard[y][x] = ch;
				colorBoard[y][x] = color;
				layerBoard[y][x] = layer;
			}
		}
	}
}

void OutputManager::paintObject(const PixelObject& pixelobject, int shift)
{
	int locationX = pixelobject.locationX + shift;
	int locationY = pixelobject.locationY;
	int layer = pixelobject.layer;

	// pixelobject.isVisible 이 false인 경우 그리지 않음
	if (!pixelobject.getVisible()) return;

	for (int j = 0; j < pixelobject.sizeY; j++) {
		for (int i = 0; i < pixelobject.sizeX; i++) {
			// 그려야될 위치 계산
			int x = locationX + i;
			int y = locationY + j;
			char ch = pixelobject.Chars[j][i];
			int color = pixelobject.Colors[j][i];

			// x, y가 화면을 벗어난다면 continue
			if (x < 0) continue;
			if (y < 0) continue;
			if (x >= SCREEN_SIZE_X) continue;
			if (y >= SCREEN_SIZE_Y) continue;

			// 그릴 문자가 CHAR_BASE이고 color가 COLOR_BG_BLACK라면 continue
			if (ch == CHAR_BASE && color == COLOR_BG_BLACK) continue;

			// 레이어 체크
			if (layerBoard[y][x] < layer)
			{
				// 문자, 색, 레이어 저장
				charBoard[y][x] = ch;
				colorBoard[y][x] = color;
				layerBoard[y][x] = layer;
			}
		}
	}
}