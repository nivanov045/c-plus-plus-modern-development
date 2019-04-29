#include "node.h"
#include "date.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const
{
  return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& comp, const Date & date) : _date(date), _comp(comp) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
  switch (_comp) {
  case Less:
    return date < _date;
  case LessOrEqual:
    return !(_date < date);
  case Greater:
    return _date < date;
  case GreaterOrEqual:
    return !(date < _date);
  case Equal:
    return !(_date < date) && !(date < _date);
  case NotEqual:
    return _date < date || date < _date;
  }
  return false;
}

EventComparisonNode::EventComparisonNode(const Comparison& comp, const string& event) : _comp(comp), _event(event) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
  switch (_comp) {
  case Less:
    return event < _event;
  case LessOrEqual:
    return event <= _event;
  case Greater:
    return event > _event;
  case GreaterOrEqual:
    return event >= _event;
  case Equal:
    return event == _event;
  case NotEqual:
    return event != _event;
  }
  return false;

}

LogicalOperationNode::
LogicalOperationNode(const LogicalOperation& oper, shared_ptr<Node> lhn, shared_ptr<Node> rhn) : _oper(oper), _lhn(lhn),
                                                                                                 _rhn(rhn) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
  switch (_oper) {
  case LogicalOperation::And:
    return _lhn->Evaluate(date, event) && _rhn->Evaluate(date, event);
  case LogicalOperation::Or:
    return _lhn->Evaluate(date, event) || _rhn->Evaluate(date, event);
  }
  return false;
}
