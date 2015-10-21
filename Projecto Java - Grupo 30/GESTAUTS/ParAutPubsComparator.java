import java.io.Serializable;
import java.util.Comparator;

/**
 * 
 * @author Grupo 30
 */
public class ParAutPubsComparator implements Comparator<ParAutPubs>, Serializable {
    public int compare(ParAutPubs n, ParAutPubs o){
            if(n.getTotal() < o.getTotal()) return 1;
            else if(o.getTotal() < n.getTotal()) return -1;
            return n.getNome().compareTo(o.getNome());
    }
}
