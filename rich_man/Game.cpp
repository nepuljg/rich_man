#include<easyx.h>
#include<graphics.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>
#define NUM 100
const int width = 900;
const int height = 506;
enum Square_Veriety {
	SPACE_SQUARE,
	GROUND_SQUARE,
	CHANCE_SQUARE,
	PENITENTIARY_SQUARE,
	BANK_SQUARE
};
struct Square {
	Square_Veriety square_veriety;
	union {
		struct space_square* space_square_ptr; //�յ�
		struct ground_square* ground_square_ptr; //����
		struct chance_square* chance_square_ptr; //����
		struct penitentiary_square* penitentiary_square_ptr; //����
		struct bank_square* bank_square_ptr;//����
	};
};
Square arr_list_square[18];
int dice_points;
bool is_player_white_or_black = false;

enum chance { //��������
	get_money,
	lose_money,
	up,
	down
};

struct Location {
	int tx;
	int ty;
};
struct Player {
	char name[64];//����
	double money = 1000;
	int index = 0;
	Square_Veriety square_veriety;
	union {
		struct space_square* space_square_ptr; //�յ�
		struct ground_square* ground_square_ptr; //����
		struct chance_square* chance_square_ptr; //����
		struct penitentiary_square* penitentiay_square_ptr; //����
		struct bank_square* bank_square_ptr;//����
	};
};
//�շ���
struct space_square {
	char name[64];
	int x;
	int y;
};
struct ground_square { //���ط���
	char name[64]; //����
	int x; //λ��
	int y; //λ��
	double amount; //������
	Player* owner;
};
//�����
struct chance_square {
	char name[64];
	int x;
	int y;
	enum chance;
	union {
		double money;
		Location location;
	};
};
//��������
struct penitentiary_square {
	char name[64];
	int x;
	int y;
};
struct lend_deposit{ //��ʹ�
	double money; // ��Ϊ�棬��Ϊ��
	Player* owner;
};
//���и���(��ʱ����Ϊ�ɴ���ʹ��)
struct bank_square {
	char name[64];
	int x;
	int y;
	lend_deposit arr[NUM];
	int index;//������߽���idx
};

struct bank_square arr_bank_square; //�������и�1��
struct penitentiary_square arr_penitentiary_square;//���ü�����1��
struct chance_square arr_chance_square[2];//���û����2��
struct ground_square arr_ground_square[6];//�������ظ�
struct space_square arr_space_square[8];//���ÿյظ�
struct Player player_white;
struct Player player_black;

