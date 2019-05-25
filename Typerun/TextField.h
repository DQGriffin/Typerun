#pragma once
#include "Label.h"

class TextField
{
private:
	Label label;
public:
	TextField();
	~TextField();
	void add_character(char character);
	void remove_last_character();
	std::string get_text();
};

