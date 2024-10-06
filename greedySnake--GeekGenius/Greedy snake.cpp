#include<iostream>
#include<conio.h>
#include<graphics.h>
#include <windows.h>
#include <random>
using namespace std;
/*
    菜单界面:
        开始游戏: 进入困难选择界面
        退出: 打印退出游戏界面“谢谢支持”后退出程序

    困难选择界面：
        提供3个按钮：
            <简单>---蛇移速为x1
            <困难>---蛇移速为x2
            <地狱>---蛇移速为x4
        点击任意难度即可进入游戏界面

    游戏界面:
        展示: 展示地图 蛇 食物 墙等等内容
        定时移动: 蛇会定时移动
            可能会碰到蛇身/墙 死亡
            可能是空地 正常移动
            可能是食物 长度+1 原先的食物消失  生成新食物 蛇移动一格
        玩家输入:
            如果是方向键: 修改蛇的方向（不能朝反方向移动）
            如果是空格: 暂停游戏，调出暂停界面
            如果是esc: 暂停游戏，调出暂停界面
        数据展示:
            所选模式 <>
            当前分数 []
            提示词：“请使用‘WASD’或键盘上的方向键来操纵蛇的移动”

    暂停界面：
        显示 “游戏已暂停”
        提供【返回主菜单】和【返回游戏】两个按钮

    结算界面：
        显示当前游戏的结果和得分
        提供3个按钮
        【再来一局】：点击进入难度选择界面
        【退出游戏】：点击打印退出游戏界面并退出游戏
        【了解开发人员】：点击进入祝福界面

    祝福界面：
        显示祝福语及开发者相关信息
        提供一个按钮
        【再来一局】

    结束界面：
        表示感谢
        结束游戏
*/

// -------------------- 数据设计 --------------------
/*
    宏定义H和W，分别表示窗口界面的高和宽
    （具体多大之后调整）initgraph(W, H);
    宏定义MAP_H和MAP_W，分别表示游戏界面中心游戏展示内容的高（格）和宽（格）
*/
#define H 480
#define W 640
#define MAP_H 60
#define MAP_W 80

/*
    定义一格：
    一格大小5*5，展示map中的数据都是一格一格展示
*/

/*
     地图:
     map[n][m]: 地图坐标(n,m)
     0表示空地 1表示墙 2表示食物
     map[3][5] = 2 //地图(3,5)是食物
*/
int map[MAP_H][MAP_W];

/*
    蛇身
    s[n][m]: 蛇的第n节身体的m坐标
    m=0 表示x坐标  m=1 表示y坐标
    蛇头是s[0]
    s[3][0] = 5, s[3][1] =7;
    表示蛇的第4节身体 坐标是(5,7)
*/
int s[(MAP_H - 2) * (MAP_W - 2)][2];

/*
    蛇的长度：
    len表示蛇 当前的长度
*/
int len;

/*
    难度表示符：
    其中用数字表示难度，1-简单，2-困难，4-地狱
*/
int flag;

/*
    currentMark表示当前成绩
    targetMark表示目标成绩
    当结算时currentMark>=targetMark时，会显示游戏胜利，否则显示游戏失败
    speed表示蛇移动的快慢，speed越大蛇移动越快
*/
int currentMark,speed,targetMark = 20;

/*
    蛇的运动方向：
    w  a  s  d--->上 左 下 右
    例如：char direction=’w’;表示运动方向为上
*/
char direction;
// -------------------- 数据设计 --------------------


// -------------------- service --------------------
/*
service 需要提供生成食物
service 需要提供初始化操作
service 提供一个修改方向的函数
service 提供一个接受输入指令并执行的函数
service 提供判断胜利的函数
service 提供移动一格的函数
service 提供根据碰撞判断执行对应指令的函数
*/

/*
    负责人:小青
功能: 生成食物
    调用随机函数，生成食物，生成食物时要避开蛇的身体和墙体
    参数: void
    返回值: void
*/
void foodCreat();

