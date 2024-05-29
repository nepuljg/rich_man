#include<easyx.h>
#include<graphics.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#define PI 3.1415926535
#define NUM 100
const int width = 900;
const int height = 506;
enum chance { //机会种类
	get_money,
	lose_money,
	up,
	down
};
struct Location {
	int tx;
	int ty;
};
struct Player{
	char name[64];//名字
	double money;//金钱
	char location[64];//位置
};
//空方块
struct space_square {
	char name[64];
	int x;
	int y;
};
struct ground_square { //土地方块
	char name[64]; //名字
	int x; //位置
	int y; //位置
	double amount; //购买金额
	Player* owner;
};
//机会格
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
//监狱格子
struct penitentiary_square {
	char name[64];
	int x;
	int y;
};
struct lend_deposit{ //借和存
	double money; // 正为存，负为借
	Player* owner;
};
//银行格子(暂时设置为可贷款和存款)
struct bank_square {
	char name[64];
	int x;
	int y;
	lend_deposit arr[NUM];
	int index;//贷款或者借款的idx
};

struct bank_square arr_bank_square[2]; //设置银行格2个
struct penitentiary_square arr_penitentiary_square[2];//设置监狱格2个
struct chance_square arr_chance_square[2];//设置机会格2个
struct ground_square arr_ground_square[8];//设置土地格
struct space_square arr_space_square[10];//设置空地格

void init_map() {
	arr_space_square[0].x = 40;
	arr_space_square[0].y = 40;
	strcpy_s(arr_space_square[0].name, "空地");
	
	//土地
	arr_ground_square[0].x = 20;
	arr_ground_square[0].y = 40;
	strcpy_s(arr_ground_square[0].name, "土地");

	//
	
}
void draw_space_square(space_square* ptr) {
	setfillcolor(BLUE);
	int up_x = ptr->x  - 20;
	int up_y = ptr->y - 20;
	int down_x = ptr->x + 20;
	int down_y = ptr->y + 20;
	
	//画矩形方块
	rectangle(up_x, up_y, down_x, down_y);
	fillrectangle(up_x, up_y, down_x, down_y);
}
void DrawArrow(int x1, int y1, int x2, int y2, int arrowSize)
{
	// 绘制箭杆（直线部分）
	line(x1, y1, x2, y2);

	// 计算箭头的两个角点
	double angle = atan2(y1 - y2, x1 - x2);
	int x3 = x2 - arrowSize * cos(angle - PI / 6);
	int y3 = y2 - arrowSize * sin(angle - PI / 6);
	int x4 = x2 - arrowSize * cos(angle + PI / 6);
	int y4 = y2 - arrowSize * sin(angle + PI / 6);
	
	int arr_1[6], arr_2[6];
	arr_1[0] = x1;
	arr_1[1] = y1;
	arr_1[2] = x2;
	arr_1[3] = y2;
	arr_1[4] = x3;
	arr_1[5] = y3;

	// 绘制箭头的两个三角形部分
	setfillcolor(BLACK);
	fillpoly(3, arr_1);
	//fillpoly(3, x1, y1, x2, y2, x4, y4);
}
//画好地图
void draw_map() {
	 //
	draw_space_square(&arr_space_square[0]);
	DrawArrow(60, 40, 80, 40, 40);
}
int main() {
	initgraph(width, height);//初始化窗口
	//设置背景图片
	IMAGE background;
	loadimage(&background, _T("./picture/background.png"));
	putimage(0, 0, &background);
	//初始化地图
	init_map();
	draw_map();
	system("pause");
}
