import java.lang.Exception;
import java.io.Serializable;

/**
 * 
 * @author Grupo 30
 */
public class NinguemPublicou extends Exception implements Serializable
{
    public NinguemPublicou(){
        super();
    } 
    public NinguemPublicou(String m){
        super(m);
    }
}
