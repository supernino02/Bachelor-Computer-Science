package visitors.execution;

public interface Value {
	/* default conversion methods */
	default int toInt() {
		throw new InterpreterException("Expecting an integer");
	}

	default boolean toBool() {
		throw new InterpreterException("Expecting a boolean");
	}

	default int[] toVector() {
		throw new InterpreterException("Expecting a vector");
	}

	default PairValue toPair() {
		throw new InterpreterException("Expecting a pair");
	}
}
