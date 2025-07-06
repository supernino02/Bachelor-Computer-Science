package visitors.execution;

import static java.util.Objects.requireNonNull;
import java.util.Arrays;

public class VectValue implements Value {
	private final int[] values;

	private static void checkValidity (int pos, int size) {
		if(size < 0) throw new InterpreterException("Negative Array Size Exception: "+size);
		else if(pos < 0 || pos >= size) throw new InterpreterException("Array Index Out Of Bound: Index "+ pos + " out of bounds for lenght " + size);
	}

	public VectValue(IntValue pos ,IntValue size) {
		int p = requireNonNull(pos).toInt();
		int s = requireNonNull(size).toInt();
		checkValidity(p,s);
		values = new int[s]; //create an array initialized with all 0
		values[p] = 1;
	}

	public VectValue(int[] values) {
		this.values = Arrays.copyOf(values,values.length);
	}

	public int getSize () {
		return values.length;
	}

	public int at (int i) {
		checkValidity(i,values.length);
		return values[i];
	}

	@Override
	public int[] toVector() {
		return values;
	}

	@Override
	public String toString() {
        StringBuilder result = new StringBuilder("["); //open the [
        for (int i = 0; i < values.length; i++) {      //iterate over the values
            result.append(values[i]);                  //add it to the result
            if (i < values.length - 1)                 //add a ; only if is not the last element
                result.append(";");
        }
         return result.append("]").toString();         //add the closing ] and cast it to a string
	}

	@Override
	public int hashCode() {
		return Arrays.hashCode(values);                   //evaluate the hash code using all the values in the array
	}

	@Override
	public final boolean equals(Object obj) {
		if (this == obj)                                  //literally the same address
			return true;
		if ( !(obj instanceof VectValue other)            //obj is not a vectValue
				|| this.getSize() != other.getSize())     //they have different size
			return false;
		return Arrays.equals(this.values, other.values); //check if they carry the same values
	}	
}