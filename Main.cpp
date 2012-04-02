#include "All.h"



int main(){
//	Simulation *Sim = new Simulation();
	//Sim->Initialize();
	//Sim->ReadGadget2IC();
//	Particle *P1 = Sim->GetP();
	
//	Sim->Run();



 int i;
   double x,y,z,vx,vy,vz,m;
   Particle *P = NULL;

    FILE *Filename;




	#define N_TEST 1000000
    P = new Particle[N_TEST];
    if (!P)
    std::cout << "could not allocate memory... q234edqwj" <<std::endl;




    Filename = fopen("IC/Hq1e6.txt","r+");
    if(!Filename)
    std::cout << "could not find file... asdfvmp" << std::endl;
    
    for (i=0;i<N_TEST;i++)
    {
			fscanf(Filename, "%lf", &x);
			fscanf(Filename, "%lf", &y);
			fscanf(Filename, "%lf", &z);
			fscanf(Filename, "%lf", &vx);
			fscanf(Filename, "%lf", &vy);
			fscanf(Filename, "%lf", &vz);
			fscanf(Filename, "%lf", &m);
			P[i].Set(x,y,z,vx,vy,vz,m,0.005,i);
    }
	


	class Node *Root = NULL;	
	
	Root = new Node();
	Root->CreateRoot(P,N_TEST);
	Root->CreateNodes(P,N_TEST);

	Root->ComputeMass(P,N_TEST);
	Root->ComputeCM(P,N_TEST,0);
	Root->ComputeCM(P,N_TEST,1);
	Root->ComputeCM(P,N_TEST,2);
//	std::cout << 	Root->ComputeCM(P,N_TEST,0) << " " << Root->ComputeCM(P,N_TEST,1) <<" " << Root->ComputeCM(P,N_TEST,2) << std::endl;
	//Root->DestroyNode();	
	
	
	
	
	
	//make this

//	for(unsigned int i=0;i<N;i++)
//	P[0].CalcGravAccel(P,Root);
//	P[0].SetAcceleration( Root->ComputeAcc   )
	double r;
//	#pragma omp parallel

	std::cout << "Start force calculation" << std::endl;

	#pragma omp parallel for private(i,r)
	for(i=0; i<N_TEST; i++){

		r = pow( pow(P[i].Pos[0],2) + pow(P[i].Pos[1],2) + pow(P[i].Pos[2],2) ,0.5);
		P[i].ComputeGravPotentialAndAcc(Root,P);
	//	std::cout << r << "\t" <<P[i].GravPotential << std::endl;
	}

	std::cout << "End force calculation" << std::endl;

	std::ofstream myfile ("V.txt");
	
	for(i=0; i<N_TEST; i++){
		r = pow( pow(P[i].Pos[0],2) + pow(P[i].Pos[1],2) + pow(P[i].Pos[2],2) ,0.5);
		myfile << r << "\t" <<P[i].GravPotential << "\t" << pow( pow(P[i].Acc[0],2) + pow(P	[i].Acc[1],2) + pow(P[i].Acc[2],2) ,0.5)  <<"\n";
	}


	myfile.close();


	double meanx = 0.0,meany = 0.0,meanz = 0.0 ;
	for (int i=0; i<N_TEST; i++){
		meanx += P[i].GetPos(0);
		meany += P[i].GetPos(1);
		meanz += P[i].GetPos(2);
	}

//	std::cout << meanx/N_TEST << " " << meany/N_TEST << " " << meanz/N_TEST << std::endl;

//	std::cout << 	Root->CM[1] << " " << Root->M << std::endl;


/* Debug stuff - check tree construction	*/
/*    for(int j=0;j<8;j++)
	for (int i=0;i<Root->GetChildren(2)->GetChildren(j)->GetN();i++){
	    int no = Root->GetChildren(2)->GetChildren(j)->GetMember(i);
	    P[no].SetColor(j+1);
	    P[no].PrintInfo();
	}*/

	
	return 0;
}
