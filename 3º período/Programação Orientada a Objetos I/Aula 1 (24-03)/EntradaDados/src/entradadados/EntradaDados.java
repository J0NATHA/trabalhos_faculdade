/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entradadados;

import java.util.Scanner;
public class EntradaDados {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String matricula, nome;
        double nota1, nota2;
        int idade;
        System.out.println("Entre com a matrícula -> ");
        matricula = sc.nextLine();
        System.out.println("Entre com o Nome -> ");
        nome = sc.nextLine();
        System.out.println("Entre com a Nota A1 -> ");
        nota1 = Double.parseDouble(sc.nextLine());
        System.out.println("Entre com a Nota A2 -> ");
        nota2 = Double.parseDouble(sc.nextLine());
        System.out.println("Entre com a idade");
        idade = Integer.parseInt(sc.nextLine());
        
        System.out.println("Matrícula: " + matricula);
        System.out.println("Nome: " + nome + " Nota 1: " + nota1);
        System.out.println("Nota 2: " + nota2 + " Idade: " + idade);
        System.out.println("Média: " + (nota1 + nota2) / 2);
    }
    
}
