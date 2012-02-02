#include "All.h"

Particle::Particle(double x,double y,double z,double vx,double vy,double vz,double M,double Soft)
{
	Set(x,y,z,vx,vy,vz,M,Soft);
	Color = 0.0;
	TimeStepBegin = 0;
    TimeStepEnd = 0;
}


void Particle::Set(double x,double y,double z,double vx,double vy,double vz,double M,double Soft)
{
	Pos[0] = x;
	Pos[1] = y;
	Pos[2] = z;
	Vel[0] = vx;
	Vel[1] = vy;
	Vel[2] = vz;
	m = M;
	Softening = Soft;
}



void Particle::SetColor(double color)
{
    Color=color;
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

