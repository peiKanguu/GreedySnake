#include<iostream>
#include<conio.h>
#include<graphics.h>
#include <windows.h>
#include <random>
using namespace std;
/*
    �˵�����:
        ��ʼ��Ϸ: ��������ѡ�����
        �˳�: ��ӡ�˳���Ϸ���桰лл֧�֡����˳�����

    ����ѡ����棺
        �ṩ3����ť��
            <��>---������Ϊx1
            <����>---������Ϊx2
            <����>---������Ϊx4
        ��������Ѷȼ��ɽ�����Ϸ����

    ��Ϸ����:
        չʾ: չʾ��ͼ �� ʳ�� ǽ�ȵ�����
        ��ʱ�ƶ�: �߻ᶨʱ�ƶ�
            ���ܻ���������/ǽ ����
            �����ǿյ� �����ƶ�
            ������ʳ�� ����+1 ԭ�ȵ�ʳ����ʧ  ������ʳ�� ���ƶ�һ��
        �������:
            ����Ƿ����: �޸��ߵķ��򣨲��ܳ��������ƶ���
            ����ǿո�: ��ͣ��Ϸ��������ͣ����
            �����esc: ��ͣ��Ϸ��������ͣ����
        ����չʾ:
            ��ѡģʽ <>
            ��ǰ���� []
            ��ʾ�ʣ�����ʹ�á�WASD��������ϵķ�����������ߵ��ƶ���

    ��ͣ���棺
        ��ʾ ����Ϸ����ͣ��
        �ṩ���������˵����͡�������Ϸ��������ť

    ������棺
        ��ʾ��ǰ��Ϸ�Ľ���͵÷�
        �ṩ3����ť
        ������һ�֡�����������Ѷ�ѡ�����
        ���˳���Ϸ���������ӡ�˳���Ϸ���沢�˳���Ϸ
        ���˽⿪����Ա�����������ף������

    ף�����棺
        ��ʾף���Ｐ�����������Ϣ
        �ṩһ����ť
        ������һ�֡�

    �������棺
        ��ʾ��л
        ������Ϸ
*/

// -------------------- ������� --------------------
/*
    �궨��H��W���ֱ��ʾ���ڽ���ĸߺͿ�
    ��������֮�������initgraph(W, H);
    �궨��MAP_H��MAP_W���ֱ��ʾ��Ϸ����������Ϸչʾ���ݵĸߣ��񣩺Ϳ���
*/
#define H 480
#define W 640
#define MAP_H 60
#define MAP_W 80

/*
    ����һ��
    һ���С5*5��չʾmap�е����ݶ���һ��һ��չʾ
*/

/*
     ��ͼ:
     map[n][m]: ��ͼ����(n,m)
     0��ʾ�յ� 1��ʾǽ 2��ʾʳ��
     map[3][5] = 2 //��ͼ(3,5)��ʳ��
*/
int map[MAP_H][MAP_W];

/*
    ����
    s[n][m]: �ߵĵ�n�������m����
    m=0 ��ʾx����  m=1 ��ʾy����
    ��ͷ��s[0]
    s[3][0] = 5, s[3][1] =7;
    ��ʾ�ߵĵ�4������ ������(5,7)
*/
int s[(MAP_H - 2) * (MAP_W - 2)][2];

/*
    �ߵĳ��ȣ�
    len��ʾ�� ��ǰ�ĳ���
*/
int len;

/*
    �Ѷȱ�ʾ����
    ���������ֱ�ʾ�Ѷȣ�1-�򵥣�2-���ѣ�4-����
*/
int flag;

/*
    currentMark��ʾ��ǰ�ɼ�
    targetMark��ʾĿ��ɼ�
    ������ʱcurrentMark>=targetMarkʱ������ʾ��Ϸʤ����������ʾ��Ϸʧ��
    speed��ʾ���ƶ��Ŀ�����speedԽ�����ƶ�Խ��
*/
int currentMark,speed,targetMark = 20;

/*
    �ߵ��˶�����
    w  a  s  d--->�� �� �� ��
    ���磺char direction=��w��;��ʾ�˶�����Ϊ��
*/
char direction;
// -------------------- ������� --------------------


