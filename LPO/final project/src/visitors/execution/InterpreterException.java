package visitors.execution;

public class InterpreterException extends RuntimeException {

	public InterpreterException() {
	}

	//describe exception caused by 2 VectValue with different size
	public InterpreterException(VectValue v1, VectValue v2) {
		this("required same size, found " + v1.getSize() + " and " + v2.getSize());
	}

	public InterpreterException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
	}

	public InterpreterException(String message, Throwable cause) {
		super(message, cause);
	}

	public InterpreterException(String message) {
		super(message);
	}

	public InterpreterException(Throwable cause) {
		super(cause);
	}

}
