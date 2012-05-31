/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// Qt includes
#include <QtPlugin>

// BrainNAV Logic includes
#include <vtkSlicerBrainNAVLogic.h>

// BrainNAV includes
#include "qSlicerBrainNAVModule.h"
#include "qSlicerBrainNAVModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerBrainNAVModule, qSlicerBrainNAVModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_BrainNAV
class qSlicerBrainNAVModulePrivate
{
public:
  qSlicerBrainNAVModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerBrainNAVModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerBrainNAVModulePrivate::qSlicerBrainNAVModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerBrainNAVModule methods

//-----------------------------------------------------------------------------
qSlicerBrainNAVModule::qSlicerBrainNAVModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerBrainNAVModulePrivate)
{
}

//-----------------------------------------------------------------------------
QStringList qSlicerBrainNAVModule::categories()const
{
  return QStringList() << "Developer Tools";
}

//-----------------------------------------------------------------------------
qSlicerBrainNAVModule::~qSlicerBrainNAVModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerBrainNAVModule::helpText()const
{
  QString help = 
    "This module was designed for MR guided applicator placement to brain.";
  return help;
}

//-----------------------------------------------------------------------------
QString qSlicerBrainNAVModule::acknowledgementText()const
{
  return "This work was supported by NAMIC, NAC, and the Slicer Community...";
}

//-----------------------------------------------------------------------------
QStringList qSlicerBrainNAVModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors << QString("Erol Yeniaras (MD Anderson Cancer Center)");
  // moduleContributors << QString("Richard Roe (Organization2)");
  // ...
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerBrainNAVModule::icon()const
{
  return QIcon(":/Icons/BrainNAV.png");
}

//-----------------------------------------------------------------------------
void qSlicerBrainNAVModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerBrainNAVModule::createWidgetRepresentation()
{
  return new qSlicerBrainNAVModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerBrainNAVModule::createLogic()
{
  return vtkSlicerBrainNAVLogic::New();
}
