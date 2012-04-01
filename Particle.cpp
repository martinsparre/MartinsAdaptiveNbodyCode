#include "All.h"

Particle::Particle(double x,double y,double z,double vx,double vy,double vz,double M,double Soft, unsigned int i)
{
	Set(x,y,z,vx,vy,vz,M,Soft,i);
	Color = 0.0;
	TimeStepBegin = 0;
    TimeStepEnd = 0;
    GravPotential = 0.0;

}


void Particle::Set(double x,double y,double z,double vx,double vy,double vz,double M,double Soft, unsigned int i)
{
	Pos[0] = x;
	Pos[1] = y;
	Pos[2] = z;
	Vel[0] = vx;
	Vel[1] = vy;
	Vel[2] = vz;
	m = M;
	Softening = Soft;
	ThisParticleNumber = i;
}

void Particle::SetColor(double color)
{
    Color = color;
}

double Particle::GetColor(void)
{
    return Color;
}

void Particle::AdvancePos(double dt)
{
	Pos[0] += dt * Vel[0];
	Pos[1] += dt * Vel[1];
	Pos[2] += dt * Vel[2];
}


void Particle::AdvanceVel(double dt)
{
	Vel[0] += dt * Acc[0];
	Vel[1] += dt * Acc[1];
	Vel[2] += dt * Acc[2];
}


void Particle::SetPos(double x, double y, double z)
{
	Pos[0] = x;
	Pos[1] = y;
	Pos[2] = z;
}


void Particle::SetVel(double vx, double vy, double vz)
{
	Vel[0] = vx;
	Vel[1] = vy;
	Vel[2] = vz;
}

void Particle::SetAcc(double ax, double ay, double az)
{
	Acc[0] = ax;
	Acc[1] = ay;
	Acc[2] = az;
}

void Particle::PrintInfo(void){
    std::cout << Pos[0] << "\t" << Pos[1] << "\t" << Pos[2] << "\t" << Color << std::endl;
}


void Particle::ComputeGravPotential(class Node *A, class Particle *P)
{
	double G = 1.0,OPENING_ANGLE = 0.5;

	double r2 = pow(Pos[0]-A->CM[0],2) + pow(Pos[1]-A->CM[1],2) + pow(Pos[2]-A->CM[2],2);
//	double r = sqrt(r2);
	
	if( r2 * OPENING_ANGLE*OPENING_ANGLE > A->LengthOfBox * A->LengthOfBox  )// || A->Members.size() < 2)
	{
		GravPotential = GravPotential - G*A->M/pow( r2 + pow(Softening,2)  ,0.5);

	}
	else if( A->EndNode == 1)
	{
		for(unsigned int i=0;i<A->Members.size();i++){
			if (A->Members.at(i) == ThisParticleNumber)
			continue;

			r2 = pow(Pos[0]-P[A->Members.at(i)].GetPos(0),2) + pow(Pos[1]-P[A->Members.at(i)].GetPos(1),2) + pow(Pos[2]-P[A->Members.at(i)].GetPos(2),2);
			GravPotential = GravPotential - G*P[A->Members.at(i)].GetMass()/pow( r2 + pow(Softening,2)  ,0.5);
			
		}

	}
	else
	{
		for(int i=0;i<8;i++)
			ComputeGravPotential(A->Children[i],P);
	}
}


