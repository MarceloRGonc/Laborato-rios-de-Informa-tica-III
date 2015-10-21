import java.lang.Exception;
import java.io.Serializable;
/**
 * 
 * @author Grupo 30
 */
public class AutorNaoExiste extends Exception implements Serializable
{
    public AutorNaoExiste(){
        super();
    } 
    public AutorNaoExiste(String m){
        super(m);
    }
}
