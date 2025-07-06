package visitors.typechecking;

public class TypecheckerException extends RuntimeException {

	public TypecheckerException() {
	}

	//used when find unexpected type , tih only 1 possible value
	public TypecheckerException(Type found, Type expected) {
		this("Found " + found + " expected " + expected);
	}

	//used when find unexpected type, and has 2 possible values
	public TypecheckerException(Type found, Type expected1,Type expected2) {
		super("Found " + found + " expected " + expected1 + " or " + expected2);
	}
	public TypecheckerException(String message, Throwable cause, boolean enableSuppression,
			boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
	}

	public TypecheckerException(String message, Throwable cause) {
		super(message, cause);
	}

	public TypecheckerException(String message) {
		super(message);
	}

	public TypecheckerException(Throwable cause) {
		super(cause);
	}

}
