
// Machine Learning 101.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMachineLearning101App:
// See Machine Learning 101.cpp for the implementation of this class
//

class CMachineLearning101App : public CWinApp
{
public:
	CMachineLearning101App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMachineLearning101App theApp;