/*
    负责人:小羽
    功能: 初始化游戏数据
    成绩,速度（根据flag（来自difficultySelectionView();）初始化）

    s[][]蛇（蛇头+蛇身）,蛇的长度为3，初始化方向（右）
    map[][]墙，空地，食物（调用foodCreat（））
    参数: void
    返回值: void
*/
void init();

/*
    负责人:Jane
    功能: 根据输入方向进行判断，改变移动方向
    参数: ch，即输入的方向
    返回值: void
*/
void turnDirection(char ch);

/*
    负责人:杨夕
    功能: 判断有无输入（使用_kbhit()），如有获取玩家则获取输入指令（input = _getch();）
            根据玩家输入指令执行:
            方向键: 修改蛇的方向（调用turnDirection函数）
            空格或esc: 暂停游戏，进入暂停界面（调用pauseView()）
    参数: void
    返回值: void
*/
void input_Add_Execute(int&);

/*
    负责人:小吉
    功能: 根据当前成绩和目标分数比较判断游戏是否胜利
    参数：void
    返回值:
        0 表示没失败
        1 表示成功
*/
int isWin();


/*
    负责人:小张
    功能: 根据direction移动蛇，更新蛇的坐标
    参数: void
    返回值: void
*/
void snakeMove();

/*
    负责人:小绪
    功能:碰撞判断
    判断蛇头s[0]的坐标和地图重合的情况，执行命令
            定时移动: 蛇会定时移动
            ①蛇头，墙或身体碰撞
                蛇死亡，进入结算，打印结算界面（ 调用settleView(iswin() ) ；）
            ②蛇头，食物碰撞
                原先的食物消失  蛇长度+1，头坐标不变，其余从蛇尾部开始将蛇后部分坐标更新成前部分
                更新当前成绩   生成新食物（调用食物生成函数foodCreat（）;）
            ③蛇头，空地碰撞 无事发生 （可不写）
*/
void judgeResult();
// -------------------- service --------------------



// -------------------- view --------------------
/*
    负责人：小青
    功能: 游戏菜单
        调出easyX 菜单页面

        设计两个需要鼠标点击的按钮
        【开始游戏】进入困难选择界面，（调用difficultySelectionView()；）
        【退出游戏】打印退出游戏界面“谢谢支持”后退出程序，（调用endView()；）
    参数: void
    返回值: void
*/
void menuView();

/*
    负责人:小绪
    功能:打印难度选择界面，难点选择有简单，困难，地狱
    调出easyX 难度选择页面
        设计三个需要鼠标点击的按钮
            【简单】
            【困难】
            【地狱】
        点击任意难度即可进入游戏界面
        根据鼠标输入进行下列内容
            简单：flag=4；
            困难：flag=8；
            地狱：flag=16；
    进入游戏界面（调用gameView()）
    参数: void
    返回值: void
*/
void difficultySelectionView();

/*
    负责人:小羽
    功能: 游戏界面打印
    根据map数组（0——空地，1————墙，2————食物），snake[][]蛇
    用easyX打印游戏界面，还要其他外部内容，
    比如：
            数据展示:
            所选模式 <>
            当前分数 []
            提示词：“请使用‘WASD’或键盘上的方向键来操纵蛇的移动”
    参数: void
    返回值: void
*/
void gameView_ShowMap();

/*
    负责人:Jane
    功能: 游戏界面整合
        初始化游戏数据(调用函数init())
        while(1){
            根据speed大小设计延时效果

            打印游戏界面(调用函数gameView_ShowMap())

            如果玩家输入则接受输入的指令并执行（调用service中input_Add_Execute（）函数）
            蛇移动一格（调用snakeMove();）

            判断蛇头和地图情况，如根据情况则进入结算（judgeResult();）
        }
    参数: void
    返回值: void
*/
void gameView();

