#ifndef MAINPLOTADOR_H
#define MAINPLOTADOR_H

#include <QMainWindow>
#include "lehfuncao.h"
#include "evaluator.h"
#include <vector>
#include <QResizeEvent>
#include "grafico.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainPlotador;
}
QT_END_NAMESPACE

class MainPlotador : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPlotador(QWidget *parent = nullptr);
    ~MainPlotador() override;

private slots:
    void slotIncluirFuncao(QString Funcao, QColor Cor);
    void slotGraficoClicked(double X, double Y);
    void on_actionFun_o_triggered();
    void on_actionApagar_triggered();
    void on_actionSair_triggered();
    void on_spinMinX_valueChanged(int arg1);
    void on_spinMaxX_valueChanged(int arg1);
    void on_spinExpX_valueChanged(int arg1);
    void on_spinMinY_valueChanged(int arg1);
    void on_spinMaxY_valueChanged(int arg1);
    void on_spinExpY_valueChanged(int arg1);
    void on_pushApagar_clicked();

private:
    Ui::MainPlotador *ui;
    LehFuncao *lehFuncao;
    Grafico *grafico;
    void exibirFuncoes();
    void atualizaLimitesEDesenha();
};
#endif // MAINPLOTADOR_H
