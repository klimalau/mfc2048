// 2048Dlg.cpp : 实现文件
//
#include <ctime>
#include <cstdlib>
using namespace std;

#include "stdafx.h"
#include "2048.h"
#include "2048Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2048Dlg 对话框



CMy2048Dlg::CMy2048Dlg(CWnd* pParent /*=NULL*/)
: CDialog(CMy2048Dlg::IDD, pParent)
, m_ptBegin(0)
, m_bDraw(FALSE)
, m_isTryMove(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ptBegin = CPoint(0, 0);
	m_bDraw = false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_pane[i][j] = 0;
		}
	}
	srand((int)(time(NULL)));
	//m_pane[0][0] = 1024;
	m_pane[rand() % 4][rand() % 4] = 2;
	m_pane[rand() % 4][rand() % 4] = 2;
	//m_pane[0][3] = 2;
	//m_pane[0][0] = 2;
}

void CMy2048Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy2048Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CMy2048Dlg 消息处理程序

BOOL CMy2048Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy2048Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CMy2048Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/************************************************************************
* COLORS:          
0   :	0xFFB3C0CC
2   :	0xffeee4da
4   :	0xffede0c8
8   :	0xfff2b179
16  :	0xfff59563
32  :	0xfff67c5f
64	:	0xfff65e3b
128	:	0xffedcf72
256 :   0xffedcc61
512 :	0xffedc850
1024:	0xffedc53f
2048:	0xffedc22e
4096:	0xff3c3a32
9182:
************************************************************************/
int colorAry[] = {0xFFB3C0CC, 0x00DAE4EE, 0x00C8E0ED, 0x0079B1F2, 0x006395F5,//16
0x005F7CF6, 0x003B5EF6, 0x0072CFED, 0x0061CCED, 0x0050C8ED, //512
0x003FC5ED, 0xffedc22e, 0xff3c3a32};
void getColorWithCount(int count, COLORREF &color)
{
	if (count < 0)
	{
		return ;
	}
	else if (count > 4096)
	{
		color = 0xff3c3a32 & 0x00FFFFFF;
	}
	else
	{
		int i = 0;
		while (count / 2 > 0)
		{
			i ++;
			count /= 2;
		}
		color = colorAry[i] & 0x00FFFFFF;
	}

	return ;
}

/*
CPoint positions[4][4] = {CPoint(15, 15), CPoint(), CPoint(), CPoint(), 
						CPoint(), CPoint(), CPoint(), CPoint(),
						CPoint(), CPoint(), CPoint(), CPoint(),
						CPoint(), CPoint(), CPoint(), CPoint()};
*/
void CMy2048Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	int lwidth = 108;	//小方块的边长
	int lradix = 5;		//小方块的圆角
	LONG left = 5;
	LONG top = 5;
	LONG width = 500;
	LONG height = 500;
	LONG radix = 10;

	int fontWidth = 37;
	int fontHeight = 37;
	int fontWeight = FW_SEMIBOLD;
	CString fontName = "华文行楷";

	int dis = 123;
	CRgn roundRect; 
	CFont font;
	CRect thisRect;
	CBrush brush; 

	brush.CreateSolidBrush(RGB(187, 173, 160));
	CClientDC dc(this); 
	// 设置TextOut文本背景色模式为透明
	SetBkMode(dc, TRANSPARENT);

	this->GetWindowRect(&thisRect);
	this->SetWindowPos(NULL, thisRect.left, thisRect.top, width + left * 2, height + top * 7, SWP_NOMOVE);
	roundRect.CreateRoundRectRgn(left, top, width, height, radix, radix);
	dc.FillRgn(&roundRect, &brush);


	int x , y;
	font.CreateFont(fontHeight, fontWidth, 0, 0, fontWeight, 0, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, fontName);
	CFont* pOldFont = dc.SelectObject(&font);
	CString str;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//x = left + 123 * i + 15;
			//y = top + 123  * j + 15;
			x = left + 123 * j + 15;
			y = top + 123 * i + 15;
			COLORREF color;
			getColorWithCount(m_pane[i][j], color);
			brush.DeleteObject();
			brush.CreateSolidBrush(color);
			roundRect.DeleteObject();
			//roundRect.CreateRoundRectRgn(x - lradix, y - lradix, x + lwidth - lradix * 2, y + lwidth - lradix * 2, lradix, lradix);
			roundRect.CreateRoundRectRgn(x - lradix, y - lradix, x + lwidth - lradix * 2, y + lwidth - lradix * 2, lradix, lradix);
			dc.FillRgn(&roundRect, &brush);
			//获取文字的高度和宽度
			if (m_pane[i][j] != 0)
			{
				str.Format("%d", m_pane[i][j]);
				int nTextHei = dc.GetTextExtent(str).cy; // length of horizontal label文字的高度
				int nTextWei = dc.GetTextExtent(str).cx; // length of horizontal label文字的宽度
				double divNum = 1.33;
				while (nTextWei > lwidth * 0.75)
				{
					font.DeleteObject();
					font.CreateFont(fontHeight, fontWidth / divNum, 0, 0, fontWeight, 0, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
						CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, fontName);
					dc.SelectObject(font);
					nTextWei = dc.GetTextExtent(str).cx;
					divNum *= 1.33;
				}
				int fontx = x - lradix * 2 + (lwidth / 2) - nTextWei / 2;
				int fonty = y - lradix + (lwidth / 2) - nTextHei / 2;
				dc.TextOut(fontx, fonty, str);
				font.DeleteObject();
				font.CreateFont(fontHeight, fontWidth, 0, 0, fontWeight, 0, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, fontName);
				dc.SelectObject(font);
			}
		}
	}
	brush.DeleteObject();
	dc.SelectObject(pOldFont);
	roundRect.DeleteObject();
}

