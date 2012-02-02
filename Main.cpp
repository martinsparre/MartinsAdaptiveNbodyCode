#include "All.h"


int main(){
	Simulation *Sim = new Simulation();
	//Sim->Initialize();
	//Sim->ReadGadget2IC();
	Particle *P1 = Sim->GetP();
	
	std::cout << P1[0].GetPos(0) << std::endl;
	
	Sim->Run();



/* int i;
   double x,y,z,vx,vy,vz,m;
   Particle *P = NULL;

    FILE *Filename;
    
    P = new Particle[2048];
    if (!P)
    std::cout << "could not allocate memory... q234edqwj" <<std::endl;

    Filename = fopen("dmhalo1.dat","r+");
    if(!Filename)
    std::cout << "could not find file... asdfvmp" << std::endl;
        
    for (i=0;i<2048;i++)
    {
			fscanf(Filename, "%lf", &x);
			fscanf(Filename, "%lf", &y);
			fscanf(Filename, "%lf", &z);
			fscanf(Filename, "%lf", &vx);
			fscanf(Filename, "%lf", &vy);
			fscanf(Filename, "%lf", &vz);
			fscanf(Filename, "%lf", &m);
			P[i].Set(x,y,z,vx,vy,vz,m,0.005);
    }
	
	int k=0;

	class Node *Root = NULL;	
	
	Root = new Node();
	Root->CreateRoot(P,2048);
	Root->CreateNodes(P,2048);
	Root->ComputeMass(P,2048);
	Root->ComputeCM(P,2048,0);
	Root->ComputeCM(P,2048,1);
	Root->ComputeCM(P,2048,2);
	std::cout << 	Root->ComputeCM(P,2048,0) << " " << Root->ComputeCM(P,2048,1) <<" " << Root->ComputeCM(P,2048,2) << std::endl;
	Root->DestroyNode();
	
	
	//make this

//	for(unsigned int i=0;i<N;i++)
//	P[0].CalcGravAccel(P,Root);
//	P[0].SetAcceleration( Root->ComputeAcc   )




	double meanx = 0.0,meany = 0.0,meanz = 0.0 ;
	for (int i=0; i<2048; i++)
	{
		meanx += P[i].GetPos(0);
		meany += P[i].GetPos(1);
		meanz += P[i].GetPos(2);
	}

	std::cout << meanx/2048.0 << " " << meany/2048.0 << " " << meanz/2048.0 << std::endl;

*/


/* Debug stuff - check tree construction	*/
/*    for(int j=0;j<8;j++)
	for (int i=0;i<Root->GetChildren(2)->GetChildren(j)->GetN();i++){
	    int no = Root->GetChildren(2)->GetChildren(j)->GetMember(i);
	    P[no].SetColor(j+1);
	    P[no].PrintInfo();
	}*/

	
	return 0;
}
