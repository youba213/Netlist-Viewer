#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include "SaveCellDialog.h"

#include "CellViewer.h"
#include "Cell.h"
#include "CellWidget.h"

namespace Netlist{ 

CellViewer::CellViewer( QWidget* parent)
    : QMainWindow ( parent )
    , cellWidget_ ( NULL )
    , saveCellDialog_ ( NULL )
{
    cellWidget_     =    new CellWidget     ();
    saveCellDialog_ =    new SaveCellDialog (this );

    setCentralWidget ( cellWidget_ );class CellWidget;
    QMenu*      fileMenu = menuBar () -> addMenu ( " & File " );

    QAction*    action   = new QAction ( " & Save ␣ As " , this );
    action   -> setStatusTip ( " Save ␣ to ␣ disk ␣ ( rename ) ␣ the ␣ Cell " );
    action   -> setShortcut ( QKeySequence ( " CTRL + S " ) );
    action   -> setVisible ( true );
    fileMenu -> addAction ( action );
    connect ( action , SIGNAL ( triggered ()) , this , SLOT ( saveCell ()) );

    action = new QAction ( " & Quit " , this );
    action   -> setStatusTip    ( " Exit ␣ the ␣ Netlist ␣ Viewer " );
    action   -> setShortcut     ( QKeySequence ( " CTRL + Q " ) );
    action   -> setVisible      ( true );
    fileMenu -> addAction       ( action );

    connect ( action , SIGNAL ( triggered ()) , this , SLOT ( close ()) );
}
CellViewer::~CellViewer()
{
    delete cellWidget_ ;

}
void CellViewer::setCell (Cell* cell){
    cellWidget_ -> setCell(cell); //setup le dessin dans la fenetre
}
Cell* CellViewer::getCell() const {
    return cellWidget_-> getCell(); //recuperer la cell de dessin
}
void CellViewer::saveCell ()
{
    Cell* cell = getCell ();
    if ( cell == NULL ) return ;

    QString cellName = cell -> getName (). c_str ();

    if ( saveCellDialog_ -> run ( cellName )) {
        cell -> setName ( cellName.toStdString () );
        cell -> save ( cellName.toStdString () );
    }
}
}