// -------------------- service --------------------
/*
service ��Ҫ�ṩ����ʳ��
service ��Ҫ�ṩ��ʼ������
service �ṩһ���޸ķ���ĺ���
service �ṩһ����������ָ�ִ�еĺ���
service �ṩ�ж�ʤ���ĺ���
service �ṩ�ƶ�һ��ĺ���
service �ṩ������ײ�ж�ִ�ж�Ӧָ��ĺ���
*/

/*
    ������:С��
����: ����ʳ��
    �����������������ʳ�����ʳ��ʱҪ�ܿ��ߵ������ǽ��
    ����: void
    ����ֵ: void
*/
void foodCreat();

/*
    ������:С��
    ����: ��ʼ����Ϸ����
    �ɼ�,�ٶȣ�����flag������difficultySelectionView();����ʼ����

    s[][]�ߣ���ͷ+����,�ߵĳ���Ϊ3����ʼ�������ң�
    map[][]ǽ���յأ�ʳ�����foodCreat������
    ����: void
    ����ֵ: void
*/
void init();

/*
    ������:Jane
    ����: �������뷽������жϣ��ı��ƶ�����
    ����: ch��������ķ���
    ����ֵ: void
*/
void turnDirection(char ch);

/*
    ������:��Ϧ
    ����: �ж��������루ʹ��_kbhit()�������л�ȡ������ȡ����ָ�input = _getch();��
            �����������ָ��ִ��:
            �����: �޸��ߵķ��򣨵���turnDirection������
            �ո��esc: ��ͣ��Ϸ��������ͣ���棨����pauseView()��
    ����: void
    ����ֵ: void
*/
void input_Add_Execute(int&);

/*
    ������:С��
    ����: ���ݵ�ǰ�ɼ���Ŀ������Ƚ��ж���Ϸ�Ƿ�ʤ��
    ������void
    ����ֵ:
        0 ��ʾûʧ��
        1 ��ʾ�ɹ�
*/
int isWin();


/*
    ������:С��
    ����: ����direction�ƶ��ߣ������ߵ�����
    ����: void
    ����ֵ: void
*/
void snakeMove();

/*
    ������:С��
    ����:��ײ�ж�
    �ж���ͷs[0]������͵�ͼ�غϵ������ִ������
            ��ʱ�ƶ�: �߻ᶨʱ�ƶ�
            ����ͷ��ǽ��������ײ
                ��������������㣬��ӡ������棨 ����settleView(iswin() ) ����
            ����ͷ��ʳ����ײ
                ԭ�ȵ�ʳ����ʧ  �߳���+1��ͷ���겻�䣬�������β����ʼ���ߺ󲿷�������³�ǰ����
                ���µ�ǰ�ɼ�   ������ʳ�����ʳ�����ɺ���foodCreat����;��
            ����ͷ���յ���ײ ���·��� ���ɲ�д��
*/
void judgeResult();
// -------------------- service --------------------



// -------------------- view --------------------
/*
    �����ˣ�С��
    ����: ��Ϸ�˵�
        ����easyX �˵�ҳ��

        ���������Ҫ������İ�ť
        ����ʼ��Ϸ����������ѡ����棬������difficultySelectionView()����
        ���˳���Ϸ����ӡ�˳���Ϸ���桰лл֧�֡����˳����򣬣�����endView()����
    ����: void
    ����ֵ: void
*/
void menuView();

/*
    ������:С��
    ����:��ӡ�Ѷ�ѡ����棬�ѵ�ѡ���м򵥣����ѣ�����
    ����easyX �Ѷ�ѡ��ҳ��
        ���������Ҫ������İ�ť
            ���򵥡�
            �����ѡ�
            ��������
        ��������Ѷȼ��ɽ�����Ϸ����
        ����������������������
            �򵥣�flag=4��
            ���ѣ�flag=8��
            ������flag=16��
    ������Ϸ���棨����gameView()��
    ����: void
    ����ֵ: void
*/
void difficultySelectionView();

/*
    ������:С��
    ����: ��Ϸ�����ӡ
    ����map���飨0�����յأ�1��������ǽ��2��������ʳ���snake[][]��
    ��easyX��ӡ��Ϸ���棬��Ҫ�����ⲿ���ݣ�
    ���磺
            ����չʾ:
            ��ѡģʽ <>
            ��ǰ���� []
            ��ʾ�ʣ�����ʹ�á�WASD��������ϵķ�����������ߵ��ƶ���
    ����: void
    ����ֵ: void
*/
void gameView_ShowMap();

