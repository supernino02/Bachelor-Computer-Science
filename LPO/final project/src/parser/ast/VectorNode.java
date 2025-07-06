package parser.ast;

import visitors.Visitor;

import static java.util.Objects.requireNonNull;

public class VectorNode implements Exp {
	private final Exp position;
	private final Exp size;
	public VectorNode (Exp position, Exp size) {
		this.position = requireNonNull (position);
		this.size = requireNonNull(size);
	}

	@Override
	public String toString() {
		return getClass().getSimpleName() + "[" + position + ";" + size + "]";
	}

	@Override
	public <T> T accept(Visitor<T> visitor) {
		return visitor.visitVector(position, size);
	}
}
