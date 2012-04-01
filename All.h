#ifndef ALL_H
#define ALL_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

//define integer time....
class Particle {
	public:
    double m,Pos[3],Vel[3],Acc[3], Pot, Softening,GravPotential;
    unsigned int ID,ThisParticleNumber;
    double Color;
    int TimeStepBegin;
    int TimeStepEnd;
    int KickTime;
    int DriftTime;
    

		Particle (){Color=0.0;};
		Particle (double ,double ,double ,double ,double ,double ,double ,double, unsigned int);
		void Set (double ,double ,double ,double ,double ,double ,double ,double, unsigned int);
		void AdvancePos(double );
		void AdvanceVel(double );
		void SetPos(double, double, double);
		void SetVel(double, double, double);
		void SetAcc(double, double, double);
		double GetPos(int i) {return Pos[i];};
		double GetMass(void) {return m;};
		double GetVel(int i) {return Vel[i];};
		double GetAcc(int i) {return Acc[i];};
		double GetSoftening(void){return Softening;};
		void PrintInfo(void);
		void SetColor(double);
        double GetColor(void);
		void ComputeGravPotentialAndAcc(class Node *A,class Particle *P);
};


class Node {
    public:	
	unsigned int *IDs;
	double xMin,yMin,zMin,xMax,yMax,zMax, LengthOfBox;
    double M,CM[3],CMVel[3],t;
    class Node *Children[8];
    unsigned short int EndNode;
    std::vector<unsigned int> Members;


	    Node();
	    void CreateRoot(class Particle *,unsigned int);
	    void CreateNodes(class Particle *,unsigned int);
	    double GetNodeMass(void){return M;};
	    unsigned int GetN(void){return Members.size();};
	    unsigned int GetMember(unsigned int i){return Members.at(i);};
	    class Node *GetChildren(int i){return Children[i];};
	    void CreateChildren(class Particle *,unsigned int);
	    double ComputeMass(class Particle *,unsigned int );
        double ComputeCM(class Particle *,unsigned int , int );
        void DestroyNode(void);
};


class Simulation {
	double G;
	int StartTime;
	int EndTime;
	long int Time;
	int TimeNextSnapshot;
	
	double dt_min;
	long int Tstart;
	long int Tend;
	double IntTimePerRealTime;
	double RealTimePerIntTimeStep;
	
	int NSnapshots;
	
	std::vector<int> SnapshotTimes;
	
	Particle *P;

    public:
	    Simulation();
		//void Initialize(void);
	    void Run(void);
	    void ReadGadget2IC();
	    void ReadGadget2Snapshot();
	    void WriteSnapshot();
	    Particle *GetP(){return P;};
};


int main();


#endif
