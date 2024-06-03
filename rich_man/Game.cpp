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
    struct space_square *space_square_ptr;               //空地
    struct ground_square *ground_square_ptr;             //土地
    struct chance_square *chance_square_ptr;             //机会
    struct penitentiary_square *penitentiary_square_ptr; //监狱
    struct bank_square *bank_square_ptr;                 //银行
  };
};
enum Chance { //机会种类
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
    struct space_square *space_square_ptr;              //空地
    struct ground_square *ground_square_ptr;            //土地
    struct chance_square *chance_square_ptr;            //机会
    struct penitentiary_square *penitentiay_square_ptr; //监狱
    struct bank_square *bank_square_ptr;                //银行
  };
};
//空方块
struct space_square {
  int x;
  int y;
};
struct ground_square { //土地方块
  int x;               //位置
  int y;               //位置
  double amount = 100;
  Player *owner = nullptr;
};
//机会格
struct chance_square {
  int x;
  int y;
  Chance chance;
  union {
    double money = 150;
    int num;
  };
};
//监狱格子
struct penitentiary_square {
  int x;
  int y;
};
//银行格子(设置为可借款)

struct bank_square {
  int x;
  int y;
  double money = 500;
  Player* player_ptr = nullptr;
};

Square arr_list_square[18];
int dice_points;
bool is_player_white_or_black = false;//判断回合数
int stop_round = 0;

struct bank_square arr_bank_square;                 //设置银行格1个
struct penitentiary_square arr_penitentiary_square; //设置监狱格1个
struct chance_square arr_chance_square[2];          //设置机会格2个
struct ground_square arr_ground_square[6];          //设置土地格
struct space_square arr_space_square[8];            //设置空地格
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
  int text_width = textwidth(_T("土地"));

  int text_x = ptr->x - text_width / 2;
  int text_y = ptr->y - text_height / 2;

  outtextxy(text_x, text_y, _T("土地"));
}
void draw_bank_square(bank_square *ptr) {
  setfillcolor(BROWN);
  circle(ptr->x, ptr->y, 40);
  fillcircle(ptr->x, ptr->y, 40);

  int text_height = textheight('A');
  int text_width = textwidth(_T("银行"));

  int text_x = ptr->x - text_width / 2;
  int text_y = ptr->y - text_height / 2;

  outtextxy(text_x, text_y, _T("银行"));
}
void draw_chance_square(chance_square *ptr) {
  setfillcolor(GREEN);
  circle(ptr->x, ptr->y, 40);
  fillcircle(ptr->x, ptr->y, 40);

  int text_height = textheight('A');
  int text_width = textwidth(_T("机会"));

  int text_x = ptr->x - text_width / 2;
  int text_y = ptr->y - text_height / 2;

  outtextxy(text_x, text_y, _T("机会"));
}
void draw_penitentiary_square(penitentiary_square *ptr) {
  setfillcolor(0x800080);
  circle(ptr->x, ptr->y, 40);
  fillcircle(ptr->x, ptr->y, 40);

  int text_height = textheight('A');
  int text_width = textwidth(_T("监狱"));

  int text_x = ptr->x - text_width / 2;
  int text_y = ptr->y - text_height / 2;

  outtextxy(text_x, text_y, _T("监狱"));
}

void draw_space_square(space_square *ptr) {
  setfillcolor(RED);
  circle(ptr->x, ptr->y, 40);
  fillcircle(ptr->x, ptr->y, 40);
  int text_height = textheight('A');
  int text_width = textwidth(_T("空地"));

  int text_x = ptr->x - text_width / 2;
  int text_y = ptr->y - text_height / 2;

  outtextxy(text_x, text_y, _T("空地"));
}
//画好地图
void draw_player_white();
void draw_player_black();
void acquire_result();

