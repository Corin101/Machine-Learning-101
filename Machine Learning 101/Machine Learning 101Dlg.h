
// Machine Learning 101Dlg.h : header file
//

#pragma once
#include "afxwin.h"


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


// Implementation
protected:
	HICON m_hIcon;
	BOOL flag = false;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRules();
	afx_msg void OnBnClickedExitgame();
	afx_msg void OnBnClickedStartgame();
protected:
	CComboBox CComboBox;
};
