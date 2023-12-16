#pragma once
#include <QMainWindow>

namespace Netlist{
class Cell;
class CellsLib ;
class CellWidget;
class InstancesWidget ;
class SaveCellDialog ;

class CellViewer : public QMainWindow {
        Q_OBJECT ;
    public :
                                   CellViewer           (QWidget* parent = NULL );
      virtual                     ~CellViewer           ();
                Cell*             getCell               () const ;
                CellWidget*       getCellWidget         ();
      inline    CellsLib*         getCellsLib           (); 
    public slots:
        void      setCell             ( Cell* );
        void      saveCell            (); 
        void      openCell            ();

        void      showCellsLib        (); 
        void      showInstancesWidget ();  
    private :
        CellWidget*     cellWidget_ ;
        SaveCellDialog* saveCellDialog_ ;
        CellsLib*        cellsLib_;         
        InstancesWidget* instancesWidget_; 
};  
    inline CellsLib* CellViewer::getCellsLib(){return cellsLib_ ;} ;
}