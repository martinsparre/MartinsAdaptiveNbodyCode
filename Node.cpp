#include "All.h"


Node::Node(){
    M = 0.0;
    CM[0] = CM[1] = CM[2] = 0.0;
    EndNode=0;
};

void Node::DestroyNode(void)
{

	if(EndNode != 1)
	{
		for(int i=0;i<8;i++)
			Children[i]->DestroyNode();
	}
	
	delete this;
}

void Node::CreateRoot(class Particle *P,unsigned int Np){
	
	xMin = P[0].GetPos(0);
	xMax = P[0].GetPos(0);
	yMin = P[0].GetPos(0);
	yMax = P[0].GetPos(0);
	zMin = P[0].GetPos(0);
	zMax = P[0].GetPos(0);
	
	for(unsigned int i=0;i<Np;i++)
	{
		if(P[i].GetPos(0) < xMin)
			xMin = P[i].GetPos(0);

		if(P[i].GetPos(1) < yMin)
			yMin = P[i].GetPos(1);

		if(P[i].GetPos(2) < zMin)
			zMin = P[i].GetPos(2);

		if(P[i].GetPos(0) > xMax)
			xMax = P[i].GetPos(0);

		if(P[i].GetPos(1) > yMax)
			yMax = P[i].GetPos(1);

		if(P[i].GetPos(2) > zMax)
			zMax = P[i].GetPos(2);
	}

	LengthOfBox = xMax - xMin;
	
	if( (yMax-yMin) > LengthOfBox )
			LengthOfBox = yMax - yMin;
	
	if( (zMax-zMin) > LengthOfBox )
			LengthOfBox = zMax - zMin;
			
	
	xMax = xMin + LengthOfBox;
	yMax = yMin + LengthOfBox;
	zMax = zMin + LengthOfBox;
	
    for(int i=0; i<Np; i++)
        Members.push_back(i);

}
	


void Node::CreateNodes(class Particle *P,unsigned int Np){
    
	if(Members.size() > 40)//implement direct summation if N<10 (e.g.)
	{
		CreateChildren(P,Np);

			for (int i=0;i<8;i++)
	    		Children[i]->CreateNodes(P,Np);
	}
	else
	    EndNode = 1;

}

void Node::CreateChildren(class Particle *P,unsigned int Np){


	for(unsigned int i=0;i<8;i++){
		Children[i] = new Node();

		if(!Children[i]){
		    std::cout<<"memory alloc failed"<<std::endl;
		    fflush(stdout);
		}
	}
	
	for(unsigned int i=0;i<8;i++)
		Children[i]->LengthOfBox = LengthOfBox / 2.0;


	Children[0]->xMin = xMin;
	Children[0]->yMin = yMin;
	Children[0]->zMin = zMin;

	Children[1]->xMin = xMin + Children[1]->LengthOfBox;
	Children[1]->yMin = yMin;
	Children[1]->zMin = zMin;

	Children[2]->xMin = xMin;
	Children[2]->yMin = yMin + Children[2]->LengthOfBox;
	Children[2]->zMin = zMin;

	Children[3]->xMin = xMin;
	Children[3]->yMin = yMin;
	Children[3]->zMin = zMin + Children[3]->LengthOfBox;

	Children[4]->yMin = yMin + Children[4]->LengthOfBox;
	Children[4]->xMin = xMin + Children[4]->LengthOfBox;
	Children[4]->zMin = zMin + Children[4]->LengthOfBox;
	
	Children[5]->xMin = xMin;
	Children[5]->yMin = yMin + Children[5]->LengthOfBox;
	Children[5]->zMin = zMin + Children[5]->LengthOfBox;

	Children[6]->xMin = xMin + Children[6]->LengthOfBox;
	Children[6]->yMin = yMin;
	Children[6]->zMin = zMin + Children[6]->LengthOfBox;

	Children[7]->xMin = xMin + Children[7]->LengthOfBox;
	Children[7]->yMin = yMin + Children[7]->LengthOfBox;
	Children[7]->zMin = zMin;


    for(int i=0;i<8;i++){
        Children[i]->xMax = Children[i]->xMin + Children[i]->LengthOfBox;
        Children[i]->yMax = Children[i]->yMin + Children[i]->LengthOfBox;
        Children[i]->zMax = Children[i]->zMin + Children[i]->LengthOfBox;
    }


   // for (std::vector<int>::size_type j = 0; j != Members.size(); j++){
    for (unsigned int j = 0; j < Members.size(); j++){
        unsigned int no = Members.at(j);
  
  
  
  
    int nX,nY,nZ,BoxNumber;

		nX = 2.0*(P[no].GetPos(0)-xMin) / LengthOfBox; /*the particle is in the left half of the box if nX=0. If nX!=0 the particle is in the right half of the box*/
		nY = 2.0*(P[no].GetPos(1)-yMin) / LengthOfBox;
		nZ = 2.0*(P[no].GetPos(2)-zMin) / LengthOfBox;		

		if(nX==0 && nY==0 && nZ==0)
		{
			BoxNumber = 0;
		}
		else if(nX!=0 && nY==0 && nZ==0)
		{
			BoxNumber = 1;
		}
		else if(nX==0 && nY!=0 && nZ==0)
		{
			BoxNumber = 2;
		}
		else if(nX==0 && nY==0 && nZ!=0)
		{
			BoxNumber = 3;
		}
		else if(nX!=0 && nY!=0 && nZ!=0)
		{
			BoxNumber = 4;
		}
		else if(nX==0 && nY!=0 && nZ!=0)
		{
			BoxNumber = 5;
		}
		else if(nX!=0 && nY==0 && nZ!=0)
		{
			BoxNumber = 6;
		}
		else if(nX!=0 && nY!=0 && nZ==0)
		{
			BoxNumber = 7;
		}
		else
		{
			BoxNumber = 42;
			printf("Error - 42\n");
		}
		
		Children[BoxNumber]->Members.push_back(no);

    }	
}