/*
    ������:Jane
    ����: ��Ϸ��������
        ��ʼ����Ϸ����(���ú���init())
        while(1){
            ����speed��С�����ʱЧ��

            ��ӡ��Ϸ����(���ú���gameView_ShowMap())

            ��������������������ָ�ִ�У�����service��input_Add_Execute����������
            ���ƶ�һ�񣨵���snakeMove();��

            �ж���ͷ�͵�ͼ��������������������㣨judgeResult();��
        }
    ����: void
    ����ֵ: void
*/
void gameView();

/*
    ������:СP
    ����:
        ����easyX ̰���ߵ���ͣ���棨��ͣʱ�Զ���ת��
        ��ʾ ����Ϸ����ͣ��
        �ṩ���������˵����͡�������Ϸ��������ť
        ����������Ӧ����
        չʾ���ز˵��ͼ�����Ϸ����ѡ�
            �����������ѡ��
            �ٷ��ز˵�  ����menuView();
            �ڼ�����Ϸ  ֱ�ӽ��������ص�����Ϸ���棩
    ����: void
    ����ֵ: void
*/
void pauseView();

/*
    ������:С��
    ����:��ӡ��Ϸ�������
    ����iswin�ж��Ƿ�ʤ����isWin==1��ʾʤ����0��ʾʧ�ܣ�
    ����easyX ����ҳ��
    ��ʾ��ǰ��Ϸ�Ľ����ʤ�����͵÷�
    �ṩ3����ť����ѡ��
    ����������������������
        ������һ�֡�����������Ѷ�ѡ����棨����difficultySelectionView();��
        ���˳���Ϸ���������ӡ�˳���Ϸ���棨����endView()�������˳���Ϸ
        ���˽⿪����Ա�����������ף�����棨����intructionView()����
    ����: int isWin������isWin�����ķ���ֵ
    ����ֵ: void
*/
void settleView(int iswin);

/*
    ������:С��
    ����: ף������
        ����easyX ף��ҳ��
        ��ʾף���Ｐ�����������Ϣ

        �ṩ1����ť
        ������һ�֡�������difficultySelectionView();
    ����: void
    ����ֵ: void
*/
void intructionView();

/*
    �����ˣ�С��
    ���ܣ�
        ��easyX��ӡ�����ġ���Ϸ��������л֧�֡�ͼƬ
        ��һ��ʱ���ִ��exit��0��
    ������void
    ����ֵ��void
*/
void endView();
// -------------------- view --------------------
int main()
{
    menuView();
    return 0;
}

void foodCreat() {
    //���������
    std::random_device rd;
    std::mt19937  rand_num(rd());

    int num_x = rand_num() % (MAP_W - 5) + 1;
    int num_y = rand_num() % (MAP_H - 5) + 1;

    for (int i = 1; i <= (MAP_H - 2) * (MAP_W - 2); i++) {
        if (s[i][0] == 0)
            break;
        if (abs(num_x - s[i][0]) < 5) {
            if (abs(num_y - s[i][1]) < 5) {
                num_x = rand_num() % (MAP_W - 5) + 1;
                num_y = rand_num() % (MAP_H - 5) + 1;
            }
        }

    }
    map[num_y][num_x] = 2;
}

void init() {
    // ��ʼ����Ϸ����
    len = 3; // �߳���Ϊ3
    speed = flag; // �ٶ���flag����
    direction = 'd'; // ��ʼ�ƶ���������

    // ���������ڵ�ͼ������
    //��ͷ����(MAP_W / 2,MAP_H / 2)
    s[0][0] = MAP_W / 2;
    s[0][1] = MAP_H / 2;
    //��������
    s[1][0] = MAP_W / 2;
    s[1][1] = (MAP_H / 2) - 1;
    s[2][0] = MAP_W / 2;
    s[2][1] = (MAP_H / 2) - 2;

    // ��ʼ����Ϸ��ͼ
    for (int i = 0; i < MAP_H; ++i) {
        for (int j = 0; j < MAP_W; ++j) {
            if (i == 0 || i == MAP_H - 1 || j == 0 || j == MAP_W - 1) {
                map[i][j] = 1; // ����ǽ��Ϊ1
            }
            else {
                map[i][j] = 0; // ���ÿյ�Ϊ0
            }
        }
    }

    currentMark = 0; // ��ʼ������

    foodCreat(); // ��ʼ��ʳ��
}

