package parser.ast;

import visitors.Visitor;

import static java.util.Objects.requireNonNull;

public class ForEachStmt implements Stmt {
	private final Variable ident;
	private final Exp vector;
	private final Block block; // could be null

	public ForEachStmt (Variable ident, Exp vector, Block block) {
		this.ident = requireNonNull(ident);
		this.vector = requireNonNull(vector);
		this.block = block;
	}
	@Override
	public String toString() {
		return getClass().getSimpleName() + "(" + ident + "," + vector + "," + block + ")";
	}

	@Override
	public <T> T accept(Visitor<T> visitor) {
		return visitor.visitForEachStmt (ident, vector, block);
	}
}
