// Shapes header file.
// This class contains static methods for drawing OpenGL shapes.

class Shapes
{
public:
	Shapes() ;
	virtual ~Shapes() ;
	static void printLetter(char letter, bool inout) ;
	static void printE() ;
	static void printF() ;
	static void printH() ;
	static void printL() ;
	static void printN() ;
	static void printOuterO() ;
	static void printInnerO() ;
	static void printOuterR() ;
	static void printInnerR() ;
	static void printT() ;
	static void printOuterU() ;
	static void printInnerU() ;
	static void printW() ;
	static void cube(float size) ;
	static void plane(float length, float width, int orientation) ;
};