// Zada4a5.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include "Fields.h"

int main()
{
	Fields my;
	StateTable zero;
	zero.range('1', '9', Next);
	StateTable one;
	one.range('0', '9', Proceed);
	StateTable two;
	two.range('0','1', Proceed);
	StateTable tree;
	tree.range('0','1', Proceed);
	StateTable four;
	four.range('a','z', Proceed);
	four.range('A', 'Z', Proceed);
	my.pushState(zero);
	my.pushState(one);
	my.pushState(two);
	my.pushState(tree);
	my.pushState(four);
	my.printState();
	my.read("fail.txt");
	return 0;
}
