package parser.ast;

import static java.util.Objects.requireNonNull;

public abstract class NonEmptySeq<FT,RT> {
	protected final FT first;
	protected final RT rest;

	protected NonEmptySeq(FT first, RT rest) {
		this.first = requireNonNull(first);
		this.rest = requireNonNull(rest);
	}

	@Override
	public String toString() {
		return getClass().getSimpleName() + "(" + first + "," + rest + ")";
	}
}