LPCTSTR CharToLPCTSTR(const char *ansiStr) {
  if (ansiStr == NULL)
    return NULL;

  size_t ansiStrLen = strlen(ansiStr) + 1; // 包括结束符'\0'
  int wideStrLen = MultiByteToWideChar(CP_ACP, 0, ansiStr, ansiStrLen, NULL, 0);
  if (wideStrLen == 0) {
    // 错误处理...
    return NULL;
  }

  wchar_t *wideStr = (wchar_t *)malloc(wideStrLen * sizeof(wchar_t));
  if (wideStr == NULL) {
    // 错误处理...
    return NULL;
  }

  MultiByteToWideChar(CP_ACP, 0, ansiStr, ansiStrLen, wideStr, wideStrLen);
  return wideStr; // 注意：返回的指针需要在使用后释放！
}
void draw_player_result() {

  char player_white_buf[128] = {0};
  char player_black_buf[128] = {0};
  sprintf_s(player_white_buf, "白色玩家金额:%f", player_white.money);
  sprintf_s(player_black_buf, "黑色玩家金额:%f", player_black.money);
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
  drawtext(_T("投骰子"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void player_events(Player *player_ptr) {
  HWND hnd = GetHWnd();
  switch (player_ptr->square_veriety) {
  case GROUND_SQUARE: {
    if (player_ptr->ground_square_ptr->owner == nullptr) {
      char buf[128] = {0};
      sprintf_s(buf, "确定花费%f购买土地吗",
                player_ptr->ground_square_ptr->amount);
      int choice = MessageBox(hnd, CharToLPCTSTR(buf), _T("确认"),
                              MB_OKCANCEL | MB_ICONQUESTION);
      if (choice == IDOK) {
        if (player_ptr->money < player_ptr->ground_square_ptr->amount) {
          MessageBox(hnd, _T("金额不够"), _T("确认"),
                     MB_OKCANCEL | MB_ICONQUESTION);
        } else {
          player_ptr->money -= player_ptr->ground_square_ptr->amount;
          player_ptr->ground_square_ptr->owner = player_ptr;
        }
      } else {
        //什么都不做
      }
    } else if (player_ptr->ground_square_ptr->owner != player_ptr) {
      char buf[128];
      sprintf_s(buf, "Sorry,你需要交过路费%f",
                player_ptr->ground_square_ptr->amount);
      MessageBox(hnd, CharToLPCTSTR(buf), _T("确定"),
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
      sprintf_s(buf1, "恭喜获取%f元金额!", ptr->money);
      MessageBox(hnd, CharToLPCTSTR(buf1), _T("确定"),
                 MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
    case LOSE_MONEY: {
      player_ptr->money -= ptr->money;
      char buf2[128] = {0};
      sprintf_s(buf2, "Sorry, 你需要失去%f元金额!", ptr->money);
      MessageBox(hnd, CharToLPCTSTR(buf2), _T("确定"),
                 MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
    case UP: {
      player_ptr->index = (player_ptr->index + ptr->num) % 18;
      char buf3[128] = {0};
      sprintf_s(buf3, "恭喜获得额外前进%d步", ptr->num);
      MessageBox(hnd, CharToLPCTSTR(buf3), _T("确定"),
                 MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
    case DOWN: {
      player_ptr->index = (player_ptr->index - ptr->num + 18) % 18;
      char buf4[128] = {0};
      sprintf_s(buf4, "Sorry, 你需要后退%d步", ptr->num);
      MessageBox(hnd, CharToLPCTSTR(buf4), _T("确定"),
                 MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
    }
    break;
  }
  case PENITENTIARY_SQUARE: {
    stop_round = 2;
    is_player_white_or_black = !is_player_white_or_black;
    MessageBox(hnd, _T("Sorry, 你需要暂停一回合"), _T("确定"),
               MB_OKCANCEL | MB_ICONQUESTION);
    break;
  }
  case BANK_SQUARE: {
    if (arr_bank_square.player_ptr == player_ptr) {
        MessageBox(hnd, _T("你好，你之前借款500，现在需要还650元"), _T("确认"), MB_OKCANCEL | MB_ICONQUESTION);
        player_ptr->money -= 650;
        arr_bank_square.player_ptr = nullptr;
    }
    else if (arr_bank_square.player_ptr == nullptr) {
        int choice = MessageBox(hnd, _T("你好，是否需要借款500元，将以30%利息偿还"), _T("确认"), MB_OKCANCEL | MB_ICONQUESTION);
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
    initgraph(width, height); //初始化窗口
    IMAGE background;
    loadimage(&background, _T("./picture/background.png"));
    putimage(0, 0, &background);

    IMAGE btn_start;
    loadimage(&btn_start, _T("./picture/StartgameButton.png"));
    putimage(340, 300, &btn_start);
    bool flag = false;
    MOUSEMSG msg;
    while (!_kbhit()) {                 // 循环直到有键盘输入
      msg = GetMouseMsg();              // 获取鼠标消息
      if (msg.uMsg == WM_LBUTTONDOWN) { // 鼠标左键按下
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
//投骰子
int throw_dice() {
  srand(time(NULL));
  dice_points = (rand() % 6 + 1);
  return dice_points;
}
int main() {
start:
  draw_start_game();
  initgraph(width, height); //初始化窗口
                            //设置背景图片
  IMAGE background;
  loadimage(&background, _T("./picture/background.png"));
  putimage(0, 0, &background);
  //初始化地图
  init_map();
  draw_dice(1);
  MOUSEMSG msg;
  while (!_kbhit()) {                  // 循环直到有键盘输入
    msg = GetMouseMsg();              // 获取鼠标消息
    if (msg.uMsg == WM_LBUTTONDOWN) { // 鼠标左键按下
      if (msg.x >= 560 && msg.x <= 750 && msg.y >= 360 && msg.y <= 400) {
        // 鼠标在按钮上点击，触发事件
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
    if (is_player_white_or_black) outtextxy(40, 430, _T("游戏回合：白色玩家"));
    else outtextxy(40, 430, _T("游戏回合：黑色玩家"));
    draw_click_dice();
    draw_map();
    HWND hnd = GetHWnd();
    if (player_black.money < 0) {
      MessageBox(hnd, _T("游戏结束了，黑色玩家破产了，白色玩家获胜!"),
                 _T("确认"), MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
    if (player_white.money < 0) {
      MessageBox(hnd, _T("游戏结束了，白色玩家破产了，黑色玩家获胜!"),
                 _T("确认"), MB_OKCANCEL | MB_ICONQUESTION);
      break;
    }
  }
  closegraph();
  goto start;

  system("pause");
}