void turnDirection(char ch) {
    //������Ĵ�д���Сд����ֹ����Ϸ��ʱ�򿪴�д������
    if (ch >= 'A' && ch <= 'Z')
    {
        ch = ch + 32;
    }

    //�޶�����ֻ���ĸ���
    if (ch != 'a' && ch != 'd' && ch != 'w' && ch != 's')
    {
        return;
    }
    //�޶�����


    /*����ì�ܵ����뷽��*/
    if (ch == 'a' && direction == 'd')
    {
        return;
    }
    if (ch == 'd' && direction == 'a')
    {
        return;
    }
    if (ch == 'w' && direction == 's')
    {
        return;
    }
    if (ch == 's' && direction == 'w')
    {
        return;
    }
    /*����ì�ܵ����뷽��*/

    direction = ch;
}

void input_Add_Execute(int& isPause) {
    if (_kbhit())//��ⰴ������
    {
        char input = _getch();//����������ַ�
        
        if (input == ' ' || input == 27)// 27��ESC��ASC||��27
        {
            pauseView();//�������Ϊ�ո��esc�����pauseview����
            isPause = 1;
        }
        else
        {
            turnDirection(input);//�������Ϊwasd�����turnDirection����
        }
    }
}

int isWin() {
    if (currentMark >= targetMark)
    {
        return 1;
    }
    return 0;
}

void snakeMove() {   //wsad �������������ң���turnDirection(char ch)�����иı䷽��õ�
    int i;
    //�ı�����
    for (i = len - 1; i > 0; i--)
    {
        s[i][0] = s[i - 1][0];
        s[i][1] = s[i - 1][1];
    }
    if (direction == 'w')      // �����ƶ�������ͷ�� y �����С
        s[i][0] -= 1;
    else if (direction == 's') // �����ƶ�������ͷ�� y ��������
        s[i][0] += 1;
    else if (direction == 'a') // �����ƶ�������ͷ�� x �����С
        s[i][1] -= 1;
    else if (direction == 'd')  // �����ƶ�������ͷ�� x ��������
        s[i][1] += 1;
}

void judgeResult() {
    // �ж���ͷ�Ƿ���ǽ����ײ
    if (s[0][0] < 0 || s[0][0] >= MAP_H || s[0][1] < 0 || s[0][1] >= MAP_W) {
        // ���������������
        // ���ý�����溯��
        settleView(isWin());
    }

    if (map[s[0][0]][s[0][1]] == 1)
    {
        settleView(isWin());
    }

    // �ж���ͷ�Ƿ�������������ײ
    for (int i = 1; i < len; i++) {
        if (s[i][0] == s[0][0] && s[i][1] == s[0][1]) {

            // ���ý�����溯��
            settleView(isWin());
            break;

        }
    }
    // �ж���ͷ�Ƿ���ʳ����ײ

    if (map[s[0][0]][s[0][1]] == 2) {//��ͷ��ʳ���ˣ����ȼ�һ
        map[s[0][0]][s[0][1]] = 0; // ԭ�ȵ�ʳ����ʧ    
        // �߳���+1
        if (direction == 'w')
        {
            s[len][0] = s[len - 1][0] - 1;
            s[len][1] = s[len - 1][1];
        }
        if (direction == 's')
        {
            s[len][0] = s[len - 1][0] + 1;
            s[len][1] = s[len - 1][1];
        }
        if (direction == 'a')
        {
            s[len][0] = s[len - 1][0];
            s[len][1] = s[len - 1][1] - 1;
        }
        if (direction == 'd')
        {
            s[len][0] = s[len - 1][0];
            s[len][1] = s[len - 1][1] + 1;
        }
        len++;
        currentMark++;//����+1
        // ������ʳ��
        foodCreat();
    }
}

void menuView() {
    initgraph(W, H);
    setbkcolor(BLACK);
    cleardevice();

    settextstyle(60, 0, "����");
    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    outtextxy(170, 50, "����̰����");
    setfillcolor(BLUE);
    solidrectangle(100, 200, 540, 260);
    solidrectangle(100, 300, 540, 360);

    settextcolor(BLACK);
    settextstyle(50, 0, "����");
    setbkmode(TRANSPARENT);
    char str1[] = "��ʼ��Ϸ";
    char str2[] = "�˳���Ϸ";
    int width1 = textwidth(str1);
    int height1 = textheight(str1);
    int width2 = textwidth(str2);
    int height2 = textheight(str2);
    int x_1 = 100 + 220 - width1 / 2;
    int y_1 = 200 + 30 - height1 / 2;
    int x_2 = 100 + 220 - width2 / 2;
    int y_2 = 300 + 30 - height2 / 2;
    outtextxy(x_1, y_1, str1);
    outtextxy(x_2, y_2, str2);
    while (1) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                if (msg.x < 540 && msg.x>100 && msg.y < 260 && msg.y>200) {

                    difficultySelectionView();
                }
                if (msg.x < 540 && msg.x>100 && msg.y < 360 && msg.y>300) {
                    cout << 2;
                    endView();
                }
            }
        }
    }
}

