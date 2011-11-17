/*!
 * \file main.cpp
 * \date 11-17-2011 13:43:19
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "main.h"
#include <iostream>
#include "MsgGenFactory.h"

void PrintHelp()
{
	std::cout << "MsgGen usage: MsgGen [input_file] [output_dir]" << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		PrintHelp();
		return 0;
	}

	if (MsgGenFactory::GetInstance().Initialize())
	{
		bool bOk = MsgGenFactory::GetInstance().Parse(argv[1], argv[2]);
		if (!bOk) std::cout << "Parse failed!" << std::endl;
		MsgGenFactory::GetInstance().Terminate();
	}

	return 0;
}
