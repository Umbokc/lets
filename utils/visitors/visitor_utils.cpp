#ifndef LL_UTIL_VISITOR_UTILS_H
#define LL_UTIL_VISITOR_UTILS_H

class VisitorUtils {
public:
	
	// static bool isValue(Node node) {
	// 	return (node instanceof ValueExpression);
	// }

	// static bool isVariable(Node node) {
	// 	return (node instanceof VariableExpression);
	// }

	// static Statement includeProgram(IncludeStatement s) {
	// 	if (!isValue(s)) return null;
	// 	try {
	// 		return s.loadProgram(s.expression.eval().asString());
	// 	} catch (IOException ex) {
	// 		return null;
	// 	}
	// }

	// static bool isIntegerValue(Node node, int valueToCheck) {
	// 	if (!isValue(node)) return false;

	// 	final Value value = ((ValueExpression) node).value;
	// 	if (value.type() != Types.NUMBER) return false;

	// 	final Number number = ((NumberValue) value).raw();
	// 	if ( (number instanceof Integer) || (number instanceof Short) || (number instanceof Byte)) {
	// 		return number.intValue() == valueToCheck;
	// 	}
	// 	return false;
	// }

	// static bool isValueAsInt(Node node, int valueToCheck) {
	// 	if (!isValue(node)) return false;

	// 	final Value value = ((ValueExpression) node).value;
	// 	if (value.type() != Types.NUMBER) return false;

	// 	return value.asInt() == valueToCheck;
	// }

	// static bool isConstantValue(Node node) {
	// 	if (!isValue(node)) return false;

	// 	final int type = ((ValueExpression) node).value.type();
	// 	return ( (type == Types.NUMBER) || (type == Types.STRING) );
	// }

	// static bool isSameVariables(Node n1, Node n2) {
	// 	if (isVariable(n1) && isVariable(n2)) {
	// 		final VariableExpression v1 = (VariableExpression) n1;
	// 		final VariableExpression v2 = (VariableExpression) n2;
	// 		return v1.name.equals(v2.name);
	// 	}
	// 	return false;
	// }

	static std::vector<std::string> operators() {
		std::vector<std::string> operators;
		for (std::string op : NS_Binary::OperatorString) {
			operators.push_back(op);
		}
		for (std::string op : NS_Unary::OperatorString) {
			operators.push_back(op);
		}
		for (std::string op : NS_Conditional::OperatorString) {
			operators.push_back(op);
		}
		return operators;
	}
};

#endif