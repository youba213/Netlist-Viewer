#ifndef NETLIST_Net_H
#define NETLIST_Net_H
#include <string>
#include <iostream>
#include "Indentation.h"
#include "Term.h"


namespace Netlist{
    class Cell; 
    class Node;

class Net 
    {
    private:
        Cell*               owner_;
        std::string         name_;
        unsigned int        id_;
        Term::Type          type_;
        std::vector<Node*>  nodes_;

    public:
        Net     ( Cell*, const std::string&, Term::Type );
        ~Net     ();

        Cell*                     getCell       () const;
        const std::string&        getName       () const;
        unsigned int              getId         () const;
        Term::Type                getType       () const;
        const std::vector<Node*>& getNodes      () const;
        size_t                    getFreeNodeId () const;

        void  add    ( Node* );
        bool  remove ( Node* );

        void						toXml(ostream&);
        static Net* 					fromXml(Cell*, xmlTextReaderPtr) ;
		static bool  					fromXml(Net*, xmlTextReaderPtr);
    };


}
#endif