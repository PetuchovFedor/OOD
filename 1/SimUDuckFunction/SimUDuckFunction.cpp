#include "DecoyDuck.h"
#include "MallardDuck.h"
#include "ModelDuck.h"
#include "RedheadDuck.h"
#include "RubberDuck.h"
#include "DuckFunctions.h"
#include <cstdlib>

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	//MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	//RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	//RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	//MallardDuck mallardDuck1;
	//PlayWithDuck(mallardDuck1);

	//MallardDuck mallardDuck;
	//PlayWithDuck(mallardDuck1);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);

	modelDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(modelDuck);
}