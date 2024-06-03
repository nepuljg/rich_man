#include <Windows.h>
#include <conio.h>
#include <easyx.h>
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
    struct space_square *space_square_ptr;               //�յ�
    struct ground_square *ground_square_ptr;             //����
    struct chance_square *chance_square_ptr;             //����
    struct penitentiary_square *penitentiary_square_ptr; //����
    struct bank_square *bank_square_ptr;                 //����
  };
};
enum Chance { //��������
  GET_MONEY = 0,
  LOSE_MONEY,
  UP,
  DOWN
};

struct Player {
  double money = 500;
  int index = 0;
  Square_Veriety square_veriety;
  union {
    struct space_square *space_square_ptr;              //�յ�
    struct ground_square *ground_square_ptr;            //����
    struct chance_square *chance_square_ptr;            //����
    struct penitentiary_square *penitentiay_square_ptr; //����
    struct bank_square *bank_square_ptr;                //����
  };
};
//�շ���
struct space_square {
  int x;
  int y;
};
struct ground_square { //���ط���
  int x;               //λ��
  int y;               //λ��
  double amount = 100;
  Player *owner = nullptr;
};
//�����
struct chance_square {
  int x;
  int y;
  Chance chance;
  union {
    double money = 150;
    int num;
  };
};
//��������
struct penitentiary_square {
  int x;
  int y;
};
//���и���(����Ϊ�ɽ��)

struct bank_square {
  int x;
  int y;
  double money = 500;
  Player* player_ptr = nullptr;
};

Square arr_list_square[18];
int dice_points;
bool is_player_white_or_black = false;//�жϻغ���
int stop_round = 0;

struct bank_square arr_bank_square;                 //�������и�1��
struct penitentiary_square arr_penitentiary_square; //���ü�����1��
struct chance_square arr_chance_square[2];          //���û����2��
struct ground_square arr_ground_square[6];          //�������ظ�
struct space_square arr_space_square[8];            //���ÿյظ�
struct Player player_white;
struct Player player_black;

