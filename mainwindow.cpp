#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Inicializar los puntos del Conecta 4
    Puntos[0][0]=ui->p00;
    Puntos[0][1]=ui->p01;
    Puntos[0][2]=ui->p02;
    Puntos[0][3]=ui->p03;
    Puntos[0][4]=ui->p04;
    Puntos[0][5]=ui->p05;
    Puntos[0][6]=ui->p06;
    Puntos[1][0]=ui->p10;
    Puntos[1][1]=ui->p11;
    Puntos[1][2]=ui->p12;
    Puntos[1][3]=ui->p13;
    Puntos[1][4]=ui->p14;
    Puntos[1][5]=ui->p15;
    Puntos[1][6]=ui->p16;
    Puntos[2][0]=ui->p20;
    Puntos[2][1]=ui->p21;
    Puntos[2][2]=ui->p22;
    Puntos[2][3]=ui->p23;
    Puntos[2][4]=ui->p24;
    Puntos[2][5]=ui->p25;
    Puntos[2][6]=ui->p26;
    Puntos[3][0]=ui->p30;
    Puntos[3][1]=ui->p31;
    Puntos[3][2]=ui->p32;
    Puntos[3][3]=ui->p33;
    Puntos[3][4]=ui->p34;
    Puntos[3][5]=ui->p35;
    Puntos[3][6]=ui->p36;
    Puntos[4][0]=ui->p40;
    Puntos[4][1]=ui->p41;
    Puntos[4][2]=ui->p42;
    Puntos[4][3]=ui->p43;
    Puntos[4][4]=ui->p44;
    Puntos[4][5]=ui->p45;
    Puntos[4][6]=ui->p46;
    Puntos[5][0]=ui->p50;
    Puntos[5][1]=ui->p51;
    Puntos[5][2]=ui->p52;
    Puntos[5][3]=ui->p53;
    Puntos[5][4]=ui->p54;
    Puntos[5][5]=ui->p55;
    Puntos[5][6]=ui->p56;

    //Inicializamos todas las variables de control de Juego
    turnoRojas=true;
    gananRojas=false;
    gananAmarillas=false;
    NoPartidas=0;
    Empates=0;
    GanadasRojas=0;
    GanadasAmarillas=0;
    PerdidasRojas=0;
    PerdidasAmarillas=0;

    //Inicializamos cada columna para tener un control del Llenado
    for(int i=0;i<7;i++)
    {
        Llena[i]=0;
    }
    for(int j=0;j<7;j++)
    {
        for(int k=0;k<6;k++)
        {
            MatrizMovimientos[k][j]=0;
        }
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //Metodo para Reiniciar todo el juego
    for(int i=0;i<7;i++)
    {
        Llena[i]=0;
    }
    for(int j=0;j<7;j++)
    {
        for(int k=0;k<6;k++)
        {
            Puntos[k][j]->setIcon(QIcon(":/Imagenes/Imagenes/circlegreyproof.png"));
            MatrizMovimientos[k][j]=0;
        }
    }
    gananRojas=false;
    gananAmarillas=false;
    turnoRojas=true;
}

void MainWindow::InsertarFicha(int columna)
{

    if(Llena[columna]<6) //Revisamos que una columna no este Llena
    {
        renglon=5-Llena[columna];//Posicion de la fila/renglon en que se encuentra la ficha
        Llena[columna]=Llena[columna]+1;//Control del vector para saber si esta llena cada que se introduce una ficha aumenta
        if(turnoRojas==true)
        {
            Puntos[renglon][columna]->setIcon(QIcon(":/Imagenes/Imagenes/circle_red.png")); //Introduce ficha Roja
            MatrizMovimientos[renglon][columna]=1;//Matriz que dibuja los movimientos
            turnoRojas=false;
            RevisarGanador(renglon,columna,1); //Revisa cada turno por si hay un ganador
        }
        else
        {
            Puntos[renglon][columna]->setIcon(QIcon(":/Imagenes/Imagenes/circle_yellow.png"));//Introduce ficha Amarilla
            MatrizMovimientos[renglon][columna]=2;//Matriz que dibuja los movimientos
            turnoRojas=true;
            RevisarGanador(renglon,columna,2);//Revisa cada turno por si hay un ganador
        }

    }
    else{
            QMessageBox::information(this,"Conecta 4","Esa Columna ya esta llena!");
    }

}

void MainWindow::RevisarGanador(int fila, int columna, int tiro)
{
    //Revisas en todas las posibles formas de ganar
    RevisarGanadorVertical(fila,columna,tiro);//Vertical
    RevisarGanadorHorizontal(fila,columna,tiro);//Horizontal
    RevisarGanadorDiagonal(fila,columna,tiro);//Diagonal
    RevisarGanadorDiagonal2(fila,columna,tiro);//Diagonal Invertida

    //Si se activa alguna de las banderas , Anuncia el Ganador y Limpia el tablero
    if(gananRojas==true ){
            QMessageBox::information(this,"Fin de juego","Ganan las Rojas","OK");
            on_pushButton_clicked();
            NoPartidas++;
            GanadasRojas++;
            PerdidasAmarillas++;
            EscribirPuntaje();


        }
    if(gananAmarillas==true){
            QMessageBox::information(this,"Fin de juego","Ganan las Amarillas","OK");
            on_pushButton_clicked();
            NoPartidas++;
            GanadasAmarillas++;
            PerdidasRojas++;
            EscribirPuntaje();

        }
}

