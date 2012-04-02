#include "All.h"

using namespace std;

int main();

Simulation::Simulation(void){
	//Read some parameter file. set G and softening
	//call ReadGadget2IC and set P
	ReadGadget2IC();
//	G = 1.0;

	StartTime = 0.0;
	EndTime = 100.;
	dt_min = (EndTime-StartTime)/1.0e5;
	
	Tstart = StartTime/dt_min;
	Tend = EndTime/dt_min;
	IntTimePerRealTime = 1.0/dt_min;
	RealTimePerIntTimeStep = dt_min;

	Time = Tstart;
	
	NSnapshots = 10;
	for (int i=0; i<NSnapshots;i++)
		SnapshotTimes.push_back(Tstart + (Tend - Tstart)/(NSnapshots) * i );

	std::cout<< dt_min<< "Tend " << Tend<<"\t"<< Tend*RealTimePerIntTimeStep <<std::endl;
}



void Simulation::Run(void){
//Run simulation	
	int SnapshotsWritten = 0;
	long int NextSnapshotTime = SnapshotTimes.at(SnapshotsWritten);
	long int SmallestStep=1;
	
	do{
			//create snapshot if necessary
			if (Time >= NextSnapshotTime){
				
				std::cout << Time << " " <<  Time*RealTimePerIntTimeStep <<std::endl;
				
				SnapshotsWritten++;
				
				if (SnapshotsWritten < SnapshotTimes.size())
					NextSnapshotTime = SnapshotTimes.at(SnapshotsWritten);
				else
					NextSnapshotTime = Tend;
				
				}
		
		
		//determine timesteps
		SmallestStep = 1;
		
		
		//advance particles... calc forces...
		

		Time += SmallestStep;
		
		
	}
	while(Time<Tend);
	
	std::cout << Time << std::endl;
	

};


void Simulation::ReadGadget2IC(void){
//Set P...	

    double x,y,z,vx,vy,vz,m;
    FILE *File;
    
    P = new Particle[2048];
    if (!P)
    std::cout << "could not allocate memory... q234edqwj" <<std::endl;

    File = fopen("IC/dmhalo1.dat","r+");
    if(!File)
    std::cout << "could not find file... asdfvmp" << std::endl;
        
    for (int i=0;i<2048;i++)
    {
		fscanf(File, "%lf", &x);
		fscanf(File, "%lf", &y);
		fscanf(File, "%lf", &z);
		fscanf(File, "%lf", &vx);
		fscanf(File, "%lf", &vy);
		fscanf(File, "%lf", &vz);
		fscanf(File, "%lf", &m);
		P[i].Set(x,y,z,vx,vy,vz,m,0.005,i);
    }
};


void Simulation::ReadGadget2Snapshot(void){
//Set P...
	

};


void Simulation::WriteSnapshot(void){};
