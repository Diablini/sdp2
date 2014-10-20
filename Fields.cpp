

#ifndef _FIELDS_H_
#define _FIELDS_H_

#include "Fields.h"
#include <fstream>
#include <iostream>
#include <string>

bool StateTable::isFound(char a, STATEFLAG flag)
{
	switch(flag)
	{
	case Next:
		{
			for (size_t i = 0; i < nextcount; i++)
			{
				if (next[i] == a) return true;
			}
		}break;
	case Proceed:
		{
			for (size_t i = 0; i < proceedcount; i++)
			{
				if (proceed[i] == a) return true;
			}
		}break;
	default:
		false;//KRASI
		break;
	}
	return false;//krasi
}

void StateTable::push(char a, STATEFLAG flag)
{
	if (!isFound(a, flag))
	{
		switch (flag)
		{
		case Next:
			next[nextcount] = a;
			nextcount++;
			break;
		case Proceed:
			proceed[proceedcount] = a;
			proceedcount++;
			break;
		default:
			throw std::exception("Invalid state flag in push operation on StateTable");//KRASI
			break;
		}
	}
}

void StateTable::range(char a, char b, STATEFLAG flag)
{
	if (a == b)
	{
		push(a, flag);
	}
	if (b < a)
	{
		std::swap(a,b);
	}
	for (size_t i = a; i <= b; i++)
	{
		push(i, flag);
	}
	
}

Fields::Fields()
{
	state = 0;
	activeStates = 0;
}

void Fields::read(std::string name)
{
	std::fstream file;
	file.open(name, std::ios::in);
	if (!file.is_open())
	{
		throw std::exception("File could not be opened");
	}
	while(!file.eof())
	{
		output bufferout;
		std::string bufferstring;
		std::getline(file, bufferstring);
		/*if (!file.good())
		{
			throw std::exception("Error reading from file");
		}*/
		if (parse(bufferstring, bufferout))
		{
			outputs.push_back(bufferout);
		}
		file.peek();
	}
}


void Fields::printState()
{
	std::cout << "Fields instance is at " << this << std::endl;
	std::cout << "Current seperator symbol is set to: '" << seperator << "'" << std::endl
			  << "Number of loaded state tables is: " << activeStates << std::endl 
			  << "State that Fields is currently in : " << state << std::endl
			  << "::::::::::::::::::::::::::::::::::::::::::::::::::::::" << std::endl;
	if (stateTables.empty()) {std::cout << "No state tables are loaded" << std::endl;}
	for (size_t i = 0; i < stateTables.size(); i++)
	{
		std::cout << "State table " << i << " is as follows: " << std::endl
					<< "NEXT: ";
		for (size_t n =0; n < stateTables[i].nextcount; n++)
		{
			std::cout << stateTables[i].next[n] << " ";
		}
		std::cout << std::endl<< "Proceed: ";
		for (size_t n =0; n < stateTables[i].proceedcount; n++)
		{
			std::cout << stateTables[i].proceed[n] << " ";
		}
		std::cout << std::endl;
	}
}

// returns false if line is invalid and true if line checks out
// returns parsed line in output& out
bool Fields::parse(std::string line, output& out)
{
	state = 0;
	std::string data[4];
	int currentWrite = 0;
	for(size_t i = 0; i < line.length(); i++)
	{
		char symbol = line[i];
		if (symbol == ';')
		{
			if(i == 0)
			{
				return false;
			}
			state++;
			currentWrite++;
			continue;
		}
		if (symbol == '#')
		{
			if (state == activeStates - 1)
			{
				break;
			}
			return false;
		}
		if(stateTables[state].isFound(symbol,Next))
		{
			data[currentWrite] += symbol;
			state++;
			continue;
		}
		if (stateTables[state].isFound(symbol, Proceed))
		{
			data[currentWrite] += symbol;
			continue;
		}
		return false;
		// check abot # in the end of the word

		//NB ako stringa e prazen? set buffer v output
	}
	out.id = atoi(data[0].c_str());
	if (data[1].length() == 1)
	{
		out.unique = (bool) atoi ( data[1].c_str () );
	}
	else return false;
	if (data[2].length() == 1)
	{
		out.null = (bool) atoi ( data[2].c_str () );
	}
	else return false;
	data[3] += '\0'; //krasigei
	out.name = data[3];
	state = 0;
	return true;
}


#endif