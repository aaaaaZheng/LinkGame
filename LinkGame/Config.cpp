#include "pch.h"
#include "Config.h"
Config* Config::m_pConfig = NULL;

int Config::GetStyle()
{
	return m_nStyle;
}

CString Config::GetElemPath()
{
	return m_strElemPath;
}

CString Config::GetMaskPath()
{
	return m_strMaskPath;
}

CString Config::GetMusicPath()
{
	return m_strMusicPath;
}

void Config::SetStyle(int m_nStyle)
{
	this->m_nStyle = m_nStyle;
}

void Config::SetElemPath(CString m_strElemPath)
{
	this->m_strElemPath = m_strElemPath;
}

void Config::SetMaskPath(CString m_strMaskPath)
{
	this->m_strMaskPath = m_strMaskPath;
}

Config* Config::GetSingleInstance()
{
	if (Config::m_pConfig == NULL)
	{
		Config::m_pConfig = new Config();
		Config::m_pConfig->Load(0);
	}
	return Config::m_pConfig;
}

void Config::Load(int flag)
{
	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
	BOOL ifFind = finder.FindFile(strPath);
	CString str;
	CString str1;
	CString str2;
	CString str3;
	CString pic = _T("Picture");
	if (flag == 1 || flag == 2)
		pic.AppendFormat(_T("%d"), flag);
	GetPrivateProfileString(pic, _T("style"), CString("NULL"), str.GetBuffer(MAX_PATH), MAX_PATH, strPath);
	m_nStyle = _ttoi(str);
	GetPrivateProfileString(pic, _T("Element"), CString("没找到"), str1.GetBuffer(MAX_PATH), MAX_PATH, strPath);
	m_strElemPath = str1;
	GetPrivateProfileString(pic, _T("Mask"), CString("没找到"), str2.GetBuffer(MAX_PATH), MAX_PATH, strPath);
	m_strMaskPath = str2;
	GetPrivateProfileString(_T("Music"), _T("Path"), CString("没找到"), str3.GetBuffer(MAX_PATH), MAX_PATH, strPath);
	m_strMusicPath = str3;
}
void Config::Save(int style)
{
	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
	BOOL ifFind = finder.FindFile(strPath);
	if (!ifFind)
	{
		WritePrivateProfileStringW(_T("Picture"), _T("style"), _T("0"), strPath);
		WritePrivateProfileStringW(_T("Picture"), _T("Element"), _T("sources\\fruit_element.bmp"), strPath);
		WritePrivateProfileStringW(_T("Picture"), _T("Mask"), _T("sources\\fruit_mask.bmp"), strPath);
	}
	if (style == 1)
		Load(1);
	else if (style == 2)
		Load(2);
	CString str;
	str.Format(_T("%d"), m_nStyle);
	WritePrivateProfileStringW(_T("Picture"), _T("style"), str, strPath);
	WritePrivateProfileStringW(_T("Picture"), _T("Element"), m_strElemPath, strPath);
	WritePrivateProfileStringW(_T("Picture"), _T("Mask"), m_strMaskPath, strPath);
}
void Config::Save(int style, CString element, CString mask)
{
	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
	BOOL ifFind = finder.FindFile(strPath);
	if (!ifFind)
	{
		WritePrivateProfileStringW(_T("Picture"), _T("style"), _T("0"), strPath);
		WritePrivateProfileStringW(_T("Picture"), _T("Element"), _T("sources\\fruit_element.bmp"), strPath);
		WritePrivateProfileStringW(_T("Picture"), _T("Mask"), _T("sources\\fruit_mask.bmp"), strPath);
	}
	CString str;
	str.Format(_T("%d"), style);
	WritePrivateProfileStringW(_T("Picture"), _T("style"), str, strPath);
	WritePrivateProfileStringW(_T("Picture"), _T("Element"), element, strPath);
	WritePrivateProfileStringW(_T("Picture"), _T("Mask"), mask, strPath);
	m_nStyle = 3;
	m_strElemPath = element;
	m_strMaskPath = mask;
}

void Config::ReleaseInstance()
{
	if (Config::m_pConfig != NULL)
	{
		delete Config::m_pConfig;
		Config::m_pConfig = NULL;
	}
}
