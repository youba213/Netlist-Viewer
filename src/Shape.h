#ifndef NETLIST_Net_H
#define NETLIST_Net_H

#include "Box.h"
#include "Symbol.h"
#include "XmlUtil.h"
#include <iostream>
#include "Term.h"

namespace Netlist
{
    class Shape
    {
        Symbol *owner_;

    public:
                        Shape           (Symbol *);
                        ~Shape          ();
        inline Symbol*  getSymbol       () const;
        virtual Box     getBoundingBox  () const = 0;
        virtual void    toXml           (ostream &);
        static Shape*   fromXml         (Symbol*, xmlTextReaderPtr);
    };

    inline Symbol *Shape::getSymbol() const { return owner_; }

    class LineShape : public Shape
    {   
        int x1_, y1_, x2_, y2_;
        public :
		
							LineShape 			( Symbol*, int x1 , int y1 , int x2 , int y2 );
							~LineShape 			() ;
			    inline int 	getX1 () const ;
			    inline int 	getY1 () const ;
			    inline int 	getX2 () const ;
			    inline int 	getY2 () const ;
		Box 				getBoundingBox 		() const ;
		void				toXml				(ostream&) ;
		static LineShape*	fromXml				(Symbol*, xmlTextReaderPtr) ;

    };
    class BoxShape : public Shape
    {
        Box box_;
        public :
			
								BoxShape 		( Symbol *, const Box & );
								BoxShape 		( Symbol *, int x1 , int y1 , int x2 , int y2 );
								~BoxShape 		();
			Box 				getBoundingBox 	() const ;	
			void				toXml			(ostream&) ;
			static BoxShape*	fromXml			(Symbol*, xmlTextReaderPtr) ;
    };
    class EllipseShape : public Shape
    {
        Box box_;
        public :

									EllipseShape 		( Symbol*, const Box &box );
									~EllipseShape 		();
			Box 					getBoundingBox 	() const ;
			void					toXml			(ostream&) ;
			static EllipseShape*	fromXml			(Symbol*, xmlTextReaderPtr) ;
		
    };
    class ArcShape : public Shape
    {
        Box box_;
        int start_, span_;
        public :
								ArcShape			(Symbol* owner, const Box&, int, int ) ;
								~ArcShape			() ;
			Box 				getBoundingBox		() const ;
			int 				getStart 		 	() const ;
			int 				getSpan 		 	() const ; 
			void				toXml				(ostream&) ;
			static ArcShape*	fromXml				(Symbol*, xmlTextReaderPtr) ;
    };

    class TermShape : public Shape 
	{
		public :
			enum NameAlign {Topleft = 1, TopRight, BottomLeft, BottomRight } ;
		public :

								TermShape 		( Symbol *, string name , int x , int y );
								~TermShape 		();
			Box 				getBoundingBox 	() const ;
			inline Term * 		getTerm 		() const ;
			inline int 			getX 			() const ;
			inline int 			getY  			() const ;
			inline NameAlign	getAlign		() const ;
			void				toXml			(ostream&) ;
			static TermShape*	fromXml			(Symbol*, xmlTextReaderPtr) ;
		
		private :
			Term * 		term_ ;
			int 		x1_ , y1_ ;
			NameAlign align_ ;
	};
	inline Term* 				TermShape::getTerm 	() const {return term_ ; } ;
	inline int 					TermShape::getX 	() const {return x1_ ;} ;
	inline int 					TermShape::getY  	() const {return y1_ ;} ;
	inline TermShape::NameAlign	TermShape::getAlign () const {return align_ ;} ;	
}
#endif