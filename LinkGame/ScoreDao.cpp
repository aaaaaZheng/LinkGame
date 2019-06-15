#include "pch.h"
#include "ScoreDao.h"

bool ScoreDao::Save(const CString& strPath, Score& score)
{
	CStdioFile out;
	out.Open(strPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	if (!out)
		return false;
	CString s1;
	s1.Format(_T("%02d"), score.nMode);
	s1.Append(score.strName);
	s1.AppendFormat(_T("%05d"), score.nGrade);
	s1.AppendFormat(_T("%d"), score.nLevel);
	s1.Append(_T("\n"));

	out.SeekToEnd();
	out.WriteString(s1);
	out.Flush();
	out.Close();
	return true;
}

bool ScoreDao::Read(const CString& strPath, vector<Score>& ranks, int nMode)
{
	CStdioFile in;
	in.Open(strPath, CFile::modeRead);
	if (!in)
		return false;
	CString str;
	while (in.ReadString(str))
	{
		Score s;
		Parse(str, s, nMode);
		if (s.nMode == nMode)
			ranks.push_back(s);
	}
	in.Close();
	return true;
}

void ScoreDao::Parse(const CString& str, Score& rank, int nMode)
{
	rank.nLevel = _ttoi(str.Mid(23, 1));
	rank.strName = str.Mid(2, 14);
	rank.nGrade = _ttoi(str.Mid(16, 5));
	rank.nMode = _ttoi(str.Left(2));
}