/*
    负责人:小P
    功能:
        调出easyX 贪吃蛇的暂停界面（暂停时自动跳转）
        显示 “游戏已暂停”
        提供【返回主菜单】和【返回游戏】两个按钮
        点击后进入相应界面
        展示返回菜单和继续游戏两个选项、
            根据鼠标输入选择
            ①返回菜单  调用menuView();
            ②继续游戏  直接结束（返回到了游戏界面）
    参数: void
    返回值: void
*/
void pauseView();

/*
    负责人:小何
    功能:打印游戏结算界面
    根据iswin判断是否胜利（isWin==1表示胜利，0表示失败）
    调出easyX 结算页面
    显示当前游戏的结果（胜负）和得分
    提供3个按钮进行选择
    根据鼠标输入进行下列内容
        【再来一局】：点击进入难度选择界面（调用difficultySelectionView();）
        【退出游戏】：点击打印退出游戏界面（调用endView()；）并退出游戏
        【了解开发人员】：点击进入祝福界面（调用intructionView()；）
    参数: int isWin，来自isWin（）的返回值
    返回值: void
*/
void settleView(int iswin);

/*
    负责人:小张
    功能: 祝福界面
        调出easyX 祝福页面
        显示祝福语及开发者相关信息

        提供1个按钮
        【再来一局】：调用difficultySelectionView();
    参数: void
    返回值: void
*/
void intructionView();

/*
    负责人：小吉
    功能：
        用easyX打印结束的“游戏结束，感谢支持“图片
        过一段时间后执行exit（0）
    参数：void
    返回值：void
*/
void endView();
// -------------------- view --------------------
int main()
{
    menuView();
    return 0;
}

void foodCreat() {
    //随机数生成
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
    // 初始化游戏数据
    len = 3; // 蛇长度为3
    speed = flag; // 速度由flag控制
    direction = 'd'; // 初始移动方向向右

    // 将蛇生成在地图的中心
    //蛇头坐标(MAP_W / 2,MAP_H / 2)
    s[0][0] = MAP_W / 2;
    s[0][1] = MAP_H / 2;
    //蛇身坐标
    s[1][0] = MAP_W / 2;
    s[1][1] = (MAP_H / 2) - 1;
    s[2][0] = MAP_W / 2;
    s[2][1] = (MAP_H / 2) - 2;

    // 初始化游戏地图
    for (int i = 0; i < MAP_H; ++i) {
        for (int j = 0; j < MAP_W; ++j) {
            if (i == 0 || i == MAP_H - 1 || j == 0 || j == MAP_W - 1) {
                map[i][j] = 1; // 设置墙体为1
            }
            else {
                map[i][j] = 0; // 设置空地为0
            }
        }
    }

    currentMark = 0; // 初始化分数

    foodCreat(); // 初始化食物
}

void turnDirection(char ch) {
    //把输入的大写变成小写（防止玩游戏的时候开大写锁定）
    if (ch >= 'A' && ch <= 'Z')
    {
        ch = ch + 32;
    }

    //限定输入只能四个键
    if (ch != 'a' && ch != 'd' && ch != 'w' && ch != 's')
    {
        return;
    }
    //限定输入


    /*四种矛盾的输入方向*/
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
    /*四种矛盾的输入方向*/

    direction = ch;
}

