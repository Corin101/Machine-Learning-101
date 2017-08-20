
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
	DDX_Control(pDX, IDC_CBBOXSTARTINGPLAYER, CComboBox);
}

BEGIN_MESSAGE_MAP(CMachineLearning101Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RULES, &CMachineLearning101Dlg::OnBnClickedRules)
	ON_BN_CLICKED(IDC_EXITGAME, &CMachineLearning101Dlg::OnBnClickedExitgame)
	ON_BN_CLICKED(IDC_STARTGAME, &CMachineLearning101Dlg::OnBnClickedStartgame)
END_MESSAGE_MAP()


// CMachineLearning101Dlg message handlers

BOOL CMachineLearning101Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CComboBox.AddString(LoadMyString(IDS_PLAYER1NAME));
	CComboBox.AddString(LoadMyString(IDS_PLAYER2NAME));
	CComboBox.SetCurSel(0);
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
	flag = TRUE;
	AfxGetMainWnd()->Invalidate();
	GetDlgItem(IDC_STATICPLAYER1)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATICPLAYER2)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATICSTARTINGPLAYER)->ShowWindow(TRUE);
	GetDlgItem(IDC_PLAYER1NAME)->ShowWindow(TRUE);
	GetDlgItem(IDC_PLAYER2NAME)->ShowWindow(TRUE);
	GetDlgItem(IDC_CBBOXSTARTINGPLAYER)->ShowWindow(TRUE);
	GetDlgItem(IDC_GAMEWINDOW)->ShowWindow(TRUE);
	GetDlgItem(IDC_RULES)->ShowWindow(TRUE);
}



void CMachineLearning101Dlg::OnBnClickedRules()
{
	CWnd *label = GetDlgItem(IDC_RULESTEXT);
	if (!label->IsWindowVisible())
	{
		label->ShowWindow(TRUE);
	}
	else
	{
		label->ShowWindow(FALSE);
	}
}


void CMachineLearning101Dlg::OnBnClickedExitgame()
{
	EndDialog(TRUE);
}


void CMachineLearning101Dlg::OnBnClickedStartgame()
{
	if (!flag)
	{
		ShowGameMenu();
	}
	else
	{
		GameConfig newGame;
		newGame.GetValueFromList(11);
		GetDlgItem(IDC_GAMEWINDOW)->SetWindowText(LoadMyString(IDS_STICKSTAKEN) + newGame.TransformValueToString());
		list<int>::iterator li = newGame.pool[3].end();
		newGame.pool[3].insert(li, 4);
	}
}

// return text from String Table
CString CMachineLearning101Dlg::LoadMyString(UINT nID)
{
	CString myString;
	myString.LoadString(nID);
	return myString;
}
