#include "Instance.h"
#include "Cell.h"
#include <iostream>
#include "algorithm"
#include "XmlUtil.h"

namespace Netlist{

        Instance::Instance      ( Cell* owner, Cell* model, const std::string& name):
                owner_(owner) , 
                masterCell_(model) ,
                name_(name) ,
                position_() 
        {
                owner->add(this);
                // on copie les Terminaux de la cellule à l'instance
                std::vector<Term*> terms_copie = model->getTerms() ; 
		for(auto it = terms_copie.begin() ; it != terms_copie.end() ; ++it)
		{
			new Term(this,(*it)) ;
			
		}
        }
        Instance::~Instance      (){
                owner_->remove(this) ;
 		for(size_t i = 0 ; i < terms_.size() ; i++)
		{
			delete terms_[i] ;
		}}
        
        const std::string&        Instance::getName       () const{
                return name_;
        }
        Cell*                     Instance::getMasterCell () const{
                return masterCell_;
        }
        Cell*                     Instance::getCell       () const{
                return owner_;
        }
        const std::vector<Term*>& Instance::getTerms      () const{
                return terms_;
        }
        Term*                     Instance::getTerm       ( const std::string& str) const{
                for (std::vector<Term*>::const_iterator it = terms_.begin(); it != terms_.end(); ++it){
                if ((*it) -> getName() ==str)
                        return *it;
                }
                std::cout<<"Le terminal auquel vous essayer d'accéder n'existe pas" <<std::endl ;
		exit(1) ;
        }
        Point                     Instance::Instance::getPosition   () const{
                return position_;
        }

        bool  Instance::connect       ( const std::string& name, Net* net){
                Term* term = getTerm( name); // on regarde si le terminal existe dans l'instance
		if(term == NULL ) 
                        return false ; // s'il n'existe pas on renvoit faux
		term->setNet(net) ; // sinon le connect sur le net
		        return true ;
        }
        void  Instance::add           ( Term* t){
                for(auto it = terms_.begin() ; it != terms_.end() ; ++it)
		{
			if(t->getName() == (*it)->getName())
			{
				std::cout<<"Impossible d'ajouter ce terminal, le nom est déjà utilisé" << std::endl ;
				exit(1) ;
			}	
		}
		terms_.push_back(t) ;

        }
        void  Instance::remove        ( Term* t){
                auto it = std::find(terms_.begin(), terms_.end(), t);
                if (it != terms_.end()) {
                terms_.erase(it);
                }
        }
        void  Instance::setPosition   ( const Point& pos ){
                position_= pos;
        }
        void  Instance::setPosition   ( int x, int y ){
                position_= Point(x,y);
        }

        void Instance::toXml(ostream& os)
	{
		extern Indentation indent ;
		os<<indent<<"<instance name=\""<<this->getName()<<"\" mastercell=\""<<this->getMasterCell()->getName()<<"\" "<<"x=\""<<this->getPosition().getX()<<"\" y=\""<<this->getPosition().getY()<<"\"/>\n" ;
	}	

        Instance* Instance::fromXml	(Cell* cellule, xmlTextReaderPtr reader)
	{
		std::string name = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
		std::string mastercell =xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"mastercell" ) );
		std::string x = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x" ) );
		std::string y = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y" ) );
		if (not (name.empty() or mastercell.empty()))
		{
			Instance* instance = new Instance(cellule,Cell::find(mastercell),name) ;
			instance->setPosition(stoi(x),stoi(y)) ;
			return instance ;
		}	
		else
		{
			cerr << "Impossible de créer correctement l'instance" ;
			return NULL ;
		}
	}


}