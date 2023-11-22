#include <QDialog>


class SaveCellDialog : public QDialog {

    Q_OBJECT ;

    public:
        SaveCellDialog ( QWidget * parent = NULL );
        bool run ( QString & name );
        const QString getCellName () const ;
        void setCellName ( const QString & );

    protected :
        QLineEdit* lineEdit_ ;
    };