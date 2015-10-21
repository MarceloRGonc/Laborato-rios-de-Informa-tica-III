import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * 
 * @author Grupo 30 
 */
public class Menu {
    
    private List<String> opcoes;
    private int op;
    
    public Menu(String[] opcoes) {
        this.opcoes = new ArrayList<String>();
        for (String op : opcoes) //(int i=0; i<opcoes.length; i++)
            this.opcoes.add(op);
        this.op = 0;
    }

    public void executa() {
        do {
            showMenu();
            this.op = lerOpcao();
        } while (this.op == -1);
    }
    
    private void showMenu() {
        System.out.println("\nMenu");
        for (int i=0; i<this.opcoes.size(); i++) {
            System.out.print(i+1);
            System.out.print(" - ");
            System.out.println(this.opcoes.get(i));
        }
        System.out.println("0 - Sair");
    }
    
    private int lerOpcao() {
        int op; 
        
        System.out.print("Insira a sua escolha: ");
        op = Input.lerInt();
        if (op<0 || op>this.opcoes.size()) {
            System.out.println("Opção Inválida!!!");
            op = -1;
        }
        return op;
    }
    
    public int getOpcao() {
        return this.op;
    }
}
