#include "Net.h"
#include "Cell.h"
#include "Node.h"
#include "Term.h"

namespace Netlist
{   
    Net::Net     ( Cell* cellule, const std::string& name, Term::Type type ):
            owner_(cellule),
            name_(name),
            id_(cellule->newNetId()),
            type_(type),
            nodes_()
    {
        cellule->add(this) ;
    }
    Net::~Net     (){
        // on va détacher tous les nodes qui sont connectés au net
        for(size_t i = 0 ; i < nodes_.size(); i++){
            (nodes_[i]->getTerm())->setNet(NULL);
        }
        //on va retire le net de sa cell
        owner_->remove(this);
    }
    Cell*                     Net::getCell       () const{
        return owner_;
    }
    const std::string&        Net::getName       () const{
        return name_;
    }
    unsigned int              Net::getId         () const{
            return id_;   	
    }
    Term::Type                Net::getType       () const{
        return type_;
    }
    const std::vector<Node*>& Net::getNodes      () const{
        return nodes_;

    }
    size_t                    Net::getFreeNodeId () const{
		for(size_t i = 0 ; i < nodes_.size() ; i++)
		{
			if(nodes_[i] == NULL)
			{
                std::cout<<"getfreeNodes"<<std::endl;
                return i;
			    break;            // dès que l'on rencontre une pointeur NULL on arrete la boucle et on renvoie sa valeur
			
			}
		}
        //sinon rretourner la taille de nodes_
		return nodes_.size() ;
    }
    void  Net::add    ( Node* node){
        size_t position_insertion = node->getId(); 
        if(position_insertion == Node::noid)
		{
            //inserer le noeud a la premier case vide de vecteur
            size_t index = getFreeNodeId();
            nodes_.insert(nodes_.begin()+index, node);
            node->setId(index);
            
		}

        else
        {
            /*
            On va insérer un noeud à la position position_insertion de notre vecteur nodes_.
            Si la position existe déja, on insère à cette position en vérifiant que rien n'est déjà écrit à cette emplacement
            Sinon si cette position n'existe pas, on va push_back(NULL) jusqu'à créer l'emplacement que l'on veut
            */
            if(position_insertion < nodes_.size())
            {
                if(nodes_[position_insertion] == NULL)
                {
                    nodes_[position_insertion] = node ; 
                }
                else
                {
                    std::cout <<"Erreur le noeud est déjà occupé, merci d'en choisir un autre" << std::endl ;
                }
            }
            else
            {
                while(nodes_.size() != position_insertion)
                {
                    nodes_.push_back(NULL) ;
                }
                nodes_.push_back(node) ;
            }
        }

    };
    bool  Net::remove ( Node* node){
        size_t id = node->getId();
        nodes_.erase(nodes_.begin()+id) ;
        return 0;
    };
    void Net::toXml(ostream& os)
	{
        extern Indentation indent ;
		//on affiche tous les nets de la Cell
		os<<indent<<"<net name=\""<<this->getName()<<"\" type=\""<<Term::toString(this->getType())<<"\">\n";		
		std::vector<Node*> nodes = this->getNodes() ;		
		indent++ ;
        // on affiche les nodes
		for(auto it = nodes.begin() ; it != nodes.end() ; ++it) 
		{
			if((*it) !=NULL)
			{
				(*it)->toXml(os) ;
			}
		}
		indent -- ;
		os<<indent<<"</net>" <<endl;
	}
    
    Net* Net::fromXml(Cell* cellule, xmlTextReaderPtr reader)
	{

		std::string name 		= xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name")) ;
		std::string type_string = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"type")) ;
		
		if(not(name.empty() or type_string.empty())) // si le nom de la cell et son type ne sont pas vides
		{
			Term::Type type = Term::toType(type_string) ;
			Net* net = new Net(cellule, name, type) ;
			
			const xmlChar* nodeTag = xmlTextReaderConstString( reader, (const xmlChar*)"node" );
			const xmlChar* lineTag = xmlTextReaderConstString( reader, (const xmlChar*)"line" );

			while(true)
			{

				  xmlTextReaderRead(reader);

			      switch ( xmlTextReaderNodeType(reader) ) 
			      {
			        //xmlTextReaderNodeType récupère le type du noeud actuel
			        //ca retourne le type du noeud ou -1 en cas d'erreur

			        case XML_READER_TYPE_COMMENT:
			          //si on est de type commentaire on ne fait rien
			        case XML_READER_TYPE_WHITESPACE:
			          //si on est de type espace on ne fait rien
			        case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
			          //si on est de type "espace significatif" on ne fait rien
			          continue;
			      }

			      const xmlChar* nodeName = xmlTextReaderConstLocalName( reader ); // on va setup le nodeName, au debut il va valoir Node

			    if ((nodeName == nodeTag ))          
                {
                	
                    if(Node::fromXml(net,reader))
                    {
                    	
                    	continue;	
                    } 
                    else
                    {
                    	cerr << "Impossible de charger le node depuis la Net, une erreur a été rencontrée" <<endl ;
                    	exit(0) ;
                    }                    
                }
                else if((nodeName == lineTag))
                {
                	
                	if(Line::fromXml(net,reader))
                	{
      
                		continue ;
                	}
                	else
                	{
                		cerr << "Impossible de charger les lines depuis le net" << endl ;
                		exit(0) ;
                	}
                }
                else
                {
                    break;       
                }
                

			} 

			return net ;
		}
		else
		{
			if(name.empty())
			{
				cerr << "name is empty" <<endl ;
			}
			if (type_string.empty())
			{
				cerr << "Type is empty" << endl ;
			}
			cerr<< "Impossible de récupérer les nets correctement"<<endl ;
			exit(0) ;
		}
		
	}
}