
#include <vector>
#include <stdint.h>

enum STATEFLAG
{
	Next,
	Proceed,
};

struct StateTable
{
	char next[256];
	char proceed[256];
	unsigned char nextcount;
	unsigned char proceedcount;
	StateTable() {nextcount = 0; proceedcount = 0;}
	bool isFound(char a, STATEFLAG flag);
	void push(char a, STATEFLAG flag);
	void range(char a, char b, STATEFLAG flag);
};

struct output
{
	
	uint32_t id;
	bool unique;
	bool null;
	std::string name;
};


class Fields
{
	char seperator;
	size_t state;
	size_t activeStates;
	std::vector<StateTable> stateTables;//zaredi
	std::vector<output> outputs;
	bool parse(std::string, output&);
public:
	Fields();
	void pushState(StateTable newState)
	{
		stateTables.push_back(newState);
		activeStates++;
	}
	bool checkId(uint32_t id)
	{
		for(size_t i = 0; i < outputs.size();i++)
		{
			if (outputs[i].id == id) return true;
		}return false;
	}
	output getId(uint32_t id)
	{
		if (checkId(id))
		{
			for(size_t i = 0; i < outputs.size();i++)
			{
				if (outputs[i].id == id) return outputs[i];
			}
		}
		throw std::exception("Trying to access non-existant id");
	}
	void read(std::string);
	void setSeperator(char a){seperator = a;}
	void printState();
};
