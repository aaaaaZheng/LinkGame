#pragma once
#include "global.h"
#include"ScoreDao.h"
#include <vector>
#include <iostream>
#include<algorithm>
using namespace std;
class ScoreLogic
{
protected:
	ScoreDao scoreDao;
	CString strPath = _T("sources\\Score.txt");
public:
	bool SaveScore(Score& score);
	int SearchRank(vector<Score> &ranks, int nMode);
};

