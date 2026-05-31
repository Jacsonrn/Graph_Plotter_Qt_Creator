#ifndef GRAFICO_H
#define GRAFICO_H

#include <QLabel>
#include <vector>
#include <QColor>
#include "evaluator.h"
#include <QResizeEvent>

class Grafico : public QLabel
{
    Q_OBJECT
public:
    explicit Grafico(QWidget *parent = nullptr);
    bool empty() const;
    int size() const;
    Evaluator getEval(int i) const;
    QColor getCor(int i) const;
    void pushFuncao(QString funcao, QColor cor);
    void clearFuncoes();
    void setLimites(double minX, double maxX, double minY, double maxY, int nTiqueX, int nTiqueY);
    void desenharGrafico();

signals:
    void signGraficoClicked(double X, double Y);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    std::vector<Evaluator> eval;
    std::vector<QColor> cor;
    int largura, altura;
    double minX, maxX, minY, maxY;
    int nTiqueX, nTiqueY;

    double convXtoJ(double X) const;
    double convYtoI(double Y) const;
    double convJtoX(double J) const;
    double convItoY(double Y) const;
};

#endif // GRAFICO_H
