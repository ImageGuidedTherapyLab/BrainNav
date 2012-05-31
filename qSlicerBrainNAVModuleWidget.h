#ifndef __qSlicerBrainNAVModuleWidget_h
#define __qSlicerBrainNAVModuleWidget_h

// CTK includes
#include <ctkPimpl.h>

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerBrainNAVModuleExport.h"

class qSlicerBrainNAVModuleWidgetPrivate;
class vtkMRMLNode;
class vtkMRMLAnnotationFiducialNode;
class vtkMRMLFiducialListNode;
class vtkMRMLAnnotationHierarchyNode;

/// \ingroup Slicer_QtModules_BrainNAV
class Q_SLICER_QTMODULES_BRAINNAV_EXPORT qSlicerBrainNAVModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT
  QVTK_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerBrainNAVModuleWidget(QWidget *parent=0);
  virtual ~qSlicerBrainNAVModuleWidget();
    
public slots:
 
  /// Get the fiducial points when the button is clicked
  void onPushButtonClicked();
  void onBtnApplicatorClicked();
  void onBtnBurnClicked();
  
protected:
  QScopedPointer<qSlicerBrainNAVModuleWidgetPrivate> d_ptr;
  
  virtual void setup();

private:
  Q_DECLARE_PRIVATE(qSlicerBrainNAVModuleWidget);
  Q_DISABLE_COPY(qSlicerBrainNAVModuleWidget);
};

#endif
