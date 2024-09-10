#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<graphics.h>//引入EasyX插件
#include<windows.h>
#include<mmsystem.h>//声音头文件
#include<vector>
#include<cmath>
#pragma comment(lib,"winmm.lib")//声音库
using namespace std;
int cialloSpeed = 2;//yzc移动速度
int boomSpeed = 2;//起爆器移动速度
int speed = 27;//发射速度
long long acnum = 100;//加速玩家花费
long long denum = 100;//加速yzc花费
long long healnum = 100;//回血花费
constexpr auto swidth = 960;//窗口宽
constexpr auto sheight = 633;//窗口高
int health = 10;//生命值
bool is_play = true;//是否进行游戏
bool is_die = false;//是否死亡
unsigned long long killnum = 0;//击杀数

//初始化
void Initial()
{
	cialloSpeed = 2;
	boomSpeed = 2;
	speed = 27;
	acnum = 100;
	healnum = 100;
	denum = 100;
	health = 10;
	is_play = true;
	is_die = false;
	killnum = 0;
}

//检测鼠标范围
bool pointInRect(int x, int y, RECT& r)
{
	return (r.left <= x && x <= r.right && r.top <= y && y <= r.bottom);
}

//检测碰撞
bool checkRectRush(RECT& rc1, RECT& rc2)
{
	RECT temp;
	temp.left = rc1.left - (rc2.right - rc2.left);
	temp.right = rc1.right;
	temp.top = rc1.top - (rc2.bottom - rc2.top);
	temp.bottom = rc1.bottom;
	//碰撞返回true
	return (temp.left <= rc2.left && rc2.left <= temp.right && temp.top <= rc2.top && rc2.top <= temp.bottom);
}

//背景类
class BackGround
{
private:
	IMAGE& image;
	//int x, y;
public:
	BackGround(IMAGE& i) :image(i)
	{

	}
	void Show()
	{
		putimage(0, 0, &image);
	}
};

