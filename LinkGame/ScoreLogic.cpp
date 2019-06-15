#include "pch.h"
#include "ScoreLogic.h"
bool ScoreLogic::SaveScore(Score& score)
{
	return scoreDao.Save(strPath, score);
}
bool CompScore(const Score& a, const Score& b)
{
	return a.nGrade > b.nGrade;
}

int ScoreLogic::SearchRank(vector<Score> &ranks, int nMode)
{
	scoreDao.Read(strPath, ranks, nMode);
	sort(ranks.begin(), ranks.end(),CompScore);
	return (int)ranks.size();
}

