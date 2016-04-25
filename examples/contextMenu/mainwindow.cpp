/********************************************************************
* Copyright (C) 2016 Jakob Flierl <jakob.flierl AT gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
********************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QKeySequence> s; // exit app with ESC or CTRL+Q
    s << QKeySequence(Qt::Key_Escape) << QKeySequence(Qt::CTRL + Qt::Key_Q);
    ui->action_Quit->setShortcuts(s);

    connect(ui->gcode, SIGNAL(runFromSelected(int)), this, SLOT(onRunFromSelected(int)));

    // add a non-menubar keyboard shortcut to QMainWindow
    QAction* a = new QAction(this);
    QList<QKeySequence> sr; // run from selected line with F1 or CTRL+R
    sr << QKeySequence(Qt::Key_F1) << QKeySequence(Qt::CTRL + Qt::Key_R);
    a->setShortcuts(sr);
    connect(a, SIGNAL(triggered()), ui->gcode, SLOT(onRunFrom()));
    this->addAction(a);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRunFromSelected(int line) {
    QMessageBox msgBox;

    QString str;
    str.sprintf("Run from line %d.", line);

    msgBox.setText(str);
    msgBox.exec();
}