//商店界面
void Shop()
{
	LPCTSTR title = _T("Shop");
	char ac[128], de[128], heal[128];
	sprintf(ac, "Accelerate you:%lld", acnum);
	LPCTSTR tplay = _T(ac);
	sprintf(de, "Accelerate yzc:%lld", denum);
	LPCTSTR tplay1 = _T(de);
	sprintf(heal, "Heal you:%lld", healnum);
	LPCTSTR tplay2 = _T(heal);
	LPCTSTR texit = _T("Back");
	RECT tplayer, texiter, tplayer1, tplayer2;
	IMAGE button4, button5, button6, button7, shopimg, bkimg;

	BeginBatchDraw();

	setbkcolor(WHITE);
	cleardevice();
	setbkmode(TRANSPARENT);

	loadimage(&bkimg, _T("reboot.jpg"));
	BackGround bk = BackGround(bkimg);
	bk.Show();

	settextstyle(60, 0, _T("黑体"));
	settextcolor(YELLOW);
	loadimage(&shopimg, _T("shop.jpg"), textwidth(title) + 100, textheight(title) + 80, true);
	putimage(swidth / 2 - textwidth(title) / 2 - 50, sheight / 10 - 40, &shopimg, SRCAND);
	//outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 10, title);

	settextstyle(40, 0, _T("黑体"));

	tplayer.left = swidth / 2 - textwidth(tplay) / 2;
	tplayer.right = tplayer.left + textwidth(tplay);
	tplayer.top = sheight / 7 * 2;
	tplayer.bottom = tplayer.top + textheight(tplay);

	tplayer1.left = swidth / 2 - textwidth(tplay1) / 2;
	tplayer1.right = tplayer1.left + textwidth(tplay1);
	tplayer1.top = sheight / 7 * 3;
	tplayer1.bottom = tplayer1.top + textheight(tplay1);

	tplayer2.left = swidth / 2 - textwidth(tplay2) / 2;
	tplayer2.right = tplayer2.left + textwidth(tplay2);
	tplayer2.top = sheight / 7 * 4;
	tplayer2.bottom = tplayer2.top + textheight(tplay2);

	texiter.left = swidth / 2 - textwidth(texit) / 2;
	texiter.right = texiter.left + textwidth(texit);
	texiter.top = sheight / 7 * 5;
	texiter.bottom = texiter.top + textheight(texit);

	setbkmode(TRANSPARENT);//设置文字背景为透明底
	loadimage(&button4, _T("button4.jpg"), tplayer.right - tplayer.left + 20, tplayer.bottom - tplayer.top + 20, true);
	putimage(tplayer.left - 10, tplayer.top - 10, &button4, SRCAND);
	loadimage(&button5, _T("button4.jpg"), tplayer1.right - tplayer1.left + 20, tplayer1.bottom - tplayer1.top + 20, true);
	putimage(tplayer1.left - 10, tplayer1.top - 10, &button5, SRCAND);
	loadimage(&button6, _T("button4.jpg"), tplayer2.right - tplayer2.left + 20, tplayer2.bottom - tplayer2.top + 20, true);
	putimage(tplayer2.left - 10, tplayer2.top - 10, &button6, SRCAND);
	loadimage(&button7, _T("button4.jpg"), texiter.right - texiter.left + 20, texiter.bottom - texiter.top + 20, true);
	putimage(texiter.left - 10, texiter.top - 10, &button7, SRCAND);
	outtextxy(tplayer.left, tplayer.top, tplay);
	outtextxy(tplayer1.left, tplayer1.top, tplay1);
	outtextxy(tplayer2.left, tplayer2.top, tplay2);
	outtextxy(texiter.left, texiter.top, texit);

	char h[25] = { 0 };
	sprintf(h, "Health : %d", health);
	settextstyle(40, 0, _T("楷体"));
	outtextxy(swidth - textwidth(h), sheight - textheight(h), h);

	char k[25] = { 0 };
	sprintf(k, "Kills : %lld", killnum);
	settextstyle(40, 0, _T("楷体"));
	outtextxy(0, sheight - textheight(k), k);

	EndBatchDraw();

	while (true)
	{
		ExMessage mess;
		getmessage(&mess, EM_MOUSE);
		if (mess.lbutton)
		{
			if (killnum >= acnum && pointInRect(mess.x, mess.y, tplayer))
			{
				mciSendString("open muc\\button.mp3 alias but", NULL, 0, NULL);
				mciSendString("play but", NULL, 0, NULL);
				killnum -= acnum;
				acnum += 100;
				boomSpeed++;
				if (speed > 1)//speed最快为1
					speed--;
				return;
			}
			else if (killnum >= denum && denum > 0 && pointInRect(mess.x, mess.y, tplayer1))
			{
				mciSendString("open muc\\button.mp3 alias but", NULL, 0, NULL);
				mciSendString("seek but to start", NULL, 0, NULL);
				mciSendString("play but", NULL, 0, NULL);
				killnum -= denum;
				denum -= 10;
				cialloSpeed++;
				return;
			}
			else if (killnum >= healnum && pointInRect(mess.x, mess.y, tplayer2))
			{
				mciSendString("open muc\\button.mp3 alias but", NULL, 0, NULL);
				mciSendString("seek but to start", NULL, 0, NULL);
				mciSendString("play but", NULL, 0, NULL);
				killnum -= healnum;
				health++;
				return;
			}
			else if (pointInRect(mess.x, mess.y, texiter))
			{
				mciSendString("open muc\\button.mp3 alias but", NULL, 0, NULL);
				mciSendString("seek but to start", NULL, 0, NULL);
				mciSendString("play but", NULL, 0, NULL);
				return;
			}
		}
	}
}

