package visitors.typechecking;

import static visitors.typechecking.AtomicType.*;

import environments.EnvironmentException;
import environments.GenEnvironment;
import parser.ast.Block;
import parser.ast.Exp;
import parser.ast.Stmt;
import parser.ast.StmtSeq;
import parser.ast.Variable;
import visitors.Visitor;

public class Typecheck implements Visitor<Type> {

	private final GenEnvironment<Type> env = new GenEnvironment<>();

    // useful to typecheck binary operations where operands must have the same type 
	private void checkBinOp(Exp left, Exp right, Type type) {
		type.checkEqual(left.accept(this));
		type.checkEqual(right.accept(this));
	}

	// static semantics for programs; no value returned by the visitor

	@Override
	public Type visitMyLangProg(StmtSeq stmtSeq) {
		try {
			stmtSeq.accept(this);
		} catch (EnvironmentException e) { // undeclared variable
			throw new TypecheckerException(e);
		}
		return null;
	}

	// static semantics for statements; no value returned by the visitor

	// -----------------------------------
	// Updated code
	// -----------------------------------
	@Override
	public Type visitForEachStmt (Variable ident, Exp exp, Block block) {
		VECTOR.checkEqual(exp.accept(this)); //check that the expression is a vector
		env.enterScope();        //create new scope
		env.dec(ident, INT);     //declare the new ident in the new scope
		block.accept(this);//visit the nested block
		env.exitScope();         //close scope
		return null;
	}
	@Override
	public Type visitVector (Exp pos, Exp size) {
		INT.checkEqual(pos.accept(this)); //the position must be an int
		INT.checkEqual(size.accept(this));//the size must be an int
		return VECTOR;
	}
	// -----------------------------------
	// Updated code
	// -----------------------------------

	@Override
	public Type visitAssignStmt(Variable var, Exp exp) {
		var found = env.lookup(var);
		found.checkEqual(exp.accept(this));
		return null;
	}

	@Override
	public Type visitPrintStmt(Exp exp) {
		exp.accept(this);
		return null;
	}

	@Override
	public Type visitVarStmt(Variable var, Exp exp) {
		env.dec(var, exp.accept(this));
		return null;
	}

	@Override
	public Type visitIfStmt(Exp exp, Block thenBlock, Block elseBlock) {
		BOOL.checkEqual(exp.accept(this));
		thenBlock.accept(this);
		if (elseBlock != null)
			elseBlock.accept(this);
		return null;
	}

	@Override
	public Type visitBlock(StmtSeq stmtSeq) {
		env.enterScope();
		stmtSeq.accept(this);
		env.exitScope();
		return null;
	}

	// static semantics for sequences of statements
	// no value returned by the visitor

	@Override
	public Type visitEmptyStmtSeq() {
		return null;
	}

	@Override
	public Type visitNonEmptyStmtSeq(Stmt first, StmtSeq rest) {
		first.accept(this);
		rest.accept(this);
		return null;
	}

	// static semantics of expressions; a type is returned by the visitor

	// -----------------------------------
	// Updated code
	// -----------------------------------
	@Override
	public AtomicType visitAdd(Exp left, Exp right) {
		var l = left.accept(this);
		var r = right.accept(this);
		//if l is neither a int or a vect, raise exception
		if (!INT.equals(l) && !VECTOR.equals(l)) throw new TypecheckerException(l,INT,VECTOR);
		//if l and r have different types, throw exception
		if (!l.equals(r)) throw new TypecheckerException(r,l);
		//automatically cat the result to int or vector
		return (AtomicType) l;
	}

	@Override
	public AtomicType visitMul(Exp left, Exp right) {
		var l = left.accept(this);
		var r = right.accept(this);
		//if l is neither a int or a vect, raise exception
		if (!INT.equals(l) && !VECTOR.equals(l)) throw new TypecheckerException(l, INT, VECTOR);
		//if l is the same as r, return int (int*int->int , vector*vector->int)
		if (l.equals(r)) return INT;
		//check if are int*vector or vector* int, then raise an exception
		if (!INT.equals(r) && !VECTOR.equals(r)) throw new TypecheckerException(r, INT, VECTOR);
		return VECTOR;
	}
	// -----------------------------------
	// Updated code
	// -----------------------------------

	@Override
	public AtomicType visitIntLiteral(int value) {
		return INT;
	}

	@Override
	public AtomicType visitSign(Exp exp) {
		INT.checkEqual(exp.accept(this));
		return INT;
	}

	@Override
	public Type visitVariable(Variable var) {
		return env.lookup(var);
	}

	@Override
	public AtomicType visitNot(Exp exp) {
		BOOL.checkEqual(exp.accept(this));
		return BOOL;
	}

	@Override
	public AtomicType visitAnd(Exp left, Exp right) {
		checkBinOp(left, right, BOOL);
		return BOOL;
	}

	@Override
	public AtomicType visitBoolLiteral(boolean value) {
		return BOOL;
	}

	@Override
	public AtomicType visitEq(Exp left, Exp right) {
		left.accept(this).checkEqual(right.accept(this));
		return BOOL;
	}

	@Override
	public PairType visitPairLit(Exp left, Exp right) {
		return new PairType(left.accept(this), right.accept(this));
	}

	@Override
	public Type visitFst(Exp exp) {
		return exp.accept(this).getFstPairType();
	}

	@Override
	public Type visitSnd(Exp exp) {
		return exp.accept(this).getSndPairType();
	}
}
