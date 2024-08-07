#include "MessageObject.h"
#include "DotRunDef.h"

MessageObject::MessageObject()
{

}

/// <summary>
/// �޽��� �ڽ� ������ (msgũ�Ⱑ �ʹ� ũ�� �޽����� ��µ��� ����)
/// </summary>
/// <param name="msg"> ȭ�鿡 ǥ���� �޼��� </param>
/// <param name="alignment"> ���Ĺ�� </param>
/// <param name="fontcolor"> ��Ʈ�� </param>
/// <param name="bgcolor"> ���� </param>
/// <param name="borderbgcolor"> �׵θ� ���� </param>
/// <param name="_locationX"> X��ġ </param>
/// <param name="_locationY"> Y��ġ </param>
/// <param name="_sizeX"> Xũ�� </param>
/// <param name="_sizeY"> Yũ�� </param>
/// <param name="_layer"> ���̾� </param>
MessageObject::MessageObject(string msg, int _alignment, int _fontcolor, int _bgcolor, int _borderbgcolor, int _locationX, int _locationY, int _sizeX, int _sizeY, int _layer)
{
	init(true, _locationX, _locationY, _sizeX, _sizeY, _layer);
	alignment = _alignment;
	fontcolor = _fontcolor;
	bgcolor = _bgcolor;
	borderbgcolor = _borderbgcolor;

	Chars.resize(_sizeY, vector<char>(_sizeX, ' '));
	Colors.resize(_sizeY, vector<int>(_sizeX, _bgcolor));

	if (_sizeX != 0) {
		for (int i = 0; i < _sizeY; i++) {
			Colors[i][0] = _borderbgcolor;
			Colors[i][1] = _borderbgcolor;
			Colors[i][_sizeX - 2] = _borderbgcolor;
			Colors[i][_sizeX - 1] = _borderbgcolor;
		}
	}

	if (_sizeY != 0) {
		for (int i = 0; i < _sizeX; i++) {
			Colors[0][i] = _borderbgcolor;
			Colors[_sizeY - 1][i] = _borderbgcolor;
		}
	}

	if (_sizeX >= msg.size()) {
		if (alignment == ALIGNMENT_LEFT) {
			for (int i = 0; i < msg.size(); i++) {
				Chars[_sizeY / 2][i] = msg[i];
				Colors[_sizeY / 2][i] = _bgcolor + _fontcolor;
			}
		}
		else if (alignment == ALIGNMENT_CENTER) {
			int leftspace = (_sizeX - msg.size()) / 2;
			for (int i = 0; i < msg.size(); i++) {
				Chars[_sizeY / 2][leftspace + i] = msg[i];
				Colors[_sizeY / 2][leftspace + i] = _bgcolor + _fontcolor;
			}
		}
		else if (alignment == ALIGNMENT_RIGHT) {
			for (int i = 0; i < msg.size(); i++) {
				Chars[_sizeY / 2][_sizeX - 1 - i] = msg[msg.size() - 1 - i];
				Colors[_sizeY / 2][_sizeX - 1 - i] = _bgcolor + _fontcolor;
			}
		}
	}
}

MessageObject::~MessageObject()
{

}

void MessageObject::SetMessage(string msg)
{
	for (int i = 0; i < Chars.size(); i++) {
		for (int j = 0; j < Chars[i].size(); j++) {
			Chars[i][j] = CHAR_BASE;
		}
	}

	if (sizeX >= msg.size()) {
		if (alignment == ALIGNMENT_LEFT) {
			for (int i = 0; i < msg.size(); i++) {
				Chars[sizeY / 2][i] = msg[i];
				Colors[sizeY / 2][i] = bgcolor + fontcolor;
			}
		}
		else if (alignment == ALIGNMENT_CENTER) {
			int leftspace = (sizeX - msg.size()) / 2;
			for (int i = 0; i < msg.size(); i++) {
				Chars[sizeY / 2][leftspace + i] = msg[i];
				Colors[sizeY / 2][leftspace + i] = bgcolor + fontcolor;
			}
		}
		else if (alignment == ALIGNMENT_RIGHT) {
			for (int i = 0; i < msg.size(); i++) {
				Chars[sizeY / 2][sizeX - 1 - i] = msg[msg.size() - 1 - i];
				Colors[sizeY / 2][sizeX - 1 - i] = bgcolor + fontcolor;
			}
		}
	}
}

void MessageObject::SetBorder(char borderchar)
{

}

void MessageObject::SetSizeX(int size)
{
	sizeX = size;
}