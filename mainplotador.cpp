#include "mainplotador.h"
#include "./ui_mainplotador.h"
#include <QMessageBox>
#include <QLabel>
#include <QPixmap>
#include <QPainter>

MainPlotador::MainPlotador(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPlotador)
{
    ui->setupUi(this);

    grafico = new Grafico(this);
    grafico->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->gridLayout->addWidget(grafico, 1, 0);

    lehFuncao = new LehFuncao(this);
    connect(lehFuncao, &LehFuncao::signIncluirFuncao, this, &MainPlotador::slotIncluirFuncao);
    connect(grafico, &Grafico::signGraficoClicked, this, &MainPlotador::slotGraficoClicked);

    ui->tableFuncoes->setStyleSheet("QHeaderView::section { background-color:lightgray }");
    ui->tableFuncoes->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableFuncoes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->tableFuncoes->setHorizontalHeaderLabels(QStringList() << "COR" << "FUNCAO");

    // Configura os limites permitidos nos SpinBoxes (para aceitarem números negativos)
    ui->spinMinX->setRange(-1000, 1000);
    ui->spinMaxX->setRange(-1000, 1000);
    ui->spinMinY->setRange(-1000, 1000);
    ui->spinMaxY->setRange(-1000, 1000);
    ui->spinExpX->setRange(-5, 5);
    ui->spinExpY->setRange(-5, 5);

    // Define valores iniciais razoáveis para o gráfico (Zoom de -10 a 10)
    ui->spinMinX->setValue(-10);
    ui->spinMaxX->setValue(10);
    ui->spinMinY->setValue(-10);
    ui->spinMaxY->setValue(10);

    atualizaLimitesEDesenha();
}

MainPlotador::~MainPlotador()
{
    delete ui;
}

void MainPlotador::on_actionFun_o_triggered()
{
    lehFuncao->clear();
    lehFuncao->show();
}

void MainPlotador::on_actionApagar_triggered()
{
    on_pushApagar_clicked();
}

void MainPlotador::on_actionSair_triggered()
{
    QCoreApplication::quit();
}

void MainPlotador::on_spinMinX_valueChanged(int arg1) {
    ui->spinMaxX->setMinimum(arg1 + 1); // Garante que Max > Min
    atualizaLimitesEDesenha();
}

void MainPlotador::on_spinMaxX_valueChanged(int arg1) {
    ui->spinMinX->setMaximum(arg1 - 1); // Garante que Min < Max
    atualizaLimitesEDesenha();
}

void MainPlotador::on_spinExpX_valueChanged(int arg1) {
    atualizaLimitesEDesenha();
}

void MainPlotador::on_spinMinY_valueChanged(int arg1) {
    ui->spinMaxY->setMinimum(arg1 + 1); // Garante que Max > Min
    atualizaLimitesEDesenha();
}

void MainPlotador::on_spinMaxY_valueChanged(int arg1) {
    ui->spinMinY->setMaximum(arg1 - 1); // Garante que Min < Max
    atualizaLimitesEDesenha();
}

void MainPlotador::on_spinExpY_valueChanged(int arg1) {
    atualizaLimitesEDesenha();
}

void MainPlotador::on_pushApagar_clicked() {
    grafico->clearFuncoes();
    exibirFuncoes();
    grafico->desenharGrafico();
}

void MainPlotador::slotIncluirFuncao(QString Funcao, QColor Cor) {
    try {
        grafico->pushFuncao(Funcao, Cor);
        exibirFuncoes();
        grafico->desenharGrafico();
    } catch (std::exception &E) {
        QMessageBox::critical(this, "Função inválida", QString("Erro na função: ") + E.what());
    }
}

void MainPlotador::exibirFuncoes() {
    ui->tableFuncoes->clearContents();
    ui->tableFuncoes->setRowCount(grafico->size());

    QLabel* prov;
    QPixmap img(20, 20);

    for (int k = 0; k < grafico->size(); ++k) {
        img.fill(grafico->getCor(k));
        prov = new QLabel;
        prov->setAlignment(Qt::AlignCenter);
        prov->setPixmap(img);
        ui->tableFuncoes->setCellWidget(k, 0, prov);

        prov = new QLabel;
        prov->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        prov->setWordWrap(true);
        prov->setText(QString::fromStdString(grafico->getEval(k).getText()));
        ui->tableFuncoes->setCellWidget(k, 1, prov);
    }
}

void MainPlotador::atualizaLimitesEDesenha() {
    double minX = ui->spinMinX->value() * pow(10.0, ui->spinExpX->value());
    double maxX = ui->spinMaxX->value() * pow(10.0, ui->spinExpX->value());
    double minY = ui->spinMinY->value() * pow(10.0, ui->spinExpY->value());
    double maxY = ui->spinMaxY->value() * pow(10.0, ui->spinExpY->value());
    int nTiqueX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();
    int nTiqueY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();

    grafico->setLimites(minX, maxX, minY, maxY, nTiqueX, nTiqueY);
    grafico->desenharGrafico();
}

void MainPlotador::slotGraficoClicked(double X, double Y) {
    QString msg = QString("X=%1; Y=%2").arg(X, 0, 'f', 5).arg(Y, 0, 'f', 5);
    ui->statusbar->showMessage(msg);
}