void difficultySelectionView() {
    cleardevice();
    initgraph(W, H);
    
    // ���������ť������ʹ�С
    int buttonWidth = 100;
    int buttonHeight = 50;
    int buttonX = 270;
    int buttonY[3] = { 150, 250, 350 };

    // ���ñ�����ɫΪ��ɫ
    setbkcolor(BLACK);
    cleardevice();

    // �����Ѷ�ѡ��ҳ��
    settextstyle(30, 0, _T("����"));
    outtextxy(240, 50, _T(" �Ѷ�ѡ�� "));

    // ���ư�ť
    settextstyle(20, 0, _T("����"));
    for (int i = 0; i < 3; i++) {
        setfillcolor(WHITE);
        fillrectangle(buttonX, buttonY[i], buttonX + buttonWidth, buttonY[i] + buttonHeight);
        outtextxy(buttonX + 20, buttonY[i] + 15, (i == 0) ? _T("��") : ((i == 1) ? _T("����") : _T("����")));
    }

    // ���������¼�
    while (true) {
        MOUSEMSG m;
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN) {
            bool yes = false;
            for (int i = 0; i < 3; i++) {
                if (m.x > buttonX && m.x < buttonX + buttonWidth && m.y > buttonY[i] && m.y < buttonY[i] + buttonHeight) {
                    // �û�����˰�ť
                    if (i == 0) {
                        flag = 4;  // ��
                    }
                    else if (i == 1) {
                        flag = 8;  // ����
                    }
                    else if (i == 2) {
                        flag = 16;  // ����
                    }
                    yes = true;
                    break;
                }
            }
            if(yes)break;
        }
    }

    // ������Ϸ����
    gameView();

    // �ر�ͼ�δ���
    closegraph();
}

void gameView_ShowMap() {
    cleardevice();
    static int LUX = 40; // ����x����
    static int LUY = 80; // ����y����
    static int RDX = 440; // ����x����
    static int RDY = 380; // ����y����
    // ���õ�Ԫ���СΪ5*5����ô��ߴ�Ϊ5
    static int squareSize = 5;
    // ��һ������
    //rectangle(0, 0, W, H);

    // ����Ϸ��������һ�����ڱ�ʾ��Ϸ��ͼ
    //rectangle(LUX, LUY, RDX, RDY);

    // ��ǽ��(��)��ʳ��(��)�Ϳյ�(��)�Բ�ͬ��ɫ��ʾ����
    for (int i = 0; i < MAP_H; i++) {
        for (int j = 0; j < MAP_W; j++) {
            if (map[i][j] == 0) {
                setfillcolor(WHITE);
                solidrectangle(LUX + j * squareSize, LUY + i * squareSize, LUX + (j + 1) * squareSize, LUY + (i + 1) * squareSize);
            }
            else if (map[i][j] == 1) {
                setfillcolor(BLACK);
                solidrectangle(LUX + j * squareSize, LUY + i * squareSize, LUX + (j + 1) * squareSize, LUY + (i + 1) * squareSize);
            }
            else if (map[i][j] == 2) {
                setfillcolor(RED);
                solidrectangle(LUX + j * squareSize, LUY + i * squareSize, LUX + (j + 1) * squareSize, LUY + (i + 1) * squareSize);
            }
        }
    }
    // ����������ɫΪ�Ϻ�ɫ
    settextcolor(MAGENTA);

    // ͨ�����������ӡ��
    for (int n = 0; n < len; n++) {
        setfillcolor(GREEN);
        solidrectangle(LUX + s[n][1] * squareSize, LUY + s[n][0] * squareSize, LUX + (s[n][1] + 1) * squareSize, LUY + (s[n][0] + 1) * squareSize);
    }

    // ��ʾ���ݡ���ѡģʽ��
    RECT mode = { 480, 80, 600, 130 };
    drawtext(_T("��ѡģʽ��"), &mode, DT_LEFT | DT_TOP); //�����  �϶���
    if (flag == 4) {
        // ��ʾ��ǰ�Ѷ�
        RECT mode1 = { 480, 130, 600, 180 };
        drawtext(_T("<��>"), &mode1, DT_CENTER | DT_TOP);//���Ķ���  �϶���
    }
    if (flag == 8) {
        // ��ʾ��ǰ�Ѷ�
        RECT mode2 = { 480, 130, 600, 180 };
        drawtext(_T("<����>"), &mode2, DT_CENTER | DT_TOP);//���Ķ���  �϶���
    }
    if (flag == 16) {
        // ��ʾ��ǰ�Ѷ�
        RECT mode3 = { 480, 130, 600, 180 };
        drawtext(_T("<����>"), &mode3, DT_CENTER | DT_TOP);//���Ķ���  �϶���
    }

    RECT grade = { 480, 180, 600, 280 };
    drawtext(_T("��ǰ������"), &grade, DT_LEFT | DT_TOP); //�����  �϶���
    // ������ת��Ϊ�ַ���
    char scoreString[20];
    sprintf_s(scoreString, "%d", currentMark);

    // �趨����չʾ��λ��
    int x = 540;  // X����
    int y = 230;  // Y����
    // ���ض�λ��չʾ��̬����
    outtextxy(x, y, scoreString);

    // ����������ɫΪ��ɫ
    settextcolor(WHITE);

    RECT tips = { 40, 420, 440, 480 };
    drawtext(_T("��ʹ�á�WASD��������ϵķ�����������ߵ��ƶ�"), &tips, DT_CENTER | DT_TOP);//���Ķ���  �϶���
}


