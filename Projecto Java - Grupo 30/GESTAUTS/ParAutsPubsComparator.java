import java.io.Serializable;
import java.util.Comparator;

/**
 * 
 * @author Grupo 30
 */
public class ParAutsPubsComparator implements Comparator<ParAutsPubs>, Serializable {
    public int compare(ParAutsPubs n, ParAutsPubs o){
            if(n.getTotal() > o.getTotal()) return -1;
            else if(o.equals(n)) return 0;
            else return 1;
    }
}
