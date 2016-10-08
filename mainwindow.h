#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QIcon>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void InsertarFicha(int columna);
    void RevisarGanador(int fila,int columna,int tiro);
    void RevisarGanadorHorizontal(int fila,int columna,int tiro);
    void RevisarGanadorVertical(int fila, int columna, int tiro);
    void RevisarGanadorDiagonal(int fila, int columna, int tiro);
    void RevisarGanadorDiagonal2(int fila, int columna, int tiro);
    void EscribirPuntaje();
    void Empate();

private slots:
    void on_InsertaCol1_clicked();

    void on_InsertaCol2_clicked();

    void on_InsertaCol3_clicked();

    void on_InsertaCol4_clicked();

    void on_InsertaCol5_clicked();

    void on_InsertaCol6_clicked();

    void on_InsertaCol7_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *Puntos[6][7];
    int Llena[7];
    int MatrizMovimientos[6][7];
    bool turnoRojas;
    bool gananRojas;
    bool gananAmarillas;
    int Empates;
    int NoPartidas;
    int GanadasRojas,GanadasAmarillas;
    int PerdidasRojas,PerdidasAmarillas;
    int renglon;
};

#endif // MAINWINDOW_H
