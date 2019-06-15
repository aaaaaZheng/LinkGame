#include "pch.h"
#include "ConfigLogic.h"

int ConfigLogic::GetStyle()
{
	return Config::GetSingleInstance()->GetStyle();
}

CString ConfigLogic::GetElemPath()
{
	return Config::GetSingleInstance()->GetElemPath();
}

CString ConfigLogic::GetMaskPath()
{
	return Config::GetSingleInstance()->GetMaskPath();
}

CString ConfigLogic::GetMusicPath()
{
	return Config::GetSingleInstance()->GetMusicPath();
}
