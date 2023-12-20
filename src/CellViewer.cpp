#include "CellViewer.h"
#include "Cell.h"
#include "CellsLib.h"
#include "CellsModel.h"
#include "CellWidget.h"
#include "InstancesWidget.h"
#include "SaveCellDialog.h"
#include "OpenCellDialog.h"

#include <QMessageBox>
#include <QDialog>
#include <QMenu>
#include <QAction> 
#include <QMenuBar>

namespace Netlist{ 

CellViewer::CellViewer( QWidget* parent)
    : QMainWindow ( parent )
    , cellWidget_ ( NULL )
    , cellsLib_(NULL)
	, instancesWidget_(NULL)
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

CellViewer::~CellViewer(){
    delete cellWidget_ ;

}

Cell* CellViewer::getCell() const {
    return cellWidget_-> getCell(); //recuperer la cell de dessin
}

void CellViewer::saveCell (){
    Cell* cell = getCell ();
    if ( cell == NULL ) return ;

    QString cellName = cell -> getName (). c_str ();

    if ( saveCellDialog_ -> run ( cellName )) {
        cell -> setName ( cellName.toStdString () );
        cell -> save ( cellName.toStdString () );
    }
}
void CellViewer::setCell(Cell* cellule){
    cellWidget_->setCell(cellule) ; // on va setup le dessin que l'on veut dans la fenetre. 
    instancesWidget_ -> setCell(cellule) ; // permet de setup toutes les instances d'une entitée chargée
    cellsLib_ -> getBaseModel() -> setCell(cellule) ; //pas de setCell dans cellLib.h

}
void CellViewer::openCell(){ // doit recuperer le nom de la cellule a ouvrir
	
    QString cellName ;
    Cell* cell;
    if(OpenCellDialog::run(cellName,this ))
    {	

        cell = Cell::find(cellName.toStdString()) ;

        if(not(cell)) // si find renvoie NULL c'est que la cellule n'est pas chargée dans ce cas on va la load5
        {

            cell = Cell::load(cellName.toStdString()) ;
            if(cell == nullptr) // on test si le load a bien réussi, permet d'éviter une segfault
            {
                return ;
            }
            cell->	setName(cellName.toStdString()) ;
            this -> setCell(cell) ;
            cerr << "Cell is well loaded " << endl ;			
        }
        else //Si find ne renvoie pas NULL c'est que la cellule est déjà chargée, dans ce cas on va juste l'afficher
        {
            cerr << "Cell is already load, printing " << endl ;
            cell->	setName(cellName.toStdString()) ;
            this -> setCell(cell) ;
        }
    }
}

void CellViewer::showInstancesWidget ()
{
    instancesWidget_->show();
}
void CellViewer::showCellsLib()
{
    cellsLib_ -> show() ;
}
}