void init_map() {

  int index = 0;
  // 1 space 0
  arr_space_square[0].x = 40;
  arr_space_square[0].y = 40;

  arr_list_square[index].square_veriety = SPACE_SQUARE;
  arr_list_square[index].space_square_ptr = &arr_space_square[0];
  index++;

  // 2 ground 0
  arr_ground_square[0].x = 120;
  arr_ground_square[0].y = 40;

  arr_list_square[index].square_veriety = GROUND_SQUARE;
  arr_list_square[index].ground_square_ptr = &arr_ground_square[0];
  index++;
  // strcpy_s(arr_ground_square[0].name, "1");

  // 3 space 1
  arr_space_square[1].x = 200;
  arr_space_square[1].y = 40;

  arr_list_square[index].square_veriety = SPACE_SQUARE;
  arr_list_square[index].space_square_ptr = &arr_space_square[1];
  index++;
  // strcpy_s(arr_space_square[1].name, "2");
  // 4 space 2
  arr_space_square[2].x = 280;
  arr_space_square[2].y = 40;

  arr_list_square[index].square_veriety = SPACE_SQUARE;
  arr_list_square[index].space_square_ptr = &arr_space_square[2];
  index++;
  // strcpy_s(arr_space_square[2].name, "3");

  // 5 ground 1
  arr_ground_square[1].x = 360;
  arr_ground_square[1].y = 40;

  arr_list_square[index].square_veriety = GROUND_SQUARE;
  arr_list_square[index].ground_square_ptr = &arr_ground_square[1];
  index++;
  // strcpy_s(arr_ground_square[0].name, "2");

  // 6 ground 2
  arr_ground_square[2].x = 440;
  arr_ground_square[2].y = 40;

  arr_list_square[index].square_veriety = GROUND_SQUARE;
  arr_list_square[index].ground_square_ptr = &arr_ground_square[2];
  index++;
  // strcpy_s(arr_ground_square[0].name, "3");

  // 7 chance 0
  arr_chance_square[0].x = 440;
  arr_chance_square[0].y = 120;

  arr_list_square[index].square_veriety = CHANCE_SQUARE;
  arr_list_square[index].chance_square_ptr = &arr_chance_square[0];
  index++;
  // strcpy_s(arr_chance_square[0].name, "1");
  // 8 penitentiary
  arr_penitentiary_square.x = 440;
  arr_penitentiary_square.y = 200;

  arr_list_square[index].square_veriety = PENITENTIARY_SQUARE;
  arr_list_square[index].penitentiary_square_ptr = &arr_penitentiary_square;
  index++;

  // 9 space 3
  arr_space_square[3].x = 440;
  arr_space_square[3].y = 280;

  arr_list_square[index].square_veriety = SPACE_SQUARE;
  arr_list_square[index].space_square_ptr = &arr_space_square[3];
  index++;
  // strcpy_s(arr_space_square[3].name, "4");
  // 10 ground 3
  arr_ground_square[3].x = 440;
  arr_ground_square[3].y = 360;

  arr_list_square[index].square_veriety = GROUND_SQUARE;
  arr_list_square[index].ground_square_ptr = &arr_ground_square[3];
  index++;
  // strcpy_s(arr_ground_square[3].name, "4");

  // 11 space 4
  arr_space_square[4].x = 360;
  arr_space_square[4].y = 360;

  arr_list_square[index].square_veriety = SPACE_SQUARE;
  arr_list_square[index].space_square_ptr = &arr_space_square[4];
  index++;
  // strcpy_s(arr_space_square[0].name, "5");

  // 12 ground 4
  arr_ground_square[4].x = 280;
  arr_ground_square[4].y = 360;

  arr_list_square[index].square_veriety = GROUND_SQUARE;
  arr_list_square[index].ground_square_ptr = &arr_ground_square[4];
  index++;
  // strcpy_s(arr_ground_square[0].name, "5");

  // 13 ground 5
  arr_ground_square[5].x = 200;
  arr_ground_square[5].y = 360;

  arr_list_square[index].square_veriety = GROUND_SQUARE;
  arr_list_square[index].ground_square_ptr = &arr_ground_square[5];
  index++;
  // strcpy_s(arr_ground_square[0].name, "6");
  // 14 space 5
  arr_space_square[5].x = 120;
  arr_space_square[5].y = 360;

  arr_list_square[index].square_veriety = SPACE_SQUARE;
  arr_list_square[index].space_square_ptr = &arr_space_square[5];
  index++;
  // strcpy_s(arr_space_square[5].name, "6");
  // 15 space 6
  arr_space_square[6].x = 40;
  arr_space_square[6].y = 360;

  arr_list_square[index].square_veriety = SPACE_SQUARE;
  arr_list_square[index].space_square_ptr = &arr_space_square[6];
  index++;
  // strcpy_s(arr_space_square[6].name, "7");
  // 16 bank
  arr_bank_square.x = 40;
  arr_bank_square.y = 280;

  arr_list_square[index].square_veriety = BANK_SQUARE;
  arr_list_square[index].bank_square_ptr = &arr_bank_square;
  index++;
  // strcpy_s(arr_bank_square.name, "");

  // 17 chance 1
  arr_chance_square[1].x = 40;
  arr_chance_square[1].y = 200;

  arr_list_square[index].square_veriety = CHANCE_SQUARE;
  arr_list_square[index].chance_square_ptr = &arr_chance_square[1];
  index++;
  // strcpy_s(arr_chance_square[1].name, "2");
  // 18 space 7
  arr_space_square[7].x = 40;
  arr_space_square[7].y = 120;

  arr_list_square[index].square_veriety = SPACE_SQUARE;
  arr_list_square[index].space_square_ptr = &arr_space_square[7];
  index++;

  // init player
  player_white.square_veriety = SPACE_SQUARE;
  player_white.space_square_ptr = &arr_space_square[0];

  player_black.square_veriety = SPACE_SQUARE;
  player_black.space_square_ptr = &arr_space_square[0];

  player_white.money = 500;
  player_black.money = 500;
  
  player_white.index = 0;
  player_black.index = 0;
}
void draw_ground_square(ground_square *ptr) {
  setfillcolor(BLUE);
  circle(ptr->x, ptr->y, 40);
  fillcircle(ptr->x, ptr->y, 40);

  int text_height = textheight('A');
  int text_width = textwidth(_T("����"));

  int text_x = ptr->x - text_width / 2;
  int text_y = ptr->y - text_height / 2;

  outtextxy(text_x, text_y, _T("����"));
}
void draw_bank_square(bank_square *ptr) {
  setfillcolor(BROWN);
  circle(ptr->x, ptr->y, 40);
  fillcircle(ptr->x, ptr->y, 40);

  int text_height = textheight('A');
  int text_width = textwidth(_T("����"));

  int text_x = ptr->x - text_width / 2;
  int text_y = ptr->y - text_height / 2;

  outtextxy(text_x, text_y, _T("����"));
}
void draw_chance_square(chance_square *ptr) {
  setfillcolor(GREEN);
  circle(ptr->x, ptr->y, 40);
  fillcircle(ptr->x, ptr->y, 40);

  int text_height = textheight('A');
  int text_width = textwidth(_T("����"));

  int text_x = ptr->x - text_width / 2;
  int text_y = ptr->y - text_height / 2;

  outtextxy(text_x, text_y, _T("����"));
}
void draw_penitentiary_square(penitentiary_square *ptr) {
  setfillcolor(0x800080);
  circle(ptr->x, ptr->y, 40);
  fillcircle(ptr->x, ptr->y, 40);

  int text_height = textheight('A');
  int text_width = textwidth(_T("����"));

  int text_x = ptr->x - text_width / 2;
  int text_y = ptr->y - text_height / 2;

  outtextxy(text_x, text_y, _T("����"));
}