//开始界面
void Welcome()
{
	LPCTSTR title = _T("KillYZC");
	LPCTSTR tplay = _T("Start");
	LPCTSTR shop = _T("Shop");
	LPCTSTR texit = _T("Exit");
	IMAGE button1, button2, button3, titleimg, bkimg;
	RECT tplayer, texiter, shoper;
	BeginBatchDraw();

	setbkcolor(WHITE);
	cleardevice();

	loadimage(&bkimg, _T("riddlejoker.jpg"));
	BackGround bk = BackGround(bkimg);
	bk.Show();

	settextstyle(60, 0, _T("黑体"));
	settextcolor(WHITE);
	loadimage(&titleimg, _T("title.jpg"), textwidth(title) + 100, textheight(title) + 80, true);
	putimage(swidth / 2 - textwidth(title) / 2 - 50, sheight / 10 - 40, &titleimg, SRCAND);
	//outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 10, title);


	settextstyle(40, 0, _T("黑体"));

	tplayer.left = swidth / 2 - textwidth(tplay) / 2;
	tplayer.right = tplayer.left + textwidth(tplay);
	tplayer.top = sheight / 5 * 2;
	tplayer.bottom = tplayer.top + textheight(tplay);

	shoper.left = swidth / 2 - textwidth(shop) / 2;
	shoper.right = shoper.left + textwidth(shop);
	shoper.top = sheight / 5 * 3;
	shoper.bottom = shoper.top + textheight(shop);

	texiter.left = swidth / 2 - textwidth(texit) / 2;
	texiter.right = texiter.left + textwidth(texit);
	texiter.top = sheight / 5 * 4;
	texiter.bottom = texiter.top + textheight(texit);

	loadimage(&button1, _T("button1.jpg"), tplayer.right - tplayer.left, tplayer.bottom - tplayer.top, true);
	putimage(tplayer.left, tplayer.top, &button1, SRCAND);
	loadimage(&button2, _T("button2.jpg"), shoper.right - shoper.left, shoper.bottom - shoper.top, true);
	putimage(shoper.left, shoper.top, &button2, SRCAND);
	loadimage(&button3, _T("button3.jpg"), texiter.right - texiter.left, texiter.bottom - texiter.top, true);
	putimage(texiter.left, texiter.top, &button3, SRCAND);
	//outtextxy(tplayer.left, tplayer.top, tplay);
	//outtextxy(shoper.left, shoper.top, shop);
	//outtextxy(texiter.left, texiter.top, texit);

	EndBatchDraw();

	//	mciSendString("open XX  alias YY", NULL, 0, NULL);
	//	mciSendString("play YY", NULL, 0, NULL);
	//	mciSendString("setaudio YY volume num", NULL, 0, NULL);//调节音量
		//PlaySound(_T("E:\\KillYZC\\muc\\op.wav"), NULL, SND_FILENAME | SND_ASYNC);//仅wav
		//system("pause");
		//PlaySound("E:\\KillYZC\\muc\\op1.wav", NULL, SND_FILENAME | SND_ASYNC);
	MCIERROR ret = mciSendString("open muc\\op.mp3 alias bgm0", NULL, 0, NULL);
	if (ret != 0)
	{
		char err[100] = { 0 };
		mciGetErrorString(ret, err, sizeof err);
		cout << err;
	}
	MCIERROR ret2 = mciSendString("play bgm0 repeat", NULL, 0, NULL);
	if (ret2 != 0)
	{
		char err[100] = { 0 };
		mciGetErrorString(ret2, err, sizeof err);
		cout << err;
	}//播放主界面音乐

	while (true)
	{
		ExMessage mess;
		getmessage(&mess, EM_MOUSE);
		if (mess.lbutton)
		{
			if (pointInRect(mess.x, mess.y, tplayer))
			{
				is_play = true;
				is_die = false;
				mciSendString("close bgm0", 0, 0, 0);//停止播放
				mciSendString("open muc\\button.mp3 alias but", NULL, 0, NULL);
				mciSendString("seek but to start", NULL, 0, NULL);
				mciSendString("play but", NULL, 0, NULL);
				return;
			}
			else if (pointInRect(mess.x, mess.y, shoper))
			{
				mciSendString("open muc\\button.mp3 alias but", NULL, 0, NULL);
				mciSendString("seek but to start", NULL, 0, NULL);
				mciSendString("play but", NULL, 0, NULL);
				Shop();
				Welcome();
			}
			else if (pointInRect(mess.x, mess.y, texiter))
			{
				mciSendString("open muc\\button.mp3 alias but", NULL, 0, NULL);
				mciSendString("seek but to start", NULL, 0, NULL);
				mciSendString("play but", NULL, 0, NULL);
				exit(0);
			}
		}
	}
	Sleep(1000);
}

