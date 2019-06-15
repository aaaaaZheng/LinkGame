#pragma once
#include "global.h"
#include "afxdialogex.h"
#include <vector>
#include<iostream>
using namespace std;
class ScoreDao
{
public:
	bool Save(const CString & strPath, Score& score);
	bool Read(const CString& strPath,vector<Score> &ranks, int nMode);
	void Parse(const CString& str, Score& rank, int nMode);
};