void input_Add_Execute(int& isPause) {
    if (_kbhit())//检测按键输入
    {
        char input = _getch();//接收输入的字符
        
        if (input == ' ' || input == 27)// 27是ESC的ASC||码27
        {
            pauseView();//如果输入为空格或esc则调用pauseview函数
            isPause = 1;
        }
        else
        {
            turnDirection(input);//如果输入为wasd则调用turnDirection函数
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

void snakeMove() {   //wsad 代表方向：上下左右，由turnDirection(char ch)函数中改变方向得到
    int i;
    //改变蛇身
    for (i = len - 1; i > 0; i--)
    {
        s[i][0] = s[i - 1][0];
        s[i][1] = s[i - 1][1];
    }
    if (direction == 'w')      // 向上移动，将蛇头的 y 坐标减小
        s[i][0] -= 1;
    else if (direction == 's') // 向下移动，将蛇头的 y 坐标增加
        s[i][0] += 1;
    else if (direction == 'a') // 向左移动，将蛇头的 x 坐标减小
        s[i][1] -= 1;
    else if (direction == 'd')  // 向右移动，将蛇头的 x 坐标增加
        s[i][1] += 1;
}

void judgeResult() {
    // 判断蛇头是否与墙壁碰撞
    if (s[0][0] < 0 || s[0][0] >= MAP_H || s[0][1] < 0 || s[0][1] >= MAP_W) {
        // 蛇死亡，进入结算
        // 调用结算界面函数
        settleView(isWin());
    }

    if (map[s[0][0]][s[0][1]] == 1)
    {
        settleView(isWin());
    }

    // 判断蛇头是否与自身身体碰撞
    for (int i = 1; i < len; i++) {
        if (s[i][0] == s[0][0] && s[i][1] == s[0][1]) {

            // 调用结算界面函数
            settleView(isWin());
            break;

        }
    }
    // 判断蛇头是否与食物碰撞

    if (map[s[0][0]][s[0][1]] == 2) {//蛇头到食物了，长度加一
        map[s[0][0]][s[0][1]] = 0; // 原先的食物消失    
        // 蛇长度+1
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
        currentMark++;//分数+1
        // 生成新食物
        foodCreat();
    }
}

void menuView() {
    initgraph(W, H);
    setbkcolor(BLACK);
    cleardevice();

    settextstyle(60, 0, "楷体");
    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    outtextxy(170, 50, "经典贪吃蛇");
    setfillcolor(BLUE);
    solidrectangle(100, 200, 540, 260);
    solidrectangle(100, 300, 540, 360);

    settextcolor(BLACK);
    settextstyle(50, 0, "楷体");
    setbkmode(TRANSPARENT);
    char str1[] = "开始游戏";
    char str2[] = "退出游戏";
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
    
    // 设计三个按钮的坐标和大小
    int buttonWidth = 100;
    int buttonHeight = 50;
    int buttonX = 270;
    int buttonY[3] = { 150, 250, 350 };

    // 设置背景颜色为黑色
    setbkcolor(BLACK);
    cleardevice();

    // 绘制难度选择页面
    settextstyle(30, 0, _T("宋体"));
    outtextxy(240, 50, _T(" 难度选择 "));

    // 绘制按钮
    settextstyle(20, 0, _T("宋体"));
    for (int i = 0; i < 3; i++) {
        setfillcolor(WHITE);
        fillrectangle(buttonX, buttonY[i], buttonX + buttonWidth, buttonY[i] + buttonHeight);
        outtextxy(buttonX + 20, buttonY[i] + 15, (i == 0) ? _T("简单") : ((i == 1) ? _T("困难") : _T("地狱")));
    }

    // 检测鼠标点击事件
    while (true) {
        MOUSEMSG m;
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN) {
            bool yes = false;
            for (int i = 0; i < 3; i++) {
                if (m.x > buttonX && m.x < buttonX + buttonWidth && m.y > buttonY[i] && m.y < buttonY[i] + buttonHeight) {
                    // 用户点击了按钮
                    if (i == 0) {
                        flag = 4;  // 简单
                    }
                    else if (i == 1) {
                        flag = 8;  // 困难
                    }
                    else if (i == 2) {
                        flag = 16;  // 地狱
                    }
                    yes = true;
                    break;
                }
            }
            if(yes)break;
        }
    }

    // 进入游戏界面
    gameView();

    // 关闭图形窗口
    closegraph();
}

void gameView_ShowMap() {
    cleardevice();
    static int LUX = 40; // 左上x坐标
    static int LUY = 80; // 左上y坐标
    static int RDX = 440; // 右下x坐标
    static int RDY = 380; // 右下y坐标
    // 设置单元格大小为5*5，那么其尺寸为5
    static int squareSize = 5;
    // 画一个窗口
    //rectangle(0, 0, W, H);

    // 在游戏界面内另画一个窗口表示游戏地图
    //rectangle(LUX, LUY, RDX, RDY);

    // 将墙体(黑)、食物(红)和空地(白)以不同颜色表示出来
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
    // 设置字体颜色为紫红色
    settextcolor(MAGENTA);

    // 通过蛇身坐标打印蛇
    for (int n = 0; n < len; n++) {
        setfillcolor(GREEN);
        solidrectangle(LUX + s[n][1] * squareSize, LUY + s[n][0] * squareSize, LUX + (s[n][1] + 1) * squareSize, LUY + (s[n][0] + 1) * squareSize);
    }

    // 显示内容“所选模式”
    RECT mode = { 480, 80, 600, 130 };
    drawtext(_T("所选模式："), &mode, DT_LEFT | DT_TOP); //左对齐  上对齐
    if (flag == 4) {
        // 显示当前难度
        RECT mode1 = { 480, 130, 600, 180 };
        drawtext(_T("<简单>"), &mode1, DT_CENTER | DT_TOP);//中心对齐  上对齐
    }
    if (flag == 8) {
        // 显示当前难度
        RECT mode2 = { 480, 130, 600, 180 };
        drawtext(_T("<困难>"), &mode2, DT_CENTER | DT_TOP);//中心对齐  上对齐
    }
    if (flag == 16) {
        // 显示当前难度
        RECT mode3 = { 480, 130, 600, 180 };
        drawtext(_T("<地狱>"), &mode3, DT_CENTER | DT_TOP);//中心对齐  上对齐
    }

    RECT grade = { 480, 180, 600, 280 };
    drawtext(_T("当前分数："), &grade, DT_LEFT | DT_TOP); //左对齐  上对齐
    // 将整形转化为字符串
    char scoreString[20];
    sprintf_s(scoreString, "%d", currentMark);

    // 设定分数展示的位置
    int x = 540;  // X坐标
    int y = 230;  // Y坐标
    // 在特定位置展示动态数据
    outtextxy(x, y, scoreString);

    // 设置字体颜色为白色
    settextcolor(WHITE);

    RECT tips = { 40, 420, 440, 480 };
    drawtext(_T("请使用“WASD”或键盘上的方向键来操纵蛇的移动"), &tips, DT_CENTER | DT_TOP);//中心对齐  上对齐
}


void gameView() {
    init();  //初始化数据
    while (1)
    {
        //游戏界面展示
        BeginBatchDraw();
        gameView_ShowMap();
        EndBatchDraw();

        //isPause=1时表示暂停，用于跳过延时功能
        int isPause = 0;

        //判断有无输入并调用其他功能函数执行暂停或改变方向
        input_Add_Execute(isPause);

        if (isPause) continue;

        //蛇移动一格
        snakeMove();

        //碰撞判断，蛇与食物，蛇与蛇身体和墙，蛇和空地
        judgeResult();

        //延时功能，停顿1/speed秒
        Sleep(1000 / speed);
    }
}


void pauseView() {
    //cleardevice();
    setbkmode(TRANSPARENT);
    char s1[] = "游戏已暂停";
    char s2[] = "返回主菜单";
    char s3[] = "继续游戏";
    MOUSEMSG msg;
    //打印s1
    settextcolor(RED);
    settextstyle(30, 0, _T("黑体"));
    outtextxy(160, 160, s1);
    //打印按钮和s2
    setfillcolor(0xAAAAAA);
    fillroundrect(190, 200, 290, 240, 10, 10);

    settextcolor(WHITE);
    settextstyle(18, 0, _T("宋体"));
    outtextxy(195, 210, s2);
    //打印按钮和s3
    setfillcolor(0xAAAAAA);
    fillroundrect(190, 245, 290, 285, 10, 10);

    settextcolor(WHITE);
    settextstyle(18, 0, _T("宋体"));
    outtextxy(205, 255, s3);
    while (1) {
        msg = GetMouseMsg();
        switch (msg.uMsg)
        {
        case WM_LBUTTONDOWN:
            //点击该xy区域可以跳转到主菜单
            if (msg.x >= 190 && msg.x <= 290 && msg.y >= 200 && msg.y <= 240)
            {
                menuView();
            }
            //点击该xy区域继续游戏（清除暂停页面，重新打印游戏界面）（借用gameView函数的内容）
            if (msg.x >= 190 && msg.x <= 290 && msg.y >= 245 && msg.y <= 285)
            {
                return;
            }
            break;
        default:
            continue;//没点击指定区域，锁死页面
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
    settextstyle(14, 0, "宋体");
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
    sprintf_s(str, "分数：%d", currentMark);
    setbkcolor(RGB(30, 30, 30));
    cleardevice();
    setbkmode(TRANSPARENT);
    while (true)
    {
        peekmessage(&msg, EX_MOUSE);
        BeginBatchDraw();
        cleardevice();
        if (button(250, 140, 135, 70, "再来一局"))
        {
            EndBatchDraw();
            difficultySelectionView();
        }
        if (button(250, 260, 135, 70, "退出游戏"))
        {
            EndBatchDraw();
            endView();
        }
        if (button(500, 380, 135, 70, "了解开发人员"))
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
            settextstyle(48, 0, "宋体");
            settextcolor(RED);
            outtextxy(280, 30, "胜利");
        }
        else if (isWin == 0)
        {
            settextstyle(48, 0, "宋体");
            settextcolor(RED);
            outtextxy(280, 30, "失败");
        }

        EndBatchDraw();
        msg.message = 0;
    }
}

void intructionView() {

    // 设计按钮的坐标和大小
    int buttonWidth = 120;
    int buttonHeight = 50;
    int buttonX = 50;
    int buttonY = 270;

    // 设置背景颜色
    setbkcolor(RGB(222, 134, 143));
    cleardevice();

    // 打印小组名
    settextstyle(30, 0, _T("宋体"));
    settextcolor(BLACK);
    outtextxy(50, 30, _T("GeekGenius"));

    //打印小组成员
    settextstyle(20, 0, _T("宋体"));
    settextcolor(BLACK);
    char str[] = "杨夕，小何，小P，小青，小吉,小绪，Jane，小羽，小张";
    int hSpace = (W - textwidth(str)) / 2;
    int vSpace = (H - textheight(str)) / 2;
    outtextxy(hSpace, vSpace - 90, str);

    //打印祝福语
    settextstyle(20, 0, _T("宋体"));
    settextcolor(BLACK);
    char str1[] = "祝福词";
    outtextxy(400, 300, str1);

    // 绘制按钮
    settextstyle(20, 0, _T("宋体"));
    setbkmode(TRANSPARENT);
    for (int i = 0; i < 3; i++) {
        setfillcolor(WHITE);
        fillrectangle(buttonX, buttonY, buttonX + buttonWidth, buttonY + buttonHeight);
        outtextxy(buttonX + 20, buttonY + 15, _T("再来一局"));
    }

    // 检测鼠标点击事件
    while (true) {
        MOUSEMSG m;
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            if (m.x > buttonX && m.x < buttonX + buttonWidth && m.y > buttonY && m.y < buttonY + buttonHeight)
            {
                // 用户点击了按钮
                difficultySelectionView();
            }
        }
    }
}

void endView() {

    // 加载图片  
    IMAGE img;
    loadimage(&img, _T("end.png"));  //  "your_image_path.jpg" 打开文件的名称

    // 获取图片的尺寸  
    int imgWidth = img.getwidth();
    int imgHeight = img.getheight();

    // 计算图片在窗口中的位置，使其适应窗口  
    int x = (W - imgWidth) / 2;  // 将图片放在窗口中心  
    int y = (H - imgHeight) / 2;  // 将图片放在窗口中心  

    putimage(x, y, &img);
    // 等待用户按键后关闭图形窗口  
    Sleep(3 * 1000);
    closegraph();
    exit(0);
}