double Node::ComputeMass(class Particle *P,unsigned int Np){

	if(EndNode != 1)
	{
	    M = 0.0;
	    for (int i=0; i<8;i++)
	    M += Children[i]->ComputeMass(P,Np);

		return M;
	}
	else
	{
		M = 0.0;
		for(unsigned int i=0;i<Members.size();i++)
		M += P[Members.at(i)].GetMass();

		return M;
	}
}


double Node::ComputeCM(class Particle *P,unsigned int Np, int Dim){
     
    
	if(EndNode != 1)
	{
	    CM[Dim] = 0.0;
	    for (int i=0; i<8;i++)
	    CM[Dim] += Children[i]->ComputeCM(P,Np,Dim)*Children[i]->GetNodeMass();
	    
	    CM[Dim] /= GetNodeMass();

		return CM[Dim];
	}
	else if (Members.size() == 0)//this else if can likely be removed...
	{
	    CM[Dim] = 0.0;
	    return CM[Dim];
	}
	else
	{
	    
		CM[Dim] = 0.0;
		
		for(unsigned int i=0;i<Members.size();i++)
		{
    		CM[Dim] += P[Members.at(i)].GetMass()*P[Members.at(i)].GetPos(Dim);
		}

		if (GetNodeMass() > 0.0)
		CM[Dim] /= GetNodeMass();

		return CM[Dim];
	}
}

/*double Node::GetAcc(double x,double y,double z, int Dim){



	if(EndNode != 1)
	{
	    a = 0.0;
	    for (int i=0; i<8;i++)
	    a += Children[i]->GetAcc(x,y,z,Dim);

		return a;
	}
	else
	{
		a = 0.0;
		for(unsigned int i=0;i<Members.size();i++){
			double x_i[3],X[3];
			X[0] = x;
			X[1] = y;
			X[2] = z;

			x_i[0] = P[Members.at(i)].GetPos(0);
			x_i[1] = P[Members.at(i)].GetPos(1);
			x_i[2] = P[Members.at(i)].GetPos(2);
			
			double Eps2 = P[Members.at(i)].GetSoftening()*P[Members.at(i)].GetSoftening();
			
		 
			m_i = P[Members.at(i)].GetMass();
			r2 = pow(x_i[0]-X[0],2) + pow(y_i[0]-Y[0],2) + pow(z_i[0]-Z[0],2);
			r = sqrt(r2);
			
			a += m_i /( (r2+Eps2)*r  ) * (x_i[Dim] - X[Dim] )  ;
		}

		return a;
	}
	
	
}
*/


