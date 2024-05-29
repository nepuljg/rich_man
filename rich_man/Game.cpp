#include<easyx.h>
#include<graphics.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#define PI 3.1415926535
#define NUM 100
const int width = 900;
const int height = 506;
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
struct Player{
	char name[64];//����
	double money;//��Ǯ
	char location[64];//λ��
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

struct bank_square arr_bank_square[2]; //�������и�2��
struct penitentiary_square arr_penitentiary_square[2];//���ü�����2��
struct chance_square arr_chance_square[2];//���û����2��
struct ground_square arr_ground_square[8];//�������ظ�
struct space_square arr_space_square[10];//���ÿյظ�

void init_map() {
	arr_space_square[0].x = 40;
	arr_space_square[0].y = 40;
	strcpy_s(arr_space_square[0].name, "�յ�");
	
	//����
	arr_ground_square[0].x = 20;
	arr_ground_square[0].y = 40;
	strcpy_s(arr_ground_square[0].name, "����");

	//
	
}
void draw_space_square(space_square* ptr) {
	setfillcolor(BLUE);
	int up_x = ptr->x  - 20;
	int up_y = ptr->y - 20;
	int down_x = ptr->x + 20;
	int down_y = ptr->y + 20;
	
	//�����η���
	rectangle(up_x, up_y, down_x, down_y);
	fillrectangle(up_x, up_y, down_x, down_y);
}
void DrawArrow(int x1, int y1, int x2, int y2, int arrowSize)
{
	// ���Ƽ��ˣ�ֱ�߲��֣�
	line(x1, y1, x2, y2);

	// �����ͷ�������ǵ�
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

	// ���Ƽ�ͷ�����������β���
	setfillcolor(BLACK);
	fillpoly(3, arr_1);
	//fillpoly(3, x1, y1, x2, y2, x4, y4);
}
//���õ�ͼ
void draw_map() {
	 //
	draw_space_square(&arr_space_square[0]);
	DrawArrow(60, 40, 80, 40, 40);
}
int main() {
	initgraph(width, height);//��ʼ������
	//���ñ���ͼƬ
	IMAGE background;
	loadimage(&background, _T("./picture/background.png"));
	putimage(0, 0, &background);
	//��ʼ����ͼ
	init_map();
	draw_map();
	system("pause");
}
