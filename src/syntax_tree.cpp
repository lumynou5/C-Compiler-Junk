#include "syntax_tree.h"

BinaryOpNode::BinaryOpNode(Kind kind, ExprNode* lhs, ExprNode* rhs)
        : kind(kind), lhs(lhs), rhs(rhs) {}

NumberNode::NumberNode(long val) : val(val) {}

StateNode::StateNode(ExprNode* content, StateNode* next)
        : content(content), next(next) {}
