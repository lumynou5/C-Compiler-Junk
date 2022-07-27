#ifndef C_COMPILER_SYNTAX_TREE_H
#define C_COMPILER_SYNTAX_TREE_H

enum class NodeKind {
    BinaryOp,
    Number,
    State,
};

/// @brief The superclass of nodes.
class Node {
public:
    Node() = default;

    Node(const Node&) = delete;
    Node& operator =(const Node&) = delete;

    [[nodiscard]] virtual NodeKind NODE_KIND() const noexcept = 0;
};

/// @brief The node represents an expression.
class ExprNode : public Node {};

/// @brief The node represents a binary operator subexpression.
class BinaryOpNode : public ExprNode {
public:
    enum Kind {
        Mul,    ///< Multiplication.
        Div,    ///< Division.
        Add,    ///< Addition.
        Sub,    ///< Subtraction.
        Less,   ///< Less than.
        LessEq, ///< Less than or equal to.
        Eq,     ///< Equal.
        NotEq   ///< Not equal.
    };

    BinaryOpNode(Kind kind, ExprNode* lhs, ExprNode* rhs);

    [[nodiscard]] NodeKind NODE_KIND() const noexcept override {
        return NodeKind::BinaryOp;
    }

    Kind kind;
    ExprNode* lhs;
    ExprNode* rhs;
};

/// @brief The node represents a number literal.
class NumberNode : public ExprNode {
public:
    explicit NumberNode(long val);

    [[nodiscard]] NodeKind NODE_KIND() const noexcept override {
        return NodeKind::Number;
    }

    long val;
};

/// @brief The node represents a statement.
class StateNode : public Node {
public:
    StateNode(ExprNode* content, StateNode* next);

    [[nodiscard]] NodeKind NODE_KIND() const noexcept override {
        return NodeKind::State;
    }

    /// @brief The content of this statement.
    ExprNode* content;

    /// @brief The next statement.
    ///
    /// `nullptr` means this is the last statement.
    StateNode* next;
};

#endif //C_COMPILER_SYNTAX_TREE_H
