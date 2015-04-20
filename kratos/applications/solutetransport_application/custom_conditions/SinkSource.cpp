// Project includes 
#include "includes/define.h"
#include "custom_conditions/SinkSource.h"
#include "solutetransport_application.h"
#include "utilities/math_utils.h"

namespace Kratos
{
	//************************************************************************************
	//************************************************************************************
	SinkSource::SinkSource(IndexType NewId, GeometryType::Pointer pGeometry)
		: Condition(NewId, pGeometry)
	{		
		//DO NOT ADD DOFS HERE!!!
	}

	//************************************************************************************
	//************************************************************************************
	SinkSource::SinkSource(IndexType NewId, GeometryType::Pointer pGeometry,  PropertiesType::Pointer pProperties)
		: Condition(NewId, pGeometry, pProperties)
	{
	}
	Condition::Pointer SinkSource::Create(IndexType NewId, NodesArrayType const& ThisNodes,  PropertiesType::Pointer pProperties) const
	{
		return Condition::Pointer(new SinkSource(NewId, GetGeometry().Create(ThisNodes), pProperties));
	}

	SinkSource::~SinkSource()
	{
	}

	//************************************************************************************
	//************************************************************************************
	void SinkSource::CalculateRightHandSide(VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo)
	{
		KRATOS_TRY
		if(rRightHandSideVector.size() != 1)
			rRightHandSideVector.resize(1,false);

		double load = GetGeometry()[0].GetSolutionStepValue(SINK_SOURCE);
		rRightHandSideVector[0] = load;
		KRATOS_CATCH("")
	}

	//************************************************************************************
	//************************************************************************************
	void SinkSource::CalculateLocalSystem(MatrixType& rLeftHandSideMatrix, VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo)
	{
		KRATOS_TRY

		if(rLeftHandSideMatrix.size1() != 1)
			rLeftHandSideMatrix.resize(1,1,false);
		noalias(rLeftHandSideMatrix) = ZeroMatrix(1,1);
		if(rRightHandSideVector.size() != 1)
			rRightHandSideVector.resize(1,false);
		double load = GetGeometry()[0].GetSolutionStepValue(SINK_SOURCE);
		rRightHandSideVector[0] = load;
		KRATOS_CATCH("")
	}


	//************************************************************************************
	//************************************************************************************
	void SinkSource::EquationIdVector(EquationIdVectorType& rResult, ProcessInfo& CurrentProcessInfo)
	{
		int number_of_nodes = GetGeometry().PointsNumber();
		unsigned int index;
		unsigned int dim = 1;
		rResult.resize(number_of_nodes*dim);
		for (int i=0;i<number_of_nodes;i++)
		{
			index = i*dim;
			rResult[index] = (GetGeometry()[i].GetDof(TEMPERATURE).EquationId());			
		}
	}

	//************************************************************************************
	//************************************************************************************
	  void SinkSource::GetDofList(DofsVectorType& ConditionalDofList,ProcessInfo& CurrentProcessInfo)
	{
		unsigned int dim = 1;
		ConditionalDofList.resize(GetGeometry().size()*dim);
		unsigned int index;
		for (unsigned int i=0;i<GetGeometry().size();i++)
		{
			
			index = i*dim;
			ConditionalDofList[index] = (GetGeometry()[i].pGetDof(TEMPERATURE));
		}
	}
} // Namespace Kratos
