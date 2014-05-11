// 2048Dlg.h : 头文件
//

#pragma once
#include "atltypes.h"


// CMy2048Dlg 对话框
class CMy2048Dlg : public CDialog
{
// 构造
public:
	CMy2048Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY2048_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CPoint m_ptBegin;
public:
	BOOL m_bDraw;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	int m_pane[4][4];
public:
	bool moveLeft(void);
public:
	bool moveRight(void);
public:
	bool moveUp(void);
public:
	bool moveDown(void);
public:
	void roundPane(void);
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	BOOL PreTranslateMessage(MSG* pMsg);
public:
	void StartGame();
	void Restart();
	BOOL createNextBlock(void);
public:
	BOOL hasFreeBlock(void);
public:
	BOOL isMoveable(void);
public:
	BOOL m_isTryMove;
public:
	afx_msg LRESULT OnHotKey(WPARAM wParam , LPARAM lParam);
public:
	BOOL m_isTouchBoardOk;
public:
	afx_msg void OnDestroy();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	CPoint m_prePos;
public:
	int m_mouseX;
public:
	int m_mouseY;
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
