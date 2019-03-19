#pragma once
#include <string>
#include <memory>

#include "date.h"

using namespace std;

enum LogicalOperation
{
  Or,
  And
};

enum Comparison
{
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

class Node
{
public:
  virtual ~Node() = default;
  virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node
{
public:
  bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node
{
public:
  DateComparisonNode(const Comparison& comp, const Date& date);
  bool Evaluate(const Date& date, const string& event) const override;
private:
  const Date _date;
  const Comparison _comp;
};

class EventComparisonNode : public Node
{
public:
  EventComparisonNode(const Comparison& comp, const string& event);
  bool Evaluate(const Date& date, const string& event) const override;
private:
  const Comparison _comp;
  const string _event;
};

class LogicalOperationNode : public Node
{
public:
  LogicalOperationNode(const LogicalOperation& oper, shared_ptr<Node> lhn, shared_ptr<Node> rhn);
  bool Evaluate(const Date& date, const string& event) const override;
private:
  const LogicalOperation _oper;
  shared_ptr<Node> _lhn;
  shared_ptr<Node> _rhn;
};