//玩家类
class Player
{
private:
	IMAGE& image;
	RECT rect;
public:
	Player(IMAGE& i) :image(i)
	{
		rect.left = swidth / 2 - image.getwidth() / 2;
		rect.right = rect.left + image.getwidth();
		rect.top = sheight - image.getheight();
		rect.bottom = sheight;
	}
	void Show()
	{
		putimage(rect.left, rect.top, &image, SRCAND);
	}
	void Control()
	{
		ExMessage mess;
		if (peekmessage(&mess, EM_MOUSE))
		{
			rect.left = mess.x - image.getwidth() / 2;
			rect.right = rect.right = rect.left + image.getwidth();
		}
	}
	RECT& getRect()
	{
		return rect;
	}
};

//yzc类
class Ciallo
{
private:
	IMAGE& image;
	RECT rect;
	int velocity;
	//bool direction;
public:
	Ciallo(IMAGE& i, int y, bool flag) :image(i)
	{
		rect.bottom = y;
		rect.top = rect.bottom - image.getheight();
		//if (dir)
		//{
		if (flag)
		{
			rect.right = abs(rand()) % 100 + 1;
			rect.left = rect.right - image.getwidth();
		}
		else
		{
			rect.left = swidth - 1 - abs(rand()) % 100;
			rect.right = rect.left + image.getwidth();
		}
		velocity = abs(rand()) % 3 - 1 + cialloSpeed;
		//	}
	/*else
	{
		rect.left = swidth - 1;
		rect.right = rect.left + image.getwidth();
	}*/
	}
	bool Show()
	{
		if (rect.left >= swidth || rect.right <= 0)
		{
			health--;
			mciSendString("open muc\\hit.mp3 alias hit", NULL, 0, NULL);
			mciSendString("seek hit to start", NULL, 0, NULL);
			mciSendString("play hit", NULL, 0, NULL);
			if (health <= 0)
				is_die = true;
			return false;
		}
		//if (direction)
		//{
		//	rect.right += cialloSpeed;
		//	rect.left += cialloSpeed;
		/*}
		else
		{
			rect.left -= 2;
			rect.right -= 2;
		}*/
		//SRCAND添加位运算宏实现透明底
		putimage(rect.left, rect.top, &image, SRCAND);
		return true;
	}
	RECT& getRect()
	{
		return rect;
	}
	int getSpeed()
	{
		return velocity;
	}
};

//起爆器类
class Boom
{
private:
	IMAGE& image;
	RECT rect;
public:
	Boom(IMAGE& i, RECT& pl) :image(i)
	{
		rect.left = pl.left + (pl.right - pl.left) / 2 - image.getwidth() / 2;
		rect.right = rect.left + image.getwidth();
		rect.top = pl.top - image.getheight();
		rect.bottom = rect.top + image.getheight();
	}
	bool Show()
	{
		if (rect.bottom <= 0)
		{
			return false;
		}
		//rect.top -= boomSpeed;
		//rect.bottom -= boomSpeed;
		putimage(rect.left, rect.top, &image, SRCAND);
		return true;
	}
	RECT& getRect()
	{
		return rect;
	}
};

