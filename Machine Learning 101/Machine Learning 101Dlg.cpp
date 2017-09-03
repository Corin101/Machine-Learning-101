
// Machine Learning 101Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Machine Learning 101.h"
#include "Machine Learning 101Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMachineLearning101Dlg dialog



CMachineLearning101Dlg::CMachineLearning101Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MACHINELEARNING101_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMachineLearning101Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBBOXSTARTINGPLAYER, PlayerSelection);
	DDX_Control(pDX, IDC_GAMEWINDOW, gameWindow);
	DDX_Control(pDX, IDC_CHOICE, playerChoice);
	DDX_Control(pDX, IDC_PLAYER1NAME, player1Name);
	DDX_Control(pDX, IDC_PLAYER2NAME, player2Name);
}

CString CMachineLearning101Dlg::TransformValueToString(int value)
{
	CString str;
	str.Format(_T("%d"), value);
	return str;
}

BEGIN_MESSAGE_MAP(CMachineLearning101Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RULES, &CMachineLearning101Dlg::OnBnClickedRules)
	ON_BN_CLICKED(IDC_EXITGAME, &CMachineLearning101Dlg::OnBnClickedExitgame)
	ON_BN_CLICKED(IDC_GAMEOPTIONS, &CMachineLearning101Dlg::OnBnClickedGameOptions)
	ON_BN_CLICKED(IDC_GAMEBUTTON, &CMachineLearning101Dlg::OnBnClickedGamebutton)
	ON_BN_CLICKED(IDC_PLAYAGAIN, &CMachineLearning101Dlg::OnBnClickedPlayagain)
END_MESSAGE_MAP()


// CMachineLearning101Dlg message handlers


BOOL CMachineLearning101Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	PlayerSelection.AddString(LoadMyString(IDS_PLAYER1NAME));
	PlayerSelection.AddString(LoadMyString(IDS_PLAYER2NAME));
	PlayerSelection.SetCurSel(0);
	GetDlgItem(IDC_GROUP)->GetParent()->CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMachineLearning101Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (!flag)
		{
			CPaintDC dc(this);
			CRect rect;
			GetClientRect(&rect);
			//ScreenToClient(rect);
			BITMAP bmp;
			HBITMAP hBmp = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BACKPCT));
			::GetObject(hBmp, sizeof(bmp), &bmp);
			HDC hDC = ::CreateCompatibleDC(NULL);
			SelectObject(hDC, hBmp);
			::BitBlt(dc.m_hDC, 0, 0, rect.Width(), rect.Height(), hDC, 0, 0, SRCCOPY);
			CDialog::OnPaint();
		}
		else
			CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMachineLearning101Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMachineLearning101Dlg::ShowGameMenu()
{
	flag = true;
	AfxGetMainWnd()->Invalidate();
	GetDlgItem(IDC_STATICPLAYER1)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATICPLAYER2)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATICSTARTINGPLAYER)->ShowWindow(TRUE);
	GetDlgItem(IDC_PLAYER1NAME)->ShowWindow(TRUE);
	GetDlgItem(IDC_PLAYER2NAME)->ShowWindow(TRUE);
	GetDlgItem(IDC_CBBOXSTARTINGPLAYER)->ShowWindow(TRUE);
	GetDlgItem(IDC_GAMEWINDOW)->ShowWindow(TRUE);
	GetDlgItem(IDC_RULES)->ShowWindow(TRUE);
	GetDlgItem(IDC_GROUP)->ShowWindow(TRUE);
	GetDlgItem(IDC_RADIO1)->ShowWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->ShowWindow(TRUE);
	GetDlgItem(IDC_GAMEBUTTON)->ShowWindow(TRUE);
	GetDlgItem(IDC_GAMEOPTIONS)->ShowWindow(FALSE);
}

void CMachineLearning101Dlg::OnBnClickedRules()
{
	CWnd *label = GetDlgItem(IDC_RULESTEXT);
	label->IsWindowVisible() ? label->ShowWindow(FALSE) : label->ShowWindow(TRUE);
}

void CMachineLearning101Dlg::OnBnClickedExitgame()
{
	if (newGame != NULL)
		delete newGame;
	EndDialog(TRUE);
}

void CMachineLearning101Dlg::OnBnClickedGameOptions()
{
		ShowGameMenu();
}

// return text from String Table
CString CMachineLearning101Dlg::LoadMyString(UINT nID)
{
	CString myString;
	myString.LoadString(nID);
	return myString;
}

void CMachineLearning101Dlg::OnBnClickedGamebutton()
{
	if (newGame == NULL)
		newGame = new GameConfig(IsDlgButtonChecked(IDC_RADIO1), !PlayerSelection.GetCurSel());
	else
		newGame->GameReset(IsDlgButtonChecked(IDC_RADIO1), !PlayerSelection.GetCurSel());

	GetDlgItem(IDC_CHOICE)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATICSTICS)->ShowWindow(TRUE);
	GetDlgItem(IDC_GAMEBUTTON)->EnableWindow(FALSE);
	WelcomeMessage();
	if (!newGame->isPlayer1Turn || !newGame->isPlayer1Human)
		playATurn(0);
}

