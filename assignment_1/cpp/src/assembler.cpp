#include "assembler.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

int GetRegIndex(std::string reg)
{
	return stoi(reg.substr(1));
}

int GetConstant(std::string constant)
{
	return stoi(constant.substr(1));
}

bool IsReg(std::string term)
{
	return term[0] == 'R';
}

int ExtractValue(std::string source, int *registers)
{
	if (IsReg(source))
	{
		return registers[GetRegIndex(source)];
	}
	return GetConstant(source);
}

bool ASM::BuildCommandList(std::vector<std::vector<std::string>> &commandList, std::string filepath)
{
	commandList.clear();

	std::ifstream file;
	file.open(filepath);
	if (!file.is_open())
		return false;

	std::vector<std::string> labelNames, labelRows;

	std::string str;
	while (getline(file, str))
	{
		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

		if (str.length() == 0)
			continue;

		std::vector<std::string> lineparts;
		{
			std::vector<std::string> result;
			std::istringstream iss(str);
			for (std::string s; iss >> s;)
				result.push_back(s);
			lineparts = result;
		}

		if (lineparts[0].back() == ':')
		{
			lineparts[0] = lineparts[0].substr(0, lineparts[0].length() - 1);
			labelNames.push_back(lineparts[0]);
			labelRows.push_back(std::to_string(commandList.size()));
		}
		else
		{
			commandList.push_back(lineparts);
		}
	}
	file.close();

	for (int i = 0; i < commandList.size(); i++)
	{
		if (commandList[i][0] == "JEQ" || commandList[i][0] == "JGT" || commandList[i][0] == "JLT")
		{
			int index = -1;
			for (int j = 0; j < labelNames.size(); j++)
			{
				if (labelNames[j] == commandList[i][1])
				{
					index = j;
				}
			}
			commandList[i][1] = labelRows[index];
		}
	}

	return true;
}

int ASM::PeekNextCommandIndex(int *registers)
{
	return registers[ASM::REGISTER_SIZE - 1];
}

int ASM::GetAndStepCommandIndex(int *registers)
{
	int index = registers[ASM::REGISTER_SIZE - 1];
	registers[ASM::REGISTER_SIZE - 1] += 1;
	return index;
}

void ASM::MOV(std::vector<std::string> &command, int *registers)
{
	auto destIndex = GetRegIndex(command[1]);
	auto value = ExtractValue(command[2], registers);
	registers[destIndex] = value;
}

void ASM::ADD(std::vector<std::string> &command, int *registers)
{
	auto destIndex = GetRegIndex(command[1]);
	auto term1 = ExtractValue(command[2], registers);
	auto term2 = ExtractValue(command[3], registers);
	registers[destIndex] = term1 + term2;
}

void ASM::SUB(std::vector<std::string> &command, int *registers)
{
	auto destIndex = GetRegIndex(command[1]);
	auto term1 = ExtractValue(command[2], registers);
	auto term2 = ExtractValue(command[3], registers);
	registers[destIndex] = term1 - term2;
}

void ASM::CMP(std::vector<std::string> &command, int *registers)
{
	auto value1 = ExtractValue(command[1], registers);
	auto value2 = ExtractValue(command[2], registers);
	if (value1 == value2)
		registers[ASM::REGISTER_SIZE - 2] = 1;
	else if (value1 > value2)
		registers[ASM::REGISTER_SIZE - 2] = 2;
	else
		registers[ASM::REGISTER_SIZE - 2] = 3;
}

void ASM::JEQ(std::vector<std::string> &command, int *registers)
{
	if (registers[ASM::REGISTER_SIZE - 2] == 1)
	{
		registers[ASM::REGISTER_SIZE - 1] = std::stoi(command[1]);
	}
}

void ASM::JGT(std::vector<std::string> &command, int *registers)
{
	if (registers[ASM::REGISTER_SIZE - 2] == 2)
	{
		registers[ASM::REGISTER_SIZE - 1] = std::stoi(command[1]);
	}
}

void ASM::JLT(std::vector<std::string> &command, int *registers)
{
	if (registers[ASM::REGISTER_SIZE - 2] == 3)
	{
		registers[ASM::REGISTER_SIZE - 1] = std::stoi(command[1]);
	}
}