#pragma once
#include<iostream>
#include"global.h"
#include "afxdialogex.h"
using namespace std;
class Config
{
protected:
	int m_nStyle;
	CString m_strElemPath;
	CString m_strMaskPath;
	CString strPath = _T("sources\\config.ini");
	CString m_strMusicPath;
public:
	static Config* m_pConfig;
	int GetStyle();
	CString GetElemPath();
	CString GetMaskPath();
	CString GetMusicPath();
	void SetStyle(int m_nStyle);
	void SetElemPath(CString m_strElemPath);
	void SetMaskPath(CString m_strMaskPath);
	static Config* GetSingleInstance();
	void  Load(int flag);
	void Save(int style);
	void Save(int style, CString element, CString mask);
	static void ReleaseInstance();
};