void CMachineLearning101Dlg::WriteToGameWindow(CString textLine, COLORREF color)
{
	int oldLines = 0, newLines = 0, nScroll = 0;
	long nInsertionPoint = 0;
	CHARRANGE cr;
	CHARFORMAT cf;

	// Save number of lines before insertion of new text
	oldLines = gameWindow.GetLineCount();

	// Initialize character format structure
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.dwEffects = 0;	// To disable CFE_AUTOCOLOR
	cf.crTextColor = color;

	// Set insertion point to end of text
	nInsertionPoint = gameWindow.GetWindowTextLength();
	nInsertionPoint = -1;
	gameWindow.SetSel(nInsertionPoint, -1);

	//  Set the character format
	gameWindow.SetSelectionCharFormat(cf);

	// Replace selection. Because we have nothing selected, this will simply insert
	// the string at the current caret position.
	gameWindow.ReplaceSel(textLine);

	// Get new line count
	newLines = gameWindow.GetLineCount();

	// Scroll by the number of lines just inserted
	nScroll = newLines - oldLines;
	gameWindow.LineScroll(nScroll);
}
void CMachineLearning101Dlg::WelcomeMessage()
{
	COLORREF color = red;
	CString str;
	str = LoadMyString(IDS_STARTINGPLAYER);
	newGame->isPlayer1Turn ? str += CheckForName(true) : str += CheckForName(false);
	str.AppendChar('\n');
	str += LoadMyString(IDS_STICKSLEFT) + TransformValueToString(newGame->numberOfSticks) + '\n';
	WriteToGameWindow(str, color);
	playerChoice.SetFocus();
}
CString CMachineLearning101Dlg::CheckForName(bool whichPlayer)
{
	CString playerName;
	whichPlayer ? player1Name.GetWindowText(playerName) : player2Name.GetWindowText(playerName);
	if (playerName.IsEmpty())
		return whichPlayer ? LoadMyString(IDS_PLAYER1NAME) : LoadMyString(IDS_PLAYER2NAME);
	return playerName;
}

bool CMachineLearning101Dlg::playATurn(int sticks)
{
	while (true)
	{
		if (!newGame->isPlayer1Turn)
		{
			newGame->GameTurn();
		}
		else
		{
			if (!newGame->GameTurn(sticks))
			{
				WrongMoveMsg();
				playerChoice.SetFocus();
				return false;
			}
		}
		if (newGame->CheckVictoryCondition())
		{
			EndGameMsg();
			GetDlgItem(IDC_PLAYAGAIN)->ShowWindow(TRUE);
			return false;
		}
		else
		{
			EndTurnMsg();
			if (newGame->isPlayer1Human)
				return true;
		}
	}	
}

void CMachineLearning101Dlg::WrongMoveMsg()
{
	COLORREF color = red;
	CString str;
	str = LoadMyString(IDS_WRONGAMOUNT);
	WriteToGameWindow(str, color);
	GetDlgItem(IDC_CHOICE)->EnableWindow(TRUE);
}

void CMachineLearning101Dlg::EndTurnMsg()
{
	COLORREF color = blue;
	CString str;
	str = LoadMyString(IDS_STICKSTAKEN);
	newGame->isPlayer1Turn ? str += CheckForName(false) : str += CheckForName(true);
	str += "\t\t\t";		
	str	+= TransformValueToString(newGame->sticksTaken) + '\n';	
	str += LoadMyString(IDS_STICKSLEFT) + TransformValueToString(newGame->numberOfSticks) + '\n';
	if (newGame->isPlayer1Turn)
		str += LoadMyString(IDS_TAKESTICKS);
	WriteToGameWindow(str, color);
	if (!newGame->isPlayer1Turn)
		GetDlgItem(IDC_CHOICE)->EnableWindow(TRUE);
	playerChoice.SetFocus();
}

void CMachineLearning101Dlg::EndGameMsg()
{
	COLORREF color = green;
	CString str;
	str = LoadMyString(IDS_WINNER);
	newGame->isPlayer1Turn ? str += CheckForName(false) : str += CheckForName(true);
	str.AppendChar('\n');
	WriteToGameWindow(str, color);
	GetDlgItem(IDC_CHOICE)->EnableWindow(FALSE);
	str = LoadMyString(IDS_STATS1);
	str += CheckForName(true);
	str += LoadMyString(IDS_STATS2) + TransformValueToString(newGame->gameStats.lost) + _T("\n\t\t");
	str += CheckForName(false);
	str += LoadMyString(IDS_STATS2) + TransformValueToString(newGame->gameStats.won) + _T("\n");
	WriteToGameWindow(str, color);
	GetDlgItem(IDC_PLAYAGAIN)->SetFocus();
}

void CMachineLearning101Dlg::OnOK()
{
	if (GetFocus() == &playerChoice)
	{
		CString textValue;
		int value;
		playerChoice.GetWindowText(textValue);
		value = _wtoi(textValue); // Don't really care what i get here, validation is done by the game logic
		GetDlgItem(IDC_CHOICE)->EnableWindow(FALSE);
		playerChoice.SetWindowText(_T(""));
		if (playATurn(value))
			playATurn(0);		
	}
}

void CMachineLearning101Dlg::OnBnClickedPlayagain()
{
	GetDlgItem(IDC_PLAYAGAIN)->ShowWindow(FALSE);
	OnBnClickedGamebutton();
	if (newGame->isPlayer1Human)
	{
		GetDlgItem(IDC_CHOICE)->EnableWindow(TRUE);
		playerChoice.SetFocus();
	}
}
