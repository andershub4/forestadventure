/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#include "Path.h"

#include <windows.h>

std::string GetHead(const std::string& filePath)
{
	std::size_t pos = filePath.find_last_of("\\/");
	std::string path = filePath.substr(0, pos);

	return path;
}


std::string GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);

	return std::string(buffer);
}


std::string GetExePath()
{
	std::string exeFileName = GetExeFileName();
	std::string exePath = GetHead(exeFileName);

	return exePath;
}