bool CMy2048Dlg::moveLeft(void)
{
	bool succeed = false;
	for (int i = 0; i < 4; i++)
	{
		//如果（1，2）（3，4）可以合并
		if (m_pane[i][0] != 0 && m_pane[i][2] != 0 
			&& m_pane[i][0] == m_pane[i][1] 
		&& m_pane[i][2] == m_pane[i][3])
		{
			succeed = true;
			m_pane[i][0] *= 2;
			m_pane[i][1] = m_pane[i][2] * 2;
			m_pane[i][2] = 0;
			m_pane[i][3] = 0;
		}
		else if (m_pane[i][0] != 0 && m_pane[i][0] == m_pane[i][1])//(1, 2)可以合并
		{
			succeed = true;
			m_pane[i][0] = m_pane[i][0] * 2;
			m_pane[i][1] = m_pane[i][2];
			m_pane[i][2] = m_pane[i][3];
			m_pane[i][3] = 0;
		}
		else if (m_pane[i][1] != 0 && m_pane[i][2] == m_pane[i][1])	//(2, 3)可以合并
		{
			succeed = true;
			m_pane[i][1] = m_pane[i][1] * 2;
			m_pane[i][2] = m_pane[i][3];
			m_pane[i][3] = 0;
			if (m_pane[i][0] == 0)	//如果第一位是0
			{
				for(int j = 0; j < 3; j++)
				{
					m_pane[i][j] = m_pane[i][j + 1];
				}
			}
		}
		else if (m_pane[i][2] != 0 && m_pane[i][3] == m_pane[i][2])	//(3, 4)可以合并
		{
			succeed = true;
			m_pane[i][2] = m_pane[i][2] * 2;
			m_pane[i][3] = 0;
			if (m_pane[i][1] == 0)
			{
				for(int j = 1; j < 3; j++)
				{
					m_pane[i][j] = m_pane[i][j + 1];
				}
			}
			if (m_pane[i][0] == 0)
			{
				for(int j = 0; j < 3; j++)
				{
					m_pane[i][j] = m_pane[i][j + 1];
				}
			}
		}
		else if (m_pane[i][0] != 0 && m_pane[i][1] == 0 && m_pane[i][0] == m_pane[i][2])//(1, 3)可以合并
		{
			succeed = true;
			m_pane[i][0] *= 2;
			m_pane[i][1] = m_pane[i][3];
			m_pane[i][2] = 0;
			m_pane[i][3] = 0;
		}
		else if (m_pane[i][1] != 0 && m_pane[i][2] == 0 && m_pane[i][1] == m_pane[i][3])//(2, 4)可以合并
		{
			succeed = true;
			m_pane[i][1] *= 2;
			m_pane[i][2] = 0;
			m_pane[i][3] = 0;
			if (m_pane[i][0] == 0)	//如果第一位是0
			{
				for(int j = 0; j < 3; j++)
				{
					m_pane[i][j] = m_pane[i][j + 1];
				}
			}
		}
		else if (m_pane[i][0] != 0 && m_pane[i][1] == 0 && m_pane[i][2] == 0 && m_pane[i][3] == m_pane[i][0])//	(1, 4)可以合并
		{
			succeed = true;
			m_pane[i][0] *= 2;
			m_pane[i][1] = 0;
			m_pane[i][2] = 0;
			m_pane[i][3] = 0;
		}
		else
		{
			int idx = 0;
			for (int j = 0; j < 4; j++)
			{
				if (m_pane[i][j] != 0)
				{
					m_pane[i][idx ++] = m_pane[i][j];
					if (idx - 1 != j)
					{
						m_pane[i][j] = 0;
						succeed = true;
					}
				}
			}
		}
	}
	if (succeed)
	{
		createNextBlock();
		if (!m_isTryMove)
		{
			if (!isMoveable())
			{
				MessageBox("Game Over!");
			}
		}
	}
	return succeed;
}

