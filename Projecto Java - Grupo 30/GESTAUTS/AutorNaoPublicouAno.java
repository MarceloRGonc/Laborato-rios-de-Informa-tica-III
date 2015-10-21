import java.lang.Exception;
import java.io.Serializable;
/**
 * 
 * @author Grupo 30
 */
public class AutorNaoPublicouAno extends Exception implements Serializable
{
    public AutorNaoPublicouAno(){
        super();
    }
    public AutorNaoPublicouAno(String m){
        super(m);
    }
}
