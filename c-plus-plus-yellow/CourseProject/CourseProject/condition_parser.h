#pragma once
#include <memory>
#include <sstream>

#include "node.h"


using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

Date ParseDate(istream& stream);