bool CMy2048Dlg::moveRight(void)
{
	roundPane();
	roundPane();

	bool succeed = moveLeft();
	roundPane();
	roundPane();

	return succeed;
}

bool CMy2048Dlg::moveUp(void)
{
	roundPane();

	bool succeed = moveLeft();
	roundPane();
	roundPane();
	roundPane();
	return succeed;
}

bool CMy2048Dlg::moveDown(void)
{
	roundPane();
	roundPane();
	roundPane();

	bool succeed = moveLeft();
	roundPane();
	return succeed;
}

void CMy2048Dlg::roundPane(void)
{
	int i, j, n = 4;
	int tmp;
	for (i = 0; i < 3; i++)
	{
		for (j = i; j < 3 - i; j++)
		{
			tmp = m_pane[i][j];
			m_pane[i][j] = m_pane[j][n-i-1];
			m_pane[j][n-i-1] = m_pane[n-i-1][n-j-1];
			m_pane[n-i-1][n-j-1] = m_pane[n-j-1][i];
			m_pane[n-j-1][i] = tmp;
		}
	}
}

void CMy2048Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

BOOL CMy2048Dlg::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN )
	{
		bool status = false;
		switch(pMsg->wParam)
		{
		case VK_LEFT:
			status = moveLeft();
			break;
		case VK_RIGHT:
			status = moveRight();
			break;
		case VK_UP:
			status = moveUp();
			break;
		case VK_DOWN:
			status = moveDown();
			break;
		case VK_ESCAPE:
			exit(0);
			break;
		}
		OnLButtonDown(0, NULL);
	}
	return FALSE;
}

BOOL CMy2048Dlg::createNextBlock(void)
{
	int freeBlockNum = 0;
	int freeBlocks[16];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_pane[i][j] == 0)
			{
				freeBlocks[freeBlockNum ++] = i * 4 + j;
			}
		}
	}
	if (freeBlockNum == 0)
	{
		return FALSE;
	}
	else
	{
		int nextBlock = freeBlocks[rand() % freeBlockNum];
		m_pane[nextBlock / 4][nextBlock % 4] = 2;
		return TRUE;
	}
}

BOOL CMy2048Dlg::hasFreeBlock(void)
{
	int freeBlockNum = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_pane[i][j] == 0)
			{
				freeBlockNum ++;
			}
		}
	}
	return freeBlockNum != 0;
}

BOOL CMy2048Dlg::isMoveable(void)
{
	int bm_pane[4][4];
	BOOL result;
	if (hasFreeBlock())
	{
		return TRUE;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				bm_pane[i][j] = m_pane[i][j];
			}
		}
		m_isTryMove = TRUE;
		result = moveLeft();
		result = moveRight() || result;
		result = moveUp() || result;
		result = moveDown() || result;
		m_isTryMove = FALSE;
		memcpy(m_pane, bm_pane, sizeof(bm_pane));
	}
	return result;
}
