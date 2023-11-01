#ifndef NETLIST_Term_H
#define NETLIST_Term_H

#include"Node.h"
#include"Cell.h"
#include"Point.h"
#include"Instance.h"


namespace Netlist{
class Term
{


    public:
        enum Type      { Internal=1, External=2 };
        enum Direction { In=1, Out=2, Inout=3, Tristate=4, Transcv=5, Unknown=6 };

        Term ( Cell*    , const std::string& name, Direction );
        Term ( Instance*, const Term* modelTerm );
        ~Term ();

     private:
        void*         owner_;
        std::string   name_;
        Direction     direction_;
        Type          type_;
        Net*          net_;
        Node          node_;

     public:
        static std::string  toString    ( Type );
        static std::string  toString    ( Direction );
        static Direction    toDirection ( std::string );
        inline bool               isInternal   () const{
            return (type_ == Internal) ? true : false ;
        }
        inline bool               isExternal   () const{
            return (type_ == External) ? true : false ;
        }
        inline const std::string& getName      () const{
            return name_;
        }
        inline Node*              getNode      (){
            return &node_;
        }
        inline Net*               getNet       () const{
            return net_;
        }
        inline Cell*              getCell      () const{
            return (type_  ==  External) ? static_cast <Cell*>(owner_): NULL;
        }
            Cell*              getOwnerCell () const;
            
        inline Instance*          getInstance  () const{
            return (type_  ==  Internal) ? static_cast <Instance*>(owner_): NULL;
        }
        inline Direction          getDirection () const{
            return direction_;
        }
        inline Point              getPosition  () const{
        }
        inline Type               getType      () const{
            return type_;
        }

       void  setNet       ( Net* );
       void  setNet       ( const std::string& );
inline void  setDirection ( Direction dir){
        direction_=dir;
}
       void  setPosition  ( const Point& );
       void  setPosition  ( int x, int y );

       void				toXml		 (ostream&) ;
       Term* 		fromXml		 (Cell*, xmlTextReaderPtr reader) ;
       


};
}
#endif