// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/4-5>" -*-

#include <string>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;

#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
using namespace Netlist;


int main ( int argc, char* argv[] )
{
  /*cout << "\nConstruction du modele <and2>." << endl;
  Cell* and2 = new Cell ( "and2" );
  new Term( and2, "i0", Term::In  );
  new Term( and2, "i1", Term::In  );
  new Term( and2,  "q", Term::Out );
  //and2->toXml( cout );

  cout << "\nConstruction du modele <or2>." << endl;
  Cell* or2 = new Cell ( "or2" );
  new Term( or2, "i0", Term::In  );
  new Term( or2, "i1", Term::In  );
  new Term( or2,  "q", Term::Out );
  //or2->toXml( cout );

  cout << "\nConstruction du modele <xor2>." << endl;
  Cell* xor2 = new Cell ( "xor2" );
  new Term( xor2, "i0", Term::In  );
  new Term( xor2, "i1", Term::In  );
  new Term( xor2,  "q", Term::Out );
  //xor2->toXml( cout );

  cout << "\nConstruction du modele <halfadder>." << endl;
  Cell* halfadder = new Cell ( "halfadder" );
  new Term( halfadder, "a"   , Term::In  );
  new Term( halfadder, "b"   , Term::In  );
  new Term( halfadder, "sout", Term::Out );
  new Term( halfadder, "cout", Term::Out );
  Net*      ha_a    = new Net      ( halfadder, "a"   , Term::External );
  Net*      ha_b    = new Net      ( halfadder, "b"   , Term::External );
  Net*      ha_sout = new Net      ( halfadder, "sout", Term::External );
  Net*      ha_cout = new Net      ( halfadder, "cout", Term::External );
  Instance* ha_xor2 = new Instance ( halfadder, Cell::find("xor2"), "xor2_1" );
  Instance* ha_and2 = new Instance ( halfadder, Cell::find("and2"), "and2_1" );
  halfadder->connect( "a"   , ha_a    );
  halfadder->connect( "b"   , ha_b    );
  halfadder->connect( "sout", ha_sout );
  halfadder->connect( "cout", ha_cout );
  ha_xor2->connect( "i0", ha_a    );
  ha_xor2->connect( "i1", ha_b    );
  ha_xor2->connect(  "q", ha_sout );
  ha_and2->connect( "i0", ha_a    );
  ha_and2->connect( "i1", ha_b    );
  ha_and2->connect(  "q", ha_cout );
  //halfadder->toXml( cout );

  cout << "\nConstruction du modele <fulladder>." << endl;
  Cell* fulladder = new Cell ("fulladder");
  new Term( fulladder, "a"    ,  Term::In  );
  new Term( fulladder, "b"    ,  Term::In  );
  new Term( fulladder, "cin"  ,  Term::In);
  new Term( fulladder, "cout" ,  Term::Out);
  new Term( fulladder, "sout" ,  Term::Out);
  Net*      fa_a        = new Net      ( fulladder, "a"      , Term::External );
  Net*      fa_b        = new Net      ( fulladder, "b"      , Term::External );
  Net*      fa_cin      = new Net      ( fulladder, "cin"    , Term::External );
  Net*      fa_sout     = new Net      ( fulladder, "sout"   , Term::External );
  Net*      fa_cout     = new Net      ( fulladder, "cout"   , Term::External );
  Net*      sout_1      = new Net      ( fulladder, "sout_ 1", Term::Internal );
  Net*      carry_1     = new Net      ( fulladder, "carry_1", Term::Internal );
  Net*      carry_2     = new Net      ( fulladder, "carry_2", Term::Internal );
  Instance* ha1    = new Instance ( fulladder, Cell::find("halfadder"), "ha1" );
  Instance* ha2    = new Instance ( fulladder, Cell::find("halfadder"), "ha2" );
  Instance* fa_or2 = new Instance ( fulladder, Cell::find("or2")      , "or2" );
  fulladder->connect( "a"   , fa_a    );
  fulladder->connect( "b"   , fa_b    );
  fulladder->connect( "cin" , fa_cin );
  fulladder->connect( "sout", fa_sout );
  fulladder->connect( "cout", fa_cout );

  ha1->connect    (   "a"   , fa_a    );
  ha1->connect    (  "b"    , fa_b    );
  ha1->connect    (  "sout", sout_1);
  ha1->connect    (  "cout", carry_1 );

  ha2->connect    (   "a", fa_cin  );
  ha2->connect    (   "b", sout_1    );
  ha2->connect    (   "sout", fa_sout );
  ha2->connect    (   "cout", carry_2 );
  fa_or2->connect (   "i0", carry_1    );
  fa_or2->connect (   "i1", carry_2    );
  fa_or2->connect (   "q", fa_cout );
  fulladder->toXml( cout );*/

  cout << "Chargement des modeles:" << endl;
  cout << "- <and2> ..." << endl;
  Cell::load( "and2" );

  cout << "- <or2> ..." << endl;
  Cell::load( "or2" );

  cout << "- <xor2> ..." << endl;
  Cell::load( "xor2" );

  cout << "- <halfadder> ..." << endl;
  Cell* halfadder = Cell::load( "halfadder" );

  cout << "\nContenu du <halfadder>:" << endl;
  halfadder->toXml( cout );

  return 0;
}