//增加yzc并避免重叠
bool addCiallo(vector<Ciallo*>& cl, IMAGE& img, bool flag)
{
	Ciallo* c = new Ciallo(img, abs(rand()) % (sheight - img.getheight()), flag);
	for (auto& it : cl)
	{
		if (checkRectRush(it->getRect(), c->getRect()))
		{
			delete c;
			return false;
		}
	}
	cl.push_back(c);
	//随机播放
	int order = abs(rand()) % 11;
	switch (order)
	{
	case 0:
		mciSendString("seek bgm1 to start", NULL, 0, NULL);
		mciSendString("play bgm1", NULL, 0, NULL);
		break;
	case 1:
		mciSendString("seek bgm2 to start", NULL, 0, NULL);
		mciSendString("play bgm2", NULL, 0, NULL);
		break;
	case 2:
		mciSendString("seek bgm3 to start", NULL, 0, NULL);
		mciSendString("play bgm3", NULL, 0, NULL);
		break;
	case 3:
		mciSendString("seek bgm4 to start", NULL, 0, NULL);
		mciSendString("play bgm4", NULL, 0, NULL);
		break;
	case 4:
		mciSendString("seek bgm5 to start", NULL, 0, NULL);
		mciSendString("play bgm5", NULL, 0, NULL);
		break;
	case 5:
		mciSendString("seek bgm6 to start", NULL, 0, NULL);
		mciSendString("play bgm6", NULL, 0, NULL);
		break;
	case 6:
		mciSendString("seek bgm7 to start", NULL, 0, NULL);
		mciSendString("play bgm7", NULL, 0, NULL);
		break;
	case 7:
		mciSendString("seek bgm8 to start", NULL, 0, NULL);
		mciSendString("play bgm8", NULL, 0, NULL);
		break;
	case 8:
		mciSendString("seek bgm9 to start", NULL, 0, NULL);
		mciSendString("play bgm9", NULL, 0, NULL);
		break;
	case 9:
		mciSendString("seek bgm10 to start", NULL, 0, NULL);
		mciSendString("play bgm10", NULL, 0, NULL);
		break;
	case 10:
		mciSendString("seek bgm11 to start", NULL, 0, NULL);
		mciSendString("play bgm11", NULL, 0, NULL);
		break;
	}
	//PlaySound("E:\\KillYZC\\ciallo .wav", NULL, SND_FILENAME | SND_ASYNC);//仅wav
	return true;
}

//结束界面
void Over()
{
	TCHAR* str = new TCHAR[128];
	_stprintf_s(str, 128, _T("Kills: %lld"), killnum);
	LPCTSTR infor = _T("Cilck to back");
	settextstyle(20, 0, _T("黑体"));
	LPCTSTR infor2;
	setbkmode(TRANSPARENT);
	settextcolor(RED);

	if (killnum >= 721)//两种结局
	{
		infor2 = _T("0721 GOD");
		mciSendString("open muc\\_0721.mp3 alias onanii", NULL, 0, NULL);
		mciSendString("play onanii", NULL, 0, NULL);
		MCIERROR ret4 = mciSendString("setaudio onanii volume to 1000", NULL, 0, NULL);//调节音量
		if (ret4 != 0)
		{
			char err[100] = { 0 };
			mciGetErrorString(ret4, err, sizeof err);
			cout << err;
		}
	}
	else
	{
		infor2 = _T("ZaaKo");
		mciSendString("open muc\\zaako.mp3 alias zaako", NULL, 0, NULL);
		mciSendString("play zaako", NULL, 0, NULL);
	}

	outtextxy(swidth / 2 - textwidth(str) / 2, sheight / 5, str);
	outtextxy(swidth - textwidth(infor), sheight - textheight(infor), infor);
	settextstyle(60, 0, _T("黑体"));
	outtextxy(swidth / 2 - textwidth(infor2) / 2, sheight / 10, infor2);

	LPCTSTR texit = _T("Exit");
	RECT texiter;
	IMAGE exitimg;
	texiter.left = swidth / 2 - textwidth(texit) / 2;
	texiter.right = texiter.left + textwidth(texit);
	texiter.top = sheight / 5 * 3;
	texiter.bottom = texiter.top + textheight(texit);
	loadimage(&exitimg, _T("button7.jpg"), textwidth(texit), textheight(texit), true);
	putimage(texiter.left, texiter.top, &exitimg,SRCAND);
	//outtextxy(texiter.left, texiter.top, texit);

	while (true)
	{
		ExMessage mess;
		getmessage(&mess, EM_MOUSE);
		if (mess.lbutton)
		{
			mciSendString("open muc\\button.mp3 alias but", NULL, 0, NULL);
			mciSendString("seek but to start", NULL, 0, NULL);
			mciSendString("play but", NULL, 0, NULL);
			if (pointInRect(mess.x, mess.y, texiter))
			{
				exit(0);
			}
			Initial();//单击退出键外的其他地方重新初始化
			mciSendString("close bgm2", NULL, 0, NULL);
			return;
		}
	}
}

