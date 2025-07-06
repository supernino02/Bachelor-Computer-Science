package visitors.execution;

import java.io.PrintWriter;

import environments.EnvironmentException;
import environments.GenEnvironment;
import parser.ast.Block;
import parser.ast.Exp;
import parser.ast.Stmt;
import parser.ast.StmtSeq;
import parser.ast.Variable;
import visitors.Visitor;

import static java.util.Objects.requireNonNull;

public class Execute implements Visitor<Value> {

	private final GenEnvironment<Value> env = new GenEnvironment<>();
	private final PrintWriter printWriter; // output stream used to print values

	public Execute() {
		printWriter = new PrintWriter(System.out, true);
	}

	public Execute(PrintWriter printWriter) {
		this.printWriter = requireNonNull(printWriter);
	}

	// dynamic semantics for programs; no value returned by the visitor

	@Override
	public Value visitMyLangProg(StmtSeq stmtSeq) {
		try {
			stmtSeq.accept(this);
			// possible runtime errors
			// EnvironmentException: undefined variable
		} catch (EnvironmentException e) {
			throw new InterpreterException(e);
		}
		return null;
	}

	// -----------------------------------
	// Updated code
	// -----------------------------------
	@Override
	public Value visitVector (Exp pos, Exp size) {
		return new VectValue(                       //create a new VectValue
				(IntValue) pos.accept(this) , //visit pos, cast it from Value to IntValue
				(IntValue) size.accept(this)  //visit size, cast it from Value to IntValue
		);
	}

	@Override
	public Value visitForEachStmt (Variable ident, Exp vector, Block block) {
		Value value = vector.accept (this);                   //calculating the Value of the expression
		if (!(value instanceof VectValue vectValue))                //check if is really a VectorValue
			throw new InterpreterException(
					"find "       + value.getClass().getSimpleName() +
					", expected " + VectValue.class.getSimpleName()
			);
		env.enterScope();                                           //allocate a new scope
		env.dec(ident, new IntValue(-1));                           //declare a new identifier initialized by a "placeholder
		int[] values = vectValue.toVector();                        //reading VectorValue as a vector of int, for practical use
		for (int val : values) {                                    //iterate over the values
			env.update(ident, new IntValue(val));                   //update the identifier (it will iterate over the array)
			block.accept(this);                               //visit the block of instruction
		}
		env.exitScope();                                             //deallocate the scope
		return null;
	}
	// -----------------------------------
	// Updated code
	// -----------------------------------

	// dynamic semantics for statements; no value returned by the visitor

	@Override
	public Value visitAssignStmt(Variable var, Exp exp) {
		env.update(var, exp.accept(this));
		return null;
	}

	@Override
	public Value visitPrintStmt(Exp exp) {
		printWriter.println(exp.accept(this));
		return null;
	}

	@Override
	public Value visitVarStmt(Variable var, Exp exp) {
		env.dec(var, exp.accept(this));
		return null;
	}

	@Override
	public Value visitIfStmt(Exp exp, Block thenBlock, Block elseBlock) {
		if (exp.accept(this).toBool())
			thenBlock.accept(this);
		else if (elseBlock != null)
			elseBlock.accept(this);
		return null;
	}

	@Override
	public Value visitBlock(StmtSeq stmtSeq) {
		env.enterScope();
		stmtSeq.accept(this);
		env.exitScope();
		return null;
	}

	// dynamic semantics for sequences of statements
	// no value returned by the visitor

	@Override
	public Value visitEmptyStmtSeq() {
		return null;
	}

	@Override
	public Value visitNonEmptyStmtSeq(Stmt first, StmtSeq rest) {
		first.accept(this);
		rest.accept(this);
		return null;
	}

