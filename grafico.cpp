#include "grafico.h"
#include <QPainter>
#include <QPen>
#include <QMouseEvent>

Grafico::Grafico(QWidget *parent) : QLabel(parent) {
    largura = 0; altura = 0;
    minX = 0.0; maxX = 0.0; minY = 0.0; maxY = 0.0;
    nTiqueX = 0; nTiqueY = 0;
}

bool Grafico::empty() const { return eval.empty(); }
int Grafico::size() const { return eval.size(); }
Evaluator Grafico::getEval(int i) const { return eval.at(i); }
QColor Grafico::getCor(int i) const { return cor.at(i); }

void Grafico::pushFuncao(QString funcao, QColor cor_func) {
    Evaluator new_eval;
    new_eval.set(funcao.toStdString());
    eval.push_back(new_eval);
    cor.push_back(cor_func);
}

void Grafico::clearFuncoes() {
    eval.clear();
    cor.clear();
}

void Grafico::setLimites(double minX, double maxX, double minY, double maxY, int nTiqueX, int nTiqueY) {
    this->minX = minX; this->maxX = maxX;
    this->minY = minY; this->maxY = maxY;
    this->nTiqueX = nTiqueX; this->nTiqueY = nTiqueY;
}

double Grafico::convXtoJ(double X) const { return (largura - 1.0) * (X - minX) / (maxX - minX); }
double Grafico::convYtoI(double Y) const { return (altura - 1.0) * (maxY - Y) / (maxY - minY); }
double Grafico::convJtoX(double J) const { return minX + (maxX - minX) * J / (largura - 1.0); }
double Grafico::convItoY(double I) const { return maxY - (maxY - minY) * I / (altura - 1.0); }

void Grafico::desenharGrafico() {
    largura = width(); // Usa a largura do próprio QLabel
    altura = height(); // Usa a altura do próprio QLabel
    QPixmap img(largura, altura);
    img.fill(Qt::white);

    QPainter painter(&img);
    QPen pen;

    // Desenhando os eixos X e Y
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawLine(0, convYtoI(0), largura, convYtoI(0));
    painter.drawLine(convXtoJ(0), 0, convXtoJ(0), altura);

    // Desenhando as funções
    pen.setWidth(1);
    for (size_t k = 0; k < eval.size(); ++k) {
        pen.setColor(cor.at(k));
        painter.setPen(pen);

        double X = convJtoX(0);
        double Y = eval.at(k)(X);
        double Iant = convYtoI(Y);

        for (int J = 1; J < largura; ++J) {
            X = convJtoX(J);
            Y = eval.at(k)(X);
            double I = convYtoI(Y);
            
            painter.drawLine(J - 1, Iant, J, I);
            Iant = I;
        }
    }

    setPixmap(img); // Aplica a imagem neste próprio widget
}

void Grafico::resizeEvent(QResizeEvent *event) {
    QLabel::resizeEvent(event); // Chama o redimensionamento original do QLabel
    
    // Se o tamanho novo for diferente do antigo, redesenha o gráfico
    if (event->oldSize() != event->size()) {
        desenharGrafico(); 
    }
}

void Grafico::mouseReleaseEvent(QMouseEvent *event) {
    QLabel::mouseReleaseEvent(event); // Chama o evento original do QLabel
    double X = convJtoX(event->pos().x());
    double Y = convItoY(event->pos().y());
    emit signGraficoClicked(X, Y);
}
