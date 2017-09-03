
// Machine Learning 101Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "GameConfig.h"
#include "afxcmn.h"

#define red RGB(255, 0, 0);
#define blue RGB(0, 0, 150);
#define green RGB(0,100,0);

// CMachineLearning101Dlg dialog
class CMachineLearning101Dlg : public CDialogEx
{
// Construction
public:
	CMachineLearning101Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MACHINELEARNING101_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	CString TransformValueToString(int value);

// Implementation
protected:
	HICON m_hIcon;
	BOOL flag = false;
	GameConfig *newGame = NULL;
	CComboBox PlayerSelection;
	virtual void OnOK();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void ShowGameMenu();
	DECLARE_MESSAGE_MAP()

public:
	CRichEditCtrl gameWindow;
	CEdit playerChoice;
private:
	afx_msg void OnBnClickedRules();
	afx_msg void OnBnClickedExitgame();
	afx_msg void OnBnClickedGameOptions();
	afx_msg void OnBnClickedGamebutton();
	afx_msg void OnBnClickedPlayagain();
	CString LoadMyString(UINT nID);
	void WriteToGameWindow(CString textLine, COLORREF color);
	int GetValueFromEditControl(CEdit *control);
	void ShowHumanInput();
	void StartNewGame();
	void WelcomeMessage();
	bool playATurn(int sticks);
	void WrongMoveMsg();
	void EndTurnMsg();
	void EndGameMsg();
	CString CheckForName(bool whichPlayer);
	CEdit autoGames;
	CEdit player1Name;
	CEdit player2Name;

public:
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
};