void MainWindow::EscribirPuntaje()
{
    ui->linePartidas1->setText(QString::number(NoPartidas));
    ui->linePartidas2->setText(QString::number(NoPartidas));
    ui->lineGanadas1->setText(QString::number(GanadasRojas));
    ui->linePerdidas1->setText(QString::number(PerdidasRojas));
    ui->lineEmpates1->setText(QString::number(Empates));
    ui->lineGanadas2->setText(QString::number(GanadasAmarillas));
    ui->linePerdidas2->setText(QString::number(PerdidasAmarillas));
    ui->lineEmpates2->setText(QString::number(Empates));
}

void MainWindow::Empate()
{
    bool empateJuego; //bandera que controla Empates
    for(int i=0;i<7;i++)
    {
        for(int j=0;i<6;i++)
        {
            if(MatrizMovimientos[j][i]==0) //Si aun existe un 0 en la matriz de dibujo significa que aun hay donde meter fichas
            {   empateJuego=false;
                break;
            }
            else{
                empateJuego=true; //Si no encuentra hace la bandera true pero continua en el ciclo hasta que encuentre un 0
                continue;
            }
        }
    }

    if(empateJuego) //Si nunca encontro un 0 y quedo verdadera significa que hay empate
    {
        QMessageBox::information(this,"Fin de juego","Fue un Empate","OK");
        on_pushButton_clicked();//Reiniciamos el juego
        NoPartidas++; //Aumenta No de partidas Jugadas
        Empates++; //Aumenta Empates
        EscribirPuntaje();
    }

}

void MainWindow::RevisarGanadorVertical(int fila,int columna,int tiro)
{
    if(MatrizMovimientos[fila-1][columna]==tiro || MatrizMovimientos[fila+1][columna]==tiro){
            if(MatrizMovimientos[fila-2][columna]==tiro || MatrizMovimientos[fila+2][columna]==tiro){
                if(MatrizMovimientos[fila-3][columna]==tiro || MatrizMovimientos[fila+3][columna]==tiro){
                    if(tiro==1){
                        gananRojas=true;
                    }else{
                        gananAmarillas=true;
                    }
                }
            }
        }

}

void MainWindow::RevisarGanadorHorizontal(int fila,int columna,int tiro)
{
    if(MatrizMovimientos[fila][columna-1]==tiro || MatrizMovimientos[fila][columna+1]==tiro){
            if(MatrizMovimientos[fila][columna-2]==tiro || MatrizMovimientos[fila][columna+2]==tiro){
                if(MatrizMovimientos[fila][columna-3]==tiro || MatrizMovimientos[fila][columna+3]==tiro){
                    if(tiro==1){
                        gananRojas=true;
                    }else{
                        gananAmarillas=true;
                    }
                }
            }
        }
}

void MainWindow::RevisarGanadorDiagonal(int fila,int columna,int tiro){

    if(MatrizMovimientos[fila-1][columna-1]==tiro || MatrizMovimientos[fila-1][columna+1]==tiro){
        if(MatrizMovimientos[fila-2][columna-2]==tiro || MatrizMovimientos[fila-2][columna+2]==tiro){
            if(MatrizMovimientos[fila-3][columna-3]==tiro || MatrizMovimientos[fila-3][columna+3]==tiro){
                if(tiro==1){
                    gananRojas=true;
                }else{
                    gananAmarillas=true;
                }
            }
        }
    }
}

void MainWindow::RevisarGanadorDiagonal2(int fila, int columna, int tiro)
{
    if(MatrizMovimientos[fila+1][columna-1]==tiro || MatrizMovimientos[fila+1][columna+1]==tiro){
        if(MatrizMovimientos[fila+2][columna-2]==tiro || MatrizMovimientos[fila+2][columna+2]==tiro){
            if(MatrizMovimientos[fila+3][columna-3]==tiro || MatrizMovimientos[fila+3][columna+3]==tiro){
                if(tiro==1){
                    gananRojas=true;
                }else{
                    gananAmarillas=true;
                }
            }
        }
    }

}

void MainWindow::on_InsertaCol1_clicked()
{
    InsertarFicha(0);
}

void MainWindow::on_InsertaCol2_clicked()
{
    InsertarFicha(1);
}

void MainWindow::on_InsertaCol3_clicked()
{
    InsertarFicha(2);
}

void MainWindow::on_InsertaCol4_clicked()
{
    InsertarFicha(3);
}

void MainWindow::on_InsertaCol5_clicked()
{
    InsertarFicha(4);
}

void MainWindow::on_InsertaCol6_clicked()
{
    InsertarFicha(5);
}

void MainWindow::on_InsertaCol7_clicked()
{
    InsertarFicha(6);
}



