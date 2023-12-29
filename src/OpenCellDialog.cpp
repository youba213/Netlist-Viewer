#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "OpenCellDialog.h"
#include "CellViewer.h"
#include "CellWidget.h"

namespace Netlist
{
  OpenCellDialog::OpenCellDialog(QWidget* parent)
    : QDialog(parent), lineEdit_(NULL)
  {
    setWindowTitle(tr("Open Cell"));

    QLabel* label = new QLabel();
    label->setText(tr("Enter Cell name (without extension)"));

    lineEdit_ = new QLineEdit();
    lineEdit_->setMinimumWidth(400);

    QPushButton* okButton = new QPushButton();
    okButton->setText("OK");
    okButton->setDefault(true);

    QPushButton* cancelButton = new QPushButton();
    cancelButton->setText("Cancel");

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addStretch();
    hlayout->addWidget(okButton);
    hlayout->addStretch();
    hlayout->addWidget(cancelButton);
    hlayout->addStretch();

    QFrame* separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSizeConstraint(QLayout::SetFixedSize);
    vlayout->addWidget(label);
    vlayout->addWidget(lineEdit_);
    vlayout->addLayout(hlayout);
    setLayout(vlayout);

    connect(    okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
  }
  OpenCellDialog::~OpenCellDialog		()
  {

  }
  const QString OpenCellDialog::getCellName() const
  {
    return lineEdit_->text();
  }
  void OpenCellDialog::setCellName(const QString& name)
  {
    return lineEdit_->setText(name);
  }
  bool OpenCellDialog::run(QString& name, CellViewer* parent)
  {
    OpenCellDialog ocd;
    ocd.setCellName(name);
    int dialogResult = ocd.exec();
    name = ocd.getCellName();
    
    return dialogResult == Accepted;
  }
}