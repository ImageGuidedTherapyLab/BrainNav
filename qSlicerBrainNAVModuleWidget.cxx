#include "ctkUtils.h"

// MRML includes
#include "vtkMRMLAnnotationHierarchyNode.h"
#include "vtkMRMLAnnotationFiducialNode.h"
#include "vtkCollection.h"
#include "vtkMRMLFiducial.h"
#include "vtkMRMLFiducialListNode.h"
#include "vtkMRMLFiducialListStorageNode.h"
#include "vtkMRMLLinearTransformNode.h"
#include "vtkMRMLScene.h"
#include "vtkMRMLDisplayNode.h"
#include "vtkMRMLModelDisplayNode.h"
#include "vtkPolyData.h"
#include <vtkLineSource.h>
#include <vtkCylinderSource.h>
#include <vtkCellArray.h>

#include "vtkSTLReader.h"

// Qt includes

// SlicerQt includes
#include "qSlicerBrainNAVModuleWidget.h"
#include "ui_qSlicerBrainNAVModule.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_BrainNAV
class qSlicerBrainNAVModuleWidgetPrivate: public Ui_qSlicerBrainNAVModule
{
public:
  qSlicerBrainNAVModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerBrainNAVModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerBrainNAVModuleWidgetPrivate::qSlicerBrainNAVModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerBrainNAVModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerBrainNAVModuleWidget::qSlicerBrainNAVModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerBrainNAVModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerBrainNAVModuleWidget::~qSlicerBrainNAVModuleWidget()
{
}
//-----------------------------------------------------------------------------
void qSlicerBrainNAVModuleWidget::setup()
{
  Q_D(qSlicerBrainNAVModuleWidget);
  d->setupUi(this);
  
  connect(this, SIGNAL(mrmlSceneChanged(vtkMRMLScene*)), d->inputFiducialsNodeSelector, SLOT(setMRMLScene(vtkMRMLScene*)));
  //connect(d->inputFiducialsNodeSelector, SIGNAL(currentNodeChanged(vtkMRMLNode*)), this, SLOT(setSeedingNode(vtkMRMLNode*)));
  connect(d->btnPath, SIGNAL(clicked()), this, SLOT(onPushButtonClicked()));
  connect(d->btnApplicator, SIGNAL(clicked()), this, SLOT(onBtnApplicatorClicked()));
  connect(d->btnBurn, SIGNAL(clicked()), this, SLOT(onBtnBurnClicked()));
  	
  this->Superclass::setup();
}
//-----------------------------------------------------------------------------
void qSlicerBrainNAVModuleWidget::onPushButtonClicked()
{
	
	//vtkMRMLNode* fiducialsNode = d_ptr->inputFiducialsNodeSelector->currentNode();

	
	//vtkMRMLFiducialListNode *fnode=vtkMRMLFiducialListNode::SafeDownCast(fiducialsNode); 
	
	//vtkMRMLAnnotationHierarchyNode *anode=vtkMRMLAnnotationHierarchyNode::SafeDownCast(fiducialsNode);

	//vtkCollection *cnodes = vtkCollection::New();	

	////if(anode->GetClassName()== "vtkMRMLAnnotationHierarchyNode")
	////{
	////	//d_ptr->label->clear();
	//	anode->GetChildrenDisplayableNodes(cnodes);

	////	
	//	int n=cnodes->GetNumberOfItems();
	//	if (n >0)
	//	{

	//		for(int i=0; i<n; i++)
	//		{
	//			d_ptr->pushButton->setText(QString::number(n));
	//			

	//			vtkMRMLFiducial *fid = vtkMRMLFiducial::SafeDownCast(cnodes->GetItemAsObject(i));
	//			if (fid != NULL)
	//			{
	//				//d_ptr->label->clear();
	//				float* xyz = fid->GetXYZ();
	//				//d_ptr->pushButton->setText(QString::number(xyz[0]));
	//			}
	//			//float coords[];
	//			//fid->GetXYZ(coords);
	//			
	//			/*vtkMRMLFiducial *fid2 = vtkMRMLFiducial::SafeDownCast(cnodes->GetItemAsObject(1));
	//			float coords2[3];
	//			fid1->GetXYZ(coords2);

	//			
	//			QString qnum= QString::number(n);
	//			d_ptr->pushButton->setText(QString::number(coords1[0]));*/
	//		}
	//	}
	////}
	//cnodes->RemoveAllItems();
	//cnodes->Delete();
	////
	// // OR Get nodes from the mrml scene...
	
	std::vector<vtkMRMLNode*> nodes;
	this->mrmlScene()->GetNodesByClass("vtkMRMLAnnotationHierarchyNode", nodes);
	
	if (nodes.size() > 1 && (d_ptr->inputFiducialsNodeSelector->currentNode() != 0))
	{		
		for (unsigned int i=0; i<nodes.size(); i++)
		{
			vtkMRMLAnnotationHierarchyNode *hnode = vtkMRMLAnnotationHierarchyNode::SafeDownCast(nodes[i]);
			vtkCollection *cnodes = vtkCollection::New();
			hnode->GetDirectChildren(cnodes);
			if (cnodes->GetNumberOfItems() > 0 && vtkMRMLAnnotationFiducialNode::SafeDownCast(cnodes->GetItemAsObject(0)) != NULL)
			{
				vtkMRMLAnnotationFiducialNode *fnode0 = vtkMRMLAnnotationFiducialNode::SafeDownCast(cnodes->GetItemAsObject(0));
				double* coors0=fnode0->GetFiducialCoordinates();
				vtkMRMLAnnotationFiducialNode *fnode1 = vtkMRMLAnnotationFiducialNode::SafeDownCast(cnodes->GetItemAsObject(1));
				double* coors1=fnode1->GetFiducialCoordinates();
								
				vtkLineSource* line=vtkLineSource::New();
				line->SetPoint1(coors0[0], coors0[1], coors0[2]);
				line->SetPoint2(coors1[0], coors1[1], coors1[2]);
							
				vtkPolyData* polydata = vtkPolyData::New();				
				polydata=line->GetOutput();
				
				vtkMRMLModelNode* modelNode=vtkMRMLModelNode::New();
				modelNode->SetScene(this->mrmlScene());
				modelNode->SetName("ApplicatorPath");
				modelNode->SetAndObservePolyData(polydata);

				vtkMRMLModelDisplayNode* modelDisplayNode=vtkMRMLModelDisplayNode::New();
				modelDisplayNode->SetColor(0,1,0); // green
				modelDisplayNode->SetScene(this->mrmlScene());
				this->mrmlScene()->AddNode(modelDisplayNode);
				modelNode->SetAndObserveDisplayNodeID(modelDisplayNode->GetID());

				modelDisplayNode->SetPolyData(modelNode->GetPolyData());
				this->mrmlScene()->AddNode(modelNode);

												
				line->Delete();
				modelNode->Delete();
				modelDisplayNode->Delete();
				polydata->Delete();
				cnodes->RemoveAllItems();
				cnodes->Delete();
				break;
			}
			cnodes->RemoveAllItems();
			cnodes->Delete();
		}
	}
	nodes.clear();	
}




void qSlicerBrainNAVModuleWidget::onBtnApplicatorClicked()
{
	vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName("C:\\Documents and Settings\\eyeniaras\\My Documents\\Downloads\\laserApplicator.stl");

	vtkMRMLModelNode* modelNode=vtkMRMLModelNode::New();
	modelNode->SetScene(this->mrmlScene());
	modelNode->SetName("Applicator");
	modelNode->SetAndObservePolyData(reader->GetOutput());
    reader->Update();

	vtkMRMLModelDisplayNode* modelDisplayNode=vtkMRMLModelDisplayNode::New();
	modelDisplayNode->SetColor(1,0,0); // green
	modelDisplayNode->SetScene(this->mrmlScene());
	this->mrmlScene()->AddNode(modelDisplayNode);
	modelNode->SetAndObserveDisplayNodeID(modelDisplayNode->GetID());

	modelDisplayNode->SetPolyData(modelNode->GetPolyData());
	this->mrmlScene()->AddNode(modelNode);

	modelNode->Delete();
	modelDisplayNode->Delete();	    
}
void qSlicerBrainNAVModuleWidget::onBtnBurnClicked()
{

}