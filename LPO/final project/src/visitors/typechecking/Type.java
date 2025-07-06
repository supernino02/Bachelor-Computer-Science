package visitors.typechecking;

public interface Type {
	default void checkEqual(Type found) throws TypecheckerException {
		if (!equals(found))
			throw new TypecheckerException("Found " + found + ", expected " + toString());
	}

	default PairType checkIsPairType() throws TypecheckerException {
		if (this instanceof PairType pt)
			return pt;
		throw new TypecheckerException("Found " + toString() + ", expected " + PairType.TYPE_NAME);
	}

	default Type getFstPairType() throws TypecheckerException {
		return checkIsPairType().getFstType();
	}

	default Type getSndPairType() throws TypecheckerException {
		return checkIsPairType().getSndType();
	}
}