//暂停界面
void Pause()
{
	LPCTSTR title = _T("PAUSE");
	LPCTSTR tplay = _T("Back");
	LPCTSTR texit = _T("Quit");
	IMAGE pauseimg, button8, button9, bkimg;
	RECT tplayer, texiter;
	BeginBatchDraw();

	setbkcolor(WHITE);
	cleardevice();
	settextstyle(60, 0, _T("黑体"));
	settextcolor(BLACK);

	loadimage(&bkimg, _T("sennebannka.jpg"));
	BackGround bk = BackGround(bkimg);
	bk.Show();


	loadimage(&pauseimg, _T("pause.jpg"), textwidth(title) + 100, textheight(title) + 80, true);
	putimage(swidth / 2 - textwidth(title) / 2 - 50, sheight / 10 - 40, &pauseimg, SRCAND);
	//outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 10, title);

	settextstyle(40, 0, _T("黑体"));

	tplayer.left = swidth / 2 - textwidth(tplay) / 2;
	tplayer.right = tplayer.left + textwidth(tplay);
	tplayer.top = sheight / 5 * 2;
	tplayer.bottom = tplayer.top + textheight(tplay);

	texiter.left = swidth / 2 - textwidth(texit) / 2;
	texiter.right = texiter.left + textwidth(texit);
	texiter.top = sheight / 5 * 3;
	texiter.bottom = texiter.top + textheight(texit);

	loadimage(&button8, _T("button5.jpg"), tplayer.right - tplayer.left, tplayer.bottom - tplayer.top, true);
	putimage(tplayer.left, tplayer.top, &button8, SRCAND);
	loadimage(&button9, _T("button6.jpg"), texiter.right - texiter.left, texiter.bottom - texiter.top, true);
	putimage(texiter.left, texiter.top, &button9, SRCAND);
	//outtextxy(tplayer.left, tplayer.top, tplay);
	//outtextxy(texiter.left, texiter.top, texit);

	setbkmode(TRANSPARENT);
	char h[25] = { 0 };
	sprintf(h, "Health : %d", health);
	settextstyle(40, 0, _T("楷体"));
	outtextxy(swidth - textwidth(h), sheight - textheight(h), h);//右下角显示health

	char k[25] = { 0 };
	sprintf(k, "Kills : %lld", killnum);
	settextstyle(40, 0, _T("楷体"));
	outtextxy(0, sheight - textheight(k), k);//左下角显示killnum

	EndBatchDraw();

	//	mciSendString("open XX  alias YY", NULL, 0, NULL);
	//	mciSendString("play YY", NULL, 0, NULL);
	//	mciSendString("setaudio YY volume num", NULL, 0, NULL);//调节音量

	while (true)
	{
		ExMessage mess;
		getmessage(&mess, EM_MOUSE | EM_KEY);
		if (mess.lbutton)
		{
			if (pointInRect(mess.x, mess.y, tplayer))
			{
				mciSendString("open muc\\button.mp3 alias but", NULL, 0, NULL);
				mciSendString("seek but to start", NULL, 0, NULL);
				mciSendString("play but", NULL, 0, NULL);
				return;
			}
			else if (pointInRect(mess.x, mess.y, texiter))
			{
				mciSendString("open muc\\button.mp3 alias but", NULL, 0, NULL);
				mciSendString("seek but to start", NULL, 0, NULL);
				mciSendString("play but", NULL, 0, NULL);
				is_play = false;
				return;
			}
		}
	}
	Sleep(1000);
}