void gameView() {
    init();  //��ʼ������
    while (1)
    {
        //��Ϸ����չʾ
        BeginBatchDraw();
        gameView_ShowMap();
        EndBatchDraw();

        //isPause=1ʱ��ʾ��ͣ������������ʱ����
        int isPause = 0;

        //�ж��������벢�����������ܺ���ִ����ͣ��ı䷽��
        input_Add_Execute(isPause);

        if (isPause) continue;

        //���ƶ�һ��
        snakeMove();

        //��ײ�жϣ�����ʳ������������ǽ���ߺͿյ�
        judgeResult();

        //��ʱ���ܣ�ͣ��1/speed��
        Sleep(1000 / speed);
    }
}


void pauseView() {
    //cleardevice();
    setbkmode(TRANSPARENT);
    char s1[] = "��Ϸ����ͣ";
    char s2[] = "�������˵�";
    char s3[] = "������Ϸ";
    MOUSEMSG msg;
    //��ӡs1
    settextcolor(RED);
    settextstyle(30, 0, _T("����"));
    outtextxy(160, 160, s1);
    //��ӡ��ť��s2
    setfillcolor(0xAAAAAA);
    fillroundrect(190, 200, 290, 240, 10, 10);

    settextcolor(WHITE);
    settextstyle(18, 0, _T("����"));
    outtextxy(195, 210, s2);
    //��ӡ��ť��s3
    setfillcolor(0xAAAAAA);
    fillroundrect(190, 245, 290, 285, 10, 10);

    settextcolor(WHITE);
    settextstyle(18, 0, _T("����"));
    outtextxy(205, 255, s3);
    while (1) {
        msg = GetMouseMsg();
        switch (msg.uMsg)
        {
        case WM_LBUTTONDOWN:
            //�����xy���������ת�����˵�
            if (msg.x >= 190 && msg.x <= 290 && msg.y >= 200 && msg.y <= 240)
            {
                menuView();
            }
            //�����xy���������Ϸ�������ͣҳ�棬���´�ӡ��Ϸ���棩������gameView���������ݣ�
            if (msg.x >= 190 && msg.x <= 290 && msg.y >= 245 && msg.y <= 285)
            {
                return;
            }
            break;
        default:
            continue;//û���ָ����������ҳ��
        }
    }
}

