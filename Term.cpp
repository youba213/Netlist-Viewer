#include"Term.h"
#include "Cell.h"
#include "Instance.h"
#include "Net.h"

namespace Netlist
{
    using namespace std;
    //CONSTRUCTEUR Term d'une cell;
    Term::Term ( Cell*   cell , const std::string& name, Direction dir ):
            owner_(cell),
            name_(name),
            direction_(dir),
            type_(External),
            net_(NULL),
            node_(this)
    {
        cell->add(this) ;
    }
    //CONSTRUCTEUR Term d'une instance;
    Term::Term ( Instance* instance, const Term* modelTerm ):
            owner_(instance) ,
			name_(modelTerm->getName()) ,
			direction_ (modelTerm->getDirection()) ,
			type_ (Internal) ,
			net_(NULL), 
			node_ (this)
    {
        instance->add(this) ;
    }
    Term::~Term (){
        //on déconnecte le terminal de son owner
        if(this->getType() == Internal)
		{
			static_cast<Instance*> (owner_)->remove(this) ;
		}
		else
		{
			static_cast<Cell*> (owner_)->remove(this) ;
		}
        (this->getNet())->remove(this->getNode());
        //on supprime son noeud
        delete &node_ ;
    }

    std::string         Term::toString    ( Term::Type t){
        if (t == Internal){
            return "Internal";
        }
        else if (t == External){
            return "External";
        }
    }    
    std::string         Term::toString    ( Term::Direction d){
        if (d == In){
        return "In";
        }
        else if (d == Out){
        return "Out";
        }
        else if (d == Inout){
        return "Inout";
        }
        else if (d == Tristate){
        return "Tristate";
        }
        else if (d == Transcv){
        return "Transcv";
        }
        else if (d == Unknown){
        return "Unknown";
        }
        
    }
    Term::Direction     Term::toDirection ( std::string str ){
        if (str == "In") 
			{
				return In ;
			}
			else if (str == "Out")
			{
				return Out ;
			}
			else if (str == "Inout")
			{
				return Inout ;
			}
			else if (str == "Tristate")
			{
				return Tristate ;
			}
			else if (str == "Transcv")
			{
				return Transcv ;
			} 				
			else if (str == "Unknown")
			{
				return Unknown ;
			} 				
			else
			{
				cerr<<"Erreur le type de direction choisi n'est pas défini" ;
				exit(1);
			}

    }
       void  Term::setNet       ( Net* net){
        if (net == NULL) {
			net_->remove(&node_);
			net_ = NULL;
		}
		else if (net_ == NULL) {
			net->add(&node_);
			net_ = net;
		}
		else {
			if (net_->remove(&node_)) {
				net->add(&node_);
				net_ = net;
			}
		}
       }
       void  Term::setNet       ( const std::string& name){
            if(type_ == Internal)
		    {
                std::vector<Net*> nets_Cell = this->getInstance()->getCell()->getNets() ; //on recupère les nets de la cell 
                int trouve = 0 ;
                //On parcourt tous les nets de la cellule propriéraire 
                for(size_t i = 0 ; i < nets_Cell.size() ; i++)
                {
                    if(nets_Cell[i]->getName() == name)//si le noeud existe on l'affecte directement au terminal
                    {
                        net_ = nets_Cell[i] ;
                        trouve = 1 ;
                    }
                }
                if (trouve==0)//si on ne l'a pas trouvé, on le créer.
                {
                    net_ = new Net(this->getInstance()->getCell(),name,Internal) ;	
                }	
		    }
            else
            {
                
                std::vector<Net*> nets_Cell = this->getCell()->getNets() ; //on recupère les nets de la cell 
                int trouve = 0 ;
                //On parcourt tous les nets de la cellule propriéraire 
                for(size_t i = 0 ; i < nets_Cell.size() ; i++)
                {
                    if(nets_Cell[i]->getName() == name)//si le noeud existe on l'affecte directement au terminal
                    {
                        net_ = nets_Cell[i] ;
                        trouve = 1 ;
                    }
                }
                if (trouve==0)//si on ne l'a pas trouvé, on le créer.
                {
                    net_ = new Net(this->getInstance()->getCell(),name,Internal) ;	
                }
            }
        }

    void  Term::setPosition  ( const Point& pos){
        node_.setPosition(pos);
    }
    void  Term::setPosition  ( int x, int y ){
        node_.setPosition(x,y);
    }
    Cell*              Term::getOwnerCell () const{
            if (Term::type_ == Internal ){
            return static_cast<Instance*> (owner_)->getCell();
            }
            else {
            return static_cast<Cell*> (owner_);
            }
        }
    void Term::toXml(ostream& os)
    {
        extern Indentation indent ;
        os<<indent<<"<term name=\""<<this->getName()<<"\" direction=\""<<toString(this->getDirection())<<"\"/>\n" ;
    }

    Term* Term::fromXml(Cell* Cell, xmlTextReaderPtr reader)
	{
			std::string 			term_name 			= xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
			std::string 			direction_string 	= xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"direction" ) );
			std::string 			x_string 			= xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x" ) );
			std::string 			y_string 			= xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y" ) );
			if(not (term_name.empty() or direction_string.empty()) )
			{
					Direction direction = toDirection(direction_string) ;
					Term* term = new Term(Cell, term_name, direction) ;
					term->setPosition(stoi(x_string),stoi(y_string)) ;
					return term ;
			}
			else 
			{
				cerr << "Impossible de charger les terminaux" << endl; 
				return NULL;
			}

	}

} // namespace Netlist