void init_map() {

	int index = 0;
	//1 space 0
	arr_space_square[0].x = 40;
	arr_space_square[0].y = 40;
	
	arr_list_square[index].square_veriety = SPACE_SQUARE;
	arr_list_square[index].space_square_ptr = &arr_space_square[0];
	index++;
	
	//2 ground 0
	arr_ground_square[0].x = 120;
	arr_ground_square[0].y = 40;

	arr_list_square[index].square_veriety = GROUND_SQUARE;
	arr_list_square[index].ground_square_ptr = &arr_ground_square[0];
	index++;
	//strcpy_s(arr_ground_square[0].name, "1");

	//3 space 1
	arr_space_square[1].x = 200;
	arr_space_square[1].y = 40;

	arr_list_square[index].square_veriety = SPACE_SQUARE;
	arr_list_square[index].space_square_ptr = &arr_space_square[1];
	index++;
	//strcpy_s(arr_space_square[1].name, "2");
	//4 space 2
	arr_space_square[2].x = 280;
	arr_space_square[2].y = 40;
	
	arr_list_square[index].square_veriety = SPACE_SQUARE;
	arr_list_square[index].space_square_ptr = &arr_space_square[2];
	index++;
	//strcpy_s(arr_space_square[2].name, "3");

	//5 ground 1
	arr_ground_square[1].x = 360;
	arr_ground_square[1].y = 40;

	arr_list_square[index].square_veriety = GROUND_SQUARE;
	arr_list_square[index].ground_square_ptr = &arr_ground_square[1];
	index++;
	//strcpy_s(arr_ground_square[0].name, "2");
	
	//6 ground 2
	arr_ground_square[2].x = 440;
	arr_ground_square[2].y = 40;

	arr_list_square[index].square_veriety = GROUND_SQUARE;
	arr_list_square[index].ground_square_ptr = &arr_ground_square[2];
	index++;
	//strcpy_s(arr_ground_square[0].name, "3");
	
	//7 chance 0
	arr_chance_square[0].x = 440;
	arr_chance_square[0].y = 120;

	arr_list_square[index].square_veriety = CHANCE_SQUARE;
	arr_list_square[index].chance_square_ptr = &arr_chance_square[0];
	index++;
	//strcpy_s(arr_chance_square[0].name, "1");
	//8 penitentiary
	arr_penitentiary_square.x = 440;
	arr_penitentiary_square.y = 200;

	arr_list_square[index].square_veriety = PENITENTIARY_SQUARE;
	arr_list_square[index].penitentiary_square_ptr = &arr_penitentiary_square;
	index++;
	//strcpy_s(arr_penitentiary_square.name, "2");

	//9 space 3
	arr_space_square[3].x = 440;
	arr_space_square[3].y = 280;

	arr_list_square[index].square_veriety = SPACE_SQUARE;
	arr_list_square[index].space_square_ptr = &arr_space_square[3];
	index++;
	//strcpy_s(arr_space_square[3].name, "4");
	//10 ground 3
	arr_ground_square[3].x = 440;
	arr_ground_square[3].y = 360;

	arr_list_square[index].square_veriety = GROUND_SQUARE;
	arr_list_square[index].ground_square_ptr = &arr_ground_square[3];
	index++;
	//strcpy_s(arr_ground_square[3].name, "4");

	//11 space 4
	arr_space_square[4].x = 360;
	arr_space_square[4].y = 360;

	arr_list_square[index].square_veriety = SPACE_SQUARE;
	arr_list_square[index].space_square_ptr = &arr_space_square[4];
	index++;
	//strcpy_s(arr_space_square[0].name, "5");
	
	//12 ground 4
	arr_ground_square[4].x = 280;
	arr_ground_square[4].y = 360;

	arr_list_square[index].square_veriety = GROUND_SQUARE;
	arr_list_square[index].ground_square_ptr = &arr_ground_square[0];
	index++;
	//strcpy_s(arr_ground_square[0].name, "5");

	//13 ground 5
	arr_ground_square[5].x = 200;
	arr_ground_square[5].y = 360;

	arr_list_square[index].square_veriety = GROUND_SQUARE;
	arr_list_square[index].ground_square_ptr = &arr_ground_square[0];
	index++;
	//strcpy_s(arr_ground_square[0].name, "6");
	//14 space 5
	arr_space_square[5].x = 120;
	arr_space_square[5].y = 360;
	
	arr_list_square[index].square_veriety = SPACE_SQUARE;
	arr_list_square[index].space_square_ptr = &arr_space_square[5];
	index++;
	//strcpy_s(arr_space_square[5].name, "6");
	//15 space 6
	arr_space_square[6].x = 40;
	arr_space_square[6].y = 360;

	arr_list_square[index].square_veriety = SPACE_SQUARE;
	arr_list_square[index].space_square_ptr = &arr_space_square[6];
	index++;
	//strcpy_s(arr_space_square[6].name, "7");
	//16 bank 
	arr_bank_square.x = 40;
	arr_bank_square.y = 280;

	arr_list_square[index].square_veriety = BANK_SQUARE;
	arr_list_square[index].bank_square_ptr = &arr_bank_square;
	index++;
	//strcpy_s(arr_bank_square.name, "");

	//17 chance 1
	arr_chance_square[1].x = 40;
	arr_chance_square[1].y = 200;
	
	arr_list_square[index].square_veriety = CHANCE_SQUARE;
	arr_list_square[index].chance_square_ptr = &arr_chance_square[0];
	index++;
	//strcpy_s(arr_chance_square[1].name, "2");
	//18 space 7
	arr_space_square[7].x = 40;
	arr_space_square[7].y = 120;
	arr_list_square[index].square_veriety = SPACE_SQUARE;
	arr_list_square[index].space_square_ptr = &arr_space_square[7];
	index++;
}
void draw_ground_square(ground_square* ptr) {
	setfillcolor(BLUE);
	circle(ptr->x, ptr->y, 40);
	fillcircle(ptr->x, ptr->y, 40);

	int text_height = textheight('A');
	int text_width = textwidth(_T("����"));

	int text_x = ptr->x - text_width / 2;
	int text_y = ptr->y - text_height / 2;

	outtextxy(text_x, text_y, _T("����"));
}
void draw_bank_square(bank_square* ptr) {
	setfillcolor(BROWN);
	circle(ptr->x, ptr->y, 40);
	fillcircle(ptr->x, ptr->y, 40);

	int text_height = textheight('A');
	int text_width = textwidth(_T("����"));

	int text_x = ptr->x - text_width / 2;
	int text_y = ptr->y - text_height / 2;

	outtextxy(text_x, text_y, _T("����"));
}
void draw_chance_square(chance_square* ptr) {
	setfillcolor(GREEN);
	circle(ptr->x, ptr->y, 40);
	fillcircle(ptr->x, ptr->y, 40);

	int text_height = textheight('A');
	int text_width = textwidth(_T("����"));

	int text_x = ptr->x - text_width / 2;
	int text_y = ptr->y - text_height / 2;

	outtextxy(text_x, text_y, _T("����"));
}
void draw_penitentiary_square(penitentiary_square* ptr) {
	setfillcolor(0x800080);
	circle(ptr->x, ptr->y, 40);
	fillcircle(ptr->x, ptr->y, 40);

	int text_height = textheight('A');
	int text_width = textwidth(_T("����"));

	int text_x = ptr->x - text_width / 2;
	int text_y = ptr->y - text_height / 2;

	outtextxy(text_x, text_y, _T("����"));
}