ExMessage msg = { 0 };
bool inArea(int mx, int my, int x, int y, int w, int h)
{
    if (mx > x && mx<x + w && my>y && my < y + h)
    {
        return true;
    }
    else
    {
        return false;

    }
}
bool button(int x, int y, int w, int h, const char* text)
{
    setfillcolor(WHITE);
    fillrectangle(x, y, x + w, y + h);
    settextstyle(14, 0, "����");
    int hSpace = (w - textwidth(text)) / 2;
    int vSpace = (h - textheight(text)) / 2;
    settextcolor(BLACK);
    outtextxy(x + hSpace, y + vSpace, text);
    if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h))
    {
        return true;
    }
    else
    {
        return false;
    }

}
void settleView(int isWin)
{
    char str[50] = "";
    sprintf_s(str, "������%d", currentMark);
    setbkcolor(RGB(30, 30, 30));
    cleardevice();
    setbkmode(TRANSPARENT);
    while (true)
    {
        peekmessage(&msg, EX_MOUSE);
        BeginBatchDraw();
        cleardevice();
        if (button(250, 140, 135, 70, "����һ��"))
        {
            EndBatchDraw();
            difficultySelectionView();
        }
        if (button(250, 260, 135, 70, "�˳���Ϸ"))
        {
            EndBatchDraw();
            endView();
        }
        if (button(500, 380, 135, 70, "�˽⿪����Ա"))
        {
            EndBatchDraw();
            intructionView();
        }
        setfillcolor(RED);
        fillrectangle(30, 140, 30 + 120, 140 + 70);
        int hSpace = (100 - textwidth(str)) / 2;
        int vSpace = (80 - textheight(str)) / 2;
        settextcolor(BLACK);
        outtextxy(30 + hSpace, 140 + vSpace, str);
        if (isWin == 1)
        {
            settextstyle(48, 0, "����");
            settextcolor(RED);
            outtextxy(280, 30, "ʤ��");
        }
        else if (isWin == 0)
        {
            settextstyle(48, 0, "����");
            settextcolor(RED);
            outtextxy(280, 30, "ʧ��");
        }

        EndBatchDraw();
        msg.message = 0;
    }
}

void intructionView() {

    // ��ư�ť������ʹ�С
    int buttonWidth = 120;
    int buttonHeight = 50;
    int buttonX = 50;
    int buttonY = 270;

    // ���ñ�����ɫ
    setbkcolor(RGB(222, 134, 143));
    cleardevice();

    // ��ӡС����
    settextstyle(30, 0, _T("����"));
    settextcolor(BLACK);
    outtextxy(50, 30, _T("GeekGenius"));

    //��ӡС���Ա
    settextstyle(20, 0, _T("����"));
    settextcolor(BLACK);
    char str[] = "��Ϧ��С�Σ�СP��С�࣬С��,С����Jane��С��С��";
    int hSpace = (W - textwidth(str)) / 2;
    int vSpace = (H - textheight(str)) / 2;
    outtextxy(hSpace, vSpace - 90, str);

    //��ӡף����
    settextstyle(20, 0, _T("����"));
    settextcolor(BLACK);
    char str1[] = "ף����";
    outtextxy(400, 300, str1);

    // ���ư�ť
    settextstyle(20, 0, _T("����"));
    setbkmode(TRANSPARENT);
    for (int i = 0; i < 3; i++) {
        setfillcolor(WHITE);
        fillrectangle(buttonX, buttonY, buttonX + buttonWidth, buttonY + buttonHeight);
        outtextxy(buttonX + 20, buttonY + 15, _T("����һ��"));
    }

    // ���������¼�
    while (true) {
        MOUSEMSG m;
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            if (m.x > buttonX && m.x < buttonX + buttonWidth && m.y > buttonY && m.y < buttonY + buttonHeight)
            {
                // �û�����˰�ť
                difficultySelectionView();
            }
        }
    }
}

void endView() {

    // ����ͼƬ  
    IMAGE img;
    loadimage(&img, _T("end.png"));  //  "your_image_path.jpg" ���ļ�������

    // ��ȡͼƬ�ĳߴ�  
    int imgWidth = img.getwidth();
    int imgHeight = img.getheight();

    // ����ͼƬ�ڴ����е�λ�ã�ʹ����Ӧ����  
    int x = (W - imgWidth) / 2;  // ��ͼƬ���ڴ�������  
    int y = (H - imgHeight) / 2;  // ��ͼƬ���ڴ�������  

    putimage(x, y, &img);
    // �ȴ��û�������ر�ͼ�δ���  
    Sleep(3 * 1000);
    closegraph();
    exit(0);
}
