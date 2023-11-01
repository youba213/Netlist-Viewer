// -*- explicit-buffer-name: "Node.cpp<M1-MOBJ/4-5>" -*-

#include  <limits>
#include  "Node.h"
#include  "Term.h"
#include  "Net.h"
#include  "Instance.h"
#include  "Cell.h"

namespace Netlist {

  using namespace std;


  const size_t  Node::noid = numeric_limits<size_t>::max();


  Node::Node ( Term* term, size_t id  )
    : id_      (id)
    , term_    (term)
    , position_()
  { }


  Node::~Node ()
  {
    if (getNet()) getNet()->remove( this );
  }


  inline Net* Node::getNet () const { return term_->getNet(); }


 void  Node::toXml ( ostream& stream ) const
  {
    if (term_->isInternal()) {
      stream << indent << "<node term=\"" << term_->getName()
                       << "\" instance=\"" << term_->getInstance()->getName()
                       << "\" id=\""       << id_;
    } else {
      stream << indent << "<node term=\"" << term_->getName()
             << "\" id=\""       << id_;
    }
    stream << "\" x=\"" << position_.getX() << "\" y=\"" << position_.getY() << "\"/>\n";
  }

 bool   Node::fromXml ( Net* net, xmlTextReaderPtr reader )
  {
    const xmlChar* nodeTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"node" );
    const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );
    int            id       = -1;

    if (nodeTag == nodeName) {
      string instanceName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"instance" ) );
      string termName     = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"term"     ) );

      xmlGetIntAttribute( reader, "id", id );
      if (id < 0) return false;

      if (termName.empty()) {
        int x = 0;
        int y = 0;
        if (   xmlGetIntAttribute( reader, "x", x )
           and xmlGetIntAttribute( reader, "y", y )) {
          new NodePoint( net, (size_t)id, Point(x,y) );
          return true;
        }
        return false;
      }

      Term* term = NULL;
      if (not instanceName.empty()) {
        Instance* instance = net->getCell()->getInstance( instanceName );
        if (not instance) {
          cerr << "[ERROR] No Instance <" << instanceName << "> in Cell <" << net->getCell()->getName()
               << "> (line:" << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
          return false;
        }
        term = instance->getTerm( termName );
        if (not term) {
          cerr << "[ERROR] No Term <" << termName << "> in Instance <" << instanceName
               << "> (line:" << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
          return false;
        }
      } else {
        term = net->getCell()->getTerm( termName );
        if (not term) {
          cerr << "[ERROR] No Term <" << termName << "> in Cell <" << net->getCell()->getName()
               << "> (line:" << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
          return false;
        }
      }

      term->getNode()->setId( id );
      term->setNet( net );
      return true;
    }

    return false;
  }


}  // Netlist namespace.