//游戏运行
bool Play()
{
	setbkcolor(WHITE);
	cleardevice();

	//加载图片
	IMAGE ciallo, boom, bkimg, player;
	IMAGE ciallo1, ciallo2, ciallo3, ciallo4, ciallo5, ciallo6;

	loadimage(&ciallo, _T("ciallo.jpg"));
	loadimage(&ciallo1, _T("ciallo1.jpg"));
	loadimage(&ciallo2, _T("ciallo2.jpg"));
	loadimage(&ciallo3, _T("ciallo3.jpg"));
	loadimage(&ciallo4, _T("ciallo4.jpg"));
	loadimage(&ciallo5, _T("ciallo5.jpg"));
	loadimage(&ciallo6, _T("ciallo6.jpg"));
	loadimage(&boom, _T("boom.jpg"));
	loadimage(&bkimg, _T("sennebannka.jpg"), 960, 633);
	loadimage(&player, _T("goblin.jpg"));

	BackGround bk = BackGround(bkimg);
	Player pl = Player(player);
	vector <Ciallo*> cl;//从左->右
	vector <Ciallo*> cl1;//从右->左
	vector <Boom*> bm;
	int bsing = 0;
	mciSendString("open	muc\\ciallo.mp3 alias bgm1", NULL, 0, NULL);
	mciSendString("open	muc\\ciallo1.mp3 alias bgm2", NULL, 0, NULL);
	mciSendString("open	muc\\ciallo2.mp3 alias bgm3", NULL, 0, NULL);
	mciSendString("open	muc\\ciallo3.mp3 alias bgm4", NULL, 0, NULL);
	mciSendString("open	muc\\ciallo4.mp3 alias bgm5", NULL, 0, NULL);
	mciSendString("open	muc\\ciallo5.mp3 alias bgm6", NULL, 0, NULL);
	mciSendString("open	muc\\ciallo6.mp3 alias bgm7", NULL, 0, NULL);
	mciSendString("open	muc\\ciallo7.mp3 alias bgm8", NULL, 0, NULL);
	mciSendString("open	muc\\ciallo8.mp3 alias bgm9", NULL, 0, NULL);
	mciSendString("open	muc\\ciallo9.mp3 alias bgm10", NULL, 0, NULL);
	mciSendString("open	muc\\ciallo10.mp3 alias bgm11", NULL, 0, NULL);

	//mciSendString("close bgm0", 0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		int order;
		order = abs(rand()) % 7;
		switch (order)
		{
		case 0:
			addCiallo(cl, ciallo, true);
			break;
		case 1:
			addCiallo(cl, ciallo1, true);
			break;
		case 2:
			addCiallo(cl, ciallo2, true);
			break;
		case 3:
			addCiallo(cl, ciallo3, true);
			break;
		case 4:
			addCiallo(cl, ciallo4, true);
			break;
		case 5:
			addCiallo(cl, ciallo5, true);
			break;
		case 6:
			addCiallo(cl, ciallo6, true);
			break;
		}
		order = abs(rand()) % 7;
		switch (order)
		{
		case 0:
			addCiallo(cl1, ciallo, false);
			break;
		case 1:
			addCiallo(cl1, ciallo1, false);
			break;
		case 2:
			addCiallo(cl1, ciallo2, false);
			break;
		case 3:
			addCiallo(cl1, ciallo3, false);
			break;
		case 4:
			addCiallo(cl1, ciallo4, false);
			break;
		case 5:
			addCiallo(cl1, ciallo5, false);
			break;
		case 6:
			addCiallo(cl1, ciallo6, false);
			break;
		}
		//mciSendString("open	ciallo.mp3 alias bgm1", NULL, 0, NULL);
	//	mciSendString("play bgm1", NULL, 0, NULL);
	}

	bm.push_back(new Boom(boom, pl.getRect()));
	while (is_play && !is_die)
	{
		bsing++;
		if (bsing == speed)
		{
			bsing = 0;
			bm.push_back(new Boom(boom, pl.getRect()));
		}
		BeginBatchDraw();

		bk.Show();
		Sleep(6);
		flushmessage();
		Sleep(2);//避免掉帧
		pl.Control();
		pl.Show();

		auto bit = bm.begin();
		while (bit != bm.end())
		{
			(*bit)->getRect().top -= boomSpeed;
			(*bit)->getRect().bottom -= boomSpeed;
			if (!(*bit)->Show())
			{
				delete (*bit);
				bm.erase(bit);
				bit = bm.begin();
			}
			if (bit != bm.end())
				bit++;
		}
		auto it = cl.begin();
		auto it1 = cl1.begin();
		while (it != cl.end())
		{
			bit = bm.begin();

			(*it)->getRect().left += (*it)->getSpeed();
			(*it)->getRect().right += (*it)->getSpeed();
			while (bit != bm.end())
			{
				if (checkRectRush((*bit)->getRect(), (*it)->getRect()))
				{
					delete (*it);
					cl.erase(it);
					it = cl.begin();
					delete(*bit);
					bm.erase(bit);
					killnum++;
					break;
				}
				bit++;
			}
			if (!(*it)->Show())
			{
				delete (*it);
				cl.erase(it);
				it = cl.begin();
			}
			if (it != cl.end())
				it++;
		}
		while (it1 != cl1.end())
		{
			bit = bm.begin();
			(*it1)->getRect().left -= (*it1)->getSpeed();
			(*it1)->getRect().right -= (*it1)->getSpeed();
			while (bit != bm.end())
			{
				if (checkRectRush((*bit)->getRect(), (*it1)->getRect()))
				{
					delete (*it1);
					cl1.erase(it1);
					it1 = cl1.begin();
					delete(*bit);
					bm.erase(bit);
					killnum++;
					break;
				}
				bit++;
			}
			if (!(*it1)->Show())
			{
				delete (*it1);
				cl1.erase(it1);
				it1 = cl1.begin();
			}
			if (it1 != cl1.end())
				it1++;
		}
		for (int i = 0; i < 4 - cl.size(); i++)
		{
			int order;
			order = abs(rand()) % 7;
			switch (order)
			{
			case 0:
				addCiallo(cl, ciallo, true);
				break;
			case 1:
				addCiallo(cl, ciallo1, true);
				break;
			case 2:
				addCiallo(cl, ciallo2, true);
				break;
			case 3:
				addCiallo(cl, ciallo3, true);
				break;
			case 4:
				addCiallo(cl, ciallo4, true);
				break;
			case 5:
				addCiallo(cl, ciallo5, true);
				break;
			case 6:
				addCiallo(cl, ciallo6, true);
				break;
			}

		}
		for (int i = 0; i < 4 - cl1.size(); i++)
		{
			int order = abs(rand()) % 7;
			switch (order)
			{
			case 0:
				addCiallo(cl1, ciallo, false);
				break;
			case 1:
				addCiallo(cl1, ciallo1, false);
				break;
			case 2:
				addCiallo(cl1, ciallo2, false);
				break;
			case 3:
				addCiallo(cl1, ciallo3, false);
				break;
			case 4:
				addCiallo(cl1, ciallo4, false);
				break;
			case 5:
				addCiallo(cl1, ciallo5, false);
				break;
			case 6:
				addCiallo(cl1, ciallo6, false);
				break;
			}
		}

		EndBatchDraw();

		flushmessage();
		Sleep(2);
		ExMessage mess;
		if (peekmessage(&mess, EX_KEY | EX_MOUSE))//检测暂停
		{
			if (mess.vkcode == VK_ESCAPE || mess.rbutton)
				Pause();
		}

		if (killnum > 10000)//最大目标数
			break;
	}
	if (is_die)//检测死亡
		Over();
	return true;
}
