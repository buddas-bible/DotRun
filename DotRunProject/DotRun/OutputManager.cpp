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
	// �ܼ� â�� Ŀ��ǥ�� ����
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void OutputManager::setColor(WORD Fontcolor, WORD BGcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Fontcolor + BGcolor);
}

// �ܼ� â���� (x, y)������ ch�� ���
void OutputManager::printChar(int x, int y, char ch)
{
	// Ŀ�� �̵�
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

			// ���� ����ߴ� �Ͱ� ���� ��� ����
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

	// pixelobject.isVisible �� false�� ��� �׸��� ����
	if (!pixelobject.getVisible()) return;

	for (int j = 0; j < pixelobject.sizeY; j++) {
		for (int i = 0; i < pixelobject.sizeX; i++) {
			// �׷��ߵ� ��ġ ���
			int x = locationX + i;
			int y = locationY + j;
			char ch = pixelobject.Chars[j][i];
			int color = pixelobject.Colors[j][i];

			// x, y�� ȭ���� ����ٸ� continue
			if (x < 0) continue;
			if (y < 0) continue;
			if (x >= SCREEN_SIZE_X) continue;
			if (y >= SCREEN_SIZE_Y) continue;

			// �׸� ���ڰ� CHAR_BASE�̰� color�� COLOR_BG_BLACK��� continue
			//if (ch == CHAR_BASE && color == COLOR_BG_BLACK) continue;

			// ���鿡 font, bg�� ��� white�� ��� continue
			if (ch == CHAR_BASE && color == COLOR_FONT_WHITE + COLOR_BG_WHITE) continue;

			// ���̾� üũ
			if (layerBoard[y][x] < layer)
			{
				// ����, ��, ���̾� ����
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

	// pixelobject.isVisible �� false�� ��� �׸��� ����
	if (!pixelobject.getVisible()) return;

	for (int j = 0; j < pixelobject.sizeY; j++) {
		for (int i = 0; i < pixelobject.sizeX; i++) {
			// �׷��ߵ� ��ġ ���
			int x = locationX + i;
			int y = locationY + j;
			char ch = pixelobject.Chars[j][i];
			int color = pixelobject.Colors[j][i];

			// x, y�� ȭ���� ����ٸ� continue
			if (x < 0) continue;
			if (y < 0) continue;
			if (x >= SCREEN_SIZE_X) continue;
			if (y >= SCREEN_SIZE_Y) continue;

			// �׸� ���ڰ� CHAR_BASE�̰� color�� COLOR_BG_BLACK��� continue
			if (ch == CHAR_BASE && color == COLOR_BG_BLACK) continue;

			// ���̾� üũ
			if (layerBoard[y][x] < layer)
			{
				// ����, ��, ���̾� ����
				charBoard[y][x] = ch;
				colorBoard[y][x] = color;
				layerBoard[y][x] = layer;
			}
		}
	}
}