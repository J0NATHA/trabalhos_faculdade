Algoritmo "Jogo da velha"
// Disciplina   : [Construção de algoritmos]
// Professor   : Eugênio da Silva
// Autor(a)    : Jonatha Salles Menezes
// Data atual  : 22/07/2022
Var

  mat : vetor[1..3,1..3] de caractere
  i,j,k,modo,preenchidos : inteiro
  vezDo, estado : caractere
  renderBoard,trocaVez,checaVitoria: logico


Inicio

 estado <- "MENU"
 enquanto nao(estado = "SAIR") faca

  se (estado = "MENU") entao
   repita
    limpatela
    escreval("              Criado por Jonatha Salles Menezes")
    escreval("               *Bem-Vindo(a) ao jogo da velha*")
    escreval("                  *Escolha um modo de jogo!*")
    escreval("                 ===========================")
    escreval("                   Dois Jogadores (JvJ)(1)")
    escreval("                    Um jogador (JvCPU) (2)")
    escreval("                                  Sair (3)")
    escreval("                 ===========================")
    escreva("                                        ")
    leia(modo)
   ate((modo = 1) ou (modo = 2) ou (modo =3))
   se (modo = 1) entao
     estado <- "REINICIO"
   fimse
   se (modo = 2) entao
     estado <- "REINICIO"
   fimse
   se (modo = 3) entao
     estado <- "SAIR"
   fimse
  fimse

  se (estado = "REINICIO") entao
   trocaVez <- falso
   k <- 0
   para i de 1 ate 3 faca
    para j de 1 ate 3 faca
     k <- k + 1
     mat[i,j] <- "_"
    fimpara
   fimpara
   renderBoard <- verdadeiro
   estado <- "ESCOLHENDO"
   vezDo <- "JOGADOR1"
  fimse
 
  se (renderBoard) entao
   //Renderizando o tabuleiro
   limpatela
   escreval
   escreval
   escreval
   escreval("                              _ _ _")
   escreval("                             |",mat[1,1],"|",mat[1,2],"|",mat[1,3],"|")
   escreval("                             |",mat[2,1],"|",mat[2,2],"|",mat[2,3],"|")
   escreval("                             |",mat[3,1],"|",mat[3,2],"|",mat[3,3],"|")
   renderBoard <- falso
   checaVitoria <- verdadeiro
  fimse
  
  se (checaVitoria) entao
   checaVitoria <- falso
    se((mat[1,1]<>"_")e(mat[1,1]=mat[2,2])e(mat[3,3]=mat[1,1]))entao
      estado <- "FIMDJOGO"
    fimse
    se((mat[3,1]<>"_")e(mat[3,1]=mat[2,2])e(mat[3,1]=mat[1,3]))entao
      estado <- "FIMDJOGO"
    fimse
    para i de 1 ate 3 faca
     j<-1
     se((mat[i,j]<>"_")e(mat[i,j]=mat[i,j+1])e(mat[i,j]=mat[i,j+2]))entao
      estado <- "FIMDJOGO"
     fimse
     se((mat[j,i]<>"_")e(mat[j,i]=mat[j+1,i])e(mat[j,i]=mat[j+2,i]))entao
      estado <- "FIMDJOGO"
     fimse
    fimpara
    preenchidos <- 0
    para i de 1 ate 3 faca
     para j de 1 ate 3 faca
      se(mat[i,j]<>"_") entao
       preenchidos <- preenchidos + 1
      fimse
      se(preenchidos = 9)entao
       estado <- "EMPATE"
      fimse
     fimpara
    fimpara
  fimse
  
  se(estado="ESCOLHENDO")entao
   se(trocaVez)entao
    trocaVez <- falso
    se (modo = 1) entao
     se (vezDo = "JOGADOR1") entao
      vezDo <- "JOGADOR2"
     senao
      vezDo <- "JOGADOR1"
     fimse
    senao
     se(vezDo = "ROBO")entao
      vezDo <- "JOGADOR1"
     senao
      vezDo <- "ROBO"
     fimse
    fimse
   fimse
  fimse
  
  se(estado = "ESCOLHENDO")entao
   escreval("                         VEZ DO:",vezDo)
   se(vezDo = "JOGADOR1")entao
    repita
     escreva("                        Escolha a linha: ")
     leia(i)
    ate (i <= 3)
    repita
     escreva("                        Escolha a coluna: ")
     leia(j)
    ate (j <= 3)
     se(mat[i,j] = "_") entao
      mat[i,j] <- "X"
      renderBoard <- verdadeiro
      trocaVez<- verdadeiro
     senao
       limpatela
       escreval
       escreval
       escreval
       escreval("                        Posição inválida")
       timer(1000)
       limpatela
       timer (0)
       renderBoard <- verdadeiro
     fimse
    fimse
    
   se(vezDo = "JOGADOR2")entao
    repita
     escreva("                        Escolha a linha: ")
     leia(i)
    ate (i <= 3)
    repita
     escreva("                        Escolha a coluna: ")
     leia(j)
    ate (j <= 3)
     se(mat[i,j] = "_") entao
      mat[i,j] <- "O"
      trocaVez <- verdadeiro
      renderBoard <- verdadeiro
     senao
       limpatela
       escreval
       escreval
       escreval
       escreval("                        Posição inválida")
       timer(1000)
       limpatela
       timer (0)
       renderBoard <- verdadeiro
     fimse
    fimse

    se(vezDo = "ROBO") entao
     escreva("                        Escolha a linha: ")
     timer (200)
     aleatorio 1,3
      leia(i)
     timer (0)
     aleatorio off
      escreva("                        Escolha a coluna: ")
     timer (200)
     aleatorio 1,3
      leia(j)
     timer (0)
     aleatorio off
     se (mat[i,j]="_") entao
      timer (100)
      mat[i,j] <- "O"
      trocaVez <- verdadeiro
      renderBoard <- verdadeiro
      timer(0)

     senao
       limpatela
       escreval
       escreval
       escreval
       escreval("                        Posição inválida")
       timer(1000)
       limpatela
       timer (0)
       renderBoard <- verdadeiro
     fimse
    fimse
   fimse

  se(estado = "EMPATE") entao
   escreval("                           Fim de jogo")
   timer(500)
   escreval("                            EMPATE!!!")
   timer(0)
   timer(500)
   estado <- "MENU"
   timer(0)
  fimse


  se(estado = "FIMDJOGO") entao
   escreval("                           Fim de jogo")
   timer(500)
   escreval("                         O vencedor foi...")
   timer(0)
   timer(500)
   escreva ("                            ",vezDo,"!!!")
   timer(0)
   timer(1000)
   estado <- "MENU"
   timer(0)
  fimse
  
 fimenquanto

Fimalgoritmo