	// dynamic semantics of expressions; a value is returned by the visitor
	// -----------------------------------
	// Updated code
	// -----------------------------------
	@Override
	public Value visitAdd(Exp left, Exp right) {
		var l = left.accept(this);                                     //evaluate the left expression
		var r = right.accept(this);                                    //evaluate the right expression
		if (l instanceof IntValue lInt && r instanceof IntValue rInt)         //if types INT,INT
			return new IntValue(lInt.toInt() + rInt.toInt());                 //add them
		if (l instanceof VectValue lVect && r instanceof VectValue rVect) {   //if types VECTOR,VECTOR
			if (lVect.getSize() != rVect.getSize())                           //if different size, exception
				throw new InterpreterException(lVect,rVect);
			int size = lVect.getSize();                                       //get the size of the VectValue in output
			int[] res = new int[size];                                        //initialize it
			for (int i = 0; i < size; i++) res[i] = lVect.at(i) + rVect.at(i);//evaluate every values of the array
			return new VectValue(res);                                        //return the vector
		}
		throw new InterpreterException(                                       //if unexpected types, exception
						"find " + l.getClass().getSimpleName() +
						" and " + r.getClass().getSimpleName() +
						", expected the same value: " + IntValue.class.getSimpleName() +
						" or "                 + VectValue.class.getSimpleName()
		);
	}

	@Override
	public Value visitMul(Exp left, Exp right) {
		var l = left.accept(this);                                       //evaluate the left expression
		var r = right.accept(this);                                      //evaluate the right expression
		if (l instanceof IntValue lInt && r instanceof IntValue rInt)           //if types INT,INT
			return new IntValue(lInt.toInt() * rInt.toInt());                   //multiply together
		if (l instanceof VectValue lVect && r instanceof VectValue rVect) {     //if types VECTOR,VECTOR
			if (lVect.getSize() != rVect.getSize())                             //if different sizes
				throw new InterpreterException(lVect,rVect);                    //exception
			int size = lVect.getSize();                                         //evaluate the return value
			int tot = 0;
			for (int i = 0; i < size; i++) tot += lVect.at(i) * rVect.at(i);
			return new IntValue(tot);                                           //return a IntValue
		}
		int scalar;                                                             //initialize a scalar
		VectValue vector;                                                       //initialize a vector
		if (l instanceof IntValue lInt && r instanceof VectValue rVect) {       //if types are INT,VECTOR is ok
			scalar = lInt.toInt();
			vector = rVect;
		} else if (l instanceof VectValue lVect && r instanceof IntValue rInt) {//if types are VECTOR,INT is ok
			vector = lVect;
			scalar = rInt.toInt();
		} else
			throw new InterpreterException(                                     //throw exception, invalid types
					"find " + l.getClass().getSimpleName() +
					" and " + r.getClass().getSimpleName() +
					", expected for both " + IntValue.class.getSimpleName() +
					" or "                 + VectValue.class.getSimpleName()
			);
		int size = vector.getSize();                                            //get the size of the returned values
		int[] res = new int[size];                                              //initialize it
		for (int i = 0; i < size; i++) res[i] = vector.at(i) * scalar;          //multiply the values with the scalar
		return new VectValue(res);                                              //return the values as a VectValue
	}
	// -----------------------------------
	// Updated code
	// -----------------------------------

	@Override
	public IntValue visitIntLiteral(int value) {
		return new IntValue(value);
	}

	@Override
	public IntValue visitSign(Exp exp) {
		return new IntValue(-exp.accept(this).toInt());
	}

	@Override
	public Value visitVariable(Variable var) {
		return env.lookup(var);
	}

	@Override
	public BoolValue visitNot(Exp exp) {
		return new BoolValue(!exp.accept(this).toBool());
	}

	@Override
	public BoolValue visitAnd(Exp left, Exp right) {
		return new BoolValue(left.accept(this).toBool() && right.accept(this).toBool());
	}

	@Override
	public BoolValue visitBoolLiteral(boolean value) {
		return new BoolValue(value);
	}

	@Override
	public BoolValue visitEq(Exp left, Exp right) {
		return new BoolValue(left.accept(this).equals(right.accept(this)));
	}

	@Override
	public PairValue visitPairLit(Exp left, Exp right) {
		return new PairValue(left.accept(this), right.accept(this));
	}

	@Override
	public Value visitFst(Exp exp) {
		return exp.accept(this).toPair().getFstVal();
	}

	@Override
	public Value visitSnd(Exp exp) {
		return exp.accept(this).toPair().getSndVal();
	}

}