void draw_space_square(space_square* ptr) {
	setfillcolor(RED);
	circle(ptr->x, ptr->y, 40);
	fillcircle(ptr->x, ptr->y, 40);
	int text_height = textheight('A');
	int text_width = textwidth(_T("�յ�"));
	
	int text_x = ptr->x - text_width / 2;
	int text_y = ptr->y - text_height / 2;
	
	outtextxy(text_x, text_y, _T("�յ�"));
}
//���õ�ͼ
void draw_player_white();
void draw_player_black();

LPCTSTR CharToLPCTSTR(const char* ansiStr) {
	if (ansiStr == NULL) return NULL;

	size_t ansiStrLen = strlen(ansiStr) + 1; // ����������'\0'  
	int wideStrLen = MultiByteToWideChar(CP_ACP, 0, ansiStr, ansiStrLen, NULL, 0);
	if (wideStrLen == 0) {
		// ������...  
		return NULL;
	}

	wchar_t* wideStr = (wchar_t*)malloc(wideStrLen * sizeof(wchar_t));
	if (wideStr == NULL) {
		// ������...  
		return NULL;
	}

	MultiByteToWideChar(CP_ACP, 0, ansiStr, ansiStrLen, wideStr, wideStrLen);
	return wideStr; // ע�⣺���ص�ָ����Ҫ��ʹ�ú��ͷţ�  
}
void draw_player_result() {
	
	char player_white_buf[128] = { 0 };
	char player_black_buf[128] = { 0 };
	sprintf_s(player_white_buf, "��ɫ��ҽ��:%f", player_white.money);
	sprintf_s(player_black_buf, "��ɫ��ҽ��:%f", player_black.money);
	outtextxy(500, 40, CharToLPCTSTR(player_white_buf));
	outtextxy(700, 40, CharToLPCTSTR(player_black_buf));
}
void draw_map() {
	for (int i = 0; i < 6; i++) {
		draw_ground_square(&arr_ground_square[i]);
	}
	for (int i = 0; i < 8; i++) {
		draw_space_square(&arr_space_square[i]);
	}
	draw_chance_square(&arr_chance_square[0]);
	draw_chance_square(&arr_chance_square[1]);
	
	draw_bank_square(&arr_bank_square);
	draw_penitentiary_square(&arr_penitentiary_square);
	draw_player_white();
	draw_player_black();
	draw_player_result();
}