void draw_space_square(space_square *ptr) {
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
void acquire_result();

LPCTSTR CharToLPCTSTR(const char *ansiStr) {
  if (ansiStr == NULL)
    return NULL;

  size_t ansiStrLen = strlen(ansiStr) + 1; // ����������'\0'
  int wideStrLen = MultiByteToWideChar(CP_ACP, 0, ansiStr, ansiStrLen, NULL, 0);
  if (wideStrLen == 0) {
    // ������...
    return NULL;
  }

  wchar_t *wideStr = (wchar_t *)malloc(wideStrLen * sizeof(wchar_t));
  if (wideStr == NULL) {
    // ������...
    return NULL;
  }

  MultiByteToWideChar(CP_ACP, 0, ansiStr, ansiStrLen, wideStr, wideStrLen);
  return wideStr; // ע�⣺���ص�ָ����Ҫ��ʹ�ú��ͷţ�
}
void draw_player_result() {

  char player_white_buf[128] = {0};
  char player_black_buf[128] = {0};
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
  fillrectangle(560, 360, 750, 400);
  RECT r = {560, 360, 750, 400};
  drawtext(_T("Ͷ����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void player_events(Player *player_ptr) {
  HWND hnd = GetHWnd();
  switch (player_ptr->square_veriety) {
  case GROUND_SQUARE: {
    if (player_ptr->ground_square_ptr->owner == nullptr) {
      char buf[128] = {0};
      sprintf_s(buf, "ȷ������%f����������",
                player_ptr->ground_square_ptr->amount);
      int choice = MessageBox(hnd, CharToLPCTSTR(buf), _T("ȷ��"),
                              MB_OKCANCEL | MB_ICONQUESTION);
      if (choice == IDOK) {
        if (player_ptr->money < player_ptr->ground_square_ptr->amount) {
          MessageBox(hnd, _T("����"), _T("ȷ��"),
                     MB_OKCANCEL | MB_ICONQUESTION);
        } else {
          player_ptr->money -= player_ptr->ground_square_ptr->amount;
          player_ptr->ground_square_ptr->owner = player_ptr;
        }
      } else {
        //ʲô������
      }
    } else if (player_ptr->ground_square_ptr->owner != player_ptr) {
      char buf[128];
      sprintf_s(buf, "Sorry,����Ҫ����·��%f",
                player_ptr->ground_square_ptr->amount);
      MessageBox(hnd, CharToLPCTSTR(buf), _T("ȷ��"),
                 MB_OKCANCEL | MB_ICONQUESTION);
      player_ptr->money -= player_ptr->ground_square_ptr->amount;
      player_ptr->ground_square_ptr->owner->money +=
          player_ptr->ground_square_ptr->amount;
    }
    break;
  }
  case CHANCE_SQUARE: {
    chance_square *ptr = player_ptr->chance_square_ptr;
    srand(time(NULL));
    int enum_idx = rand() % 4;
    ptr->chance = (Chance)enum_idx;
    switch (ptr->chance) {
    case GET_MONEY: {
      player_ptr->money += ptr->money;
      char buf1[128] = {0};
      sprintf_s(buf1, "��ϲ��ȡ%fԪ���!", ptr->money);
      MessageBox(hnd, CharToLPCTSTR(buf1), _T("ȷ��"),
                 MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
    case LOSE_MONEY: {
      player_ptr->money -= ptr->money;
      char buf2[128] = {0};
      sprintf_s(buf2, "Sorry, ����Ҫʧȥ%fԪ���!", ptr->money);
      MessageBox(hnd, CharToLPCTSTR(buf2), _T("ȷ��"),
                 MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
    case UP: {
      player_ptr->index = (player_ptr->index + ptr->num) % 18;
      char buf3[128] = {0};
      sprintf_s(buf3, "��ϲ��ö���ǰ��%d��", ptr->num);
      MessageBox(hnd, CharToLPCTSTR(buf3), _T("ȷ��"),
                 MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
    case DOWN: {
      player_ptr->index = (player_ptr->index - ptr->num + 18) % 18;
      char buf4[128] = {0};
      sprintf_s(buf4, "Sorry, ����Ҫ����%d��", ptr->num);
      MessageBox(hnd, CharToLPCTSTR(buf4), _T("ȷ��"),
                 MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
    }
    break;
  }
  case PENITENTIARY_SQUARE: {
    stop_round = 2;
    is_player_white_or_black = !is_player_white_or_black;
    MessageBox(hnd, _T("Sorry, ����Ҫ��ͣһ�غ�"), _T("ȷ��"),
               MB_OKCANCEL | MB_ICONQUESTION);
    break;
  }
  case BANK_SQUARE: {
    if (arr_bank_square.player_ptr == player_ptr) {
        MessageBox(hnd, _T("��ã���֮ǰ���500��������Ҫ��650Ԫ"), _T("ȷ��"), MB_OKCANCEL | MB_ICONQUESTION);
        player_ptr->money -= 650;
        arr_bank_square.player_ptr = nullptr;
    }
    else if (arr_bank_square.player_ptr == nullptr) {
        int choice = MessageBox(hnd, _T("��ã��Ƿ���Ҫ���500Ԫ������30%��Ϣ����"), _T("ȷ��"), MB_OKCANCEL | MB_ICONQUESTION);
        if (choice == IDOK) {
            player_ptr->money += 500;
            arr_bank_square.player_ptr = player_ptr;
        }
    }
    break;
  }
  }
}
void draw_start_game() {
  while (1) {
    initgraph(width, height); //��ʼ������
    IMAGE background;
    loadimage(&background, _T("./picture/background.png"));
    putimage(0, 0, &background);

    IMAGE btn_start;
    loadimage(&btn_start, _T("./picture/StartgameButton.png"));
    putimage(340, 300, &btn_start);
    bool flag = false;
    MOUSEMSG msg;
    while (!_kbhit()) {                 // ѭ��ֱ���м�������
      msg = GetMouseMsg();              // ��ȡ�����Ϣ
      if (msg.uMsg == WM_LBUTTONDOWN) { // ����������
        if (msg.x >= 340 && msg.x <= 340 + 213 && msg.y >= 300 &&
            msg.y <= 300 + 86) {
          flag = true;
          break;
        }
      }
    }
    if (flag)
      break;
  }
  closegraph();
}
//Ͷ����
int throw_dice() {
  srand(time(NULL));
  dice_points = (rand() % 6 + 1);
  return dice_points;
}
int main() {
start:
  draw_start_game();
  initgraph(width, height); //��ʼ������
                            //���ñ���ͼƬ
  IMAGE background;
  loadimage(&background, _T("./picture/background.png"));
  putimage(0, 0, &background);
  //��ʼ����ͼ
  init_map();
  draw_dice(1);
  MOUSEMSG msg;
  while (!_kbhit()) {                  // ѭ��ֱ���м�������
    msg = GetMouseMsg();              // ��ȡ�����Ϣ
    if (msg.uMsg == WM_LBUTTONDOWN) { // ����������
      if (msg.x >= 560 && msg.x <= 750 && msg.y >= 360 && msg.y <= 400) {
        // ����ڰ�ť�ϵ���������¼�
        draw_dice(throw_dice());
        if (is_player_white_or_black) {
          player_white.index = (dice_points + player_white.index) % 18;
          int idx = player_white.index;
          switch (arr_list_square[idx].square_veriety) {
          case SPACE_SQUARE: {
            player_white.square_veriety = SPACE_SQUARE;
            player_white.space_square_ptr =
                arr_list_square[idx].space_square_ptr;
            break;
          }
          case GROUND_SQUARE: {
            player_white.square_veriety = GROUND_SQUARE;
            player_white.ground_square_ptr =
                arr_list_square[idx].ground_square_ptr;
            break;
          }
          case PENITENTIARY_SQUARE: {
            player_white.square_veriety = PENITENTIARY_SQUARE;
            player_white.penitentiay_square_ptr =
                arr_list_square[idx].penitentiary_square_ptr;
            break;
          }
          case CHANCE_SQUARE: {
            player_white.square_veriety = CHANCE_SQUARE;
            player_white.chance_square_ptr =
                arr_list_square[idx].chance_square_ptr;
            break;
          }
          case BANK_SQUARE: {
            player_white.square_veriety = BANK_SQUARE;
            player_white.bank_square_ptr = arr_list_square[idx].bank_square_ptr;
            break;
          }
          }
          draw_map();
          player_events(&player_white);
        } else {
          player_black.index = (dice_points + player_black.index) % 18;
          int idx = player_black.index;
          switch (arr_list_square[idx].square_veriety) {
          case SPACE_SQUARE: {
            player_black.square_veriety = SPACE_SQUARE;
            player_black.space_square_ptr =
                arr_list_square[idx].space_square_ptr;
            break;
          }
          case GROUND_SQUARE: {
            player_black.square_veriety = GROUND_SQUARE;
            player_black.ground_square_ptr =
                arr_list_square[idx].ground_square_ptr;
            break;
          }
          case PENITENTIARY_SQUARE: {
            player_black.square_veriety = PENITENTIARY_SQUARE;
            player_black.penitentiay_square_ptr =
                arr_list_square[idx].penitentiary_square_ptr;
            break;
          }
          case CHANCE_SQUARE: {
            player_black.square_veriety = CHANCE_SQUARE;
            player_black.chance_square_ptr =
                arr_list_square[idx].chance_square_ptr;
            break;
          }
          case BANK_SQUARE: {
            player_black.square_veriety = BANK_SQUARE;
            player_black.bank_square_ptr = arr_list_square[idx].bank_square_ptr;
            break;
          }
          }
          draw_map();
          player_events(&player_black);
        }
        if (!stop_round) {
            is_player_white_or_black = !is_player_white_or_black;
        }
        else {
            stop_round--;
        }

      }
    }
    if (is_player_white_or_black) outtextxy(40, 430, _T("��Ϸ�غϣ���ɫ���"));
    else outtextxy(40, 430, _T("��Ϸ�غϣ���ɫ���"));
    draw_click_dice();
    draw_map();
    HWND hnd = GetHWnd();
    if (player_black.money < 0) {
      MessageBox(hnd, _T("��Ϸ�����ˣ���ɫ����Ʋ��ˣ���ɫ��һ�ʤ!"),
                 _T("ȷ��"), MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
    if (player_white.money < 0) {
      MessageBox(hnd, _T("��Ϸ�����ˣ���ɫ����Ʋ��ˣ���ɫ��һ�ʤ!"),
                 _T("ȷ��"), MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
  }
  closegraph();
  goto start;

  system("pause");
}
