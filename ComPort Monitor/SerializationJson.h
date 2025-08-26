#pragma once

#ifndef SERIALIZATION_JSON_H_
#define SERIALIZATION_JSON_H_

#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

static json jRead;
static json jSave;
static std::ofstream fout;
static std::ifstream fin;

void setJsonSetting(int baudRate, bool isAutoExtern)
{
	jSave = {
		{"baud", baudRate},
		{"auto", isAutoExtern},
	};
	fout.open("settings.json");

	if (fout.is_open())
	{
		fout << jSave;
	}

	fout.close();
}

void readJsonSetting(int& baudRate, bool& isAutoExtern)
{
	fin.open("settings.json");
	if (fin.is_open())
	{
		std::string str;
		std::getline(fin, str);
		jRead = json::parse(str);
		baudRate = jRead["baud"];
		isAutoExtern = jRead["auto"];
	}

	fin.close();
}

#endif // !SERIALIZATION_JSON_H_