void draw_player_white() {
	setfillcolor(WHITE);
	int tx, ty;
	struct Square square = arr_list_square[player_white.index];
	switch (square.square_veriety) {
	case SPACE_SQUARE:
		tx = square.space_square_ptr->x + 10;
		ty = square.space_square_ptr->y + 10;
		break;
	case GROUND_SQUARE:
		tx = square.ground_square_ptr->x + 10;
		ty = square.ground_square_ptr->y + 10;
		break;
	case CHANCE_SQUARE:
		tx = square.chance_square_ptr->x + 10;
		ty = square.chance_square_ptr->y + 10;
		break;
	case BANK_SQUARE:
		tx = square.bank_square_ptr->x + 10;
		ty = square.bank_square_ptr->y + 10;
		break;
	case PENITENTIARY_SQUARE:
		tx = square.penitentiary_square_ptr->x + 10;
		ty = square.penitentiary_square_ptr->y + 10;
		break;
	}

	circle(tx, ty, 15);
	fillcircle(tx, ty, 15);

}
void draw_player_black() {
	setfillcolor(BLACK);
	int tx, ty;
	struct Square square = arr_list_square[player_black.index];
	switch (square.square_veriety) {
	case SPACE_SQUARE:
		tx = square.space_square_ptr->x - 10;
		ty = square.space_square_ptr->y - 10;
		break;
	case GROUND_SQUARE:
		tx = square.ground_square_ptr->x - 10;
		ty = square.ground_square_ptr->y - 10;
		break;
	case CHANCE_SQUARE:
		tx = square.chance_square_ptr->x - 10;
		ty = square.chance_square_ptr->y - 10;
		break;
	case BANK_SQUARE:
		tx = square.bank_square_ptr->x - 10;
		ty = square.bank_square_ptr->y - 10;
		break;
	case PENITENTIARY_SQUARE:
		tx = square.penitentiary_square_ptr->x - 10;
		ty = square.penitentiary_square_ptr->y - 10;
		break;
	}

	circle(tx, ty, 15);
	fillcircle(tx, ty, 15);
}
int throw_dice();
void draw_dice(int point) {
	IMAGE image_dice;
	//int res = throw_dice();
	switch (point) {
	case 1:
		loadimage(&image_dice, _T("./picture/dice_1.png"));
		break;
	case 2:
		loadimage(&image_dice, _T("./picture/dice_2.png"));
		break;
	case 3:
		loadimage(&image_dice, _T("./picture/dice_3.png"));
		break;
	case 4:
		loadimage(&image_dice, _T("./picture/dice_4.png"));
		break;
	case 5:
		loadimage(&image_dice, _T("./picture/dice_5.png"));
		break;
	case 6:
		loadimage(&image_dice, _T("./picture/dice_6.png"));
		break;
	}
	putimage(600, 150, &image_dice);
}
void draw_click_dice() {
	setfillcolor(BLUE);
	
	rectangle(560, 360, 750, 400);
	fillrectangle(560,360 ,750, 400);
	RECT r = { 560, 360, 750, 400 };
	drawtext(_T("Ͷ����"), &r, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}
void player_events(Player* player_ptr) {
	//switch (player_ptr->square_veriety) {
	//case GROUND_SQUARE:
		//if (player_ptr->ground_square_ptr->owner == nullptr) {
	HWND hnd = GetHWnd();
			char buf[128] = { 0 };
			sprintf_s(buf, "ȷ������%f����������", 10);
			int choice = MessageBox(hnd, CharToLPCTSTR(buf), _T("ȷ��"), MB_OKCANCEL | MB_ICONQUESTION);
			if (choice == IDOK) {
				if (player_ptr->money < player_ptr->ground_square_ptr->amount) {
					MessageBox(hnd, _T("����"), _T("ȷ��"), MB_OKCANCEL | MB_ICONQUESTION);
				}
				else {
					player_ptr->money -= player_ptr->ground_square_ptr->amount;
					player_ptr->ground_square_ptr->owner = player_ptr;
				}
			}
			else {
				//ʲô������
			}
		//}
		//break;
	// }
}
//Ͷ����
int  throw_dice() {
	srand(time(NULL));
	dice_points = (rand() % 6 + 1);
	return dice_points;
}
int main() {
	initgraph(width, height);//��ʼ������
	//���ñ���ͼƬ
	IMAGE background;
	loadimage(&background, _T("./picture/background.png"));
	putimage(0, 0, &background);
	//��ʼ����ͼ
	init_map();
	draw_dice(1);
	MOUSEMSG msg;
	while (!_kbhit()) { // ѭ��ֱ���м�������  
		msg = GetMouseMsg(); // ��ȡ�����Ϣ  
		if (msg.uMsg == WM_LBUTTONDOWN) { // ����������  
			if (msg.x >= 560 && msg.x <= 750 &&
				msg.y >= 360 && msg.y <= 400) {
				// ����ڰ�ť�ϵ���������¼�  
				draw_dice(throw_dice());
				if (is_player_white_or_black) {
					player_white.index = (dice_points + player_white.index) % 18;
					player_events(&player_white);
				}
				else {
					player_black.index = (dice_points + player_black.index) % 18;
					player_events(&player_black);
				}
				is_player_white_or_black = !is_player_white_or_black;
			}
		}
		draw_click_dice();
		draw_map();
	}
	system("pause");
	//setcolor()
	
}
